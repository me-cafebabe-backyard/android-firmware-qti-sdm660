/*==============================================================================
  FILE:         spm_config.c

  OVERVIEW:     This file contains target specific data/configuration for SPM
                instances.

  DEPENDENCIES: None
                
                Copyright (c) 2015 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/spm/src/asic/8996/spm_config.c#1 $
$DateTime: 2020/02/10 01:57:30 $
================================================================================*/
#include "spm.h"
#include "spm_hal.h"
#include "spm_hal_bsp.h"
#include "spm_config.h"

/*==========================================================================
 *                           INTERNAL MACROS
 *=========================================================================*/
/**
 * @brief Shortened wrapper macros for SPM HAL command sequence macros
 */
#define PWR_CTLX  SPM_HAL_SEQ_PWR_CTLX_CMD 
#define PMIC      SPM_HAL_SEQ_PMIC_CMD
#define EVENT     SPM_HAL_SEQ_EVENT_CMD
#define DLY       SPM_HAL_SEQ_DLY_CMD
#define SLEEP     SPM_HAL_SEQ_SLEEP_CMD
#define END       SPM_HAL_SEQ_END_CMD

/* Default value for the sync events bits from the HPG */
#define SYNC_EVENTS 0xFF000000

/*==========================================================================
 *                                   NOTE
 *=========================================================================*/
/**
 * Even though different low power modes share some commands, for some 
 * of them actual impact at the HW level will be determined by special control
 * registers values (e.g. SPMCTL) which are programmed as part of enter 
 * functions of low power modes. Below is the list of such known 
 * commands/toggles.
 *
 * QDSP6_RESET
 * -----------
 * Depending on how SPMCTL_EN_ARES register is programed, this command may 
 * reset core differently (partially or full).
 * 
 * QDSP6_RETAIN_SAVE
 * -----------------
 * If SAVE field in SPMCTL_EN_STATERET is programed zero, this command/toggle 
 * may not take impact. (For example in Power collapse - but we removed this 
 * toggle itself from sequence).
 *
 * QDSP6_RETAIN_RESTORE 
 * --------------------
 * Same as QDSP6_RETAIN_SAVE but with RESTORE field.
 *
 * QDSP6_PMI
 * ---------
 * Same as QDSP6_RETAIN_SAVE but with WAKEUP_IRQ field.
 */

/*==========================================================================
 *                          CPU SPM CONFIGURATIONS
 *=========================================================================*/
/* Init time config for SPM. */
static spm_hal_bsp_cfg_t g_cpuSpmCfg = 
{
  /* SawCfg
   * ------
   * frc_ref_clk_on,  clk_div */
  {  0x0,             0x1F },

  /* SawSpmCtlCfg
   * ------------
   * spm_wakeup */
  {  SPM_HAL_BSP_WAKEUP_CONFIG_0 },

  /* SawSpmDlyType
   * -------------
   * delay1,  delay2,   delay3 */
  {  0x0,     0x0,     0x0 },

  /* SawSpmPmicData[]
   * ----------
   *  mode,                           data, delay,  size, index */
  NULL, 0
}; /* SPM_BSP_DATA */

/*==========================================================================
 *                           SPM COMMAND SEQUENCES 
 *=========================================================================*/
/* SPM command sequence for ADSP APCR with PLL on */
static uint8 spmCmdSeqAPCRPLLOn[] =
{ 
  /* index 0x0 */
  PWR_CTLX( QDSP6_CLOCK, 0 ),          /* QDSP6 Clock Off */
  PWR_CTLX( QDSP6_CLAMP, 0 ),          /* QDSP6 Assert Clamp */
  PWR_CTLX( QDSP6_RETAIN_SAVE, 0 ),    /* Assert QDSP6 retain save */
  PWR_CTLX( QDSP6_RETAIN_SAVE, 0 ),    /* Deassert QDSP6 retain save */

  /* index 0x4 */
  PWR_CTLX( QDSP6_COPROC_BHS, 0 ),     /* Assert CoProc BHS off */
  PWR_CTLX( QDSP6_CLAMP_WL, 0 ),       /* QDSP6 Assert Clamp WL */
  PWR_CTLX( QDSP6_MEM_RET_SLEEP, 0 ),  /* Retention memory sleep */
  DLY( DLY_1 ),                        /* Delay for in-rush current */

  /* index 0x8 */
  PWR_CTLX( QDSP6_QMC_MEM_CLAMP, 0 ),  /* QDSP6 QMC Mem Clamp */
  PWR_CTLX( QDSP6_LDO_BYPASS, 0 ),     /* Force LDO Bypass Off */
  PWR_CTLX( QDSP6_BHS, 1 ),            /* Force BHS Off */
  PWR_CTLX( QDSP6_LDO, 0 ),            /* Force LDO Off */

  /* index 0xC */
  SLEEP( NO_RPM_HS ),                  /* Init Sleep to NO RPM HS */
  PWR_CTLX( QDSP6_RESET, 0 ),          /* Assert Reset */
  PWR_CTLX( QDSP6_LDO, 0 ),            /* Deassert LDO Off */
  PWR_CTLX( QDSP6_BHS, 1 ),            /* Deassert BHS Off */

  /* index 0x10 */
  PWR_CTLX( QDSP6_LDO_BYPASS, 0 ),     /* Deassert LDO Bypass Off */
  PWR_CTLX( QDSP6_QMC_MEM_CLAMP, 0 ),  /* Deassert QMC Mem Clamp */
  PWR_CTLX( QDSP6_MEM_RET_SLEEP, 1 ),  /* Retention memory sleep */
  PWR_CTLX( QDSP6_CLAMP_WL, 0 ),       /* Deassert QDSP6 Clamp WL */

  /* index 0x14 */
  PWR_CTLX( QDSP6_COPROC_BHS, 1 ),     /* Deassert CoProc BHS off */
  PWR_CTLX( QDSP6_RETAIN_RESTORE, 0 ), /* Assert QDSP6 retain restore */
  PWR_CTLX( QDSP6_RETAIN_RESTORE, 0 ), /* Deassert QDSP6 retain restore */
  PWR_CTLX( QDSP6_CLAMP, 0 ),          /* Deassert QDSP6 Clamp */

  /* index 0x18 */
  PWR_CTLX( QDSP6_RESET, 0 ),          /* Deassert Reset */
  PWR_CTLX( QDSP6_PMI, 0 ),            /* Assert Power Manager Interrupt (PMI) */
  PWR_CTLX( QDSP6_PMI, 0 ),            /* Deassert PMI */
  PWR_CTLX( QDSP6_CLOCK, 0 ),          /* Deassert QDSP6 Clock Off */

  /* index 0x1C */
  END                                 /* End of Program */
};

/* SPM command sequence for ADSP APCR PLL in low power mode. */
static uint8 spmCmdSeqAPCRPLLLPM[] =
{
  /* index 0x0 */
  PWR_CTLX( QDSP6_CLOCK, 1 ),         /* QDSP6 Clock Off */
  EVENT( EVENT_2 ),                   /* Wait for clock off event */
  PWR_CTLX( QDSP6_CLAMP, 0 ),         /* Assert clamp */
  PWR_CTLX( QDSP6_RETAIN_SAVE, 0 ),   /* Assert QDSP6 retain save */

  /* index 0x4 */
  PWR_CTLX( QDSP6_RETAIN_SAVE, 0 ),   /* Deassert QDSP6 retain save */
  PWR_CTLX( QDSP6_COPROC_BHS, 0 ),    /* Assert CoProc BHS off */
  PWR_CTLX( QDSP6_CLAMP_WL, 0 ),      /* Assert QDSP6 Clamp WL */
  PWR_CTLX( QDSP6_MEM_SRC_BIAS, 0 ),  /* Assert memory biasing */

  /* index 0x8 */
  PWR_CTLX( QDSP6_MEM_RET_SLEEP, 0 ), /* Assert ret memory sleep */
  PWR_CTLX( QDSP6_MEM_SLEEP, 1 ),     /* Assert non ret memory sleep */
  PWR_CTLX( QDSP6_QMC_MEM_CLAMP, 0 ), /* Assert Q6 memory clamp */
  PWR_CTLX( QDSP6_LDO_BYPASS, 0 ),    /* Assert LDO bypass */

  /* index 0xC */
  PWR_CTLX( QDSP6_BHS, 0 ),           /* Assert BHS off */
  PWR_CTLX( QDSP6_LDO, 0 ),           /* Assert LDO off */
  PWR_CTLX( QDSP6_SMMU_PD_VOTE, 0 ),  /* Vote off SMMU GDHS */
  PWR_CTLX( QDSP6_PLL_VOTE, 0 ),      /* LPASS vote on PLL mode */

  /* index 0x10 */
  SLEEP( NO_RPM_HS ),                 /* Sleep w/o RPM handshake */
  PWR_CTLX( QDSP6_RESET, 0 ),         /* Assert QDSP6 reset */
  PWR_CTLX( QDSP6_PLL_VOTE, 0 ),      /* LPASS vote on PLL restore */
  PWR_CTLX( QDSP6_SMMU_PD_VOTE, 0 ),  /* Vote off SMMU GDHS */  

  /* index 0x14 */
  PWR_CTLX( QDSP6_LDO, 0 ),           /* Deassert LDO force off */
  PWR_CTLX( QDSP6_BHS, 1 ),           /* Deassert BHS off */
  PWR_CTLX( QDSP6_LDO_BYPASS, 0 ),    /* Deassert LDO Bypass off */
  PWR_CTLX( QDSP6_QMC_MEM_CLAMP, 0 ), /* Deassert QMC memory clamp */

  /* index 0x18 */
  PWR_CTLX( QDSP6_MEM_SLEEP, 1 ),     /* Deassert non ret memory sleep */
  PWR_CTLX( QDSP6_MEM_RET_SLEEP, 1 ), /* Deassert ret memory sleep */
  PWR_CTLX( QDSP6_MEM_SRC_BIAS, 0 ),  /* Deassert source biasing */
  PWR_CTLX( QDSP6_CLAMP_WL, 0 ),      /* Deassert QDSP6 Clamp WL */

  /* index 0x1C */
  PWR_CTLX( QDSP6_COPROC_BHS, 1 ),    /* Deassert CoProc BHS off */
  PWR_CTLX( QDSP6_RETAIN_RESTORE, 0 ),/* Assert QDSP6 retain restore */
  PWR_CTLX( QDSP6_RETAIN_RESTORE, 0 ),/* Deassert QDSP6 retain restore */
  PWR_CTLX( QDSP6_CLAMP, 0 ),         /* Deassert QDSP6 clamp */

  /* index 0x20 */
  PWR_CTLX( QDSP6_RESET, 0 ),         /* Deassert QDSP6 reset */
  PWR_CTLX( QDSP6_PMI, 0 ),           /* Assert PMI */
  PWR_CTLX( QDSP6_PMI, 0 ),           /* Deassert PMI */
  EVENT( EVENT_0 ),                   /* Wait for PLL lock */

  /* index 0x24 */
  EVENT( EVENT_4 ),                   /* Wait for SMMU power up */
  PWR_CTLX( QDSP6_CLOCK, 0 ),         /* Deassert Clock off */
  END                                 /* End of command sequence */
};

/* SPM command sequence for ADSP APCR PLL in low power mode. */
static uint8 spmCmdSeqBHS[] =
{
  /* index 0x0 */
  PWR_CTLX( QDSP6_CLOCK, 1 ),         /* QDSP6 Clock Off */
  EVENT( EVENT_2 ),                   /* Wait for clock off event */
  PWR_CTLX( QDSP6_CLAMP, 0 ),         /* Assert clamp */
  PWR_CTLX( QDSP6_COPROC_BHS, 0 ),    /* Assert CoProc BHS off */

  /* index 0x4 */
  PWR_CTLX( QDSP6_CLAMP_WL, 0 ),      /* Assert QDSP6 Clamp WL */
  PWR_CTLX( QDSP6_MEM_SRC_BIAS, 0 ),  /* Assert memory biasing */
  PWR_CTLX( QDSP6_MEM_RET_SLEEP, 0 ), /* Assert ret memory sleep */
  PWR_CTLX( QDSP6_MEM_SLEEP, 0 ),     /* Assert non ret memory sleep */

  /* index 0x8 */
  PWR_CTLX( QDSP6_QMC_MEM_CLAMP, 0 ), /* Assert Q6 memory clamp */
  PWR_CTLX( QDSP6_LDO_BYPASS, 0 ),    /* Assert LDO bypass */
  PWR_CTLX( QDSP6_BHS, 0 ),           /* Assert BHS off */
  PWR_CTLX( QDSP6_LDO, 0 ),           /* Assert LDO off */

  /* index 0x1C */
  PWR_CTLX( QDSP6_SMMU_PD_VOTE, 0 ),  /* Vote for SMMU GDHS */
  PWR_CTLX( QDSP6_PLL_VOTE, 0 ),      /* LPASS vote on PLL mode */
  SLEEP( NO_RPM_HS ),                 /* Sleep w/o RPM handshake */
  PWR_CTLX( QDSP6_RESET, 0 ),         /* Assert QDSP6 reset */

  /* index 0x10 */
  PWR_CTLX( QDSP6_PLL_VOTE, 0 ),      /* LPASS vote on PLL restore */
  PWR_CTLX( QDSP6_SMMU_PD_VOTE, 0 ),  /* Vote for SMMU GDHS */
  PWR_CTLX( QDSP6_LDO, 0 ),           /* Deassert LDO force off */
  PWR_CTLX( QDSP6_BHS, 1 ),           /* Deassert BHS off */

  /* index 0x14 */
  PWR_CTLX( QDSP6_LDO_BYPASS, 0 ),    /* Deassert LDO Bypass off */
  PWR_CTLX( QDSP6_QMC_MEM_CLAMP, 0 ), /* Deassert QMC memory clamp */
  PWR_CTLX( QDSP6_MEM_SLEEP, 1 ),     /* Deassert non ret memory sleep */
  PWR_CTLX( QDSP6_MEM_RET_SLEEP, 1),  /* Deassert ret memory sleep */

  /* index 0x18 */
  PWR_CTLX( QDSP6_MEM_SRC_BIAS, 0 ),  /* Deassert source biasing */
  PWR_CTLX( QDSP6_CLAMP_WL, 0 ),      /* Deassert QDSP6 Clamp WL */
  PWR_CTLX( QDSP6_COPROC_BHS, 1 ),    /* Deassert CoProc BHS off */
  PWR_CTLX( QDSP6_CLAMP, 0 ),         /* Deassert QDSP6 clamp */

  /* index 0x1C */
  PWR_CTLX( QDSP6_RESET, 0 ),         /* Deassert QDSP6 reset */
  EVENT( EVENT_0 ),                   /* Wait for PLL lock */
  EVENT( EVENT_4 ),                   /* Wait for SMMU power up */
  PWR_CTLX( QDSP6_CLOCK, 0 ),         /* Deassert Clock off */

  /* index 0x20 */
  END                                 /* End of command sequence */
};

/* Mode configurations objects. */
static spm_hal_bsp_mode_t g_cpuModes[] =
{
  { 
    {SPM_ARRAY(spmCmdSeqAPCRPLLOn)}, SPM_MODE_APCR_PLL_ON,
    (SYNC_EVENTS | SPM_HAL_ISAR_SET)
  },
  {
    {SPM_ARRAY(spmCmdSeqAPCRPLLLPM)}, SPM_MODE_APCR_PLL_LPM,
    (SYNC_EVENTS | SPM_HAL_ISAR_SET)
  },
  {
    {SPM_ARRAY(spmCmdSeqBHS)}, SPM_MODE_PWRC,
    (SYNC_EVENTS | SPM_HAL_ISAR_SET)
  }
};

/*==========================================================================
 *                          SUBSYSTEM SPM INSTANCES
 *=========================================================================*/
/* Array containing necessary information of each SPM instance on a given subsystem. */
spm_t g_spmInstances[] =
{
  {
    SPM_DEFAULT_INSTANCE_NAME,    /* Name */
    0,                            /* Offset */
    &g_cpuSpmCfg,                 /* config */
    SPM_ARRAY(g_cpuModes)         /* Mode & size */
  },
};

