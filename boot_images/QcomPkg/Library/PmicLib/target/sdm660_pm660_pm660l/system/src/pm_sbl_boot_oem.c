/*! \file pm_sbl_boot_oem.c
*  \n
*  \brief This file contains PMIC device initialization function where initial PMIC
*  \n SBL settings are configured through the PDM auto-generated code.
*  \n
*  \n &copy; Copyright 2015-2017 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/*===========================================================================

                        Edit History

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


when        who     what, where, why
--------    ---     ---------------------------------------------------------
07/18/17    ks      RF_CLK2.CLKBUFF_HOLD_CTL  to 0x01 (CR 2076624 )
06/30/17    ks      Added the condional code to enable/disable the RFCLK1(CR2011208)
04/10/17    ks      Configured LPI CX/MX pin controlled setting to stable solution.
03/31/17   pbitra   pm_sbl_chg_pre_init(); added a call pm_sbl_set_batt_id_forced_mode()
03/16/17    sv      Remove Charger FSM configuration for uUSB and add factory-mode configuratiion (CR#2020297)
02/09/17    sv      Enable LDO2B during bootup
12/12/16    mr      Config TypeC/uUSB Operation Mode
01/09/16    ps      Added support for PM660 and PM660L PMICs (CR-1074489)
04/29/15    aab     Updated pm_device_post_init()
12/04/15    aab     Updated to support MSM8998 target
12/04/15    aab     Creation
===========================================================================*/

/*===========================================================================

                        INCLUDE FILES

===========================================================================*/
#include <stdio.h>
#include "CoreVerify.h"

#include "boot_logger.h"

#include "DDIChipInfo.h"
#include "DALDeviceId.h"
#include "DDIPlatformInfo.h"

#include "pm_sbl_boot_target.h"
#include "pm_app_pon.h"
#include "pm_sbl_boot.h"
#include "pm_comm.h"
#include "pm_utils.h"
#include "pm_ldo.h"
#include "pm_app_vreg.h"
#include "pm_uefi.h"
#include "pm_target_information.h"
#include "pm_clk.h"



/*===========================================================================

                        TYPE DEFINITIONS

===========================================================================*/
#define PM660L_LCD_VARIENT 0x2

/*** Added for supporting multi-card tray removal feature */
#define PM_MCT_PAIRING_SLAVE_ID                 2
#define PM_MCT_PAIRING_SD_CARD_SEPARATE         0
#define PM_MCT_PAIRING_SD_CARD_UIM1             1
#define PM_MCT_PAIRING_SD_CARD_UIM2             2
#define PM_MCT_PAIRING_SD_CARD_UIM1_UIM2  		3
#define PM_MCT_PAIRING_INFO_PAIRING_MASK  		3
#define PM_MCT_PAIRING_INFO_DEBOUNCE_MASK 		0xFF
#define PM_MCT_PAIRING_INFO_DET_POLARITY_MASK   1
#define GPIO8_EN_CTL_MASK                       0x80
#define GPIO8_EN_CTL							0xc746
#define SD_UICC_PAIRING_INFO   					0xC71A //GPIO8_INT_MID_SEL  -> for setting pairing info
#define SD_CARD_DETECTION_POLARITY  		    0xC711 //GPIO8_INT_SET_TYPE -> for setting SD card Detection polarity (LOW/HIGH)

//De bounce registers which applied to GPIO on SD-Card Removal event.
//Written as Number of Cycles of 19.2 MHz clock (~52 ns) Default: 0x03C0 = 960 x 52ns = 50us
#define SD_REMOVAL_DEBOUNCE_19M_CYCLES_LSB  	0x098C // PM660L.MISC.VSET5_LB
#define SD_REMOVAL_DEBOUNCE_19M_CYCLES_MSB  	0x098D // PM660L.MISC.VSET5_UB

#define CLOCK_PERIOD         52  //19.2MHz
#define CLOCK_PERIOD_DENOM   1000

/*===========================================================================

                        FUNCTION DEFINITIONS

===========================================================================*/

/**
* pm_target_multi_card_tray_config configures the scratch registers to configure the OEM multi-card tray settings
* These settings are used in PBS RAM to handle the UICC/SDCARD removal triggers to shut down the LDOs accordingly
*
* INPUT-1: pairing_info
*           00 - Default config, SD card is handles separately
*                 01 - SD card is paired with UIM1
*                 01 - SD card is paired with UIM2
*                 01 - SD card is paired with UIM1 and UIM2
* INPUT-2: debounce  
*                 debounce delay in micro seconds.
* INPUT-3: det_polarity
*                 0 - Low
*                 1 - High
*
* Return: This function returns SPMI errors if any during communication to PMIC
* 
* Example code:
* To enable MCT when paired with UIM._UIM2_SDCARD
* err_flag |= pm_target_multi_card_tray_config(PM_MCT_PAIRING_SD_CARD_UIM1_UIM2, 50, 0); 
*/

pm_err_flag_type pm_target_multi_card_tray_config (uint8 pairing_info, uint16 debounce, uint8 det_polarity)
{
      pm_err_flag_type err_flag = PM_ERR_FLAG__SUCCESS;
      uint16 DbCycles = 0;
      uint8 DbCyclesLSB =0;
      uint8 DbCyclesMSB =0;
      
      err_flag |= pm_comm_write_byte_mask(PM_MCT_PAIRING_SLAVE_ID, GPIO8_EN_CTL, GPIO8_EN_CTL_MASK, 0x00, 1);  // Disable GPIO8
      
      err_flag |= pm_comm_write_byte_mask (PM_MCT_PAIRING_SLAVE_ID, SD_CARD_DETECTION_POLARITY, PM_MCT_PAIRING_INFO_DET_POLARITY_MASK, det_polarity, 1);
      
      //Programming Debounce delay = (Debounce delay in us) / (Clock cycle time in us)
      DbCycles = (uint16) ((uint32)debounce * CLOCK_PERIOD_DENOM) / CLOCK_PERIOD;
      DbCyclesLSB = (DbCycles & 0xFF);
      DbCyclesMSB = (DbCycles >>8);
      err_flag |= pm_comm_write_byte_mask (PM_MCT_PAIRING_SLAVE_ID, SD_REMOVAL_DEBOUNCE_19M_CYCLES_LSB, PM_MCT_PAIRING_INFO_DEBOUNCE_MASK, DbCyclesLSB, 1);
      err_flag |= pm_comm_write_byte_mask (PM_MCT_PAIRING_SLAVE_ID, SD_REMOVAL_DEBOUNCE_19M_CYCLES_MSB, PM_MCT_PAIRING_INFO_DEBOUNCE_MASK, DbCyclesMSB, 1);
      
      err_flag |= pm_comm_write_byte_mask (PM_MCT_PAIRING_SLAVE_ID, SD_UICC_PAIRING_INFO, PM_MCT_PAIRING_INFO_PAIRING_MASK, pairing_info, 1);
      
      err_flag |= pm_comm_write_byte_mask(PM_MCT_PAIRING_SLAVE_ID, GPIO8_EN_CTL, GPIO8_EN_CTL_MASK, 0x80, 1);  // Enable GPIO8
      
      return err_flag;
}

pm_err_flag_type
pm_device_pre_init(void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG__SUCCESS;
  pm_sbl_specific_data_type *config_param_ptr = NULL;

  config_param_ptr = (pm_sbl_specific_data_type*)pm_target_information_get_specific_info(PM_PROP_SBL_SPECIFIC_DATA);
  CORE_VERIFY_PTR(config_param_ptr);

  if(config_param_ptr->rfclk1_config_flag)
  {
  	err_flag |= pm_comm_write_byte(0, 0x5447, 0x0, 0);	// Do NOT follow pin control
	err_flag |= pm_comm_write_byte(0, 0x5448, 0x80, 0);	// Enable pull down for RF_CLK1 peripheral
  }
  

  return err_flag;
}

pm_err_flag_type
pm_device_post_init(void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG__SUCCESS;

  //These configurations is only used for development phones and should be commented out for production phones
  err_flag |= pm_app_pon_pshold_cfg(PM_APP_PON_CFG_WARM_RESET);
  err_flag |= pm_app_pon_reset_cfg( PM_APP_PON_RESET_SOURCE_KPDPWR, PM_APP_PON_CFG_WARM_RESET, 10256, 2000); //PON KPDPWR PON Reset configuration
  err_flag |= pm_app_pon_reset_cfg( PM_APP_PON_RESET_SOURCE_RESIN_AND_KPDPWR, PM_APP_PON_CFG_DVDD_HARD_RESET, 10256, 2000); //PON RESIN_AND_KPDPWR PON Reset configuration

  err_flag |= pm_app_pon_reset_init();

  /*check for valid PON keypress */
  err_flag |= pm_app_pwrkey_long_press_check(PM_PON_PWRKEY_DBNC_CHK_AT_LOADER);
  
  /*** Place holder code to enable multi-card removal feature ***/
 // err_flag |= pm_target_multi_card_tray_config(PM_MCT_PAIRING_SD_CARD_UIM1_UIM2, 50, 0);

  return err_flag;
}

pm_err_flag_type
pm_driver_pre_init (void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG__SUCCESS;

  return err_flag;
}


pm_err_flag_type
pm_driver_post_init (void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG__SUCCESS;
  pm_device_info_type PmicDeviceInfo;
  uint8 pmic_variant;

  pm_get_pmic_variant(PM_DEVICE_1, &pmic_variant);
  err_flag = pm_get_pmic_info(PM_DEVICE_1, &PmicDeviceInfo);
  pm_sbl_specific_data_type *config_param_ptr = NULL;

  config_param_ptr = (pm_sbl_specific_data_type*)pm_target_information_get_specific_info(PM_PROP_SBL_SPECIFIC_DATA);
  CORE_VERIFY_PTR(config_param_ptr);

  if(config_param_ptr->rfclk1_config_flag)
  {
  	err_flag |= pm_clk_sw_enable(0, PM_CLK_RF_1, PM_OFF); // Turn off RF_CLK1
  }
  
  if( ( PMIC_IS_PM660L == PmicDeviceInfo.ePmicModel) && (PM660L_LCD_VARIENT == pmic_variant) && (1 == PmicDeviceInfo.nPmicAllLayerRevision) && (0 == PmicDeviceInfo.nPmicMetalRevision) )
  {
     boot_log_message("PM660L 1.0 Have LCDB HW issue.. ");
     return PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
  }
     
     //SW WA to Enable LDO2B (SDCARD LDO), This should go in OTP.
     err_flag |= pm_ldo_sw_enable(PM_DEVICE_1,PM_LDO_2,PM_ON);

     //Configure MISC.VSET_LB to stable solution(0x02)
     /* This should have been handled in SBL config, but SBL config has the best power optimised solution as default,
        once all agreed to this solution, it can move back to sbl config.*/
     err_flag |= pm_comm_write_byte_mask(2, 0x98E, 0xFF, 0x02, 0);
     //PM660L.LDO10.FOLLOW_HWEN  
     err_flag |= pm_comm_write_byte_mask(3, 0x4947, 0xFF, 0x80, 0);
     //PM660L.LDO09.FOLLOW_HWEN
     err_flag |= pm_comm_write_byte_mask(3, 0x4847, 0xFF, 0x80, 0);
     
     //WA: set RF_CLK2.CLKBUFF_HOLD_CTL  to 0x01
     err_flag |= pm_comm_write_byte_mask(0, 0x5545, 0xFF, 0x01, 0);

  return err_flag;
}

pm_err_flag_type
pm_sbl_chg_pre_init (void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG__SUCCESS;

  /*  Start battery id conversion in continuous mode.
      Next image (UEFI) would need to stop this mode */
  err_flag = pm_sbl_set_batt_id_forced_mode(TRUE);
  
  return err_flag;
}

pm_err_flag_type
pm_sbl_chg_post_init (void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG__SUCCESS;

  return err_flag;
}

