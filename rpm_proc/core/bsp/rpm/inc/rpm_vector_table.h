/*============================================================================

FILE:      rpm_vector_table.h

DESCRIPTION: RPM vector table for exceptions and interrupts

PUBLIC CLASSES:  Not Applicable

INITIALIZATION AND SEQUENCING REQUIREMENTS:  N/A

      Copyright (c) 2015 Qualcomm Technologies, Inc.
               All Rights Reserved.
         QUALCOMM Proprietary and Confidential

$Header: //components/rel/rpm.bf/1.8/core/bsp/rpm/inc/rpm_vector_table.h#2 $
$Date: 2017/03/15 $

============================================================================*/
#ifndef RPM_VECTOR_TABLE_H
#define RPM_VECTOR_TABLE_H

#ifdef __clang__
#include "llvm_compat.h"
#endif
#define NUM_EXCEPTIONS      16
#define INTERRUPT_OFFSET    NUM_EXCEPTIONS
#define NUM_INTERRUPTS      64

#define WATCHDOG_IRQ_NUM    49

typedef void (*ExecFuncPtr)(void) __irq;

extern ExecFuncPtr vector_table[NUM_EXCEPTIONS+NUM_INTERRUPTS];

#endif /* RPM_VECTOR_TABLE_H */
