/**
==============================================================================

  @file ClockSDI.c
  
  Clock functions for support System Debug Image driver.  Since SDI image is
  required to be every small memory footprint, clock drivers only brings in
  necessary code to support it.

  Copyright (c) 2015-2016, Qualcomm Technologies, Inc. All rights reserved.

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
#include "ClockHWIO.h"


/*=========================================================================
                       MACRO DEFINITIONS
==========================================================================*/
#define SPARK_CONFIG_CTL 0x4001055B

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


#define CLK_ELEM_SIZE(array)      sizeof((array)[0])
#define CLK_NUM_ELEM(array)       (sizeof(array) / CLK_ELEM_SIZE(array))

#define CLK_BITS_ARE_CLR(nVal, nMask)    (((nVal) & (nMask)) == 0)
#define CLK_BITS_ARE_SET(nVal, nMask)    (((nVal) & (nMask)) == (nMask))

#define CLK_ENABLE_MSK 0x00000001
#define CLK_OFF_MSK    0x80000000
#define CLK_GDSCR_SW_COLLAPSE_MSK 0x00000001
#define CLK_GDSCR_PWR_ON_MSK      0x80000000
#define CLK_GDSCR_TIMEOUT_US      150


/*
 * ClockSDIConfigPLLType
 *
 * Parameters used for configuring a source that is a PLL.
 *
 *  nPLLModeAddr  - The address of the PLL MODE register.
 *  nVoteAddr     - The address of the PLL voting register. Set to NULL for 
 *                  non-FSM mode.
 *  nVoteMask     - The mask of the voting bit.
 *  eVCO          - The internal VCO to use.
 *  nPreDiv       - The pre-divider value (generally 1 or 2).
 *  nPostDiv      - The post-divider value 
 *  nL            - The L value for the PLL.  The PLL output frequency is derived
 *                  as out_freq = ((in_freq / nPreDiv) * (L + M/N)) / nPostDiv.
 *  nM            - The M value (see above).
 *  nN            - The N value (see above).
 *  nAlpha        - The Alpha(prog) value. For the 20nm PLLs, the output frequency is
 *                  derived as :
 *                  out_freq = ((in_freq / nPreDiv) * (L + ALPHAfrac)) / nPostDiv.
 *                  ALPHAprog = 2^b x ALPHAfrac where 'b' is 40 for Prius and 40 for Tesla.
 */
typedef struct ClockSDIConfigPLL
{
  uintnt nPLLModeAddr;
  uintnt nVoteAddr;
  uint32 nVoteMask;  
  uint32 nVCO;
  uint8  nPreDiv;
  uint8  nPostDiv;
  uint16 nL;
  uint16  nM;
  uint16  nN;
  uint32 nConfigCtl;
  uint64 nAlpha;
} ClockSDIConfigPLLType;

/*
 * ClockSDIConfigMuxType
 *
 * Parameters used for configuring a standard clock multiplexer.
 *
 *  nCMDRCGRAddr - The address of the CMD RCGR register.
 *  eSource     - The source to use.
 *  nDiv2x      - The integer (2 * divider) value to use.
 *  nM          - The M value for any M/N counter, or 0 to bypass.
 *  nN          - The N value for any M/N counter.
 *  n2D         - Twice the D value for any M/N counter.
 */
typedef struct ClockSDIConfigMux
{
  uintnt nCMDRCGRAddr;
  uint32 eSource;   // Originally 'ClockSourceType'.
  uint32 nDiv2x;
  uint32 nM;
  uint32 nN;
  uint32 n2D;
} ClockSDIConfigMuxType;

/*
 * ClockSDI_CBCRtoggleType
 *
 * A type to choose the the operation on clocks(enable/disable).
 */
typedef enum{
  CLK_TOGGLE_DISABLE    = 0,
  CLK_TOGGLE_ENABLE     = 1,
  NUM_CLK_TOGGLE_TYPES
} ClockSDI_CBCRtoggleType;


/* ---------- */
/*   Server   */
/* ---------- */
#if defined HWIO_GCCSN_SYS_PLL0_MODE_ADDR

  /* Map MSM register names to the corresponding server names. */
  #define GCC_GPLL0_MODE                       GCCSN_SYS_PLL0_MODE
  #define GCC_GPLL0_USER_CTL                   GCCSN_SYS_PLL0_USER_CTL
  #define GCC_SDCC2_APPS_CMD_RCGR              GCCSN_SDCC2_APPS_CMD_RCGR
  #define GCC_SDCC2_APPS_CFG_RCGR              GCCSN_SDCC2_APPS_CFG_RCGR
  #define GCC_SDCC2_APPS_M                     GCCSN_SDCC2_APPS_M
  #define GCC_SDCC2_APPS_N                     GCCSN_SDCC2_APPS_N
  #define GCC_SDCC2_APPS_D                     GCCSN_SDCC2_APPS_D

#endif

/*
 * Definitions for configuring the PLL in FSM Mode.
 */
#define CLOCK_PLL_BIAS_COUNT_VAL  (0x6 << HWIO_SHFT(GCC_GPLL0_MODE, PLL_BIAS_COUNT))
#define CLOCK_PLL_LOCK_COUNT_VAL  (0x0 << HWIO_SHFT(GCC_GPLL0_MODE, PLL_LOCK_COUNT))



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
      Data
==========================================================================*/

/* GPLL0 @ 600 MHz (general purpose PLL). */
static ClockSDIConfigPLLType PLL0_Cfg =
{
  .nPLLModeAddr  =  HWIO_ADDR(GCC_GPLL0_MODE),
  .nVoteAddr     =  HWIO_ADDR(GCC_APCS_GPLL_ENA_VOTE),
  .nVoteMask     =  HWIO_FMSK(GCC_APCS_GPLL_ENA_VOTE, GPLL0),
  .nVCO          =  2, 
  .nPreDiv       =  1,
  .nPostDiv      =  1, 
  .nL            =  31,
  .nM            =  0, // unused
  .nN            =  0, // unused
  .nConfigCtl    =  SPARK_CONFIG_CTL,
  .nAlpha        =  0x4000000000
};

/*=========================================================================
      Function Prototypes
==========================================================================*/
static boolean ClockSDI_TriggerUpdate ( uintnt cmdReg, uintnt nMask );
static boolean ClockSDI_ToggleClock   ( uintnt CBCR_addr, ClockSDI_CBCRtoggleType toggle_clk );
static boolean ClockSDI_ConfigurePLL  ( const ClockSDIConfigPLLType *pConfig );
static boolean ClockSDI_ConfigMux     ( const ClockSDIConfigMuxType *pConfig );
static boolean ClockSDI_EnablePLL     ( const ClockSDIConfigPLLType *pConfig );


/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/ 

/* =========================================================================
**  Function : ClockSDI_TriggerUpdate
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
static boolean ClockSDI_TriggerUpdate(uintnt cmdReg, uintnt nMask)
{
  uintnt nVal;

  nVal = inp32(cmdReg) | nMask;

  /* Trigger CMD_REG:UPDATE */
  outp32(cmdReg, nVal);

  /* Wait for CMD_REG:UPDATE to clear, showing the clock switch is complete */
  while (inp32(cmdReg) & nMask);

  return TRUE;
}


/* =========================================================================
**  Function : ClockSDI_ToggleClock
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
static boolean ClockSDI_ToggleClock(uintnt CBCR_addr, ClockSDI_CBCRtoggleType toggle_clk)
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

/* =========================================================================
**  Function : ClockSDI_ConfigurePLL
** =========================================================================*/
/**
  Configures a PLL.

  @param *pConfig [in] -- PLL configuration

*/
static boolean ClockSDI_ConfigurePLL(const ClockSDIConfigPLLType *pConfig)
{
  uintnt nModeAddr;
  uint32 nUserVal, nModeVal;

  nModeAddr = pConfig->nPLLModeAddr;
  nModeVal = inp32(nModeAddr);

  if ( ((nModeVal & CLOCK_PLL_MODE_ACTIVE) == CLOCK_PLL_MODE_ACTIVE) ||
       (nModeVal & HWIO_FMSK(GCC_GPLL0_MODE, PLL_LOCK_DET)) )
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
}


/* =========================================================================
**  Function : ClockSDI_ConfigMux
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
static boolean ClockSDI_ConfigMux (const ClockSDIConfigMuxType *pConfig)
{
  uintnt nCmdRCGRAddr, nCfgRCGRAddr;
  uint32 nCmdRCGRVal,  nCfgRCGRVal;
  uintnt nMAddr, nNAddr, nDAddr;
  uint32 nSource  = 0;

  nSource = pConfig->eSource;

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
  while ( inp32(nCmdRCGRAddr) & CLOCK_CMD_CFG_UPDATE_FMSK );

  return TRUE;
}


/* ============================================================================
**  Function : ClockSDI_EnablePLL
** ============================================================================
*/
/*!
    Enable a PLL.  If it is voteable, it will be set for FSM mode
    and voted for using the vote register. Doesn't configure the PLL.

    @param pConfig -  [IN] PLL configuration structure
    @return
    TRUE -- Initialization was successful.
    FALSE -- Initialization failed.

    @dependencies
    None.

    @sa None
*/
static boolean ClockSDI_EnablePLL(const ClockSDIConfigPLLType *pConfig)
{
  uintnt nModeAddr;
  uint32 nModeVal;

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
      while ((inp32(nModeAddr) & HWIO_FMSK(GCC_GPLL0_MODE, PLL_ACTIVE_FLAG)) == 0);
  }

        return TRUE;
      }

  /*
   * Configure the PLL.
   */
    if ( !ClockSDI_ConfigurePLL(pConfig) ) return FALSE;
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
    while ((inp32(nModeAddr) & HWIO_FMSK(GCC_GPLL0_MODE, PLL_ACTIVE_FLAG)) == 0);
  }
  else
  {
    /* Not support non-FSM PLL yet */
    return FALSE;
  }

  return TRUE;
}


/* ========================================================================
**  Function : Clock_ConfigureDDR
** ======================================================================*/
/*
    Description: Configure all clocks needed for DDR configuration.  This
    extension API is used for bootup and emergency download mode.

    @param None
    @return
    TRUE -- Initialization was successful.
    FALSE -- Initialization failed.

    @dependencies
    None.

    @sa None
*/
boolean Clock_ConfigureDDR( void )
{
  uint32 mask;
  ClockSDIConfigMuxType clkCfgDDR      = {HWIO_ADDR(GCC_BIMC_DDR_CPLL0_ROOT_CMD_RCGR), 1,  6, 0, 0, 0};
  ClockSDIConfigMuxType clkCfgBIMC     = {HWIO_ADDR(GCC_BIMC_CMD_RCGR),                1, 18, 0, 0, 0};
  ClockSDIConfigMuxType clkCfgBIMCHMSS = {HWIO_ADDR(GCC_BIMC_HMSS_AXI_CMD_RCGR),       1, 12, 0, 0, 0};
  ClockSDIConfigMuxType clkCfgBIMCGFX  = {HWIO_ADDR(GCC_GPU_BIMC_GFX_CMD_RCGR),        1, 24, 0, 0, 0};
  //ClockSDIConfigMuxType clkCfgBIMCQ6   = {HWIO_ADDR(GCC_MSS_Q6_BIMC_AXI_CMD_RCGR),     1,  6, 0, 0, 0};
  ClockSDIConfigMuxType clkCfgPIMEM    = {HWIO_ADDR(GCC_PIMEM_AXI_CMD_RCGR),         1,  6, 0, 0, 0};  // GPLL0

  /* Config PIMEM */
  if ( !ClockSDI_EnablePLL(&PLL0_Cfg) ) return FALSE;
  if ( !ClockSDI_ConfigMux(&clkCfgPIMEM) ) return FALSE;
   
  ClockSDI_ToggleClock(HWIO_GCC_MCCC_CFG_AHB_CBCR_ADDR, CLK_TOGGLE_ENABLE);
  ClockSDI_ToggleClock(HWIO_GCC_PIMEM_AHB_CBCR_ADDR, CLK_TOGGLE_ENABLE);
  ClockSDI_ToggleClock(HWIO_GCC_SYS_NOC_PIMEM_AXI_CBCR_ADDR, CLK_TOGGLE_ENABLE);
  ClockSDI_ToggleClock(HWIO_GCC_PIMEM_AXI_CBCR_ADDR, CLK_TOGGLE_ENABLE);
  ClockSDI_ToggleClock(HWIO_GCC_BIMC_PIMEM_AXI_CBCR_ADDR, CLK_TOGGLE_ENABLE);

  /* Enable the necessary voteable HMSS and BIMC related clocks */
  mask =
    HWIO_FMSK(GCC_APCS_CLOCK_BRANCH_ENA_VOTE, SYS_NOC_HMSS_AHB_CLK_ENA) | 
    HWIO_FMSK(GCC_APCS_CLOCK_BRANCH_ENA_VOTE, BIMC_HMSS_AXI_CLK_ENA) | 
    HWIO_FMSK(GCC_APCS_CLOCK_BRANCH_ENA_VOTE, HMSS_AHB_CLK_ENA) |
    HWIO_FMSK(GCC_APCS_CLOCK_BRANCH_ENA_VOTE, BIMC_HMSS_AXI_CLK_ENA);
  HWIO_OUTM(GCC_APCS_CLOCK_BRANCH_ENA_VOTE, mask, mask);
  
  mask = HWIO_FMSK(GCC_APCS_CLOCK_SLEEP_ENA_VOTE, BIMC_HMSS_AXI_CLK_SLEEP_ENA);
  HWIO_OUTM(GCC_APCS_CLOCK_SLEEP_ENA_VOTE, mask, mask);
  
  /* Revoke APCS IMEM clock enable, since RPM will manage this clock and turn off during XO shutdown */
  HWIO_OUTF( GCC_APCS_CLOCK_BRANCH_ENA_VOTE, IMEM_AXI_CLK_ENA, 0 );

  mask =
    HWIO_FMSK(GCC_RPM_CLOCK_BRANCH_ENA_VOTE, IMEM_AXI_CLK_ENA) |
    HWIO_FMSK(GCC_RPM_CLOCK_BRANCH_ENA_VOTE, BIMC_HMSS_AXI_CLK_ENA) |
    HWIO_FMSK(GCC_RPM_CLOCK_BRANCH_ENA_VOTE, MSG_RAM_AHB_CLK_ENA);
  HWIO_OUTM(GCC_RPM_CLOCK_BRANCH_ENA_VOTE, mask, mask);

  /* Enable all possible BIMC and DDR clocks */
  ClockSDI_ToggleClock(HWIO_GCC_CFG_NOC_DDR_CFG_CBCR_ADDR, CLK_TOGGLE_ENABLE);
  ClockSDI_ToggleClock(HWIO_GCC_DDR_DIM_CFG_CBCR_ADDR, CLK_TOGGLE_ENABLE);
  ClockSDI_ToggleClock(HWIO_GCC_DDR_DIM_SLEEP_CBCR_ADDR, CLK_TOGGLE_ENABLE);
  HWIO_OUTF(GCC_BIMC_DDR_CPLL0_CBCR, CLK_ENABLE, 1);
  
  ClockSDI_ToggleClock(HWIO_GCC_BIMC_XO_CBCR_ADDR, CLK_TOGGLE_ENABLE);
  ClockSDI_ToggleClock(HWIO_GCC_BIMC_CFG_AHB_CBCR_ADDR, CLK_TOGGLE_ENABLE);
  ClockSDI_ToggleClock(HWIO_GCC_BIMC_SLEEP_CBCR_ADDR, CLK_TOGGLE_ENABLE);
  ClockSDI_ToggleClock(HWIO_GCC_BIMC_SYSNOC_AXI_CBCR_ADDR, CLK_TOGGLE_ENABLE);
  ClockSDI_ToggleClock(HWIO_GCC_BIMC_CBCR_ADDR, CLK_TOGGLE_ENABLE);

  /* Perform a BIMC DDR clock switch */
  if( ! ClockSDI_ConfigMux(&clkCfgBIMC)) return FALSE;

  /* Perform a BIMC APSS clock switch */
  if( ! ClockSDI_ConfigMux(&clkCfgBIMCHMSS)) return FALSE;

  /* Perform a BIMC GFX clock switch */
  if( ! ClockSDI_ConfigMux(&clkCfgBIMCGFX)) return FALSE;

  /* Perform a BIMC Q6 clock switch */
  //if( ! ClockSDI_ConfigMux(&clkCfgBIMCQ6)) return FALSE;

  /* Perform a DDR clock switch */
  if( ! ClockSDI_ConfigMux(&clkCfgDDR)) return FALSE;

  HWIO_OUTF(GCC_BIMC_GDSCR, RETAIN_FF_ENABLE, 1);

  return TRUE;
}
