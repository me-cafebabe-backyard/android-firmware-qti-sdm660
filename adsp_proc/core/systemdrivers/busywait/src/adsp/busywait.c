/*=========================================================================

                         Busywait

GENERAL DESCRIPTION
  This file contains the implementation of the busywait() function for
  hardware based blocking waits that use the QTIMER as a
  reference.

EXTERNALIZED FUNCTIONS
  busywait

INITIALIZATION AND SEQUENCING REQUIREMENTS
 None

      Copyright (c) 2016 by Qualcomm Technologies Incorporated.
      All Rights Reserved.
      QUALCOMM Proprietary and Confidential.
==========================================================================*/

/*==========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.
 
  $Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/busywait/src/adsp/busywait.c#1 $
  $DateTime: 2020/02/10 01:57:30 $
  $Author: pwbldsvc $

when       who     what, where, why 
--------   ---     --------------------------------------------------------- 
08/25/16   shm     Initial version for core.qdsp6

==========================================================================*/ 

/*==========================================================================

                     INCLUDE FILES FOR MODULE

==========================================================================*/

#include "busywait.h"


/*==========================================================================

                  DEFINITIONS AND DECLARATIONS FOR MODULE

==========================================================================*/

/*=========================================================================
      Constants and Macros 
==========================================================================*/

#define BUSYWAIT_XO_FREQUENCY_IN_KHZ 19200

/*=========================================================================
      Typedefs
==========================================================================*/


/*=========================================================================
      Variables
==========================================================================*/

/*==========================================================================

                         FUNCTIONS FOR MODULE

==========================================================================*/

/*==========================================================================

  FUNCTION      BUSYWAIT_INIT

  DESCRIPTION   None

  PARAMETERS    None

  DEPENDENCIES  None

  RETURN VALUE  None

  SIDE EFFECTS  None

==========================================================================*/

void busywait_init(void)
{

}

/*==========================================================================

  FUNCTION      BUSYWAIT

  DESCRIPTION   This function pauses the execution of a thread for a
                specified time.

  PARAMETERS    pause_time_us - Time to pause in microseconds

  DEPENDENCIES  None

  RETURN VALUE  None.

  SIDE EFFECTS  The UGPT counter will be enabled and left running to 
                support nested busywait calls, i.e. to support 
                multithreading and/or ISRs..

==========================================================================*/

void busywait
(
  uint32 pause_time_us
)
{
  uint64 utimer = 0;
  uint64 start_count = 0;
  uint64 delay_count = 0;

  __asm__ volatile ("%[start_count] = UTIMER" : [start_count] "=r"(start_count));
  utimer = start_count;
  
  /*
   * Perform the delay and handle potential overflows of the timer.
   */
  delay_count = (pause_time_us * (uint64)BUSYWAIT_XO_FREQUENCY_IN_KHZ)/1000;
  
  while ((utimer - start_count) < delay_count)
  {
    __asm__ volatile ("pause(#50)");
    __asm__ volatile ("%[utimer] = UTIMER" : [utimer] "=r"(utimer));
  }
}
