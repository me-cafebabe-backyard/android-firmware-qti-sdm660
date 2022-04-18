/*============================================================================

FILE:      err.h

DESCRIPTION: Function declarations

PUBLIC CLASSES:  Not Applicable

INITIALIZATION AND SEQUENCING REQUIREMENTS:  N/A

      Copyright (c) 2010 Qualcomm Technologies Incorporated.
               All Rights Reserved.
         QUALCOMM Proprietary and Confidential

$Header: //components/rel/rpm.bf/1.8/core/bsp/rpm/inc/err.h#1 $
$Date: 2016/11/03 $

============================================================================*/

#ifndef ERR_H
#define ERR_H

#include <stdint.h>
#include <stdlib.h>
#include "comdef.h" 

// This is the macro that most erroring people should call.
#define ERR_FATAL(string, a, b, c) { abort(); }

// Initializes the error handling system.
void err_init(void);

#endif /* ERR_H */

