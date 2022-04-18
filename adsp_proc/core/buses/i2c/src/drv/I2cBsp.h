#ifndef _I2CBSP_H_
#define _I2CBSP_H_
/*=============================================================================

  @file   I2cBsp.h

   This file contains the types for the platform services.
 
Copyright (c) 2014-2016 Qualcomm Technologies, Incorporated.
                  All rights reserved.
Qualcomm Technologies, Confidential and Proprietary.
===========================================================================*/
/*=============================================================================
                    EDIT HISTORY FOR MODULE
$Header: //components/rel/core.qdsp6/1.0.c2/buses/i2c/src/drv/I2cBsp.h#1 $ 

When     Who    What, where, why
-------- ---    -----------------------------------------------------------
10/17/16 VG     Updated the Copy Rights
04/08/16 VG     Added binary compatibility changes
=============================================================================*/

/*-------------------------------------------------------------------------
 * Include Files
 * ----------------------------------------------------------------------*/

#include "I2cTypes.h"
#include "I2cDriverTypes.h"

/*-------------------------------------------------------------------------
 * Externalized Function Definitions
 * ----------------------------------------------------------------------*/

void I2cBsp_Init(void);
void I2cBsp_DeInit(void);


#endif /* _I2CBSP_H_ */

