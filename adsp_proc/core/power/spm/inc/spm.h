#ifndef _SPM_H_
#define _SPM_H_
/*==============================================================================
  FILE:         spm.h

  OVERVIEW:     This file contains APIs for external modules to interact with
                SPM HW block(s).

  DEPENDENCIES: None
                
                Copyright (c) 2009-2016 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/spm/inc/spm.h#1 $
$DateTime: 2020/02/10 01:57:30 $
================================================================================*/
#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include "comdef.h"
#include "spm_common.h"
#include "spm_dyn.h"

/*=======================================================================
 *                           TYPE DEFINITIONS
 *======================================================================*/
/**
 * @brief Forward declaration of SPM configuration structure. This struct's
 *        definition could be version specific.
 */
struct spm_hal_bsp_cfg_s;

/**
 * @brief Forward declaration of SPM low power mode structure. Its definition
 *        could be SPM version specific.
 */
struct spm_hal_bsp_mode_s;

/**
 * @brief Structure containing information about a specific SPM instance.
 *
 * This can be moved to internal header file eventually. In general, each 
 * target will have one or more instances of this structure in target 
 * specific file(s).
 */
typedef struct spm_s
{
  const char                *name;          /* Name of the SPM instance - same as 
                                             * controlled entity e.g core_n, clust_m */
  size_t                    offset;         /* Offset from subsystem base in mem map */
  struct spm_hal_bsp_cfg_s  *cfg;           /* Init time config */
  struct spm_hal_bsp_mode_s *modes;         /* List of modes for this SPM */
  uint32                    mode_count;     /* Number of mode in above list */

  /* Internal fields */
  void                      *lock;          /* Mutex to prevent multiple operations on this instance */
  uint8                     *addr;          /* Instance address in memory map */
  uint32                    copied_cmds;    /* Number of commands copied on this SPM
                                             * instance */
  struct spm_hal_bsp_mode_s *dyn_modes;     /* List of dynamic modes for this SPM */
  uint32                    dyn_mode_count; /* Number of mode in above list */
}spm_t;

/**
 * @brief Generic enumeration that can be used for different 
 *        SPM sequence mode ID's
 */
typedef enum
{
  SPM_MODE_CLK_GATE,         /* Gate Clock to Processor Core            */
  SPM_MODE_VDD_MIN,          /* Minimize the Processor Core Voltage     */
  SPM_MODE_APCR_PLL_ON,      /* APCR/Fast PC with PLL on                */
  SPM_MODE_APCR_PLL_LPM,     /* APCR/Fast PC with PLL stand by or off   */
  SPM_MODE_APCR_RAIL_LPM,    /* APCR/Fast PC with supply rail to LPM    */
  SPM_MODE_PWRC,             /* PC Processor Core using PMIC            */
  SPM_MODE_PWRC_BHS,         /* PC Q6 CORE using BHS.                   */
  SPM_MODE_PWRC_L2RET,       /* PC with L2 retention                    */
  SPM_MODE_L2_RETENTION,     /* Retain Power to L2 Cache Memory         */
  SPM_MODE_L2_GDHS,          /* Power Off L2 Cache using Local Switch   */
  SPM_MODE_L2_OFF,           /* Power Off L2 Cache                      */
  SPM_NUM_LOW_POWER_MODES
} spm_low_power_mode_type;

/*=======================================================================
 *                           GLOBAL DRIVER FUNCTIONS
 *======================================================================*/

/**
 * @brief Performs intialization of common SPM driver (SPM instance agnostic
 *        initialization).
 *
 * @note This function must be called before calling any other SPM function.
 */
void spm_driver_init(void);

/*=======================================================================
 *                   GLOBAL SPM INSTANCE FUNCTIONS
 *======================================================================*/
/**
 * @brief Performs SPM instance specific initialization. 
 *
 * @note This function must be called on an instance before calling any
 *       other functions that take SPM handle as one of the parameters.
 *
 * @dependency spm_driver_init
 *
 * @param handle: Handle to SPM that is going to be initialized.
 *
 * @return SPM error code (@see spm_result_t)
 */
spm_result_t spm_instance_init(spm_handle handle);

/**
 * @brief Sets a low power mode in SPM. The configured low power mode 
 *        settings will take place next time SPM state machine kicks
 *        in.
 *
 * @dependency spm_instance_init
 *
 * @param handle: Handle to SPM which needs to be configured for low power mode.
 * @param mode: Low power mode id (typically corresponds to the ones defined
 *              in subsystem HPG).
 *
 * @return SPM error code (@see spm_result_t)
 */
spm_result_t spm_instance_set_lpm(spm_handle handle, uint8 mode);

/**
 * @brief Returns the index of low power mode the input SPM is currently
 *        executing.
 * 
 * @dependency spm_instance_init
 *
 * @param handle: Handle to SPM where we want to find out running low 
 *                power mode.
 *
 * @param mode_id: Low power mode id (negative value if SPM is not executing
 *                 any low power mode currently).
 *
 * @return SPM error code (@see spm_result_t)
 */
spm_result_t spm_instance_get_executing_lpm(spm_handle handle, uint16 *mode_id);

/**
 * @brief Sets SPM to perform or skip RPM handshake when command sequence
 *        triggers next time.
 *
 * @dependency spm_instance_init
 *
 * @param handle: Handle to SPM which needs to be configured for handshaking 
 *                with RPM.
 * @param handshake: Value to indicate whether to perform handshake or skip it
 *                   (TRUE - Perform RPM handshake, FALSE - skip it).
 *
 * @return SPM error code (@see spm_result_t)
 */
spm_result_t spm_instance_set_rpm_handshake(spm_handle handle, boolean handshake);

/**
 * @brief Enables or disables SPM.
 *
 * @dependency spm_instance_init
 *
 * @param handle: Handle to the SPM that we want to enable or disable.
 * @param enable: If TRUE, enables the SPM. If FALSE, disables SPM.
 *
 * @return SPM error code (@see spm_result_t)
 */
spm_result_t spm_instance_enable(spm_handle handle, boolean enable);

#ifdef __cplusplus
}
#endif

#endif
