/*
==============================================================================

FILE:         HALclkMNOCAHB.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   MNOCAHB clocks.

   List of clock domains:
     - HAL_clk_mMMSSAHBClkDomain


   List of power domains:



==============================================================================

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/HALclkLib/HALclkMNOCAHB.c#2 $

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

extern HAL_clk_ClockDomainControlType  HAL_clk_mMMSSClockDomainControl;
extern HAL_clk_ClockDomainControlType  HAL_clk_mMMSSClockDomainControlRO;


/* ============================================================================
**    Data
** ==========================================================================*/


/*                           
 *  HAL_clk_mAHBClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mAHBClkDomainClks[] =
{
  {
    /* .szClockName      = */ "mmss_bimc_smmu_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_BIMC_SMMU_AHB_CBCR), HWIO_OFFS(MMSS_BIMC_SMMU_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_BIMC_SMMU_AHB_CLK
  },
#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "mmss_bto_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_BTO_AHB_CBCR), HWIO_OFFS(MMSS_BTO_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_BTO_AHB_CLK
  },
#endif

  {
    /* .szClockName      = */ "mmss_camss_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_CAMSS_AHB_CBCR), HWIO_OFFS(MMSS_CAMSS_AHB_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_CAMSS_AHB_CLK
  },
  {
    /* .szClockName      = */ "mmss_camss_cci_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_CAMSS_CCI_AHB_CBCR), HWIO_OFFS(MMSS_CAMSS_CCI_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_CAMSS_CCI_AHB_CLK
  },
  {
    /* .szClockName      = */ "mmss_camss_cpp_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_CAMSS_CPP_AHB_CBCR), HWIO_OFFS(MMSS_CAMSS_CPP_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_CAMSS_CPP_AHB_CLK
  },
  {
    /* .szClockName      = */ "mmss_camss_cpp_vbif_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_CAMSS_CPP_VBIF_AHB_CBCR), HWIO_OFFS(MMSS_CAMSS_CPP_TOP_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_CAMSS_CPP_VBIF_AHB_CLK
  },
  {
    /* .szClockName      = */ "mmss_camss_csi0_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_CAMSS_CSI0_AHB_CBCR), HWIO_OFFS(MMSS_CAMSS_CSI0_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_CAMSS_CSI0_AHB_CLK
  },
  {
    /* .szClockName      = */ "mmss_camss_csi1_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_CAMSS_CSI1_AHB_CBCR), HWIO_OFFS(MMSS_CAMSS_CSI1_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_CAMSS_CSI1_AHB_CLK
  },
  {
    /* .szClockName      = */ "mmss_camss_csi2_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_CAMSS_CSI2_AHB_CBCR), HWIO_OFFS(MMSS_CAMSS_CSI2_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_CAMSS_CSI2_AHB_CLK
  },
  {
    /* .szClockName      = */ "mmss_camss_csi3_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_CAMSS_CSI3_AHB_CBCR), HWIO_OFFS(MMSS_CAMSS_CSI3_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_CAMSS_CSI3_AHB_CLK
  },
  {
    /* .szClockName      = */ "mmss_camss_ispif_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_CAMSS_ISPIF_AHB_CBCR), HWIO_OFFS(MMSS_CAMSS_ISPIF_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_CAMSS_ISPIF_AHB_CLK
  },
  {
    /* .szClockName      = */ "mmss_camss_jpeg_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_CAMSS_JPEG_AHB_CBCR), HWIO_OFFS(MMSS_CAMSS_JPEG_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_CAMSS_JPEG_AHB_CLK
  },
  {
    /* .szClockName      = */ "mmss_camss_micro_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_CAMSS_MICRO_AHB_CBCR), HWIO_OFFS(MMSS_CAMSS_MICRO_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_CAMSS_MICRO_AHB_CLK
  },
  {
    /* .szClockName      = */ "mmss_camss_top_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_CAMSS_TOP_AHB_CBCR), HWIO_OFFS(MMSS_CAMSS_TOP_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_CAMSS_TOP_AHB_CLK
  },
  {
    /* .szClockName      = */ "mmss_camss_vfe0_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_CAMSS_VFE0_AHB_CBCR), HWIO_OFFS(MMSS_CAMSS_VFE0_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_CAMSS_VFE0_AHB_CLK
  },
  {
    /* .szClockName      = */ "mmss_camss_vfe1_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_CAMSS_VFE1_AHB_CBCR), HWIO_OFFS(MMSS_CAMSS_VFE1_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_CAMSS_VFE1_AHB_CLK
  },
  {
    /* .szClockName      = */ "mmss_camss_vfe_vbif_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_CAMSS_VFE_VBIF_AHB_CBCR), HWIO_OFFS(MMSS_CAMSS_VFE_VBIF_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_CAMSS_VFE_VBIF_AHB_CLK
  },
  {
    /* .szClockName      = */ "mmss_csiphy_ahb2crif_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_CSIPHY_AHB2CRIF_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_CSIPHY_AHB2CRIF_CLK
  },
  {
    /* .szClockName      = */ "mmss_mdss_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_MDSS_AHB_CBCR), HWIO_OFFS(MMSS_MDSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_MDSS_AHB_CLK
  },
  {
    /* .szClockName      = */ "mmss_mdss_hdmi_dp_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_MDSS_HDMI_DP_AHB_CBCR), HWIO_OFFS(MMSS_MDSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_MDSS_HDMI_DP_AHB_CLK
  },
  {
    /* .szClockName      = */ "mmss_misc_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_MISC_AHB_CBCR), HWIO_OFFS(MMSS_MISC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_MISC_AHB_CLK
  },
  {
    /* .szClockName      = */ "mmss_mnoc_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_MNOC_AHB_CBCR), HWIO_OFFS(MMSS_MNOCAHB_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_MNOC_AHB_CLK
  },
  {
    /* .szClockName      = */ "mmss_spdm_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_SPDM_AHB_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_SPDM_AHB_CLK
  },
  {
    /* .szClockName      = */ "mmss_throttle_camss_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_THROTTLE_CAMSS_AHB_CBCR), HWIO_OFFS(MMSS_THROTTLE_CAMSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_THROTTLE_CAMSS_AHB_CLK
  },
  {
    /* .szClockName      = */ "mmss_throttle_mdss_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_THROTTLE_MDSS_AHB_CBCR), HWIO_OFFS(MMSS_THROTTLE_MDSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_THROTTLE_MDSS_AHB_CLK
  },
  {
    /* .szClockName      = */ "mmss_throttle_video_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_THROTTLE_VIDEO_AHB_CBCR), HWIO_OFFS(MMSS_THROTTLE_VIDEO_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_THROTTLE_VIDEO_AHB_CLK
  },
  {
    /* .szClockName      = */ "mmss_video_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_VIDEO_AHB_CBCR), HWIO_OFFS(MMSS_VIDEO_TOP_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_VIDEO_AHB_CLK
  },
};


/*
 * HAL_clk_mMMSSAHBClkDomain
 *
 * AHB clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mMMSSAHBClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(MMSS_AHB_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mAHBClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mAHBClkDomainClks)/sizeof(HAL_clk_mAHBClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mMMSSClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};

