/*
==============================================================================

FILE:         HALclkSECONDARYPCM.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   SECONDARYPCM clocks.

   List of clock domains:
     - HAL_clk_mLPASSLPAIFSECClkDomain
     - HAL_clk_mLPASSSECMI2SCLKINClkDomain


   List of power domains:



==============================================================================

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/hal/clk/hw/sdm660/adsp_slpi/src/lpass/HALclkSECONDARYPCM.c#1 $

==============================================================================
            Copyright (c) 2016 Qualcomm Technologies Incorporated.
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

extern HAL_clk_ClockControlType HAL_clk_mLpass_ClockControl_2;
extern HAL_clk_ClockDomainControlType  HAL_clk_mLPASSClockDomainControl;
extern HAL_clk_ClockDomainControlType  HAL_clk_mLPASSClockDomainControlRO;


/* ============================================================================
**    Data
** ==========================================================================*/


/*                           
 *  HAL_clk_mLPAIFSECClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mLPAIFSECClkDomainClks[] =
{
  {
    /* .szClockName      = */ "audio_core_lpaif_sec_ibit_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mLpass_ClockControl_2,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AUDIO_CORE_LPAIF_SEC_IBIT_CLK
  },
};


/*
 * HAL_clk_mLPASSLPAIFSECClkDomain
 *
 * LPAIFSEC clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSLPAIFSECClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(LPASS_LPAIF_SEC_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mLPAIFSECClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mLPAIFSECClkDomainClks)/sizeof(HAL_clk_mLPAIFSECClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mLPASSClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};


/*                           
 *  HAL_clk_mSECMI2SCLKINClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mSECMI2SCLKINClkDomainClks[] =
{
  {
    /* .szClockName      = */ "audio_core_lpaif_sec_ebit_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mLpass_ClockControl_2,
    /* .nTestClock       = */ 0
  },
};


/*
 * HAL_clk_mLPASSSECMI2SCLKINClkDomain
 *
 * SECMI2SCLKIN clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSSECMI2SCLKINClkDomain =
{
  /* .nCGRAddr             = */ 0, /* this domain does not have a cmd rcgr */
  /* .pmClocks             = */ HAL_clk_mSECMI2SCLKINClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mSECMI2SCLKINClkDomainClks)/sizeof(HAL_clk_mSECMI2SCLKINClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mLPASSClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};

