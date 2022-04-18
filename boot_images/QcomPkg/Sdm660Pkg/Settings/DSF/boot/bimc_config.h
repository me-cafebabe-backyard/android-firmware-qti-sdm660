#ifndef __BIMC_CONFIG_H__
#define __BIMC_CONFIG_H__


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
extern uint32 (*bimc_global0_config_base)[2];
extern uint32 (*bimc_scmo_config_base)[2];
extern uint32 (*bimc_dpe_config_base)[2] ;
extern uint32 (*bimc_shke_config_base)[2];
extern uint32 (*bimc_dtts_config_base)[2];

extern uint32 (*bimc_global0_config_ch_delta)[2];
extern uint32 (*bimc_scmo_config_ch_delta)[2];
extern uint32 (*bimc_dpe_config_ch_delta)[2] ;
extern uint32 (*bimc_shke_config_ch_delta)[2];
extern uint32 (*bimc_dtts_config_ch_delta)[2];

extern uint32 (*bimc_global0_config_delta)[2];
extern uint32 (*bimc_scmo_config_delta)[2];
extern uint32 (*bimc_dpe_config_delta)[2] ;
extern uint32 (*bimc_shke_config_delta)[2];
extern uint32 (*bimc_dtts_config_delta)[2];

/*==============================================================================
                                  FUNCTIONS
==============================================================================*/
void bimc_set_config
(
  DDR_STRUCT *ddr,
  uint32 offset,
  uint32 (*bimc_config_base)[2], uint32 (*bimc_config_ch_delta)[2], uint32 (*bimc_config_delta)[2]
);


#endif
