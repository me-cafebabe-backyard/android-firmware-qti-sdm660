#ifndef __MCCC_CONFIG_H__
#define __MCCC_CONFIG_H__


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
#include "mccc.h"


/*==============================================================================
                                  DATA
==============================================================================*/
extern uint32 (*mccc_regs_config_base)[2];
extern uint32 (*mccc_ch_regs_config_base)[2];

extern uint32 (*mccc_regs_config_ch_delta)[2];
extern uint32 (*mccc_ch_regs_config_ch_delta)[2];

extern uint32 (*mccc_regs_config_delta)[2];
extern uint32 (*mccc_ch_regs_config_delta)[2];

/*==============================================================================
                                  FUNCTIONS
==============================================================================*/
void mccc_set_config
(
  DDR_STRUCT *ddr,
  uint32 offset,
  uint32 (*mccc_config_base)[2], uint32 (*mccc_config_ch_delta)[2], uint32 (*mccc_config_delta)[2]
);


#endif
