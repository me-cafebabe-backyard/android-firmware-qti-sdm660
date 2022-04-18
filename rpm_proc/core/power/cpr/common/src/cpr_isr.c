/**
 * @file:  cpr_isr.c
 *
 * Copyright (c) 2015-2016 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * QUALCOMM Proprietary and Confidential.
 *
 * $DateTime: 2016/11/03 00:13:13 $
 * $Header: //components/rel/rpm.bf/1.8/core/power/cpr/common/src/cpr_isr.c#1 $
 * $Change: 11690628 $
 */
#include "cpr_cfg.h"
#include "cpr_utils.h"
#include "cpr_rail.h"

uint32 cpr_isr_get_interrupt(cpr_domain_id railId)
{
    cpr_rail* rail = cpr_utils_get_rail( railId );
    return rail->interruptId;
}

void cpr_isr_process(cpr_domain_id railId)
{
    cpr_rail* rail = cpr_utils_get_rail( railId );
    cpr_rail_isr( rail );
}
