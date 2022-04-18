/*==============================================================================

  D A L   G P I O   M A N A G E R

DESCRIPTION
  This file has the direct connect GPIO interrupt mapping required for
  this target.

REFERENCES

    Copyright (c) 2016 Qualcomm Technologies Incorporated.
               All Rights Reserved.
            QUALCOMM Proprietary/GTDR
===========================================================================*/

/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/GPIOMgr/config/sdm660/adsp_slpi/GPIOMgrConfigData.c#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
08/26/16   shm     First version for SDM660
===========================================================================*/

#include "com_dtypes.h"
#include "DDIGPIOMgr.h"
#include "GPIOMgr.h"

GPIOMgrConfigMapType GPIOMgrConfigMap[] =
{
  {0, 24, GPIOMGR_FLAG_RESERVED, 1 }, /* LPASS direct connect 0 */
  {1, 25, GPIOMGR_FLAG_RESERVED, 1 }, /* LPASS direct connect 1 */
  {2, 26, GPIOMGR_UNUSED_GPIO,   0 }, /* LPASS direct connect 2 */
  {3, 27, GPIOMGR_UNUSED_GPIO,   0 }, /* LPASS direct connect 3 */
  {4, 28, GPIOMGR_UNUSED_GPIO,   1 }, /* LPASS direct connect 4 */
  {5, 29, GPIOMGR_UNUSED_GPIO,   1 }, /* LPASS direct connect 5 */
  {6, 70, GPIOMGR_UNUSED_GPIO,   2 }, /* Sensor direct connect 0 */
  {7, 71, GPIOMGR_UNUSED_GPIO,   2 }, /* Sensor direct connect 2 */
  {0, 0, 0, 0 }, /* End */
};

GPIOMgrConfigPDType GPIOMgrConfigPD[] =
{
  {0, GPIOMGR_DEVICE_LPA_DSP },
  {1, GPIOMGR_DEVICE_LPA_DSP },
  {2, GPIOMGR_DEVICE_SPS     },
  {0, GPIOMGR_DEVICE_NONE    }
};
