#ifndef _I2CPLATSVCTYPES_H_
#define _I2CPLATSVCTYPES_H_
/*=============================================================================

  @file   I2cPlatSvcTypes.h

   This file contains the types for the platform services.
 
   Copyright (c) 2011-2016 Qualcomm Technologies, Incorporated.
                  All rights reserved.
   Qualcomm Technologies, Confidential and Proprietary.
=============================================================================*/
/*=============================================================================
                             EDIT HISTORY FOR MODULE
  ===========================================================================
  
 $Header: //components/rel/core.qdsp6/1.0.c2/buses/i2c/src/drv/I2cPlatSvcTypes.h#1 $ 

When     Who    What, where, why
-------- ---    -----------------------------------------------------------
10/14/16 VG     Updated the Copy Rights
09/27/16 VG     Removed the commented code
=============================================================================*/
/*-------------------------------------------------------------------------
 * Include Files
 * ----------------------------------------------------------------------*/

#include "I2cTypes.h"
#include "I2cError.h"
#include "uClock.h"

/*-------------------------------------------------------------------------
 * Type Declarations
 * ----------------------------------------------------------------------*/

typedef enum I2cPlat_Error
{
   I2CPLAT_ERROR_BASE = I2C_RES_ERROR_CLS_DEV_PLATFORM,
   
   I2CPLAT_ERROR_INVALID_DEVICE_INDEX,
   I2CPLAT_ERROR_DAL_GET_PROPERTY_HANDLE,
   I2CPLAT_ERROR_DAL_GET_PROPERTY_VALUE,
   I2CPLAT_ERROR_ATTACH_TO_DALHWIO     ,
   I2CPLAT_ERROR_FAILED_TO_MAP_BLOCK_HWIO     ,
   I2CPLAT_ERROR_DETACH_FROM_DALHWIO,
   I2CPLAT_ERROR_INVALID_POWER_STATE,
   I2CPLAT_ERROR_FAILED_TO_ATTACH_TO_TLMM,
   I2CPLAT_ERROR_FAILED_TO_DETTACH_FROM_TLMM,
   I2CPLAT_ERROR_FAILED_TO_OPEN_TLMM,
   I2CPLAT_ERROR_FAILED_TO_CLOSE_TLMM,
   I2CPLAT_ERROR_FAILED_TO_CONFIGURE_GPIO,
   I2CPLAT_ERROR_FAILED_TO_ENABLE_CLOCK,
   I2CPLAT_ERROR_FAILED_TO_DISABLE_CLOCK,
   I2CPLAT_ERROR_FAILED_TO_CREATE_PNOC_CLIENT,
   I2CPLAT_ERROR_PNOC_CLIENT_NOT_CREATED,
   I2CPLAT_ERROR_FAILED_TO_ENABLE_AHB_CLK,
   I2CPLAT_ERROR_FAILED_TO_ENABLE_APPS_CLK,
   I2CPLAT_ERROR_FAILED_TO_DISABLE_AHB_CLK,
   I2CPLAT_ERROR_FAILED_TO_DISABLE_APPS_CLK,
   I2CPLAT_ERROR_FAILED_TO_ISSUE_PNOC_REQ,
   
} I2cPlat_Error;

typedef enum I2cPlat_PowerStates
{
   I2CPLAT_POWER_STATE_0,/**< Bus and clocks off. */
   I2CPLAT_POWER_STATE_1,/**< Bus on clocks off. */
   I2CPLAT_POWER_STATE_2,/**< Bus on clocks on. */
} I2cPlat_PowerStates;

typedef enum I2cPlat_TargetInitState
{
   I2CPLAT_TGT_INIT_NOT_DONE = 0,
   //I2CPLAT_TGT_INIT_CLK_ALLOCATED  = 0x01,
   I2CPLAT_TGT_INIT_HWIO_ALLOCATED = 0x01,
   I2CPLAT_TGT_INIT_GPIO_INITED    = 0x02,
   I2CPLAT_TGT_INIT_PNOC_INITED    = 0x04,
   I2CPLAT_TGT_INIT_HWIO_INITED    = 0x20,

} I2cPlat_TargetInitState;

typedef struct I2cPlat_PropertyType
{
   uint32                aGpioCfg[2];
   uint32                uNumGpios;
   const char*           pPeriphSsAddrName;
   uint32                coreOffset;
   uClockIdType           QupHClkId;
   uClockIdType           QupAppClkId;
} I2cPlat_PropertyType ;


typedef struct I2cPlat_DescType
{
   uint32                        tmpPowerState;
   I2cPlat_TargetInitState       initState;
   uint8                         *pQupAddr;
   I2cPlat_PropertyType          props;
} I2cPlat_DescType;

#define I2CPLAT_DESC_INIT                                        \
{                                                                \
  /* .tmpPowerState = */        0,                               \
  /* initState      = */        I2CPLAT_TGT_INIT_NOT_DONE,       \
  /* qQupAddr       = */        NULL,                            \
  /* props          = */        {0,{0,0},0,NULL},                \
}                                                                \

#endif /* _I2CPLATSVCTYPES_H_ */

