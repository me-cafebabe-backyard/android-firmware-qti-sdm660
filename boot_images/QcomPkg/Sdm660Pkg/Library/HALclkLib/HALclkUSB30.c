/*
==============================================================================

FILE:         HALclkUSB30.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   USB30 clocks.

   List of clock domains:
     - HAL_clk_mGCCUSB30MASTERClkDomain
     - HAL_clk_mGCCUSB30MOCKUTMIClkDomain
     - HAL_clk_mGCCUSB3PHYAUXClkDomain
     - HAL_clk_mGCCUSB3PHYPIPEClkDomain


   List of power domains:
     - HAL_clk_mGCCUSB30PowerDomain



==============================================================================

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/HALclkLib/HALclkUSB30.c#3 $

==============================================================================
            Copyright (c) 2016 QUALCOMM Technologies Incorporated.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
==============================================================================
*/

/*============================================================================

                     INCLUDE FILES FOR MODULE

============================================================================*/


#include <HALhwio.h>

#include "HALclkInternal.h"
#include "HALclkTest.h"
#include "HALclkGeneric.h"
#include "HALclkHWIO.h"


/*============================================================================

             DEFINITIONS AND DECLARATIONS FOR MODULE

=============================================================================*/


/* ============================================================================
**    Prototypes
** ==========================================================================*/

static void HAL_clk_GCCUSB3PHYConfigMux       ( HAL_clk_ClockDomainDescType *pmClockDomainDesc, const HAL_clk_ClockMuxConfigType *pmConfig );
static void HAL_clk_GCCUSB3PHYDetectMuxConfig ( HAL_clk_ClockDomainDescType *pmClockDomainDesc, HAL_clk_ClockMuxConfigType *pmConfig );

/* ============================================================================
**    Externs
** ==========================================================================*/

extern HAL_clk_ClockDomainControlType  HAL_clk_mGCCClockDomainControl;
extern HAL_clk_ClockDomainControlType  HAL_clk_mGCCClockDomainControlRO;
extern HAL_clk_ClockDomainControlType  HAL_clk_mGCCClockDomainControl_1;
extern HAL_clk_ClockDomainControlType  HAL_clk_mGCCClockDomainControlRO_1;


/* ============================================================================
**    Data
** ==========================================================================*/

static HAL_clk_SourceMapType aGCCUSB3PHYSourceMap[] =
{
  {HAL_CLK_SOURCE_EXTERNAL,    0},
  {HAL_CLK_SOURCE_PLLTEST,     1},
  {HAL_CLK_SOURCE_XO,          2},
  {HAL_CLK_SOURCE_NULL,        HAL_CLK_SOURCE_INDEX_INVALID}
};

/*
 * HAL_clk_mGCCUSB3PHYClockDomainControl
 *
 * Functions for controlling GCC USB3 PHY PIPE clock domains
 */
HAL_clk_ClockDomainControlType HAL_clk_mGCCUSB3PHYClockDomainControl =
{
   /* .ConfigMux          = */ HAL_clk_GCCUSB3PHYConfigMux,
   /* .DetectMuxConfig    = */ HAL_clk_GCCUSB3PHYDetectMuxConfig,
   /* .pmSourceMap        = */ aGCCUSB3PHYSourceMap
};


/*                           
 *  HAL_clk_mUSB30MASTERClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mUSB30MASTERClkDomainClks[] =
{
  {
    /* .szClockName      = */ "gcc_aggre2_usb3_axi_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_AGGRE2_USB3_AXI_CBCR), HWIO_OFFS(GCC_AGGRE2_NOC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_AGGRE2_USB3_AXI_CLK
  },
  {
    /* .szClockName      = */ "gcc_cfg_noc_usb3_axi_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_CFG_NOC_USB3_AXI_CBCR), HWIO_OFFS(GCC_CONFIG_NOC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_CFG_NOC_USB3_AXI_CLK
  },
#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_cnoc_bus_timeout14_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_CNOC_BUS_TIMEOUT14_AHB_CBCR), HWIO_OFFS(GCC_CNOC_BUS_TIMEOUT14_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_CNOC_BUS_TIMEOUT14_AHB_CLK
  },
#endif

  {
    /* .szClockName      = */ "gcc_usb30_master_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_USB30_MASTER_CBCR), HWIO_OFFS(GCC_USB_30_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_USB30_MASTER_CLK
  },
};


/*
 * HAL_clk_mGCCUSB30MASTERClkDomain
 *
 * USB30MASTER clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGCCUSB30MASTERClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(GCC_USB30_MASTER_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mUSB30MASTERClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mUSB30MASTERClkDomainClks)/sizeof(HAL_clk_mUSB30MASTERClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGCCClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};


/*                           
 *  HAL_clk_mUSB30MOCKUTMIClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mUSB30MOCKUTMIClkDomainClks[] =
{
  {
    /* .szClockName      = */ "gcc_usb30_mock_utmi_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_USB30_MOCK_UTMI_CBCR), HWIO_OFFS(GCC_USB_30_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_USB30_MOCK_UTMI_CLK
  },
};


/*
 * HAL_clk_mGCCUSB30MOCKUTMIClkDomain
 *
 * USB30MOCKUTMI clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGCCUSB30MOCKUTMIClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(GCC_USB30_MOCK_UTMI_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mUSB30MOCKUTMIClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mUSB30MOCKUTMIClkDomainClks)/sizeof(HAL_clk_mUSB30MOCKUTMIClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGCCClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};


/*                           
 *  HAL_clk_mUSB3PHYAUXClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mUSB3PHYAUXClkDomainClks[] =
{
  {
    /* .szClockName      = */ "gcc_usb3_phy_aux_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_USB3_PHY_AUX_CBCR), HWIO_OFFS(GCC_USB_30_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_USB3_PHY_AUX_CLK
  },
};


/*
 * HAL_clk_mGCCUSB3PHYAUXClkDomain
 *
 * USB3PHYAUX clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGCCUSB3PHYAUXClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(GCC_USB3_PHY_AUX_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mUSB3PHYAUXClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mUSB3PHYAUXClkDomainClks)/sizeof(HAL_clk_mUSB3PHYAUXClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGCCClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};


/*                           
 *  HAL_clk_mUSB3PHYPIPEClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mUSB3PHYPIPEClkDomainClks[] =
{
  {
    /* .szClockName      = */ "gcc_usb3_phy_pipe_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_USB3_PHY_PIPE_CBCR), HWIO_OFFS(GCC_USB_30_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_USB3_PHY_PIPE_CLK
  },
};


/*
 * HAL_clk_mGCCUSB3PHYPIPEClkDomain
 *
 * USB3PHYPIPE clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGCCUSB3PHYPIPEClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(GCC_USB3_PHY_PIPE_MISC),
  /* .pmClocks             = */ HAL_clk_mUSB3PHYPIPEClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mUSB3PHYPIPEClkDomainClks)/sizeof(HAL_clk_mUSB3PHYPIPEClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGCCUSB3PHYClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};


/*
 * HAL_clk_mGCCUSB30PowerDomain
 *
 * USB_30 power domain.
 */
HAL_clk_PowerDomainDescType HAL_clk_mGCCUSB30PowerDomain =
{
  /* .szPowerDomainName       = */ "VDD_USB_30",
  /* .nGDSCRAddr              = */ HWIO_OFFS(GCC_USB_30_GDSCR),
  /* .pmControl               = */ &HAL_clk_mGenericPowerDomainControl,
  /* .pmNextPowerDomain       = */ NULL
};

/*============================================================================

               FUNCTION DEFINITIONS FOR MODULE

============================================================================*/


/* ===========================================================================
**  HAL_clk_GCCUSB3PHYConfigMux
**
** ======================================================================== */

static void HAL_clk_GCCUSB3PHYConfigMux
(
  HAL_clk_ClockDomainDescType       *pmClockDomainDesc,
  const HAL_clk_ClockMuxConfigType  *pmConfig
)
{
  size_t                 nMiscRegAddr;
  uint32                 nMiscRegVal;
  uint32                 nSourceIndex = 0;
  HAL_clk_SourceMapType *pmSourceMap;

  /*
   * Sanity check
   */
  if((pmConfig                                    == NULL) ||
     (pmClockDomainDesc                           == NULL) ||
     (pmClockDomainDesc->nCGRAddr                 == 0   ) ||
     (pmClockDomainDesc->pmControl                == NULL) ||
     (pmClockDomainDesc->pmControl->pmSourceMap   == NULL) )
  {
    return;
  }

  /*
   * Get current MISC register value
   */
  nMiscRegAddr = pmClockDomainDesc->nCGRAddr;
  nMiscRegVal  = inpdw(nMiscRegAddr);

  /*
   * Clear the fields
   */
  nMiscRegVal &= ~HWIO_FMSK(GCC_USB3_PHY_PIPE_MISC, SRC_SEL);

  /*
   * Get source index from source enum
   */
  pmSourceMap = pmClockDomainDesc->pmControl->pmSourceMap;
  nSourceIndex = HAL_clk_GenericSourceMapToHW(pmSourceMap, pmConfig->eSource);

  /*
   * Bail if could not find matching source index
   */
  if (nSourceIndex == HAL_CLK_SOURCE_INDEX_INVALID)
  {
    return;
  }

  /*
   * Program the new source value.
   */
  nMiscRegVal |= ((nSourceIndex << HWIO_SHFT(GCC_USB3_PHY_PIPE_MISC, SRC_SEL))
                                 & HWIO_FMSK(GCC_USB3_PHY_PIPE_MISC, SRC_SEL));

  /*
   * Write the final MISC register value
   */
  outpdw(nMiscRegAddr, nMiscRegVal);

} /* END HAL_clk_GCCUSB3PHYConfigMux */


/* ===========================================================================
**  HAL_clk_GCCUSB3PHYDetectMuxConfig
**
** ======================================================================== */

static void HAL_clk_GCCUSB3PHYDetectMuxConfig
(
  HAL_clk_ClockDomainDescType *pmClockDomainDesc,
  HAL_clk_ClockMuxConfigType  *pmConfig
)
{
  size_t                 nMiscRegAddr;
  uint32                 nMiscRegVal, nSourceIndex;
  HAL_clk_SourceType     eSource;
  HAL_clk_SourceMapType *pmSourceMap;

  if (pmConfig == NULL)
  {
    return;
  }

  pmConfig->eSource = HAL_CLK_SOURCE_NULL;
  pmConfig->nDiv2x  = 0;
  pmConfig->n2D     = 0;
  pmConfig->nM      = 0;
  pmConfig->nN      = 0;

  /*
   * Sanity check
   */
  if((pmClockDomainDesc                           == NULL) ||
     (pmClockDomainDesc->nCGRAddr                 == 0   ) ||
     (pmClockDomainDesc->pmControl                == NULL) ||
     (pmClockDomainDesc->pmControl->pmSourceMap   == NULL) )
  {
    return;
  }

  /*
   * Get current MISC register value
   */
  nMiscRegAddr = pmClockDomainDesc->nCGRAddr;
  nMiscRegVal  = inpdw(nMiscRegAddr);

  /*
   * Get the source
   */
  nSourceIndex = (nMiscRegVal & HWIO_FMSK(GCC_USB3_PHY_PIPE_MISC, SRC_SEL))
                             >> HWIO_SHFT(GCC_USB3_PHY_PIPE_MISC, SRC_SEL);

  /*
   * Get source enum from source index
   */
  pmSourceMap = pmClockDomainDesc->pmControl->pmSourceMap;
  eSource = HAL_clk_GenericSourceMapFromHW(pmSourceMap, nSourceIndex);

  /*
   * Bail if could not find matching source enum
   */
  if (eSource == HAL_CLK_SOURCE_NULL)
  {
    return;
  }

  pmConfig->eSource = eSource;

} /* END HAL_clk_GCCUSB3PHYDetectMuxConfig */


