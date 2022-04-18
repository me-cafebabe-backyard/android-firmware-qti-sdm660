/*
==============================================================================

FILE:         HALclkAPCS.c

DESCRIPTION:
  This file contains the clock HAL code to control the APCS clocks.


==============================================================================

                             Edit History


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
#include "HALclkAPCS.h"


/*============================================================================

             DEFINITIONS AND DECLARATIONS FOR MODULE

=============================================================================*/

/* ============================================================================
**    Prototypes
** ==========================================================================*/

static void HAL_clk_APCSConfigMux       (HAL_clk_ClockDomainDescType *pmClockDomainDesc, const HAL_clk_ClockMuxConfigType *pmConfig);
static void HAL_clk_APCSDetectMuxConfig (HAL_clk_ClockDomainDescType *pmClockDomainDesc, HAL_clk_ClockMuxConfigType  *pmConfig);


/* ============================================================================
**    Typedefs
** ==========================================================================*/

/*
 * HAL_clk_APCSClusterDomainDescType
 *
 */
typedef struct HAL_clk_APCSClusterDomainDescType
{
  HAL_clk_ClockDomainDescType mDomain; /* Must be first element. */
  const HAL_clk_APCSCPUType   eCPU;
} HAL_clk_APCSClusterDomainDescType;


/* ============================================================================
**    Data
** ==========================================================================*/

/*
 * aClusterSourceMap
 *
 * APCS cluster HW source mapping.
 */
static HAL_clk_SourceMapType aClusterSourceMap_0[] =
{
  {HAL_CLK_SOURCE_XO,                 0},
  {HAL_CLK_SOURCE_GPLL4,              1},
  {HAL_CLK_SOURCE_GPLL0,              4},
  {HAL_CLK_SOURCE_APCSPLL0,           5},
  {HAL_CLK_SOURCE_NULL,               HAL_CLK_SOURCE_INDEX_INVALID}
};
static HAL_clk_SourceMapType aClusterSourceMap_1[] =
{
  {HAL_CLK_SOURCE_XO,                 0},
  {HAL_CLK_SOURCE_GPLL4,              1},
  {HAL_CLK_SOURCE_GPLL0,              4},
  {HAL_CLK_SOURCE_APCSPLL1,           5},
  {HAL_CLK_SOURCE_NULL,               HAL_CLK_SOURCE_INDEX_INVALID}
};


/*
 * HAL_clk_mAPCSClusterDomainControl
 *
 * Functions for controlling APCS clock domains
 */
static HAL_clk_ClockDomainControlType HAL_clk_mAPCSClusterDomainControl_0 =
{
   /* .ConfigMux          = */ HAL_clk_APCSConfigMux,
   /* .DetectMuxConfig    = */ HAL_clk_APCSDetectMuxConfig,
   /* .pmSourceMap        = */ aClusterSourceMap_0,
};

static HAL_clk_ClockDomainControlType HAL_clk_mAPCSClusterDomainControl_1 =
{
   /* .ConfigMux          = */ HAL_clk_APCSConfigMux,
   /* .DetectMuxConfig    = */ HAL_clk_APCSDetectMuxConfig,
   /* .pmSourceMap        = */ aClusterSourceMap_1,
};
/*
 *  HAL_clk_mAPCSCluster0DomainClocks
 *
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mAPCSCluster0DomainClks[] =
{
  {
    /* .szClockName      = */ "apcs_cluster0_clk",
    /* .mRegisters       = */ { 0 },
    /* .pmControl        = */ NULL,
    /* .nTestClock       = */ HAL_CLK_APCS_TEST_CLUSTER0_CLK,
  },
};

/*
 * HAL_clk_mAPCSCluster0ClkDomain
 *
 * APCS cluster 0 clock domain.
 */
HAL_clk_APCSClusterDomainDescType HAL_clk_mAPCSCluster0ClkDomain =
{
  /* .mDomain = */
  {
    /* .nCGRAddr             = */ HWIO_OFFS(APCS_ALIAS0_CMD_RCGR),
    /* .pmClocks             = */ HAL_clk_mAPCSCluster0DomainClks,
    /* .nClockCount          = */ sizeof(HAL_clk_mAPCSCluster0DomainClks)/sizeof(HAL_clk_mAPCSCluster0DomainClks[0]),
    /* .pmControl            = */ &HAL_clk_mAPCSClusterDomainControl_0,
    /* .pmNextClockDomain    = */ NULL
  },

  /* .eCPU  = */ HAL_CLK_APCS_CPU_CLUSTER0
};


/*
 *  HAL_clk_mAPCSCluster1DomainClocks
 *
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mAPCSCluster1DomainClks[] =
{
  {
    /* .szClockName      = */ "apcs_cluster1_clk",
    /* .mRegisters       = */ { 0 },
    /* .pmControl        = */ NULL,
    /* .nTestClock       = */ HAL_CLK_APCS_TEST_CLUSTER1_CLK,
  },
};


/*
 * HAL_clk_mAPCSCluster1ClkDomain
 *
 * APCS cluster 1 clock domain.
 */
static HAL_clk_APCSClusterDomainDescType HAL_clk_mAPCSCluster1ClkDomain =
{
  /* .mDomain = */
  {
    /* .nCGRAddr             = */ HWIO_OFFS(APCS_ALIAS1_CMD_RCGR),
    /* .pmClocks             = */ HAL_clk_mAPCSCluster1DomainClks,
    /* .nClockCount          = */ sizeof(HAL_clk_mAPCSCluster1DomainClks)/sizeof(HAL_clk_mAPCSCluster1DomainClks[0]),
    /* .pmControl            = */ &HAL_clk_mAPCSClusterDomainControl_1,
    /* .pmNextClockDomain    = */ NULL
  },

  /* .eCPU  = */ HAL_CLK_APCS_CPU_CLUSTER1
};


/*
 *  HAL_clk_mAPCSCCIDomainClocks
 *
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mAPCSCCIDomainClks[] =
{
  {
    /* .szClockName      = */ "apcs_cci_clk",
    /* .mRegisters       = */ { 0 },
    /* .pmControl        = */ NULL,
    /* .nTestClock       = */ HAL_CLK_APCS_TEST_CCI_CLK,
  },
};


/*
 * HAL_clk_mAPCSCCIClkDomain
 *
 * APCS CCI clock domain.
 */
static HAL_clk_APCSClusterDomainDescType HAL_clk_mAPCSCCIClkDomain =
{
  /* .mDomain = */
  {
    /* .nCGRAddr             = */ 0,
    /* .pmClocks             = */ HAL_clk_mAPCSCCIDomainClks,
    /* .nClockCount          = */ sizeof(HAL_clk_mAPCSCCIDomainClks)/sizeof(HAL_clk_mAPCSCCIDomainClks[0]),
    /* .pmControl            = */ NULL,
    /* .pmNextClockDomain    = */ NULL
  },

  /* .eCPU  = */ HAL_CLK_APCS_CPU_CCI
};


/*============================================================================

               FUNCTION DEFINITIONS FOR MODULE

============================================================================*/

/* ===========================================================================
**  HAL_clk_IsClusterSource
**
** ======================================================================== */

static boolean HAL_clk_IsClusterSource
(
  HAL_clk_SourceType eSource
)
{
  return eSource >= HAL_CLK_SOURCE_BEGIN_CLUSTER_SOURCES &&
         eSource <= HAL_CLK_SOURCE_END_CLUSTER_SOURCES;

} /* END HAL_clk_IsClusterSource */


/* ===========================================================================
**  HAL_clk_APCSDetectMuxConfig
**
** ======================================================================== */

static void HAL_clk_APCSDetectMuxConfig
(
  HAL_clk_ClockDomainDescType *pmClockDomainDesc,
  HAL_clk_ClockMuxConfigType  *pmConfig
)
{
  HAL_clk_APCSClusterDomainDescType *pmAPCSClusterDomainDesc;
  HAL_clk_SourceMapType             *pmSourceMap;
  size_t                             nAddr;
  uint32                             nVal, nSel;

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

  pmAPCSClusterDomainDesc = (HAL_clk_APCSClusterDomainDescType *)pmClockDomainDesc;
  nAddr = pmClockDomainDesc->nCGRAddr + HAL_CLK_CFG_REG_OFFSET;
  nVal = inpdw(nAddr);

  nSel = (nVal &  HWIO_FMSK(APCS_ALIAS0_CFG_RCGR, SRC_SEL))
               >> HWIO_SHFT(APCS_ALIAS0_CFG_RCGR, SRC_SEL);

  pmSourceMap = pmClockDomainDesc->pmControl->pmSourceMap;
  pmConfig->eSource =
    HAL_clk_GenericSourceMapFromHW(pmSourceMap, nSel);

  /*
   * Map to cluster-specific PLL.
   */
  if (HAL_clk_IsClusterSource(pmConfig->eSource))
  {
    pmConfig->eSource += pmAPCSClusterDomainDesc->eCPU;
  }

  pmConfig->nDiv2x = ((nVal &  HWIO_FMSK(APCS_ALIAS0_CFG_RCGR, SRC_DIV))
                            >> HWIO_SHFT(APCS_ALIAS0_CFG_RCGR, SRC_DIV)) + 1;
  pmConfig->nM = 0;
  pmConfig->nN = 0;
  pmConfig->n2D = 0;

} /* END HAL_clk_APCSDetectMuxConfig */


/* ===========================================================================
**  HAL_clk_APCSConfigMux
**
** ======================================================================== */

static void HAL_clk_APCSConfigMux
(
  HAL_clk_ClockDomainDescType      *pmClockDomainDesc,
  const HAL_clk_ClockMuxConfigType *pmConfig
)
{
  HAL_clk_APCSClusterDomainDescType *pmAPCSClusterDomainDesc;
  HAL_clk_SourceType                 eSource;
  size_t                             nCmdCGRAddr, nCfgCGRAddr;
  uint32                             nCmdCGRVal, nCfgCGRVal;
  uint32                             nSourceIndex = 0;
  HAL_clk_SourceMapType             *pmSourceMap;

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

  pmAPCSClusterDomainDesc = (HAL_clk_APCSClusterDomainDescType *)pmClockDomainDesc;
  /*
   * Get current CMD and CFG register values
   */
  nCmdCGRAddr = pmClockDomainDesc->nCGRAddr;
  nCmdCGRVal  = inpdw(nCmdCGRAddr);
  nCfgCGRAddr = pmClockDomainDesc->nCGRAddr + HAL_CLK_CFG_REG_OFFSET;
  nCfgCGRVal  = inpdw(nCfgCGRAddr);

  /*
   * Clear the fields
   */
  nCfgCGRVal &= ~(HAL_CLK_CFG_CGR_SRC_SEL_FMSK |
                  HAL_CLK_CFG_CGR_SRC_DIV_FMSK |
                  HAL_CLK_CFG_CGR_MODE_FMSK);

  /*
   * Get source index from source enum
   */
  pmSourceMap = pmClockDomainDesc->pmControl->pmSourceMap;

  /*
   * There is only a source map for cluster 0.  Convert Cluster 1 specific
   * sources to the equivalent cluster 0 source.
   * Map from cluster-specfic PLL to cluster 0 PLL for the mapping lookup.
   */
  eSource = pmConfig->eSource;
  if (HAL_clk_IsClusterSource(eSource))
  {
    eSource -= pmAPCSClusterDomainDesc->eCPU;
  }

  nSourceIndex = HAL_clk_GenericSourceMapToHW(pmSourceMap, eSource);
  /*
   * Bail if could not find matching source index
   */
  if (nSourceIndex == HAL_CLK_SOURCE_INDEX_INVALID)
  {
    return;
  }

  /*
   * Program the source and divider values.
   */
  nCfgCGRVal |= ((nSourceIndex << HAL_CLK_CFG_CGR_SRC_SEL_SHFT) & HAL_CLK_CFG_CGR_SRC_SEL_FMSK);
  nCfgCGRVal |= ((HALF_DIVIDER(pmConfig) << HAL_CLK_CFG_CGR_SRC_DIV_SHFT)
                  & HAL_CLK_CFG_CGR_SRC_DIV_FMSK);
  /*
   * Write the final CFG register value
   */
  outpdw(nCfgCGRAddr, nCfgCGRVal);

  /*
   * Trigger the update
   */
  nCmdCGRVal |= HAL_CLK_CMD_CFG_UPDATE_FMSK;
  outpdw(nCmdCGRAddr, nCmdCGRVal);

  /*
   * Wait until update finishes
   */
  while(inpdw(nCmdCGRAddr) & HAL_CLK_CMD_CFG_UPDATE_FMSK);

} /* END HAL_clk_APCSConfigMux */

/* ===========================================================================
**  Function : HAL_clk_KPSSAXISleepEnable
**
** ======================================================================== */

void HAL_clk_KPSSAXISleepEnable(boolean bEnable)
{
  if (bEnable)
  {
  }
  else
  {
  }
} /* End HAL_clk_KPSSAXISleepEnable */


/* ===========================================================================
**  Function : HAL_clk_ApplyMemAccValue
**
** ======================================================================== */

void HAL_clk_ApplyMemAccValue
(
  HAL_clk_APCSCPUType eCore,
  HAL_clk_VRegLevelType eVRegLevelPrev,
  HAL_clk_VRegLevelType eVRegLevelNext
)
{
} /* End HAL_clk_ApplyMemAccValue */


/* ===========================================================================
**  HAL_clk_PlatformInitAPCSMain
**
** ======================================================================== */

void HAL_clk_PlatformInitAPCSMain (void)
{

  HAL_clk_InstallClockDomain(&HAL_clk_mAPCSCluster0ClkDomain.mDomain, HMSS_BASE);
  HAL_clk_InstallClockDomain(&HAL_clk_mAPCSCluster1ClkDomain.mDomain, HMSS_BASE);
  HAL_clk_InstallClockDomain(&HAL_clk_mAPCSCCIClkDomain.mDomain, HMSS_BASE);

} /* END HAL_clkPlatformInitAPCSMain */

