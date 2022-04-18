#ifndef _SPM_HAL_BSP_H_
#define _SPM_HAL_BSP_H_
/*==============================================================================
  FILE:         spm_hal_bsp.h

  OVERVIEW:     This file provides typedefs for the target specific data. Usually
                these types emulate underlying SPM HW block.

  DEPENDENCIES: None
                
                Copyright (c) 2015 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/spm/src/hal/v3/inc/spm_hal_bsp.h#1 $
$DateTime: 2020/02/10 01:57:30 $
================================================================================*/
#ifdef __cplusplus
extern "C" {
#endif

#include "comdef.h"

/*========================================================================
 *                                 TYPES
 *=======================================================================*/

/**
 * @brief Enumeration to indicate size of PMIC data.
 */
typedef enum
{
  SPM_HAL_BSP_PMIC_DATA_SIZE_0,   /* HW treats data size to be 1 byte */
  SPM_HAL_BSP_PMIC_DATA_SIZE_1    /* HW treats data size to be 2 bytes */
}spm_hal_bsp_pmic_data_size_t;

/**
 * @brief SPM wakeup configuration type.
 */
typedef enum
{
  SPM_HAL_BSP_WAKEUP_CONFIG_0,    /* sys_spm_wakeup */
  SPM_HAL_BSP_WAKEUP_CONFIG_1,    /* sys_spm_wakeup OR !cpu_spm_wait_req */
  SPM_HAL_BSP_WAKEUP_CONFIG_2,    /* sys_spm_wakeup OR rising edge of
                                   * sys_spm_dbg_nopwrdwn */
  SPM_HAL_BSP_WAKEUP_CONFIG_3     /* sys_spm_wakeup OR !cpu_spm_wait_req OR
                                   * rising edge of sys_saw_dbg_nopwrdwn */
}spm_hal_bsp_wakeup_cfg_t;

/**
 * @brief PMIC operation mode for the commands that are being sent to PMIC.
 */
typedef enum
{
  SPM_HAL_BSP_PMIC_MODE_NOMINAL,
  SPM_HAL_BSP_PMIC_MODE_VDD_MIN,
  SPM_HAL_BSP_PMIC_MODE_PC,
  SPM_HAL_BSP_PMIC_MODE_MAX = 6  /* Max no of modes supported on SAW3 */
}spm_hal_bsp_pmic_mode_t;

/**
 * @brief Structure containing configuration of common SPM and AVS controls.
 */
typedef struct spm_hal_bsp_clk_cfg_s
{
  uint8 frc_ref_clk_on;
  uint8 clk_div;
}spm_hal_bsp_clk_cfg_t;

/**
 * @brief Contains some of the SPM control parameters.
 */
typedef struct spm_hal_bsp_ctl_cfg_s
{
  spm_hal_bsp_wakeup_cfg_t wakeup;     /* SPM wakeup configuration */
}spm_hal_bsp_ctl_cfg_t;

/**
 * @brief Type to provide delays between various SPM commands.
 */
typedef struct spm_hal_bsp_delay_cfg_s
{
  uint16 delay1;
  uint16 delay2;
  uint16 delay3;
}spm_hal_bsp_delay_cfg_t;

/**
 * @brief Type to provide PMIC control data.
 */
typedef struct spm_hal_bsp_pmic_cfg_s
{
  spm_hal_bsp_pmic_mode_t       mode;   /* PMIC mode of operation */
  uint8                         data;   /* Data sent to PMIC arbiter */
  uint8                         delay;  /* PMIC delay - time between pmic 
                                         * command and next command in sequnce */
  spm_hal_bsp_pmic_data_size_t  size;   /* Data size per PMIC request */
  uint8                         index;  /* PMIC arbiter address index */
}spm_hal_bsp_pmic_cfg_t;

/**
 * @brief Structure containing initial SPM configuration.
 */
typedef struct spm_hal_bsp_cfg_s
{
  spm_hal_bsp_clk_cfg_t   clk_cfg;
  spm_hal_bsp_ctl_cfg_t   ctl_cfg;
  spm_hal_bsp_delay_cfg_t delay_cfg;
  spm_hal_bsp_pmic_cfg_t  *pmic_cfg;
  uint8                   pmic_cfg_count; /* Number of elements above */
}spm_hal_bsp_cfg_t;

/**
 * @brief Type to specify an SPM command sequence for a low power mode.
 */
typedef struct spm_hal_bsp_mode_s
{
  spm_sequence_data_t sequence;
  uint16              mode_id;    /* Mode id - unique identifier for this mode */

  /* Internal data */
  uint32              ctl_vals;   /* Optional values for SPM_CTL register */
  uint16              start_addr; /* Sequence's start address in SPM - filled 
                                   * during initialization. */
}spm_hal_bsp_mode_t;

#ifdef __cplusplus
}
#endif

#endif

