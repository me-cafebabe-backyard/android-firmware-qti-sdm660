/*! \file pm_mpm_volt_rail_cmd_cfg.c
*  \n
*  \brief This file contains pmic configuration data specific for mpm shutdown/wakeup voltage rail cmds.
*  \n
*  \n &copy; Copyright 2014-2016 Qualcomm Technologies Incorporated, All Rights Reserved
*/
/* =======================================================================
Edit History
This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/rpm.bf/1.8/core/pmic/pm/config/sdm660/pm_mpm_volt_rail_cmd_cfg.c#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
02/12/14   vtw     Updated with 8994 MPM sequence settings.
10/31/13   vtw     Created.
========================================================================== */

/*=========================================================================
      Include Files
==========================================================================*/

#include "pm_mpm.h"
#include "pm_mpm_internal.h"
#include "pm_mpm_target.h"


/**
  * MPM PMIC sleep register settings.
  */
pm_mpm_cfg_type
pm_mpm_sleep_cfg[] =
{
  [PM_MPM_SLEEP_CMD_CX_VSET_LB]      = {0x3, 0x01A40, 0x0, 0x0}, /* Set VDD_CX (S3B) retention. */
  [PM_MPM_SLEEP_CMD_CX_VSET_UB]      = {0x3, 0x01A41, 0x0, 0x0}, /* Set VDD_CX (S3B)retention. */
  //[PM_MPM_SLEEP_CMD_EBI_DIS]         = {0x1, 0x02946, 0x0, 0x0}, /* DDR PHY PC */
  [PM_MPM_SLEEP_CMD_MX_VSET_LB]      = {0x3, 0x02040, 0x0, 0x0}, /* Set VDD_MX (S5B) retention */
  [PM_MPM_SLEEP_CMD_MX_VSET_UB]      = {0x3, 0x02041, 0x0, 0x0}, /* Set VDD_MX (S5B)retention */
  [PM_MPM_SLEEP_CMD_PBS_TRIG_ARG]    = {0xE, 0x07250, 0x1, 0x0}, /* Set PBS sleep trigger argument */  ///Arun TODO findout the PBS trigger 
  [PM_MPM_SLEEP_CMD_PBS_TRIG]        = {0xE, 0x07242, 0x80, 0x6}, /* Program PBS SW trigger. */        ///Arun TODO findout the PBS trigger 
  [PM_MPM_SLEEP_CMD_END]             = {0x0, 0x0,     0x0, 0x0}, /* End of sleep sequence. */
};

/**
  * MPM PMIC active register settings.
  */
pm_mpm_cfg_type
pm_mpm_active_cfg[] =
{
  [PM_MPM_ACTIVE_CMD_PBS_TRIG_ARG]      = {0xE, 0x07250, 0x2, 0x0},  /* Set PBS wake trigger argument */ ///Arun TODO findout the PBS trigger 
  [PM_MPM_ACTIVE_CMD_PBS_TRIG]          = {0xE, 0x07242, 0x80, 0x6},  /* Program PBS SW trigger. */      ///Arun TODO findout the PBS trigger 
  [PM_MPM_ACTIVE_CMD_MX_MODE]           = {0x3, 0x02045, 0x0, 0x0},  /* Retore MX (S5B) to mode before sleep. */
  [PM_MPM_ACTIVE_CMD_CX_MODE]           = {0x3, 0x01A45, 0x0, 0x0},  /* Retore CX (S3B) to mode before sleep. */
  [PM_MPM_ACTIVE_CMD_MX_VSET_LB]        = {0x3, 0x02040, 0x0, 0x0},  /* Turn on MX (S5B) with active voltage.  */
  [PM_MPM_ACTIVE_CMD_MX_VSET_UB]        = {0x3, 0x02041, 0x0, 0x0},  /* Turn on MX (S5B) with active voltage.  */
  //[PM_MPM_ACTIVE_CMD_EBI_EN]            = {0x1, 0x02946, 0x80, 0x0}, /* DDR PHY Restore */
  [PM_MPM_ACTIVE_CMD_CX_VSET_LB]        = {0x3, 0x01A40, 0x0, 0x0},  /* Turn on CX (S3B) with active voltage.  */
  [PM_MPM_ACTIVE_CMD_CX_VSET_UB]        = {0x3, 0x01A41, 0x0, 0x0},  /* Turn on CX (S3B) with active voltage.  */
  [PM_MPM_ACTIVE_CMD_END]               = {0x0, 0x0,     0x0, 0x0},  /* End active sequence. */  
};

/**
  * MPM cmd index buffer.
  */
const pm_mpm_cmd_index_type pm_mpm_cmd_index[] =
{
                             /* rail retention index, rail active index, rail sw mode before sleep */
  [PM_MPM_CX_INDEX]        = {PM_MPM_SLEEP_CMD_CX_VSET_LB, PM_MPM_ACTIVE_CMD_CX_VSET_LB, PM_MPM_ACTIVE_CMD_CX_MODE},
  [PM_MPM_MX_INDEX]        = {PM_MPM_SLEEP_CMD_MX_VSET_LB, PM_MPM_ACTIVE_CMD_MX_VSET_LB, PM_MPM_ACTIVE_CMD_MX_MODE},
};

/**
  * MPM rails info.
  */
pm_mpm_rails_info_type pm_mpm_rails_info[] =
{
                             /* resource_type, resource_index, sleep_headroom_uv */
  [PM_MPM_CX_INDEX]        = {RPM_SMPS_B_REQ, 3, 0}, // CX is S3B
  [PM_MPM_MX_INDEX]        = {RPM_SMPS_B_REQ, 5, 0}, // MX is S5B
};
