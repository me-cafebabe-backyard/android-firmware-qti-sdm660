/*
===========================================================================

FILE:   I2CConfig.c

DESCRIPTION:

        This file contains the implementation of the APIs for configuration

===========================================================================

Edit History


When     Who    What, where, why
-------- ---    -----------------------------------------------------------
02/01/17 vg     Copyright updated
10/27/14 unr    Fix undefined reference to DALREG_DriverInfo in XBL Loader
08/27/14 vk     Warning clean
01/23/13 unr    Initial Version

===========================================================================
    Copyright (c) 2011-2017 Qualcomm Technologies, Incorporated.
                        All rights reserved.
    Qualcomm Technologies, Confidential and Proprietary.

===========================================================================*/

#include "I2cSys.h"
#include "I2CConfig.h"
#include "I2cPlatLog.h"
#include "I2cSys.h"

const DALREG_DriverInfo DALI2C_DriverInfo =
{
    NULL,
    0,
    NULL
};

DALResult I2CDeviceGetConfig (
    void *hConfigHandle,
    I2CDeviceConfigType *pDeviceConfig
    )
{
    DALSYS_PROPERTY_HANDLE_DECLARE(hProp);
    DALSYSPropertyVar PropVar;
    DALResult result = DAL_ERROR;
    UINT32 DALID = 0;

    if (pDeviceConfig == NULL)
    {
        I2C_CONFIG_LOG(0, "I2C invalid device config place holder");
        return DAL_ERROR;
    }

    I2CSYS_Memset(pDeviceConfig, 0, sizeof(I2CDeviceConfigType));

    pDeviceConfig->hConfigHandle = hConfigHandle;

    DALID = (UINT32) (UINTN) hConfigHandle;

    //
    // Get DAL Config Handle
    //

    if ((result = DALSYS_GetDALPropertyHandle(DALID, hProp)) != DAL_SUCCESS)
    {
        I2C_CONFIG_LOG(0, "I2C fail to get property handle");
        return result;
    }

    //
    // Core Index
    //

    if ((result = DALSYS_GetPropertyValue (hProp, "CHIP_BUS_INDEX", 0, &PropVar)) != DAL_SUCCESS)
    {
        I2C_CONFIG_LOG(0, "I2C fail to get chip bus index");
        pDeviceConfig->uCoreIndex = 0;
    }
    else
    {
        pDeviceConfig->uCoreIndex = PropVar.Val.dwVal;
    }

    //
    // GPIOs
    //

    if ((result = DALSYS_GetPropertyValue (hProp, "CHIP_GPIO_CONFIG_ARR", 0, &PropVar)) != DAL_SUCCESS)
    {
        I2C_CONFIG_LOG(0, "I2C fail to get gpio array");
        pDeviceConfig->bHasGpios = 0;
    }
    else
    {
        pDeviceConfig->bHasGpios = 1;
        pDeviceConfig->aGpioCfg[0] = PropVar.Val.pdwVal[0];
        pDeviceConfig->aGpioCfg[1] = PropVar.Val.pdwVal[1];
    }

    //
    // Clocks
    //

    // APP CLK
    if ((result = DALSYS_GetPropertyValue (hProp, "CHIP_APP_CLK_NAME", 0, &PropVar)) != DAL_SUCCESS)
    {
        I2C_CONFIG_LOG(0, "I2C fail to get app clk name");
        return result;
    }
    pDeviceConfig->pQupAppClkName = PropVar.Val.pszVal;

    // HCLK
    if ((result = DALSYS_GetPropertyValue (hProp, "CHIP_HCLK_NAME", 0, &PropVar)) != DAL_SUCCESS)
    {
        I2C_CONFIG_LOG(0, "I2C fail to get hclk name");
        return result;
    }
    pDeviceConfig->pQupHClkName = PropVar.Val.pszVal;

    // APP CLK Frequency
    if ((result = DALSYS_GetPropertyValue (hProp, "CHIP_APP_CLK_FREQ_KHZ", 0, &PropVar)) != DAL_SUCCESS)
    {
        I2C_CONFIG_LOG(0, "I2C fail to get app clk frequency");
        return result;
    }
    pDeviceConfig->uAppClkFreqKhz = PropVar.Val.dwVal;

    //
    // Core Configuration
    //

    // Interrupts
    if ((result = DALSYS_GetPropertyValue (hProp, "SW_USE_POLLING_MODE", 0, &PropVar)) != DAL_SUCCESS)
    {
        I2C_CONFIG_LOG(0, "I2C fail to get polling mode");
        return result;
    }
    pDeviceConfig->bInterruptBased = ((uint32)PropVar.Val.dwVal == 1) ? 0:1;

    if (pDeviceConfig->bInterruptBased)
    {
        if ((result = DALSYS_GetPropertyValue (hProp, "CHIP_IRQ_ID", 0, &PropVar)) != DAL_SUCCESS)
        {
            I2C_CONFIG_LOG(0, "I2C fail to get interrupt id");
            return result;
        }
        pDeviceConfig->uInterruptId = (uint32) PropVar.Val.dwVal;

        if ((result = DALSYS_GetPropertyValue (hProp, "CHIP_IRQ_TRIGGER_CFG", 0, &PropVar)) != DAL_SUCCESS)
        {
            I2C_CONFIG_LOG(0, "I2C fail to get interrupt trigger config");
            return result;
        }
        pDeviceConfig->uIrqTriggerCfg = (uint32)PropVar.Val.dwVal;
    }

    // Device Name
    if ((result = DALSYS_GetPropertyValue (hProp, "SW_DEVICE_NAME", 0, &PropVar)) != DAL_SUCCESS)
    {
        I2C_CONFIG_LOG(0, "I2C fail to get sw device name");
        return result;
    }
    pDeviceConfig->pDevName = PropVar.Val.pszVal;

    // CHIP Base
    if (NULL == pDeviceConfig->pPeriphSsAddrName)
    {
        if ((result = DALSYS_GetPropertyValue (hProp, "CHIP_PERIPH_SS_BASE_NAME", 0, &PropVar)) != DAL_SUCCESS)
        {
            I2C_CONFIG_LOG(0, "I2C fail to get periph ss name");
            return result;
        }
        pDeviceConfig->pPeriphSsAddrName = PropVar.Val.pszVal;
    }

    if ((result = DALSYS_GetPropertyValue (hProp, "CHIP_PERIPH_SS_BASE", 0, &PropVar)) != DAL_SUCCESS)
    {
        I2C_CONFIG_LOG(0, "I2C fail to get qup base address");
        pDeviceConfig->pPeriphSsAddr = NULL;
    }
    else
    {
        pDeviceConfig->pPeriphSsAddr = (char *) PropVar.Val.dwVal;
    }

    if ((result = DALSYS_GetPropertyValue (hProp, "CHIP_BLOCK_OFFSET", 0, &PropVar)) != DAL_SUCCESS)
    {
        I2C_CONFIG_LOG(0, "I2C fail to get block offset");
        return result;
    }
    pDeviceConfig->uQupBlockOffset = PropVar.Val.dwVal;

    // BAM
    if ((result = DALSYS_GetPropertyValue (hProp, "SW_USE_BAM", 0, &PropVar)) != DAL_SUCCESS)
    {
        I2C_CONFIG_LOG(0, "I2C fail to get bam settings");
        pDeviceConfig->bBamEnabled = 0;
    }
    else
    {
        pDeviceConfig->bBamEnabled = (uint32) PropVar.Val.dwVal;
    }

    if (pDeviceConfig->bBamEnabled)
    {
        if ((result = DALSYS_GetPropertyValue (hProp, "CHIP_BAM_PHYS_ADDR", 0, &PropVar)) != DAL_SUCCESS)
        {
            I2C_CONFIG_LOG(0, "I2C fail to get bam physical address");
            return result;
        }
        pDeviceConfig->uBamPhysAddr = (uint32) PropVar.Val.dwVal;

        if ((result = DALSYS_GetPropertyValue (hProp, "CHIP_BAM_INTRERRUPT_ID", 0, &PropVar)) != DAL_SUCCESS)
        {
            I2C_CONFIG_LOG(0, "I2C fail to get bam interrupt id");
            return result;
        }
        pDeviceConfig->uBamIrqId = (uint32) PropVar.Val.dwVal;

        if ((result = DALSYS_GetPropertyValue (hProp, "SW_BAM_THRESHOLD", 0, &PropVar)) != DAL_SUCCESS)
        {
            I2C_CONFIG_LOG(0, "I2C fail to get bam threshold");
            return result;
        }
        pDeviceConfig->uBamThreshold = (uint32) PropVar.Val.dwVal;

        if ((result = DALSYS_GetPropertyValue (hProp, "CHIP_QUP_INPUT_BAM_PIPE_NUM", 0, &PropVar)) != DAL_SUCCESS)
        {
            I2C_CONFIG_LOG(0, "I2C fail to get bam input pipe");
            return result;
        }
        pDeviceConfig->uBamInPipeId = (uint32) PropVar.Val.dwVal;

        if ((result = DALSYS_GetPropertyValue (hProp, "CHIP_QUP_OUTPUT_BAM_PIPE_NUM", 0, &PropVar)) != DAL_SUCCESS)
        {
            I2C_CONFIG_LOG(0, "I2C fail to get bam output pipe");
            return result;
        }
        pDeviceConfig->uBamOutPipeId = (uint32) PropVar.Val.dwVal;
    }

    // Other
    if ((result = DALSYS_GetPropertyValue (hProp, "SW_DISABLE_PM", 0, &PropVar)) != DAL_SUCCESS)
    {
        I2C_CONFIG_LOG(0, "I2C fail to get power management mode");
        return result;
    }
    pDeviceConfig->bDisablePm = (uint32) PropVar.Val.dwVal;

    return DAL_SUCCESS;
}
