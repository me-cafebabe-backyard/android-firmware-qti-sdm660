/*==============================================================================
  FILE:         spm_internal.c

  OVERVIEW:     This file provides implementation of functions that usually are
                internal to SPM driver (in terms of functionality or data 
                access).

  DEPENDENCIES: None
                
                Copyright (c) 2015 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/spm/src/common/spm_internal.c#1 $
$DateTime: 2020/02/10 01:57:30 $
================================================================================*/
#include "spm.h"
#include "spm_internal.h"
#include "spm_hal.h"
#include "spm_hal_bsp.h"

/*=======================================================================
 *                           GLOBAL FUNCTIONS
 *======================================================================*/
/*
 * spm_internal_config
 *
 * @note - This needs somewhat more refactoring to decouple BSP structures.
 */
void spm_internal_config(spm_handle handle)
{
  uint32                  i;
  uint8*                  addr        = handle->addr;
  spm_hal_bsp_cfg_t       *cfg        = handle->cfg;
  spm_hal_bsp_clk_cfg_t   *clk_cfg    = &cfg->clk_cfg;
  spm_hal_bsp_ctl_cfg_t   *ctl_cfg    = &cfg->ctl_cfg;
  spm_hal_bsp_delay_cfg_t *delay_cfg  = &cfg->delay_cfg;
  spm_hal_bsp_mode_t      *mode       = NULL;
  spm_hal_bsp_pmic_cfg_t  *pmic_cfg   = NULL;

  SPM_SEQ_LOCK(handle);

  spm_hal_config_clk_div(addr, clk_cfg->clk_div);  
  spm_hal_config_wakeup(addr, ctl_cfg->wakeup);
  spm_hal_config_delays(addr, delay_cfg->delay1, 
                        delay_cfg->delay2, delay_cfg->delay3);

  for(i = 0; i < cfg->pmic_cfg_count; i++)
  {
    pmic_cfg = &cfg->pmic_cfg[i];

    spm_hal_config_pmic(addr, pmic_cfg->mode, pmic_cfg->index,
                        pmic_cfg->data, pmic_cfg->size, pmic_cfg->delay);
  }

  /* Some basic set up for sanity. */
  spm_hal_invalidate_cmd_seqs(handle->addr);
  for(i = 0; i < handle->mode_count; i++)
  {
    mode = &handle->modes[i];
    mode->start_addr = SPM_HAL_INVALID_SEQ_START_ADR;
  }

  handle->copied_cmds = 0;

  SPM_SEQ_UNLOCK(handle);
}

/*
 * spm_internal_copy_cmd_seqs
 */
spm_result_t spm_internal_copy_cmd_seqs(spm_handle handle)
{
  uint32              i           = 0;
  spm_result_t        result      = SPM_SUCCESS;
  uint8               *spm_base   = handle->addr;
  spm_hal_bsp_mode_t  *mode       = NULL;
  uint32              copied_cmds = 0;

  SPM_SEQ_LOCK(handle);

  for(i = 0; i < handle->mode_count; i++)
  {
    mode = &handle->modes[i];

    if(0 == mode->sequence.length)
    {
      result = SPM_INVALID_PARAM;
      break;
    }

    copied_cmds = spm_hal_copy_cmd_seq(spm_base, handle->copied_cmds, 
                                       mode->sequence.cmds, mode->sequence.length);

    if(0 == copied_cmds)
    {
      result = SPM_NO_SEQ_MEMORY;
      break;
    }
    
    mode->start_addr = handle->copied_cmds;
    mode->ctl_vals |= SPM_HAL_START_ADR_SET(mode->start_addr);
    handle->copied_cmds += copied_cmds;
  }

  SPM_SEQ_UNLOCK(handle);

  return result;
}

/*
 * spm_internal_mode_index
 */
uint32 spm_internal_mode_index(spm_handle handle, uint8 lpm_id)
{
  uint32              i = 0;
  spm_hal_bsp_mode_t  *mode;

  for(i = 0; i < handle->mode_count; i++)
  {
    mode = &handle->modes[i];
    if(mode->mode_id == lpm_id)
      return i;
  }

  return SPM_HAL_INVALID_MODE_INDEX;
}

