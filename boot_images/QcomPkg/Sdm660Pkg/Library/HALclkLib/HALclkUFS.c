/*
==============================================================================

FILE:         HALclkUFS.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   UFS clocks.

   List of clock domains:
     - HAL_clk_mGCCUFSAXIClkDomain
     - HAL_clk_mGCCUFSICECOREClkDomain
     - HAL_clk_mGCCUFSPHYAUXClkDomain
     - HAL_clk_mGCCUFSRXSYMBOL0ClkDomain
     - HAL_clk_mGCCUFSRXSYMBOL1ClkDomain
     - HAL_clk_mGCCUFSTXSYMBOL0ClkDomain
     - HAL_clk_mGCCUFSUNIPROCOREClkDomain


   List of power domains:
     - HAL_clk_mGCCUFSPowerDomain



==============================================================================

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/HALclkLib/HALclkUFS.c#3 $

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

static void HAL_clk_GCCUFSConfigMux       ( HAL_clk_ClockDomainDescType *pmClockDomainDesc, const HAL_clk_ClockMuxConfigType *pmConfig );
static void HAL_clk_GCCUFSDetectMuxConfig ( HAL_clk_ClockDomainDescType *pmClockDomainDesc, HAL_clk_ClockMuxConfigType *pmConfig );


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


static HAL_clk_SourceMapType aGCCUFSSourceMap[] =
{
  {HAL_CLK_SOURCE_EXTERNAL0,   0},
  {HAL_CLK_SOURCE_EXTERNAL1,   1},
  {HAL_CLK_SOURCE_EXTERNAL2,   2},
  {HAL_CLK_SOURCE_NULL,        HAL_CLK_SOURCE_INDEX_INVALID}
};

/*
 * HAL_clk_mGCCUFSClockDomainControl
 *
 * Functions for controlling GCC UFS clock domain
 */
HAL_clk_ClockDomainControlType HAL_clk_mGCCUFSClockDomainControl =
{
   /* .ConfigMux          = */ HAL_clk_GCCUFSConfigMux,
   /* .DetectMuxConfig    = */ HAL_clk_GCCUFSDetectMuxConfig,
   /* .pmSourceMap        = */ aGCCUFSSourceMap
};


/*                           
 *  HAL_clk_mUFSAXIClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mUFSAXIClkDomainClks[] =
{
  {
    /* .szClockName      = */ "gcc_aggre2_ufs_axi_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_AGGRE2_UFS_AXI_CBCR), HWIO_OFFS(GCC_AGGRE2_NOC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_AGGRE2_UFS_AXI_CLK
  },
  {
    /* .szClockName      = */ "gcc_ufs_axi_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_UFS_AXI_CBCR), HWIO_OFFS(GCC_UFS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_UFS_AXI_CLK
  },
};


/*
 * HAL_clk_mGCCUFSAXIClkDomain
 *
 * UFSAXI clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGCCUFSAXIClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(GCC_UFS_AXI_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mUFSAXIClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mUFSAXIClkDomainClks)/sizeof(HAL_clk_mUFSAXIClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGCCClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};


/*                           
 *  HAL_clk_mUFSICECOREClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mUFSICECOREClkDomainClks[] =
{
  {
    /* .szClockName      = */ "gcc_ufs_ice_core_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_UFS_ICE_CORE_CBCR), HWIO_OFFS(GCC_UFS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_UFS_ICE_CORE_CLK
  },
};


/*
 * HAL_clk_mGCCUFSICECOREClkDomain
 *
 * UFSICECORE clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGCCUFSICECOREClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(GCC_UFS_ICE_CORE_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mUFSICECOREClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mUFSICECOREClkDomainClks)/sizeof(HAL_clk_mUFSICECOREClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGCCClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};


/*                           
 *  HAL_clk_mUFSPHYAUXClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mUFSPHYAUXClkDomainClks[] =
{
  {
    /* .szClockName      = */ "gcc_ufs_phy_aux_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_UFS_PHY_AUX_CBCR), HWIO_OFFS(GCC_UFS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_UFS_PHY_AUX_CLK
  },
};


/*
 * HAL_clk_mGCCUFSPHYAUXClkDomain
 *
 * UFSPHYAUX clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGCCUFSPHYAUXClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(GCC_UFS_PHY_AUX_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mUFSPHYAUXClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mUFSPHYAUXClkDomainClks)/sizeof(HAL_clk_mUFSPHYAUXClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGCCClockDomainControl_1,
  /* .pmNextClockDomain    = */ NULL
};


/*                           
 *  HAL_clk_mUFSRXSYMBOL0ClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mUFSRXSYMBOL0ClkDomainClks[] =
{
  {
    /* .szClockName      = */ "gcc_ufs_rx_symbol_0_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_UFS_RX_SYMBOL_0_CBCR), HWIO_OFFS(GCC_UFS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_UFS_RX_SYMBOL_0_CLK
  },
};


/*
 * HAL_clk_mGCCUFSRXSYMBOL0ClkDomain
 *
 * UFSRXSYMBOL0 clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGCCUFSRXSYMBOL0ClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(GCC_UFS_RX_SYMBOL_0_MISC),
  /* .pmClocks             = */ HAL_clk_mUFSRXSYMBOL0ClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mUFSRXSYMBOL0ClkDomainClks)/sizeof(HAL_clk_mUFSRXSYMBOL0ClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGCCUFSClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};


/*                           
 *  HAL_clk_mUFSRXSYMBOL1ClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mUFSRXSYMBOL1ClkDomainClks[] =
{
  {
    /* .szClockName      = */ "gcc_ufs_rx_symbol_1_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_UFS_RX_SYMBOL_1_CBCR), HWIO_OFFS(GCC_UFS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_UFS_RX_SYMBOL_1_CLK
  },
};


/*
 * HAL_clk_mGCCUFSRXSYMBOL1ClkDomain
 *
 * UFSRXSYMBOL1 clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGCCUFSRXSYMBOL1ClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(GCC_UFS_RX_SYMBOL_1_MISC),
  /* .pmClocks             = */ HAL_clk_mUFSRXSYMBOL1ClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mUFSRXSYMBOL1ClkDomainClks)/sizeof(HAL_clk_mUFSRXSYMBOL1ClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGCCUFSClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};


/*                           
 *  HAL_clk_mUFSTXSYMBOL0ClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mUFSTXSYMBOL0ClkDomainClks[] =
{
  {
    /* .szClockName      = */ "gcc_ufs_tx_symbol_0_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_UFS_TX_SYMBOL_0_CBCR), HWIO_OFFS(GCC_UFS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_UFS_TX_SYMBOL_0_CLK
  },
};


/*
 * HAL_clk_mGCCUFSTXSYMBOL0ClkDomain
 *
 * UFSTXSYMBOL0 clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGCCUFSTXSYMBOL0ClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(GCC_UFS_TX_SYMBOL_0_MISC),
  /* .pmClocks             = */ HAL_clk_mUFSTXSYMBOL0ClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mUFSTXSYMBOL0ClkDomainClks)/sizeof(HAL_clk_mUFSTXSYMBOL0ClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGCCUFSClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};


/*                           
 *  HAL_clk_mUFSUNIPROCOREClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mUFSUNIPROCOREClkDomainClks[] =
{
  {
    /* .szClockName      = */ "gcc_ufs_unipro_core_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_UFS_UNIPRO_CORE_CBCR), HWIO_OFFS(GCC_UFS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_UFS_UNIPRO_CORE_CLK
  },
};


/*
 * HAL_clk_mGCCUFSUNIPROCOREClkDomain
 *
 * UFSUNIPROCORE clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGCCUFSUNIPROCOREClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(GCC_UFS_UNIPRO_CORE_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mUFSUNIPROCOREClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mUFSUNIPROCOREClkDomainClks)/sizeof(HAL_clk_mUFSUNIPROCOREClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGCCClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};


/*
 * HAL_clk_mGCCUFSPowerDomain
 *
 * UFS power domain.
 */
HAL_clk_PowerDomainDescType HAL_clk_mGCCUFSPowerDomain =
{
  /* .szPowerDomainName       = */ "VDD_UFS",
  /* .nGDSCRAddr              = */ HWIO_OFFS(GCC_UFS_GDSCR),
  /* .pmControl               = */ &HAL_clk_mGenericPowerDomainControl,
  /* .pmNextPowerDomain       = */ NULL
};


/* ===========================================================================
**  HAL_clk_GCCUFSConfigMux
**
** ======================================================================== */

static void HAL_clk_GCCUFSConfigMux
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
  nMiscRegVal &= ~HWIO_FMSK(GCC_UFS_RX_SYMBOL_0_MISC, SRC_SEL);

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
  nMiscRegVal |= ((nSourceIndex << HWIO_SHFT(GCC_UFS_RX_SYMBOL_0_MISC, SRC_SEL))
                                 & HWIO_FMSK(GCC_UFS_RX_SYMBOL_0_MISC, SRC_SEL));

  /*
   * Write the final MISC register value
   */
  outpdw(nMiscRegAddr, nMiscRegVal);

} /* END HAL_clk_GCCUFSConfigMux */


/* ===========================================================================
**  HAL_clk_GCCUFSDetectMuxConfig
**
** ======================================================================== */

static void HAL_clk_GCCUFSDetectMuxConfig
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
  nSourceIndex = (nMiscRegVal & HWIO_FMSK(GCC_UFS_RX_SYMBOL_0_MISC, SRC_SEL))
                             >> HWIO_SHFT(GCC_UFS_RX_SYMBOL_0_MISC, SRC_SEL);

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

} /* END HAL_clk_GCCUFSDetectMuxConfig */



