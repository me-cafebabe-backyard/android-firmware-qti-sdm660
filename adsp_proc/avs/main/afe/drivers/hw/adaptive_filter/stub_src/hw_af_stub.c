/*==============================================================================
  @brief This file contains stub implementation 

  Copyright (c) 2017 QUALCOMM Technologies, Inc.  All Rights Reserved.
  QUALCOMM Technologies, Inc Proprietary.  Export of this technology or
  software is regulated by the U.S. Government, Diversion contrary to U.S.
  law prohibited.
==============================================================================*/

/*==============================================================================
  Edit History

  $Header: //components/rel/avs.adsp/2.8/afe/drivers/hw/adaptive_filter/stub_src/hw_af_stub.c#2 $

  when       who     what, where, why
  --------   ---     -------------------------------------------------------
  09/19/17   unni     Created file
==============================================================================*/

#include "hw_af.h"

/*==============================================================================
   Public Function stub definition
==============================================================================*/

ADSPResult hw_af_init()
{
  return ADSP_EOK;
}

ADSPResult hw_af_deinit()
{
  return ADSP_EOK;
}

hw_af_t* hw_af_open(
  hw_af_config_t* config_ptr, 
  hw_af_client_info_t* client_info_ptr)
{
  return NULL;
}

void hw_af_close(
  hw_af_t* hw_af_ptr)
{
  return;
}

ADSPResult hw_af_process(
  hw_af_t* hw_af_ptr,
  hw_af_buffer_t* hw_af_buffer_ptr,
  hw_af_callback_func_t callback_func,
  void* callback_arg_ptr)
{
  return ADSP_EOK;
}

ADSPResult hw_af_fetch(
  hw_af_t* hw_af_ptr,
  hw_af_buffer_t* hw_af_buffer_ptr)
{
  return ADSP_EOK;
}


