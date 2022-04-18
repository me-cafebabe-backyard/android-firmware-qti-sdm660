/*! \file
*  \n
*  \brief  pm_spmi_config.c
*  \n
*  \n This file contains pmic configuration data specific for SPMI Controller's
      Peripheral for MSM8998 device..
*  \n
*  \n &copy; Copyright 2015 Qualcomm Technologies Incorporated, All Rights Reserved
*/
/* =======================================================================
Edit History
This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/core.tz/1.0.7.1/systemdrivers/pmic/config/sdm660_pm660/src/pm_tz_config.c#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
02/16/17   as     changes in PVC port modem core rail (CR#2007718)
12/27/16   as     gang leader of APPS1 updated to S3A ( CR 1105270 )
08/25/15   vtw    Created.
========================================================================== */

/*-------------------------------------------------------------------------
* Include Files
* ----------------------------------------------------------------------*/

#include "SpmiCfg.h"

/*-------------------------------------------------------------------------
* Preprocessor Definitions and Constants
* ----------------------------------------------------------------------*/

/* Converts a PVC port index to an overall PMIC Arbiter port index */
#define PVC_PORT_TO_PMIC_ARB_PORT(p) (p+1)

/*   Port assignment in SDM660   */ //TODO - HPG is not yet updated To confirm if the same holds good
#define GFX_PORT        0   /* Graphics  */
#define APPS0_PORT      1   /* APPS Port 0  */
#define APPS1_PORT      2   /* APPS Port 1  */
#define MSS_MGPI_PORT   3   /* MGPI   */
#define MSS_MVC_PORT    4   /* Modem MVC   */
#define MSS_SAW_PORT    5   /* MSS SAW   */

/*-------------------------------------------------------------------------
* Static Variable Definitions
* ----------------------------------------------------------------------*/

/*
 * pm_pvc_apps0_addr
 *
 * PVC port addr for APPS0 Silver cluster block.
 */
static SpmiCfg_Ppid pm_pvc_apps0_addr[] =
{
  {0x1, 0x1440}, /* PM660, S1A_CTRL_VSET_LB */
  {0x1, 0x1441}, /* PM660, S1A_CTRL_VSET_UB */
  {0x1, 0x1445}, /* PM660, S1A_CTRL_MODE_CTL */
  {0x1, 0x1446}, /* PM660, S1A_CTRL_EN_CTL */
};

/*
 * pm_pvc_apps1_addr
 *
 * PVC port addr for APPS1 Gold cluster.
 */
static SpmiCfg_Ppid pm_pvc_apps1_addr[] =
{
  {0x1, 0x1A40}, /* PM660, S3A_CTRL_VSET_LB */
  {0x1, 0x1A41}, /* PM660, S3A_CTRL_VSET_UB */
  {0x1, 0x1A45}, /* PM660, S3A_CTRL_MODE_CTL */
  {0x1, 0x1A46}, /* PM660, S3A_CTRL_EN_CTL */
};

/*
 * pm_pvc_mss_addr
 *
 * PVC port addr for Modem core rail.
 */
static SpmiCfg_Ppid pm_pvc_mss_addr[] =
{
  {0x1, 0x2340}, /* PM660, S6A_CTRL_VSET_LB */
  {0x1, 0x2341}, /* PM660, S6A_CTRL_VSET_UB */
  {0x0, 0x7350}, /* PM660, PBS_CLIENT2_SCRATCH1  */
  {0x0, 0x7342}, /* PM660, PBS_CLIENT2_TRIG_CTL */
};

/*
 * pm_pvc_mgpi_addr
 *
 * PVC port addr for MGPI block.
 */
static SpmiCfg_Ppid pm_pvc_mgpi_addr[] =
{
  {0x2, 0x094A}, /* PM660L, MISC_TX_GTR_THRES_CTL */ //TODO MGPI is not supported - confirm
};


/*
 * pm_arb_pvc_cfg
 *
 * PMIC Arbiter PVC ports config.
 */
const SpmiCfg_PvcPortCfg pm_arb_pvc_cfg[] =
{
  {
    /* .pvcPortId = */  APPS0_PORT,
    /* .priority  = */ SPMI_ACCESS_PRIORITY_LOW,
    /* .ppids     = */ pm_pvc_apps0_addr,
    /* .numPpids  = */ sizeof(pm_pvc_apps0_addr)/sizeof(SpmiCfg_Ppid)
  },
  {
    /* .pvcPortId = */  APPS1_PORT,
    /* .priority  = */ SPMI_ACCESS_PRIORITY_LOW,
    /* .ppids     = */ pm_pvc_apps1_addr,
    /* .numPpids  = */ sizeof(pm_pvc_apps1_addr)/sizeof(SpmiCfg_Ppid)
  },
  {
    /* .pvcPortId = */  MSS_SAW_PORT,
    /* .priority  = */ SPMI_ACCESS_PRIORITY_LOW,
    /* .ppids     = */ pm_pvc_mss_addr,
    /* .numPpids  = */ sizeof(pm_pvc_mss_addr)/sizeof(SpmiCfg_Ppid)
  },
  #if 0
  {
    /* .pvcPortId = */  MSS_MGPI_PORT,
    /* .priority  = */ SPMI_ACCESS_PRIORITY_LOW,
    /* .ppids     = */ pm_pvc_mgpi_addr,
    /* .numPpids  = */ sizeof(pm_pvc_mgpi_addr)/sizeof(SpmiCfg_Ppid)
  }
  #endif
};

/* Number of pvc ports. */
const uint32 pm_num_pvc_port = sizeof(pm_arb_pvc_cfg) / sizeof(SpmiCfg_PvcPortCfg);

const uint8 pm_arb_priorities[] =
{
    0,                                         /* SW port -- highest priority */
    PVC_PORT_TO_PMIC_ARB_PORT(APPS0_PORT),
    PVC_PORT_TO_PMIC_ARB_PORT(APPS1_PORT),
    PVC_PORT_TO_PMIC_ARB_PORT(MSS_SAW_PORT),
  //   PVC_PORT_TO_PMIC_ARB_PORT(MSS_MGPI_PORT)

};

/* Number of port prioriries. */
const uint32 pm_num_prio = sizeof(pm_arb_priorities) / sizeof(uint8);
































































































































































