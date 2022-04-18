/*==============================================================================
  FILE:         spm_config.c

  OVERVIEW:     This file contains target specific data/configuration for SPM
                instances.
 
  NOTE:         Based on HPG_QDSP6SS_v62_1.2+ (3.01 - September 29, 2015)
  
  DEPENDENCIES: None
                
                Copyright (c) 2015-2016 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/spm/src/asic/8998/spm_config.c#1 $
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
  PWR_CTLX( QDSP6_CLOCK,         0 ), /* QDSP6 Clock Off */
  PWR_CTLX( QDSP6_CLAMP,         0 ), /* QDSP6 Assert Clamp */
  PWR_CTLX( QDSP6_RETAIN_SAVE,   0 ), /* Assert QDSP6 retain save */
  PWR_CTLX( QDSP6_RETAIN_SAVE,   0 ), /* Deassert QDSP6 retain save */

  /* index 4 */
  PWR_CTLX( QDSP6_COPROC_BHS_OFF,0 ), /* Coproc BHS off - HVX is PC by HW */
  PWR_CTLX( QDSP6_CLAMP_WL,      0 ), /* QDSP6 Assert Clamp WL */
  PWR_CTLX( QDSP6_MEM_RET_SLEEP, 0 ), /* Retention memory sleep */
  DLY( DLY_1 ),                       /* Delay for in-rush current */

  /* index 8 */
  PWR_CTLX( QDSP6_QMC_MEM_CLAMP, 0 ), /* QDSP6 QMC Mem Clamp */
  PWR_CTLX( QDSP6_LDO_BYPASS,    0 ), /* Force LDO Bypass Off */
  PWR_CTLX( QDSP6_BHS,           1 ), /* Force BHS Off */
  PWR_CTLX( QDSP6_LDO_OFF,       0 ), /* Force LDO Off */

  /* index 12 */
  SLEEP( NO_RPM_HS ),                 /* Init Sleep to NO RPM HS */
  PWR_CTLX( QDSP6_RESET,         0 ), /* Assert Reset */
  PWR_CTLX( QDSP6_LDO_OFF,       0 ), /* Deassert LDO Off */
  PWR_CTLX( QDSP6_BHS,           0 ), /* Deassert BHS Off */

  /* index 16 */
  EVENT( EVENT_QDSP6_PWR ),           /* Wait for BHS/LDO ready */
  PWR_CTLX( QDSP6_LDO_BYPASS,    0 ), /* Deassert LDO Bypass Off */
  PWR_CTLX( QDSP6_QMC_MEM_CLAMP, 0 ), /* Deassert QMC Mem Clamp */ 
  PWR_CTLX( QDSP6_MEM_RET_SLEEP, 1 ), /* Retention memory sleep */

  /* index 20 */
  PWR_CTLX( QDSP6_CLAMP_WL,      0 ), /* Deassert QDSP6 Clamp WL */
  PWR_CTLX( QDSP6_COPROC_BHS_OFF,1 ), /* Coproc BHS on - HVX is PC by HW */
  PWR_CTLX( QDSP6_RETAIN_RESTORE,0 ), /* Assert QDSP6 retain restore */
  PWR_CTLX( QDSP6_RETAIN_RESTORE,0 ), /* Deassert QDSP6 retain restore */

  /* index 24 */
  PWR_CTLX( QDSP6_CLAMP,         0 ), /* Deassert QDSP6 Clamp */
  PWR_CTLX( QDSP6_RESET,         0 ), /* Deassert Reset */
  PWR_CTLX( QDSP6_PMI,           0 ), /* Assert Power Manager Interrupt (PMI) */
  PWR_CTLX( QDSP6_PMI,           0 ), /* Deassert PMI */

  /* index 28 */
  PWR_CTLX( QDSP6_CLOCK,         0 ), /* Deassert QDSP6 Clock Off */
  END                                 /* End of Program */
};

/* SPM command sequence for APCR or Full PC PLL in low power mode. */
static uint8 g_spmCmdSeqFullPcOrApcr[] =
{
  /* index 0 */
  PWR_CTLX( QDSP6_CLOCK,         1 ), /* QDSP6 Clock Off */
  EVENT( EVENT_QDSP6_CLK ),           /* Wait for clock off event */
  PWR_CTLX( QDSP6_CLAMP,         0 ), /* Assert clamp */
  PWR_CTLX( QDSP6_RETAIN_SAVE,   0 ), /* Assert QDSP6 retain save*/

  /* index 4 */
  PWR_CTLX( QDSP6_RETAIN_SAVE,   0 ), /* Deassert QDSP6 retain save */
  PWR_CTLX( QDSP6_COPROC_BHS_OFF,0 ), /* Coproc BHS off - HVX is PC by HW */
  PWR_CTLX( QDSP6_CLAMP_WL,      0 ), /* Assert QDSP6 Clamp WL */
  PWR_CTLX( QDSP6_MEM_RET_SLEEP, 0 ), /* Assert ret memory sleep */

  /* index 8 */
  PWR_CTLX( QDSP6_MEM_SLEEP,     1 ), /* Assert non ret memory sleep */
  PWR_CTLX( QDSP6_QMC_MEM_CLAMP, 0 ), /* Assert Q6 QMC memory clamp */
  PWR_CTLX( QDSP6_LDO_BYPASS,    0 ), /* LDO bypass off */
  PWR_CTLX( QDSP6_BHS,           0 ), /* Assert BHS off */

  /* index 12 */
  PWR_CTLX( QDSP6_LDO_OFF,       0 ), /* Assert LDO off */
  PWR_CTLX( QDSP6_LDO_BG,        0 ), /* LDO Bandgap off */
  PWR_CTLX( QDSP6_SMMU_PD_VOTE,  0 ), /* Vote off SMMU GDHS */
  PWR_CTLX( QDSP6_PLL_OUTPUT,    0 ), /* Disable Q6 PLL outputs */
  
  /* index 16 */
  PWR_CTLX( QDSP6_PLL_OPMODE0,   0 ), /* Standby Q6 PLL */
  PWR_CTLX( QDSP6_PLL_RESET,     0 ), /* Reset Q6 PLL */
  SLEEP( NO_RPM_HS),                  /* Sleep w/o RPM handshake */
  PWR_CTLX( QDSP6_RESET,         0 ), /* Assert QDSP6 reset */
  
  /* index 20 */
  PWR_CTLX( QDSP6_PLL_RESET,     2 ), /* Release reset Q6 PLL */
  PWR_CTLX( QDSP6_PLL_OPMODE0,   0 ), /* Release standby Q6 PLL */
  PWR_CTLX( QDSP6_SMMU_PD_VOTE,  0 ), /* Vote on SMMU GDHS */
  PWR_CTLX( QDSP6_LDO_BG,        2 ), /* LDO Bandgap on */
  
  /* index 24 */
  PWR_CTLX( QDSP6_LDO_OFF,       0 ), /* Deassert LDO force off */
  PWR_CTLX( QDSP6_BHS,           0 ), /* Deassert BHS off */
  EVENT( EVENT_QDSP6_PWR ),           /* Wait for BHS/LDO ready */
  PWR_CTLX( QDSP6_LDO_BYPASS,    0 ), /* Deassert LDO bypass force off */
  
  /* index 28 */
  PWR_CTLX( QDSP6_QMC_MEM_CLAMP, 0 ), /* Deassert Q6 QMC memory clamp */
  PWR_CTLX( QDSP6_MEM_SLEEP,     1 ), /* Deassert Q6 memory sleep + pipeline delay to assert L2 */
  PWR_CTLX( QDSP6_MEM_RET_SLEEP, 1 ), /* Deassert ret memory sleep */
  PWR_CTLX( QDSP6_CLAMP_WL,      0 ), /* Assert Q6 clamp_wl */
  
  /* index 32 */
  PWR_CTLX( QDSP6_COPROC_BHS_OFF,1 ), /* Coproc BHS on - HVX is PC by HW */
  PWR_CTLX( QDSP6_RETAIN_RESTORE,0 ), /* Assert Q6 restore */
  PWR_CTLX( QDSP6_RETAIN_RESTORE,0 ), /* De-assert Q6 restore */
  PWR_CTLX( QDSP6_CLAMP,         0 ), /* Deassert Q6 clamp */
  
  /* index 36 */
  PWR_CTLX( QDSP6_RESET,         0 ), /* Deassert Q6 reset */
  PWR_CTLX( QDSP6_PMI,           0 ), /* Assert SPM wakeup IRQ */
  PWR_CTLX( QDSP6_PMI,           0 ), /* De-assert SPM wakeup IRQ */
  EVENT( EVENT_PLL_LOCK ),            /* Wait for Q6 PLL lock */
  
  /* index 40 */
  PWR_CTLX( QDSP6_PLL_OUTPUT,    0 ), /* Enable Q6 PLL outputs */
  EVENT( EVENT_SMMU_PWR ),            /* Wait for SMMU powered up */
  PWR_CTLX( QDSP6_CLOCK,         0 ), /* Q6 Clock on */
  END                                 /* End of command sequence */
};

/* Mode configurations objects. */
static spm_hal_bsp_mode_t g_cpuModes[] =
{
  { 
    {SPM_ARRAY(g_spmCmdSeqAPCRPLLOn)}, SPM_MODE_APCR_PLL_ON,
    (SYNC_EVENTS | SPM_HAL_ISAR_SET)
  },
  {
    {SPM_ARRAY(g_spmCmdSeqFullPcOrApcr)}, SPM_MODE_APCR_PLL_LPM,
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

