#ifndef _I2CSYS_H_
#define _I2CSYS_H_
/*===========================================================================
  @file   I2cSys.h

  This file contains the API for the QUP OS Services 
 
  Copyright (c) 2011-2016 Qualcomm Technologies, Incorporated.
                  All rights reserved.
  Qualcomm Technologies, Confidential and Proprietary.
  ===========================================================================*/
/*=========================================================================
  EDIT HISTORY FOR MODULE

 $Header: //components/rel/core.qdsp6/1.0.c2/buses/i2c/src/drv/I2cSys.h#1 $ 

  When     Who    What, where, why
  -------- ---    -----------------------------------------------------------
  10/14/16 VG     Updated the Copy Rights & removed DAL based code
  04/08/16 VG     created
  ===========================================================================*/

/*-------------------------------------------------------------------------
 * Include Files
 * ----------------------------------------------------------------------*/
#include "I2cSysTypes.h"

/*-------------------------------------------------------------------------
 * Type Declarations
 * ----------------------------------------------------------------------*/

/**
   Some of the most common errors may be defined here.
   Each OS defines its own values which will be interpreted
   differently based on OS.
 */
typedef enum
{
   I2CSYS_RESULT_OK = 0,
   I2CSYS_RESULT_ERROR_BASE = I2C_RES_ERROR_CLS_DEV_OS,
   I2CSYS_RESULT_ERROR_EVT_WAIT_TIMEOUT,

   I2CSYS_RESULT_FIRST_SECTION = I2CSYS_RESULT_ERROR_EVT_WAIT_TIMEOUT,
   I2CSYS_RESULT_SECOND_SECTION = I2CSYS_RESULT_FIRST_SECTION+1000,


} I2cSys_Result;

typedef void* I2CSYS_EVENT_HANDLE;

typedef void* I2CSYS_CRITSECTION_HANDLE;
typedef void* I2CSYS_INTLOCK_HANDLE;


/*-------------------------------------------------------------------------
 * Function Declarations and Documentation
 * ----------------------------------------------------------------------*/

/** @brief Creates an event object.

    @param[out] pEvent  Pointer to event object.
    @return          I2cSys_Result .
  */
int32
I2cSys_CreateEvent
(
   I2cSys_EventType *pEvent
);

/** @brief Destroys an event object.
 
 @param[out] pEvent  Pointer to event object.
 @return          I2cSys_Result .
 */
int32
I2cSys_DestroyEvent
(
   I2cSys_EventType *pEvent
);

/** @brief Signals the event object pointed to by the handle.

    @param[in] pEvent  Pointer to event.
    @return           I2cSys_Result .
  */
int32
I2cSys_SetEvent
(
   I2cSys_EventType *pEvent
);

/** @brief Clears outstanding signals on the event object.

    @param[in] pEvent  Pointer to event.
    @return          I2cSys_Result .
  */
int32
I2cSys_ClearEvent
(
   I2cSys_EventType *pEvent
);

/** @brief Wait with a timeout on the event object.

    @param[in] pEvent  Pointer to event.
    @param[in] dwMilliseconds  Event wait timeout.
    @return          I2cSys_Result .
  */
int32
I2cSys_Wait
(
   I2cSys_EventType   *pEvent,
   uint32              dwMilliseconds
);

/** @brief Creates a critical section object and sets the handle pointer.

    @param[out] pCritSec  Pointer to critical section object.
    @return          I2cSys_Result .
  */
int32
I2cSys_CreateCriticalSection
(
   I2cSys_SyncType    *pCritSec
);

/** @brief Enters the critical section.

    @param[in] pCritSection  Pointer to critical section object.
    @return          I2cSys_Result .
  */
int32
I2cSys_EnterCriticalSection
(
   I2cSys_SyncType    *pCritSec
);

/** @brief Leaves the critical section.

    @param[in] pCritSec   Pointer to critical section object.
    @return          I2cSys_Result .
  */
int32
I2cSys_LeaveCriticalSection
(
   I2cSys_SyncType    *pCritSec
);

/** @brief Destroys a critical section object and sets the handle pointer.
 
 @param[out] pCritSec  Pointer to critical section object.
 @return          I2cSys_Result .
 */
int32
I2cSys_DestroyCriticalSection
(
   I2cSys_SyncType    *pCritSec
);

/** @brief Busy waits the uTimeMicrosec microseconds before returning.

  @param[in] uTimeMicrosec  wait time in microseconds.
  @return          Nothing.
  */
void
I2cSys_BusyWait
(
   uint32 uTimeMicrosec
);

#endif /* #ifndef I2CSYS_H */

