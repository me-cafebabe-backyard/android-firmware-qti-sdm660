#ifndef VMPM_H
#define VMPM_H

/*===========================================================================

        V I R T U A L  M P M   I N T E R R U P T   C O N T R O L L E R

GENERAL DESCRIPTION
  This file contains the definitions for the virtual MPM interrupt controller.
  The virtual MPM interrupt controller is a service offered by the RPM to allow
  every processor in the system manage which interrupts are enabled in the MPM
  at sleep time.

EXTERNAL FUNCTIONS
  vmpm_init
    Do something.

INITIALIZATION AND SEQUENCING REQUIREMENTS
  Function vmpm_init() should be called before any of the VMPM services can be
  used.

Copyright (c) 2009 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
===========================================================================*/

/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/rpm.bf/1.8/core/power/mpm/inc/vmpm.h#1 $
   
when       who     what, where, why
--------   ---     ----------------------------------------------------------
09/14/09   ajf     Created.

===========================================================================*/


/*
 * Include files
 */
#include <comdef.h>


/*
 * Function prototypes
 */

/** Initialize the VMPM service.
 *
 * Initializes the VMPM service for operation, registering ISRs to handle
 * master VMPM requests.
 */
extern void vmpm_init(void);

/** Program MPM with the net configuration of all masters.
 *
 * Should be called before sleep.  Activates the MPM so it can wake us from
 * sleep whenever a configured interrupt is received.
 */
extern void vmpm_prepare_for_sleep(void);

/** Read MPM pending interrupts and pass them on to masters.
 *
 * Should be called after sleep.  Queries the MPM for its pending interrupts
 * and passes them on to all masters, sending interrupts to those masters if
 * they have requested the pending interrupts to be enabled.
 *
 * Also clears the pending MPM interrupts after it reads them.
 */
extern void vmpm_propogate_interrupts(void);

#endif /* VMPM_H */

