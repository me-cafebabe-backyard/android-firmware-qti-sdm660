/*==============================================================================
  FILE:         spm.c

  OVERVIEW:     This file implements some of the APIs defined in spm public 
                header file to interact with SPM HW block(s).

  DEPENDENCIES: None
                
                Copyright (c) 2015 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/spm/src/common/spm.c#1 $
$DateTime: 2020/02/10 01:57:30 $
================================================================================*/
#ifdef SPM_USE_SHARED_STD_LIB
#include "shared_lib_imports.h"
#else
#include <string.h>
#include <stdlib.h>
#endif
#include "spm.h"
#include "CoreVerify.h"
#include "spm_hal.h"
#include "spm_hal_bsp.h"
#include "spm_internal.h"

/*=======================================================================
 *                        EXTERNAL GLOBAL VARIABLES
 *======================================================================*/
extern spm_t  *g_spms;
extern uint32 g_spmCount;

/*=======================================================================
 *                          GLOBAL DRIVER FUNCTIONS
 *======================================================================*/
/*
 * spm_driver_get_handles
 */
uint32 spm_driver_get_handles(const char  *entity,
                              uint32      count,
                              spm_handle  *handles)
{
  uint32 copiedCount  = 0;
  uint32 nSpm         = 0;

  if((NULL == entity) || (0 == count) || (NULL == handles))
  {
    return copiedCount;
  }

  for(nSpm = 0; nSpm < g_spmCount; nSpm++)
  {
    if(0 == strncmp(entity, g_spms[nSpm].name, SPM_INSTANCE_MAX_NAME_LEN))
    {
      ((spm_handle *)handles)[copiedCount++] = &g_spms[nSpm];

      if(copiedCount >= count)
        break;
    }
  }

  return copiedCount;
}

/*
 * spm_driver_init
 */
void spm_driver_init(void)
{
  /* Nothing as of now to intialize in instance agnostic way. */
  spm_target_init();
  return;
}

/*=======================================================================
 *           GLOBAL DRIVER FUNCTIONS NOT NEEDED IN LITE VERSION
 *======================================================================*/
#ifndef SPM_LITE
/*
 * spm_instance_get_count
 */
uint32 spm_driver_get_count(const char *entity)
{
  uint32 count  = 0;
  uint32 nSPM   = 0;

  if(NULL == entity)
  {
    return count;
  }

  for(nSPM = 0; nSPM < g_spmCount; nSPM++)
  {
    if(0 == strncmp(entity, g_spms[nSPM].name, SPM_INSTANCE_MAX_NAME_LEN))
    {
      count++;
    }
  }

  return count;
}
#endif

/*=======================================================================
 *                     GLOBAL SPM INSTANCE FUNCTIONS
 *======================================================================*/
/*
 * spm_instance_init
 */
spm_result_t spm_instance_init(spm_handle handle)
{
  spm_result_t result;

  if(NULL == handle || NULL == handle->cfg || NULL == handle->modes) 
    return SPM_INVALID_PARAM;

  /* Create and lock out multiple changes to this instance */
  SPM_MUTEX_CREATE(handle->lock);
  SPM_SEQ_LOCK(handle);

  /* Initialize the SPM instance */
  spm_env_init(handle);
  spm_internal_config(handle);

  result = spm_internal_copy_cmd_seqs(handle);

  SPM_SEQ_UNLOCK(handle);

  return result;
}

/*
 * spm_instance_enable
 */
spm_result_t spm_instance_enable(spm_handle handle, boolean enable)
{
  if(!SPM_VALID_HANDLE(handle))
    return SPM_INVALID_PARAM;

  spm_hal_enable(handle->addr, (enable ? 1 : 0));

  return SPM_SUCCESS;
}

/*
 * spm_instance_set_lpm
 */
spm_result_t spm_instance_set_lpm(spm_handle handle, uint8 lpm)
{
  spm_hal_bsp_mode_t  *mode;
  int32               mode_index;
  
  if(!SPM_VALID_HANDLE(handle))
    return SPM_INVALID_HANDLE;

  mode_index = spm_internal_mode_index(handle, lpm);

  if(SPM_HAL_INVALID_MODE_INDEX == mode_index)
    return SPM_INVALID_PARAM;

  mode = &handle->modes[mode_index];

  if(SPM_HAL_INVALID_SEQ_START_ADR == mode->start_addr)
    return SPM_INVALID_PARAM;

  spm_hal_config_lpm_ctl(handle->addr, mode->ctl_vals);

  return SPM_SUCCESS;
}

/*=======================================================================
 *     GLOBAL INSTANCE FUNCTIONS FOR DYNAMIC SEQUENCE REGISTRATION
 *======================================================================*/
#ifdef SPM_DYNAMIC_SEQ
/**
 * @brief Ensures a dynamic SPM mode has already been added and retrieves 
 *        that mode based on the given ID 
 *
 * @param handle  : Handle to SPM where we want to find out running low 
 *                  power mode.
 * @param mode_id : Low power mode id to retrieve.  
 * @param mode    : Previously registered mode assocated with the mode_id
 *  
 * @return SPM error code (@see spm_result_t)
 */
static spm_result_t spm_instance_get_dyn_mode(spm_handle          handle,
                                              uint16              mode_id,
                                              spm_hal_bsp_mode_t  **mode)
{
  uint32        nMode;
  spm_result_t  result = SPM_INVALID_PARAM;

  *mode = NULL;

  if(!SPM_VALID_HANDLE(handle))
  {
    result = SPM_INVALID_HANDLE;
  }
  else 
  {
    result = SPM_MODE_ID_NOT_EXIST;

    if((NULL != handle->dyn_modes) && (handle->dyn_mode_count > 0))
    {
      /* Verify ID exists already */
      for(nMode = 0; nMode < handle->dyn_mode_count; nMode++)
      {
        *mode = &handle->dyn_modes[nMode];
        if(mode_id == (*mode)->mode_id)
        {
          result = SPM_SUCCESS;
          break;
        }
      }
    }
  }

  return result;
}

/*
 * spm_instance_update_sequence
 */
spm_result_t spm_instance_update_cmd_in_seq(spm_handle handle,
                                            uint16     start_addr,
                                            uint16     cmd_offset,
                                            spm_cmd_t  command)
{
  spm_hal_bsp_mode_t  *mode;
  spm_result_t        result = SPM_INVALID_PARAM;

  SPM_SEQ_LOCK(handle);

  /* Some basic sanity checks first */
  result = spm_instance_get_dyn_mode(handle, start_addr, &mode);

  if(SPM_SUCCESS == result)
  {
    if(cmd_offset < mode->sequence.length)
    {
      spm_hal_config_cmd_at_idx(handle->addr, 
                                (mode->start_addr + cmd_offset),
                                command);
    }
    else
    {
      result = SPM_INVALID_PARAM;
    }
  }

  SPM_SEQ_UNLOCK(handle);

  return result;
}

/*
 * spm_instance_update_sequence
 */
spm_result_t spm_instance_update_sequence(spm_handle          handle,
                                          uint16              start_addr,
                                          spm_sequence_data_t *new_seq)
{
  uint16              cmds_copied;
  spm_hal_bsp_mode_t  *dyn_mode;
  spm_result_t        result        = SPM_INVALID_PARAM;

  SPM_SEQ_LOCK(handle);

  /* Some basic sanity checks first */
  result = spm_instance_get_dyn_mode(handle, start_addr, &dyn_mode);

  if(SPM_SUCCESS == result)
  {
    /* Everything checks out, update the sequence data */
    cmds_copied = spm_hal_copy_cmd_seq(handle->addr, dyn_mode->start_addr,
                                       new_seq->cmds, new_seq->length);

    CORE_VERIFY(cmds_copied == new_seq->length);

    dyn_mode->sequence.cmds = new_seq->cmds;
  }

  SPM_SEQ_UNLOCK(handle);

  return result;
}

/*
 * spm_instance_program_cmd_seq
 */
spm_result_t spm_instance_program_cmd_seq(spm_handle          handle,
                                          spm_sequence_data_t *new_seq,
                                          uint16              *start_addr)
{
  uint16              cmds_copied;
  spm_hal_bsp_mode_t  *dyn_mode;
  spm_result_t        result = SPM_SUCCESS;

  SPM_SEQ_LOCK(handle);

  /* Some basic sanity checks first */
  if(!SPM_VALID_HANDLE(handle))
  {
    result = SPM_INVALID_HANDLE;
  }
  else if((NULL == new_seq->cmds) || (0 == new_seq->length))
  {
    result = SPM_INVALID_PARAM;
  }

  if(SPM_SUCCESS == result)
  {
    /* Parameters look ok, program the sequence */
    cmds_copied = spm_hal_copy_cmd_seq(handle->addr, handle->copied_cmds,
                                       new_seq->cmds, new_seq->length);
    if(0 == cmds_copied)
    {
      result = SPM_NO_SEQ_MEMORY;
    }
    else
    {
      CORE_VERIFY(cmds_copied == new_seq->length);

      CORE_VERIFY_PTR(handle->dyn_modes = 
                      realloc(handle->dyn_modes, 
                              sizeof(spm_hal_bsp_mode_t) * (handle->dyn_mode_count + 1)));

      dyn_mode = &handle->dyn_modes[handle->dyn_mode_count];

      /* Update mode data */
      dyn_mode->sequence.cmds     = new_seq->cmds;
      dyn_mode->sequence.length   = new_seq->length;
      dyn_mode->start_addr        = dyn_mode->mode_id = *start_addr = handle->copied_cmds;
      dyn_mode->ctl_vals          = SPM_HAL_START_ADR_SET(dyn_mode->start_addr);

      /* Update handle data */
      handle->copied_cmds += cmds_copied;
      handle->dyn_mode_count++;
    }
  }

  SPM_SEQ_UNLOCK(handle);

  return result;
}
#endif /* SPM_DYNAMIC_SEQ */

/*=======================================================================
 *           GLOBAL INSTANCE FUNCTIONS NOT NEEDED IN LITE VERSION
 *======================================================================*/
#ifndef SPM_LITE
/*
 * spm_instance_get_executing_lpm
 */
spm_result_t spm_instance_get_executing_lpm(spm_handle  handle,
                                            uint16      *mode_id)
{
  uint16              start;
  uint16              end;
  uint16              last_cmd_adr;
  uint32              i = 0;
  spm_hal_bsp_mode_t  *mode;

  if(!SPM_VALID_HANDLE(handle))
    return SPM_INVALID_HANDLE;

  if(NULL == mode_id)
    return SPM_INVALID_PARAM;

  *mode_id = SPM_HAL_INVALID_MODE_INDEX;
  last_cmd_adr = spm_hal_get_last_cmd_addr(handle->addr);
  for(i = 0; i < handle->mode_count; i++)
  {
    mode = &handle->modes[i];
    start = mode->start_addr;
    end = start + mode->sequence.length - 1;    /* -1 for end of sequence command */

    if( 0 != last_cmd_adr && last_cmd_adr >= start && last_cmd_adr < end )
    {
      /* There is a subtlety here.
       * If we don't check last_cmd_adr to be non zero, any call made before 
       * spm is triggered for the first time will incorrectly return first 
       * mode as the one being executed. This may misrepresent node's state.
       * 
       * However, with this check, if SPM is indeed triggered and query is
       * made just after first command execution, we would return no mode
       * as running. This can happen even when the query is made from 
       * different core before before actually SPM is triggered. So seems 
       * like a safe window. */
      *mode_id = mode->mode_id;
      break;
    }
  }

  return SPM_SUCCESS;
}
#endif /* SPM_LITE */

