#ifndef UCLOCK_H
#define UCLOCK_H
/*
===========================================================================
*/
/**
  @file uClock.h
  @brief Public definitions include file for accessing the micro image clock
         device driver.
*/
/*===========================================================================
NOTE: The @brief description and any detailed descriptions above do not appear 
      in the PDF. 

      This file is the public header file for the sensors micro image (uImage)
      clock driver implementation.  It is meant to be used by a small subset
      of drivers supporting the sensors uImage feature, which cannot access
      DDR.

===========================================================================*/
/*
  ===========================================================================

  Copyright (c) 2016 Qualcomm Technologies Incorporated.
  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ===========================================================================

  $Header: //components/rel/core.qdsp6/1.0.c2/api/systemdrivers/uClock.h#1 $
  $DateTime: 2020/02/10 01:57:30 $
  $Author: pwbldsvc $

  when       who     what, where, why
  --------   ---     ---------------------------------------------------------- 
  10/19/16   shm     Updated for SDM660.
  12/17/13   dcf     Created.

  ===========================================================================
*/


/*=========================================================================
      Include Files
==========================================================================*/

#include "com_dtypes.h"


/*=========================================================================
      Type Definitions
==========================================================================*/

/*
 * Enumeration of available clocks for the uImage clock controller.
 */
typedef enum
{
  CLOCK_SCC_QUP_I2C1_CLK,
  CLOCK_SCC_QUP_I2C2_CLK,
  CLOCK_SCC_QUP_I2C3_CLK,
  CLOCK_SCC_QUP_SPI1_CLK,
  CLOCK_SCC_QUP_SPI2_CLK,
  CLOCK_SCC_QUP_SPI3_CLK,
  CLOCK_SCC_UART_DM_UART1_CLK,
  CLOCK_SCC_UART_DM_UART2_CLK,
  CLOCK_SCC_UART_DM_UART3_CLK,
  CLOCK_SCC_UART_DM_UART4_CLK,
  CLOCK_SCC_BLSP_H_CLK,

  CLOCK_TOTAL_CLOCK_ENUMS,

} uClockIdType;

#define CLOCK_GCC_BLSP1_AHB_CLK       CLOCK_SCC_BLSP_H_CLK
#define CLOCK_GCC_BLSP2_AHB_CLK       CLOCK_SCC_BLSP_H_CLK

#define CLOCK_GCC_BLSP1_QUP1_APPS_CLK CLOCK_SCC_QUP_I2C1_CLK
#define CLOCK_GCC_BLSP2_QUP1_APPS_CLK CLOCK_SCC_QUP_I2C1_CLK

#define CLOCK_GCC_BLSP1_QUP2_APPS_CLK CLOCK_SCC_QUP_I2C2_CLK
#define CLOCK_GCC_BLSP2_QUP2_APPS_CLK CLOCK_SCC_QUP_I2C2_CLK

#define CLOCK_GCC_BLSP1_QUP3_APPS_CLK CLOCK_SCC_QUP_I2C3_CLK
#define CLOCK_GCC_BLSP2_QUP3_APPS_CLK CLOCK_SCC_QUP_I2C3_CLK

#define CLOCK_GCC_BLSP1_QUP4_APPS_CLK CLOCK_TOTAL_CLOCK_ENUMS
#define CLOCK_GCC_BLSP2_QUP4_APPS_CLK CLOCK_TOTAL_CLOCK_ENUMS

#define CLOCK_GCC_BLSP1_QUP5_APPS_CLK CLOCK_TOTAL_CLOCK_ENUMS
#define CLOCK_GCC_BLSP2_QUP5_APPS_CLK CLOCK_TOTAL_CLOCK_ENUMS

#define CLOCK_GCC_BLSP1_QUP6_APPS_CLK CLOCK_TOTAL_CLOCK_ENUMS
#define CLOCK_GCC_BLSP2_QUP6_APPS_CLK CLOCK_TOTAL_CLOCK_ENUMS


/*=========================================================================
      Function Definitions.
==========================================================================*/


/* ============================================================================
**  Function : uClock_EnableClock
** ============================================================================
*/
/**
  Enables a clock.
    
  @param[in]  eClockId  - The ID of the clock to enable.

  @return
  TRUE  - The clock was enabled.
  FALSE - Otherwise.
  
  @dependencies
  None.

*/

boolean uClock_EnableClock(uClockIdType eClockId);


/* ============================================================================
**  Function : uClock_DisableClock
** ============================================================================
*/
/**
  Disables a clock.
    
  @param[in]  eClockId  - The ID of the clock to disable.

  @return
  TRUE  - The clock was disabled.
  FALSE - Otherwise.
  
  @dependencies
  None.

*/

boolean uClock_DisableClock(uClockIdType eClockId);


/* ============================================================================
**  Function : uClock_IsClockEnabled
** ============================================================================
*/
/**
  Returns whether a clock is enabled or not.
    
  @param[in]  eClockId  - The ID of the clock to disable.

  @return
  TRUE  - The clock is on.
  FALSE - The clock is off.
  
  @dependencies
  None.

*/

boolean uClock_IsClockEnabled(uClockIdType eClockId);


/* ============================================================================
**  Function : uClock_SetClockDivider
** ============================================================================
*/
/**
  Allows a caller to set the divider value of a clock.
    
  @param[in]  eClockId  - The ID of the clock to perform the operation on.
  @param[in]  nDivider  - The divider value to program for the specified clock.

  @return
  TRUE  - The operation completed successfully.
  FALSE - A parameter is invalid.
  
  @dependencies
  None.

*/

boolean uClock_SetClockDivider(uClockIdType eClockId, uint32 nDivider);


/* ============================================================================
**  Function : uClock_SetClockFrequency
** ============================================================================
*/
/**
  Allows a caller to set the frequency value of a clock that has its own
  root clock generator.
    
  @param[in]  eClockId  - The ID of the clock to perform the operation on.
  @param[in]  nFreqHz  - The frequency in Hz to program for the specified clock.

  @return
  TRUE  - The operation completed successfully.
  FALSE - Frequency is too high or clock is not supported.
  
  @dependencies
  None.

*/

boolean uClock_SetClockFrequency(uClockIdType eClockId, uint32 nFreqHz);


/* ============================================================================
**  Function : uClock_GetClockFrequency
** ============================================================================
*/
/**
  Allows a caller to get the frequency value of a clock that has its own
  root clock generator.  This API should be used after calling the API
  uClock_SetClockFrequency at least once.
    
  @param[in]  eClockId  - The ID of the clock to perform the operation on.
  @param[in]  *nFreqHz  - The frequency in Hz that has been programmed to HW.

  @return
  TRUE  - The operation completed successfully.
  FALSE - Frequency has not been programmed or the clock does not support this
          API.
  
  @dependencies
  uClock_SetClockFrequency should be called at least once before calling this API.

*/

boolean uClock_GetClockFrequency(uClockIdType eClockId, uint32 *nFreqHz);

#endif /* UCLOCK_H */
