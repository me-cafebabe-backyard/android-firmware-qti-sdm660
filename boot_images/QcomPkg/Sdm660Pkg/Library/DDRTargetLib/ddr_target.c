/**
 * @file ddr_target.c
 * @brief
 * Target specific DDR drivers.
 */
/*==============================================================================
                                EDIT HISTORY

================================================================================
when       who     what, where, why
--------   ---     -------------------------------------------------------------
03/27/17   din     Added voltage settings for VSEL_1 of ext buck
03/06/17   mrr     Added ext buck detection
02/25/17   din     Increased SL max freq to 1804Mhz
02/25/17   din     Reduced SL max freq to 1555MHz
02/22/17   din     Added ext buck voltage bump up & SL max freq to 1804Mhz
02/07/17   din     Increased SH max freq to 1296Mhz
02/07/17   din     Increased SH max freq to 768Mhz & Enabled training for SH
02/07/17   mrr     Added platform check to differentiate b/w SL & SH
09/14/16   qbz     optimized training restore from calling twice to once
06/16/16   qbz     added ddr_do_phy_training_DDI
07/28/15   rp      Added ddr_post_training function to support conditional loading of ddr training
07/20/15   tw      enable one time training
07/01/15   tw      added bimc remapper api call
06/20/14   tw      added ddr_pre_init api to capture any target specific 
                   workarounds that needs to be applied prior to ddr init
05/28/14   tw      cleaned up sbl <-> ddr driver dependencies around ddr training
                   implementation of cx\mx\cpr hash to force retraining
03/12/14   sr      Initial version.
================================================================================
                   Copyright 2014-2017 Qualcomm Technologies Incorporated
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
#include "ddr_log.h"
#include "ddr_params.h"
#include "ddr_target.h"
#include "HAL_SNS_DDR.h"
#include "ddr_config.h"
#include "ClockBoot.h"
#include "icbcfg.h"
#include <stddef.h>
#include "ddr_external.h"
#include "pm_ldo.h"
#include "CoreVerify.h"
#include "cpr.h"
#include "crc.h"
#include "boot_extern_platforminfo_interface.h"
#include "boothw_target.h"
#include "busywait.h"
#include "boot_cache_mmu.h"
#include "pm_smps.h"
#include "pm_resources_and_types.h"
#include "DDIPlatformInfo.h"
#include "ddr_hwio.h"
#include "boot_build_component.h"
#include "boot_page_table_armv8.h"
#include "boot_error_if.h"
#include "I2cDevice.h"

#define TRAINING_ENABLED TRUE
#define ONE_TIME_TRAINING TRUE
#define STARLORD_DDR_MAX_FREQ           1804800
#define STARHAWK_DDR_MAX_FREQ 			1296000
#define BLACKBOLT_DDR_MAX_FREQ      1353600

#define STARLORD_PLTFORM 0x3006
#define STARHAWK_PLTFORM 0x3007

boolean starhawk_platform = FALSE;

/*==============================================================================
                                  MACROS
==============================================================================*/
/* Macro for round-up division */
#define div_ceil(n, d)  (((n) + (d) - 1) / (d))

#define EIGHT_SEGMENT_MASK                           0xFF
#define FOUR_SEGMENT_MASK                            0xF

#define LPDDR_RAIL_PMIC_INDEX                         1
#define MSM_VERSION_MASK 							 (3<<25)

#define I2C_SLAVE_ADDR                               0x60
#define I2C_BUS_FREQ                                 400
#define TRANSFER_TIMEOUT_US                          2500
#define EXT_BUCK_ID_REG                              0x03
#define EXT_BUCK_SEL0_REG                            0x00
#define EXT_BUCK_SEL1_REG                            0x01
#define PM3003_ID                                    0xA8
#define MISC_LP4X_PRESENT                            0x0992
#define DRAX_MISC_SLAVE_ADDR                         0x2
#define EXT_BUCK_VDDQ                                0x83 // Set to 0.61875v 


/*==============================================================================
                                  DATA
==============================================================================*/
/* DDR interface status, keeps track of active interfaces and their status */
extern ddr_interface_state ddr_status;

/* DDR Partition information */
ddr_size_partition ddr_size_partition_info;

extern ddr_info ddr_physical_size;
extern ddr_size_info ddr_system_size;

 
static railway_voter_t ebi_pin = NULL;
static I2CDEV_HANDLE  handle = NULL;
/*==============================================================================
                                  FUNCTIONS
==============================================================================*/
extern pm_err_flag_type pm_comm_read_byte(uint32 slave_id, uint16 addr, uint8* data, uint8 priority);

static uint32 ddr_i2c_buck_read(uint8 offset, uint8 *data)
{
    I2cClientConfig config = {I2C_BUS_FREQ, TRANSFER_TIMEOUT_US};
    int32 i2cResult = I2C_RES_SUCCESS;
    I2cBuffDesc     rdIoVecs[2];
    I2cTransfer     rdTrans[2];
    I2cSequence     rdSeq;
    I2cIoResult     ioRes;
       
    rdIoVecs[0].pBuff     = &offset;
    rdIoVecs[0].uBuffSize = 1;
    
    rdTrans[0].pI2cBuffDesc       = &rdIoVecs[0];
    rdTrans[0].uTrSize            = rdIoVecs[0].uBuffSize;
    rdTrans[0].tranCfg.uSlaveAddr = I2C_SLAVE_ADDR;
    rdTrans[0].eTranDirection     = I2cTranDirOut;
    rdTrans[0].eTranCtxt          = I2cTrCtxNotASequence;

    rdIoVecs[1].pBuff             = data;
    rdIoVecs[1].uBuffSize         = 1;
    rdTrans[1].pI2cBuffDesc       = &rdIoVecs[1];
    rdTrans[1].uTrSize            = rdIoVecs[1].uBuffSize;
    rdTrans[1].tranCfg.uSlaveAddr = I2C_SLAVE_ADDR;
    rdTrans[1].eTranDirection     = I2cTranDirIn;
    rdTrans[1].eTranCtxt          = I2cTrCtxNotASequence;
    
    rdSeq.pTransfer     = rdTrans;
    rdSeq.uNumTransfers  = 2;
    i2cResult = I2CDEV_BatchTransfer(handle, &rdSeq, &config, &ioRes);
    if(i2cResult != I2C_RES_SUCCESS)
    {
      return -1;
    }
    
    return 0x0;
}

static uint32 ddr_i2c_buck_write(uint8 offset, uint8 data)
{
    I2cClientConfig config = {I2C_BUS_FREQ, TRANSFER_TIMEOUT_US};
    int32 i2cResult = I2C_RES_SUCCESS;

    I2cBuffDesc rdIoVecs[2];
    I2cTransfer rdTrans;
    uint32 uWriteSize;

    rdIoVecs[0].pBuff          = &offset;
    rdIoVecs[0].uBuffSize      = 1; // 1 byte register offset
    rdIoVecs[1].pBuff          = &data;
    rdIoVecs[1].uBuffSize      = 1; // 1 byte data would be written

    rdTrans.pI2cBuffDesc       = rdIoVecs;
    rdTrans.uTrSize            = rdIoVecs[0].uBuffSize + rdIoVecs[1].uBuffSize;
    rdTrans.tranCfg.uSlaveAddr = I2C_SLAVE_ADDR;
    rdTrans.eTranDirection     = I2cTranDirOut;
    rdTrans.eTranCtxt          = I2cTrCtxNotASequence;

    i2cResult = I2CDEV_Write(handle, &rdTrans, &config, &uWriteSize);
    if(i2cResult != I2C_RES_SUCCESS)
    {
      return -1;
    }
    
    return 0x0;
}

static void ddr_ext_buck_set_voltage(void)
{
  uint32 result = 0;
  uint32 device_id = DALDEVICEID_I2C_DEVICE_2;
  uint8 data;
           
  result = I2CDEV_Init(((void *)(INTN)device_id), &handle);
  if(I2C_RES_SUCCESS != result)
  {
    boot_log_message("Ext Buck I2C Init Error");
    return;
  }

  // Bus on, clock on
  result = I2CDEV_SetPowerState(handle, I2CDEV_POWER_STATE_2);
  if(I2C_RES_SUCCESS != result)
  {
    boot_log_message("Ext Buck I2C Power Set Error");
    I2CDEV_DeInit(handle);
    return;
  }
  if(ddr_i2c_buck_read (EXT_BUCK_ID_REG, &data) == 0)
  {
    ddrsns_share_data->misc.ext_buck_id = data;
    if (data == PM3003_ID)
    {
      result = ddr_i2c_buck_write(EXT_BUCK_SEL0_REG, EXT_BUCK_VDDQ);
      if (result != 0)
      {
        boot_log_message("VSEL_0 Ext Buck Set Voltage Error");
      }
      result = ddr_i2c_buck_write(EXT_BUCK_SEL1_REG, EXT_BUCK_VDDQ);
      if (result != 0)
      {
        boot_log_message("VSEL_1 Ext Buck Set Voltage Error");
      }
    }
  }

  result = I2CDEV_SetPowerState(handle, I2CDEV_POWER_STATE_0);
  if(I2C_RES_SUCCESS != result)
  {
    boot_log_message("Ext Buck I2C Power Set Error");
  }

  I2CDEV_DeInit(handle);
}




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

void ddr_target_init()
{
  uint8 nNumLevel, i;
  uint32 chip_plat_ver_info;
  uint32 qfprom_row5;
  uint32 jtag_id;
  ClockPlanType   *pClockPlan;
  uint8  lp4x_ext_buck_present = 0;
  uint32 err;
  DalPlatformInfoPlatformType platform = DalPlatformInfo_Platform();
  
  /* The current function where target silicon flag is set is not called for deviceprogrammer
    Adding it in ddr_target_init.
    To-do: Clean it up so we don't have the check called twice */
  if (platform != DALPLATFORMINFO_TYPE_RUMI)
  {
    ddrsns_share_data->misc.target_silicon = 1;
  }
  
  if (ddrsns_share_data->misc.target_silicon == 1)
  {
    if (PcdGet32 (PcdBuildType) == SBL_BUILD_SBL)
    {
      int rail = rail_id("vddmx");
      CORE_VERIFY(rail!=RAIL_NOT_SUPPORTED_BY_RAILWAY);    
      ebi_pin = railway_create_voter(rail, RAILWAY_DDR_TRAINING_VOTER_ID);
      railway_corner_vote(ebi_pin, RAILWAY_NOMINAL);
      railway_transition_rails();
    
      err = pm_smps_sw_mode(LPDDR_RAIL_PMIC_INDEX, PM_SMPS_5, PM_SW_MODE_NPM); // VDDmx SMPS5 to PWM
      CORE_VERIFY(err == PM_ERR_FLAG__SUCCESS);
      err = pm_smps_sw_mode(LPDDR_RAIL_PMIC_INDEX, PM_SMPS_3, PM_SW_MODE_NPM); // CX SMPS3 to PWM
      CORE_VERIFY(err == PM_ERR_FLAG__SUCCESS);
      err = pm_smps_sw_mode(LPDDR_RAIL_PMIC_INDEX, PM_SMPS_1, PM_SW_MODE_NPM); 
      CORE_VERIFY(err == PM_ERR_FLAG__SUCCESS);    
      ddr_ext_buck_set_voltage(); /* Set External VDDQ voltage */
    }
  }
  
  chip_plat_ver_info =  HWIO_IN(TCSR_SOC_HW_VERSION);
  qfprom_row5 = HWIO_INM(QFPROM_RAW_CALIB_ROW5_MSB, MSM_VERSION_MASK);
  jtag_id =  (HWIO_IN(JTAG_ID) & DEVICE_MASK) >> 12;
  
  /* extract upper 16 bit and store it in platform field of ddr_misc */
  ddrsns_share_data->misc.platform_id  = chip_plat_ver_info >> 16 /*& 0xFFFF0000*/ ;
  
  if(ddrsns_share_data->misc.platform_id == STARLORD_PLTFORM)
  {
	  starhawk_platform = FALSE;
  }
  else if(ddrsns_share_data->misc.platform_id == STARHAWK_PLTFORM)
  {
	  starhawk_platform = TRUE;
  }
  
  /* extract lower 16 bits and store it in version field of ddr_misc */
  if (qfprom_row5 != 0)
  {
    ddrsns_share_data->misc.chip_version  = 0x101;
  }
  else
  {
    ddrsns_share_data->misc.chip_version  = chip_plat_ver_info & 0x0000FFFF ;
  }
  
  
  /* Extract the MSM_PKG_TYPE from QFPROM register */
  ddrsns_share_data->misc.package_type = HWIO_INF(QFPROM_RAW_FEAT_CONFIG_ROW4_MSB , MSM_PKG_TYPE);

  Clock_BIMCQuery(CLOCK_RESOURCE_QUERY_NUM_PERF_LEVELS,&nNumLevel);
  CORE_VERIFY((DALSYS_Malloc(nNumLevel * sizeof(ClockPlanType), (void **)&pClockPlan) == DAL_SUCCESS));

  if ( pClockPlan == NULL )
  {
    return;
  }
  Clock_BIMCQuery(CLOCK_RESOURCE_QUERY_ALL_FREQ_KHZ,pClockPlan);
  
  for(i=0;i<nNumLevel;i++)
  {
    ddrsns_share_data->misc.clock_plan[i].clk_freq_in_khz  = pClockPlan[i].nFreqKHz;
    ddrsns_share_data->misc.clock_plan[i].clk_mode         = pClockPlan[i].eMode;
  }
  
  if(jtag_id == MSM_SDM636_ID || jtag_id == MSM_SDA636_ID)
  {
    ddrsns_share_data->misc.max_ddr_frequency = BLACKBOLT_DDR_MAX_FREQ;
  }
  else if(starhawk_platform == TRUE)
  {
    ddrsns_share_data->misc.max_ddr_frequency = STARHAWK_DDR_MAX_FREQ;
  }
  else
  {
    ddrsns_share_data->misc.max_ddr_frequency = STARLORD_DDR_MAX_FREQ;
  }
  
  ddrsns_share_data->misc.misc_cfg[0] = 1;
  
  /* This call is made in order to know the voltage level , 
   * for determining whether we have LP4 or LP4x on the chip */

  err = pm_comm_read_byte(DRAX_MISC_SLAVE_ADDR , MISC_LP4X_PRESENT , &lp4x_ext_buck_present , 0 );
  CORE_VERIFY(err == PM_ERR_FLAG__SUCCESS); 

  if(lp4x_ext_buck_present == 1){
     ddrsns_share_data->detected_ddr_device[0].device_type = DDR_TYPE_LPDDR4X;
     ddrsns_share_data->detected_ddr_device[1].device_type = DDR_TYPE_LPDDR4X;	
  }
  
  if (ddrsns_share_data->misc.chip_version == 0x100)
  {
    ddrsns_share_data->detected_ddr_device[0].interleave_en = 0;
    ddrsns_share_data->detected_ddr_device[1].interleave_en = 0;
  }
 
  DALSYS_Free(pClockPlan);
}

/* ============================================================================
**  Function : ddr_pre_init
** ============================================================================
*/
/*!
*   @brief
*   This function is called before ddr is initialized. It will take care of any
*   pre initialization workarounds.
*
*   @details
*   This function is called before ddr is initialized. It will take care of any
*   pre initialization workarounds.
*
*   @param
*   boolean -
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
boolean ddr_pre_init()
{
  return TRUE;
}


/* ============================================================================
**  Function : ddr_post_init
** ============================================================================
*/
/*!
*   @brief
*   This function is called after ddr is initialized. It will take care of any
*   post initialization activities such as ddr training.
*
*   @details
*   This function is called after ddr is initialized. It will take care of any
*   post initialization activities such as ddr training.
*
*   @param
*   boolean -
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
  char ddr_log_string[50];
  snprintf (ddr_log_string, 50, "DSF version = %d.%d, DSF RPM version = %d.%d", 
            ((ddrsns_share_data->version) >> 16),((ddrsns_share_data->version) & 0x0000FFFF),
             ((ddrsns_share_data->rpm_version) >> 16),((ddrsns_share_data->rpm_version) & 0x0000FFFF));
  boot_log_message(ddr_log_string);


	Clock_SetDDRMinMax( 2, ddrsns_share_data->misc.ddr_num_clock_levels-1 );
	snprintf (ddr_log_string, 50, "Max Frequency = %d MHz", 
            (ddrsns_share_data->misc.clock_plan[ddrsns_share_data->misc.ddr_num_clock_levels-1].clk_freq_in_khz)/1000);
	boot_log_message(ddr_log_string);  


  if(ddrsns_share_data->misc.target_silicon == 1)
  {
    if (PcdGet32 (PcdBuildType) == SBL_BUILD_SBL)
    {
      railway_corner_vote(ebi_pin, RAILWAY_NO_REQUEST);
      railway_transition_rails();
    }
  }
  /* ddr_struct_cookie is added, to prevent the memset of ddr_struct to 0 during warm reset*/
  ddrsns_share_data->misc.ddr_struct_cookie = DDR_STRUCT_COOKIE;
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

void ddr_pre_clock_switch(uint32 curr_clk, uint32 new_clk , SDRAM_INTERFACE interface_name)
{
     HAL_DDR_Pre_Clock_Switch(ddrsns_share_data, (DDR_CHANNEL)interface_name, curr_clk, new_clk);
} /* ddr_pre_clock_switch */


/* ============================================================================
**  Function : ddr_clock_switch
** ============================================================================
*/
/*!
*   @brief
*   This function is called right after pre clock switching function.
*   The function will actually do the real clock switch
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

void ddr_clock_switch(uint32 curr_clk, uint32 new_clk , SDRAM_INTERFACE interface_name)
{
    HAL_DDR_Clock_Switch(ddrsns_share_data, (DDR_CHANNEL)interface_name, curr_clk, new_clk);
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

void ddr_post_clock_switch(uint32 curr_clk, uint32 new_clk, SDRAM_INTERFACE interface_name)
{
     HAL_DDR_Post_Clock_Switch(ddrsns_share_data, (DDR_CHANNEL)interface_name , curr_clk, new_clk);
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

void ddr_pre_vddmx_switch(uint32 vddmx_microvolts)
{
  /* Stepping Down in VDDCX voltage */
  ddr_status.vddmx_voltage = vddmx_microvolts;
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

void ddr_post_vddmx_switch(uint32 vddmx_microvolts)
{

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
void ddr_pre_vddcx_switch(uint32 vddcx_microvolts)
{
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

void ddr_post_vddcx_switch(uint32 vddcx_microvolts)
{
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
  ddr_exit_self_refresh_all(clk_speed);

} /* ddr_post_xo_shutdown */

/* ============================================================================
**  Function : ddr_check_partition
** ============================================================================
*/
/*!
*   @brief
*   A helper function for ddr_dmm_partition to check the given interface and partition
*   whether we can put into dpd or full\partial self refresh
*
*   @details
*   Given the retention and active state, put the corresponding ddr interface
*   into self refresh, or deep power down when possible
*
*   Truth table for active and retention state:
*                        Active State:0         |      Active_state:1
*   Retention_state:0    self refresh/dpd       |      Invalid config, assume to be
*                                               |      Active retention
*   Retention_state:1    self refresh retention |      Active Retention
*
*   @param interface_name   -  [IN] the interface to check for
*   @param chip_sel         -  [IN] the chip select on the interface to check for
*   @param retention_state  -  [IN] the retention state for the partitions given
*   @param active_state     -  [IN] the active state for the partitions given
*   @param num_partitions   -  [IN] the number of partitions on this interface
*
*   @par Dependencies
*   None
*
*   @par Side Effects
*   None
*
*   @retval
*   None
*
*   @sa None
*/
void ddr_check_partition(DDR_CHANNEL interface_name, SDRAM_CHIPSELECT chip_sel, uint32 retention_state, uint32 active_state, uint8 num_partitions)
{

} /* ddr_check_partition */

/* ============================================================================
**  Function : ddr_dmm_partition
** ============================================================================
*/
/*!
*   @brief
*   Given the retention and active state, put the corresponding ddr interface
*   into self refresh, or deep power down when possible
*
*   @details
*   Given the retention and active state, put the corresponding ddr interface
*   into self refresh, or deep power down when possible
*
*   Truth table for active and retention state:
*                        Active State:0         |      Active_state:1
*   Retention_state:0    self refresh/dpd       |      Invalid config, assume to be
*                                               |      Active retention
*   Retention_state:1    self refresh retention |      Active Retention
*
*   @param retention_state  -  [IN] the retention state for the partitions given
*   @param active_state     -  [IN] the active state for the partitions given
*
*   @par Dependencies
*   Caller of this API has to take care not to put ddr interface that is in use
*   into self refresh or deep power down.
*
*   @par Side Effects
*   None
*
*   @retval
*  None
*
*   @sa None
*/

void ddr_dmm_partition(uint32 retention_state, uint32 active_state)
{
}
/* =============================================================================
**  Function : ddr_params_is_training_required
** =============================================================================
*/
/**
*   @brief
*   Indicate whether DDR parameter training is required or not. Training is
*   required if and only if DDR itself (e.g. PCDDR3) requires parameter training
*   and DDR parameter partition is invalid. LPDDR3 will always require training syncronization
*   to be done between rpm and sbl
*
*   @param  None
*
*   @retval  TRUE   Training required
*   @retval  FALSE  Training not required
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
boolean ddr_params_is_training_required( void )
{
  DalPlatformInfoPlatformType platform = DalPlatformInfo_Platform();
  if (platform != DALPLATFORMINFO_TYPE_RUMI)
  {
    ddrsns_share_data->misc.target_silicon = 1;
    return TRAINING_ENABLED;
  }
  else
    return FALSE;
} /* ddr_params_is_training_required */


/* ============================================================================
**  Function : ddr_is_training_required
** ============================================================================
*/
/*!
*   @brief
*   This function will parse the crc hash and determine if training is required
*   based on serial number, mx\cx\rbcpr hash
*
*   @details
*   This function will parse the crc hash and determine if training is required
*   based on serial number, mx\cx\rbcpr hash
*
*   @param
*   None
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval  boolean - Training required/Not required
*
*   @sa None
*/
boolean ddr_is_training_required(void)
{
  uint32 serial_number;
  uint32 check_sum = 0;


  
  /* cx/mx/vdda hash variables */
  uint32 combined_checksum = cpr_cx_mx_settings_checksum();

  /* compare checksum for training data in our partition with DDR_STRUCT to see if training is required */
  serial_number = BOOT_HWIO_IN(QFPROM_RAW_PTE_ROW1_LSB , 0);

  ddr_printf ( DDR_NORMAL, "DDR: The serial number is %d", serial_number);

  /* combine serial number with voltage checksum for a new seed */
  combined_checksum = serial_number ^ combined_checksum;

  check_sum = ddr_get_training_checksum(combined_checksum);

  ddr_printf (DDR_NORMAL, "DDR: Checksum on flash is %d", ddrsns_share_data->flash_params.checksum);
  ddr_printf (DDR_NORMAL, "DDR: Recomputed checksum is %d", check_sum);

  if (ddrsns_share_data->flash_params.checksum  != check_sum)
  {
    ddr_printf (DDR_NORMAL, "DDR: Training is required");

    return TRUE;
  }

  ddr_printf (DDR_NORMAL, "DDR: Training is not required");
  return FALSE;
} /* ddr_is_training_required */

/* =============================================================================
**  Function : ddr_set_bootup_freq
** =============================================================================
*/
/**
*   @brief
*   Set the boot up frequency
*
*   @param  None
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
void ddr_set_bootup_freq( void )
{
    char ddr_log_string[50];
    uint32 ddr_boot_up_freq = 1296000;
	
	uint32 ddr_max_num_levels_freq = ddrsns_share_data->misc.clock_plan[ddrsns_share_data->misc.ddr_num_clock_levels-1].clk_freq_in_khz;
	
	if(ddr_max_num_levels_freq < ddr_boot_up_freq)
	{
	    Clock_SetBIMCSpeed(ddr_max_num_levels_freq); 
		snprintf (ddr_log_string, 50, "Bootup frequency set to sw_override frequency %u", ddr_max_num_levels_freq);
	}
	else
	{
        Clock_SetBIMCSpeed(ddr_boot_up_freq); 
		snprintf (ddr_log_string, 50, "Bootup frequency set to %u", ddr_boot_up_freq);
	}
	boot_log_message(ddr_log_string);
} /* ddr_set_bootup_freq */

/* =============================================================================
**  Function : ddr_do_phy_training_init
** =============================================================================
*/
/**
*   @brief
*   Indicates that PHY training needs to be done in SBL1.
*
*   @param  None
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
void ddr_do_phy_training_init( void )
{
    ddr_printf (DDR_NORMAL, "DDR: Start of HAL DDR Boot Training");
    HAL_DDR_Boot_Training_Init(ddrsns_share_data, DDR_CH_BOTH, DDR_CS_BOTH);	
	ddr_set_bootup_freq(); 
	ddr_printf (DDR_NORMAL, "DDR: End of HAL DDR Boot Training");
} /* ddr_do_phy_training */

/* =============================================================================
**  Function : ddr_do_phy_training_restore
** =============================================================================
*/
/**
*   @brief
*   Restore training data results, if phy training is already done
*
*   @param  None
*
*   @retval  TRUE   Training required
*   @retval  FALSE  Training not required
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
boolean ddr_do_phy_training_restore( void )
{

#if ONE_TIME_TRAINING
  boolean training_restore = FALSE;
  /* Boot training */
  if((ddr_is_training_required() == TRUE)||
				((training_restore=HAL_DDR_Boot_Training_Restore(ddrsns_share_data, DDR_CH_BOTH, DDR_CS_BOTH)) == FALSE))
#endif
  {
    /* training data corrupted, memclr training data to force a retraining */
    memset(&ddrsns_share_data->flash_params, 0x0, sizeof(struct ddr_params_partition));

    return TRUE;

  }
#if ONE_TIME_TRAINING
  else if(training_restore == TRUE){
	ddr_printf (DDR_NORMAL, "DDR: DDR training mode check failed");
	ddr_set_bootup_freq();
      
	return FALSE;
  }

  else {
     return FALSE;
  }
#endif

} /* ddr_do_phy_training */

/* =============================================================================
**  Function : ddr_post_training
** =============================================================================
*/
/**
*   @brief
*   This function is called after ddr training. It will take care of all post
*   training activities such as computing checksum over training data.
*
*   @param  None
*
*   @retval  TRUE If one time training is enabled
*   @retval  FALSE If one time training is disabled
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
boolean ddr_post_training(void)
{
  uint32 serial_number;
  uint32 combined_checksum = cpr_cx_mx_settings_checksum();
  
  serial_number = BOOT_HWIO_IN(QFPROM_RAW_PTE_ROW1_LSB , 0);

  /* combine serial number with voltage checksum for a new seed */
  combined_checksum = serial_number ^ combined_checksum;

  /* update training data checksum */
  ddr_set_training_checksum(combined_checksum);

  /* update training data and log size */
  ddrsns_share_data->flash_params.training_data_size = sizeof(ddrsns_share_data->flash_params.training_data);
  ddrsns_share_data->flash_params.training_log_size = ddr_external_get_training_log_size();

  return ONE_TIME_TRAINING;
}

/*  Remapper Table 
    This table and code will need to be updated based on newer DDR configurations 
*/
RemapperTable RemapTable[] =
{
/* remapping configurations */
  
/*             SCMO_CS0  SCMO_CS1                 rank_detected  cs0_size cs1_size cs0_remap_size cs1_remap_size  BIMC_Remap_CS0 BIMC_Remap_CS1 */
/* 1GB Single Rank    { 0x0   N/A         } */    {DDR_CS0,       0x400,  0x0,     0x400,          0x0,           0x80000000,              0},
/* 2GB Single Rank    { 0x0   N/A         } */    {DDR_CS0,       0x800,  0x0,     0x800,          0x0,           0x80000000,              0},
/* 2GB Dual Rank    { 0x0,  0x80000000  }*/       {DDR_CS_BOTH,   0x400,  0x400,   0x400,          0x0,           0xC0000000,              0},
/* 3GB Single Rank    { 0x0   N/A         } */    {DDR_CS0 ,      0xC00,  0x0,     0xC00,          0x0,           0x80000000,              0},
/* 3GB Dual Rank(1+2) { 0x0   0x80000000  } */    {DDR_CS_BOTH,   0x400,  0x800,   0x400,          0x0,           0x100000000,             0},
/* 3GB Dual Rank(1.5+1.5){ 0x0  0x80000000  } */  {DDR_CS_BOTH,   0x600,  0x600,   0x600,          0x600,         0x40000000,     0xA0000000},
/* 3GB Dual Rank(2+1) { 0x0   0x80000000  } */    {DDR_CS_BOTH,   0x800,  0x400,   0x800,          0x0,           0xC0000000,              0},
/* 4GB Single Rank    { 0x0   N/A         } */    {DDR_CS0,       0x1000, 0x0,     0x1000,         0x0,           0x80000000,              0},
/* 4GB Dual Rank(1+3) { 0x0   0x100000000 } */    {DDR_CS_BOTH,   0x400,  0xC00,   0x400,          0x400,         0x80000000,    0x180000000},
/* 4GB Dual Rank(2+2) { 0x0   0x100000000 } */    {DDR_CS_BOTH,   0x800,  0x800,   0x800,          0x0,           0x80000000,              0},
/* 4GB Dual Rank(3+1) { 0x0   0x100000000 } */    {DDR_CS_BOTH,   0xC00,  0x400,   0xC00,          0x0,           0x40000000,              0},
/* 6GB Dual Rank(2+4) { 0x0   0x80000000 } */     {DDR_CS_BOTH,   0x800,  0x1000,  0x800,          0x0,           0x80000000,             0},
/* 6GB Dual Rank(3+3) { 0x0   0x80000000 } */     {DDR_CS_BOTH,   0xC00,  0xC00,   0xC00,          0x0,           0x40000000,              0},
/* 6GB Dual Rank(4+2) { 0x0   0x100000000 } */    {DDR_CS_BOTH,   0x1000, 0x800,   0x800,          0x0,           0x180000000,             0},
/* 8GB Dual Rank(4+4) { 0x0,    0x100000000 } */  {DDR_CS_BOTH,   0x1000, 0x1000,  0x1000,         0x1000,        0x80000000,    0x180000000}

};

/* =============================================================================
**  Function : ddr_remapper
** =============================================================================
*/
/**
*   @brief
*   configures ddr to be remapped based on density
*
*   @param void
*
*   @retval  void
*
*   @dependencies
*   ddr initialization has already finished
*
*   @sideeffects
*   None
*
*   @sa
*   None
*/
void ddr_remapper(void)
{
  icbcfg_remap_info_type remap_info;
  uint64 remap_size = 0;

  uint8 cs=0, index;
  RemapperTable *Remap_Tbl_ptr = RemapTable;
  uint8 remap_table_size = (sizeof(RemapTable)/sizeof(RemapTable[0]));
  DDR_CHIPSELECT chip_select = ddrsns_share_data->detected_ddr_device[0].populated_chipselect;
  uint8 cs_loop_inx = 0;

  /*
    remapping configurations
    
                      SCMO CS0   SCMO CS1      BIMC Remapper CS0  BIMC Remapper CS1
    3GB Single Rank   0x0        N/A           0x80000000         N/A
    3GB Dual Rank     0x0        0x80000000    0x100000000        N/A
    4GB Dual Rank     0x0        0x100000000   0x80000000         N/A
    4GB Single Rank   0x0        N/A           0x80000000         N/A
    6GB Dual Rank     0x0        0x100000000   0x40000000         N/A
    8GB Dual Rank     0x0        0x100000000   0x80000000         0x180000000
  */

    /* Find the correct index in the remapper table */
	if (ddrsns_share_data->misc.chip_version == 0x100 && starhawk_platform == FALSE) {
	    ddrsns_share_data->ddr_size_info.ddr0_cs0_remapped_addr = ddr_system_size.sdram0_cs0_addr = 0;
	    ddrsns_share_data->ddr_size_info.ddr0_cs1_remapped_addr = ddr_system_size.sdram0_cs1_addr = 0;
	    ddrsns_share_data->ddr_size_info.ddr1_cs1_remapped_addr = ddr_system_size.sdram1_cs1_addr = 0x80000000;
		ddrsns_share_data->ddr_size_info.ddr1_cs0_remapped_addr = ddr_system_size.sdram1_cs0_addr = ddr_system_size.sdram1_cs1_addr + (ddrsns_share_data->ddr_size_info.ddr1_cs1_mb << 20) ;//0x100000000;
	    ddrsns_share_data->ddr_size_info.ddr0_cs0_mb= ddr_system_size.sdram0_cs0 = 0;
	    ddrsns_share_data->ddr_size_info.ddr0_cs1_mb= ddr_system_size.sdram0_cs1 = 0;
		
   return;
  }
		
  for (index = 0; index < remap_table_size; index++)
  {

    if(((ddr_system_size.sdram0_cs0 + ddr_system_size.sdram1_cs0) == Remap_Tbl_ptr[index].cs0_size) && 
      ((ddr_system_size.sdram0_cs1 + ddr_system_size.sdram1_cs1) == Remap_Tbl_ptr[index].cs1_size) && 
      (Remap_Tbl_ptr[index].rank_detected == chip_select)) 
	 	break;
  }
  
  if(index >= remap_table_size)
    ddr_printf (DDR_ERROR, "**ERROR Can't find a matching entry in the DDR remapper table**");
  else
  {
    for(cs = DDR_CS1; cs >= DDR_CS0; cs--) {

      remap_info.dest_addr = (cs == DDR_CS0)? Remap_Tbl_ptr[index].bimc_remapper_cs0 : Remap_Tbl_ptr[index].bimc_remapper_cs1;
      remap_info.src_addr = (cs == DDR_CS0)?ddrsns_share_data->ddr_size_info.ddr0_cs0_addr: ddrsns_share_data->ddr_size_info.ddr0_cs1_addr;
  
      remap_size = (cs == DDR_CS0)? Remap_Tbl_ptr[index].cs0_remap_size : Remap_Tbl_ptr[index].cs1_remap_size;
      remap_size *= 1024 * 1024; /* ram size is in byte */
    
      remap_info.size = remap_size;
      remap_info.interleaved = ICBCFG_REMAP_INTERLEAVE_DEFAULT;
      remap_info.deinterleave = FALSE;

      /* if dest addr is 0, will skip mapping */
      if(0 == remap_info.dest_addr) {
         if(cs == DDR_CS1) {
              ddrsns_share_data->ddr_size_info.ddr0_cs1_remapped_addr = ddrsns_share_data->ddr_size_info.ddr0_cs1_addr;
              ddrsns_share_data->ddr_size_info.ddr1_cs1_remapped_addr = ddrsns_share_data->ddr_size_info.ddr1_cs1_addr;
        }
        continue;
      }

      ICB_RemapEx("/dev/icbcfg/boot", &ddr_physical_size, cs_loop_inx, &remap_info);

      if(cs == DDR_CS0) {
        /* update internal variable to track new mapping */
        ddrsns_share_data->ddr_size_info.ddr0_cs0_remapped_addr = ddr_system_size.sdram0_cs0_addr = remap_info.dest_addr;
        ddrsns_share_data->ddr_size_info.ddr1_cs0_remapped_addr = ddr_system_size.sdram1_cs0_addr = remap_info.dest_addr;

      }
      else if(cs == DDR_CS1) {
        ddrsns_share_data->ddr_size_info.ddr0_cs1_remapped_addr = ddr_system_size.sdram0_cs1_addr = remap_info.dest_addr;
        ddrsns_share_data->ddr_size_info.ddr1_cs1_remapped_addr = ddr_system_size.sdram1_cs1_addr = remap_info.dest_addr;
      }
      
      cs_loop_inx ++;
    }
    ddr_printf (DDR_NORMAL, "Remapped addresses ddr0_cs0 is %X, ddr1_cs0 is %X, ddr0_cs1 is %X, ddr1_cs1 is %X", 
	  	                              ddrsns_share_data->ddr_size_info.ddr0_cs0_remapped_addr,
	  	                              ddrsns_share_data->ddr_size_info.ddr1_cs0_remapped_addr,
	  	                              ddrsns_share_data->ddr_size_info.ddr0_cs1_remapped_addr,
	  	                              ddrsns_share_data->ddr_size_info.ddr1_cs1_remapped_addr);
  }

} /* ddr_remapper */


