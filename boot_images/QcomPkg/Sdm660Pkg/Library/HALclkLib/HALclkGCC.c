/*
==============================================================================

FILE:         HALclkGCC.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   GCC clocks.

   List of clock domains:
     - HAL_clk_mGCCGCCSLEEPClkDomain
     - HAL_clk_mGCCGCCXOClkDomain


   List of power domains:



==============================================================================

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/HALclkLib/HALclkGCC.c#3 $

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
extern HAL_clk_ClockDomainControlType  HAL_clk_mGCCClockDomainControl_1;
extern HAL_clk_ClockDomainControlType  HAL_clk_mGCCClockDomainControlRO_1;


/* ============================================================================
**    Data
** ==========================================================================*/


/*                           
 *  HAL_clk_mGCCSLEEPClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mGCCSLEEPClkDomainClks[] =
{
#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_bimc_sleep_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_BIMC_SLEEP_CBCR), HWIO_OFFS(GCC_BIMC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_BIMC_SLEEP_CLK
  },
#endif

  {
    /* .szClockName      = */ "gcc_blsp1_sleep_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_BLSP1_SLEEP_CBCR), HWIO_OFFS(GCC_BLSP1_BCR), HAL_CLK_FMSK(PROC_CLK_BRANCH_ENA_VOTE, BLSP1_SLEEP_CLK_ENA) },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_BLSP1_SLEEP_CLK
  },
  {
    /* .szClockName      = */ "gcc_blsp2_sleep_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_BLSP2_SLEEP_CBCR), HWIO_OFFS(GCC_BLSP2_BCR), HAL_CLK_FMSK(PROC_CLK_BRANCH_ENA_VOTE, BLSP2_SLEEP_CLK_ENA) },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_BLSP2_SLEEP_CLK
  },
#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_ddr_dim_sleep_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_DDR_DIM_SLEEP_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_DDR_DIM_SLEEP_CLK
  },
#endif

#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_im_sleep_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_GCC_IM_SLEEP_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_IM_SLEEP_CLK
  },
#endif

#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_ipa_sleep_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_IPA_SLEEP_CBCR), HWIO_OFFS(GCC_IPA_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_IPA_SLEEP_CLK
  },
#endif

#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_rpm_sleep_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_RPM_SLEEP_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_RPM_SLEEP_CLK
  },
#endif

  {
    /* .szClockName      = */ "gcc_usb20_sleep_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_USB20_SLEEP_CBCR), HWIO_OFFS(GCC_USB_20_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_USB20_SLEEP_CLK
  },
  {
    /* .szClockName      = */ "gcc_usb30_sleep_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_USB30_SLEEP_CBCR), HWIO_OFFS(GCC_USB_30_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_USB30_SLEEP_CLK
  },
};


/*
 * HAL_clk_mGCCGCCSLEEPClkDomain
 *
 * GCCSLEEP clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGCCGCCSLEEPClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(GCC_GCC_SLEEP_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mGCCSLEEPClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mGCCSLEEPClkDomainClks)/sizeof(HAL_clk_mGCCSLEEPClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGCCClockDomainControlRO,
  /* .pmNextClockDomain    = */ NULL
};


/*                           
 *  HAL_clk_mGCCXOClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mGCCXOClkDomainClks[] =
{
#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_a2noc_throttle_cxo_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_A2NOC_THROTTLE_CXO_CBCR), HWIO_OFFS(GCC_AGGRE2_NOC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_A2NOC_THROTTLE_CXO_CLK
  },
#endif

#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_aggre2_noc_cxo_north_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_AGGRE2_NOC_CXO_NORTH_CBCR), HWIO_OFFS(GCC_AGGRE2_NOC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_AGGRE2_NOC_CXO_NORTH_CLK
  },
#endif

#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_aggre2_noc_cxo_south_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_AGGRE2_NOC_CXO_SOUTH_CBCR), HWIO_OFFS(GCC_AGGRE2_NOC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_AGGRE2_NOC_CXO_SOUTH_CLK
  },
#endif

#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_ahb2phy_east_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_AHB2PHY_EAST_CBCR), HWIO_OFFS(GCC_AHB2PHY_EAST_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_AHB2PHY_EAST_CLK
  },
#endif

  {
    /* .szClockName      = */ "gcc_cfg_noc_ah2phy_xo_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_CFG_NOC_AH2PHY_XO_CBCR), HWIO_OFFS(GCC_CONFIG_NOC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControlRO,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_CFG_NOC_AH2PHY_XO_CLK
  },
#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_cfg_noc_dcd_xo_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_CFG_NOC_DCD_XO_CBCR), HWIO_OFFS(GCC_CONFIG_NOC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_CFG_NOC_DCD_XO_CLK
  },
#endif

  {
    /* .szClockName      = */ "gcc_cfg_noc_north_dcd_xo_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_CFG_NOC_NORTH_DCD_XO_CBCR), HWIO_OFFS(GCC_CONFIG_NOC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControlRO,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_CFG_NOC_NORTH_DCD_XO_CLK
  },
  {
    /* .szClockName      = */ "gcc_cfg_noc_south_dcd_xo_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_CFG_NOC_SOUTH_DCD_XO_CBCR), HWIO_OFFS(GCC_CONFIG_NOC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControlRO,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_CFG_NOC_SOUTH_DCD_XO_CLK
  },
#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_cm_phy_refgen1_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_CM_PHY_REFGEN1_CBCR), HWIO_OFFS(GCC_CM_PHY_REFGEN1_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_CM_PHY_REFGEN1_CLK
  },
#endif

#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_cm_phy_refgen2_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_CM_PHY_REFGEN2_CBCR), HWIO_OFFS(GCC_CM_PHY_REFGEN2_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_CM_PHY_REFGEN2_CLK
  },
#endif

#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_cnoc_bus_timeout13_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_CNOC_BUS_TIMEOUT13_AHB_CBCR), HWIO_OFFS(GCC_CNOC_BUS_TIMEOUT13_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_CNOC_BUS_TIMEOUT13_AHB_CLK
  },
#endif

#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_glm_xo_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_GLM_XO_CBCR), HWIO_OFFS(GCC_GLM_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_GLM_XO_CLK
  },
#endif

#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_lpass_cxo_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_LPASS_CXO_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_LPASS_CXO_CLK
  },
#endif

  {
    /* .szClockName      = */ "gcc_pdm_xo4_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_PDM_XO4_CBCR), HWIO_OFFS(GCC_PDM_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_PDM_XO4_CLK
  },
#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_qdss_xo_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_QDSS_XO_CBCR), HWIO_OFFS(GCC_QDSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_QDSS_XO_CLK
  },
#endif

#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_qrefs_vbg_cal_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_QREFS_VBG_CAL_CBCR), HWIO_OFFS(GCC_QREFS_VBG_CAL_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_QREFS_VBG_CAL_CLK
  },
#endif

#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_rpm_timer_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_RPM_TIMER_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_RPM_TIMER_CLK
  },
#endif

#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_spdm_ff_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SPDM_FF_CBCR), HWIO_OFFS(GCC_SPDM_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_SPDM_FF_CLK
  },
#endif

#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_sram_sensor_xo_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SRAM_SENSOR_XO_CBCR), HWIO_OFFS(GCC_SRAM_SENSOR_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_SRAM_SENSOR_XO_CLK
  },
#endif

#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_sys_noc_dcd_xo_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SYS_NOC_DCD_XO_CBCR), HWIO_OFFS(GCC_SYSTEM_NOC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_SYS_NOC_DCD_XO_CLK
  },
#endif

#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_xo_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_GCC_XO_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_XO_CLK
  },
#endif

#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_xo_div4_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_GCC_XO_DIV4_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_XO_DIV4_CLK
  },
#endif

};


/*
 * HAL_clk_mGCCGCCXOClkDomain
 *
 * GCCXO clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGCCGCCXOClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(GCC_GCC_XO_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mGCCXOClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mGCCXOClkDomainClks)/sizeof(HAL_clk_mGCCXOClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGCCClockDomainControlRO_1,
  /* .pmNextClockDomain    = */ NULL
};

