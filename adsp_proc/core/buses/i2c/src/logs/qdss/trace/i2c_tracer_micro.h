/*
===========================================================================

FILE:   i2c_tracer_micro.h

DESCRIPTION:
    This file contains a wrapper to QDSS software event calls.


===========================================================================

        Edit History

$Header: //components/rel/core.qdsp6/1.0.c2/buses/i2c/src/logs/qdss/trace/i2c_tracer_micro.h#1 $

When     Who    What, where, why
-------- ---    -----------------------------------------------------------
04/13/15 NP     Created

===========================================================================
        Copyright c 2015 Qualcomm Technologies Incorporated.
            All Rights Reserved.
            Qualcomm Proprietary/GTDR

===========================================================================
*/
#include "tracer_micro.h"
#include "I2CSWEventId.h"

#define I2C_UTRACER_EVENT(event, args...) \
   UTRACER_EVENT(event, ##args);