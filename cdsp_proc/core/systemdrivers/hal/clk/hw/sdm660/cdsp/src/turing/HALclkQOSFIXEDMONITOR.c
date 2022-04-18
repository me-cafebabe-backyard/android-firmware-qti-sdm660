/*
==============================================================================

FILE:         HALclkQOSFIXEDMONITOR.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   QOSFIXEDMONITOR clocks.

   List of clock domains:
     - HAL_clk_mTURINGQOSFIXEDLATCOUNTERSRCClkDomain


   List of power domains:



==============================================================================

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/hal/clk/hw/sdm660/cdsp/src/turing/HALclkQOSFIXEDMONITOR.c#1 $

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

extern HAL_clk_ClockDomainControlType  HAL_clk_mTURINGClockDomainControl;
extern HAL_clk_ClockDomainControlType  HAL_clk_mTURINGClockDomainControlRO;


/* ============================================================================
**    Data
** ==========================================================================*/


/*                           
 *  HAL_clk_mQOSFIXEDLATCOUNTERSRCClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mQOSFIXEDLATCOUNTERSRCClkDomainClks[] =
{
  {
    /* .szClockName      = */ "turing_wrapper_qos_danger_fixed_lat_counter_clk",
    /* .mRegisters       = */ { HWIO_OFFS(TURING_TURING_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_TURING_TEST_TURING_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CLK
  },
  {
    /* .szClockName      = */ "turing_wrapper_qos_dmonitor_fixed_lat_counter_clk",
    /* .mRegisters       = */ { HWIO_OFFS(TURING_TURING_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_TURING_TEST_TURING_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CLK
  },
};


/*
 * HAL_clk_mTURINGQOSFIXEDLATCOUNTERSRCClkDomain
 *
 * QOSFIXEDLATCOUNTERSRC clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mTURINGQOSFIXEDLATCOUNTERSRCClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(TURING_QOS_FIXED_LAT_COUNTER_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mQOSFIXEDLATCOUNTERSRCClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mQOSFIXEDLATCOUNTERSRCClkDomainClks)/sizeof(HAL_clk_mQOSFIXEDLATCOUNTERSRCClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mTURINGClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};

