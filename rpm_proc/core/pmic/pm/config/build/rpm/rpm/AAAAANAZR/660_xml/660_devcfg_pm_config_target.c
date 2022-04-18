#include "devcfg_pm_config_common.h"
#include "devcfg_pm_config_target.h"
/*! \file pm_config_target.c
 *
 *  \brief This file contains customizable target specific driver settings & PMIC registers.
 *         This file info is taken from Target Component Resource Specific Settings from PDM
 *         that is maintained for each of the targets separately.
 *
 *  &copy; Copyright 2013 - 2016 QUALCOMM Technologies Incorporated, All Rights Reserved
 */

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

$Header: //components/rel/rpm.bf/1.8/core/pmic/pm/config/sdm660/pm_config_target.c#17 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
06/20/17   as      Disabling settling error check on EMMC rail (LDO5B) (CR#2054999)
04/06/17   as      LDO7B RBSC Off , Mode changed of LDO5A , LDO9B and LDO10B (CR#2017096) 
03/15/17   as      Min/Max freq updated of S1B buck (CR#2013798)
03/09/17   as      LDO13A to NPM from LPM (CR2017061)
03/02/17   as      update min voltage S5A buck / S2B to auto mode / LDO8A and LDO13A to LPM mode (CR#2001566)
02/18/17   as      update min voltage of LDO8B(CR#2008782)
02/09/17   akt     Update DDR specific clients (CR-2004483)
01/24/17   as      LDO8A NPM mode (CR#1114608))
01/16/17   as      max/min voltage changed nearest 8mV and LDO1A and LDO2b always on (CR1111900)
01/10/17   as      CX/MX max voltage set to 0.988V (CR1109587)
01/17/14   kt      Created.
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES

===========================================================================*/
#include "pmapp_npa.h"
#include "pm_npa.h"
#include "pm_target_information.h"
#include "pm_rpm_ldo_trans_apply.h"
#include "pm_rpm_smps_trans_apply.h"
#include "pm_rpm_vs_trans_apply.h"
#include "pm_rpm_clk_buffer_trans_apply.h"
#include "pm_rpm_bob_trans_apply.h"
#include "pm_config.h"
#include "pm_sleep_config.h"

uint32   num_of_ldo[]        = {19, 10, 0} ;
uint32   num_of_smps[]       = {6, 5, 0};
uint32   num_of_bob[]        = { 0, 1, 0};
uint32   num_of_vs[]         = { 0, 0, 0} ;

/* LpHpCurrentThreshold, SafetyHeadRoom, IsSawControlled, AccessAllowed, AlwaysOn, MinPwrMode, BypassDisallowed, DroopDetect, MinVoltage, MaxVoltage, MinSettlingTime, SettlingErrorEnabled, SettlingEnabled,  Reserved */
pm_rpm_ldo_rail_info_type ldo_rail_a[] = 
{
    {30,  40, 0, PM_ACCESS_ALLOWED,   PM_NONE,      PM_NPA_SW_MODE_LDO__IPEAK, PM_NPA_BYPASS_DISALLOWED, PM_DROOP_DETECT_DIS, 1256, 1256, 0, PM_SETTLING_ERR_EN, PM_SETTLING_EN, 0}, // LDO1 LDO440_N600_STEPPER
    {30,  24, 0, PM_ACCESS_ALLOWED,   PM_NONE,      PM_NPA_SW_MODE_LDO__IPEAK, PM_NPA_BYPASS_DISALLOWED, PM_DROOP_DETECT_DIS, 952, 1016,  0, PM_SETTLING_ERR_EN, PM_SETTLING_EN, 0}, // LDO2 HT_N1200_STEPPER
    {30,  40, 0, PM_ACCESS_ALLOWED,   PM_NONE,      PM_NPA_SW_MODE_LDO__IPEAK, PM_NPA_BYPASS_DISALLOWED, PM_DROOP_DETECT_DIS, 952, 1048,  0, PM_SETTLING_ERR_EN, PM_SETTLING_EN, 0}, // LDO3 LDO440_N600_STEPPER
    {10,  24, 0, PM_ACCESS_DISALLOWED,PM_NONE,      PM_NPA_SW_MODE_LDO__IPEAK, PM_NPA_BYPASS_DISALLOWED, PM_DROOP_DETECT_DIS, 525,  950,  0, PM_SETTLING_ERR_EN, PM_SETTLING_EN, 0}, // LDO4 NOT DEFINED
    {30,  24, 0, PM_ACCESS_ALLOWED,   PM_NONE,      PM_NPA_SW_MODE_LDO__NPM  , PM_NPA_BYPASS_DISALLOWED, PM_DROOP_DETECT_DIS, 528,  952,  0, PM_SETTLING_ERR_EN, PM_SETTLING_EN, 0}, // LDO5 HT_N600_STEPPER
    {30,  24, 0, PM_ACCESS_ALLOWED,   PM_NONE,      PM_NPA_SW_MODE_LDO__IPEAK, PM_NPA_BYPASS_DISALLOWED, PM_DROOP_DETECT_DIS, 1200, 1376, 0, PM_SETTLING_ERR_EN, PM_SETTLING_EN, 0}, // LDO6 HT_N600_STEPPER
    {30,  24, 0, PM_ACCESS_ALLOWED,   PM_NONE,      PM_NPA_SW_MODE_LDO__IPEAK, PM_NPA_BYPASS_DISALLOWED, PM_DROOP_DETECT_DIS, 1200, 1200, 0, PM_SETTLING_ERR_EN, PM_SETTLING_EN, 0}, // LDO7 HT_N1200_STEPPER
    {10,  40, 0, PM_ACCESS_ALLOWED,   PM_NONE,      PM_NPA_SW_MODE_LDO__IPEAK, PM_NPA_BYPASS_DISALLOWED, PM_DROOP_DETECT_DIS, 1752, 1904, 0, PM_SETTLING_ERR_EN, PM_SETTLING_EN, 0}, // LDO8 LDO440_LV_P600 
    {10,  24, 0, PM_ACCESS_ALLOWED,   PM_NONE,      PM_NPA_SW_MODE_LDO__IPEAK, PM_NPA_BYPASS_DISALLOWED, PM_DROOP_DETECT_DIS, 1752, 1904, 0, PM_SETTLING_ERR_EN, PM_SETTLING_EN,  0}, // LDO9 HT_LV_P150
    {10,  24, 0, PM_ACCESS_ALLOWED,   PM_NONE,      PM_NPA_SW_MODE_LDO__IPEAK, PM_NPA_BYPASS_DISALLOWED, PM_DROOP_DETECT_DIS, 1784, 1952, 0, PM_SETTLING_ERR_EN, PM_SETTLING_EN,  0}, // LDO10 HT_LV_P300
    {10,  40, 0, PM_ACCESS_ALLOWED,   PM_NONE,      PM_NPA_SW_MODE_LDO__IPEAK, PM_NPA_BYPASS_DISALLOWED, PM_DROOP_DETECT_DIS, 1784, 1952, 0, PM_SETTLING_ERR_EN, PM_SETTLING_EN, 0}, // LDO11 LDO440_LV_P150
    {10,  24, 0, PM_ACCESS_ALLOWED,   PM_NONE,      PM_NPA_SW_MODE_LDO__IPEAK, PM_NPA_BYPASS_DISALLOWED, PM_DROOP_DETECT_DIS, 1784, 1952, 0, PM_SETTLING_ERR_EN, PM_SETTLING_EN, 0}, // LDO12 HT_LV_P300
    {10,  40, 0, PM_ACCESS_ALLOWED,   PM_ALWAYS_ON, PM_NPA_SW_MODE_LDO__NPM, PM_NPA_BYPASS_DISALLOWED, PM_DROOP_DETECT_DIS, 1752, 1952, 0, PM_SETTLING_ERR_EN, PM_SETTLING_EN,  0}, // LDO13 LDO440_LV_P600
    {10,  40, 0, PM_ACCESS_ALLOWED,   PM_NONE,      PM_NPA_SW_MODE_LDO__IPEAK, PM_NPA_BYPASS_DISALLOWED, PM_DROOP_DETECT_DIS, 1712, 1904, 0, PM_SETTLING_ERR_EN, PM_SETTLING_EN, 0}, // LDO14 LDO440_LV_P150
    {10, 128, 0, PM_ACCESS_ALLOWED,   PM_NONE,      PM_NPA_SW_MODE_LDO__IPEAK, PM_NPA_BYPASS_DISALLOWED, PM_DROOP_DETECT_DIS, 1664, 2960, 0, PM_SETTLING_ERR_DIS, PM_SETTLING_EN, 0}, // LDO15 LDO440_P150
    {10, 128, 0, PM_ACCESS_ALLOWED,   PM_NONE,      PM_NPA_SW_MODE_LDO__IPEAK, PM_NPA_BYPASS_DISALLOWED, PM_DROOP_DETECT_DIS, 2560, 2848, 0, PM_SETTLING_ERR_EN,  PM_SETTLING_EN,  0}, // LDO16 LDO440_P150 
    {10, 128, 0, PM_ACCESS_ALLOWED,   PM_NONE,      PM_NPA_SW_MODE_LDO__IPEAK, PM_NPA_BYPASS_DISALLOWED, PM_DROOP_DETECT_DIS, 1664, 2960, 0, PM_SETTLING_ERR_DIS, PM_SETTLING_EN, 0}, // LDO17 LDO440_P150
    {10, 128, 0, PM_ACCESS_ALLOWED,   PM_NONE,      PM_NPA_SW_MODE_LDO__IPEAK, PM_NPA_BYPASS_DISALLOWED, PM_DROOP_DETECT_DIS, 2560, 2864, 0, PM_SETTLING_ERR_EN,  PM_SETTLING_EN,  0}, // LDO18 LDO440_P50
    {10, 128, 0, PM_ACCESS_ALLOWED,   PM_NONE,      PM_NPA_SW_MODE_LDO__IPEAK, PM_NPA_BYPASS_DISALLOWED, PM_DROOP_DETECT_DIS, 3200, 3408, 0, PM_SETTLING_ERR_EN,  PM_SETTLING_EN,  0}, // LDO19 LDO440_P600 

   
};

/* LpHpCurrentThreshold, SafetyHeadRoom, IsSawControlled, AccessAllowed, AlwaysOn, MinPwrMode, BypassDisallowed, DroopDetect, MinVoltage, MaxVoltage, MinSettlingTime, SettlingErrorEnabled, SettlingEnabled,  Reserved */
pm_rpm_ldo_rail_info_type ldo_rail_b[] = 
{
    {30,   40, 0, PM_ACCESS_ALLOWED,   PM_NONE,      PM_NPA_SW_MODE_LDO__IPEAK, PM_NPA_BYPASS_DISALLOWED, PM_DROOP_DETECT_DIS,  920,  920, 0, PM_SETTLING_ERR_EN, PM_SETTLING_EN, 0}, // LDO1 LDO440_N300_STEPPER
    {10,  128, 0, PM_ACCESS_ALLOWED,   PM_NONE,      PM_NPA_SW_MODE_LDO__IPEAK, PM_NPA_BYPASS_DISALLOWED, PM_DROOP_DETECT_DIS, 1664, 3104, 0, PM_SETTLING_ERR_EN, PM_SETTLING_EN, 0}, // LDO2 LDO440_P50
    {10,  128, 0, PM_ACCESS_ALLOWED,   PM_NONE,      PM_NPA_SW_MODE_LDO__IPEAK, PM_NPA_BYPASS_DISALLOWED, PM_DROOP_DETECT_DIS, 2704, 3544, 0, PM_SETTLING_ERR_EN, PM_SETTLING_EN, 0}, // LDO3 LDO440_P600
    {10,  128, 0, PM_ACCESS_ALLOWED,   PM_NONE,      PM_NPA_SW_MODE_LDO__IPEAK, PM_NPA_BYPASS_DISALLOWED, PM_DROOP_DETECT_DIS, 2704, 2950, 0, PM_SETTLING_ERR_EN, PM_SETTLING_EN, 0}, // LDO4 LDO440_P600
    {10,  128, 0, PM_ACCESS_ALLOWED,   PM_NONE,      PM_NPA_SW_MODE_LDO__IPEAK, PM_NPA_BYPASS_DISALLOWED, PM_DROOP_DETECT_DIS, 2704, 3544, 0, PM_SETTLING_ERR_DIS,PM_SETTLING_EN, 0}, // LDO5 LDO440_P600
    {10,  128, 0, PM_ACCESS_ALLOWED,   PM_NONE,      PM_NPA_SW_MODE_LDO__IPEAK, PM_NPA_BYPASS_DISALLOWED, PM_DROOP_DETECT_DIS, 2704, 3312, 0, PM_SETTLING_ERR_EN, PM_SETTLING_EN, 0}, // LDO6 LDO440_P50
    {10,  128, 0, PM_ACCESS_ALLOWED,   PM_NONE,      PM_NPA_SW_MODE_LDO__IPEAK, PM_NPA_BYPASS_DISALLOWED, PM_DROOP_DETECT_DIS, 2928, 3136, 0, PM_SETTLING_ERR_EN, PM_SETTLING_EN, 0}, // LDO7 LDO440_P150
    {10,  128, 0, PM_ACCESS_ALLOWED,   PM_NONE,      PM_NPA_SW_MODE_LDO__IPEAK, PM_NPA_BYPASS_DISALLOWED, PM_DROOP_DETECT_DIS, 2800, 3408, 0, PM_SETTLING_ERR_EN, PM_SETTLING_EN, 0}, // LDO8 LDO440_P600 
    {30,   24, 0, PM_ACCESS_ALLOWED,   PM_ALWAYS_ON, PM_NPA_SW_MODE_LDO__NPM,   PM_NPA_BYPASS_DISALLOWED, PM_DROOP_DETECT_DIS,  352,  992, 0, PM_SETTLING_ERR_DIS,PM_SETTLING_EN, 0}, // LDO9 HT_N600_STEPPER
    {30,   24, 0, PM_ACCESS_ALLOWED,   PM_ALWAYS_ON, PM_NPA_SW_MODE_LDO__NPM,   PM_NPA_BYPASS_DISALLOWED, PM_DROOP_DETECT_DIS,  528,  992, 0, PM_SETTLING_ERR_DIS,PM_SETTLING_EN, 0}, // LDO10 HT_N300_STEPPER
   
};

/* LpHpCurrentThreshold, IsSawControlled, AccessAllowed, AlwaysOn, MinPwrMode, MinFreq, MaxFreq, MinVoltage, MaxVoltage, MinSettlingTime, SettlingErrorEnabled, SettlingEnabled, Reserved */
pm_rpm_smps_rail_info_type smps_rail_a[] = 
{
    {400, 0, PM_ACCESS_DISALLOWED,   PM_NONE,      PM_NPA_SW_MODE_SMPS__AUTO,   PM_CLK_3p2_MHz, PM_CLK_3p2_MHz, PM_DROOP_DETECT_DIS,  568, 1172, 0, PM_SETTLING_ERR_EN, PM_SETTLING_EN, 0}, //FTS1 - APC0
    {400, 0, PM_ACCESS_DISALLOWED,   PM_NONE,      PM_NPA_SW_MODE_SMPS__AUTO,   PM_CLK_3p2_MHz, PM_CLK_3p2_MHz, PM_DROOP_DETECT_DIS,  568, 1172, 0, PM_SETTLING_ERR_EN, PM_SETTLING_EN, 0}, //FTS2 - APC1
    {100, 0, PM_ACCESS_DISALLOWED,   PM_NONE,      PM_NPA_SW_MODE_SMPS__AUTO,   PM_CLK_2p13_MHz,PM_CLK_2p13_MHz,PM_DROOP_DETECT_DIS,  568, 1172, 0, PM_SETTLING_ERR_EN, PM_SETTLING_EN, 0}, //HFS3 - APC1
    {100, 0, PM_ACCESS_ALLOWED,      PM_ALWAYS_ON, PM_NPA_SW_MODE_SMPS__AUTO,   PM_CLK_3p2_MHz, PM_CLK_3p2_MHz, PM_DROOP_DETECT_DIS, 1808, 2040, 0, PM_SETTLING_ERR_EN, PM_SETTLING_EN, 0}, //HFS4 - SubReg-1.8VL
    {100, 0, PM_ACCESS_ALLOWED,      PM_NONE,      PM_NPA_SW_MODE_SMPS__AUTO,   PM_CLK_1p6_MHz, PM_CLK_1p6_MHz, PM_DROOP_DETECT_DIS, 1224, 1352, 0, PM_SETTLING_ERR_EN, PM_SETTLING_EN, 0}, //HFS5 - SubREg-1.35VL
    {400, 0, PM_ACCESS_DISALLOWED,   PM_NONE,      PM_NPA_SW_MODE_SMPS__INVALID,PM_SWITCHING_FREQ_FREQ_NONE, PM_SWITCHING_FREQ_FREQ_NONE, PM_DROOP_DETECT_DIS, 504, 992, 0, PM_SETTLING_ERR_EN, PM_SETTLING_EN, 0}, //FTS6 - MSS
    
};

/* LpHpCurrentThreshold, IsSawControlled, AccessAllowed, AlwaysOn, MinPwrMode, MinFreq, MaxFreq, MinVoltage, MaxVoltage, MinSettlingTime, SettlingErrorEnabled, SettlingEnabled, Reserved */
pm_rpm_smps_rail_info_type smps_rail_b[] = 
{
    {400, 0, PM_ACCESS_ALLOWED,    PM_ALWAYS_ON, PM_NPA_SW_MODE_SMPS__AUTO,    PM_CLK_3p2_MHz,              PM_CLK_3p2_MHz,              PM_DROOP_DETECT_DIS,   1128,    1128, 0, PM_SETTLING_ERR_EN, PM_SETTLING_EN, 0}, //FTS1 - LPDDR4x
    {400, 0, PM_ACCESS_ALLOWED,    PM_ALWAYS_ON, PM_NPA_SW_MODE_SMPS__AUTO,    PM_CLK_3p2_MHz,              PM_CLK_3p2_MHz,              PM_DROOP_DETECT_DIS, 1016, 1088, 0, PM_SETTLING_ERR_DIS,PM_SETTLING_DIS,0}, //FTS2 - SUB REG FTS
    {400, 0, PM_ACCESS_ALLOWED,    PM_ALWAYS_ON, PM_NPA_SW_MODE_SMPS__AUTO,    PM_CLK_3p2_MHz,              PM_CLK_3p2_MHz,              PM_DROOP_DETECT_DIS, 352 ,  988, 0, PM_SETTLING_ERR_EN, PM_SETTLING_EN, 0}, //FTS3 - CX/GPU
    {400, 0, PM_ACCESS_DISALLOWED, PM_ALWAYS_ON, PM_NPA_SW_MODE_SMPS__INVALID, PM_SWITCHING_FREQ_FREQ_NONE, PM_SWITCHING_FREQ_FREQ_NONE, PM_DROOP_DETECT_DIS,    0,   0, 0, PM_SETTLING_ERR_EN, PM_SETTLING_EN, 0}, //FTS4- CX/GPU
    {400, 0, PM_ACCESS_ALLOWED,    PM_ALWAYS_ON, PM_NPA_SW_MODE_SMPS__AUTO,    PM_CLK_3p2_MHz,              PM_CLK_3p2_MHz,              PM_DROOP_DETECT_DIS, 488,  988, 0, PM_SETTLING_ERR_EN, PM_SETTLING_EN, 0}, //FTS5 - MX
};


/* AccessAllowed, AlwaysOn, SettlingErrorEnabled, SettlingEnabled, MinTimeGapOffOn (in us) */
pm_rpm_clk_info_type clk_info_a[]=
{
    //{PM_ACCESS_DISALLOWED, PM_NONE, PM_SETTLING_ERR_EN, PM_SETTLING_EN, 0},  //XO *managed by SBL settings
    {PM_ACCESS_DISALLOWED,PM_ALWAYS_ON, PM_SETTLING_ERR_EN, PM_SETTLING_EN, 0},//BB_CLK1 *PBS puts in PIN control
    {PM_ACCESS_ALLOWED,   PM_NONE, PM_SETTLING_ERR_EN, PM_SETTLING_EN, 0},     //BB_CLK2
    {PM_ACCESS_ALLOWED,   PM_NONE, PM_SETTLING_ERR_EN, PM_SETTLING_EN, 0},     //BB_CLK3
    {PM_ACCESS_ALLOWED,   PM_NONE, PM_SETTLING_ERR_EN, PM_SETTLING_EN, 0},     //RF_CLK1
    {PM_ACCESS_ALLOWED,   PM_NONE, PM_SETTLING_ERR_EN, PM_SETTLING_EN, 0},     //RF_CLK2
    {PM_ACCESS_DISALLOWED,   PM_NONE, PM_SETTLING_ERR_EN, PM_SETTLING_EN, 0},     //RF_CLK3
    {PM_ACCESS_DISALLOWED,PM_NONE, PM_SETTLING_ERR_EN, PM_SETTLING_EN, 0},     //EMPTY
    {PM_ACCESS_DISALLOWED,PM_NONE, PM_SETTLING_ERR_EN, PM_SETTLING_EN, 0},     //EMPTY
    {PM_ACCESS_DISALLOWED,PM_NONE, PM_SETTLING_ERR_EN, PM_SETTLING_EN, 0},     //CLK_DIST *not supported
    {PM_ACCESS_DISALLOWED,PM_ALWAYS_ON, PM_SETTLING_ERR_EN, PM_SETTLING_EN, 0},//SLEEP_CLK
    {PM_ACCESS_ALLOWED,   PM_NONE, PM_SETTLING_ERR_EN, PM_SETTLING_EN, 0},     //DIV_CLK1
    {PM_ACCESS_DISALLOWED,   PM_NONE, PM_SETTLING_ERR_EN, PM_SETTLING_EN, 0},     //DIV_CLK2
    {PM_ACCESS_DISALLOWED,   PM_NONE, PM_SETTLING_ERR_EN, PM_SETTLING_EN, 0}      //DIV_CLK3
};


/* AccessAllowed, AlwaysOn, MinPwrMode, Settling failure, Settling, Reserved, MinVoltage, MaxVoltage, MinPinVoltage, MaxPinVoltage */
pm_rpm_bob_rail_info_type bob_rail_b[] = 
{
    {PM_ACCESS_ALLOWED, PM_ALWAYS_ON, PM_BOB_MODE_AUTO, PM_SETTLING_ERR_DIS, PM_SETTLING_EN, 0, 3008, 4000, 3008, 4000},
};

/*LDO ping mapping with BOB. Position of LDO HW Pin in below array represents BOB pin number */
pm_npa_pin_control_enable_type  bob_pin_mapping[PM_BOB_EXT_PIN_MAX] = 
{
  PM_NPA_PIN_CONTROL_ENABLE__NONE, PM_NPA_PIN_CONTROL_ENABLE__EN3, PM_NPA_PIN_CONTROL_ENABLE__NONE, PM_NPA_PIN_CONTROL_ENABLE__NONE
};

pm_rpm_ldo_rail_info_type* ldo_rail[]=
{
    ldo_rail_a, ldo_rail_b, NULL
};

pm_rpm_smps_rail_info_type* smps_rail[]=
{
    smps_rail_a, smps_rail_b, NULL
};

pm_rpm_vs_rail_info_type* vs_rail[]=
{
    NULL, NULL, NULL
};

pm_rpm_clk_info_type* clk_info[]=
{
    clk_info_a, NULL, NULL
};

pm_rpm_bob_rail_info_type* bob_rail[]=
{
    NULL, bob_rail_b, NULL
};

/* Sleep configuration for enter XO_SHUTDOWN or VDD_MIN. */
static const pm_sleep_reg_type enter_xo_shutdown[] =
{
    {0, 0x5146, 0x01}, // BB_CLK1_EN_CTL: Set BBCLK_NOT_FORCE, and follow Pin
    {0, 0xFFFF, 0x00}, // invalid setting, used to check the end of the array.
};

static const pm_sleep_reg_type enter_vdd_min[] =
{
    {0, 0x5146, 0x01}, // BB_CLK1_EN_CTL: Set BBCLK_NOT_FORCE, and follow Pin
    //LDO 1A 1B turn off
    //{1, 0x4046, 0x00}, //Turn OFF LDO1A - meant to be always ON for DDR but sleep OFF
    //{3, 0x4046, 0x00}, //Turn OFF LDO1B - meant to be always ON for DDR but sleep OFF
    {0, 0xFFFF, 0x00}, // invalid setting, used to check the end of the array.
};

const pm_sleep_cfg_type sleep_enter_info[] = {
    {enter_xo_shutdown},
    {enter_vdd_min}
};

static const pm_sleep_reg_type exit_xo_shutdown[] =
{
    {0, 0x5146, 0x81}, // BB_CLK1_EN_CTL: Force BBCLK enable and follow Pin
    {0, 0xFFFF, 0x00}, // invalid setting, used to check the end of the array.
};

static const pm_sleep_reg_type exit_vdd_min[] =
{
    {0x0, 0x5146, 0x81},    // BB_CLK1_EN_CTL: Force BBCLK enable and follow Pin
    {0xE, 0x540,  0x01},    // Sending resend all command.
    {0xE, 0x614,  0x01},    // HW bug fix, clear SPMI INT LATCHED bit.
    // turn on while exit
    //{1, 0x4046, 0x80}, //Turn ON LDO1A - meant to be always ON for DDR but sleep OFF
    //{3, 0x4046, 0x80}, //Turn ON LDO1B - meant to be always ON for DDR but sleep OFF

    {0x0, 0xFFFF, 0x00},    // check the end of the array.
};

const pm_sleep_cfg_type sleep_exit_info[] = {
    {exit_xo_shutdown},
    {exit_vdd_min}
};
