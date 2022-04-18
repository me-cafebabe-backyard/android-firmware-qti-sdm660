#ifndef ISLAND_SPM_H
#define ISLAND_SPM_H
/*==============================================================================
  FILE:         island_spm.h

  OVERVIEW:     Types & prototypes for internal SPM island transition functions

  DEPENDENCIES: None
  
                Copyright (c) 2014-2016 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/uSleep/src/transition/island_spm.h#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#include "DALStdDef.h"
#include "spm_common.h"
#include "uSleepi.h"

/*==============================================================================
                            DEFINITIONS & TYPES
 =============================================================================*/
/* Transtion interrupts */
#define ISLAND_ENTRY_IRQ   156 /* enter_island_mode_irq */
#define ISLAND_EXIT_IRQ    194 /* q6ss_spm_trig_done_irq[1] */

/*==============================================================================
                              COMMAND MACROS
 =============================================================================*/
/*******************************************************************************                                                                          
 * The following macros are taken from the target SPM data file and duplicated
 * here for easy readability in uSleep code.
 ******************************************************************************/ 
/* Enumeration containing SPM control signal mapping for this target. */
typedef enum 
{
/*       Command            Index     Mask register
  -----------------------   -------   --------------                  */
  QDSP6_RESET = 0,          /* 0      SPMCTL_EN_ARES                  */
  QDSP6_CLAMP,              /* 1      SPMCTL_EN_CLAMP                 */
  QDSP6_CLOCK,              /* 2      SPMCTL_EN_CLK                   */
  QDSP6_MEM_NONRET_SLEEP,   /* 3      SPMCTL_EN_MEM                   */
  QDSP6_BHS,                /* 4      SPMCTL_EN_BHS   
                                      SPMCTL_EN_EXT[7]                */
  QDSP6_LDO_BYPASS,         /* 5      SPMCTL_EN_LDO[0]                */
  QDSP6_LDO_OFF,            /* 6      SPMCTL_EN_LDO[4]                */
  QDSP6_PLL_VOTE,           /* 7      SPMCTL_EN_PLL
                                      SPMCTL_EN_EXT                   */
  QDSP6_PLL_BYPASS,         /* 8      SPMCTL_EN_PLL
                                      SPMCTL_EN_EXT                   */
  QDSP6_PLL_OUTPUT,         /* 9      SPMCTL_EN_PLL
                                      SPMCTL_EN_EXT                   */
  QDSP6_LDO_ON,             /* 10     SPMCTL_EN_LDO[2]                */
  EXT_SPARE,                /* 11     SPMCTL_EN_EXT[8]                */
  EXT_SHUTDOWN,             /* 12     SPMCTL_EN_EXT[9]  (SSC only)    */
  EXT_SMMU_VOTE,            /* 13     SPMCTL_EN_EXT[10] (LPASS only)  */
  EXT_XO_SELECT_UNUSED,     /* 14     SPMCTL_EN_EXT[6]                */
  QDSP6_LDO_RET_VREF,       /* 15     SPMCTL_EN_LDO[6]                */
  QDSP6_CLAMP_WL,           /* 16     SPMCTL_EN_MEM                   */
  QDSP6_QMC_MEM_CLAMP,      /* 17     SPMCTL_EN_MEM                   */
  QPSP6_PLL_FREEZE,         /* 18     SPMCTL_EN_PLL                   */
  QDSP6_MEM_SRC_BIAS,       /* 19     SPMCTL_EN_MEM                   */
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
}island_spm_seq_pwr_ctl;

/* Set of macros to create SPM command to toggle power control bits defined in
 * @island_spm_seq_pwr_ctl */
#define SPM_CMD_BIT7_4(bit)   (((bit) & 0xF) << 4)
#define SPM_CMD_BIT3(bit)     (((bit) & 0x10) >> 1)
#define SPM_CMD_BIT2_1(delay) ((delay) << 1)
#define SPM_SEQ_PWR_CTL(bit,delay) ( SPM_CMD_BIT7_4(bit)   | \
                                     SPM_CMD_BIT3(bit)     | \
                                     SPM_CMD_BIT2_1(delay) ) 

/* Event bits for SPM command. */
typedef enum
{
  EVENT_0,
  EVENT_1,
  EVENT_2,
  EVENT_3
}island_spm_seq_event;

/* Macro to create SPM command to wait for events defined in island_spm_seq_event.*/
#define SPM_SEQ_EVENT_CTL(bit,delay) (bit<<4)|(0xB)

/* SPM end of sequence command. */
#define SPM_SEQ_END_CTL(bit,delay)   (0xF)

/*==============================================================================
                                  TYPES
 =============================================================================*/
/* Contains a single SPM sequence for SPM sequence registration */
typedef struct island_spm_seq_s
{
  spm_sequence_data_t data;
  uint16              start_addr;
}island_spm_seq;

/* Contains the island entry and exit SPM sequences */
typedef struct island_spm_island_sequence_s
{
  island_spm_seq  enter;
  island_spm_seq  exit;
}island_spm_island_sequence;

/* Index into the spm_trig_cfgn register that holds the index into the
 * SPM sequence to run when SW triggers it. */
typedef enum
{
  ISLAND_SW_TRIGGER_ENTER = 0,
  ISLAND_SW_TRIGGER_EXIT,
  
  ISLAND_SW_TRIGGER_LAST
}island_spm_soft_trigger;

/*==============================================================================
                            FUNCTION DECLARATIONS
 =============================================================================*/
/**
 * islandSPM_setupSequenceTransition
 *
 * @brief Performs any setup required to trigger island entry
 */ 
void islandSPM_setupSequenceTransition(void);

#endif /* ISLAND_SPM_H */

