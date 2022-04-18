/*===========================================================================

                P W R   D E B U G   P A C K / U N P A C K

GENERAL DESCRIPTION

  This file contains functions to help with packing and unpacking. These are
  used to translate between the external (packed) format for command scripts
  and logs and the internal (unpacked) format.
  from teh

EXTERNALIZED FUNCTIONS
  None

REGIONAL FUNCTIONS
  pwrdb_pack_log_items
  pwrdb_pack_log_items_reset
  pwrdb_unpack_script_commands

INITIALIZATION AND SEQUENCING REQUIREMENTS

  Must call pwrdbdiag_init() before commands can be processed by power debugger.


  Copyright (c) 2014 by QUALCOMM Technologies, Incorporated.  All Rights Reserved.

===========================================================================*/

/*===========================================================================

                      EDIT HISTORY FOR FILE

$Header: //components/rel/core.qdsp6/1.0.c2/powertools/pwrdb/src/pwrdb_pack.c#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
12/02/14   dy      Add Downsampling command for SystemDB
09/29/14   dy      Add RPM Dump and Err Fatal commands for SystemDB
                   Remove some code for cleanup
09/24/10   hluo	   Obsolete the sbi_write and sbi_read
03/05/10   jl      Added NPA support.
01/12/10   jl      Added extended sleep voting function.
11/25/09   ab      Added DALI2C read and DALI2C write commands
10/19/09   jl      Added DSLSBI read and DALSBI write commands
10/01/09   ab      Adding Physical address, numbering log feature
09/14/09   jl      Added clkrgm device manager unpack commands.
                   Modify sleep vote to register when unpacking
                   command rather than when processing command.
08/10/09   jl/ck   Added support for sleep vote command.
                   Update the start timer command.
07/24/09    sg     Added Peek32, Poke32 range and string features.
04/29/09    gw     Created file by moving functions out of pwrdb.c.

===========================================================================*/

/* <EJECT> */
/*==========================================================================

                     INCLUDE FILES FOR MODULE

==========================================================================*/
#include "pwrdb.h"
#include "pwrdb_diag.h"
#include "pwrdbi.h"

#include <stdlib.h>                     

/* <EJECT> */
/*===========================================================================

            DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains local definitions for constants, macros, types,
variables and other items needed by this module.

===========================================================================*/

/* Various functions in this module process commands from a script.
   Scripts are provided to the debugger from a script file in EFS or
   a diag packet (PWRDB_DIAG_PKT_SCRIPT). The high level format for
   the script file and the diag packet are given below.

   [xx] means one or more of xx

   <script>  = <event>[<command>]
   <file>    = [<script>]
   <packet>  = <header>[<script>]

   <event>   = pwrdb_cmd_event_type
   <command> = pwrdb_cmd_start_task_cmds_type |
               pwrdb_cmd_start_timer_type     |
               pwrdb_cmd_stop_logging_type    |
               ...
*/

/*===========================================================================

                      VARIABLES

===========================================================================*/
static uint32                  pwrdb_log_read_ix;
static boolean                 pwrdb_log_first_read;

/* EJECT */
/*===========================================================================

                      INTERNAL FUNCTION DEFINITIONS

===========================================================================*/


/*===========================================================================

FUNCTION PWRDB_UNPACK_CMD_LEN_OK

DESCRIPTION
  Check that the value in the length field of the command matches the size
  of the type.

PARAMETERS
  Pointer to the command to check

RETURN VALUE
  TRUE  - OK
  FALSE - length mismatch

===========================================================================*/
boolean pwrdb_unpack_cmd_len_ok( pwrdb_cmd_null_cmd_type *in_cmd_ptr )
{

  uint32 tlen = 0;

  switch (in_cmd_ptr->hdr.cmd_id)
  {
    case PWRDB_CMD_NULL_CMD:
      tlen = (uint32) sizeof(pwrdb_cmd_null_cmd_type);
    break;

    case PWRDB_CMD_START_TASK_CMDS:
      tlen = (uint32) sizeof(pwrdb_cmd_start_task_cmds_type);
    break;

    case PWRDB_CMD_END_OF_CMDS:
      tlen =  (uint32) sizeof(pwrdb_cmd_end_of_cmds_type);
    break;
    
    case PWRDB_CMD_START_TIMER:
      tlen = (uint32) sizeof(pwrdb_cmd_start_timer_type);
    break;

    case PWRDB_CMD_ENABLE_PRO:
      tlen = (uint32) sizeof(pwrdb_cmd_enable_pro_type);
    break;
    
    case PWRDB_CMD_TLMM_GET_CURR_CONFIG:
      tlen = (uint32) sizeof(pwrdb_cmd_tlmm_get_curr_config_type); /*ctk- size of returns 1 byte more that structure size, could be due to.*/
    break; 

    case PWRDB_CMD_TLMM_IS_LOCKED:
      tlen = (uint32) sizeof(pwrdb_cmd_tlmm_is_locked_type);
    break;

    case PWRDB_CMD_CLK_GET_CLK_EN:
    {
      pwrdb_cmd_clk_get_clk_en_type *clk_ptr = NULL;
      clk_ptr = (pwrdb_cmd_clk_get_clk_en_type *)in_cmd_ptr;
      tlen = (uint32) (sizeof(pwrdb_cmd_clk_get_clk_en_type));
      tlen += ((clk_ptr->clk_en_len - 4) * sizeof(uint8));
    }
    break;
  
    case PWRDB_CMD_CLK_GET_CLK_FREQ:
    {
      pwrdb_cmd_clk_get_clk_freq_type *clk_ptr = NULL;
      clk_ptr = (pwrdb_cmd_clk_get_clk_freq_type *)in_cmd_ptr;
      tlen = (uint32) (sizeof(pwrdb_cmd_clk_get_clk_freq_type));
      tlen += ((clk_ptr->clk_en_len - 4) * sizeof(uint8));
    }
    break;

    case PWRDB_CMD_CLK_BUSY_WAIT:
      tlen = (uint32) sizeof(pwrdb_cmd_clk_busy_wait_type);
    break;
  
    case PWRDB_CMD_CLK_LOG_STATE:
      tlen = (uint32) sizeof(pwrdb_cmd_clk_log_state_type);
    break;
 
    case PWRDB_CMD_RPM_TLMM_READ:
      tlen = (uint32)sizeof(pwrdb_cmd_rpm_tlmm_read_type);
    break;
 
    case PWRDB_CMD_RPM_END_OF_CMD:
      tlen = (uint32)sizeof(pwrdb_cmd_rpm_end_of_cmd_type);
    break; 

    case PWRDB_CMD_RPM_SPMI_READ:
      tlen = (uint32)sizeof(pwrdb_cmd_rpm_spmi_read_type);
    break;
 
    case PWRDB_CMD_RPM_FLUSH_CMDS:
      tlen = (uint32)sizeof(pwrdb_cmd_rpm_flush_cmds_type);
    break; 
 
    case PWRDB_CMD_RPM_CLK_LOG_STATE:
      tlen = (uint32)sizeof(pwrdb_cmd_rpm_clk_log_state_type);
    break;
    
    case PWRDB_CMD_RPM_DUMP:
      tlen = (uint32)sizeof(pwrdb_cmd_rpm_dump_type);
    break;
    
    case PWRDB_CMD_RPM_ERR_FATAL:
      tlen = (uint32)sizeof(pwrdb_cmd_rpm_err_fatal_type);
    break;
    
    case PWRDB_CMD_RPM_DOWNSAMPLE:
      tlen = (uint32)sizeof(pwrdb_cmd_rpm_downsample_type);
    break;
    
#ifdef PWRDB_PRO
  #ifdef FEATURE_PWRDB_MPSS
    case PWRDB_CMD_STOP_AND_LOG_TO_FS:
      tlen =  (uint32) sizeof(pwrdb_cmd_stop_and_log_to_fs_type);
    break;
  #endif

    case PWRDB_CMD_TLMM_SET_CURR_CONFIG:
      tlen = (uint32) sizeof(pwrdb_cmd_tlmm_set_curr_config_type);
    break;

    case PWRDB_CMD_TLMM_OUTPUT:
      tlen = (uint32) sizeof(pwrdb_cmd_tlmm_output_type);
    break;

    case PWRDB_CMD_TLMM_INPUT:
      tlen = (uint32) sizeof(pwrdb_cmd_tlmm_input_type);
    break;
 
    case PWRDB_CMD_TLMM_GET_PIN_STATUS:
      tlen = (uint32) sizeof(pwrdb_cmd_tlmm_get_pin_status_type);
    break;

    case PWRDB_CMD_TLMM_LOCK:
      tlen = (uint32) sizeof(pwrdb_cmd_tlmm_lock_type);
    break;
 
    case PWRDB_CMD_TLMM_UNLOCK:
      tlen = (uint32) sizeof(pwrdb_cmd_tlmm_unlock_type);
    break;

    case PWRDB_CMD_CLK_SET_CLK_EN:
    {
      pwrdb_cmd_clk_set_clk_en_type *clk_ptr = NULL;
      clk_ptr = (pwrdb_cmd_clk_set_clk_en_type *)in_cmd_ptr;
      tlen = (uint32) (sizeof(pwrdb_cmd_clk_set_clk_en_type));
      tlen += ((clk_ptr->clk_en_len - 2) * sizeof(uint8));
    }
    break;

    case PWRDB_CMD_CLK_OUTPUT_GPIO:
      tlen = (uint32) sizeof(pwrdb_cmd_clk_output_gpio_type);
    break;

    case PWRDB_CMD_PEEK8:
      tlen = (uint32) sizeof(pwrdb_cmd_peek8_type);
    break;

    case PWRDB_CMD_PEEK16:
      tlen = (uint32) sizeof(pwrdb_cmd_peek16_type);
    break;

    case PWRDB_CMD_PEEK32:
      tlen = (uint32) sizeof(pwrdb_cmd_peek32_type);
    break;

    case PWRDB_CMD_PEEK32_RANGE:
      tlen = (uint32) sizeof(pwrdb_cmd_peek32_range_type);
    break;

    case PWRDB_CMD_POKE32_RANGE:
    {
      /* Finding the size of whole packet which includes size of structure as well as the values passed */
      pwrdb_cmd_poke32_range_type *ptr = NULL;
      ptr = (pwrdb_cmd_poke32_range_type *)in_cmd_ptr;
      if (ptr->range > 0) 
      {
          tlen = (uint32)sizeof(pwrdb_cmd_poke32_range_type) + (ptr->range - 1) * sizeof(uint32); 
      }
      else
          tlen=0;
    }
    break;

    case PWRDB_CMD_POKE8_M:
      tlen = (uint32) sizeof(pwrdb_cmd_poke8_m_type);
    break;
  
    case PWRDB_CMD_POKE16_M:
      tlen = (uint32) sizeof(pwrdb_cmd_poke16_m_type);
    break;
    
    case PWRDB_CMD_POKE32_M:
      tlen = (uint32) sizeof(pwrdb_cmd_poke32_m_type);
    break;

    case PWRDB_CMD_NPA_ISSUE_REQUIRED_REQUEST:
    {
      /* Finding the size of whole packet which includes size of structure as well as the size of the string passed */
      pwrdb_cmd_npa_issue_required_request_type *strptr = NULL;
      strptr = (pwrdb_cmd_npa_issue_required_request_type *)in_cmd_ptr;
      tlen = (uint32) (sizeof(pwrdb_cmd_npa_issue_required_request_type) + (strptr->resource_name_len - 4) * sizeof(uint8));
    }
    break;
 
    case PWRDB_CMD_NPA_MODIFY_REQUIRED_REQUEST:
    {
      /* Finding the size of whole packet which includes size of structure as well as the size of the string passed */
      pwrdb_cmd_npa_modify_required_request_type *strptr = NULL;
      strptr = (pwrdb_cmd_npa_modify_required_request_type *)in_cmd_ptr;
      tlen = (uint32) (sizeof(pwrdb_cmd_npa_modify_required_request_type) + (strptr->resource_name_len - 4) * sizeof(uint8));
    }
    break;
   
    case PWRDB_CMD_NPA_ISSUE_IMPULSE_REQUEST:
    {
      /* Finding the size of whole packet which includes size of structure as well as the size of the string passed */
      pwrdb_cmd_npa_issue_impulse_request_type *strptr = NULL;
      strptr = (pwrdb_cmd_npa_issue_impulse_request_type *)in_cmd_ptr;
      tlen = (uint32) (sizeof(pwrdb_cmd_npa_issue_impulse_request_type) + (strptr->resource_name_len - 2) * sizeof(uint8));
    }
    break;
  
    case PWRDB_CMD_NPA_ISSUE_ISOC_REQUEST:
    {
      /* Finding the size of whole packet which includes size of structure as well as the size of the string passed */
      pwrdb_cmd_npa_issue_isoc_request_type *strptr = NULL;
      strptr = (pwrdb_cmd_npa_issue_isoc_request_type *)in_cmd_ptr;
      tlen = (uint32) (sizeof(pwrdb_cmd_npa_issue_isoc_request_type) + (strptr->resource_name_len - 4) * sizeof(uint8));
    }
    break;
  
    case PWRDB_CMD_NPA_ISSUE_LIMIT_MAX_REQUEST:
    {
      /* Finding the size of whole packet which includes size of structure as well as the size of the string passed */
      pwrdb_cmd_npa_issue_limit_max_request_type *strptr = NULL;
      strptr = (pwrdb_cmd_npa_issue_limit_max_request_type *)in_cmd_ptr;
      tlen = (uint32) (sizeof(pwrdb_cmd_npa_issue_limit_max_request_type) + (strptr->resource_name_len - 4) * sizeof(uint8));
    }
    break;
   
    case PWRDB_CMD_NPA_COMPLETE_REQUEST:
    {
      /* Finding the size of whole packet which includes size of structure as well as the size of the string passed */
      pwrdb_cmd_npa_complete_request_type *strptr = NULL;
      strptr = (pwrdb_cmd_npa_complete_request_type *)in_cmd_ptr;
      tlen = (uint32) (sizeof(pwrdb_cmd_npa_complete_request_type) + (strptr->resource_name_len - 2) * sizeof(uint8));
    }
    break;
  
    case PWRDB_CMD_NPA_QUERY_BY_NAME:
    {
      /* Finding the size of whole packet which includes size of structure as well as the size of the string passed */
      pwrdb_cmd_npa_query_by_name_type *strptr = NULL;
      strptr = (pwrdb_cmd_npa_query_by_name_type *)in_cmd_ptr;
      tlen = (uint32) (sizeof(pwrdb_cmd_npa_query_by_name_type) + (strptr->resource_name_len - 4) * sizeof(uint8));
    }
    break;
   
    case PWRDB_CMD_CONFIGURE_HW_EVENTS_MUX:
      tlen = (uint32)sizeof(pwrdb_cmd_configure_hw_events_mux_type);
    break;
   
    case PWRDB_CMD_TRIGGER_LOG_SIGNALS:
      tlen = (uint32)sizeof(pwrdb_cmd_trigger_log_signals_type);
    break;
   
    case PWRDB_CMD_CHANGE_LOG_FORMAT:
      tlen = (uint32)sizeof(pwrdb_cmd_change_log_format_type);
    break;
  
    case PWRDB_CMD_RPM_TLMM_WRITE:
      tlen = (uint32)sizeof(pwrdb_cmd_rpm_tlmm_write_type);
    break;
   
    case PWRDB_CMD_RPM_MEMORY_PEEK :
      tlen = (uint32)sizeof(pwrdb_cmd_rpm_memory_peek_type);
    break;
  
    case PWRDB_CMD_RPM_MEMORY_POKE:
      tlen = (uint32)sizeof(pwrdb_cmd_rpm_memory_poke_type);
    break;

    case PWRDB_CMD_RPM_SPMI_WRITE:
      tlen = (uint32)sizeof(pwrdb_cmd_rpm_spmi_write_type);
    break;

  #if 0
    case PWRDB_CMD_STRING:
    {
      /* Finding the size of whole packet which includes size of structure as well as the size of the string passed */
      pwrdb_cmd_string_type *strptr = NULL;
      strptr = (pwrdb_cmd_string_type *)in_cmd_ptr;
      tlen = (uint32) (sizeof(pwrdb_cmd_string_type) + (strptr->str_len - 2) * sizeof(uint8));
    }
    break;
    case PWRDB_CMD_DATA3_STRING:
    {
      /* Finding the size of whole packet which includes size of structure as well as the size of the string passed */
      pwrdb_cmd_data3_string_type *strptr = NULL;
      strptr = (pwrdb_cmd_data3_string_type *)in_cmd_ptr;
      tlen = (uint32) (sizeof(pwrdb_cmd_data3_string_type) + (strptr->str_len - 4) * sizeof(uint8));
    }
    break;
  #endif
#endif /* #ifdef PWRDB_PRO */
    
    default:
      tlen = 0;
    break;
  }

  if (in_cmd_ptr->hdr.len != tlen)
  {
    PWRDB_MSG_E3("Bad command length for %i. %i != %i.",
                 in_cmd_ptr->hdr.cmd_id,
                 in_cmd_ptr->hdr.len,
                 tlen);
    return FALSE;
  }

  return TRUE;
} /* pwrdb_unpack_cmd_len_ok */

/*===========================================================================

The next set of functions are helpers to pwrdb_unpack_cmds. Each one is used
to unpack the parameters for a specific commands. They may also perform
error checking on the parameters.

The functions take a pointer to pwrdb_cmd_null_cmd_type as there only
parameter. They cast this to the appropriate type based on the command.

Functions that return a value return PWRDB_RES_OK or PWRDB_RES_ERROR.

===========================================================================*/

/*===========================================================================

FUNCTION PWRDB_UNPACK_CMD_EVENT

===========================================================================*/
static pwrdb_event_ll_type *pwrdb_unpack_cmd_event( pwrdb_cmd_null_cmd_type *in_cmd_ptr )
{
  PWRDB_ASSERT( in_cmd_ptr  != 0 );

  pwrdb_cmd_event_type  *evt_ptr = (pwrdb_cmd_event_type*)in_cmd_ptr;
  pwrdb_event_ll_type   *temp_event;
  pwrdb_res_type         res;
  DALResult              malloc_res;

  // check event is unique
  temp_event = pwrdb_find_existing_event( evt_ptr->source , evt_ptr->id );
  if (temp_event != NULL)
  {
    return NULL;
  }
  
  malloc_res = DALSYS_Malloc(sizeof( pwrdb_event_ll_type ), (void *)&temp_event);
  if( malloc_res != DAL_SUCCESS )
  {
    return NULL;
  }
  
  temp_event->event.id     = evt_ptr->id;
  temp_event->event.source = evt_ptr->source;
  temp_event->next         = NULL;
  temp_event->pwrdb_cmds   = NULL;
  
  res = pwrdb_setup_event( evt_ptr->source, evt_ptr->id );
  if (res != PWRDB_RES_OK)
  {
    (void) DALSYS_Free(temp_event);
    return NULL;
  }

  return temp_event;
}


/*===========================================================================

FUNCTION PWRDB_UNPACK_CMD_START_TIMER

===========================================================================*/
static pwrdb_res_type pwrdb_unpack_cmd_start_timer( pwrdb_cmd_type *loc_cmd_ptr,
                                                    pwrdb_cmd_null_cmd_type *in_cmd_ptr )
{
  pwrdb_res_type              status = PWRDB_RES_OK;
  pwrdb_cmd_start_timer_type *ptr    = (pwrdb_cmd_start_timer_type *)in_cmd_ptr;

  if (pwrdb_timer_id_is_ok( ptr->id ))
  {
    loc_cmd_ptr->params.start_timer.time       = ptr->time;
    loc_cmd_ptr->params.start_timer.id         = ptr->id;
    loc_cmd_ptr->params.start_timer.repeat     = ptr->repeat ? TRUE : FALSE;
    loc_cmd_ptr->params.start_timer.always_on  = ptr->always_on ? TRUE : FALSE;
  }
  else
  {
    status = PWRDB_RES_ERROR;
  }

  return status;
}



/*===========================================================================

FUNCTION PWRDB_UNPACK_CMD_ENABLE_PRO

===========================================================================*/
static pwrdb_res_type pwrdb_unpack_cmd_enable_pro( pwrdb_cmd_type *loc_cmd_ptr,
                                                    pwrdb_cmd_null_cmd_type *in_cmd_ptr )
{
  pwrdb_res_type              status = PWRDB_RES_OK;
  pwrdb_cmd_enable_pro_type *ptr    = (pwrdb_cmd_enable_pro_type *)in_cmd_ptr;

  loc_cmd_ptr->params.enable_pro.enable       = ptr->enable;

  return status;
}


/*===========================================================================

FUNCTION PWRDB_UNPACK_CMD_TLMM_GET_CURR_CONFIG

===========================================================================*/
static void pwrdb_unpack_cmd_tlmm_get_curr_config( pwrdb_cmd_type *loc_cmd_ptr,
                                                   pwrdb_cmd_null_cmd_type *in_cmd_ptr )
{
  pwrdb_cmd_tlmm_get_curr_config_type *ptr = (pwrdb_cmd_tlmm_get_curr_config_type *)in_cmd_ptr;

  loc_cmd_ptr->params.tlmm_get_curr_config.gpio_number = ptr->gpio_number;
  loc_cmd_ptr->params.tlmm_get_curr_config.dest        = ptr->dest;

  pwrdb_open_DAL_TLMM();
}


/*===========================================================================

FUNCTION PWRDB_UNPACK_CMD_TLMM_IS_LOCKED

===========================================================================*/
static void pwrdb_unpack_cmd_tlmm_is_locked( pwrdb_cmd_type *loc_cmd_ptr,
                                             pwrdb_cmd_null_cmd_type *in_cmd_ptr )
{
  pwrdb_cmd_tlmm_is_locked_type *ptr = (pwrdb_cmd_tlmm_is_locked_type *)in_cmd_ptr;

  loc_cmd_ptr->params.tlmm_is_locked.gpio_number = ptr->gpio_number;
  loc_cmd_ptr->params.tlmm_is_locked.dest        = ptr->dest;

  pwrdb_open_DAL_TLMM();
}


/*===========================================================================

FUNCTION PWRDB_UNPACK_CMD_CLK_GET_CLK_EN

===========================================================================*/
static void pwrdb_unpack_cmd_clk_get_clk_en( pwrdb_cmd_type *loc_cmd_ptr,
                                             pwrdb_cmd_null_cmd_type *in_cmd_ptr )
{
  uint32 count = 0;
  DALResult result;
  pwrdb_cmd_clk_get_clk_en_type *ptr = (pwrdb_cmd_clk_get_clk_en_type *)in_cmd_ptr;

  char *str1 = NULL;

  if (in_cmd_ptr->hdr.len > ptr->clk_en_len)
  {
      /* '1' is extra for adding '\0' at last of C string*/
      result = DALSYS_Malloc( ((ptr->clk_en_len + 1)*sizeof(char)),(void *)&str1 );
  }
  else
  {
      return;
  }
  
  if(result != DAL_SUCCESS )
  {
    return;
  }
  pwrdb_addto_malloc_array(str1);

  loc_cmd_ptr->params.clk_get_clk_en.clk_en_len      = ptr->clk_en_len;
  
  for(count=0; count<ptr->clk_en_len; count++)
  {
       *(str1+ count) = *(ptr->clk + count);
  }
  
  *(str1 + ptr->clk_en_len) = '\0';
  
  loc_cmd_ptr->params.clk_get_clk_en.clk = str1;
  
}


/*===========================================================================

FUNCTION PWRDB_UNPACK_CMD_CLK_GET_CLK_FREQ

===========================================================================*/
static void pwrdb_unpack_cmd_clk_get_clk_freq( pwrdb_cmd_type *loc_cmd_ptr,
                                               pwrdb_cmd_null_cmd_type *in_cmd_ptr )
{
  uint32 count = 0;
  DALResult result;
  pwrdb_cmd_clk_get_clk_freq_type *ptr = (pwrdb_cmd_clk_get_clk_freq_type *)in_cmd_ptr;
  char *str1 = NULL;

  if (in_cmd_ptr->hdr.len > ptr->clk_en_len)
  {
      /* '1' is extra for adding '\0' at last of C string*/
      result = DALSYS_Malloc( ((ptr->clk_en_len + 1)*sizeof(char)),(void *)&str1 );
  }
  else
  {
      return;
  }
  if(result != DAL_SUCCESS )
  {
    return;
  }
  pwrdb_addto_malloc_array(str1);

  loc_cmd_ptr->params.clk_get_clk_freq.clk_en_len      = ptr->clk_en_len;
  
  for(count=0; count<ptr->clk_en_len; count++)
  {
       *(str1+ count) = *(ptr->clk + count);
  }
  
  *(str1 + ptr->clk_en_len) = '\0';
  
  loc_cmd_ptr->params.clk_get_clk_freq.clk = str1;
  
}


static void pwrdb_unpack_cmd_rpm_dump( pwrdb_cmd_type *loc_cmd_ptr, pwrdb_cmd_null_cmd_type *in_cmd_ptr )
{
  pwrdb_cmd_rpm_dump_type *ptr = (pwrdb_cmd_rpm_dump_type *)in_cmd_ptr;

  loc_cmd_ptr->params.rpm_dump.pwrdb_rpm_event_mask    = ptr->pwrdb_rpm_event_mask;
  loc_cmd_ptr->cmd_id                                  = ptr->hdr.cmd_id;
  loc_cmd_ptr->params.rpm_dump.pwrdb_rpm_execution_num = ptr->pwrdb_rpm_execution_num;  
}

static void pwrdb_unpack_cmd_rpm_err_fatal( pwrdb_cmd_type *loc_cmd_ptr, pwrdb_cmd_null_cmd_type *in_cmd_ptr )
{
  pwrdb_cmd_rpm_err_fatal_type *ptr = (pwrdb_cmd_rpm_err_fatal_type *)in_cmd_ptr;

  loc_cmd_ptr->params.rpm_err_fatal.pwrdb_rpm_event_mask    = ptr->pwrdb_rpm_event_mask;
  loc_cmd_ptr->cmd_id                                       = ptr->hdr.cmd_id;
  loc_cmd_ptr->params.rpm_err_fatal.param1                  = ptr->param1;
  loc_cmd_ptr->params.rpm_err_fatal.pwrdb_rpm_execution_num = ptr->pwrdb_rpm_execution_num;  
}

static void pwrdb_unpack_cmd_rpm_downsample( pwrdb_cmd_type *loc_cmd_ptr, pwrdb_cmd_null_cmd_type *in_cmd_ptr )
{
  pwrdb_cmd_rpm_downsample_type *ptr = (pwrdb_cmd_rpm_downsample_type *)in_cmd_ptr;

  loc_cmd_ptr->cmd_id                                       = ptr->hdr.cmd_id;
  loc_cmd_ptr->params.rpm_downsample.downsample             = ptr->downsample;
}

#ifdef PWRDB_PRO
/*===========================================================================

FUNCTION PWRDB_PACK_LOG_PEEK8

===========================================================================*/
static uint32 pwrdb_pack_log_peek8( pwrdb_log_type *log_item, uint8 *bptr, int len, pwrdb_res_type *res )
{
  pwrdb_log_peek8_type *ptr = (pwrdb_log_peek8_type *)bptr;

  if ( sizeof(pwrdb_log_peek8_type) > len )
  {
    /* can't fit this into the buffer, time to stop */
    *res = PWRDB_RES_OK_CONTINUE;
    return 0;
  }
  else
  {
    ptr->hdr.len  = sizeof(pwrdb_log_peek8_type);
    ptr->addr     = log_item->data.peek8.addr;
    ptr->physaddr = log_item->data.peek8.physaddr;
    ptr->val      = log_item->data.peek8.val;

    return sizeof(pwrdb_log_peek8_type);
  }
}

/*===========================================================================

FUNCTION PWRDB_PACK_LOG_PEEK16

===========================================================================*/
static uint32 pwrdb_pack_log_peek16( pwrdb_log_type *log_item, uint8 *bptr, int len, pwrdb_res_type *res )
{
  pwrdb_log_peek16_type *ptr = (pwrdb_log_peek16_type *)bptr;

  if ( sizeof(pwrdb_log_peek16_type) > len )
  {
    /* can't fit this into the buffer, time to stop */
    *res = PWRDB_RES_OK_CONTINUE;
    return 0;
  }
  else
  {
    ptr->hdr.len  = sizeof(pwrdb_log_peek16_type);
    ptr->addr     = log_item->data.peek16.addr;
    ptr->physaddr = log_item->data.peek16.physaddr;
    ptr->val      = log_item->data.peek16.val;

    return sizeof(pwrdb_log_peek16_type);
  }
}

/*===========================================================================

FUNCTION PWRDB_PACK_LOG_PEEK32

===========================================================================*/
static int32 pwrdb_pack_log_peek32( pwrdb_log_type *log_item, uint8 *bptr, int len, pwrdb_res_type *res )
{
  pwrdb_log_peek32_type *ptr = (pwrdb_log_peek32_type *)bptr;

  if ( sizeof(pwrdb_log_peek32_type) > len )
  {
    /* can't fit this into the buffer, time to stop */
    *res = PWRDB_RES_OK_CONTINUE;
    return 0;
  }
  else
  {
    ptr->hdr.len  = sizeof(pwrdb_log_peek32_type);
    ptr->addr     = log_item->data.peek32.addr;
    ptr->physaddr = log_item->data.peek32.physaddr;
    ptr->val      = log_item->data.peek32.val;

    return sizeof(pwrdb_log_peek32_type);
  }
}

/*===========================================================================

FUNCTION PWRDB_PACK_LOG_PEEK32_RANGE

===========================================================================*/
static uint32 pwrdb_pack_log_peek32_range( pwrdb_log_type *log_item, uint8 *bptr, int len, pwrdb_res_type *res )
{
  pwrdb_log_peek32_range_type *ptr = (pwrdb_log_peek32_range_type *)bptr;
  uint32 num=0, *arrayptr=NULL, sizetoberet=0;

  /* Calculating the size of the packet */
  ptr->num_vals = log_item->data.peek32_range.num_vals;
  sizetoberet = sizeof(pwrdb_log_peek32_range_type) + (ptr->num_vals - 1) * sizeof(uint32);

  if ( sizetoberet > len )
  {
     /* can't fit this into the buffer, time to stop */
     *res = PWRDB_RES_OK_CONTINUE;
      return 0;
  }
  else
  {
     ptr->addr     = log_item->data.peek32_range.addr;
     ptr->physaddr = log_item->data.peek32_range.physaddr;
     ptr->hdr.len  = sizetoberet;
    /* Get the address where the values to be stored to */
     arrayptr = log_item->data.peek32_range.vals;

     if(arrayptr == NULL)
     {
       for(num=0;num<(ptr->num_vals);num++)
      {
        /* Incase of Malloc failures returning the Read address itself as the
        return values for the indication*/
        *(ptr->vals + num) = ptr->addr;
      }
    }
    else
    {
       for(num=0;num<(ptr->num_vals);num++)
       {
          *(ptr->vals + num) = *(arrayptr + num);
       }
    }

    return sizetoberet;
  }
}

/*===========================================================================

FUNCTION PWRDB_PACK_LOG_STRING

===========================================================================*/
static uint32 pwrdb_pack_log_string( pwrdb_log_type *log_item, uint8 *bptr, int len, pwrdb_res_type *res )
{
  pwrdb_log_string_type *ptr = (pwrdb_log_string_type *)bptr;
  uint32 sizetoberet=0;
  uint16 num=0;
  char *strptr=NULL;
  char *null_msg = "message logging failed";
  uint16 str_len=log_item->data.strng.str_len;
  uint32 str_type = log_item->data.strng.str_type;

  strptr = log_item->data.strng.str;

  if(strptr == NULL)
  {
     str_len=0;
     /* Incase of Malloc failures returning the Read address itself as the
              return values for the indication*/
     while(null_msg[str_len++]);
     strptr = null_msg;
     str_type = (uint32)PWRDB_ERROR_MESSAGE;
  }

  /* Calculating the size of the packet */
  sizetoberet = sizeof(pwrdb_log_string_type) + (str_len -1) * sizeof(char);

  if ( sizetoberet > len )
  {
     /* can't fit this into the buffer, time to stop */
     *res = PWRDB_RES_OK_CONTINUE;
     return 0;
  }
  else
  {
     ptr->str_len = str_len;
     ptr->str_type = str_type;
     ptr->hdr.len  = sizetoberet;

     /* Get the address where the values to be stored to */
     for(num=0;num<str_len;num++)
     {
         *(ptr->str + num) = *(strptr + num);
     }

     return sizetoberet;
  }
}

/*===========================================================================

FUNCTION PWRDB_PACK_LOG_DATA3_STRING

===========================================================================*/
static uint32 pwrdb_pack_log_data3_string( pwrdb_log_type *log_item, uint8 *bptr, int len, pwrdb_res_type *res )
{
  pwrdb_log_data3_string_type *ptr = (pwrdb_log_data3_string_type *)bptr;
  uint32 sizetoberet=0;
  uint16 num=0;
  char   *strptr=NULL;
  char   *null_msg = "message logging failed";
  uint16 str_len = log_item->data.data3_strng.str_len;
  uint32 str_type = log_item->data.data3_strng.str_type;

  strptr = log_item->data.data3_strng.str;

  if(strptr == NULL)
  {
     str_len=0;
     /* Incase of Malloc failures returning the Read address itself as the
              return values for the indication*/
     while(null_msg[str_len++]);
     strptr = null_msg;
     str_type = (uint32)PWRDB_ERROR_MESSAGE;
  }

  /* Calculating the size of the packet */
  sizetoberet = sizeof(pwrdb_log_data3_string_type) + (str_len -1) * sizeof(char);

  if ( sizetoberet > len )
  {
     /* can't fit this into the buffer, time to stop */
     *res = PWRDB_RES_OK_CONTINUE;
     return 0;
  }
  else
  {
     ptr->hdr.len  = sizetoberet;
     ptr->str_type = str_type;
     ptr->value1   = log_item->data.data3_strng.value1;
     ptr->value2   = log_item->data.data3_strng.value2;
     ptr->value3   = log_item->data.data3_strng.value3;
     ptr->str_len  = str_len;

     /* Get the address where the values to be stored to */
     for(num=0;num<str_len;num++)
     {
         *(ptr->str + num) = *(strptr + num);
     }

     return sizetoberet;
  }
}

/*===========================================================================

FUNCTION PWRDB_PACK_LOG_NPA_QUERY_BY_NAME

===========================================================================*/
static uint32 pwrdb_pack_log_npa_query_by_name( pwrdb_log_type *log_item, uint8 *bptr, int len, pwrdb_res_type *res )
{
  pwrdb_log_npa_query_by_name_type *ptr = (pwrdb_log_npa_query_by_name_type *)bptr;
  uint32 sizetoberet = 0;
  uint16 num         = 0;
  char *rscptr       = NULL;
  char *null_rsc     = "NPA init resource name";
  uint16 resource_name_len  = log_item->data.npa_query_by_name.resource_name_len;

  rscptr = log_item->data.npa_query_by_name.resource_name;

  if(rscptr == NULL)
  {
     resource_name_len=0;
     /* Incase of Malloc failures returning the Read address itself as the
              return values for the indication*/
     while(null_rsc[resource_name_len++]);
     rscptr = null_rsc;
  }

  /* Calculating the size of the packet */
  sizetoberet = sizeof(pwrdb_log_npa_query_by_name_type) + (resource_name_len -1) * sizeof(char);

  if ( sizetoberet > len )
  {
     /* can't fit this into the buffer, time to stop */
     *res = PWRDB_RES_OK_CONTINUE;
     return 0;
  }
  else
  {
     ptr->query_id          = log_item->data.npa_query_by_name.query_id;
     ptr->NPAQueryHandle    = (uint32)(log_item->data.npa_query_by_name.NPAQueryHandle);
     ptr->result_type       = (uint32)(log_item->data.npa_query_by_name.result.type);
     ptr->result_data       = (uint32)(log_item->data.npa_query_by_name.result.data.state);
     ptr->resource_name_len = resource_name_len;
     ptr->hdr.len           = sizetoberet;

     /* Get the address where the values to be stored to */
     for(num=0;num<resource_name_len;num++)
     {
         *(ptr->resource_name + num) = *(rscptr + num);
     }

     return sizetoberet;
  }
}

/*===========================================================================

FUNCTION PWRDB_UNPACK_CMD_CLK_SET_CLK_EN

===========================================================================*/
static void pwrdb_unpack_cmd_clk_set_clk_en( pwrdb_cmd_type *loc_cmd_ptr,
                                             pwrdb_cmd_null_cmd_type *in_cmd_ptr )
{
  uint32 count = 0;
  pwrdb_cmd_clk_set_clk_en_type *ptr = (pwrdb_cmd_clk_set_clk_en_type *)in_cmd_ptr;
  char *str1 = NULL;

  /* '1' is extra for adding '\0' at last of C string*/
  DALResult result = DALSYS_Malloc( ((ptr->clk_en_len + 1)*sizeof(char)),(void *)&str1 );
  //malloc();
  
  if( result != DAL_SUCCESS )
  {
    return;
  }
  pwrdb_addto_malloc_array(str1);

  loc_cmd_ptr->params.clk_set_clk_en.clk_en_len      = ptr->clk_en_len;
  loc_cmd_ptr->params.clk_set_clk_en.enable          = ptr->enable;

  for(count=0; count<ptr->clk_en_len; count++)
  {
     *(str1+ count) = *(ptr->clk + count);
  }
  
  *(str1 + ptr->clk_en_len) = '\0';
  
  loc_cmd_ptr->params.clk_set_clk_en.clk = str1;
  
}

/*===========================================================================

FUNCTION PWRDB_UNPACK_CMD_CLK_OUTPUT_GPIO

===========================================================================*/
static void pwrdb_unpack_cmd_clk_output_gpio
( 
  pwrdb_cmd_type          *loc_cmd_ptr,
  pwrdb_cmd_null_cmd_type *in_cmd_ptr
)
{
  pwrdb_cmd_clk_output_gpio_type *ptr = (pwrdb_cmd_clk_output_gpio_type *)in_cmd_ptr;

  loc_cmd_ptr->params.clk_output_gpio.reg_value = ptr->reg_value;
}


/*===========================================================================

FUNCTION PWRDB_UNPACK_CMD_TLMM_SET_CURR_CONFIG

===========================================================================*/
static void pwrdb_unpack_cmd_tlmm_set_curr_config( pwrdb_cmd_type *loc_cmd_ptr,
                                                   pwrdb_cmd_null_cmd_type *in_cmd_ptr )
{
  pwrdb_cmd_tlmm_set_curr_config_type *ptr = (pwrdb_cmd_tlmm_set_curr_config_type *)in_cmd_ptr;

  loc_cmd_ptr->params.tlmm_set_curr_config.gpio_number     = ptr->gpio_number;
  loc_cmd_ptr->params.tlmm_set_curr_config.function        = ptr->function;
  loc_cmd_ptr->params.tlmm_set_curr_config.direction       = ptr->direction;
  loc_cmd_ptr->params.tlmm_set_curr_config.pull            = ptr->pull;
  loc_cmd_ptr->params.tlmm_set_curr_config.drive_strength  = ptr->drive_strength;
  loc_cmd_ptr->params.tlmm_set_curr_config.output_value    = ptr->output_value;
  loc_cmd_ptr->params.tlmm_set_curr_config.enable          = ptr->enable;

  pwrdb_open_DAL_TLMM();
}

/*===========================================================================

FUNCTION PWRDB_UNPACK_CMD_TLMM_OUTPUT

===========================================================================*/
static void pwrdb_unpack_cmd_tlmm_output( pwrdb_cmd_type *loc_cmd_ptr,
                                          pwrdb_cmd_null_cmd_type *in_cmd_ptr )
{
  pwrdb_cmd_tlmm_output_type *ptr = (pwrdb_cmd_tlmm_output_type *)in_cmd_ptr;

  loc_cmd_ptr->params.tlmm_output.gpio_number  = ptr->gpio_number;
  loc_cmd_ptr->params.tlmm_output.output_value = ptr->output_value;

  pwrdb_open_DAL_TLMM();
}

/*===========================================================================

FUNCTION PWRDB_UNPACK_CMD_TLMM_INPUT

===========================================================================*/
static void pwrdb_unpack_cmd_tlmm_input( pwrdb_cmd_type *loc_cmd_ptr,
                                         pwrdb_cmd_null_cmd_type *in_cmd_ptr )
{
  pwrdb_cmd_tlmm_input_type *ptr = (pwrdb_cmd_tlmm_input_type *)in_cmd_ptr;

  loc_cmd_ptr->params.tlmm_input.gpio_number = ptr->gpio_number;
  loc_cmd_ptr->params.tlmm_input.dest        = ptr->dest;

  pwrdb_open_DAL_TLMM();
}

/*===========================================================================

FUNCTION PWRDB_UNPACK_CMD_TLMM_GET_PIN_STATUS

===========================================================================*/
static void pwrdb_unpack_cmd_tlmm_get_pin_status( pwrdb_cmd_type *loc_cmd_ptr,
                                                  pwrdb_cmd_null_cmd_type *in_cmd_ptr )
{
  pwrdb_cmd_tlmm_get_pin_status_type *ptr = (pwrdb_cmd_tlmm_get_pin_status_type *)in_cmd_ptr;

  loc_cmd_ptr->params.tlmm_get_pin_status.gpio_number = ptr->gpio_number;
  loc_cmd_ptr->params.tlmm_get_pin_status.dest        = ptr->dest;

  pwrdb_open_DAL_TLMM();
}

/*===========================================================================

FUNCTION PWRDB_UNPACK_CMD_TLMM_LOCK

===========================================================================*/
static void pwrdb_unpack_cmd_tlmm_lock( pwrdb_cmd_type *loc_cmd_ptr,
                                        pwrdb_cmd_null_cmd_type *in_cmd_ptr )
{
  pwrdb_cmd_tlmm_lock_type *ptr = (pwrdb_cmd_tlmm_lock_type *)in_cmd_ptr;

  loc_cmd_ptr->params.tlmm_lock.gpio_number = ptr->gpio_number;

  pwrdb_open_DAL_TLMM();
}

/*===========================================================================

FUNCTION PWRDB_UNPACK_CMD_TLMM_UNLOCK

===========================================================================*/
static void pwrdb_unpack_cmd_tlmm_unlock( pwrdb_cmd_type *loc_cmd_ptr,
                                          pwrdb_cmd_null_cmd_type *in_cmd_ptr )
{
  pwrdb_cmd_tlmm_unlock_type *ptr = (pwrdb_cmd_tlmm_unlock_type *)in_cmd_ptr;

  loc_cmd_ptr->params.tlmm_unlock.gpio_number = ptr->gpio_number;

  pwrdb_open_DAL_TLMM();
}



/*===========================================================================

FUNCTION PWRDB_UNPACK_CMD_PEEK8

===========================================================================*/
static void pwrdb_unpack_cmd_peek8( pwrdb_cmd_type *loc_cmd_ptr,
                                    pwrdb_cmd_null_cmd_type *in_cmd_ptr )
{
  pwrdb_cmd_peek8_type *ptr = (pwrdb_cmd_peek8_type *)in_cmd_ptr;

  loc_cmd_ptr->params.peek8.addr = ptr->addr;
}

/*===========================================================================

FUNCTION PWRDB_UNPACK_CMD_PEEK16

===========================================================================*/
static void pwrdb_unpack_cmd_peek16( pwrdb_cmd_type *loc_cmd_ptr,
                                     pwrdb_cmd_null_cmd_type *in_cmd_ptr )
{
  pwrdb_cmd_peek16_type *ptr = (pwrdb_cmd_peek16_type *)in_cmd_ptr;

  loc_cmd_ptr->params.peek16.addr = ptr->addr;
}

/*===========================================================================

FUNCTION PWRDB_UNPACK_CMD_PEEK32

===========================================================================*/
static void pwrdb_unpack_cmd_peek32( pwrdb_cmd_type *loc_cmd_ptr,
                                     pwrdb_cmd_null_cmd_type *in_cmd_ptr )
{
  pwrdb_cmd_peek32_type *ptr = (pwrdb_cmd_peek32_type *)in_cmd_ptr;

  loc_cmd_ptr->params.peek32.addr = ptr->addr;
}

/*===========================================================================

FUNCTION PWRDB_UNPACK_CMD_PEEK32_RANGE

===========================================================================*/
static void pwrdb_unpack_cmd_peek32_range( pwrdb_cmd_type *loc_cmd_ptr,
                                     pwrdb_cmd_null_cmd_type *in_cmd_ptr )
{
  pwrdb_cmd_peek32_range_type *ptr = (pwrdb_cmd_peek32_range_type *)in_cmd_ptr;

  loc_cmd_ptr->params.peek32_range.addr = ptr->addr;
  loc_cmd_ptr->params.peek32_range.range = ptr->range;
}

/*===========================================================================

FUNCTION PWRDB_UNPACK_CMD_POKE32_RANGE

===========================================================================*/
static pwrdb_res_type pwrdb_unpack_cmd_poke32_range( pwrdb_cmd_type *loc_cmd_ptr,
                                     pwrdb_cmd_null_cmd_type *in_cmd_ptr )
{
  pwrdb_res_type              status = PWRDB_RES_OK;
  pwrdb_cmd_poke32_range_type *ptr = (pwrdb_cmd_poke32_range_type *)in_cmd_ptr;
  uint32 *arrayaddr = NULL;
  DALResult result = DALSYS_Malloc(((ptr->range)*sizeof(uint32)),(void*)&arrayaddr);
  uint32 i = 0;
  
  if( result != DAL_SUCCESS )
  {
    return(PWRDB_RES_ERROR);
  }
  if(arrayaddr == NULL)
  {
     PWRDB_MSG_H0("Malloc Failed, returning from POKE32 RANGE BYTE Command execution");
     pwrdb_log_message(PWRDB_ERROR_MESSAGE, "Poke32 malloc failed");
     status = PWRDB_RES_ERROR;
     return status;
  }

  pwrdb_addto_malloc_array(arrayaddr);

  loc_cmd_ptr->params.poke32_range.addr = ptr->addr;
  loc_cmd_ptr->params.poke32_range.range  = ptr->range;
  for(i=0;i<ptr->range; i++)
  {
      *(arrayaddr + i) = *(ptr->vals + i);
  }
  loc_cmd_ptr->params.poke32_range.vals = arrayaddr;

  return status;

}

/*===========================================================================

FUNCTION PWRDB_UNPACK_CMD_POKE8_M

===========================================================================*/
static void pwrdb_unpack_cmd_poke8_m( pwrdb_cmd_type *loc_cmd_ptr,
                                      pwrdb_cmd_null_cmd_type *in_cmd_ptr )
{
  pwrdb_cmd_poke8_m_type *ptr = (pwrdb_cmd_poke8_m_type *)in_cmd_ptr;

  loc_cmd_ptr->params.poke8_m.addr = ptr->addr;
  loc_cmd_ptr->params.poke8_m.val  = ptr->val;
  loc_cmd_ptr->params.poke8_m.mask = ptr->mask;
}

/*===========================================================================

FUNCTION PWRDB_UNPACK_CMD_POKE16_M

===========================================================================*/
static void pwrdb_unpack_cmd_poke16_m( pwrdb_cmd_type *loc_cmd_ptr,
                                       pwrdb_cmd_null_cmd_type *in_cmd_ptr )
{
  pwrdb_cmd_poke16_m_type *ptr = (pwrdb_cmd_poke16_m_type *)in_cmd_ptr;

  loc_cmd_ptr->params.poke16_m.addr = ptr->addr;
  loc_cmd_ptr->params.poke16_m.val  = ptr->val;
  loc_cmd_ptr->params.poke16_m.mask = ptr->mask;
}

/*===========================================================================

FUNCTION PWRDB_UNPACK_CMD_POKE32_M

===========================================================================*/
static void pwrdb_unpack_cmd_poke32_m( pwrdb_cmd_type *loc_cmd_ptr,
                                       pwrdb_cmd_null_cmd_type *in_cmd_ptr )
{
  pwrdb_cmd_poke32_m_type *ptr = (pwrdb_cmd_poke32_m_type *)in_cmd_ptr;

  loc_cmd_ptr->params.poke32_m.addr = ptr->addr;
  loc_cmd_ptr->params.poke32_m.val  = ptr->val;
  loc_cmd_ptr->params.poke32_m.mask = ptr->mask;
}

/*===========================================================================

FUNCTION PWRDB_UNPACK_CMD_NPA_ISSUE_REQUIRED_REQUEST

===========================================================================*/
static pwrdb_res_type pwrdb_unpack_cmd_npa_issue_required_request( pwrdb_cmd_type *loc_cmd_ptr,
                                       pwrdb_cmd_null_cmd_type *in_cmd_ptr )
{
  pwrdb_res_type  status = PWRDB_RES_OK;
  pwrdb_cmd_npa_issue_required_request_type *ptr = (pwrdb_cmd_npa_issue_required_request_type *)in_cmd_ptr;
  uint16 count=0;
  char *str1 = NULL;

  /* '1' is extra for adding '\0' at last of C string*/
  DALResult result = DALSYS_Malloc( ((ptr->resource_name_len + 1)*sizeof(char)),(void *)&str1 );
  //malloc();
  
  if( result != DAL_SUCCESS )
  {
       PWRDB_MSG_H0("Malloc Failed, returning from NPA_ISSUE_REQUIRED_REQUEST Command execution");
       pwrdb_log_message(PWRDB_ERROR_MESSAGE, "malloc failed in unpack npa_issue_required_request command");
       status = PWRDB_RES_ERROR;
       return status;
  }

  loc_cmd_ptr->params.npa_issue_required_request.state = ptr->state;

  for(count=0; count<ptr->resource_name_len; count++)
  {
       *(str1 + count) = *(ptr->resource_name + count);
  }
  *(str1 + ptr->resource_name_len) = '\0';

  status = pwrdb_npa_get_client_handle(&(loc_cmd_ptr->params.npa_issue_required_request.NPAClientHandle),
                                         str1,
                                         ptr->sync,
                                         NPA_CLIENT_REQUIRED);

  if(status != PWRDB_RES_OK)
  {
    PWRDB_MSG_H0("NPA get client handle failed in unpack npa_issue_required_request command");
    pwrdb_log_message(PWRDB_ERROR_MESSAGE, "NPA get client handle failed in unpack npa_issue_required_request command");
    status = PWRDB_RES_ERROR;
  }
  DALSYS_Free((void *)str1);
  return status;
}

/*===========================================================================

FUNCTION PWRDB_UNPACK_CMD_NPA_MODIFY_REQUIRED_REQUEST

===========================================================================*/
static pwrdb_res_type pwrdb_unpack_cmd_npa_modify_required_request( pwrdb_cmd_type *loc_cmd_ptr,
                                       pwrdb_cmd_null_cmd_type *in_cmd_ptr )
{
  pwrdb_res_type  status = PWRDB_RES_OK;
  pwrdb_cmd_npa_modify_required_request_type *ptr = (pwrdb_cmd_npa_modify_required_request_type *)in_cmd_ptr;
  uint16 count=0;
  char *str1 = NULL;

  /* '1' is extra for adding '\0' at last of C string*/
  DALResult result = DALSYS_Malloc( ((ptr->resource_name_len + 1)*sizeof(char)),(void *)&str1 );
  //malloc();
  
  if( result != DAL_SUCCESS )
  {
       PWRDB_MSG_H0("Malloc Failed, returning from NPA_MODIFY_REQUIRED_REQUEST command execution");
       pwrdb_log_message(PWRDB_ERROR_MESSAGE, "malloc failed in unpack npa_modify_required_request command");
       status = PWRDB_RES_ERROR;
       return status;
  }

  loc_cmd_ptr->params.npa_modify_required_request.delta = ptr->delta;;

  for(count=0; count<ptr->resource_name_len; count++)
  {
       *(str1 + count) = *(ptr->resource_name + count);
  }
  *(str1 + ptr->resource_name_len) = '\0';

  status = pwrdb_npa_get_client_handle(&(loc_cmd_ptr->params.npa_modify_required_request.NPAClientHandle),
                                         str1,
                                         ptr->sync,
                                         NPA_CLIENT_REQUIRED);

  if(status != PWRDB_RES_OK)
  {
    PWRDB_MSG_H0("NPA get client handle failed in unpack npa_modify_required_request command");
    pwrdb_log_message(PWRDB_ERROR_MESSAGE, "NPA get client handle failed in unpack npa_modify_required_request command");
    status = PWRDB_RES_ERROR;
  }
  DALSYS_Free((void *)str1);
  return status;
}

/*===========================================================================

FUNCTION PWRDB_UNPACK_CMD_NPA_ISSUE_IMPULSE_REQUEST

===========================================================================*/
static pwrdb_res_type pwrdb_unpack_cmd_npa_issue_impulse_request( pwrdb_cmd_type *loc_cmd_ptr,
                                       pwrdb_cmd_null_cmd_type *in_cmd_ptr )
{
  pwrdb_res_type  status = PWRDB_RES_OK;
  pwrdb_cmd_npa_issue_impulse_request_type *ptr = (pwrdb_cmd_npa_issue_impulse_request_type *)in_cmd_ptr;
  uint16 count=0;
  char *str1 = NULL;

  /* '1' is extra for adding '\0' at last of C string*/
  DALResult result = DALSYS_Malloc( ((ptr->resource_name_len + 1)*sizeof(char)),(void *)&str1 );
  //malloc();
  
  if( result != DAL_SUCCESS )
  {
       PWRDB_MSG_H0("Malloc Failed, returning from npa_issue_impulse_request command execution");
       pwrdb_log_message(PWRDB_ERROR_MESSAGE, "malloc failed in unpack npa_issue_impulse_request command");
       status = PWRDB_RES_ERROR;
       return status;
  }

  for(count=0; count<ptr->resource_name_len; count++)
  {
       *(str1 + count) = *(ptr->resource_name + count);
  }
  *(str1 + ptr->resource_name_len) = '\0';

  status = pwrdb_npa_get_client_handle(&(loc_cmd_ptr->params.npa_issue_impulse_request.NPAClientHandle),
                                         str1,
                                         ptr->sync,
                                         NPA_CLIENT_IMPULSE);

  if(status != PWRDB_RES_OK)
  {
    PWRDB_MSG_H0("NPA get client handle failed in unpack npa_issue_impulse_request command");
    pwrdb_log_message(PWRDB_ERROR_MESSAGE, "NPA get client handle failed in unpack npa_issue_impulse_request command");
    status = PWRDB_RES_ERROR;
  }
  DALSYS_Free((void *)str1);
  return status;
}

/*===========================================================================

FUNCTION PWRDB_UNPACK_CMD_NPA_ISSUE_ISOC_REQUEST

===========================================================================*/
static pwrdb_res_type pwrdb_unpack_cmd_npa_issue_isoc_request( pwrdb_cmd_type *loc_cmd_ptr,
                                       pwrdb_cmd_null_cmd_type *in_cmd_ptr )
{
  pwrdb_res_type  status = PWRDB_RES_OK;
  pwrdb_cmd_npa_issue_isoc_request_type *ptr = (pwrdb_cmd_npa_issue_isoc_request_type *)in_cmd_ptr;
  uint16 count=0;
  char *str1 = NULL;

  /* '1' is extra for adding '\0' at last of C string*/
  DALResult result = DALSYS_Malloc( ((ptr->resource_name_len + 1)*sizeof(char)),(void *)&str1 );
  //malloc();
  
  if( result != DAL_SUCCESS )
  {
       PWRDB_MSG_H0("Malloc Failed, returning from npa_issue_isoc_request command execution");
       pwrdb_log_message(PWRDB_ERROR_MESSAGE, "malloc failed in unpack npa_issue_isoc_request command");
       status = PWRDB_RES_ERROR;
       return status;
  }

  loc_cmd_ptr->params.npa_issue_isoc_request.deadline   = ptr->deadline;
  loc_cmd_ptr->params.npa_issue_isoc_request.level_hint = ptr->level_hint;

  for(count=0; count<ptr->resource_name_len; count++)
  {
       *(str1 + count) = *(ptr->resource_name + count);
  }
  *(str1 + ptr->resource_name_len) = '\0';

  status = pwrdb_npa_get_client_handle(&(loc_cmd_ptr->params.npa_issue_isoc_request.NPAClientHandle),
                                         str1,
                                         ptr->sync,
                                         NPA_CLIENT_ISOCHRONOUS);

  if(status != PWRDB_RES_OK)
  {
    PWRDB_MSG_H0("NPA get client handle failed in unpack npa_issue_isoc_request command");
    pwrdb_log_message(PWRDB_ERROR_MESSAGE, "NPA get client handle failed in unpack npa_issue_isoc_request command");
    status = PWRDB_RES_ERROR;
  }
  DALSYS_Free((void *)str1);
  return status;
}

/*===========================================================================

FUNCTION PWRDB_UNPACK_CMD_NPA_ISSUE_LIMIT_MAX_REQUEST

===========================================================================*/
static pwrdb_res_type pwrdb_unpack_cmd_npa_issue_limit_max_request( pwrdb_cmd_type *loc_cmd_ptr,
                                       pwrdb_cmd_null_cmd_type *in_cmd_ptr )
{
  pwrdb_res_type  status = PWRDB_RES_OK;
  pwrdb_cmd_npa_issue_limit_max_request_type *ptr = (pwrdb_cmd_npa_issue_limit_max_request_type *)in_cmd_ptr;
  uint16 count=0;
  char *str1 = NULL;

  /* '1' is extra for adding '\0' at last of C string*/
  DALResult result = DALSYS_Malloc( ((ptr->resource_name_len + 1)*sizeof(char)),(void *)&str1 );
  //malloc();
  
  if( result != DAL_SUCCESS )
  {
       PWRDB_MSG_H0("Malloc Failed, returning from npa_issue_limit_max_request command execution");
       pwrdb_log_message(PWRDB_ERROR_MESSAGE, "malloc failed in unpack npa_issue_limit_max_request command");
       status = PWRDB_RES_ERROR;
       return status;
  }

  loc_cmd_ptr->params.npa_issue_limit_max_request.max = ptr->max;

  for(count=0; count<ptr->resource_name_len; count++)
  {
       *(str1 + count) = *(ptr->resource_name + count);
  }
  *(str1 + ptr->resource_name_len) = '\0';

  status = pwrdb_npa_get_client_handle(&(loc_cmd_ptr->params.npa_issue_limit_max_request.NPAClientHandle),
                                         str1,
                                         ptr->sync,
                                         NPA_CLIENT_LIMIT_MAX);

  if(status != PWRDB_RES_OK)
  {
    PWRDB_MSG_H0("NPA get client handle failed in unpack npa_issue_limit_max_request command");
    pwrdb_log_message(PWRDB_ERROR_MESSAGE, "NPA get client handle failed in unpack npa_issue_limit_max_request command");
    status = PWRDB_RES_ERROR;
  }
  DALSYS_Free((void *)str1);
  return status;
}

/*===========================================================================

FUNCTION PWRDB_UNPACK_CMD_NPA_COMPLETE_REQUEST

===========================================================================*/
static pwrdb_res_type pwrdb_unpack_cmd_npa_complete_request( pwrdb_cmd_type *loc_cmd_ptr,
                                       pwrdb_cmd_null_cmd_type *in_cmd_ptr )
{
  pwrdb_res_type  status = PWRDB_RES_OK;
  pwrdb_cmd_npa_complete_request_type *ptr = (pwrdb_cmd_npa_complete_request_type *)in_cmd_ptr;
  uint16 count=0;
  char *str1 = NULL;

  /* '1' is extra for adding '\0' at last of C string*/
  DALResult result = DALSYS_Malloc( ((ptr->resource_name_len + 1)*sizeof(char)),(void *)&str1 );
  //malloc();
  
  if( result != DAL_SUCCESS )
  {
       PWRDB_MSG_H0("Malloc Failed, returning from npa_complete_request command execution");
       pwrdb_log_message(PWRDB_ERROR_MESSAGE, "malloc failed in unpack npa_complete_request command");
       status = PWRDB_RES_ERROR;
       return status;
  }

  for(count=0; count<ptr->resource_name_len; count++)
  {
       *(str1 + count) = *(ptr->resource_name + count);
  }
  *(str1 + ptr->resource_name_len) = '\0';

  status = pwrdb_npa_get_complete_request_client_handle(&(loc_cmd_ptr->params.npa_complete_request.NPAClientHandle),
                                                          str1,
                                                          ptr->sync);

  if(status != PWRDB_RES_OK)
  {
    PWRDB_MSG_H0("NPA get client handle failed in unpack npa_complete_request command");
    pwrdb_log_message(PWRDB_ERROR_MESSAGE, "NPA get client handle failed in unpack npa_complete_request command");
    status = PWRDB_RES_ERROR;
  }
  DALSYS_Free((void *)str1);
  return status;
}

/*===========================================================================

FUNCTION PWRDB_UNPACK_CMD_NPA_QUERY_BY_NAME

===========================================================================*/
static pwrdb_res_type pwrdb_unpack_cmd_npa_query_by_name( pwrdb_cmd_type *loc_cmd_ptr,
                                       pwrdb_cmd_null_cmd_type *in_cmd_ptr )
{
  pwrdb_res_type  status = PWRDB_RES_OK;
  pwrdb_cmd_npa_query_by_name_type *ptr = (pwrdb_cmd_npa_query_by_name_type *)in_cmd_ptr;
  uint16 count=0;
  npa_query_handle hQuery;
  char *str1 = NULL;

  /* '1' is extra for adding '\0' at last of C string*/
  DALResult result = DALSYS_Malloc( ((ptr->resource_name_len + 1)*sizeof(char)),(void *)&str1 );
  //malloc();
  
  if( result != DAL_SUCCESS )
  {
       PWRDB_MSG_H0("Malloc Failed, returning from npa_query_by_name command");
       pwrdb_log_message(PWRDB_ERROR_MESSAGE, "malloc failed in unpack npa_query_by_name command");
       status = PWRDB_RES_ERROR;
       return status;
  }

  for(count=0; count<ptr->resource_name_len; count++)
  {
       *(str1 + count) = *(ptr->resource_name + count);
  }
  *(str1 + ptr->resource_name_len) = '\0';

  hQuery = npa_create_query_handle(str1);

  if (hQuery == NULL)
  {

      PWRDB_MSG_H0("Returning invalid resource handle in NPA query by name");
      pwrdb_log_message(PWRDB_ERROR_MESSAGE, "Returning invalid resource handle in NPA query by name");
      status = PWRDB_RES_ERROR;
      return status;
  }

  loc_cmd_ptr->params.npa_query_by_name.query_id          = ptr->query_id;
  loc_cmd_ptr->params.npa_query_by_name.NPAQueryHandle    = hQuery;
  loc_cmd_ptr->params.npa_query_by_name.resource_name     = pwrdb_npa_malloc2cpy_str( str1 );
  loc_cmd_ptr->params.npa_query_by_name.resource_name_len = ptr->resource_name_len;

  if(status != PWRDB_RES_OK)
  {
    PWRDB_MSG_H0("Failed in unpack npa_query_by_name command");
    pwrdb_log_message(PWRDB_ERROR_MESSAGE, "Failed in unpack npa_query_by_name command");
    status = PWRDB_RES_ERROR;
  }
  DALSYS_Free((void *)str1);
  return status;
}

/*===========================================================================

FUNCTION PWRDB_UNPACK_CMD_CONFIGURE_hw_events_mux

DESCRIPTION
  Unpack one command by copying the id and parameters from the packed
  struct to the internal array of union.

PARAMETERS
  in_cmd_ptr - pointer to the command to unpack

RETURN VALUE
  PWRDB_RES_OK or PWRDB_RES_ERROR

===========================================================================*/
static pwrdb_res_type pwrdb_unpack_cmd_configure_hw_events_mux( pwrdb_cmd_type *loc_cmd_ptr,
                                       pwrdb_cmd_null_cmd_type *in_cmd_ptr )
{
  pwrdb_res_type  status = PWRDB_RES_OK;
  return status;
}

static void pwrdb_unpack_cmd_trigger_log_signals ( pwrdb_cmd_type *loc_cmd_ptr,
                                              pwrdb_cmd_null_cmd_type *in_cmd_ptr )
{
  pwrdb_cmd_trigger_log_signals_type *ptr = ( pwrdb_cmd_trigger_log_signals_type *)in_cmd_ptr;
  loc_cmd_ptr->params.trigger_log_signal.log_mask = ptr->log_mask;
  loc_cmd_ptr->params.trigger_log_signal.gpio_number = ptr->gpio_number;
}

/*===========================================================================

FUNCTION pwrdb_change_log_format

DESCRIPTION
  This command is used by the User to notify the preferred logging mechanism
  for pwrdb.

PARAMETERS
  

RETURN VALUE
  PWRDB_RES_OK or PWRDB_RES_ERROR

===========================================================================*/
static void pwrdb_unpack_cmd_change_log_format ( pwrdb_cmd_type          *loc_cmd_ptr,
                                                 pwrdb_cmd_null_cmd_type *in_cmd_ptr )
{
  pwrdb_cmd_change_log_format_type *ptr = (pwrdb_cmd_change_log_format_type *)in_cmd_ptr;
  loc_cmd_ptr->params.set_log_format.log_format = ptr->log_format;
}

static void pwrdb_unpack_cmd_rpm_tlmm_write( pwrdb_cmd_type *loc_cmd_ptr, pwrdb_cmd_null_cmd_type *in_cmd_ptr )
{
  pwrdb_cmd_rpm_tlmm_write_type *ptr = (pwrdb_cmd_rpm_tlmm_write_type *)in_cmd_ptr;

  loc_cmd_ptr->params.rpm_tlmm_write.pwrdb_rpm_event_mask = ptr->pwrdb_rpm_event_mask;
  loc_cmd_ptr->cmd_id                                     = ptr->hdr.cmd_id;
  loc_cmd_ptr->params.rpm_tlmm_write.range           = ptr->range;
  loc_cmd_ptr->params.rpm_tlmm_write.gpio_number     = ptr->gpio_number;
  loc_cmd_ptr->params.rpm_tlmm_write.function        = ptr->function;
  loc_cmd_ptr->params.rpm_tlmm_write.direction       = ptr->direction;
  loc_cmd_ptr->params.rpm_tlmm_write.pull            = ptr->pull;
  loc_cmd_ptr->params.rpm_tlmm_write.drive_strength  = ptr->drive_strength;
  loc_cmd_ptr->params.rpm_tlmm_write.output_value    = ptr->output_value;
  loc_cmd_ptr->params.rpm_tlmm_write.enable          = ptr->enable;
  loc_cmd_ptr->params.rpm_tlmm_write.pwrdb_rpm_execution_num = ptr->pwrdb_rpm_execution_num;  
}

static void pwrdb_unpack_cmd_rpm_memory_peek( pwrdb_cmd_type          *loc_cmd_ptr,
                                              pwrdb_cmd_null_cmd_type *in_cmd_ptr )
{
  pwrdb_cmd_rpm_memory_peek_type *ptr = (pwrdb_cmd_rpm_memory_peek_type *)in_cmd_ptr;
  loc_cmd_ptr->cmd_id                                      = ptr->hdr.cmd_id;
  loc_cmd_ptr->params.rpm_memory_peek.pwrdb_rpm_event_mask = ptr->pwrdb_rpm_event_mask;
  loc_cmd_ptr->params.rpm_memory_peek.range = ptr->range;
  loc_cmd_ptr->params.rpm_memory_peek.addr = ptr->addr;
  loc_cmd_ptr->params.rpm_memory_peek.pwrdb_rpm_execution_num = ptr->pwrdb_rpm_execution_num;
}

static void pwrdb_unpack_cmd_rpm_memory_poke( pwrdb_cmd_type          *loc_cmd_ptr,
                                              pwrdb_cmd_null_cmd_type *in_cmd_ptr )
{
  pwrdb_cmd_rpm_memory_poke_type *ptr = (pwrdb_cmd_rpm_memory_poke_type *)in_cmd_ptr;
  loc_cmd_ptr->cmd_id                                      = ptr->hdr.cmd_id;
  loc_cmd_ptr->params.rpm_memory_poke.pwrdb_rpm_event_mask = ptr->pwrdb_rpm_event_mask;
  loc_cmd_ptr->params.rpm_memory_poke.range = ptr->range;
  loc_cmd_ptr->params.rpm_memory_poke.addr = ptr->addr;
  loc_cmd_ptr->params.rpm_memory_poke.value = ptr->value;
  loc_cmd_ptr->params.rpm_memory_poke.pwrdb_rpm_execution_num = ptr->pwrdb_rpm_execution_num;
}

static void pwrdb_unpack_cmd_rpm_spmi_write( pwrdb_cmd_type          *loc_cmd_ptr,
                                            pwrdb_cmd_null_cmd_type *in_cmd_ptr )
{
  pwrdb_cmd_rpm_spmi_write_type *ptr = (pwrdb_cmd_rpm_spmi_write_type *)in_cmd_ptr;
  loc_cmd_ptr->cmd_id                                     = ptr->hdr.cmd_id;
  loc_cmd_ptr->params.rpm_spmi_write.pwrdb_rpm_event_mask = ptr->pwrdb_rpm_event_mask;
  loc_cmd_ptr->params.rpm_spmi_write.slave_id             = ptr->slave_id;
  loc_cmd_ptr->params.rpm_spmi_write.offset               = ptr->offset;
  loc_cmd_ptr->params.rpm_spmi_write.range            = ptr->range;
  loc_cmd_ptr->params.rpm_spmi_write.value                = ptr->value;
  loc_cmd_ptr->params.rpm_spmi_write.pwrdb_rpm_execution_num = ptr->pwrdb_rpm_execution_num;
}
#endif /* ifdef PWRDB_PRO */


/*===========================================================================

FUNCTION PWRDB_UNPACK_CMD_CLK_BUSY_WAIT

===========================================================================*/
static void pwrdb_unpack_cmd_clk_busy_wait( pwrdb_cmd_type *loc_cmd_ptr,
                                            pwrdb_cmd_null_cmd_type *in_cmd_ptr )
{
  pwrdb_cmd_clk_busy_wait_type *ptr = (pwrdb_cmd_clk_busy_wait_type *)in_cmd_ptr;

  loc_cmd_ptr->params.clk_busy_wait.usec   = ptr->usec;

}


static void pwrdb_unpack_cmd_rpm_spmi_read( pwrdb_cmd_type          *loc_cmd_ptr,
                                            pwrdb_cmd_null_cmd_type *in_cmd_ptr )
{
  pwrdb_cmd_rpm_spmi_read_type *ptr = (pwrdb_cmd_rpm_spmi_read_type *)in_cmd_ptr;
  loc_cmd_ptr->cmd_id                                    = ptr->hdr.cmd_id;
  loc_cmd_ptr->params.rpm_spmi_read.pwrdb_rpm_event_mask = ptr->pwrdb_rpm_event_mask;
  loc_cmd_ptr->params.rpm_spmi_read.slave_id             = ptr->slave_id;
  loc_cmd_ptr->params.rpm_spmi_read.offset               = ptr->offset;
  loc_cmd_ptr->params.rpm_spmi_read.range            = ptr->range;
  loc_cmd_ptr->params.rpm_spmi_read.pwrdb_rpm_execution_num = ptr->pwrdb_rpm_execution_num;
}

static void pwrdb_unpack_cmd_rpm_flush_cmd ( pwrdb_cmd_type *loc_cmd_ptr, pwrdb_cmd_null_cmd_type *in_cmd_ptr )
{
  pwrdb_cmd_rpm_flush_cmds_type  *ptr = (pwrdb_cmd_rpm_flush_cmds_type *)in_cmd_ptr;
  loc_cmd_ptr->cmd_id                                     = ptr->hdr.cmd_id;
  loc_cmd_ptr->params.rpm_flush_cmds.pwrdb_rpm_event_mask = ptr->pwrdb_rpm_event_mask;
}

static void pwrdb_unpack_cmd_rpm_tlmm_read( pwrdb_cmd_type          *loc_cmd_ptr,
                                            pwrdb_cmd_null_cmd_type *in_cmd_ptr )
{
  pwrdb_cmd_rpm_tlmm_read_type *ptr = (pwrdb_cmd_rpm_tlmm_read_type *)in_cmd_ptr;
  loc_cmd_ptr->cmd_id                                     = ptr->hdr.cmd_id;
  loc_cmd_ptr->params.rpm_tlmm_read.gpio_number = ptr->gpio_number;
  loc_cmd_ptr->params.rpm_tlmm_read.pwrdb_rpm_event_mask = ptr->pwrdb_rpm_event_mask;
  loc_cmd_ptr->params.rpm_tlmm_read.range            = ptr->range;
  loc_cmd_ptr->params.rpm_tlmm_read.pwrdb_rpm_execution_num = ptr->pwrdb_rpm_execution_num;  
}

static void pwrdb_unpack_cmd_rpm_clk_log_state( pwrdb_cmd_type          *loc_cmd_ptr,
                                            pwrdb_cmd_null_cmd_type *in_cmd_ptr )
{
  pwrdb_cmd_rpm_clk_log_state_type *ptr = (pwrdb_cmd_rpm_clk_log_state_type *)in_cmd_ptr;
  loc_cmd_ptr->cmd_id                                     = ptr->hdr.cmd_id;
  loc_cmd_ptr->params.rpm_clk_log_state.pwrdb_rpm_event_mask = ptr->pwrdb_rpm_event_mask;
  loc_cmd_ptr->params.rpm_clk_log_state.pwrdb_rpm_execution_num = ptr->pwrdb_rpm_execution_num;
}

static void pwrdb_unpack_cmd_rpm_end_of_cmd( pwrdb_cmd_type          *loc_cmd_ptr,
                                            pwrdb_cmd_null_cmd_type *in_cmd_ptr )
{
  pwrdb_cmd_rpm_end_of_cmd_type *ptr = (pwrdb_cmd_rpm_end_of_cmd_type *)in_cmd_ptr;
  loc_cmd_ptr->cmd_id                                     = ptr->hdr.cmd_id;
  loc_cmd_ptr->params.rpm_end_of_cmd.pwrdb_rpm_event_mask = ptr->pwrdb_rpm_event_mask;
  loc_cmd_ptr->params.rpm_end_of_cmd.pwrdb_rpm_execution_num = ptr->pwrdb_rpm_execution_num;
}

static void pwrdb_unpack_cmd_clk_log_state ( pwrdb_cmd_type *loc_cmd_ptr,
                                              pwrdb_cmd_null_cmd_type *in_cmd_ptr )
{
  pwrdb_cmd_clk_log_state_type *ptr = (pwrdb_cmd_clk_log_state_type *)in_cmd_ptr;
  loc_cmd_ptr->cmd_id                                     = ptr->hdr.cmd_id;
  loc_cmd_ptr->params.clk_log_state.measureFreq = ptr->measureFreq;  
}


#if 0
/*===========================================================================

FUNCTION PWRDB_UNPACK_CMD_STRING

===========================================================================*/
static pwrdb_res_type pwrdb_unpack_cmd_string( pwrdb_cmd_type *loc_cmd_ptr,
                                       pwrdb_cmd_null_cmd_type *in_cmd_ptr )
{
  pwrdb_res_type  status = PWRDB_RES_OK;
  pwrdb_cmd_string_type *ptr = (pwrdb_cmd_string_type *)in_cmd_ptr;
  uint16 count=0;
  char *str1 = NULL;

  /* '1' is extra for adding '\0' at last of C string*/
  DALResult result = DALSYS_Malloc( ((ptr->str_len + 1)*sizeof(char)),(void *)&str1 );
  //malloc();
  
  if( result != DAL_SUCCESS )
  {
       PWRDB_MSG_H0("Malloc Failed, returning from STRING Command execution");
       pwrdb_log_message(PWRDB_ERROR_MESSAGE, "malloc failed in unpack string command");
       status = PWRDB_RES_ERROR;
       return status;
  }
  pwrdb_addto_malloc_array(str1);

  loc_cmd_ptr->params.strng.str_type = ptr->str_type;
  loc_cmd_ptr->params.strng.str_len  = ptr->str_len;
  for(count=0; count<ptr->str_len; count++)
  {
       *(str1 + count) = *(ptr->str + count);
  }
  *(str1 + ptr->str_len) = '\0';
  loc_cmd_ptr->params.strng.str  = str1;

  return status;
}

/*===========================================================================

FUNCTION PWRDB_UNPACK_CMD_DATA3_STRING

===========================================================================*/
static pwrdb_res_type pwrdb_unpack_cmd_data3_string( pwrdb_cmd_type *loc_cmd_ptr,
                                       pwrdb_cmd_null_cmd_type *in_cmd_ptr )
{
  pwrdb_res_type  status = PWRDB_RES_OK;
  pwrdb_cmd_data3_string_type *ptr = (pwrdb_cmd_data3_string_type *)in_cmd_ptr;
  uint16 count=0;
  char *str1 = NULL;

  /* '1' is extra for adding '\0' at last of C string*/
  DALResult result = DALSYS_Malloc( ((ptr->str_len + 1)*sizeof(char)),(void *)&str1 );
  //malloc();
  
  if( result != DAL_SUCCESS )
  {
       PWRDB_MSG_H0("Malloc Failed, returning from DATA3_STRING Command execution");
       pwrdb_log_message(PWRDB_ERROR_MESSAGE, "malloc failed in unpack data3_string command");
       status = PWRDB_RES_ERROR;
       return status;
  }
  pwrdb_addto_malloc_array(str1);

  loc_cmd_ptr->params.data3_strng.str_type = ptr->str_type;
  loc_cmd_ptr->params.data3_strng.value1   = ptr->value1;
  loc_cmd_ptr->params.data3_strng.value2   = ptr->value2;
  loc_cmd_ptr->params.data3_strng.value3   = ptr->value3;
  loc_cmd_ptr->params.data3_strng.str_len  = ptr->str_len;
  for(count=0; count<ptr->str_len; count++)
  {
       *(str1 + count) = *(ptr->str + count);
  }
  *(str1 + ptr->str_len) = '\0';
  loc_cmd_ptr->params.data3_strng.str  = str1;

  return status;
}
#endif

/*===========================================================================

FUNCTION PWRDB_UNPACK_CMDS

DESCRIPTION
  Unpack one command by allocating memory for a new internal command linked
  list element and copying the id and parameters from the packed struct to
  the approriate the new command linked list element.

PARAMETERS
  in_cmd_ptr - pointer to the command to unpack

RETURN VALUE
  pointer to newly allcoated command or
  NULL on error

===========================================================================*/
pwrdb_command_ll_type* pwrdb_unpack_cmd( pwrdb_cmd_null_cmd_type *in_cmd_ptr )
{
  pwrdb_res_type         status= PWRDB_RES_OK;
  pwrdb_command_ll_type *temp_command;
  pwrdb_cmd_type        *temp_cmd;
  DALResult              res;

  if (!pwrdb_unpack_cmd_len_ok( in_cmd_ptr ))
  {
    return NULL;
  }

  /* copy the command */
  res = DALSYS_Malloc(sizeof(pwrdb_command_ll_type), (void *)&temp_command);
  if (res != DAL_SUCCESS)
  {
    return NULL;
  }
  PWRDB_MSG_H1("Unpacking PWRDB Command %i.", in_cmd_ptr->hdr.cmd_id);  

  temp_command->next = NULL;
  temp_cmd = &(temp_command->command);
  temp_cmd->cmd_id = in_cmd_ptr->hdr.cmd_id;

  /* copy parameters depending on command */
  switch ( in_cmd_ptr->hdr.cmd_id )
  {
    case PWRDB_CMD_NULL_CMD:
    case PWRDB_CMD_START_TASK_CMDS:
    case PWRDB_CMD_END_OF_CMDS:
#ifdef PWRDB_PRO
   #ifdef FEATURE_PWRDB_MPSS
    case PWRDB_CMD_STOP_AND_LOG_TO_FS:
   #endif
#endif
    /* no parameters to copy for these commands */
    break;

    case PWRDB_CMD_START_TIMER:
      status = pwrdb_unpack_cmd_start_timer( temp_cmd, in_cmd_ptr );
    break;
  
    case PWRDB_CMD_ENABLE_PRO:
      status = pwrdb_unpack_cmd_enable_pro( temp_cmd, in_cmd_ptr );
    break;
  
    case PWRDB_CMD_TLMM_IS_LOCKED:
      pwrdb_unpack_cmd_tlmm_is_locked( temp_cmd, in_cmd_ptr );
    break;

    case PWRDB_CMD_CLK_GET_CLK_EN:
      pwrdb_unpack_cmd_clk_get_clk_en( temp_cmd, in_cmd_ptr );
    break;

    case PWRDB_CMD_CLK_GET_CLK_FREQ:
      pwrdb_unpack_cmd_clk_get_clk_freq( temp_cmd, in_cmd_ptr );
    break;
  
    case PWRDB_CMD_CLK_BUSY_WAIT:
      pwrdb_unpack_cmd_clk_busy_wait( temp_cmd, in_cmd_ptr );
    break;

    case PWRDB_CMD_CLK_LOG_STATE:
      pwrdb_unpack_cmd_clk_log_state( temp_cmd, in_cmd_ptr );
    break; 
 
    case PWRDB_CMD_TLMM_GET_CURR_CONFIG:
      pwrdb_unpack_cmd_tlmm_get_curr_config( temp_cmd, in_cmd_ptr );
    break;
  
    case PWRDB_CMD_RPM_TLMM_READ:
      pwrdb_unpack_cmd_rpm_tlmm_read( temp_cmd,in_cmd_ptr );
    break;

    case PWRDB_CMD_RPM_CLK_LOG_STATE:
      pwrdb_unpack_cmd_rpm_clk_log_state( temp_cmd,in_cmd_ptr );
    break;

    case PWRDB_CMD_RPM_END_OF_CMD:
      pwrdb_unpack_cmd_rpm_end_of_cmd( temp_cmd,in_cmd_ptr );
    break;  

    case PWRDB_CMD_RPM_SPMI_READ:
      pwrdb_unpack_cmd_rpm_spmi_read( temp_cmd,in_cmd_ptr );
    break;

    case PWRDB_CMD_RPM_FLUSH_CMDS:
      pwrdb_unpack_cmd_rpm_flush_cmd( temp_cmd, in_cmd_ptr );
    break;
  
    case PWRDB_CMD_RPM_DUMP:
      pwrdb_unpack_cmd_rpm_dump(temp_cmd,in_cmd_ptr);
    break;
    
    case PWRDB_CMD_RPM_ERR_FATAL:
      pwrdb_unpack_cmd_rpm_err_fatal(temp_cmd,in_cmd_ptr);
    break;
    
    case PWRDB_CMD_RPM_DOWNSAMPLE:
      pwrdb_unpack_cmd_rpm_downsample(temp_cmd,in_cmd_ptr);
    break;
    
#ifdef PWRDB_PRO
    case PWRDB_CMD_TLMM_SET_CURR_CONFIG:
      pwrdb_unpack_cmd_tlmm_set_curr_config( temp_cmd, in_cmd_ptr );
    break;

    case PWRDB_CMD_TLMM_OUTPUT:
      pwrdb_unpack_cmd_tlmm_output( temp_cmd, in_cmd_ptr );
    break;

    case PWRDB_CMD_TLMM_INPUT:
      pwrdb_unpack_cmd_tlmm_input( temp_cmd, in_cmd_ptr );
    break;

    case PWRDB_CMD_TLMM_GET_PIN_STATUS:
      pwrdb_unpack_cmd_tlmm_get_pin_status( temp_cmd, in_cmd_ptr );
    break;

    case PWRDB_CMD_TLMM_LOCK:
      pwrdb_unpack_cmd_tlmm_lock( temp_cmd, in_cmd_ptr );
    break;

    case PWRDB_CMD_TLMM_UNLOCK:
      pwrdb_unpack_cmd_tlmm_unlock( temp_cmd, in_cmd_ptr );
    break;

    case PWRDB_CMD_CLK_SET_CLK_EN:
      pwrdb_unpack_cmd_clk_set_clk_en( temp_cmd, in_cmd_ptr );
    break;

    case PWRDB_CMD_CLK_OUTPUT_GPIO:
      pwrdb_unpack_cmd_clk_output_gpio( temp_cmd, in_cmd_ptr );
    break;

    case PWRDB_CMD_PEEK8:
      pwrdb_unpack_cmd_peek8( temp_cmd, in_cmd_ptr );
    break;

    case PWRDB_CMD_PEEK16:
      pwrdb_unpack_cmd_peek16( temp_cmd, in_cmd_ptr );
    break;

    case PWRDB_CMD_PEEK32:
      pwrdb_unpack_cmd_peek32( temp_cmd, in_cmd_ptr );
    break;

    case PWRDB_CMD_PEEK32_RANGE:
      pwrdb_unpack_cmd_peek32_range( temp_cmd, in_cmd_ptr );
    break;

    case PWRDB_CMD_POKE32_RANGE:
      status = pwrdb_unpack_cmd_poke32_range( temp_cmd, in_cmd_ptr );
    break;

    case PWRDB_CMD_POKE8_M:
      pwrdb_unpack_cmd_poke8_m( temp_cmd, in_cmd_ptr );
    break;

    case PWRDB_CMD_POKE16_M:
      pwrdb_unpack_cmd_poke16_m( temp_cmd, in_cmd_ptr );
    break;

    case PWRDB_CMD_POKE32_M:
      pwrdb_unpack_cmd_poke32_m( temp_cmd, in_cmd_ptr );
    break;

    case PWRDB_CMD_NPA_ISSUE_REQUIRED_REQUEST:
      pwrdb_unpack_cmd_npa_issue_required_request( temp_cmd, in_cmd_ptr );
    break;

    case PWRDB_CMD_NPA_MODIFY_REQUIRED_REQUEST:
      pwrdb_unpack_cmd_npa_modify_required_request( temp_cmd, in_cmd_ptr );
    break;

    case PWRDB_CMD_NPA_ISSUE_IMPULSE_REQUEST:
      pwrdb_unpack_cmd_npa_issue_impulse_request( temp_cmd, in_cmd_ptr );
    break;

    case PWRDB_CMD_NPA_ISSUE_ISOC_REQUEST:
      pwrdb_unpack_cmd_npa_issue_isoc_request( temp_cmd, in_cmd_ptr );
    break;

    case PWRDB_CMD_NPA_ISSUE_LIMIT_MAX_REQUEST:
      pwrdb_unpack_cmd_npa_issue_limit_max_request( temp_cmd, in_cmd_ptr );
    break;

    case PWRDB_CMD_NPA_COMPLETE_REQUEST:
      pwrdb_unpack_cmd_npa_complete_request( temp_cmd, in_cmd_ptr );
    break;

    case PWRDB_CMD_NPA_QUERY_BY_NAME:
      pwrdb_unpack_cmd_npa_query_by_name( temp_cmd, in_cmd_ptr );
    break;

    case PWRDB_CMD_CONFIGURE_HW_EVENTS_MUX:
      pwrdb_unpack_cmd_configure_hw_events_mux( temp_cmd, in_cmd_ptr );
    break;
  
    case PWRDB_CMD_TRIGGER_LOG_SIGNALS:
      pwrdb_unpack_cmd_trigger_log_signals( temp_cmd, in_cmd_ptr );
    break;
   
    case PWRDB_CMD_CHANGE_LOG_FORMAT:
      pwrdb_unpack_cmd_change_log_format( temp_cmd,in_cmd_ptr );
    break;

    case PWRDB_CMD_RPM_TLMM_WRITE:
      pwrdb_unpack_cmd_rpm_tlmm_write(temp_cmd,in_cmd_ptr);
    break;
  
    case PWRDB_CMD_RPM_MEMORY_PEEK :
      pwrdb_unpack_cmd_rpm_memory_peek(temp_cmd,in_cmd_ptr);
    break;
   
    case PWRDB_CMD_RPM_MEMORY_POKE:
      pwrdb_unpack_cmd_rpm_memory_poke(temp_cmd,in_cmd_ptr);
    break;
    
    case PWRDB_CMD_RPM_SPMI_WRITE:
      pwrdb_unpack_cmd_rpm_spmi_write( temp_cmd,in_cmd_ptr );
    break;
  #if 0
    case PWRDB_CMD_STRING:
      status = pwrdb_unpack_cmd_string(temp_cmd, in_cmd_ptr);
    break;

    case PWRDB_CMD_DATA3_STRING:
      status = pwrdb_unpack_cmd_data3_string(temp_cmd, in_cmd_ptr);
    break;
  
  #endif 
#endif /* #ifdef PWRDB_PRO */
  
    default:
      /* unsupported command */
      status = PWRDB_RES_FATAL;
      PWRDB_MSG_E1("Unknown command %i.", in_cmd_ptr->hdr.cmd_id);
    break;
  } /* switch */

  if (status != PWRDB_RES_OK)
  {
    /* Release command memory to avoid a memory leak if there were any issues */
    (void) DALSYS_Free(temp_cmd);
    return NULL;
  }

  return temp_command;
}


/*===========================================================================

The next set of functions are helpers to pwrdb_pack_log_items. Each one is
used to pack the data for a specific log item.

The functions must only proceed if there is sufficient space left in the
buffer (as indicated by len).

The functions take three input parameters (and one output param):
 log_item - pointer to the log item in the internal log to be packed
 bptr     - pointer to the next free space in the output buffer
 len      - available space in the output buffer

The functions return the following values in res
 PWRDB_RES_OK            - all OK
 PWRDB_RES_OK_CONTINUE   - no error but no room left for this item
 PWRDB_RES_ERROR         - an error occurred

The function return value is the number of bytes written to the output buffer.
This will be less than or equal to alen and must be 0 if res is not
PWRDB_RES_OK.

===========================================================================*/


/*===========================================================================

FUNCTION PWRDB_PACK_LOG_EVENT

===========================================================================*/
static uint32 pwrdb_pack_log_event( pwrdb_log_type *log_item, uint8 *bptr, int len, pwrdb_res_type *res )
{
  pwrdb_log_event_type *ptr = (pwrdb_log_event_type *)bptr;

  if ( sizeof(pwrdb_log_event_type) > len )
  {
    /* can't fit this into the buffer, time to stop */
    *res = PWRDB_RES_OK_CONTINUE;
    return 0;
  }
  else
  {
    ptr->hdr.len   = sizeof(pwrdb_log_event_type);
    ptr->source    = log_item->data.event.source;
    ptr->id        = log_item->data.event.id;
    ptr->reserved1 = 0;
    ptr->reserved2 = 0;

    return sizeof(pwrdb_log_event_type);
  }
}

/*===========================================================================

FUNCTION PWRDB_PACK_LOG_TLMM_GET_CURR_CONFIG

===========================================================================*/
static uint32 pwrdb_pack_log_tlmm_get_curr_config( pwrdb_log_type *log_item, uint8 *bptr, int len, pwrdb_res_type *res )
{
  pwrdb_log_tlmm_get_curr_config_type *ptr = (pwrdb_log_tlmm_get_curr_config_type *)bptr;

  if ( sizeof(pwrdb_log_tlmm_get_curr_config_type) > len )
  {
    /* can't fit this into the buffer, time to stop */
    *res = PWRDB_RES_OK_CONTINUE;
    return 0;
  }
  else
  {
    ptr->hdr.len         = sizeof(pwrdb_log_tlmm_get_curr_config_type);
    ptr->gpio_number     = log_item->data.tlmm_get_curr_config.gpio_number;
    ptr->function        = log_item->data.tlmm_get_curr_config.function;
    ptr->direction       = log_item->data.tlmm_get_curr_config.direction;
    ptr->pull            = log_item->data.tlmm_get_curr_config.pull;
    ptr->drive_strength  = log_item->data.tlmm_get_curr_config.drive_strength;
    ptr->output_value    = log_item->data.tlmm_get_curr_config.output_value;
    ptr->status          = log_item->data.tlmm_get_curr_config.status;

    return sizeof(pwrdb_log_tlmm_get_curr_config_type);
  }
}

/*===========================================================================

FUNCTION PWRDB_PACK_LOG_TLMM_INPUT

===========================================================================*/
static uint32 pwrdb_pack_log_tlmm_input( pwrdb_log_type *log_item, uint8 *bptr, int len, pwrdb_res_type *res )
{
  pwrdb_log_tlmm_input_type *ptr = (pwrdb_log_tlmm_input_type *)bptr;

  if ( sizeof(pwrdb_log_tlmm_input_type) > len )
  {
    /* can't fit this into the buffer, time to stop */
    *res = PWRDB_RES_OK_CONTINUE;
    return 0;
  }
  else
  {
    ptr->hdr.len         = sizeof(pwrdb_log_tlmm_input_type);
    ptr->gpio_number     = log_item->data.tlmm_input.gpio_number;
    ptr->input_value     = log_item->data.tlmm_input.input_value;

    return sizeof(pwrdb_log_tlmm_input_type);
  }
}

/*===========================================================================

FUNCTION PWRDB_PACK_LOG_TLMM_GET_PIN_STATUS

===========================================================================*/
static uint32 pwrdb_pack_log_tlmm_get_pin_status( pwrdb_log_type *log_item, uint8 *bptr, int len, pwrdb_res_type *res )
{
  pwrdb_log_tlmm_get_pin_status_type *ptr = (pwrdb_log_tlmm_get_pin_status_type *)bptr;

  if ( sizeof(pwrdb_log_tlmm_get_pin_status_type) > len )
  {
    /* can't fit this into the buffer, time to stop */
    *res = PWRDB_RES_OK_CONTINUE;
    return 0;
  }
  else
  {
    ptr->hdr.len         = sizeof(pwrdb_log_tlmm_get_pin_status_type);
    ptr->gpio_number     = log_item->data.tlmm_get_pin_status.gpio_number;
    ptr->pin_status      = log_item->data.tlmm_get_pin_status.pin_status;

    return sizeof(pwrdb_log_tlmm_get_pin_status_type);
  }
}

/*===========================================================================

FUNCTION PWRDB_PACK_LOG_TLMM_IS_LOCKED

===========================================================================*/
static uint32 pwrdb_pack_log_tlmm_is_locked( pwrdb_log_type *log_item, uint8 *bptr, int len, pwrdb_res_type *res )
{
  pwrdb_log_tlmm_is_locked_type *ptr = (pwrdb_log_tlmm_is_locked_type *)bptr;

  if ( sizeof(pwrdb_log_tlmm_is_locked_type) > len )
  {
    /* can't fit this into the buffer, time to stop */
    *res = PWRDB_RES_OK_CONTINUE;
    return 0;
  }
  else
  {
    ptr->hdr.len         = sizeof(pwrdb_log_tlmm_is_locked_type);
    ptr->gpio_number     = log_item->data.tlmm_is_locked.gpio_number;
    ptr->locked          = log_item->data.tlmm_is_locked.locked;

    return sizeof(pwrdb_log_tlmm_is_locked_type);
  }
}

/*===========================================================================

FUNCTION PWRDB_PACK_LOG_CLK_GET_CLK_EN

===========================================================================*/
static uint32 pwrdb_pack_log_clk_get_clk_en( pwrdb_log_type *log_item, uint8 *bptr, int len, pwrdb_res_type *res )
{
  pwrdb_log_clk_get_clk_en_type *ptr = (pwrdb_log_clk_get_clk_en_type *)bptr;

  uint32 sizetoberet=0;
  uint16 num=0;
  char *clk=NULL;
  char *null_msg = "message logging failed";
  uint16 clk_en_len=log_item->data.clk_get_clk_en.clk_en_len;
  

  clk = log_item->data.clk_get_clk_en.clk;

  if(clk == NULL)
  {
     clk_en_len=0;
     /* Incase of Malloc failures returning the Read address itself as the
              return values for the indication*/
     while(null_msg[clk_en_len++]);
     clk = null_msg;     
  }

  /* Calculating the size of the packet */
  sizetoberet = sizeof(pwrdb_log_clk_get_clk_en_type) - sizeof(char) + (clk_en_len) * sizeof(char);

  if ( sizetoberet > len )
  {
     /* can't fit this into the buffer, time to stop */
     *res = PWRDB_RES_OK_CONTINUE;
     return 0;
  }
  else
  {
     ptr->enable = (uint8)(log_item->data.clk_get_clk_en.enable);;
     ptr->hdr.len  = sizetoberet;

     /* Get the address where the values to be stored to */
     for(num=0;num<clk_en_len;num++)
     {
         *(ptr->clk + num) = *(clk + num);
     }

     return sizetoberet;
  }
}

/*===========================================================================

FUNCTION PWRDB_PACK_LOG_CLK_GET_CLK_FREQ

===========================================================================*/
static uint32 pwrdb_pack_log_clk_get_clk_freq( pwrdb_log_type *log_item, uint8 *bptr, int len, pwrdb_res_type *res )
{
  
  pwrdb_log_clk_get_clk_freq_type *ptr = (pwrdb_log_clk_get_clk_freq_type *)bptr;
  uint32 sizetoberet=0;
  uint16 num=0;
  char *clk=NULL;
  char *null_msg = "message logging failed";
  uint16 clk_en_len=log_item->data.clk_get_clk_freq.clk_en_len;
  

  clk = log_item->data.clk_get_clk_freq.clk;

  if(clk == NULL)
  {
     clk_en_len=0;
     /* Incase of Malloc failures returning the Read address itself as the
              return values for the indication*/
     while(null_msg[clk_en_len++]);
     clk = null_msg;     
  }

  /* Calculating the size of the packet */
  sizetoberet = sizeof(pwrdb_log_clk_get_clk_freq_type) - sizeof(char) + (clk_en_len) * sizeof(char);

  if ( sizetoberet > len )
  {
     /* can't fit this into the buffer, time to stop */
     *res = PWRDB_RES_OK_CONTINUE;
     return 0;
  }
  else
  {
     ptr->freq = (uint32)(log_item->data.clk_get_clk_freq.freq);;
     ptr->hdr.len  = sizetoberet;

     /* Get the address where the values to be stored to */
     for(num=0;num<clk_en_len;num++)
     {
         *(ptr->clk + num) = *(clk + num);
     }

     return sizetoberet;
  }
}


/* EJECT */
/*===========================================================================

                      REGIONAL FUNCTION DEFINITIONS

===========================================================================*/

/*===========================================================================

FUNCTION PWRDB_UNPACK_SCRIPT_COMMANDS

DESCRIPTION
  Unpack commands from a file or diag packet into the internal
  event/command structure.
 
  This function may be called multiple times if the script is longer than
  the memory buffer. Each time it is called this function will traverse
  the event list to the last event and then traverse the command list of
  that event to the last command.

PARAMETERS 
  event_ptr - Pointer to head of the list of events. May be NULL if there
              are no events yet.
  clen      - max number of commands that may be unpacked
  buf       - buffer to unpack the commands from
  blen      - length of the buffer (in bytes)
  res       - pointer to variable to return result information

RETURN VALUE
  Of function:
    PWRDB_RES_OK      - The buffer was completed processed with no errors.
    PWRDB_RES_ERROR   - There was an error processing the buffer.
    PWRDB_RES_PARTIAL - The last command in the buffer was not complete.
                        The function return value can be used to compute
                        the number of unprocessed bytes. These bytes should
                        be moved to the front of the buffer, additional
                        bytes added to the buffer and then this function
                        can be called again.

  bytes_read:
    The number of bytes from buf that were processed

  cmd_cntr:
    The variable refereneced by this pointer is incremented each time a
    command is added to the cmd_ptr buffer. *cmd_cntr is NOT required to be 0
    when this function is called so it CANNOT be considered to hold the number
    of commands that have been processed.

    This behavior is used to allow correct updating of
    pwrdb_command_events[pwrdb_event_curr_ix].num_cmds in the function
    pwrdb_setup_event().

SIDE EFFECTS
  Adds events and commands under event_ptr

===========================================================================*/
pwrdb_res_type pwrdb_unpack_script_commands( pwrdb_event_ll_type **event_ptr,
                                             uint32                clen,
                                             uint8                *buf,
                                             uint32                blen,
                                             uint32               *bytes_read,
                                             uint32               *cmd_cntr )
{
  uint32                   buf_ix     = 0;
  pwrdb_res_type           status     = PWRDB_RES_OK;
  pwrdb_cmd_null_cmd_type *in_cmd_ptr;
  pwrdb_event_ll_type     *current_event   = NULL;
  pwrdb_command_ll_type   *current_command = NULL;

  PWRDB_ASSERT( event_ptr != 0 );
  PWRDB_ASSERT( buf       != 0 );
  PWRDB_ASSERT( cmd_cntr  != 0 );

  /* Traverse existing event/command structure */
  current_event = *event_ptr;
  if (current_event != NULL)
  {
    while (current_event->next != NULL)
    {
      current_event = current_event->next;
    }

    current_command = current_event->pwrdb_cmds;
    if (current_command != NULL)
    {
      while (current_command->next != NULL)
      {
        current_command = current_command->next;
      }
    }
  }

  /* loop through the buffer until the end of the buffer */
  in_cmd_ptr = (pwrdb_cmd_null_cmd_type*)(buf);
  for (;;)
  {
    if ( in_cmd_ptr->hdr.cmd_id == PWRDB_CMD_EVENT )
    {
      pwrdb_event_ll_type *prev_event = current_event;

      current_event = pwrdb_unpack_cmd_event( in_cmd_ptr );
      if (current_event == NULL )
      {
        status = PWRDB_RES_ERROR;
        break; /* for */
      }

      if (*event_ptr == NULL)
      {
        // first event in list
        *event_ptr = current_event;
      }
      else
      {
        // next event in list
        prev_event->next = current_event;
      }
      current_command = NULL;
    }
    else if (current_event == NULL)
    {
      /* we didn't process an event command yet,
         we can't process any other commands
       */
      status = PWRDB_RES_ERROR;
      PWRDB_MSG_E0("Commands before any event.");
      break; /* for (;;) */
    }
    else if ( *cmd_cntr >= clen )
    {
      /* no room for any more commands */
      status = PWRDB_RES_ERROR;
      break;
    }
    else
    {
      // process a command, we know we already has at least one event
      pwrdb_command_ll_type* prev_command = current_command;
      current_command = pwrdb_unpack_cmd( in_cmd_ptr );  

      if (current_command == NULL)
      {
        status = PWRDB_RES_ERROR;
        break;
      }

      if (prev_command == NULL)
      {
        // first command for this event
        current_event->pwrdb_cmds = current_command;
      }
      else
      {
        // next command in list for this event
        prev_command->next = current_command;
      }
    }

    (*cmd_cntr)++;

    /* Update index into input buffer and check for end of loop */
    buf_ix += in_cmd_ptr->hdr.len;

    if ( buf_ix == blen )
    {
      status = PWRDB_RES_OK;
      break; /* for (;;) */
    }
    else if ( buf_ix+sizeof(pwrdb_cmd_null_cmd_type) > blen )
    {
      status = PWRDB_RES_PARTIAL;
      break; /* for (;;) */
    }
    else
    {
      in_cmd_ptr = (pwrdb_cmd_null_cmd_type*)(&(buf[buf_ix]));

      if ( ( buf_ix + in_cmd_ptr->hdr.len ) > blen )
      {
        status = PWRDB_RES_PARTIAL;
        break; /* for (;;) */
      }
    }
  } /* for (;;) */

  *bytes_read = buf_ix;

  return status;

} /* pwrdb_unpack_script_commands */

/*===========================================================================

FUNCTION PWRDB_PACK_LOG_ITEMS_RESET

DESCRIPTION
  Reset the log item read pointer so that the next call to
  pwrdb_pack_log_items() will start with the oldest log item.

===========================================================================*/
void pwrdb_pack_log_items_reset( void )
{
  pwrdb_log_read_ix    = 0;
  pwrdb_log_first_read = TRUE;
}

/*===========================================================================

FUNCTION PWRDB_PACK_LOG_ITEMS

DESCRIPTION
  Packs items from log into buf.

  NOTES:
  1. Log may contain more data than can fit in buf. This function
  supports being called multiple times to handle this case.
  2. Log is circular so the intial starting point may not be at the start
  of the log array. This is determined by looking at llen and lix.

PARAMETERS
  buf   - pointer to a buffer to pack the log items into
  blen  - length of the buffer

  log   - pointer to the log array to read from
  llen  - total length of the log array
  lix   - next element that would have been written in the log array
  res   - used to pass back result:
           PWRDB_RES_OK_CONTINUE - buffer was filled OK, more items left to process
           PWRDB_RES_OK_DONE     - buffer was filled OK, no items left to process
           PWDB_RES_ERROR        - there was an error packing a log item

DEPENDENCIES
  Should call pwrdb_pack_log_items_reset() before calling this function.

RETURN VALUE
  number of bytes written into the buffer

SIDE EFFECTS
  pwrdb_log_read_ix is updated (required to support calling this function
  multiple times if buffer is too small to hold the whole log)

===========================================================================*/
uint32 pwrdb_pack_log_items(  uint8          *buf,
                              uint32          blen,
                              pwrdb_log_type *log,
                              uint32          llen,
                              uint32          lix,
                              pwrdb_res_type *res )
{
  uint32               buf_ix;
  pwrdb_res_type       status;
  pwrdb_log_null_type *l_ptr;
  PWRDB_ASSERT( buf != 0 );
  PWRDB_ASSERT( log != 0 );
  PWRDB_ASSERT( res != 0 );

  /* Set the read index if this is the first call to this function
     (since call to pwrdb_reset()). A little complex since we are
     dealing with a circular buffer.
   */
  if ( pwrdb_log_first_read )
  {
    if ( lix >= llen ) /* > should never happen but do for error checking */
    {
      pwrdb_log_read_ix = 0;
    }
    else /* log has wrapped */
    {
      pwrdb_log_read_ix = lix;
    }
    pwrdb_log_first_read = FALSE;
  }

  if ( lix >= llen ) /* > should never happen but do for error checking */
  {
    lix = 0;
  }

  buf_ix = 0;
  status = PWRDB_RES_OK;

  do /* break out of loop on error, or when buffer full,
        won't process null log so OK to process
        first item of empty log
      */
  {
    /* Save address where current log item will be written so we can
       update id and time at the end of the switch. */
    l_ptr = (pwrdb_log_null_type *)&(buf[buf_ix]);

    switch ( log[pwrdb_log_read_ix].log_id )
    {
    case PWRDB_LOG_NULL:
      /* do nothing */
      break;

    case PWRDB_LOG_EVENT:
      buf_ix += pwrdb_pack_log_event( &(log[pwrdb_log_read_ix]),
                                      &(buf[buf_ix]), blen-buf_ix,
                                      &status );
      break;

    case PWRDB_LOG_TLMM_GET_CURR_CONFIG:
      buf_ix += pwrdb_pack_log_tlmm_get_curr_config( &(log[pwrdb_log_read_ix]),
                                                     &(buf[buf_ix]), blen-buf_ix,
                                                     &status );
      break;

    case PWRDB_LOG_TLMM_INPUT:
      buf_ix += pwrdb_pack_log_tlmm_input( &(log[pwrdb_log_read_ix]),
                                           &(buf[buf_ix]), blen-buf_ix,
                                           &status );
      break;

    case PWRDB_LOG_TLMM_GET_PIN_STATUS:
      buf_ix += pwrdb_pack_log_tlmm_get_pin_status( &(log[pwrdb_log_read_ix]),
                                                    &(buf[buf_ix]), blen-buf_ix,
                                                    &status );
      break;

    case PWRDB_LOG_TLMM_IS_LOCKED:
      buf_ix += pwrdb_pack_log_tlmm_is_locked( &(log[pwrdb_log_read_ix]),
                                               &(buf[buf_ix]), blen-buf_ix,
                                               &status );
      break;


    case PWRDB_LOG_CLK_GET_CLK_EN:
      buf_ix += pwrdb_pack_log_clk_get_clk_en( &(log[pwrdb_log_read_ix]),
                                               &(buf[buf_ix]), blen-buf_ix,
                                               &status );
      break;

    case PWRDB_LOG_CLK_GET_CLK_FREQ:
      buf_ix += pwrdb_pack_log_clk_get_clk_freq( &(log[pwrdb_log_read_ix]),
                                                 &(buf[buf_ix]), blen-buf_ix,
                                                 &status );
      break;

#ifdef PWRDB_PRO
    case PWRDB_LOG_PEEK8:
      buf_ix += pwrdb_pack_log_peek8( &(log[pwrdb_log_read_ix]),
                                      &(buf[buf_ix]), blen-buf_ix,
                                      &status );
      break;

    case PWRDB_LOG_PEEK16:
      buf_ix += pwrdb_pack_log_peek16( &(log[pwrdb_log_read_ix]),
                                       &(buf[buf_ix]), blen-buf_ix,
                                       &status );
      break;

    case PWRDB_LOG_PEEK32:
      buf_ix += pwrdb_pack_log_peek32( &(log[pwrdb_log_read_ix]),
                                       &(buf[buf_ix]), blen-buf_ix,
                                       &status );
      break;

    case PWRDB_LOG_PEEK32_RANGE:
      buf_ix += pwrdb_pack_log_peek32_range( &(log[pwrdb_log_read_ix]),
                                       &(buf[buf_ix]), blen-buf_ix,
                                       &status );
      break;

    case PWRDB_LOG_STRING:
      buf_ix += pwrdb_pack_log_string( &(log[pwrdb_log_read_ix]),
                                       &(buf[buf_ix]), blen-buf_ix,
                                       &status );
      break;

    case PWRDB_LOG_DATA3_STRING:
      buf_ix += pwrdb_pack_log_data3_string( &(log[pwrdb_log_read_ix]),
                                             &(buf[buf_ix]), blen-buf_ix,
                                             &status );
      break;

    case PWRDB_LOG_NPA_QUERY_BY_NAME:
      buf_ix += pwrdb_pack_log_npa_query_by_name( &(log[pwrdb_log_read_ix]),
                                                  &(buf[buf_ix]), blen-buf_ix,
                                                  &status );
      break;
#endif /* ifdef PRWDB_PRO */

    default:
      /* unsupported log item */
      status = PWRDB_RES_ERROR;

      PWRDB_MSG_E1("Unknown log item %i.", log[pwrdb_log_read_ix].log_id);

      break;
    } /* switch */

    if ( status == PWRDB_RES_OK )
    {
      l_ptr->hdr.log_id = log[pwrdb_log_read_ix].log_id;
      l_ptr->hdr.time   = log[pwrdb_log_read_ix].time;

      /* update the read index */
      if (++pwrdb_log_read_ix >= llen)
      {
        pwrdb_log_read_ix = 0;
      }
    }

  } while ( status == PWRDB_RES_OK && pwrdb_log_read_ix != lix );

  if ( status == PWRDB_RES_OK && pwrdb_log_read_ix == lix )
  {
    /* must have no log items left */
    status = PWRDB_RES_OK_DONE;
    pwrdb_log_first_read = TRUE; /* in case we want to read the log again */
  }

  *res = status;
  return buf_ix;

} /* pwrdb_pack_log_items */


