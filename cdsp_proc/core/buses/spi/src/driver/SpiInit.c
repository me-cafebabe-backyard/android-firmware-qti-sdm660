/*=============================================================================

  FILE:     SpiInit.c

  OVERVIEW: Contains target specific SPI configuration for 8994 ADSP 
 
Copyright (c) 2009-2017 Qualcomm Technologies, Inc.
        All Rights Reserved.
Qualcomm Technologies, Inc. Confidential and Proprietary.

  ===========================================================================*/

/*=========================================================================
  EDIT HISTORY FOR MODULE

  $Header: //components/rel/core.qdsp6/1.0.c2/buses/spi/src/driver/SpiInit.c#1 $
  $DateTime: 2020/02/10 01:57:30 $$Author: pwbldsvc $

  When        Who    What, where, why
  --------    ---    -----------------------------------------------------------
  2017/02/10  dpk    Set LPASS PLL clock freq to enable the clock in island mode.
  2016/10/25  ska    Created for Binary Compatablity

  ===========================================================================*/
#include "SpiDevicePlatSvc.h"
#include "SpiDriverTypes.h"
#include "DALDeviceId.h"
#include "DDIHWIO.h"
#include "uTlmm.h"
#include "SpiConfig.h"
#include "DDIChipInfo.h"
#include "qurt_island.h"
#include "DDIClock.h"

spiDevice spiDevices[SPIPD_DEVICE_COUNT] ATTRIBUTE_ISLAND_DATA = {
   { NULL, 0, 0 }, //device handle, core number, current status
   { NULL, 1, 0 },
   { NULL, 2, 0 },
};

SpiDevicePlat_DevCfg Spi_DeviceCfg[SPIPD_DEVICE_COUNT] ATTRIBUTE_ISLAND_DATA;
const char         *spiDeviceID[SPIPD_DEVICE_COUNT] = {"DALDEVICEID_SPI_DEVICE_1","DALDEVICEID_SPI_DEVICE_2","DALDEVICEID_SPI_DEVICE_3"};



uint32 num_devices;
uint32 ssc_base_phyc_addr = 0;
uint32 spi_src_clk_freq, clk_div_value;

void Spi_Read_Props_Value(void);
void SpiInit(void);

void SpiInit(void)
{
	memset(Spi_DeviceCfg, 0, sizeof(Spi_DeviceCfg));
	Spi_Read_Props_Value();
}

void Spi_Read_Props_Value(void)
{
	DALSYS_PROPERTY_HANDLE_DECLARE(hProp);
	DALSYSPropertyVar PropVar,gPropVar;
	DALResult dalRes;
	SpiDevicePlat_DevCfg *tgtCfg;
	uint8 *periph_base = NULL;  
	DalDeviceHandle *phDalHWIO = NULL;
    DalDeviceHandle *phDalClock = NULL;
	ClockIdType clockId = 0;
	uint32 nResultFreq = 0;
	int32 i;


	if (DAL_SUCCESS != DALSYS_GetDALPropertyHandleStr(spiDeviceID[0], hProp)) 
	{
		return;
	}

	if (DAL_SUCCESS != DALSYS_GetPropertyValue(hProp, "num_devices", 0, &gPropVar)) 
	{
		return;
	}
	
	num_devices = (uint32)gPropVar.Val.dwVal;
    dalRes = DAL_DeviceAttach(DALDEVICEID_HWIO, &phDalHWIO);
    if ((DAL_SUCCESS != dalRes) || (NULL == phDalHWIO))   
    { 
   	return;  
    }

	if (DAL_SUCCESS != DalHWIO_MapRegion(phDalHWIO, "LPASS", &periph_base))   
	{ 
	return;   
	} 
	for (i = 0; i < num_devices; i++) 
	{      
	
		if (DAL_SUCCESS != DALSYS_GetDALPropertyHandleStr(spiDeviceID[i], hProp)) 
		{
			break;
		}
		tgtCfg = &(Spi_DeviceCfg[i]);
		if (DAL_SUCCESS != DALSYS_GetPropertyValue(hProp, "CHIP_BUS_INDEX", 0, &PropVar)) 
		{
			break;
		}
		tgtCfg->uQupCoreNum = (uint32)PropVar.Val.dwVal;  

		tgtCfg->bInterruptBased = 0; /* hard coding to zero as only polling is supported */

		if (DAL_SUCCESS != DALSYS_GetPropertyValue(hProp, "SSC_BASE_PHYS_ADDR", 0, &PropVar)) 
		{
			break;
		}
        ssc_base_phyc_addr = (uint32)PropVar.Val.dwVal;
		
		if (DAL_SUCCESS != DALSYS_GetPropertyValue(hProp, "CHIP_BLOCK_OFFSET", 0, &PropVar)) 
		{
			break;
		}
		tgtCfg->qupPhysBlockAddr = ssc_base_phyc_addr + (uint32)PropVar.Val.dwVal; 
		tgtCfg->qupVirtBlockAddr = (uint32)periph_base + (uint32)PropVar.Val.dwVal;
	    if (DAL_SUCCESS != DALSYS_GetPropertyValue(hProp, "SPI_SRC_CLK_FREQ", 0, &PropVar)) 
		{
			break;
		}
        spi_src_clk_freq = (uint32)PropVar.Val.dwVal;
	    if (DAL_SUCCESS != DALSYS_GetPropertyValue(hProp, "CLK_DIVIDER_VALUE", 0, &PropVar)) 
		{
			break;
		}
        clk_div_value = (uint32)PropVar.Val.dwVal;
		if (DAL_SUCCESS != DALSYS_GetPropertyValue(hProp, "gpio_spi_clk_str", 0, &PropVar)) 
		{
			break;
		}
		tgtCfg->spiGpio.gpio_sig_spi_clk = (uint32)PropVar.Val.dwVal;
		if (DAL_SUCCESS != DALSYS_GetPropertyValue(hProp, "gpio_spi_cs_str", 0, &PropVar)) 
		{
			break;
		}
		tgtCfg->spiGpio.gpio_sig_spi_cs= (uint32)PropVar.Val.dwVal;
		if (DAL_SUCCESS != DALSYS_GetPropertyValue(hProp, "gpio_spi_mosi_str", 0, &PropVar)) 
		{
			break;
		}
		tgtCfg->spiGpio.gpio_sig_spi_mosi= (uint32)PropVar.Val.dwVal;

		if (DAL_SUCCESS != DALSYS_GetPropertyValue(hProp, "gpio_spi_miso_str", 0, &PropVar)) 
		   {
			 break;
		   }
		tgtCfg->spiGpio.gpio_sig_spi_miso= (uint32)PropVar.Val.dwVal;
		if (DAL_SUCCESS != DALSYS_GetPropertyValue(hProp, "gpio_spi_alt_cs1_str", 0, &PropVar)) 
		{
			break;
		}
		tgtCfg->spiGpio.gpio_sig_spi_alt1_cs= (uint32)PropVar.Val.dwVal;
		if (DAL_SUCCESS != DALSYS_GetPropertyValue(hProp, "gpio_spi_alt_cs2_str", 0, &PropVar)) 
		{
			break;
		}
		tgtCfg->spiGpio.gpio_sig_spi_alt2_cs= (uint32)PropVar.Val.dwVal;
		if (DAL_SUCCESS != DALSYS_GetPropertyValue(hProp, "gpio_spi_alt_cs3_str", 0, &PropVar)) 
		{
			break;
		}
		tgtCfg->spiGpio.gpio_sig_spi_alt3_cs= (uint32)PropVar.Val.dwVal;

	}

	dalRes= DAL_DeviceAttach(DALDEVICEID_CLOCK, &phDalClock);
    if ((DAL_SUCCESS != dalRes) || (NULL == phDalClock))   
    { 
        return;  
    }

    if (DAL_SUCCESS != DalClock_GetClockId(phDalClock, "island_scc_qup_spi1_clk", &clockId))
    {
        return;
	}

	if (DAL_SUCCESS != DalClock_SetClockFrequency(phDalClock, clockId, spi_src_clk_freq, CLOCK_FREQUENCY_HZ_CLOSEST, &nResultFreq))
    {
        return;
	}
}

void SpiInit_DeviceInstance(spi_device_id_t device_id)
{
	uint32 clkSig, mosiSig, misoSig, csSig;
	SpiDevicePlat_DevCfg *tgtCfg;
	tgtCfg = &(Spi_DeviceCfg[device_id]);
	clkSig =  tgtCfg->spiGpio.gpio_sig_spi_clk;
	csSig =  tgtCfg->spiGpio.gpio_sig_spi_cs;
	mosiSig =  tgtCfg->spiGpio.gpio_sig_spi_mosi;
	misoSig =  tgtCfg->spiGpio.gpio_sig_spi_miso;
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
	  csSig = tgtCfg->spiGpio.gpio_sig_spi_alt1_cs;
	  if (csSig)
      {
         if (TRUE != uTlmm_ConfigGpio(csSig, UTLMM_GPIO_ENABLE))
            break;
      }
	  csSig = tgtCfg->spiGpio.gpio_sig_spi_alt2_cs;
      if (csSig)
      {
         if (TRUE != uTlmm_ConfigGpio(csSig, UTLMM_GPIO_ENABLE))
            break;
      }
	  csSig = tgtCfg->spiGpio.gpio_sig_spi_alt3_cs;
	  if (csSig)
      {
         if (TRUE != uTlmm_ConfigGpio(csSig, UTLMM_GPIO_ENABLE))
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
   return spi_src_clk_freq;
}

uint32 SpiConfig_GetMaxClkDividers(void)
{
   return clk_div_value; // maximum divider value possible in SCC_SPI_I2C1_CLK_CDIV_REG register(511)
}