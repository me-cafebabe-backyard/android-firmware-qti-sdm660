/*==============================================================================
  FILE:         q6_lpm_config_v60.c

  OVERVIEW:     This file implements the APIs from q6_lpm_config header file
                on ADSP/LPASS subsystems for Q6v60 version. It may be 
                shared for targets with same Q6 version.

  NOTE:         This file depends on how Q6 core is integrated within a 
                subystem. So LPASS/ADSP implementation may vary from MPSS.

  DEPENDENCIES: None

                Copyright (c) 2014-2017 QUALCOMM Technologies Incorporated.
                All Rights Reserved.
                Qualcomm Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/sleep2.0/src/target/q6_lpm_config_v60.c#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/

#include "DALStdDef.h"
#include "spm.h"
#include "q6_lpm_config.h"
#include "sleep_hwio.h"
#include "HALsleep_hwio.h"
#include "CoreVerify.h"
#include "sleep_target.h"
#include "q6_lpm_config.h"

/*==============================================================================
                           EXTERNAL VARIABLES
 =============================================================================*/
/* g_sleepTargetConfig stores target specific config */
extern sleep_target_config g_sleepTargetConfig;

/*==============================================================================
 *                             GLOBAL FUNCTIONS
 *============================================================================*/
/**
 * q6LPMConfig_setupBase
 */
void q6LPMConfig_setupBase(void)
{
  /* Configure Q6SS registers that are invariant across all 
   * cpu_vdd low-power modes */
  SLEEP_HWIO_OUTF( WAKEUP_CTL, L2VIC_WAKE_EN, 0x01);

  SLEEP_HWIO_OUT( SPMCTL_EN_CLAMP, 0x3 );

  SLEEP_HWIO_OUT( SPMCTL_EN_CLK, 0x3FF );

  SLEEP_HWIO_OUT( SPMCTL_EN_MEM_CTL,
            SLEEP_HWIO_FVAL( SPMCTL_EN_MEM_CTL, CLAMP_QMC_MEM,  0x1 ) |
            SLEEP_HWIO_FVAL( SPMCTL_EN_MEM_CTL, CLAMP_WL,       0x1 ) |
            SLEEP_HWIO_FVAL( SPMCTL_EN_MEM_CTL, MEM_PERIPH,     0x1 ) |
            SLEEP_HWIO_FVAL( SPMCTL_EN_MEM_CTL, ARR_STBY,       0x0 ));

  SLEEP_HWIO_OUT( SPMCTL_EN_BHS, 0x3 ); 

  SLEEP_HWIO_OUT( SPMCTL_EN_LDO,
            SLEEP_HWIO_FVAL( SPMCTL_EN_LDO, BG_OFF,       0x1 ) |
            SLEEP_HWIO_FVAL( SPMCTL_EN_LDO, FORCEOFF,     0x1 ) |
            SLEEP_HWIO_FVAL( SPMCTL_EN_LDO, BYPASS_OPEN,  0x1 ));

     SLEEP_HWIO_OUT( SPMCTL_EN_EXT,
          SLEEP_HWIO_FVAL( SPMCTL_EN_EXT, SMMU_PD_VOTE, 0x1 ) |
          SLEEP_HWIO_FVAL( SPMCTL_EN_EXT, PLL_VOTE,     0x1 ));


  /* Due to HW bug (HW CR QCTDD03560301), SparkPLL_14LPP PLL fails to lock after FREEZE/UNFREEZE operation for some 
   * corner cases, CDSP Q6 PLL cannot be configured for FREEZE MODE. It should be turned off during long APCR/full PC.
   *
   * Configure CDSP Q6 PLL for OFF MODE.
   * There are two types of modes
   *   1) Don't vote for Q6 PLL off: "clk_gate" and "apcr". These modes will 
   *      not have spm commands for voting pll off.
   *   2) Vote for Q6 PLL off : "apcr_pll_lpm" and "pc_l2_noret". These modes
   *      will have spm commands to vote for pll off.
   *
   * By configuring Q6 PLL related registers for OFF at init time, we 
   * eliminate the need to perform PLL configuration as part of any mode's
   * enter function. */
  SLEEP_HWIO_OUT( SPMCTL_EN_PLL, 
	    SLEEP_HWIO_FVAL( SPMCTL_EN_PLL, PLL_FREEZE, 0x0 ) |
   	    SLEEP_HWIO_FVAL( SPMCTL_EN_PLL, PLL_VOTE,   0x1 ) |
            SLEEP_HWIO_FVAL( SPMCTL_EN_PLL, PLL_OUTDIS, 0x1 ) |
            SLEEP_HWIO_FVAL( SPMCTL_EN_PLL, PLL_BYPASS, 0x1 ) |
            SLEEP_HWIO_FVAL( SPMCTL_EN_PLL, PLL_RESET,  0x1 ) );

  SLEEP_HWIO_OUT( SLPC_CFG, 
            SLEEP_HWIO_FVAL( SLPC_CFG, MEM_PU_PERI_STAGGER, 0x1 ) |
            SLEEP_HWIO_FVAL( SLPC_CFG, MEM_PD_PERI_STAGGER, 0x0 ) |
            SLEEP_HWIO_FVAL( SLPC_CFG, MEM_PU_ARRY_STAGGER, 0x1 ) |
            SLEEP_HWIO_FVAL( SLPC_CFG, MEM_PD_ARRY_STAGGER, 0x0 ) |
            SLEEP_HWIO_FVAL( SLPC_CFG, WAKEUP_IN_EN,        0x0 ) |
            SLEEP_HWIO_FVAL( SLPC_CFG, CLK_GATING_MODE,     0x0 ) |
            SLEEP_HWIO_FVAL( SLPC_CFG, SAW_DBG,             0x0 ) );

  /* Wait for SMMU powerup */
  SLEEP_HWIO_OUT( SPM_EVENT_CTL, 
            SLEEP_HWIO_FVAL( SPM_EVENT_CTL, PLL_FINE_OVRRD,    0x1 ) |
    	    SLEEP_HWIO_FVAL( SPM_EVENT_CTL, SMMU_STATUS_OVRRD, 0x0 ) |
            SLEEP_HWIO_FVAL( SPM_EVENT_CTL, EXT_PLL_OVRRD,     0x1 ) );
}

/**
 * q6LPMConfig_setupModeConfig
 *
 * Based on QDSP6v56 HPG
 *
 * Reg[Field]                       PC     APCR     APCRCached     ClockGating
 *
 * SLPC_CFG[WAKEUP_IN_EN]           0        1          1              0
 *   Enables QDSP6_wakeup_in
 *   handshaking signal.
 *
 * SLPC_CFG[CLK_GATING_MODE]        0        0          0              1
 *   Bit to indicate clock 
 *   gating only on allwait.
 * 
 * STATERET[WAKE_IRQ]               0        1          0              0
 *   If 1, PMI interrupt is
 *   triggered from spm exit
 *   sequence, else not.
 * 
 * STATERET[SAVE|RESTORE]           0        1          1              0
 *   If 1, Q6 state save/restore   
 *   is needed around core off,   
 *   else not.
 * 
 * SPMCTL_EN_ARES                  0xFFF    0xE7F      0xE7F           0
 *   Async reset of various
 *   subcomponents indicated
 *   by each bit of this reg.
 */
void q6LPMConfig_setupModeConfig( spm_low_power_mode_type coreMode, 
                                  boolean                 flag )
{
  uint32 wakeup_in_en;
  uint32 wake_irq;
  uint32 save_restore;
  uint32 en_ares;
  uint32 spm_config_lpm;

  switch( coreMode )
  {
    case SPM_MODE_APCR_PLL_ON:
    case SPM_MODE_APCR_PLL_LPM:
    {
      wakeup_in_en    = 0x1;
      wake_irq        = (flag == TRUE) ? 0x1 : 0x0;
      save_restore    = 0x1;
      en_ares         = 0xE7F;
      spm_config_lpm  = 0x1; /* Configure SPM low-power mode */
      break;
    }

    case SPM_MODE_PWRC_BHS:
    {
      wakeup_in_en    = 0x0;
      wake_irq        = 0x0;
      save_restore    = 0x0;
      en_ares         = 0xFFF;
      spm_config_lpm  = 0x1; /* Configure SPM low-power mode */
      break;
    }

    case SPM_MODE_CLK_GATE:
    {
      /* Clock gating bit overrides all other settings, so just set this one bit.
       * This setting will be in effect until explicitly unset */
      SLEEP_HWIO_OUTF(SLPC_CFG, CLK_GATING_MODE, (flag == TRUE) ? 0x1 : 0x0);
      return;
    }

    default:
    {
      CORE_VERIFY(0);
      break;
    }
  }
  
  SLEEP_HWIO_OUTF( SLPC_CFG, WAKEUP_IN_EN, wakeup_in_en );

  SLEEP_HWIO_OUT( SPMCTL_EN_STATERET,
            SLEEP_HWIO_FVAL( SPMCTL_EN_STATERET, WAKE_IRQ, wake_irq     ) |
            SLEEP_HWIO_FVAL( SPMCTL_EN_STATERET, RESTORE,  save_restore ) |
            SLEEP_HWIO_FVAL( SPMCTL_EN_STATERET, SAVE,     save_restore ) );

  SLEEP_HWIO_OUT( SPMCTL_EN_ARES, en_ares );

  /* Configure SPM if required by lprm */
  if(0 != spm_config_lpm)
  { 
    /* SPM Driver does not support efficient storage of sequences when
     * multiple low-power mode employ the same spm sequence commands.
     * SPM Long sequence supports both PC and APCR_PLL_LPM modes.  */
    if(coreMode == SPM_MODE_APCR_PLL_LPM)
    {
      coreMode = SPM_MODE_PWRC_BHS;
    }

    sleepTarget_setSpmLowPowerMode(coreMode);
  } 

  return;
}

/*
 * q6LPMConfig_setupL2Config
 */
void q6LPMConfig_setupL2Config(mem_state state)
{
  uint32 memRetValue;
  uint32 l2data = SLEEP_HWIO_INF(SPMCTL_EN_MEM_RET, L2DATA);

  if(MEM_RET == state)
  {
    /* Setup for cache related logic to be retained */ 
    l2data &= ~g_sleepTargetConfig.l2_mask;

    memRetValue = SLEEP_HWIO_FVAL(SPMCTL_EN_MEM_RET, JU,      0x0) |
                  SLEEP_HWIO_FVAL(SPMCTL_EN_MEM_RET, ETB,     0x0) |
                  SLEEP_HWIO_FVAL(SPMCTL_EN_MEM_RET, L1IU,    0x0) |
                  SLEEP_HWIO_FVAL(SPMCTL_EN_MEM_RET, L1DU,    0x0) |
                  SLEEP_HWIO_FVAL(SPMCTL_EN_MEM_RET, L2PLRU,  0x0) |
                  SLEEP_HWIO_FVAL(SPMCTL_EN_MEM_RET, L2TAG,   0x0) |
                  SLEEP_HWIO_FVAL(SPMCTL_EN_MEM_RET, L2DATA,  l2data);
  }
  else
  {
    /* Setup for cache related logic to be turned off/reset */
    l2data |= g_sleepTargetConfig.l2_mask;

    memRetValue = 
#ifdef MEM_INRUSH_WORKAROUND
                  SLEEP_HWIO_FVAL(SPMCTL_EN_MEM_RET, JU,      0x0)   |
#else
                  SLEEP_HWIO_FVAL(SPMCTL_EN_MEM_RET, JU,      0x7)   |
#endif
                  SLEEP_HWIO_FVAL(SPMCTL_EN_MEM_RET, ETB,     0x0)   |
                  SLEEP_HWIO_FVAL(SPMCTL_EN_MEM_RET, L1IU,    0x3)   |
                  SLEEP_HWIO_FVAL(SPMCTL_EN_MEM_RET, L1DU,    0x3)   |
                  SLEEP_HWIO_FVAL(SPMCTL_EN_MEM_RET, L2PLRU,  0x1)   |
                  SLEEP_HWIO_FVAL(SPMCTL_EN_MEM_RET, L2TAG,   0xFF)  |
                  SLEEP_HWIO_FVAL(SPMCTL_EN_MEM_RET, L2DATA,  l2data);
  }
 
  SLEEP_HWIO_OUT(SPMCTL_EN_MEM_RET, memRetValue);
  
  return;
}

