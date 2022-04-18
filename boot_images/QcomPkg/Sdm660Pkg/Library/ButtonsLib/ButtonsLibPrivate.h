#ifndef __BUTTONSLIBPRIVATE_H__
#define __BUTTONSLIBPRIVATE_H__

/** @file
ButtonsLibPrivate.h

  Buttons library internal defines

  Copyright (c) 2012-2016 Qualcomm Technologies, Inc. All rights reserved.
  Qualcomm Technologies Proprietary and Confidential.

**/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ----------------------------------------------------------
02/04/16   ma      Port to Sdm660
===========================================================================*/

#include <Protocol/EFIPlatformInfo.h>
#include <Protocol/SimpleTextInEx.h>
#include <Protocol/EFIPmicGpio.h>
#include <Protocol/EFIPmicPwrOn.h>

//GPIO Numbers
#define VOLUME_UP_BUTTON_GPIO            7
#define HOME_BUTTON_GPIO                 11  // Need to udate based on CDP schematic
//#define CAMERA_SNAPSHOT_BUTTON_GPIO      7  //-> CAMERA Button moved to MSM for SDM660


#endif /* __BUTTONSLIBPRIVATE_H__ */
