/*
===========================================================================
*/
/**
  @file uClock.c
  @brief Public definitions include file for accessing the uClock device driver.
*/
/*===========================================================================
NOTE: The @brief description and any detailed descriptions above do not appear
      in the PDF.

      This file is the public header file for the sensors micro image (uImage)
      clock driver implementation. It is meant to be used by a small subset
      of drivers supporting the sensors uImage feature, which cannot access
      DDR.

===========================================================================*/
/*
  ===========================================================================

  Copyright (c) 2016 Qualcomm Technologies Incorporated.
  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ===========================================================================

  $Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/clock/hw/sdm660/adsp_slpi/src/uClock.c#1 $
  $DateTime: 2020/02/10 01:57:30 $
  $Author: pwbldsvc $

  when       who     what, where, why
  --------   ---     ---------------------------------------------------------- 
  10/19/16   shm     First version for SDM660.

  ===========================================================================
*/


/*=========================================================================
      Include Files
==========================================================================*/

#include "com_dtypes.h"
#include "uClock.h"
#include "uClockInternal.h"
#include "qurt.h"
#include "qurt_qdi.h"
#include "qurt_qdi_driver.h"
#include "uClockHWIO.h"
#include "HALhwio.h"

/*=========================================================================
      Type Definitions
==========================================================================*/

/*
 * uClock user context type.
 * Parameters:
 *   bIsInitialized  - Specifies if the driver has been initialized.
 *   nClockQDIHandle - The QDI handle to the root PD.
 */
typedef struct
{
  boolean bIsInitialized;
  int32   nClockQDIHandle;

} uClockUserCtxtType;

/*=========================================================================
      Local Variables
==========================================================================*/
/*
 * Bit-field values for the clock configuration registers.
 */
#define CLOCK_CBCR_CLK_OFF_BMSK  0x80000000
#define CLOCK_CBCR_CLK_ENA_BMSK  0x00000001

static uClockFreqConfigType uClockUARTFreqConfig[] =
{
  { 14745600,   2,  150, 2539 },
  { 49918771,  10,    0,    0 },
  { 62398464,   8,    0,    0 },
  { 0,          0,    0,    0 }
};

static uClockFreqCfgRegType uClockFreqCfgRegs[] =
{
  {
    HWIO_ADDR(LPASS_SCC_UART1_CMD_RCGR),
    HWIO_ADDR(LPASS_SCC_UART1_CFG_RCGR),
    HWIO_ADDR(LPASS_SCC_UART1_M),
    HWIO_ADDR(LPASS_SCC_UART1_N),
    HWIO_ADDR(LPASS_SCC_UART1_D)
  },
  {
    HWIO_ADDR(LPASS_SCC_UART2_CMD_RCGR),
    HWIO_ADDR(LPASS_SCC_UART2_CFG_RCGR),
    HWIO_ADDR(LPASS_SCC_UART2_M),
    HWIO_ADDR(LPASS_SCC_UART2_N),
    HWIO_ADDR(LPASS_SCC_UART2_D)
  },
  {
    HWIO_ADDR(LPASS_SCC_UART3_CMD_RCGR),
    HWIO_ADDR(LPASS_SCC_UART3_CFG_RCGR),
    HWIO_ADDR(LPASS_SCC_UART3_M),
    HWIO_ADDR(LPASS_SCC_UART3_N),
    HWIO_ADDR(LPASS_SCC_UART3_D)
  },
  {
    HWIO_ADDR(LPASS_SCC_UART4_CMD_RCGR),
    HWIO_ADDR(LPASS_SCC_UART4_CFG_RCGR),
    HWIO_ADDR(LPASS_SCC_UART4_M),
    HWIO_ADDR(LPASS_SCC_UART4_N),
    HWIO_ADDR(LPASS_SCC_UART4_D)
  }
};

/*
 * Register map table for clocks residing in the uImage.  Some clocks have divider
 * registers separate from their CBCRs so that must be reflected here.
 */
static uClockRegType gnClockRegs[CLOCK_TOTAL_CLOCK_ENUMS] =
{
  {HWIO_ADDR(LPASS_ISLAND_SCC_QUP_I2C1_CBCR),
   HWIO_ADDR(LPASS_ISLAND_SCC_SPI_I2C1_CLK_CDIV_REG),
   HWIO_SHFT(LPASS_ISLAND_SCC_SPI_I2C1_CLK_CDIV_REG, CLK_DIV),
   HWIO_FMSK(LPASS_ISLAND_SCC_SPI_I2C1_CLK_CDIV_REG, CLK_DIV) },

  {HWIO_ADDR(LPASS_ISLAND_SCC_QUP_I2C2_CBCR),
   HWIO_ADDR(LPASS_ISLAND_SCC_SPI_I2C2_CLK_CDIV_REG),
   HWIO_SHFT(LPASS_ISLAND_SCC_SPI_I2C2_CLK_CDIV_REG, CLK_DIV),
   HWIO_FMSK(LPASS_ISLAND_SCC_SPI_I2C2_CLK_CDIV_REG, CLK_DIV) },

  {HWIO_ADDR(LPASS_ISLAND_SCC_QUP_I2C3_CBCR),
   HWIO_ADDR(LPASS_ISLAND_SCC_SPI_I2C3_CLK_CDIV_REG),
   HWIO_SHFT(LPASS_ISLAND_SCC_SPI_I2C3_CLK_CDIV_REG, CLK_DIV),
   HWIO_FMSK(LPASS_ISLAND_SCC_SPI_I2C3_CLK_CDIV_REG, CLK_DIV) },

  {HWIO_ADDR(LPASS_ISLAND_SCC_QUP_SPI1_CBCR),
   HWIO_ADDR(LPASS_ISLAND_SCC_SPI_I2C1_CLK_CDIV_REG),
   HWIO_SHFT(LPASS_ISLAND_SCC_SPI_I2C1_CLK_CDIV_REG, CLK_DIV),
   HWIO_FMSK(LPASS_ISLAND_SCC_SPI_I2C1_CLK_CDIV_REG, CLK_DIV) },

  {HWIO_ADDR(LPASS_ISLAND_SCC_QUP_SPI2_CBCR),
   HWIO_ADDR(LPASS_ISLAND_SCC_SPI_I2C2_CLK_CDIV_REG),
   HWIO_SHFT(LPASS_ISLAND_SCC_SPI_I2C2_CLK_CDIV_REG, CLK_DIV),
   HWIO_FMSK(LPASS_ISLAND_SCC_SPI_I2C2_CLK_CDIV_REG, CLK_DIV) },

  {HWIO_ADDR(LPASS_ISLAND_SCC_QUP_SPI3_CBCR),
   HWIO_ADDR(LPASS_ISLAND_SCC_SPI_I2C3_CLK_CDIV_REG),
   HWIO_SHFT(LPASS_ISLAND_SCC_SPI_I2C3_CLK_CDIV_REG, CLK_DIV),
   HWIO_FMSK(LPASS_ISLAND_SCC_SPI_I2C3_CLK_CDIV_REG, CLK_DIV) },

  {HWIO_ADDR(LPASS_ISLAND_SCC_UART_DM_UART1_CBCR),
   0,
   0,
   0,
   &uClockFreqCfgRegs[0]},

  {HWIO_ADDR(LPASS_ISLAND_SCC_UART_DM_UART2_CBCR),
   0,
   0,
   0,
   &uClockFreqCfgRegs[1]},

  {HWIO_ADDR(LPASS_ISLAND_SCC_UART_DM_UART3_CBCR),
   0,
   0,
   0,
   &uClockFreqCfgRegs[2]},

  {HWIO_ADDR(LPASS_ISLAND_SCC_UART_DM_UART4_CBCR),
   0,
   0,
   0,
   &uClockFreqCfgRegs[3]},

  {HWIO_ADDR(LPASS_ISLAND_SCC_BLSP_H_CORE_CBCR),
   HWIO_ADDR(LPASS_ISLAND_SCC_BUS_CLK_CDIV_REG),
   HWIO_SHFT(LPASS_ISLAND_SCC_BUS_CLK_CDIV_REG, CLK_DIV),
   HWIO_FMSK(LPASS_ISLAND_SCC_BUS_CLK_CDIV_REG, CLK_DIV) }
};


/*
 * Local uClock user context.
 */
static uClockUserCtxtType uClockUserCtxt;


/*=========================================================================
      Function Definitions.
==========================================================================*/

/* ============================================================================
**  Function : uClock_SendRequest
** ============================================================================
*/
/**
  Sends a request to the root PD for the specified command.
    
  @param[in]  eClockId  - The ID of the clock to perform the operation on.
  @param[in]  eCmd      - The requested command to perform.
  @param[in]  nParams   - The parameters to pass in.

  @return
  TRUE  - The operation completed successfully.
  FALSE - Initialization failed or one of the parameters is invalid.
  
  @dependencies
  None.

*/

boolean uClock_SendRequest(uClockIdType eClockId, uClockCmdType eCmd, uint32 nParams)
{
  int nQDIResult;

  /*
   * Make sure the QDI path is open and all initialization has taken
   * place.
   */
  if( uClockUserCtxt.bIsInitialized == FALSE )
  {
    if(0 != (uClockUserCtxt.nClockQDIHandle = qurt_qdi_open(uClockQDIName)))
    {
      uClockUserCtxt.bIsInitialized = TRUE;
    }
    else
    {
      return(FALSE);
    }
  }

  /*
   * Send the request to the root PD.
   */
  nQDIResult = qurt_qdi_handle_invoke(uClockUserCtxt.nClockQDIHandle, 
                                      UCLOCK_QDI_CLOCK_CMD_ROUTER,
                                      eCmd,
                                      (uint32)eClockId,
                                      nParams);

  if(nQDIResult != 0)
  {
    return(FALSE);
  }
  return(TRUE);

}


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

boolean uClock_EnableClock(uClockIdType eClockId)
{
  return uClock_SendRequest(eClockId, UCLOCK_CMD_ENABLE_CLOCK, 0);

} /* uClock_EnableClock */


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

boolean uClock_DisableClock(uClockIdType eClockId)
{
  return uClock_SendRequest(eClockId, UCLOCK_CMD_DISABLE_CLOCK, 0);

} /* uClock_DisableClock */


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

boolean uClock_IsClockEnabled(uClockIdType eClockId)
{
  if(eClockId < CLOCK_TOTAL_CLOCK_ENUMS)
  {
    if(in_dword(gnClockRegs[eClockId].nEnableAddr) & CLOCK_CBCR_CLK_OFF_BMSK)
    {
      return(FALSE);
    }
    else
    {
      return(TRUE);
    }
  }

  return(FALSE);

} /* uClock_IsClockEnabled */


/* ============================================================================
**  Function : uClock_SetClockDivider
** ============================================================================
*/
/**
  Configures the divider of a clock output.
    
  @param[in]  eClockId  - The ID of the clock to disable.
  @param[in]  nDivider  - The divider value to program.

  @return
  TRUE  - The clock divider was set.
  FALSE - The divider is out of range or not supported for the requeste clock.
  
  @dependencies
  None.

*/

boolean uClock_SetClockDivider(uClockIdType eClockId, uint32 nDivider)
{
  return uClock_SendRequest(eClockId, UCLOCK_CMD_SET_DIVIDER, nDivider);
   
} /* uClock_SetClockDivider */


/* ============================================================================
**  Function : uClock_SetClockFrequency
** ============================================================================
*/
/**
  Sets a frequency for clocks that contain dedicated RCGs.
    
  @param[in]  eClockId  - The ID of the clock to disable.
  @param[in]  nFreqHz  -  The desired frequency of the clock.

  @return
  TRUE  - The clock frequency was set.
  FALSE - The clock does not support frequency settings or desired frequency
          cannot be attained.
  
  @dependencies
  None.

*/

boolean uClock_SetClockFrequency(uClockIdType eClockId, uint32 nFreqHz)
{
  return uClock_SendRequest(eClockId, UCLOCK_CMD_SET_FREQUENCY, nFreqHz);
   
} /* uClock_SetClockFrequency */


/* ============================================================================
**  Function : uClock_GetClockFrequency
** ============================================================================
*/
/**
  Reads the RCG registers of a particular clock that has a dedicated root clock
  generator and compares against known clock frequency settings to determine
  the current clock frequency.
    
  @param[in]  eClockId  - The ID of the clock to perform the operation on.
  @param[in]  *nFreqHz  - The currently programmed frequency.

  @return
  TRUE  - The clock frequency was found and returned.
  FALSE - Either the clock does not have a dedicated RCG or it has not had a 
          frequency set.
  
  @dependencies
  Expects uClock_SetClockFrequency to be called at least once before calling 
  this API.

*/

boolean uClock_GetClockFrequency(uClockIdType eClockId, uint32 *nFreqHz)
{
  uint16 n2Div = 0, nM = 0, nN = 0;
  uint32 nCfgIdx = 0;

  if ((eClockId < CLOCK_TOTAL_CLOCK_ENUMS) && 
      (gnClockRegs[eClockId].pRCG != NULL) && 
      (nFreqHz != NULL))
  {
    n2Div = (uint16)((in_dword(gnClockRegs[eClockId].pRCG->nRCGCfgAddr) & \
                     HWIO_LPASS_SCC_UART1_CFG_RCGR_SRC_DIV_BMSK) + 1);
    nM = (uint16)in_dword(gnClockRegs[eClockId].pRCG->nMAddr);
    nN = (uint16)in_dword(gnClockRegs[eClockId].pRCG->nNAddr);

    if (nN != 0)
    {
      nN = ~nN + nM;
    }

    while (uClockUARTFreqConfig[nCfgIdx].nFreqHz != 0)
    {
      if ((uClockUARTFreqConfig[nCfgIdx].n2Div == n2Div) &&
          (uClockUARTFreqConfig[nCfgIdx].nM == nM) &&
          (uClockUARTFreqConfig[nCfgIdx].nN == nN))
      {
        *nFreqHz = uClockUARTFreqConfig[nCfgIdx].nFreqHz;
        return (TRUE);
      }
      nCfgIdx++;
    }

    if (uClockUARTFreqConfig[nCfgIdx].nFreqHz == 0)
    {
      *nFreqHz = 0;
    }
  }
  return (FALSE);
}
