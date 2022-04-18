#ifndef HAL_AONINT_H
#define HAL_AONINT_H
/*
===========================================================================

FILE:         HALgpiointInternal.h

DESCRIPTION:  
  This is the hardware abstraction layer internal interface for the always
  on interrupt controller block.

===========================================================================

                             Edit History

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/hal/aonint/inc/HALaonint.h#1 $

when       who     what, where, why
--------   ---     --------------------------------------------------------
09/29/14   cpaulo  Added retention enter and exit APIs.
08/20/14   cpaulo  Created.

===========================================================================
             Copyright (c) 2014 QUALCOMM Technologies Incorporated.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
===========================================================================
*/

#ifdef __cplusplus
extern "C" {
#endif


/* -----------------------------------------------------------------------
**                           INCLUDES
** ----------------------------------------------------------------------- */

#include <HALcomdef.h>


/* -----------------------------------------------------------------------
**                          DEFINES
** ----------------------------------------------------------------------- */

#define HAL_AONINT_NUM_REGS 5

/* -----------------------------------------------------------------------
**                           TYPES
** ----------------------------------------------------------------------- */

typedef enum
{
  HAL_AONINT_TRIGGER_DEFAULT  = 0,
  HAL_AONINT_TRIGGER_HIGH     = 1,
  HAL_AONINT_TRIGGER_LOW      = 2,
  HAL_AONINT_TRIGGER_RISING   = 3,
  HAL_AONINT_TRIGGER_FALLING  = 4,
  HAL_AONINT_TRIGGER_DUAL_EDGE = 5
} HAL_aonint_TriggerType;

/*
 * HAL_aonint_PlatformInfo
 * Platform info for AONINT
 *
 * nClearRegs:          Address of aonint clear reg.
 * nEnableRegs:         Address of aonint enable reg.
 * nPolarityRegs:       Address of aonint polarity reg.
 * nPositiveEdgeRegs:   Address of aonint positive edge enable reg.
 * nNegativeEdgeRegs:   Address of aonint negative edge enable reg.
 * nStatusRegs:         Address of status register.
 */
typedef struct
{
  uint32 nClearRegs[HAL_AONINT_NUM_REGS];
  uint32 nEnableRegs[HAL_AONINT_NUM_REGS];
  uint32 nPolarityRegs[HAL_AONINT_NUM_REGS];
  uint32 nPositiveEdgeRegs[HAL_AONINT_NUM_REGS];
  uint32 nNegativeEdgeRegs[HAL_AONINT_NUM_REGS];
  uint32 nStatusRegs[HAL_AONINT_NUM_REGS];
} HAL_aonint_PlatformInfo;


/* -----------------------------------------------------------------------
**                           FUNCTIONS
** ----------------------------------------------------------------------- */

void HAL_aonint_Init ( void );
void HAL_aonint_PlatformInitEarly ( HAL_aonint_PlatformInfo *pmPlatform );
void HAL_aonint_Enable ( uint32 nAonIdx );
void HAL_aonint_Disable ( uint32 nAonIdx );
void HAL_aonint_Config ( uint32 nAonIdx, HAL_aonint_TriggerType eTrigger );
void HAL_aonint_Clear ( uint32 nAonIdx );
HAL_aonint_TriggerType HAL_aonint_Get_Config ( uint32 nAonIdx );
boolean HAL_aonint_Status ( uint32 nAonIdx );

void HAL_aonint_RetentionEnter ( void );
void HAL_aonint_RetentionExit ( void );

/* 
===============================================================================
  INTERFACES DOCUMENTATION
===============================================================================

HAL_aonint_Init ( void )

Description:
   This function initializes configuration for always on interrupt.

Parameters:
   None.

===============================================================================

HAL_aonint_PlatformInitEarly ( HAL_aonint_PlatformInfo *pmPlatform )

Description:
   This function populates platform specific always on interrupt info.

Parameters:
   pmPlatform - Pointer to the platform information structure to populate.

===============================================================================

HAL_aonint_Enable ( uint32 nAonIdx )

Description:
   This function is invoked when enabling an always on interrupt.

Parameters:
   nAonIdx - Always on index, associated with mapping in PMU.

===============================================================================

HAL_aonint_Disable ( uint32 nAonIdx )

Description:
   This function is invoked when disabling an always on interrupt.

Parameters:
   nAonIdx -  Always on index, associated with mapping in PMU.
 
===============================================================================

HAL_aonint_Config ( uint32 nAonIdx, HAL_aonint_TriggerType eTrigger )

Description:
   This function is used to configure the interrupt trigger in the PMU.

Parameters:
   nAonIdx  -  Always on index, associated with mapping in PMU.
   eTrigger -  Type of trigger to configure at the PMU.

===============================================================================

HAL_aonint_Clear ( uint32 nAonIdx )

Description:
   This function is used to clear the interrupt source at the PMU.

Parameters:
   nAonIdx -  Always on index, associated with mapping in PMU.

===============================================================================

HAL_aonint_Get_Config ( uint32 nAonIdx )

Description:
   This function is used to get the currently configured interrupt trigger.

Parameters:
   nAonIdx -  Always on index, associated with mapping in PMU.

===============================================================================
 
HAL_aonint_RetentionEnter ( void )

Description:
   This function is used to write the associated registers to
   enter retention mode.

Parameters:
   None.

===============================================================================
 
HAL_aonint_RetentionExit ( void )

Description:
   This function is used to write the associated registers to
   leave retention mode.

Parameters:
   None.

===============================================================================
*/ 


#ifdef __cplusplus
}
#endif

#endif /* HAL_AONINT_H */
