#ifndef _SPIDEVICEPLATSVC_H_
#define _SPIDEVICEPLATSVC_H_
/*
===========================================================================

FILE:   SpiDevicePlatSvc.h

DESCRIPTION:
    This file contains the API for the platform services.

===========================================================================

        Edit History

$Header: //components/rel/core.qdsp6/1.0.c2/buses/spi/src/device/inc/SpiDevicePlatSvc.h#1 $

When       Who      What, where, why
--------   ---      -----------------------------------------------------------
11/01/16   ska      Added members for ALT CS in SpiGpioCfg_s Struct
07/16/15   vmk      Added clk control
04/10/13   vmk      Initial version.
===========================================================================
        Copyright c 2013-16 Qualcomm Technologies Incorporated.
            All Rights Reserved.
            Qualcomm Proprietary & Confidential

===========================================================================*/
#include "uClock.h"
#include "DALSys.h"
#include "SpiDevice.h"

#ifdef BUILD_FOR_ISLAND
#define ATTRIBUTE_ISLAND_CODE __attribute__((section("RX.island")))
#define ATTRIBUTE_ISLAND_CONST __attribute__((section("RO.island")))
#define ATTRIBUTE_ISLAND_DATA __attribute__((section("RW.island")))
#else
#define ATTRIBUTE_ISLAND_CODE /* empty */
#define ATTRIBUTE_ISLAND_CONST /* empty */
#define ATTRIBUTE_ISLAND_DATA /* empty */
#endif

typedef struct SpiGpioCfg_s
{
   uint32      gpio_sig_spi_clk;
   uint32      gpio_sig_spi_cs;
   uint32      gpio_sig_spi_alt1_cs;
   uint32      gpio_sig_spi_alt2_cs;
   uint32      gpio_sig_spi_alt3_cs;
   uint32      gpio_sig_spi_mosi;
   uint32      gpio_sig_spi_miso;
} SpiGpioCfg_t;

typedef struct
{
   uint32 uQupCoreNum;
   uint32 qupVirtBlockAddr;
   uint32 qupPhysBlockAddr;
   boolean bInterruptBased;
   SpiGpioCfg_t spiGpio;
} SpiDevicePlat_DevCfg; 


/** @brief Releases data structures necessary to support the target calls.

    @param[in] hPlat platform device handle.

    @return          int32 .
  */
int32 SpiDevicePlat_DeInitTarget(SPIDEVICE_PLAT_HANDLE hPlat);

//Interface: IBusPlatCfg
/** @brief Initializes data structures necessary to support the target calls.

    @param[in] phPlat pointer to platform device handle.

    @return          int32 .
  */
int32 SpiDevicePlat_InitTarget(uint32 qup_core_num, SPIDEVICE_PLAT_HANDLE *phPlat);


/** @brief Gets the app clock frequency in Hz.

    @param[in] hPlat platform device handle.
    @param[out] pFrequencyHz Frequency of the core.

    @return          int32 .
  */
uint32 SpiDevicePlat_GetAppClkHz
(
   SPIDEVICE_PLAT_HANDLE hPlat,
   uint32 *pFrequencyHz
   );

/** @brief Sets the app clock frequency in Hz.

    @param[in] hPlat platform device handle.
    @param[in] reqFrequencyHz Frequency requested
    @param[out] pFinalFrequencyHz Frequency after the request.

    @return          int32 .
  */
uint32 SpiDevicePlat_SetAppClkHz
(
   SPIDEVICE_PLAT_HANDLE hPlat,
   uint32 reqFrequencyHz,
   uint32 *pFinalFrequencyHz
);

//Interface: IBusPower
/** @brief Sets the power state of the device.

    @param[in] hPlat platform device handle.

    @return          int32 .
  */
int32 SpiDevicePlat_SetPowerState(SPIDEVICE_PLAT_HANDLE hPlat, uint32 state);

/** @brief Gets the power state of the device.

    @param[in] hPlat platform device handle.

    @return          int32 .
  */
int32 SpiDevicePlat_GetPowerState(SPIDEVICE_PLAT_HANDLE hPlat, uint32 state);

int32 SpiDevicePlat_ClkCtrl(SpiDevicePlat_DevCfg *pDev, boolean ctrl);
#endif // _SPIDEVICEPLATSVC_H_

