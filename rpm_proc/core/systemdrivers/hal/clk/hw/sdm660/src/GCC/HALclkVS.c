/*
==============================================================================

FILE:         HALclkVS.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   VS clocks.

   List of clock domains:
    - HAL_clk_mGCCAPC0VSClkDomain
    - HAL_clk_mGCCAPC0VSPLL0ClkDomain
    - HAL_clk_mGCCAPC1VSClkDomain
    - HAL_clk_mGCCAPC1VSPLL0ClkDomain
    - HAL_clk_mGCCMSSVSClkDomain
    - HAL_clk_mGCCMSSVSPLL0ClkDomain
    - HAL_clk_mGCCVDDAVSClkDomain
    - HAL_clk_mGCCVDDAVSPLL0ClkDomain
    - HAL_clk_mGCCVDDCXVSClkDomain
    - HAL_clk_mGCCVDDCXVSPLL0ClkDomain
    - HAL_clk_mGCCVDDMXVSClkDomain
    - HAL_clk_mGCCVDDMXVSPLL0ClkDomain
    - HAL_clk_mGCCVSCTRLClkDomain
    - HAL_clk_mGCCWCSSVSClkDomain
    - HAL_clk_mGCCWCSSVSPLL0ClkDomain


   List of power domains:



==============================================================================

$Header: //components/rel/rpm.bf/1.8/core/systemdrivers/hal/clk/hw/sdm660/src/GCC/HALclkVS.c#1 $

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


/* ============================================================================
**    Externs
** ==========================================================================*/

extern HAL_clk_ClockDomainControlType  HAL_clk_mGCCClockDomainControl;
extern HAL_clk_ClockDomainControlType  HAL_clk_mGCCClockDomainControlRO;


/* ============================================================================
**    Data
** ==========================================================================*/


/*                           
 *  HAL_clk_mAPC0VSClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mAPC0VSClkDomainClks[] =
{
  {
    /* .szClockName      = */ "gcc_apc0_vs_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_APC0_VS_CBCR), HWIO_OFFS(GCC_VS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_APC0_VS_CLK
  },
};


/*
 * HAL_clk_mGCCAPC0VSClkDomain
 *
 * APC0VS clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGCCAPC0VSClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(GCC_APC0_VS_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mAPC0VSClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mAPC0VSClkDomainClks)/sizeof(HAL_clk_mAPC0VSClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGCCClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};


/*                           
 *  HAL_clk_mAPC1VSClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mAPC1VSClkDomainClks[] =
{
  {
    /* .szClockName      = */ "gcc_apc1_vs_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_APC1_VS_CBCR), HWIO_OFFS(GCC_VS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_APC1_VS_CLK
  },
};


/*
 * HAL_clk_mGCCAPC1VSClkDomain
 *
 * APC1VS clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGCCAPC1VSClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(GCC_APC1_VS_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mAPC1VSClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mAPC1VSClkDomainClks)/sizeof(HAL_clk_mAPC1VSClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGCCClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};




/*                           
 *  HAL_clk_mMSSVSClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mMSSVSClkDomainClks[] =
{
  {
    /* .szClockName      = */ "gcc_mss_vs_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_MSS_VS_CBCR), HWIO_OFFS(GCC_VS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_MSS_VS_CLK
  },
};


/*
 * HAL_clk_mGCCMSSVSClkDomain
 *
 * MSSVS clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGCCMSSVSClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(GCC_MSS_VS_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mMSSVSClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mMSSVSClkDomainClks)/sizeof(HAL_clk_mMSSVSClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGCCClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};


/*                           
 *  HAL_clk_mVDDAVSClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mVDDAVSClkDomainClks[] =
{
  {
    /* .szClockName      = */ "gcc_vdda_vs_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_VDDA_VS_CBCR), HWIO_OFFS(GCC_VS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_VDDA_VS_CLK
  },
};


/*
 * HAL_clk_mGCCVDDAVSClkDomain
 *
 * VDDAVS clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGCCVDDAVSClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(GCC_VDDA_VS_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mVDDAVSClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mVDDAVSClkDomainClks)/sizeof(HAL_clk_mVDDAVSClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGCCClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};


/*                           
 *  HAL_clk_mVDDCXVSClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mVDDCXVSClkDomainClks[] =
{
  {
    /* .szClockName      = */ "gcc_vddcx_vs_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_VDDCX_VS_CBCR), HWIO_OFFS(GCC_VS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_VDDCX_VS_CLK
  },
};


/*
 * HAL_clk_mGCCVDDCXVSClkDomain
 *
 * VDDCXVS clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGCCVDDCXVSClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(GCC_VDDCX_VS_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mVDDCXVSClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mVDDCXVSClkDomainClks)/sizeof(HAL_clk_mVDDCXVSClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGCCClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};


/*                           
 *  HAL_clk_mVDDMXVSClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mVDDMXVSClkDomainClks[] =
{
  {
    /* .szClockName      = */ "gcc_vddmx_vs_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_VDDMX_VS_CBCR), HWIO_OFFS(GCC_VS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_VDDMX_VS_CLK
  },
};


/*
 * HAL_clk_mGCCVDDMXVSClkDomain
 *
 * VDDMXVS clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGCCVDDMXVSClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(GCC_VDDMX_VS_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mVDDMXVSClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mVDDMXVSClkDomainClks)/sizeof(HAL_clk_mVDDMXVSClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGCCClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};


/*                           
 *  HAL_clk_mVSCTRLClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mVSCTRLClkDomainClks[] =
{
  {
    /* .szClockName      = */ "gcc_vs_ctrl_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_VS_CTRL_CBCR), HWIO_OFFS(GCC_VS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_VS_CTRL_CLK
  },
};


/*
 * HAL_clk_mGCCVSCTRLClkDomain
 *
 * VSCTRL clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGCCVSCTRLClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(GCC_VS_CTRL_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mVSCTRLClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mVSCTRLClkDomainClks)/sizeof(HAL_clk_mVSCTRLClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGCCClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};


/*
 *  HAL_clk_mWCSSVSClkDomainClks
 *
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mWCSSVSClkDomainClks[] =
{
  {
    /* .szClockName      = */ "gcc_wcss_vs_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_WCSS_VS_CBCR), HWIO_OFFS(GCC_VS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_WCSS_VS_CLK
  },
};


/*
 * HAL_clk_mGCCWCSSVSClkDomain
 *
 * WCSSVS clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGCCWCSSVSClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(GCC_WCSS_VS_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mWCSSVSClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mWCSSVSClkDomainClks)/sizeof(HAL_clk_mWCSSVSClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGCCClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};

