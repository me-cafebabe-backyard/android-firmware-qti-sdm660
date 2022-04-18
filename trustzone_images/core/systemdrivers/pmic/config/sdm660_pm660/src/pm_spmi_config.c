/*! \file
*  \n
*  \brief  pm_spmi_config.c
*  \n
*  \n This file contains pmic configuration data specific for SPMI Controller's
      Peripheral for MSM8996 device..
*  \n
*  \n &copy; Copyright 2015-2016 QUALCOMM Technologies, Incorporated, All Rights Reserved
*/
/* =======================================================================
Edit History
This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/core.tz/1.0.7.1/systemdrivers/pmic/config/sdm660_pm660/src/pm_spmi_config.c#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
02/16/17   as      Reverting PBS_CLIENT2 owner to Modem and GPIO11A access has been given to APPS(CR#2007718)
02/10/17   as      Adding missing peripheral LDO4B(0x43 )(CR#2005189)
01/30/17   as      On 0x19 and 0x3F peripheral access has been given to Hlos and modem (CR1112923)
01/12/17   as      LDO9a&10a rpm owner , Ldo15a&17a  MSS owner (CR1110718)
06/09/16   aab     Updated to the latest access control doc 
08/25/15   vtw     Created.
========================================================================== */

/*-------------------------------------------------------------------------
* Include Files
* ----------------------------------------------------------------------*/

#include "pm_spmi.h"

/*-------------------------------------------------------------------------
* Preprocessor Definitions and Constants
* ----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
* Static Variable Definitions
* ----------------------------------------------------------------------*/

/* PMIC MMU/SMMU configuration table. */

SpmiCfg_ChannelCfg pm_spmi_pheriph_cfg [] =
{
  /* PM660 */
  {0, 0x01, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* REVID */
  {0, 0x04, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* BUS */
  {0, 0x05, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* INT */
  {0, 0x06, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* SPMI */
  {0, 0x08, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER    }, /* PON */
  {0, 0x09, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER    }, /* MISC */
  {0, 0x0B, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* VREF_MSM */
  
  {0, 0x10, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER    }, /* SCHG8998_CHGR */
  {0, 0x11, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER    }, /* SCHG8998_OTG */
  {0, 0x12, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER    }, /* SCHG8998_BATIF */
  {0, 0x13, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER    }, /* SCHG8998_USB */
  {0, 0x14, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER    }, /* SCHG8998_DC */
  {0, 0x15, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER    }, /* QNOVO */
  {0, 0x16, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER    }, /* SCHG8998_MISC */
  {0, 0x17, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER    }, /* USB_PD_PHY */
  {0, 0x18, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER    }, /* SCHG8998_OTP_HDR */
  {0, 0x19, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER    },/* SCHG_CHGR_FREQ */
  {0, 0x1B, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER    }, /* BSI */

  {0, 0x1C, 0, PM_MSS_OWNER, PM_MSS_OWNER    }, /* BUA_EXT_CHARGER */
  {0, 0x24, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER    }, /* TEMP_ALARM */
  {0, 0x28, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER    }, /* COIN */
  {0, 0x2C, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* MBG1 */
  {0, 0x31, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER    }, /* VADC_HM1_USR */
  {0, 0x32, 0, PM_MSS_OWNER, PM_MSS_OWNER    }, /* VADC_HM2_MDM */
  {0, 0x34, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER    }, /* VADC_HC7_BTM8 */
  {0, 0x35, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER    }, /* VADC_HC5_VBAT */
  {0, 0x37, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER    }, /* VADC_HM4_CAL */
  {0, 0x38, 0, PM_MSS_OWNER, PM_MSS_OWNER    }, /* VADC_HM9_BTM_2 */
  {0, 0x39, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER    }, /* VADC_HM10_CMN */
  {0, 0x3C, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* VDDGEN */
  


  {0, 0x40, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER    }, /* FG_BATT_SOC */
  {0, 0x41, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER    }, /* FG_BATT_INFO */
  {0, 0x42, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER    }, /* FG_BCL */
  {0, 0x43, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER    }, /* FG_LMH */
  {0, 0x44, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER    }, /* FG_MEM_IF */
  {0, 0x45, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER    }, /* FG_ADC_RR */
  {0, 0x46, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER    }, /* FG_FT_HDR */
  {0, 0x48, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER    }, /* FG_DMA0 */
  {0, 0x49, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER    }, /* FG_DMA1 */
  {0, 0x4A, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER    }, /* FG_DMA2 */
  {0, 0x4B, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER    }, /* FG_DMA3 */

  {0, 0x50, 0, PM_MSS_OWNER, PM_MSS_OWNER    }, /* XO */
  {0, 0x51, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* LN_BB_CLK1 */
  {0, 0x52, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* LN_BB_CLK2 */
  {0, 0x53, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* LN_BB_CLK3 */
  {0, 0x54, 0, PM_MSS_OWNER, PM_MSS_OWNER    }, /* RF_CLK1 */
  {0, 0x55, 0, PM_MSS_OWNER, PM_MSS_OWNER    }, /* RF_CLK2 */
  {0, 0x59, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* CLK_DIST */
  {0, 0x5A, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* SLEEP_CLK1 */
  {0, 0x5B, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* DIV_CLK1 */
  {0, 0x60, 0, PM_MSS_OWNER, PM_MSS_OWNER    }, /* RTC_RW */
  {0, 0x61, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER    }, /* RTC_ALARM */
  {0, 0x62, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER    }, /* RTC_TIMER */

  {0, 0x70, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* PBS_CORE */
  {0, 0x71, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* PBS_CLIENT0 */
  {0, 0x72, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* PBS_CLIENT1 */
  {0, 0x73, 0, PM_MSS_OWNER, PM_MSS_OWNER    }, /* PBS_CLIENT2 */
  {0, 0x74, 0, PM_MSS_OWNER, PM_MSS_OWNER    }, /* PBS_CLIENT3 */

  {0, 0xC0, 0, PM_MSS_OWNER, PM_MSS_OWNER    }, /* GPIO01 */
  {0, 0xC1, 0, PM_APPS_HLOS_OWNER,  SPMI_OPEN_OWNER    }, /* GPIO02 */
  {0, 0xC2, 0, PM_APPS_HLOS_OWNER,  SPMI_OPEN_OWNER    }, /* GPIO03 */
  {0, 0xC3, 0, PM_APPS_HLOS_OWNER,  SPMI_OPEN_OWNER    }, /* GPIO04 */
  {0, 0xC4, 0, PM_APPS_HLOS_OWNER,  SPMI_OPEN_OWNER    }, /* GPIO05 */
  {0, 0xC5, 0, PM_APPS_HLOS_OWNER,  SPMI_OPEN_OWNER    }, /* GPIO06 */
  {0, 0xC6, 0, PM_APPS_HLOS_OWNER,  SPMI_OPEN_OWNER    }, /* GPIO07 */
  {0, 0xC7, 0, PM_APPS_HLOS_OWNER,  SPMI_OPEN_OWNER    }, /* GPIO08 */
  {0, 0xC8, 0, PM_APPS_HLOS_OWNER,  SPMI_OPEN_OWNER    }, /* GPIO09 */
  {0, 0xC9, 0, PM_APPS_HLOS_OWNER,  SPMI_OPEN_OWNER    }, /* GPIO10 */
  {0, 0xCA, 0, PM_APPS_HLOS_OWNER, SPMI_OPEN_OWNER    }, /* GPIO11 */
  {0, 0xCB, 0, PM_APPS_HLOS_OWNER,  SPMI_OPEN_OWNER    }, /* GPIO12 */
  {0, 0xCC, 0, PM_APPS_HLOS_OWNER,  SPMI_OPEN_OWNER    }, /* GPIO13 */

  

  {1, 0x01, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* REVID1 */
  {1, 0x10, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* BUCK_CMN_MOD */
  {1, 0x14, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER    }, /* S1_CTRL */
  {1, 0x15, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER    }, /* S1_PS */
  {1, 0x16, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER    }, /* S1_FREQ */
  {1, 0x17, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER    }, /* S2_CTRL */
  {1, 0x18, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER    }, /* S2_PS */
  {1, 0x19, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER    }, /* S2_FREQ */
  {1, 0x1A, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER    }, /* S3_CTRL */
  {1, 0x1B, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER    }, /* S3_PS */
  {1, 0x1C, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER    }, /* S3_FREQ */
  {1, 0x1D, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* S4_CTRL */
  {1, 0x1E, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* S4_PS */
  {1, 0x1F, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* S4_FREQ */
  {1, 0x20, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* S5_CTRL */
  {1, 0x21, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* S5_PS */
  {1, 0x22, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* S5_FREQ */
  {1, 0x23, 0, PM_MSS_OWNER, PM_MSS_OWNER    }, /* S6_CTRL */
  {1, 0x24, 0, PM_MSS_OWNER, PM_MSS_OWNER    }, /* S6_PS */
  {1, 0x25, 0, PM_MSS_OWNER, PM_MSS_OWNER    }, /* S6_FREQ */



  {1, 0x40, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* LDO01 */
  {1, 0x41, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* LDO02 */
  {1, 0x42, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* LDO03 */
   /* LDO4B is not defined for Groot */
  {1, 0x44, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* LDO05 */
  {1, 0x45, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* LDO06 */
  {1, 0x46, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* LDO07 */
  {1, 0x47, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* LDO08 */
  {1, 0x48, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* LDO09 */
  {1, 0x49, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* LDO10 */
  {1, 0x4A, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* LDO11 */
  {1, 0x4B, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* LDO12 */
  {1, 0x4C, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* LDO13 */
  {1, 0x4D, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* LDO14 */
  {1, 0x4E, 0, PM_MSS_OWNER, PM_MSS_OWNER    }, /* LDO15 */
  {1, 0x4F, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* LDO16 */
  {1, 0x50, 0, PM_MSS_OWNER, PM_MSS_OWNER    }, /* LDO17 */
  {1, 0x51, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* LDO18 */
  {1, 0x52, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* LDO19 */

  {1, 0xC0, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER    }, /* HAPTICS */

  /* PM660L */


  {2, 0x01, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* REVID */
  {2, 0x04, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* BUS */
  {2, 0x05, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* INT */
  {2, 0x06, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* SPMI */
  {2, 0x08, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER    }, /* PON */
  {2, 0x09, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER    }, /* MISC */



  {2, 0x20, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER    }, /* ALARM BCL_D */
  {2, 0x21, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER    }, /* ALARM BCL_D_PLM */
  {2, 0x24, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER    }, /* TEMP_ALARM */

  {2, 0x2C, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* MBG1 */
  {2, 0x3C, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* VDDGEN */

  {2, 0x3F, 0, PM_MSS_OWNER, PM_MSS_OWNER    }, /* ALARM BCL_COMP_LITE */

  {2, 0x59, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* CLK_DIST */
  {2, 0x66, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* SPMI_MONITOR */
  {2, 0x70, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* PBS_CORE */
  {2, 0x71, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* PBS_CLIENT0 */
  {2, 0x72, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* PBS_CLIENT1 */
  {2, 0x73, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER    }, /* PBS_CLIENT2 */
  {2, 0xC0, 0, PM_APPS_HLOS_OWNER,  SPMI_OPEN_OWNER    }, /* GPIO01 */
  {2, 0xC1, 0, PM_APPS_HLOS_OWNER,  SPMI_OPEN_OWNER    }, /* GPIO02 */
  {2, 0xC2, 0, PM_APPS_HLOS_OWNER,  SPMI_OPEN_OWNER    }, /* GPIO03 */
  {2, 0xC3, 0, PM_APPS_HLOS_OWNER,  SPMI_OPEN_OWNER    }, /* GPIO04 */
  {2, 0xC4, 0, PM_APPS_HLOS_OWNER,  SPMI_OPEN_OWNER    }, /* GPIO05 */
  {2, 0xC5, 0, PM_APPS_HLOS_OWNER,  SPMI_OPEN_OWNER    }, /* GPIO06 */
  {2, 0xC6, 0, PM_APPS_HLOS_OWNER,  SPMI_OPEN_OWNER    }, /* GPIO07 */
  {2, 0xC7, 0, PM_APPS_HLOS_OWNER,  SPMI_OPEN_OWNER    }, /* GPIO08 */
  {2, 0xC8, 0, PM_APPS_HLOS_OWNER,  SPMI_OPEN_OWNER    }, /* GPIO09 */
  {2, 0xC9, 0, PM_APPS_HLOS_OWNER,  SPMI_OPEN_OWNER    }, /* GPIO10 */
  {2, 0xCA, 0, PM_APPS_HLOS_OWNER,  SPMI_OPEN_OWNER    }, /* GPIO11 */
  {2, 0xCB, 0, PM_APPS_HLOS_OWNER, SPMI_OPEN_OWNER    }, /* GPIO12 */

  
  
  {3, 0x14, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* S1_CTRL */
  {3, 0x15, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* S1_PS */
  {3, 0x16, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* S1_FREQ */
  {3, 0x17, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* S2_CTRL */
  {3, 0x18, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* S2_PS */
  {3, 0x19, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* S2_FREQ */
  {3, 0x1A, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* S3_CTRL */
  {3, 0x1B, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* S3_PS */
  {3, 0x1C, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* S3_FREQ */
  {3, 0x1D, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* S4_CTRL */
  {3, 0x1E, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* S4_PS */
  {3, 0x1F, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* S4_FREQ */
  {3, 0x20, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* S5_CTRL */
  {3, 0x21, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* S5_PS */
  {3, 0x22, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* S5_FREQ */

  {3, 0x23, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER    }, /* CODEC_BOOST_FREQ */
  {3, 0x24, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER    }, /* CODEC_NCP_FREQ */

  {3, 0x40, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* LDO01 */
  {3, 0x41, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* LDO02 */
  {3, 0x42, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* LDO03 */
  {3, 0x43, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* LDO04 */
  {3, 0x44, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* LDO05 */
  {3, 0x45, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* LDO06 */
  {3, 0x46, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* LDO07 */
  {3, 0x47, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* LDO08 */
  {3, 0x48, 0, PM_MSS_OWNER, PM_MSS_OWNER    }, /* LDO09 */
  {3, 0x49, 0, PM_MSS_OWNER, PM_MSS_OWNER    }, /* LDO10 */

  
  {3, 0xA0, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* BOB_CONFIG */
  {3, 0xA1, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER    }, /* BOB_MONITORING */
  {3, 0xB0, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER    }, /* LPG_LUT */
  {3, 0xB1, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER    }, /* LPG_CHAN1 */
  {3, 0xB2, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER    }, /* LPG_CHAN2 */
  {3, 0xB3, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER    }, /* LPG_CHAN3 */
  {3, 0xB4, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER    }, /* LPG_CHAN4 */
  {3, 0xD0, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER    }, /* TRI_LED */
  {3, 0xD3, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER    }, /* FLASH1 */
  {3, 0xD8, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER    }, /* WLED1_CTRL */
  {3, 0xD9, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER    }, /* WLED1_SINK */
  {3, 0xDC, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER    }, /* IBB */
  {3, 0xDE, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER    }, /* LAB */
  
  {3, 0xE0, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER    }, /* OLEDB */
  {3, 0xEC, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER    }, /* LCDB_G1 */ 
  {3, 0xF0, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER    }, /* CODEC DIG */
  {3, 0xF1, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER    }, /* CODEC ANA */

  {3, 0x06, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* SPMI_OPTIONS */
  {3, 0x08, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER    }, /* PON_OPTIONS */

  
  /* Peripheral with slave ID for broadcast write access.*/
  {14, 0x05, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* INT */
  {14, 0x06, 0, PM_RPM_OWNER, PM_RPM_OWNER    }, /* SPMI */
  {14, 0x08, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER    }, /* PON */

};

/* Number of spmi channels config entries. . */
uint32 pm_spmi_pheriph_cfg_sz = sizeof(pm_spmi_pheriph_cfg) / sizeof(SpmiCfg_ChannelCfg);

