/*
==============================================================================

FILE:         HALclkSTANDALONEBCR.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   STANDALONEBCR clocks.

   List of clock domains:
     - HAL_clk_mLPASSSTANDALONEBCRClkDomain


   List of power domains:



==============================================================================

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/hal/clk/hw/sdm660/adsp_slpi/src/lpass/HALclkSTANDALONEBCR.c#1 $

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

extern HAL_clk_ClockDomainControlType  HAL_clk_mLPASSClockDomainControl;
extern HAL_clk_ClockDomainControlType  HAL_clk_mLPASSClockDomainControlRO;


/* ============================================================================
**    Data
** ==========================================================================*/


/*                           
 *  HAL_clk_mSTANDALONEBCRClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mSTANDALONEBCRClkDomainClks[] =
{
  {
    /* .szClockName      = */ "lpass_audio_core_bcr",
    /* .mRegisters       = */ { 0, HWIO_OFFS(LPASS_AUDIO_CORE_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ 0
  },
  {
    /* .szClockName      = */ "lpass_sensor_core_bcr",
    /* .mRegisters       = */ { 0, HWIO_OFFS(LPASS_SENSOR_CORE_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ 0
  },
};


/*
 * HAL_clk_mLPASSSTANDALONEBCRClkDomain
 *
 * STANDALONEBCR clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSSTANDALONEBCRClkDomain =
{
  /* .nCGRAddr             = */ 0, /* this domain does not have a cmd rcgr */
  /* .pmClocks             = */ HAL_clk_mSTANDALONEBCRClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mSTANDALONEBCRClkDomainClks)/sizeof(HAL_clk_mSTANDALONEBCRClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mLPASSClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};

