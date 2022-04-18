/*=============================================================================

  FILE:     I2cPlatCOnfig.c

  OVERVIEW: This file has the devices for 8998 platform for slpi. 
 
    Copyright (c) 2016-2017 Qualcomm Technologies, Incorporated.
                  All rights reserved.
    Qualcomm Technologies, Confidential and Proprietary.
  ===========================================================================*/

/*=========================================================================
  EDIT HISTORY FOR MODULE

  $Header: //components/rel/core.qdsp6/1.0.c2/buses/i2c/src/drv/I2cPlatConfig.c#1 $
  $DateTime: 2020/02/10 01:57:30 $$Author: pwbldsvc $

  When     Who    What, where, why
  -------- ---    -----------------------------------------------------------
  12/11/17 ska    uEnablePadding added for enabling padding
  04/07/17 VG     Adding FS_HS divider values configurable 
  03/24/17 VG     backout FS_HS divider fix
  03/10/17 VG     Adding FS_HS divider values as configurable
  02/10/17 VG     Set LPASS PLL clock freq to enable the clock in island mode.
  10/17/16 VG     Initial version.
  ===========================================================================*/

/*-------------------------------------------------------------------------
 * Include Files
 * ----------------------------------------------------------------------*/

#include "I2cDriverTypes.h"
#include "I2cPlatSvc.h"
#include "DDIHWIO.h"

/*-------------------------------------------------------------------------
 * Global Data Definitions
 * ----------------------------------------------------------------------*/

I2cDrv_DescType           i2cDrvDescArray[I2C_NUM_PLATFORM_DEVICES];
I2cPlat_PropertyType      i2cPlatPropertyArray[I2C_NUM_PLATFORM_DEVICES];
I2cDev_PropertyType       i2cDevPropertyArray[I2C_NUM_PLATFORM_DEVICES];
I2cDrv_DriverProperty     i2cDrvPropertyArray[I2C_NUM_PLATFORM_DEVICES];
I2cDev_ClkDividers        i2cDivPropertyArray;

const uint32              i2cDeviceNum = I2C_NUM_PLATFORM_DEVICES;
/** @brief Read the properties from xml and populate them in instance wise.
    @return             I2C_RES_SUCCESS is successful, otherwise**/

/** @brief Read the properties from xml and populate them in instance wise.
    @return             I2C_RES_SUCCESS is successful, otherwise**/
   	 
int32 I2cPlat_ReadPlatConfig()
{
   DALSYS_PROPERTY_HANDLE_DECLARE(hProp);
   DALSYSPropertyVar     PropVar;
   int32                 result=0,deviceCnt=0;
   const char            *i2cDevices[3] = {"I2CDRV_I2C_3","I2CDRV_I2C_2","I2CDRV_I2C_1"};
   
   if ( DAL_SUCCESS != DALSYS_GetDALPropertyHandleStr("I2C_DIV_GLOBAL_PROP", hProp ) ) {
	  
        return (int32)I2CPLAT_ERROR_DAL_GET_PROPERTY_HANDLE;
      }
	  
         if ( DAL_SUCCESS !=
               DALSYS_GetPropertyValue(hProp, "STMODEFSVAL", 0, &PropVar )) {
         }
         i2cDivPropertyArray.stdModeFsval = (uint32)PropVar.Val.dwVal;
		 
		 if ( DAL_SUCCESS !=
               DALSYS_GetPropertyValue(hProp, "STMODEHSVAL", 0, &PropVar )) {
         }
         i2cDivPropertyArray.stdModeHsval = (uint32)PropVar.Val.dwVal;

		 if ( DAL_SUCCESS !=
               DALSYS_GetPropertyValue(hProp, "FSMODEFSVAL", 0, &PropVar )) {
         }
		 i2cDivPropertyArray.fastModeFsval = (uint32)PropVar.Val.dwVal;

		 if ( DAL_SUCCESS !=
               DALSYS_GetPropertyValue(hProp, "FSMODEHSVAL", 0, &PropVar )) {
         }
		 i2cDivPropertyArray.fastModeHsval = (uint32)PropVar.Val.dwVal;

		 if ( DAL_SUCCESS !=
               DALSYS_GetPropertyValue(hProp, "FSPMODEFSVAL", 0, &PropVar )) {
         }
		 i2cDivPropertyArray.fastModePlusFsval = (uint32)PropVar.Val.dwVal;

		 if ( DAL_SUCCESS !=
               DALSYS_GetPropertyValue(hProp, "FSPMODEHSVAL", 0, &PropVar )) {
         }
		 i2cDivPropertyArray.fastModePlusHsval = (uint32)PropVar.Val.dwVal;
		
   for ( deviceCnt  = 0; deviceCnt < i2cDeviceNum; ++deviceCnt){
      
      if ( DAL_SUCCESS != DALSYS_GetDALPropertyHandleStr(i2cDevices[deviceCnt], hProp ) ) {
	  
        return (int32)I2CPLAT_ERROR_DAL_GET_PROPERTY_HANDLE;
      }
	  
	  do {
	    
		 if ( DAL_SUCCESS !=
               DALSYS_GetPropertyValue(hProp, "CHIP_BUS_INDEX", 0, &PropVar )) {
            break;
         }
         i2cDrvPropertyArray[deviceCnt].eDevId = (uint32)PropVar.Val.dwVal;
		 
         if ( DAL_SUCCESS !=
               DALSYS_GetPropertyValue(hProp, "GPIO_I2C_SDA", 0, &PropVar )) {
            break;
         }
         i2cPlatPropertyArray[deviceCnt].aGpioCfg[0] = (uint32)PropVar.Val.dwVal;
	         
         if ( DAL_SUCCESS !=
               DALSYS_GetPropertyValue(hProp, "GPIO_I2C_SCL", 0, &PropVar )) {
            break;
         }
        i2cPlatPropertyArray[deviceCnt].aGpioCfg[1] = (uint32)PropVar.Val.dwVal;
		 
         i2cPlatPropertyArray[deviceCnt].uNumGpios = 2;
         
         if ( DAL_SUCCESS !=
               DALSYS_GetPropertyValue(hProp, "CHIP_PERIPH_SS_BASE_NAME", 0, &PropVar )) {
            break;
         }
         i2cPlatPropertyArray[deviceCnt].pPeriphSsAddrName = (char*)PropVar.Val.dwVal;

         if ( DAL_SUCCESS != 
               DALSYS_GetPropertyValue(hProp,"CHIP_BLOCK_OFFSET", 0, &PropVar ) ) {
            break;
         }
         i2cPlatPropertyArray[deviceCnt].coreOffset = PropVar.Val.dwVal;
		 
         if ( DAL_SUCCESS !=
               DALSYS_GetPropertyValue(hProp, "CHIP_APP_CLK_NAME", 0, &PropVar)) {
            break;
         }
        i2cPlatPropertyArray[deviceCnt].QupAppClkId = (uClockIdType)PropVar.Val.dwVal;
		 
		 if ( DAL_SUCCESS !=
               DALSYS_GetPropertyValue(hProp, "CHIP_HCLK_NAME", 0, &PropVar )) {
            break;
         }
         i2cPlatPropertyArray[deviceCnt].QupHClkId = (uClockIdType)PropVar.Val.dwVal;
		 
         if ( DAL_SUCCESS !=
                  DALSYS_GetPropertyValue(hProp, "LPASS_PLL_SRC_FREQ", 0, &PropVar)) {
            break;     
         }
		 i2cDevPropertyArray[deviceCnt].pLpassPllClk = (uint32)PropVar.Val.dwVal;
		 
		 if ( DAL_SUCCESS !=
                  DALSYS_GetPropertyValue(hProp, "CHIP_APP_CLK_FREQ_KHZ", 0, &PropVar)) {
            break;     
         }
		 i2cDevPropertyArray[deviceCnt].uI2cInputClkKhz = (uint32)PropVar.Val.dwVal;
         
         if ( DAL_SUCCESS !=
                  DALSYS_GetPropertyValue(hProp, "ENABLE_PADDING", 0, &PropVar)) {
            break;     
         }
		 i2cDevPropertyArray[deviceCnt].uEnablePadding = (uint32)PropVar.Val.dwVal;
		 
		 
		 i2cDevPropertyArray[deviceCnt].virtBlockAddr = NULL;

         result = I2C_RES_SUCCESS;
		 
      } while ( 0 );
      if (I2C_RES_SUCCESS != result){
		 break;
      }
    }
   return result;
}

