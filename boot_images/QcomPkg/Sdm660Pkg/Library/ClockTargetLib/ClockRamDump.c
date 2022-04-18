/**
==============================================================================
  @file ClockRamDump.c

  Clock functions for the XBL RAM Dump image, which primarily supports a 
  video splash screen.

==============================================================================

                             Edit History


when      who           what, where, why
--------  ------------  ------------------------------------------------------
06/07/16  bc            Initial MSM8998 revision, new file

==============================================================================
            Copyright (c) 2016 QUALCOMM Technologies Incorporated.
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
#include <string.h>
#include "busywait.h"

/*=========================================================================
                       MACRO DEFINITIONS
==========================================================================*/
#define DIV(div) ((int)2*div)
#define ARRAY_LEN(a) (sizeof(a)/sizeof(a[0]))

/* To keep ClockDomainID's apart from ClockID's, I am adding this offset */
#define DOMAIN_OFFSET 0x1000
#define DEVICE_ID_SDM630      0x7
/*=========================================================================
      Data
==========================================================================*/
const struct 
{
  ClockConfigPLLType MPLL0_Cfg;
  ClockConfigPLLType MPLL5_Cfg;
} 
Clock_RD_Plan = 
{
  /* MMPLL0 @ 808 MHz */
  .MPLL0_Cfg =
  {
    .nPLLModeAddr  =  HWIO_ADDR(MMSS_MMPLL0_PLL_MODE),
    .nVoteAddr     =  0,
    .nVoteMask     =  0,
    .nVCO          =  2, 
    .nPreDiv       =  1,
    .nPostDiv      =  1,
    .nL            =  42,
    .nM            =  0,
    .nN            =  0,
    .nConfigCtl    =  SPARK_CONFIG_CTL,
    .nAlpha        =  0x1555555555,
  },
  
  /* MMPLL5 @ 825 MHz */
  .MPLL5_Cfg =
  {
    .nPLLModeAddr  =  HWIO_ADDR(MMSS_MMPLL5_PLL_MODE),
    .nVoteAddr     =  0,
    .nVoteMask     =  0,
    .nVCO          =  2, 
    .nPreDiv       =  1,
    .nPostDiv      =  1,
    .nL            =  42,
    .nM            =  0,
    .nN            =  0,
    .nConfigCtl    =  SPARK_CONFIG_CTL,
    .nAlpha        =  0xF800000000,
  },
};

/* MMSS Splash Screen Requirements, 
 * Clock_Domain,        Clock Name,         Freq,   Source
 * MMSS_BYTE0_GRP       mmss_mdss_byte0_clk      262.50  DSI0_PHYPLL_BYTE(src1)
 * MMSS_BYTE1_GRP       mmss_mdss_byte1_clk      262.50  DSI0_PHYPLL_BYTE(src1)
 * MMSS_ESC0_GRP        mmss_mdss_esc0_clk       19.20   XO
 * MMSS_ESC1_GRP        mmss_mdss_esc1_clk       19.20   XO
 * MMSS_EXTPCLK_GRP     mmss_mdss_extpclk_clk    600.00  HDMIPHYPLL(src1)
 * MMSS_HDMI_APP_GRP    mmss_mdss_hdmi_clk       19.20   XO
 * MMSS_MDP_GRP         mmss_mdss_mdp_clk        330.00  MMPLL5(src2)
 * MMSS_MDP_VSYNC_GRP   mmss_mdss_vsync_clk      19.20   XO
 * MMSS_NOC_AHB_GRP:DIV mmss_mdss_ahb_clk        80.00   MMPLL0
 * MMSS_NOC_AHB_GRP:DIV mmss_mdss_hdmi_ahb_clk   80.00   MMPLL0
 * MMSS_NOC_AXI_GRP:DIV mmss_mdss_axi_clk        320.00  MMPLL0
 * MMSS_PCLK0_GRP       mmss_mdss_pclk0_clk      350.00  DSI0_PHYPLL_DSI(src1)
 * MMSS_PCLK1_GRP       mmss_mdss_pclk1_clk      350.00  DSI0_PHYPLL_DSI(src1)
*/

/* Also required (see MDSSPlatform_3xx.h )
 *
 * The first set will be passed to SelectExternalSource
  // {"mmss_mdss_esc0_clk",      0, 1, 0, 0, 0, 0},  // Index 0 : primary source :XO , Secondary source : dsi pll
  // {"mmss_mdss_pclk0_clk",     1, 0, 0, 0, 0, 0},  // Index 1 : Source DSI0_PLL
  // {"mmss_mdss_byte0_clk",     1, 0, 0, 0, 0, 0},  // Index 2 : Source DSI0_PLL
  // {"mmss_mdss_byte0_intf_clk",1, 0, 2, 0, 0, 0},  // Index 2 : Source DSI0_PLL 
  // {"mmss_mdss_esc1_clk",      0, 1, 0, 0, 0, 0},  // Index 0 : primary source :XO , Secondary source : dsi pll
  // {"mmss_mdss_pclk1_clk",     2, 0, 0, 0, 0, 0},  // Index 1 : Source DSI1_PLL
  // {"mmss_mdss_byte1_clk",     2, 0, 0, 0, 0, 0},  // Index 2 : Source DSI1_PLL
  // {"mmss_mdss_byte1_intf_clk",2, 0, 2, 0, 0, 0},  // Index 2 : Source DSI1_PLL 
  // 
  //  * These will select these frequencies, 0 means CXO 
  // {"mmss_mnoc_ahb_clk",              0, NULL},
  // {"mmss_mnoc_axi_clk",              0, NULL},
  // {"mmss_bimc_smmu_ahb_clk",         0, NULL},
  // {"mmss_bimc_smmu_axi_clk",         0, NULL},
  // {"mmss_s0_axi_clk",                0, NULL},
  // {"mmss_mdss_axi_clk",      240000000, NULL},
  // {"mmss_mdss_ahb_clk",              0, NULL},
  // {"mmss_mdss_mdp_clk",      200000000, NULL},
  // {"mmss_mdss_rot_clk",      330000000, NULL},
  // {"mmss_mdss_vsync_clk",            0, NULL}, 
 *
 */
const struct 
{
  const char         *sDomainName;
  uintnt              nGDSCRAddr;
} Clock_RD_MMSS_Domains[] =
{
  {"VDD_MDSS", HWIO_ADDR(MMSS_MDSS_GDSCR)},
  {"VDD_BIMC_SMMU", HWIO_ADDR(MMSS_BIMC_SMMU_GDSCR)},
  {"VDD_MMSS", HWIO_ADDR(GCC_MMSS_GDSCR) },
  
};

const struct 
{
  const char         *sClockName;
  uintnt              nCBCRAddr;
  uint32              nFreqKHz;
  ClockConfigMuxType  sMuxCfg;
} Clock_RD_MMSS_ClockCfg[] =
{
  /* MMSS_BYTE0_GRP       mdss_byte0_clk     262.50  DSI0_PHYPLL_BYTE(src1) */
  {"mmss_mdss_byte0_clk", HWIO_ADDR(MMSS_MDSS_BYTE0_CBCR), 
    262500, {HWIO_ADDR(MMSS_BYTE0_CMD_RCGR), MUX_MMSS, SRC_EXT1, 0, 0, 0, 0}},
  {"mmss_mdss_byte0_intf_clk", HWIO_ADDR(MMSS_MDSS_BYTE0_INTF_CBCR), 
    262500, {HWIO_ADDR(MMSS_BYTE0_CMD_RCGR), MUX_MMSS, SRC_EXT1, 0, 0, 0, 0}},
  /* MMSS_BYTE1_GRP       mdss_byte1_clk     262.50  DSI1_PHYPLL_BYTE(src1) */
  {"mmss_mdss_byte1_clk", HWIO_ADDR(MMSS_MDSS_BYTE1_CBCR), 
    262500, {HWIO_ADDR(MMSS_BYTE1_CMD_RCGR), MUX_MMSS, SRC_EXT1, 0, 0, 0, 0}},
  {"mmss_mdss_byte1_intf_clk", HWIO_ADDR(MMSS_MDSS_BYTE1_INTF_CBCR), 
    262500, {HWIO_ADDR(MMSS_BYTE1_CMD_RCGR), MUX_MMSS, SRC_EXT1, 0, 0, 0, 0}},

  /* MMSS_ESC0_GRP        mdss_esc0_clk      19.20   XO                     */
  {"mmss_mdss_esc0_clk", HWIO_ADDR(MMSS_MDSS_ESC0_CBCR), 
    19200, {HWIO_ADDR(MMSS_ESC0_CMD_RCGR), MUX_MMSS, SRC_CXO, 0, 0, 0, 0}},
  /* MMSS_ESC1_GRP        mdss_esc1_clk      19.20   XO                     */
  {"mmss_mdss_esc1_clk", HWIO_ADDR(MMSS_MDSS_ESC1_CBCR),
    19200, {HWIO_ADDR(MMSS_ESC1_CMD_RCGR), MUX_MMSS, SRC_CXO, 0, 0, 0, 0}},

  /* MMSS_MDP_GRP         mdss_mdp_clk       330.00  MMPLL5(src2)           */
  {"mmss_mdss_mdp_clk", HWIO_ADDR(MMSS_MDSS_MDP_CBCR),
    330000, {HWIO_ADDR(MMSS_MDP_CMD_RCGR), MUX_MMSS, SRC_MMPLL5, DIV(2.5), 0, 0, 0}}, 
  /* MMSS_MDP_VSYNC_GRP   mdss_vsync_clk     19.20   XO                     */
  {"mmss_mdss_vsync_clk", HWIO_ADDR(MMSS_MDSS_VSYNC_CBCR),
    19200, {HWIO_ADDR(MMSS_VSYNC_CMD_RCGR), MUX_MMSS, SRC_CXO, 0, 0, 0, 0}}, 

  /* MMSS_NOC_AHB_GRP:DIV mdss_ahb_clk       80.00   MMPLL0                 */
  {"mmss_mdss_ahb_clk", HWIO_ADDR(MMSS_MDSS_AHB_CBCR),
    80800, {HWIO_ADDR(MMSS_AHB_CMD_RCGR), MUX_MMSS, SRC_MMPLL0, DIV(10), 0, 0, 0}}, 
  /* MMSS_NOC_AHB_GRP:DIV mmss_mdss_hdmi_ahb_clk  80.00   MMPLL0                 */
  {"mmss_mdss_hdmi_dp_ahb_clk", HWIO_ADDR(MMSS_MDSS_HDMI_DP_AHB_CBCR),
    80800, {HWIO_ADDR(MMSS_AHB_CMD_RCGR), MUX_MMSS, SRC_MMPLL0, DIV(10), 0, 0, 0}}, 
  /* MMSS_NOC_AXI_GRP:DIV mdss_axi_clk       320.00  MMPLL0                 */
  {"mmss_mdss_axi_clk", HWIO_ADDR(MMSS_MDSS_AXI_CBCR),
    323200, {HWIO_ADDR(MMSS_AXI_CMD_RCGR), MUX_MMSS, SRC_MMPLL0, DIV(2.5), 0, 0, 0}}, 

  /* MMSS_PCLK0_GRP       mdss_pclk0_clk     350.00  DSI0_PHYPLL_DSI(src1)  */
  {"mmss_mdss_pclk0_clk", HWIO_ADDR(MMSS_MDSS_PCLK0_CBCR),
    350000, {HWIO_ADDR(MMSS_PCLK0_CMD_RCGR), MUX_MMSS, SRC_EXT1, 0, 0, 0, 0}}, 
  /* MMSS_PCLK1_GRP       mdss_pclk1_clk     350.00  DSI1_PHYPLL_DSI(src2)  */
  {"mmss_mdss_pclk1_clk", HWIO_ADDR(MMSS_MDSS_PCLK1_CBCR),
    350000, {HWIO_ADDR(MMSS_PCLK1_CMD_RCGR), MUX_MMSS, SRC_EXT1, 0, 0, 0, 0}}, 

  {"mmss_mnoc_ahb_clk", HWIO_ADDR(MMSS_MNOC_AHB_CBCR), 
    80800, {HWIO_ADDR(MMSS_AHB_CMD_RCGR), MUX_MMSS, SRC_MMPLL0, DIV(10), 0, 0, 0}}, 
  {"mmss_mnoc_axi_clk", HWIO_ADDR(MMSS_MNOC_AXI_CBCR), 
    323200, {HWIO_ADDR(MMSS_AXI_CMD_RCGR), MUX_MMSS, SRC_MMPLL0, DIV(2.5), 0, 0, 0}}, 
  {"mmss_bimc_smmu_ahb_clk", HWIO_ADDR(MMSS_BIMC_SMMU_AHB_CBCR), 
    80800, {HWIO_ADDR(MMSS_AHB_CMD_RCGR), MUX_MMSS, SRC_MMPLL0, DIV(10), 0, 0, 0}}, 
  {"mmss_bimc_smmu_axi_clk", HWIO_ADDR(MMSS_BIMC_SMMU_AXI_CBCR), 
    323200, {HWIO_ADDR(MMSS_AXI_CMD_RCGR), MUX_MMSS, SRC_MMPLL0, DIV(2.5), 0, 0, 0}}, 
  {"mmss_s0_axi_clk", HWIO_ADDR(MMSS_S0_AXI_CBCR), 
    323200, {HWIO_ADDR(MMSS_AXI_CMD_RCGR), MUX_MMSS, SRC_MMPLL0, DIV(2.5), 0, 0, 0}}, 
  {"mmss_mdss_rot_clk", HWIO_ADDR(MMSS_MDSS_ROT_CBCR),
    330000, {HWIO_ADDR(MMSS_ROT_CMD_RCGR), MUX_MMSS, SRC_MMPLL5, DIV(2.5), 0, 0, 0}}, 
};


#define MAX_EXT_SRC 3
static const ClockSourceType Clock_RD_ReverseSourceMap[MAX_EXT_SRC] = 
{
  SRC_CXO,
  SRC_EXT1,
  SRC_EXT2,
};

/*=========================================================================
      Function Prototypes
==========================================================================*/


/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/

/*!

  This function initializes the MMSS clock sources.

  @dependencies
  None.

*/
static int Clock_RD_InitSources( void )
{
   if( Clock_EnablePLL(&Clock_RD_Plan.MPLL0_Cfg) != TRUE) return FALSE;
   if( Clock_EnablePLL(&Clock_RD_Plan.MPLL5_Cfg) != TRUE) return FALSE;

  return TRUE;
}

/* FUNCTION: Clock_RD_GetClockID
 *   Input Parameter: char *sClockName -- clock name to return the ID
 *   Return Value : 
 *     Success : A clock ID in the range 0 .. number_of_clocks
 *     Failure : -1
 */
int     Clock_RD_GetClockID( const char *sClockName)
{
  int i;

  if( sClockName == NULL) return -1;

  if(HWIO_INF(TCSR_SOC_HW_VERSION, DEVICE_NUMBER) == DEVICE_ID_SDM630)
  {
    if(! strcmp(sClockName, "mmss_mdss_byte1_clk")) 	 return -1;
    if(! strcmp(sClockName, "mmss_mdss_byte1_intf_clk")) return -1;
    if(! strcmp(sClockName, "mmss_mdss_esc1_clk"))       return -1;
    if(! strcmp(sClockName, "mmss_mdss_pclk1_clk"))      return -1;
  }
  for(i = 0; i< ARRAY_LEN(Clock_RD_MMSS_ClockCfg); i++)
  {
    if(! strcmp(sClockName, Clock_RD_MMSS_ClockCfg[i].sClockName))
    {
      return i;
    }
  }
  return -1;
};


/* FUNCTION: Clock_RD_EnableClock
 *   Input Parameter: int nClockID -- Use GetClockID() to return this for the clock in question 
 *   Return Value : TRUE=Success, FALSE=Failure or bad parameter
 * 
 * This assumes a standard CBCR (non-votable) with CLK_EN in bit 0 */
boolean Clock_RD_EnableClock( int nClockID )
{
  if( nClockID < 0 || nClockID >= ARRAY_LEN(Clock_RD_MMSS_ClockCfg)) return FALSE;

  return Clock_ToggleClock(Clock_RD_MMSS_ClockCfg[nClockID].nCBCRAddr, CLK_TOGGLE_ENABLE);
}


/* FUNCTION: Clock_RD_DisableClock
 *   Input Parameter: int nClockID -- Use GetClockID() to return this for the clock in question 
 *   Return Value : TRUE=Success, FALSE=Failure or bad parameter
 * 
 * This assumes a standard CBCR (non-votable) with CLK_EN in bit 0 */
boolean Clock_RD_DisableClock( int nClockID )
{
  if( nClockID < 0 || nClockID >= ARRAY_LEN(Clock_RD_MMSS_ClockCfg)) return FALSE;

  return Clock_ToggleClock(Clock_RD_MMSS_ClockCfg[nClockID].nCBCRAddr, CLK_TOGGLE_DISABLE);
}


/* FUNCTION: Clock_RD_IsClockEnabled
 *   Input Parameter: int nClockID -- Use GetClockID() to return this for the clock in question 
 *   Return Value : TRUE=clock is enabled, FALSE=clock is disable
 *
 * Note: This only tells you the state of the control.  After you enable a clock, it takes
 * a few cycles for it to turn on which will be indicated by IsClockOn().  If something
 * goes wrong with a clock enable, then it could be Enabled but not On, or Disabled but not Off.
 *
 * This assumes a standard CBCR (non-votable) with CLK_EN in bit 0 */
boolean Clock_RD_IsClockEnabled( int nClockID )
{
  if( nClockID < 0 || nClockID >= ARRAY_LEN(Clock_RD_MMSS_ClockCfg)) return FALSE;

  return (inp32(Clock_RD_MMSS_ClockCfg[nClockID].nCBCRAddr) & 0x1);
}


/* FUNCTION: Clock_RD_IsClockEnabled
 *   Input Parameter: int nClockID -- Use GetClockID() to return this for the clock in question 
 *   Return Value : TRUE=clock is on, FALSE=clock is off
 * 
 * This assumes a standard CBCR (non-votable) with CLK_OFF in bit 31 */
boolean Clock_RD_IsClockOn( int nClockID )
{
  if( nClockID < 0 || nClockID >= ARRAY_LEN(Clock_RD_MMSS_ClockCfg)) return FALSE;

  return (inp32(Clock_RD_MMSS_ClockCfg[nClockID].nCBCRAddr)>>31) == 0;
}

/* FUNCTION: Clock_RD_SetClockFreqKHz
 *   Input Parameter: nClockID -- Use GetClockID() to return this for the clock in question 
 *   Input Parameter: nFreqKHz -- The frequency to use.  If this frequency is either
 *     0 or 19200, CXO will be used.  Otherwise, the one frequency in the table is used.
 *   Return Value : TRUE=Success, FALSE=Failed
 *
 * This assumes a standard CBCR (non-votable) with CLK_OFF in bit 31 */
boolean Clock_RD_SetClockFreqKHz( int nClockID, uint32 nFreqKHz )
{
  ClockConfigMuxType muxConfig;

  /* One time initialize the MMSS PLLs */
  Clock_RD_InitSources();

  if( nClockID < 0 || nClockID >= ARRAY_LEN(Clock_RD_MMSS_ClockCfg)) return FALSE;
  muxConfig = Clock_RD_MMSS_ClockCfg[nClockID].sMuxCfg;

  /* This function has exactly two choices, 19200, or whatever is in the plan */
  if( (nFreqKHz == 19200) || (nFreqKHz == 0) ) 
  {
    muxConfig.eSource = 0;
    muxConfig.nDiv2x = 0;

    return Clock_ConfigMux(&muxConfig);
  }

  return Clock_ConfigMux(&Clock_RD_MMSS_ClockCfg[nClockID].sMuxCfg);
}


/* FUNCTION: Clock_RD_SetExternalSource
 *   Input Parameter: nClockID -- Use GetClockID() to return this for the clock in question 
 *   Input Parameter: nSource, nDivider, nM, nN, nD : This gives the client the ability 
 *    to choose their external source with a divider, similar to the DDIClock function.
 *
 *   Return Value : TRUE=Success, FALSE=Failed
 */
boolean Clock_RD_SelectExternalSource( int nClockID, uint32 nFreqHz, uint32 nSource, uint32  nDivider,
                                       uint32  nM,  uint32  nN,  uint32  n2D)
{
  ClockConfigMuxType muxConfig;
  ClockSourceType eSource = SRC_CXO;

  if( nClockID < 0 || nClockID >= ARRAY_LEN(Clock_RD_MMSS_ClockCfg)) return FALSE;

  if (nSource<MAX_EXT_SRC) eSource = Clock_RD_ReverseSourceMap[nSource];

  muxConfig = Clock_RD_MMSS_ClockCfg[nClockID].sMuxCfg;
  muxConfig.eSource = eSource;
  muxConfig.nDiv2x  = nDivider;
  muxConfig.nM      = nM;
  muxConfig.nN      = nN;
  muxConfig.n2D     = n2D;

  return Clock_ConfigMux(&muxConfig);
}


/* FUNCTION: Clock_RD_GetClockPowerDomainID
 *   Input Parameter: char *sClockName -- clock domain to return the ID
 *   Return Value : 
 *     Success : A clock ID in the range 0x1000 .. 0x1000+number_of_domains
 *     Failure : -1
 *   The Domain IDs are offset by DOMAIN_OFFSET (0x1000) to keep these distinct
 *   from the clock IDs which start at 0.
 */
int     Clock_RD_GetClockPowerDomainID( const char *sClockDomain )
{
  int i;

  if( sClockDomain == NULL) return -1;

  for(i = 0; i< ARRAY_LEN(Clock_RD_MMSS_Domains); i++)
  {
    if(! strcmp(sClockDomain, Clock_RD_MMSS_Domains[i].sDomainName))
    {
      return i + DOMAIN_OFFSET;
    }
  }
  return -1;
};


/* FUNCTION: Clock_RD_EnableClockPowerDomain
 *   Input Parameter: int nClockDomainID -- Use GetClockPowerDomainID() to get a valid ID
 *   Return Value : TRUE=Success, FALSE=Failed
 */
boolean Clock_RD_EnableClockPowerDomain( int nClockDomainID )
{
  int loops = 200;
  int i = nClockDomainID - DOMAIN_OFFSET;
  if( i < 0|| i >= ARRAY_LEN(Clock_RD_MMSS_Domains)) return FALSE;

  outp32(Clock_RD_MMSS_Domains[i].nGDSCRAddr, inp32(Clock_RD_MMSS_Domains[i].nGDSCRAddr) & ~0x1);

  while( (loops > 0) &&  ((inp32(Clock_RD_MMSS_Domains[i].nGDSCRAddr) >> 31) == 0)) {
    loops--;
    busywait(1);
  }
  return (loops != 0);
}


/* FUNCTION: Clock_RD_DisableClockPowerDomain
 *   Input Parameter: int nClockDomainID -- Use GetClockPowerDomainID() to get a valid ID
 *   Return Value : TRUE=Success, FALSE=Failed
 */
boolean Clock_RD_DisableClockPowerDomain( int nClockDomainID )
{
  int i = nClockDomainID - DOMAIN_OFFSET;
  if( i < 0 || i >= ARRAY_LEN(Clock_RD_MMSS_Domains)) return FALSE;

  outp32(Clock_RD_MMSS_Domains[i].nGDSCRAddr, inp32(Clock_RD_MMSS_Domains[i].nGDSCRAddr) | 0x1);

  return TRUE;
}

#if 0
/* I expect some fails here.  External sources will not be configured
 * during this test */
volatile int Clock_RD_successes = 0;
volatile int Clock_RD_fails = 0;

void Clock_RD_Test(void)
{
  int i, id;
  boolean result;

  /* Enable the Power Domains */
  for(i = 0; i< ARRAY_LEN(Clock_RD_MMSS_Domains); i++)
  {
    id = Clock_RD_GetClockPowerDomainID( Clock_RD_MMSS_Domains[i].sDomainName );
    result = Clock_RD_EnableClockPowerDomain( id );
    if(result == TRUE) { Clock_RD_successes++; } else { Clock_RD_fails++; };
    //boolean Clock_RD_DisableClockPowerDomain( int nClockDomainID )
  }

  /* Test the Clock APIs */
  for(i = 0; i< ARRAY_LEN(Clock_RD_MMSS_ClockCfg); i++)
  {
    id = Clock_RD_GetClockID(Clock_RD_MMSS_ClockCfg[i].sClockName);
    if(id >= 0) { Clock_RD_successes++; } else { Clock_RD_fails++; };

    result = Clock_RD_IsClockEnabled( id );
    if(result == FALSE) { Clock_RD_successes++; } else { Clock_RD_fails++; };
    result = Clock_RD_IsClockOn( id );
    if(result == FALSE) { Clock_RD_successes++; } else { Clock_RD_fails++; };
    result = Clock_RD_EnableClock( id );
    if(result == TRUE) { Clock_RD_successes++; } else { Clock_RD_fails++; };
    result = Clock_RD_IsClockEnabled( id );
    if(result == TRUE) { Clock_RD_successes++; } else { Clock_RD_fails++; };
    result = Clock_RD_IsClockOn( id );
    if(result == TRUE) { Clock_RD_successes++; } else { Clock_RD_fails++; };

    result = Clock_RD_DisableClock( id );
    if(result == TRUE) { Clock_RD_successes++; } else { Clock_RD_fails++; };
    result = Clock_RD_IsClockEnabled( id );
    if(result == FALSE) { Clock_RD_successes++; } else { Clock_RD_fails++; };
    result = Clock_RD_IsClockOn( id );
    if(result == FALSE) { Clock_RD_successes++; } else { Clock_RD_fails++; };

    result = Clock_RD_EnableClock( id );
    if(result == TRUE) { Clock_RD_successes++; } else { Clock_RD_fails++; };

    /* There is only one config, so you can give three things here.
     * 19200 (CXO) or 0 (also CXO) and anything else, which will select whatever 
     * it has in the table.  If the table lists CXO, you get CXO anyway. */
    if(Clock_RD_MMSS_ClockCfg[id].sMuxCfg.eSource != SRC_EXT1)
    {
      result = Clock_RD_SetClockFreqKHz(id, 100000); 
      if(result == TRUE) { Clock_RD_successes++; } else { Clock_RD_fails++; };
    }
   
  }

  // Unit testing ext clock sources is problematic because the DSI PLLs and such
  // are the property of the DSI driver and PHY and I cannot turn them on.
  {
    const char *ext_clocks[] =
    {
      "mmss_mdss_esc0_clk",
      "mmss_mdss_pclk0_clk",
      "mmss_mdss_byte0_clk",
      "mmss_mdss_byte0_intf_clk",
      "mmss_mdss_esc1_clk",
      "mmss_mdss_pclk1_clk",
      "mmss_mdss_byte1_clk",
      "mmss_mdss_byte1_intf_clk"
    };

    for(i = 0; i< ARRAY_LEN(ext_clocks); i++)
    {
      /* This will set 19.2 MHz */
      id = Clock_RD_GetClockID(ext_clocks[i]);
      result = Clock_RD_SelectExternalSource( id, 0, 0, 2, 0, 0, 0 );
      if(result == TRUE) { Clock_RD_successes++; } else { Clock_RD_fails++; };
    }
  }

  // Try source 1.  This will fail.
  id = Clock_RD_GetClockID( "mmss_mdss_byte0_intf_clk" );
  result = Clock_RD_SelectExternalSource( id, 0, 1, 2, 0, 0, 0 );
  if(result == TRUE) { Clock_RD_successes++; } else { Clock_RD_fails++; };

}
#endif
