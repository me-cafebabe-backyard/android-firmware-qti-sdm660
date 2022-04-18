/*==============================================================================
@file  DALModEnv_userpd.c

Initialization functions on user PD

        Copyright © 2013,2105 Qualcomm Technologies Inc.
        All Rights Reserved.
        Qualcomm Confidential and Proprietary

                      EDIT HISTORY FOR FILE
                      
  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.
  
 when       who     what, where, why
 --------   ---     ---------------------------------------------------------
 1/4/15   ap        Change supporting multi-config in audio pd. Call Devcfg_init()

=============================================================================
                           INCLUDE FILES
=============================================================================*/
#include "DALSys.h"
#include "DALStdDef.h"
#include "DALStdErr.h"
#include "DALSysCmn.h"
#include "DALQdiDefs.h"

extern void DevCfg_Init(void);

/*=============================================================================
                    DEFINITIONS AND DECLARATIONS
=============================================================================*/
void
_DALSYS_InitMod(DALSYSConfig *pCfg)
{
#if !defined LPASS_SENSOR_IMG
   DevCfg_Init();
   // does nothing
#endif   
}
