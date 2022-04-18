/*=============================================================================

  FILE:   I2cPlatSvc.c

  OVERVIEW: This file contains the implementation for the platform services.
 
        Copyright (c) 2011-2017 Qualcomm Technologies, Incorporated.
                    All Rights Reserved.
       Qualcomm Technologies, Confidential and Proprietary.

=============================================================================*/
/*=============================================================================
EDIT HISTORY FOR MODULE

$Header: //components/rel/core.qdsp6/1.0.c2/buses/i2c/src/drv/I2cBsp.c#1 $
$DateTime: 2020/02/10 01:57:30 $$Author: pwbldsvc $
When     Who    What, where, why
-------- ---    -----------------------------------------------------------
02/10/17 VG     Set LPASS PLL clock freq to enable the clock in island mode.
12/19/16 VG     Kw fix
10/17/16 VG     Updated the Copy Rights
04/08/16 VG     Added binary compatibility changes
07/17/13 LK     Added xml properties.
09/26/11 LK     Created
=============================================================================*/

/*-------------------------------------------------------------------------
 * Include Files
 * ----------------------------------------------------------------------*/

#include "I2cBsp.h"
#include "I2cPlatSvc.h"
#include "I2cDevice.h"
#include "I2cDriverTypes.h"
#include "DDIChipInfo.h"
#include "I2cDriver.h"
#include "DDIClock.h"

/*-------------------------------------------------------------------------
 * Global Data Definitions
 * ----------------------------------------------------------------------*/
extern I2cDrv_DescType           i2cDrvDescArray[];
extern I2cPlat_PropertyType      i2cPlatPropertyArray[];
extern I2cDev_PropertyType       i2cDevPropertyArray[];
extern I2cDrv_DriverProperty     i2cDrvPropertyArray[];
extern const uint32              i2cDeviceNum;

int32
I2cDrv_Init
(
   void
);

int32
I2cDrv_InitDevice
(
   I2cDrv_I2cBusId  eI2cBusId,
   I2cDrv_DescType* pDesc
);

/*-------------------------------------------------------------------------
 * Externalized Function Definitions
 * ----------------------------------------------------------------------*/
//DEBUG:
//void i2c_test(void);
/** @brief Releases a device driver struct .
 
 @return             Pointer to dev if found, otherwise NULL.
 */
void
I2cBsp_ReleaseDriverObj
(
 I2cDrv_DescType* pDesc
)
{
   pDesc->opState = I2CDRV_OPSTATE_OBJ_FREE;
}

/** @brief Initialises all I2C driver devices for the platform .
 
 @return             Pointer to dev if found, otherwise NULL.
 */
void I2cBsp_Init(void)
{
   I2cDrv_DescType       *pDesc = NULL;
   I2cPlat_PropertyType  *pPlatProperty = NULL;
   I2cDev_PropertyType   *pDevProperty = NULL;
   I2cDrv_DriverProperty *pDrvProperty = NULL;
   int32                  drvPropertyIndex,result=0;
   static boolean         bBspInitDone = FALSE;
   DalDeviceHandle       *phDalClock = NULL;
   ClockIdType            clockId = 0;
   uint32                 nResultFreq = 0;
   DALResult              dalRes = 0;

   if (bBspInitDone) {
      return;     
   }

   I2cDrv_Init();
   result=I2cPlat_ReadPlatConfig();
   if (I2C_RES_SUCCESS == result)
    {
		for ( drvPropertyIndex=0; drvPropertyIndex < i2cDeviceNum; drvPropertyIndex++ ) {
		  pDrvProperty = &i2cDrvPropertyArray[drvPropertyIndex];
		  pPlatProperty = &i2cPlatPropertyArray[drvPropertyIndex];
		  pDevProperty  = &i2cDevPropertyArray[drvPropertyIndex];
		  pDesc         = &i2cDrvDescArray[drvPropertyIndex];
		  pDesc->pDrvProps  = pDrvProperty;
		  pDesc->pPlatProps = pPlatProperty;
		  pDesc->pDevProps  = pDevProperty;
		  pDesc->opState    = I2CDRV_OPSTATE_OBJ_FREE;
	  
		  if (I2CDEV_PROPVALUE_INPUT_CLK_CHIP_VER_BASED == pDesc->pDevProps->uI2cInputClkKhz) {
			 DalChipInfoVersionType nChipVersion;
			 nChipVersion = DalChipInfo_ChipVersion();   
			 pDesc->pDevProps->uI2cInputClkKhz = 19995;
		  }
		  I2cDrv_InitDevice(pDrvProperty->eDevId,pDesc);
	   }
		 if(NULL != pDesc){
		   pDesc->InitState |= I2cBspInit_Done;
		 }
	     bBspInitDone = TRUE;
	}
    else if(NULL != pDesc)
	{
	  	pDesc->InitState |= I2cBspInit_Failed;
	}

	dalRes= DAL_DeviceAttach(DALDEVICEID_CLOCK, &phDalClock);
    if ((DAL_SUCCESS != dalRes) || (NULL == phDalClock))   
    { 
        return;  
    }

    if (DAL_SUCCESS != DalClock_GetClockId(phDalClock, "island_scc_qup_i2c1_clk", &clockId))
    {
        return;
	}

	if (NULL != pDesc)
    {
	    if (DAL_SUCCESS != DalClock_SetClockFrequency(phDalClock, clockId, pDesc->pDevProps->pLpassPllClk, CLOCK_FREQUENCY_HZ_CLOSEST, &nResultFreq))
        {
            return;
	    }
    }
}
