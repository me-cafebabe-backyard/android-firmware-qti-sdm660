/*
===========================================================================

FILE:   I2CConfig.h

DESCRIPTION:
    This file contains the implementation of the APIs for configuration

===========================================================================

        Edit History


When     Who    What, where, why
-------- ---    -----------------------------------------------------------
02/01/17 vg     Copyright updated
01/23/13 unr    Initial Version

===========================================================================
    Copyright (c) 2011-2017 Qualcomm Technologies, Incorporated.
                        All rights reserved.
    Qualcomm Technologies, Confidential and Proprietary.

===========================================================================*/

#ifndef _I2CCONFIG_H_
#define _I2CCONFIG_H_

#include "DALStdDef.h"
#include "DALDeviceId.h"
#include "DALSys.h"
#include "DDIHWIO.h"

typedef struct I2CDeviceConfigType
{
    void                       *hConfigHandle;
    uint32                      uCoreIndex;
    char                       *pDevName;
    char                       *pPeriphSsAddrName;
    char                       *pPeriphSsAddr;
    uint32                      uQupBlockOffset;

    char                       *pQupHClkName;
    char                       *pQupAppClkName;

    uint32                      uAppClkFreqKhz;

    boolean                     bHasGpios;
    uint32                      aGpioCfg[2];

    boolean                     bInterruptBased;
    uint32                      uInterruptId;
    uint32                      uIrqTriggerCfg;

    boolean                     bBamEnabled;
    uint32                      uBamPhysAddr;
    uint32                      uBamIrqId;
    uint32                      uBamThreshold;
    uint32                      uBamInPipeId;
    uint32                      uBamOutPipeId;

    boolean                     bDisablePm;

} I2CDeviceConfigType;

/** @brief Gets Device Configuration

    This function gets the DAL device configuration for the I2C driver

    @param[in] hConfigHandle    Handle to the DAL Device
    @param[in] pDeviceConfig    Pointer to stor configuration

    @return DALResult
  */
DALResult I2CDeviceGetConfig (
    void *hConfigHandle,
    I2CDeviceConfigType *pDeviceConfig
    );

#endif /* _I2CCONFIG_H_ */
