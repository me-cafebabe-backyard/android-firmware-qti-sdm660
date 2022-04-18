/**
==============================================================================

  @file ClockTools.c

  This file provides clock initialization for starting SDCC clocks at boot.

==============================================================================

                             Edit History


when      who           what, where, why
--------  ------------  ------------------------------------------------------
09/22/16    vg          Removed null entry in Clock_RegType 
08/11/15  jcuddihy      Initial SDM660 revision, branched from MSM8996.

==============================================================================
            Copyright (c) 2015-2016 QUALCOMM Technologies Incorporated.
                    All Rights Reserved.
                   QUALCOMM Proprietary
==============================================================================
*/

/*=========================================================================
      Include Files
==========================================================================*/
#include "ClockHWIO.h"
#include "ClockBSP.h"

/*=========================================================================
      Data
==========================================================================*/
struct Clock_RegType 
{
  uint32 nCmd;
  uint32 nApps;
};

const struct Clock_RegType Clock_UARTRegs[CLK_BLSP_UART_NUM_CLKS] = 
{
  { 0,0 },    // CLK_BLSP_UART_NONE,
  { 0,0 },    // CLK_BLSP0_UART0_APPS,
  { 0,0 },    // CLK_BLSP0_UART1_APPS,
  { 0,0 },    // CLK_BLSP0_UART2_APPS,
  { 0,0 },    // CLK_BLSP0_UART3_APPS,
  { HWIO_ADDR(GCC_BLSP1_UART1_APPS_CMD_RCGR),  HWIO_ADDR(GCC_BLSP1_UART1_APPS_CBCR) },
  { HWIO_ADDR(GCC_BLSP1_UART2_APPS_CMD_RCGR),  HWIO_ADDR(GCC_BLSP1_UART2_APPS_CBCR) },
  { 0,0 },    // CLK_BLSP1_UART3_APPS
  { 0,0 },    // CLK_BLSP1_UART4_APPS
  { 0,0 },    // CLK_BLSP1_UART5_APPS
  { 0,0 },    // CLK_BLSP1_UART6_APPS
  { HWIO_ADDR(GCC_BLSP2_UART1_APPS_CMD_RCGR),  HWIO_ADDR(GCC_BLSP2_UART1_APPS_CBCR) },
  { HWIO_ADDR(GCC_BLSP2_UART2_APPS_CMD_RCGR),  HWIO_ADDR(GCC_BLSP2_UART2_APPS_CBCR) },
  { 0,0 },    // CLK_BLSP2_UART3_APPS
  { 0,0 },    // CLK_BLSP2_UART4_APPS
  { 0,0 },    // CLK_BLSP2_UART5_APPS
  { 0,0 },    // CLK_BLSP2_UART6_APPS
};


const struct Clock_RegType Clock_I2CRegs[CLK_BLSP_QUP_I2C_NUM_CLKS] = 
{ 
  { 0,0 },
  { HWIO_ADDR(GCC_BLSP1_QUP1_I2C_APPS_CMD_RCGR),  HWIO_ADDR(GCC_BLSP1_QUP1_I2C_APPS_CBCR) },
  { HWIO_ADDR(GCC_BLSP1_QUP2_I2C_APPS_CMD_RCGR),  HWIO_ADDR(GCC_BLSP1_QUP2_I2C_APPS_CBCR) },
  { HWIO_ADDR(GCC_BLSP1_QUP3_I2C_APPS_CMD_RCGR),  HWIO_ADDR(GCC_BLSP1_QUP3_I2C_APPS_CBCR) },
  { HWIO_ADDR(GCC_BLSP1_QUP4_I2C_APPS_CMD_RCGR),  HWIO_ADDR(GCC_BLSP1_QUP4_I2C_APPS_CBCR) },
  { 0,0 }, //GCC_BLSP1_QUP5_I2C_APPS_CBCR
  { 0,0 },//GCC_BLSP1_QUP6_I2C_APPS_CBCR
  { HWIO_ADDR(GCC_BLSP2_QUP1_I2C_APPS_CMD_RCGR),  HWIO_ADDR(GCC_BLSP2_QUP1_I2C_APPS_CBCR) },
  { HWIO_ADDR(GCC_BLSP2_QUP2_I2C_APPS_CMD_RCGR),  HWIO_ADDR(GCC_BLSP2_QUP2_I2C_APPS_CBCR) },
  { HWIO_ADDR(GCC_BLSP2_QUP3_I2C_APPS_CMD_RCGR),  HWIO_ADDR(GCC_BLSP2_QUP3_I2C_APPS_CBCR) },
  { HWIO_ADDR(GCC_BLSP2_QUP4_I2C_APPS_CMD_RCGR),  HWIO_ADDR(GCC_BLSP2_QUP4_I2C_APPS_CBCR) },
  { 0,0 },//GCC_BLSP2_QUP5_I2C_APPS_CBCR
  { 0,0 },//GCC_BLSP2_QUP6_I2C_APPS_CBCR
};

struct Clock_SDCCRegAddrType
{
  uint32 nCmd;
  uint32 nApps;
  uint32 nAHB;
};

const struct Clock_SDCCRegAddrType Clock_SDCCRegs[CLK_SDC_NUM_CLKS] = 
{ 
  { 0,0,0 },
  { HWIO_ADDR(GCC_SDCC1_APPS_CMD_RCGR), HWIO_ADDR(GCC_SDCC1_APPS_CBCR), HWIO_ADDR(GCC_SDCC1_AHB_CBCR) },
  { HWIO_ADDR(GCC_SDCC2_APPS_CMD_RCGR), HWIO_ADDR(GCC_SDCC2_APPS_CBCR), HWIO_ADDR(GCC_SDCC2_AHB_CBCR) },
  { 0,0,0 },
  { 0,0,0 },
  { 0,0,0 }
};

static const struct Clock_RegType Clock_SPIRegs[CLK_BLSP_QUP_SPI_NUM_CLKS] = 
{ 
  { 0,0 },
  { 0,0 },
  { HWIO_ADDR(GCC_BLSP1_QUP1_SPI_APPS_CMD_RCGR),  HWIO_ADDR(GCC_BLSP1_QUP1_SPI_APPS_CBCR) },
  { HWIO_ADDR(GCC_BLSP1_QUP2_SPI_APPS_CMD_RCGR),  HWIO_ADDR(GCC_BLSP1_QUP2_SPI_APPS_CBCR) },
  { HWIO_ADDR(GCC_BLSP1_QUP3_SPI_APPS_CMD_RCGR),  HWIO_ADDR(GCC_BLSP1_QUP3_SPI_APPS_CBCR) },
  { HWIO_ADDR(GCC_BLSP1_QUP4_SPI_APPS_CMD_RCGR),  HWIO_ADDR(GCC_BLSP1_QUP4_SPI_APPS_CBCR) },
  { 0,0 },//BLSP1_QUP5_SPI_APPS
  { 0,0 },//BLSP1_QUP6_SPI_APPS
  { HWIO_ADDR(GCC_BLSP2_QUP1_SPI_APPS_CMD_RCGR),  HWIO_ADDR(GCC_BLSP2_QUP1_SPI_APPS_CBCR) },
  { HWIO_ADDR(GCC_BLSP2_QUP2_SPI_APPS_CMD_RCGR),  HWIO_ADDR(GCC_BLSP2_QUP2_SPI_APPS_CBCR) },
  { HWIO_ADDR(GCC_BLSP2_QUP3_SPI_APPS_CMD_RCGR),  HWIO_ADDR(GCC_BLSP2_QUP3_SPI_APPS_CBCR) },
  { HWIO_ADDR(GCC_BLSP2_QUP4_SPI_APPS_CMD_RCGR),  HWIO_ADDR(GCC_BLSP2_QUP4_SPI_APPS_CBCR) },
  { 0,0 },//BLSP2_QUP5_SPI_APPS
  { 0,0 },//BLSP2_QUP6_SPI_APPS
  { 0,0 },
  { 0,0 },

};

/* ============================================================================
**  Function : Clock_AGGRE2Init
** ============================================================================
*/
/*!
    Configure AGGRE2 NOC clocks.

    @param None.
    @return
    TRUE -- Initialization was successful.
    FALSE -- Initialization failed.

    @dependencies
    None.

    @sa None
*/

boolean Clock_AGGRE2Init( void )
{
  static boolean bInit = FALSE;

  /* Init Aggre2 only one time */
  if ( !bInit )
  {
    // Enable AGGRE2 power domain
    Clock_PowerDomainEnable ( HWIO_GCC_AGGRE2_NOC_GDSCR_ADDR );
    Clock_ToggleClock(HWIO_GCC_AGGRE2_SNOC_AXI_CBCR_ADDR, CLK_TOGGLE_ENABLE); 
    Clock_ToggleClock(HWIO_GCC_AGGRE2_CNOC_NORTH_PERIPH_AHB_CBCR_ADDR, CLK_TOGGLE_ENABLE);
    Clock_ToggleClock(HWIO_GCC_AGGRE2_CNOC_AHB_CBCR_ADDR, CLK_TOGGLE_ENABLE);
    Clock_ToggleClock(HWIO_GCC_AGGRE2_CNOC_SOUTH_PERIPH_AHB_CBCR_ADDR, CLK_TOGGLE_ENABLE);
    Clock_ToggleClock(HWIO_GCC_AGGRE2_NOC_AT_CBCR_ADDR, CLK_TOGGLE_ENABLE);
    Clock_ToggleClock(HWIO_GCC_SMMU_AGGRE2_AXI_CBCR_ADDR, CLK_TOGGLE_ENABLE);
    Clock_ToggleClock(HWIO_GCC_SMMU_AGGRE2_AXI_SRC_CBCR_ADDR, CLK_TOGGLE_ENABLE);
    Clock_ToggleClock(HWIO_GCC_SMMU_AGGRE2_AHB_CBCR_ADDR, CLK_TOGGLE_ENABLE);

    bInit = TRUE;
  }

  return TRUE;
}

/* ============================================================================
**  Function : Clock_SetQSPIFrequency
** ============================================================================
*/
/*!
    Set QSPI clock frequency.  Clocks will turn off if request frequency is zero

    @param nFreqKHz - Clock frequency in KHz

    @return - Frequency that clock has been match and set to.

    @dependencies
    None.

    @sa None
*/
uint32 Clock_SetQSPIFrequency( uint32 nFreqKHz )
{
  const Clock_ConfigType *cfg = Clock_Config();
  const ClockFreqMuxCfgType *pCfg = NULL;
  uint32 n;

  /* Turn clock off */
  if ( nFreqKHz == 0 )
  {
    Clock_ToggleClock(HWIO_GCC_QSPI_AHB_CBCR_ADDR, CLK_TOGGLE_DISABLE);
    Clock_ToggleClock(HWIO_GCC_QSPI_SER_CBCR_ADDR, CLK_TOGGLE_DISABLE);
    return 0;
  }

  pCfg = cfg->QSPISer_Cfg;

  /* Find the nearest frequency that matches the request */
  for(n = 0; pCfg[n].nFrequency != 0; n++)
  {
    if(pCfg[n].nFrequency >= nFreqKHz) break;
  }
  if(pCfg[n].nFrequency == 0) return 0;

  if( !Clock_EnableSource(pCfg[n].Cfg.eSource) )
  {
    /* Failed.  Loop here forever for easy debug */
    while (1);
  }
  if( !Clock_ConfigMux(&pCfg[n].Cfg) )
  {
    /* Failed.  Loop here forever for easy debug */
    while (1);
  }
  Clock_ToggleClock(HWIO_GCC_QSPI_AHB_CBCR_ADDR, CLK_TOGGLE_ENABLE);
  Clock_ToggleClock(HWIO_GCC_QSPI_SER_CBCR_ADDR, CLK_TOGGLE_ENABLE);
  Clock_ToggleClock(HWIO_GCC_CNOC_PERIPH_NORTH_AHB_CBCR_ADDR, CLK_TOGGLE_ENABLE);
  Clock_ToggleClock(HWIO_GCC_CNOC_PERIPH_SOUTH_AHB_CBCR_ADDR, CLK_TOGGLE_ENABLE);
  Clock_ToggleClock(HWIO_GCC_CNOC_PERIPH_AHB_CBCR_ADDR, CLK_TOGGLE_ENABLE);

  return pCfg[n].nFrequency;
}
/* ============================================================================
**  Function : Clock_SetSDCClockFrequencyExt
** ============================================================================
*/
/*!
    Configure SDC clock to a specific perf level.

    @param eClockPerfLevel   -  [IN] Clock frequency level
           eClock            -  [IN] SDC clock to configure
    @return
    TRUE -- Initialization was successful.
    FALSE -- Initialization failed.

    @dependencies
    None.

    @sa None
*/
uint32 Clock_SetSDCClockFrequencyExt
(
  uint32 nFreqKHz,
  ClockSDCType eClock
)
{
  ClockConfigMuxType SDCCCfg = {0};
  const ClockFreqMuxCfgType *pCfg = NULL;
  uint32 n;
  const Clock_ConfigType *cfg = Clock_Config();

  /* Check for a valid SDC */
  if ( (eClock >= CLK_SDC_NUM_CLKS) || (Clock_SDCCRegs[eClock].nCmd == 0) )
  {
    return FALSE;
  }

  /* Copy the config to the local so the nCMDCGRAddr can be modified. */
  pCfg = (eClock == CLK_SDC1)? (cfg->SDC1_Ext_Cfg) : (cfg->SDC2_Ext_Cfg);

  /* Find the nearest frequency that matches the request */
  for(n = 0; pCfg[n].nFrequency != 0; n++)
  {
    if(pCfg[n].nFrequency >= nFreqKHz)
    {
      break;
    }
  }
  if ( pCfg[n].nFrequency == 0 )
  {
    return FALSE;
  }

  /* A configuration is found.  Set it */
  SDCCCfg = pCfg[n].Cfg; /* copy struct and fix it */
  SDCCCfg.nCMDRCGRAddr = Clock_SDCCRegs[eClock].nCmd;

  /*
   * Enable access to the Peripheral NOC.
   */
  Clock_ToggleClock(HWIO_GCC_CNOC_PERIPH_NORTH_AHB_CBCR_ADDR, CLK_TOGGLE_ENABLE);
  Clock_ToggleClock(HWIO_GCC_CNOC_PERIPH_SOUTH_AHB_CBCR_ADDR, CLK_TOGGLE_ENABLE);
  Clock_ToggleClock(HWIO_GCC_CNOC_PERIPH_AHB_CBCR_ADDR, CLK_TOGGLE_ENABLE);

  if ( (!Clock_EnableSource(SDCCCfg.eSource)) ||
      (!Clock_ConfigMux(&SDCCCfg)) ||
      (!Clock_ToggleClock(Clock_SDCCRegs[eClock].nApps, CLK_TOGGLE_ENABLE)) ||
      (!Clock_ToggleClock(Clock_SDCCRegs[eClock].nAHB, CLK_TOGGLE_ENABLE)) )
  {
    return FALSE;
  }

  return (pCfg[n].nFrequency? TRUE : FALSE);
}


/* ============================================================================
**  Function : Clock_SetSDCClockFrequency
** ============================================================================
*/
/*!
    Configure SDC clock to a specific perf level.

    @param eClockPerfLevel   -  [IN] SDC Clock perf level
           eClock            -  [IN] SDC clock to configure
    @return
    TRUE -- Initialization was successful.
    FALSE -- Initialization failed.

    @dependencies
    None.

    @sa None
*/
boolean Clock_SetSDCClockFrequency
(
  ClockBootPerfLevelType ePerfLevel,
  ClockSDCType eClock
)
{
  const Clock_ConfigType *cfg = Clock_Config();

  if(ePerfLevel >= CLOCK_BOOT_PERF_NUM) return FALSE;
 
  return Clock_SetSDCClockFrequencyExt( cfg->SDC_Cfg[ePerfLevel], eClock);

} /* END Clock_SetSDCClockFrequency */


/* ========================================================================
**  Function : Clock_ReplaceUSBBootClockEnable
** ======================================================================*/
/*
    Description: The register GCC_USB_BOOT_CLOCK_CTL turns on all the clocks
    necessary to access USB from the APPS.  This function must be ported
    on every new MSM.  It replaces that single register with all the clock
    enables that it replaced.  This allows for fine grained control of these
    clocks on an individual basis.

    @param None
    @return None

    @dependencies
    None.

    @sa None
*/
void Clock_ReplaceUSBBootClockEnable()
{
  Clock_ToggleClock(HWIO_GCC_SYS_NOC_AXI_CBCR_ADDR, CLK_TOGGLE_ENABLE);
  Clock_ToggleClock(HWIO_GCC_SYS_NOC_NORTH_AXI_CBCR_ADDR, CLK_TOGGLE_ENABLE);
  Clock_ToggleClock(HWIO_GCC_SYS_NOC_SOUTH_AXI_CBCR_ADDR, CLK_TOGGLE_ENABLE);
  Clock_ToggleClock(HWIO_GCC_SNOC_CNOC_AHB_CBCR_ADDR, CLK_TOGGLE_ENABLE);
  Clock_ToggleClock(HWIO_GCC_CFG_NOC_USB3_AXI_CBCR_ADDR, CLK_TOGGLE_ENABLE);
  Clock_ToggleClock(HWIO_GCC_CNOC_PERIPH_NORTH_AHB_CBCR_ADDR, CLK_TOGGLE_ENABLE);
  Clock_ToggleClock(HWIO_GCC_CNOC_PERIPH_SOUTH_AHB_CBCR_ADDR, CLK_TOGGLE_ENABLE);
  Clock_ToggleClock(HWIO_GCC_CNOC_PERIPH_AHB_CBCR_ADDR, CLK_TOGGLE_ENABLE);
  Clock_ToggleClock(HWIO_GCC_USB30_MASTER_CBCR_ADDR, CLK_TOGGLE_ENABLE);
  Clock_ToggleClock(HWIO_GCC_USB30_SLEEP_CBCR_ADDR, CLK_TOGGLE_ENABLE);
  Clock_ToggleClock(HWIO_GCC_USB30_MOCK_UTMI_CBCR_ADDR, CLK_TOGGLE_ENABLE);
  Clock_ToggleClock(HWIO_GCC_USB3_PHY_AUX_CBCR_ADDR, CLK_TOGGLE_ENABLE);
  HWIO_OUTF(GCC_USB3_PHY_PIPE_CBCR, CLK_ENABLE, 1);
  Clock_ToggleClock(HWIO_GCC_USB_PHY_CFG_AHB2PHY_CBCR_ADDR, CLK_TOGGLE_ENABLE);
  Clock_ToggleClock(HWIO_GCC_AGGRE2_SNOC_AXI_CBCR_ADDR, CLK_TOGGLE_ENABLE);
  Clock_ToggleClock(HWIO_GCC_AGGRE2_CNOC_PERIPH_AHB_CBCR_ADDR, CLK_TOGGLE_ENABLE);
  Clock_ToggleClock(HWIO_GCC_SMMU_AGGRE2_AXI_SRC_CBCR_ADDR, CLK_TOGGLE_ENABLE);
  Clock_ToggleClock(HWIO_GCC_SMMU_AGGRE2_AXI_CBCR_ADDR, CLK_TOGGLE_ENABLE);
  Clock_ToggleClock(HWIO_GCC_AGGRE2_USB3_AXI_CBCR_ADDR, CLK_TOGGLE_ENABLE);
  Clock_ToggleClock(HWIO_GCC_AGGRE2_CNOC_NORTH_PERIPH_AHB_CBCR_ADDR, CLK_TOGGLE_ENABLE);
  Clock_ToggleClock(HWIO_GCC_AGGRE2_CNOC_SOUTH_PERIPH_AHB_CBCR_ADDR, CLK_TOGGLE_ENABLE);

#if 0 /*USB2 clocks*/
  Clock_ToggleClock(HWIO_GCC_CFG_NOC_USB2_AXI_CBCR_ADDR, CLK_TOGGLE_ENABLE);
  Clock_ToggleClock(HWIO_GCC_USB20_MASTER_CBCR_ADDR, CLK_TOGGLE_ENABLE);
  Clock_ToggleClock(HWIO_GCC_USB20_SLEEP_CBCR_ADDR, CLK_TOGGLE_ENABLE);
  Clock_ToggleClock(HWIO_GCC_USB20_MOCK_UTMI_CBCR_ADDR, CLK_TOGGLE_ENABLE);

#endif


  /* Don't poll this clock for enable since the clock source from PHY which may not be out of reset yet */
  HWIO_OUTF(GCC_RX1_USB2_CLKREF_EN, RX1_USB2_ENABLE, 1);
  HWIO_OUTF(GCC_RX0_USB2_CLKREF_EN, RX0_USB2_ENABLE, 1);


  /* Now disable the master boot control, allowing each of those above to replace */
  HWIO_OUTF(GCC_USB_BOOT_CLOCK_CTL, CLK_ENABLE, 0);
}

/* ========================================================================
**  Function : Clock_InitAHB2PHY
** ======================================================================*/
/*!
    Initialize the clocks necessary to access the PHY and REFGEN.

    @param
      None.

    @return
      None.

    @dependencies
      None.

    @sa None
*/

void Clock_InitAHB2PHY( void )
{
  Clock_ToggleClock(HWIO_ADDR(GCC_CFG_NOC_AH2PHY_XO_CBCR), 1);
  Clock_ToggleClock(HWIO_ADDR(GCC_CNOC_PERIPH_NORTH_AHB_CBCR), 1);
  Clock_ToggleClock( HWIO_ADDR(GCC_CFG_NOC_DDR_CFG_CBCR), 1);
  HWIO_OUTF(GCC_AHB2PHY_EAST_CBCR, NOC_HANDSHAKE_FSM_EN, 0);
  Clock_ToggleClock(HWIO_ADDR(GCC_CNOC_PERIPH_SOUTH_AHB_CBCR), 1);
  Clock_ToggleClock(HWIO_ADDR(GCC_USB_PHY_CFG_AHB2PHY_CBCR), 1);
  Clock_ToggleClock(HWIO_ADDR(GCC_AHB2PHY_EAST_CBCR), 1);
}

/* ============================================================================
**  Function : Clock_InitUSB
** ============================================================================
*/
/*!
    Configure USB clocks.

    @param None.
    @return
    TRUE -- Initialization was successful.
    FALSE -- Initialization failed.

    @dependencies
    None.

    @sa None
*/
boolean Clock_InitUSB(void)
{
  ClockConfigMuxType USB30Cfg = {0};
  ClockConfigMuxType USB30_MockCfg = {0};
  ClockConfigMuxType USB30_AuxCfg = {0};
    
  /* This is redundant with BootROM, except on the debugger tools, 
   * because the JTAG tools do not use BootROM */
  Clock_InitAHB2PHY();
  /* Configured gcc_usb30_master_clk to 125 MHz */
  USB30Cfg.nCMDRCGRAddr = HWIO_ADDR(GCC_USB30_MASTER_CMD_RCGR);
  USB30Cfg.eSource = SRC_GPLL0; 
  USB30Cfg.nDiv2x = 2;
  USB30Cfg.nM = 5;
  USB30Cfg.nN = 24;
  USB30Cfg.n2D = 24;

  /* Configure gcc_usb30_mock_utmi_clk to 60 MHz */
  USB30_MockCfg.nCMDRCGRAddr = HWIO_ADDR(GCC_USB30_MOCK_UTMI_CMD_RCGR);
  USB30_MockCfg.eSource = SRC_GPLL0;
  USB30_MockCfg.nDiv2x = 20;
  USB30_MockCfg.nM = 0;
  USB30_MockCfg.nN = 0;
  USB30_MockCfg.n2D = 0;

  /* Configure gcc_usb3_phy_aux_clk to 19.2 */
  USB30_AuxCfg.nCMDRCGRAddr = HWIO_ADDR(GCC_USB3_PHY_AUX_CMD_RCGR);
  USB30_AuxCfg.eSource = SRC_CXO;
  USB30_AuxCfg.nDiv2x = 2;
  USB30_AuxCfg.nM = 0;
  USB30_AuxCfg.nN = 0;
  USB30_AuxCfg.n2D = 0;

  /* Enable Aggre2 NOC since UFS has depedency */
  if( ! Clock_AGGRE2Init()) return FALSE;

  if (!Clock_ConfigMux(&USB30Cfg))
  {
    return FALSE;
  }

  HWIO_OUTF(GCC_AGGRE2_USB3_AXI_CBCR, CLK_ENABLE, 1);
  HWIO_OUTF(GCC_CFG_NOC_USB3_AXI_CBCR, CLK_ENABLE, 1);
  HWIO_OUTF(GCC_USB30_MASTER_CBCR, CLK_ENABLE, 1);
  HWIO_OUTF(GCC_USB30_SLEEP_CBCR, CLK_ENABLE, 1);

  // Configure the Mock UTMI clock
  if(!Clock_ConfigMux(&USB30_MockCfg))
  {
    return FALSE; 
  }
  HWIO_OUTF(GCC_USB30_MOCK_UTMI_CBCR, CLK_ENABLE, 1);
  HWIO_OUTF(GCC_USB_PHY_CFG_AHB2PHY_CBCR, CLK_ENABLE, 1);

  // Configure the USB3 Aux Clock
  if(!Clock_ConfigMux(&USB30_AuxCfg))
  {
    return FALSE;
  }

  HWIO_OUTF(GCC_USB3_PHY_AUX_CBCR, CLK_ENABLE, 1);
  HWIO_OUTF(GCC_USB3_PHY_PIPE_CBCR, CLK_ENABLE, 1);

  return TRUE;
}


/* ============================================================================
**  Function : Clock_DisableUSB
** ============================================================================
*/
/*!
    Disable USB clocks.

    @param None.
    @return
    TRUE -- Disable was successful.
    FALSE -- Disable failed.

    @dependencies
    None.

    @sa None
*/
boolean Clock_DisableUSB(void)
{

  /* Don't poll this clock since it sources from PHY which may not be out of reset yet */
  HWIO_OUTF(GCC_USB3_PHY_PIPE_CBCR, CLK_ENABLE, 0);

  if( ! Clock_ToggleClock(HWIO_GCC_USB3_PHY_AUX_CBCR_ADDR, CLK_TOGGLE_DISABLE)) return FALSE;
  if( ! Clock_ToggleClock(HWIO_GCC_USB_PHY_CFG_AHB2PHY_CBCR_ADDR, CLK_TOGGLE_DISABLE)) return FALSE;
  if( ! Clock_ToggleClock(HWIO_GCC_USB30_MOCK_UTMI_CBCR_ADDR, CLK_TOGGLE_DISABLE)) return FALSE;
  if( ! Clock_ToggleClock(HWIO_GCC_USB30_SLEEP_CBCR_ADDR, CLK_TOGGLE_DISABLE)) return FALSE;
  if( ! Clock_ToggleClock(HWIO_GCC_USB30_MASTER_CBCR_ADDR, CLK_TOGGLE_DISABLE)) return FALSE;
  if( ! Clock_ToggleClock(HWIO_GCC_CFG_NOC_USB3_AXI_CBCR_ADDR, CLK_TOGGLE_DISABLE)) return FALSE;

  return TRUE;
} /* END Clock_DisableUSB */


/* ============================================================================
**  Function : Clock_USB30_PipeClkSrcSel
** ============================================================================
*/
/*!
    Select USB3 PIPE clock source.

    @param eSrc -  [IN] Clock source choice for the USB3.0 PHY
    @return
    TRUE -- Initialization was successful.
    FALSE -- Initialization failed.
    @dependencies  None.
    @sa None
*/
boolean Clock_USB30_PipeClkSrcSel(ClockUSB30PipeClkSrcType eSrc)
{
  boolean Success = FALSE;
  if(CLOCK_USB30_SRC_INVALID > eSrc)
  {
    HWIO_OUTF( GCC_USB3_PHY_PIPE_MISC, SRC_SEL, eSrc); 
    Success = TRUE;
  }
  return Success;
}  /* END Clock_USB30_PipeClkSrcSel */


/* ============================================================================
**  Function : Clock_Usb30EnableSWCollapse
** ============================================================================
*/
/*!
    Enable SW Collapse for USB30

    @param Enable/Disable.
    @return
    TRUE always

    @dependencies
    None.

    @sa None
   */
boolean Clock_Usb30EnableSWCollapse(boolean enable)
{
  /* Enable/Disable SW PowerCollapse for USB30 */
  HWIO_OUTF(GCC_USB_30_GDSCR, SW_COLLAPSE, enable ? 1:0 );
  return TRUE;	
}


/* ============================================================================
**  Function : Clock_Usb30GetSWCollapse
** ============================================================================
*/
/*!
    Returns the status of SW Collapse for USB30

    @param None
    @return
    TRUE if enabled
    FALSE if disabled

    @dependencies
    None.

    @sa None
*/
boolean Clock_Usb30GetSWCollapse(void)
{
  uint8 sw_collapse = HWIO_INF(GCC_USB_30_GDSCR, SW_COLLAPSE);
  return (sw_collapse ? TRUE : FALSE);	
}


/* ========================================================================
**  Function : Clock_UFSInit
** ======================================================================*/
/*!
    Get the requested clock frequency in hertz.

    @param
      ePerfLevel [in]  - Performance level

    @return
      True - Success init UFS clocks

    @dependencies
    None.

    @sa None
*/

boolean Clock_UFSInit( ClockBootPerfLevelType ePerfLevel )
{
  Clock_CBCRtoggleType enable;

  const ClockConfigMuxType *clkCfg;
  ClockConfigMuxType clkUniproCfg;
  const Clock_ConfigType *cfg = Clock_Config();

  if( ePerfLevel >= CLOCK_BOOT_PERF_NUM ) return FALSE;

  /* This is redundant with BootROM, except on the debugger tools, 
   * because the JTAG tools do not use BootROM */
  Clock_InitAHB2PHY();

  /* Configure UFS. */
  clkCfg = &cfg->UFS_Cfg[ePerfLevel];
  if( ! Clock_EnableSource( clkCfg->eSource )) return FALSE;
  if( ! Clock_ConfigMux(clkCfg)) return FALSE;

  /* Configure UFS ICE CORE. */
  clkCfg = &cfg->UFS_Ice_Cfg[ePerfLevel];
  if( ! Clock_EnableSource( clkCfg->eSource )) return FALSE;
  if( ! Clock_ConfigMux(clkCfg)) return FALSE;

  /* Unipro is half of ICE Core */
  clkUniproCfg = *clkCfg;  /* Copy everything first */
  clkUniproCfg.nCMDRCGRAddr = HWIO_ADDR(GCC_UFS_UNIPRO_CORE_CMD_RCGR);
  clkUniproCfg.nDiv2x = clkCfg->nDiv2x * 2;
  if(clkUniproCfg.nDiv2x > 32) return FALSE;
  if( ! Clock_ConfigMux(&clkUniproCfg)) return FALSE;

  if ( ePerfLevel == CLOCK_BOOT_PERF_NONE )
  {
    /* Disable UFS clocks before disabling the power domain. */
    enable = CLK_TOGGLE_DISABLE;
  }
  else
  {
    /* Enable UFS clocks after enabling the power domain. */
    enable = CLK_TOGGLE_ENABLE;

    /* Enable Aggre2 NOC since UFS has depedency. */
    if( ! Clock_AGGRE2Init()) return FALSE;

    Clock_PowerDomainEnable ( HWIO_GCC_UFS_GDSCR_ADDR );
    Clock_ToggleClock(HWIO_GCC_CNOC_PERIPH_SOUTH_AHB_CBCR_ADDR, CLK_TOGGLE_ENABLE);
    Clock_ToggleClock(HWIO_GCC_CNOC_PERIPH_NORTH_AHB_CBCR_ADDR, CLK_TOGGLE_ENABLE);
  }
  Clock_ToggleClock(HWIO_GCC_AGGRE2_UFS_AXI_CBCR_ADDR, enable);
  
  Clock_ToggleClock(HWIO_GCC_UFS_PHY_AUX_CBCR_ADDR, enable);
  Clock_ToggleClock(HWIO_GCC_UFS_AXI_CBCR_ADDR, enable);
  Clock_ToggleClock(HWIO_GCC_UFS_AHB_CBCR_ADDR, enable);
  Clock_ToggleClock(HWIO_GCC_UFS_UNIPRO_CORE_CBCR_ADDR, enable);
  Clock_ToggleClock(HWIO_GCC_UFS_ICE_CORE_CBCR_ADDR, enable);

  HWIO_OUTF(GCC_UFS_CLKREF_EN, UFS_ENABLE, enable);
  HWIO_OUTF(GCC_UFS_TX_SYMBOL_0_CBCR, CLK_ENABLE, enable);
  HWIO_OUTF(GCC_UFS_RX_SYMBOL_0_CBCR, CLK_ENABLE, enable) ;
  

  if ( ePerfLevel == CLOCK_BOOT_PERF_NONE )
  {
    Clock_PowerDomainDisable ( HWIO_GCC_UFS_GDSCR_ADDR );
  }

  return TRUE;
}


/* ============================================================================
**  Function : Clock_SetUARTClockFrequency
** ============================================================================
*/
/*!
    Configure UART clock to a specific perf level.

    @param eClockPerfLevel   -  [IN] Clock frequency level
                     eClock            -  [IN] UART clock to configure
    @return
    TRUE -- Initialization was successful.
    FALSE -- Initialization failed.

    @dependencies
    None.

    @sa None
*/
boolean Clock_SetUARTClockFrequency(ClockBootPerfLevelType ePerfLevel,
                                    ClockUARTType eClock)
{
  ClockConfigMuxType UARTCfg = {0};
  const Clock_ConfigType *cfg = Clock_Config();

  if(ePerfLevel >= CLOCK_BOOT_PERF_NUM) return FALSE;

  // Check for un-support UART clock
  if ( Clock_UARTRegs[eClock].nCmd == 0)
  {
    return FALSE;
  }

  /* Copy the config to the local so the nCMDRCGRAddr can be modified. */
  UARTCfg = cfg->UART_Cfg[ePerfLevel];

  if( ! Clock_EnableSource( UARTCfg.eSource )) return FALSE;

  UARTCfg.nCMDRCGRAddr = Clock_UARTRegs[eClock].nCmd;
  if( ! Clock_ConfigMux(&UARTCfg)) return FALSE;
  Clock_ToggleClock(Clock_UARTRegs[eClock].nApps, CLK_TOGGLE_ENABLE);
  return TRUE;
}


/* ============================================================================
**	Function : Clock_DisableUARTClock
** ============================================================================
*/
/*!
	Disable  specific UART clock.

	@param    eClock	-	[IN] UART clock to Disable
	@return
	TRUE -- Clock disable was successful.
	FALSE -- Clock disable failed.

	@dependencies
	None.

	@sa None
*/
boolean Clock_DisableUARTClock(ClockUARTType eClock)
{
  // Check for un-support UART clock
  if ( Clock_UARTRegs[eClock].nApps == 0)
  {
    return FALSE;
  }

  Clock_ToggleClock(Clock_UARTRegs[eClock].nApps, CLK_TOGGLE_DISABLE);
  return TRUE;
}

/* ============================================================================
**	Function : Clock_SetI2CClockFrequency
** ============================================================================
*/
/*!
	Configure QUP_I2C clock to a specific perf level.

	@param      ePerfLevel	 -	[IN] UART Clock perf level
		        eClock	 -	[IN] UART clock to configure
	@return
	TRUE -- Initialization was successful.
	FALSE -- Initialization failed.

	@dependencies
	None.

	@sa None
*/
boolean Clock_SetI2CClockFrequency
(
  ClockBootPerfLevelType ePerfLevel,
  ClockQUPI2CType eClock
)
{
  ClockConfigMuxType I2CCfg = {0};
  const Clock_ConfigType *cfg = Clock_Config();

  if(ePerfLevel >= CLOCK_BOOT_PERF_NUM) return FALSE;

  // Check for un-support I2C clock
  if ( Clock_I2CRegs[eClock].nCmd == 0)
  {
    return FALSE;
  }

  /* Copy the config to the local so the nCMDRCGRAddr can be modified. */
  I2CCfg = cfg->I2C_Cfg[ePerfLevel];

  if( ! Clock_EnableSource( I2CCfg.eSource )) return FALSE;

  I2CCfg.nCMDRCGRAddr = Clock_I2CRegs[eClock].nCmd;
  if( ! Clock_ConfigMux(&I2CCfg)) return FALSE;
  Clock_ToggleClock(Clock_I2CRegs[eClock].nApps, CLK_TOGGLE_ENABLE);
 
  /* Enable BLSP1 and BLSP2 AHB CLK */
  if (eClock <= CLK_BLSP1_QUP6_I2C_APPS)
  {
    HWIO_OUTF(GCC_APCS_CLOCK_BRANCH_ENA_VOTE, BLSP1_AHB_CLK_ENA, 1);
  }
  else
  {
    HWIO_OUTF(GCC_APCS_CLOCK_BRANCH_ENA_VOTE, BLSP2_AHB_CLK_ENA, 1);
  }

 return TRUE;
} /* END Clock_SetI2CClockFrequency */


/* ============================================================================
**	Function : Clock_DisableI2CClock
** ============================================================================
*/
/*!
	Disable  specific I2C clock.

	@param    eClock	-	[IN] I2C clock to Disable
	@return
	TRUE -- Clock disable was successful.
	FALSE -- Clock disable failed.

	@dependencies
	None.

	@sa None
*/
boolean Clock_DisableI2CClock(ClockQUPI2CType eClock)
{
  // Check for un-support I2C clock
  if ( Clock_I2CRegs[eClock].nApps == 0)
  {
    return FALSE;
  }
  Clock_ToggleClock(Clock_I2CRegs[eClock].nApps, CLK_TOGGLE_DISABLE);
  
  return TRUE;
}

/* ============================================================================
**  Function : Clock_SetSPIClockFrequency
** ============================================================================
*/
/*!
    Configure the SPI clock to a specified Frquency, rounding up.

    @param nFreqKHz          -  [IN] Frequency in KHz
           eClock            -  [IN] SPI clock to configure
    @return
        freq - Returns the frequency which may be rounded up if the 
          requested frequency was not in the clock plan.

    @dependencies
    None.

    @sa None
*/
uint32 Clock_SetSPIClockFrequency(ClockQUPSPIType eClock,  uint32 nFreqKHz)
{
  ClockConfigMuxType SPICfg = {0};
  const ClockFreqMuxCfgType *pCfg = NULL;
  uint32 n;
  const Clock_ConfigType *cfg = Clock_Config();

  /* Check for a valid SDC */
  if( eClock >= CLK_BLSP_QUP_SPI_NUM_CLKS ) return 0;
  if (Clock_SPIRegs[eClock].nCmd == 0) return 0;

  /* Copy the config to the local so the nCMDRCGRAddr can be modified. */
  pCfg = cfg->SPI_Cfg;

  /* Find the nearest frequency that matches the request */
  for(n = 0; pCfg[n].nFrequency != 0; n++)
  {
    if(pCfg[n].nFrequency >= nFreqKHz) break;
  }
  if(pCfg[n].nFrequency == 0) return 0;

  /* A configuration is found.  Set it */
  SPICfg = pCfg[n].Cfg; /* copy struct and fix it */
  SPICfg.nCMDRCGRAddr = Clock_SPIRegs[eClock].nCmd;

  /* pfab_core_clk defaults to enabled */

  if( SPICfg.eSource != SRC_CXO )
  {
    if( ! Clock_EnableSource( SPICfg.eSource )) return 0;
  }
  if( ! Clock_ConfigMux(&SPICfg)) return 0;
  if( ! Clock_ToggleClock(Clock_SPIRegs[eClock].nApps, CLK_TOGGLE_ENABLE)) return 0;

  return pCfg[n].nFrequency;
}

/* ============================================================================
**  Function : Clock_InitVSense
** ============================================================================
*/
/*!
    This function enables the Voltage Sensor clocks, and configure them run
    at max frequency level at NOMINAL voltage.

    @return
      TRUE -- Initialization was successful.
      FALSE -- Initialization failed.

   @dependencies
     None.

*/
boolean Clock_InitVSense( void )
{
  /* Default VS clocks are running at 600MHz. */
  ClockConfigMuxType VSMXMuxCfg =   {HWIO_ADDR(GCC_VDDMX_VS_CMD_RCGR),  MUX_GCC,  SRC_GPLL0,   1, 0, 0, 0};
  ClockConfigMuxType VSCXMuxCfg =   {HWIO_ADDR(GCC_VDDCX_VS_CMD_RCGR),  MUX_GCC,  SRC_GPLL0,   1, 0, 0, 0};
  ClockConfigMuxType VSVDDAMuxCfg = {HWIO_ADDR(GCC_VDDA_VS_CMD_RCGR),   MUX_GCC,  SRC_GPLL0,   1, 0, 0, 0};
  ClockConfigMuxType VSMSSMuxCfg =  {HWIO_ADDR(GCC_MSS_VS_CMD_RCGR),    MUX_GCC,  SRC_GPLL0,   1, 0, 0, 0};
  ClockConfigMuxType VSWCSSMuxCfg =  {HWIO_ADDR(GCC_WCSS_VS_CMD_RCGR),  MUX_GCC,  SRC_GPLL0,   1, 0, 0, 0};
  ClockConfigMuxType VSAPC0MuxCfg = {HWIO_ADDR(GCC_APC0_VS_CMD_RCGR),   MUX_GCC,  SRC_GPLL0,   1, 0, 0, 0};
  ClockConfigMuxType VSAPC1MuxCfg = {HWIO_ADDR(GCC_APC1_VS_CMD_RCGR),   MUX_GCC,  SRC_GPLL0,   1, 0, 0, 0};

  /* Need to enable QDSS AT & DAP clocks for access VSense config registers */
  HWIO_OUTF(GCC_APCS_CLOCK_BRANCH_ENA_VOTE_1, QDSS_CFG_AHB_CLK_ENA, 1 );

  HWIO_OUTF(GCC_QDSS_CENTER_AT_CBCR, CLK_ENABLE, 1);
  HWIO_OUTF(GCC_QDSS_DAP_CBCR, CLK_ENABLE, 1);
  HWIO_OUTF(GCC_QDSS_DAP_AHB_CBCR, CLK_ENABLE, 1);

  if( ! Clock_EnableSource( VSMXMuxCfg.eSource )) return FALSE;
  if( ! Clock_ConfigMux(&VSMXMuxCfg) ) return FALSE;
  if( ! Clock_ConfigMux(&VSCXMuxCfg) ) return FALSE;
  if( ! Clock_ConfigMux(&VSVDDAMuxCfg) ) return FALSE;
  if( ! Clock_ConfigMux(&VSAPC0MuxCfg) ) return FALSE;
  if( ! Clock_ConfigMux(&VSAPC1MuxCfg) ) return FALSE;

  Clock_ToggleClock(HWIO_ADDR(GCC_VS_CTRL_CBCR), CLK_TOGGLE_ENABLE);
  Clock_ToggleClock(HWIO_ADDR(GCC_VDDMX_VS_CBCR), CLK_TOGGLE_ENABLE);
  Clock_ToggleClock(HWIO_ADDR(GCC_VDDCX_VS_CBCR), CLK_TOGGLE_ENABLE);
  Clock_ToggleClock(HWIO_ADDR(GCC_VDDA_VS_CBCR), CLK_TOGGLE_ENABLE);
  Clock_ToggleClock(HWIO_ADDR(GCC_APC0_VS_CBCR), CLK_TOGGLE_ENABLE);
  Clock_ToggleClock(HWIO_ADDR(GCC_APC1_VS_CBCR), CLK_TOGGLE_ENABLE);

  Clock_ToggleClock(HWIO_ADDR(GCC_MSS_CFG_AHB_CBCR), CLK_TOGGLE_ENABLE ); 
  if( ! Clock_ConfigMux(&VSMSSMuxCfg) ) return FALSE;
  Clock_ToggleClock(HWIO_ADDR(GCC_MSS_VS_CBCR), CLK_TOGGLE_ENABLE);

  Clock_ToggleClock(HWIO_ADDR(GCC_WCSS_AHB_S0_CBCR), CLK_TOGGLE_ENABLE ); 
  if( ! Clock_ConfigMux(&VSWCSSMuxCfg) ) return FALSE;
  Clock_ToggleClock(HWIO_ADDR(GCC_WCSS_VS_CBCR), CLK_TOGGLE_ENABLE);


  return TRUE;
}


/* ============================================================================
**  Function : Clock_ShutdownVSense
** ============================================================================
*/
/*!
    This function disables the voltage sensor clocks.

    @return
      TRUE -- Initialization was successful.
      FALSE -- Initialization failed.

   @dependencies
      None.

*/
boolean Clock_ShutdownVSense( void )
{
  Clock_ToggleClock(HWIO_ADDR(GCC_VS_CTRL_CBCR),  CLK_TOGGLE_DISABLE);
  Clock_ToggleClock(HWIO_ADDR(GCC_VDDMX_VS_CBCR), CLK_TOGGLE_DISABLE);
  Clock_ToggleClock(HWIO_ADDR(GCC_VDDCX_VS_CBCR), CLK_TOGGLE_DISABLE);
  Clock_ToggleClock(HWIO_ADDR(GCC_VDDA_VS_CBCR),  CLK_TOGGLE_DISABLE);
  Clock_ToggleClock(HWIO_ADDR(GCC_APC0_VS_CBCR),  CLK_TOGGLE_DISABLE);
  Clock_ToggleClock(HWIO_ADDR(GCC_APC1_VS_CBCR),  CLK_TOGGLE_DISABLE);

  /* Restore QDSS clocks back to default state */
  HWIO_OUTF(GCC_APCS_CLOCK_BRANCH_ENA_VOTE_1, QDSS_CFG_AHB_CLK_ENA, 0 );

  HWIO_OUTF(GCC_QDSS_CENTER_AT_CBCR, CLK_ENABLE, 0);
  HWIO_OUTF(GCC_QDSS_DAP_CBCR, CLK_ENABLE, 0);
  HWIO_OUTF(GCC_QDSS_DAP_AHB_CBCR, CLK_ENABLE, 0);

  Clock_ToggleClock(HWIO_ADDR(GCC_MSS_VS_CBCR), CLK_TOGGLE_DISABLE);
  Clock_ToggleClock(HWIO_ADDR(GCC_MSS_CFG_AHB_CBCR), CLK_TOGGLE_ENABLE ); 

  Clock_ToggleClock(HWIO_ADDR(GCC_WCSS_VS_CBCR), CLK_TOGGLE_DISABLE);
  Clock_ToggleClock(HWIO_ADDR(GCC_WCSS_AHB_S0_CBCR), CLK_TOGGLE_ENABLE ); 


  return TRUE;
}
