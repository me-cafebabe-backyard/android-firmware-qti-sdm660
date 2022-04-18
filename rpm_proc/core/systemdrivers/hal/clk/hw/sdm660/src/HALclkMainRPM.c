/*
==============================================================================

FILE:         HALclkMainRPM.c

DESCRIPTION:
  This file contains the main platform initialization code for the clock
  HAL on the RPM processor on MSM8998.

==============================================================================

                             Edit History

$Header: //components/rel/rpm.bf/1.8/core/systemdrivers/hal/clk/hw/sdm660/src/HALclkMainRPM.c#9 $

when       who     what, where, why
--------   ---     -----------------------------------------------------------
04/01/16   dai     Add QREFs to list of clocks turned off during deep sleep.
06/12/15   vph     Add MMSS for support rate matching.
11/27/13   vph     Initial version for MSM8994

==============================================================================
            Copyright (c) 2012-2015 QUALCOMM Technologies Incorporated.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
==============================================================================
*/

/*============================================================================

                     INCLUDE FILES FOR MODULE

============================================================================*/

#include <stdlib.h>
#include "HALclkInternal.h"
#include "HALclkGeneric.h"
#include "HALclkGenericPLL.h"
#include "HALhwio.h"
#include "HALclkHWIO.h"
#include "assert.h"
#include "Chipinfo.h"


/* List of clocks being turned off during deep sleep */
typedef struct
{
  boolean bSPMIClk;        /* gcc_spmi_ser_clk */
  boolean bHMSSAHBClk;     /* gcc_hmss_ahb_clk */
  boolean bMsgRAMClk;      /* gcc_msg_ram_ahb_clk */
  boolean bSecCtrlAccClk;  /* gcc_sec_ctrl_acc_clk */
  boolean bSecCtrlClk;     /* gcc_sec_ctrl_clk */
  boolean bSPMIAHBClk;     /* gcc_spmi_ahb_clk */
  boolean bDDRDimCfgClk;   /* gcc_ddr_dim_cfg_clk */
  boolean bDDRDimSleepClk; /* gcc_ddr_dim_sleep_clk */
  boolean bDCCAHBClk;      /* gcc_dcc_ahb_clk */
  boolean bUSBCfgAHB2PHYClk; /*gcc_usb_phy_cfg_ahb2phy_clk */
  boolean bWCSSEcahbClk;     /*gcc_wcss_ecahb_clk */
  boolean bWCSSShdregAhbClk; /*gcc_wcss_shdreg_ahb_clk */
  boolean bPIMEMClk;       /* gcc_pimem_axi_clk */
  boolean bSRAMSensorXOClk;  /* gcc_sram_sensor_xo_clk */
} HAL_MiscClkStateType;  


/* ============================================================================
**    Prototypes
** ==========================================================================*/

void HAL_clk_PlatformInitSources(void);


/* ============================================================================
**    Externs
** ==========================================================================*/

extern void HAL_clk_PlatformInitGCCMain(void);
extern void HAL_clk_PlatformInitMMSSMain(void);

/* ============================================================================
**    Data
** ==========================================================================*/
#define MAX_RETRY 120

static HAL_MiscClkStateType HAL_MiscClkState;

/*
 * HAL_clk_aInitFuncs
 *
 * Declare array of module initialization functions.
 */
static HAL_clk_InitFuncType HAL_clk_afInitFuncs[] =
{
  /*
   * Sources
   */
  HAL_clk_PlatformInitSources,
  
  /*
   * GCC
   */
  HAL_clk_PlatformInitGCCMain,

  /*
   * MMSS
   */
  HAL_clk_PlatformInitMMSSMain,

  NULL
};


/*
 * Declare the base pointers for HWIO access.
 */
uint32 HAL_clk_nHWIOBaseTop     = CLK_CTL_BASE_PHYS;
uint32 HAL_clk_nHWIOBaseTopMMSS = MMSS_BASE_PHYS;


/*
 * HAL_clk_aHWIOBases
 *
 * Declare array of HWIO bases in use on this platform.
 */
static HAL_clk_HWIOBaseType HAL_clk_aHWIOBases[] =
{
  { CLK_CTL_BASE_PHYS,  CLK_CTL_BASE_SIZE, &HAL_clk_nHWIOBaseTop },
  { MMSS_BASE_PHYS,     MMSS_BASE_SIZE,    &HAL_clk_nHWIOBaseTopMMSS },
  { 0, 0, NULL }
};


/*
 * HAL_clk_Platform;
 * Platform data.
 */
HAL_clk_PlatformType HAL_clk_Platform =
{
  HAL_clk_afInitFuncs,
  HAL_clk_aHWIOBases
};


/*
 * GPLL contexts
 */
static HAL_clk_PLLContextType HAL_clk_aPLLContextGPLL[] =
{
  {
    HWIO_OFFS(GCC_GPLL0_MODE),
    HAL_CLK_FMSK(GCC_RPM_GPLL_ENA_VOTE, GPLL0),
    HAL_CLK_PLL_SPARK
  },
  {
    HWIO_OFFS(GCC_GPLL1_MODE),
    HAL_CLK_FMSK(GCC_RPM_GPLL_ENA_VOTE, GPLL1),
    HAL_CLK_PLL_SPARK
  },
  {
    HWIO_OFFS(GCC_GPLL2_MODE),
    HAL_CLK_FMSK(GCC_RPM_GPLL_ENA_VOTE, GPLL2),
    HAL_CLK_PLL_SPARK
  },
  {
    HWIO_OFFS(GCC_GPLL3_MODE),
    HAL_CLK_FMSK(GCC_RPM_GPLL_ENA_VOTE, GPLL3),
    HAL_CLK_PLL_SPARK
  },
  {
    HWIO_OFFS(GCC_GPLL4_MODE),
    HAL_CLK_FMSK(GCC_RPM_GPLL_ENA_VOTE, GPLL4),
    HAL_CLK_PLL_SPARK
  },  
  {
    HWIO_OFFS(GCC_GPLL5_MODE),
    HAL_CLK_FMSK(GCC_RPM_GPLL_ENA_VOTE, GPLL5),
    HAL_CLK_PLL_SPARK
  },
  {
    HWIO_OFFS(MMSS_MMPLL0_PLL_MODE),
    HAL_CLK_FMSK(MMSS_PLL_VOTE_RPM, ENABLE_MMPLL0),
    HAL_CLK_PLL_SPARK
  },
  {
    HWIO_OFFS(MMSS_MMPLL1_PLL_MODE),
    HAL_CLK_FMSK(MMSS_PLL_VOTE_RPM, ENABLE_MMPLL1),
    HAL_CLK_PLL_SPARK
  },
  {
    HWIO_OFFS(MMSS_MMPLL6_PLL_MODE),
    HAL_CLK_FMSK(MMSS_PLL_VOTE_RPM, ENABLE_MMPLL6),
    HAL_CLK_PLL_SPARK
  }
};


/* ============================================================================
**    Functions
** ==========================================================================*/


/* ===========================================================================
**  HAL_clk_PlatformInitSources
**
** ======================================================================== */

void HAL_clk_PlatformInitSources (void)
{
  /*
   * Install PLL handlers.
   */
  HAL_clk_InstallPLL(
    HAL_CLK_SOURCE_GPLL0,   &HAL_clk_aPLLContextGPLL[0], CLK_CTL_BASE);

  HAL_clk_InstallPLL(
    HAL_CLK_SOURCE_GPLL1,   &HAL_clk_aPLLContextGPLL[1], CLK_CTL_BASE);

  HAL_clk_InstallPLL(
    HAL_CLK_SOURCE_GPLL2,   &HAL_clk_aPLLContextGPLL[2], CLK_CTL_BASE);

  HAL_clk_InstallPLL(
    HAL_CLK_SOURCE_GPLL3,   &HAL_clk_aPLLContextGPLL[3], CLK_CTL_BASE);

  HAL_clk_InstallPLL(
    HAL_CLK_SOURCE_GPLL4,   &HAL_clk_aPLLContextGPLL[4], CLK_CTL_BASE);

  HAL_clk_InstallPLL(
    HAL_CLK_SOURCE_GPLL5,   &HAL_clk_aPLLContextGPLL[5], CLK_CTL_BASE);
  
  HAL_clk_InstallPLL(
    HAL_CLK_SOURCE_MMPLL0,   &HAL_clk_aPLLContextGPLL[6], MMSS_BASE);
  
  HAL_clk_InstallPLL(
    HAL_CLK_SOURCE_MMPLL1,   &HAL_clk_aPLLContextGPLL[7], MMSS_BASE);

  HAL_clk_InstallPLL(
    HAL_CLK_SOURCE_MMPLL6,   &HAL_clk_aPLLContextGPLL[8], MMSS_BASE);

} /* END HAL_clk_PlatformInitSources */


/* ===========================================================================
**  HAL_clk_Save
**
** ======================================================================== */

void HAL_clk_Save (void)
{
  /*
   * Nothing to save.
   */

} /* END HAL_clk_Save */


/* ===========================================================================
**  HAL_clk_Restore
**
** ======================================================================== */

void HAL_clk_Restore (void)
{
  /*
	<Ener summary of changes here>
   * Nothing to restore.
   */
  
} /* END HAL_clk_Restore */


/* Loop over a table is appropriate to save space.
 * Each of these clocks has a CBCR with a CLK_OFF bit to poll when turned off, and a single
 * bit to enable it. Added QREF Clocks that share ENABLE and STATUS bits with same functionality.
 *
 * pStatusVar  : points to a status value that is used to hold the pre-shutdown state.
 * nCBCRReg    : the address of the CBCR register
 * nEnableReg  : the address of the enable register.
 * nEnableMask : the bit to set(enable) or clear(disable) the clock in the nEnableReg.
 */
const struct {
  boolean* pStatusVar;
  uint32   nCBCRReg;
  uint32   nEnableReg;
  uint32   nEnableMask;
} HAL_clk_DisableDuringSleep[] = 
{
#if 0
  { 
    &HAL_MiscClkState.bDDRDimCfgClk, 
    HWIO_ADDR(GCC_DDR_DIM_CFG_CBCR),
    HWIO_ADDR(GCC_DDR_DIM_CFG_CBCR),
    HWIO_FMSK(GCC_DDR_DIM_CFG_CBCR, CLK_ENABLE) 
  }, 
#endif  
  { 
    &HAL_MiscClkState.bDDRDimSleepClk, 
    HWIO_ADDR(GCC_DDR_DIM_SLEEP_CBCR),
    HWIO_ADDR(GCC_DDR_DIM_SLEEP_CBCR),
    HWIO_FMSK(GCC_DDR_DIM_SLEEP_CBCR, CLK_ENABLE) 
  },  
  { 
    &HAL_MiscClkState.bSPMIClk, 
    HWIO_ADDR(GCC_SPMI_SER_CBCR),
    HWIO_ADDR(GCC_SPMI_SER_CBCR),
    HWIO_FMSK(GCC_SPMI_SER_CBCR, CLK_ENABLE) 
  },  
  { 
    &HAL_MiscClkState.bHMSSAHBClk, 
    HWIO_ADDR(GCC_HMSS_AHB_CBCR),
    HWIO_ADDR(GCC_RPM_CLOCK_BRANCH_ENA_VOTE),
    HWIO_FMSK(GCC_RPM_CLOCK_BRANCH_ENA_VOTE, HMSS_AHB_CLK_ENA)
  },
  { &HAL_MiscClkState.bMsgRAMClk,
    HWIO_ADDR(GCC_MSG_RAM_AHB_CBCR),
    HWIO_ADDR(GCC_RPM_CLOCK_BRANCH_ENA_VOTE),
    HWIO_FMSK(GCC_RPM_CLOCK_BRANCH_ENA_VOTE, MSG_RAM_AHB_CLK_ENA)
  },
  { 
    &HAL_MiscClkState.bSecCtrlAccClk, 
    HWIO_ADDR(GCC_SEC_CTRL_ACC_CBCR),
    HWIO_ADDR(GCC_SEC_CTRL_ACC_CBCR),
    HWIO_FMSK(GCC_SEC_CTRL_ACC_CBCR, CLK_ENABLE) 
  },  
  { 
    &HAL_MiscClkState.bSecCtrlClk, 
    HWIO_ADDR(GCC_SEC_CTRL_CBCR),
    HWIO_ADDR(GCC_SEC_CTRL_CBCR),
    HWIO_FMSK(GCC_SEC_CTRL_CBCR, CLK_ENABLE) 
  },  
  { 
    &HAL_MiscClkState.bSPMIAHBClk, 
    HWIO_ADDR(GCC_SPMI_AHB_CBCR),
    HWIO_ADDR(GCC_SPMI_AHB_CBCR),
    HWIO_FMSK(GCC_SPMI_AHB_CBCR, CLK_ENABLE),
  },
  { 
    &HAL_MiscClkState.bUSBCfgAHB2PHYClk,
    HWIO_ADDR(GCC_USB_PHY_CFG_AHB2PHY_CBCR),
    HWIO_ADDR(GCC_USB_PHY_CFG_AHB2PHY_CBCR),
    HWIO_FMSK(GCC_USB_PHY_CFG_AHB2PHY_CBCR, CLK_ENABLE),
  },
  { 
    &HAL_MiscClkState.bWCSSEcahbClk,
    HWIO_ADDR(GCC_WCSS_ECAHB_CBCR),
    HWIO_ADDR(GCC_WCSS_ECAHB_CBCR),
    HWIO_FMSK(GCC_WCSS_ECAHB_CBCR, CLK_ENABLE),
  },
  { 
    &HAL_MiscClkState.bWCSSShdregAhbClk,
    HWIO_ADDR(GCC_WCSS_SHDREG_AHB_CBCR),
    HWIO_ADDR(GCC_WCSS_SHDREG_AHB_CBCR),
    HWIO_FMSK(GCC_WCSS_SHDREG_AHB_CBCR, CLK_ENABLE),
  },
  {
    &HAL_MiscClkState.bPIMEMClk, 
    HWIO_ADDR(GCC_PIMEM_AXI_CBCR),
    HWIO_ADDR(GCC_PIMEM_AXI_CBCR),
    HWIO_FMSK(GCC_PIMEM_AXI_CBCR, CLK_ENABLE),
  },
  {
    &HAL_MiscClkState.bSRAMSensorXOClk, 
    HWIO_ADDR(GCC_SRAM_SENSOR_XO_CBCR),
    HWIO_ADDR(GCC_SRAM_SENSOR_XO_CBCR),
    HWIO_FMSK(GCC_SRAM_SENSOR_XO_CBCR, CLK_ENABLE),
  },
};


/* ===========================================================================
**  HAL_clk_DeepSleepDisableMiscClk
** ======================================================================== */
void HAL_clk_DeepSleepDisableMiscClk(void)
{
  int i;
  boolean status;
  uint32 shadow;
  uint32 nRetry = 0;

//  HWIO_OUTF( PHY_REFGEN_EAST_BIAS_EN, PWRDN_B, 0 );  
//  HWIO_OUTF( PERIPH_SS_PHY_REFGEN_WEST_BIAS_EN, PWRDN_B, 0 );

  /* Enable all the clocks */
  for(i=0; i<sizeof( HAL_clk_DisableDuringSleep ) / sizeof( HAL_clk_DisableDuringSleep[0] ); i++)
  {
    status = ( (inpdw(HAL_clk_DisableDuringSleep[i].nCBCRReg) & HWIO_FMSK(GCC_SPMI_SER_CBCR, CLK_OFF)) ? FALSE : TRUE);
    *(HAL_clk_DisableDuringSleep[i].pStatusVar) = status;

    if ( status == TRUE )
    {
      /* Masked write to disable the clock */
      shadow = inpdw(HAL_clk_DisableDuringSleep[i].nEnableReg);
      shadow &= (~HAL_clk_DisableDuringSleep[i].nEnableMask);
      outpdw(HAL_clk_DisableDuringSleep[i].nEnableReg, shadow);
    }
  }

  /* Now wait for the statuses, this is faster */
  for(i=0; i<sizeof( HAL_clk_DisableDuringSleep ) / sizeof( HAL_clk_DisableDuringSleep[0] ); i++)
  {
    if( *HAL_clk_DisableDuringSleep[i].pStatusVar == TRUE )
    {
      // Test to make sure that clock gets turn off
      nRetry  = 0;
      while( ((inpdw(HAL_clk_DisableDuringSleep[i].nCBCRReg) & HWIO_FMSK(GCC_SPMI_SER_CBCR, CLK_OFF)) == 0) &&
             (nRetry < MAX_RETRY) )
      {
        nRetry++;
        HAL_clk_BusyWait( 1 );
      }
      assert (nRetry < MAX_RETRY);
    }
  }

  /*
   * Need to handle special case for GCC_DCC_AHB_CLK, 
   * since this clock has HW signal which forces on when JTAG connect
   * so it cannot handle like previous clocks.  Just clear CLK_ENABLE bit
   */
  HAL_MiscClkState.bDCCAHBClk = HWIO_INF( GCC_DCC_AHB_CBCR, CLK_ENABLE );
  if ( HAL_MiscClkState.bDCCAHBClk )
  {
    HWIO_OUTF( GCC_DCC_AHB_CBCR, CLK_ENABLE, 0 );
  }
}


/* ===========================================================================
**  HAL_clk_MiscClkRestoreDuringWakeup
** ======================================================================== */
void HAL_clk_MiscClkRestoreDuringWakeup(void)
{
  int i;
  uint32 shadow;

  /*
   * Need to handle special case for GCC_DCC_AHB_CLK, 
   * since this clock has HW signal which force on when JTAG connect, 
   * so it cannot handle like previous clocks.  Just set CLK_ENABLE bit back
   * if it was previous enabled
   */
  if ( HAL_MiscClkState.bDCCAHBClk )
  {
    HWIO_OUTF( GCC_DCC_AHB_CBCR, CLK_ENABLE, 1 );
  }

  /* Run them in the opposite order, as this is usually desired in shutdown / restart sequences */
  for(i= (sizeof( HAL_clk_DisableDuringSleep ) / sizeof( HAL_clk_DisableDuringSleep[0]))-1; i>=0; i--)
  {
    if( *HAL_clk_DisableDuringSleep[i].pStatusVar == TRUE )
    {
      /* Masked write to enable the clock */
      shadow = inpdw(HAL_clk_DisableDuringSleep[i].nEnableReg);
      shadow |= HAL_clk_DisableDuringSleep[i].nEnableMask;
      outpdw(HAL_clk_DisableDuringSleep[i].nEnableReg, shadow);
    }
  }

  for(i=(sizeof( HAL_clk_DisableDuringSleep ) / sizeof( HAL_clk_DisableDuringSleep[0] ))-1; i>=0; i--)
  {
    if( *HAL_clk_DisableDuringSleep[i].pStatusVar == TRUE )
    {
      /* Wait for clock to enable */
      while( (inpdw(HAL_clk_DisableDuringSleep[i].nCBCRReg) & HAL_CLK_BRANCH_CTRL_REG_CLK_OFF_FMSK) != 0 );
    }
  }
 // HWIO_OUTF( PHY_REFGEN_EAST_BIAS_EN, PWRDN_B, 1 ); 
 // HWIO_OUTF( PERIPH_SS_PHY_REFGEN_WEST_BIAS_EN, PWRDN_B, 1 );
}

 
/* ===========================================================================
**  HAL_clk_GetDeviceID
**
** ======================================================================== */
uint16 HAL_clk_GetDeviceID ( void )
{
  return HWIO_INF(TLMM_HW_REVISION_NUMBER, PRODUCT_DEVICE_ID);
} /* END HAL_clk_GetDeviceID */


/* ===========================================================================
**  HAL_clk_GPLL0_disable_deep_sleep
**
** ======================================================================== */
void HAL_clk_GPLL0_disable_deep_sleep(void)
{
  HWIO_OUTF(GCC_GPLL0_MODE, PLL_VOTE_FSM_ENA ,0);
  HWIO_OUTF(GCC_GPLL0_MODE, PLL_RESET_N ,0);
  HWIO_OUTF(GCC_GPLL0_MODE, PLL_OUTCTRL ,0);
}


/* ===========================================================================
**  HAL_clk_GPLL0_FSM_reset_deep_sleep
**
** ======================================================================== */
void HAL_clk_GPLL0_FSM_reset_deep_sleep(void)
{
  HWIO_OUTF(GCC_GPLL0_MODE, PLL_VOTE_FSM_RESET ,1);
  HWIO_OUTF(GCC_GPLL0_MODE, PLL_RESET_N ,0);
  HWIO_OUTF(GCC_GPLL0_MODE, PLL_OUTCTRL ,0);
   
  HAL_clk_BusyWait( 1 );
        
  HWIO_OUTF(GCC_GPLL0_MODE, PLL_VOTE_FSM_ENA ,1);
  
  HAL_clk_BusyWait( 1 );
  
  HWIO_OUTF(GCC_GPLL0_MODE, PLL_VOTE_FSM_RESET ,0);
}  

/* ===========================================================================
**  HAL_clk_IsDDRPLL0Active
**    Check the active DDR PLL is PLL0 or not
** ======================================================================== */
boolean HAL_clk_IsDDRPLL0Active ( void )
{
  return TRUE;//( HWIO_INF(GCC_BIMC_MISC, BIMC_DDR_JCPLL_SEL_STATUS) == 0 ); TODO
}

/* ===========================================================================
**  HAL_clk_CLKREF_restore
**
** ======================================================================== */
void HAL_clk_CLKREF_restore (boolean bEnable)
{
  HWIO_OUTF(GCC_RX2_QLINK_CLKREF_EN, RX2_QLINK_ENABLE, bEnable);
//  HWIO_OUTF(GCC_RX3_MODEM_CLKREF_EN, RX3_MODEM_ENABLE, bEnable);
}
#ifdef CLOCK_PSCBC_TEST
const uint32 HAL_PSCBC_addrs[] =
{
   HWIO_ADDR(GCC_BLSP1_AHB_CBCR),                                // 0x117004
   HWIO_ADDR(GCC_BLSP2_AHB_CBCR),                                // 0x125004
   HWIO_ADDR(GCC_BOOT_ROM_AHB_CBCR),                             // 0x138004
   HWIO_ADDR(GCC_CE1_CBCR),                                      // 0x141004
   HWIO_ADDR(GCC_DCC_AHB_CBCR),                                  // 0x184004
   HWIO_ADDR(GCC_GPU_BIMC_GFX_SRC_CBCR),                         // 0x17100c
   //HWIO_ADDR(GCC_IMEM_AXI_CBCR),                                 // 0x108004
   HWIO_ADDR(GCC_IPA_2X_CBCR),                                   // 0x189008
   HWIO_ADDR(GCC_IPA_CBCR),                                      // 0x18900c
//   HWIO_ADDR(GCC_LPASS_CORE_SMMU_CLIENT_SRC_CBCR),               // 0x147024
   HWIO_ADDR(GCC_LPASS_Q6_SMMU_AXI_SRC_CBCR),                    // 0x147004
   HWIO_ADDR(GCC_TURING_Q6_SMMU_AXI_SRC_CBCR),                    // 0x147004
   //HWIO_ADDR(GCC_MSG_RAM_AHB_CBCR),                              // 0x139004
   //HWIO_ADDR(GCC_PIMEM_AXI_CBCR),                                // 0x10a004
   HWIO_ADDR(GCC_QDSS_CENTER_AT_CBCR),                           // 0x10c00c
   // (always on with RPM CPU) HWIO_ADDR(GCC_RPM_BUS_AHB_CBCR),  // 0x13c004
   HWIO_ADDR(GCC_SDCC1_APPS_CBCR),                               // 0x114004
   HWIO_ADDR(GCC_SDCC2_APPS_CBCR),                               // 0x116004
   HWIO_ADDR(GCC_SDCC1_ICE_CORE_CBCR),                               // 0x116004
   //HWIO_ADDR(GCC_SEC_CTRL_ACC_CBCR),                             // 0x13d004
   //HWIO_ADDR(GCC_SEC_CTRL_CBCR),                                 // 0x13d00c
//   HWIO_ADDR(GCC_SMMU_AGGRE1_AXI_SRC_CBCR),                      // 0x182018
   HWIO_ADDR(GCC_SMMU_AGGRE2_AXI_SRC_CBCR),                      // 0x18301c
   //HWIO_ADDR(GCC_SPMI_AHB_CBCR),                                 // 0x13f00c
   //HWIO_ADDR(GCC_SPMI_SER_CBCR),                                 // 0x13f004
   HWIO_ADDR(GCC_SRAM_SENSOR_XO_CBCR),                           // 0x12d004
//   HWIO_ADDR(GCC_SYS_NOC_SSC_Q6_AXI_CBCR),                       // 0x163008
   HWIO_ADDR(GCC_TIC_CFG_AHB_CBCR),                              // 0x110000
//   HWIO_ADDR(GCC_TSIF_AHB_CBCR),                                 // 0x136004
   HWIO_ADDR(GCC_UFS_AXI_CBCR),                                  // 0x175008
   HWIO_ADDR(GCC_UFS_ICE_CORE_CBCR),                             // 0x17600c
   HWIO_ADDR(GCC_UFS_UNIPRO_CORE_CBCR),                          // 0x176008
   HWIO_ADDR(GCC_USB30_MASTER_CBCR),                             // 0x10f008
   HWIO_ADDR(GCC_USB20_MASTER_CBCR),                             // 0x10f008
};

/* To prevent storing data in the HAL, the API is as follows:
 * Make the first call as index = HAL_clk_CheckPSCBCs( 0, &badPSCBC)
 * Then loop until index is 0 to get the remaining PSCBCs that are left on
 */
int32 HAL_clk_CheckPSCBCs( uint32 index, uint32 *retPSCBCAddr, uint32 *retPSCBCValue )
{
  int i;
  uint32 nVal;

  for(i=index; i < sizeof(HAL_PSCBC_addrs)/sizeof(HAL_PSCBC_addrs[0]); i++)
  {
    nVal  = inpdw(HAL_PSCBC_addrs[i]);
    if( (nVal & HAL_CLK_BRANCH_CTRL_REG_CLK_OFF_FMSK) == 0)
    {
      *retPSCBCAddr = HAL_PSCBC_addrs[i];
      *retPSCBCValue = nVal;
      return i+1;
    }
  }
  // For loop finished with no more problems, return success.
  retPSCBCAddr = 0;
  return 0;
}
#endif


extern uint32 nPllSel[NUM_GPLLx_ASYNC_CLK_PLL_ID][2];

HAL_clk_SourceType 
HAL_clk_getDDRSources(const HAL_clk_ClockMuxConfigType *pmConfig)
{
  if(HAL_CLK_BIMC_DIV2X_DDR_GPLL0_SEL(pmConfig->nDiv2x) == 0)
  {
    return pmConfig->eSource;
  } 
  else
  {
    return (HAL_clk_SourceType)(nPllSel[HAL_CLK_BIMC_DIV2X_DDR_GPLL0_SEL(pmConfig->nDiv2x)][0]);
  }
}



HAL_clk_SourceType 
HAL_clk_getBIMCSources(const HAL_clk_ClockMuxConfigType *pmConfig)
{
  if(HAL_CLK_BIMC_M_BIMC_GPLL0_SEL(pmConfig->nM) == 0)
  {
    return pmConfig->eSource;
  } 
  else
  {
    return (HAL_clk_SourceType)(nPllSel[HAL_CLK_BIMC_M_BIMC_GPLL0_SEL(pmConfig->nM)][0]);
  }
}

HAL_clk_SourceType 
HAL_clk_getHMSSSources(const HAL_clk_ClockMuxConfigType *pmConfig)
{
  if(HAL_CLK_BIMC_M_HMSS_GPLL0_SEL(pmConfig->nM) == 0)
  {
    return pmConfig->eSource;
  } 
  else
  {
    return (HAL_clk_SourceType)(nPllSel[HAL_CLK_BIMC_M_HMSS_GPLL0_SEL(pmConfig->nM)][0]);
  }
}

HAL_clk_SourceType 
HAL_clk_getGFXSources(const HAL_clk_ClockMuxConfigType *pmConfig)
{

  if(HAL_CLK_BIMC_N_GFX_GPLL0_SEL(pmConfig->nN) == 0)
  {
    return pmConfig->eSource;
  } 
  else
  {
    return (HAL_clk_SourceType)(nPllSel[HAL_CLK_BIMC_N_GFX_GPLL0_SEL(pmConfig->nN)][0]);
  }
}

HAL_clk_SourceType 
HAL_clk_getMPSSSources(const HAL_clk_ClockMuxConfigType *pmConfig)
{

  if(HAL_CLK_BIMC_N_MPSS_GPLL0_SEL(pmConfig->nN) == 0)
  {
    return pmConfig->eSource;
  } 
  else
  {
    return (HAL_clk_SourceType)(nPllSel[HAL_CLK_BIMC_N_MPSS_GPLL0_SEL(pmConfig->nN)][0]);
  }
}

HAL_clk_SourceType 
HAL_clk_get_CDSPSources(const HAL_clk_ClockMuxConfigType *pmConfig)
{

  if(HAL_CLK_BIMC_DIV2X_CDSP_GPLL0_SEL(pmConfig->nDiv2x) == 0)
  {
    return pmConfig->eSource;
  } 
  else
  {
    return (HAL_clk_SourceType)(nPllSel[HAL_CLK_BIMC_DIV2X_CDSP_GPLL0_SEL(pmConfig->nDiv2x)][0]);
  }
}


#define OFFS_ADDR           0x60000000

#define NUM_WAITS           10
#define WAIT_TIME           20
#define DELAY_TIME          100
#define IPA_SAVE_SUCCESS    0xFADEFADE
#define IPA_SAVE_FAIL       0x0BADFADE
#define IPA_RESTORE_SUCCESS 0xCAFECAFE
#define IPA_RESTORE_FAIL    0x0BADCAFE
#define IPA_RESTORE_INTR    0xFADECAFE

static uint32 nIPASave = 0;
static uint32 nIPARestore = 0;
static uint32 nIPASaveTimes = 0;
//static uint32 nIPARestoreTimes = 0;

typedef enum
{
  IPA_SAVE_ENTER = 0,
  IPA_SAVE_COMPLETE,
  IPA_RESTORE_ENTER,
  IPA_RESTORE_COMPLETE,
  IPA_RESTORE_PW_ENABLED,
  IPA_RESTORE_IN_LOOP,
  IPA_RESTORE_OUT_LOOP,
  IPA_RESTORE_BEFORE_WAIT
}ipa_pc_state_e;

ipa_pc_state_e pc_state;




void HAL_clk_IPAGating(boolean bIPAGating)
{
  if(!bIPAGating) //ungate here; while enablong clock
  {

    pc_state = IPA_RESTORE_ENTER;

  //  HAL_clk_BusyWait( DELAY_TIME );

    // Write to MBOX for trigger interrupt to uC
    HWIO_OUTI2( IPA_0_IPA_UC_MAILBOX_m_n, 0, 18, IPA_RESTORE_INTR); //m=0, n=18

    // Keep track number of IPA Restore for debug purpose
    nIPARestore++;
    pc_state = IPA_RESTORE_COMPLETE;
  }
  else //Gate here, while disabling the clock
  {

    nIPASaveTimes = NUM_WAITS;
    pc_state = IPA_SAVE_ENTER;

    // Invalidate mailbox 17 before polling
    HWIO_OUTI2( IPA_0_IPA_UC_MAILBOX_m_n, 0, 17, 0 );

    // Write to MBOX for trigger interrupt to uC
    HWIO_OUTI2( IPA_0_IPA_UC_MAILBOX_m_n, 0, 16, HWIO_ADDRI2(IPA_0_IPA_UC_MAILBOX_m_n, 0, 17) - OFFS_ADDR );

    while ( (HWIO_INI2(IPA_0_IPA_UC_MAILBOX_m_n, 0, 17) != IPA_SAVE_SUCCESS) && nIPASaveTimes--  )
    {
      HAL_clk_BusyWait( WAIT_TIME );
    }

    assert( HWIO_INI2(IPA_0_IPA_UC_MAILBOX_m_n, 0, 17) == IPA_SAVE_SUCCESS );

    // Keep track number of IPA Save for debug purpose
    nIPASave++;

    pc_state = IPA_SAVE_COMPLETE;
  }

}

/*nDualChannelDDR=1: Its single channel DDR
 nDualChannelDDR=2: Its dual channel DDR
 */
unsigned int nDualChannelDDR = 2;
#define GET_25_26_BIT(val) ((val>>25)&3)

/*return 2 for dual channle, 1 for single channel*/
unsigned int HALGetSLActiveCH(void)
{

  if(HAL_clk_GetChipFamily() == CHIPINFO_FAMILY_SDM660)
  {
    /*[25,26] bits valid for SL, will give 0 for MSM1.0[single channle], rest of the cases it is dual channel*/
    if(GET_25_26_BIT(inpdw(HWIO_ADDR(QFPROM_RAW_CALIB_ROW5_MSB))) == 0)
    {
      nDualChannelDDR = 1;
    }
  }
  return nDualChannelDDR;
}

