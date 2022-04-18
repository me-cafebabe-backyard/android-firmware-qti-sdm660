/*
===========================================================================

FILE:   SpiDevicePlatSvc.c

DESCRIPTION:

===========================================================================

        Edit History

$Header: //components/rel/core.qdsp6/1.0.c2/buses/spi/src/device/SpiDevicePlatSvc.c#1 $

When       Who      What, where, why
--------   ---      -----------------------------------------------------------
07/16/15   vmk      Added clk control
04/10/13   vmk      Initial version.

===========================================================================
        Copyright c 2013-16 Qualcomm Technologies Incorporated.
            All Rights Reserved.
            Qualcomm Confidential & Proprietary

===========================================================================
*/

#include "SpiDevice.h"
#include "SpiDevicePlatSvc.h"
#include "SpiDeviceOsSvc.h"
#include "SpiDriver.h"
#include "SpiConfig.h"


#include "DALStdDef.h"
#include "DALSys.h"
#include "uClock.h"

typedef enum SpiDevicePlat_Error
{
   SPIDEVICE_PLAT_ERROR_DAL_GET_PROPERTY_HANDLE = SPI_ERROR_CLS_PLATFORM,
   SPIDEVICE_PLAT_ERROR_INVALID_POWER_STATE,
   SPIDEVICE_PLAT_ERROR_FAILED_TO_ENABLE_APPCLK,
   SPIDEVICE_PLAT_ERROR_FAILED_TO_DISABLE_APPCLK,
   SPIDEVICE_PLAT_ERROR_FAILED_TO_ENABLE_HCLK,
   SPIDEVICE_PLAT_ERROR_FAILED_TO_DISABLE_HCLK,
   SPIDEVICE_PLAT_ERROR_FAILED_TO_SET_APPCLK_FREQ,
   SPIDEVICE_PLAT_ERROR_NULL_PTR,
} SpiDevicePlat_Error;

static SpiDevicePlat_DevCfg* SpiDevicePlat_GetTargetConfig(uint32 qup_core_num)
{
   SpiDevicePlat_DevCfg *tgtCfg = NULL, *devCfg;
   int32 index = -1, i;
   
   for (i = 0; i < SPIPD_DEVICE_COUNT; i++)
   {
      devCfg = (SpiDevicePlat_DevCfg *)SpiConfig_GetConfigObject(i);
      if (devCfg->uQupCoreNum == qup_core_num)
      {
         index = i;
      }
   }
   if (index == -1)
   {
      return NULL;
   }
   tgtCfg = (SpiDevicePlat_DevCfg *)SpiConfig_GetConfigObject(index);

   return tgtCfg;
}

int32 SpiDevicePlat_InitTarget(uint32 qup_core_num, SPIDEVICE_PLAT_HANDLE *phPlat)
{
   int32 res = -1;
   SpiDevicePlat_DevCfg *tgtCfg = NULL;

   tgtCfg = SpiDevicePlat_GetTargetConfig(qup_core_num);

   if (NULL != tgtCfg)
   {
      *phPlat = (SPIDEVICE_PLAT_HANDLE)tgtCfg;

      do
      {
         if (SPI_SUCCESS != (res = SpiDevicePlat_ClkCtrl(tgtCfg, 1)))
         {
            break;
         }
         res = SPI_SUCCESS;
      }
      while (0);
   }
   return res;
}

int32 SpiDevicePlat_DeInitTarget(SPIDEVICE_PLAT_HANDLE hPlat)
{
   /* SpiDevicePlat_InitTarget, just does data structure allocation.
    * The allocated data structures will be available for the life-time 
    * of the driver. There is no point in allocating and de-allocating 
    * them.
   */
   SpiDevicePlat_DevCfg *tgtCfg = (SpiDevicePlat_DevCfg *)hPlat;
   SpiDevicePlat_ClkCtrl(tgtCfg, 0);
   return SPI_SUCCESS;
}


int32 SpiDevicePlat_ClkCtrl(SpiDevicePlat_DevCfg *pDev, boolean ctrl)
{
   uClockIdType coreClockId;
   uClockIdType hClockId = CLOCK_SCC_BLSP_H_CLK;
   int32 res = SPI_SUCCESS;

   switch (pDev->uQupCoreNum)
   {
      case 0:
         coreClockId = CLOCK_SCC_QUP_SPI1_CLK;
         break;

      case 1:
         coreClockId = CLOCK_SCC_QUP_SPI2_CLK;
         break;

      case 2:
         coreClockId = CLOCK_SCC_QUP_SPI3_CLK;
         break;

      default:
         res = SPIDEVICE_PLAT_ERROR_FAILED_TO_ENABLE_APPCLK;
         return res;
   }
   do
   {
      if (ctrl)
	  {
         /* Enable QUP Clock */
         if(!uClock_EnableClock(coreClockId))
         {
            res = SPIDEVICE_PLAT_ERROR_FAILED_TO_ENABLE_APPCLK;
            break;
         }

         /* Enable HCLK */
         if(!uClock_EnableClock(hClockId))
         {
            res = SPIDEVICE_PLAT_ERROR_FAILED_TO_ENABLE_HCLK;
            break;
         }
      }
	  else
	  {
         /* Disable QUP Clock */
         if(!uClock_DisableClock(coreClockId))
         {
            res = SPIDEVICE_PLAT_ERROR_FAILED_TO_DISABLE_APPCLK;
            break;
         }

         /* Disable HCLK */
         if(!uClock_DisableClock(hClockId))
         {
            res = SPIDEVICE_PLAT_ERROR_FAILED_TO_DISABLE_HCLK;
            break;
         }
	  }
   }
   while (0);

   return res;
}

static uint32 SpiDevicePlat_DetermineDivider(uint32 dev_instance, uint32 req_freq, uint32 *real_freq)
{
   uint32 i, divider = 0;
   *real_freq = 0;
   uint32 source_freq = SpiConfig_GetMaxSourceClkFreqHz();
   uint32 max_divider = SpiConfig_GetMaxClkDividers();
   if (req_freq >= source_freq)
   {
      divider = 1;
      *real_freq = source_freq;
   }
   else
   {
      for (i = 2; i <= max_divider; i++)
      {
         if (source_freq/i <= req_freq)
	     {
	        divider = i;
	        break;
	     }
      }
	  if (divider != 0)
         *real_freq = source_freq / divider;
   }
   return divider;
}

uint32 SpiDevicePlat_SetAppClkHz (SPIDEVICE_PLAT_HANDLE hPlat,
                                  uint32 reqFrequencyHz,
                                  uint32 *pFinalFrequencyHz)
{
   SpiDevicePlat_DevCfg *pDev = (SpiDevicePlat_DevCfg *)hPlat;

   uClockIdType coreClockId;
   int32 res = SPI_SUCCESS;
   uint32 divider;

   switch (pDev->uQupCoreNum)
   {
      case 0:
         coreClockId = CLOCK_SCC_QUP_SPI1_CLK;
         break;

      case 1:
         coreClockId = CLOCK_SCC_QUP_SPI2_CLK;
         break;

      case 2:
         coreClockId = CLOCK_SCC_QUP_SPI3_CLK;
         break;

      default:
         res = SPIDEVICE_PLAT_ERROR_FAILED_TO_SET_APPCLK_FREQ;
         return res;
   }
   divider = SpiDevicePlat_DetermineDivider(pDev->uQupCoreNum, reqFrequencyHz, pFinalFrequencyHz);
   
   if (divider != 0 && uClock_SetClockDivider (coreClockId, divider))
      return SPI_SUCCESS;
   else 
      return SPIDEVICE_PLAT_ERROR_FAILED_TO_SET_APPCLK_FREQ;
}
