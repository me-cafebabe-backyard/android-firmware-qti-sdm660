/*#==============================================================================
   Copyright (c)2014 Qualcomm Technologies, Inc .
   All Rights Reserved.
   Qualcomm Confidential and Proprietary

# THIS IS AN AUTO-GENERATED TEMPLATE FILE FOR DAL DRIVER LIST
# DO NOT MODIFY.
#================================================================================*/
#include "DALStdDef.h" 
#include "DALReg.h" 
#include "DALSysTypes.h"

extern DALREG_DriverInfo DALSystem_DriverInfo;
extern DALREG_DriverInfo DALVAdc_DriverInfo;

static DALREG_DriverInfo * DALDriverInfoArr[] = {
	& DALSystem_DriverInfo,
	& DALVAdc_DriverInfo,
};

DALREG_DriverInfoList gDALModDriverInfoList = {2, DALDriverInfoArr}; 



StringDevice DAL_Mod_driver_list[] = {
			{"/core/hwengines/adc/pmic_0/vadc",3608013919u, 1472, &DALVAdc_DriverInfo, 0, NULL },
			{"/core/hwengines/adc/pmic_1/vadc",3647149312u, 1488, &DALVAdc_DriverInfo, 0, NULL },
			
};

DALProps gDALModStringDeviceInfoList = {NULL, 0 ,2, DAL_Mod_driver_list};
