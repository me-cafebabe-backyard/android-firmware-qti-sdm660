/*
==============================================================================

FILE:         HALclkMDSS.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   MDSS clocks.

   List of clock domains:
     - HAL_clk_mMMSSBYTE0ClkDomain
     - HAL_clk_mMMSSBYTE1ClkDomain
     - HAL_clk_mMMSSDPAUXClkDomain
     - HAL_clk_mMMSSDPCRYPTOClkDomain
     - HAL_clk_mMMSSDPGTCClkDomain
     - HAL_clk_mMMSSDPLINKClkDomain
     - HAL_clk_mMMSSDPPIXELClkDomain
     - HAL_clk_mMMSSESC0ClkDomain
     - HAL_clk_mMMSSESC1ClkDomain
     - HAL_clk_mMMSSMDPClkDomain
     - HAL_clk_mMMSSPCLK0ClkDomain
     - HAL_clk_mMMSSPCLK1ClkDomain
     - HAL_clk_mMMSSROTClkDomain
     - HAL_clk_mMMSSVSYNCClkDomain


   List of power domains:
     - HAL_clk_mMMSSMDSSPowerDomain



==============================================================================

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/HALclkLib/HALclkMDSS.c#3 $

==============================================================================
            Copyright (c) 2016 QUALCOMM Technologies Incorporated.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
==============================================================================
*/

/*============================================================================

                     INCLUDE FILES FOR MODULE

============================================================================*/

#include "Drivers/ClockDxe/ClockDriver.h"
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
extern HAL_clk_ClockDomainControlType  HAL_clk_mMMSSClockDomainControl_1;
extern HAL_clk_ClockDomainControlType  HAL_clk_mMMSSClockDomainControlRO_1;
extern HAL_clk_ClockDomainControlType  HAL_clk_mMMSSClockDomainControl_6;
extern HAL_clk_ClockDomainControlType  HAL_clk_mMMSSClockDomainControlRO_6;


/* ============================================================================
**    Data
** ==========================================================================*/


/*                           
 *  HAL_clk_mBYTE0ClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mBYTE0ClkDomainClks[] =
{
  {
    /* .szClockName      = */ "mmss_mdss_byte0_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_MDSS_BYTE0_CBCR), HWIO_OFFS(MMSS_MDSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_MDSS_BYTE0_CLK
  },
  {
    /* .szClockName      = */ "mmss_mdss_byte0_intf_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_MDSS_BYTE0_INTF_CBCR), HWIO_OFFS(MMSS_MDSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_MDSS_BYTE0_INTF_CLK
  },
};


/*
 * HAL_clk_mMMSSBYTE0ClkDomain
 *
 * BYTE0 clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mMMSSBYTE0ClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(MMSS_BYTE0_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mBYTE0ClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mBYTE0ClkDomainClks)/sizeof(HAL_clk_mBYTE0ClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mMMSSClockDomainControl_1,
  /* .pmNextClockDomain    = */ NULL
};


/*                           
 *  HAL_clk_mBYTE1ClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mBYTE1ClkDomainClks[] =
{
  {
    /* .szClockName      = */ "mmss_mdss_byte1_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_MDSS_BYTE1_CBCR), HWIO_OFFS(MMSS_MDSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_MDSS_BYTE1_CLK
  },
  {
    /* .szClockName      = */ "mmss_mdss_byte1_intf_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_MDSS_BYTE1_INTF_CBCR), HWIO_OFFS(MMSS_MDSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_MDSS_BYTE1_INTF_CLK
  },
};


/*
 * HAL_clk_mMMSSBYTE1ClkDomain
 *
 * BYTE1 clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mMMSSBYTE1ClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(MMSS_BYTE1_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mBYTE1ClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mBYTE1ClkDomainClks)/sizeof(HAL_clk_mBYTE1ClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mMMSSClockDomainControl_1,
  /* .pmNextClockDomain    = */ NULL
};


/*                           
 *  HAL_clk_mDPAUXClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mDPAUXClkDomainClks[] =
{
  {
    /* .szClockName      = */ "mmss_mdss_dp_aux_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_MDSS_DP_AUX_CBCR), HWIO_OFFS(MMSS_MDSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_MDSS_DP_AUX_CLK
  },
};


/*
 * HAL_clk_mMMSSDPAUXClkDomain
 *
 * DPAUX clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mMMSSDPAUXClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(MMSS_DP_AUX_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mDPAUXClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mDPAUXClkDomainClks)/sizeof(HAL_clk_mDPAUXClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mMMSSClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};


/*                           
 *  HAL_clk_mDPCRYPTOClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mDPCRYPTOClkDomainClks[] =
{
  {
    /* .szClockName      = */ "mmss_mdss_dp_crypto_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_MDSS_DP_CRYPTO_CBCR), HWIO_OFFS(MMSS_MDSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_MDSS_DP_CRYPTO_CLK
  },
  {
    /* .szClockName      = */ "mmss_spdm_dp_crypto_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_SPDM_DP_CRYPTO_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_SPDM_DP_CRYPTO_CLK
  },
};


/*
 * HAL_clk_mMMSSDPCRYPTOClkDomain
 *
 * DPCRYPTO clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mMMSSDPCRYPTOClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(MMSS_DP_CRYPTO_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mDPCRYPTOClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mDPCRYPTOClkDomainClks)/sizeof(HAL_clk_mDPCRYPTOClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mMMSSClockDomainControl_1,
  /* .pmNextClockDomain    = */ NULL
};


/*                           
 *  HAL_clk_mDPGTCClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mDPGTCClkDomainClks[] =
{
  {
    /* .szClockName      = */ "mmss_mdss_dp_gtc_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_MDSS_DP_GTC_CBCR), HWIO_OFFS(MMSS_MDSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_MDSS_DP_GTC_CLK
  },
};


/*
 * HAL_clk_mMMSSDPGTCClkDomain
 *
 * DPGTC clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mMMSSDPGTCClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(MMSS_DP_GTC_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mDPGTCClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mDPGTCClkDomainClks)/sizeof(HAL_clk_mDPGTCClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mMMSSClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};


/*                           
 *  HAL_clk_mDPLINKClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mDPLINKClkDomainClks[] =
{
  {
    /* .szClockName      = */ "mmss_mdss_dp_link_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_MDSS_DP_LINK_CBCR), HWIO_OFFS(MMSS_MDSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_MDSS_DP_LINK_CLK
  },
  {
    /* .szClockName      = */ "mmss_mdss_dp_link_intf_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_MDSS_DP_LINK_INTF_CBCR), HWIO_OFFS(MMSS_MDSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_MDSS_DP_LINK_INTF_CLK
  },
};


/*
 * HAL_clk_mMMSSDPLINKClkDomain
 *
 * DPLINK clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mMMSSDPLINKClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(MMSS_DP_LINK_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mDPLINKClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mDPLINKClkDomainClks)/sizeof(HAL_clk_mDPLINKClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mMMSSClockDomainControl_1,
  /* .pmNextClockDomain    = */ NULL
};


/*                           
 *  HAL_clk_mDPPIXELClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mDPPIXELClkDomainClks[] =
{
  {
    /* .szClockName      = */ "mmss_mdss_dp_pixel_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_MDSS_DP_PIXEL_CBCR), HWIO_OFFS(MMSS_MDSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_MDSS_DP_PIXEL_CLK
  },
  {
    /* .szClockName      = */ "mmss_spdm_dp_pixel_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_SPDM_DP_PIXEL_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_SPDM_DP_PIXEL_CLK
  },
};


/*
 * HAL_clk_mMMSSDPPIXELClkDomain
 *
 * DPPIXEL clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mMMSSDPPIXELClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(MMSS_DP_PIXEL_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mDPPIXELClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mDPPIXELClkDomainClks)/sizeof(HAL_clk_mDPPIXELClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mMMSSClockDomainControl_1,
  /* .pmNextClockDomain    = */ NULL
};


/*                           
 *  HAL_clk_mESC0ClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mESC0ClkDomainClks[] =
{
  {
    /* .szClockName      = */ "mmss_mdss_esc0_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_MDSS_ESC0_CBCR), HWIO_OFFS(MMSS_MDSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_MDSS_ESC0_CLK
  },
};


/*
 * HAL_clk_mMMSSESC0ClkDomain
 *
 * ESC0 clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mMMSSESC0ClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(MMSS_ESC0_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mESC0ClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mESC0ClkDomainClks)/sizeof(HAL_clk_mESC0ClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mMMSSClockDomainControl_1,
  /* .pmNextClockDomain    = */ NULL
};


/*                           
 *  HAL_clk_mESC1ClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mESC1ClkDomainClks[] =
{
  {
    /* .szClockName      = */ "mmss_mdss_esc1_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_MDSS_ESC1_CBCR), HWIO_OFFS(MMSS_MDSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_MDSS_ESC1_CLK
  },
};


/*
 * HAL_clk_mMMSSESC1ClkDomain
 *
 * ESC1 clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mMMSSESC1ClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(MMSS_ESC1_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mESC1ClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mESC1ClkDomainClks)/sizeof(HAL_clk_mESC1ClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mMMSSClockDomainControl_1,
  /* .pmNextClockDomain    = */ NULL
};


/*                           
 *  HAL_clk_mMDPClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mMDPClkDomainClks[] =
{
  {
    /* .szClockName      = */ "mmss_mdss_mdp_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_MDSS_MDP_CBCR), HWIO_OFFS(MMSS_MDSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_MDSS_MDP_CLK
  },
  {
    /* .szClockName      = */ "mmss_spdm_mdp_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_SPDM_MDP_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_SPDM_MDP_CLK
  },
};


/*
 * HAL_clk_mMMSSMDPClkDomain
 *
 * MDP clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mMMSSMDPClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(MMSS_MDP_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mMDPClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mMDPClkDomainClks)/sizeof(HAL_clk_mMDPClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mMMSSClockDomainControl_6,
  /* .pmNextClockDomain    = */ NULL
};


/*                           
 *  HAL_clk_mPCLK0ClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mPCLK0ClkDomainClks[] =
{
  {
    /* .szClockName      = */ "mmss_mdss_pclk0_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_MDSS_PCLK0_CBCR), HWIO_OFFS(MMSS_MDSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_MDSS_PCLK0_CLK
  },
  {
    /* .szClockName      = */ "mmss_spdm_pclk0_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_SPDM_PCLK0_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_SPDM_PCLK0_CLK
  },
};


/*
 * HAL_clk_mMMSSPCLK0ClkDomain
 *
 * PCLK0 clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mMMSSPCLK0ClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(MMSS_PCLK0_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mPCLK0ClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mPCLK0ClkDomainClks)/sizeof(HAL_clk_mPCLK0ClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mMMSSClockDomainControl_1,
  /* .pmNextClockDomain    = */ NULL
};


/*                           
 *  HAL_clk_mPCLK1ClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mPCLK1ClkDomainClks[] =
{
  {
    /* .szClockName      = */ "mmss_mdss_pclk1_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_MDSS_PCLK1_CBCR), HWIO_OFFS(MMSS_MDSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_MDSS_PCLK1_CLK
  },
  {
    /* .szClockName      = */ "mmss_spdm_pclk1_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_SPDM_PCLK1_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_SPDM_PCLK1_CLK
  },
};


/*
 * HAL_clk_mMMSSPCLK1ClkDomain
 *
 * PCLK1 clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mMMSSPCLK1ClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(MMSS_PCLK1_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mPCLK1ClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mPCLK1ClkDomainClks)/sizeof(HAL_clk_mPCLK1ClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mMMSSClockDomainControl_1,
  /* .pmNextClockDomain    = */ NULL
};


/*                           
 *  HAL_clk_mROTClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mROTClkDomainClks[] =
{
  {
    /* .szClockName      = */ "mmss_mdss_rot_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_MDSS_ROT_CBCR), HWIO_OFFS(MMSS_MDSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_MDSS_ROT_CLK
  },
  {
    /* .szClockName      = */ "mmss_spdm_rot_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_SPDM_ROT_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_SPDM_ROT_CLK
  },
};


/*
 * HAL_clk_mMMSSROTClkDomain
 *
 * ROT clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mMMSSROTClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(MMSS_ROT_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mROTClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mROTClkDomainClks)/sizeof(HAL_clk_mROTClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mMMSSClockDomainControl_6,
  /* .pmNextClockDomain    = */ NULL
};


/*                           
 *  HAL_clk_mVSYNCClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mVSYNCClkDomainClks[] =
{
  {
    /* .szClockName      = */ "mmss_mdss_vsync_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_MDSS_VSYNC_CBCR), HWIO_OFFS(MMSS_MDSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_MDSS_VSYNC_CLK
  },
};


/*
 * HAL_clk_mMMSSVSYNCClkDomain
 *
 * VSYNC clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mMMSSVSYNCClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(MMSS_VSYNC_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mVSYNCClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mVSYNCClkDomainClks)/sizeof(HAL_clk_mVSYNCClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mMMSSClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};


/*
 * HAL_clk_mMMSSMDSSPowerDomain
 *
 * MDSS power domain.
 */
HAL_clk_PowerDomainDescType HAL_clk_mMMSSMDSSPowerDomain =
{
  /* .szPowerDomainName       = */ "VDD_MDSS",
  /* .nGDSCRAddr              = */ HWIO_OFFS(MMSS_MDSS_GDSCR),
  /* .pmControl               = */ &HAL_clk_mGenericPowerDomainControl,
  /* .pmClockMemCore          = */ NULL,
  /* .pmClockMemPeriph        = */ NULL,
  /* .pmNextPowerDomain       = */ NULL
};

/*
 * aClocksDividers
 *
 * MDSS Clocks Dividers.
 */
HAL_Clk_ExtDividerNodeType HAL_clk_aClocksDividers[] =
{
  {"mmss_mdss_byte0_intf_clk",   HWIO_OFFS(MMSS_MDSS_BYTE0_INTF_DIV)},
  {"mmss_mdss_byte1_intf_clk",   HWIO_OFFS(MMSS_MDSS_BYTE1_INTF_DIV)},
  {"mmss_mdss_dp_link_intf_clk", HWIO_OFFS(MMSS_MDSS_DP_LINK_INTF_DIV)},
};

/* ===========================================================================
**  HAL_clk_SetExternalSourceDiv
**
** ======================================================================== */
void HAL_clk_SetExternalSourceDiv
(
  const char   *szClock,
  uint32        nExtDivider
)
{
  HAL_Clk_ExtDividerNodeType  *paClkDivider;
  size_t                       nExtDivAddr = 0;
  uint32                       nClockIndex, nMaxClockIndex;

  nMaxClockIndex = sizeof(HAL_clk_aClocksDividers)/sizeof(HAL_clk_aClocksDividers[0]);

  for (nClockIndex = 0; nClockIndex < nMaxClockIndex; nClockIndex++)
  {
    paClkDivider = &HAL_clk_aClocksDividers[nClockIndex];
    if (paClkDivider == 0)
	{
	  return ; // NOT_FOUND
	}

    if (strcmp(szClock, paClkDivider->szName) == 0)
    {
      nExtDivAddr = paClkDivider->nExtDivAddr + HAL_clk_nHWIOBaseMMSS;
      break;
    }
  }

  if (nExtDivAddr == 0)
  {
    return ; // NOT_FOUND
  }
  outpdw(nExtDivAddr, nExtDivider);
}/* END HAL_clk_SetExternalSourceDiv */
