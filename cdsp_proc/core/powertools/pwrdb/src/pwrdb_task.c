/*===========================================================================

                      P W R   D E B U G   T A S K
                      
DESCRIPTION

GENERAL DESCRIPTION

  This file contains the code for the power debugger task.
  
EXTERNALIZED FUNCTIONS

  pwrdb_task - The entry point for the power debug task.

REGIONAL FUNCTIONS

  None

INITIALIZATION AND SEQUENCING REQUIREMENTS

  Must start the power debug task before performing any operations with
  power debugger.
  

  Copyright (c) 2014 by QUALCOMM Technologies, Incorporated.  All Rights Reserved.
  
===========================================================================*/

/*===========================================================================

                      EDIT HISTORY FOR FILE

$Header: //components/rel/core.qdsp6/1.0.c2/powertools/pwrdb/src/pwrdb_task.c#1 $

when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
09/29/14   dy      Remove ChipID detection
04/04/14   gw      Added support for MSM8916. 
03/28/14   gw      Added test on chipinfo before allowing PWRDB to accept 
                   commands. 
05/01/09   gw      Refactoring based on code review comments.
04/10/09   gw      Added some debug messaging.
11/21/08   gw      Created task

===========================================================================*/

/* <EJECT> */
/*==========================================================================

                     INCLUDE FILES FOR MODULE

==========================================================================*/

#include "rcinit.h"
#include "pwrdb.h"
#include "pwrdbi.h"


#include "tracer.h"
#include "pwrdb_tracer_event_ids.h"

#include "queue.h"

/* #include <KxMutex.h> */

/* <EJECT> */
/*===========================================================================

            DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains local definitions for constants, macros, types,
variables and other items needed by this module.

===========================================================================*/
/* Signal to the Task  */
#define PWRDB_TASK_CMD_SIG             0x0000


#define PWRDB_TASK_CMD_QUEUE_LEN       15

/* <EJECT> */
/*==========================================================================

                     VARIABLES

==========================================================================*/
static pwrdb_task_queue_type pwrdb_task_queue_pool[PWRDB_TASK_CMD_QUEUE_LEN];
static q_type                pwrdb_task_cmd_free_queue;
static q_type                pwrdb_task_cmd_queue;

static uint32                pwrdb_dal_sig;
static DALSYSEventHandle     pwrdb_dal_events[PWRDB_TASK_TOTAL_EVENTS];
static DALSYSEventHandle     pwrdb_task_cmd_event;

/*===========================================================================

FUNCTION PWRDB_TASK_CMD_QUEUE_INIT

DESCRIPTION
  Initialize the power debug task's command queue.

SIDE EFFECTS
  None.

===========================================================================*/
static void pwrdb_task_cmd_queue_init( void )
{
  int i;

  /* init the queues and the items and add all the items to the free queue */
  (void) q_init( &pwrdb_task_cmd_free_queue );
  (void) q_init( &pwrdb_task_cmd_queue );

  for (i=0; i<PWRDB_TASK_CMD_QUEUE_LEN; i++)
  {
    (void) q_link( &(pwrdb_task_queue_pool[i]),  
                   &(pwrdb_task_queue_pool[i].link) );
    (void) q_put( &pwrdb_task_cmd_free_queue, 
                  &(pwrdb_task_queue_pool[i].link) );
  }
}

/*===========================================================================

FUNCTION PWRDB_TASK_CMD_SEND

DESCRIPTION
  Send a command to the power debug task by placing it in the command queue.  

PARAMETERS
  cmd   - command to send
  p1,p2 - parameters to the command (meaning depends on command)

DPENDENCIES
  Command queue must have previously been initialized by calling 
  pwrdb_task_cmd_queue_init().

SIDE EFFECTS
  None.

===========================================================================*/
void pwrdb_task_cmd_send( pwrdb_task_cmd_type cmd, uint32 p1, uint32 p2 )
{
  pwrdb_task_queue_type *c_ptr;

  /* get a queue item */
  c_ptr = (pwrdb_task_queue_type *)q_get( &pwrdb_task_cmd_free_queue );

  if (c_ptr == NULL)
  {
    /* queue is full */
    pwrdb_error_str = "Task command queue overflow.";
    /* pwrdb_state_change( PWRDB_STATE_ERROR ); */
    return;
  }

  /* populate the item */
  c_ptr->cmd    = cmd;
  c_ptr->param1 = p1;
  c_ptr->param2 = p2;

  /* post the item to the queue */
  q_put( &pwrdb_task_cmd_queue, &(c_ptr->link) );
  /* We have put the command in the queue lets check for the pwrdb state
     before triggering a signal */
  if( (pwrdb_state==PWRDB_STATE_READY_FOR_SCRIPTS) || (pwrdb_state==PWRDB_STATE_RUNNING) )
  {
    if( DAL_SUCCESS != DALSYS_EventCtrl(pwrdb_task_cmd_event, DALSYS_EVENT_CTRL_TRIGGER ))
      ERR_FATAL("Pwrdb DalSys Event Ctrl Error",0,0,0);
  }  
}

/*===========================================================================

FUNCTION PWRDB_TASK

DESCRIPTION
  This is the power debug task, created via rex_def_task from the Main 
  Control task. This task sets MC_ACK_SIG when it is done with initialization
  and it then waits for PWRDB_START_SIG before starting its normal operations.
  The power debug task then enters a main loop, awaiting signals from other 
  functions in the power debug modle. Each signal received is processed and 
  the loop continues. The power debug task does not need to report to the 
  dog task.

DEPENDENCIES
  None.

RETURN VALUE
  None.

SIDE EFFECTS
  None.

===========================================================================*/

void  pwrdb_task
( 
  dword unused
)
{
  (void) unused; // silence compiler warnings of unused parameter
  rcinit_handshake_startup();

  /* Init task command queue */
  pwrdb_task_cmd_queue_init();

  /* Do rest of initialization */
  pwrdb_init();

  if(DAL_SUCCESS != DALSYS_EventCreate( DALSYS_EVENT_ATTR_NORMAL,&pwrdb_task_cmd_event,NULL ))
    ERR_FATAL( "Pwrdb DALSys Event creation failed",0,0,0 );

  pwrdb_dal_events[0] = pwrdb_task_cmd_event;

  #ifdef FEATURE_PWRDB_MPSS
  pwrdb_check_fs_for_script( PWRDB_DEFAULT_SCRIPT_FILENAME );
  #endif /* #ifdef FEATURE_PWRDB_MPSS */

  /* Main task loop for power debug */
  for (;;)
  {
    if(DAL_SUCCESS != DALSYS_EventMultipleWait( pwrdb_dal_events,
                                                sizeof(pwrdb_dal_events)/sizeof(DALSYSEventHandle),
                                                DALSYS_EVENT_TIMEOUT_INFINITE, &pwrdb_dal_sig ))
    {
      ERR_FATAL( "Pwrdb DalSys WAit Error",0,0,0 );
    }

    /* Check for commands and process if present */
    if ( pwrdb_dal_sig == PWRDB_TASK_CMD_SIG )
    {
      pwrdb_task_queue_type *c_ptr;
      PWRDB_MSG_H0("Processing commands in task.");
      c_ptr = (pwrdb_task_queue_type *)q_get( &pwrdb_task_cmd_queue );
      while ( c_ptr != NULL )
      {
        /* take the item off the queue, process it and put it on the
           free queue */
        pwrdb_task_cmd_process( c_ptr->cmd, c_ptr->param1, c_ptr->param2 );

        (void) q_put( &pwrdb_task_cmd_free_queue, &(c_ptr->link) );

        c_ptr = (pwrdb_task_queue_type *)q_get( &pwrdb_task_cmd_queue );
      }
      PWRDB_MSG_H0("Done processing commmands in task");
      
      if( DAL_SUCCESS != DALSYS_EventCtrl( pwrdb_task_cmd_event, DALSYS_EVENT_CTRL_RESET ))
        ERR_FATAL( "Pwrdb DalSys Event Ctrl Reset Error",0,0,0 );
      }
  } /* for (;;) */
} /* pwrdb_task */



