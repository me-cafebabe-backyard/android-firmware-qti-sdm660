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
$Header: //components/rel/core.qdsp6/1.0.c2/power/spm/src/asic/8998/spm_config.h#1 $
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
/*       Command            Index     Mask register
  -----------------------   -------   --------------                  */
  QDSP6_RESET = 0,          /* 0      SPMCTL_EN_ARES                  */
  QDSP6_CLAMP,              /* 1      SPMCTL_EN_CLAMP                 */
  QDSP6_CLOCK,              /* 2      SPMCTL_EN_CLK                   */
  QDSP6_MEM_SLEEP,          /* 3      SPMCTL_EN_MEM                   */
  QDSP6_BHS,                /* 4      SPMCTL_EN_BHS   
                                      SPMCTL_EN_EXT[7]                */
  QDSP6_LDO_BYPASS,         /* 5      SPMCTL_EN_LDO[0]                */
  QDSP6_LDO_OFF,            /* 6      SPMCTL_EN_LDO[5]                */
  QDSP6_PLL_OPMODE0,        /* 7      SPMCTL_EN_PLL (STANDBY)
                                      SPMCTL_EN_EXT                   */
  QDSP6_PLL_RESET,          /* 8      SPMCTL_EN_PLL
                                      SPMCTL_EN_EXT                   */
  QDSP6_PLL_OUTPUT,         /* 9      SPMCTL_EN_PLL
                                      SPMCTL_EN_EXT                   */
  QDSP6_LDO_BG,             /* 10     SPMCTL_EN_LDO[6]                */
  QDSP6_EXT_SPARE,          /* 11     SPMCTL_EN_EXT[8]                */
  QDSP6_AON_HS,             /* 12     SPMCTL_EN_EXT[9]  (SSC only)    */
  QDSP6_SMMU_PD_VOTE,       /* 13     SPMCTL_EN_EXT[10] (LPASS only)  */
  QDSP6_EXT_XO_CLK_SELECT,  /* 14     SPMCTL_EN_EXT[6]  (MSS only)    */
  QDSP6_RSVD_15,            /* 15     Reserved                        */
  QDSP6_CLAMP_WL,           /* 16     SPMCTL_EN_MEM                   */
  QDSP6_QMC_MEM_CLAMP,      /* 17     SPMCTL_EN_MEM                   */
  QDSP6_PLL_OPMODE1,        /* 18     SPMCTL_EN_PLL (N/A in Nazgul)   */
  QDSP6_MEM_SRC_BIAS,       /* 19     SPMCTL_EN_MEM (N/A in Nazgul)   */
  QDSP6_RETAIN_SAVE,        /* 20     SPMCTL_EN_STATERET[0]           */
  QDSP6_RETAIN_RESTORE,     /* 21     SPMCTL_EN_STATERET[1]           */
  QDSP6_PMI,                /* 22     SPMCTL_EN_STATERET[2]           */
  QDSP6_BUS_HALT,           /* 23     SPMCTL_EN_ISOINTF_CTL           */
  QDSP6_BUS_INT_CLAMP_SET,  /* 24     SPMCTL_EN_ISOINTF_CLAMP         */
  QDSP6_BUS_PWR_CLAMP_SET,  /* 25     SPMCTL_EN_ISOINTF_CLAMP         */
  QDSP6_BUS_INT_CLAMP_CLR,  /* 26     SPMCTL_EN_ISOINTF_CLAMP         */
  QDSP6_BUS_PWR_CLAMP_CLR,  /* 27     SPMCTL_EN_ISOINTF_CLAMP         */
  QDSP6_BUS_FIFO_RESET,     /* 28     SPMCTL_EN_ISOINTF_CTL           */
  QDSP6_BUS_CLK,            /* 29     SPMCTL_EN_ISOINTF_CLK           */
  QDSP6_MEM_RET_SLEEP,      /* 30     SPMCTL_EN_MEM                   */
  QDSP6_COPROC_BHS_OFF      /* 31     SPMCTH_EN_BHS (LPASS only)      */
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
  /*       Event            Index     Mask register
  -----------------------   -------   --------------                  */
  EVENT_PLL_LOCK = 0,       /* 0      QDSP6SS_SPM_EVENT_CTL[9,1:0]    */
  EVENT_QDSP6_PWR,          /* 1      QDSP6SS_SPM_EVENT_CTL[8,2]      */
  EVENT_QDSP6_CLK,          /* 2      QDSP6SS_SPM_EVENT_CTL[3]        */
  EVENT_BUS_HALT,           /* 3      QDSP6SS_SPM_EVENT_CTL[6,4]      */
  EVENT_SMMU_PWR,           /* 4      QDSP6SS_SPM_EVENT_CTL[7] (LPASS)*/
  EVENT_RSVD_5,             /* 5      Reserved                        */
  EVENT_RSVD_6,             /* 6      Reserved                        */
  EVENT_RSVD_7              /* 7      Reserved                        */
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

