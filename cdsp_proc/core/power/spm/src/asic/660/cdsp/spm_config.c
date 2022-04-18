/*==============================================================================
  FILE:         spm_config.c

  OVERVIEW:     This file contains target specific data/configuration for SPM
                instances.
 
  NOTE:         Based on HPG_QDSP6SS_v62_1.2+ (3.01 - September 29, 2016)
  
  DEPENDENCIES: None
                
                Copyright (c) 2015-2016 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/spm/src/asic/660/cdsp/spm_config.c#1 $
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
#define SYNC_EVENTS 0x00000000

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
 * Depending on how SPMCTL_EN_ARES register is programmed, this command may 
 * reset core differently (partially or full).
 * 
 * QDSP6_RETAIN_SAVE
 * -----------------
 * If SAVE field in SPMCTL_EN_STATERET is programmed zero, this command/toggle 
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
/* SPM command sequence for APCR with PLL on (Short seqeunce). */
static uint8 g_spmCmdSeqAPCRPLLOn[] =
{ 
  /* index 0 */
/* 0x20 */  PWR_CTLX( QDSP6_CLOCK,         0 ), /* QDSP6 Clock Off */
/* 0x10 */  PWR_CTLX( QDSP6_CLAMP,         0 ), /* QDSP6 Assert Clamp */
/* 0x48 */  PWR_CTLX( QDSP6_RETAIN_SAVE,   0 ), /* Assert QDSP6 retain save */
/* 0x48 */  PWR_CTLX( QDSP6_RETAIN_SAVE,   0 ), /* Deassert QDSP6 retain save */

  /* index 4 */
/* 0xf8 */  PWR_CTLX( QDSP6_COPROC_BHS_OFF,0 ), /* Coproc BHS off - HVX is PC by HW */
/* 0x8  */  PWR_CTLX( QDSP6_CLAMP_WL,      0 ), /* QDSP6 Assert Clamp WL */
/* 0xe8 */  PWR_CTLX( QDSP6_MEM_RET_SLEEP, 0 ), /* Retention memory sleep */
/* 0x1f */  DLY( DLY_1 ),                       /* Delay for in-rush current */

  /* index 8 */
/* 0x18 */  PWR_CTLX( QDSP6_QMC_MEM_CLAMP, 0 ), /* QDSP6 QMC Mem Clamp */
/* 0x42 */  PWR_CTLX( QDSP6_BHS,           1 ), /* Force BHS Off */
/* 0x3  */  SLEEP( NO_RPM_HS ),                 /* Init Sleep to NO RPM HS */
/* 0x0  */  PWR_CTLX( QDSP6_RESET,         0 ), /* Assert Reset */

  /* index 16 */
/* 0x40 */  PWR_CTLX( QDSP6_BHS,           0 ), /* Deassert BHS Off */
/* 0x1b */  EVENT( EVENT_QDSP6_PWR ),           /* Wait for BHS/LDO ready */
/* 0x18 */  PWR_CTLX( QDSP6_QMC_MEM_CLAMP, 0 ), /* Deassert QMC Mem Clamp */ 
/* 0xea */  PWR_CTLX( QDSP6_MEM_RET_SLEEP, 1 ), /* Retention memory sleep */

  /* index 20 */
/* 0x8  */  PWR_CTLX( QDSP6_CLAMP_WL,      0 ), /* Deassert QDSP6 Clamp WL */
/* 0xfa */  PWR_CTLX( QDSP6_COPROC_BHS_OFF,1 ), /* Coproc BHS on - HVX is PC by HW */
/* 0x58 */  PWR_CTLX( QDSP6_RETAIN_RESTORE,0 ), /* Assert QDSP6 retain restore */
/* 0x58 */  PWR_CTLX( QDSP6_RETAIN_RESTORE,0 ), /* Deassert QDSP6 retain restore */

  /* index 24 */
/* 0x10 */  PWR_CTLX( QDSP6_CLAMP,         0 ), /* Deassert QDSP6 Clamp */
/* 0x0  */  PWR_CTLX( QDSP6_RESET,         0 ), /* Deassert Reset */
/* 0x68 */  PWR_CTLX( QDSP6_PMI,           0 ), /* Assert Power Manager Interrupt (PMI) */
/* 0x68 */  PWR_CTLX( QDSP6_PMI,           0 ), /* Deassert PMI */

  /* index 28 */
/* 0x20 */  PWR_CTLX( QDSP6_CLOCK,         0 ), /* Deassert QDSP6 Clock Off */
/* 0xF  */  END                                 /* End of Program */
};

/* SPM command sequence for APCR or Full PC PLL in low power mode. */
static uint8 g_spmCmdSeqPLLLpm[] =
{
  /* index 0 */
/* 0x20 */  PWR_CTLX( QDSP6_CLOCK,         0 ), /* QDSP6 Clock Off */
/* 0x2b */  EVENT( EVENT_QDSP6_CLK ),           /* Wait for clock off event */
/* 0x10 */  PWR_CTLX( QDSP6_CLAMP,         0 ), /* Assert clamp */
/* 0x48 */  PWR_CTLX( QDSP6_RETAIN_SAVE,   0 ), /* Assert QDSP6 retain save*/

  /* index 4 */
/* 0x48 */  PWR_CTLX( QDSP6_RETAIN_SAVE,   0 ), /* Deassert QDSP6 retain save */
/* 0xf8 */  PWR_CTLX( QDSP6_COPROC_BHS_OFF,0 ), /* Coproc BHS off - HVX is PC by HW */
/* 0x8  */  PWR_CTLX( QDSP6_CLAMP_WL,      0 ), /* Assert QDSP6 Clamp WL */
/* 0xe8 */  PWR_CTLX( QDSP6_MEM_RET_SLEEP, 0 ), /* Assert ret memory sleep */

  /* index 8 */
/* 0x32 */  PWR_CTLX( QDSP6_MEM_SLEEP,     1 ), /* Assert non ret memory sleep */
/* 0x18 */  PWR_CTLX( QDSP6_QMC_MEM_CLAMP, 0 ), /* Assert Q6 QMC memory clamp */
/* 0x40 */  PWR_CTLX( QDSP6_BHS,           0 ), /* Assert BHS off */
/* 0xd0 */  PWR_CTLX( QDSP6_SMMU_PD_VOTE,  0 ), /* Vote off SMMU GDHS */

  /* index 12 */
/* 0x90 */  PWR_CTLX( QDSP6_PLL_OUTPUT,    0 ), /* Disable Q6 PLL outputs */
/* 0x70 */  PWR_CTLX( QDSP6_PLL_RESET,     0 ), /* Reset Q6 PLL  */
/* 0x80 */  PWR_CTLX( QDSP6_PLL_BYPASS,    0 ), /* Bypass Q6 PLL */
/* 0x28 */  PWR_CTLX( QDSP6_PLL_FREEZE,    0 ), /* Freeze Q6 PLL */  
  
 /* index 16 */
/* 0x3  */  SLEEP( NO_RPM_HS),                  /* Sleep w/o RPM handshake */
/* 0x0  */  PWR_CTLX( QDSP6_RESET,         0 ), /* Assert QDSP6 reset */
/* 0x28 */  PWR_CTLX( QDSP6_PLL_FREEZE,    0 ), /* Unfreeze Q6 PLL */
/* 0x84 */  PWR_CTLX( QDSP6_PLL_BYPASS,    2 ), /* Disable Q6 PLL bypass*/  

  /* index 20 */
/* 0x70 */  PWR_CTLX( QDSP6_PLL_RESET,     0 ), /* Release Q6 PLL from Reset*/
/* 0xd0 */  PWR_CTLX( QDSP6_SMMU_PD_VOTE,  0 ), /* Vote on SMMU GDHS */
/* 0x40 */  PWR_CTLX( QDSP6_BHS,           0 ), /* Deassert BHS off */
/* 0x1b */  EVENT( EVENT_QDSP6_PWR ),           /* Wait for BHS/LDO ready */  
  
  /* index 24 */
/* 0x18 */  PWR_CTLX( QDSP6_QMC_MEM_CLAMP, 0 ), /* Deassert Q6 QMC memory clamp */
/* 0x32 */  PWR_CTLX( QDSP6_MEM_SLEEP,     1 ), /* Deassert Q6 memory sleep + pipeline delay to assert L2 */
/* 0xea */  PWR_CTLX( QDSP6_MEM_RET_SLEEP, 1 ), /* Deassert ret memory sleep */
/* 0x8  */  PWR_CTLX( QDSP6_CLAMP_WL,      0 ), /* Assert Q6 clamp_wl */
  
  /* index 28 */
/* 0xfa */  PWR_CTLX( QDSP6_COPROC_BHS_OFF,1 ), /* Coproc BHS on - HVX is PC by HW */
/* 0x58 */  PWR_CTLX( QDSP6_RETAIN_RESTORE,0 ), /* Assert Q6 restore */
/* 0x58 */  PWR_CTLX( QDSP6_RETAIN_RESTORE,0 ), /* De-assert Q6 restore */
/* 0x10 */  PWR_CTLX( QDSP6_CLAMP,         0 ), /* Deassert Q6 clamp */
  
  /* index 32 */
/* 0x0  */  PWR_CTLX( QDSP6_RESET,         0 ), /* Deassert Q6 reset */
/* 0x68 */  PWR_CTLX( QDSP6_PMI,           0 ), /* Assert SPM wakeup IRQ */
/* 0x68 */  PWR_CTLX( QDSP6_PMI,           0 ), /* De-assert SPM wakeup IRQ */
/* 0xb  */  EVENT( EVENT_PLL_LOCK ),            /* Wait for Q6 PLL lock */
  
  /* index 36 */
/* 0x90 */  PWR_CTLX( QDSP6_PLL_OUTPUT,    0 ), /* Enable Q6 PLL outputs */
/* 0x4b */  EVENT( EVENT_SMMU_PWR ),            /* Wait for SMMU powered up */
/* 0x20 */  PWR_CTLX( QDSP6_CLOCK,         0 ), /* Q6 Clock on */
/* 0xF  */  END                                 /* End of command sequence */
};

/* Mode configurations objects. */
static spm_hal_bsp_mode_t g_cpuModes[] =
{
  { 
    {SPM_ARRAY(g_spmCmdSeqAPCRPLLOn)}, SPM_MODE_APCR_PLL_ON,
    (SYNC_EVENTS | SPM_HAL_ISAR_SET)
  },
  {
    {SPM_ARRAY(g_spmCmdSeqPLLLpm)}, SPM_MODE_PWRC_BHS,
    (SYNC_EVENTS | SPM_HAL_ISAR_SET)
  },
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

