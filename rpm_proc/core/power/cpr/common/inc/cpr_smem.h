/**
 * @file:  cpr_smem.h
 * @brief:
 *
 * Copyright (c) 2015-2016 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * QUALCOMM Proprietary and Confidential.
 *
 * $DateTime: 2016/11/03 00:13:13 $
 * $Header: //components/rel/rpm.bf/1.8/core/power/cpr/common/inc/cpr_smem.h#1 $
 * $Change: 11690628 $
 */
#ifndef CPR_SMEM_H
#define CPR_SMEM_H

#include "cpr_cfg.h"
#include "cpr_data.h"

void cpr_smem_deserialize_config(cpr_rail* rail, cpr_rail_state* state);
void cpr_smem_serialize_config(cpr_rail_state* state, boolean append);

#endif
