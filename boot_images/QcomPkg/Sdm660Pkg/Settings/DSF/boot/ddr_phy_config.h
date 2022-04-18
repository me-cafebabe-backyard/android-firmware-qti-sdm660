#ifndef __DDR_PHY_CONFIG_H__
#define __DDR_PHY_CONFIG_H__


/*==============================================================================
                      Warning: This file is auto-generated
================================================================================
                   Copyright (c) 2015 Qualcomm Technologies Incorporated
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
extern uint32 (*ddr_phy_dq_config_base)[2];
extern uint32 (*ddr_phy_ca_config_base)[2];
extern uint32 (*ddr_cc_config_base)[2];

extern uint32 (*ddr_phy_dq_lp4x_config_base)[2];
extern uint32 (*ddr_phy_dq_starlord_config_base)[2];
extern uint32 (*ddr_phy_ca_lp4x_config_base)[2];
extern uint32 (*ddr_phy_ca_starlord_config_base)[2];

/*==============================================================================
                                  FUNCTIONS
==============================================================================*/
void ddr_phy_dq_set_config
(
  DDR_STRUCT *ddr,
  uint32 offset,
  uint32 (*ddr_phy_dq_config_base)[2], uint32 (*ddr_phy_dq_lp4x_config_base)[2], uint32 (*ddr_phy_dq_starlord_config_base)[2]
);

void ddr_phy_ca_set_config
(
  DDR_STRUCT *ddr,
  uint32 offset,
  uint32 (*ddr_phy_ca_config_base)[2], uint32 (*ddr_phy_ca_lp4x_config_base)[2], uint32 (*ddr_phy_ca_starlord_config_base)[2]
);

void ddr_cc_set_config
(
  DDR_STRUCT *ddr,
  uint32 offset,
  uint32 (*ddr_cc_config_base)[2]//, uint32 (*ddr_cc_config_lpddr4x)[2]
);


#endif
