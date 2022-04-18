/*
==============================================================================

FILE:         HALclkMNOCAXI.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   MNOCAXI clocks.

   List of clock domains:
     - HAL_clk_mMMSSAXIClkDomain


   List of power domains:



==============================================================================

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/HALclkLib/HALclkMNOCAXI.c#2 $

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

extern HAL_clk_ClockDomainControlType  HAL_clk_mMMSSClockDomainControl_8;
extern HAL_clk_ClockDomainControlType  HAL_clk_mMMSSClockDomainControlRO_8;


/* ============================================================================
**    Data
** ==========================================================================*/


/*                           
 *  HAL_clk_mAXIClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mAXIClkDomainClks[] =
{
  {
    /* .szClockName      = */ "mmss_bimc_smmu_axi_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_BIMC_SMMU_AXI_CBCR), HWIO_OFFS(MMSS_BIMC_SMMU_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_BIMC_SMMU_AXI_CLK
  },
  {
    /* .szClockName      = */ "mmss_camss_cpp_axi_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_CAMSS_CPP_AXI_CBCR), HWIO_OFFS(MMSS_CAMSS_CPP_TOP_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_CAMSS_CPP_AXI_CLK
  },
  {
    /* .szClockName      = */ "mmss_camss_jpeg_axi_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_CAMSS_JPEG_AXI_CBCR), HWIO_OFFS(MMSS_CAMSS_JPEG_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_CAMSS_JPEG_AXI_CLK
  },
  {
    /* .szClockName      = */ "mmss_camss_vfe_vbif_axi_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_CAMSS_VFE_VBIF_AXI_CBCR), HWIO_OFFS(MMSS_CAMSS_VFE_VBIF_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_CAMSS_VFE_VBIF_AXI_CLK
  },
  {
    /* .szClockName      = */ "mmss_mdss_axi_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_MDSS_AXI_CBCR), HWIO_OFFS(MMSS_MDSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_MDSS_AXI_CLK
  },
#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "mmss_mnoc_axi_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_MNOC_AXI_CBCR), HWIO_OFFS(MMSS_MNOCAXI_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_MNOC_AXI_CLK
  },
#endif

#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "mmss_s0_axi_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_S0_AXI_CBCR), HWIO_OFFS(MMSS_MNOCAXI_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_S0_AXI_CLK
  },
#endif

  {
    /* .szClockName      = */ "mmss_snoc_dvm_axi_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_SNOC_DVM_AXI_CBCR), HWIO_OFFS(MMSS_BIMC_SMMU_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_SNOC_DVM_AXI_CLK
  },
  {
    /* .szClockName      = */ "mmss_spdm_axi_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_SPDM_AXI_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_SPDM_AXI_CLK
  },
  {
    /* .szClockName      = */ "mmss_spdm_rm_axi_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_SPDM_RM_AXI_CBCR), HWIO_OFFS(MMSS_SPDM_RM_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_SPDM_RM_AXI_CLK
  },
  {
    /* .szClockName      = */ "mmss_throttle_camss_axi_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_THROTTLE_CAMSS_AXI_CBCR), HWIO_OFFS(MMSS_THROTTLE_CAMSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_THROTTLE_CAMSS_AXI_CLK
  },
  {
    /* .szClockName      = */ "mmss_throttle_mdss_axi_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_THROTTLE_MDSS_AXI_CBCR), HWIO_OFFS(MMSS_THROTTLE_MDSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_THROTTLE_MDSS_AXI_CLK
  },
  {
    /* .szClockName      = */ "mmss_throttle_video_axi_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_THROTTLE_VIDEO_AXI_CBCR), HWIO_OFFS(MMSS_THROTTLE_VIDEO_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_THROTTLE_VIDEO_AXI_CLK
  },
  {
    /* .szClockName      = */ "mmss_video_axi_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_VIDEO_AXI_CBCR), HWIO_OFFS(MMSS_VIDEO_TOP_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_VIDEO_AXI_CLK
  },
};


/*
 * HAL_clk_mMMSSAXIClkDomain
 *
 * AXI clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mMMSSAXIClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(MMSS_AXI_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mAXIClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mAXIClkDomainClks)/sizeof(HAL_clk_mAXIClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mMMSSClockDomainControlRO_8,
  /* .pmNextClockDomain    = */ NULL
};

