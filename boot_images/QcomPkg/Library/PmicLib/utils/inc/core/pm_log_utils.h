#ifndef __PM_LOG_UTILS_H__
#define __PM_LOG_UTILS_H__

/*! \file
 *  
 *  \brief  pm_log_utils.h ----This file contain PMIC wrapper function of DALSYS_Malloc()
 *  \details his file contain PMIC wrapper function of DALSYS_Malloc()
 *  
 *    &copy; Copyright 2012-2016 Qualcomm Technologies Incorporated, All Rights Reserved
 */

/*===========================================================================

                EDIT HISTORY FOR MODULE

  This document is created by a code generator, therefore this section will
  not contain comments describing changes made to the module over time.


when       who     what, where, why
--------   ---     ----------------------------------------------------------
08/05/16   aab     Created

===========================================================================*/

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>

#include "pm_uefi.h"

#define pm_log_message(...)   DEBUG((EFI_D_ERROR,__VA_ARGS__))

/*===========================================================================

                        FUNCTION PROTOTYPES

===========================================================================*/


#endif // __PM_LOG_UTILS_H__
