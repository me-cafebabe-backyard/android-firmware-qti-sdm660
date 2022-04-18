/*
===========================================================================

FILE:         BSPmpm.c

DESCRIPTION:
  This is the platform hardware abstraction layer implementation for the
  MPM hardware block.
  This platform is for the RPM on the 8998.

===========================================================================

                             Edit History

$Header: //components/rel/rpm.bf/1.8/core/power/mpm/hal/bsp/source/660/BSPmpm.c#1 $

when       who     what, where, why
--------   ---     --------------------------------------------------------

===========================================================================
             Copyright (c) 2015 Qualcomm Technologies, Inc.
                    All Rights Reserved.
              QUALCOMM Proprietary and Confidential
===========================================================================
*/

/* -----------------------------------------------------------------------
**                           INCLUDES
** ----------------------------------------------------------------------- */

#include <stdint.h>
#include "BSPmpm.h"

/* -----------------------------------------------------------------------
**                           TYPES
** ----------------------------------------------------------------------- */

/* -----------------------------------------------------------------------
**                           DATA
** ----------------------------------------------------------------------- */

/*
 * TODO: update delays when PMIC driver is ready
 */
/* wakeup delays for CXO warm-up in 32kHz ticks */
/* Need to be >= 500 usec for PM8994 (CR 701462)*/
static const uint32_t cxoDelay = 0x11; /* 531 usec to be safe */

/* target backoff for deep sleep exit in 19.2Mhz ticks */
/*                                        VDD min   */
static const uint32_t deepSleepExitDelay = 3578;

/*
 * Target specific MPM Hardware configuration.
 */
BSP_mpm_ConfigDataType MPM_BSP_DATA =
{
  /* MPM Configuration */
  {
    /* Wakeup Delays */
    {
      cxoDelay, deepSleepExitDelay
    },

    /* IO Cfg */
    {
      /* Freeze  Clamp  SW Ebi1     Warm Boot    Warm Boot    VREF_PWRSAVE
       * IOs     IOs    Ctl Enable  Freeze EBI1  Freeze EBI2                   */
      TRUE,      TRUE,   TRUE,       TRUE,        TRUE,       TRUE
    },

    /* Debug Through Power Collapse */
    FALSE,

    /* Debug Bus Enable (bit 0)     Debug Bus Enable (bit 1) */
    FALSE,                          FALSE,
  },

  /* Peripherals Configuration */
  {
    /* Pen Debounce Cfg */
    {
      /* Enable */
      FALSE,

      /* Delay */
      HAL_MPM_PEN_DEBOUNCE_DELAY_0400US
    },
  },

  /* Voltage Rail Configuration */
  {
    1500, //step size: 1.5mV/uS
  }

}; /* End BSP_mpm_ConfigData */

