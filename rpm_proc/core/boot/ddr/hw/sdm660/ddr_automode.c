/**
 * @file ddr_automode.c
 * @brief
 * Target specific DDR drivers.
 */
/*==============================================================================
                                EDIT HISTORY

$Header: //components/rel/rpm.bf/1.8/core/boot/ddr/hw/sdm660/ddr_automode.c#4 $
$DateTime: 2017/03/11 00:40:01 $
$Author: pwbldsvc $
================================================================================
when       who     what, where, why
--------   ---     -------------------------------------------------------------
03/11/17   din     Changed threshold for PW mode for PM3003A to 768
03/03/17   mrr     Added ext buck detection
06/10/14   tw      Initial version.
================================================================================
                   Copyright 2014,2017 Qualcomm Technologies Incorporated
                              All Rights Reserved
                     Qualcomm Confidential and Proprietary
==============================================================================*/
/*==============================================================================
                                  INCLUDES
==============================================================================*/
#include "ddr_common.h"
#include "ddr_params.h"
#include "ddr_log.h"
#include "npa.h"
#include "railway.h"
#include "pm_rpm.h"
#include "ddr_automode.h"

/*==============================================================================
                                  MACROS
==============================================================================*/

/* -----------------------------------------------------------------------
**                           DATA
** ----------------------------------------------------------------------- */
/* global flag to turn on and off auto mode*/
boolean ddr_automode_en = TRUE;

/* structure to contain automode enums and thresholds */
#define DDR_AUTOMODE_MAX 0x7FFFFFFF
#define PM3003_ID 0xA8

ddr_automode ddr_automode_cfg[] =
{
  {000000,  PMIC_NPA_MODE_ID_DDR_CFG_0},
  {150000,  PMIC_NPA_MODE_ID_DDR_CFG_1},	
  {200000,  PMIC_NPA_MODE_ID_DDR_CFG_2},
  {300000,  PMIC_NPA_MODE_ID_DDR_CFG_3},
  {412800,  PMIC_NPA_MODE_ID_DDR_CFG_4},
  {547200,  PMIC_NPA_MODE_ID_DDR_CFG_5},
  {681600,  PMIC_NPA_MODE_ID_DDR_CFG_6},
  {768000,  PMIC_NPA_MODE_ID_DDR_CFG_7},
  {1017600, PMIC_NPA_MODE_ID_DDR_CFG_8},
  {1354000, PMIC_NPA_MODE_ID_DDR_CFG_9},
  {1555200, PMIC_NPA_MODE_ID_DDR_CFG_10},
  {1804800, PMIC_NPA_MODE_ID_DDR_CFG_11},
  {DDR_AUTOMODE_MAX, DDR_AUTOMODE_MAX},
};
/* -----------------------------------------------------------------------
**                           FUNCTIONS
** ----------------------------------------------------------------------- */

/* =============================================================================
**  Function : ddr_automode_init
** =============================================================================
*/
/**
*   @brief
*   Function called to initialize automode settings
*
*   @param[in]  None
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
void ddr_automode_init(void)
{
//  if(!ddr_automode_en)
//  {
    /* force pmic enum to max to ensure we don't operate in automode for
       high frequency cases when dynamic auto mode is disabled
    */
  if (ddrsns_share_data->misc.ext_buck_id == PM3003_ID)
  {
	  pm_npa_rpm_set_auto_mode_thr(PMIC_NPA_MODE_ID_DDR_CFG_7);
  }
	else
	{
	  pm_npa_rpm_set_auto_mode_thr(PMIC_NPA_MODE_ID_DDR_CFG_3);
	}
    /* Apply pmic automode setting */
    pm_npa_rpm_smps_auto_mode_config(PMIC_NPA_MODE_ID_DDR_CFG_8);

    /* perform sanity check to ensure pmic setting is what we expected */
    pm_npa_rpm_verify_smps_mode(PMIC_NPA_MODE_ID_DDR_CFG_8);    
//  }
}

/* =============================================================================
**  Function : ddr_automode_toggle
** =============================================================================
*/
/**
*   @brief
*   Function called to update automode settings
*
*   @param[in]  clk_speed_in_khz  Current clock speed (in KHz)
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
void ddr_automode_toggle(uint32 clk_speed_in_khz)
{
  uint8 i = 0;
  
  if(ddr_automode_en)
  {
    while(ddr_automode_cfg[i].freq != DDR_AUTOMODE_MAX)
    {
      if(clk_speed_in_khz <= ddr_automode_cfg[i].freq)
      {
        /* Apply pmic automode setting */
        pm_npa_rpm_smps_auto_mode_config(ddr_automode_cfg[i].pmic_enum);

        /* perform sanity check to ensure pmic setting is what we expected */
        pm_npa_rpm_verify_smps_mode(ddr_automode_cfg[i].pmic_enum);
        
        break;
      }
      i++;
    }  
  }
} /* ddr_automode_toggle */

