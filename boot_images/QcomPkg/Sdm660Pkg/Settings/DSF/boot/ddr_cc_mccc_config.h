#ifndef __DDR_CC_MCCC_CONFIG_H__
#define __DDR_CC_MCCC_CONFIG_H__


/*==============================================================================
                      Warning: This file is auto-generated
================================================================================
                   Copyright 2016 Qualcomm Techologies Incorporated
                              All Rights Reserved
                     Qualcomm Confidential and Proprietary
==============================================================================*/
/*==============================================================================
                                  INCLUDES
==============================================================================*/
#include "ddrss.h"
#include "ddr_common.h"


/*==============================================================================
                                  DATA
==============================================================================*/
extern uint32 (*ddr_cc_mccc_regs_config_base)[2];
extern uint32 (*ddr_cc_mccc_ch_regs_config_base)[2];

extern uint32 (*ddr_cc_mccc_regs_config_ch_delta)[2];
extern uint32 (*ddr_cc_mccc_ch_regs_config_ch_delta)[2];

extern uint32 (*ddr_cc_mccc_regs_config_delta)[2];
extern uint32 (*ddr_cc_mccc_ch_regs_config_delta)[2];

/*==============================================================================
                                  FUNCTIONS
==============================================================================*/
void ddr_cc_mccc_set_config
(
  DDR_STRUCT *ddr,
  uint32 offset,
  uint32 (*ddr_cc_mccc_config_base)[2], uint32 (*ddr_cc_mccc_config_ch_delta)[2], uint32 (*ddr_cc_mccc_config_delta)[2]
);


#endif
