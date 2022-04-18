/**
==============================================================================
  @file ClockXBL.c

  Clock functions for the XBL Loader Clock Driver.

==============================================================================

                             Edit History


when      who           what, where, why
--------  ------------  ------------------------------------------------------
10/07/15  plc           Comment out railway calls until railway is delivered.
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
#include "ClockBoot.h"
#include "ClockCommon.h"
#include "ClockBSP.h"
#include "railway.h"
#include "boot_build_component.h"

/*=========================================================================
                       MACRO DEFINITIONS
==========================================================================*/


/*=========================================================================
      Data
==========================================================================*/
/*
 * Variable to enable Dynamic Clock Divide.
 */
boolean Boot_Clock_DCD = TRUE;


/*=========================================================================
      Function Prototypes
==========================================================================*/

boolean Clock_InitCrypto(void);
boolean Clock_InitRBCPR(void);
boolean Clock_InitIPA(void);
boolean Clock_InitPLLStatic(void);
extern boolean Clock_AGGRE2Init(void);
extern void Clock_ReplaceUSBBootClockEnable(void);
extern void Clock_StoreDDRFreqKHz ( uint32 nFreqKHz );
extern boolean Clock_CopyBIMCPlanToRPM( void );
extern uint32 Clock_GetAPSSCL0SpeedKHz(void);
extern void Clock_InitBIMCPlan( void );

/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/

/*!

  This function enables dynamic clock divider.  HW auto divides clock down
  when bus clock is not in used for power saving.

  @dependencies
  None.

*/
static void Clock_EnableDynClkDivide (void)
{
  /*This is to increase the CNOC Center TO value to 1.026ms.
  As the DCD in IPA-->AGGNOC-->CNOC_Center --> USB3 path was impacting
  USB traffic*/
  HWIO_OUTF(CNOC_DCD_CENTER_QHCLK_HYSTCNT, FIRSTCNT, 19712);
   /* CNOC DCD */
  HWIO_OUTF(GCC_CNOC_DCD_CONFIG, DCD_ENABLE, 1);
  HWIO_OUTF(GCC_CNOC_NORTH_DCD_CONFIG, DCD_ENABLE, 1);
  HWIO_OUTF(GCC_CNOC_SOUTH_DCD_CONFIG, DCD_ENABLE, 1);
  //HWIO_OUTF(GCC_CNOC_PERIPH_NORTH_DCD_CONFIG, DCD_ENABLE, 1);

  HWIO_OUTF(CNOC_DCD_CENTER_QHCLK_CONFIG, DCDEN, 1);
  HWIO_OUTF(CNOC_DCD_NORTH_QHCLK_CONFIG, DCDEN, 1);
  HWIO_OUTF(CNOC_DCD_SOUTH_QHCLK_CONFIG, DCDEN, 1);

  /* SNOC DCD */
  HWIO_OUTF(GCC_SNOC_DCD_CONFIG, DCD_ENABLE, 1);
  HWIO_OUTF(GCC_SNOC_NORTH_DCD_CONFIG, DCD_ENABLE, 1);
  HWIO_OUTF(GCC_SNOC_SOUTH_DCD_CONFIG, DCD_ENABLE, 1);
  HWIO_OUTF(GCC_SNOC_HS_DCD_CONFIG, DCD_ENABLE, 1);
 //To be: enabled later, not working on virtio
// #ifndef PRE_SIL
  HWIO_OUTF(SNOC_DCD_HS_QXCLK_CONFIG, DCDEN, 1);
  HWIO_OUTF(SNOC_DCD_QXCLK_CONFIG, DCDEN, 1);
 //#endif
  /* Gladiator DCD */
  // Removed when this clock was put under HW_CTL 
  //HWIO_OUTF(GCC_BIMC_HMSS_AXI_DCD_CONFIG, DCD_ENABLE, 1);
  HWIO_OUTF(GCC_BIMC_MSS_Q6_AXI_DCD_CONFIG, DCD_ENABLE, 1);
  HWIO_OUTF(GCC_BIMC_GFX_DCD_CONFIG, DCD_ENABLE, 1);
  HWIO_OUTF(GCC_BIMC_CORE_DCD_CONFIG, DCD_ENABLE, 1);
      /* Due to hardware issue cdsp is facing latency issues in accessing the ddr, so disabling the cdsp_bimc_dcd*/
  //HWIO_OUTF(GCC_CDSP_BIMC_DCD_CONFIG, DCD_ENABLE, 1);

  /* Aggregator NOC DCD */
  HWIO_OUTF(A2_NOC_AGGRE2NOC_NORTH_DCD_CONFIG, DCDEN, 1);

  //To be: enabled later, not working on virtio
  /* MMSS NOC DCD */
//#ifndef PRE_SIL
  HWIO_OUTF(MNOC_DCD_QHCLK_CONFIG, DCDEN, 1);
  HWIO_OUTF(MNOC_DCD_QXCLK_CONFIG, DCDEN, 1);
//#endif

  return;
}


/* ============================================================================
**  Function : Clock_Init
** ============================================================================
*/
/*!

    This function turns on the required clocks and configures
    Fabric and Krait speeds depending on the System Fabric and
    CPU boot performance level.

    @param eSysPerfLevel   -  [in] Fabric and DDR performance level to initialize.
    @param eCPUPerfLevel   -  [in] Scropion CPU performance level to initialize.

    @return
    TRUE -- Initialization was successful.
    FALSE -- Initialization failed.

   @dependencies
    None.

*/

boolean Clock_Init( ClockBootPerfLevelType eSysPerfLevel,
                    ClockBootPerfLevelType eCPUPerfLevel)
{
  uint32 val = 0;
  if( ! Clock_SetCPUPerfLevel(eCPUPerfLevel)) return FALSE;
  if( ! Clock_SetSysPerfLevel(eSysPerfLevel)) return FALSE;
  if( ! Clock_InitIPA()) return FALSE;

  Clock_ReplaceUSBBootClockEnable();

  /* Enable HW clock divider. */
  if (Boot_Clock_DCD == TRUE)
  {
     Clock_ToggleClock(HWIO_GCC_AGGRE2_NOC_CXO_NORTH_CBCR_ADDR, CLK_TOGGLE_ENABLE);
    Clock_EnableDynClkDivide();
  }

#if 0
  TODO: There is no obvious equivalent to these two enables on Sdm660.
  APCS_COMMON_LMH_CMD_RCGR, APCS_COMMON_LMH_CFG_RCGR : Set freq, but do not enable
  GCC_GLM_AHB_CBCR, GCC_GLM_CBCR : Enable, but not very similar to what came before
  Ask LMh team for their requirement.
  /* Enable 200 MHz AHB for LMh Lite */
  if( HWIO_IN(TCSR_SOC_HW_VERSION) != CLK_SOC_MSM8994_V1 )
  {
    uint32 mask = HWIO_FMSK(APCS_COMMON_LMH_AUX_DIV, LMH_RCG_CLK_EN) |
                  HWIO_FMSK(APCS_COMMON_LMH_AUX_DIV, LMH_RCG_WR_EN);
    HWIO_OUTM( APCS_COMMON_LMH_AUX_DIV, mask, mask );
  }
#endif
   /*Adding this to avoid SNOC-BIMC slave NIUs reset during BIMC PC. 
   in NZ, this portion was power collapsible while it is not in case of SL.
   See CR:1116780*/
   HWIO_OUTF(GCC_SYS_NOC_BIMC_NIUS_MISC, GDSC_ENABLE, 0);
   
   /*This is to enable the CGC between PLLs and RCG for powere saving*/
   /*GCC*/
   val = HWIO_IN(GCC_GCC_SPARE3_REG);
   val = val & 0xFFFFFFFE; /*resetting only 0th bit*/
   HWIO_OUT(GCC_GCC_SPARE3_REG,val);
   /*MMSS*/
   HWIO_OUTF(MMSS_CC_SPARE_FLOPS,CC_SPAREFLOP_0,0x0);
  return TRUE;
}


/* ========================================================================
**  Function : Clock_PreDDRInitEx
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
boolean Clock_PreDDRInitEx( uint32 ddr_type )
{
  uint32 mask;
  ClockConfigMuxType clkCfgDDR      = {HWIO_ADDR(GCC_BIMC_DDR_CPLL0_ROOT_CMD_RCGR), MUX_GCC, SRC_GPLL0,   6, 0, 0, 0};
  ClockConfigMuxType clkCfgBIMC     = {HWIO_ADDR(GCC_BIMC_CMD_RCGR),                MUX_GCC, SRC_GPLL0,   6, 0, 0, 0};
  ClockConfigMuxType clkCfgBIMCHMSS = {HWIO_ADDR(GCC_BIMC_HMSS_AXI_CMD_RCGR),       MUX_GCC, SRC_GPLL0,   6, 0, 0, 0};
  ClockConfigMuxType clkCfgBIMCGFX  = {HWIO_ADDR(GCC_GPU_BIMC_GFX_CMD_RCGR),        MUX_GCC, SRC_GPLL0,  12, 0, 0, 0};
  ClockConfigMuxType clkCfgBIMCQ6   = {HWIO_ADDR(GCC_MSS_Q6_BIMC_AXI_CMD_RCGR),     MUX_GCC, SRC_GPLL0,   6, 0, 0, 0};
  ClockConfigMuxType clkCfgBIMCCDSP = {HWIO_ADDR(GCC_CDSP_BIMC_CMD_RCGR),           MUX_GCC, SRC_GPLL0,  12, 0, 0, 0};

  Clock_StoreDDRFreqKHz(200000);


  /* Enable the necessary voteable HMSS and BIMC related clocks */
  mask = HWIO_FMSK(GCC_APCS_CLOCK_BRANCH_ENA_VOTE, SYS_NOC_HMSS_AHB_CLK_ENA);
  HWIO_OUTM(GCC_APCS_CLOCK_BRANCH_ENA_VOTE, mask, mask);
  /* Try out BIMC_HMSS_AXI dynamic clock gating */
  HWIO_OUTF(GCC_BIMC_HMSS_AXI_CBCR,HW_CTL,0x1);
  HWIO_OUTF(GCC_APCS_CLOCK_BRANCH_ENA_VOTE,BIMC_HMSS_AXI_CLK_ENA, 0x0);


  mask =
    HWIO_FMSK(GCC_RPM_CLOCK_BRANCH_ENA_VOTE, IMEM_AXI_CLK_ENA) |
    HWIO_FMSK(GCC_RPM_CLOCK_BRANCH_ENA_VOTE, HMSS_AHB_CLK_ENA) |
    HWIO_FMSK(GCC_RPM_CLOCK_BRANCH_ENA_VOTE, MSG_RAM_AHB_CLK_ENA);
  HWIO_OUTM(GCC_RPM_CLOCK_BRANCH_ENA_VOTE, mask, mask);

  /* Revoke APCS IMEM clock enable, since RPM will manage this clock and turn off during XO shutdown */
  /* Same for gcc_hmss_ahb_clk */
  HWIO_OUTF( GCC_APCS_CLOCK_BRANCH_ENA_VOTE, IMEM_AXI_CLK_ENA, 0 );
  HWIO_OUTF( GCC_APCS_CLOCK_BRANCH_ENA_VOTE, HMSS_AHB_CLK_ENA, 0 );

  /* Enable all possible BIMC and DDR clocks */
  Clock_ToggleClock(HWIO_GCC_CFG_NOC_DDR_CFG_CBCR_ADDR, CLK_TOGGLE_ENABLE);
  Clock_ToggleClock(HWIO_GCC_DDR_DIM_CFG_CBCR_ADDR, CLK_TOGGLE_ENABLE);
  Clock_ToggleClock(HWIO_GCC_DDR_DIM_SLEEP_CBCR_ADDR, CLK_TOGGLE_ENABLE);
  HWIO_OUTF(GCC_BIMC_DDR_CPLL0_CBCR, CLK_ENABLE, 1);
  //HWIO_OUTF(GCC_BIMC_DDR_CPLL1_CBCR, CLK_ENABLE, 1);

  Clock_ToggleClock(HWIO_GCC_BIMC_XO_CBCR_ADDR, CLK_TOGGLE_ENABLE);
  Clock_ToggleClock(HWIO_GCC_BIMC_DTTS_XO_CBCR_ADDR, CLK_TOGGLE_ENABLE);
  Clock_ToggleClock(HWIO_GCC_BIMC_CFG_AHB_CBCR_ADDR, CLK_TOGGLE_ENABLE);
  Clock_ToggleClock(HWIO_GCC_BIMC_SLEEP_CBCR_ADDR, CLK_TOGGLE_ENABLE);
  Clock_ToggleClock(HWIO_GCC_BIMC_SYSNOC_AXI_CBCR_ADDR, CLK_TOGGLE_ENABLE);
  Clock_ToggleClock(HWIO_GCC_BIMC_CBCR_ADDR, CLK_TOGGLE_ENABLE);

  /* Perform a BIMC CDSP clock switch */
  if( ! Clock_EnableSource( clkCfgBIMCCDSP.eSource )) return FALSE;
  if( ! Clock_ConfigMux(&clkCfgBIMCCDSP)) return FALSE;

  /* Perform a BIMC DDR clock switch */
  if( ! Clock_EnableSource( clkCfgBIMC.eSource )) return FALSE;
  if( ! Clock_ConfigMux(&clkCfgBIMC)) return FALSE;

  /* Perform a BIMC APSS clock switch */
  if( ! Clock_EnableSource( clkCfgBIMCHMSS.eSource )) return FALSE;
  if( ! Clock_ConfigMux(&clkCfgBIMCHMSS)) return FALSE;

  /* Perform a BIMC GFX clock switch */
  if( ! Clock_EnableSource( clkCfgBIMCGFX.eSource )) return FALSE;
  if( ! Clock_ConfigMux(&clkCfgBIMCGFX)) return FALSE;

  /* Perform a BIMC Q6 clock switch */
  HWIO_OUTF(GCC_MSS_Q6_BIMC_AXI_CBCR, CLK_ENABLE, 1);
  if( ! Clock_EnableSource( clkCfgBIMCQ6.eSource )) return FALSE;
  if( ! Clock_ConfigMux(&clkCfgBIMCQ6)) return FALSE;

  /* Perform a DDR clock switch */
  if( ! Clock_EnableSource( clkCfgDDR.eSource )) return FALSE;
  if( ! Clock_ConfigMux(&clkCfgDDR)) return FALSE;

  Clock_I2CInit();

  HWIO_OUTF(GCC_BIMC_GDSCR, RETAIN_FF_ENABLE, 1);

  HWIO_OUT(MCCC_MCCC_CH0_SPARE0, 0x2); /* Select ddrss_ch0_mc_clk so it is selectable */
                                       /* by HLOS kernel on GCC_DEBUG_CLK_CTL mux     */
                                       /* as 0x14e on MSM8998v2                       */
  
  /* Bringining SSC out of RESET is required to enable LPASS SWAY register */
  HWIO_OUTF(GCC_SSC_RESET,SSC_ARES,0);

    /* LPASS SWAY clock is required for handling ABT Error */
  Clock_ToggleClock(HWIO_ADDR(GCC_LPASS_SWAY_CBCR), CLK_TOGGLE_ENABLE);
  return TRUE;
}


/* ========================================================================
**  Function : Clock_PreDDRInit
** ======================================================================*/
/*
    Description: Clock_PreDDRInitEx() was added in 8974 to provide a separate API
    for emergency download (EDL) without including Mxdroop work around. Adding wrapper
    function to avoid compilation erros in 8x26 and 8x10.

    @param None
    @return
    TRUE -- Initialization was successful.
    FALSE -- Initialization failed.

    @dependencies
    None.

    @sa None
*/
boolean Clock_PreDDRInit( uint32 ddr_type )
{
  Clock_RailwayType *pClockRailway;


  /* Setup railways */
  pClockRailway = Clock_RailwayConfig();
  pClockRailway->nCxRailId = RAIL_NOT_SUPPORTED_BY_RAILWAY;
  pClockRailway->nEBIRailId = RAIL_NOT_SUPPORTED_BY_RAILWAY;

  /* Only vote for railways for normal boot (Not deviceprogrammer) */
  if ( PcdGet32 (PcdBuildType) != SBL_BUILD_DEVICEPROGRAMMER_LITE && PcdGet32 (PcdBuildType) != SBL_BUILD_DEVICEPROGRAMMER_DDR)
  {
    /* Initialize CX & VDDA_EBI Rails */
    pClockRailway->nCxRailId = rail_id(pClockRailway->CxRail);
    pClockRailway->nEBIRailId = rail_id(pClockRailway->EBIRail);

    if( (RAIL_NOT_SUPPORTED_BY_RAILWAY == pClockRailway->nCxRailId) ||
        (RAIL_NOT_SUPPORTED_BY_RAILWAY == pClockRailway->nEBIRailId) )
    {
      return FALSE;
    }

    pClockRailway->CxVoter = railway_create_voter(pClockRailway->nCxRailId,RAILWAY_CLOCK_DRIVER_VOTER_ID);
    pClockRailway->EBIVoter = railway_create_voter(pClockRailway->nEBIRailId,RAILWAY_CLOCK_DRIVER_VOTER_ID);

    railway_corner_vote(pClockRailway->CxVoter, RAILWAY_NOMINAL);
    railway_corner_vote(pClockRailway->EBIVoter, RAILWAY_NOMINAL);
    railway_transition_rails( );
  }

  /* Init BIMC clock plan for the chipset's version. */
  Clock_InitBIMCPlan();

  return Clock_PreDDRInitEx( ddr_type );
}


/* ========================================================================
**  Function : Clock_I2CInit
** ======================================================================*/
/*
    Description: Configure all clocks needed for EEPROM to be used Pre DDR.

    @param None
    @return
    TRUE -- Initialization was successful.
    FALSE -- Initialization failed.

    @dependencies
    None.

    @sa None
*/
boolean Clock_I2CInit( void )
{
  /* These clocks can be disabled at Clock_ExitBoot, so keep that function
   * in sync */

  HWIO_OUTF(GCC_APCS_CLOCK_BRANCH_ENA_VOTE, BLSP2_AHB_CLK_ENA, 1);
  HWIO_OUTF(GCC_APCS_CLOCK_BRANCH_ENA_VOTE, BLSP2_SLEEP_CLK_ENA, 1);
  //Clock_ToggleClock(HWIO_GCC_BLSP2_QUP5_I2C_APPS_CBCR_ADDR, CLK_TOGGLE_ENABLE);

  // Turn  on the GCC_BLSP1_QUP2_I2C_APPS_CBCR
  HWIO_OUTF(GCC_APCS_CLOCK_BRANCH_ENA_VOTE, BLSP1_AHB_CLK_ENA, 1);
  HWIO_OUTF(GCC_APCS_CLOCK_BRANCH_ENA_VOTE, BLSP1_SLEEP_CLK_ENA, 1);
  HWIO_OUTF(GCC_BLSP1_QUP2_I2C_APPS_CBCR, CLK_ENABLE, 1);

  return TRUE;
}


/* ============================================================================
**  Function : Clock_InitForDownloadMode
** ============================================================================
*/
/*!
    Configure clocks for download.  Enable every RAM we want to dump.

    @param None.
    @return
    TRUE -- Initialization was successful.
    FALSE -- Initialization failed.

    @dependencies
    None.

    @sa None
*/
void Clock_InitForDownloadMode(void)
{
  uint32 mask;

  /* Enable the necessary voteable KPSS and BIMC related clocks */
  mask =
    HWIO_FMSK(GCC_APCS_CLOCK_BRANCH_ENA_VOTE, SYS_NOC_HMSS_AHB_CLK_ENA) |
    HWIO_FMSK(GCC_APCS_CLOCK_BRANCH_ENA_VOTE, BIMC_HMSS_AXI_CLK_ENA) |
    HWIO_FMSK(GCC_APCS_CLOCK_BRANCH_ENA_VOTE, HMSS_AHB_CLK_ENA) |
    HWIO_FMSK(GCC_APCS_CLOCK_BRANCH_ENA_VOTE, BOOT_ROM_AHB_CLK_ENA);

  HWIO_OUTM(GCC_APCS_CLOCK_BRANCH_ENA_VOTE, mask, mask);

  mask =
    HWIO_FMSK(GCC_RPM_CLOCK_BRANCH_ENA_VOTE, MSG_RAM_AHB_CLK_ENA) |
    HWIO_FMSK(GCC_RPM_CLOCK_BRANCH_ENA_VOTE, IMEM_AXI_CLK_ENA);

  HWIO_OUTM(GCC_RPM_CLOCK_BRANCH_ENA_VOTE, mask, mask);
}


/* ============================================================================
**  Function : Clock_ExitBoot
** ============================================================================
*/
/*!

    This function turns off clocks that were used during boot, but are not
    needed after boot.  This should be called at the end of boot.

    @return
    TRUE -- Initialization was successful.
    FALSE -- Initialization failed.

   @dependencies
    None.

*/
boolean Clock_ExitBoot(void)
{
  /* Clear UFS_BOOT_CLOCK_CTL, so UFS clocks can be managed by HLOS */
  HWIO_OUTF ( GCC_UFS_BOOT_CLOCK_CTL, CLK_ENABLE, 0 );

  /* Disable I2C related clocks */
  HWIO_OUTF(GCC_APCS_CLOCK_BRANCH_ENA_VOTE, BLSP2_AHB_CLK_ENA, 0);
  HWIO_OUTF(GCC_APCS_CLOCK_BRANCH_ENA_VOTE, BLSP2_SLEEP_CLK_ENA, 0);
  Clock_ToggleClock(HWIO_GCC_BLSP2_QUP4_I2C_APPS_CBCR_ADDR, CLK_TOGGLE_DISABLE);

   // Turn  off the GCC_BLSP1_QUP2_I2C_APPS_CBCR
  HWIO_OUTF(GCC_APCS_CLOCK_BRANCH_ENA_VOTE, BLSP1_AHB_CLK_ENA, 0);
  HWIO_OUTF(GCC_APCS_CLOCK_BRANCH_ENA_VOTE, BLSP1_SLEEP_CLK_ENA, 0);
  HWIO_OUTF(GCC_BLSP1_QUP2_I2C_APPS_CBCR, CLK_ENABLE, 0);

  return TRUE;
}


/* ============================================================================
**  Function : Clock_DebugInit
** ============================================================================
*/
/*!

    This function is called very early in boot.  It is used for work-arounds that
    need to be done before JTAG attaches at the XBL "hold focus button" spin loop.

    @return
    TRUE -- Clean up was successful.
    FALSE -- Clean up failed.

   @dependencies
    You cannot use busywait in this function.

*/
boolean Clock_DebugInit(void)
{
  /* Set BIMC clocks to 300 MHz to accelerate boot */
  const ClockConfigMuxType clkCfgBIMC     = {HWIO_ADDR(GCC_BIMC_CMD_RCGR),                MUX_GCC, SRC_GPLL0,  4, 0, 0, 0};
  const ClockConfigMuxType clkCfgBIMCHMSS = {HWIO_ADDR(GCC_BIMC_HMSS_AXI_CMD_RCGR),       MUX_GCC, SRC_GPLL0,  4, 0, 0, 0};

  /* Enable SPMI clocks */
  HWIO_OUTF(GCC_RPM_CLOCK_BRANCH_ENA_VOTE, SPMI_CNOC_AHB_CLK_ENA, 1);

  /* Enable PIMEM clocks */
  HWIO_OUTF(GCC_PIMEM_AHB_CBCR, CLK_ENABLE, 1);
  HWIO_OUTF(GCC_SYS_NOC_PIMEM_AXI_CBCR, CLK_ENABLE, 1);
  HWIO_OUTF(GCC_PIMEM_AXI_CBCR, CLK_ENABLE, 1);
  HWIO_OUTF(GCC_BIMC_PIMEM_AXI_CBCR, CLK_ENABLE, 1);

  /* Enable AGGRE NOC clocks*/
//  Clock_ToggleClock(HWIO_GCC_AGGRE1_NOC_MSMPU_CFG_AHB_CBCR_ADDR, CLK_TOGGLE_ENABLE);
  Clock_ToggleClock(HWIO_GCC_AGGRE2_NOC_MSMPU_CFG_AHB_CBCR_ADDR, CLK_TOGGLE_ENABLE);

  Clock_ToggleClock(HWIO_GCC_SPMI_SER_CBCR_ADDR, CLK_TOGGLE_ENABLE);
  Clock_ToggleClock(HWIO_GCC_SPMI_AHB_CBCR_ADDR, CLK_TOGGLE_ENABLE);

  /* Always enable this clock for GCC resets (BCRs) to work */
  Clock_ToggleClock(HWIO_GCC_GCC_IM_SLEEP_CBCR_ADDR, CLK_TOGGLE_ENABLE);

  Clock_ToggleClock( HWIO_ADDR(GCC_SNOC_CNOC_AHB_CBCR), CLK_TOGGLE_ENABLE );
  Clock_ToggleClock( HWIO_ADDR(GCC_CNOC_PERIPH_NORTH_AHB_CBCR), CLK_TOGGLE_ENABLE );
  Clock_ToggleClock( HWIO_ADDR(GCC_CNOC_PERIPH_SOUTH_AHB_CBCR), CLK_TOGGLE_ENABLE );
  Clock_ToggleClock( HWIO_ADDR(GCC_CNOC_PERIPH_AHB_CBCR), CLK_TOGGLE_ENABLE );

//  Clock_ToggleClock( HWIO_ADDR(GCC_CNOC_PERIPH_WEST_AHB_CBCR), CLK_TOGGLE_ENABLE );
//  Clock_ToggleClock( HWIO_ADDR(GCC_CNOC_PERIPH_EAST_AHB_CBCR), CLK_TOGGLE_ENABLE );

  /* Needed for Random Stack Canary */
  HWIO_OUTF(GCC_APCS_CLOCK_BRANCH_ENA_VOTE, PRNG_AHB_CLK_ENA, 1);
  HWIO_OUTF(GCC_RPM_CLOCK_BRANCH_ENA_VOTE, MSG_RAM_AHB_CLK_ENA, 1);

  /*
   * These clocks are required for the GDS HW controllers to receive the
   * necessary NOC handshakes. Enable them once and leave them on all the time,
   * allowing the ones on collapsible power domains to enable/disable along with
   * the GDS.
   */
  HWIO_OUTF(GCC_MMSS_SYS_NOC_AXI_CBCR,  CLK_ENABLE, 1);
  HWIO_OUTF(GCC_MMSS_AT_CBCR,           CLK_ENABLE, 1);
  HWIO_OUTF(GCC_AGGRE2_NOC_AT_CBCR,     CLK_ENABLE, 1);

  if( ! Clock_InitPLLStatic()) return FALSE;

  if( ! Clock_InitCrypto()) return FALSE;
  if( ! Clock_InitRBCPR()) return FALSE;

  /* To improve boot time, speed up the CPU and buses */
  if( ! Clock_SetCPUPerfLevel(CLOCK_BOOT_PERF_MAX)) return FALSE;
  if( ! Clock_SetSysPerfLevel(CLOCK_BOOT_PERF_MAX)) return FALSE;

  /* To speed up PMIC accesses, they need these clocks increased :  gcc_bimc_clk */
  if( ! Clock_EnableSource( clkCfgBIMC.eSource )) return FALSE;
  if( ! Clock_ConfigMux(&clkCfgBIMC)) return FALSE;

  /* gcc_bimc_hmss_axi_clk */
  if( ! Clock_EnableSource( clkCfgBIMCHMSS.eSource )) return FALSE;
  if( ! Clock_ConfigMux(&clkCfgBIMCHMSS)) return FALSE;

  return TRUE;
}

/* ============================================================================
**  Function : Clock_SetSysPerfLevel
** ============================================================================
*/
/**
  Configure NOCs and RPM to a perf level.

  @param eSysPerfLevel [in]  -  NOCs and RPM performance level to configure.

  @return
  TRUE -- NOCs were configured to perf level successful.
  FALSE -- Configuration failed.

  @dependencies
  None.

  @sa
  Clock_Init.
*/

boolean Clock_SetSysPerfLevel
(
  ClockBootPerfLevelType eSysPerfLevel
)
{
  const ClockConfigMuxType *clkCfg;
  const Clock_ConfigType *cfg = Clock_Config();
  static ClockBootPerfLevelType eCurrLevel = CLOCK_BOOT_PERF_NONE;

  /* Don't switch performance level if it has been set previously */
  if ( eCurrLevel == eSysPerfLevel )
  {
    return TRUE;
  }
  eCurrLevel = eSysPerfLevel;

  if(eSysPerfLevel >= CLOCK_BOOT_PERF_NUM) return FALSE;

  /* Configure RPM */
  clkCfg = &cfg->RPM_Cfg[eSysPerfLevel];
  if( ! Clock_EnableSource( clkCfg->eSource )) return FALSE;
  if( ! Clock_ConfigMux(clkCfg)) return FALSE;

  /* Configure SNOC */
  clkCfg = &cfg->SNOC_Cfg[eSysPerfLevel];
  if( ! Clock_EnableSource( clkCfg->eSource )) return FALSE;
  if( ! Clock_ConfigMux(clkCfg)) return FALSE;

  /* Configure PIMEM_AXI */
  clkCfg = &cfg->PIMEM_Cfg[eSysPerfLevel];
  if( ! Clock_EnableSource( clkCfg->eSource )) return FALSE;
  if( ! Clock_ConfigMux(clkCfg)) return FALSE;

  /* Configure HS_SNOC */
  clkCfg = &cfg->HS_SNOC_Cfg[eSysPerfLevel];
  if( ! Clock_EnableSource( clkCfg->eSource )) return FALSE;
  if( ! Clock_ConfigMux(clkCfg)) return FALSE;

  /* Configure CNOC */
  clkCfg = &cfg->CNOC_Cfg[eSysPerfLevel];
  if( ! Clock_EnableSource( clkCfg->eSource )) return FALSE;
  if( ! Clock_ConfigMux(clkCfg)) return FALSE;


  /* gcc_usb_phy_cfg_ahb2phy_clk is limited to about 75 MHz, 
     * so add wait states to lower the clock to 37.5 MHz.
     * Nazgul had 100 and 0x11 made 50MHz.   */
  HWIO_OUT(PERIPH_SS_AHB2PHY_TOP_CFG, 0x11);


  /* Configure CNOC-Periph */
  clkCfg = &cfg->CNOC_Periph_Cfg[eSysPerfLevel];
  if( ! Clock_EnableSource( clkCfg->eSource )) return FALSE;
  if( ! Clock_ConfigMux(clkCfg)) return FALSE;

  /* Configure HMSS AHB clock */
  clkCfg = &cfg->HMSS_AHB_Cfg;
  if( ! Clock_EnableSource( clkCfg->eSource )) return FALSE;
  if( ! Clock_ConfigMux(clkCfg)) return FALSE;

  return TRUE;
}


/* ============================================================================
**  Function : Clock_InitCrypto
** ============================================================================
*/
/*!
    Configure Crypto clocks.

    @param None.
    @return
    TRUE -- Initialization was successful.
    FALSE -- Initialization failed.

    @dependencies
    None.

    @sa None
*/

boolean Clock_InitCrypto(void)
{
  uint32 mask;
  const ClockConfigMuxType *CECfg;
  const Clock_ConfigType *cfg = Clock_Config();
  CECfg = &cfg->CE_Cfg;

  if( ! Clock_EnableSource( CECfg->eSource )) return FALSE;
  if( ! Clock_ConfigMux(CECfg)) return FALSE;

  mask =
    HWIO_FMSK(GCC_RPM_CLOCK_BRANCH_ENA_VOTE, CE1_CLK_ENA) |
    HWIO_FMSK(GCC_RPM_CLOCK_BRANCH_ENA_VOTE, CE1_AXI_CLK_ENA) |
    HWIO_FMSK(GCC_RPM_CLOCK_BRANCH_ENA_VOTE, CE1_AHB_CLK_ENA );
  HWIO_OUTM(GCC_RPM_CLOCK_BRANCH_ENA_VOTE, mask, mask);

  /* Revoke APCS CE1 clocks which may be enable in PBL, since RPM will manage these clocks */
  HWIO_OUTF(GCC_APCS_CLOCK_BRANCH_ENA_VOTE, CE1_CLK_ENA, 0);
  HWIO_OUTF(GCC_APCS_CLOCK_BRANCH_ENA_VOTE, CE1_AXI_CLK_ENA, 0);
  HWIO_OUTF(GCC_APCS_CLOCK_BRANCH_ENA_VOTE, CE1_AHB_CLK_ENA, 0 );
  return TRUE;

} /* END Clock_InitCrypto */


/* ============================================================================
**  Function : Clock_InitRBCPR
** ===========================================================================*/
/*!
    Configure RBCPR clocks.

    @param None.
    @return
    TRUE -- Initialization was successful.
    FALSE -- Initialization failed.

    @dependencies
    None.

    @sa None
*/

boolean Clock_InitRBCPR(void)
{

  /* Enable RPCPR clocks */
  Clock_ToggleClock(HWIO_GCC_HMSS_RBCPR_CBCR_ADDR, CLK_TOGGLE_ENABLE);
  Clock_ToggleClock(HWIO_GCC_RBCPR_CX_CBCR_ADDR, CLK_TOGGLE_ENABLE);
  Clock_ToggleClock(HWIO_GCC_RBCPR_CX_AHB_CBCR_ADDR, CLK_TOGGLE_ENABLE);
  Clock_ToggleClock(HWIO_GCC_RBCPR_MX_CBCR_ADDR, CLK_TOGGLE_ENABLE);
  Clock_ToggleClock(HWIO_GCC_RBCPR_MX_AHB_CBCR_ADDR, CLK_TOGGLE_ENABLE);

  return TRUE;

} /* END Clock_InitRBCPR */


/* ============================================================================
**  Function : Clock_InitIPA
** ===========================================================================*/
/*!
    Configure and enable IPA clocks

    @param None.
    @return
    TRUE -- Initialization was successful.
    FALSE -- Initialization failed.

    @dependencies
    None.

    @sa None
*/

boolean Clock_InitIPA(void)
{
  /* A mux config for IPA clock to 150MHz (GCC_IPA_2X_CLK @ 300 MHz) */
  const ClockConfigMuxType IPACfg = {HWIO_ADDR(GCC_IPA_2X_CMD_RCGR), MUX_GCC, SRC_GPLL0, 4, 0, 0, 0};

  /* IPA has dependency on Aggre2 NOC.  Request Aggre2 NOC on */
  Clock_AGGRE2Init();

  /* Enable IPA clocks */
  HWIO_OUTF(GCC_IPA_GDSCR, SW_COLLAPSE, 0);


  while(HWIO_INF(GCC_IPA_GDSCR, PWR_ON) == 0);  // loop while off
  if( ! Clock_ConfigMux(&IPACfg)) return FALSE;

  if( ! Clock_ToggleClock(HWIO_GCC_AGGRE2_NOC_IPA_CBCR_ADDR, CLK_TOGGLE_ENABLE)) return FALSE;

  if( ! Clock_ToggleClock(HWIO_GCC_IPA_2X_CBCR_ADDR, CLK_TOGGLE_ENABLE)) return FALSE;
  if( ! Clock_ToggleClock(HWIO_GCC_IPA_CBCR_ADDR, CLK_TOGGLE_ENABLE)) return FALSE;
  if( ! Clock_ToggleClock(HWIO_GCC_IPA_AHB_CBCR_ADDR, CLK_TOGGLE_ENABLE)) return FALSE;
  if( ! Clock_ToggleClock(HWIO_GCC_IPA_SLEEP_CBCR_ADDR, CLK_TOGGLE_ENABLE)) return FALSE;

  return TRUE;

} /* END Clock_InitIPA */


/* ============================================================================
**  Function : Clock_GetClockFrequency
** ============================================================================
*/
/*!
    Get the requested clock frequency in hertz.

    @param
      eBootLogClock [in]  - targeted clock
      pnFrequencyHz [out] - frequency of clock in hertz

    @return
      True iff the requested clock frequency is placed in pnFrequencyHz.

    @dependencies
    None.

    @sa None
*/

boolean Clock_GetClockFrequency(ClockBootLogQueryType eBootLogClock,
                                uint32 *pnFrequencyHz)
{
  boolean ret = TRUE;

  switch(eBootLogClock)
  {
  case CLK_BOOT_LOG_APPS_CLUSTER_0:
    *pnFrequencyHz = (Clock_GetAPSSCL0SpeedKHz() * 1000);
    break;

  case CLK_BOOT_LOG_DDR:
    *pnFrequencyHz = (Clock_DDRSpeed() * 1000);
    break;

  default:
    ret = FALSE;
    break;
  }

  return ret;
}


/* ============================================================================
**  Function : Clock_InitRPM()
** ============================================================================
*/
/**
  Perform any initialization needed just before RPM starts.  SMEM is available
  at this time.

  @param
  @return
  TRUE -- Initialization succeeded.
  FALSE -- Initialization failed.

  @dependencies
  None.

  @sa
  Clock_Init.
  boot_smem_init
*/
boolean Clock_InitRPM( void )
{
  return Clock_CopyBIMCPlanToRPM();
}


/* ============================================================================
**  Function : Clock_InitPLLStatic()
** ============================================================================
*/
/**
  Perform initial static configurations and workarounds
  defined in frequency plan documentation,

  @param
  @return
  TRUE -- Initialization succeeded.
  FALSE -- Initialization failed.

  @dependencies
  None.

*/
boolean Clock_InitPLLStatic( void )
{
#if 1
  const uint32 nPLLConfigAddrs[] = 
  { 
    HWIO_ADDR(GCC_GPLL6_CONFIG_CTL), // Modem has ownership of GPLL6
    HWIO_ADDR(MMSS_MMPLL0_PLL_CONFIG_CTL),
    HWIO_ADDR(MMSS_MMPLL1_PLL_CONFIG_CTL),
    HWIO_ADDR(MMSS_MMPLL3_PLL_CONFIG_CTL),
    HWIO_ADDR(MMSS_MMPLL4_PLL_CONFIG_CTL),
    HWIO_ADDR(MMSS_MMPLL5_PLL_CONFIG_CTL),
    HWIO_ADDR(MMSS_MMPLL6_PLL_CONFIG_CTL),
    HWIO_ADDR(MMSS_MMPLL7_PLL_CONFIG_CTL),
    HWIO_ADDR(MMSS_MMPLL8_PLL_CONFIG_CTL),
//    HWIO_ADDR(MMSS_MMPLL10_PLL_CONFIG_CTL),
    HWIO_ADDR(GPUCC_GPU_PLL0_PLL_CONFIG_CTL), // TODO: Need to verify AHB access
    HWIO_ADDR(GPUCC_GPU_PLL1_PLL_CONFIG_CTL), 

  };

  const uint32 nPLLAgConfigAddrs[] = 
  { 
    HWIO_ADDR(APCS_C0_PLL_CONFIG_CTL_LO),     // Unused by BootROM so
    HWIO_ADDR(APCS_C1_PLL_CONFIG_CTL_LO),     // it can be reconfigured
  };

  int i;
#endif
  /* Initialize XBL loader's PLL configurations (GPLL0 is already configured). */
  // GPLL0 already On, cannot be fully configured
  //HWIO_OUT(GCC_GPLL0_USER_CTL_U, FABIA_USER_CTL_U_VAL | HWIO_IN(GCC_GPLL0_USER_CTL_U));
  // PLL team approves that we may change GPLL0_CONFIG_CTL without disturbing PLL lock for this
  // one change.  Any future change must be approved on a case by case basis.
  // 0x204456BB changed to 0x20485699 is allowed when GPLL0 is in fine-lock only mode.
  //if( HWIO_IN(GCC_GPLL0_CONFIG_CTL) == 0x204456BB )
 // {
 //   HWIO_OUT(GCC_GPLL0_CONFIG_CTL, (FABIA_CONFIG_CTL_VAL & 0xffffffff));
 // }
  (void)Clock_ConfigureSource(SRC_GPLL0);
  (void)Clock_ConfigureSource(SRC_GPLL1);
  (void)Clock_ConfigureSource(SRC_GPLL2);
  (void)Clock_ConfigureSource(SRC_GPLL3);
  (void)Clock_ConfigureSource(SRC_GPLL4);
  (void)Clock_ConfigureSource(SRC_GPLL5);
  /* (void)Clock_ConfigureSource(SRC_GPLL6); Modem has ownership of GPLL6 */


	
  /* This consolidates most of the PLL configurations into one place, and
   * is done before they have been turned on.*/
  Clock_ToggleClock(HWIO_ADDR(GCC_MMSS_NOC_CFG_AHB_CBCR), CLK_TOGGLE_ENABLE);

   /*Starlord virtio issue*/
  Clock_ToggleClock(HWIO_ADDR(GCC_GPU_CFG_AHB_CBCR), CLK_TOGGLE_ENABLE);
  /* LPASS Q6 SMMU and CNOC interface needs CFG_NOC_LPASS_AON_AHB clock to access LPASS Q6 SMMU, 
   * so keeping this clock Always ON */
  Clock_ToggleClock(HWIO_ADDR(GCC_CFG_NOC_LPASS_AON_AHB_CBCR), CLK_TOGGLE_ENABLE);
  
#if 1
  for(i=0; i<sizeof(nPLLConfigAddrs)/sizeof(nPLLConfigAddrs[0]); i++)
  {
//    outp32((uint64)nPLLConfigAddrs[i]-4,
//      FABIA_USER_CTL_U_VAL | inp32((uint64)nPLLConfigAddrs[i]-4));                // PLL_USER_CTL_U
    outp32((uint64)nPLLConfigAddrs[i],    (SPARK_CONFIG_CTL & 0xffffffff));   // PLL_CONFIG_CTL
    //outp32((uint64)nPLLFabConfigAddrs[i]+4,  (FABIA_PLL_TEST_CTL_VAL & 0xffffffff)); // PLL_TEST_CTL
    //outp32((uint64)nPLLFabConfigAddrs[i]+8, (FABIA_PLL_TEST_CTL_VAL >> 32));        // PLL_TEST_CTL_U
  }

  for(i=0; i<sizeof(nPLLAgConfigAddrs)/sizeof(nPLLAgConfigAddrs[0]); i++)
  {
    outp32((uint64)nPLLAgConfigAddrs[i],    (AGERA_CONFIG_CTL & 0xffffffff));   // PLL_CONFIG_CTL
    outp32((uint64)nPLLAgConfigAddrs[i]+4,  (AGERA_CONFIG_CTL >> 32));          // PLL_CONFIG_CTL_U
//    outp32((uint64)nPLLAgConfigAddrs[i]+8,  (AGERA_PLL_TEST_CTL & 0xffffffff)); // PLL_TEST_CTL
//    outp32((uint64)nPLLAgConfigAddrs[i]+12, (AGERA_PLL_TEST_CTL >> 32));        // PLL_TEST_CTL_U
  }
  HWIO_OUTF(MMSS_MMPLL10_PLL_TEST_CTL,RESERVE_BITS31_30,0);
#endif
  Clock_EnableSource(SRC_GPLL5);
  Clock_EnableSource(SRC_GPLL1);
  return TRUE;

}
