/*
==============================================================================

FILE:         HALclkQOSFIXEDMONITOR.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   QOSFIXEDMONITOR clocks.

   List of clock domains:
     - HAL_clk_mLPASSQOSFIXEDLATCOUNTERClkDomain


   List of power domains:



==============================================================================

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/hal/clk/hw/msm8998/adsp/src/lpass/HALclkQOSFIXEDMONITOR.c#1 $

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

extern HAL_clk_ClockDomainControlType  HAL_clk_mLPASSClockDomainControl;
extern HAL_clk_ClockDomainControlType  HAL_clk_mLPASSClockDomainControlRO;


/* ============================================================================
**    Data
** ==========================================================================*/


/*                           
 *  HAL_clk_mQOSFIXEDLATCOUNTERClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mQOSFIXEDLATCOUNTERClkDomainClks[] =
{
  {
    /* .szClockName      = */ "lpass_audio_core_qos_dmonitor_fixed_lat_counter_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_LPASS_AUDIO_CORE_QOS_DMONITOR_FIXED_LAT_COUNTER_CLK
  },
  {
    /* .szClockName      = */ "lpass_audio_wrapper_qos_danger_fixed_lat_counter_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_LPASS_AUDIO_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CLK
  },
  {
    /* .szClockName      = */ "lpass_audio_wrapper_qos_dmonitor_fixed_lat_counter_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_LPASS_AUDIO_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CLK
  },
};


/*
 * HAL_clk_mLPASSQOSFIXEDLATCOUNTERClkDomain
 *
 * QOSFIXEDLATCOUNTER clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSQOSFIXEDLATCOUNTERClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mQOSFIXEDLATCOUNTERClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mQOSFIXEDLATCOUNTERClkDomainClks)/sizeof(HAL_clk_mQOSFIXEDLATCOUNTERClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mLPASSClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};

