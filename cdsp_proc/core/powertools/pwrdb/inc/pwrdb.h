#ifndef PWRDB_H
#define PWRDB_H
/*===========================================================================

                    P W R   D E B U G   H E A D E R 
                      
DESCRIPTION


GENERAL DESCRIPTION
  This is the power debug header to define the power debugger interfaces.

  
EXTERNALIZED FUNCTIONS

  pwrdb_task() - Task for the power debug module.


INITIALIZATION AND SEQUENCING REQUIREMENTS

  Must create and start pwrdb task before commands will be processed by pwrdb.
  

  Copyright (c) 2008, 2009 by QUALCOMM Technologies, Incorporated.  All Rights Reserved.
  
===========================================================================*/

/*===========================================================================

                      EDIT HISTORY FOR FILE

$Header: //components/rel/core.qdsp6/1.0.c2/powertools/pwrdb/inc/pwrdb.h#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
08/14/08   ts      Created file.

===========================================================================*/


/*==========================================================================

                     INCLUDE FILES FOR MODULE

==========================================================================*/
#include "comdef.h"

/*===========================================================================

            DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains local definitions for constants, macros, types,
variables and other items needed by this module.

===========================================================================*/

/*===========================================================================

FUNCTION PWRDB_TASK

DESCRIPTION
  This is the power debug task, created via rex_def_task from the Main 
  Control task.

  See pwrdb_task.c for more information.

DEPENDENCIES
  None.

RETURN VALUE
  None.

SIDE EFFECTS
  Power debug task is created.

===========================================================================*/

void  pwrdb_task
( 
    dword unused          /* from REX - ignored */
);

#endif /* PWRDB_H */
