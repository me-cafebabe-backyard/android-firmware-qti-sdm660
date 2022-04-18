/*=========================================================================

                         Busywait

GENERAL DESCRIPTION
  This file contains the implementation of the busywait() function for
  hardware based blocking waits that use the IEC_BSY_WAIT_COUNTER as a
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
 
  $Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/busywait/src/adsp_slpi/busywait.c#1 $
  $DateTime: 2020/02/10 01:57:30 $
  $Author: pwbldsvc $

when       who     what, where, why 
--------   ---     --------------------------------------------------------- 
08/25/16   shm     Initial version for core.qdsp6

==========================================================================*/ 

/*==========================================================================

                     INCLUDE FILES FOR MODULE

==========================================================================*/

#include "HALhwio.h"
#include "busywaitTimerHWIO.h"
#include "busywait.h"


/*==========================================================================

                  DEFINITIONS AND DECLARATIONS FOR MODULE

==========================================================================*/

/*=========================================================================
      Constants and Macros 
==========================================================================*/

#define BUSYWAIT_XO_FREQUENCY_IN_KHZ 20000

/*=========================================================================
      Typedefs
==========================================================================*/


/*=========================================================================
      Variables
==========================================================================*/
static boolean bIsBusywaitEnabled = 0;

/*==========================================================================

                         FUNCTIONS FOR MODULE

==========================================================================*/

/*==========================================================================

  FUNCTION      BUSYWAIT_INIT

  DESCRIPTION   This function enables the Busywait Counter.

  PARAMETERS    None

  DEPENDENCIES  None

  RETURN VALUE  None

  SIDE EFFECTS  None

==========================================================================*/

void busywait_init(void)
{
  if (!bIsBusywaitEnabled)
  {
    /* Enable the Busywait Counter. */
    HWIO_LPASS_SCSR_IEC_BSY_WAIT_OUTM(
      LPASS_SCSR_REGS_REG_BASE,
      HWIO_LPASS_SCSR_IEC_BSY_WAIT_BUSY_WAIT_EN_BMSK,
      (1 << HWIO_LPASS_SCSR_IEC_BSY_WAIT_BUSY_WAIT_EN_SHFT));
    
    bIsBusywaitEnabled = 1;
  }
}

/*==========================================================================

  FUNCTION      BUSYWAIT

  DESCRIPTION   This function pauses the execution of a thread for a
                specified time.

  PARAMETERS    pause_time_us - Time to pause in microseconds

  DEPENDENCIES  busywait_init needs to be called before this.
                This being done through RCINIT.

  RETURN VALUE  None.

  SIDE EFFECTS  The Busywait counter will be enabled and left running to
                support nested busywait calls, i.e. to support
                multithreading and/or ISRs

==========================================================================*/

void busywait
(
  uint32 pause_time_us
)
{
  uint32 start_count = 0;
  uint64 delay_count = 0;
  
  if (bIsBusywaitEnabled)
  {
    start_count = HWIO_LPASS_SCSR_IEC_BUSY_WAIT_CNTR_VAL0_IN(LPASS_SCSR_REGS_REG_BASE);
    /*
     * Perform the delay.
     */
    delay_count = (pause_time_us * (uint64)BUSYWAIT_XO_FREQUENCY_IN_KHZ)/1000;
    while ((HWIO_LPASS_SCSR_IEC_BUSY_WAIT_CNTR_VAL0_IN(LPASS_SCSR_REGS_REG_BASE)
              - start_count) < delay_count);
  }
}
