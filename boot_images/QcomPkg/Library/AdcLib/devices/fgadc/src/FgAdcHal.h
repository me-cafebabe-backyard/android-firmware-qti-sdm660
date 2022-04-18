#ifndef __FGADCHAL_H__
#define __FGADCHAL_H__
/*============================================================================
  @file FgAdcHal.h

  Function and data structure declarations for FG ADC HAL


                Copyright (c) 2016-2017 Qualcomm Technologies, Inc.
                All Rights Reserved.
                Qualcomm Technologies Proprietary and Confidential.
============================================================================*/
/* $Header: //components/rel/boot.xf/1.4/QcomPkg/Library/AdcLib/devices/fgadc/src/FgAdcHal.h#4 $ */

/*-------------------------------------------------------------------------
 * Include Files
 * ----------------------------------------------------------------------*/
#include "com_dtypes.h"

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * ----------------------------------------------------------------------*/
/* These triggers should be ORed together */
#define FGADC_TRIGGER_DEFAULT      0
#define FGADC_TRIGGER_SLEEP        (1 << 0)
#define FGADC_TRIGGER_RFU          (1 << 1)
#define FGADC_TRIGGER_DTEST        (1 << 2)
#define FGADC_TRIGGER_BCL_HPM      (1 << 3)
#define FGADC_TRIGGER_OTG          (1 << 4)
#define FGADC_TRIGGER_DCIN         (1 << 5)
#define FGADC_TRIGGER_USB          (1 << 6)
#define FGADC_TRIGGER_EVERY_CYCLE  (1 << 7)

#define FGADC_HAL_NUM_REGISTERS_TO_DUMP 132

/*-------------------------------------------------------------------------
 * Type Declarations
 * ----------------------------------------------------------------------*/
typedef enum
{
   FGADC_CHAN_SKIN_TEMP = 0,
   FGADC_CHAN_BATT_ID,
   FGADC_CHAN_BATT_ID_FRESH,
   FGADC_CHAN_BATT_ID_5,
   FGADC_CHAN_BATT_ID_15,
   FGADC_CHAN_BATT_ID_150,
   FGADC_CHAN_BATT_THERM,
   FGADC_CHAN_AUX_THERM,
   FGADC_CHAN_USB_IN_V,
   FGADC_CHAN_USB_IN_I,
   FGADC_CHAN_DC_IN_V,
   FGADC_CHAN_DC_IN_I,
   FGADC_CHAN_DIE_TEMP,
   FGADC_CHAN_CHARGER_TEMP,
   FGADC_CHAN_GPIO
} FcAdcChannelType;

typedef enum
{
   FGADC_THRESH_SKIN_HOT = 0,
   FGADC_THRESH_SKIN_TOO_HOT,
   FGADC_THRESH_CHARGER_HOT,
   FGADC_THRESH_CHARGER_TOO_HOT
} FgAdcThresholdType;

typedef enum
{
   FGADC_HAL_SUCCESS = 0,
   FGADC_HAL_ERROR
} FgAdcHalResultType;

typedef struct
{
   uint8 ucType;
   uint8 ucSubType;
} FgAdcRevisionInfoType;

typedef enum
{
   FGADC_DISABLE = 0,
   FGADC_ENABLE
} FgAdcEnableType;

typedef enum
{
   FGADC_SHDN_NOT_REQUESTED = 0,
   FGADC_SHDN_REQUESTED
} FgAdcShdnType;

typedef struct
{
   boolean bReadingAvailable;
   boolean bReadingFresh;
} FgAdcChanStatusType;

typedef struct
{
   uint8 ucOffset;
   uint8 ucVal;
} FgAdcHalRegType;

typedef struct
{
   FgAdcHalRegType aFgAdcReg[FGADC_HAL_NUM_REGISTERS_TO_DUMP];
} FgAdcHalRegDumpType;

typedef struct
{
   void *pCtxt;
   FgAdcHalResultType (*pfnWriteBytes)(void *pCtxt, uint32 uRegisterAddress, uint8 *pucData, uint32 uDataLen);
   FgAdcHalResultType (*pfnReadBytes)(void *pCtxt, uint32 uRegisterAddress, uint8 *pucData, uint32 uDataLen);
} FgAdcHalInterfaceType;

/*-------------------------------------------------------------------------
 * Function Declarations and Documentation
 * ----------------------------------------------------------------------*/
FgAdcHalResultType FgAdcHalGetRevisionInfo(FgAdcHalInterfaceType *piFgAdcHal, FgAdcRevisionInfoType *pRevisionInfo);
FgAdcHalResultType FgAdcHalSetEnable(FgAdcHalInterfaceType *piFgAdcHal, FgAdcEnableType eEnable);
FgAdcHalResultType FgAdcHalSetShutdown(FgAdcHalInterfaceType *piFgAdcHal, FgAdcShdnType eShutdown);
FgAdcHalResultType FgAdcHalSetChanEn(FgAdcHalInterfaceType *piFgAdcHal, FcAdcChannelType eChannel, FgAdcEnableType eEnable);
FgAdcHalResultType FgAdcHalMakeSwReq(FgAdcHalInterfaceType *piFgAdcHal);
FgAdcHalResultType FgAdcHalGetChanTrigs(FgAdcHalInterfaceType *piFgAdcHal, FcAdcChannelType eChannel, uint8 *pucTriggers);
FgAdcHalResultType FgAdcHalSetChanTrigs(FgAdcHalInterfaceType *piFgAdcHal, FcAdcChannelType eChannel, uint8 ucTriggers);
FgAdcHalResultType FgAdcHalGetChanStatus(FgAdcHalInterfaceType *piFgAdcHal, FcAdcChannelType eChannel, FgAdcChanStatusType *pStatus);
FgAdcHalResultType FgAdcHalGetConversionCode(FgAdcHalInterfaceType *piFgAdcHal, FcAdcChannelType eChannel, uint32 *puCode);
FgAdcHalResultType FgAdcHalSetThreshold(FgAdcHalInterfaceType *piFgAdcHal, FgAdcThresholdType eThresh, uint32 uCode);
FgAdcHalResultType FgAdcHalClearThresholdComparison(FgAdcHalInterfaceType *piFgAdcHal, FgAdcThresholdType eThresh);
FgAdcHalResultType FgAdcHalDumpRegisters(FgAdcHalInterfaceType *piFgAdcHal, FgAdcHalRegDumpType *pFgAdcRegDump);
FgAdcHalResultType FgAdcHalSetContModeEn(FgAdcHalInterfaceType *piFgAdcHal, FgAdcEnableType eEnable);

#endif /* #ifndef __FGADCHAL_H__ */

