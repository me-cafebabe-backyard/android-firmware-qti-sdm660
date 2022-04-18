#ifndef __DDR_AUTOMODE_H__
#define __DDR_AUTOMODE_H__

/*=============================================================================

                                   DDR AUTOMODE
                            Header File
GENERAL DESCRIPTION
This is the target header file for DDR AUTOMODE

Copyright 2014 by Qualcomm Technologies, Inc.  All Rights Reserved.

===========================================================================

                            EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  $Header: //components/rel/rpm.bf/1.8/core/boot/ddr/hw/sdm660/ddr_automode.h#1 $

when       who     what, where, why
--------   ---     ------------------------------------------------------------
06/10/14   tw      Initial revision.
=============================================================================*/
/*==============================================================================
                                  INCLUDES
==============================================================================*/
#include "ddr_common.h"
#include "HALhwio.h"


/*==============================================================================
                                  MACROS
==============================================================================*/

/*==============================================================================
                                  DATA
==============================================================================*/
typedef struct 
{
  uint32 freq;
  uint32 pmic_enum;
}ddr_automode;

/* -----------------------------------------------------------------------
**                           FUNCTIONS
** ----------------------------------------------------------------------- */

/* =============================================================================
**  Function : ddr_automode_init
** =============================================================================
*/
/**
*   @brief
*   Function called to initialize automode settings
*
*   @param[in]  None
*
*   @retval  None
*
*   @dependencies
*   None
*
*   @sideeffects
*   None
*
*   @sa
*   None
*/
void ddr_automode_init(void);

/* =============================================================================
**  Function : ddr_automode_toggle
** =============================================================================
*/
/**
*   @brief
*   Function called to update automode settings
*
*   @param[in]  clk_speed_in_khz  Current clock speed (in KHz)
*
*   @retval  None
*
*   @dependencies
*   None
*
*   @sideeffects
*   None
*
*   @sa
*   None
*/
void ddr_automode_toggle(uint32 clk_speed_in_khz);
#endif /* __DDR_AUTOMODE_H__ */
