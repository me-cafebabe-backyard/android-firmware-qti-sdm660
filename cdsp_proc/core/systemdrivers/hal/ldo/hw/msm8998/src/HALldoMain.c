/*
==============================================================================

FILE:         HALldoMain.c

DESCRIPTION:
  This file contains the main platform initialization code for the VCS
  HAL.

==============================================================================

                             Edit History

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/hal/ldo/hw/msm8998/src/HALldoMain.c#1 $

when       who     what, where, why
--------   ---     -----------------------------------------------------------
11/10/14   dcf     Created.

==============================================================================
            Copyright (c) 2014 Qualcomm Technologies Incorporated.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
==============================================================================
*/

/*============================================================================

                     INCLUDE FILES FOR MODULE

============================================================================*/


#include "HALldoInternal.h"
#include "HALhwio.h"
#include "HALldoHWIO.h"


/* ============================================================================
**    Externs
** ==========================================================================*/


extern void HAL_ldo_PlatformInitQ6(void);


/* ============================================================================
**    Prototypes
** ==========================================================================*/


/* ============================================================================
**    Data
** ==========================================================================*/


/*
 * HAL_ldo_aInitFuncs
 *
 * Declare array of module initialization functions.
 */
static HAL_ldo_InitFuncType HAL_ldo_afInitFuncs[] =
{
  /*
   * LPASS
   */
  HAL_ldo_PlatformInitQ6,
  
  NULL
};


/*
 * Declare the base pointers for HWIO access.
 */
uint32 HAL_ldo_nHWIOBaseLPASS;


/*
 * HAL_ldo_aHWIOBases
 *
 * Declare array of HWIO bases in use on this platform.
 */
static HAL_ldo_HWIOBaseType HAL_ldo_aHWIOBases[] =
{
  { LPASS_BASE_PHYS, LPASS_BASE_SIZE, &HAL_ldo_nHWIOBaseLPASS },
  { 0, 0, NULL }
};


/*
 * HAL_ldo_Platform;
 * Platform data.
 */
HAL_ldo_PlatformType HAL_ldo_Platform =
{
  HAL_ldo_afInitFuncs,
  HAL_ldo_aHWIOBases
};

