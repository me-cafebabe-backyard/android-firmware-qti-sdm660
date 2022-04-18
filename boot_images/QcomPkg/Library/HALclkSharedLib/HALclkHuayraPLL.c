/*
==============================================================================

FILE:         HALclkHuayraPLL.c

DESCRIPTION:
  This file contains the clock HAL code for the Huayra PLL control.
  These PLLs are of the Huayra PLL variety.

==============================================================================

                             Edit History

$Header: //components/rel/boot.xf/1.4/QcomPkg/Library/HALclkSharedLib/HALclkHuayraPLL.c#2 $

when       who     what, where, why
--------   ---     -----------------------------------------------------------
06/07/14   sr      Created

==============================================================================
    Copyright (c) 2014-2015 QUALCOMM Technologies Incorporated.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
==============================================================================
*/

/*============================================================================

                     INCLUDE FILES FOR MODULE

============================================================================*/

#include "HALclkHuayraPLL.h"

/* ============================================================================
**    Data Declarations
** ==========================================================================*/

/*
 * HAL_clk_HuayraPLLControl
 *
 * Control function array for the Huayra PLLs.
 */
HAL_clk_SourceControlType HAL_clk_HuayraPLLControl =
{
  /* .Enable          = */ HAL_clk_HuayraPLLEnable,
  /* .Disable         = */ HAL_clk_HuayraPLLDisable,
  /* .IsEnabled       = */ HAL_clk_HuayraPLLIsEnabled,
  /* .Config          = */ HAL_clk_HuayraPLLConfig,
  /* .ConfigPLL       = */ HAL_clk_HuayraPLLConfigPLL,
  /* .DetectPLLConfig = */ HAL_clk_HuayraPLLDetectPLLConfig,
  /* .EnableVote      = */ NULL,
  /* .DisableVote     = */ NULL,
  /* .IsVoteEnabled   = */ NULL,
};

/*
 * Include common implemenation.
 */
#include "HALclkHuayraPLLTemplate.c"

