#ifndef Q6_LPM_CONFIG
#define Q6_LPM_CONFIG
/*==============================================================================
  FILE:         q6_lpm_config.h

  OVERVIEW:     This file contains the APIs for configuring Q6 cpu to low 
                power modes. These APIs are may have Q6 version specific
                implementation. 

  DEPENDENCIES: None

                Copyright (c) 2014,2016 QUALCOMM Technologies Incorporated.
                All Rights Reserved.
                Qualcomm Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/sleep2.0/inc/q6_lpm_config.h#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#include "comdef.h"
#include "sleep.h"
#include "spm.h"

/*==============================================================================
 *                                GLOBAL TYPES
 *============================================================================*/
/** 
 * mem_state
 * 
 * @brief Used to enumerate lprm configuration for cacheLPR_l2ConfigureSPM
 */
typedef enum
{
  MEM_RET,       /* Config processor SS & MEM for ret           */
  MEM_NORET,     /* Config processor SS & MEM for non-ret       */
} mem_state;

/*==============================================================================
 *                             GLOBAL FUNCTIONS
 *============================================================================*/
/**
 * q6LPMConfig_setupBase
 *
 * @brief This function configures basic low power mode related Q6 registers 
 *        that remain same across all low power modes Q6 can be put in to.
 */
void q6LPMConfig_setupBase(void);

/**
 * q6LPMConfig_setupModeConfig
 *
 * @brief Performs Q6SS register configuration related to mode passed as
 *        input.
 *
 * @param coreMode  : Specifies the low power mode we want Q6 to put when
 *                    it goes idle next.
 * @param flag      : Boolean indicating a specific option based on the coreMode
 *                    For APCR modes:
 *                      Indicates PMI interrupt needs to be triggered upon spm exit
 *                      from low power mode.  Currently it is required only for APCR low power
 *                      modes entered from single threaded context.
 *                    For Clockgate mode:
 *                      Indicates if the mode should be enabled or disabled.  When clockgate is
 *                      disabled, the previously configured mode will be effective
 *                    For other modes:
 *                      Currently has no meaning
 */
void q6LPMConfig_setupModeConfig(spm_low_power_mode_type  coreMode, 
                                 boolean                  flag);

/**
 * q6LPMConfig_setupL2Config
 *
 * @brief Performs Q6SS register configuration to configure the L2 cache for 
 *        retention or non-retention 
 *
 * @param state: Requested L2 memory state
 */
void q6LPMConfig_setupL2Config(mem_state state);

#endif
