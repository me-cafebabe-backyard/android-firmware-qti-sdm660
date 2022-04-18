#ifndef OS_TYPE_H
#define OS_TYPE_H

/*===========================================================================

                      G-Link OS Specific types/functions


 Copyright (c) 2014-2015 by QUALCOMM Technologies, Incorporated.  All Rights
 Reserved.
===========================================================================*/


/*===========================================================================

                           EDIT HISTORY FOR FILE

$Header: //components/rel/rpm.bf/1.8/core/mproc/glink/os/inc/glink_os_type.h#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
03/20/15   an      Disable logging for memory constrained environment
03/03/15   rs      Redefine ASSERT for RPM build environment
01/23/15   bc      Update isr api to remove rpm featurization
12/26/14   bc      Update os_isr_cb_fn accordingly for RPM
12/09/14   bc      include RPM file for registering ISR
11/21/14   an      Branch for RPM DAL adaptation
04/18/14   bm      Initial version
===========================================================================*/


/*===========================================================================

                        INCLUDE FILES

===========================================================================*/
#include "comdef.h"
#include "string.h"
#include "err.h"
#include "amssassert.h"
#include "DALFramework.h"
#include "DDIIPCInt.h"
#include "ULogFront.h"
#include "cortex-m3.h"

/*===========================================================================
                        MACRO DEFINITIONS
===========================================================================*/

#define OS_LOG_INIT( ) glink_os_log_init()

#ifdef ASSERT
#undef ASSERT
#define ASSERT assert
#endif

#define OS_EVENT_LOG_LEVEL_NONE    0
#define OS_EVENT_LOG_LEVEL_FATAL   1
#define OS_EVENT_LOG_LEVEL_ERROR   2
#define OS_EVENT_LOG_LEVEL_WARNING 3
#define OS_EVENT_LOG_LEVEL_INFO    4
#define OS_EVENT_LOG_LEVEL_TRACE   5


#define OS_EVENT_LOG_LEVEL OS_EVENT_LOG_LEVEL_NONE


/** Tracing macro */
#if OS_EVENT_LOG_LEVEL >= OS_EVENT_LOG_LEVEL_TRACE
#define OS_EVENT_TRACE( args... ) \
  if( os_log_handle ) \
  { \
    ULogFront_RealTimePrintf( os_log_handle, ##args ); \
  }
#else
#define OS_EVENT_TRACE( args... )
#endif

/** Generic debug message */
#if OS_EVENT_LOG_LEVEL >= OS_EVENT_LOG_LEVEL_INFO
#define OS_LOG_MSG( args... ) \
  if( os_log_handle ) \
  { \
    ULogFront_RealTimePrintf( os_log_handle, ##args ); \
  }
#else
#define OS_LOG_MSG( args... )
#endif

/** Generic error message print */
#if OS_EVENT_LOG_LEVEL >= OS_EVENT_LOG_LEVEL_ERROR
#define OS_LOG_ERROR( args... ) \
  if( os_log_handle ) \
  { \
    ULogFront_RealTimePrintf( os_log_handle, ##args ); \
  }
#else
#define OS_LOG_ERROR( args... )
#endif

#if OS_EVENT_LOG_LEVEL >= OS_EVENT_LOG_LEVEL_FATAL
#define OS_LOG_ERROR_FATAL( args... ) \
  do \
  { \
    if( os_log_handle ) \
    { \
      ULogFront_RealTimePrintf( os_log_handle, ##args ); \
    } \
    ASSERT( FALSE ); \
  } \
  while( 0 )
#else
#define OS_LOG_ERROR_FATAL( args... ) \
  do \
  { \
    ASSERT( FALSE ); \
  } \
  while( 0 )
#endif


/*===========================================================================
                        TYPE DEFINITIONS
===========================================================================*/
typedef void* os_cs_type;

typedef void ( *os_timer_cb_fn )( void *cb_data );

typedef void* os_timer;

typedef struct 
{
  void* placeholder;
}os_event_type;

typedef void ( *os_isr_cb_fn )( void * );

typedef struct os_ipc_intr_struct
{
  DalIPCIntProcessorType  processor;
  DalIPCIntInterruptType  irq_out;
} os_ipc_intr_type;

typedef long long os_timetick_type;

/*===========================================================================
                    EXTERNAL FUNCTION DEFINITIONS
===========================================================================*/

/*===========================================================================
                    EXTERNAL VARIABLE DEFINITIONS
===========================================================================*/

extern ULogHandle os_log_handle;

#endif /* OS_TYPE_H */
