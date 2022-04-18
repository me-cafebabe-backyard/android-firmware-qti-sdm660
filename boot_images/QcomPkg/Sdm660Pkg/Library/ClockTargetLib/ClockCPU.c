/**
==============================================================================

  @file ClockCPU.c

  This file provides clock initialization for the Apps CPU.

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

/*=========================================================================
      Include Files
==========================================================================*/
#include "ClockHWIO.h"
#include "ClockBSP.h"
#include <HALcomdef.h>
#include <HALhwio.h>
#include <busywait.h>
#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/DebugLib.h>

#include <Protocol/EFIPmicVreg.h>

/*=========================================================================
      Macro Definitions
==========================================================================*/
#define MODE_CTL_MSK 0x7

#define PLL_OFFS(x)  (HWIO_ADDR(APCS_C0_PLL_##x) - HWIO_ADDR(APCS_C0_PLL_MODE))
#define PLL_FMSK(x,m)  HWIO_FMSK(APCS_C0_PLL_##x, m)
#define PLL_SHFT(x,m)  HWIO_SHFT(APCS_C0_PLL_##x, m)

#define APCS_CLKSEL_MASK  0xF
#define APCS_CLKSEL_GPLL0 0xC
#define APCS_CLKSEL_MAIN  0x4
#define APCS_CLKSEL_ALT   0x3

#define SBL_DLOAD_MODE_BIT_MASK_V1       0x00100000
#define SBL_DLOAD_MODE_BIT_MASK_V1_SHFT  20

static EFI_QCOM_PMIC_VREG_PROTOCOL  *PmicVRegProtocol = NULL;

/*=========================================================================
     Externs
==========================================================================*/

/*=========================================================================
      Function Prototypes
==========================================================================*/
static boolean Clock_EnableAppsPLL(const ClockConfigPLLType *pConfig);
static boolean Clock_DisableAppsPLL(const ClockConfigPLLType *pConfig);

/*=========================================================================
      Data
==========================================================================*/

/* The current rate of the APPS cluster 0 clock in KHz */
static uint32 Clock_APPSCL0SpeedKHz = 600000;

/* save the CPU1 frequency setting info when enter LMh mode and restore its setting when leaving LMh mode */
static uint32 saved_pll_mode=0;
static uint32 saved_L_value=0;
static uint32 saved_postdiv=0;
static uint32 saved_src=0;
static uint32 saved_div2x=0;
static uint32 saved_VLeveluV=0;


/*=========================================================================
      Function Definitions
==========================================================================*/

/* ========================================================================
**  Function : Clock_GetAPSSCL0SpeedKHz
** ======================================================================*/
/*
    Description: Configure CPU clock source

    @param
      None.

    @return
      Frequency of APPS cluster zero in KHZ.

    @dependencies
      None.

    @sa
      None.
*/

uint32 Clock_GetAPSSCL0SpeedKHz(void)
{
  return Clock_APPSCL0SpeedKHz;
}

/* ========================================================================
**  Function : Clock_CPUMuxSelect
** ======================================================================*/
/*
    Description: Configure CPU clock source for CPU 1

    @param
      cfg_reg_addr -   Config register Address.
      hf_mux_select -  High frequency mux source to be selected.
      lf_mux_select -  Low frequency mux source to be selected.
      pll_div       -  PLL main divider (1-2)

    @return
    TRUE -- Initialization was successful.
    FALSE -- Initialization failed.

    @dependencies
    None.

    @sa None
*/

static boolean Clock_CPUMuxSelect( uint64 nCMDAddr, uint32 src, uint32 div2x )
{
  uint32 nCfgVal;

  if(nCMDAddr == 0) return FALSE;

  if( div2x > 0 ) div2x--;  /* div2x is double the divide we want, this maps it to the HW register */

  nCfgVal = ((src << HWIO_SHFT(APCS_ALIAS0_CFG_RCGR, SRC_SEL)) |
             (div2x << HWIO_SHFT(APCS_ALIAS0_CFG_RCGR, SRC_DIV)));
  outp32( nCMDAddr + 4, nCfgVal );  /* CFG_RCGR is +4 from CMD_RCGR */

  if(Clock_TriggerUpdate( nCMDAddr, HWIO_FMSK(APCS_ALIAS0_CMD_RCGR, UPDATE)) != TRUE) return FALSE;

  return TRUE;
} /* END Clock_CPUMuxSelect */

/* ============================================================================
**  Function : Clock_SetCPUPerfLevel
** ============================================================================
*/
/**
  Configure A53 CPU to a specific perf level.

  @param eCPUPerfLevel [in] - CPU performance level.

  @return
  TRUE -- CPU configuration to perf level was successful.
  FALSE -- Configuration failed.

  @dependencies
  None.

  @sa
  Clock_Init.
*/

boolean Clock_SetCPUPerfLevel(ClockBootPerfLevelType eCPUPerfLevel)
{
  static ClockBootPerfLevelType eCurrLevel = CLOCK_BOOT_PERF_NONE;
  const Clock_ConfigType *cfg = Clock_Config();
  const ClockConfigApcsCfgType *CPU_Cfg;
  const ClockConfigPLLType *AppsPLL_cfg;
  int ret = FALSE;
  ClockAPCSSourceSelectType  ePrevCPUSource;
  uint32 nDiv2x;
  ClockConfigMuxType cfgHMSSGPLL0   = {HWIO_ADDR(GCC_HMSS_GPLL0_CMD_RCGR), MUX_GCC, SRC_GPLL0, 0, 0, 0, 0};
  ClockConfigMuxType cfgHMSSGPLL4   = {HWIO_ADDR(GCC_HMSS_GPLL4_CMD_RCGR), MUX_GCC, SRC_GPLL4, 0, 0, 0, 0};
  /* Don't switch performance level if it has been set previously */

  /* For error handling, we have clean-up to do at the end */
  do 
  {
  if ( eCurrLevel == eCPUPerfLevel )
  {
      ret=TRUE; break;
  }
  eCurrLevel = eCPUPerfLevel;

    if( eCPUPerfLevel >= CLOCK_BOOT_PERF_NUM ) break;

  /* Set the GCC sources if not done yet. */
  if( HWIO_INF(GCC_HMSS_GPLL0_CFG_RCGR, SRC_SEL) != 1)
  {
      if( ! Clock_ConfigMux(&cfgHMSSGPLL0)) break;
  }
  if( HWIO_INF(GCC_HMSS_GPLL4_CFG_RCGR, SRC_SEL) != 5)
  {
      if( ! Clock_ConfigMux(&cfgHMSSGPLL4)) break;
  }

  ePrevCPUSource = HWIO_INF( APCS_ALIAS0_CFG_RCGR, SRC_SEL );

  if(HWIO_INF(TCSR_SOC_HW_VERSION, DEVICE_NUMBER) == DEVICE_ID_SDM630)
  {
     CPU_Cfg = &cfg->CPU_Cfg_SDM630[eCPUPerfLevel];     
     AppsPLL_cfg = &CPU_Cfg->PLL_Cfg;
  }else
  {
  CPU_Cfg = &cfg->CPU_Cfg[eCPUPerfLevel];
  AppsPLL_cfg = &CPU_Cfg->PLL_Cfg;
  }
 

  /* Enable the "backup" source for APCS and CCI */
    if( !Clock_EnableSource(SRC_GPLL0) ) break;

  /* If I am switching to the high frequency PLL or GPLL4, I may need to retune them first,
   * so switch the CPU to a safe source like GPLL0 */
  if( (CPU_Cfg->eCPUSource == APCS_SOURCE_GPLL4_MAIN) ||
      (CPU_Cfg->eCPUSource == APCS_SOURCE_AG_EARLY)  ||
      (CPU_Cfg->eCPUSource == APCS_SOURCE_AG_MAIN) ||
      (CPU_Cfg->eCCISource == CCI_SOURCE_GPLL4_MAIN) )
  {
    /* Switch APCS from HF PLL or GPLL4 to GPLL0 Div 3 : TODO put back at 600 when safe. */
    if(! Clock_CPUMuxSelect( CPU_Cfg->nCPUCMDRCGRAddr, APCS_SOURCE_GPLL0_MAIN, 2) ) break;

    if( (CPU_Cfg->eCPUSource == APCS_SOURCE_GPLL4_MAIN) ||
        (CPU_Cfg->eCCISource == CCI_SOURCE_GPLL4_MAIN) )
    {
      /* Retune GPLL4 */
      if( !Clock_DisableSource(SRC_GPLL4) ) break;
      if( !Clock_EnableSource(SRC_GPLL4) ) break;
    }
    else /* It must be the high frequency PLL */
    {
      /* Retune the Apps PLL */
      if( ! Clock_DisableAppsPLL(AppsPLL_cfg) ) break;
      if( ! Clock_EnableAppsPLL(AppsPLL_cfg) ) break;
    }
  }

  nDiv2x = CPU_Cfg->nCPUDiv2x;
  /* Switch CPU to the desired source and divider */
  if(! Clock_CPUMuxSelect( CPU_Cfg->nCPUCMDRCGRAddr, CPU_Cfg->eCPUSource, nDiv2x) ) break;

  /* Save new CPU state */
  Clock_APPSCL0SpeedKHz = CPU_Cfg->nFrequency;


    /* Configure GPLL4 if not in use, regardless of whether or not it was used in PBL */

    if( (CPU_Cfg->eCPUSource != APCS_SOURCE_GPLL4_MAIN) &&
        (CPU_Cfg->eCCISource != CCI_SOURCE_GPLL4_MAIN) )
    {
      /* Retune GPLL4 to match the clock plan. */
      if( !Clock_DisableSource(SRC_GPLL4) ) break;
      if( !Clock_ConfigureSource(SRC_GPLL4) ) break;
    }
    ret = TRUE;

  } while(0);

  /* If the silver cluster PLL is not on, set it up as this is a pre-requisite for the OSM FSM. */
  if( (HWIO_IN( APCS_C0_PLL_MODE ) & (MODE_CTL_MSK)) != 0x7 )
  {
    const ClockConfigPLLType AppsPLLDefault = 
    {HWIO_ADDR(APCS_C0_PLL_MODE), 0, 0, 1, 1, 1, 32, 0, 0, AGERA_CONFIG_CTL, 0};
    /* nPLLModeAddr, nVoteAddr, nVoteMask, nVCO, nPreDiv,  nPostDiv, nL,  nM,  nN, nConfigCtl, nTestCtl,  nAlpha;*/

    Clock_EnableAppsPLL(&AppsPLLDefault);
  }

  /* If the gold cluster PLL is not on, set it up as this is a pre-requisite for the OSM FSM. */
  if( (HWIO_IN( APCS_C1_PLL_MODE ) & (MODE_CTL_MSK)) != 0x7 )
  {
    const ClockConfigPLLType AppsPLLDefault = 
     {HWIO_ADDR(APCS_C1_PLL_MODE), 0, 0, 1, 1, 1, 32, 0, 0, AGERA_CONFIG_CTL, 0};

    Clock_EnableAppsPLL(&AppsPLLDefault);
  }

  return ret;
}


/* Stubbed out for backwards compatibility, L2 clock is sync to CPU */
boolean Clock_SetL2PerfLevel(ClockBootPerfLevelType eL2PerfLevel)
{
  return TRUE;
}

/* ============================================================================
**  Function : Clock_EnableAppsPLL
** ============================================================================
    Configure and enable a high frequency Apps PLL.

    @param
      pConfig -  [IN] PLL configuration structure

    @return
      TRUE -- Initialization was successful.
      FALSE -- Initialization failed.

    @dependencies
    None.

    @sa None
*/
static boolean Clock_EnableAppsPLL
(
  const ClockConfigPLLType *pConfig
)
{
  uintnt nModeAddr;
  uint32 nUserVal;
  volatile uint32 nModeVal;
  uint32 nDiv = 0;

  if( (pConfig == 0) || (pConfig->nL == 0) || (pConfig->nPLLModeAddr == 0) ) return FALSE;

  nModeAddr = pConfig->nPLLModeAddr;

  if ( (inp32(nModeAddr + PLL_OFFS(STATUS)) & PLL_FMSK(STATUS, LOCK_DET)) != 0 )
  {
    /* The PLL is already enabled, it cannot be reconfigured */
    return FALSE;
  }

  /*
   * Get the USER value.
   */
  nUserVal = inp32(nModeAddr + PLL_OFFS(USER_CTL));

  /*
   * Program the post-div value
   */
  switch (pConfig->nPostDiv )
  {
    case 0:
    case 1:   nDiv =  0; break; /* Divide-by-1 */
    case 2:   nDiv =  1; break; /* Divide-by-2 */
    case 4:   nDiv =  3; break; /* Divide-by-4 */
    case 8:   nDiv =  2; break; /* Divide-by-8 */
    default:
              nDiv =  0;
  }

  nUserVal &= (~PLL_FMSK(USER_CTL, CLK_POST_DIV));
  nUserVal |= (nDiv  << PLL_SHFT(USER_CTL, CLK_POST_DIV));

  /*
   * Enable MAIN and EARLY Output bits.
   */
  nUserVal |= PLL_FMSK(USER_CTL, LVEARLY_EN);
  nUserVal |= PLL_FMSK(USER_CTL, LVMAIN_EN);

  /*
   * Program the USER_CTL register.
   */
  outp32(nModeAddr + PLL_OFFS(USER_CTL), nUserVal);


  /* Set CONFIG_CTL */
  outp32(nModeAddr + PLL_OFFS(CONFIG_CTL_HI), (uint32)(pConfig->nConfigCtl >> 32));
  outp32(nModeAddr + PLL_OFFS(CONFIG_CTL_LO), (uint32)(pConfig->nConfigCtl));

  /* Set TEST_CTL */
  if(pConfig->nTestCtl != 0)
  {
    outp32(nModeAddr + PLL_OFFS(TEST_CTL_HI), (uint32)(pConfig->nTestCtl >> 32));
    outp32(nModeAddr + PLL_OFFS(TEST_CTL_LO), (uint32)(pConfig->nTestCtl));
  }
  /*
   * Program L, Alpha.
   */
  outp32(nModeAddr + PLL_OFFS(L_VAL), pConfig->nL);
  outp32(nModeAddr + PLL_OFFS(ALPHA_VAL), (uint32)pConfig->nAlpha);

  /*
   * Enable the PLL.
   */
  nModeVal = inp32(nModeAddr);
  nModeVal = (nModeVal & (~MODE_CTL_MSK)) | 0x2;
  outp32(nModeAddr, nModeVal);

  busywait( 5 );

  nModeVal = inp32(nModeAddr);
  nModeVal = (nModeVal & (~MODE_CTL_MSK)) | 0x6;
  outp32(nModeAddr, nModeVal);

  busywait( 5 );

  while ( (inp32(nModeAddr + PLL_OFFS(STATUS)) & PLL_FMSK(STATUS, LOCK_DET)) == 0 )
  {
    busywait(1);
  }

  nModeVal = inp32(nModeAddr);
  nModeVal = (nModeVal & (~MODE_CTL_MSK)) | 0x7;
  outp32(nModeAddr, nModeVal);

  return TRUE;

} /* END Clock_EnableAppsPLL */



/* ============================================================================
**  Function : Clock_DisableAppsPLL
** ============================================================================
    Turn off the APCS PLL.

    @param
      pConfig -  [IN] PLL configuration structure

    @return
      void

    @dependencies
    None.

    @sa None
*/
static boolean Clock_DisableAppsPLL
(
  const ClockConfigPLLType *pConfig
)
{
  if( (pConfig == 0) || (pConfig->nPLLModeAddr == 0) ) return FALSE;

  /* According to the data sheet, PLL off is: */
  outp32(pConfig->nPLLModeAddr, 0x6);
  outp32(pConfig->nPLLModeAddr, 0x0);

  return TRUE;
}

/* ============================================================================
**  Function : Clock_LMhInit
** ============================================================================
*/
/*  Initialize for the current limiter calibration.
 *  Power on A57 at Turbo Voltage(A57 operation and stability is not a requirement)
    L2 headswitch needs to be closed as well.

    @param nA57uV  -  [IN] requested voltage in microvolts
    @return
    TRUE -- Initialization was successful.
    FALSE -- Initialization failed.

    @dependencies
    None.

    @sa None
*/
boolean Clock_LMhInit( uint32 nA57uV )
{

  if (PmicVRegProtocol==NULL)
  {
   gBS->LocateProtocol( &gQcomPmicVregProtocolGuid,
                        NULL,
                        (VOID **)&PmicVRegProtocol );
  }

  if (PmicVRegProtocol == NULL) return FALSE;

  /* Limit the voltage to legal limits */
  if( nA57uV < 500000 ) nA57uV = 500000;
  if( nA57uV > 1140000 ) nA57uV = 1140000;

  /* save the current CPU setting before enter LMh */
  if( PmicVRegProtocol->VregGetLevel(0, EFI_PM_SMPS_3, &saved_VLeveluV) != EFI_SUCCESS) return FALSE;
  saved_pll_mode = HWIO_IN(APCS_C1_PLL_MODE);
  saved_L_value  = HWIO_IN(APCS_C1_PLL_L_VAL);
  saved_postdiv  = HWIO_INF(APCS_C1_PLL_USER_CTL, CLK_POST_DIV);
  saved_src      = HWIO_INF(APCS_ALIAS1_CFG_RCGR, SRC_SEL);
  saved_div2x    = HWIO_INF(APCS_ALIAS1_CFG_RCGR, SRC_DIV)+1;

  /* Enable the A57 switch mode power supply */
  if( PmicVRegProtocol->VregSetLevel(0, EFI_PM_SMPS_3, nA57uV/1000) != EFI_SUCCESS) return FALSE;

  if( PmicVRegProtocol->VregControl(0, EFI_PM_SMPS_3, TRUE) != EFI_SUCCESS) return FALSE;

  return TRUE;
}

/* ============================================================================
**  Function : Clock_LMhPreCalibration
** ============================================================================
*/
/*  Set the A57 cores at the maximum clock rate.

    @param  nFreqKHz : The frequency to set in KHz
    @return : rounded freqeuncy that was set, or 0 on failure in kHz.

    @dependencies
    None.

    @sa None
*/
uint32 Clock_LMhPreCalibration( uint32 nFreqKHz )
{
  ClockConfigPLLType AppsPLL_cfg = {0};
  uint32 nL = 0;
  uint32 nPLLPostDiv = 1;

  // Need the clock limit raised to full frequency for proper calibration.
  // Currently capped at 2.4576Ghz.
  if( nFreqKHz > 2457600)
  {
    nFreqKHz = 2457600;
  }

  /* The use of the PLL below does not support PLL division
   * so the only allowable frequencies must exceed the PLL
   * minimum of 600 MHz */
  if( nFreqKHz < 600000) {
    if(nFreqKHz > 300000) {
      nPLLPostDiv = 2;
      nFreqKHz *= 2;
    } else if ( nFreqKHz > 150000 ) {
      nPLLPostDiv = 4;
      nFreqKHz *= 4;
    } else if( nFreqKHz == 19200 ) {
      // Allow 19200
    } else {
      return 0;
    }
  }

  nL = nFreqKHz / 19200;   /* Round request down to nearest multiple of 19.2 MHz */

  AppsPLL_cfg.nPLLModeAddr = HWIO_ADDR(APCS_C1_PLL_MODE);
  AppsPLL_cfg.nL = nL;
  AppsPLL_cfg.nPostDiv = nPLLPostDiv;
  AppsPLL_cfg.nN = 1;
  AppsPLL_cfg.nConfigCtl = AGERA_CONFIG_CTL;
  AppsPLL_cfg.nTestCtl = 0;

  /* Select CXO for safety */
  Clock_CPUMuxSelect( HWIO_ADDR(APCS_ALIAS1_CMD_RCGR), APCS_SOURCE_CXO, 0);
  busywait(3);
  /* So that this PLL can be changed if it has already been set, turn it off */
  if( ! Clock_DisableAppsPLL(&AppsPLL_cfg) ) return FALSE;

  /* If CXO is selected, we are now CXO with PLL off, so return */
  if( nFreqKHz == 19200 ) {
    return 19200;
  }

  /* And now enable the PLL at the desired frequency */
  if( ! Clock_EnableAppsPLL(&AppsPLL_cfg) ) return FALSE;

  if( nPLLPostDiv > 1 )
  {
    /* Switch Cluster 1 CPU to PLL main divided output */
    Clock_CPUMuxSelect( HWIO_ADDR(APCS_ALIAS1_CMD_RCGR), APCS_SOURCE_AG_MAIN, 0);
  } else {
    /* Switch Cluster 1 CPU to HF PLL early output */
    Clock_CPUMuxSelect( HWIO_ADDR(APCS_ALIAS1_CMD_RCGR), APCS_SOURCE_AG_EARLY, 0);
  }
  busywait(3);

  return  ((nL * 19200) / nPLLPostDiv);
}

/* ============================================================================
**  Function : Clock_LMhDeInit
** ============================================================================
*/
/*  Disable the PLL, turn of the L2 head switch, power off the rail.

    @param  None.
    @return
    TRUE -- Success.
    FALSE -- Reserved, not used.

    @dependencies
    None.

    @sa None
*/
boolean Clock_LMhDeInit( void )
{
  ClockConfigPLLType AppsPLL_cfg = {0};
  uint32 nDivider;

  /* Select CXO for safety */
  Clock_CPUMuxSelect( HWIO_ADDR(APCS_ALIAS1_CMD_RCGR), APCS_SOURCE_CXO, 0);
  busywait(3);

  AppsPLL_cfg.nPLLModeAddr = HWIO_ADDR(APCS_C1_PLL_MODE);
  if( ! Clock_DisableAppsPLL(&AppsPLL_cfg) ) return FALSE;

  /* Turn off A57 power supply */
  //pm_smps_sw_enable( 0, PM_SMPS_11, PM_OFF );

  if (PmicVRegProtocol->VregControl(0, EFI_PM_SMPS_3, FALSE)!= EFI_SUCCESS)
  {
    return FALSE;
  }

  /************************************************/
  /* restore APCS CPU1 setting when exit LMh mode */
  /************************************************/
  /* restore  VReg Level */
  if( PmicVRegProtocol->VregSetLevel(0, EFI_PM_SMPS_3, saved_VLeveluV/1000) != EFI_SUCCESS) return FALSE;

  if(saved_pll_mode > 0)
  {
    switch (saved_postdiv)
    {
      case 0:   nDivider = 1; break; /* Divide-by-1 */
      case 1:   nDivider = 2; break; /* Divide-by-2 */
      case 2:   nDivider = 8; break; /* Divide-by-8 */
      case 3:   nDivider = 4; break; /* Divide-by-4 */
      default:
                nDivider = 1;
    }
    /* fill Apps PLL structure with L and postdiv */
    AppsPLL_cfg.nPLLModeAddr = HWIO_ADDR(APCS_C1_PLL_MODE);
    AppsPLL_cfg.nL           = saved_L_value;
    AppsPLL_cfg.nPostDiv     = nDivider;
    AppsPLL_cfg.nN           = 1;
    AppsPLL_cfg.nConfigCtl   = AGERA_CONFIG_CTL;
    AppsPLL_cfg.nTestCtl     = 0;

    /* restore the PLL  frequency */
	if( ! Clock_EnableAppsPLL(&AppsPLL_cfg) ) return FALSE;
  }

  /* Switch Cluster 1 CPU to HF PLL early output */
  Clock_CPUMuxSelect( HWIO_ADDR(APCS_ALIAS1_CMD_RCGR), saved_src, saved_div2x);
  return TRUE;
} /* Clock_LMhDeInit */
