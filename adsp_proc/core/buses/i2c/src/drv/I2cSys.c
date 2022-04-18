/*=============================================================================

  FILE:   I2cSys.c

  OVERVIEW: This file contains the implementation for the QUP OS Services 
            Interface: IQupI2cDevice 
 
     Copyright (c) 2011-2016 Qualcomm Technologies, Incorporated.
                  All rights reserved.
     Qualcomm Technologies, Confidential and Proprietary.
  ===========================================================================*/
/*=========================================================================
  EDIT HISTORY FOR MODULE

  $Header: //components/rel/core.qdsp6/1.0.c2/buses/i2c/src/drv/I2cSys.c#1 $
  $DateTime: 2020/02/10 01:57:30 $$Author: pwbldsvc $

  When     Who    What, where, why
  -------- ---    -----------------------------------------------------------
  10/14/16 VG     Updated the Copy Rights & Remove unused code
  09/26/11 LK     Created
  ===========================================================================*/

/*-------------------------------------------------------------------------
 * Include Files
 * ----------------------------------------------------------------------*/

#include "I2cSys.h"
#include "busywait.h"

/*-------------------------------------------------------------------------
 * Type Declarations
 * ----------------------------------------------------------------------*/


/*-------------------------------------------------------------------------
 * Externalized Function Definitions
 * ----------------------------------------------------------------------*/

/** @brief Creates an event object.

    @param[out] pEvent  Pointer to event object.
    @return          I2cSys_Result .
  */
int32
I2cSys_CreateEvent
(
   I2cSys_EventType *pEvent
)
{
   return I2CSYS_RESULT_OK;
}



/** @brief Destroys an event object.
 
 @param[out] pEvent  Pointer to event object.
 @return          I2cSys_Result .
 */
int32
I2cSys_DestroyEvent
(
   I2cSys_EventType *pEvent
)
{
   return I2CSYS_RESULT_OK;
}


/** @brief Signals the event object pointed to by the handle.

    @param[in] pEvent  Pointer to event.
    @return           I2cSys_Result .
  */
int32
I2cSys_SetEvent
(
   I2cSys_EventType *pEvent
)
{

   return I2CSYS_RESULT_OK;
}

/** @brief Clears outstanding signals on the event object.

    @param[in] pEvent  Pointer to event.
    @return          I2cSys_Result .
  */
int32
I2cSys_ClearEvent
(
   I2cSys_EventType *pEvent
)
{

   return I2CSYS_RESULT_OK;
}

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
)
{
   return I2CSYS_RESULT_OK;
}

/** @brief Destroys a critical section object and sets the handle pointer.
 
 @param[out] pCritSec  Pointer to critical section object.
 @return          I2cSys_Result .
 */
int32
I2cSys_DestroyCriticalSection
(
   I2cSys_SyncType    *pCritSec
)
{
   qurt_mutex_destroy(&pCritSec->i2c_mutex);
   return I2CSYS_RESULT_OK;
}


/** @brief Creates a critical section object and sets the handle pointer.

    @param[out] pCritSec  Pointer to critical section object.
    @return          I2cSys_Result .
  */
int32
I2cSys_CreateCriticalSection
(
   I2cSys_SyncType    *pCritSec
)
{
   qurt_mutex_init(&pCritSec->i2c_mutex);
   return I2CSYS_RESULT_OK;
}

/** @brief Enters the critical section.

    @param[in] pCritSection  Pointer to critical section object.
    @return          I2cSys_Result .
  */
int32
I2cSys_EnterCriticalSection
(
   I2cSys_SyncType    *pCritSec
)
{
   qurt_mutex_lock(&pCritSec->i2c_mutex);
   return I2CSYS_RESULT_OK;
}

/** @brief Leaves the critical section.

    @param[in] pCritSec   Pointer to critical section object.
    @return          I2cSys_Result .
  */
int32
I2cSys_LeaveCriticalSection
(
   I2cSys_SyncType    *pCritSec
)
{
   qurt_mutex_unlock(&pCritSec->i2c_mutex);
   return I2CSYS_RESULT_OK;
}


/** @brief Frees memory allocated by I2CSYS_Malloc.

    @param[in] pBuffer  pointer to buffer.
    @param[in] c        character byte to init the memory.
    @param[in] size     the size of the buffer. 
    @return          I2CSYS_Result .
  */
int32
I2cSys_Memset
(
   void  *pBuffer,
   int32  c,
   uint32 size
)
{
   return I2CSYS_RESULT_OK;
}

/** @brief Busy waits the uTimeMicrosec microseconds before returning.

  @param[in] uTimeMicrosec  wait time in microseconds.
  @return          Nothing.
  */
void
I2cSys_BusyWait
(
   uint32 uTimeMicrosec
)
{
   busywait (uTimeMicrosec);
}





