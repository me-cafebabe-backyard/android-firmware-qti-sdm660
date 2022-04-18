/*! \file pm_rpm_target.c
*  \n
*  \brief This file contains PMIC functions to run sleep enter and sleep exit settings.
*  \n
*  &copy; Copyright 2013-2016 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

$Header: //components/rel/rpm.bf/1.8/core/pmic/pm/target/sdm660_pm660_pm660i/src/pm_rpm_target.c#8 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
02/24/17    as      DDR threshold freq for auto mode set default to mode_3(CR#2011417)
02/20/17    as      Halo buck changes (CR#2008912)
01/18/17    as      DDR Phy check has been removed (CR1113035)
01/16/17    as      ddr threshold has been changed and MISC_PERIPHERAL has been detected (CR1111900)
09/10/15    kt      Initial version.
12/20/16    as      SLPI changes for LDO9B and LDO10B (CR 1103422) 
===========================================================================*/
/*===========================================================================

                     INCLUDE FILES

===========================================================================*/
#include "CoreVerify.h"
#include "pm_comm.h"
#include "pm_target_information.h"
#include "pm_sleep.h"
#include "pm_sleep_config.h"
#include "pm_rpm.h"
#include "pm_npa.h"
#include "npa.h"
#include "pm_rpm_target.h"
#include "pm_config.h"
#include "pm_rpm_ldo_trans_apply.h"
#include "railway.h"
#include "pm_npa_irep.h"

/*===========================================================================

                 LOCAL CONSTANT AND MACRO DEFINITIONS

===========================================================================*/
#define MISC_LP4X_PRESENT                              0x0992


#define PMI_PMIC_INDEX  1  //PMIC index for interface pmic

#define SW_EN_MASK                                  0x80

#define DRAX_MISC_SLAVE_ADDR                         0x2
#define DRAX_MISC_BASE_ADDRESS                            0x900

//SSC_MX
#define DRAX_MISC_VSET3_L10_RETENTION_ADDRESS_LB         (DRAX_MISC_BASE_ADDRESS + 0x88)
#define DRAX_MISC_VSET3_L10_RETENTION_ADDRESS_UB         (DRAX_MISC_BASE_ADDRESS + 0x89)
#define DRAX_MISC_VSET4_L10_ACTIVE_ADDRESS_LB            (DRAX_MISC_BASE_ADDRESS + 0x8A)
#define DRAX_MISC_VSET4_L10_ACTIVE_ADDRESS_UB            (DRAX_MISC_BASE_ADDRESS + 0x8B)
//SSC_CX 
#define DRAX_MISC_VSET1_L9_RETENTION_ADDRESS_LB          (DRAX_MISC_BASE_ADDRESS + 0x84)
#define DRAX_MISC_VSET1_L9_RETENTION_ADDRESS_UB          (DRAX_MISC_BASE_ADDRESS + 0x85)
#define DRAX_MISC_VSET2_L9_ACTIVE_ADDRESS_LB             (DRAX_MISC_BASE_ADDRESS + 0x86)
#define DRAX_MISC_VSET2_L9_ACTIVE_ADDRESS_UB             (DRAX_MISC_BASE_ADDRESS + 0x87)


#define GPIO12B_SLAVE_ADDR                            0x02
#define GPIO12B_BASE_ADDR                             0x0000CB00
#define GPIO12B_STATUS1_ADDR                          (GPIO12B_BASE_ADDR + 0x00000008)
#define GPIO12B_EN_CTL                                (GPIO12B_BASE_ADDR + 0x00000046)
#define GPIO12B_DIG_OUT_SOURCE_CTL                    (GPIO12B_BASE_ADDR + 0x00000044)

/*===========================================================================

                        STATIC VARIABLES

===========================================================================*/

static pm_sleep_cfg_type* sleep_enter_settings = NULL;
static pm_sleep_cfg_type* sleep_exit_settings = NULL;

static npa_client_handle handle_ddr = NULL;

static uint8 ebi_settling_err = 0; //0x1 ->settling err, 0x2 spmi read error

static uint32 g_thr_ddr_freq_for_auto_mode = PMIC_NPA_MODE_ID_DDR_CFG_3;


//static boolean pm_ddrx_config_flag = FALSE;

/*===========================================================================

                        FUNCTION DEFINITIONS

===========================================================================*/

/**
 * @name pm_rpm_sleep_init
 *
 * @brief Initializes the sleep settings LUT.
 *
 * @param  sleep_mode: can be vdd_min/XO shutdown
 *
 * @return None.
 *
 * @sideeffects None.
 *
 * @sideeffects Sleep settings should be available in config.
 *
 */
__attribute__((section("pm_dram_reclaim_pool")))
void pm_rpm_sleep_init()
{
    sleep_enter_settings = (pm_sleep_cfg_type*)pm_target_information_get_specific_info(PM_PROP_SLEEP_ENTER_INFO);
    sleep_exit_settings = (pm_sleep_cfg_type*)pm_target_information_get_specific_info(PM_PROP_SLEEP_EXIT_INFO);
    CORE_VERIFY((sleep_enter_settings != NULL) && (sleep_exit_settings != NULL));
}

/**
 * @name pm_rpm_enter_sleep
 *
 * @brief This function calls the driver layer PMIC calls to set
 *        the Rails to the state prior to entering sleep.
 *
 * @param  sleep_mode: can be vdd_min/XO shutdown
 *
 * @return PMIC error code.
 *
 * @sideeffects Will over-write any client configuration
 *              requests. Any additions to the below function
 *              should be cautiously be added.
 *
 */
pm_err_flag_type
pm_rpm_enter_sleep (pm_sleep_mode_type sleep_mode)
{
    uint32 i = 0;
    pm_err_flag_type err_flag = PM_ERR_FLAG__SUCCESS;
    const pm_sleep_cfg_type* p_settings;

    if (sleep_mode > PM_SLEEP_MODE_VDD_MIN)
    {
      return PM_ERR_FLAG__PAR1_OUT_OF_RANGE;
    }

    p_settings = &sleep_enter_settings[(uint16)sleep_mode];

    /* Two config data arrays on enter sleep: XO_SHUTDOWN and VDD_MIN.
       "The VDD_MIN one has a copy of the XO_SHUTDOWN data most likely."   */
    while( (p_settings->p_cfg[i].regAddr != 0xFFFF) &&
          (err_flag == PM_ERR_FLAG__SUCCESS) )
    {
      err_flag |= pm_comm_write_byte( p_settings->p_cfg[i].slaveID,
                              p_settings->p_cfg[i].regAddr,
                              p_settings->p_cfg[i].data, 0 );
      i++;
    }

    return err_flag;
}

/**
 * @name pm_rpm_exit_sleep
 *
 * @brief This function calls the driver layer PMIC calls to set
 *        the Rails back to the prior state of entering sleep.
 *
 * @param sleep_mode: can be vdd_min/XO shutdown
 *
 * @return PMIC error code.
 *
 * @sideeffects Will restore any client configuration requests.
 *              Any additions to the below function should be
 *              cautiously be added.
 *
 */
pm_err_flag_type
pm_rpm_exit_sleep (pm_sleep_mode_type sleep_mode)
{
    uint32 i = 0;
    pm_err_flag_type err_flag = PM_ERR_FLAG__SUCCESS;
    const pm_sleep_cfg_type* p_settings;

    (void)ebi_settling_err ;

    if (sleep_mode > PM_SLEEP_MODE_VDD_MIN)
    {
       return PM_ERR_FLAG__PAR1_OUT_OF_RANGE;
    }
    p_settings = &sleep_exit_settings[(uint16)sleep_mode];

    /* Two config data arrays on exit sleep: XO_SHUTDOWN and VDD_MIN.
      "The VDD_MIN one has a copy of the XO_SHUTDOWN data most likely."  */
    while( (p_settings->p_cfg[i].regAddr != 0xFFFF) &&
          (err_flag == PM_ERR_FLAG__SUCCESS) )
    {
      err_flag |= pm_comm_write_byte( p_settings->p_cfg[i].slaveID,
                              p_settings->p_cfg[i].regAddr,
                              p_settings->p_cfg[i].data, 0) ;
      i++;
    }

    return err_flag;
}


__attribute__((section("pm_dram_reclaim_pool")))
void pm_rpm_platform_pre_init(void)
{
  
   
}

static uint8  g_is_lp4x_ext_buck_present = 0;

__attribute__((section("pm_dram_reclaim_pool")))
void pm_rpm_platform_init(void)
{
   pm_err_flag_type err_flag = PM_ERR_FLAG__SUCCESS;
    
  // PM660L GPIO11B status decides which DDR is used - if LPDDR4x, use GPIO12B for mode control
  err_flag = pm_comm_read_byte(DRAX_MISC_SLAVE_ADDR , MISC_LP4X_PRESENT , &g_is_lp4x_ext_buck_present , 0 );
  if(err_flag != PM_ERR_FLAG__SUCCESS) 
  {
     abort();
  }

}

pm_err_flag_type pm_rpm_platform_post_init(void)
{
   pm_err_flag_type err_flag = PM_ERR_FLAG__SUCCESS;

   if(handle_ddr == NULL)
   {

      //create handle for DDR 
      handle_ddr = npa_create_sync_client(PMIC_NPA_GROUP_ID_DDR, "ddr", NPA_CLIENT_REQUIRED);
      if(handle_ddr == NULL)
      {
         abort();
      }
   }
   
   
   return err_flag;
}

/* pm_npa_rpm_set_auto_mode_thr() API called before pm_npa_rpm_smps_auto_mode_config() API in automode.c file to update threshold freq */

pm_err_flag_type pm_npa_rpm_set_auto_mode_thr (uint32 lp4x_buck_auto_mode_thr)
{
    pm_err_flag_type err_flag = PM_ERR_FLAG__SUCCESS;
	
    g_thr_ddr_freq_for_auto_mode = lp4x_buck_auto_mode_thr; // exposed to boot driver to update threshold freq 
	
    return err_flag;
    
}


pm_err_flag_type pm_npa_rpm_smps_auto_mode_config(uint32  ddr_cfg)
{
   pm_err_flag_type err_flag = PM_ERR_FLAG__SUCCESS;

    if((ddr_cfg >= PMIC_NPA_MODE_ID_DDR_CFG_MAX) || (NULL == handle_ddr) )
   {
      return PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
   }


   npa_issue_required_request(handle_ddr, ddr_cfg);

    //ext buck presence
    if (0 !=  g_is_lp4x_ext_buck_present)
   {
        // get g_thr_ddr_freq_for_auto_mode threshold from boot 
        if ( ddr_cfg > g_thr_ddr_freq_for_auto_mode )
       {
        err_flag = pm_comm_write_byte(GPIO12B_SLAVE_ADDR, GPIO12B_EN_CTL, 0x80, 0); //Enable the GPIOB12 to control the PWM mode assuming that DIG_OUT_SOURCE_CTL ≠ 0x80 previously
        err_flag = pm_comm_write_byte(GPIO12B_SLAVE_ADDR, GPIO12B_DIG_OUT_SOURCE_CTL, 0x80, 0); // Write 0x80 on GPIO12B_DIG_OUT_SOURCE_CTL register to decrease ramp time
       }
       else
       {
        err_flag = pm_comm_write_byte(GPIO12B_SLAVE_ADDR, GPIO12B_DIG_OUT_SOURCE_CTL, 0x00, 0);
        err_flag = pm_comm_write_byte(GPIO12B_SLAVE_ADDR, GPIO12B_EN_CTL, 0x00, 0);

       }
   }

   return err_flag;
}


pm_err_flag_type pm_npa_rpm_verify_smps_mode(uint32 ddr_cfg)
{
   

   if(NULL == handle_ddr)
   {
      return PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
   }

   

   return PM_ERR_FLAG__SUCCESS;
}

pm_err_flag_type pm_rpm_check_battery_status(pm_battery_status_type *batt_status)
{
   return PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
}

pm_err_flag_type 
pm_rpm_target_execute_smps_pre_enable(uint8 pmic_index, uint8 smps_index, pm_on_off_type sw_en, 
                                      boolean *continue_enable_flag)
{
    pm_err_flag_type err_flag = PM_ERR_FLAG__SUCCESS;

    // Enable SMPS2C (MSS rail) in NPA layer and 
    // ignore the disable request
    if((smps_index == 1) && (pmic_index == 2))
    {
        if(sw_en == PM_ON)
        {
            *continue_enable_flag = TRUE;
        }
        else
        {
            *continue_enable_flag = FALSE;
        }
    }

    return err_flag;
}

void pm_pbs_client_driver_init(pm_comm_info_type *comm_ptr, peripheral_info_type *peripheral_info, uint8 pmic_index)
{
   // stub to avoid compilation error and save memory by not compiling pbs driver
}


void pm_fg_driver_init(pm_comm_info_type *comm_ptr, peripheral_info_type *peripheral_info, uint8 pmic_index)
{
   // stub to avoid compilation error 
}


void pm_boost_driver_init(pm_comm_info_type *comm_ptr, peripheral_info_type *peripheral_info, uint8 pmic_index)
{
   // stub to avoid compilation error 
   CORE_VERIFY(0);
}

// TODO just for debugging purpose to be removed later 

uint8  g_retention_voltage[2] = { 0 };
uint8  g_active_voltage[2] = { 0 };


/* update the active and retention spare registers on first SSC_CX/MX vote. */
pm_err_flag_type
pm_rpm_target_pre_dependency_execute(rpm_application_info *info)
{
   pm_err_flag_type err_flag = PM_ERR_FLAG__SUCCESS;
   pm_npa_ldo_int_rep *ldo_current_aggregation = (pm_npa_ldo_int_rep *)(info->current_aggregation);
   uint8 ldo_index = ldo_current_aggregation->resource_id - 1;
   pm_register_address_type retention_spare_lb = 0;
   pm_register_address_type active_spare_lb = 0;
   uint32 retention_voltage_mv = 0x00;
   uint8  voltage_level[2] = { 0 };
   int  rail = 0;
   static boolean ssc_cx_pre_init_done = FALSE;
   static boolean ssc_mx_pre_init_done = FALSE;

   if(((ldo_index != PM_LDO_9)&& (ldo_index != PM_LDO_10)) 
      ||((ldo_index == PM_LDO_10)&& (ssc_mx_pre_init_done == TRUE)) 
      ||((ldo_index == PM_LDO_9)&& (ssc_cx_pre_init_done == TRUE)) 
      ||(ldo_current_aggregation->device_index != 1))
   {
      return err_flag;
   }

   switch(ldo_index)
   {
   case PM_LDO_9: //CX - SSC_CX is LDO9B
      rail = rail_id("vdd_lpi_cx");
      CORE_VERIFY(RAIL_NOT_SUPPORTED_BY_RAILWAY != rail);
      retention_spare_lb = DRAX_MISC_VSET1_L9_RETENTION_ADDRESS_LB;
      active_spare_lb = DRAX_MISC_VSET2_L9_ACTIVE_ADDRESS_LB;
      ssc_cx_pre_init_done = TRUE;
      break;
   case PM_LDO_10 : //MX - - SSC_MX is LDO10B
      rail = rail_id("vdd_lpi_mx");
      CORE_VERIFY(RAIL_NOT_SUPPORTED_BY_RAILWAY != rail);
      retention_spare_lb = DRAX_MISC_VSET3_L10_RETENTION_ADDRESS_LB;
      active_spare_lb = DRAX_MISC_VSET4_L10_ACTIVE_ADDRESS_LB;
      ssc_mx_pre_init_done = TRUE;
      break;
   default:
      return err_flag;
   }
    /* get and store retention lpi_cx_mx voltage level*/
    retention_voltage_mv = railway_get_corner_voltage(rail,  RAILWAY_RETENTION) / 1000; 
    voltage_level[0] =  (uint8)(retention_voltage_mv & 0xFF);
    voltage_level[1] =  (uint8)((retention_voltage_mv >> 8) & 0xFF);
    g_retention_voltage[0] = voltage_level[0];
    g_retention_voltage[1] = voltage_level[1];
    err_flag = pm_comm_write_byte_array(DRAX_MISC_SLAVE_ADDR, retention_spare_lb, 2, voltage_level, 0);

    /* get and store active lpi_cx_mx voltage level*/
    voltage_level[0] =  (uint8)((ldo_current_aggregation->output_uvol/1000) & 0xFF);
    voltage_level[1] =  (uint8)(((ldo_current_aggregation->output_uvol/1000) >> 8) & 0xFF);
    g_active_voltage[0] = voltage_level[0];
    g_active_voltage[1] = voltage_level[1];
    err_flag |= pm_comm_write_byte_array(DRAX_MISC_SLAVE_ADDR, active_spare_lb, 2, voltage_level, 0);

   return err_flag;
}




