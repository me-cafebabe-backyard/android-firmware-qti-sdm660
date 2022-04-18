/*=============================================================================

  FILE:     spi_slpi_8998.c

  OVERVIEW: Contains target specific SPI configuration for 8994 ADSP 
 
Copyright (c) 2009-2015 Qualcomm Technologies, Inc.
        All Rights Reserved.
Qualcomm Technologies, Inc. Confidential and Proprietary.

  ===========================================================================*/

/*=========================================================================
  EDIT HISTORY FOR MODULE

  $Header: //components/rel/core.qdsp6/1.0.c2/buses/spi/src/config/spi_slpi_8998.c#1 $
  $DateTime: 2020/02/10 01:57:30 $$Author: pwbldsvc $

  When        Who    What, where, why
  --------    ---    -----------------------------------------------------------
  2014/04/01  vk     Initial version 

  ===========================================================================*/
#include "SpiDevicePlatSvc.h"
#include "SpiDriverTypes.h"
#include "DALDeviceId.h"
#include "DDIHWIO.h"
#include "uTlmm.h"
#include "SpiConfig.h"

spiDevice spiDevices[SPIPD_DEVICE_COUNT] ATTRIBUTE_ISLAND_DATA = {
   { NULL, 0, 0 }, //device handle, core number, current status
   { NULL, 1, 0 },
};

SpiDevicePlat_DevCfg Spi_DeviceCfg[SPIPD_DEVICE_COUNT] ATTRIBUTE_ISLAND_DATA;

#define SSC_BASE_PHYS_ADDR 0x5800000

const uint32 SpiQupPhysAddrOffset[] ATTRIBUTE_ISLAND_DATA = {0x6B5000, 0x6B6000, 0x6B7000};
//Alt CS definitions are not clear from IPCAT nazgul_ssc_io v2.0 - get clarification from TLMM team
const uint32 SpioGpioAltCS[] ATTRIBUTE_ISLAND_CONST = {0x2006C001, 0, 0};
const uint32 SpiGpioClk[] ATTRIBUTE_ISLAND_CONST     = {0x2006C091, 0x2006C052, 0x2006C101};
const uint32 SpiGpioCS[] ATTRIBUTE_ISLAND_CONST      = {0x2006C081, 0x2006C042, 0x2006C111};
const uint32 SpiClkGpioMISO[] ATTRIBUTE_ISLAND_CONST = {0x2006C0B1, 0x2006C072, 0x2006C131};
const uint32 SpiClkGpioMOSI[] ATTRIBUTE_ISLAND_CONST = {0x2006C0A1, 0x2006C062, 0x2006C121};

//static boolean ChipVer1or2 = TRUE; //chip rev is older than v3

void SpiInit(void)
{
   int32 i;
   SpiDevicePlat_DevCfg *tgtCfg;
   DALResult dalRes;
   uint8 *periph_base = NULL;
   DalDeviceHandle *phDalHWIO = NULL;

   memset(Spi_DeviceCfg, 0, sizeof(Spi_DeviceCfg));

   dalRes = DAL_DeviceAttach(DALDEVICEID_HWIO, &phDalHWIO);
   if ((DAL_SUCCESS != dalRes) || (NULL == phDalHWIO))
   {
      return;
   }
   if (DAL_SUCCESS != DalHWIO_MapRegion(phDalHWIO, "SSC", &periph_base))
   {
      return;
   }

   for (i = 0; i < SPIPD_DEVICE_COUNT; i++)
   {
      tgtCfg = &(Spi_DeviceCfg[i]);
      tgtCfg->uQupCoreNum = spiDevices[i].qup_core_num;
      tgtCfg->bInterruptBased = 0;
      tgtCfg->qupPhysBlockAddr = SSC_BASE_PHYS_ADDR + SpiQupPhysAddrOffset[tgtCfg->uQupCoreNum];
      tgtCfg->qupVirtBlockAddr = (uint32)periph_base + SpiQupPhysAddrOffset[tgtCfg->uQupCoreNum];
   }
}

void SpiInit_DeviceInstance(spi_device_id_t device_id)
{
   static uint32 SpiInitDone = FALSE;
   uint32 clkSig, mosiSig, misoSig, csSig, cs2Sig;
   
   if (SpiInitDone == FALSE)
   {
      SpiInit();
      SpiInitDone = TRUE;
   }

   clkSig = SpiGpioClk[device_id];
   csSig = SpiGpioCS[device_id];
   misoSig = SpiClkGpioMISO[device_id];
   mosiSig = SpiClkGpioMOSI[device_id];
   cs2Sig = SpioGpioAltCS[device_id];
   do
   {
      if (TRUE != uTlmm_ConfigGpio(clkSig, UTLMM_GPIO_ENABLE))
         break;
      if (TRUE != uTlmm_ConfigGpio(mosiSig, UTLMM_GPIO_ENABLE))
         break;
      if (TRUE != uTlmm_ConfigGpio(misoSig, UTLMM_GPIO_ENABLE))
         break;
      if (csSig)
      {
         if (TRUE != uTlmm_ConfigGpio(csSig, UTLMM_GPIO_ENABLE))
            break;
      }
      if (cs2Sig)
      {
         if (TRUE != uTlmm_ConfigGpio(cs2Sig, UTLMM_GPIO_ENABLE))
            break;
      }
   }
   while (0); 
}

void *SpiConfig_GetConfigObject(uint32 dev_instance)
{
   return &(Spi_DeviceCfg[dev_instance]);
}

uint32 SpiConfig_GetMaxSourceClkFreqHz(void)
{
   return 99975168;
}

uint32 SpiConfig_GetMaxClkDividers(uint32 dev_instance)
{
   uint32 dividers = 8;

   switch (dev_instance)
   {
   case 0:
      dividers = 256;
      break;
   case 1:
      dividers = 32;
	  break;
   }

   return dividers;
}

