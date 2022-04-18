/**
 * @file ddr_target.c
 * @brief
 * Target specific DDR drivers.
 */
/*==============================================================================
                                EDIT HISTORY

$Header: //components/rel/rpm.bf/1.8/core/boot/ddr/hw/sdm660/ddr_target.c#7 $
$DateTime: 2017/03/06 22:30:00 $
$Author: pwbldsvc $
================================================================================
when       who     what, where, why
--------   ---     -------------------------------------------------------------
03/03/17   mrr     Removed Virtio validation related code
12/04/14   tw      Reworked logic around enter\exit power collapse
12/04/14   tw      Updated to include QDSS SW events
05/20/14   tw      Added support for ddr health monitor and ddr hash check
01/03/14   sr      Initial version.
================================================================================
                   Copyright 2014 Qualcomm Technologies Incorporated
                              All Rights Reserved
                     Qualcomm Confidential and Proprietary
==============================================================================*/
/*==============================================================================
                                  INCLUDES
==============================================================================*/
#include "ddr_common.h"
#include "ddr_drivers.h"
#include "ddr_internal.h"
#include "ddr_sync.h"
#include "ddr_params.h"
#include "ddr_target.h"
#include "HAL_SNS_DDR.h"
#include "ddr_log.h"
#include "npa.h"
#include "ClockDefs.h"
#include "Clock.h"
#include "mpm.h"
#include "railway.h"
#include "pm_rpm.h"
#include "PlatformInfo.h"
#include "ddr_status_reg.h"
#include "ddr_health_monitor.h"
#include "rpm_global_hash.h"
#include "CoreVerify.h"
#include "QDSSLite.h"
#include "ddr_automode.h"
#include "pm_smps.h"
#include "pm_resources_and_types.h"

/*==============================================================================
                                  MACROS
==============================================================================*/
/* Macro for round-up division */
#define div_ceil(n, d)  (((n) + (d) - 1) / (d))

#define EIGHT_SEGMENT_MASK 0xFF
#define FOUR_SEGMENT_MASK 0xF

#define UNUSED(x) (void)(x)
#define LPDDR_RAIL_PMIC_INDEX 1

/* -----------------------------------------------------------------------
**                           DATA
** ----------------------------------------------------------------------- */

/* DDR interface status, keeps track of active interfaces and their status */
extern ddr_interface_state ddr_status;

/* DDR Partition information */
ddr_size_partition ddr_size_partition_info;

/* DDR logging level */
enum ddr_log_level ddr_log_level = DDR_STATUS;

extern boolean ddr_init_done;

/* runtime hash of ddr shared parameter data */
static uint32 ddr_data_hash;

/* -----------------------------------------------------------------------
**                           FUNCTIONS
** ----------------------------------------------------------------------- */

extern boolean Clock_IsQDSSOn(void);

/* ============================================================================
**  Function : ddr_target_init
** ============================================================================
*/
/*!
*   @brief
*   This function is called at the end of ddr init to initialize any
*   target specific configurations
*
*   @details
*   Target specific configurations such as override of timing registers and
*   calling target specific init functions will be captured in this api
*
*   @param
*   None
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval  None
*
*   @sa None
*/

 __attribute__((section("ddr_init_funcs"))) void ddr_target_init()
{
  /* Railway voter variables */
  const int cx_rail_id = rail_id("vddcx");
  const int mx_rail_id = rail_id("vddmx");
  
  /* uint32      nCurClkKHz =19200, nNewClkKHz =1000; Needed for virtio validation */
  
/*  ddrsns_share_data->misc.boot_rpm_version |= (RPM_MAJOR_VERSION << 8) | RPM_MINOR_VERSION;
  if ((ddrsns_share_data->misc.boot_rpm_version & 0xFF000000) != ((ddrsns_share_data->misc.boot_rpm_version & 0x0000FF00) << 16))
  {
	DDR_LOG(DDR_ERROR, DDR_RPM_BOOT_VERSION_CHECK);
	CORE_VERIFY(0);
  }
  if (ddrsns_share_data->ddr_struct_size != sizeof(DDR_STRUCT))
  {
	DDR_LOG(DDR_ERROR, DDR_STRUCT_SIZE_CHECK);
	CORE_VERIFY(0);
  } */

  /* Update partition information */
  ddr_size_partition_info = ddr_get_partition();

  /* Initialize ddr auto mode settings */
  ddr_automode_init();
  
#if (!defined BUILD_BOOT_CHAIN) && (!defined BUILD_EHOSTDL)

  /* Register ddr driver for railway callback */
  railway_set_callback(cx_rail_id,RAILWAY_PRECHANGE_CB, ddr_pre_vddcx_switch,NULL);
  railway_set_callback(cx_rail_id,RAILWAY_POSTCHANGE_CB, ddr_post_vddcx_switch,NULL);
  railway_set_callback(mx_rail_id,RAILWAY_PRECHANGE_CB, ddr_pre_vddmx_switch,NULL);
  railway_set_callback(mx_rail_id,RAILWAY_POSTCHANGE_CB, ddr_post_vddmx_switch,NULL);
#endif
}

/* ============================================================================
**  Function : ddr_post_init
** ============================================================================
*/
/*!
*   @brief
*   This function will train the ddr at every voltage and frequency level
*   supported
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval  None
*
*   @sa None
*/

boolean ddr_post_init()
{
  return TRUE;
}

/* ============================================================================
**  Function : ddr_pre_clock_switch
** ============================================================================
*/
/*!
*   @brief
*   This function is called right before clock switching occures.
*   The function will configure the ddr such that no data loss will occur
*
*   @details
*   DDR will be stalled and new timing parameter is loaded into shadow.
*   Depending on bumping up or stepping down clock speed, we will load the
*   shadow register value to actual registers before or after clock switch
*   has occurred.
*
*   @param curr_clk   -   [IN] the current clock speed
*   @param new_clk    -  [IN] the clock speed we are switching to
*   @param new_clk    -  [IN] interface to switch clock for
*
*   @par Dependencies
*
*
*   @par Side Effects
*   None
*
*   @retval  None
*
*   @sa None
*/

void ddr_pre_clock_switch(uint32 curr_clk, uint32 new_clk,SDRAM_INTERFACE interface)
{
  DDR_LOG(DDR_STATUS, DDR_PRE_CLK_SWITCH, interface, curr_clk, new_clk);
  
  ddr_save_status_regs(PRE_CLK_VOL_SWITCH_LOGGING);

  /* perform sanity check */
  ddr_health_monitor();

  HAL_DDR_Pre_Clock_Switch(ddrsns_share_data, DDR_CH_BOTH, curr_clk, new_clk);
     
  if(new_clk > curr_clk)
  {
    ddr_automode_toggle(new_clk);
  }  
} /* ddr_pre_clock_switch */


/* ============================================================================
**  Function : ddr_clock_switch
** ============================================================================
*/
/*!
*   @brief
*   This function is called right before clock switching occures.
*   The function will configure the ddr such that no data loss will occur
*
*   @details
*   DDR will be stalled and new timing parameter is loaded into shadow.
*   Depending on bumping up or stepping down clock speed, we will load the
*   shadow register value to actual registers before or after clock switch
*   has occurred.
*
*   @param curr_clk   -   [IN] the current clock speed
*   @param new_clk    -  [IN] the clock speed we are switching to
*   @param new_clk    -  [IN] interface to switch clock for
*
*   @par Dependencies
*
*
*   @par Side Effects
*   None
*
*   @retval  None
*
*   @sa None
*/

void ddr_clock_switch(uint32 curr_clk, uint32 new_clk,SDRAM_INTERFACE interface)
{
  UNUSED(interface);
  HAL_DDR_Clock_Switch(ddrsns_share_data, DDR_CH_BOTH, curr_clk, new_clk);
} /* ddr_clock_switch */

/* ============================================================================
**  Function : ddr_post_clock_switch
** ============================================================================
*/
/*!
*   @brief
*   This function is called right after clock switching occurs.
*   The function will configure the ddr such that no data loss will occur
*
*   @details
*   DDR will be unstalled.
*   Depending on bumping up or stepping down clock speed, we will load the
*   shadow register value to actual registers before or after clock switch
*   has occurred.
*
*   @param curr_clk          -  [IN] the current clock speed
*   @param new_clk           -  [IN] the clock speed we are switching to
*   @param interface_name    -  [IN] interface to switch clock for
*
*   @par Dependencies
*   This code has to be on IRAM because ddr is unavailable during clock switching
*
*   @par Side Effects
*   None
*
*   @retval  None
*
*   @sa None
*/

void ddr_post_clock_switch(uint32 curr_clk, uint32 new_clk,SDRAM_INTERFACE interface)
{

  HAL_DDR_Post_Clock_Switch(ddrsns_share_data, DDR_CH_BOTH, curr_clk, new_clk);
  
  ddr_automode_toggle(new_clk);
  
  ddr_save_status_regs(POST_CLK_VOL_SWITCH_LOGGING);

  /* perform sanity check */
  ddr_health_monitor();
  
  DDR_LOG(DDR_STATUS, DDR_POST_CLK_SWITCH, interface, curr_clk, new_clk);

  /* update internal structure to keep track of clock speed */
  ddr_status.clk_speed = new_clk;
} /* ddr_post_clock_switch */

/* ============================================================================
**  Function : ddr_pre_vddmx_switch
** ============================================================================
*/
/*!
*   @brief
*   This function is called right before voltage switch occurs.
*
*   @param vddmx_microvolts - vddmx voltage in microvolts
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval None
*
*   @sa None
*/

void ddr_pre_vddmx_switch(const railway_settings *proposal, void * callback_cookie)
{
  /* TODO: commented temporarily as there is an issue during XO shutdown */
  //ddr_save_status_regs(PRE_CLK_VOL_SWITCH_LOGGING);
  // need to call voltage switch API in DDRSNS .

  /* perform sanity check */
  ddr_health_monitor();
} /* ddr_pre_vddmx_switch */

/* ============================================================================
**  Function : ddr_post_vddmx_switch
** ============================================================================
*/
/*!
*   @brief
*   This function is called right after voltage switch occurs.
*
*   @param vddmx_microvolts - vddmx voltage in microvolts
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval None
*
*   @sa None
*/

void ddr_post_vddmx_switch(const railway_settings *proposal, void * callback_cookie)
{
/* TODO: commented temporarily as there is an issue during XO shutdown */
  //ddr_save_status_regs(POST_CLK_VOL_SWITCH_LOGGING);
  // need to call voltage switch API in DDRSNS .

  /* perform sanity check */
  ddr_health_monitor();
  
  /* update internal structure to keep track of voltage */
  ddr_status.vddmx_voltage = proposal->mode;
} /* ddr_post_vddmx_switch */

/* ============================================================================
**  Function : ddr_pre_vddcx_switch
** ============================================================================
*/
/*!
*   @brief
*   This function is called right before vddcx switch.
*
*   @param settings - contains the VDDCX voltage level we just switched to
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval None
*
*   @sa None
*/
void ddr_pre_vddcx_switch(const railway_settings *proposal, void * callback_cookie)
{
  /* perform sanity check */
  ddr_health_monitor();
} /* ddr_pre_vddcx_switch */

/* ============================================================================
**  Function : ddr_post_vddcx_switch
** ============================================================================
*/
/*!
*   @brief
*   This function is called right after VDDCX is switched
*
*   @param none
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval None
*
*   @sa None
*/

void ddr_post_vddcx_switch(const railway_settings *proposal, void * callback_cookie)
{
  /* perform sanity check */
  ddr_health_monitor();
    
  /* update internal structure to keep track of voltage */
  ddr_status.vddcx_voltage = proposal->mode;  
} /* ddr_post_vddcx_switch */

/* ============================================================================
**  Function : ddr_pre_xo_shutdown
** ============================================================================
*/
/**
*   @brief
*   Called right before XO shutdown. Puts DDR into self refresh mode and
*   disables CDC and I/O calibration.
*
*   @param[in]  clk_speed    Current clock speed
*
*   @return
*   None
*
*   @dependencies
*   None
*
*   @sideeffects
*   None
*
*   @sa
*   ddr_post_xo_shutdown
*/

void ddr_pre_xo_shutdown(uint32 clk_speed)
{

  ddr_save_status_regs(PRE_CLK_VOL_SWITCH_LOGGING);
  
  /* perform sanity check */
  ddr_health_monitor();
  
  /* perform hash of ddr struct to ensure data integrity */
  ddr_data_hash = rpm_hash(sizeof(DDR_STRUCT),  ddrsns_share_data);
  
  ddr_enter_self_refresh_all(clk_speed);

} /* ddr_pre_xo_shutdown */

/* ============================================================================
**  Function : ddr_post_xo_shutdown
** ============================================================================
*/
/**
*   @brief
*   Called right after XO wakeup. Takes DDR out of self refresh mode and enables
*   CDC and I/O calibration.
*
*   @param[in]  clk_speed    Current clock speed
*
*   @return
*   None
*
*   @dependencies
*   None
*
*   @sideeffects
*   None
*
*   @sa
*   ddr_pre_xo_shutdown
*/

void ddr_post_xo_shutdown(uint32 clk_speed)
{

  /* perform hash check first before taking ddr out of self refresh*/
  if(ddr_data_hash != rpm_hash(sizeof(DDR_STRUCT),  ddrsns_share_data))
  {
    CORE_VERIFY(0);
  }
  ddr_exit_self_refresh_all(clk_speed);
  
  ddr_save_status_regs(POST_CLK_VOL_SWITCH_LOGGING);
  
  /* perform sanity check */
  ddr_health_monitor();
} /* ddr_post_xo_shutdown */

/* =============================================================================
**  Function : ddr_enter_power_collapse
** =============================================================================
*/
/**
*   @brief
*   Function called before DDR controller goes into power collapse.
*
*   @param[in]  clk_speed  Current clock speed (in KHz)
*
*   @retval  None
*
*   @dependencies
*   None
*
*   @sideeffects
*   None
*
*   @sa
*   None
*/
void ddr_enter_power_collapse(uint32 clk_speed)
{
  DDR_LOG(DDR_STATUS, DDR_BIMC_POWER_COLLAPSE_ENTRY);

  if (Clock_IsQDSSOn()) 
  {
     QDSSDDRTraceDisable();
  }
  /* perform sanity check */
  ddr_health_monitor();
  
  /* perform hash of ddr struct to ensure data integrity */
  ddr_data_hash = rpm_hash(sizeof(DDR_STRUCT),  ddrsns_share_data);
  
 /* ENH: please check the CDT and pass the right channel information on target basis */
  HAL_DDR_Enter_Power_Collapse(ddrsns_share_data, DDR_CH_BOTH, DDR_POWER_CLPS_MODE_BIMC_ONLY, 200000);
  HAL_DDR_Enter_Power_Collapse(ddrsns_share_data, DDR_CH_BOTH, DDR_POWER_CLPS_MODE_PHY_ONLY, 200000); 

  /*Enter auto mode retention state clock speed set to 0*/  
  ddr_automode_toggle(0);

  ddr_set_status(DDR_SELF_REFRESH);

} /* ddr_enter_power_collapse */

/* =============================================================================
**  Function : ddr_exit_power_collapse
** =============================================================================
*/
/**
*   @brief
*   Function called after DDR controller comes out of power collapse.
*
*   @param[in]  clk_speed  Current clock speed (in KHz)
*
*   @retval  None
*
*   @dependencies
*   None
*
*   @sideeffects
*   None
*
*   @sa
*   None
*/
void ddr_exit_power_collapse(uint32 clk_speed)
{
  /* perform hash check first before taking ddr out of self refresh*/
  if(ddr_data_hash != rpm_hash(sizeof(DDR_STRUCT),  ddrsns_share_data))
  {
    CORE_VERIFY(0);
  }

  /* update pmic to correct stat */
  ddr_automode_toggle(clk_speed);
    
  /* ENH: please check the CDT and pass the right channel information on target basis */
  HAL_DDR_Exit_Power_Collapse(ddrsns_share_data, DDR_CH_BOTH, DDR_POWER_CLPS_MODE_PHY_ONLY, 200000);   
  HAL_DDR_Exit_Power_Collapse(ddrsns_share_data, DDR_CH_BOTH, DDR_POWER_CLPS_MODE_BIMC_ONLY, 200000);
  
  ddr_set_status(DDR_ACTIVE);
  
  /* perform sanity check */
  ddr_health_monitor();

  if (Clock_IsQDSSOn()) 
  {
     QDSSDDRTraceEnable();
  }
  
  DDR_LOG(DDR_STATUS, DDR_EVENT_BIMC_PWR_COLLAPSE_EXIT);
} /* ddr_exit_power_collapse */

