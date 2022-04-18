/*
==============================================================================

FILE:         uTimetick.c

DESCRIPTION:  
  This file implements the required timetick apis 
             to be used in the uImage mode. 

Copyright (c) 2016 Qualcomm Technologies Incorporated.
               All Rights Reserved.
            QUALCOMM Proprietary/GTDR
===============================================================================
*/

/*=============================================================================

                           INCLUDE FILES

=============================================================================*/

#include "msmhwiobase.h"
#include "TimerHWIO.h"
#include "HALhwio.h"
#include "uTimetick.h"
#include "DALSys.h"

/*=========================================================================   
   
                              DATA DEFINITIONS
   
==========================================================================*/

static uint32 QTimerBase = 0;
static uint32 WakeupTimerBase = 0;

/*=============================================================================

                   FUNCTION DEFINITIONS

=============================================================================*/

/*=============================================================================

FUNCTION UTIMETICK_INIT

DESCRIPTION
  Retrieves the QTimer base address from the DAL properties. 

DEPENDENCIES
  None.

RETURN VALUE
  None

SIDE EFFECTS
  None

=============================================================================*/
void uTimetick_Init( void )
{
  static DALSYSPropertyVar system_property_var;
  static DALSYS_PROPERTY_HANDLE_DECLARE(timetick_property);
  
  /* Get the propery handle to timetick DAL */
  DALSYS_GetDALPropertyHandleStr("SystemTimer", timetick_property);
  DALSYS_GetPropertyValue(
    timetick_property, "QTIMER_BASE", 0, &system_property_var);
  QTimerBase = system_property_var.Val.dwVal;
  DALSYS_GetPropertyValue(
    timetick_property, "QTIMER_OFFSET", 0, &system_property_var);
  QTimerBase += system_property_var.Val.dwVal;
  
  DALSYS_GetDALPropertyHandleStr("WakeUpTimer", timetick_property);
  DALSYS_GetPropertyValue(
    timetick_property, "QTIMER_BASE", 0, &system_property_var);
  WakeupTimerBase = system_property_var.Val.dwVal;
  DALSYS_GetPropertyValue(
    timetick_property, "QTIMER_OFFSET", 0, &system_property_var);
  WakeupTimerBase += system_property_var.Val.dwVal;
}

/*=============================================================================

FUNCTION UTIMETICK_GET

DESCRIPTION
  Returns the QTimer Count. The QTimer runs at 19.2MHz 

DEPENDENCIES
  None.

RETURN VALUE
  QTimer Count value

SIDE EFFECTS
  None

=============================================================================*/

uTimetick_type uTimetick_Get( void )
{
  uint32   nCountLow, nCountHi1,nCountHi2;
  uTimetick_type   count64 = 0;

  if (QTimerBase)
  {
    do
    {
     nCountHi1 = HWIO_QTMR_CNTPCT_HI_IN(QTimerBase);
     nCountLow = HWIO_QTMR_CNTPCT_LO_IN(QTimerBase);

     /* repeat the above until the same value is read from the   
       high count register successively */
     nCountHi2 = HWIO_QTMR_CNTPCT_HI_IN(QTimerBase);
    }while (nCountHi1 != nCountHi2);

    count64 = (((uTimetick_type)nCountHi1 <<32)| nCountLow);
  }
  return count64;

} /* uTimetick_Get */

/*=============================================================================

FUNCTION UTIMETICK_CVTFROMTICKS

DESCRIPTION
  Converts the QTimer Ticks to specificed unit.

DEPENDENCIES
  None.

RETURN VALUE
   QTimer Count value in the unit specified.

SIDE EFFECTS
  None

=============================================================================*/

uTimetick_type uTimetick_CvtFromTicks
( 
   uTimetick_type time, 
   uTimetick_unitType unit
)

{
  /* Factor for converting to hours or minutes */
  uint32                          scale = 1;
  uint32 nFreq = HWIO_QTMR_CNTFRQ_IN(QTimerBase);
  uTimetick_type milliseconds=0;

  /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

  switch ( unit )
  {
    case T_HOUR:
      /*  Scale minutes to hours */
      scale *= 60;
      /* fall-through */

    case T_MIN:
      /* Scale seconds to minutes */
      scale *= 60;
      /* fall-through */

    case T_SEC:
      /* Convert slow clocks to seconds (or minutes, or hours) */
      time /= nFreq * scale;
      break;

    case T_MSEC:
      /* Convert ticks to milliseconds */
      if ( time >= nFreq )
      {
        /* Compute seconds portion of time period first, to avoid overflows */
        milliseconds  = (time / nFreq) * 1000;
        time        %= nFreq;
      }

      milliseconds += 
         (time * 1000 + nFreq/2) / nFreq;
      time = milliseconds;

      break;

    case T_USEC:
      /* Convert ticks to microseconds */
      time = ((uint64)time * 1000000) / (uint64)nFreq;
      break;

    case T_TICK:
      /* time = time; */
      break;

    default:
      break;
  }

   return time;

} /* uTimetick_CvtFromTicks */

/*=============================================================================

FUNCTION UTIMETICK_CVTTOTICKS

DESCRIPTION
    Converts the specified time to QTimer equivalent ticks.

DEPENDENCIES
  None.

RETURN VALUE
  QTimer Count ticks equivalent to the time specified.

SIDE EFFECTS
  None

=============================================================================*/

uTimetick_type uTimetick_CvtToTicks
(
   uTimetick_type time,
   uTimetick_unitType unit
)
{
  uint32 nFreq = HWIO_QTMR_CNTFRQ_IN(QTimerBase);

  switch ( unit )
  {
    case T_HOUR:
      /* Convert hours to minutes */
      time *= 60;
      /* fall-through */

    case T_MIN:
      /* Convert minutes to seconds */
      time *= 60;
      /* fall-through */

    case T_SEC:
      /* Seconds to ticks */
      time *= nFreq;
      break;

    case T_MSEC:
      /* Milliseconds to ticks */
      time = (time * nFreq)/ 1000;
      break;

    case T_USEC:
      /* Microseconds to ticks */
      time = ((time * nFreq) / 1000000);
      break;

    case T_TICK:
      /* time = time; */
      break;

    default:
      break;

  }
   return time;

} /* uTimetick_CvtToTicks */


/*=============================================================================

FUNCTION UTIMETICK_SETWAKEUPTIMERINTERRUPT

DESCRIPTION
  Program the match value for Wakeup Timer 

DEPENDENCIES
  None.

RETURN VALUE
  None

SIDE EFFECTS
  None

=============================================================================*/

void uTimetick_SetWakeUpTimerInterrupt( uint64 matchValue )
{
  uint32   nMatchLow, nMatchHi;

  nMatchLow = ( matchValue & 0xFFFFFFFF);
  nMatchHi = matchValue >>32;
  HWIO_QTMR_CNTP_CVAL_HI_OUT(WakeupTimerBase, nMatchHi);
  HWIO_QTMR_CNTP_CVAL_LO_OUT(WakeupTimerBase, nMatchLow);

  return;

} /* uTimetick_SetWakeUpTimerInterrupt */

/*=============================================================================

FUNCTION UTIMETICK_ENABLEWAKEUPTIMERINTERRUPT

DESCRIPTION
   Enable/Disable the WakeupTimer interrupt. 

DEPENDENCIES
  None.

RETURN VALUE
  None

SIDE EFFECTS
  None

=============================================================================*/

void uTimetick_EnableWakeUpTimerInterrupt( boolean enable )
{
  HWIO_QTMR_CNTP_CTL_OUTM(WakeupTimerBase, HWIO_QTMR_CNTP_CTL_EN_BMSK, enable);

  return;

} /* uTimetick_SetWakeUpTimerInterrupt */