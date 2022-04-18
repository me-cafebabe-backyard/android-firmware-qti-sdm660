/*============================================================================
  FILE:         HALtsensFuses.c

  OVERVIEW:     Implementation of the TSENS HAL for reading fuses

  DEPENDENCIES: None

                Copyright (c) 2016 Qualcomm Technologies, Inc.
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary.
============================================================================*/
/*============================================================================
  EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.  Please
  use ISO format for dates.

  when        who  what, where, why
  ----------  ---  -----------------------------------------------------------
  2016-09-29  SA   Updated for SDM660.
  2016-04-12  jjo  Add truncated offsets.
  2016-03-07  jjo  Initial revision.

============================================================================*/
/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "HALhwio.h"
#include "HALhwioTsensFuses.h"
#include "HALtsens.h"
#include "msmhwiobase.h"

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Static Function Declarations
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Global Data Definitions
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Static Variable Definitions
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Static Function Declarations and Definitions
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Externalized Function Definitions
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Char data
 * -------------------------------------------------------------------------*/
/* ============================================================================
**
**  HAL_tsens_UseRedundant
**
**  Description:
**    Whether or not to use the redundant region
**
**  Parameters:
**    None
**
**  Return: FALSE
**
**  Dependencies: None
**
** ========================================================================= */
boolean HAL_tsens_UseRedundant(void)
{
   return FALSE;
}

/* ============================================================================
**
**  HAL_tsens_CalSelect
**
**  Description:
**    Determines whether there is 1) no cal data 2) single point cal data or
**    3) two point cal data
**
**  Parameters:
**    bUseRedundant - whether or not to use the redundant location
**
**  Return: HAL_tsens_Calibration (not calibrated, one point, or two point)
**
**  Dependencies: None
**
** ========================================================================= */
HAL_tsens_Calibration HAL_tsens_CalSelect(boolean bUseRedundant)
{
   /* TSENS_CAL_SEL
    * 0: not calibrated
    * 1: 2 point truncated; 1 offset bit == 8 codes
    * 2: 1 point
    * 3: 2 point
    * 4: 2 point (future method compatible with 3)
    * 5: 2 point (future method compatible with 3)
    * 6: new method
    * 7: new method
    */
   if (!bUseRedundant)
   {
      switch (HWIO_INF(QFPROM_CORR_CALIB_ROW12_MSB, TSENS_CAL_SEL))
      {
         case 1:
            return HAL_TSENS_CAL_TWO_POINT_TRUNCATED;
         case 2:
            return HAL_TSENS_CAL_ONE_POINT;
         case 3:
            return HAL_TSENS_CAL_TWO_POINT;
         case 4:
            return HAL_TSENS_CAL_TWO_POINT;
         case 5:
            return HAL_TSENS_CAL_TWO_POINT;
         default:
            return HAL_TSENS_CAL_NOT_CALIBRATED;
      }
   }

   return HAL_TSENS_CAL_NOT_CALIBRATED;
}

/* ============================================================================
**
**  HAL_tsens_PartialGoodsEnabled
**
**  Description:
**    Determines whether or not partial goods encoding has been enabled
**
**  Parameters:
**    bUseRedundant - whether or not to use the redundant location
**
**  Return: TRUE / FALSE
**
**  Dependencies: None
**
** ========================================================================= */
boolean HAL_tsens_PartialGoodsEnabled(boolean bUseRedundant)
{
   return FALSE;
}

/* ============================================================================
**
**  HAL_tsens_GetBase1
**
**  Description:
**    Gets the Tsens base for cal point 1
**
**  Parameters:
**    bUseRedundant - whether or not to use the redundant location
**    uController - which controller
**
**  Return: adc code
**
**  Dependencies: None
**
** ========================================================================= */
uint32 HAL_tsens_GetBase1(boolean bUseRedundant, uint32 uController)
{
   if (!bUseRedundant)
   {
      switch (uController)
      {
         case 0:
            return HWIO_INF(QFPROM_CORR_CALIB_ROW11_MSB, TSENS0_BASE0);
         default:
            break;
      }
   }

   return 0;
}

/* ============================================================================
**
**  HAL_tsens_GetBase2
**
**  Description:
**    Gets the Tsens base for cal point 2
**
**  Parameters:
**    bUseRedundant - whether or not to use the redundant location
**    uController - which controller
**
**  Return: adc code
**
**  Dependencies: None
**
** ========================================================================= */
uint32 HAL_tsens_GetBase2(boolean bUseRedundant, uint32 uController)
{
   if (!bUseRedundant)
   {
      switch (uController)
      {
         case 0:
            return HWIO_INF(QFPROM_CORR_CALIB_ROW11_MSB, TSENS0_BASE1);
         default:
            break;
      }
   }

   return 0;
}

/* ============================================================================
**
**  HAL_tsens_GetOffset1
**
**  Description:
**    Gets Tsens uSensor offset for cal point 1
**
**  Parameters:
**    bUseRedundant - whether or not to use the redundant location
**    uint32 uFuseIdx
**
**  Return: offset from base
**
**  Dependencies: None
**
** ========================================================================= */
uint32 HAL_tsens_GetOffset1(boolean bUseRedundant, uint32 uFuseIdx)
{
   if (!bUseRedundant)
   {
      switch (uFuseIdx)
      {
         case 0:
            return HWIO_INF(QFPROM_CORR_CALIB_ROW11_MSB, TSENS0_OFFSET);
         case 1:
            return HWIO_INF(QFPROM_CORR_CALIB_ROW11_MSB, TSENS1_OFFSET);
         case 2:
            return HWIO_INF(QFPROM_CORR_CALIB_ROW11_MSB, TSENS2_OFFSET);
         case 3:
            return HWIO_INF(QFPROM_CORR_CALIB_ROW12_LSB, TSENS3_OFFSET);
         case 4:
            return HWIO_INF(QFPROM_CORR_CALIB_ROW12_LSB, TSENS4_OFFSET);
         case 5:
            return HWIO_INF(QFPROM_CORR_CALIB_ROW12_LSB, TSENS5_OFFSET);
         case 6:
            return HWIO_INF(QFPROM_CORR_CALIB_ROW12_LSB, TSENS6_OFFSET);
         case 7:
            return HWIO_INF(QFPROM_CORR_CALIB_ROW12_LSB, TSENS7_OFFSET);
         case 8:
            return HWIO_INF(QFPROM_CORR_CALIB_ROW12_LSB, TSENS8_OFFSET);
         case 9:
            return HWIO_INF(QFPROM_CORR_CALIB_ROW12_LSB, TSENS9_OFFSET);
         case 10:
            return HWIO_INF(QFPROM_CORR_CALIB_ROW12_LSB, TSENS10_OFFSET);
         case 11:
            return HWIO_INF(QFPROM_CORR_CALIB_ROW12_MSB, TSENS11_OFFSET);
         case 12:
            return HWIO_INF(QFPROM_CORR_CALIB_ROW12_MSB, TSENS12_OFFSET);
         case 13:
            return HWIO_INF(QFPROM_CORR_CALIB_ROW12_MSB, TSENS13_OFFSET);
         default:
            break;
      }
   }

   return 0;
}

/* ============================================================================
**
**  HAL_tsens_GetOffset2
**
**  Description:
**    Gets Tsens uSensor offset for cal point 2
**
**  Parameters:
**    bUseRedundant - whether or not to use the redundant location
**    uint32 uFuseIdx
**
**  Return: offset from base
**
**  Dependencies: None
**
** ========================================================================= */
uint32 HAL_tsens_GetOffset2(boolean bUseRedundant, uint32 uFuseIdx)
{
   return 0;
}

