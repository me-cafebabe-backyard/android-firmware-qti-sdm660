/*=========================================================================

                M S M   C L O C K   D E V I C E   D R I V E R

               A D A P T I V E   V O L T A G E   S C A L I N G

GENERAL DESCRIPTION
  This file contains the implementation for the MSM Clock Device
  Adaptive Voltage Scaling software.

INITIALIZATION AND SEQUENCING REQUIREMENTS
  Invoke the Clock_InitAVS function to initialize all data structures and
  base addresses before calling any other API.  This ensures all AVS
  hardware has been initialized and HW accesses will work.

      Copyright (c) 2011 by QUALCOMM Technologies, Inc.  All Rights Reserved.

==========================================================================*/

/*==========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     --------------------------------------------------------
03/15/11   dcf     Created.

==========================================================================*/

/*==========================================================================

                     INCLUDE FILES FOR MODULE

==========================================================================*/

#include "Library/HALclkSharedLib/HALavs.h"
#include <HALclk.h>
#include <DALDeviceId.h>
#include "ClockAVS.h"
#include "Drivers/ClockDxe/ClockDriver.h"


/*==========================================================================

               FUNCTION DECLARATIONS FOR MODULE

==========================================================================*/

#define Clock_UpdateAVSDelaySynth(val1, val2, val3)

/*
 *  Static pointer to the BSP data for AVS.
 */
static ClockAVSCoreConfigType *pClockBases = NULL;

/*
 *  Global boolean value to specify if AVS is enabled.
 */
static boolean bIsEnabledAVS = FALSE;

/*
 *  Global structure to hold current frequency information.
 */
static ClockAVSCoreFreqCfgType *paCurrentCoreCfg[HAL_AVS_NUM_CORES];


/*==========================================================================

               FUNCTION DECLARATIONS FOR MODULE

==========================================================================*/


/* =========================================================================
**  Function : Clock_InitAVS
** =========================================================================*/
/*
  See ClockAVS.h
*/

DALResult Clock_InitAVS
(
  ClockDrvCtxt          *pDrvCtxt,
  ClockAVSInitType      *pInit
)
{
  uint32 eCPU;
  HAL_avs_CoreType  eCore;
  DALResult eResult = DAL_ERROR;
  uint32 nIdx = 0;
  HAL_avs_ContextType pHALCtxt;
  HAL_avs_CoreDataType HALCoreData[HAL_AVS_NUM_CORES];
  ClockPropertyValueType PropVal = NULL;

  /*
   * Initialize the temporary data structure to 0.
   */
  memset((void *)HALCoreData, 0x0,
         sizeof(HAL_avs_CoreDataType)*HAL_AVS_NUM_CORES);

  /*
   * Get a pointer to the AVS BSP data.
   */
  eResult = Clock_GetPropertyValue("AVSData", &PropVal);

  if (eResult != DAL_SUCCESS)
  {
    DALSYS_LogEvent (
      DALDEVICEID_CLOCK, DALSYS_LOGEVENT_FATAL_ERROR,
      "AVS Initialization failed in DAL properties retrieval.");
    return(eResult);
  }

  pClockBases = (ClockAVSCoreConfigType *)PropVal;

  if( !pClockBases )
  {
    DALSYS_LogEvent (
      DALDEVICEID_CLOCK, DALSYS_LOGEVENT_FATAL_ERROR,
      "AVS Initialization failed to retrieve BSP data structure.");
    return(DAL_ERROR);
  }

  /*-----------------------------------------------------------------------*/
  /* Map any virtual addresses needed by each core and hook up virtual     */
  /* addresses to the HAL Address array.  Note that the AVS region is 4K.  */
  /*-----------------------------------------------------------------------*/

  while( pClockBases[nIdx].nPhysicalBase != 0 )
  {
    eCPU = pClockBases[nIdx].eCore;
    eCore = (HAL_avs_CoreType)eCPU;

    if(eCore < HAL_AVS_NUM_CORES)
    {
      eResult = Clock_MapHWIORegion(
        pClockBases[nIdx].nPhysicalBase, 0x1000, &HALCoreData[eCore].nBaseAddr);

      if (eResult != DAL_SUCCESS)
      {
        DALSYS_LogEvent (
          DALDEVICEID_CLOCK, DALSYS_LOGEVENT_FATAL_ERROR,
          "AVS init failed to map memory for base 0x%8lx, on core ID[%d].",
          pClockBases[nIdx].nPhysicalBase,
          pClockBases[nIdx].eCore);

        return(eResult);
      }

      HALCoreData[eCore].ePMIC = pClockBases[nIdx].ePMIC;
    }
    nIdx++;
  }

  /*
   * If no core base address has been initialized, AVS HW cannot run.
   */
  if( nIdx == 0 )
  {
    DALSYS_LogEvent (
      DALDEVICEID_CLOCK, DALSYS_LOGEVENT_FATAL_ERROR,
      "AVS Initialization failed:  No cores to initialize from properties file.");
    return(DAL_ERROR);
  }

  /*
   * Connect the busywait and core initializers for HAL AVS.
   */
  pHALCtxt.BusyWait = DALSYS_BusyWait;
  pHALCtxt.pCoreData = HALCoreData;
  pHALCtxt.nChipId = HAL_clk_GetChipId();
  pHALCtxt.nChipVersion = HAL_clk_GetChipVersion();

  /*
   * Initialize HAL.
   */
  HAL_avs_Init(&pHALCtxt);

  nIdx = 0;

  /*
   * Set up each core's AVS controller parameters based on the BSP data.
   */

  if(pInit != NULL)
  {
    while( pClockBases[nIdx].nPhysicalBase != 0 )
    {
      if(pInit[nIdx].pCurrCfg != NULL)
      {
        eCore = (HAL_avs_CoreType)pClockBases[nIdx].eCore;

        if( eCore >= HAL_AVS_NUM_CORES )
        {
          break;
        }

        /*
         * Initialize the configuration data for this core for enable/resume APIs.
         */

        paCurrentCoreCfg[eCore] = pInit[nIdx].pCurrCfg;

        /*
         * Initialize the AVS FSM HW with an initial voltage write using the current Vdd.
         */

        HAL_avs_SetCurrentVoltage(eCore, pInit[nIdx].pCurrCfg->nPerfVdd);

        /*
         * Set up the delay between voltage requests to HW.
         */

        HAL_avs_SetDelay(eCore, pClockBases[nIdx].nVddRequestDelay);

        /*
         * Set up the clock divider for the AVS circuitry.
         */

        HAL_avs_SetClockDivider(eCore, pClockBases[nIdx].nClockDiv);

        /*
         * Set up the Vdd ramping step size.
         */

        HAL_avs_SetVoltageStepSize(eCore, pClockBases[nIdx].eStepSize);

        /*
         * Configure the Vdd width for HW requests to PMIC arbiter.
         */

        HAL_avs_SetVoltageWidth(eCore, pClockBases[nIdx].ePMIC);
      }

      nIdx++;
    }
  }

  /*-----------------------------------------------------------------------*/
  /* AVS initialization complete                                          */
  /*-----------------------------------------------------------------------*/

  return DAL_SUCCESS;

} /* END Clock_InitAVS */



/* =========================================================================
**  Function : Clock_SetVoltageLevel
** =========================================================================*/
/*
  See ClockAVS.h
*/

DALResult Clock_SetVoltageLevel
(
  HAL_avs_CoreType eCore,
  uint32 nVoltage
)
{
  if(eCore < HAL_AVS_NUM_CORES)
  {
    if (HAL_avs_SetCurrentVoltage(eCore, nVoltage))
    {
      return(DAL_SUCCESS);
    }
    return(DAL_ERROR);
  }

  return(DAL_ERROR);

} /* END Clock_SetVoltageLevel */



/* =========================================================================
**  Function : Clock_HaltAVS
** =========================================================================*/
/*
  See ClockAVS.h
*/

DALResult Clock_HaltAVS
(
  ClockDrvCtxt     *pDrvCtxt,
  HAL_avs_CoreType eCore
)
{
  /*
   * Stop the AVS HW adjustments for this core.
   */
  if(bIsEnabledAVS)
  {
    if(eCore < HAL_AVS_NUM_CORES)
    {
      HAL_avs_Enable(eCore, FALSE);
    }
  }

  return(DAL_SUCCESS);

} /* END Clock_HaltAVS */



/* =========================================================================
**  Function : Clock_ResumeAVS
** =========================================================================*/
/*
  See ClockAVS.h
*/

DALResult Clock_ResumeAVS
(
  ClockDrvCtxt            *pDrvCtxt,
  HAL_avs_CoreType        eCore,
  ClockAVSCoreFreqCfgType *pResumeData
)
{
  static uint32 nCurrentDelayValues[HAL_AVS_NUM_CORES];

  /*
   * Update the current Core configuration data.
   */

  if(eCore < HAL_AVS_NUM_CORES)
  {
    paCurrentCoreCfg[eCore] = pResumeData;

    if(bIsEnabledAVS)
    {
      /*
       * Do not resume AVS if minimum voltage is the same as or greater than DCVS level
       * which indicates that AVS is not allowed or if the frequency level dictates
       * AVS should not run.
       */

      if (pResumeData->nMinVdd == pResumeData->nPerfVdd)
      {
        return DAL_SUCCESS;
      }

      if(pResumeData->nMinVdd > pResumeData->nPerfVdd)
      {
        DALSYS_LogEvent (
          DALDEVICEID_CLOCK, DALSYS_LOGEVENT_FATAL_ERROR,
          "Clock_ResumeAVS failed:  MinVdd is greater than MaxVdd.");
        return(DAL_ERROR);
      }

      /*
       * Update the delay synthesizer if required for this frequency.
       */

      if(pResumeData->nDelaySynth != nCurrentDelayValues[eCore])
      {
        Clock_UpdateAVSDelaySynth(pDrvCtxt, eCore, pResumeData->nDelaySynth);
        nCurrentDelayValues[eCore] = pResumeData->nDelaySynth;
      }

      /*
       * Set the voltage floor and ceiling for this core entry.
       */

      HAL_avs_SetMinVoltage(eCore, pResumeData->nMinVdd);

      HAL_avs_SetMaxVoltage(eCore, pResumeData->nPerfVdd);

      /*
       * Enable AVS for this core.
       */

      HAL_avs_Enable(eCore, TRUE);

      return DAL_SUCCESS;
    }

    return(DAL_SUCCESS);
  }
  else
  {
    return(DAL_ERROR);
  }

} /* END Clock_ResumeAVS */


/* =========================================================================
**  Function : Clock_EnableAVS
** =========================================================================*/
/*
  See DDIClock.h
*/

DALResult Clock_EnableAVS
(
  ClockDrvCtxt *pDrvCtxt
)
{
  uint32 nIdx = 0;
  DALResult eResult = DAL_ERROR;

  DALCLOCK_LOCK(pDrvCtxt);

  /*
   * Loop through supported cores and enable AVS.
   */

  if(pClockBases)
  {
    bIsEnabledAVS = TRUE;

    while( pClockBases[nIdx].nPhysicalBase != 0 )
    {
      /*
       * Attempt to enable AVS.
       */

      if(paCurrentCoreCfg[pClockBases[nIdx].eCore])
      {
        eResult = Clock_ResumeAVS(pDrvCtxt,
                                  pClockBases[nIdx].eCore,
                                  paCurrentCoreCfg[pClockBases[nIdx].eCore]);

        if(eResult != DAL_SUCCESS)
        {
          DALSYS_LogEvent (
            DALDEVICEID_CLOCK, DALSYS_LOGEVENT_FATAL_ERROR,
            "Clock_EnableAVS:  Failed to resume AVS core %d.", pClockBases[nIdx].eCore);
        }
      }
      nIdx++;
    }
  }

  DALCLOCK_FREE(pDrvCtxt);

  return(DAL_SUCCESS);

} /* END Clock_EnableAVS */


/* =========================================================================
**  Function : Clock_SetPowerMode
** =========================================================================*/
/*
  See ClockAVS.h
*/

DALResult Clock_SetPowerMode
(
  HAL_avs_CoreType  eCore,
  HAL_avs_PowerMode eMode
)
{
  if (HAL_avs_SetPowerMode(eCore, eMode))
  {
    return(DAL_SUCCESS);
  }

  return(DAL_ERROR);

} /* END Clock_SetPowerMode */

