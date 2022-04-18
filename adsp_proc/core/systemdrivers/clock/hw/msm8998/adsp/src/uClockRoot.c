/*
===========================================================================
*/
/**
  @file uClockRoot.c
  @brief Implementation of the micro clock driver in the root protection
  domain.
*/
/*===========================================================================
NOTE: The @brief description and any detailed descriptions above do not appear
      in the PDF.

      This file is source file for the sensors micro image (uImage)
      clock driver implementation.  It is meant to be used by a small subset
      of drivers supporting the sensors uImage feature, which cannot access
      DDR.  This file implements the portion of the driver residing in the
      root protection domain.

===========================================================================*/
/*
  ===========================================================================

  Copyright (c) 2014 QUALCOMM Technologies Incorporated.
  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ===========================================================================

  $Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/clock/hw/msm8998/adsp/src/uClockRoot.c#1 $
  $DateTime: 2020/02/10 01:57:30 $
  $Author: pwbldsvc $

  when       who     what, where, why
  --------   ---     ----------------------------------------------------------
  11/17/14   dcf     Added for MSM8994 micro sensors functionality.

  ===========================================================================
*/


/*=========================================================================
      Include Files
==========================================================================*/

#include "com_dtypes.h"
#include "uClock.h"
#include "uClockHWIO.h"
#include "uClockInternal.h"
#include "HALhwio.h"
#include "qurt.h"
#include "busywait.h"
#include "qurt_qdi.h"
#include "qurt_qdi_driver.h"
#include "qurt_futex.h"
#include "qurt_atomic_ops.h"
#include "stdlib.h"

/*=========================================================================
      Type Definitions
==========================================================================*/

/*
 * QDI Opener object type.
 */
typedef struct
{
  qurt_qdi_obj_t    qdiobj;

}uClockQDIOpenerType;

/*
 * QDI Driver object type.
 */
typedef struct
{
  qurt_qdi_obj_t qdiobj;

}uClockQDIDrvType;


/*
 * Micro-Clock state context structure.
 * Parameters:
 *   Mutex             - Synchronization mutex locking.
 *   bInitialized      - Specifies if initialization has taken place.
 *   uClockQDIDrv      - uClock QDI driver handle.
 *   anClockReferences - Array of clock references.
 */
typedef struct
{
   qurt_mutex_t     Mutex;
   boolean          bInitialized;
   uClockQDIDrvType uClockQDIDrv;
   uint8            anClockReferences[CLOCK_TOTAL_CLOCK_ENUMS];

}uClockCtxtType;

static uClockFreqConfigType uClockUARTFreqConfig[] =
{
  { 14745600,   2,  3, 61 },
  { 48000000,   2,  4, 25 },
  { 50000000,  12,  0,  0 },
  { 0,          0,  0,  0 }
};

/*=========================================================================
      Local Variables
==========================================================================*/

/*
 * Bit-field values for the clock configuration registers.
 */
#define CLOCK_CBCR_CLK_OFF_BMSK  0x80000000
#define CLOCK_CBCR_CLK_ENA_BMSK  0x00000001

#define CLOCK_SSC_PLL_OUT_EVEN_VAL  0x2

static uClockFreqCfgRegType uClockFreqCfgRegs[] =
{
  {
    HWIO_ADDR(SSC_SCC_SCC_UART_DM_UART1_CMD_RCGR),
    HWIO_ADDR(SSC_SCC_SCC_UART_DM_UART1_CFG_RCGR),
    HWIO_ADDR(SSC_SCC_SCC_UART_DM_UART1_M),
    HWIO_ADDR(SSC_SCC_SCC_UART_DM_UART1_N),
    HWIO_ADDR(SSC_SCC_SCC_UART_DM_UART1_D)
  },
  {
    HWIO_ADDR(SSC_SCC_SCC_UART_DM_UART2_CMD_RCGR),
    HWIO_ADDR(SSC_SCC_SCC_UART_DM_UART2_CFG_RCGR),
    HWIO_ADDR(SSC_SCC_SCC_UART_DM_UART2_M),
    HWIO_ADDR(SSC_SCC_SCC_UART_DM_UART2_N),
    HWIO_ADDR(SSC_SCC_SCC_UART_DM_UART2_D)
  },
  {
    HWIO_ADDR(SSC_SCC_SCC_UART_DM_UART3_CMD_RCGR),
    HWIO_ADDR(SSC_SCC_SCC_UART_DM_UART3_CFG_RCGR),
    HWIO_ADDR(SSC_SCC_SCC_UART_DM_UART3_M),
    HWIO_ADDR(SSC_SCC_SCC_UART_DM_UART3_N),
    HWIO_ADDR(SSC_SCC_SCC_UART_DM_UART3_D)
  }
};



/*
 * Register map table for clocks residing in the uImage.  Some clocks have divider
 * registers separate from their CBCRs so that must be reflected here.
 */
static uClockRegType gnClockRegs[CLOCK_TOTAL_CLOCK_ENUMS] =
{
  {HWIO_ADDR(SSC_SCC_SCC_QUP_I2C1_CBCR), 
   HWIO_ADDR(SSC_SCC_SCC_SPI_I2C1_CLK_CDIV_REG), 
   HWIO_SHFT(SSC_SCC_SCC_SPI_I2C1_CLK_CDIV_REG, CLK_DIV), 
   HWIO_FMSK(SSC_SCC_SCC_SPI_I2C1_CLK_CDIV_REG, CLK_DIV) },

  {HWIO_ADDR(SSC_SCC_SCC_QUP_I2C2_CBCR), 
   HWIO_ADDR(SSC_SCC_SCC_SPI_I2C2_CLK_CDIV_REG),
   HWIO_SHFT(SSC_SCC_SCC_SPI_I2C2_CLK_CDIV_REG, CLK_DIV),
   HWIO_FMSK(SSC_SCC_SCC_SPI_I2C2_CLK_CDIV_REG, CLK_DIV) },

  {HWIO_ADDR(SSC_SCC_SCC_QUP_I2C3_CBCR), 
   HWIO_ADDR(SSC_SCC_SCC_SPI_I2C3_CLK_CDIV_REG),
   HWIO_SHFT(SSC_SCC_SCC_SPI_I2C3_CLK_CDIV_REG, CLK_DIV),
   HWIO_FMSK(SSC_SCC_SCC_SPI_I2C3_CLK_CDIV_REG, CLK_DIV) },

  {HWIO_ADDR(SSC_SCC_SCC_QUP_SPI1_CBCR), 
   HWIO_ADDR(SSC_SCC_SCC_SPI_I2C1_CLK_CDIV_REG),
   HWIO_SHFT(SSC_SCC_SCC_SPI_I2C1_CLK_CDIV_REG, CLK_DIV),
   HWIO_FMSK(SSC_SCC_SCC_SPI_I2C1_CLK_CDIV_REG, CLK_DIV) },

  {HWIO_ADDR(SSC_SCC_SCC_QUP_SPI2_CBCR), 
   HWIO_ADDR(SSC_SCC_SCC_SPI_I2C2_CLK_CDIV_REG),
   HWIO_SHFT(SSC_SCC_SCC_SPI_I2C2_CLK_CDIV_REG, CLK_DIV),
   HWIO_FMSK(SSC_SCC_SCC_SPI_I2C2_CLK_CDIV_REG, CLK_DIV) },

  {HWIO_ADDR(SSC_SCC_SCC_QUP_SPI3_CBCR), 
   HWIO_ADDR(SSC_SCC_SCC_SPI_I2C3_CLK_CDIV_REG),
   HWIO_SHFT(SSC_SCC_SCC_SPI_I2C3_CLK_CDIV_REG, CLK_DIV),
   HWIO_FMSK(SSC_SCC_SCC_SPI_I2C3_CLK_CDIV_REG, CLK_DIV) },

  {HWIO_ADDR(SSC_SCC_SCC_UART_DM_UART1_CBCR), 
   0,
   0, 
   0,
   &uClockFreqCfgRegs[0]},

  {HWIO_ADDR(SSC_SCC_SCC_UART_DM_UART2_CBCR), 
   0, 
   0,
   0,
   &uClockFreqCfgRegs[1]},

  {HWIO_ADDR(SSC_SCC_SCC_UART_DM_UART3_CBCR), 
   0,
   0,
   0,
   &uClockFreqCfgRegs[2]},

  {HWIO_ADDR(SSC_SCC_SCC_BLSP_H_CBCR),  
   HWIO_ADDR(SSC_SCC_SCC_BUS_CLK_CDIV_REG),
   HWIO_SHFT(SSC_SCC_SCC_BUS_CLK_CDIV_REG, CLK_DIV),
   HWIO_FMSK(SSC_SCC_SCC_BUS_CLK_CDIV_REG, CLK_DIV) }
};


/*
 * Global Micro-Clock Driver Context.
 */
static uClockCtxtType uClockDriverCtxt;



/*=========================================================================
      Function Prototypes.
==========================================================================*/

/*
 * Invocation function for routing QDI requests to the associated clock APIs.
 */
static int uClockQDI_Invoke(int hClientHandle,
                          qurt_qdi_obj_t *pobj,
                          int method,
                          qurt_qdi_arg_t a1,
                          qurt_qdi_arg_t a2,
                          qurt_qdi_arg_t a3,
                          qurt_qdi_arg_t a4,
                          qurt_qdi_arg_t a5,
                          qurt_qdi_arg_t a6,
                          qurt_qdi_arg_t a7,
                          qurt_qdi_arg_t a8,
                          qurt_qdi_arg_t a9);

/*
 * Release function for QDI objects.
 */
void uClockQDI_Release(qurt_qdi_obj_t *qdiobj);


/*
 * The QDI functionality is implemented in a opener object.
 */
const uClockQDIOpenerType uClockQDIOpener = {
  {
    uClockQDI_Invoke,
    QDI_REFCNT_PERM,
    uClockQDI_Release
  }
};

/*
 * Internal uClock_IsOn API used by QDI router function.
 */
boolean uClock_IsOn(uClockIdType eClockId);


/*=============================================================================
 ==============================================================================

       Q D I   H A N D L E R   P R O G R A M M E R   I N T E R F A C E

 ==============================================================================
 ============================================================================*/

/* ============================================================================
**  Function : uClockQDI_Release
** ============================================================================
*/
/**
  Releases a QDI object.

  @param[in]  qdiobj  - The QDI object to release.

  @return
  None.

  @dependencies
  None.

*/
void uClockQDI_Release
(
  qurt_qdi_obj_t *qdiobj
)
{
  free(qdiobj);
}

/* ============================================================================
**  Function : uClock_QDIOpen
** ============================================================================
*/
/**
  Opens a QDI object.

  @param[in]  hClientHandle  - Handle to the requesting client.
  @param[in]  objptr         - Pointer to the object.
  @param[in]  devname        - The string name of the device.
  @param[in]  mode           - Unused.

  @return
  0  - success
  -1 - failure

  @dependencies
  None.

*/
int uClock_QDIOpen
(
  int hClientHandle,
  qurt_qdi_obj_t *objptr,
  const char *devname,
  int mode
)
{
  /*
   * Initialize the QDI object function pointers and create the handle.
   */
  uClockDriverCtxt.uClockQDIDrv.qdiobj.invoke = uClockQDI_Invoke;
  uClockDriverCtxt.uClockQDIDrv.qdiobj.refcnt = QDI_REFCNT_INIT;
  uClockDriverCtxt.uClockQDIDrv.qdiobj.release = uClockQDI_Release;

  return qurt_qdi_handle_create_from_obj_t(hClientHandle,&uClockDriverCtxt.uClockQDIDrv.qdiobj);

} /* uClock_QDIOpen */


/* ============================================================================
**  Function : uClock_QDIRouteCommand
** ============================================================================
*/
/**
  Router API to invoke the proper clock API based on QDI request.

  @param[in]  hClientHandle  - Handle to the requesting client.
  @param[in]  nCmd           - The requested command.
  @param[in]  nClockId       - The clock identifier.
  @param[in]  nDivider       - The divider value for the SetClockDivider API,
                               if used.

  @return
  0  - success
  -1 - failure

  @dependencies
  None.

*/
int uClock_QDIRouteCommand
(
  int hClientHandle,
  int nCmd,
  int nClockId,
  int nClockVal
)
{
  boolean bRetVal = FALSE;

  switch((uClockCmdType)nCmd)
  {
    case UCLOCK_CMD_ENABLE_CLOCK:
      bRetVal = uClock_EnableClock((uClockIdType)nClockId);
      break;

    case UCLOCK_CMD_DISABLE_CLOCK:
      bRetVal = uClock_DisableClock((uClockIdType)nClockId);
      break;

    case UCLOCK_CMD_IS_CLOCK_ON:
      /*
       * Return a success only if the clock is on.
       */
      if(uClock_IsOn((uClockIdType)nClockId)) { bRetVal = TRUE; }
      else { bRetVal = FALSE; }

    case UCLOCK_CMD_SET_DIVIDER:
      bRetVal = uClock_SetClockDivider((uClockIdType)nClockId, (uint32)nClockVal);
      break;

    case UCLOCK_CMD_SET_FREQUENCY:
      bRetVal = uClock_SetClockFrequency((uClockIdType)nClockId, (uint32)nClockVal);
      break;

    default:
      bRetVal = FALSE;
      break;
  }

  if(bRetVal == TRUE)
  {
    return 0;
  }
  return -1;

}

/* ============================================================================
**  Function : uClockQDI_Invoke
** ============================================================================
*/
/**
  Main receiving API for QDI requests from user PD.

  @param[in]  hClientHandle         - Handle to the requesting client.
  @param[in]  method                - The requested command.
  @param[in]  a1 (a1.num: nClockId) - The clock identifier.
  @param[in]  a2 (a2.num: nDivider) - The divider value for the SetClockDivider API,
                                      if used.
  @param[in] ...

  @return
  0  - success
  -1 - failure

  @dependencies
  None.

*/
static int uClockQDI_Invoke(int hClientHandle,
                          qurt_qdi_obj_t *pobj,
                          int method,
                          qurt_qdi_arg_t a1,
                          qurt_qdi_arg_t a2,
                          qurt_qdi_arg_t a3,
                          qurt_qdi_arg_t a4,
                          qurt_qdi_arg_t a5,
                          qurt_qdi_arg_t a6,
                          qurt_qdi_arg_t a7,
                          qurt_qdi_arg_t a8,
                          qurt_qdi_arg_t a9)
{
  switch (method)
  {
    case QDI_OPEN:
      return uClock_QDIOpen(hClientHandle, (void *)pobj, a1.ptr, a2.num);

    case UCLOCK_QDI_CLOCK_CMD_ROUTER:
      return uClock_QDIRouteCommand(hClientHandle, a1.num, a2.num, a3.num);

    case QDI_ISLAND_CHECK_ALLOC:
      return 1;

    default:
      return qurt_qdi_method_default(hClientHandle, pobj, method,
                                     a1, a2, a3, a4, a5, a6, a7, a8, a9);
  }

  return -1;

} /* End uClockQDI_Invoke */


/*=============================================================================
 ==============================================================================

  A P P L I C A T I O N    P R O G R A M M E R   I N T E R F A C E

 ==============================================================================
 ============================================================================*/


/* ============================================================================
**  Function : uClock_Init
** ============================================================================
*/
/**
  Initializes the uClock driver.

  @return
  TRUE  - Driver was initialized.
  FALSE - Otherwise.

  @dependencies
  None.

*/
boolean uClock_Init(void)
{
  qurt_mutex_init(&uClockDriverCtxt.Mutex);

  if (qurt_qdi_register_devname(uClockQDIName, &uClockQDIOpener) < 0)
  {
    return(FALSE);
  }

  uClockDriverCtxt.bInitialized = TRUE;
  return(TRUE);

} /* uClock_Init */


/* ============================================================================
**  Function : uClock_IsOn
** ============================================================================
*/
/**
  Internal API which returns whether a clock is on or not.

  @param[in]  eClockId  - The ID of the clock to enable.

  @return
  TRUE  - The clock is on.
  FALSE - Otherwise.

  @dependencies
  None.

*/
boolean uClock_IsOn(uClockIdType eClockId)
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

} /* uClock_IsOn */


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
  boolean bRetVal = FALSE;
  uint32 nTimeout = 150;

  if(eClockId < CLOCK_TOTAL_CLOCK_ENUMS)
  {
    /*
     * Synchronize.
     */
    qurt_mutex_lock(&uClockDriverCtxt.Mutex);

    if(uClockDriverCtxt.anClockReferences[eClockId] == 0)
    {
      /*
       * Clock is not already on, so enable it here.
       */
      out_dword(gnClockRegs[eClockId].nEnableAddr,
          (in_dword(gnClockRegs[eClockId].nEnableAddr) | CLOCK_CBCR_CLK_ENA_BMSK));

      /*
       * Make sure the clock is on.
       */
      while(uClock_IsOn(eClockId) != TRUE)
      {
        if(nTimeout == 0)
        {
          break;
        }
        busywait(2);
        nTimeout--;
      }

      /*
       * Increase the reference count on this clock.
       */
      if(nTimeout != 0)
      {
        uClockDriverCtxt.anClockReferences[eClockId]++;
        bRetVal = TRUE;
      }
    }
    else
    {
      /*
       * Clock is already on so just increase reference count.
       */
      uClockDriverCtxt.anClockReferences[eClockId]++;
      bRetVal = TRUE;
    }

    /*
     * Release lock.
     */
    qurt_mutex_unlock(&uClockDriverCtxt.Mutex);  }

  return(bRetVal);

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
  if(eClockId < CLOCK_TOTAL_CLOCK_ENUMS)
  {
    /*
     * Workaround for 8996.  BLSP_H_CLK must remain on indefinitely.
     */
    if(eClockId == CLOCK_SCC_BLSP_H_CLK)
    {
      return(TRUE);
    }

    /*
     * Synchronize.
     */
    qurt_mutex_lock(&uClockDriverCtxt.Mutex);

    /*
     * Only enable the clock if it's not already enabled.
     */
    if(uClockDriverCtxt.anClockReferences[eClockId] > 0)
    {
      uClockDriverCtxt.anClockReferences[eClockId]--;
    }

    if(uClockDriverCtxt.anClockReferences[eClockId] == 0)
    {
      out_dword(gnClockRegs[eClockId].nEnableAddr,
          in_dword(gnClockRegs[eClockId].nEnableAddr) & ~CLOCK_CBCR_CLK_ENA_BMSK);
    }

    /*
     * Release lock.
     */
    qurt_mutex_unlock(&uClockDriverCtxt.Mutex);

    return(TRUE);
  }

  return(FALSE);

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
   return(uClock_IsOn(eClockId));

} /* uClock_IsClockEnabled */


/* ============================================================================
**  Function : uClock_SetClockDivider
** ============================================================================
*/
/**
  Sets the clock divider for a particular clock managed in uImage.

  @param[in]  eClockId  - The ID of the clock to perform the operation on.
  @param[in]  nDivider  - The divider value to set.

  @return
  TRUE  - The divider was programmed.
  FALSE - The the clock ID is invalid.

  @dependencies
  None.

*/

boolean uClock_SetClockDivider
(
  uClockIdType eClockId,
  uint32 nClockDivider
)
{
  if(eClockId < CLOCK_TOTAL_CLOCK_ENUMS)
  {
    /*
     * Synchronize.
     */
    qurt_mutex_lock(&uClockDriverCtxt.Mutex);

    if(nClockDivider <= 1)
    {
      nClockDivider = 0;
    }
    else
    {
      nClockDivider--;
    }

    /*
     * Program the clock divider value for the associate clock.
     */
    out_dword(gnClockRegs[eClockId].nDividerAddr,
          ((in_dword(gnClockRegs[eClockId].nDividerAddr) &~ gnClockRegs[eClockId].nDividerBmsk) | \
           (nClockDivider << gnClockRegs[eClockId].nDividerShft)));

    /*
     * Release lock.
     */
    qurt_mutex_unlock(&uClockDriverCtxt.Mutex);

    return(TRUE);
  }
  return(FALSE);

} /* uClock_SetClockDivider */


/* ============================================================================
**  Function : uClock_SetClockFrequency
** ============================================================================
*/
/**
  Sets the clock frequency for a particular clock managed in uImage.  This
  API will only work for clocks that have a configurable root domain.  Any
  clock that is derived from the 100 MHz clock will not be able to use this
  API.

  @param[in]  eClockId  - The ID of the clock to perform the operation on.
  @param[in]  nFreqHz  -  The desired frequency in Hz.

  @return
  TRUE  - The divider was programmed.
  FALSE - The the clock ID is invalid.

  @dependencies
  None.

*/

boolean uClock_SetClockFrequency
(
  uClockIdType eClockId,
  uint32       nFreqHz
)
{
  uint32 nCfgIdx = 0;
  uint32 nNewCfgVal = 0;
  uint32 nMVal = 0, nNVal = 0, nDVal = 0;

  if (eClockId < CLOCK_TOTAL_CLOCK_ENUMS)
  {
    /*
     * Find the first clock frequency that is greater than or equal to
     * the desired frequency.
     */
    while (uClockUARTFreqConfig[nCfgIdx].nFreqHz != 0)
    {
      if (uClockUARTFreqConfig[nCfgIdx].nFreqHz >= nFreqHz)
      {
        break;
      }
      nCfgIdx++;
    }

    if (uClockUARTFreqConfig[nCfgIdx].nFreqHz != 0)
    {
      if (gnClockRegs[eClockId].pRCG != NULL)
      {
        /*
         * New config found.  Update the divider and source select.
         */
        nNewCfgVal =
          (uClockUARTFreqConfig[nCfgIdx].n2Div == 0 ?
           uClockUARTFreqConfig[nCfgIdx].n2Div :
           (uClockUARTFreqConfig[nCfgIdx].n2Div-1));

        nNewCfgVal |=
          (CLOCK_SSC_PLL_OUT_EVEN_VAL << HWIO_SSC_SCC_SCC_UART_DM_UART1_CFG_RCGR_SRC_SEL_SHFT);

        out_dword(gnClockRegs[eClockId].pRCG->nRCGCfgAddr, nNewCfgVal);

        if ((uClockUARTFreqConfig[nCfgIdx].nM != 0) && (uClockUARTFreqConfig[nCfgIdx].nN != 0))
        {
          nMVal = uClockUARTFreqConfig[nCfgIdx].nM;
          nNVal = ~(uClockUARTFreqConfig[nCfgIdx].nN-uClockUARTFreqConfig[nCfgIdx].nM);
          nDVal = ~(uClockUARTFreqConfig[nCfgIdx].nN);
        }

        /*
         * Program the fractional dividers here.
         */
        out_dword(gnClockRegs[eClockId].pRCG->nMAddr, nMVal);
        out_dword(gnClockRegs[eClockId].pRCG->nNAddr, nNVal);
        out_dword(gnClockRegs[eClockId].pRCG->nDAddr, nDVal);

        /*
         * Trigger the state update.
         */
        out_dword(gnClockRegs[eClockId].pRCG->nRCGCmdAddr, 0x1);

        return(TRUE);
      }
    }
  }

  return(FALSE);
}


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

boolean uClock_GetClockFrequency
(
  uClockIdType eClockId,
  uint32       *nFreqHz
)
{
  uint16 n2Div = 0, nM = 0, nN = 0;
  uint32 nCfgIdx = 0;

  if ((eClockId < CLOCK_TOTAL_CLOCK_ENUMS) &&
      (gnClockRegs[eClockId].pRCG != NULL) &&
      (nFreqHz != NULL))
  {
    n2Div = (uint16)((in_dword(gnClockRegs[eClockId].pRCG->nRCGCfgAddr) & \
                               HWIO_SSC_SCC_SCC_UART_DM_UART1_CFG_RCGR_SRC_DIV_BMSK) + 1);
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


