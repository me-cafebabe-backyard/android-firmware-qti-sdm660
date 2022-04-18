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


   List of power domains:



==============================================================================

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/HALclkLib/HALclkQDSS.c#3 $

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
#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_center_apb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_CENTER_APB_CBCR), HWIO_OFFS(GCC_QDSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_CENTER_APB_CLK
  },
#endif

#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_gpu_trig_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_GPU_TRIG_CBCR), HWIO_OFFS(GCC_GPU_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_GPU_TRIG_CLK
  },
#endif

#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_hmss_trig_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_HMSS_TRIG_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_HMSS_TRIG_CLK
  },
#endif

  {
    /* .szClockName      = */ "gcc_lpass_trig_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_LPASS_TRIG_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_LPASS_TRIG_CLK
  },
#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_mmss_trig_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_MMSS_TRIG_CBCR), HWIO_OFFS(GCC_MMSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_MMSS_TRIG_CLK
  },
#endif

#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_mss_trig_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_MSS_TRIG_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_MSS_TRIG_CLK
  },
#endif

#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_north_apb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_NORTH_APB_CBCR), HWIO_OFFS(GCC_QDSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_NORTH_APB_CLK
  },
#endif

#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_qdss_apb2jtag_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_QDSS_APB2JTAG_CBCR), HWIO_OFFS(GCC_APB2JTAG_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_QDSS_APB2JTAG_CLK
  },
#endif

#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_qdss_dap_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_QDSS_DAP_CBCR), HWIO_OFFS(GCC_QDSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_QDSS_DAP_CLK
  },
#endif

#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_qdss_trig_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_QDSS_TRIG_CBCR), HWIO_OFFS(GCC_QDSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_QDSS_TRIG_CLK
  },
#endif

#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_south_apb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SOUTH_APB_CBCR), HWIO_OFFS(GCC_QDSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_SOUTH_APB_CLK
  },
#endif

#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_turing_trig_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_TURING_TRIG_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_TURING_TRIG_CLK
  },
#endif

#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_wcss_apb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_WCSS_APB_CBCR), HWIO_OFFS(GCC_WCSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_WCSS_APB_CLK
  },
#endif

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
  /* .pmControl            = */ &HAL_clk_mGCCClockDomainControlRO,
  /* .pmNextClockDomain    = */ NULL
};


/*                           
 *  HAL_clk_mQDSSATBAClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mQDSSATBAClkDomainClks[] =
{
#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_aggre2_noc_at_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_AGGRE2_NOC_AT_CBCR), HWIO_OFFS(GCC_AGGRE2_NOC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_AGGRE2_NOC_AT_CLK
  },
#endif

#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_gpu_at_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_GPU_AT_CBCR), HWIO_OFFS(GCC_GPU_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_GPU_AT_CLK
  },
#endif

#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_hmss_at_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_HMSS_AT_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_HMSS_AT_CLK
  },
#endif

#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_mmss_at_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_MMSS_AT_CBCR), HWIO_OFFS(GCC_MMSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_MMSS_AT_CLK
  },
#endif

#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_mmss_noc_at_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_MMSS_NOC_AT_CBCR), HWIO_OFFS(GCC_MMSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_MMSS_NOC_AT_CLK
  },
#endif

#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_north_at_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_NORTH_AT_CBCR), HWIO_OFFS(GCC_QDSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_NORTH_AT_CLK
  },
#endif

#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_qdss_center_at_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_QDSS_CENTER_AT_CBCR), HWIO_OFFS(GCC_QDSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_QDSS_CENTER_AT_CLK
  },
#endif

#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_south_at_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SOUTH_AT_CBCR), HWIO_OFFS(GCC_QDSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_SOUTH_AT_CLK
  },
#endif

  {
    /* .szClockName      = */ "gcc_sys_noc_at_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SYS_NOC_AT_CBCR), HWIO_OFFS(GCC_SYSTEM_NOC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControlRO,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_SYS_NOC_AT_CLK
  },
#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_wcss_at_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_WCSS_AT_CBCR), HWIO_OFFS(GCC_WCSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_WCSS_AT_CLK
  },
#endif

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
  /* .pmControl            = */ &HAL_clk_mGCCClockDomainControlRO,
  /* .pmNextClockDomain    = */ NULL
};


/*                           
 *  HAL_clk_mQDSSATBBClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mQDSSATBBClkDomainClks[] =
{
#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_bimc_at_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_BIMC_AT_CBCR), HWIO_OFFS(GCC_BIMC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_BIMC_AT_CLK
  },
#endif

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
  /* .pmControl            = */ &HAL_clk_mGCCClockDomainControlRO,
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
#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_turing_at_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_TURING_AT_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_TURING_AT_CLK
  },
#endif

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
  /* .pmControl            = */ &HAL_clk_mGCCClockDomainControlRO,
  /* .pmNextClockDomain    = */ NULL
};

