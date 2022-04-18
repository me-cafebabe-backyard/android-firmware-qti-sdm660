/**
==============================================================================

FILE:         ClockCommon.c

DESCRIPTION:  Common functions for Clock library.

==============================================================================

                             Edit History


when      who           what, where, why
--------  ------------  ------------------------------------------------------
08/11/15  jcuddihy      Initial SDM660 revision, branched from MSM8996.

==============================================================================
            Copyright (c) 2015 QUALCOMM Technologies Incorporated.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
==============================================================================
*/


/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include "ClockBoot.h"
#include "ClockHWIO.h"
#include "busywait.h"
#include "ClockCommon.h"
#include "ClockBSP.h"

/*=========================================================================
      Macro Definitions
==========================================================================*/

/* ---------- */
/*    MSMs    */
/* ---------- */
#if defined HWIO_GCC_GPLL0_MODE_ADDR
  #define HWIO_PLL_MODE_OFFS                 (HWIO_ADDR(GCC_GPLL0_MODE) - HWIO_ADDR(GCC_GPLL0_MODE))
  #define HWIO_PLL_L_VAL_OFFS                (HWIO_ADDR(GCC_GPLL0_L_VAL) - HWIO_ADDR(GCC_GPLL0_MODE))
  #define HWIO_PLL_M_VAL_OFFS                (HWIO_ADDR(GCC_GPLL0_M_VAL) - HWIO_ADDR(GCC_GPLL0_MODE))
  #define HWIO_PLL_N_VAL_OFFS                (HWIO_ADDR(GCC_GPLL0_N_VAL) - HWIO_ADDR(GCC_GPLL0_MODE))
  #define HWIO_PLL_ALPHA_VAL_OFFS            (HWIO_ADDR(GCC_GPLL0_ALPHA_VAL) - HWIO_ADDR(GCC_GPLL0_MODE))
  #define HWIO_PLL_ALPHA_VAL_U_OFFS          (HWIO_ADDR(GCC_GPLL0_ALPHA_VAL_U) - HWIO_ADDR(GCC_GPLL0_MODE))
  #define HWIO_PLL_USER_CTL_OFFS             (HWIO_ADDR(GCC_GPLL0_USER_CTL) - HWIO_ADDR(GCC_GPLL0_MODE))
  #define HWIO_PLL_CONFIG_CTL_OFFS           (HWIO_ADDR(GCC_GPLL0_CONFIG_CTL) - HWIO_ADDR(GCC_GPLL0_MODE))
  #define HWIO_PLL_TEST_CTL_OFFS             (HWIO_ADDR(GCC_GPLL0_TEST_CTL) - HWIO_ADDR(GCC_GPLL0_MODE))

  #define CLOCK_PLL_MODE_ACTIVE  \
    (HWIO_FMSK(GCC_GPLL0_MODE, PLL_OUTCTRL)  | \
     HWIO_FMSK(GCC_GPLL0_MODE, PLL_BYPASSNL) | \
     HWIO_FMSK(GCC_GPLL0_MODE, PLL_RESET_N))
   
  /*
   * Definitions for configuring the PLL in FSM Mode
   */
  #define CLOCK_PLL_BIAS_COUNT_VAL  (0x6 << HWIO_SHFT(GCC_GPLL0_MODE, PLL_BIAS_COUNT))
  #define CLOCK_PLL_LOCK_COUNT_VAL  (0x0 << HWIO_SHFT(GCC_GPLL0_MODE, PLL_LOCK_COUNT))

/* ---------- */
/*   Server   */
/* ---------- */
#elif defined HWIO_GCCSN_SYS_PLL0_MODE_ADDR

  #define HWIO_PLL_MODE_OFFS                 (HWIO_ADDR(GCCSN_SYS_PLL0_MODE) - HWIO_ADDR(GCCSN_SYS_PLL0_MODE))
  #define HWIO_PLL_L_VAL_OFFS                (HWIO_ADDR(GCCSN_SYS_PLL0_L_VAL) - HWIO_ADDR(GCCSN_SYS_PLL0_MODE))
  #define HWIO_PLL_M_VAL_OFFS                (HWIO_ADDR(GCCSN_SYS_PLL0_M_VAL) - HWIO_ADDR(GCCSN_SYS_PLL0_MODE))
  #define HWIO_PLL_N_VAL_OFFS                (HWIO_ADDR(GCCSN_SYS_PLL0_N_VAL) - HWIO_ADDR(GCCSN_SYS_PLL0_MODE))
  #define HWIO_PLL_ALPHA_VAL_OFFS            (HWIO_ADDR(GCCSN_SYS_PLL0_ALPHA_VAL) - HWIO_ADDR(GCCSN_SYS_PLL0_MODE))
  #define HWIO_PLL_ALPHA_VAL_U_OFFS          (HWIO_ADDR(GCCSN_SYS_PLL0_ALPHA_VAL_U) - HWIO_ADDR(GCCSN_SYS_PLL0_MODE))
  #define HWIO_PLL_USER_CTL_OFFS             (HWIO_ADDR(GCCSN_SYS_PLL0_USER_CTL) - HWIO_ADDR(GCCSN_SYS_PLL0_MODE))
  #define HWIO_PLL_CONFIG_CTL_OFFS           (HWIO_ADDR(GCCSN_SYS_PLL0_CONFIG_CTL) - HWIO_ADDR(GCCSN_SYS_PLL0_MODE))
  #define HWIO_PLL_TEST_CTL_OFFS             (HWIO_ADDR(GCCSN_SYS_PLL0_TEST_CTL) - HWIO_ADDR(GCCSN_SYS_PLL0_MODE))

  #define CLOCK_PLL_MODE_ACTIVE  \
    (HWIO_FMSK(GCCSN_SYS_PLL0_MODE, PLL_OUTCTRL)  | \
     HWIO_FMSK(GCCSN_SYS_PLL0_MODE, PLL_BYPASSNL) | \
     HWIO_FMSK(GCCSN_SYS_PLL0_MODE, PLL_RESET_N))

  /*
   * Definitions for configuring the PLL in FSM Mode
   */
  #define CLOCK_PLL_BIAS_COUNT_VAL  (0x6 << HWIO_SHFT(GCCSN_SYS_PLL0_MODE, PLL_BIAS_COUNT))
  #define CLOCK_PLL_LOCK_COUNT_VAL  (0x0 << HWIO_SHFT(GCCSN_SYS_PLL0_MODE, PLL_LOCK_COUNT))

  /*
   * Map MSM register names to the corresponding server names
   */
  #define GCC_GPLL0_MODE                       GCCSN_SYS_PLL0_MODE
  #define GCC_GPLL0_USER_CTL                   GCCSN_SYS_PLL0_USER_CTL
  #define GCC_SDCC2_APPS_CMD_RCGR              GCCSN_SDCC2_APPS_CMD_RCGR
  #define GCC_SDCC2_APPS_CFG_RCGR              GCCSN_SDCC2_APPS_CFG_RCGR
  #define GCC_SDCC2_APPS_M                     GCCSN_SDCC2_APPS_M
  #define GCC_SDCC2_APPS_N                     GCCSN_SDCC2_APPS_N
  #define GCC_SDCC2_APPS_D                     GCCSN_SDCC2_APPS_D

#endif


/*
 * CLOCK_PLL_INIT_TIME_US
 *
 * Init time in microseconds after de-asserting PLL reset (normal mode).
 */
#define CLOCK_PLL_INIT_TIME_US 5

/*
 * CLOCK_PLL_WARMUP_TIME_US
 *
 * Warm-up time in microseconds after turning on the PLL.
 */
#define CLOCK_PLL_WARMUP_TIME_US 50

/*
 * NOT_2D / NOT_N_MINUS_M
 *
 * Macros to return the inverted value of the 2D field or (N - M)
 * in a type 1 mux structure.  Used to prepare the value for writing
 * to the hardware register field.
 */
#define NOT_2D(mux)         (~(mux)->n2D)
#define NOT_N_MINUS_M(mux)  (~((mux)->nN - (mux)->nM))

/*
 * HALF_DIVIDER
 *
 * Macro to return the normalized half divider for a given mux structure.
 * NOTE: Expecting (2 * divider) value as input.
 */
#define HALF_DIVIDER(mux)  ((mux)->nDiv2x ? (((mux)->nDiv2x) - 1) : 0)

/*
 * PLL lock timeout (2x max locking time).
 */
#define CLOCK_PLL_LOCK_TIMEOUT_US 200



/* Definitions for generalizing clock configuration */
#define CLOCK_CMD_CFG_UPDATE_FMSK   HWIO_FMSK(GCC_SDCC2_APPS_CMD_RCGR, UPDATE)

#define CLOCK_CFG_REG_OFFSET        (HWIO_ADDR(GCC_SDCC2_APPS_CFG_RCGR)-HWIO_ADDR(GCC_SDCC2_APPS_CMD_RCGR))
#define CLOCK_CFG_RCGR_SRC_SEL_FMSK  HWIO_FMSK(GCC_SDCC2_APPS_CFG_RCGR, SRC_SEL)
#define CLOCK_CFG_RCGR_SRC_SEL_SHFT  HWIO_SHFT(GCC_SDCC2_APPS_CFG_RCGR, SRC_SEL)
#define CLOCK_CFG_RCGR_SRC_DIV_FMSK  HWIO_FMSK(GCC_SDCC2_APPS_CFG_RCGR, SRC_DIV)
#define CLOCK_CFG_RCGR_SRC_DIV_SHFT  HWIO_SHFT(GCC_SDCC2_APPS_CFG_RCGR, SRC_DIV)

#define CLOCK_CFG_RCGR_MODE_FMSK     HWIO_FMSK(GCC_SDCC2_APPS_CFG_RCGR, MODE)
#define CLOCK_CFG_RCGR_MODE_SHFT     HWIO_SHFT(GCC_SDCC2_APPS_CFG_RCGR, MODE)
#define CLOCK_CFG_RCGR_MODE_DUAL_EDGE_VAL  0x2
#define CLOCK_CFG_RCGR_MODE_BYPASS_VAL     0x0

#define CLOCK_M_REG_OFFSET         (HWIO_ADDR(GCC_SDCC2_APPS_M)-HWIO_ADDR(GCC_SDCC2_APPS_CMD_RCGR))
#define CLOCK_N_REG_OFFSET         (HWIO_ADDR(GCC_SDCC2_APPS_N)-HWIO_ADDR(GCC_SDCC2_APPS_CMD_RCGR))
#define CLOCK_D_REG_OFFSET         (HWIO_ADDR(GCC_SDCC2_APPS_D)-HWIO_ADDR(GCC_SDCC2_APPS_CMD_RCGR))



/*=========================================================================
      Function Prototypes
==========================================================================*/
extern boolean Clock_SourceMapToMux(const ClockConfigMuxType *pConfig, uint32 *nMuxValue );
boolean Clock_ConfigurePLL(const ClockConfigPLLType *pConfig);


/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/ 

/* ============================================================================
**  Function : Clock_EnablePLL
** ============================================================================
*/
/*!
    Configure and enable a PLL.  If it is voteable, it will be set for FSM mode
    and voted for using the vote register.

    @param pConfig -  [IN] PLL configuration structure
    @return
    TRUE -- Initialization was successful.
    FALSE -- Initialization failed.

    @dependencies
    None.

    @sa None
*/
boolean Clock_EnablePLL(const ClockConfigPLLType *pConfig)
{
  uintnt nModeAddr;
  uint32 nModeVal, nTimeout = 0;

  nModeAddr = pConfig->nPLLModeAddr;
  nModeVal  = inp32(nModeAddr);

  if ( ((nModeVal & CLOCK_PLL_MODE_ACTIVE) == CLOCK_PLL_MODE_ACTIVE) ||
       (nModeVal & HWIO_FMSK(GCC_GPLL0_MODE, PLL_VOTE_FSM_ENA)) )
  {
    /*
     * The PLL is already running, so vote for the resource but don't configure it.
     */
    if (pConfig->nVoteAddr != 0)
  {
      outp32(pConfig->nVoteAddr, inp32(pConfig->nVoteAddr) | pConfig->nVoteMask);

      /*
       * Wait for the PLL to go active.
       */
      nTimeout = 0;
      while ((inp32(nModeAddr) & HWIO_FMSK(GCC_GPLL0_MODE, PLL_ACTIVE_FLAG)) == 0)
    {
        if (nTimeout++ >= CLOCK_PLL_LOCK_TIMEOUT_US)
      {
          return FALSE;
      }
        busywait(1);
    }
  }

     return TRUE;
  }

  /*
   * Configure the PLL.
   */
    if ( !Clock_ConfigurePLL(pConfig) ) return FALSE;
  nModeVal = inp32(nModeAddr);

  /*
   * Enable the PLL.
   */
  if (pConfig->nVoteAddr != 0)
  {
    outp32(pConfig->nVoteAddr, inp32(pConfig->nVoteAddr) | pConfig->nVoteMask);

    /*
     * Wait for the PLL to go active.
     */
    while ((inp32(nModeAddr) & HWIO_FMSK(GCC_GPLL0_MODE, PLL_ACTIVE_FLAG)) == 0)
    {
      if ( nTimeout++ >= CLOCK_PLL_LOCK_TIMEOUT_US )
      {
        return FALSE;
      }

      busywait(1);
    }
  }
  else
  {
    nModeVal |= HWIO_FMSK(GCC_GPLL0_MODE, PLL_BYPASSNL);
    outp32(nModeAddr, nModeVal);
    busywait(CLOCK_PLL_INIT_TIME_US);

    nModeVal |= HWIO_FMSK(GCC_GPLL0_MODE, PLL_RESET_N);
    outp32(nModeAddr, nModeVal);
    busywait(CLOCK_PLL_WARMUP_TIME_US);

    while ((inp32(nModeAddr) & HWIO_FMSK(GCC_GPLL0_MODE, PLL_LOCK_DET)) == 0)
    {
      if ( nTimeout++ >= CLOCK_PLL_LOCK_TIMEOUT_US )
      {
        return FALSE;
      }

      busywait(1);
    }

    nModeVal |= HWIO_FMSK(GCC_GPLL0_MODE, PLL_OUTCTRL);
    outp32(nModeAddr, nModeVal);
  }

  return TRUE;

} /* END Clock_EnablePLL */


/* ============================================================================
**  Function : Clock_DisablePLL
** ============================================================================
*/
/*!
    Disable a PLL.

    @param pConfig -  [IN] PLL configuration structure
    @return
    TRUE -- The PLL was succesfully disabled.
    FALSE -- Disable failed.

    @dependencies
    None.

    @sa None
*/
boolean Clock_DisablePLL(const ClockConfigPLLType *pConfig)
{
  uintnt nModeAddr;
  uint32 nModeVal, nTimeout = 0;

  nModeAddr = pConfig->nPLLModeAddr;
  nModeVal  = inp32(nModeAddr);

  if (nModeVal & HWIO_FMSK(GCC_GPLL0_MODE, PLL_VOTE_FSM_ENA)) 
  {
    if(pConfig->nVoteAddr != 0) 
    {
      outp32(pConfig->nVoteAddr, inp32(pConfig->nVoteAddr) & ~pConfig->nVoteMask);

      while (inp32(nModeAddr) & HWIO_FMSK(GCC_GPLL0_MODE, PLL_ACTIVE_FLAG))
      {
        if (nTimeout++ >= CLOCK_PLL_LOCK_TIMEOUT_US)
        {
    return FALSE;
  }
    busywait(1);
  }

  return TRUE;
}
    /* An FSM enabled PLL requires a VoteAddr */
    return FALSE;
  }

  /* This is a non-shared PLL, so just turn it off */
  outp32(nModeAddr, 0);
  return TRUE;

} /* END Clock_DisablePLL */

/* =========================================================================
**  Function : Clock_ConfigurePLL
** =========================================================================*/
/**
  Configures a PLL.

  @param *pConfig [in] -- PLL configuration

*/
boolean Clock_ConfigurePLL(const ClockConfigPLLType *pConfig)
{
  uintnt nModeAddr;
  uint32 nUserVal, nModeVal;

  nModeAddr = pConfig->nPLLModeAddr;
  nModeVal = inp32(nModeAddr);

  if ( ((nModeVal & CLOCK_PLL_MODE_ACTIVE) == CLOCK_PLL_MODE_ACTIVE) ||
       (nModeVal & HWIO_FMSK(GCC_GPLL0_MODE, PLL_ACTIVE_FLAG)) ) /*HWIO_FMSK(GCC_GPLL0_MODE, PLL_LOCK_DET), this is changed to overcome virtio issue on SL*/
  {
    /* This clock has already been configured */
    return FALSE;
  }

  /*
   * Program L, Alpha.
   */
  outp32(nModeAddr + HWIO_OFFS(PLL_L_VAL), pConfig->nL);
  if( pConfig->nAlpha )
  {
    outp32(nModeAddr + HWIO_OFFS(PLL_ALPHA_VAL), (uint32)pConfig->nAlpha);
    outp32(nModeAddr + HWIO_OFFS(PLL_ALPHA_VAL_U), (uint32)(pConfig->nAlpha >> 32));
  }
  
  /*
   * Get the CONFIG value and clear out fields we will configure.
   */
  nUserVal = inp32(nModeAddr + HWIO_OFFS(PLL_USER_CTL));
  nUserVal &= ~(HWIO_FMSK(GCC_GPLL0_USER_CTL, ALPHA_EN)      |
                HWIO_FMSK(GCC_GPLL0_USER_CTL, VCO_SEL)       |
                HWIO_FMSK(GCC_GPLL0_USER_CTL, PRE_DIV_RATIO) |
                HWIO_FMSK(GCC_GPLL0_USER_CTL, POST_DIV_RATIO));


  /*
   * Program the VCO.
   */
  nUserVal |= (pConfig->nVCO << HWIO_SHFT(GCC_GPLL0_USER_CTL, VCO_SEL));

  /*
   * Program the pre-div value (div-1 to div-8).
   */
  if (pConfig->nPreDiv <= 8 && pConfig->nPreDiv > 0)
  {
    nUserVal |= ((pConfig->nPreDiv - 1) << HWIO_SHFT(GCC_GPLL0_USER_CTL, PRE_DIV_RATIO));
  }

  /*
   * Program the post-div value (div-3 not supported)
   */
  if (pConfig->nPostDiv == 2)
  {
    nUserVal |= (1 << HWIO_SHFT(GCC_GPLL0_USER_CTL, POST_DIV_RATIO));
  }
  else if (pConfig->nPostDiv == 4)
  {
    nUserVal |= (3 << HWIO_SHFT(GCC_GPLL0_USER_CTL, POST_DIV_RATIO));
  }

  /*
   *  Check fractional output or integer output.
   */
  if( pConfig->nAlpha )
  {
    nUserVal |= HWIO_FMSK(GCC_GPLL0_USER_CTL, ALPHA_EN);
  }

  /*
   * Enable MAIN_OUT_ENA bit. 
   */
  nUserVal |= HWIO_FMSK(GCC_GPLL0_USER_CTL, PLLOUT_LV_MAIN);

  /* 
   * Finally program the CONFIG register.
   */
  outp32(nModeAddr + HWIO_OFFS(PLL_USER_CTL), nUserVal);

  /*
   * Program the FSM portion of the mode register.
   */
  nModeVal &= ~HWIO_FMSK(GCC_GPLL0_MODE, PLL_BIAS_COUNT);
  nModeVal &= ~HWIO_FMSK(GCC_GPLL0_MODE, PLL_LOCK_COUNT);
  #if defined HWIO_APC0_QLL_PLL_MODE_FMSK
  nModeVal &= ~HWIO_FMSK(APC0_QLL_PLL_MODE, APC_PDN);  // Clear power down bit
  #endif
    nModeVal |= CLOCK_PLL_BIAS_COUNT_VAL;
    nModeVal |= CLOCK_PLL_LOCK_COUNT_VAL;

  if (pConfig->nVoteAddr != 0)
  {
    nModeVal |= HWIO_FMSK(GCC_GPLL0_MODE, PLL_VOTE_FSM_ENA);
  }

    outp32(nModeAddr, nModeVal);

  if (pConfig->nConfigCtl)
  {
    /* The CONFIG_CTL resets with an incorrect default value.  Fix it. */
    outp32(nModeAddr + HWIO_OFFS(PLL_CONFIG_CTL), pConfig->nConfigCtl);
  }

  return TRUE;
} /* END Clock_ConfigurePLL */


/* =========================================================================
**  Function : Clock_ConfigMux
** =========================================================================*/
/*!
    Configure a clock mux. 

    @param pConfig -  [IN] Clock mux config structure
    @return
    TRUE -- Initialization was successful.
    FALSE -- Initialization failed.

    @dependencies
    None.

    @sa None
*/
boolean Clock_ConfigMux (const ClockConfigMuxType *pConfig)
{
  uintnt nCmdRCGRAddr, nCfgRCGRAddr;
  uint32 nCmdRCGRVal,  nCfgRCGRVal;
  uintnt nMAddr, nNAddr, nDAddr;
  uint32 nSource  = 0;
  uint32 nTimeout = 0;

  if( ! Clock_SourceMapToMux( pConfig, &nSource) )
  {
    return FALSE;
  }

  nCmdRCGRAddr = pConfig->nCMDRCGRAddr;
  nCmdRCGRVal  = inp32(nCmdRCGRAddr);
  nCfgRCGRAddr = pConfig->nCMDRCGRAddr + CLOCK_CFG_REG_OFFSET; 
  nCfgRCGRVal  = inp32(nCfgRCGRAddr);

  /* Clear the fields. */
  nCfgRCGRVal &= ~(CLOCK_CFG_RCGR_SRC_SEL_FMSK |
                  CLOCK_CFG_RCGR_SRC_DIV_FMSK |
                  CLOCK_CFG_RCGR_MODE_FMSK);

  /* Program the source and divider values. */
  nCfgRCGRVal |= (nSource << CLOCK_CFG_RCGR_SRC_SEL_SHFT)
                  & CLOCK_CFG_RCGR_SRC_SEL_FMSK;
  nCfgRCGRVal |= ((HALF_DIVIDER(pConfig) << CLOCK_CFG_RCGR_SRC_DIV_SHFT)
                  & CLOCK_CFG_RCGR_SRC_DIV_FMSK);

  /* Set MND counter mode depending on if it is in use. */
  if (pConfig->nM != 0 && (pConfig->nM < pConfig->nN))
  {
    nMAddr = pConfig->nCMDRCGRAddr + CLOCK_M_REG_OFFSET;
    nNAddr = pConfig->nCMDRCGRAddr + CLOCK_N_REG_OFFSET;
    nDAddr = pConfig->nCMDRCGRAddr + CLOCK_D_REG_OFFSET;

    outp32(nMAddr, pConfig->nM);
    outp32(nNAddr, NOT_N_MINUS_M(pConfig));
    outp32(nDAddr, NOT_2D(pConfig));

    nCfgRCGRVal |= ((CLOCK_CFG_RCGR_MODE_DUAL_EDGE_VAL << CLOCK_CFG_RCGR_MODE_SHFT)
                    & CLOCK_CFG_RCGR_MODE_FMSK);
  }

  /* Write the final CFG register value. */
  outp32(nCfgRCGRAddr, nCfgRCGRVal);

  /* Trigger the update. */
  nCmdRCGRVal |= CLOCK_CMD_CFG_UPDATE_FMSK;
  outp32(nCmdRCGRAddr, nCmdRCGRVal);

  /* Wait until update finishes. */
  while ( inp32(nCmdRCGRAddr) & CLOCK_CMD_CFG_UPDATE_FMSK )
  {
    if ( nTimeout++ >= CLOCK_UPDATE_TIMEOUT_US )
    {
      return FALSE;
    }

    busywait(1);
  }

  return TRUE;
}

  
/* =========================================================================
**  Function : Clock_TriggerUpdate
** =========================================================================*/
/*!
    Clock switch and wait for UPDATE bit to complete

    @param cmdReg - Address of the CBCR register

    TRUE -- CBCR programming successful.
    FALSE -- CBCR programming failed.

    @dependencies
    None.

    @sa None
*/
boolean Clock_TriggerUpdate(uintnt cmdReg, uintnt nMask)
{
  uint32 nTimeout = 0;
  uintnt nVal;

  nVal = inp32(cmdReg) | nMask;

  /* Trigger CMD_REG:UPDATE */
  outp32(cmdReg, nVal);

  /* Wait for CMD_REG:UPDATE to clear, showing the clock switch is complete */
  while (inp32(cmdReg) & nMask)
  {
    if (nTimeout++ >= CLOCK_UPDATE_TIMEOUT_US)
    {
      return FALSE;
    }
    busywait(1);
  }
  return TRUE;
}  
  
/* =========================================================================
**  Function : Clock_ToggleClock
** =========================================================================*/
/*!
    Enable/Disable a Clock and poll for CLK_OFF BIT. 

    @param CBCR_addr - Address of the CBCR register
           enable :-  enable/disable the CBCR 
    TRUE -- CBCR programming successful.
    FALSE -- CBCR programming failed.

    @dependencies
    None.

    @sa None
*/
boolean Clock_ToggleClock(uintnt CBCR_addr, Clock_CBCRtoggleType toggle_clk)
{
  uintnt CBCR_value;
  
  if(toggle_clk >= NUM_CLK_TOGGLE_TYPES) return FALSE;

  CBCR_value = inp32(CBCR_addr);
  
  if(toggle_clk == CLK_TOGGLE_ENABLE)  
  {
    CBCR_value = CBCR_value | CLK_ENABLE_MSK;
    outp32(CBCR_addr, CBCR_value);  
    do
    {
      CBCR_value = inp32(CBCR_addr);
    }while((CBCR_value & CLK_OFF_MSK) != 0);
    
  }
  else
  {
    CBCR_value = CBCR_value & ~CLK_ENABLE_MSK;
    outp32(CBCR_addr, CBCR_value);  
  }
  return TRUE;
}


/* ===========================================================================
**  Clock_PowerDomainEnable
** ======================================================================== */

boolean Clock_PowerDomainEnable ( uintnt nGDSCRAddr )
{
  uintnt nVal;
  uintnt nTimeout = 0;

  if( nGDSCRAddr == 0 )
  {
    return FALSE;
  }

  nVal  = inp32(nGDSCRAddr);

  /*
   * Clear the SW PD collapse bit
   */
  nVal &= ~CLK_GDSCR_SW_COLLAPSE_MSK;
  outp32(nGDSCRAddr, nVal);

  /*
   * Wait for PD ON
   */
  while( !(inp32(nGDSCRAddr) & CLK_GDSCR_PWR_ON_MSK) )
  {
    if (nTimeout++ >= CLK_GDSCR_TIMEOUT_US)
    {
      return FALSE;
    }
    busywait(1);
  }
  return TRUE;

} /* END Clock_PowerDomainEnable */


/* ===========================================================================
**  Clock_PowerDomainDisable
** ======================================================================== */

boolean Clock_PowerDomainDisable ( uintnt nGDSCRAddr )
{
  uintnt nVal;

  /* Sanity check */
  if(nGDSCRAddr == 0)
  {
    return FALSE;
  }

  nVal  = inp32(nGDSCRAddr);

  /* Set the SW PD collapse bit */
  nVal |= CLK_GDSCR_SW_COLLAPSE_MSK;
  outp32(nGDSCRAddr, nVal);

  return TRUE;
} /* END Clock_PowerDomainDisable */

