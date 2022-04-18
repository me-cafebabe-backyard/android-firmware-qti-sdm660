/*
==============================================================================

FILE:         HALclkQDSS.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   QDSS clocks.

   List of clock domains:
     - HAL_clk_mGCCQDSSAPBTRIGClkDomain
     - HAL_clk_mGCCQDSSATBAClkDomain
     - HAL_clk_mGCCQDSSATBBClkDomain
     - HAL_clk_mGCCQDSSATBCClkDomain
     - HAL_clk_mGCCQDSSSTMClkDomain
     - HAL_clk_mGCCQDSSTRACECLKINClkDomain
     - HAL_clk_mGCCQDSSTSCTRClkDomain


   List of power domains:



==============================================================================

$Header: //components/rel/rpm.bf/1.8/core/systemdrivers/hal/clk/hw/sdm660/src/GCC/HALclkQDSS.c#1 $

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
 *  HAL_clk_mQDSSAPBTRIGClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mQDSSAPBTRIGClkDomainClks[] =
{
  {
    /* .szClockName      = */ "gcc_center_apb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_CENTER_APB_CBCR), HWIO_OFFS(GCC_QDSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_CENTER_APB_CLK
  },
  {
    /* .szClockName      = */ "gcc_gpu_trig_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_GPU_TRIG_CBCR), HWIO_OFFS(GCC_GPU_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_GPU_TRIG_CLK
  },
  {
    /* .szClockName      = */ "gcc_hmss_trig_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_HMSS_TRIG_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_HMSS_TRIG_CLK
  },
  {
    /* .szClockName      = */ "gcc_lpass_trig_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_LPASS_TRIG_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_LPASS_TRIG_CLK
  },
  {
    /* .szClockName      = */ "gcc_mmss_trig_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_MMSS_TRIG_CBCR), HWIO_OFFS(GCC_MMSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_MMSS_TRIG_CLK
  },
  {
    /* .szClockName      = */ "gcc_mss_trig_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_MSS_TRIG_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_MSS_TRIG_CLK
  },
  {
    /* .szClockName      = */ "gcc_north_apb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_RPM_VOTE_QDSS_APB_CLK), HWIO_OFFS(GCC_QDSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_NORTH_APB_CLK
  },
  {
    /* .szClockName      = */ "gcc_qdss_apb2jtag_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_QDSS_APB2JTAG_CBCR), HWIO_OFFS(GCC_APB2JTAG_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_QDSS_APB2JTAG_CLK
  },
  {
    /* .szClockName      = */ "gcc_qdss_dap_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_QDSS_DAP_CBCR), HWIO_OFFS(GCC_QDSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_QDSS_DAP_CLK
  },
  {
    /* .szClockName      = */ "gcc_qdss_trig_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_QDSS_TRIG_CBCR), HWIO_OFFS(GCC_QDSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_QDSS_TRIG_CLK
  },
  {
    /* .szClockName      = */ "gcc_south_apb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SOUTH_APB_CBCR), HWIO_OFFS(GCC_QDSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_SOUTH_APB_CLK
  },
  {
    /* .szClockName      = */ "gcc_turing_trig_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_TURING_TRIG_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_TURING_TRIG_CLK
  },
  {
    /* .szClockName      = */ "gcc_wcss_apb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_WCSS_APB_CBCR), HWIO_OFFS(GCC_WCSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_WCSS_APB_CLK
  },
};


/*
 * HAL_clk_mGCCQDSSAPBTRIGClkDomain
 *
 * QDSSAPBTRIG clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGCCQDSSAPBTRIGClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(GCC_QDSS_APB_TRIG_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mQDSSAPBTRIGClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mQDSSAPBTRIGClkDomainClks)/sizeof(HAL_clk_mQDSSAPBTRIGClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGCCClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};


/*                           
 *  HAL_clk_mQDSSATBAClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mQDSSATBAClkDomainClks[] =
{
  {
    /* .szClockName      = */ "gcc_aggre2_noc_at_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_AGGRE2_NOC_AT_CBCR), HWIO_OFFS(GCC_AGGRE2_NOC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_AGGRE2_NOC_AT_CLK
  },
  {
    /* .szClockName      = */ "gcc_gpu_at_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_GPU_AT_CBCR), HWIO_OFFS(GCC_GPU_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_GPU_AT_CLK
  },
  {
    /* .szClockName      = */ "gcc_hmss_at_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_HMSS_AT_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_HMSS_AT_CLK
  },
  {
    /* .szClockName      = */ "gcc_mmss_at_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_MMSS_AT_CBCR), HWIO_OFFS(GCC_MMSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_MMSS_AT_CLK
  },
  {
    /* .szClockName      = */ "gcc_mmss_noc_at_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_MMSS_NOC_AT_CBCR), HWIO_OFFS(GCC_MMSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_MMSS_NOC_AT_CLK
  },
  {
    /* .szClockName      = */ "gcc_north_at_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_NORTH_AT_CBCR), HWIO_OFFS(GCC_QDSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_NORTH_AT_CLK
  },
  {
    /* .szClockName      = */ "gcc_qdss_center_at_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_QDSS_CENTER_AT_CBCR), HWIO_OFFS(GCC_QDSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_QDSS_CENTER_AT_CLK
  },
  {
    /* .szClockName      = */ "gcc_south_at_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SOUTH_AT_CBCR), HWIO_OFFS(GCC_QDSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_SOUTH_AT_CLK
  },
  {
    /* .szClockName      = */ "gcc_sys_noc_at_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SYS_NOC_AT_CBCR), HWIO_OFFS(GCC_SYSTEM_NOC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_SYS_NOC_AT_CLK
  },
  {
    /* .szClockName      = */ "gcc_wcss_at_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_WCSS_AT_CBCR), HWIO_OFFS(GCC_WCSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_WCSS_AT_CLK
  },

};


/*
 * HAL_clk_mGCCQDSSATBAClkDomain
 *
 * QDSSATBA clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGCCQDSSATBAClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(GCC_QDSS_ATB_A_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mQDSSATBAClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mQDSSATBAClkDomainClks)/sizeof(HAL_clk_mQDSSATBAClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGCCClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};


/*                           
 *  HAL_clk_mQDSSATBBClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mQDSSATBBClkDomainClks[] =
{
  {
    /* .szClockName      = */ "gcc_bimc_at_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_BIMC_AT_CBCR), HWIO_OFFS(GCC_BIMC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_BIMC_AT_CLK
  },
  {
    /* .szClockName      = */ "gcc_mss_at_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_MSS_AT_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_MSS_AT_CLK
  },
};


/*
 * HAL_clk_mGCCQDSSATBBClkDomain
 *
 * QDSSATBB clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGCCQDSSATBBClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(GCC_QDSS_ATB_B_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mQDSSATBBClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mQDSSATBBClkDomainClks)/sizeof(HAL_clk_mQDSSATBBClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGCCClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};


/*                           
 *  HAL_clk_mQDSSATBCClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mQDSSATBCClkDomainClks[] =
{
  {
    /* .szClockName      = */ "gcc_lpass_at_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_LPASS_AT_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_LPASS_AT_CLK
  },
  {
    /* .szClockName      = */ "gcc_turing_at_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_TURING_AT_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_TURING_AT_CLK
  },
};


/*
 * HAL_clk_mGCCQDSSATBCClkDomain
 *
 * QDSSATBC clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGCCQDSSATBCClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(GCC_QDSS_ATB_C_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mQDSSATBCClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mQDSSATBCClkDomainClks)/sizeof(HAL_clk_mQDSSATBCClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGCCClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};


/*                           
 *  HAL_clk_mQDSSSTMClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mQDSSSTMClkDomainClks[] =
{
  {
    /* .szClockName      = */ "gcc_qdss_stm_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_QDSS_STM_CBCR), HWIO_OFFS(GCC_QDSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_QDSS_STM_CLK
  },
  {
    /* .szClockName      = */ "gcc_sys_noc_qdss_stm_axi_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SYS_NOC_QDSS_STM_AXI_CBCR), HWIO_OFFS(GCC_SYSTEM_NOC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_SYS_NOC_QDSS_STM_AXI_CLK
  },
};


/*
 * HAL_clk_mGCCQDSSSTMClkDomain
 *
 * QDSSSTM clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGCCQDSSSTMClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(GCC_QDSS_STM_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mQDSSSTMClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mQDSSSTMClkDomainClks)/sizeof(HAL_clk_mQDSSSTMClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGCCClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};


/*                           
 *  HAL_clk_mQDSSTRACECLKINClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mQDSSTRACECLKINClkDomainClks[] =
{
  {
    /* .szClockName      = */ "gcc_qdss_traceclkin_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_QDSS_TRACECLKIN_CBCR), HWIO_OFFS(GCC_QDSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_QDSS_TRACECLKIN_CLK
  },
};


/*
 * HAL_clk_mGCCQDSSTRACECLKINClkDomain
 *
 * QDSSTRACECLKIN clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGCCQDSSTRACECLKINClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(GCC_QDSS_TRACECLKIN_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mQDSSTRACECLKINClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mQDSSTRACECLKINClkDomainClks)/sizeof(HAL_clk_mQDSSTRACECLKINClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGCCClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};


/*                           
 *  HAL_clk_mQDSSTSCTRClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mQDSSTSCTRClkDomainClks[] =
{
  {
    /* .szClockName      = */ "gcc_apss_qdss_tsctr_div2_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_APSS_QDSS_TSCTR_DIV2_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_APSS_QDSS_TSCTR_DIV2_CLK
  },
  {
    /* .szClockName      = */ "gcc_apss_qdss_tsctr_div8_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_APSS_QDSS_TSCTR_DIV8_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_APSS_QDSS_TSCTR_DIV8_CLK
  },
  {
    /* .szClockName      = */ "gcc_qdss_tsctr_div16_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_QDSS_TSCTR_DIV16_CBCR), HWIO_OFFS(GCC_QDSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_QDSS_TSCTR_DIV16_CLK
  },
  {
    /* .szClockName      = */ "gcc_qdss_tsctr_div2_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_QDSS_TSCTR_DIV2_CBCR), HWIO_OFFS(GCC_QDSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_QDSS_TSCTR_DIV2_CLK
  },
  {
    /* .szClockName      = */ "gcc_qdss_tsctr_div3_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_QDSS_TSCTR_DIV3_CBCR), HWIO_OFFS(GCC_QDSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_QDSS_TSCTR_DIV3_CLK
  },
  {
    /* .szClockName      = */ "gcc_qdss_tsctr_div4_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_QDSS_TSCTR_DIV4_CBCR), HWIO_OFFS(GCC_QDSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_QDSS_TSCTR_DIV4_CLK
  },
  {
    /* .szClockName      = */ "gcc_qdss_tsctr_div8_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_QDSS_TSCTR_DIV8_CBCR), HWIO_OFFS(GCC_QDSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_QDSS_TSCTR_DIV8_CLK
  },
  {
    /* .szClockName      = */ "gcc_wcss_tsctr_div2_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_WCSS_TSCTR_DIV2_CBCR), HWIO_OFFS(GCC_WCSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_WCSS_TSCTR_DIV2_CLK
  },
};


/*
 * HAL_clk_mGCCQDSSTSCTRClkDomain
 *
 * QDSSTSCTR clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGCCQDSSTSCTRClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(GCC_QDSS_TSCTR_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mQDSSTSCTRClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mQDSSTSCTRClkDomainClks)/sizeof(HAL_clk_mQDSSTSCTRClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGCCClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};

