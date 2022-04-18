/*========================================================================
   This file contains HW codec specific configuration, interrupt handling

Copyright (c) 2017 QUALCOMM Technologies, Inc.  All Rights Reserved.
QUALCOMM Technologies, Inc Proprietary.  Export of this technology or software is regulated
  by the U.S. Government, Diversion contrary to U.S. law prohibited.

  $Header: //components/rel/avs.adsp/2.8/afe/drivers/afe/codec_reg_op/stub_src/AFECdcRegOp_stub.cpp#1 $
 ====================================================================== */

/*==========================================================================
  Include files
========================================================================== */
#include "AFECdcRegOp.h"


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

/*==========================================================================
  Functions
========================================================================== */

capi_v2_cdc_handle afe_cdc_reg_access_registration(void)
{
  MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "AFE cdc reg access registration failed, AFE cdc reg op is stubbed");

  return NULL;
}

capi_v2_err_t afe_cdc_reg_access_deregistration(capi_v2_cdc_handle cdc_dev_handle)
{
  MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "AFE cdc reg access deregistration failed, AFE cdc reg op is stubbed");

  return CAPI_V2_EUNSUPPORTED;
}

capi_v2_err_t afe_cdc_register_read(capi_v2_cdc_handle cdc_dev_handle, uint32_t reg_addr,\
                                           uint8_t* read_value_ptr, uint32_t reg_bit_width)
{
  MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "AFE cdc register read failed, AFE cdc reg op is stubbed");

  return CAPI_V2_EUNSUPPORTED;
}

capi_v2_err_t afe_cdc_register_multi_read(capi_v2_cdc_handle cdc_dev_handle, uint32_t reg_addr, \
                                                 uint8_t* read_value_ptr, uint32_t reg_bit_width, uint32_t no_of_regs_to_read)
{
  MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "AFE cdc register multi read failed, AFE cdc reg op is stubbed");

  return CAPI_V2_EUNSUPPORTED;
}

capi_v2_err_t afe_cdc_register_write(capi_v2_cdc_handle cdc_dev_handle, uint32_t reg_addr, uint8_t* write_value_ptr,\
                                            uint32_t reg_field_bit_mask, uint32_t reg_bit_width,\
                                            bool_t is_blocking)
{
  MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "AFE cdc register write failed, AFE cdc reg op is stubbed");

  return CAPI_V2_EUNSUPPORTED;
}

capi_v2_err_t afe_cdc_register_update(capi_v2_cdc_handle cdc_dev_handle, uint32_t reg_addr, uint8_t* write_value_ptr,\
                                             uint32_t reg_field_bit_mask,  uint32_t reg_bit_width, \
                                             bool_t is_blocking)
{
  MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "AFE cdc register update failed, AFE cdc reg op is stubbed");

  return CAPI_V2_EUNSUPPORTED;
}
