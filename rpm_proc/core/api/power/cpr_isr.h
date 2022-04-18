/**
 * @file:  cpr_isr.h
 * @brief:
 *
 * Copyright (c) 2015 by Qualcomm Technologies Incorporated. All Rights Reserved.
 *
 * $DateTime: 2016/11/03 00:13:13 $
 * $Header: //components/rel/rpm.bf/1.8/core/api/power/cpr_isr.h#1 $
 * $Change: 11690628 $
 */
#ifndef CPR_ISR_H
#define	CPR_ISR_H

#include "cpr_defs.h"

/**
 * Gets the CPR interrupt number for the given rail
 */
uint32 cpr_isr_get_interrupt(cpr_rail_id_t railId);

/**
 * Runs the CPR ISR for the given rail.
 */
void cpr_isr_process(cpr_rail_id_t railId);

#endif

