/*
==============================================================================

FILE:         HALclkCONFIGNOC.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   CONFIGNOC clocks.

   List of clock domains:
     - HAL_clk_mGCCCNOCPERIPHClkDomain
     - HAL_clk_mGCCCONFIGNOCClkDomain


   List of power domains:



==============================================================================

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/HALclkLib/HALclkCONFIGNOC.c#3 $

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
 *  HAL_clk_mCNOCPERIPHClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mCNOCPERIPHClkDomainClks[] =
{
  {
    /* .szClockName      = */ "gcc_aggre2_cnoc_north_periph_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_AGGRE2_CNOC_NORTH_PERIPH_AHB_CBCR), HWIO_OFFS(GCC_AGGRE2_NOC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControlRO,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_AGGRE2_CNOC_NORTH_PERIPH_AHB_CLK
  },
  {
    /* .szClockName      = */ "gcc_aggre2_cnoc_periph_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_AGGRE2_CNOC_PERIPH_AHB_CBCR), HWIO_OFFS(GCC_AGGRE2_NOC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControlRO,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_AGGRE2_CNOC_PERIPH_AHB_CLK
  },
  {
    /* .szClockName      = */ "gcc_aggre2_cnoc_south_periph_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_AGGRE2_CNOC_SOUTH_PERIPH_AHB_CBCR), HWIO_OFFS(GCC_AGGRE2_NOC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControlRO,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_AGGRE2_CNOC_SOUTH_PERIPH_AHB_CLK
  },
  {
    /* .szClockName      = */ "gcc_blsp1_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_BLSP1_AHB_CBCR), HWIO_OFFS(GCC_BLSP1_BCR), HAL_CLK_FMSK(PROC_CLK_BRANCH_ENA_VOTE, BLSP1_AHB_CLK_ENA) },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_BLSP1_AHB_CLK
  },
  {
    /* .szClockName      = */ "gcc_blsp2_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_BLSP2_AHB_CBCR), HWIO_OFFS(GCC_BLSP2_BCR), HAL_CLK_FMSK(PROC_CLK_BRANCH_ENA_VOTE, BLSP2_AHB_CLK_ENA) },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_BLSP2_AHB_CLK
  },
#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_cnoc_bus_timeout0_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_CNOC_BUS_TIMEOUT0_AHB_CBCR), HWIO_OFFS(GCC_CNOC_BUS_TIMEOUT0_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_CNOC_BUS_TIMEOUT0_AHB_CLK
  },
#endif

  {
    /* .szClockName      = */ "gcc_cnoc_periph_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_CNOC_PERIPH_AHB_CBCR), HWIO_OFFS(GCC_CONFIG_NOC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControlRO,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_CNOC_PERIPH_AHB_CLK
  },
#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_cnoc_periph_bus_timeout1_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_CNOC_PERIPH_BUS_TIMEOUT1_AHB_CBCR), HWIO_OFFS(GCC_CNOC_PERIPH_BUS_TIMEOUT1_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_CNOC_PERIPH_BUS_TIMEOUT1_AHB_CLK
  },
#endif

#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_cnoc_periph_bus_timeout2_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_CNOC_PERIPH_BUS_TIMEOUT2_AHB_CBCR), HWIO_OFFS(GCC_CNOC_PERIPH_BUS_TIMEOUT2_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_CNOC_PERIPH_BUS_TIMEOUT2_AHB_CLK
  },
#endif

  {
    /* .szClockName      = */ "gcc_cnoc_periph_north_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_CNOC_PERIPH_NORTH_AHB_CBCR), HWIO_OFFS(GCC_CONFIG_NOC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControlRO,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_CNOC_PERIPH_NORTH_AHB_CLK
  },
  {
    /* .szClockName      = */ "gcc_cnoc_periph_south_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_CNOC_PERIPH_SOUTH_AHB_CBCR), HWIO_OFFS(GCC_CONFIG_NOC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControlRO,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_CNOC_PERIPH_SOUTH_AHB_CLK
  },
  {
    /* .szClockName      = */ "gcc_pdm_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_PDM_AHB_CBCR), HWIO_OFFS(GCC_PDM_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_PDM_AHB_CLK
  },
  {
    /* .szClockName      = */ "gcc_qspi_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_QSPI_AHB_CBCR), HWIO_OFFS(GCC_QSPI_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_QSPI_AHB_CLK
  },
  {
    /* .szClockName      = */ "gcc_sdcc1_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SDCC1_AHB_CBCR), HWIO_OFFS(GCC_SDCC1_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_SDCC1_AHB_CLK
  },
  {
    /* .szClockName      = */ "gcc_sdcc2_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SDCC2_AHB_CBCR), HWIO_OFFS(GCC_SDCC2_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_SDCC2_AHB_CLK
  },
#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_spdm_pnoc_cy_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SPDM_PNOC_CY_CBCR), HWIO_OFFS(GCC_SPDM_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_SPDM_PNOC_CY_CLK
  },
#endif

};


/*
 * HAL_clk_mGCCCNOCPERIPHClkDomain
 *
 * CNOCPERIPH clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGCCCNOCPERIPHClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(GCC_CNOC_PERIPH_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mCNOCPERIPHClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mCNOCPERIPHClkDomainClks)/sizeof(HAL_clk_mCNOCPERIPHClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGCCClockDomainControlRO,
  /* .pmNextClockDomain    = */ NULL
};


/*                           
 *  HAL_clk_mCONFIGNOCClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mCONFIGNOCClkDomainClks[] =
{
#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_a2noc_throttle_cfg_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_A2NOC_THROTTLE_CFG_CBCR), HWIO_OFFS(GCC_AGGRE2_NOC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_A2NOC_THROTTLE_CFG_CLK
  },
#endif

#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_aggre2_cnoc_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_AGGRE2_CNOC_AHB_CBCR), HWIO_OFFS(GCC_AGGRE2_NOC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_AGGRE2_CNOC_AHB_CLK
  },
#endif

#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_aggre2_noc_msmpu_cfg_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_AGGRE2_NOC_MSMPU_CFG_AHB_CBCR), HWIO_OFFS(GCC_MSMPU_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_AGGRE2_NOC_MSMPU_CFG_AHB_CLK
  },
#endif

#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_GCC_AHB_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_AHB_CLK
  },
#endif

#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_bimc_cfg_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_BIMC_CFG_AHB_CBCR), HWIO_OFFS(GCC_BIMC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_BIMC_CFG_AHB_CLK
  },
#endif

#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_bimc_nius_cfg_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_BIMC_NIUS_CFG_AHB_CBCR), HWIO_OFFS(GCC_SYSTEM_NOC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_BIMC_NIUS_CFG_AHB_CLK
  },
#endif

  {
    /* .szClockName      = */ "gcc_boot_rom_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_BOOT_ROM_AHB_CBCR), HWIO_OFFS(GCC_BOOT_ROM_BCR), HAL_CLK_FMSK(PROC_CLK_BRANCH_ENA_VOTE, BOOT_ROM_AHB_CLK_ENA) },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_BOOT_ROM_AHB_CLK
  },
  {
    /* .szClockName      = */ "gcc_ce1_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_CE1_AHB_CBCR), HWIO_OFFS(GCC_CE1_BCR), HAL_CLK_FMSK(PROC_CLK_BRANCH_ENA_VOTE, CE1_AHB_CLK_ENA) },
    /* .pmControl        = */ &HAL_clk_mGenericClockControlRO,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_CE1_AHB_CLK
  },
  {
    /* .szClockName      = */ "gcc_cfg_noc_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_CFG_NOC_AHB_CBCR), HWIO_OFFS(GCC_CONFIG_NOC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControlRO,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_CFG_NOC_AHB_CLK
  },
#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_cfg_noc_lpass_aon_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_CFG_NOC_LPASS_AON_AHB_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_CFG_NOC_LPASS_AON_AHB_CLK
  },
#endif

  {
    /* .szClockName      = */ "gcc_cfg_noc_north_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_CFG_NOC_NORTH_AHB_CBCR), HWIO_OFFS(GCC_CONFIG_NOC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControlRO,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_CFG_NOC_NORTH_AHB_CLK
  },
  {
    /* .szClockName      = */ "gcc_cfg_noc_south_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_CFG_NOC_SOUTH_AHB_CBCR), HWIO_OFFS(GCC_CONFIG_NOC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControlRO,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_CFG_NOC_SOUTH_AHB_CLK
  },
#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_cfg_noc_turing_aon_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_CFG_NOC_TURING_AON_AHB_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_CFG_NOC_TURING_AON_AHB_CLK
  },
#endif

#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_cnoc_bus_timeout10_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_CNOC_BUS_TIMEOUT10_AHB_CBCR), HWIO_OFFS(GCC_CNOC_BUS_TIMEOUT10_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_CNOC_BUS_TIMEOUT10_AHB_CLK
  },
#endif

#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_cnoc_bus_timeout11_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_CNOC_BUS_TIMEOUT11_AHB_CBCR), HWIO_OFFS(GCC_CNOC_BUS_TIMEOUT11_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_CNOC_BUS_TIMEOUT11_AHB_CLK
  },
#endif

#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_cnoc_bus_timeout2_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_CNOC_BUS_TIMEOUT2_AHB_CBCR), HWIO_OFFS(GCC_CNOC_BUS_TIMEOUT2_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_CNOC_BUS_TIMEOUT2_AHB_CLK
  },
#endif

#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_cnoc_bus_timeout3_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_CNOC_BUS_TIMEOUT3_AHB_CBCR), HWIO_OFFS(GCC_CNOC_BUS_TIMEOUT3_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_CNOC_BUS_TIMEOUT3_AHB_CLK
  },
#endif

#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_cnoc_bus_timeout4_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_CNOC_BUS_TIMEOUT4_AHB_CBCR), HWIO_OFFS(GCC_CNOC_BUS_TIMEOUT4_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_CNOC_BUS_TIMEOUT4_AHB_CLK
  },
#endif

#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_cnoc_bus_timeout6_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_CNOC_BUS_TIMEOUT6_AHB_CBCR), HWIO_OFFS(GCC_CNOC_BUS_TIMEOUT6_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_CNOC_BUS_TIMEOUT6_AHB_CLK
  },
#endif

#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_cnoc_bus_timeout7_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_CNOC_BUS_TIMEOUT7_AHB_CBCR), HWIO_OFFS(GCC_CNOC_BUS_TIMEOUT7_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_CNOC_BUS_TIMEOUT7_AHB_CLK
  },
#endif

#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_cnoc_bus_timeout8_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_CNOC_BUS_TIMEOUT8_AHB_CBCR), HWIO_OFFS(GCC_CNOC_BUS_TIMEOUT8_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_CNOC_BUS_TIMEOUT8_AHB_CLK
  },
#endif

#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_cnoc_bus_timeout9_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_CNOC_BUS_TIMEOUT9_AHB_CBCR), HWIO_OFFS(GCC_CNOC_BUS_TIMEOUT9_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_CNOC_BUS_TIMEOUT9_AHB_CLK
  },
#endif

#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_cnoc_mst_rpm_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_CNOC_MST_RPM_AHB_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_CNOC_MST_RPM_AHB_CLK
  },
#endif

  {
    /* .szClockName      = */ "gcc_dcc_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_DCC_AHB_CBCR), HWIO_OFFS(GCC_DCC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_DCC_AHB_CLK
  },
#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_glm_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_GLM_AHB_CBCR), HWIO_OFFS(GCC_GLM_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_GLM_AHB_CLK
  },
#endif

  {
    /* .szClockName      = */ "gcc_gpu_cfg_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_GPU_CFG_AHB_CBCR), HWIO_OFFS(GCC_GPU_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_GPU_CFG_AHB_CLK
  },
#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_imem_cfg_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_IMEM_CFG_AHB_CBCR), HWIO_OFFS(GCC_IMEM_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_IMEM_CFG_AHB_CLK
  },
#endif

#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_ipa_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_IPA_AHB_CBCR), HWIO_OFFS(GCC_IPA_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_IPA_AHB_CLK
  },
#endif

#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_lpass_cnoc_cfg_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_LPASS_CNOC_CFG_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_LPASS_CNOC_CFG_CLK
  },
#endif

#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_lpass_q6_smmu_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_LPASS_Q6_SMMU_AHB_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_LPASS_Q6_SMMU_AHB_CLK
  },
#endif

#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_lpass_q6_smmu_gds_cfg_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_LPASS_Q6_SMMU_GDS_CFG_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_LPASS_Q6_SMMU_GDS_CFG_CLK
  },
#endif

#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_mccc_cfg_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_MCCC_CFG_AHB_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_MCCC_CFG_AHB_CLK
  },
#endif

  {
    /* .szClockName      = */ "gcc_mmss_noc_cfg_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_MMSS_NOC_CFG_AHB_CBCR), HWIO_OFFS(GCC_MMSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_MMSS_NOC_CFG_AHB_CLK
  },
  {
    /* .szClockName      = */ "gcc_mmss_qm_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_MMSS_QM_AHB_CBCR), HWIO_OFFS(GCC_MMSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_MMSS_QM_AHB_CLK
  },
#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_mpm_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_MPM_AHB_CBCR), HWIO_OFFS(GCC_MPM_BCR), HAL_CLK_FMSK(PROC_CLK_BRANCH_ENA_VOTE, MPM_AHB_CLK_ENA) },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_MPM_AHB_CLK
  },
#endif

#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_msg_ram_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_MSG_RAM_AHB_CBCR), HWIO_OFFS(GCC_MSG_RAM_BCR), HAL_CLK_FMSK(PROC_CLK_BRANCH_ENA_VOTE, MSG_RAM_AHB_CLK_ENA) },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_MSG_RAM_AHB_CLK
  },
#endif

  {
    /* .szClockName      = */ "gcc_mss_cfg_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_MSS_CFG_AHB_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_MSS_CFG_AHB_CLK
  },
#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_mss_msmpu_cfg_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_MSS_MSMPU_CFG_AHB_CBCR), HWIO_OFFS(GCC_MSMPU_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_MSS_MSMPU_CFG_AHB_CLK
  },
#endif

#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_mss_q6_msmpu_cfg_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_MSS_Q6_MSMPU_CFG_AHB_CBCR), HWIO_OFFS(GCC_MSMPU_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_MSS_Q6_MSMPU_CFG_AHB_CLK
  },
#endif

#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_pimem_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_PIMEM_AHB_CBCR), HWIO_OFFS(GCC_PIMEM_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_PIMEM_AHB_CLK
  },
#endif

  {
    /* .szClockName      = */ "gcc_prng_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_PRNG_AHB_CBCR), HWIO_OFFS(GCC_PRNG_BCR), HAL_CLK_FMSK(PROC_CLK_BRANCH_ENA_VOTE, PRNG_AHB_CLK_ENA) },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_PRNG_AHB_CLK
  },
#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_qdss_cfg_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_QDSS_CFG_AHB_CBCR), HWIO_OFFS(GCC_QDSS_BCR), HAL_CLK_FMSK(PROC_CLK_BRANCH_ENA_VOTE_1, QDSS_CFG_AHB_CLK_ENA) },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_QDSS_CFG_AHB_CLK
  },
#endif

#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_qdss_dap_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_QDSS_DAP_AHB_CBCR), HWIO_OFFS(GCC_QDSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_QDSS_DAP_AHB_CLK
  },
#endif

#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_rbcpr_cx_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_RBCPR_CX_AHB_CBCR), HWIO_OFFS(GCC_RBCPR_CX_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_RBCPR_CX_AHB_CLK
  },
#endif

#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_rbcpr_mx_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_RBCPR_MX_AHB_CBCR), HWIO_OFFS(GCC_RBCPR_MX_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_RBCPR_MX_AHB_CLK
  },
#endif

#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_rpm_mst_m2_cnoc_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_RPM_MST_M2_CNOC_AHB_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_RPM_MST_M2_CNOC_AHB_CLK
  },
#endif

#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_sec_ctrl_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SEC_CTRL_AHB_CBCR), HWIO_OFFS(GCC_SEC_CTRL_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_SEC_CTRL_AHB_CLK
  },
#endif

#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_sec_ctrl_boot_rom_patch_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SEC_CTRL_BOOT_ROM_PATCH_CBCR), HWIO_OFFS(GCC_SEC_CTRL_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_SEC_CTRL_BOOT_ROM_PATCH_CLK
  },
#endif

#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_smmu_aggre2_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SMMU_AGGRE2_AHB_CBCR), HWIO_OFFS(GCC_AGGRE2_NOC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_SMMU_AGGRE2_AHB_CLK
  },
#endif

#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_snoc_bus_timeout4_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SNOC_BUS_TIMEOUT4_AHB_CBCR), HWIO_OFFS(GCC_SNOC_BUS_TIMEOUT4_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_SNOC_BUS_TIMEOUT4_AHB_CLK
  },
#endif

  {
    /* .szClockName      = */ "gcc_snoc_cnoc_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SNOC_CNOC_AHB_CBCR), HWIO_OFFS(GCC_SYSTEM_NOC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControlRO,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_SNOC_CNOC_AHB_CLK
  },
#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_spdm_cfg_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SPDM_CFG_AHB_CBCR), HWIO_OFFS(GCC_SPDM_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_SPDM_CFG_AHB_CLK
  },
#endif

#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_spdm_mstr_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SPDM_MSTR_AHB_CBCR), HWIO_OFFS(GCC_SPDM_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_SPDM_MSTR_AHB_CLK
  },
#endif

#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_spmi_cnoc_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SPMI_CNOC_AHB_CBCR), HWIO_OFFS(GCC_SPMI_BCR), HAL_CLK_FMSK(PROC_CLK_BRANCH_ENA_VOTE, SPMI_CNOC_AHB_CLK_ENA) },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_SPMI_CNOC_AHB_CLK
  },
#endif

#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_tcsr_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_TCSR_AHB_CBCR), HWIO_OFFS(GCC_TCSR_BCR), HAL_CLK_FMSK(PROC_CLK_BRANCH_ENA_VOTE, TCSR_AHB_CLK_ENA) },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_TCSR_AHB_CLK
  },
#endif

  {
    /* .szClockName      = */ "gcc_tic_cfg_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_TIC_CFG_AHB_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_TIC_CFG_AHB_CLK
  },
#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_tlmm_centre_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_TLMM_CENTRE_AHB_CBCR), HWIO_OFFS(GCC_TLMM_BCR), HAL_CLK_FMSK(PROC_CLK_BRANCH_ENA_VOTE, TLMM_CENTRE_AHB_CLK_ENA) },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_TLMM_CENTRE_AHB_CLK
  },
#endif

#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_tlmm_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_TLMM_CBCR), HWIO_OFFS(GCC_TLMM_BCR), HAL_CLK_FMSK(PROC_CLK_BRANCH_ENA_VOTE, TLMM_CLK_ENA) },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_TLMM_CLK
  },
#endif

#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_tlmm_north_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_TLMM_NORTH_AHB_CBCR), HWIO_OFFS(GCC_TLMM_BCR), HAL_CLK_FMSK(PROC_CLK_BRANCH_ENA_VOTE, TLMM_NORTH_AHB_CLK_ENA) },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_TLMM_NORTH_AHB_CLK
  },
#endif

#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_tlmm_south_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_TLMM_SOUTH_AHB_CBCR), HWIO_OFFS(GCC_TLMM_BCR), HAL_CLK_FMSK(PROC_CLK_BRANCH_ENA_VOTE, TLMM_SOUTH_AHB_CLK_ENA) },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_TLMM_SOUTH_AHB_CLK
  },
#endif

#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_turing_q6_smmu_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_TURING_Q6_SMMU_AHB_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_TURING_Q6_SMMU_AHB_CLK
  },
#endif

  {
    /* .szClockName      = */ "gcc_ufs_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_UFS_AHB_CBCR), HWIO_OFFS(GCC_UFS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_UFS_AHB_CLK
  },
  {
    /* .szClockName      = */ "gcc_usb_phy_cfg_ahb2phy_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_USB_PHY_CFG_AHB2PHY_CBCR), HWIO_OFFS(GCC_USB_PHY_CFG_AHB2PHY_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_USB_PHY_CFG_AHB2PHY_CLK
  },
};


/*
 * HAL_clk_mGCCCONFIGNOCClkDomain
 *
 * CONFIGNOC clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGCCCONFIGNOCClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(GCC_CONFIG_NOC_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mCONFIGNOCClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mCONFIGNOCClkDomainClks)/sizeof(HAL_clk_mCONFIGNOCClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGCCClockDomainControlRO,
  /* .pmNextClockDomain    = */ NULL
};

