/*
===========================================================================

FILE:   HALqupeI2c.c

DESCRIPTION:
    This file implements qup hal functions specific to I2c operations.

===========================================================================

        Edit History


When     Who    What, where, why
-------- ---    -----------------------------------------------------------
02/01/17 VG     Copyright updated
07/08/13 BS     Fixed compiler warnings, matching with the defined types.
06/12/12 LK     Added flush and error state clearing.
06/06/12 ddk    Created

===========================================================================
    Copyright (c) 2012-2017 Qualcomm Technologies, Incorporated.
                        All rights reserved.
    Qualcomm Technologies, Confidential and Proprietary.

===========================================================================
*/
#include "HALqupe.h"
#include "HALqupeTarget.h"

// Define and include the header file that adds the relevant log headers
#define HAL_QUPE_I2C_LOG
#include "QupLog.h"

/*
#ifdef QUP_HAL_DBG
  #define WHERE_STR "FILE: %s LINE: %d"

  #define HAL_QUPE_ASSERT(COND)\
   {\
    if (COND) {\
      IBUSLOG(QUP_HAL_DBG, LOG_LEVEL_5,pQupAddr,2, WHERE_STR, __FILE__, __LINE__);\
      while(1);\
    }\
   }\

#else
*/
#define HAL_QUPE_ASSERT(...)

/*
#endif
*/


#define HAL_QUPE_TRANSFER_SIZE                          8
#define HAL_QUPE_MIN_FS_DIV_VAL                         3

/** @brief Configures the mini core for i2c use.
    @param[in]  pQupAddr Qup Block address.
    @return Nothing.
  */
void
HAL_qupe_Configure
(
   uint8 *pQupAddr
)
{
   QUPE_OUTF(pQupAddr, QUP_CONFIG, MINI_CORE, HAL_QUPE_MINI_CORE_I2C_MASTER);

   QUPE_OUTF(pQupAddr, QUP_CONFIG, N, (HAL_QUPE_TRANSFER_SIZE - 1));

   QUPE_OUTF(pQupAddr, QUP_IO_MODES, OUTPUT_BIT_SHIFT_EN, 0);

   QUPE_OUTF(pQupAddr, QUP_IO_MODES, PACK_EN, 1);

   QUPE_OUTF(pQupAddr, QUP_IO_MODES, UNPACK_EN, 1);

   QUPE_OUTF(pQupAddr, QUP_CONFIG, EN_EXT_OUT_FLAG, 0);
   QUPE_OUTF(pQupAddr, QUP_CONFIG, FIFO_CLK_GATE_EN, 1);
   QUPE_OUTF(pQupAddr, QUP_CONFIG, CORE_CLK_ON_EN, 1);
   QUPE_OUTF(pQupAddr, QUP_CONFIG, APP_CLK_ON_EN, 1);

   QUPE_OUTF(pQupAddr, QUP_OPERATIONAL_MASK, INPUT_SERVICE_MASK, 0); //en QUP irqs

   QUPE_OUTF(pQupAddr, QUP_OPERATIONAL_MASK, OUTPUT_SERVICE_MASK, 0); //en QUP irqs

   QUPE_OUTF(pQupAddr, I2C_MASTER_CONFIG, EN_VERSION_TWO_TAG, 1);

   HAL_qupe_SetOutputFifoEnabled(pQupAddr,1);
   HAL_qupe_SetInputFifoEnabled(pQupAddr,1);
}

/** @brief Performs flush for i2c use.
    @param[in]  pQupAddr Qup Block address.
    @return success.
  */
HAL_qupe_ResultType
HAL_qupe_I2cFlush
(
   uint8 *pQupAddr
)
{
   QUPE_OUTF(pQupAddr, QUP_STATE, I2C_FLUSH, 1);
   return HAL_QUPE_RESULT_SUCCESS;
}
/** @brief Sets the fast standard clock given the input clock freq in KHz.
    @param[in]  pQupAddr Qup Block address.
    @param[in]  uInputClockKhz Input clock to the i2c core in KHz.
    @param[in]  uI2cBusClockReqKhz Requested clock in KHz.
                I2C freq in KHz.	
    @param[in]  uI2cBusSDANoiseRejection Noise rejection for SDA.
    @param[in]  uI2cBusSCLNoiseRejection Noise rejection for SCL.
   
    @return HAL_QUPE_RESULT_SUCCESS if successful, error code otherwise.
  */
HAL_qupe_ResultType
HAL_qupe_SetI2cConfig
(
   uint8                      *pQupAddr,
   const uint32               uInputClockKhz,
   const uint32               uI2cBusClockReqKhz,
   const uint32               uI2cBusSDANoiseRejection,
   const uint32               uI2cBusSCLNoiseRejection
)
{
   uint32 uRegVal;
   uint32 uFsDivider;

   if ((0 == uI2cBusClockReqKhz) || (0 == uInputClockKhz)) {
      return HAL_QUPE_RESULT_INVALID_ARG;
   }

   uFsDivider = uInputClockKhz/(2*uI2cBusClockReqKhz) - 3;

   /* The lowest scaler should be 3 */
   if (uFsDivider < HAL_QUPE_MIN_FS_DIV_VAL) {
      return HAL_QUPE_RESULT_INVALID_FS_DIVIDER;     
   }

   uRegVal = QUPE_IN(pQupAddr, I2C_MASTER_CLK_CTL);

   /* clear the previous value */
   uRegVal &= (~ (QUPE_FMSK(I2C_MASTER_CLK_CTL, FS_DIVIDER_VALUE) |
                  QUPE_FMSK(I2C_MASTER_CLK_CTL, SDA_NOISE_REJECTION) |
                  QUPE_FMSK(I2C_MASTER_CLK_CTL, SCL_NOISE_REJECTION) )
              );
   
   uRegVal |= (uFsDivider << QUPE_SHFT(I2C_MASTER_CLK_CTL, FS_DIVIDER_VALUE) &
                             QUPE_FMSK(I2C_MASTER_CLK_CTL, FS_DIVIDER_VALUE));

   uRegVal |= (uI2cBusSDANoiseRejection << QUPE_SHFT(I2C_MASTER_CLK_CTL, SDA_NOISE_REJECTION) &
                                           QUPE_FMSK(I2C_MASTER_CLK_CTL, SDA_NOISE_REJECTION));

   uRegVal |= (uI2cBusSCLNoiseRejection << QUPE_SHFT(I2C_MASTER_CLK_CTL, SCL_NOISE_REJECTION) &
                                           QUPE_FMSK(I2C_MASTER_CLK_CTL, SCL_NOISE_REJECTION));

   QUPE_OUT(pQupAddr, I2C_MASTER_CLK_CTL, uRegVal);

   return HAL_QUPE_RESULT_SUCCESS;
}

/** @brief Issues bus clear cmd that is 9 clock cycles.
    @param[in]  pQupAddr index of the qup.
    @return Nothing.
  */
void
HAL_qupe_ClearI2CBus
(
   uint8  *pQupAddr
)
{
   QUPE_OUT(pQupAddr, I2C_MASTER_BUS_CLEAR, 1);
}

/** @brief Checks if bus is clear.
    @param[in]  pQupAddr index of the qup.
    @return Nothing.
  */
boolean
HAL_qupe_IsI2CBusClkForcedLow
(
   uint8  *pQupAddr
)
{
   uint32 uClkState, uBusActive, uOutFsmState, uI2cMasterReg;

   uI2cMasterReg = QUPE_IN(pQupAddr, I2C_MASTER_STATUS);

   uBusActive = (uI2cMasterReg &
         (QUPE_FMSK(I2C_MASTER_STATUS, BUS_ACTIVE))) >>
          QUPE_SHFT(I2C_MASTER_STATUS, BUS_ACTIVE);

   uOutFsmState = (uI2cMasterReg &
         (QUPE_FMSK(I2C_MASTER_STATUS, OUTPUT_FSM_STATE))) >>
          QUPE_SHFT(I2C_MASTER_STATUS, OUTPUT_FSM_STATE);

   uClkState = (uI2cMasterReg &
         (QUPE_FMSK(I2C_MASTER_STATUS, CLK_STATE))) >>
          QUPE_SHFT(I2C_MASTER_STATUS, CLK_STATE);

   return (
             (HAL_QUPE_I2C_CLOCK_FORCED_LOW_STATE == uClkState) &&
             (
                (HAL_QUPE_I2C_OUT_FSM_IDLE_STATE  == uOutFsmState) ||
                (HAL_QUPE_I2C_OUT_FSM_MIREC_STATE == uOutFsmState)
             )
          ) || (!uBusActive);
}

/** @brief Checks if bus is clear.
    @param[in]  pQupAddr index of the qup.
    @return Nothing.
  */
boolean
HAL_qupe_IsI2CBusBusy
(
   uint8  *pQupAddr
)
{
   uint32 uActiveField, uI2cMasterReg;

   uI2cMasterReg = QUPE_IN(pQupAddr, I2C_MASTER_STATUS);
   uActiveField  = (uI2cMasterReg &
                   (QUPE_FMSK(I2C_MASTER_STATUS, BUS_ACTIVE)) )>>
                   QUPE_SHFT(I2C_MASTER_STATUS, BUS_ACTIVE);

   return (boolean) uActiveField;
}

/** @brief Checks if bus state given by the pointer is clear.
    @param[in]  pI2cStatus  Pointer to i2c status stored with HAL_qupe_GetI2cState.
    @return TRUE if bus busy FALSE otherwise.
  */
boolean
HAL_qupe_IsI2CStateBusy
(
   HAL_qupe_I2cStatus  *pI2cStatus
)
{
   uint32 uActiveField, uI2cMasterReg;

   uI2cMasterReg = pI2cStatus->uRawStatus;
   uActiveField  = (uI2cMasterReg &
                   (QUPE_FMSK(I2C_MASTER_STATUS, BUS_ACTIVE)) )>>
                   QUPE_SHFT(I2C_MASTER_STATUS, BUS_ACTIVE);

   // since this is a stored state do extra checks

   return (boolean) (uActiveField ||
                     (!(uI2cMasterReg & QUPE_FMSK(I2C_MASTER_STATUS, I2C_SCL))) ||
                     (!(uI2cMasterReg & QUPE_FMSK(I2C_MASTER_STATUS, I2C_SDA)))
                    );
}

/** @brief Gets the state of the I2C.
    @param[in]  pQupAddr index of the qup.
    @param[out] pI2cStatus pointer to a location to store status struct.
    @return     Nothing.
  */
void
HAL_qupe_GetI2cState
(
   uint8               *pQupAddr,
   HAL_qupe_I2cStatus  *pI2cStatus
)
{
   HAL_QUPE_ASSERT(NULL == pI2cStatus);

   pI2cStatus->uRawStatus    = QUPE_IN(pQupAddr, I2C_MASTER_STATUS);
}

/** @brief Gets the data state of the I2C.
    @param[in]  pQupAddr index of the qup.
    @return     Data State
  */
uint32
HAL_qupe_GetI2cDataState
(
   uint8               *pQupAddr
)
{
   uint32 I2cDataState = 0;

   I2cDataState = (QUPE_IN(pQupAddr, I2C_MASTER_STATUS) &
                   QUPE_FMSK(I2C_MASTER_STATUS, DATA_STATE)) >>
                   QUPE_SHFT(I2C_MASTER_STATUS, DATA_STATE);

   return I2cDataState;
}

/** @brief Clears I2c errors.
    @param[in]  pQupAddr index of the qup.
    @param[in]  uErrMask error mask to clear.
    @return     Nothing.
  */
void
HAL_qupe_ClearI2cErrors
(
   uint8               *pQupAddr,
   uint32              uErrMask
)
{
   QUPE_OUT(pQupAddr,I2C_MASTER_STATUS,uErrMask);
}
