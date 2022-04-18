#ifndef PWRDBI_H
#define PWRDBI_H

/*===========================================================================

           P W R   D E B U G   I N T E R N A L   H E A D E R 
                      
DESCRIPTION
  Internal definitions for the power debug service.
   
EXTERNALIZED FUNCTIONS


REGIONAL FUNCTIONS



INITIALIZATION AND SEQUENCING REQUIREMENTS

  Must create and start pwrdb task before commands will be processed by pwrdb.


  Copyright (c) 2014 by QUALCOMM Technologies, Incorporated.  All Rights Reserved.
  
===========================================================================*/

/*===========================================================================

                      EDIT HISTORY FOR FILE

$Header: //components/rel/core.qdsp6/1.0.c2/powertools/pwrdb/src/pwrdbi.h#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
12/02/14   dy      Add Downsampling command for SystemDB
09/29/14   dy      Add RPM Dump and Err Fatal commands for SystemDB
09/13/13   rs      Made pwrdb_log_type struct into a node for the pwrdb_log linked list.
09/24/10   hluo    Obsolete the sbi_write and sbi_read
05/17/10   jl      Added CLK_BUSY_WAIT and NPA_QUERY_BY_NAME commands.
03/05/10   jl      Added NPA support.
01/12/10   jl      Added extended sleep voting function.
12/16/09   gw      Fixed featurizaton for single processor builds.
11/25/09   ab      Added DALI2C read and DALI2C write commands
10/19/09   jl      Added DSLSBI read and DALSBI write commands
10/02/09   jl      Added EFS support for apps proc
10/01/09   ab      Adding Physical address, numbering log feature
09/14/09   jl      Added clkrgm device manager commands. 
08/21/09   gw      Removed PACKED directive from structs.
08/10/09   jl/ck   Added sleep vote command. Update start timer command struct.
07/24/09   sg      Added support for message logging.
05/01/09   gw      Refactoring based on code review comments.
04/10/09   gw      Added support for debug messaging.
03/17/09   gw      Added commands and log items for TLMM and clkregime APIs.
11/04/08   gw      Created this file 

===========================================================================*/

/* <EJECT> */
/*==========================================================================

                     INCLUDE FILES FOR MODULE

==========================================================================*/
#include "pwrdb_diag.h"

#include "assert.h"
#include "comdef.h"

#include "msg.h"

#include "npa.h"
#include <npa_resource.h>

#include "queue.h"
#include "DalDevice.h" 
#include "DALDeviceId.h"
#include "HALhwio.h"

/* mk:HalFpioInt.h is not available in 8974 */
/*
#include "HALtlmmHWIO.h"
#include "HALhwioClk.h"   
#include "HALclkHWIO.h"   
*/
#include "diagpkt.h"


/* mk:For mutex we use "qmutex.h" on 8974*/
#include "qmutex.h"


#include "timetick.h"

#include "ULogFront.h"
#include "ULog.h"

#include "system_db.h"
#include "system_db_master.h"


#include "msmhwiobase.h"

/* Include for the DAL events */
#include "DALSys.h"

#if defined(__cplusplus)
#define PWRDB_INLINE inline
#else
#define PWRDB_INLINE __inline
#endif

/*==========================================================================

                     CONSTANTS

==========================================================================*/

/* Version of the power debugger software. The version should be 
   incremented whenever a change is made to the behavior or interface
   of the debugger.

   The major version must be incremented whenever a change is made that
   is not backward compatible. This should be rare. The minor version
   should be incremented for other changes including backwards 
   compatible changes.
 */
#define PWRDB_MAJOR_VERSION       0x0012
#define PWRDB_MINOR_VERSION       0x0001


#define PWRDB_TASK_TOTAL_EVENTS   0001

/* PWRDB logs and scripts root directory */
#define PWRDB_ROOT_DIR                "/pwrdb"

#ifdef IMAGE_APPS_PROC
/* Default filenames for apps processor */
#define PWRDB_DEFAULT_SCRIPT_FILENAME     "/pwrdb/pwrdb_apps_startup.pds"
#define PWRDB_LOG_PROTO_NAME              "pwrdb_apps_log_"
#elif  FEATURE_PWRDB_MPSS
#define PWRDB_DEFAULT_SCRIPT_FILENAME     "/pwrdb/pwrdb_modem_startup.pds"
#define PWRDB_LOG_PROTO_NAME              "pwrdb_modem_log_"
#elif  FEATURE_PWRDB_ADSP
#define PWRDB_DEFAULT_SCRIPT_FILENAME     "/pwrdb/pwrdb_lpass_startup.pds"
#define PWRDB_LOG_PROTO_NAME              "pwrdb_lpass_log_"
#else
#define PWRDB_LOG_PROTO_NAME              "pwrdb_modem_log_"
#endif 

/* Default filename to save logs in */
#define PWRDB_LOG_EXT                 ".pdl"   //Should be 4 characters
#define PWRDB_MAX_FILENAME_LEN        35

/* Macro to mark the GPIO to program, for the SW Signal */
/* Note: the Gpio number for Badger is yet to be identified */
#define PWRDB_TRIGGER_GPIO_NUM             54
#define PWRDB_TRIGGER_GPIO_FUNC       0

#define PWRDB_LOG_NAME                "Pwrdb Log"

#define PWRDB_GCC_DEBUG_CLK_CTL_ADDR           (CLK_CTL_BASE      + 0x00001880)
#define PWRDB_GCC_PLLTEST_PAD_CFG_ADDR         (CLK_CTL_BASE      + 0x0000188c)

#ifdef PWRDB_PRO
#define PWRDB_LOGGING_MASK_NPA                 0x1
#endif
#define PWRDB_LOGGING_MASK_QDSS_STM            0x2
#define PWRDB_LOGGING_MASK_UDAS                0x4


/*==========================================================================

                     GLOBAL Variables

==========================================================================*/

ULogHandle                                 pwrdb_ulog_handle;

/* Pwrdb Rpm Command Interface */
SYSTEMDB_EVENT_TYPE pwrdb_rpm_event;


/*==========================================================================

                     TYPES

==========================================================================*/

/* -----------------------------------------------------------------------
** Internal representation of commands for pwrdb command scripts
** ----------------------------------------------------------------------- */

/* PWRDB_CMD_NULL_CMD */
typedef struct { 
} pwrdb_icmd_null_cmd_type;

/* PWRDB_CMD_START_TASK_CMDS */
typedef struct { 
} pwrdb_icmd_start_task_cmds_type;

/* PWRDB_CMD_END_OF_CMDS  */
typedef struct { 
} pwrdb_icmd_end_of_cmds_type;

/* PWRDB_CMD_START_TIMER */
typedef struct { 
  uint32    time;
  uint16    id;
  uint8     repeat;
  uint8     always_on;
} pwrdb_icmd_start_timer_type;

/* PWRDB_CMD_STOP_LOGGING  */
typedef struct { 
} pwrdb_icmd_stop_logging_type;

/* PWRDB_CMD_ENABLE_PRO */
typedef struct { 
  uint32     enable;
} pwrdb_icmd_enable_pro_type;

/* PWRDB_CMD_TLMM_SET_CURR_CONFIG */ 
typedef struct {
  uint16    gpio_number;
  uint8     function;
  uint8     direction;
  uint8     pull;
  uint8     drive_strength;
  uint8     output_value;
  uint8     enable;
} pwrdb_icmd_tlmm_set_curr_config_type;

/* PWRDB_CMD_TLMM_GET_CURR_CONFIG */
typedef struct {
  uint16    gpio_number;
  uint16    dest; 
} pwrdb_icmd_tlmm_get_curr_config_type;

/* PWRDB_CMD_TLMM_SET_INACT_CONFIG */
typedef struct {
  uint16 gpio_number;
  uint8  function;
  uint8  direction;
  uint8  pull;
  uint8  drive_strength;
  uint8  output_value;
  uint8  bypass;
} pwrdb_icmd_tlmm_set_inact_config_type; 

/* PWRDB_CMD_TLMM_GET_INACT_CONFIG */
typedef struct {
  uint16 gpio_number;
  uint16  dest;
} pwrdb_icmd_tlmm_get_inact_config_type;

/* PWRDB_CMD_TLMM_OUTPUT */
typedef struct {
  uint16    gpio_number;
  uint16    output_value;
} pwrdb_icmd_tlmm_output_type;

/* PWRDB_CMD_TLMM_INPUT */
typedef struct {
  uint16    gpio_number;
  uint16    dest;
} pwrdb_icmd_tlmm_input_type;

/* PWRDB_CMD_TLMM_GET_PIN_STATUS */
typedef struct {
  uint16    gpio_number;
  uint16    dest;
} pwrdb_icmd_tlmm_get_pin_status_type;

/* PWRDB_CMD_TLMM_LOCK */
typedef struct {
  uint16     gpio_number;
  uint16     pad_align;
} pwrdb_icmd_tlmm_lock_type;

/* PWRDB_CMD_TLMM_UNLOCK */
typedef struct {
  uint16     gpio_number;
  uint16     pad_align;
} pwrdb_icmd_tlmm_unlock_type;

/* PWRDB_CMD_TLMM_IS_LOCKED */
typedef struct {
  uint16    gpio_number;
  uint16    dest;
} pwrdb_icmd_tlmm_is_locked_type;

/* PWRDB_CMD_CLK_SET_CLK_EN */
typedef struct {
  uint16   clk_en_len;
  uint16   enable;
  char     *clk; 
} pwrdb_icmd_clk_set_clk_en_type;

/* PWRDB_CMD_CLK_GET_CLK_EN */
typedef struct {
  uint32  clk_en_len;
  char    *clk;
} pwrdb_icmd_clk_get_clk_en_type;

/* PWRDB_CMD_CLK_GET_CLK_FREQ */
typedef struct {
  uint32   clk_en_len;
  char     *clk;
} pwrdb_icmd_clk_get_clk_freq_type;

/* cmd:PWRDB_CMD_CLK_OUTPUT_GPIO */
typedef struct{
  uint32 reg_value; 
}pwrdb_icmd_clk_output_gpio_type;

/* PWRDB_CMD_CLK_BUSY_WAIT */
typedef struct {
  uint32 usec;
} pwrdb_icmd_clk_busy_wait_type;

/* PWRDB_CMD_CLK_LOG_STATE  */
typedef struct {
  uint32 measureFreq; 
} pwrdb_icmd_clk_log_state_type;

/* PWRDB_CMD_PEEK8 */
typedef struct {
  uint32 addr;
} pwrdb_icmd_peek8_type;

/* PWRDB_CMD_PEEK16 */
typedef struct {
  uint32 addr;
} pwrdb_icmd_peek16_type;

/* PWRDB_CMD_PEEK32 */
typedef struct {
  uint32 addr;
} pwrdb_icmd_peek32_type;

/* PWRDB_CMD_PEEK32_RANGE */
typedef struct {
  uint32 addr;
  uint32 range;
} pwrdb_icmd_peek32_range_type;

/* PWRDB_CMD_POKE32_RANGE */
typedef struct {
  uint32 addr;
  uint32 range;
  uint32 *vals; /* need to allocate this memory separately */
} pwrdb_icmd_poke32_range_type;

/* PWRDB_CMD_POKE8_M */
typedef struct {
  uint32 addr;
  uint16  val; /* VK: Changed from uint8 to uint16 */
  uint16  mask; /* VK: Changed from uint8 to uint16 */
} pwrdb_icmd_poke8_m_type;

/* PWRDB_CMD_POKE16_M */
typedef struct {
  uint32 addr;
  uint16 val;
  uint16 mask;
} pwrdb_icmd_poke16_m_type;

/* PWRDB_CMD_POKE32_M */
typedef struct {
  uint32 addr;
  uint32 val;
  uint32 mask;
} pwrdb_icmd_poke32_m_type;


/* PWRDB_CMD_STRING */
typedef struct {
  uint16 str_type;
  uint16 str_len;
  char*  str;
} pwrdb_icmd_string_type; /* VK: this would give a diff lenth need one byte to be padded*/

/* PWRDB_CMD_DATA3_STRING */
typedef struct {
  uint32 str_type;
  uint32 value1;
  uint32 value2;
  uint32 value3;  
  uint32 str_len;
  char*  str;  /* VK: this would give a diff lenth need one byte to be padded*/
} pwrdb_icmd_data3_string_type;

/* PWRDB_CMD_NPA_ISSUE_REQUIRED_REQUEST */
typedef struct {
  npa_client_handle  NPAClientHandle; 
  uint32             state;
} pwrdb_icmd_npa_issue_required_request_type;

/* PWRDB_CMD_NPA_MODIFY_REQUIRED_REQUEST */
typedef struct {
  npa_client_handle  NPAClientHandle; 
  int32              delta;
} pwrdb_icmd_npa_modify_required_request_type;

/* PWRDB_CMD_NPA_ISSUE_IMPULSE_REQUEST */
typedef struct {
  npa_client_handle  NPAClientHandle; 
} pwrdb_icmd_npa_issue_impulse_request_type;

/* PWRDB_CMD_NPA_ISSUE_ISOC_REQUEST */
typedef struct {
  npa_client_handle  NPAClientHandle; 
  uint32             deadline;
  uint32             level_hint;
} pwrdb_icmd_npa_issue_isoc_request_type;

/* PWRDB_CMD_NPA_ISSUE_LIMIT_MAX_REQUEST */
typedef struct {
  npa_client_handle  NPAClientHandle;
  uint32             max;
} pwrdb_icmd_npa_issue_limit_max_request_type;

/* PWRDB_CMD_NPA_COMPLETE_REQUEST */
typedef struct {
  npa_client_handle  NPAClientHandle;
} pwrdb_icmd_npa_complete_request_type;

/* PWRDB_CMD_NPA_QUERY_BY_NAME */
typedef struct {
  uint32           query_id;
  npa_query_handle NPAQueryHandle;
  npa_query_type   result;
  uint32           resource_name_len;
  char*            resource_name; 
} pwrdb_icmd_npa_query_by_name_type;

typedef struct {
uint32 mux_value;
} pwrdb_icmd_configure_hw_events_mux_type;

typedef struct{
  uint32 log_mask;
  uint32 gpio_number;
}pwrdb_icmd_trigger_log_signals_type;

typedef struct{
  uint32 log_format;
}pwrdb_icmd_change_log_format_type;


typedef struct{
  uint16 pwrdb_rpm_event_mask;
  uint16 range;
  uint32 gpio_number;
  uint32 pwrdb_rpm_execution_num;  
}pwrdb_icmd_rpm_tlmm_read_type;

typedef struct{
  uint32 pwrdb_rpm_event_mask;
  uint32 pwrdb_rpm_execution_num;  
}pwrdb_icmd_rpm_clk_log_state_type;

typedef struct{
  uint32 pwrdb_rpm_event_mask;
  uint32 pwrdb_rpm_execution_num;
}pwrdb_icmd_rpm_end_of_cmd_type;

typedef struct{
  uint16              pwrdb_rpm_event_mask;
  uint16              range;
  uint16              gpio_number;
  uint8               function;
  uint8               direction;
  uint8               pull;
  uint8               drive_strength;
  uint8               output_value;
  uint8               enable;
  uint32 pwrdb_rpm_execution_num;
}pwrdb_icmd_rpm_tlmm_write_type;

typedef struct{
  uint32 pwrdb_rpm_event_mask;
  uint32 pwrdb_rpm_execution_num;
}pwrdb_icmd_rpm_dump_type;

typedef struct{
  uint32              pwrdb_rpm_event_mask;
  uint32              param1;
  uint32 pwrdb_rpm_execution_num;
}pwrdb_icmd_rpm_err_fatal_type;

typedef struct{
  uint32              downsample;
}pwrdb_icmd_rpm_downsample_type;

typedef struct{
uint16 pwrdb_rpm_event_mask;
uint16 range;
uint32 addr;  
uint32 pwrdb_rpm_execution_num;  
}pwrdb_icmd_rpm_memory_peek_type;

typedef struct{
uint16 pwrdb_rpm_event_mask;
uint16 range;
uint32 addr;
uint32 value;
uint32 pwrdb_rpm_execution_num;
}pwrdb_icmd_rpm_memory_poke_type;

typedef struct{
  uint16 pwrdb_rpm_event_mask;
  uint16 slave_id;
  uint16 offset;
  uint16 range;
  uint32 pwrdb_rpm_execution_num;
}pwrdb_icmd_rpm_spmi_read_type;

typedef struct{
  uint16 pwrdb_rpm_event_mask;
  uint16 slave_id;
  uint16 offset;
  uint16 range;
  uint32 value;
  uint32 pwrdb_rpm_execution_num;
}pwrdb_icmd_rpm_spmi_write_type;

typedef struct{
  uint32 pwrdb_rpm_event_mask;
}pwrdb_icmd_rpm_flush_cmd_type;

typedef struct {
    uint32 protocol_num;
}pwrdb_icmd_set_ulog_output_to_qdss;

/* Union that brings all the structs above into one type */
typedef struct {
  uint16 cmd_id;

  union {
      pwrdb_icmd_null_cmd_type                      null_cmd;
      pwrdb_icmd_start_task_cmds_type               start_task_cmds;
      pwrdb_icmd_end_of_cmds_type                   end_of_cmds;
      pwrdb_icmd_start_timer_type                   start_timer;  
      pwrdb_icmd_stop_logging_type                  stop_logging;
      pwrdb_icmd_enable_pro_type                    enable_pro;
      pwrdb_icmd_tlmm_set_curr_config_type          tlmm_set_curr_config;
      pwrdb_icmd_tlmm_get_curr_config_type          tlmm_get_curr_config;
      pwrdb_icmd_tlmm_set_inact_config_type         tlmm_set_inact_config;
      pwrdb_icmd_tlmm_get_inact_config_type         tlmm_get_inact_config;
      pwrdb_icmd_tlmm_output_type                   tlmm_output;
      pwrdb_icmd_tlmm_input_type                    tlmm_input;
      pwrdb_icmd_tlmm_get_pin_status_type           tlmm_get_pin_status;
      pwrdb_icmd_tlmm_lock_type                     tlmm_lock;
      pwrdb_icmd_tlmm_unlock_type                   tlmm_unlock;
      pwrdb_icmd_tlmm_is_locked_type                tlmm_is_locked;
      pwrdb_icmd_clk_set_clk_en_type                clk_set_clk_en;
      pwrdb_icmd_clk_get_clk_en_type                clk_get_clk_en;
      pwrdb_icmd_clk_get_clk_freq_type              clk_get_clk_freq;
      pwrdb_icmd_clk_output_gpio_type               clk_output_gpio;
      pwrdb_icmd_clk_busy_wait_type                 clk_busy_wait;
      pwrdb_icmd_clk_log_state_type                 clk_log_state;
      pwrdb_icmd_peek8_type                         peek8;
      pwrdb_icmd_peek16_type                        peek16;
      pwrdb_icmd_peek32_type                        peek32;
      pwrdb_icmd_peek32_range_type                  peek32_range;
      pwrdb_icmd_poke32_range_type                  poke32_range;
      pwrdb_icmd_poke8_m_type                       poke8_m;
      pwrdb_icmd_poke16_m_type                      poke16_m;
      pwrdb_icmd_poke32_m_type                      poke32_m;
      pwrdb_icmd_string_type                        strng;
      pwrdb_icmd_data3_string_type                  data3_strng;
      pwrdb_icmd_npa_issue_required_request_type    npa_issue_required_request;
      pwrdb_icmd_npa_modify_required_request_type   npa_modify_required_request;
      pwrdb_icmd_npa_issue_impulse_request_type     npa_issue_impulse_request;
      pwrdb_icmd_npa_issue_isoc_request_type        npa_issue_isoc_request;
      pwrdb_icmd_npa_issue_limit_max_request_type   npa_issue_limit_max_request;
      pwrdb_icmd_npa_complete_request_type          npa_complete_request;
      pwrdb_icmd_npa_query_by_name_type             npa_query_by_name;
      pwrdb_icmd_configure_hw_events_mux_type       configure_hw_events_mux;
      pwrdb_icmd_trigger_log_signals_type           trigger_log_signal;
      pwrdb_icmd_change_log_format_type             set_log_format;
      pwrdb_icmd_rpm_tlmm_read_type                 rpm_tlmm_read;
      pwrdb_icmd_rpm_clk_log_state_type             rpm_clk_log_state;
      pwrdb_icmd_rpm_end_of_cmd_type                rpm_end_of_cmd;
      pwrdb_icmd_rpm_tlmm_write_type                rpm_tlmm_write;
      pwrdb_icmd_rpm_dump_type                      rpm_dump;
      pwrdb_icmd_rpm_err_fatal_type                 rpm_err_fatal;
      pwrdb_icmd_rpm_downsample_type                rpm_downsample;
      pwrdb_icmd_rpm_spmi_read_type                 rpm_spmi_read;
      pwrdb_icmd_rpm_spmi_write_type                rpm_spmi_write;
      pwrdb_icmd_rpm_memory_peek_type               rpm_memory_peek;
      pwrdb_icmd_rpm_memory_poke_type               rpm_memory_poke;
      pwrdb_icmd_rpm_flush_cmd_type                 rpm_flush_cmds;
      pwrdb_icmd_set_ulog_output_to_qdss            set_ulog_output;
  } params;
} pwrdb_cmd_type;

typedef struct {
  uint16 source; 
  uint16 id;
} pwrdb_ievt_type;

typedef struct pwrdb_command_ll_type{
  pwrdb_cmd_type                command;
  struct pwrdb_command_ll_type *next; 
}pwrdb_command_ll_type;

typedef struct pwrdb_event_ll_type {
  pwrdb_ievt_type             event;
  struct pwrdb_event_ll_type *next;
  pwrdb_command_ll_type      *pwrdb_cmds;
}pwrdb_event_ll_type;

typedef void ( *pwrdb_log_function_type )( uint32, uint64 );

/* -----------------------------------------------------------------------
** Internal representation of log items
** ----------------------------------------------------------------------- */


/* PWRDB_LOG_NULL */
//typedef struct {
//} pwrdb_ilog_null_type;

/* PWRDB_LOG_EVENT */
typedef struct {
  uint32 source;
  uint32 id;
  uint32 reserved1;
  uint32 reserved2;
} pwrdb_ilog_event_type;

/* PWRDB_LOG_TLMM_GET_CURR_CONFIG */
typedef struct {
  uint16 gpio_number;
  uint8  function;
  uint8  direction;
  uint8  pull;
  uint8  drive_strength;
  uint8  output_value;
  uint8  status;
} pwrdb_ilog_tlmm_get_curr_config_type;

/* PWRDB_LOG_TLMM_GET_INACT_CONFIG */
typedef struct {
  uint16 gpio_number;
  uint16 function;
  uint8  direction;
  uint8  pull;
  uint8  drive_strength;
  uint8  output_value;
} pwrdb_ilog_tlmm_get_inact_config_type;

/* PWRDB_LOG_TLMM_INPUT */
typedef struct {
  uint16  gpio_number;
  uint16  input_value;
} pwrdb_ilog_tlmm_input_type;

/* PWRDB_LOG_TLMM_GET_PIN_STATUS */
typedef struct {
  uint16 gpio_number;
  uint16 pin_status;
} pwrdb_ilog_tlmm_get_pin_status_type;

/* PWRDB_LOG_TLMM_IS_LOCKED */
typedef struct {
  uint16 gpio_number;
  uint16 locked;
} pwrdb_ilog_tlmm_is_locked_type;

/* PWRDB_LOG_CLK_GET_CLK_EN */
typedef struct {
  uint16  clk_en_len;
  uint16  enable;
  char    *clk;  
} pwrdb_ilog_clk_get_clk_en_type;

/* PWRDB_LOG_CLK_GET_CLK_FREQ */
typedef struct {
  uint16  freq;
  uint16  clk_en_len;
  char    *clk;
} pwrdb_ilog_clk_get_clk_freq_type;

/* PWRDB_LOG_PEEK8 */
typedef struct {
  uint32 addr;
  uint32 physaddr;
  uint32 val;
} pwrdb_ilog_peek8_type;

/* PWRDB_LOG_PEEK16 */  
typedef struct {
  uint32 addr;
  uint32 physaddr;
  uint32 val;
} pwrdb_ilog_peek16_type;

/* PWRDB_LOG_PEEK32 */ 
typedef struct {
  uint32 addr;
  uint32 physaddr;
  uint32 val;
} pwrdb_ilog_peek32_type;

/* PWRDB_LOG_PEEK32_RANGE */
typedef struct {
  uint32 addr;
  uint32 physaddr;
  uint32 num_vals;         /* number of 32 bit values being returned */
  uint32 *vals;            /* pointer to memory allocated separately */
} pwrdb_ilog_peek32_range_type;

/* PWRDB_LOG_STRING */
typedef struct {
  uint16 str_type;
  uint16 str_len;
  char* str;
} pwrdb_ilog_string_type;

/* PWRDB_LOG_DATA3_STRING */
typedef struct {
  uint32 str_type;
  uint32 value1;
  uint32 value2;
  uint32 value3;
  uint32 str_len;
  char*  str;
} pwrdb_ilog_data3_string_type;

/* PWRDB_LOG_NPA_QUERY_BY_NAME */
typedef struct {
  uint32           query_id;
  npa_query_handle NPAQueryHandle;
  npa_query_type   result;
  uint32           resource_name_len;
  char*            resource_name;
} pwrdb_ilog_npa_query_by_name_type;

/* Union that brings all the structs above into one type */
typedef struct pwrdb_log_type{
  uint32 time;
  uint16 log_id;

  union {
//    pwrdb_ilog_null_type                     null_log;
    pwrdb_ilog_event_type                     event;
    pwrdb_ilog_tlmm_get_curr_config_type      tlmm_get_curr_config;
    pwrdb_ilog_tlmm_get_inact_config_type     tlmm_get_inact_config;
    pwrdb_ilog_tlmm_input_type                tlmm_input;
    pwrdb_ilog_tlmm_get_pin_status_type       tlmm_get_pin_status;
    pwrdb_ilog_tlmm_is_locked_type            tlmm_is_locked;
    pwrdb_ilog_clk_get_clk_en_type            clk_get_clk_en; 
    pwrdb_ilog_clk_get_clk_freq_type          clk_get_clk_freq;
    pwrdb_ilog_peek8_type                     peek8;
    pwrdb_ilog_peek16_type                    peek16;
    pwrdb_ilog_peek32_type                    peek32;
    pwrdb_ilog_peek32_range_type              peek32_range;
    pwrdb_ilog_string_type                    strng;
    pwrdb_ilog_data3_string_type              data3_strng;
    pwrdb_ilog_npa_query_by_name_type         npa_query_by_name;
  } data;
} pwrdb_log_type;

typedef struct pwrdb_malloc_item_ll_type
{
  void *addr;
  struct pwrdb_malloc_item_ll_type *next;
} pwrdb_malloc_item_ll_type;

/* -----------------------------------------------------------------------
** Communication between PWRDB task and code in other contexts
** ----------------------------------------------------------------------- */

typedef enum {
  PWRDB_TASK_CMD_NONE                = 0,
  PWRDB_TASK_CMD_PROCESS_SCRIPT,
#ifdef PWRDB_PRO
#ifdef FEATURE_PWRDB_MPSS
  PWRDB_TASK_CMD_WRITE_LOGS_TO_FS,
  PWRDB_TASK_CMD_READ_FILE_FROM_FS,
#endif
#endif
} pwrdb_task_cmd_type;

typedef struct {
  q_link_type           link;
  pwrdb_task_cmd_type   cmd;
  uint32                param1;
  uint32                param2;
} pwrdb_task_queue_type;


/* -----------------------------------------------------------------------
** Overall PWRDB state
** ----------------------------------------------------------------------- */

typedef enum {
  PWRDB_STATE_INIT = 0,
  PWRDB_STATE_READY_FOR_SCRIPTS,
  PWRDB_STATE_PARSING_FS_COMMANDS,
  PWRDB_STATE_RUNNING,
  PWRDB_STATE_LOGS_READY,
  PWRDB_STATE_PROC_EVENT,
  PWRDB_STATE_PROC_EVENT_STOP_PENDING,
} pwrdb_state_type;

/* Used by pwrdb_unpack_script_commands and 
   pwrdb_pack_log_items to return result status.
 */
typedef enum {
  PWRDB_RES_OK,
  PWRDB_RES_OK_CONTINUE,
  PWRDB_RES_OK_DONE,
  PWRDB_RES_PARTIAL,
  PWRDB_RES_ERROR,
  PWRDB_RES_FATAL
} pwrdb_res_type;

typedef struct
{
  uint64 timsestamp;
  uint64 command;
  uint64 data;
}pwrdb_ulog_packet;

typedef enum
{
  PWRDB_LOG_TO_ULOG = 0,
  PWRDB_LOG_TO_ULOG_OVER_QDSS,
  PWRDB_LOG_TO_STM_LOG,
  PWRDB_LOG_TO_RAM,
  PWRDB_LOG_MAX
}pwrdb_log_format_type;

/*==========================================================================

                     VARIABLES

==========================================================================*/

extern pwrdb_state_type  pwrdb_state;
extern char             *pwrdb_error_str;

/*==========================================================================

                     MACROS

==========================================================================*/

/* Macros for deug messages. The names have the format PWRDB_MSG_ln where
   l is the level Error/High/Medium/Low
   n is the number of sprintf style arguments (diag supports up to 9)
  */
#define PWRDB_MSG_E0( s )            MSG(MSG_SSID_PWRDB, MSG_MASK_3, s)
#define PWRDB_MSG_E1( s,a )          MSG_1(MSG_SSID_PWRDB, MSG_MASK_3, s, a)
#define PWRDB_MSG_E2( s,a,b )        MSG_2(MSG_SSID_PWRDB, MSG_MASK_3, s, a,b)
#define PWRDB_MSG_E3( s,a,b,c )      MSG_3(MSG_SSID_PWRDB, MSG_MASK_3, s, a,b,c)

#define PWRDB_MSG_H0( s )            MSG(MSG_SSID_PWRDB, MSG_MASK_2, s)
#define PWRDB_MSG_H1( s,a )          MSG_1(MSG_SSID_PWRDB, MSG_MASK_2, s, a)
#define PWRDB_MSG_H2( s,a,b )        MSG_2(MSG_SSID_PWRDB, MSG_MASK_2, s, a,b)
#define PWRDB_MSG_H3( s,a,b,c )      MSG_3(MSG_SSID_PWRDB, MSG_MASK_2, s, a,b,c)

#define PWRDB_ASSERT( x )            ASSERT(x)

/*==========================================================================

                     FUNCTIONS

==========================================================================*/

/* See .c files for header comments */

/* pwrdb.c */
#ifdef PWRDB_PRO
void pwrdb_check_fs_for_script( const char *path );
#endif
boolean pwrdb_event_is_active( void );

void pwrdb_init( void );

void pwrdb_open_DAL_TLMM( void );

void pwrdb_register_sleep( void );

pwrdb_res_type pwrdb_setup_event( uint32 source, uint32 id );

void pwrdb_state_change( pwrdb_state_type new_state );

void pwrdb_task_cmd_send( pwrdb_task_cmd_type cmd, uint32 p1, uint32 p2 );

void pwrdb_task_cmd_process( pwrdb_task_cmd_type cmd, uint32 p1, uint32 p2 );

boolean pwrdb_timer_id_is_ok( uint32 tid );

pwrdb_res_type pwrdb_npa_get_client_handle( npa_client_handle *phNPAClient, 
                                            const char        *npa_resource_name, 
                                            uint8              sync, 
                                            npa_client_type    client_type);

pwrdb_res_type pwrdb_npa_get_complete_request_client_handle( npa_client_handle *phNPAClient, 
                                                             const char        *npa_resource_name,
                                                             uint8              sync);

/* pwrdb_pack.c */
pwrdb_res_type pwrdb_unpack_script_commands( pwrdb_event_ll_type **event_ptr,
                                             uint32                clen,
                                             uint8                *buf,
                                             uint32                blen,
                                             uint32               *bytes_read,
                                             uint32               *cmd_cntr );

uint32 pwrdb_pack_log_items(  uint8          *buf, 
                              uint32          blen,
                              pwrdb_log_type *log,
                              uint32          llen,
                              uint32          lix,
                              pwrdb_res_type *res );

void pwrdb_pack_log_items_reset( void );

void pwrdb_addto_malloc_array(void *arrayaddr);

char* pwrdb_npa_malloc2cpy_str( const char *fromStr );

void pwrdb_log_message(pwrdb_message_type type, char *message);

void  pwrdb_log_msg_3(pwrdb_message_type type, char *message, 
                      uint32 value1, uint32 value2, uint32 value3);

#ifdef PWRDB_PRO
/* For PWRDB NPA node. Internal test only */
boolean            pwrdb_npa_init (void);

npa_resource_state pwrdb_npa_node_max ( struct npa_resource *resource, npa_client_handle client, npa_resource_state state);
/* End NPA node. Internal test only */
#endif

void pwrdb_mutex_init( void );

pwrdb_res_type pwrdb_ulog_init( void );

pwrdb_res_type pwrdb_qdss_init( void );

void pwrdb_log_command( uint64 cmd , uint64 data);

#ifdef PWRDB_PRO
void pwrdb_sleep_lpr_init( void *context,
                           unsigned int event_type, 
                           void *data,       
                           unsigned int data_size );
#endif

#if 0
void pwrdb_mpss_xo_shutdown_enter( uint64 duration_sclk );

void pwrdb_mpss_xo_shutdown_exit( void );

void pwrdb_mpss_pc_enter( uint64 duration_sclk );

void pwrdb_mpss_pc_exit( void );

void pwrdb_mpss_vdd_min_enter( uint64 duration_sclk );

void pwrdb_mpss_vdd_min_exit( void );
#endif


void pwrdb_log_to_ulog( uint32, uint64 );

void pwrdb_log_Ulog_to_QDSS( uint32, uint64 );

void pwrdb_log_to_QDSS_STM( uint32, uint64 );

void pwrdb_log_to_ram( uint32 a, uint64 b);

pwrdb_event_ll_type *pwrdb_find_existing_event( uint32 source, uint32 id );

uint16 pwrdb_update_and_get_cmd_number( void );

uint16 pwrdb_generate_command_id( uint16 sequential_cmd_id, uint16 pwrdb_cmd_id, uint32 execution_num );

void pwrdb_process_evt_src( uint32 evt_src );

#ifdef PWRDB_PRO
char* pwrdb_get_npa_marker( void );
#endif

#endif /* PWRDBI_H */
