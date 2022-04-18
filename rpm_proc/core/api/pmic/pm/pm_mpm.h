#ifndef __PM_MPM_H__
#define __PM_MPM_H__

/**
 * @file pm_mpm.h
 *
 * Header file for PMIC MPM VDD command driver.
 */
/*
  ====================================================================

  Copyright (c) 2013-2016 Qualcomm Technologies, Inc.  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ====================================================================

  $Header: //components/rel/rpm.bf/1.8/core/api/pmic/pm/pm_mpm.h#1 $
  $DateTime: 2016/11/03 00:13:13 $
  $Author: pwbldsvc $

  ====================================================================
*/

/*----------------------------------------------------------------------------
 *  Include Files
 * -------------------------------------------------------------------------*/

#include "com_dtypes.h"
#include "pm_err_flags.h"

/*----------------------------------------------------------------------------
 * Type Definitions
 * -------------------------------------------------------------------------*/

/**
 * MPM command configuration.
 */
typedef struct
{
  uint32 slave_id;    /* Slave ID */
  uint32 slave_addr;  /* SPMI address  */
  uint32 data;        /* Data */
  uint32 delay;       /* Delay */
} pm_mpm_cfg_type;

/**
 * PMIC config data for the MPM wake/sleep sequence.
 */
typedef struct
{
  pm_mpm_cfg_type* active_cfg_ptr; /* [OUT] - pointer to SPMI command buffer for MPM wake */
  pm_mpm_cfg_type* sleep_cfg_ptr;  /* [OUT] - pointer to SPMI command buffer for MPM sleep */
  uint32 mx_sleep_microvolts;      /* [IN] - MX sleep voltage */
  uint32 cx_sleep_microvolts;      /* [IN] - CX sleep voltage */
  uint32 mx_active_microvolts;     /* [IN] - MX active voltage */
  uint32 cx_active_microvolts;     /* [IN] - CX active voltage */
} pm_mpm_cmd_cfg_type;

/*----------------------------------------------------------------------------
 * Function : pm_mpm_cmd_config
 * -------------------------------------------------------------------------*/
/*!
    Description: Return a pointer to a config data buffer for MPM voltage rail
                 command.
    @param
      mpm_cfg_ptr: pointer to the data structure that pointer to
                   the buffer which contains config data
                   for retention and active voltage.
    @return
    PM_ERR_FLAG__SUCCESS success otherwise PMIC error.

    @dependencies None

    @sa None
*/
pm_err_flag_type pm_mpm_cmd_config
(
  pm_mpm_cmd_cfg_type * mpm_cmd_ptr
);

#endif /* __PM_MPM_H__ */

