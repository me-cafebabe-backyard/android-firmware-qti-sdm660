#ifndef __VADCHAL_H__
#define __VADCHAL_H__
/*============================================================================
  @file VAdcHal.h

  Function and data structure declarations for VADC HAL


                Copyright (c) 2012, 2015 Qualcomm Technologies, Inc.
                All Rights Reserved.
                Qualcomm Technologies Proprietary and Confidential.
============================================================================*/
/* $Header: //components/rel/boot.xf/1.4/QcomPkg/Library/AdcLib/devices/vadc/src/VAdcHal.h#2 $ */

/*-------------------------------------------------------------------------
 * Include Files
 * ----------------------------------------------------------------------*/
#include "com_dtypes.h"

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * ----------------------------------------------------------------------*/
#define VADC_REVISION(major, minor) (((major) << 8) | (minor))

#define VADC_INVALID_ADC_CODE 0x8000

#define VADC_INT_MASK_EOC                 0x1
#define VADC_INT_MASK_VBAT_MIN_THRESHOLD  0x2

#define VADC_HAL_NUM_REGISTERS_TO_DUMP 29

/*-------------------------------------------------------------------------
 * Type Declarations
 * ----------------------------------------------------------------------*/
typedef enum
{
   VADC_HAL_SUCCESS = 0,
   VADC_HAL_ERROR
} VAdcHalResultType;

typedef struct
{
   uint16 usDigitalRev;
   uint16 usAnalogRev;
   uint8 ucType;
   uint8 ucSubType;
} VAdcRevisionInfoType;

typedef enum
{
   VADC_CONVERSION_STATUS_INVALID = 0,
   VADC_CONVERSION_STATUS_COMPLETE,
   VADC_CONVERSION_STATUS_PENDING,
   VADC_CONVERSION_STATUS_WAITING
} VAdcConversionStatusType;

typedef enum
{
   VADC_CONVERSION_STATE_IDLE = 0,
   VADC_CONVERSION_STATE_WAIT_HOLDOFF_RST,
   VADC_CONVERSION_STATE_WAIT_HOLDOFF,
   VADC_CONVERSION_STATE_RST_CH_ARB,
   VADC_CONVERSION_STATE_GET_NEXT_CH,
   VADC_CONVERSION_STATE_WAIT_CAL,
   VADC_CONVERSION_STATE_WAIT_ADC_EOC,
   VADC_CONVERSION_STATE_GET_IRQ
} VAdcConversionStateType;

typedef struct
{
   VAdcConversionStatusType eConversionStatus;
   VAdcConversionStateType eConversionState;
} VAdcStatusType;

typedef enum
{
   VADC_INTERRUPT_CONFIG_LEVEL_HIGH = 0,
   VADC_INTERRUPT_CONFIG_LEVEL_LOW,
   VADC_INTERRUPT_CONFIG_RISING_EDGE,
   VADC_INTERRUPT_CONFIG_FALLING_EDGE
} VAdcInterruptConfigType;

typedef enum
{
   VADC_CAL_METHOD_NO_CAL = 0,
   VADC_CAL_METHOD_RATIOMETRIC,
   VADC_CAL_METHOD_ABSOLUTE
} VAdcCalMethodType;

typedef enum
{
   VADC_DECIMATION_RATIO_256 = 0,
   VADC_DECIMATION_RATIO_512,
   VADC_DECIMATION_RATIO_1024
} VAdcDecimationRatioType;

typedef enum
{
   VADC_AVERAGE_1_SAMPLE = 0,
   VADC_AVERAGE_2_SAMPLES,
   VADC_AVERAGE_4_SAMPLES,
   VADC_AVERAGE_8_SAMPLES,
   VADC_AVERAGE_16_SAMPLES
} VAdcAverageModeType;

typedef enum
{
   VADC_SETTLING_DELAY_0_US = 0,
   VADC_SETTLING_DELAY_100_US,
   VADC_SETTLING_DELAY_200_US,
   VADC_SETTLING_DELAY_300_US,
   VADC_SETTLING_DELAY_400_US,
   VADC_SETTLING_DELAY_500_US,
   VADC_SETTLING_DELAY_600_US,
   VADC_SETTLING_DELAY_700_US,
   VADC_SETTLING_DELAY_800_US,
   VADC_SETTLING_DELAY_900_US,
   VADC_SETTLING_DELAY_1_MS,
   VADC_SETTLING_DELAY_2_MS,
   VADC_SETTLING_DELAY_4_MS,
   VADC_SETTLING_DELAY_6_MS,
   VADC_SETTLING_DELAY_8_MS,
   VADC_SETTLING_DELAY_10_MS
} VAdcSettlingDelay;

typedef struct
{
   uint32 uChannel;
   VAdcCalMethodType eCalMethod;
   VAdcDecimationRatioType eDecimationRatio;
   VAdcAverageModeType eAverageMode;
   VAdcSettlingDelay eSettlingDelay;
} VAdcConversionParametersType;

typedef enum
{
   VADC_DISABLE = 0,
   VADC_ENABLE
} VAdcEnableType;

typedef struct
{
   uint8 ucOffset;
   uint8 ucVal;
} VAdcHalRegType;

typedef struct
{
   VAdcHalRegType aVAdcReg[VADC_HAL_NUM_REGISTERS_TO_DUMP];
} VAdcHalRegDumpType;

typedef struct
{
   void *pCtxt;
   VAdcHalResultType (*pfnWriteBytes)(void *pCtxt, uint32 uRegisterAddress, uint8 *pucData, uint32 uDataLen);
   VAdcHalResultType (*pfnReadBytes)(void *pCtxt, uint32 uRegisterAddress, uint8 *pucData, uint32 uDataLen);
} VAdcHalInterfaceType;

/*-------------------------------------------------------------------------
 * Function Declarations and Documentation
 * ----------------------------------------------------------------------*/
VAdcHalResultType VAdcHalGetRevisionInfo(VAdcHalInterfaceType *piVAdcHal, VAdcRevisionInfoType *pRevisionInfo);
VAdcHalResultType VAdcHalGetStatus(VAdcHalInterfaceType *piVAdcHal, VAdcStatusType *pStatus);
VAdcHalResultType VAdcHalConfigInterrupts(VAdcHalInterfaceType *piVAdcHal, uint8 ucIntrMask, VAdcInterruptConfigType eConfig);
VAdcHalResultType VAdcHalGetPendingInterrupts(VAdcHalInterfaceType *piVAdcHal, uint8 *pucIntrMask);
VAdcHalResultType VAdcHalClearInterrupts(VAdcHalInterfaceType *piVAdcHal, uint8 ucIntrMask);
VAdcHalResultType VAdcHalEnableInterrupts(VAdcHalInterfaceType *piVAdcHal, uint8 ucIntrMask);
VAdcHalResultType VAdcHalSetInterruptMid(VAdcHalInterfaceType *piVAdcHal, uint32 uIntrMid);
VAdcHalResultType VAdcHalSetEnable(VAdcHalInterfaceType *piVAdcHal, VAdcEnableType eEnable);
VAdcHalResultType VAdcHalRequestConversion(VAdcHalInterfaceType *piVAdcHal, VAdcConversionParametersType *pParams, uint32 *puConvTimeUs);
VAdcHalResultType VAdcHalGetConversionCode(VAdcHalInterfaceType *piVAdcHal, uint32 *puCode);
VAdcHalResultType VAdcHalDumpRegisters(VAdcHalInterfaceType *piVAdcHal, VAdcHalRegDumpType *pVAdcRegDump);

#endif /* #ifndef __VADCHAL_H__ */

