#ifndef _SPM_CONFIG_H_
#define _SPM_CONFIG_H_
/*==============================================================================
  FILE:         spm_config.h

  OVERVIEW:     This file provides types for target specific SPM command
                sequences.

  DEPENDENCIES: None
                
                Copyright (c) 2015 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/spm/src/asic/8996/spm_config.h#1 $
$DateTime: 2020/02/10 01:57:30 $
================================================================================*/
#ifdef __cplusplus
extern "C" {
#endif

/*=======================================================================
 *                           TYPE DEFINITIONS
 *======================================================================*/
/* Enumeration containing SPM control signal mapping for this target. */
typedef enum
{
/*       Command            Index
  -----------------------   ------- */
  QDSP6_RESET,               /* 0 */
  QDSP6_CLAMP,               /* 1 */
  QDSP6_CLOCK,               /* 2 */
  QDSP6_MEM_SLEEP,           /* 3 */
  QDSP6_BHS,                 /* 4 */
  QDSP6_LDO_BYPASS,          /* 5 */
  QDSP6_LDO,                 /* 6 */
  QDSP6_PLL_VOTE,            /* 7 */
  QDSP6_SMMU_PD_VOTE  = 13,  /* 13 */
  QDSP6_CLAMP_WL      = 16,  /* 16 */
  QDSP6_QMC_MEM_CLAMP,       /* 17 */
  QDSP6_MEM_SRC_BIAS  = 19,  /* 19 */
  QDSP6_RETAIN_SAVE,         /* 20 */
  QDSP6_RETAIN_RESTORE,      /* 21 */
  QDSP6_PMI,                 /* 22 */
  QDSP6_MEM_RET_SLEEP = 30,  /* 30 */
  QDSP6_COPROC_BHS    = 31   /* 31 */
}SPM_SEQ_PWR_CTL_BITS;

/* Enumeration to indicate bit for different PMIC data in SPM command. */
typedef enum
{
  DATA_0,
  DATA_1,
  DATA_2,
} SPM_SEQ_PMIC_DATA_BITS;

/* Enumeration to indicate bit settings for RPM interaction during Sleep in SPM command. */
typedef enum
{
  NO_RPM_HS,
  RPM_HS
} SPM_SEQ_SLEEP_BITS;

/* Event bits for SPM command. */
typedef enum
{
  EVENT_0,
  EVENT_1,
  EVENT_2,
  EVENT_3,
  EVENT_4
} SPM_SEQ_EVENT_BITS;

/* Enumeration to be used for delay field selection. */
typedef enum
{
  DLY_1 = 1,
  DLY_2,
  DLY_3
} SPM_SEQ_DLY_BITS;

#ifdef __cplusplus
}
#endif

#endif

