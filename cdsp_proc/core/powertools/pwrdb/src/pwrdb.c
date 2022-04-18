/*===========================================================================

                            P W R   D E B U G 
                      
DESCRIPTION

GENERAL DESCRIPTION

  This file contains the power debugger code.  This includes the DIAG 
  interface and the power debugger engine.
  
EXTERNALIZED FUNCTIONS
  None
  
REGIONAL FUNCTIONS
  pwrdb_check_fs_for_script
  pwrdb_configure_DAL_I2C
  pwrdb_event_is_active
  pwrdb_i2c_fill_config_struct
  pwrdb_init
  pwrdb_open_DAL_TLMM
  pwrdb_open_DAL_SBI
  pwrdb_setup_event
  pwrdb_state_change
  pwrdb_task_cmd_send
  pwrdb_task_cmd_process
  pwrdb_timer_id_is_ok

INITIALIZATION AND SEQUENCING REQUIREMENTS

  Must call pwrdbdiag_init() before commands can be processed by power 
  debugger.
  

  Copyright (c) 2014 by QUALCOMM Technologies, Incorporated.  All Rights Reserved.
  
===========================================================================*/

/*===========================================================================

                      EDIT HISTORY FOR FILE

$Header: //components/rel/core.qdsp6/1.0.c2/powertools/pwrdb/src/pwrdb.c#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
12/02/14   dy      Add Downsampling command for SystemDB
09/29/14   dy      Add RPM Dump and Err Fatal commands for SystemDB
09/03/13   rs      Convert pwrdb_commands and pwrdblog from static array to 
                   dynamic buffer to save memory. 
01/19/10   hw      Add FEATURE_LEGACY_SLEEP_EVENT for sleep event notification.
09/27/10   ab      Added Extern function to Remove compiler warnings
09/24/10   hluo    Obsolete the sbi_write and sbi_read
08/01/10   jl      Fixed PWRDB_GPIO_OUT_VAL macro.
07/01/10   ab      Removed call to I2C_init() function and modified code to
                   allow i/p slave addr of I2C device to be given as it is
05/17/10   jl      Added CLK_BUSY_WAIT and NPA_QUERY_BY_NAME commands.
                   Corrected pwrdb_register_sleep to vote "TRUE" for sleep.
03/30/10   jl      Added sleep event notification.
03/05/10   jl      Added NPA support.
01/12/10   jl      Added extended sleep voting function.
01/08/10   jl      Fixed compiling warnings. Removed legacy hw_msm_id() and 
                   replaced with DalChipInfo_GetChipId().
12/17/09   gw      Increased size of command and log arrays from 1000 to 5000
                   items.
12/16/09   gw      Fixed featurizaton for single processor builds.
11/25/09   ab      Added DALI2C read and DALI2C write commands
10/19/09   jl      Added DSLSBI read and DALSBI write commands
10/01/09   ab      Adding Physical address, numbering log feature
09/13/09   jl      Added support for clkrgm device manager request. Added set 
                   minimum speed command and set op level command. 
                   Modify sleep vote command to register when unpacking 
                   command rather than when processing command. Added sleep 
                   register helper function.
                   Align variables.
08/10/09   jl/ck   Added support for apps processor, and sleep vote command.
                   Update the start timer command.
07/24/09   sg      Added Peek32, Poke32 range and string features.
05/01/09   gw      Refactoring based on code review comments.
04/10/09   gw      Added use of clkregime and TLMM APIs.
                   Added debug messaging.
08/07/08   ts      Created service

===========================================================================*/

/* <EJECT> */
/*==========================================================================

                     INCLUDE FILES FOR MODULE

==========================================================================*/
/* Include files are listed in alphabetical order. pwrdb includes are listed before includes
   from other modules. */
#include "pwrdb.h"
#include "pwrdbi.h"

#include "busywait.h"
#include "ClockLog.h"
#include "DalDevice.h" 
#include "DALSys.h"
#include "DALStdDef.h"
#include <DDIChipInfo.h>
#include "DDIClock.h"
#include "DDITlmm.h"
#include "diag.h"
#include "diagcmd.h"
#include "diagpkt.h"

#ifdef PWRDB_PRO
#ifdef FEATURE_PWRDB_MPSS
#include "fs_public.h"
#include "fs_sys_types.h"
#endif  /* #ifdef FEATURE_PWRDB_MPSS */
#endif /* #ifdef FEATURE_PWRDB_PRO */

#include "qurt.h"
#include <stdlib.h>
#include <string.h>
#include "timer.h"
#include "timetick.h"

#ifdef FEATURE_GNSS_RELOCATABLE_MODEM
  #ifdef FEATURE_BLAST 
    #include "qmemory.h"
  #else
  /* For the virt to phys.  TODO: move to cgps_api.h later */
   #include <iguana/memsection.h>
  #endif
#endif

/* Include for QDSS */
#include "tracer.h"
#include "pwrdb_tracer_event_ids.h"
#include "ULogFront.h"

#ifdef PWRDB_PRO
#include "npa_resource.h"
#endif /* #ifdef PWRDB_PRO */

#include "CoreString.h"
/* <EJECT> */
/*===========================================================================

            DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains local definitions for constants, macros, types,
variables and other items needed by this module.

===========================================================================*/
// Select a specific processor at compile time.
#ifdef IMAGE_APPS_PROC
#define  PWRDB_DIAG_PKT_CPU_ID  PWRDB_DIAG_PKT_APPS_ID
#elif  FEATURE_PWRDB_MPSS
#define  PWRDB_DIAG_PKT_CPU_ID  PWRDB_DIAG_PKT_MODEM_ID
#elif  FEATURE_PWRDB_ADSP
#define  PWRDB_DIAG_PKT_CPU_ID  PWRDB_DIAG_PKT_ADSP_ID
#elif FEATURE_PWRDB_WCNSS
#define   PWRDB_DIAG_PKT_CPU_ID  PWRDB_DIAG_PKT_WCNSS_ID
#elif  FEATURE_PWRDB_SLPI
#define  PWRDB_DIAG_PKT_CPU_ID  PWRDB_DIAG_PKT_SLPI_ID
#endif

/*===========================================================================

                      INTERNAL FUNCTION PROTOTYPES

===========================================================================*/
PACKED void *pwrdb_process_reset_req(PACKED void *req_pkt_ptr, uint16 pkt_len);
PACKED void *pwrdb_process_version_req(PACKED void *req_pkt_ptr, uint16 pkt_len);
PACKED void *pwrdb_process_script_req(PACKED void *req_pkt_ptr, uint16 pkt_len);
PACKED void *pwrdb_process_log_req(PACKED void *req_pkt_ptr, uint16 pkt_len);
PACKED void *pwrdb_process_run_req(PACKED void *req_pkt_ptr, uint16 pkt_len);
PACKED void *pwrdb_process_stop_req(PACKED void *req_pkt_ptr, uint16 pkt_len);
PACKED void *pwrdb_process_test_event_req(PACKED void *req_pkt_ptr, uint16 pkt_len);
#ifdef PWRDB_PRO
#ifdef FEATURE_PWRDB_MPSS
PACKED void *pwrdb_process_log_to_fs_req(PACKED void *req_pkt_ptr, uint16 pkt_len);
PACKED void *pwrdb_process_file_read_req( PACKED void *req_pkt_ptr, uint16 pkt_len );
#endif
#endif
PACKED void *pwrdb_process_cmd_clk_output_gpio( PACKED void *req_pkt_ptr, uint16 pkt_len );
PACKED void *pwrdb_process_change_log_format_req( PACKED void *req_pkt_ptr, uint16 pkt_len );

static void pwrdb_process_event( uint32 source, uint32 id );


/*===========================================================================

                      EXTERNAL FUNCTION PROTOTYPES

===========================================================================*/
//ctk--old--> extern uintptr_t memsection_virt_to_phys(uintptr_t vaddr, size_t *size);

/*===========================================================================
                               MACROS

===========================================================================*/

/* The following macros are for unpacking the GPIO configuration. 
   Hopefully these are temporary and the TLMM driver will eventually
   implement them.
 */
#define PWRDB_GPIO_GET_GPIO_NUMBER(config) ((0x20000000&(config))?(((config)&0x3FF0)>>4):(((config)&0xFF00)>>8))        
#define PWRDB_GPIO_GET_FUNC(config)        ((config) & 0xF)
#define PWRDB_GPIO_GET_DIR(config)         ((0x20000000&(config))?(((config)&0x4000)>>14):(((config)&0x10000)>>16))
#define PWRDB_GPIO_GET_PULL(config)        ((0x20000000&(config))?(((config)&0x18000)>>15):(((config)&0x60000)>>17))
#define PWRDB_GPIO_GET_DRIVE(config)       ((0x20000000&(config))?(((config)&0x1E0000)>>17):(((config)&0x380000)>>19))
#define PWRDB_GPIO_OUT_VAL(config)         ((0x20000000&(config))?(((config)&0x1E00000)>>0x15):(((config)&0xF0)>>4))

#define PWRDB_TLMM_GPIO_OFFSET             0x00010000
#define PWRDB_TLMM_BASE_ADDR               (TLMM_BASE_PHYS+PWRDB_TLMM_GPIO_OFFSET)
#define PWRDB_GPIO_CFGn_ADDR(n)            ((PWRDB_TLMM_BASE_ADDR) + 0x1000 * (n))
#define PWRDB_GPIO_IN_OUTn_ADDR(n)         ((PWRDB_TLMM_BASE_ADDR)+ 0x4 + 0x1000 * (n))


/* Following Macro is for preparing the GPIO config based
   on the parameters passed */
#define PWRDB_GPIO_CFG_OUT( gpio, func, dir, pull, drv ) \
          (((pull) & 0x3)     |  \
          ((func) & 0xF) << 2 |  \
          ((drv)& 0x7)   << 6 |  \
          ((dir)  & 0x1) << 9 )

#define PWRDB_TLMM_BYPASS_VAL              (0xff)

#define TIME_SYNC_SIG 0x200 /* Change this to a signal that is not used on the task */

/*===========================================================================

                    TYPES

===========================================================================*/
typedef enum {
  PWRDB_LOG_OFF = 0,
  PWRDB_LOG_ON  = 1,
} pwrdb_log_state_type;

typedef struct {
  DALDEVICEID       daldevice_id;
  DalDeviceHandle  *hDaldev;
  boolean           dal_opened; 
} pwrdb_Daldevice_type;

typedef struct
{ 
  /* Resource used by the client */
  const char        *npa_resource_name;   
  /* Synchronous client handle */
  npa_client_handle sync_handle;
  /* Asynchronous client handle */
  npa_client_handle async_handle;
   /* Name of the client used within NPA */
  const char        *npa_client_name;
} pwrdb_npa_resource_type;

typedef enum {
  ASYNC = 0,
  SYNC  = 1,
} pwrdb_npa_client_sync_type;

/* For PWRDB NPA node. Internal test only */
typedef struct
{
  npa_client_handle         handle[2];
} pwrdb_npa_test_client_type;

typedef struct
{
  npa_node_definition       node;
  npa_resource_definition   rsrc[2];
} pwrdb_npa_test_node_type;

/* End PWRDB NPA node.*/
/*===========================================================================

                     CONSTANTS

===========================================================================*/
static const diagpkt_user_table_entry_type pwrdb_diag_tbl[] =
{
  { (PWRDB_DIAG_PKT_RESET | PWRDB_DIAG_PKT_CPU_ID),      (PWRDB_DIAG_PKT_RESET | PWRDB_DIAG_PKT_CPU_ID),      pwrdb_process_reset_req },
  { (PWRDB_DIAG_PKT_VER | PWRDB_DIAG_PKT_CPU_ID),        (PWRDB_DIAG_PKT_VER | PWRDB_DIAG_PKT_CPU_ID),        pwrdb_process_version_req },
  { (PWRDB_DIAG_PKT_SCRIPT | PWRDB_DIAG_PKT_CPU_ID),     (PWRDB_DIAG_PKT_SCRIPT | PWRDB_DIAG_PKT_CPU_ID),     pwrdb_process_script_req },
  { (PWRDB_DIAG_PKT_LOG | PWRDB_DIAG_PKT_CPU_ID),        (PWRDB_DIAG_PKT_LOG | PWRDB_DIAG_PKT_CPU_ID),        pwrdb_process_log_req },
  { (PWRDB_DIAG_PKT_RUN | PWRDB_DIAG_PKT_CPU_ID),        (PWRDB_DIAG_PKT_RUN | PWRDB_DIAG_PKT_CPU_ID),        pwrdb_process_run_req },
  { (PWRDB_DIAG_PKT_STOP | PWRDB_DIAG_PKT_CPU_ID),       (PWRDB_DIAG_PKT_STOP | PWRDB_DIAG_PKT_CPU_ID),       pwrdb_process_stop_req },
  { (PWRDB_DIAG_PKT_TEST_EVENT | PWRDB_DIAG_PKT_CPU_ID), (PWRDB_DIAG_PKT_TEST_EVENT | PWRDB_DIAG_PKT_CPU_ID), pwrdb_process_test_event_req },
  { (PWRDB_DIAG_PKT_CHANGE_LOG_FORMAT | PWRDB_DIAG_PKT_CPU_ID), (PWRDB_DIAG_PKT_CHANGE_LOG_FORMAT | PWRDB_DIAG_PKT_CPU_ID), pwrdb_process_change_log_format_req },  
#ifdef PWRDB_PRO
  { (PWRDB_DIAG_PKT_CLK_OUTPUT_GPIO | PWRDB_DIAG_PKT_CPU_ID), (PWRDB_DIAG_PKT_CLK_OUTPUT_GPIO | PWRDB_DIAG_PKT_CPU_ID), pwrdb_process_cmd_clk_output_gpio }
  #ifdef FEATURE_PWRDB_MPSS 
  { (PWRDB_DIAG_PKT_READ_FILE  | PWRDB_DIAG_PKT_CPU_ID), (PWRDB_DIAG_PKT_READ_FILE  | PWRDB_DIAG_PKT_CPU_ID), pwrdb_process_file_read_req  },
  { (PWRDB_DIAG_PKT_LOG_TO_FS | PWRDB_DIAG_PKT_CPU_ID),  (PWRDB_DIAG_PKT_LOG_TO_FS | PWRDB_DIAG_PKT_CPU_ID),  pwrdb_process_log_to_fs_req },
  #endif
#endif
}; 

/* Number of events that can be stored. */
#define PWRDB_NUM_EVENTS                20

/* Max number of script commands that can be stored (total for all events). */
#define PWRDB_NUM_SCRIPT_COMMANDS       1000

/* Length of buffer to use for interacting with file system. */
#define PWRDB_FS_RW_BUF_SIZE            1024

/* Number of diag events that can be used at the same time. */
#define PWRDB_NUM_DIAG_EVENTS           20

/* Number of sleep events that can be used at the same time. */
#ifdef FEATURE_LEGACY_SLEEP_EVENT
#define PWRDB_NUM_SLEEP_EVENTS          SLEEP_EVENT_COUNT
#endif /* FEATURE_LEGACY_SLEEP_EVENT */

/* Number of timers available to access from scripts. */
#define PWRDB_NUM_TIMERS                10

#define PWRDB_NO_EVENT                  PWRDB_NUM_EVENTS

/* Number of elements in ram log buffer */
#define PWRDB_DEFAULT_LOG_SIZE          1000

/* This number set the size of the pwrdb npa resource table, it can be increased if needed */
#define PWRDB_NUM_NPA_RESOURCE          40

static char PWRDB_NO_ERROR_STR[] = "No error";

/* String corresponding to the "official" pwrdb client name inside NPA. */
static const char *PWRDB_NPA_CLIENT_NAME = "/core/powertool/pwrdb";

static const char *PWRDB_NPA_NO_RESOURCE = "No resource";

#define PWRDB_MAX_CMD_SEQ_NUMBER        0xFF

#define PWRDB_INITIAL_LOG_PKT_SIZE      500

/*===========================================================================

                      VARIABLES

===========================================================================*/
pwrdb_state_type                 pwrdb_state;
char                            *pwrdb_error_str = PWRDB_NO_ERROR_STR;

pwrdb_malloc_item_ll_type       *pwrdb_malloc_array;
pwrdb_malloc_item_ll_type       *pwrdb_malloc_array_end;

pwrdb_event_ll_type             *pwrdb_events;

static uint32                    pwrdb_command_count;

static pwrdb_log_type           *pwrdb_log = NULL;
static uint32                    pwrdb_log_write_ix;
static boolean                   pwrdb_log_wr_wrap;
static uint32                    pwrdb_log_size = PWRDB_DEFAULT_LOG_SIZE;
static pwrdb_log_state_type      pwrdb_log_state;

static qmutex_t                  pwrdb_mutex;

#ifdef PWRDB_PRO
#ifdef FEATURE_PWRDB_MPSS
/* Buffer for interacting with file system. */
static uint8                     pwrdb_fs_rw_buf[PWRDB_FS_RW_BUF_SIZE];
#endif /* #ifdef FEATURE_PWRDB_MPSS */
#endif

static uint32                    pwrdb_dropped_event_count;

/* Always on timers */
static timer_type                pwrdb_timers[PWRDB_NUM_TIMERS];
static timer_group_type          pwrdb_always_on_timer_group;
/* Trigger timer for log time sync */

#ifdef PWRDB_PRO
/*QURT to ATS timer*/
static timer_type                pwrdb_trigger_timer;
#endif 

/* Lazy timers */
static timer_type                pwrdb_timers_lazy[PWRDB_NUM_TIMERS];

static boolean                   TLMM_opened = FALSE;
static DalDeviceHandle           *hTlmm;
static DalDeviceHandle           *pwrdb_dal_Clk_handle = NULL;

static unsigned int              pwrdb_diag_events[PWRDB_NUM_DIAG_EVENTS];
static uint32                    pwrdb_diag_event_count=0;

static pwrdb_npa_resource_type   pwrdb_npa_resource[PWRDB_NUM_NPA_RESOURCE];
static boolean                   pwrdb_npa_resource_initialized = FALSE;

/* For PWRDB NPA node. Internal test only */
#ifdef PWRDB_PRO
static pwrdb_npa_test_client_type pwrdb_test_client;
static pwrdb_npa_test_node_type   pwrdb_test_node;
static uint32                     pwrdb_test_max = 0;

/* Array containing the sleep LPR resource,needed for the LPR implementation */
static const char *pwrdb_lpr_init_resources[] = 
{
  "/sleep/lpr"
};
/* Pwrdb Npa String */
char npa_str[64];
#endif /* #ifdef PWRDB_PRO */

static pwrdb_log_format_type      pwrdb_log_format = PWRDB_LOG_TO_RAM;

static pwrdb_log_function_type    pwrdb_log_function_table[] =
{
  pwrdb_log_to_ulog,
  pwrdb_log_Ulog_to_QDSS,
  pwrdb_log_to_QDSS_STM,
  pwrdb_log_to_ram
};

static pwrdb_log_function_type pwrdb_log_function;

qurt_anysignal_t pwrdb_trigger_timer_sig;

static uint32 pwrdb_cmd_seq_num = PWRDB_MAX_CMD_SEQ_NUMBER;

/* EJECT */
/*===========================================================================

                      INTERNAL FUNCTION DEFINITIONS

===========================================================================*/

/*===========================================================================

FUNCTION PWRDB_GET_TIMESTAMP

DESCRIPTION
  Returns a time stamp to use in logs. Implementation at this point is to
  read timetick - a free runnning 32bit counter driven by the sleep clock.
  
DEPENDENCIES
  None

RETURN VALUE
  time stamp
===========================================================================*/
// Stub out until anyone need to use it to avoid compiling error
/* 
static __inline uint32 pwrdb_get_timestamp( void )
{
  return (uint32) timetick_get_safe();
}
*/
/*===========================================================================

FUNCTION PWRDB_NEXT_LOG_ITEM

DESCRIPTION
 Returns a pointer to the next log item. An item can be added to the log by
 calling this function and then filling in the fields of the log item
 through the pointer returned by this function. This function takes care of
 filling in the timestamp in the log item.
  
DEPENDENCIES
  None

RETURN VALUE
  pointer to next log item
  NULL if error (e.g. logging off, or array not allocated)
 
===========================================================================*/
static pwrdb_log_type *pwrdb_next_log_item( void )
{
  pwrdb_log_type *li_ptr;

  if ( (pwrdb_log_state == PWRDB_LOG_ON) && (pwrdb_log != NULL) )
  {
    li_ptr = &(pwrdb_log[pwrdb_log_write_ix]);
    if (++pwrdb_log_write_ix >= pwrdb_log_size)
    {
      pwrdb_log_write_ix = 0;
      pwrdb_log_wr_wrap  = TRUE;
    }
  }
  else
  {
    li_ptr = NULL;
  }

  return li_ptr;
}

/*===========================================================================

FUNCTION PWRDB_ADDTO_MALLOC_ARRAY

DESCRIPTION
 This function should be called whenever a new malloc memory allocation is
 done in pwrdb. The address is logged into a array of addresses.
 In pwrdb_reset all these addresses are freed.
  
DEPENDENCIES
  None

RETURN VALUE
  None
===========================================================================*/
void pwrdb_addto_malloc_array(void *arrayaddr)
{
  pwrdb_malloc_item_ll_type *new_item;
  DALResult res;

  res = DALSYS_Malloc(sizeof(pwrdb_malloc_item_ll_type), (void *)&new_item);

  if (res == DAL_SUCCESS)
  {
    new_item->addr = arrayaddr;
    new_item->next = NULL;

    if (pwrdb_malloc_array == NULL)
    {
      pwrdb_malloc_array = new_item;
    }
    else
    {
      pwrdb_malloc_array_end->next = new_item;
    }
    pwrdb_malloc_array_end = new_item;
  }
  else
  {
    // potential memory leak
    PWRDB_MSG_H0("Can't allocate memory for malloc array. Potential memory leak.");
  }
}

/*===========================================================================

FUNCTION PWRDB_FREE_MALLOC_ARRAY

DESCRIPTION
  Release all the memory referenced in the malloc array.
  
DEPENDENCIES
  None

RETURN VALUE
  None
===========================================================================*/
void pwrdb_free_malloc_array( void )
{
  pwrdb_malloc_item_ll_type *i_ptr = pwrdb_malloc_array;
  pwrdb_malloc_item_ll_type *n_ptr;

  while (i_ptr != NULL)
  {
    if (i_ptr->next != NULL) { DALSYS_Free(i_ptr->addr); }
    n_ptr = i_ptr->next;
    DALSYS_Free(i_ptr);
    i_ptr = n_ptr;
  }

  pwrdb_malloc_array     = NULL;
  pwrdb_malloc_array_end = NULL;
}

/*===========================================================================

FUNCTION PWRDB_LAZY_TIMER_CB

DESCRIPTION
  Callback function to pass to timer services when requesting a timer. Timer
  will not wake the modem or apps processor from sleep.

DEPENDENCIES
  None

===========================================================================*/
static void pwrdb_lazy_timer_cb( int32 time_ms, timer_cb_data_type id )
{
  pwrdb_process_event( PWRDB_EVT_SRC_PWRDB_TIMER, (uint32)id  );
}

/*===========================================================================

FUNCTION PWRDB_TIMER_CB

DESCRIPTION
  Callback function to pass to timer services when requesting a timer. Timer
  interrupt will wake the modem or apps processor from sleep to service this 
  timer.

DEPENDENCIES
  None

===========================================================================*/
static void pwrdb_timer_cb( timer_cb_data_type id )
{
  pwrdb_process_event( PWRDB_EVT_SRC_PWRDB_TIMER, (uint32)id  );
}

/*===========================================================================
FUNCTION PWRDB_LOG_MESSAGE

DESCRIPTION
Logs a message into pwrdb_log array which will be sent to the user. Type field indicates the message type. 
  
DEPENDENCIES
  None

RETURN VALUE
  None
===========================================================================*/
void  pwrdb_log_message(pwrdb_message_type type, char *message)
{
  uint16 len = 0;
  uint16 num=0;
  pwrdb_log_type *li_ptr;
  char *messageptr = NULL;
  DALResult res;

  len = 0;
  while(message[len++]);

  /* '1' is extra for adding '\0' at last of C string */
  res = DALSYS_Malloc((len+1)*sizeof(char), (void *)&messageptr);
  
  if(res != DAL_SUCCESS)
  {
       PWRDB_MSG_H0("Malloc Failed, returning from STRING Command execution");
  }
  else
  {
       /* Adding this address to malloc array, which would be freed uo during pwrdb_reset */
       pwrdb_addto_malloc_array(messageptr);
       for(num=0; num<(len+1); num++)
       {
        /* Reversing the input string to test how strings are passed */
        *(messageptr + num) = *(message+num);
       }
  }
  
    /* put the result into the log */
  li_ptr = pwrdb_next_log_item();
  if ( li_ptr )
  {
    li_ptr->log_id              = PWRDB_LOG_STRING;
    li_ptr->data.strng.str_len  = len;
    li_ptr->data.strng.str_type = (uint16)type;
    li_ptr->data.strng.str      = messageptr;
  }

}

/*===========================================================================
FUNCTION PWRDB_LOG_MSG_3

DESCRIPTION
Logs a message into pwrdb_log array which will be sent to the user. Type field indicates the message type. 
Any required data can also be sent through this function to the user. At max 3 data values can be sent.

If not going to send any data values, this function can be called with 3 zeros as other arguments
  
DEPENDENCIES
  None

RETURN VALUE
  None
===========================================================================*/
void  pwrdb_log_msg_3(pwrdb_message_type type, char *message, 
                      uint32 value1, uint32 value2, uint32 value3)
{
  uint16 len = 0;
  uint16 num=0;
  pwrdb_log_type *li_ptr;
  char *messageptr = NULL;
  DALResult res;

  len = 0;
  while(message[len++]);

  /* '1' is extra for adding '\0' at last of C string */
  res = DALSYS_Malloc((len+1)*sizeof(char), (void *)&messageptr);
  
  if(res != DAL_SUCCESS)
  {
       PWRDB_MSG_H0("Malloc Failed, returning from STRING Command execution");
  }
  else
  {
       /* Adding this address to malloc array, which would be freed uo during pwrdb_reset */
       pwrdb_addto_malloc_array(messageptr);
       for(num=0; num<(len+1); num++)
       {
        /* Reversing the input string to test how strings are passed */
        *(messageptr + num) = *(message+num);
       }
  }
  
    /* put the result into the log */
  li_ptr = pwrdb_next_log_item();
  if ( li_ptr )
  {
    li_ptr->log_id                    = PWRDB_LOG_DATA3_STRING;
    li_ptr->data.data3_strng.str_len  = len;
    li_ptr->data.data3_strng.str_type = (uint32)type;
    li_ptr->data.data3_strng.value1   = value1;
    li_ptr->data.data3_strng.value2   = value2;
    li_ptr->data.data3_strng.value3   = value3;
    li_ptr->data.data3_strng.str      = messageptr;
  }
}

/*===========================================================================

FUNCTION PWRDB_DIAG_EVENT_LISTENER

DESCRIPTION
  Callback function to use when registering for diag events.
  
DEPENDENCIES
  None

===========================================================================*/
static void pwrdb_diag_event_listener( uint32 seq_num, 
                                       const diag_event_type *event, 
                                       void *param )
{
  pwrdb_process_event( PWRDB_EVT_SRC_DIAG, (uint32)(event->event_id) );
}

/*===========================================================================

FUNCTION PWRDB_SETUP_DIAG_EVENT

DESCRIPTION
  Register with diag to respond to a particular diag event packet.

  This function keeps a record of the requested events so that we can
  unregister later by calling pwrdb_clear_diag_events().
  
DEPENDENCIES
  None

RETURN VALUE
  TRUE  - success
  FALSE - failure 
  
===========================================================================*/
static boolean pwrdb_setup_diag_event( unsigned int event_id)
{
  boolean ok = FALSE;
  int     i;

  if ( pwrdb_diag_event_count >= PWRDB_NUM_DIAG_EVENTS )
  {
    /* No room for more events */
    return FALSE;
  }

  /* check if event already registered */
  for (i=0; i<pwrdb_diag_event_count; i++)
  {
    if (pwrdb_diag_events[i] == event_id)
    {
      ok = TRUE;
      break; /* for */
    }
  }

  /* Check there is enough room for event.*/
  if (!ok)
  {
    /* Add event in local list in case we neeed to remove
       its listener later. */
    pwrdb_diag_events[pwrdb_diag_event_count] = event_id;
    pwrdb_diag_event_count++;

    /* register the event with diag */
    ok = diag_add_event_listener( event_id ,
                                  pwrdb_diag_event_listener,
                                  0 );
  }

  return ok;
}

/*===========================================================================

FUNCTION PWRDB_CLEAR_DIAG_EVENTS

DESCRIPTION
  Clear the events that we have registered with diag.
  
DEPENDENCIES
  None

===========================================================================*/
static void pwrdb_clear_diag_events( void )
{
  int32 i;

  PWRDB_ASSERT( pwrdb_diag_event_count < PWRDB_NUM_DIAG_EVENTS );

  for (i=0; i<pwrdb_diag_event_count; i++)
  {
    (void) diag_remove_event_listener ( pwrdb_diag_events[i],
                                        pwrdb_diag_event_listener,
                                        0 );
  }

  pwrdb_diag_event_count = 0;
}

/*===========================================================================

FUNCTION PWRDB_INIT_RAM_LOG

DESCRIPTION
  Prepare the RAM log for use, allocating a memoory buffer if necessary.
  
DEPENDENCIES
  None

===========================================================================*/
static void pwrdb_init_ram_log( void )
{
  DALResult res;

  pwrdb_log_write_ix = 0;
  pwrdb_log_wr_wrap  = FALSE;

  if (pwrdb_log == NULL)
  {
      res = DALSYS_Malloc(pwrdb_log_size*sizeof(pwrdb_log_type), (void *)&pwrdb_log);

      if (res == DAL_SUCCESS)
      {
        memset(pwrdb_log, 0, pwrdb_log_size*sizeof(pwrdb_log_type));
      }
      else
      {
        pwrdb_log = NULL;
      }
  }

}

/*===========================================================================

FUNCTION pwrdb_free_events_commands
 
DESCRIPTION
  Free the Memory allocated for the pwrdb event and the commands
 
PARAMETERS
  None
  
RETURN VALUE
  None
 
Dependencies 
  None

SIDE EFFECTS 
  None
===========================================================================*/
static void pwrdb_free_events_commands( void )
{
  pwrdb_event_ll_type   *evt = pwrdb_events;
  pwrdb_event_ll_type   *next_evt;
  pwrdb_command_ll_type *cmd;
  pwrdb_command_ll_type *next_cmd;

  while (evt != NULL)
  {
    cmd = evt->pwrdb_cmds;
    while (cmd != NULL)
    {
      next_cmd = cmd->next;
      (void) DALSYS_Free(cmd);
      cmd = next_cmd;
    }

    next_evt = evt->next;
    (void) DALSYS_Free(evt);
    evt = next_evt;
  }

  pwrdb_events = NULL;
}

/*===========================================================================

FUNCTION PWRDB_RESET

DESCRIPTION
  Resets PWRDB by clearing events, script commands, logs etc.
  
DEPENDENCIES
  None

===========================================================================*/
static void pwrdb_reset( void )
{
  int i;

  PWRDB_MSG_H0("pwrdb_reset");

  // Events and commands 
  pwrdb_free_events_commands();

  // logs
  pwrdb_pack_log_items_reset();

  // NOTE: Allocation of memory for RAM log is deferred until
  // a diag packet is received to avoid using memory when 
  // PWRDB is not used.

  /* default logging to on */
  pwrdb_log_state = PWRDB_LOG_ON;

  pwrdb_dropped_event_count = 0;

  timer_group_set_deferrable(&pwrdb_always_on_timer_group, FALSE);
  /* timers */
  for (i=0; i<PWRDB_NUM_TIMERS; i++)
  {
    timer_def2( &(pwrdb_timers_lazy[i]), NULL );
    timer_def_osal( &(pwrdb_timers[i]),
               &pwrdb_always_on_timer_group,
               TIMER_FUNC1_CB_TYPE,
               &pwrdb_timer_cb,
               (time_osal_notify_data)i );
  }

  /* diag events */
  pwrdb_clear_diag_events();

  /* deregister all sleep events */
#ifdef FEATURE_LEGACY_SLEEP_EVENT
  pwrdb_clear_sleep_events();
#endif /* FEATURE_LEGACY_SLEEP_EVENT */

  /* Freeing the memory allocated through malloc's in pwrdb */
  pwrdb_free_malloc_array();
}

/*===========================================================================

FUNCTION PWRDB_STATE_CHECK_AND_CHANGE

DESCRIPTION
  Atomic check and change of the state.
  If current state == check_state then the state is changed to new state.
  
DEPENDENCIES
  None

RETURN VALUE
  TRUE  - The old state was equal to check_state and the state has been 
          changed to new_state.
  FALSE - The old state was not equal to check_state. It has not been
          changed.
  
===========================================================================*/
static boolean pwrdb_state_check_and_change( pwrdb_state_type check_state,
                                             pwrdb_state_type new_state )
{
  boolean rv = FALSE;
  /* take mutex */
  qmutex_lock( pwrdb_mutex );

  /* check state and change if matches */
  if ( pwrdb_state == check_state )
  {
    pwrdb_state = new_state;
    rv          = TRUE;
  }
  /* release mutex */
  qmutex_unlock( pwrdb_mutex );
  return rv;
}

/*===========================================================================

FUNCTION PWRDB_CHANGE_LOG_FORMAT

DESCRIPTION
  Change the sink for logs.
  
DEPENDENCIES
  None.

RETURN VALUE
  PWRDB_RES_OK    - log sink changed OK
  PWRDB_RES_ERROR - an error occurred, log sink is set to RAM

SIDE EFFECTS
  Logging sink may be changed
  
===========================================================================*/
static pwrdb_res_type pwrdb_change_log_format( pwrdb_log_format_type log_format )
{
  pwrdb_res_type res   = PWRDB_RES_ERROR;
  boolean log_path_set = FALSE;

  switch( log_format )
  {
  case PWRDB_LOG_TO_ULOG:
    if( pwrdb_ulog_init() == PWRDB_RES_OK ) 
    {
      log_path_set = TRUE; 
      res = PWRDB_RES_OK;
    }
    break;
  case PWRDB_LOG_TO_ULOG_OVER_QDSS:
  case PWRDB_LOG_TO_STM_LOG:
    if (pwrdb_qdss_init() == PWRDB_RES_OK)
    {
      log_path_set = TRUE; 
      res = PWRDB_RES_OK;
    }
    break;
  case PWRDB_LOG_TO_RAM:
    res = PWRDB_RES_OK;
    // fall through
  default:
    pwrdb_init_ram_log();
    pwrdb_log_function = pwrdb_log_to_ram;
    pwrdb_log_format   = PWRDB_LOG_TO_RAM;
    break;
  } // switch

  if( log_path_set == TRUE )
  {
    pwrdb_log_format   = log_format;
    pwrdb_log_function = pwrdb_log_function_table[ pwrdb_log_format ];    
  }

  return res;
}

/*===========================================================================

The functions below are helper functions to pwrdb_process_commands(). Each
function handles a specific command.

All the functions take one parameter that is a pointer to the command to
process.

===========================================================================*/

/*===========================================================================

FUNCTION pwrdb_program_clk_test_reg

DESCRIPTION
  This function is called to program the clock test register for the debug bus
  
DEPENDENCIES
  None.

RETURN VALUE
  None.

SIDE EFFECTS
  Depends on commands.
  
===========================================================================*/
static void pwrdb_program_clk_test_reg( uint32 reg_value)
{
  uint32 cfg = 0;
  pwrdb_open_DAL_TLMM();

  cfg = DAL_GPIO_CFG_OUT( 0x52,0x6,0x1,0x0,0x111,0x0 );
  (void) DalTlmm_ConfigGpio( hTlmm, 
                             cfg, 
                             DAL_TLMM_GPIO_ENABLE );
  out_dword( PWRDB_GCC_PLLTEST_PAD_CFG_ADDR,0x1300);
  
  out_dword( PWRDB_GCC_DEBUG_CLK_CTL_ADDR,reg_value ); 
}


/*===========================================================================

FUNCTION PWRDB_PROCESS_CMD_START_TIMER

===========================================================================*/
static void pwrdb_process_cmd_start_timer( pwrdb_cmd_type *c_ptr )
{
  PWRDB_ASSERT( c_ptr->params.start_timer.id < PWRDB_NUM_TIMERS );

  if(c_ptr->params.start_timer.always_on == 0)
  {/* Lazy timer*/
      timer_reg( &(pwrdb_timers_lazy[c_ptr->params.start_timer.id]),
                 pwrdb_lazy_timer_cb,
                 (timer_cb_data_type)c_ptr->params.start_timer.id,
                 (timetick_type)c_ptr->params.start_timer.time,
                 c_ptr->params.start_timer.repeat );
  }
  else
  {/* Out of band timers*/
      timer_set_64( &(pwrdb_timers[c_ptr->params.start_timer.id]),
                 (timetick_type)c_ptr->params.start_timer.time,
                 c_ptr->params.start_timer.repeat,
                 T_MSEC );
  }
}



/*===========================================================================

FUNCTION PWRDB_PROCESS_CMD_ENABLE_PRO

===========================================================================*/
static void pwrdb_process_cmd_enable_pro( pwrdb_cmd_type *c_ptr )
{
    (void) c_ptr;
    
    /* Stub out since we can't enable pro on ADSP */
}


/*===========================================================================

FUNCTION PWRDB_PROCESS_CMD_TLMM_GET_CURR_CONFIG

===========================================================================*/
static void pwrdb_process_cmd_tlmm_get_curr_config( pwrdb_cmd_type *c_ptr )
{
  uint32     cfg;
  DALGpioValueType GPIO_outstatus;
  DALGpioStatusType     status;
  DALResult       res;
  pwrdb_log_type *li_ptr;
  uint64     opt_cfg = 0;

  /* Need two calls to TLMM: 1st for config, 2nd to see if config
     is for active or sleep. */
  res = DalTlmm_GetCurrentConfig( hTlmm,
                                  c_ptr->params.tlmm_get_curr_config.gpio_number,
                                  &cfg );
  if (res == DAL_SUCCESS)
  {
    res = DalTlmm_GetPinStatus( hTlmm,
                                c_ptr->params.tlmm_get_curr_config.gpio_number,
                                &status );
  }
  if (res == DAL_SUCCESS)
  {
    res = DalTlmm_GetOutput( hTlmm,
                                c_ptr->params.tlmm_get_curr_config.gpio_number,
                                &GPIO_outstatus );
  }
  if (res == DAL_SUCCESS)
  {
    if( pwrdb_log_format != PWRDB_LOG_TO_RAM )
    {
      opt_cfg = (c_ptr->params.tlmm_get_curr_config.gpio_number)|(((status & 0xF )<<20)|(GPIO_outstatus & 0xF)<<16);
      opt_cfg = ((opt_cfg<<32)|cfg);
      pwrdb_log_function( PWRDB_CMD_TLMM_GET_CURR_CONFIG, opt_cfg );  
    }
    else
    {
      /* put the result into the log */
      li_ptr = pwrdb_next_log_item();
      if ( li_ptr )
      {
        li_ptr->log_id                                   = PWRDB_LOG_TLMM_GET_CURR_CONFIG;
        li_ptr->data.tlmm_get_curr_config.gpio_number    = c_ptr->params.tlmm_get_curr_config.gpio_number;
        li_ptr->data.tlmm_get_curr_config.function       = (uint8)(PWRDB_GPIO_GET_FUNC( cfg )); 
        li_ptr->data.tlmm_get_curr_config.direction      = (uint8)(PWRDB_GPIO_GET_DIR( cfg ));
        li_ptr->data.tlmm_get_curr_config.pull           = (uint8)(PWRDB_GPIO_GET_PULL( cfg ));
        li_ptr->data.tlmm_get_curr_config.drive_strength = (uint8)(PWRDB_GPIO_GET_DRIVE( cfg ));
        li_ptr->data.tlmm_get_curr_config.output_value   = (uint8)GPIO_outstatus;
        li_ptr->data.tlmm_get_curr_config.status         = (uint8)status;
      }
    }
  }
}

/*===========================================================================

FUNCTION PWRDB_PROCESS_CMD_TLMM_GET_INACT_CONFIG

===========================================================================*/
static void pwrdb_process_cmd_tlmm_get_inact_config( pwrdb_cmd_type *c_ptr )
{
  uint32          cfg;
  DALResult       res;
  uint8           gpio_status;
  pwrdb_log_type *li_ptr;

  res = DalTlmm_GetInactiveConfig( hTlmm,
                                   c_ptr->params.tlmm_get_inact_config.gpio_number,
                                   &cfg );
  /* put the result into the log  */
  if (res == DAL_SUCCESS)
  {
    if( pwrdb_log_format != PWRDB_LOG_TO_RAM )
    {
      pwrdb_log_function( PWRDB_CMD_TLMM_GET_CURR_CONFIG, cfg );  
    }
    else
    {
      li_ptr = pwrdb_next_log_item();
      if ( li_ptr )
      {
        li_ptr->log_id = PWRDB_LOG_TLMM_GET_INACT_CONFIG;
        gpio_status    = (uint8)(PWRDB_GPIO_GET_GPIO_NUMBER(cfg));
        if(gpio_status == 0xFF)
        {
          li_ptr->data.tlmm_get_inact_config.function     = gpio_status;
        }
        else
        {
          li_ptr->data.tlmm_get_inact_config.function     = (uint8)(PWRDB_GPIO_GET_FUNC( cfg ));
        }
        li_ptr->data.tlmm_get_inact_config.gpio_number    = c_ptr->params.tlmm_get_inact_config.gpio_number;
        li_ptr->data.tlmm_get_inact_config.direction      = (uint8)(PWRDB_GPIO_GET_DIR( cfg ));
        li_ptr->data.tlmm_get_inact_config.pull           = (uint8)(PWRDB_GPIO_GET_PULL( cfg ));
        li_ptr->data.tlmm_get_inact_config.drive_strength = (uint8)(PWRDB_GPIO_GET_DRIVE( cfg ));
        li_ptr->data.tlmm_get_inact_config.output_value   = (uint8)(DAL_GPIO_GET_OUTVAL( cfg ));
      }
    }
  }
}  



/*===========================================================================

FUNCTION PWRDB_PROCESS_CMD_TLMM_IS_LOCKED

===========================================================================*/
static void pwrdb_process_cmd_tlmm_is_locked( pwrdb_cmd_type *c_ptr )
{
  DALGpioLockType          locked;
  DALResult       res;
  pwrdb_log_type *li_ptr;
  
  res = DalTlmm_IsGpioLocked( hTlmm, 
                              c_ptr->params.tlmm_is_locked.gpio_number,
                              &locked ) ;
  
  if (res == DAL_SUCCESS)
  {
    /* put the result into the log */
    if( pwrdb_log_format != PWRDB_LOG_TO_RAM )
    {
      pwrdb_log_function( PWRDB_CMD_TLMM_GET_CURR_CONFIG, locked );  
    }
    else
    {
      li_ptr = pwrdb_next_log_item();
      if ( li_ptr )
      {
        li_ptr->log_id                          = PWRDB_LOG_TLMM_IS_LOCKED;
        li_ptr->data.tlmm_is_locked.gpio_number = c_ptr->params.tlmm_is_locked.gpio_number;
        li_ptr->data.tlmm_is_locked.locked      = (uint8)locked;
      }
    }
  } 
}


/*===========================================================================

FUNCTION PWRDB_PROCESS_CMD_CLK_GET_CLK_EN

===========================================================================*/
static void pwrdb_process_cmd_clk_get_clk_en( pwrdb_cmd_type *c_ptr )
{
  boolean         enable = FALSE;
  pwrdb_log_type *li_ptr = NULL;
  uint32 ClockID = 0;
    
  
  if( pwrdb_dal_Clk_handle == NULL )
  {
    if( DAL_SUCCESS != DAL_DeviceAttach(DALDEVICEID_CLOCK, &pwrdb_dal_Clk_handle) )
    {
      return;
    }
  }
  
  if( DAL_SUCCESS != DalClock_GetClockId( pwrdb_dal_Clk_handle, c_ptr->params.clk_get_clk_en.clk, &ClockID) )
  {
    return;
  }

  enable = DalClock_IsClockEnabled( pwrdb_dal_Clk_handle, ClockID  );

  /* put the result into the log */ 
  if( pwrdb_log_format != PWRDB_LOG_TO_RAM )
  {
    pwrdb_log_function( PWRDB_CMD_CLK_GET_CLK_EN, enable );
  }
  else
  {
    li_ptr = pwrdb_next_log_item();
    if ( li_ptr )
    {
      li_ptr->log_id                         = PWRDB_LOG_CLK_GET_CLK_EN;
      li_ptr->data.clk_get_clk_en.clk        = c_ptr->params.clk_get_clk_en.clk;
      li_ptr->data.clk_get_clk_en.clk_en_len = (uint16)c_ptr->params.clk_get_clk_en.clk_en_len;
      if (enable)
      {
        li_ptr->data.clk_get_clk_en.enable = 1;
      }
      else
      {
        li_ptr->data.clk_get_clk_en.enable = 0;
      }
    }
  }
}

/*===========================================================================

FUNCTION PWRDB_PROCESS_CMD_CLK_GET_CLK_FREQ

===========================================================================*/
static void pwrdb_process_cmd_clk_get_clk_freq( pwrdb_cmd_type *c_ptr )
{
  uint32          freq       = 0;
  pwrdb_log_type  *li_ptr    = NULL;
  uint32          ClockID    = 0;
  
  if( pwrdb_dal_Clk_handle == NULL )
  {
    if( DAL_SUCCESS != DAL_DeviceAttach(DALDEVICEID_CLOCK, &pwrdb_dal_Clk_handle) )
    {  
      return;
    }
  }
  
  if( DAL_SUCCESS != DalClock_GetClockId( pwrdb_dal_Clk_handle, c_ptr->params.clk_get_clk_freq.clk, &ClockID) )
  {
    return;
  }
  
  if( DAL_SUCCESS != DalClock_GetClockFrequency( pwrdb_dal_Clk_handle, ClockID, &freq ) )
  {
    return;
  }
  /* put the result into the log */
  if( pwrdb_log_format != PWRDB_LOG_TO_RAM  )
  {
    pwrdb_log_function( PWRDB_CMD_CLK_GET_CLK_FREQ, freq );
  }
  else
  {
    li_ptr = pwrdb_next_log_item();
    if ( li_ptr )
    {
      li_ptr->log_id                           = PWRDB_LOG_CLK_GET_CLK_FREQ;
      li_ptr->data.clk_get_clk_freq.clk        = c_ptr->params.clk_get_clk_freq.clk;
      li_ptr->data.clk_get_clk_freq.freq       = freq;
      li_ptr->data.clk_get_clk_freq.clk_en_len = (uint16) c_ptr->params.clk_get_clk_freq.clk_en_len;
    }
  }
} 


#ifdef PWRDB_PRO

/*===========================================================================

FUNCTION PWRDB_PROCESS_CMD_TLMM_SET_CURR_CONFIG

===========================================================================*/
static void pwrdb_process_cmd_tlmm_set_curr_config( pwrdb_cmd_type *c_ptr )
{
  /* DAL_GPIO_CFG_OUT(gpio, func, dir, pull, drive, outval) */
  uint32 cfg = DAL_GPIO_CFG_OUT( c_ptr->params.tlmm_set_curr_config.gpio_number,
                                 c_ptr->params.tlmm_set_curr_config.function,
                                 c_ptr->params.tlmm_set_curr_config.direction,
                                 c_ptr->params.tlmm_set_curr_config.pull,
                                 c_ptr->params.tlmm_set_curr_config.drive_strength,
                                 c_ptr->params.tlmm_set_curr_config.enable );

  /* If the Gpio is set to Output, Only then it is possible to set the Output to High/Low */
  if ( c_ptr->params.tlmm_set_curr_config.enable == 1 )
  { 
    /* Check if the Function is 0, Function should be set to 0 for Bit Bang Mode */ 
    if ( c_ptr->params.tlmm_set_curr_config.function == 0  )
    {

    }
  }
  /* Conditional compilation required on Karura 7x27 since functionality in DAL does not support RPC for tlmm (yet!). */
#ifdef IMAGE_APPS_PROC
 gpio_tlmm_config_remote(cfg);
#else
 (void) DalTlmm_ConfigGpio( hTlmm, 
                            cfg, 
                            DAL_TLMM_GPIO_ENABLE );
#endif
}




/*================================7===========================================

FUNCTION PWRDB_PROCESS_CMD_TLMM_SET_INACT_CONFIG

===========================================================================*/
static void pwrdb_process_cmd_tlmm_set_inact_config( pwrdb_cmd_type *c_ptr )
{
  uint8 gpio = c_ptr->params.tlmm_set_inact_config.bypass ? PWRDB_TLMM_BYPASS_VAL : c_ptr->params.tlmm_set_inact_config.gpio_number;

  //DAL_GPIO_CFG_OUT(gpio, func, dir, pull, drive, outval)
  uint32 cfg = DAL_GPIO_CFG_OUT( gpio,
                                 c_ptr->params.tlmm_set_inact_config.function,
                                 c_ptr->params.tlmm_set_inact_config.direction,
                                 c_ptr->params.tlmm_set_inact_config.pull,
                                 c_ptr->params.tlmm_set_inact_config.drive_strength,
                                 c_ptr->params.tlmm_set_inact_config.output_value );

  (void) DalTlmm_SetInactiveConfig( hTlmm,
                                    c_ptr->params.tlmm_set_inact_config.gpio_number,
                                    cfg );
} 

/*===========================================================================

FUNCTION PWRDB_PROCESS_CMD_TLMM_OUTPUT

===========================================================================*/
static void pwrdb_process_cmd_tlmm_output( pwrdb_cmd_type *c_ptr )
{
/* Must be a config descriptor to DAL not raw GPIO number. */
    uint32 cfg = DAL_GPIO_CFG_OUT( c_ptr->params.tlmm_output.gpio_number,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0 );
  (void) DalTlmm_GpioOut( hTlmm, 
                          cfg,
                          c_ptr->params.tlmm_output.output_value );

} 

/*===========================================================================

FUNCTION PWRDB_PROCESS_CMD_TLMM_INPUT

===========================================================================*/
static void pwrdb_process_cmd_tlmm_input( pwrdb_cmd_type *c_ptr )
{
  DALGpioValueType          val;
  DALResult       res;
  pwrdb_log_type *li_ptr;
  
  res = DalTlmm_GpioIn( hTlmm, 
                        c_ptr->params.tlmm_input.gpio_number,
                        &val );

  if (res == DAL_SUCCESS)
  {
    /* put the result into the log */
    if( pwrdb_log_format != PWRDB_LOG_TO_RAM )
    {
      pwrdb_log_function( PWRDB_CMD_TLMM_GET_CURR_CONFIG, val );  
    }
    else
    {
      li_ptr = pwrdb_next_log_item();
      if ( li_ptr )
      {
        li_ptr->log_id                      = PWRDB_LOG_TLMM_INPUT;
        li_ptr->data.tlmm_input.gpio_number = c_ptr->params.tlmm_input.gpio_number;
        li_ptr->data.tlmm_input.input_value = (uint8)val;
      }
    }
  } 
}

/*===========================================================================

FUNCTION PWRDB_PROCESS_CMD_TLMM_GET_PIN_STATUS

===========================================================================*/
static void pwrdb_process_cmd_tlmm_get_pin_status( pwrdb_cmd_type *c_ptr )
{
  DALGpioStatusType     status;
  DALResult       res;
  pwrdb_log_type *li_ptr;
  
  res = DalTlmm_GetPinStatus( hTlmm, 
                              c_ptr->params.tlmm_get_pin_status.gpio_number,
                              &status );
  if (res == DAL_SUCCESS)
  {
    /* put the result into the log */
    if( pwrdb_log_format != PWRDB_LOG_TO_RAM )
    {
      pwrdb_log_function( PWRDB_CMD_TLMM_GET_CURR_CONFIG, status );  
    }
    else
    {
      li_ptr = pwrdb_next_log_item();
      if ( li_ptr )
      {
        li_ptr->log_id                               = PWRDB_LOG_TLMM_GET_PIN_STATUS;
        li_ptr->data.tlmm_get_pin_status.gpio_number = c_ptr->params.tlmm_get_pin_status.gpio_number;
        li_ptr->data.tlmm_get_pin_status.pin_status  = (uint8)status;
      }
    }
  } 
}

/*===========================================================================

FUNCTION PWRDB_PROCESS_CMD_TLMM_LOCK

===========================================================================*/
static void pwrdb_process_cmd_tlmm_lock( pwrdb_cmd_type *c_ptr )
{
  (void) DalTlmm_LockGpio( hTlmm,
                           0, 
                           c_ptr->params.tlmm_lock.gpio_number );
}

/*===========================================================================

FUNCTION PWRDB_PROCESS_CMD_TLMM_UNLOCK

===========================================================================*/
static void pwrdb_process_cmd_tlmm_unlock( pwrdb_cmd_type *c_ptr )
{
  (void) DalTlmm_UnlockGpio( hTlmm,
                             0, 
                             c_ptr->params.tlmm_lock.gpio_number );
}

/*===========================================================================

FUNCTION PWRDB_PROCESS_CMD_CLK_SET_CLK_EN

===========================================================================*/
static void pwrdb_process_cmd_clk_set_clk_en( pwrdb_cmd_type *c_ptr )
{
  uint32 ClockID = 0;
  if( pwrdb_dal_Clk_handle == NULL )
  {
    if( DAL_SUCCESS != DAL_DeviceAttach(DALDEVICEID_CLOCK, &pwrdb_dal_Clk_handle) )
    {
      return;
    }
  }
  
  if( DAL_SUCCESS != DalClock_GetClockId( pwrdb_dal_Clk_handle, c_ptr->params.clk_set_clk_en.clk, &ClockID) )
  {
    return;
  }
  
  if (c_ptr->params.clk_set_clk_en.enable)
  {
    DalClock_EnableClock( pwrdb_dal_Clk_handle, ClockID );
  }
  else
  {
    DalClock_DisableClock( pwrdb_dal_Clk_handle, ClockID );
  }
}




/*===========================================================================

FUNCTION pwrdb_get_npa_marker
 
DESCRIPTION
  Get the Npa Marker for Pwrdb Time Sync on Npa Log
 
PARAMETERS
  Void
  
RETURN VALUE
  Char*: String to be put on the Npa Log for sync
 
Dependencies 
  None

SIDE EFFECTS 
  None
===========================================================================*/

char* pwrdb_get_npa_marker( void )
{
  static const char digits[] = "0123456789abcdef";
  static uint32 npa_trigger_index = 0;
  uint32 i = npa_trigger_index%(sizeof(digits)-1); 
  core_snprintf(npa_str, sizeof(npa_str),"/pwrdb/npa_log_trigger_%c", digits[i]);
  npa_trigger_index++;
  return npa_str;
}




/*==========================================================================

FUNCTION PWRDB_NPA_INIT

DESCRIPTION
  Initialize the NPA node for PWRDB. This is for testing purpose only. 
  No other users should call this function.

RETURN VALUE
  TRUE  - an event is active
  FALSE - no event is active  

==========================================================================*/

boolean pwrdb_npa_init (void)
{
  /*-----------------------------------------------------------------------*/
  /* Local variables                                                       */
  /*-----------------------------------------------------------------------*/

  npa_resource_state            initial_state[2]={0,0};

  /*-----------------------------------------------------------------------*/
  /* Init the NPA PWRDB resource/node. The test PWRDB node will be used to */
  /* find the maximum number. Here the npa max plugin function is used.    */
  /*-----------------------------------------------------------------------*/
  
  pwrdb_test_node.node.name = "/core/powertools/pwrdb_test_node";
  pwrdb_test_node.node.driver_fcn = pwrdb_npa_node_max;
  pwrdb_test_node.node.attributes = NPA_NODE_DEFAULT;
  pwrdb_test_node.node.resources = pwrdb_test_node.rsrc;
  pwrdb_test_node.node.resource_count = 2;

  pwrdb_test_node.rsrc[0].name = "/core/powertools/pwrdb_test_rsrc1";
  pwrdb_test_node.rsrc[0].units = "Unit";
  pwrdb_test_node.rsrc[0].attributes = NPA_RESOURCE_DEFAULT;
  pwrdb_test_node.rsrc[0].plugin = &npa_max_plugin;
  pwrdb_test_node.rsrc[0].data = 0;
  pwrdb_test_node.rsrc[0].max = 0xffffffff;

  pwrdb_test_node.rsrc[1].name = "/core/powertools/pwrdb_test_rsrc2";
  pwrdb_test_node.rsrc[1].units = "Unit";
  pwrdb_test_node.rsrc[1].attributes = NPA_RESOURCE_DEFAULT;
  pwrdb_test_node.rsrc[1].plugin = &npa_max_plugin;
  pwrdb_test_node.rsrc[1].data = 0;
  pwrdb_test_node.rsrc[1].max = 0xffffffff;

  npa_define_node(&pwrdb_test_node.node, initial_state, NULL);

  /*-----------------------------------------------------------------------*/
  /* Create an internal client handle                                       */
  /*-----------------------------------------------------------------------*/

  pwrdb_test_client.handle[0] =
    npa_create_sync_client("/core/powertools/pwrdb_test_rsrc1","/core/powertools/pwrdb_test_client1",
    NPA_CLIENT_REQUIRED);
  
  if(pwrdb_test_client.handle[0]==NULL)
  {
    PWRDB_MSG_E0( "Created test handle 1 failed in pwrdb_npa_init." );
    return FALSE;
  }
  npa_issue_required_request(pwrdb_test_client.handle[0], 25);


  pwrdb_test_client.handle[1] =
  npa_create_sync_client("/core/powertools/pwrdb_test_rsrc2","/core/powertools/pwrdb_test_client2", 
  NPA_CLIENT_REQUIRED);
  
  if(pwrdb_test_client.handle[1]==NULL)
  {
    PWRDB_MSG_E0( "Created test handle 2 failed in pwrdb_npa_init." );
    return FALSE;
  }
  npa_issue_required_request(pwrdb_test_client.handle[1], 50);
  
  
  /* Sleep LPR implementation */
  npa_resources_available_cb( NPA_ARRAY( pwrdb_lpr_init_resources ),
                              pwrdb_sleep_lpr_init,
                              NULL );
  return TRUE;
} 

/* Sleep LPR implementation */
/*===========================================================================

FUNCTION pwrdb_sleep_lpr_init

DESCRIPTION


RETURN VALUE
  
    
===========================================================================*/
void pwrdb_sleep_lpr_init( void *context,
                           unsigned int event_type, 
                           void *data,       
                           unsigned int data_size )
{
  npa_client_handle pwrdb_npa_handle = npa_create_sync_client( "/sleep/lpr",
                                                               "/npa/scheduler/lpr",
                                                               NPA_CLIENT_REQUIRED );
  sleep_define_lpr_str( "pwrdb_mpss_lpr" , pwrdb_npa_handle );
  
  
  npa_issue_required_request( pwrdb_npa_handle, SLEEP_ALL_LPRMS);
}

/*===========================================================================

FUNCTION PWRDB_NPA_NODE_MAX

DESCRIPTION
  Driver function for pwrdb test node. For testing purpose only.
  No other users should call this function.

RETURN VALUE
  The final max value for pwrdb_test_max.
    
===========================================================================*/
npa_resource_state pwrdb_npa_node_max(struct npa_resource *resource, npa_client_handle client,npa_resource_state state )
{
    if(state >= pwrdb_test_max)
    {
      pwrdb_test_max = state;
    }
    //Uncomment this when debugging
    //pwrdb_log_msg_3(PWRDB_INFO_MESSAGE, "PWRDB NPA TEST MAX VALUE:", pwrdb_test_max, 0, 0);
    return pwrdb_test_max;
}

/*===========================================================================

FUNCTION PWRDB_PROCESS_CMD_CLK_OUTPUT_GPIO
 
DESCRIPTION
  Program the CLK_TEST register to get the clock output to the GPIO  

PARAMETERS
 c_ptr
 
DPENDENCIES
  Command queue must have previously been initialized by calling 
  pwrdb_task_cmd_queue_init().

SIDE EFFECTS
  None. 
===========================================================================*/
PACKED void *pwrdb_process_cmd_clk_output_gpio( PACKED void *req_pkt_ptr, uint16 pkt_len )
{

  pwrdb_diag_pkt_clk_output_gpio_rsp_type  *rsp_ptr = NULL;
  pwrdb_diag_pkt_clk_output_gpio_req_type  *req_ptr = (pwrdb_diag_pkt_clk_output_gpio_req_type *)req_pkt_ptr;

  /* Set up response packet */
  rsp_ptr = (pwrdb_diag_pkt_clk_output_gpio_rsp_type *) diagpkt_subsys_alloc (
                                                    DIAG_SUBSYS_PWRDB,
                                                    (PWRDB_DIAG_PKT_CLK_OUTPUT_GPIO | PWRDB_DIAG_PKT_CPU_ID),
                                                    sizeof(pwrdb_diag_pkt_clk_output_gpio_rsp_type) );

  //if( req_ptr->hdr.subsys_cmd_code != PWRDB_DIAG_PKT_CLK_OUTPUT_GPIO )
  //  return NULL;
  if(rsp_ptr == NULL)
    return NULL;

  if ( pwrdb_state != PWRDB_STATE_PROC_EVENT )
  {
    /* push this processing to the task */
    pwrdb_program_clk_test_reg( req_ptr->reg_value );

    rsp_ptr->status = PWRDB_RSP_SUCCESS;
  }
  else
  {
    rsp_ptr->status = PWRDB_RSP_ERROR;
  }

  return rsp_ptr;
}   

/*===========================================================================

FUNCTION PWRDB_PROCESS_CMD_PEEK8

===========================================================================*/
static void pwrdb_process_cmd_peek8( pwrdb_cmd_type *c_ptr )
{
  pwrdb_log_type *li_ptr;
  uint8          *addr = (uint8 *)(c_ptr->params.peek8.addr);
  uint64         peekresult=0;

  /* put the result into the log */
  peekresult = (uint64)(*addr&0XFF);
  if( pwrdb_log_format != PWRDB_LOG_TO_RAM )
  {
    //*peek_result &= 0x00FF;
    pwrdb_log_function( PWRDB_CMD_PEEK8 ,peekresult );  
  }
  else
  {
    li_ptr = pwrdb_next_log_item();
  
    if ( li_ptr )
    {
      li_ptr->log_id              = PWRDB_LOG_PEEK8;
      li_ptr->data.peek8.addr     = c_ptr->params.peek8.addr;
      li_ptr->data.peek8.physaddr = c_ptr->params.peek8.addr;
      li_ptr->data.peek8.val      = *addr;
    }
  }
}

/*===========================================================================

FUNCTION PWRDB_PROCESS_CMD_PEEK16

===========================================================================*/
static void pwrdb_process_cmd_peek16( pwrdb_cmd_type *c_ptr )
{
  pwrdb_log_type *li_ptr;
  uint16         *addr = (uint16 *)(c_ptr->params.peek16.addr);
  uint64         peekresult=0;

  /* put the result into the log */
  peekresult = (uint64)(*addr&0XFFFF);

  /* put the result into the log */
  if( pwrdb_log_format != PWRDB_LOG_TO_RAM )
  {
    pwrdb_log_function( PWRDB_CMD_PEEK16, peekresult );
  }
  else
  {
    li_ptr = pwrdb_next_log_item();
    if ( li_ptr )
    {
      li_ptr->log_id              = PWRDB_LOG_PEEK16;
      li_ptr->data.peek16.addr    = c_ptr->params.peek16.addr;
      li_ptr->data.peek8.physaddr = c_ptr->params.peek8.addr;
      li_ptr->data.peek16.val     = *addr;
    }
  }
}

/*===========================================================================

FUNCTION PWRDB_PROCESS_CMD_PEEK32

===========================================================================*/
static void pwrdb_process_cmd_peek32( pwrdb_cmd_type *c_ptr )
{
  pwrdb_log_type *li_ptr;
  uint32         *addr = (uint32 *)(c_ptr->params.peek32.addr);
  uint64         peekresult=0;

  /* put the result into the log */
  peekresult = (uint64)(*addr&0XFFFFFFFF);

  /* put the result into the log */
  if( pwrdb_log_format != PWRDB_LOG_TO_RAM )
  {
    pwrdb_log_function( PWRDB_CMD_PEEK32, peekresult );
  }
  else
  {
    li_ptr = pwrdb_next_log_item();
    if ( li_ptr )
    {
      li_ptr->log_id              = PWRDB_LOG_PEEK32;
      li_ptr->data.peek32.addr    = c_ptr->params.peek32.addr;
      li_ptr->data.peek8.physaddr = c_ptr->params.peek8.addr;
      li_ptr->data.peek32.val     = *addr;
    }
  }
}

/*===========================================================================

FUNCTION PWRDB_PROCESS_CMD_PEEK32_RANGE

===========================================================================*/
static void pwrdb_process_cmd_peek32_range( pwrdb_cmd_type *c_ptr )
{
  pwrdb_log_type *li_ptr;
  uint32         *arrayaddr;
  uint32 num, *addrfrom = NULL;
  uint64         peekresult = 0;
  addrfrom = (uint32 *)c_ptr->params.peek32_range.addr;
  DALResult res;

  res = DALSYS_Malloc((c_ptr->params.peek32_range.range)*sizeof(uint32), (void*)&arrayaddr);
  if(res != DAL_SUCCESS)
  {
       PWRDB_MSG_H0("Malloc Failed, returning from POKE32 RANGE BYTE Command execution");
       pwrdb_log_message(PWRDB_ERROR_MESSAGE, "peek32 range malloc failed");
  }
  else
  {
       pwrdb_addto_malloc_array(arrayaddr);

       for(num=0;num<(c_ptr->params.peek32_range.range);num++)
       {
         *(arrayaddr+num) = *(addrfrom+num);
       peekresult = (uint64)((*(addrfrom+num))&0xFFFFFFFF);
       pwrdb_log_function( PWRDB_CMD_PEEK32_RANGE, peekresult );
       }
  }
  if( pwrdb_log_format == PWRDB_LOG_TO_RAM )
  {
    /* put the result into the log */
    li_ptr = pwrdb_next_log_item();
    if ( li_ptr )
    {
      li_ptr->log_id                      = PWRDB_LOG_PEEK32_RANGE;
      li_ptr->data.peek32_range.addr      = c_ptr->params.peek32_range.addr;
      li_ptr->data.peek8.physaddr         = c_ptr->params.peek8.addr;
      li_ptr->data.peek32_range.num_vals  = c_ptr->params.peek32_range.range;
      li_ptr->data.peek32_range.vals      = (uint32 *) arrayaddr;
    }
  }
}

/*===========================================================================

FUNCTION PWRDB_PROCESS_CMD_POKE32_RANGE

===========================================================================*/
static void pwrdb_process_cmd_poke32_range( pwrdb_cmd_type *c_ptr )
{
  uint32 *addr = (uint32 *)(c_ptr->params.poke32_range.addr);
  uint32 range = (uint32)(c_ptr->params.poke32_range.range);
  uint32 i;
  for(i=0;i<range;i++)
     *(addr + i)= *(c_ptr->params.poke32_range.vals + i);

  pwrdb_log_message(PWRDB_INFO_MESSAGE, "POKE32_RANGE successful");
}

/*===========================================================================

FUNCTION PWRDB_PROCESS_CMD_POKE8_M

===========================================================================*/

static void pwrdb_process_cmd_poke8_m( pwrdb_cmd_type *c_ptr )
{
  uint8 *addr = (uint8 *)(c_ptr->params.poke8_m.addr);
  uint8  mask = c_ptr->params.poke8_m.mask;
  uint8  val  = c_ptr->params.poke8_m.val;
  
  *addr = (*addr & ~mask) | (val & mask); /* TODO add INTLOCK or equivalent */
}

/*===========================================================================

FUNCTION PWRDB_PROCESS_CMD_POKE16_M

===========================================================================*/
static void pwrdb_process_cmd_poke16_m( pwrdb_cmd_type *c_ptr )
{
  uint16 *addr = (uint16 *)(c_ptr->params.poke16_m.addr);
  uint16  mask = c_ptr->params.poke16_m.mask;
  uint16  val  = c_ptr->params.poke16_m.val;
  
  *addr = (*addr & ~mask) | (val & mask); /* TODO add INTLOCK or equivalent */
}

/*===========================================================================

FUNCTION PWRDB_PROCESS_CMD_POKE32_M

===========================================================================*/
static void pwrdb_process_cmd_poke32_m( pwrdb_cmd_type *c_ptr )
{
  uint32 *addr = (uint32 *)(c_ptr->params.poke32_m.addr);
  uint32  mask = c_ptr->params.poke32_m.mask;
  uint32  val  = c_ptr->params.poke32_m.val;
  
  *addr = (*addr & ~mask) | (val & mask); /* TODO add INTLOCK or equivalent */
}

#if 0
/*===========================================================================

FUNCTION PWRDB_PROCESS_CMD_STRING

DESCRIPTION
  Processes the received string and returns the same to the user.  
  
===========================================================================*/
static void pwrdb_process_cmd_string( pwrdb_cmd_type *c_ptr )
{
  pwrdb_log_type *li_ptr;

  /* put the result into the log */
  if( pwrdb_log_format != PWRDB_LOG_TO_FS )
  {
    pwrdb_log_function( PWRDB_CMD_STRING, 0 );
  }
  else
  {
    li_ptr = pwrdb_next_log_item();
    if ( li_ptr )
    {
         li_ptr->log_id              = PWRDB_LOG_STRING;
         li_ptr->data.strng.str_type = c_ptr->params.strng.str_type;
         li_ptr->data.strng.str_len  = c_ptr->params.strng.str_len;
         li_ptr->data.strng.str      = c_ptr->params.strng.str;
    }
  }
}
#endif

/*===========================================================================

FUNCTION PWRDB_PROCESS_CMD_DATA3_STRING

DESCRIPTION
  Processes the received string, data and returns the same to the user.
  
===========================================================================*/
static void pwrdb_process_cmd_data3_string( pwrdb_cmd_type *c_ptr )
{
  pwrdb_log_type *li_ptr;

  /* put the result into the log */
  if( pwrdb_log_format != PWRDB_LOG_TO_RAM )
  {
    /* TBD: What are the expected values in the value* parameters */
    pwrdb_log_function( PWRDB_CMD_DATA3_STRING, 0 );
  }
  else
  {
    li_ptr = pwrdb_next_log_item();
    if ( li_ptr )
    {
      li_ptr->log_id                    = PWRDB_LOG_DATA3_STRING;
      li_ptr->data.data3_strng.str_type = c_ptr->params.data3_strng.str_type;
      li_ptr->data.data3_strng.value1   = c_ptr->params.data3_strng.value1;
      li_ptr->data.data3_strng.value2   = c_ptr->params.data3_strng.value2;
      li_ptr->data.data3_strng.value3   = c_ptr->params.data3_strng.value3;
      li_ptr->data.data3_strng.str_len  = c_ptr->params.data3_strng.str_len;
      li_ptr->data.data3_strng.str      = c_ptr->params.data3_strng.str;
    }
  }
}

/*===========================================================================

FUNCTION pwrdb_process_cmd_npa_issue_required_request

DESCRIPTION
   The function processs the REQUIRED client work request.
   The client must be of REQUIRED work model
  
===========================================================================*/
static void pwrdb_process_cmd_npa_issue_required_request(pwrdb_cmd_type *c_ptr)
{
  uint32            state              = c_ptr->params.npa_issue_required_request.state;
  npa_client_handle NPAClientHandle    = c_ptr->params.npa_issue_required_request.NPAClientHandle;

 /* Make sure we have a valid npa handle available */
  if ( NPAClientHandle != NULL )
  {
    /* Issue a work request of the specified state to the resource */
    npa_issue_required_request( NPAClientHandle,
                               (npa_resource_state)state);
  }
  else
  {
    pwrdb_log_message(PWRDB_ERROR_MESSAGE, "Issued required request on invalid handle");
  }
}

/*===========================================================================

FUNCTION pwrdb_process_cmd_npa_modify_required_request

DESCRIPTION
   This function process the request to modify the existing 
   REQUIRED client work request. This is intended to be used in a 
   feedback loop, so the client can request incrementally more 
   (or less) resource .

===========================================================================*/
static void pwrdb_process_cmd_npa_modify_required_request(pwrdb_cmd_type *c_ptr)
{
  int32             delta              = c_ptr->params.npa_modify_required_request.delta;
  npa_client_handle NPAClientHandle    = c_ptr->params.npa_modify_required_request.NPAClientHandle;

 /* Make sure we have a valid npa handle available */
  if (NPAClientHandle != NULL )
  {
    npa_modify_required_request( NPAClientHandle,
                                (npa_resource_state_delta)delta);
  }
  else
  {
    pwrdb_log_message(PWRDB_ERROR_MESSAGE, "Modify required request on invalid handle");
  }
}

/*===========================================================================

FUNCTION pwrdb_process_cmd_npa_issue_impulse_request

DESCRIPTION
   This function process the request to issue an IMPULSE work request. 
   The client must be of IMPULSE work model.The resource defines the 
   impulse response.

   Note: This is not completed supported yet at the time I wrote this.

===========================================================================*/
static void pwrdb_process_cmd_npa_issue_impulse_request(pwrdb_cmd_type *c_ptr)
{
  npa_client_handle NPAClientHandle    = c_ptr->params.npa_issue_impulse_request.NPAClientHandle;

  /* Make sure we have a valid npa handle available */
  if (NPAClientHandle != NULL )
  {
    /* Issue a work request of the specified number of mips to the CPU */
    npa_issue_impulse_request( NPAClientHandle);
  }
  else
  {
    pwrdb_log_message(PWRDB_ERROR_MESSAGE, "Issued impulse request on invalid handle");
  }
}

/*===========================================================================

FUNCTION pwrdb_process_cmd_npa_ssue_isoc_request

DESCRIPTION
   This function process the request to issue an ISOCHRONOUS work request. 
   The client must be of ISOCHRONOUS work model. The client must issue 
   npa_complete_request() when the work is completed

   Note: This is not yet supported at the time I wrote this.

===========================================================================*/
static void pwrdb_process_cmd_npa_issue_isoc_request(pwrdb_cmd_type *c_ptr)
{
  uint32            deadline           = c_ptr->params.npa_issue_isoc_request.deadline;
  uint32            level_hint         = c_ptr->params.npa_issue_isoc_request.level_hint;
  npa_client_handle NPAClientHandle    = c_ptr->params.npa_issue_isoc_request.NPAClientHandle;

  /* Make sure we have a valid npa handle available */
  if (NPAClientHandle != NULL )
  {
    npa_issue_isoc_request(  NPAClientHandle,
                            (npa_resource_time)deadline,
                            (npa_resource_state)level_hint);
  }
  else
  {
    pwrdb_log_message(PWRDB_ERROR_MESSAGE, "Issued isoc request on invalid handle");
  }
}

/*===========================================================================

FUNCTION pwrdb_process_cmd_npa_issue_limit_max_request

DESCRIPTION
   This function process the request to issue a LIMIT_MAX work request. 
   The client must be of LIMIT_MAXS work model. 

===========================================================================*/
static void pwrdb_process_cmd_npa_issue_limit_max_request(pwrdb_cmd_type *c_ptr)
{
  uint32            max                = c_ptr->params.npa_issue_limit_max_request.max;
  npa_client_handle NPAClientHandle    = c_ptr->params.npa_issue_limit_max_request.NPAClientHandle;

  /* Make sure we have a valid npa handle available */
  if (NPAClientHandle != NULL )
  {
    npa_issue_limit_max_request(  NPAClientHandle,
                                 (npa_resource_state)max);
  }
  else
  {
    pwrdb_log_message(PWRDB_ERROR_MESSAGE, "Issued limit max request on invalid handle");
  }
}

/*===========================================================================

FUNCTION pwrdb_process_cmd_npa_complete_request

DESCRIPTION
   This function process the request to notify the resource that the work 
   request is complete and the client no longer needs the resource.

===========================================================================*/
static void pwrdb_process_cmd_npa_complete_request(pwrdb_cmd_type *c_ptr)
{
  npa_client_handle NPAClientHandle    = c_ptr->params.npa_complete_request.NPAClientHandle;

  /* Make sure we have a valid npa handle available */
  if (NPAClientHandle != NULL )
  {
    npa_complete_request(  NPAClientHandle );
  }
  else
  {
    pwrdb_log_message(PWRDB_ERROR_MESSAGE, "Issued limit max request on invalid handle");
  }
}

/*===========================================================================

FUNCTION PWRDB_NPA_GET_CLIENT_HANDLE

DESCRIPTION
  Helper function to look up the NPA client handle from our npa resources array.
 
PARAMETERS
  phNPAClient - The address of the npa client handle.The parameter in this address is a 
  pointer to a npa client. 
  npa_resource_name - The npa resource that we issue command to.
  sync - 1:synchrous client. 0:asynchrous client.
  npa_client type - npa client work model.

DEPENDENCIES
  None

RETURN VALUE
  pwrdb_res_type

===========================================================================*/
pwrdb_res_type pwrdb_npa_get_client_handle( npa_client_handle *phNPAClient, 
                                            const char *npa_resource_name, 
                                            uint8 sync, 
                                            npa_client_type client_type)
{
    int                        ix;
    boolean                    bNPANOResource = FALSE;    /* Flag to indicate if PWRDB_NPA_NO_RESOURCE is encountered */
    boolean                    bNPAFindResource = FALSE;  /* Flag to indicate if NPA resource is found */     
    npa_client_handle          hNPAClient;
    pwrdb_res_type             status      = PWRDB_RES_OK;
    pwrdb_npa_client_sync_type npa_sync =(pwrdb_npa_client_sync_type)sync;
    

    if (!pwrdb_npa_resource_initialized)
    {
        pwrdb_npa_resource_init();
    }


    /* Loop through the pwrdb_npa_resource structure table */
    for (ix = 0;ix < PWRDB_NUM_NPA_RESOURCE; ix ++)
    {
      if ((strcmp(PWRDB_NPA_NO_RESOURCE,pwrdb_npa_resource[ix].npa_resource_name) == 0))
      {
        bNPANOResource = TRUE;
      }
      else if (strcmp(npa_resource_name,pwrdb_npa_resource[ix].npa_resource_name) == 0)
      {
        bNPAFindResource = TRUE;
      }

      if( bNPANOResource  || bNPAFindResource)
      {
        /* Created synchronous handle if the resource didn't exist before or it existed but was requested for different async type */
        /* Note: The same resources can have both sync and async clients at the same time. */
        if( npa_sync == SYNC )
        {
          if ( bNPANOResource || (bNPAFindResource && (pwrdb_npa_resource[ix].sync_handle == NULL)))
          {
            /* Malloc to copy the resource name */       
            if ( bNPANOResource )
            { 
              pwrdb_npa_resource[ix].npa_resource_name = pwrdb_npa_malloc2cpy_str( npa_resource_name );
            }
            /*Creates a synchronous client of a resource */
            hNPAClient = npa_create_sync_client( pwrdb_npa_resource[ix].npa_resource_name, 
                                                 PWRDB_NPA_CLIENT_NAME,
                                                 client_type);
            /* Check to see that the handle was created successfully */
            if ( hNPAClient == NULL )
            {
              PWRDB_MSG_E0("NPA sync client created failed. ");
              pwrdb_log_msg_3(PWRDB_ERROR_MESSAGE, "NPA sync client created failed.", 0, 0, 0);
              status = PWRDB_RES_ERROR;
              return status;
            }
            /* Assign this handle to sync client handle */
            pwrdb_npa_resource[ix].sync_handle = hNPAClient;
            /* Update the client handle in loc_cmd_ptr */
            *phNPAClient                       = hNPAClient;
            break;
          }
          else if ( bNPAFindResource && (pwrdb_npa_resource[ix].sync_handle != NULL) )
          {
            *phNPAClient = pwrdb_npa_resource[ix].sync_handle;
            break;
          }		
        }
        /* Created asynchronous handle if the resource didn't exist before or it existed but was requested for different sync type */
        /* Note: The same resources can have both sync and async clients at the same time. */
        else if ( npa_sync == ASYNC )
        {
          if ( bNPANOResource || (bNPAFindResource && (pwrdb_npa_resource[ix].async_handle == NULL)))
          {
            /* Malloc to copy the resource name */       
            if ( bNPANOResource )
            {   
              pwrdb_npa_resource[ix].npa_resource_name = pwrdb_npa_malloc2cpy_str( npa_resource_name );
            }
            /* To do: Not sure about the client type and which completion event should we pass, so use NULL first */
            hNPAClient = npa_create_async_client( pwrdb_npa_resource[ix].npa_resource_name, 
                                                  PWRDB_NPA_CLIENT_NAME,
                                                  client_type,
                                                  NULL );
            /* Check to see that the handle was created successfully */
            if ( hNPAClient == NULL )
            {
              PWRDB_MSG_E0("NPA get client handle failed. ");
              pwrdb_log_msg_3(PWRDB_ERROR_MESSAGE, "NPA get client handle failed.", 0, 0, 0);
              status = PWRDB_RES_ERROR;
              return status;
            }
            /* Assign this handle to async client handle */
            pwrdb_npa_resource[ix].async_handle = hNPAClient;			  
            /* Update the client handle in loc_cmd_ptr */
            *phNPAClient                        = hNPAClient;
            break;		  
          }
          else if (bNPAFindResource && (pwrdb_npa_resource[ix].async_handle != NULL))
          {
            *phNPAClient = pwrdb_npa_resource[ix].async_handle;
            break;
          }
        }
      }
    }
      
    /* The pwrdb_npa_resource array is full */
    if (ix == PWRDB_NUM_NPA_RESOURCE)
    {
      PWRDB_MSG_E0("pwrdb_npa_resource array is full. npa_resource cannot be added ");
      pwrdb_log_msg_3(PWRDB_ERROR_MESSAGE, "pwrdb_npa_resource array is full. npa_resource cannot be added", 0, 0, 0);
      status = PWRDB_RES_ERROR;
      return status;
    }
    return status;
}

/*===========================================================================

FUNCTION PWRDB_NPA_GET_COMPLETE_REQUEST_CLIENT_HANDLE

DESCRIPTION
  Helper function to look up the NPA client handle from our npa resources array
  when complete request is issued to certian npa resources.
 
PARAMETERS
  phNPAClient - The address of the npa client handle.The parameter in this address is a 
  pointer to a npa client. 
  npa_resource_name - The npa resource that we issue command to.
  sync - 1:synchrous client. 0:asynchrous client.

DEPENDENCIES
  None

RETURN VALUE
  pwrdb_res_type

===========================================================================*/
pwrdb_res_type pwrdb_npa_get_complete_request_client_handle( npa_client_handle *phNPAClient, 
                                                             const char        *npa_resource_name,
                                                             uint8              sync )
{
    int                        ix;
    boolean                    bNPANOResource   = FALSE;  /* Flag to indicate if PWRDB_NPA_NO_RESOURCE is encountered */
    boolean                    bNPAFindResource = FALSE;  /* Flag to indicate if NPA resource is found */     
    pwrdb_res_type             status = PWRDB_RES_OK;
    pwrdb_npa_client_sync_type npa_sync =(pwrdb_npa_client_sync_type)sync; 



    if (!pwrdb_npa_resource_initialized)
    {
      PWRDB_MSG_E0("There weren't any requests made before, hence shouldn't complete any requests.");
      pwrdb_log_message(PWRDB_ERROR_MESSAGE, "There weren't any requests made before, hence shouldn't complete any requests.");
      status = PWRDB_RES_ERROR;
      return status;
    }
    /* Loop through the pwrdb_npa_resource strucure table */
    for (ix = 0;ix < PWRDB_NUM_NPA_RESOURCE; ix ++)
    {
      if ((strcmp(PWRDB_NPA_NO_RESOURCE,pwrdb_npa_resource[ix].npa_resource_name) == 0))
      {
        bNPANOResource = TRUE;
      }
      else if (strcmp(npa_resource_name,pwrdb_npa_resource[ix].npa_resource_name) == 0)
      {
        bNPAFindResource = TRUE;
      }

      if( bNPANOResource || bNPAFindResource)
      { 
        /* If the npa resource doesn't exist. */
        if ( bNPANOResource )
        {
          PWRDB_MSG_E0("Failed at get_complete_request_client_handle. Requested resource doesn't exist. ");
          pwrdb_log_message(PWRDB_ERROR_MESSAGE, "Failed at get_complete_request_client_handle. Requested resource doesn't exist.");
          status = PWRDB_RES_ERROR;
          return status;   
        }
        /* If the npa resource is already requested. */
        else
        {  
          /* The npa resource is already requested */
          if ( npa_sync == SYNC)
          {
           *phNPAClient = pwrdb_npa_resource[ix].sync_handle;
            break;
          }
          else 
          { 
           *phNPAClient = pwrdb_npa_resource[ix].async_handle;
            break;
          }
        }
      }
    }
    /* The pwrdb_npa_resource array is full */
    if (ix == PWRDB_NUM_NPA_RESOURCE)
    {
      PWRDB_MSG_E0("pwrdb_npa_resource array is full. Requested resource doesn't exist. ");
      pwrdb_log_msg_3(PWRDB_ERROR_MESSAGE, "pwrdb_npa_resource array is full. Requested resource doesn't exist.", 0, 0, 0);
      status = PWRDB_RES_ERROR;
      return status;   
    }
    return status;
}

/*===========================================================================

FUNCTION pwrdb_process_cmd_npa_query_by_name

DESCRIPTION
   This function process the request to query NPA state according to different
   query ID.

===========================================================================*/
static void pwrdb_process_cmd_npa_query_by_name(pwrdb_cmd_type *c_ptr)
{
  uint32            query_id       = c_ptr->params.npa_query_by_name.query_id;
  npa_query_handle  NPAQueryHandle = c_ptr->params.npa_query_by_name.NPAQueryHandle;
  npa_query_status  res            = NPA_QUERY_UNSUPPORTED_QUERY_ID;
  pwrdb_log_type   *li_ptr;
  npa_query_type    npa_query_result;
  uint64            result = 0;
  /* Make sure we have a valid npa handle available */
  if (NPAQueryHandle != NULL )
  {
    res = npa_query( NPAQueryHandle, 
                     query_id, 
                    &npa_query_result );

    if (res == NPA_QUERY_SUCCESS)
    {
      /* put the result into the log */
      if( pwrdb_log_format != PWRDB_LOG_TO_RAM )
      {
        result = npa_query_result.type;
        switch( npa_query_result.type  )
        {
          case NPA_QUERY_TYPE_VALUE:
            result = (result<<32|npa_query_result.data.value);
          break;
          case NPA_QUERY_TYPE_STATE:
            result = (result<<32|npa_query_result.data.state);
          break;
          case NPA_QUERY_TYPE_REFERENCE:
            result = (result<<32|(uint32)(npa_query_result.data.reference));
          break;
          default:
          break;
        }
        pwrdb_log_function( PWRDB_LOG_NPA_QUERY_BY_NAME, result );
      }
      else
      {
        li_ptr = pwrdb_next_log_item();
        if ( li_ptr )
        {
          li_ptr->log_id                                   = PWRDB_LOG_NPA_QUERY_BY_NAME;
          li_ptr->data.npa_query_by_name.query_id          = c_ptr->params.npa_query_by_name.query_id;
          li_ptr->data.npa_query_by_name.NPAQueryHandle    = c_ptr->params.npa_query_by_name.NPAQueryHandle;
          li_ptr->data.npa_query_by_name.result.type       = c_ptr->params.npa_query_by_name.result.type;
          li_ptr->data.npa_query_by_name.result.data       = c_ptr->params.npa_query_by_name.result.data;
          li_ptr->data.npa_query_by_name.resource_name     = c_ptr->params.npa_query_by_name.resource_name;
          li_ptr->data.npa_query_by_name.resource_name_len = c_ptr->params.npa_query_by_name.resource_name_len;
        }
      }
    }
    else
    {   
        PWRDB_MSG_H0("NPA query command failed");
        pwrdb_log_msg_3(PWRDB_ERROR_MESSAGE, "NPA query failed. NPA query error code:",res,0,0);
    }
  }
  else
  {
    pwrdb_log_message(PWRDB_ERROR_MESSAGE, "NPA query by name on invalid handle");
  }
}

/*===========================================================================

FUNCTION pwrdb_process_cmd_configure_hw_events_mux


DESCRIPTION
   Configure the HW Mux for QDSS Signals

===========================================================================*/
static void pwrdb_process_cmd_configure_hw_events_mux( pwrdb_cmd_type *c_ptr )
{
  /* Place Holder for configuring Hw mux */
  return;
}

/*===========================================================================

FUNCTION pwrdb_process_cmd_trigger_log_signals


DESCRIPTION
   The intention of this function is to trigger the signal
   across multiple logs based on the user input
 

===========================================================================*/
static void pwrdb_process_cmd_trigger_log_signals( pwrdb_cmd_type *c_ptr )
{
  uint32 GpioCfg = 0;
  char* npa_marker_str = NULL;
  uint32 gpio = 0;

  // Pull the time sync GPIO low by default Delay for 1ms, then send the sync messages.
  // This should align the Xerxex sync to log sync 
  pwrdb_open_DAL_TLMM();
  
    timer_error_type err;

  if( c_ptr->params.trigger_log_signal.gpio_number == 0 )
  {
    gpio = (uint32)PWRDB_TRIGGER_GPIO_NUM;
  }
  else
  {
    gpio = c_ptr->params.trigger_log_signal.gpio_number;
  }
  /* Program the GPIO to low and Pull the Signal Down */
  GpioCfg = DAL_GPIO_CFG_OUT( gpio,PWRDB_TRIGGER_GPIO_FUNC,
                                0x1,0x0,0x111,0x0 ); 
    DalTlmm_ConfigGpio(hTlmm,GpioCfg,DAL_TLMM_GPIO_DISABLE); 

    {
      /*initialize the signal */
      qurt_anysignal_init (&pwrdb_trigger_timer_sig);
      qurt_anysignal_clear(&pwrdb_trigger_timer_sig, TIME_SYNC_SIG);
      
      /*changing qurt to ATS timer, not tested for PWRDB PRO version*/
      err = timer_def_osal(&pwrdb_trigger_timer, &pwrdb_always_on_timer_group, TIMER_NATIVE_OS_SIGNAL_TYPE, &pwrdb_trigger_timer_sig,TIME_SYNC_SIG); 
      if (err != TE_SUCCESS )
      {
        PWRDB_MSG_E1("PwrDB: ATS timer creation failed with error=%d.", err, 0, 0);
        return;
      }

      timer_set_64( &pwrdb_trigger_timer, 10, 0, T_MSEC );
       
      qurt_anysignal_wait(&pwrdb_trigger_timer_sig, TIME_SYNC_SIG);


      /*once you get a signal, clearing it is a good practice*/
      qurt_anysignal_clear(&pwrdb_trigger_timer_sig, TIME_SYNC_SIG);
      /* Now Program the GPIO to low and Pull the Signal Down */
    }
  
  /* Trigger Logs based on the mask that the user programs */
  if(pwrdb_log_function) pwrdb_log_function( PWRDB_CMD_TRIGGER_LOG_SIGNALS, 0 );  // broken
  
  if( (c_ptr->params.trigger_log_signal.log_mask & PWRDB_LOGGING_MASK_NPA )  )
  {
    npa_marker_str = pwrdb_get_npa_marker();
  /* Trigger for NPA Log: Add a client with the name pwrdb_signal */
    npa_define_marker(npa_marker_str);
  }
  if( (c_ptr->params.trigger_log_signal.log_mask & PWRDB_LOGGING_MASK_QDSS_STM ) )
  {
    tracer_event_simple_vargs(PWRDB_SWE_2,0);
  }
  if( (c_ptr->params.trigger_log_signal.log_mask & PWRDB_LOGGING_MASK_UDAS )  )
  {
  /* Trigger for the UDAS: Need to identify the GPIO Signal
     For the time being keep the trigger ready and feed the GPIO number
     later when the GPIO number gets finalised*/

    GpioCfg = DAL_GPIO_CFG_OUT( gpio,PWRDB_TRIGGER_GPIO_FUNC,
                                0x1,0x0,0x111,0x1 ); 
    DalTlmm_ConfigGpio(hTlmm,GpioCfg,DAL_TLMM_GPIO_ENABLE); 
    {
      /*initialize the signal */
      qurt_anysignal_init (&pwrdb_trigger_timer_sig);
      qurt_anysignal_clear(&pwrdb_trigger_timer_sig, TIME_SYNC_SIG);
      
      /*changing qurt to ATS timer, not tested for PWRDB PRO version*/
      err = timer_def_osal(&pwrdb_trigger_timer, &pwrdb_always_on_timer_group, TIMER_NATIVE_OS_SIGNAL_TYPE, &pwrdb_trigger_timer_sig,TIME_SYNC_SIG); 
      if (err != TE_SUCCESS )
      {
        PWRDB_MSG_E1("PwrDB: ATS timer creation failed with error=%d.", err, 0, 0);
      }

      timer_set_64( &pwrdb_trigger_timer, 10, 0, T_MSEC );
      
      qurt_anysignal_wait(&pwrdb_trigger_timer_sig, TIME_SYNC_SIG);
      
      
      /*once you get a signal, clearing it is a good practice*/
      qurt_anysignal_clear(&pwrdb_trigger_timer_sig, TIME_SYNC_SIG);
    /* Now Program the GPIO to low and Pull the Signal Down */
    }
    GpioCfg = DAL_GPIO_CFG_OUT( gpio,PWRDB_TRIGGER_GPIO_FUNC,
                                0x1,0x0,0x111,0x0 ); 
    DalTlmm_ConfigGpio(hTlmm,GpioCfg,DAL_TLMM_GPIO_DISABLE);
  }
}

static void pwrdb_process_cmd_rpm_tlmm_write( pwrdb_cmd_type *c_ptr )
{
  uint16 command_id = pwrdb_update_and_get_cmd_number();
  uint16 execution_num = c_ptr->params.rpm_tlmm_write.pwrdb_rpm_execution_num;
  command_id = pwrdb_generate_command_id(command_id, c_ptr->cmd_id, execution_num);
  uint32 cfg = PWRDB_GPIO_CFG_OUT( c_ptr->params.rpm_tlmm_write.gpio_number,
                                 c_ptr->params.rpm_tlmm_write.function,
                                 c_ptr->params.rpm_tlmm_write.direction,
                                 c_ptr->params.rpm_tlmm_write.pull,
                                 c_ptr->params.rpm_tlmm_write.drive_strength );
  RPM_system_db_write(c_ptr->params.rpm_tlmm_write.pwrdb_rpm_event_mask,
                      PWRDB_GPIO_CFGn_ADDR(c_ptr->params.rpm_tlmm_write.gpio_number ),
                      c_ptr->params.rpm_tlmm_write.range,
                      cfg,
                      0xFFFFFFFF,
                     command_id,SYSTEMDB_MEMORY);
  /* If the Gpio is set to Output, Only then it is possible to set the Output to High/Low */
  if ( c_ptr->params.rpm_tlmm_write.enable == 1 )
  { 
    /* Check if the Function is 0, Function should be set to 0 for Bit Bang Mode */ 
    if ( c_ptr->params.rpm_tlmm_write.function == 0  )
    {
      RPM_system_db_write( c_ptr->params.rpm_tlmm_write.pwrdb_rpm_event_mask,
                           PWRDB_GPIO_IN_OUTn_ADDR(c_ptr->params.rpm_tlmm_write.gpio_number ),
                           c_ptr->params.rpm_tlmm_write.range,
                           c_ptr->params.rpm_tlmm_write.output_value ,
                           0xFFFFFFFF,
                           command_id,SYSTEMDB_MEMORY);
    }
  }
}

static void pwrdb_process_cmd_rpm_memory_peek( pwrdb_cmd_type *c_ptr )
{
  uint16 command_id = pwrdb_update_and_get_cmd_number();
  uint16 execution_num = c_ptr->params.rpm_memory_peek.pwrdb_rpm_execution_num;
  command_id = pwrdb_generate_command_id(command_id, c_ptr->cmd_id, execution_num);
  RPM_system_db_read(c_ptr->params.rpm_memory_peek.pwrdb_rpm_event_mask,
                      c_ptr->params.rpm_memory_peek.addr,
                      c_ptr->params.rpm_memory_peek.range,
                      command_id,SYSTEMDB_MEMORY);
}

static void pwrdb_process_cmd_rpm_memory_poke( pwrdb_cmd_type *c_ptr )
{
  uint16 command_id = pwrdb_update_and_get_cmd_number();
  uint16 execution_num = c_ptr->params.rpm_memory_poke.pwrdb_rpm_execution_num;
  command_id = pwrdb_generate_command_id(command_id, c_ptr->cmd_id, execution_num);
  RPM_system_db_write(c_ptr->params.rpm_memory_poke.pwrdb_rpm_event_mask,
                      c_ptr->params.rpm_memory_poke.addr,
                      c_ptr->params.rpm_memory_poke.range,
                      c_ptr->params.rpm_memory_poke.value,
                      0xFFFFFFFF,
                     command_id,SYSTEMDB_MEMORY);
}

static void pwrdb_process_cmd_rpm_spmi_write( pwrdb_cmd_type *c_ptr )
{
  uint32 address = 0;
  uint16 command_id = pwrdb_update_and_get_cmd_number();
  uint16 execution_num = c_ptr->params.rpm_spmi_write.pwrdb_rpm_execution_num;
  command_id = pwrdb_generate_command_id(command_id, c_ptr->cmd_id, execution_num);
  /* Pmic Address is 0x000( 0,1,4,5 for slave ID)XXXX( Offset Address ) */
  address   = (((c_ptr->params.rpm_spmi_write.slave_id)<<16)|(c_ptr->params.rpm_spmi_write.offset));
  RPM_system_db_write(c_ptr->params.rpm_spmi_write.pwrdb_rpm_event_mask,
                      address,
                      c_ptr->params.rpm_spmi_write.range,
                      c_ptr->params.rpm_spmi_write.value,
                      0xFFFFFFFF,
                      command_id,SYSTEMDB_PMIC);
}

#ifdef FEATURE_PWRDB_MPSS
/*===========================================================================

FUNCTION: PWRDB_GET_NEXT_LOG_NAME

DESCRIPTION
  Returns 
  1.) a string to keep as name for the log file that is to be saved. It 
      initially checks what is the last log file saved in PWRDB directory and 
      accordingly returns the next file name 
2.) Null if either directory cannot be created or opened.

PARAMETERS
  void
 
DEPENDENCIES
  None

RETURN VALUE
  Character string

SIDE EFFECTS
1.)  If PWRDB folder is not there in efs, it gets created
2.)  Any string returned by a previous call to this function is overwritten
===========================================================================*/
static char* pwrdb_get_next_log_name( void )
{
  EFSDIR           *efd        = NULL;
  struct fs_dirent *fsDentry   = NULL;
  char             *pwrdb_root = PWRDB_ROOT_DIR;
  char             *proto_name = PWRDB_LOG_PROTO_NAME; //Prototype Filename
  char             *log_ext    = PWRDB_LOG_EXT;        //Log Extension
  uint8            root_len;
  uint8            proto_len;
  static char      log_name[PWRDB_MAX_FILENAME_LEN];   //Return Filename
  uint8            log_len;
  char             temp[10];
  uint8            last_num = 0;
  uint8            i,j;
  
  // Opening Root Directory in EFS

  /* If the directory does not exist, attempt to create it */
  if (NULL == (efd = efs_opendir(pwrdb_root))) 
  {
      if (-1 == efs_mkdir(pwrdb_root, 0777))
      {
          pwrdb_log_message(PWRDB_ERROR_MESSAGE, " Could not create PWRDB directory in EFS."); 
          return NULL;
      }
      efd = efs_opendir(pwrdb_root);  //Open after creating dir
  }
  if( efd == NULL )
  {
    pwrdb_log_message(PWRDB_ERROR_MESSAGE, "Directory opening failed.\n");
    return NULL;
  } 
    else
  {
     last_num = 0;
     proto_len = strlen( proto_name );
     root_len = strlen(pwrdb_root);
     
     if((proto_len + root_len + 4 + 3) > PWRDB_MAX_FILENAME_LEN)
     {  // 4 is for extension. 3 is for '/', '\0', and one digit number
        pwrdb_log_message(PWRDB_ERROR_MESSAGE, "File Name Exceeds max length");
        return NULL;
     }
     
     // Loop for each file in directory
     // fsDentry gets each file name in its structure
     while(( fsDentry = efs_readdir ( efd ) ) != NULL)
     {   
         //current file name length
         log_len = strlen( fsDentry->d_name ); 
         
        /*Processes current file string only if its length is more than
          proto name length nd also it should contain ".pds" as extension */
         if( (log_len > proto_len+4)                     && 
             (fsDentry->d_name[log_len-4] == log_ext[0]) && 
             (fsDentry->d_name[log_len-3] == log_ext[1]) && 
             (fsDentry->d_name[log_len-2] == log_ext[2]) && 
             (fsDentry->d_name[log_len-1] == log_ext[3]) )
         {
            fsDentry->d_name[log_len-4] = '\0';  //Removing extension
            // Comparing with Prototype 
            for(i=0; i < proto_len && proto_name[i] == fsDentry->d_name[i]; i++);
         
            if(i == proto_len)
            {  // Found 1 more file with similar name 
               // Get the number present in the file name
               i = atoi((char *)(fsDentry->d_name + proto_len));
               if(i > last_num)
               {
                  last_num = i;
               }
            }
         }  
     }  
     efs_closedir(efd);   
  
     last_num++; // Next log file number
     
     /* Building full path log name */
     // Pwrdb root
     memcpy( log_name, pwrdb_root, root_len );
     memcpy( (char *)(log_name + root_len), "/", 1); 
     root_len++;  //Taking '/' into count
     
     // prototype name 'pwrdb_log_'
     memcpy( (char *)(log_name + root_len), proto_name, proto_len );
  
     // Converting number to string
     for(j=0; last_num; j++)
     {
        i = last_num % 10;
        last_num /= 10;
        temp[j] = (char)((int)'0' + i);
     }
     
     //Calculating Length to protect from overflowing
     if((proto_len + root_len + 4 + j + 2) > PWRDB_MAX_FILENAME_LEN)
     {  // 4 is for extension. 2 is for '/','\0', and j is for number of digits
        pwrdb_log_message(PWRDB_ERROR_MESSAGE, "File Name Exceeds max length");
        return NULL;
     }
     
     for(i=0;i<j;i++)
     {
        log_name[root_len+proto_len+i] = temp[j-i-1];
     }
     
     // Extension
     memcpy( (char *)(log_name + root_len + proto_len + j), log_ext, 4);
     log_name[root_len+ proto_len + j + 4] = '\0'; //closing string
     
     //Thus, log_name = "/pwrdb/pwrdb_log_xx.pdl"
     pwrdb_log_message(PWRDB_INFO_MESSAGE, log_name);
     PWRDB_MSG_H1("The string is %s",log_name);
  }
  
  return log_name;
} /* pwrdb_get_next_log_name() */

/*===========================================================================

FUNCTION PWRDB_WRITE_LOGS_TO_FS

DESCRIPTION
  Write the logs to the file system. If the file already exists in the file
  system then it is overwritten.

PARAMETERS
  filename - the name (and optionally path) for the file to write the 
             logs into.
             
DEPENDENCIES
  Debugger must be in LOGS_READY state, otherwise this function will force
  it to ERROR state.

RETURN VALUE
  none

SIDE EFFECTS
  Forces debugger to ERROR state if error occurs.
  
===========================================================================*/
void pwrdb_write_logs_to_fs( char* filename )
{
  int            fd;
  int            byte_count;
  int            written_bytes;
  pwrdb_res_type res;
  uint32 llen = pwrdb_log_wr_wrap ? pwrdb_log_size : pwrdb_log_write_ix;

  if (pwrdb_state != PWRDB_STATE_LOGS_READY)
  {
    /* logs not ready */
    pwrdb_error_str = "Not in LOGS_READY state to write logs to fs.";
    return;
  }

  fd = efs_open( filename, O_WRONLY | O_CREAT | O_TRUNC );

  if (fd < 0)
  {
    /* can't open file */
    pwrdb_error_str = "Can't open file to write logs to fs.";
    /* pwrdb_state_change( PWRDB_STATE_ERROR ); */
    pwrdb_state_change( PWRDB_STATE_RUNNING );
    return;
  }

  /* loop filing buffer from logs and writing to file,
     errors jump out of loop (and function)
   */
  do
  {
    byte_count = (int) pwrdb_pack_log_items( pwrdb_fs_rw_buf, 
                                             PWRDB_FS_RW_BUF_SIZE, 
                                             pwrdb_log,
                                             llen,
                                             pwrdb_log_write_ix,
                                             &res );

    if ( res == PWRDB_RES_OK_CONTINUE ||
         res == PWRDB_RES_OK_DONE )
    {
      written_bytes = efs_write( fd, pwrdb_fs_rw_buf, byte_count );
      
      if (written_bytes < byte_count)
      {
        /* error writing to file */
        efs_close( fd);
        pwrdb_error_str = "Error writing logs to fs.";
        /* VK: why should the state be changed if a fs log write is failed? */
        /* pwrdb_state_change( PWRDB_STATE_ERROR ); */
        pwrdb_state_change( PWRDB_STATE_RUNNING );
        return;
      }
    }
    else
    {
      /* error packing log */
      /* VK: We got an unsupported log item, Why shld the state be changed? */
      efs_close( fd);
      pwrdb_error_str = "Error packing logs to write to fs.";
      /* pwrdb_state_change( PWRDB_STATE_ERROR ); */
      pwrdb_state_change( PWRDB_STATE_RUNNING );
      return;
    }
  } while ( res == PWRDB_RES_OK_CONTINUE );

  efs_close( fd );
}
#endif
#endif


static void pwrdb_process_cmd_rpm_end_of_cmd( pwrdb_cmd_type *c_ptr )
{
  uint16 command_id = pwrdb_update_and_get_cmd_number();
  uint16 execution_num = c_ptr->params.rpm_end_of_cmd.pwrdb_rpm_execution_num;
  command_id = pwrdb_generate_command_id(command_id, c_ptr->cmd_id, execution_num) | (1 << 15);
  RPM_system_db_end_of_commands();
}

static void pwrdb_process_cmd_clk_log_state ( pwrdb_cmd_type *c_ptr )
{
  DalDeviceHandle *hDaldev;
  uint32 nFlags = 0;
  if (c_ptr->params.clk_log_state.measureFreq) {
    nFlags = CLOCK_LOG_STATE_CLOCK_FREQUENCY;
  }
  if (DAL_DeviceAttach(DALDEVICEID_CLOCK, &hDaldev) == DAL_SUCCESS) 
  { 
    if (DAL_SUCCESS == DalClock_LogState(hDaldev, pwrdb_ulog_handle, nFlags)) {
      PWRDB_MSG_H0("Logging clock states to Ulog handle successful.");
      pwrdb_log_to_ulog( c_ptr->cmd_id , (uint64)DAL_SUCCESS);
    }
    else {
      PWRDB_MSG_E0("Logging Clock states to Ulog failed.");
    }
  }
  else {
    PWRDB_MSG_E0("Failed attaching Dal Device Handle for Clock Log State.");
  }
}

static void pwrdb_process_cmd_rpm_clk_log_state( pwrdb_cmd_type *c_ptr )
{
  uint16 command_id = pwrdb_update_and_get_cmd_number();
  uint16 execution_num = c_ptr->params.rpm_clk_log_state.pwrdb_rpm_execution_num;
  command_id = pwrdb_generate_command_id(command_id, c_ptr->cmd_id, execution_num);
  RPM_system_db_read(c_ptr->params.rpm_clk_log_state.pwrdb_rpm_event_mask,
                      0,
                      0,
                     command_id,SYSTEMDB_CLK);
}

static void pwrdb_process_cmd_rpm_spmi_read( pwrdb_cmd_type *c_ptr )
{
  uint32 address = 0;
  uint16 command_id = pwrdb_update_and_get_cmd_number();
  uint16 execution_num = c_ptr->params.rpm_spmi_read.pwrdb_rpm_execution_num;
  command_id = pwrdb_generate_command_id(command_id, c_ptr->cmd_id, execution_num);
  /* Pmic Address is 0x000( 0,1,4,5 for slave ID)XXXX( Offset Address ) */
  address = (((c_ptr->params.rpm_spmi_read.slave_id)<<16)|(c_ptr->params.rpm_spmi_read.offset));
  RPM_system_db_read(c_ptr->params.rpm_spmi_read.pwrdb_rpm_event_mask,
                      address,
                      c_ptr->params.rpm_spmi_read.range,
                      command_id,SYSTEMDB_PMIC );
}

static void pwrdb_process_cmd_rpm_tlmm_read( pwrdb_cmd_type *c_ptr )
{
  uint16 command_id = pwrdb_update_and_get_cmd_number();
  uint16 execution_num = c_ptr->params.rpm_tlmm_read.pwrdb_rpm_execution_num;
  command_id = pwrdb_generate_command_id(command_id, c_ptr->cmd_id, execution_num);
  RPM_system_db_read(c_ptr->params.rpm_tlmm_read.pwrdb_rpm_event_mask,
                      c_ptr->params.rpm_tlmm_read.gpio_number,
                      c_ptr->params.rpm_tlmm_read.range,
                     command_id,SYSTEMDB_GPIO);
}

static void pwrdb_process_cmd_rpm_flush_cmds ( pwrdb_cmd_type *c_ptr )
{
  uint16 comand_id = pwrdb_update_and_get_cmd_number();
  comand_id = ((comand_id<<8)|c_ptr->cmd_id);
  RPM_system_db_clearall();
  
}

/*===========================================================================

FUNCTION PWRDB_PROCESS_CMD_RPM_DUMP

===========================================================================*/
static void pwrdb_process_cmd_rpm_dump( pwrdb_cmd_type *c_ptr )
{
  uint16 command_id = pwrdb_update_and_get_cmd_number();
  uint16 execution_num = c_ptr->params.rpm_dump.pwrdb_rpm_execution_num;

  command_id = pwrdb_generate_command_id(command_id, c_ptr->cmd_id, execution_num);
  
  RPM_system_db_read( c_ptr->params.rpm_dump.pwrdb_rpm_event_mask,  
                      0,
                      0,
                      command_id,
                      SYSTEMDB_RPMDUMP);
}

/*===========================================================================

FUNCTION PWRDB_PROCESS_CMD_ERR_FATAL

===========================================================================*/
static void pwrdb_process_cmd_rpm_err_fatal( pwrdb_cmd_type *c_ptr )
{
  uint16 command_id = pwrdb_update_and_get_cmd_number();
  uint32 param1 = 0;
  uint16 execution_num = c_ptr->params.rpm_err_fatal.pwrdb_rpm_execution_num;
  
  param1  = c_ptr->params.rpm_err_fatal.param1;
  
  command_id = pwrdb_generate_command_id(command_id, c_ptr->cmd_id, execution_num);
  
  RPM_system_db_read( c_ptr->params.rpm_err_fatal.pwrdb_rpm_event_mask,  
                      param1,
                      0,
                      command_id,
                      SYSTEMDB_ERRFATAL_CMD);
}

/*===========================================================================

FUNCTION PWRDB_PROCESS_CMD_RPM_DOWNSAMPLE

===========================================================================*/
static void pwrdb_process_cmd_rpm_downsample( pwrdb_cmd_type *c_ptr )
{
  uint16 command_id = pwrdb_update_and_get_cmd_number();
  uint32 downsample = 0;
  
  downsample  = c_ptr->params.rpm_downsample.downsample;
  
  command_id = pwrdb_generate_command_id(command_id, c_ptr->cmd_id, 1);
  
  RPM_system_db_read( 1,  
                      downsample,
                      0,
                      command_id,
                      SYSTEMDB_DOWNSAMPLE);
}

//#endif /* #ifdef FEATURE_PWRDB_MPSS */

/*===========================================================================

FUNCTION pwrdb_process_cmd_clk_busy_wait


DESCRIPTION
   This function pauses the the execution of a thread for a specified time.

===========================================================================*/
static void pwrdb_process_cmd_clk_busy_wait(pwrdb_cmd_type *c_ptr)
{
  uint32 usec = c_ptr->params.clk_busy_wait.usec;
  //if usec >FFFFFFFF??
  busywait(usec);

}


/*===========================================================================

FUNCTION PWRDB_LOG_EVENT

DESCRIPTION
  Put a record for the event in the log.
  
PARAMETERS
  source,id - the source and id that identify the event to be logged

RETURN VALUE
  None

SIDE EFFECTS
  None
  
===========================================================================*/
static void pwrdb_log_event( uint32 source, uint32 id )
{
  /* add the event to the log */
  pwrdb_log_type *li_ptr = pwrdb_next_log_item();

  if (li_ptr != NULL)
  {
      li_ptr->log_id                       = PWRDB_LOG_EVENT;
      li_ptr->data.event.source            = source;
      li_ptr->data.event.id                = id;
    }
  }

/*===========================================================================

FUNCTION PWRDB_PROCESS_COMMANDS

DESCRIPTION
  This function is called to process the list of commands associated with
  an event. This happens is response to pwrdb receiving that event.
  
DEPENDENCIES
  None.

RETURN VALUE
  None.

SIDE EFFECTS
  Depends on commands.
  
===========================================================================*/
static void pwrdb_process_commands( pwrdb_command_ll_type  *commands, 
                                    boolean                 in_task )
{
  boolean         done = FALSE;
  pwrdb_cmd_type *c_ptr;

  /* Loop though the commands. The are 3 conditions that could 
     termintate the loop:
     1. All the commands have been processed - commands == NULL.
     2. Hit PWRDB_CMD_END_OF_CMDS.
     3. Hit PWRDB_START_TASK_CMDS and not in task.
  */
  while (commands != NULL && !done)
  {
    c_ptr = &(commands->command);

    switch ( c_ptr->cmd_id )
    {
    /* Meta Commands */
    case PWRDB_CMD_NULL_CMD:
      /* unexpected, but do nothing */
      break;

    case PWRDB_CMD_START_TASK_CMDS:
      if (!in_task)
      {
        /* tell task to start processing at next command */
        pwrdb_task_cmd_send( PWRDB_TASK_CMD_PROCESS_SCRIPT, 
                             (uint32)(commands->next),
                             0 ); 
        done = TRUE;
      }
      break;

    case PWRDB_CMD_END_OF_CMDS:
      done = TRUE;
    break;

    case PWRDB_CMD_ENABLE_PRO:
      pwrdb_process_cmd_enable_pro( c_ptr );
      break;

    /* non-Meta Commands */
    case PWRDB_CMD_START_TIMER:
     pwrdb_process_cmd_start_timer( c_ptr );
    break;

    case PWRDB_CMD_TLMM_GET_CURR_CONFIG:
     pwrdb_process_cmd_tlmm_get_curr_config( c_ptr );
    break;


    case PWRDB_CMD_TLMM_IS_LOCKED:
     pwrdb_process_cmd_tlmm_is_locked( c_ptr );
    break;


    case PWRDB_CMD_CLK_GET_CLK_EN:
       pwrdb_process_cmd_clk_get_clk_en( c_ptr );
    break;

    case PWRDB_CMD_CLK_GET_CLK_FREQ:
      pwrdb_process_cmd_clk_get_clk_freq( c_ptr );
    break;

    case PWRDB_CMD_CLK_OUTPUT_GPIO:
      pwrdb_program_clk_test_reg( c_ptr->params.clk_output_gpio.reg_value );
    break;

    case PWRDB_CMD_CLK_BUSY_WAIT:
      pwrdb_process_cmd_clk_busy_wait( c_ptr );
    break;

    case PWRDB_CMD_CLK_LOG_STATE:
      pwrdb_process_cmd_clk_log_state( c_ptr );
    break;

    case PWRDB_CMD_RPM_CLK_LOG_STATE:
      pwrdb_process_cmd_rpm_clk_log_state(c_ptr);
    break;

    case PWRDB_CMD_RPM_SPMI_READ:
      pwrdb_process_cmd_rpm_spmi_read( c_ptr );
    break;

    case PWRDB_CMD_RPM_TLMM_READ:
      pwrdb_process_cmd_rpm_tlmm_read(c_ptr);
    break;

    case PWRDB_CMD_RPM_DUMP:
      pwrdb_process_cmd_rpm_dump( c_ptr );
    break;
    
    case PWRDB_CMD_RPM_ERR_FATAL:
      pwrdb_process_cmd_rpm_err_fatal( c_ptr );
    break;
    
    case PWRDB_CMD_RPM_DOWNSAMPLE:
      pwrdb_process_cmd_rpm_downsample( c_ptr );
    break;
    
    case PWRDB_CMD_TLMM_GET_INACT_CONFIG:
      pwrdb_process_cmd_tlmm_get_inact_config( c_ptr );
    break;

    case PWRDB_CMD_RPM_END_OF_CMD:
      pwrdb_process_cmd_rpm_end_of_cmd(c_ptr);
    break; 

    case PWRDB_CMD_RPM_FLUSH_CMDS:
      pwrdb_process_cmd_rpm_flush_cmds( c_ptr );
    break;

#ifdef PWRDB_PRO            
    case PWRDB_CMD_TLMM_SET_CURR_CONFIG:
        pwrdb_process_cmd_tlmm_set_curr_config( c_ptr );
    break;
         
    case PWRDB_CMD_TLMM_SET_INACT_CONFIG:
        pwrdb_process_cmd_tlmm_set_inact_config( c_ptr );
    break;

    case PWRDB_CMD_TLMM_OUTPUT:
      pwrdb_process_cmd_tlmm_output( c_ptr );
    break;

    case PWRDB_CMD_TLMM_INPUT:
      pwrdb_process_cmd_tlmm_input( c_ptr );
    break;

    case PWRDB_CMD_TLMM_GET_PIN_STATUS:
      pwrdb_process_cmd_tlmm_get_pin_status( c_ptr );
    break;

    case PWRDB_CMD_TLMM_LOCK:
      pwrdb_process_cmd_tlmm_lock( c_ptr );
    break;

    case PWRDB_CMD_TLMM_UNLOCK:
      pwrdb_process_cmd_tlmm_unlock( c_ptr );
    break;

    case PWRDB_CMD_PEEK8:
      pwrdb_process_cmd_peek8( c_ptr );
    break;

    case PWRDB_CMD_PEEK16:
      pwrdb_process_cmd_peek16( c_ptr );
    break;

    case PWRDB_CMD_PEEK32:
      pwrdb_process_cmd_peek32( c_ptr );
    break;

    case PWRDB_CMD_PEEK32_RANGE:
      pwrdb_process_cmd_peek32_range( c_ptr );
    break;

    case PWRDB_CMD_POKE32_RANGE:
        pwrdb_process_cmd_poke32_range( c_ptr );
    break;

    case PWRDB_CMD_POKE8_M:
       pwrdb_process_cmd_poke8_m( c_ptr );
    break;

    case PWRDB_CMD_POKE16_M:
       pwrdb_process_cmd_poke16_m( c_ptr );
    break;

    case PWRDB_CMD_POKE32_M:
       pwrdb_process_cmd_poke32_m( c_ptr );
    break;

    case PWRDB_CMD_CLK_SET_CLK_EN:
       pwrdb_process_cmd_clk_set_clk_en( c_ptr );
    break;


    case PWRDB_CMD_NPA_ISSUE_REQUIRED_REQUEST:
      pwrdb_process_cmd_npa_issue_required_request( c_ptr );
    break;

    case PWRDB_CMD_NPA_MODIFY_REQUIRED_REQUEST:
      pwrdb_process_cmd_npa_modify_required_request( c_ptr );
    break;
  #if 0
    case PWRDB_CMD_STRING:
      pwrdb_process_cmd_string(c_ptr);
    break;

    case PWRDB_CMD_DATA3_STRING:
      pwrdb_process_cmd_data3_string(c_ptr);
    break;
  #endif
    case PWRDB_CMD_NPA_ISSUE_IMPULSE_REQUEST:
      pwrdb_process_cmd_npa_issue_impulse_request( c_ptr );
    break;

    case PWRDB_CMD_NPA_ISSUE_ISOC_REQUEST:
      pwrdb_process_cmd_npa_issue_isoc_request( c_ptr );
    break;

    case PWRDB_CMD_NPA_ISSUE_LIMIT_MAX_REQUEST:
      pwrdb_process_cmd_npa_issue_limit_max_request( c_ptr );
    break;

    case PWRDB_CMD_NPA_COMPLETE_REQUEST:
      pwrdb_process_cmd_npa_complete_request( c_ptr );
    break;

    case PWRDB_CMD_NPA_QUERY_BY_NAME:
      pwrdb_process_cmd_npa_query_by_name( c_ptr );
    break;

    case PWRDB_CMD_CONFIGURE_HW_EVENTS_MUX:
      pwrdb_process_cmd_configure_hw_events_mux( c_ptr );
    break;

    case PWRDB_CMD_TRIGGER_LOG_SIGNALS:
      pwrdb_process_cmd_trigger_log_signals( c_ptr );
    break;

    case PWRDB_CMD_RPM_MEMORY_PEEK :
      pwrdb_process_cmd_rpm_memory_peek(c_ptr);
    break;

    case PWRDB_CMD_RPM_MEMORY_POKE:
      pwrdb_process_cmd_rpm_memory_poke(c_ptr);
     break;

    case PWRDB_CMD_RPM_SPMI_WRITE:
      pwrdb_process_cmd_rpm_spmi_write( c_ptr );
    break;


    case PWRDB_CMD_RPM_TLMM_WRITE:
       pwrdb_process_cmd_rpm_tlmm_write(c_ptr);
    break;

 #ifdef FEATURE_PWRDB_MPSS
    case PWRDB_CMD_STOP_AND_LOG_TO_FS:
      /* Already it is in proc_event state. Changing the state to logs_ready  */
      pwrdb_state_change( PWRDB_STATE_LOGS_READY );

      /* Check if this is called from task context or ISR context, which is based on the perl file calls */
      if (!in_task)
      {
              /* push this processing to the task */
              pwrdb_task_cmd_send( PWRDB_TASK_CMD_WRITE_LOGS_TO_FS, 0, 0 );
      }
      else
      {
             log_name = pwrdb_get_next_log_name();
              /* If it is already called from task context */
             if(log_name != NULL)
             {
                 pwrdb_write_logs_to_fs(log_name);
             }
      }
      done = TRUE;
      break;
 #endif  
#endif /* #ifdef PWRDB_PRO */

    default:
        PWRDB_MSG_E1("Unknown command %i", c_ptr->cmd_id);
        break;
    } /* switch */
    commands = commands->next;
  } /* while */
}



/*===========================================================================

FUNCTION PWRDB_PROCESS_EVENT

DESCRIPTION
  
  NOTE: This function may be called often and may be called from ISR context.
  It is important that this function executes very quickly especially in the
  case where no script is run.
   
DEPENDENCIES


RETURN VALUE


SIDE EFFECTS

  
===========================================================================*/
static void pwrdb_process_event( uint32 source, uint32 id )
{
  boolean               OK_to_process = FALSE;
  pwrdb_event_ll_type  *event_to_process = NULL;
  uint64                logopt = 0;
  /* Only process event if we're not in the middle of processing something
     else.
   */
  logopt = ((uint64)((id&0xF)<<16)|(source&0xFFFF));
  OK_to_process = pwrdb_state_check_and_change( PWRDB_STATE_RUNNING,
                                                PWRDB_STATE_PROC_EVENT );
  if ( OK_to_process == TRUE )
  {
    /* Check for dropped events */
    if (pwrdb_dropped_event_count != 0)
    {
      /* add log item for dropped events */
      pwrdb_dropped_event_count = 0;
    }
    
    event_to_process = pwrdb_find_existing_event( source, id );
    if( event_to_process != NULL )
    {
      if( pwrdb_log_state == PWRDB_LOG_ON )
      {
        if( pwrdb_log_format != PWRDB_LOG_TO_RAM )
        {
          pwrdb_log_function( PWRDB_CMD_EVENT, logopt );
        }
        else
        {
          pwrdb_log_event( source, id );
        }
      }
      
      if( event_to_process->pwrdb_cmds != NULL )
      {
        pwrdb_process_commands( event_to_process->pwrdb_cmds, FALSE );
      }
    }
    
    /* Update state */   
    qmutex_lock( pwrdb_mutex );
    if ( pwrdb_state == PWRDB_STATE_PROC_EVENT )
    {
      pwrdb_state_change( PWRDB_STATE_RUNNING );
    }
    else if ( pwrdb_state == PWRDB_STATE_PROC_EVENT_STOP_PENDING )
    {
      pwrdb_state_change( PWRDB_STATE_LOGS_READY );
    }
    qmutex_unlock( pwrdb_mutex );
  }
  else /* must be not OK_to_process */
  {
    pwrdb_dropped_event_count++;
  }
}

/*===========================================================================

FUNCTION PWRDB_PROCESS_RESET_REQ

DESCRIPTION
  Process the reset request packet when it is received over the diag
  connection.
  
DEPENDENCIES
  This function should be registered with diag to be called when a
  PWRDB_DIAG_PKT_RESET packet is send to PWRDB.

RETURN VALUE
  Pointer to a response packet.

SIDE EFFECTS
  PWRDB is reset.
  
===========================================================================*/
PACKED void *pwrdb_process_reset_req(PACKED void *req_pkt_ptr, uint16 pkt_len)
{
  pwrdb_diag_pkt_reset_rsp_type *rsp_ptr = NULL;

  /* Allocate response packet */
  rsp_ptr = (pwrdb_diag_pkt_reset_rsp_type *) diagpkt_subsys_alloc (
                                                DIAG_SUBSYS_PWRDB,
                                                (PWRDB_DIAG_PKT_RESET | PWRDB_DIAG_PKT_CPU_ID),
                                                sizeof (pwrdb_diag_pkt_reset_rsp_type) );
  if(rsp_ptr == NULL)
    return NULL;

  /* Reset */
  pwrdb_state_change( PWRDB_STATE_READY_FOR_SCRIPTS );
  pwrdb_reset();

  rsp_ptr->status = PWRDB_RSP_SUCCESS;
  return rsp_ptr;
}

/*===========================================================================

FUNCTION PWRDB_PROCESS_VERSION_REQ

DESCRIPTION
  Process the version request packet when it is received over the diag
  connection.
  
DEPENDENCIES
  This function should be registered with diag to be called when a
  PWRDB_DIAG_PKT_VER packet is send to PWRDB.

RETURN VALUE
  Pointer to a response packet containing the PWRDB version info.

SIDE EFFECTS
  None.
  
===========================================================================*/
PACKED void *pwrdb_process_version_req(PACKED void *req_pkt_ptr, uint16 pkt_len)
{
  pwrdb_diag_pkt_ver_rsp_type *rsp_ptr = NULL;
  DalDeviceHandle             *phChipInfo;
  DalChipInfoIdType            eId;

  /* Send response */
  rsp_ptr = (pwrdb_diag_pkt_ver_rsp_type *) diagpkt_subsys_alloc (
                                              DIAG_SUBSYS_PWRDB,
                                              (PWRDB_DIAG_PKT_VER | PWRDB_DIAG_PKT_CPU_ID),
                                              sizeof (pwrdb_diag_pkt_ver_rsp_type) );

  if(rsp_ptr == NULL)
    return NULL;

  // To do - use same handle used at init time check

  if (DAL_DeviceAttach(DALDEVICEID_CHIPINFO, &phChipInfo) == DAL_SUCCESS)
  {
    DalDevice_Open(phChipInfo, DAL_OPEN_SHARED);
    DalChipInfo_GetChipId(phChipInfo, &eId);

    /*-----------------------------------------------------------------------*/
    /* Close the connection and detach.                                      */
    /*-----------------------------------------------------------------------*/

    DalDevice_Close(phChipInfo);
    DAL_DeviceDetach(phChipInfo);
  }
  else
  {
    eId = DALCHIPINFO_ID_UNKNOWN;
  }

  /* Populate the data in the response */
  rsp_ptr->major_version = PWRDB_MAJOR_VERSION;
  rsp_ptr->minor_version = PWRDB_MINOR_VERSION;
  rsp_ptr->msm_id = (uint32)eId;

  return rsp_ptr;
}

/*===========================================================================

FUNCTION PWRDB_PROCESS_SCRIPT_REQ

DESCRIPTION
  Process the script packet when it is received over the diag connection. 
  This function calls pwrdb_unpack_script_commands() to get the commands
  out of the diag packet and put them in the internal array.
  
DEPENDENCIES
  This function should be registered with diag to be called when a
  PWRDB_DIAG_PKT_SCRIPT packet is send to PWRDB.

RETURN VALUE
  Pointer to a response packet.

SIDE EFFECTS
  None.
  
===========================================================================*/
PACKED void *pwrdb_process_script_req(PACKED void *req_pkt_ptr, uint16 pkt_len)
{
  pwrdb_diag_pkt_script_req_type *req_ptr = (pwrdb_diag_pkt_script_req_type *) req_pkt_ptr;
  pwrdb_diag_pkt_script_rsp_type *rsp_ptr = NULL;
  pwrdb_res_type                  proc_res;
  uint32                          dummy;

  /* Get set up to send response */
  rsp_ptr = (pwrdb_diag_pkt_script_rsp_type *) diagpkt_subsys_alloc (
                                                 DIAG_SUBSYS_PWRDB,
                                                 (PWRDB_DIAG_PKT_SCRIPT | PWRDB_DIAG_PKT_CPU_ID),
                                                 sizeof(pwrdb_diag_pkt_script_rsp_type) );

  if(rsp_ptr == NULL)
    return NULL;
    
  /* Check we are in the right state to process this */
  if (pwrdb_state != PWRDB_STATE_READY_FOR_SCRIPTS)
  {
    /* not in right state, respond with error */
    rsp_ptr->status = PWRDB_RSP_ERROR;
  }
  else
  {
    pwrdb_init_ram_log();

    /* Need to unpack the packet into our arrays */
    proc_res = pwrdb_unpack_script_commands( &pwrdb_events,
                                             PWRDB_NUM_SCRIPT_COMMANDS,
                                             (uint8*)(req_ptr->cmds), 
                                             req_ptr->cmds_len,
                                             &dummy,
                                             &pwrdb_command_count );

    if (proc_res == PWRDB_RES_FATAL || proc_res == PWRDB_RES_ERROR)
    {
      /* something went wrong */
      pwrdb_error_str = "Error processing script packet";
      pwrdb_state_change( PWRDB_STATE_INIT );
      rsp_ptr->status = PWRDB_RSP_ERROR;
    }
    else
    {
      rsp_ptr->status = PWRDB_RSP_SUCCESS;
    }
  }

  return rsp_ptr;
}

/*===========================================================================

FUNCTION PWRDB_PROCESS_LOG_REQ

DESCRIPTION
  Process the log request packet when it is received over the diag
  connection.

  The log stored in PWRDB may contain more information than can fit in a 
  single diag packet. In this case multiple requests will be required to get
  the entire log. The status field in the response packets indicates 
  whether there is additional information in the log that did not fit in 
  this packet.
  
DEPENDENCIES
  This function should be registered with diag to be called when a
  PWRDB_DIAG_PKT_LOG packet is send to PWRDB.
  
RETURN VALUE
  Pointer to a response packet containing the log.

SIDE EFFECTS
  Advances the log read pointer.
  
===========================================================================*/
PACKED void *pwrdb_process_log_req(PACKED void *req_pkt_ptr, uint16 pkt_len)
{
  pwrdb_diag_pkt_log_rsp_type *rsp_ptr = NULL;
  uint32                       log_len;
  pwrdb_res_type               res;

  /* Set up response packet - start large we may shorten later */
  rsp_ptr = (pwrdb_diag_pkt_log_rsp_type *) diagpkt_subsys_alloc (
                                              DIAG_SUBSYS_PWRDB,
                                              (PWRDB_DIAG_PKT_LOG | PWRDB_DIAG_PKT_CPU_ID),
                                              PWRDB_INITIAL_LOG_PKT_SIZE + FPOS(pwrdb_diag_pkt_log_rsp_type, log));

  if(rsp_ptr == NULL)
    return NULL;

  /* start out assuming something went wrong */
  rsp_ptr->status = PWRDB_RSP_ERROR;
  log_len         = 0;

  if( pwrdb_log_format != PWRDB_LOG_TO_RAM  )
  {
    rsp_ptr->status = PWRDB_RSP_SUCCESS;
  }
  else 
  {
  if ( pwrdb_state == PWRDB_STATE_LOGS_READY )
  {
    /* If we wrapped then the length is the whole log, otherwise the length
       is only up to the write pointer. */
    uint32 llen = pwrdb_log_wr_wrap ? pwrdb_log_size : pwrdb_log_write_ix;

    log_len = pwrdb_pack_log_items( (uint8*)(rsp_ptr->log), 
                                    PWRDB_INITIAL_LOG_PKT_SIZE, 
                                    pwrdb_log,
                                    llen,
                                    pwrdb_log_write_ix,
                                    &res );
    
    if ( res == PWRDB_RES_OK_DONE )
    {
      rsp_ptr->status = PWRDB_RSP_SUCCESS;
    }
    else if ( res == PWRDB_RES_OK_CONTINUE )
    {
      rsp_ptr->status = PWRDB_RSP_OK_PARTIAL;
    }
  }
  }
  /* Shorten the packet since we probably started out too big */
  rsp_ptr->log_len = log_len;
  diagpkt_shorten( rsp_ptr, FPOS(pwrdb_diag_pkt_log_rsp_type, log) + log_len );

  return rsp_ptr;
}

#ifdef PWRDB_PRO
#ifdef FEATURE_PWRDB_MPSS
/*===========================================================================

FUNCTION PWRDB_LOG_TO_FS_REQ

DESCRIPTION
  Process the log to filesstem request packet when it is received over the diag
  connection by writing the contents of the PWRDB log to the filesystem.
  
DEPENDENCIES
  This function should be registered with diag to be called when a
  PWRDB_DIAG_PKT_LOG_TO_MEM packet is send to PWRDB.

RETURN VALUE
  Pointer to a response packet.

SIDE EFFECTS
  Log is written into the file system.
  
===========================================================================*/
PACKED void *pwrdb_process_log_to_fs_req(PACKED void *req_pkt_ptr, uint16 pkt_len)
{
  pwrdb_diag_pkt_log_to_mem_rsp_type *rsp_ptr = NULL;

  /* Set up response packet */
  rsp_ptr = (pwrdb_diag_pkt_log_to_fs_rsp_type *) diagpkt_subsys_alloc (
                                                    DIAG_SUBSYS_PWRDB,
                                                    (PWRDB_DIAG_PKT_LOG_TO_FS | PWRDB_DIAG_PKT_CPU_ID),
                                                    sizeof(pwrdb_diag_pkt_log_to_fs_rsp_type) );

  if(rsp_ptr == NULL)
    return NULL;
  if( pwrdb_log_format != PWRDB_LOG_TO_RAM )
  {
    rsp_ptr->status = PWRDB_RSP_SUCCESS;
  }
  else
  {
  if ( pwrdb_state == PWRDB_STATE_LOGS_READY )
  {
    /* push this processing to the task */
    pwrdb_task_cmd_send( PWRDB_TASK_CMD_WRITE_LOGS_TO_FS, 0, 0 );
    rsp_ptr->status = PWRDB_RSP_SUCCESS;
  }
  else
  {
    rsp_ptr->status = PWRDB_RSP_ERROR;
  }
  }
  return rsp_ptr;
}


/*===========================================================================

FUNCTION PWRDB_CHECK_FS_FOR_SCRIPT

DESCRIPTION
  Looks in file system for a file matching PWRDB_DEFAULT_SCRIPT_FILENAME.
  If the file is found it is read in and processed as a script.
  
DEPENDENCIES
  None

RETURN VALUE
  None

SIDE EFFECTS
  If file is present script is loaded.
  If script is loaded the state is changed to RUNNING otherwise the state
  is changed to READY_FOR_SCRIPTS.
  
===========================================================================*/

void pwrdb_check_fs_for_script( const char *path )
{
  int                  fd;
  uint32               read_size;
  uint32               buf_ix;
  uint32               proc_bytes;
  pwrdb_res_type       proc_res;

  if((pwrdb_state != PWRDB_STATE_READY_FOR_SCRIPTS) && (pwrdb_state != PWRDB_STATE_RUNNING) )
  {
    return;
  }

  fd = efs_open( path, O_RDONLY );

  if (fd < 0)
  {
    PWRDB_MSG_H0("No pwrdb command script in EFS.");
    return;
  }
    
  buf_ix = 0;

  for (;;) /* loop is exited on eof or error */
  {
    read_size = (uint32)efs_read( fd,
                                   &(pwrdb_fs_rw_buf[buf_ix]),
                                   (fs_size_t) (PWRDB_FS_RW_BUF_SIZE-buf_ix) );
    if (read_size == 0) break; /* eof */

    pwrdb_state_change( PWRDB_STATE_PARSING_FS_COMMANDS);

    pwrdb_init_ram_log();
    
    proc_res = pwrdb_unpack_script_commands(  &pwrdb_events,
                                              PWRDB_NUM_SCRIPT_COMMANDS,
                                              pwrdb_fs_rw_buf,
                                              read_size+buf_ix,
                                              &proc_bytes,
                                              &pwrdb_command_count );

    if (proc_res == PWRDB_RES_OK)
    {
      /* must have processed whole buffer, start again at start */
      buf_ix = 0;
    }
    else if (proc_res == PWRDB_RES_PARTIAL)
    {
      /* end of buffer contains partial command, need to
         move to front of buffer before reading more data
       */
      uint32 end = read_size + buf_ix;
      uint32 ix  = proc_bytes;
      for (buf_ix = 0; ix < end; buf_ix++, ix++)
      {
        pwrdb_fs_rw_buf[buf_ix] = pwrdb_fs_rw_buf[ix];
      }
    }
    else if( proc_res == PWRDB_RES_FATAL)
    {
      /* Either Received an unsupported command */
     /* something went wrong, bail */
      pwrdb_error_str = "Error processing PCS file";
      PWRDB_MSG_E0("Error processing PCS file.");
      pwrdb_state_change( PWRDB_STATE_INIT );
      (void) efs_close( fd );
      pwrdb_reset();
      pwrdb_state_change( PWRDB_STATE_READY_FOR_SCRIPTS );
      return;
    }
    else
    {
      if( !pwrdb_command_count )
      {
        /* Pwrdb events are not started */
        pwrdb_state_change( PWRDB_STATE_READY_FOR_SCRIPTS );
        return;
      }
    }
  }
  
  /* close the file (don't care if this works or not) */
  (void) efs_close( fd );

  PWRDB_MSG_H0("PCS loaded from EFS.");

  pwrdb_state_change( PWRDB_STATE_RUNNING );

  pwrdb_process_event( PWRDB_EVT_SRC_PWRDB_INTERNAL,
                       PWRDB_INT_EVT_ID_ENTER_RUNNING );
}

/*===========================================================================

FUNCTION pwrdb_process_file_read_req

DESCRIPTION
  Request from Diag to read a pds file from the FS, Raise a req to
  Pwrdb task to read the file
 
DEPENDENCIES
  This function should be registered with diag to be called when a
  PWRDB_DIAG_PKT_READ_FILE is called to DIAG.

RETURN VALUE
  Pointer to a response packet.

SIDE EFFECTS
  PWRDB command script for event is executed if present and PWRDB is in
  running state.
  
===========================================================================*/

PACKED void *pwrdb_process_file_read_req( PACKED void *req_pkt_ptr, uint16 pkt_len )
{
  /* req_pkt_ptr will have the file name */
  pwrdb_process_file_read_rsp_type *rsp_ptr = NULL;

  /* ToDo: Need to be implement the flexible filename  */
  /* Set up response packet */
  rsp_ptr = (pwrdb_process_file_read_rsp_type *) diagpkt_subsys_alloc (
                                                    DIAG_SUBSYS_PWRDB,
                                                    (PWRDB_DIAG_PKT_READ_FILE | PWRDB_DIAG_PKT_CPU_ID),
                                                    sizeof(pwrdb_process_file_read_rsp_type) );

  
  if(rsp_ptr == NULL)
    return NULL;
  if( (pwrdb_state != PWRDB_STATE_READY_FOR_SCRIPTS) && (pwrdb_state != PWRDB_STATE_RUNNING) )
  {
    /* Can we add an item to the Cmd Queue and then process it after we move to Running state? */
    rsp_ptr->status = PWRDB_RSP_ERROR;
  }
  else
  {
    pwrdb_task_cmd_send(PWRDB_TASK_CMD_READ_FILE_FROM_FS,0,0);
    rsp_ptr->status = PWRDB_RSP_SUCCESS;
  }
 
  return rsp_ptr;
}
#endif /* #ifdef FEATURE_PWRDB_MPSS */
#endif /* #ifdef PWRDB_PRO */

/*===========================================================================

FUNCTION PWRDB_PROCESS_RUN_REQ

DESCRIPTION
  Process the run request packet when it is received over the diag
  connection.
  
DEPENDENCIES
  This function should be registered with diag to be called when a
  PWRDB_DIAG_PKT_RUN packet is send to PWRDB.

RETURN VALUE
  Pointer to a response packet.

SIDE EFFECTS
  PWRDB state is changed to running.
  
===========================================================================*/
PACKED void *pwrdb_process_run_req(PACKED void *req_pkt_ptr, uint16 pkt_len)
{
  pwrdb_diag_pkt_run_rsp_type *rsp_ptr = NULL;

  /* Set up response packet */
  rsp_ptr = (pwrdb_diag_pkt_run_rsp_type *) diagpkt_subsys_alloc (
                                              DIAG_SUBSYS_PWRDB,
                                              (PWRDB_DIAG_PKT_RUN | PWRDB_DIAG_PKT_CPU_ID),
                                              sizeof(pwrdb_diag_pkt_run_rsp_type) );

  if(rsp_ptr == NULL)
    return NULL;

  if( pwrdb_state_check_and_change( PWRDB_STATE_READY_FOR_SCRIPTS,
                                       PWRDB_STATE_RUNNING )       )
  {
    rsp_ptr->status = PWRDB_RSP_SUCCESS;

    pwrdb_process_event( PWRDB_EVT_SRC_PWRDB_INTERNAL, 
                         PWRDB_INT_EVT_ID_ENTER_RUNNING );

  }
  else
  {
    rsp_ptr->status = PWRDB_RSP_ERROR;
  }

  return rsp_ptr;
}



/*===========================================================================

FUNCTION PWRDB_PROCESS_STOP_REQ

DESCRIPTION
  Process the stop request packet when it is received over the diag
  connection. If PWRDB is in the middle of processing an event then the
  stop request will only be serviced once the event processing is
  complete.
  
DEPENDENCIES
  This function should be registered with diag to be called when a
  PWRDB_DIAG_PKT_STOP packet is send to PWRDB.

RETURN VALUE
  Pointer to a response packet.

SIDE EFFECTS
  PWRDB state is changed to logs ready.
  
===========================================================================*/
PACKED void *pwrdb_process_stop_req(PACKED void *req_pkt_ptr, uint16 pkt_len)
{
  pwrdb_diag_pkt_stop_rsp_type *rsp_ptr = NULL;

  /* Set up response packet */
  rsp_ptr = (pwrdb_diag_pkt_stop_rsp_type *) diagpkt_subsys_alloc (
                                              DIAG_SUBSYS_PWRDB,
                                              (PWRDB_DIAG_PKT_STOP | PWRDB_DIAG_PKT_CPU_ID),
                                              sizeof(pwrdb_diag_pkt_stop_rsp_type) );

  if(rsp_ptr == NULL)
    return NULL;

  rsp_ptr->status = PWRDB_RSP_ERROR;

  /* Update state */
  qmutex_lock( pwrdb_mutex );
  if ( pwrdb_state == PWRDB_STATE_RUNNING )
  {
    pwrdb_state_change( PWRDB_STATE_LOGS_READY );
    rsp_ptr->status = PWRDB_RSP_SUCCESS;
  }
  else if ( pwrdb_state == PWRDB_STATE_PROC_EVENT )
  {
    pwrdb_state_change( PWRDB_STATE_PROC_EVENT_STOP_PENDING );
    rsp_ptr->status = PWRDB_RSP_SUCCESS;
  }
  qmutex_unlock( pwrdb_mutex );

  return rsp_ptr;
}


/*===========================================================================

FUNCTION PWRDB_PROCESS_TEST_EVENT_REQ

DESCRIPTION
  Process the test event request packet by triggering the specified event.
  complete.
  
DEPENDENCIES
  This function should be registered with diag to be called when a
  PWRDB_DIAG_PKT_TEST_EVENT packet is send to PWRDB.

RETURN VALUE
  Pointer to a response packet.

SIDE EFFECTS
  PWRDB command script for event is executed if present and PWRDB is in
  running state.
  
===========================================================================*/
PACKED void *pwrdb_process_test_event_req(PACKED void *req_pkt_ptr, uint16 pkt_len)
{
  pwrdb_diag_pkt_test_event_req_type *req_ptr = (pwrdb_diag_pkt_test_event_req_type *) req_pkt_ptr;
  pwrdb_diag_pkt_test_event_rsp_type *rsp_ptr = NULL;

  /* Set up response packet */
  rsp_ptr = (pwrdb_diag_pkt_test_event_rsp_type *) diagpkt_subsys_alloc (
                                                    DIAG_SUBSYS_PWRDB,
                                                    (PWRDB_DIAG_PKT_TEST_EVENT | PWRDB_DIAG_PKT_CPU_ID),
                                                    sizeof(pwrdb_diag_pkt_test_event_rsp_type) );

  if(rsp_ptr == NULL)
    return NULL;

  /* Trigger event */
  pwrdb_process_event( req_ptr->source, req_ptr->id );

  return rsp_ptr;
}

/*===========================================================================

FUNCTION PWRDB_PROCESS_TEST_EVENT_REQ

DESCRIPTION
  Process the log format change request by changing the current log format.
  
DEPENDENCIES
  This function should be registered with diag to be called when a
  PWRDB_DIAG_PKT_LOG_FORMAT_CHANGE_REQ packet is send to PWRDB.

RETURN VALUE
  Pointer to a response packet.

SIDE EFFECTS
  Log format is changed.
  
===========================================================================*/
PACKED void *pwrdb_process_change_log_format_req( PACKED void *req_pkt_ptr, uint16 pkt_len )
{
  pwrdb_diag_pkt_change_log_format_req_type *req_ptr = (pwrdb_diag_pkt_change_log_format_req_type *) req_pkt_ptr;
  pwrdb_diag_pkt_change_log_format_rsp_type *rsp_ptr = NULL;
  pwrdb_res_type                                    res     = PWRDB_RES_ERROR;
  pwrdb_log_format_type                             format  = PWRDB_LOG_MAX;

  /* Set up response packet */
  rsp_ptr = (pwrdb_diag_pkt_change_log_format_rsp_type *) diagpkt_subsys_alloc (
                                                           DIAG_SUBSYS_PWRDB,
                                                           (PWRDB_DIAG_PKT_CHANGE_LOG_FORMAT | PWRDB_DIAG_PKT_CPU_ID),
                                                           sizeof(pwrdb_diag_pkt_test_event_rsp_type) );

  if(rsp_ptr == NULL)
    return NULL;

  if (pwrdb_state == PWRDB_STATE_READY_FOR_SCRIPTS)
  {
    switch (req_ptr->log_format)
    {
    case 0:
      format = PWRDB_LOG_TO_ULOG;
      break;
    case 1:
      format = PWRDB_LOG_TO_ULOG_OVER_QDSS;
      break;
    case 2:
      format = PWRDB_LOG_TO_STM_LOG;
      break;
    case 3:
      format = PWRDB_LOG_TO_RAM;
      break;
    }
    
    if (format != PWRDB_LOG_MAX)
    {
      res = pwrdb_change_log_format( format );
    }
  }

  rsp_ptr->status = res == PWRDB_RES_OK ? PWRDB_RSP_SUCCESS : PWRDB_RSP_ERROR;

  return rsp_ptr;
}


/* EJECT */
/*===========================================================================

                      EXTERNAL FUNCTION DEFINITIONS

===========================================================================*/

/*===========================================================================

FUNCTION PWRDB_INIT

DESCRIPTION
  Initialize the power debug module:
  - register with diag for power debug packets
  
DEPENDENCIES
  None

RETURN VALUE
  None

SIDE EFFECTS
  The registration with DIAG causes DIAG to call the power debug functions
  upon receipt of a power debug packet.

===========================================================================*/
void pwrdb_init( void )
{
  /* reset data structures */
  pwrdb_reset();
  
  pwrdb_log_size = PWRDB_DEFAULT_LOG_SIZE;

  pwrdb_ulog_init();
  
  pwrdb_log_format = PWRDB_LOG_TO_RAM;
  pwrdb_log_function = pwrdb_log_function_table[ pwrdb_log_format ];

#ifdef PWRDB_PRO
  if ( !pwrdb_npa_init() )
  {
    PWRDB_MSG_E0("pwrdb_npa_init failed");
  }
#endif
  /* init our mutex */
  pwrdb_mutex_init();
  /* Register with diag ro get the power debug packets. */
  DIAGPKT_DISPATCH_TABLE_REGISTER (DIAG_SUBSYS_PWRDB, pwrdb_diag_tbl);
  
  PWRDB_MSG_H0("pwrdb_init done");
  
  pwrdb_state_change( PWRDB_STATE_READY_FOR_SCRIPTS );
}

/*===========================================================================

FUNCTION PWRDB_TASK_CMD_PROCESS

DESCRIPTION
  Called from the PWRDB task to process commands sent to the task.

PARAMETERS
  cmd - the command to process
  param1, param2 - parameters that depend on the command
  (the same info that was passed into pwrdb_task_cmd_send)  
  
DEPENDENCIES
  None

RETURN VALUE
  None

SIDE EFFECTS
  None
  
===========================================================================*/
void pwrdb_task_cmd_process( pwrdb_task_cmd_type cmd, uint32 p1, uint32 p2 )
{
  switch (cmd)
  {
    case PWRDB_TASK_CMD_NONE:
      /*Do nothing*/
    break;
    case PWRDB_TASK_CMD_PROCESS_SCRIPT:
      pwrdb_process_commands( (pwrdb_command_ll_type*)p1, TRUE );
    break;
    
#ifdef PWRDB_PRO
#ifdef FEATURE_PWRDB_MPSS
    case PWRDB_TASK_CMD_WRITE_LOGS_TO_FS:
    {
      char *log_name = pwrdb_get_next_log_name();
      if(log_name != NULL)
      {
        pwrdb_write_logs_to_fs(log_name);
      }
    }
    break;

    case PWRDB_TASK_CMD_READ_FILE_FROM_FS:
      if( (pwrdb_state == PWRDB_STATE_READY_FOR_SCRIPTS) || (pwrdb_state == PWRDB_STATE_RUNNING) )
      {
        pwrdb_check_fs_for_script( PWRDB_DEFAULT_SCRIPT_FILENAME );
      }
      else
      {
        /* Pwrdb is either processing an event or parsing the file in EFS */
        /* TBD: Set a command in the Queue that we have a pending Job to do */
      }
    break;
#endif /* #ifdef FEATURE_PWRDB_MPSS */
#endif /* #ifdef PWRDB_PRO */

    default:
      /* do nothing */
    break;
  }
}

/*===========================================================================

FUNCTION PWRDB_STATE_CHANGE

DESCRIPTION
  Change the top level state of the debugger

PARAMETERS
  new_state - the state to change to

  NOTE: It is the responsibilty of the calling function to make sure that
  race conditions cannot occur - e.g. by taking mutex.
  
DEPENDENCIES
  None

RETURN VALUE
  None

SIDE EFFECTS
  None
  
===========================================================================*/
void pwrdb_state_change( pwrdb_state_type new_state )
{
  pwrdb_state = new_state;

/* Below _asm portion  can be uncommented for debugging purposes. 
         Keeping _asm part pushes this function not to get inlined*/

/*
__asm 
{
nop
}
*/

}
/*===========================================================================

FUNCTION PWRDB_OPEN_DAL_TLMM

DESCRIPTION
  Helper function to create a connection to DAL TLMM if one is not already
  open.
 
DEPENDENCIES
  None

===========================================================================*/
void pwrdb_open_DAL_TLMM( void )
{
 if (!TLMM_opened)
 {
   DAL_DeviceAttach(DALDEVICEID_TLMM, &hTlmm);
   DalDevice_Open(hTlmm, DAL_OPEN_SHARED);
   TLMM_opened = TRUE;
 }
}

/*===========================================================================

FUNCTION    PWRDB_NPA_RESOURCE_INIT

DESCRIPTION
  Initialize the npa resources array. Set both async/sync client handles to NULL.
  Set npa_client_name for each resource to PWRDB_NPA_CLIENT_NAME. 
  Set npa_resource_name to PWRDB_NPA_NO_RESOURCE.

DEPENDENCIES
  None
  
RETURN VALUE
  None

SIDE EFFECTS
  None

 
===========================================================================*/
void pwrdb_npa_resource_init( void )
{
  int ix;
  if (!pwrdb_npa_resource_initialized)
  { 
    for ( ix = 0; ix < PWRDB_NUM_NPA_RESOURCE; ix ++)
    {
      pwrdb_npa_resource[ix].sync_handle         = NULL;
      pwrdb_npa_resource[ix].async_handle        = NULL;
      pwrdb_npa_resource[ix].npa_client_name     = PWRDB_NPA_CLIENT_NAME;
      pwrdb_npa_resource[ix].npa_resource_name   = PWRDB_NPA_NO_RESOURCE;
    }
    pwrdb_npa_resource_initialized = TRUE;
  }
}
/*===========================================================================

FUNCTION    PWRDB_NPA_MALLOC2CPY_STR

DESCRIPTION
  Helper function to malloc and copy the input string.

DEPENDENCIES
  None
  
RETURN VALUE
  Malloc string:toStr

SIDE EFFECTS
  None

 
===========================================================================*/
char* pwrdb_npa_malloc2cpy_str( const char *fromStr )
{
   char *toStr;
   DALResult res;
   uint32 fromStr_size =  strlen(fromStr) + 1;
            
   res = DALSYS_Malloc(fromStr_size*sizeof(char), (void *)&toStr);
   if( res != DAL_SUCCESS)
   {
     PWRDB_MSG_H0("Malloc Failed, returning from NPA malloc for string copy");
      return NULL;
   }
   else
   {
     /* Adding this address to malloc array, which would be freed during pwrdb_reset */
     pwrdb_addto_malloc_array(toStr);
   }
   
   /* In our case, copy desination size is the same as copy source size, so put source size in std_strlen instead.
      For more information, check std_strlen */
   strlcpy(toStr, fromStr, fromStr_size);

   return toStr;
}


/*===========================================================================

FUNCTION PWRDB_SETUP_EVENT

DESCRIPTION
  Set up and event by:

  1. Making sure subsequent commands are associated with this event.
  
  2. Taking whatever actions are necessary for us to respond to an event, e.g.
  registering a callback function with the module that generates the
  event. The exact action depends on the source of the event.

PARAMETERS
  source and id of the event to setup
  
DEPENDENCIES
  None

RETURN VALUE
  PWRDB_RES_OK
  PWRDB_RES_ERROR

SIDE EFFECTS
  If there was a previous event then this marks the end of the commands
  for the that event so the num_cmds field for the previous event is 
  updated.
    
===========================================================================*/
pwrdb_res_type pwrdb_setup_event( uint32 source, uint32 id )
{
  pwrdb_res_type res = PWRDB_RES_OK;

  switch( source )
  {
  /* PWRDB_EVT_SRC_DIAG */
  case PWRDB_EVT_SRC_DIAG:
    {
      if (!pwrdb_setup_diag_event( (unsigned int)id ))
      {
        res = PWRDB_RES_ERROR;
      }
    }
    break;
  case PWRDB_EVT_SRC_SLEEP:
    {
#ifdef FEATURE_LEGACY_SLEEP_EVENT
      if (!pwrdb_setup_sleep_event( id ))
      {
        res = PWRDB_RES_ERROR;
      }
#else
      pwrdb_log_message(PWRDB_ERROR_MESSAGE, "Error: PWRDB_EVT_SRC_SLEEP is not enabled. (FEATURE_LEGACY_SLEEP_EVENT undefined.)");
#endif /* FEATURE_LEGACY_SLEEP_EVENT */
    }
    break;

  default:
    /* do nothing */
    break;
    
  } /* switch source */

  return res;
}

/*===========================================================================

FUNCTION PWRDB_TIMER_ID_IS_OK

DESCRIPTION
  Checks that timer id is OK.
  
PARAMETERS
  tid of timer
  
RETURN VALUE
  TRUE  - id is OK to use
  FALSE - id is not OK
    
===========================================================================*/
boolean pwrdb_timer_id_is_ok( uint32 tid )
{
  return tid < PWRDB_NUM_TIMERS;
}

/*==========================================================================

FUNCTION PWRDB_ULOG_INIT

DESCRIPTION
  
RETURN VALUE
  PWRDB_RES_OK    - Ulog creation Successful, use the Ulog handle for logging
  PWRDB_RES_ERROR - Something went bad with the Ulog creation, can't use Ulog
==========================================================================*/
pwrdb_res_type pwrdb_ulog_init( void )
{
  pwrdb_res_type  ulog_init_done = PWRDB_RES_OK;
  if(!pwrdb_ulog_handle)
  {
  ulog_init_done = (pwrdb_res_type)ULogFront_RealTimeInit( &pwrdb_ulog_handle,
                                                            PWRDB_LOG_NAME,
                                                            PWRDB_FS_RW_BUF_SIZE*16,
                                                            ULOG_MEMORY_LOCAL,
                                                            ULOG_LOCK_NONE );
  
    if (ulog_init_done != PWRDB_RES_OK )
      ulog_init_done = PWRDB_RES_ERROR;
  }
  return(ulog_init_done);
}

/*==========================================================================

FUNCTION pwrdb_qdss_init

DESCRIPTION
  Initialises the clocks that are needed for logging over QDSS.
 
RETURN VALUE
  PWRDB_RES_OK
==========================================================================*/
pwrdb_res_type pwrdb_qdss_init( void )
{
  /* TBD: Initailise the clocks that are needed for QDSS  */
  return PWRDB_RES_OK;
}


/*===========================================================================

FUNCTION pwrdb_mutex_init
 
DESCRIPTION
  Initialise the Mutex
 
PARAMETERS
  None
RETURN VALUE
  None
SIDE EFFECTS 
 
===========================================================================*/

void pwrdb_mutex_init( void )
{
  qmutex_attr_t mutex_attr;
  int intErr=0;
  
  mutex_attr.type = QMUTEX_LOCAL;
  intErr = qmutex_create( &pwrdb_mutex, &mutex_attr ); 
  if( intErr != QURT_EOK)
  {
    ERR_FATAL("qmutex_create failed to create list_ptr->pkcsListCriticalSection",0,0,0);
  }
}

#if 0
/*===========================================================================

FUNCTION pwrdb_mpss_xo_shutdown_enter
 
DESCRIPTION
  PWRDB Entry function for the XO Shutdown LPRM
  xo shutdown is given as the dependency for this lpr,
  this entry function would be called whenever sleep algorithm decides
  that the xo shutdown is the lprm for the resource xo.
 
PARAMETERS
  duration_sclk: Sleep duration when entering this LPRM
 
RETURN VALUE
  Void
 
SIDE EFFECTS 
  When declaring the LPRM the latency for enter and exit functions
  have to be defined, because the latencys not pre defined it is given as 1
  So the activity here disturbs the sleep
===========================================================================*/

void pwrdb_mpss_xo_shutdown_enter( uint64 duration_sclk )
{
  /* Raise the XO Shutdown event to PWRDB*/
  pwrdb_process_event( PWRDB_EVT_SRC_SLEEP,PWRDB_INT_EVT_ID_SLEEP_XO_SHUTDOWN_ENTER );
}

/*===========================================================================

FUNCTION pwrdb_mpss_xo_shutdown_exit
 
DESCRIPTION
  PWRDB Exit function for the XO Shutdown LPRM
  xo shutdown is given as the dependency for this lpr,
  this exit function would be called whenever system
  comes out of xo shutdown
 
PARAMETERS
  None
 
RETURN VALUE
  Void
 
SIDE EFFECTS 
  None
===========================================================================*/

void pwrdb_mpss_xo_shutdown_exit( void )
{
  /* Raise XO shutdown exit event to PWRDB */
  pwrdb_process_event( PWRDB_EVT_SRC_SLEEP,PWRDB_INT_EVT_ID_SLEEP_XO_SHUTDOWN_EXIT );
}
/*===========================================================================

FUNCTION pwrdb_mpss_pc_enter
 
DESCRIPTION
  PWRDB Entry function for MPSS Power Collapse LPRM
  MPSS PC is given as the dependency for this lpr,
  this entry function would be called whenever sleep algorithm decides
  that the Processor Power Collapse is the lprm for the Core Resoirce.
 
PARAMETERS
  duration_sclk: Sleep duration when entering this LPRM
 
RETURN VALUE
  Void
 
SIDE EFFECTS 
  When declaring the LPRM the latency for enter and exit functions
  have to be defined, because the latency s not pre defined it is given as 1
  So the activity here disturbs the sleep
===========================================================================*/

void pwrdb_mpss_pc_enter( uint64 duration_sclk )
{
  /* does this occur in the sleep context */
  pwrdb_process_event( PWRDB_EVT_SRC_SLEEP, PWRDB_INT_EVT_ID_SLEEP_PC_ENTER );
}
/*===========================================================================

FUNCTION pwrdb_mpss_pc_exit
 
DESCRIPTION
  PWRDB Exit function for the MPSS PC LPRM
  MPSS PC is given as the dependency for this lpr,
  this exit function would be called whenever system
  comes out of MPSS Power Collapse
 
PARAMETERS
  None
 
RETURN VALUE
  Void
 
SIDE EFFECTS 
  None
===========================================================================*/
void pwrdb_mpss_pc_exit( void )
{
  pwrdb_process_event( PWRDB_EVT_SRC_SLEEP, PWRDB_INT_EVT_ID_SLEEP_PC_EXIT );
}
/*===========================================================================

FUNCTION pwrdb_mpss_vdd_min_enter
 
DESCRIPTION
  PWRDB Exit function for the MPSS PC LPRM
  MPSS PC is given as the dependency for this lpr,
  this exit function would be called whenever system
  comes out of MPSS Power Collapse
 
PARAMETERS
  None
 
RETURN VALUE
  Void
 
SIDE EFFECTS 
  None
===========================================================================*/
void pwrdb_mpss_vdd_min_enter( uint64 duration_sclk )
{
  pwrdb_process_event( PWRDB_EVT_SRC_SLEEP, PWRDB_INT_EVT_ID_SLEEP_VDDMIN_ENTER );
}
/*===========================================================================

FUNCTION pwrdb_mpss_vdd_min_enter
 
DESCRIPTION
  PWRDB Exit function for the MPSS PC LPRM
  MPSS PC is given as the dependency for this lpr,
  this exit function would be called whenever system
  comes out of MPSS Power Collapse
 
PARAMETERS
  None
 
RETURN VALUE
  Void
 
SIDE EFFECTS 
  None
===========================================================================*/
void pwrdb_mpss_vdd_min_exit( void )
{
  pwrdb_process_event( PWRDB_EVT_SRC_SLEEP, PWRDB_INT_EVT_ID_SLEEP_VDDMIN_EXIT );
}
#endif
/*===========================================================================

FUNCTION pwrdb_log_to_ulog
 
DESCRIPTION
  Log mechanism for this session is set to be Ulog.
 
PARAMETERS
  cmd_id:  The command that this log is being invoked for
  cmd_ptr: Data_structure with the command information
  result:  Pwrdb result of the command processing 
 
RETURN VALUE
  Void
 
Dependencies 
   None
 
SIDE EFFECTS 
  None
===========================================================================*/
void pwrdb_log_to_ulog( uint32 cmd_id, uint64 result)
{
  if( pwrdb_ulog_handle )
  {
    ULOG_RT_PRINTF_3( pwrdb_ulog_handle, " cmd_id: 0x%lx Result: 0x%llx ",
                      cmd_id ,ULOG64_LOWWORD(result),ULOG64_HIGHWORD(result) ); 
  }
}

/*===========================================================================

FUNCTION pwrdb_log_Ulog_to_QDSS
 
DESCRIPTION
  Log mechanism for this session is set to be ULOG over QDSS
 
PARAMETERS
  cmd_id:  The command that this log is being invoked for
  result:  Pwrdb result of the command processing 
 
RETURN VALUE
  Void
 
Dependencies 
   Need QDSS to be enabled before the first log is pushed and Ulog to be set
   to go out over QDSS STM
 
SIDE EFFECTS 
  None
===========================================================================*/
void pwrdb_log_Ulog_to_QDSS( uint32 cmd_id, uint64 result)
{
}

/*===========================================================================

FUNCTION pwrdb_log_to_QDSS_STM
 
DESCRIPTION
  Log mechanism for this session is set to be QDSS STM by the user
 
PARAMETERS
  cmd_id:  The command that this log is being invoked for
  result:  Pwrdb result of the command processing 
 
RETURN VALUE
  Void
 
Dependencies 
   Need QDSS to be enabled before the first log is pushed. 

SIDE EFFECTS 
  None
===========================================================================*/
void pwrdb_log_to_QDSS_STM( uint32 cmd_id, uint64 result)
{
  tracer_event_simple_vargs(PWRDB_SWE_1, 3, cmd_id, (uint32)(result>>32), (uint32)(result));
}

/*===========================================================================

FUNCTION pwrdb_log_to_ram
 
DESCRIPTION
  Log mechanism for this session is set to null. This function is not
  expected to be called but is used to fill out the function table
  to avoid potential crashes - since logging to RAM does not use the
  function table
 
PARAMETERS
  All parameters are ignored.
 
RETURN VALUE
  Void
 
Dependencies 
  None
 
SIDE EFFECTS 
  None
===========================================================================*/
void pwrdb_log_to_ram( uint32 a, uint64 b )
{
  // Indicate the error usage
  PWRDB_MSG_E0( "Error: Invalid usage of pwrdb_log_to_ram()" );

  // avoid compiler warnings
  (void)a;
  (void)b;
}

/*===========================================================================

FUNCTION pwrdb_find_existing_event
 
DESCRIPTION
  Log mechanism for this session is set to be QDSS STM by the user
 
PARAMETERS
  cmd_id:  The command that this log is being invoked for
  cmd_ptr: Data_structure with the command information
  result:  Pwrdb result of the command processing 
 
RETURN VALUE
  Void
 
Dependencies 
   Need QDSS to be enabled before the first log is pushed. 

SIDE EFFECTS 
  None
===========================================================================*/

pwrdb_event_ll_type *pwrdb_find_existing_event( uint32 source, uint32 id )
{
  pwrdb_event_ll_type *pwrdbi_event = pwrdb_events;

  while( pwrdbi_event !=NULL )
  {
    if( ( pwrdbi_event->event.source == source ) && 
        ( pwrdbi_event->event.id == id ) )
    {
      return pwrdbi_event;
    }
      pwrdbi_event = pwrdbi_event->next;
  }
  return NULL;
}

/*===========================================================================

FUNCTION pwrdb_update_and_get_cmd_number
 
DESCRIPTION
  Each command has to be identified with a unique command number
  keep a note of the last command number in the sequence and spit
  out a new command number for the next command that is being processed/
  being passed to RPM
 
PARAMETERS
  None
  
RETURN VALUE
  Command number that is uniquely identified
 
Dependencies 
  None

SIDE EFFECTS 
  None
===========================================================================*/
uint16 pwrdb_update_and_get_cmd_number( void )
{
  if( pwrdb_cmd_seq_num == PWRDB_MAX_CMD_SEQ_NUMBER )
    pwrdb_cmd_seq_num = 0;
  else
    pwrdb_cmd_seq_num++;
  return(pwrdb_cmd_seq_num);
}

/*===========================================================================

FUNCTION pwrdb_update_and_get_cmd_number
 
DESCRIPTION
  Each command has to be identified with a unique command number
  keep a note of the last command number in the sequence and spit
  out a new command number for the next command that is being processed/
  being passed to RPM
 
PARAMETERS
  None
  
RETURN VALUE
  Command number that is uniquely identified
 
Dependencies 
  None

SIDE EFFECTS 
  None
===========================================================================*/
uint16 pwrdb_generate_command_id( uint16 sequential_cmd_id, uint16 pwrdb_cmd_id, uint32 execution_num )
{
  uint16 command_id = (((sequential_cmd_id & 0x7F) << 8) | 
                      ((pwrdb_cmd_id & 0xF) << 4) | (execution_num & 0xF));
  return command_id;
}

