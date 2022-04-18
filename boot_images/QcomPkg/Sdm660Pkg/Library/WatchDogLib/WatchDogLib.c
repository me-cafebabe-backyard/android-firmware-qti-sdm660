/**@file WatchDogLib.c

  Copyright (c) 2016, Qualcomm Technologies Inc. All rights reserved.<BR>

**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 
 --------   ---     -----------------------------------------------------------
 06/13/16   vk      Initial version
=============================================================================*/

#include <Library/DebugLib.h>
#include <Library/ArmLib.h>
#include <Library/IoLib.h>
#include <Library/WatchdogLib.h>

#define APCS_WDT_TMR1_WDOG_BITE_TIME 0x17817014
#define APCS_WDT_TMR1_WDOG_CTL       0x17817008

#define BITE_TIME 4
#define ENABLE    1

EFI_STATUS
DoWatchDogReset ( VOID )
{
  /* BITE Time */
  MmioWrite32(APCS_WDT_TMR1_WDOG_BITE_TIME, BITE_TIME);
  ArmInstructionSynchronizationBarrier();

  /* CTL, Enable */
  MmioWrite32(APCS_WDT_TMR1_WDOG_CTL, ENABLE);
  ArmInstructionSynchronizationBarrier();

  return EFI_SUCCESS;
}
