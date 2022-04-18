/*========================================================================
   This file contains functions to set the parameters for different modules.

Copyright (c) 2017 QUALCOMM Technologies, Inc.  All Rights Reserved.
QUALCOMM Technologies, Inc Proprietary.  Export of this technology or software is regulated
  by the U.S. Government, Diversion contrary to U.S. law prohibited.

  $Header: //components/rel/avs.adsp/2.8/afe/drivers/afe/codec_reg_op/inc/AFECdcRegOp.h#1 $
 ====================================================================== */
#ifndef _AFE_CDC_REG_OP_H_
#define _AFE_CDC_REG_OP_H_

/*==========================================================================
  Include Files
========================================================================== */
#include "AFECodecService.h"
#include "AFESlimbusDriver.h"
#include "Elite_fwk_extns_codec_reg_op.h"

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus


  /**
  Registers with codec device.

  To do any codec register operation, it is mandatory that module should have registered with
  codec device. During registration, Elite framework opens the codec device, and returns the
  codec device handle.

  @param[in] none

  @return
  On success returns non-NULL handle.
  On failure, returns NULL handle.
  */
capi_v2_cdc_handle afe_cdc_reg_access_registration(void);

/**
De-registers with codec device.

To avoid latency, it is recommended not to de-register and register for every operation,
de-register, if there are no more register operations.

If module registered with codec device, then de-registration is mandatory.

@param[in] capi_v2_cdc_handle      A valid codec device handle, which returned as part of registration.

@return
Indication of success or failure.
*/
capi_v2_err_t afe_cdc_reg_access_deregistration(capi_v2_cdc_handle cdc_dev_handle);

/**
Reads single codec register.

Elite framework reads whole register and stores that value in read_value_ptr. Module need to apply
masking and shifting operation on top of the read value based on register_field_bit_mask to get actual
value. Module need to allocate enough memory for read_value_ptr to hold whole read value based on
register bit width to avoid corruption.

@param[in] capi_v2_cdc_handle      A valid codec device handle, which returned as part of registration.
@param[in] reg_addr                reg_addr is the logical address of the Codec register.
@param[in] read_value_ptr          read_value_ptr is a pointer to value read from codec register.
@param[in] reg_bit_width           reg_bit_width is the width of the register to be read from, in bits.
                                   Possible values are 8, 16 and 32.
@return
Indication of success or failure.
*/
capi_v2_err_t afe_cdc_register_read(capi_v2_cdc_handle cdc_dev_handle, uint32_t reg_addr,\
                                           uint8_t* read_value_ptr, uint32_t reg_bit_width);

/**
Reads multiple contiguous registers.

Elite framework reads contiguous registers and stores the value of those registers in
read_value_ptr. read_value_ptr should be pointer to an array of read values to be stored
from registers. Module need to apply masking and shifting operations on top of each
read value to get actual data. Module should allocate enough memory for read_value_ptr
to hold whole read values to avoid corruption.

For non-contiguous register reads, module needs to use cdc_register_read sequentially.

@param[in] capi_v2_cdc_handle       A valid codec device handle, which returned as part of registration.
@param[in] reg_addr                 reg_addr is the logical address of the first Codec register.
@param[in] read_value_ptr           read_value_ptr is a pointer to value read from codec register.
@param[in] reg_bit_width            reg_bit_width is the width of the register to be read from, in bits.
                                    Possible values are 8, 16 and 32.
@param[in] no_of_regs_to_read       no_of_regs_to_read is the number of contiguous registers to read.

@return
Indication of success or failure.
*/
capi_v2_err_t afe_cdc_register_multi_read(capi_v2_cdc_handle cdc_dev_handle, uint32_t reg_addr, uint8_t* read_value_ptr,\
                                                 uint32_t reg_bit_width, uint32_t no_of_regs_to_read);
/**
Writes single codec register.

Contents of the register overwritten with the written value, based on reg_field_bit_mask.

@param[in] capi_v2_cdc_handle         A valid codec device handle, which returned as part of registration.
@param[in] reg_addr                   The logical address of the Codec register.
@param[in] write_value_ptr            write_value_ptr is pointer to value to be written to the Codec register.
@param[in] reg_field_bit_mask         A valid bit field mask
@param[in] reg_bit_width              reg_bit_width is the width of the register to be written to, in bits.
                                      Possible values are 8, 16 and 32.
@param[in] is_blocking                Indicates if write should be blocking.
                                      Possible values are TRUE and FALSE.
                                      If is_blocking is TRUE, then execution will only be returned only after
                                      completing the write request. If in case, module needs to write multiple
                                      registers sequentially, then set is_blocking = TRUE, only for the last
                                      register write, by this latency can be reduced.
@return
Indication of success or failure.
*/
capi_v2_err_t afe_cdc_register_write(capi_v2_cdc_handle cdc_dev_handle, uint32_t reg_addr, uint8_t* write_value_ptr,\
                                            uint32_t reg_field_bit_mask, uint32_t reg_bit_width,\
                                            bool_t is_blocking);
/**
Updates single codec register.

Reads existing value in the register, clear outs the bits indicated in reg_field_bit_mask and ORs this value with
value to be written. Content of the bits not related to the reg_field_bit_mask were retained.

@param[in] capi_v2_cdc_handle         A valid codec device handle, which returned as part of registration.
@param[in] reg_addr                   The logical address of the Codec register.
@param[in] write_value_ptr            write_value_ptr is pointer to value to be written to the Codec register.
@param[in] reg_field_bit_mask         A valid bit field mask
@param[in] reg_bit_width              reg_bit_width is the width of the register to be written to, in bits.
                                      Possible values are 8, 16 and 32.
@param[in] is_blocking                Indicates if update should be blocking. Possible values are TRUE and FALSE.
                                      If is_blocking is TRUE, then execution will only be returned only after
                                      completing the requested codec register update. If in case, module needs
                                      to update multiple registers sequentially, then set is_blocking = TRUE,
                                      only for the last register update, by this latency can be reduced.

@return
Indication of success or failure.
*/
capi_v2_err_t afe_cdc_register_update(capi_v2_cdc_handle cdc_dev_handle, uint32_t reg_addr, uint8_t* write_value_ptr,\
                                             uint32_t reg_field_bit_mask,  uint32_t reg_bit_width, \
                                             bool_t is_blocking);

/*==========================================================================
  Globals
========================================================================== */

#ifdef __cplusplus
}
#endif //__cplusplus

#endif // _AFE_CDC_REG_OP_H_
