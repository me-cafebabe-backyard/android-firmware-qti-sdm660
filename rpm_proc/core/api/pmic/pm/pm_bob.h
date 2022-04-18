#ifndef __PM_BOB_H__
#define __PM_BOB_H__

/*! \file pm_bob.h
 *  \n
 *  \brief This header file contains enums and API definitions for PMIC BOB
 *         power rail driver.
 *  \n
 *  \n &copy; Copyright 2016 QUALCOMM Technologies Incorporated, All Rights Reserved
 */
/* ======================================================================= */

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

  $Header: //components/rel/rpm.bf/1.8/core/api/pmic/pm/pm_bob.h#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
12/22/15   al      Created
=============================================================================*/

/*===========================================================================

                 HEADER FILE INCLUDE

===========================================================================*/
#include "pm_err_flags.h"
#include "pm_resources_and_types.h"
#include "com_dtypes.h"

/*===========================================================================

                        TYPE DEFINITIONS 

===========================================================================*/

/*!
 *  \brief 
 *  BOB peripheral index. This enum type contains all bob regulators that you may need. 
 */

enum
{
  PM_BOB_1,
  PM_BOB_INVALID
};

enum
{
  PM_BOB_EXT_PIN_RESERVED = 0,
  PM_BOB_EXT_PIN_CTRL1 = 1,
  PM_BOB_EXT_PIN_CTRL2 = 2,
  PM_BOB_EXT_PIN_CTRL3 = 3,
  PM_BOB_EXT_PIN_MAX,
};

typedef enum
{
  PM_BOB_MODE_PASS,
  PM_BOB_MODE_PFM,
  PM_BOB_MODE_AUTO,
  PM_BOB_MODE_PWM,
  PM_BOB_MODE_INVALID,
}pm_bob_mode_type; 

/*===========================================================================

                        API PROTOTYPE

===========================================================================*/


#endif /* __PM_BOB_H__ */

