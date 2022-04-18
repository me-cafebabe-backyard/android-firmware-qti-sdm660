/*
===========================================================================
*/
/**
  @file ClockAppsAVS.c

  AVS Image specific definitions for MSM8974 apps clock driver.
*/
/*
  ====================================================================

  Copyright (c) 2011-2015, Qualcomm Technologies, Inc.
                   All rights reserved.
                 QUALCOMM Proprietary/GTDR

  ====================================================================
  ====================================================================
*/


/*=========================================================================
      Include Files
==========================================================================*/

#include "Drivers/ClockDxe/ClockDriver.h"
#include "ClockApps.h"
#include "ClockAVS.h"
#include "HALhwio.h"


/*=========================================================================
      Data
==========================================================================*/


/*=========================================================================
      Functions
==========================================================================*/

/* =========================================================================
**  Function : Clock_UpdateAVSDelaySynth
** =========================================================================*/
/*
  API to program the delay synthesizer for a particular CPU.

  This function may be invoked either when enabling AVS or when a change of
  CPU frequency dictates a new value to be programmed to the associated CPU.
  This API should be called only when resuming AVS, as part of the required
  programming of the CPU.

  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
  NOTE: In UEFI, this function supports only core 0.
  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

  @param *pContext [in] -- Context pointer, the driver context in this case.
  @param eCore [in] -- The core that is to be programmed.
  @param *nSynthValue [in] -- The delay synthesizer value to program to the CPU.

  @return
  DAL_ERROR -- if the operation failed.

  @dependencies
  Must be synchronous.
*/

DALResult Clock_UpdateAVSDelaySynth
(
  ClockDrvCtxt     *pDrvCtxt,
  HAL_avs_CoreType eCore,
  uint32           nSynthValue
)
{
  #if 0
  if (nSynthValue)
  {
    /*
     * Update delay synthesizer value.
     */
    HWIO_MCR((nSynthValue), 15, 7, 15, 0, 6);

    /*
     * Enable the AVSCSR coprocessor instructions for AVS.  This value is
     * static for the APPS processor.
     */
    HWIO_MCR(0x21, 15, 7, 15, 1, 7);
  }
  #endif
  return DAL_SUCCESS;

} /* END Clock_UpdateAVSDelaySynth */

