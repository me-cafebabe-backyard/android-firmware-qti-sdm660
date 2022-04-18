#ifndef PWRDB_DIAG_H
#define PWRDB_DIAG_H
/*===========================================================================

             P W R   D E B U G   D I A G   H E A D E R 
                      
DESCRIPTION
 This file contains definitions for interction between the power debug module
 and diag.

 These definition are important for any off target tools that will interface
 with the power debugger. In general the definitions in this file should
 not be changes (adding definitions is OK).
   
EXTERNALIZED FUNCTIONS
  None

REGIONAL FUNCTIONS
  None

INITIALIZATION AND SEQUENCING REQUIREMENTS
 N/A

  Copyright (c) 2014 by QUALCOMM Technologies, Incorporated.  All Rights Reserved.
  
===========================================================================*/

/*===========================================================================

                      EDIT HISTORY FOR FILE

$Header: //components/rel/core.qdsp6/1.0.c2/powertools/pwrdb/src/pwrdb_diag.h#1 $

when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
12/02/14   dy      Add Downsampling command for SystemDB
09/29/14   dy      Add RPM Dump and Err Fatal commands for SystemDB
04/04/14   gw      Cleaned up by commenting odsolete #defines and removing 
                   obsolete structs.
09/24/10   hluo	   Obsolete the sbi_write and sbi_read
05/17/10   jl      Added CLK_BUSY_WAIT and NPA_QUERY_BY_NAME commands.
04/01/10   jl      Added sleep event source.
03/05/10   jl      Added NPA support.
01/12/10   jl      Added extended sleep voting function. 
11/25/09   ab      Added DALI2C read and DALI2C write commands
10/19/09   jl      Added DSLSBI read and DALSBI write commands
10/01/09   ab      Adding Physical address, numbering log feature
09/13/09   jl      Added clkrgm device manager commands.
08/21/09   gw      Fixed compiler warning in pwrdb_message_type.
08/10/09   jl/ck   Added support for apps processor, and sleep vote command.
                   Update the start timer command. Correct the format for
                   PWRDB_CMD_CLK_GET_PLL_EN
08/05/09   jl      Added format comments for commands.
07/24/09   sg      Added support for message logging.
05/01/09   gw      Refactoring based on code review comments.
03/17/09   gw      Added commands and log items for TLMM and clkregime APIs.
11/04/08   gw      Created this file 

===========================================================================*/

/* <EJECT> */
/*==========================================================================

                     INCLUDE FILES FOR MODULE

==========================================================================*/
#include "comdef.h"
#include "diagpkt.h"

/* <EJECT> */
/*===========================================================================

            DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains local definitions for constants, macros, types,
variables and other items needed by this module.

===========================================================================*/

/*===========================================================================

                     CONSTANTS

===========================================================================*/

/* ------------------------------------------------------------------------
** Diag Packet Processor IDs
**
**  In multi-processor systems there may be pwrdb tasks running on more
**  than one processor. The processor ID is ORed with the commands below
**  to create a unique command code that identifies both the command and
**  the processor that the command is intended for.
**
**  Diag defines a command as 16 bits. We use the top 4 bits for the ID
**  and the remianing bits for the actual command.
** ------------------------------------------------------------------------ */
#define PWRDB_DIAG_PKT_MODEM_ID                0x0000
#define PWRDB_DIAG_PKT_APPS_ID                 0x1000
#define PWRDB_DIAG_PKT_ADSP_ID                 0x2000
#define PWRDB_DIAD_PKT_WCNSS_ID                0x3000
#define PWRDB_DIAG_PKT_SLPI_ID                 0x4000
#define PWRDB_DIAG_PKT_LPASS_ID                PWRDB_DIAG_PKT_ADSP_ID
#define PWRDB_DIAG_PKT_PRONTO_ID               PWRDB_DIAD_PKT_WCNSS_ID

/* ------------------------------------------------------------------------
** Diag Packet IDs
**
**  These command code must be ORed with the processor ID (see above).
** ------------------------------------------------------------------------ */
#define PWRDB_DIAG_PKT_VER                     0x0000
#define PWRDB_DIAG_PKT_RESET                   0x0001
#define PWRDB_DIAG_PKT_SCRIPT                  0x0002
#define PWRDB_DIAG_PKT_LOG                     0x0003
#define PWRDB_DIAG_PKT_LOG_TO_FS               0x0004
#define PWRDB_DIAG_PKT_RUN                     0x0005
#define PWRDB_DIAG_PKT_STOP                    0x0006
#define PWRDB_DIAG_PKT_TEST_EVENT              0x0007
#define PWRDB_DIAG_PKT_READ_FILE               0x0008
#define PWRDB_DIAG_PKT_CLK_OUTPUT_GPIO         0x0009
#define PWRDB_DIAG_PKT_CHANGE_LOG_FORMAT       0x000A

/* ------------------------------------------------------------------------
** Commands to use in pwrdb command scripts
** ------------------------------------------------------------------------ */

/* meta commands */
#define PWRDB_CMD_NULL_CMD                     0
#define PWRDB_CMD_EVENT                        0x0021
#define PWRDB_CMD_START_TASK_CMDS              0x0022
#define PWRDB_CMD_END_OF_CMDS                  0x0023
#define PWRDB_CMD_START_TIMER                  0x0024
#define PWRDB_CMD_SIMULATE_EVENT               0x0025 /* OBSOLETE */
#define PWRDB_CMD_STOP_LOGGING                 0x0026
#define PWRDB_CMD_STOP_AND_LOG_TO_FS           0x0027
#define PWRDB_CMD_ENABLE_PRO                   0x0028

/* TLMM commands */
#define PWRDB_CMD_TLMM_SET_CURR_CONFIG         0x0100
#define PWRDB_CMD_TLMM_GET_CURR_CONFIG         0x0101
#define PWRDB_CMD_TLMM_SET_INACT_CONFIG        0x0102 /* OBSOLETE */
#define PWRDB_CMD_TLMM_GET_INACT_CONFIG        0x0103 /* OBSOLETE */
#define PWRDB_CMD_TLMM_OUTPUT                  0x0104
#define PWRDB_CMD_TLMM_INPUT                   0x0105
#define PWRDB_CMD_TLMM_SET_PIN_STATUS          0x0106 /* OBSOLETE */
#define PWRDB_CMD_TLMM_GET_PIN_STATUS          0x0107
#define PWRDB_CMD_TLMM_LOCK                    0x0108
#define PWRDB_CMD_TLMM_UNLOCK                  0x0109
#define PWRDB_CMD_TLMM_IS_LOCKED               0x010A

/* I2C commands */
#define PWRDB_CMD_I2C_DEV_CONFIG               0x0130 /* OBSOLETE */
#define PWRDB_CMD_I2C_DEV_WRITE                0x0131 /* OBSOLETE */
#define PWRDB_CMD_I2C_DEV_READ                 0x0132 /* OBSOLETE */

/* clkregime commands */
#define PWRDB_CMD_CLK_SET_CLK_EN               0x0140
#define PWRDB_CMD_CLK_GET_CLK_EN               0x0141
#define PWRDB_CMD_CLK_GET_CLK_FREQ             0x0143
#define PWRDB_CMD_CLK_LOG_STATE                0x0144
/* vk: Get the clock output on the GPIO */
#define PWRDB_CMD_CLK_OUTPUT_GPIO              0x0146
 
#define PWRDB_CMD_CLK_BUSY_WAIT                0x0148

/* peek / poke commands */
#define PWRDB_CMD_PEEK8                        0x0150
#define PWRDB_CMD_PEEK16                       0x0151
#define PWRDB_CMD_PEEK32                       0x0152
#define PWRDB_CMD_PEEK32_RANGE                 0x0153
#define PWRDB_CMD_POKE32_RANGE                 0x0157
#define PWRDB_CMD_POKE8_M                      0x0158
#define PWRDB_CMD_POKE16_M                     0x0159
#define PWRDB_CMD_POKE32_M                     0x015A

/* string commands */
#define PWRDB_CMD_STRING                       0x0160
#define PWRDB_CMD_DATA3_STRING                 0x0161

/* NPA client commands */
#define PWRDB_CMD_NPA_ISSUE_REQUIRED_REQUEST   0x0180
#define PWRDB_CMD_NPA_MODIFY_REQUIRED_REQUEST  0x0181
#define PWRDB_CMD_NPA_ISSUE_IMPULSE_REQUEST    0x0182
#define PWRDB_CMD_NPA_ISSUE_ISOC_REQUEST       0x0183
#define PWRDB_CMD_NPA_ISSUE_LIMIT_MAX_REQUEST  0x0184
#define PWRDB_CMD_NPA_COMPLETE_REQUEST         0x0185
#define PWRDB_CMD_NPA_QUERY_BY_NAME            0x0186

/* Misc commands */
#define PWRDB_CMD_CONFIGURE_HW_EVENTS_MUX      0x190
#define PWRDB_CMD_TRIGGER_LOG_SIGNALS          0x191
#define PWRDB_CMD_CHANGE_LOG_FORMAT            0x192 /* OBSOLETE */
#define PWRDB_CMD_SET_ULOG_OUTPUT_TO_QDSS      0x193 /* OBSOLETE */

/* RPM (SystemDB) Commands */
#define PWRDB_CMD_RPM_SPMI_READ                0x1
#define PWRDB_CMD_RPM_SPMI_WRITE               0x2
#define PWRDB_CMD_RPM_TLMM_READ                0x3
#define PWRDB_CMD_RPM_TLMM_WRITE               0x4
#define PWRDB_CMD_RPM_MEMORY_PEEK              0x5
#define PWRDB_CMD_RPM_MEMORY_POKE              0x6
#define PWRDB_CMD_RPM_END_OF_CMD               0x7
#define PWRDB_CMD_RPM_FLUSH_CMDS               0x8
#define PWRDB_CMD_RPM_CLK_LOG_STATE            0x9
#define PWRDB_CMD_RPM_DUMP                     0xA
#define PWRDB_CMD_RPM_ERR_FATAL                0xB
#define PWRDB_CMD_RPM_DOWNSAMPLE               0xC

/* ------------------------------------------------------------------------
** IDs for log items
** ------------------------------------------------------------------------ */

/* meta items */
#define PWRDB_LOG_NULL                         0x0000
#define PWRDB_LOG_EVENT                        0x0001

/* TLMM */
#define PWRDB_LOG_TLMM_GET_CURR_CONFIG         0x0101
#define PWRDB_LOG_TLMM_GET_INACT_CONFIG        0x0103 /* OBSOLETE */
#define PWRDB_LOG_TLMM_INPUT                   0x0105
#define PWRDB_LOG_TLMM_GET_PIN_STATUS          0x0107
#define PWRDB_LOG_TLMM_IS_LOCKED               0x010A

/* SBI */
#define PWRDB_LOG_SBI_READ                     0x0121 /* OBSOLETE */
#define PWRDB_LOG_DALSBI_READ                  0x0123 /* OBSOLETE */
#define PWRDB_LOG_DALSBI_READWRITE             0x0124 /* OBSOLETE */

/* I2C */
#define PWRDB_LOG_I2C_DEV_READ                 0x0132 /* OBSOLETE */

/* clkregime */
#define PWRDB_LOG_CLK_GET_CLK_EN               0x0141
#define PWRDB_LOG_CLK_GET_CLK_FREQ             0x0143
#define PWRDB_LOG_CLK_GET_PLL_EN               0x0145 /* OBSOLETE */

/* peek */
#define PWRDB_LOG_PEEK8                        0x0150
#define PWRDB_LOG_PEEK16                       0x0151
#define PWRDB_LOG_PEEK32                       0x0152
#define PWRDB_LOG_PEEK32_RANGE                 0x0153

/* strings */
#define PWRDB_LOG_STRING                       0x0160
#define PWRDB_LOG_DATA3_STRING                 0x0161

/* 0x0180-0x0185 are saved for other NPA commands that are not logged for now*/
#define PWRDB_LOG_NPA_QUERY_BY_NAME            0x0186

/* ------------------------------------------------------------------------
** Values to use in diag response packets that contain a return status
** ------------------------------------------------------------------------ */
#define PWRDB_RSP_SUCCESS                      0
#define PWRDB_RSP_ERROR                        1
#define PWRDB_RSP_OK_PARTIAL                   2


/* ------------------------------------------------------------------------
** Constants to use to specify events
** ------------------------------------------------------------------------ */

/* Event sources */
#define PWRDB_EVT_SRC_NONE                                0
#define PWRDB_EVT_SRC_PWRDB_TIMER                         1
#define PWRDB_EVT_SRC_PWRDB_INTERNAL                      2
#define PWRDB_EVT_SRC_DIAG                                3
#define PWRDB_EVT_SRC_CLK_REGIME                          4
#define PWRDB_EVT_SRC_CLK_DEV_PRE_SPEED_CHANGE            5 /* OBSOLETE */
#define PWRDB_EVT_SRC_CLK_DEV_POST_SPEED_CHANGE           6 /* OBSOLETE */
#define PWRDB_EVT_SRC_SLEEP                               7

/* Rpm Command Interface */
#define PWRDB_EVT_SRC_RPM                                 8

/* Events for internal event source */
#define PWRDB_INT_EVT_ID_ENTER_RUNNING                    1
#define PWRDB_INT_EVT_ID_TEST_EVENT_A                     2

#define PWRDB_INT_EVT_ID_SLEEP_PC_ENTER                   3
#define PWRDB_INT_EVT_ID_SLEEP_PC_EXIT                    4

#define PWRDB_INT_EVT_ID_SLEEP_XO_SHUTDOWN_ENTER          5
#define PWRDB_INT_EVT_ID_SLEEP_XO_SHUTDOWN_EXIT           6

#define PWRDB_INT_EVT_ID_SLEEP_PROC_HALT_ENTER            8
#define PWRDB_INT_EVT_ID_SLEEP_PROC_HALT_EXIT             9

#define PWRDB_INT_EVT_ID_SLEEP_VDDMIN_ENTER               11
#define PWRDB_INT_EVT_ID_SLEEP_VDDMIN_EXIT                12

/* IDs for the LOGS to be selected for sending a trigger signal */
/* Used with the comamnd PWRDB_CMD_TRIGGER_LOG_SIGNALS */
#define PWRDB_TRIGGER_NPA_SIGNAL                          0x1
#define PWRDB_TRIGGER_UDAS_SIGNAL                         0x2
#define PWRDB_TRIGGER_QDSS_SIGNAL                         0x4


/* Indicates the type of message returned to the user */
typedef enum {
  PWRDB_INFO_MESSAGE         = 0x1,
  PWRDB_ERROR_MESSAGE        = 0x2,
  PWRDB_WARNING_MESSAGE      = 0x4, /* Next items will continue like 0x8, 0x10 ....*/
  PWRDB_ALL_MESSAGE          = 0x7fffffff
} pwrdb_message_type;


/*===========================================================================

                    TYPES

===========================================================================*/
/* -----------------------------------------------------------------------
** Commands for pwrdb command scripts
** ----------------------------------------------------------------------- */

/* The following structures define the parameters associated with each command 

   NOTE: Since these are part of the interface to external tools these structures
   are declared as PACKED so that the exact byte positions are known independent
   of the compiler that is used. 
 */

/* cmd:PWRDB_CMD_HDR format:vv */
typedef PACKED struct {
  uint16              cmd_id;
  uint16              len;
} pwrdb_cmd_hdr_type;

/* cmd:PWRDB_CMD_NULL_CMD format:vv */
typedef PACKED struct { 
  pwrdb_cmd_hdr_type  hdr;
} pwrdb_cmd_null_cmd_type;

/* cmd:PWRDB_CMD_EVENT format:vvVVVV */
typedef PACKED struct {
  pwrdb_cmd_hdr_type  hdr;
  uint32              source;
  uint32              id;
  uint32              reserved1;
  uint32              reserved2;
} pwrdb_cmd_event_type;

/* cmd:PWRDB_CMD_START_TASK_CMDS format:vv */
typedef PACKED struct { 
  pwrdb_cmd_hdr_type  hdr;
} pwrdb_cmd_start_task_cmds_type;

/* cmd:PWRDB_CMD_END_OF_CMDS  format:vv */
typedef PACKED struct { 
  pwrdb_cmd_hdr_type  hdr;
} pwrdb_cmd_end_of_cmds_type;

/* cmd:PWRDB_CMD_START_TIMER format:vvVvCC */
typedef PACKED struct { 
  pwrdb_cmd_hdr_type  hdr;
  uint32              time;
  uint16              id;
  uint8               repeat;
  uint8               always_on;
} pwrdb_cmd_start_timer_type;

/* cmd:PWRDB_CMD_STOP_LOGGING format:vv */
typedef PACKED struct { 
  pwrdb_cmd_hdr_type  hdr;
} pwrdb_cmd_stop_logging_type;

/* cmd:PWRDB_CMD_STOP_AND_LOG_TO_FS format:vv  */
typedef PACKED struct { 
  pwrdb_cmd_hdr_type  hdr;
} pwrdb_cmd_stop_and_log_to_fs_type;

/* cmd:PWRDB_CMD_ENABLE_PRO format:vvvv */
typedef PACKED struct { 
  pwrdb_cmd_hdr_type  hdr;
  uint32              enable;
} pwrdb_cmd_enable_pro_type;

/* cmd:PWRDB_CMD_TLMM_SET_CURR_CONFIG format:vvvCCCCCC */ 
typedef PACKED struct {
  pwrdb_cmd_hdr_type  hdr;
  uint16              gpio_number;
  uint8               function;
  uint8               direction;
  uint8               pull;
  uint8               drive_strength;
  uint8               output_value;
  uint8               enable;
} pwrdb_cmd_tlmm_set_curr_config_type;

/* cmd:PWRDB_CMD_TLMM_GET_CURR_CONFIG format:vvvv */
typedef PACKED struct {
  pwrdb_cmd_hdr_type  hdr;
  uint16              gpio_number;
  uint16              dest;           /*ctk - For pointer alignment changed from uint8 to uint16*/
} pwrdb_cmd_tlmm_get_curr_config_type;

/* cmd:PWRDB_CMD_TLMM_OUTPUT format:vvvv */
typedef PACKED struct {
  pwrdb_cmd_hdr_type  hdr;
  uint16              gpio_number;
  uint16              output_value;  /*ctk - For pointer alignment changed from uint8 to uint16*/
} pwrdb_cmd_tlmm_output_type;

/* cmd:PWRDB_CMD_TLMM_INPUT format:vvvv */
typedef PACKED struct {
  pwrdb_cmd_hdr_type  hdr;
  uint16              gpio_number;
  uint16              dest;          /*ctk - For pointer alignment changed from uint8 to uint16*/
} pwrdb_cmd_tlmm_input_type;

/* cmd:PWRDB_CMD_TLMM_GET_PIN_STATUS format:vvvv */
typedef PACKED struct {
  pwrdb_cmd_hdr_type  hdr;
  uint16              gpio_number;
  uint16              dest;
} pwrdb_cmd_tlmm_get_pin_status_type;

/* cmd:PWRDB_CMD_TLMM_LOCK format:vvvv */
typedef PACKED struct {
  pwrdb_cmd_hdr_type  hdr;
  uint16              gpio_number;
  uint16              pad_align;
} pwrdb_cmd_tlmm_lock_type;

/* cmd:PWRDB_CMD_TLMM_UNLOCK format:vvvv */
typedef PACKED struct {
  pwrdb_cmd_hdr_type  hdr;
  uint16              gpio_number;
  uint16              dest;
} pwrdb_cmd_tlmm_unlock_type;

/* cmd:PWRDB_CMD_TLMM_IS_LOCKED format:vvvv */
typedef PACKED struct {
  pwrdb_cmd_hdr_type  hdr;
  uint16              gpio_number;
  uint16              dest;
} pwrdb_cmd_tlmm_is_locked_type;

/* cmd:PWRDB_CMD_CLK_SET_CLK_EN format:vvvva* */
typedef struct {
  pwrdb_cmd_hdr_type  hdr;
  uint16              enable;
  uint16              clk_en_len;
  char                clk[1];
} pwrdb_cmd_clk_set_clk_en_type;

/* cmd:PWRDB_CMD_CLK_GET_CLK_EN format:vvVa* */
typedef PACKED struct {
  pwrdb_cmd_hdr_type  hdr;
  uint32              clk_en_len;
  char                clk[1];
} pwrdb_cmd_clk_get_clk_en_type;

/* cmd:PWRDB_CMD_CLK_GET_CLK_FREQ format: vvVa* */
typedef PACKED struct {
  pwrdb_cmd_hdr_type  hdr;
  uint32              clk_en_len;
  char                clk[1];
} pwrdb_cmd_clk_get_clk_freq_type;

/* cmd:PWRDB_CMD_CLK_LOG_STATE format:vvV */
typedef PACKED struct {
  pwrdb_cmd_hdr_type  hdr;
  uint32              measureFreq;
} pwrdb_cmd_clk_log_state_type;

/* cmd:PWRDB_CMD_CLK_OUTPUT_GPIO format: vvV */
typedef PACKED struct {
  pwrdb_cmd_hdr_type  hdr;
  uint32              reg_value;
} pwrdb_cmd_clk_output_gpio_type;

/* cmd:PWRDB_CMD_CLK_BUSY_WAIT format:vvV */
typedef PACKED struct {
  pwrdb_cmd_hdr_type  hdr;
  uint32              usec;
} pwrdb_cmd_clk_busy_wait_type;

/* cmd:PWRDB_CMD_PEEK8 format:vvVV */
typedef PACKED struct {
  pwrdb_cmd_hdr_type  hdr;
  uint32              addr;
  uint32              dest;      /*ctk- changed from uint8 to uint32 for buffer alignment.*/
} pwrdb_cmd_peek8_type;

/* cmd:PWRDB_CMD_PEEK16 format:vvVV */
typedef PACKED struct {
  pwrdb_cmd_hdr_type  hdr;
  uint32              addr;
  uint32              dest;      /*ctk- changed from uint8 to uint32 for buffer alignment.*/
} pwrdb_cmd_peek16_type;

/* cmd:PWRDB_CMD_PEEK32 format:vvVV */
typedef PACKED struct {
  pwrdb_cmd_hdr_type  hdr;
  uint32              addr;
  uint32              dest;      /*ctk- changed from uint8 to uint32 for buffer alignment.*/
} pwrdb_cmd_peek32_type;

/* cmd:PWRDB_CMD_PEEK32_RANGE format:vvVVV */
typedef PACKED struct {
  pwrdb_cmd_hdr_type  hdr;
  uint32              addr;
  uint32              range;
  uint32              dest;      /*ctk- changed from uint8 to uint32 for buffer alignment.*/
} pwrdb_cmd_peek32_range_type;

/* cmd:PWRDB_CMD_POKE32_RANGE format:vvVVV* */
typedef PACKED struct {
  pwrdb_cmd_hdr_type  hdr;
  uint32              addr;
  uint32              range;
  uint32              vals[1];
} pwrdb_cmd_poke32_range_type;

/* vk: Change this for Alignment, can i set it to 16bit both? */
/* cmd:PWRDB_CMD_POKE8_M format:vvVvv */
typedef PACKED struct {
  pwrdb_cmd_hdr_type  hdr;
  uint32              addr;
  uint16              val;  /* VK: This will result in 2 bytes more size..change uint8 to uint16*/
  uint16              mask; /* VK: This will result in 2 bytes more size..change uint8 to uint16*/
} pwrdb_cmd_poke8_m_type;

/* cmd:PWRDB_CMD_POKE16_M format:vvVvv */
typedef PACKED struct {
  pwrdb_cmd_hdr_type  hdr;
  uint32              addr;
  uint16              val;
  uint16              mask;
} pwrdb_cmd_poke16_m_type;

/* cmd:PWRDB_CMD_POKE32_M format:vvVVV */
typedef PACKED struct {
  pwrdb_cmd_hdr_type  hdr;
  uint32              addr;
  uint32              val;
  uint32              mask;
} pwrdb_cmd_poke32_m_type;

/* cmd:PWRDB_CMD_STRING format:vvvva* */
typedef struct {
  pwrdb_cmd_hdr_type  hdr;
  uint16              str_type;
  uint16              str_len;
  char                str[1]; 
} pwrdb_cmd_string_type;

/* cmd:PWRDB_CMD_DATA3_STRING format:vvVVVVVa* */
typedef PACKED struct {
  pwrdb_cmd_hdr_type  hdr;
  uint32              str_type;
  uint32              value1;
  uint32              value2;
  uint32              value3;
  uint32              str_len;
  char                str[1];
} pwrdb_cmd_data3_string_type;

/* cmd:PWRDB_CMD_NPA_ISSUE_REQUIRED_REQUEST format:vvVvva* */
typedef PACKED struct {
  pwrdb_cmd_hdr_type  hdr;
  uint32              state;
  uint16              sync;             
  uint16              resource_name_len;
  char                resource_name[1];  
} pwrdb_cmd_npa_issue_required_request_type;

/* cmd:PWRDB_CMD_NPA_MODIFY_REQUIRED_REQUEST format:vvlvva* */
typedef PACKED struct {
  pwrdb_cmd_hdr_type  hdr;
  int32               delta;
  uint16              sync;               /* VK: This will result in 1 bytes more size..change uint8 to uint16*/
  uint16              resource_name_len;
  char                resource_name[1];
} pwrdb_cmd_npa_modify_required_request_type;

/* cmd:PWRDB_CMD_NPA_ISSUE_IMPULSE_REQUEST format:vvvva* */
typedef PACKED struct {
  pwrdb_cmd_hdr_type  hdr;
  uint16              sync;              
  uint16              resource_name_len;
  char                resource_name[1];
} pwrdb_cmd_npa_issue_impulse_request_type;

/* cmd:PWRDB_CMD_NPA_ISSUE_ISOC_REQUEST format:vvVVvva* */
typedef PACKED struct {
  pwrdb_cmd_hdr_type  hdr;
  uint32              deadline;
  uint32              level_hint;
  uint16              sync;              /* VK: This will result in 1 bytes more size..change uint8 to uint16*/
  uint16              resource_name_len;
  char                resource_name[1];
} pwrdb_cmd_npa_issue_isoc_request_type;

/* cmd:PWRDB_CMD_NPA_ISSUE_LIMIT_MAX_REQUEST format:vvVvva* */
typedef PACKED struct {
  pwrdb_cmd_hdr_type  hdr;
  uint32              max;              /* VK: This will result in 1 bytes more size..change uint8 to uint16 */
  uint16              sync;             /* VK: This will result in 1 bytes more size..change uint8 to uint16 */
  uint16              resource_name_len;
  char                resource_name[1];
} pwrdb_cmd_npa_issue_limit_max_request_type;

/* cmd:PWRDB_CMD_NPA_COMPLETE_REQUEST format:vvvva* */
typedef PACKED struct {
  pwrdb_cmd_hdr_type  hdr;
  uint16              sync;              /* VK: This will result in 1 bytes more size..change uint8 to uint16 */
  uint16              resource_name_len;
  char                resource_name[1];
} pwrdb_cmd_npa_complete_request_type;

/* cmd:PWRDB_CMD_NPA_QUERY_BY_NAME format:vvVVa* */
typedef PACKED struct {
  pwrdb_cmd_hdr_type  hdr;
  uint32              query_id;
  uint32              resource_name_len;
  char                resource_name[1];
} pwrdb_cmd_npa_query_by_name_type;

/* cmd:PWRDB_CMD_CONFIGURE_HW_EVENTS_MUX format:vvV */
typedef PACKED struct {
  pwrdb_cmd_hdr_type  hdr;
  uint32              mux_value;
} pwrdb_cmd_configure_hw_events_mux_type;

/* cmd:PWRDB_CMD_TRIGGER_LOG_SIGNALS format:vvVV */
typedef PACKED struct {
  pwrdb_cmd_hdr_type hdr;
  uint32             log_mask;
  uint32             gpio_number;
} pwrdb_cmd_trigger_log_signals_type;

/* Pwrdb RPM Commands */

/* cmd:PWRDB_CMD_RPM_SPMI_READ format:vvvvvvV */
typedef PACKED struct {
  pwrdb_cmd_hdr_type  hdr;
  uint16              pwrdb_rpm_event_mask;
  uint16              slave_id;
  uint16              offset;
  uint16              range;
  uint32              pwrdb_rpm_execution_num;
} pwrdb_cmd_rpm_spmi_read_type;

/* cmd:PWRDB_CMD_RPM_SPMI_WRITE format:vvvvvvVV */
typedef PACKED struct {
  pwrdb_cmd_hdr_type  hdr;
  uint16              pwrdb_rpm_event_mask;
  uint16              slave_id;
  uint16              offset;
  uint16              range;
  uint32              value;
  uint32              pwrdb_rpm_execution_num;  
} pwrdb_cmd_rpm_spmi_write_type;

/* cmd:PWRDB_CMD_RPM_TLMM_READ format:vvvvVV */
typedef PACKED struct {
  pwrdb_cmd_hdr_type  hdr;
  uint16              pwrdb_rpm_event_mask;
  uint16              range;
  uint32              gpio_number;  
  uint32              pwrdb_rpm_execution_num;    
} pwrdb_cmd_rpm_tlmm_read_type;

/* cmd:PWRDB_CMD_RPM_TLMM_WRITE format:vvvvvCCCCCCV */
typedef PACKED struct {
  pwrdb_cmd_hdr_type  hdr;
  uint16              pwrdb_rpm_event_mask;
  uint16              range;
  uint16              gpio_number;
  uint8               function;
  uint8               direction;
  uint8               pull;
  uint8               drive_strength;
  uint8               output_value;
  uint8               enable;
  uint32              pwrdb_rpm_execution_num;  
} pwrdb_cmd_rpm_tlmm_write_type;

/* cmd:PWRDB_CMD_RPM_MEMORY_PEEK format:vvvvVV */
typedef PACKED struct {
  pwrdb_cmd_hdr_type  hdr;
  uint16              pwrdb_rpm_event_mask;
  uint16              range;
  uint32              addr;
  uint32              pwrdb_rpm_execution_num;  
} pwrdb_cmd_rpm_memory_peek_type;

/* cmd:PWRDB_CMD_RPM_MEMORY_POKE format:vvvvVVV */
typedef PACKED struct {
  pwrdb_cmd_hdr_type  hdr;
  uint16              pwrdb_rpm_event_mask;
  uint16              range;
  uint32              addr;
  uint32              value;
  uint32              pwrdb_rpm_execution_num;  
} pwrdb_cmd_rpm_memory_poke_type;

/* cmd:PWRDB_CMD_RPM_DUMP format:vvVV */
typedef PACKED struct {
  pwrdb_cmd_hdr_type  hdr;
  uint32              pwrdb_rpm_event_mask;
  uint32              pwrdb_rpm_execution_num;    
} pwrdb_cmd_rpm_dump_type;

/* cmd:PWRDB_CMD_RPM_ERR_FATAL format:vvVVV */
typedef PACKED struct {
  pwrdb_cmd_hdr_type  hdr;
  uint32              pwrdb_rpm_event_mask;
  uint32              param1;
  uint32              pwrdb_rpm_execution_num;    
} pwrdb_cmd_rpm_err_fatal_type;

/* cmd:PWRDB_CMD_RPM_DOWNSAMPLE format:vvV */
typedef PACKED struct {
  pwrdb_cmd_hdr_type  hdr;
  uint32              downsample;
} pwrdb_cmd_rpm_downsample_type;

/* cmd:PWRDB_CMD_RPM_END_OF_CMD format:vvVV */
typedef PACKED struct {
  pwrdb_cmd_hdr_type  hdr;
  uint32              pwrdb_rpm_event_mask;
  uint32              pwrdb_rpm_execution_num;
} pwrdb_cmd_rpm_end_of_cmd_type;

/* cmd:PWRDB_CMD_RPM_FLUSH_CMDS format:vvvv */
typedef PACKED struct {
  pwrdb_cmd_hdr_type  hdr;
  uint32              pwrdb_rpm_event_mask;
} pwrdb_cmd_rpm_flush_cmds_type;

/* cmd: PWRDB_CMD_RPM_CLK_LOG_STATE format:vvVV */
typedef PACKED struct {
  pwrdb_cmd_hdr_type  hdr;
  uint32              pwrdb_rpm_event_mask;
  uint32              pwrdb_rpm_execution_num;
} pwrdb_cmd_rpm_clk_log_state_type;

/* -----------------------------------------------------------------------
** Items for logs
** ----------------------------------------------------------------------- */

/* PWRDB_LOG_HDR */
typedef PACKED struct {
  uint16              log_id;
  uint16              len;
  uint32              time;
} pwrdb_log_hdr_type;

/* PWRDB_LOG_NULL */
typedef PACKED struct {
  pwrdb_log_hdr_type  hdr;
} pwrdb_log_null_type;

/* PWRDB_LOG_EVENT */
typedef PACKED struct {
  pwrdb_log_hdr_type  hdr;
  uint32              source;
  uint32              id;
  uint32              reserved1;
  uint32              reserved2;
} pwrdb_log_event_type;

/* PWRDB_LOG_TLMM_GET_CURR_CONFIG */
typedef PACKED struct {
  pwrdb_log_hdr_type  hdr;
  uint16              gpio_number;
  uint8               function;
  uint8               direction;
  uint8               pull;
  uint8               drive_strength;
  uint8               output_value;
  uint8               status;
} pwrdb_log_tlmm_get_curr_config_type;

/* PWRDB_LOG_TLMM_INPUT */
typedef PACKED struct {
  pwrdb_log_hdr_type  hdr;
  uint16              gpio_number;
  uint16              input_value;
} pwrdb_log_tlmm_input_type;

/* PWRDB_CMD_TLMM_GET_PIN_STATUS */
typedef PACKED struct {
  pwrdb_log_hdr_type  hdr;
  uint16              gpio_number;
  uint16              pin_status; 
} pwrdb_log_tlmm_get_pin_status_type;

/* PWRDB_CMD_TLMM_IS_LOCKED */
typedef PACKED struct {
  pwrdb_log_hdr_type  hdr;
  uint16              gpio_number;
  uint16              locked; 
} pwrdb_log_tlmm_is_locked_type;

/* PWRDB_LOG_CLK_GET_CLK_EN */
typedef PACKED struct {
  pwrdb_log_hdr_type  hdr;
  uint32              enable;
  char                clk[1];
} pwrdb_log_clk_get_clk_en_type;

/* PWRDB_LOG_CLK_GET_CLK_FREQ */
typedef PACKED struct {
  pwrdb_log_hdr_type  hdr;
  uint32              freq;
  char                clk[1];
} pwrdb_log_clk_get_clk_freq_type;

/* PWRDB_LOG_PEEK8 */
typedef PACKED struct {
  pwrdb_log_hdr_type  hdr;
  uint32              addr;
  uint32              physaddr;
  uint32              val; /* VK: This will result in 3 bytes more size.. chnged uint8 to 32*/
} pwrdb_log_peek8_type;

/* PWRDB_LOG_PEEK16 */  
typedef PACKED struct {
  pwrdb_log_hdr_type  hdr;
  uint32              addr;
  uint32              physaddr;
  uint32              val; /* VK: This will result in 2 bytes more size.. chnged uint16 to 32*/
} pwrdb_log_peek16_type;

/* PWRDB_LOG_PEEK32 */ 
typedef PACKED struct {
  pwrdb_log_hdr_type  hdr;
  uint32              addr;
  uint32              physaddr;
  uint32              val;
} pwrdb_log_peek32_type;

/* PWRDB_LOG_PEEK32_RANGE */
typedef PACKED struct {
  pwrdb_log_hdr_type  hdr;
  uint32              addr;
  uint32              physaddr;
  uint32              num_vals;         /* number of 32 bit values being returned */
  uint32              vals[1];          
} pwrdb_log_peek32_range_type;

/* PWRDB_LOG_STRING */
typedef PACKED struct {
  pwrdb_log_hdr_type  hdr;
  uint16              str_type;
  uint16              str_len;
  char                str[1];
} pwrdb_log_string_type;

/* PWRDB_LOG_DATA3_STRING */
typedef PACKED struct {
  pwrdb_log_hdr_type  hdr;
  uint32              str_type;
  uint32              value1;
  uint32              value2;
  uint32              value3;
  uint32              str_len;
  char                str[1];
} pwrdb_log_data3_string_type;

/* PWRDB_LOG_NPA_QUERY_BY_NAME */
typedef PACKED struct {
  pwrdb_log_hdr_type  hdr;
  uint32              query_id;
  uint32              NPAQueryHandle;
  uint32              result_type;
  uint32              result_data;
  uint32              resource_name_len;
  char                resource_name[1];
} pwrdb_log_npa_query_by_name_type;

/* -----------------------------------------------------------------------
** Diag packet definitions
**   grouped in request/response pairs
**   do not access the header (hdr) fields directly
** ----------------------------------------------------------------------- */

/* PWRDB_DIAG_PKT_VER */
typedef PACKED struct {
  diagpkt_subsys_header_type hdr;
} pwrdb_diag_pkt_ver_req_type;

typedef PACKED struct {
  diagpkt_subsys_header_type hdr;
  uint16 major_version;
  uint16 minor_version;
  uint32 msm_id; 
} pwrdb_diag_pkt_ver_rsp_type;

/* PWRDB_DIAG_PKT_RESET */
typedef PACKED struct {
  diagpkt_subsys_header_type hdr;
} pwrdb_diag_pkt_reset_req_type;

typedef PACKED struct {
  diagpkt_subsys_header_type hdr;
  uint32                     status;
} pwrdb_diag_pkt_reset_rsp_type;

/* PWRDB_DIAG_PKT_SCRIPT */
typedef PACKED struct {
  diagpkt_subsys_header_type hdr;

  /* script - first command must be an event */
  uint32 cmds_len;  /*--ctk--Q6 changed to uint32 from uint16 to guarantee longword point alignment of command payload buffer*/
  uint8  cmds[1];  /* variable length buffer of packed commands */                   
} pwrdb_diag_pkt_script_req_type;

typedef PACKED struct {
  diagpkt_subsys_header_type hdr;
  uint32                     status;
} pwrdb_diag_pkt_script_rsp_type;

/* PWRDB_DIAG_PKT_LOG */
typedef PACKED struct {
  diagpkt_subsys_header_type hdr;
} pwrdb_diag_pkt_log_req_type;

typedef PACKED struct {
  diagpkt_subsys_header_type hdr;
  uint32 status;
  uint32 log_len;  /*ctk- changed from uint16 to uint32 to longword align the first access.*/
  uint8  log[1]; /* variable length buffer containing log */               
} pwrdb_diag_pkt_log_rsp_type;

/* PWRDB_DIAG_PKT_LOG_TO_FS */
typedef PACKED struct {
  diagpkt_subsys_header_type hdr;
} pwrdb_diag_pkt_log_to_fs_req_type;

typedef PACKED struct {
  diagpkt_subsys_header_type hdr;
  uint32                     status;
} pwrdb_diag_pkt_log_to_fs_rsp_type;

/* PWRDB_DIAG_PKT_RUN */
typedef PACKED struct {
  diagpkt_subsys_header_type hdr;
} pwrdb_diag_pkt_run_req_type;

typedef PACKED struct {
  diagpkt_subsys_header_type hdr;
  uint32                     status;
} pwrdb_diag_pkt_run_rsp_type;

/* PWRDB_DIAG_PKT_STOP */
typedef PACKED struct {
  diagpkt_subsys_header_type hdr;
} pwrdb_diag_pkt_stop_req_type;

typedef PACKED struct {
  diagpkt_subsys_header_type hdr;
  uint32                     status;
} pwrdb_diag_pkt_stop_rsp_type;

/* PWRDB_DIAG_PKT_TEST_EVENT */
typedef PACKED struct {
  diagpkt_subsys_header_type hdr;
  uint32                     source;
  uint32                     id;
} pwrdb_diag_pkt_test_event_req_type;

typedef PACKED struct {
  diagpkt_subsys_header_type hdr;
} pwrdb_diag_pkt_test_event_rsp_type;

/* PWRDB_DIAG_PKT_FILE_READ_RSP */
typedef PACKED struct {
  diagpkt_subsys_header_type hdr;
  uint32                     status;
} pwrdb_process_file_read_rsp_type;

/* PWRDB_DIAG_PKT_CLK_OUTPUT_GPIO */
typedef PACKED struct {
  diagpkt_subsys_header_type hdr;             /* Sub System header */
  uint32 reg_value;                           /* Reg value to be written */
} pwrdb_diag_pkt_clk_output_gpio_req_type;

typedef PACKED struct {
  diagpkt_subsys_header_type hdr;          
  //uint16 command;
  uint32 status;                           
} pwrdb_diag_pkt_clk_output_gpio_rsp_type;

/* PWRDB_DIAG_PACKET_CHANGE_LOG_FORMAT */
typedef PACKED struct  {
  pwrdb_cmd_hdr_type hdr;
  uint32             log_format;
} pwrdb_diag_pkt_change_log_format_req_type;

typedef PACKED struct  {
  pwrdb_cmd_hdr_type hdr;
  uint32             status;
} pwrdb_diag_pkt_change_log_format_rsp_type;

#endif /* PWRDB_DIAG_H */

