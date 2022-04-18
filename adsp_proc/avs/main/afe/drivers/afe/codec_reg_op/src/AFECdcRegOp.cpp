/*========================================================================
   This file contains HW codec specific configuration, interrupt handling

Copyright (c) 2017 QUALCOMM Technologies, Inc.  All Rights Reserved.
QUALCOMM Technologies, Inc Proprietary.  Export of this technology or software is regulated
  by the U.S. Government, Diversion contrary to U.S. law prohibited.

  $Header: //components/rel/avs.adsp/2.8/afe/drivers/afe/codec_reg_op/src/AFECdcRegOp.cpp#1 $
 ====================================================================== */

/*==========================================================================
  Include files
========================================================================== */
#include "AFECdcRegOp.h"
#include "AFECodecHandler.h"


capi_v2_cdc_reg_op_vtbl_t cdc_reg_vtbl =
{
    CDC_REG_OP_VTBL_VERSION,
    afe_cdc_reg_access_registration,
    afe_cdc_reg_access_deregistration,
    afe_cdc_register_read,
    afe_cdc_register_multi_read,
    afe_cdc_register_write,
    afe_cdc_register_update
};

extern afe_cdc_handler_t *cdc_handler_global_ptr;

/*==========================================================================
  Functions
========================================================================== */

capi_v2_cdc_handle afe_cdc_reg_access_registration(void)
{
  ADSPResult result;

  if(ADSP_EOK == afe_svc_check_codec_interrupts_supported())
  {
    if (ADSP_EOK == (result = afe_slimbus_core_driver_open((void *) cdc_handler_global_ptr->sb_cfg.p_sb_driver)))
    {
      MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "AFE cdc reg access registration successful");

      return ( cdc_handler_global_ptr->sb_cfg.p_sb_driver );
    }
  }

  MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "AFE cdc reg access registration failed");

  return NULL;
}

capi_v2_err_t afe_cdc_reg_access_deregistration(capi_v2_cdc_handle cdc_dev_handle)
{
  ADSPResult result;

  if(ADSP_EOK == afe_svc_check_codec_interrupts_supported())
  {
    if(NULL != cdc_dev_handle)
    {
      if (ADSP_EOK == (result = afe_slimbus_core_driver_close((void *) cdc_handler_global_ptr->sb_cfg.p_sb_driver)))
      {
        MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "AFE cdc reg access deregistration successful");

        return CAPI_V2_EOK;
      }
    }
  }

  return CAPI_V2_EFAILED;
}

capi_v2_err_t afe_cdc_register_read(capi_v2_cdc_handle cdc_dev_handle, uint32_t reg_addr,\
                                           uint8_t* read_value_ptr, uint32_t reg_bit_width)
{
  ADSPResult result = ADSP_EFAILED;

  if(ADSP_EOK == afe_svc_check_codec_interrupts_supported())
  {
    if( (NULL != cdc_dev_handle) && (NULL != reg_addr) && (NULL != read_value_ptr) )
    {
      result = afe_sb_read_register(cdc_dev_handle,
                                    &cdc_handler_global_ptr->sb_cfg.reg_prop,
                                    reg_addr,
                                    read_value_ptr,
                                    0xFFFF, // Read all bits of the register
                                    reg_bit_width,
                                    TRUE); // read register need to be always blocking call

      if(ADSP_EOK == result)
      {
        MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "afe_cdc_register_read: reg_addr: 0x%lx, value: %d", reg_addr, *read_value_ptr);

        return CAPI_V2_EOK;
      }
    }
  }

  return CAPI_V2_EFAILED;
}

capi_v2_err_t afe_cdc_register_multi_read(capi_v2_cdc_handle cdc_dev_handle, uint32_t reg_addr, \
                                                 uint8_t* read_value_ptr, uint32_t reg_bit_width, uint32_t no_of_regs_to_read)
{
  ADSPResult result = ADSP_EFAILED;

  if(ADSP_EOK == afe_svc_check_codec_interrupts_supported())
  {
    if( (NULL != cdc_dev_handle) && (NULL != reg_addr) && (NULL != read_value_ptr) )
    {
      result = afe_sb_read_multi_register(cdc_dev_handle,
                                          &cdc_handler_global_ptr->sb_cfg.reg_prop,
                                          reg_addr,
                                          read_value_ptr,
                                          0xFFFF, // Read all bits of each register
                                          reg_bit_width,
                                          no_of_regs_to_read,
                                          TRUE);

      if(ADSP_EOK == result)
      {
        return CAPI_V2_EOK;
      }
    }
  }

  return CAPI_V2_EFAILED;
}

capi_v2_err_t afe_cdc_register_write(capi_v2_cdc_handle cdc_dev_handle, uint32_t reg_addr, uint8_t* write_value_ptr,\
                                            uint32_t reg_field_bit_mask, uint32_t reg_bit_width,\
                                            bool_t is_blocking)
{
  ADSPResult result = ADSP_EFAILED;

  if(ADSP_EOK == afe_svc_check_codec_interrupts_supported())
  {
    if( (NULL != cdc_dev_handle) && (NULL != reg_addr) && (NULL != write_value_ptr) )
    {
      result = afe_sb_write_register(cdc_dev_handle,
                                     &cdc_handler_global_ptr->sb_cfg.reg_prop,
                                     reg_addr,
                                     write_value_ptr,
                                     reg_field_bit_mask,
                                     reg_bit_width,
                                     is_blocking);

      if(ADSP_EOK == result)
      {
        return CAPI_V2_EOK;
      }
    }
  }

  return CAPI_V2_EFAILED;
}

capi_v2_err_t afe_cdc_register_update(capi_v2_cdc_handle cdc_dev_handle, uint32_t reg_addr, uint8_t* write_value_ptr,\
                                             uint32_t reg_field_bit_mask,  uint32_t reg_bit_width, \
                                             bool_t is_blocking)
{
  ADSPResult result = ADSP_EFAILED;

  if(ADSP_EOK == afe_svc_check_codec_interrupts_supported())
  {
    if( (NULL != cdc_dev_handle) && (NULL != reg_addr) && (NULL != write_value_ptr) )
    {
      result = afe_sb_update_register(cdc_dev_handle,
                                      &cdc_handler_global_ptr->sb_cfg.reg_prop,
                                      reg_addr,
                                      write_value_ptr,
                                      reg_field_bit_mask,
                                      reg_bit_width,
                                      is_blocking);

      if(ADSP_EOK == result)
      {
        return CAPI_V2_EOK;
      }
    }
  }

  return CAPI_V2_EFAILED;
}
