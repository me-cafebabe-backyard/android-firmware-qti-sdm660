/*
==============================================================================

FILE:         HALclkSCC.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   SCC clocks.

   List of clock domains:
     - HAL_clk_mSSCSCC100MClkDomain


   List of power domains:



==============================================================================

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/hal/clk/hw/msm8998/slpi/src/scc/HALclkSCC.c#1 $

==============================================================================
            Copyright (c) 2015 QUALCOMM Technologies Incorporated.
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

extern HAL_clk_ClockDomainControlType  HAL_clk_mSSCClockDomainControl;
extern HAL_clk_ClockDomainControlType  HAL_clk_mSSCClockDomainControlRO;


/* ============================================================================
**    Data
** ==========================================================================*/


/*                           
 *  HAL_clk_mSCC100MClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mSCC100MClkDomainClks[] =
{
  {
    /* .szClockName      = */ "scc_ahb_timeout_clk",
    /* .mRegisters       = */ { HWIO_OFFS(SSC_SCC_SCC_AHB_TIMEOUT_CBCR), HWIO_OFFS(SSC_SCC_SCC_AHB_TIMEOUT_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_SSC_TEST_SCC_AHB_TIMEOUT_CLK
  },
  {
    /* .szClockName      = */ "scc_at_clk",
    /* .mRegisters       = */ { HWIO_OFFS(SSC_SCC_SCC_AT_CBCR), HWIO_OFFS(SSC_SCC_SCC_DBG_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_SSC_TEST_SCC_AT_CLK
  },
  {
    /* .szClockName      = */ "scc_blsp_h_clk",
    /* .mRegisters       = */ { HWIO_OFFS(SSC_SCC_SCC_BLSP_H_CBCR), HWIO_OFFS(SSC_SCC_SCC_BLSP_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_SSC_TEST_SCC_BLSP_H_CLK
  },
  {
    /* .szClockName      = */ "scc_cfg_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(SSC_SCC_SCC_CFG_AHB_CBCR), HWIO_OFFS(SSC_SCC_SCC_BUS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_SSC_TEST_SCC_CFG_AHB_CLK
  },
  {
    /* .szClockName      = */ "scc_crif_clk",
    /* .mRegisters       = */ { HWIO_OFFS(SSC_SCC_SCC_CRIF_CBCR), HWIO_OFFS(SSC_SCC_SCC_BUS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_SSC_TEST_SCC_CRIF_CLK
  },
  {
    /* .szClockName      = */ "scc_csr_h_clk",
    /* .mRegisters       = */ { HWIO_OFFS(SSC_SCC_SCC_CSR_H_CBCR), HWIO_OFFS(SSC_SCC_SCC_BUS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_SSC_TEST_SCC_CSR_H_CLK
  },
  {
    /* .szClockName      = */ "scc_data_h_clk",
    /* .mRegisters       = */ { HWIO_OFFS(SSC_SCC_SCC_DATA_H_CBCR), HWIO_OFFS(SSC_SCC_SCC_BUS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_SSC_TEST_SCC_DATA_H_CLK
  },
  {
    /* .szClockName      = */ "scc_dbg_tsctr_clk",
    /* .mRegisters       = */ { HWIO_OFFS(SSC_SCC_SCC_DBG_TSCTR_CBCR), HWIO_OFFS(SSC_SCC_SCC_DBG_TSCTR_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_SSC_TEST_SCC_DBG_TSCTR_CLK
  },
  {
    /* .szClockName      = */ "scc_pclkdbg_clk",
    /* .mRegisters       = */ { HWIO_OFFS(SSC_SCC_SCC_PCLKDBG_CBCR), HWIO_OFFS(SSC_SCC_SCC_DBG_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_SSC_TEST_SCC_PCLKDBG_CLK
  },
  {
    /* .szClockName      = */ "scc_q6_ahbm_clk",
    /* .mRegisters       = */ { HWIO_OFFS(SSC_SCC_SCC_Q6_AHBM_CBCR), HWIO_OFFS(SSC_SCC_SCC_Q6_AHB_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_SSC_TEST_SCC_Q6_AHBM_CLK
  },
  {
    /* .szClockName      = */ "scc_q6_ahbs_clk",
    /* .mRegisters       = */ { HWIO_OFFS(SSC_SCC_SCC_Q6_AHBS_CBCR), HWIO_OFFS(SSC_SCC_SCC_Q6_AHB_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_SSC_TEST_SCC_Q6_AHBS_CLK
  },
  {
    /* .szClockName      = */ "scc_q6_atbm_clk",
    /* .mRegisters       = */ { HWIO_OFFS(SSC_SCC_SCC_Q6_ATBM_CBCR), HWIO_OFFS(SSC_SCC_SCC_DBG_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_SSC_TEST_SCC_Q6_ATBM_CLK
  },
  {
    /* .szClockName      = */ "scc_q6_spm_clk",
    /* .mRegisters       = */ { HWIO_OFFS(SSC_SCC_SCC_Q6_SPM_CBCR), HWIO_OFFS(SSC_SCC_SCC_Q6_SPM_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_SSC_TEST_SCC_Q6_SPM_CLK
  },
  {
    /* .szClockName      = */ "scc_q6_xpu2_client_clk",
    /* .mRegisters       = */ { HWIO_OFFS(SSC_SCC_SCC_Q6_XPU2_CLIENT_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_SSC_TEST_SCC_Q6_XPU2_CLIENT_CLK
  },
  {
    /* .szClockName      = */ "scc_q6_xpu2_config_clk",
    /* .mRegisters       = */ { HWIO_OFFS(SSC_SCC_SCC_Q6_XPU2_CONFIG_CBCR), HWIO_OFFS(SSC_SCC_SCC_Q6_XPU2_CONFIG_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_SSC_TEST_SCC_Q6_XPU2_CONFIG_CLK
  },
  {
    /* .szClockName      = */ "scc_qup_i2c1_clk",
    /* .mRegisters       = */ { HWIO_OFFS(SSC_SCC_SCC_QUP_I2C1_CBCR), HWIO_OFFS(SSC_SCC_SCC_SPI_I2C1_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_SSC_TEST_SCC_QUP_I2C1_CLK
  },
  {
    /* .szClockName      = */ "scc_qup_i2c2_clk",
    /* .mRegisters       = */ { HWIO_OFFS(SSC_SCC_SCC_QUP_I2C2_CBCR), HWIO_OFFS(SSC_SCC_SCC_SPI_I2C2_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_SSC_TEST_SCC_QUP_I2C2_CLK
  },
  {
    /* .szClockName      = */ "scc_qup_i2c3_clk",
    /* .mRegisters       = */ { HWIO_OFFS(SSC_SCC_SCC_QUP_I2C3_CBCR), HWIO_OFFS(SSC_SCC_SCC_SPI_I2C3_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_SSC_TEST_SCC_QUP_I2C3_CLK
  },
  {
    /* .szClockName      = */ "scc_qup_spi1_clk",
    /* .mRegisters       = */ { HWIO_OFFS(SSC_SCC_SCC_QUP_SPI1_CBCR), HWIO_OFFS(SSC_SCC_SCC_SPI_I2C1_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_SSC_TEST_SCC_QUP_SPI1_CLK
  },
  {
    /* .szClockName      = */ "scc_qup_spi2_clk",
    /* .mRegisters       = */ { HWIO_OFFS(SSC_SCC_SCC_QUP_SPI2_CBCR), HWIO_OFFS(SSC_SCC_SCC_SPI_I2C2_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_SSC_TEST_SCC_QUP_SPI2_CLK
  },
  {
    /* .szClockName      = */ "scc_qup_spi3_clk",
    /* .mRegisters       = */ { HWIO_OFFS(SSC_SCC_SCC_QUP_SPI3_CBCR), HWIO_OFFS(SSC_SCC_SCC_SPI_I2C3_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_SSC_TEST_SCC_QUP_SPI3_CLK
  },
  {
    /* .szClockName      = */ "scc_smem_clk",
    /* .mRegisters       = */ { HWIO_OFFS(SSC_SCC_SCC_SMEM_CBCR), HWIO_OFFS(SSC_SCC_SCC_SMEM_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_SSC_TEST_SCC_SMEM_CLK
  },
};


/*
 * HAL_clk_mSSCSCC100MClkDomain
 *
 * SCC100M clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mSSCSCC100MClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(SSC_SCC_SCC_100M_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mSCC100MClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mSCC100MClkDomainClks)/sizeof(HAL_clk_mSCC100MClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mSSCClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};

