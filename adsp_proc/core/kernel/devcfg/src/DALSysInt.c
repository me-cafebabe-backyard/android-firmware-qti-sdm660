#include "DALSysInt.h"
#include "DevCfg_ImgParams.h"
#ifndef DEVCFG_STANDALONE
    #include "stringl/stringl.h"
#endif

extern DALProps DAL_Mod_Info;
extern DEVCFG_TARGET_INFO devcfg_target_soc_info[];
DALProps * SOC_PropInfo         = NULL;
DALProps * PLATFORM_PropInfo    = NULL;
DALProps * OEM_PropInfo         = NULL;
DEVCFG_PLATFORM_INFO gtcsrSOCHWVersion = {0, 0}; //family_number_device_number, major_ver_minor_ver

void DevCfg_log(const char* errMsg, ...)
{
    return;
}
void
DALSYS_SOC_PropsSymLookUp(DEVCFG_TARGET_INFO *pTargetInfoTableIter)
{
    if(!pTargetInfoTableIter)
    {
        DevCfg_log("SOC PropInfo lookup failed\n");
        return;
    }
    
    if(!SOC_PropInfo)
    {        
      /* Iterate over the table until you reach end of it {0, NULL, NULL, 0}*/
      while(pTargetInfoTableIter->plinker_soc_seg_sym)
      {
        #ifndef DEVCFG_MULTICFG_ENABLED
            //The Image is a Single config. No need to comapre Chip ID
            //Assume that the first entry is for the desired chip
            SOC_PropInfo = (DALProps *)(pTargetInfoTableIter->plinker_soc_seg_sym);
            return;
        #endif
        
         if(pTargetInfoTableIter->tcsr_soc_info == gtcsrSOCHWVersion.soc_number)
         {
            SOC_PropInfo = (DALProps *)(pTargetInfoTableIter->plinker_soc_seg_sym);
         }
         pTargetInfoTableIter++;
      }    
    }
}

#ifdef DEVCFG_MULTIPLATFORM_ENABLED

void
DALSYS_Platform_PropsSymLookUp(DEVCFG_TARGET_INFO *pTargetInfoTableIter)
{
    DalPlatformInfoPlatformType platform_id = DALPLATFORMINFO_TYPE_UNKNOWN;
    uint32 dwPlatformCount = 0;
    if(!pTargetInfoTableIter)
        return;
    
    if(!PLATFORM_PropInfo)
    {       
      /* Iterate over the table until you reach end of it {0, NULL, NULL, 0}*/
      while(pTargetInfoTableIter->plinker_soc_seg_sym)
      {
         if(pTargetInfoTableIter->tcsr_soc_info == gtcsrSOCHWVersion.soc_number)
         {
            if(pTargetInfoTableIter->num_platform_type > 0)
            {
               platform_id = DalPlatformInfo_Platform();
            }
            else
            {
                return;
            }   
            for( dwPlatformCount = 0; dwPlatformCount < pTargetInfoTableIter->num_platform_type; 
               dwPlatformCount++) 
            {
               if(pTargetInfoTableIter->platform_info->platform_id == platform_id)
               {
                  PLATFORM_PropInfo =  (DALProps *)(pTargetInfoTableIter->platform_info->plinker_platform_seg_sym);
                  break;
               }
               pTargetInfoTableIter->platform_info++;
            }
         }
         pTargetInfoTableIter++;
      }    
    }
}
#endif               


#ifdef DEVCFG_OEM_ENABLED
void
DALSYS_OEM_PropsSymLookUp(DEVCFG_TARGET_INFO *pTargetInfoTableIter)
{
    if(!pTargetInfoTableIter)
        return;
    if(!OEM_PropInfo)
    {        
      /* Iterate over the table until you reach end of it {0, NULL, NULL, 0}*/
      while(pTargetInfoTableIter->plinker_soc_seg_sym)
      {
         if(pTargetInfoTableIter->tcsr_soc_info == gtcsrSOCHWVersion.soc_number)
         {
            OEM_PropInfo = (DALProps *)(pTargetInfoTableIter->plinker_soc_seg_sym);
         }
         pTargetInfoTableIter++;
      }    
    }
}
#endif
/*
  Called at DALSYS Init to detect chipset info by mapping the 
  TCSR_SOC_HW_VERSION register physical address. The register
  address is assumed to be fixed for a family and defined in ipcat
*/


#ifdef DEVCFG_MULTICFG_ENABLED

void
DALSYS_ReadSocHwInfo(void)
{
#ifdef TCSR_ADDR_PHS_SAME_AS_VIR
    memscpy(&gtcsrSOCHWVersion, sizeof(uint32), (uint32*)DEVCFG_TCSR_SOC_HW_ADDR,
        sizeof(uint32));
#else
    DALResult eResult;
    DALSYSMemHandle hMem;
    DALSYSMemInfo MemInfo;
    volatile uint32 val_tcsrSOCHWVersion;
    
    eResult = DALSYS_MemRegionAlloc(
       DALSYS_MEM_PROPS_HWIO,
       DALSYS_MEM_ADDR_NOT_SPECIFIED,
       DEVCFG_TCSR_SOC_HW_ADDR, // 0xFD4A8000 TCSR_SOC_HW_VERSION
       0x1000, //4k , One page
       &hMem,
       NULL);
    
    if (eResult != DAL_SUCCESS) 
    {
        DevCfg_log("Failed to map DEVCFG_TCSR_SOC_HW_ADDR");
        return; 
    }

    eResult = DALSYS_MemInfo(hMem, &MemInfo);
    if (eResult != DAL_SUCCESS) 
    {
        DevCfg_log("Failed to get memory info\n");
        DALSYS_DestroyObject(hMem);
        return; 
    }
    
    val_tcsrSOCHWVersion = *(uint32*)MemInfo.VirtualAddr;
    gtcsrSOCHWVersion.hw_version = (uint16)(val_tcsrSOCHWVersion & 0xFFFF);
    gtcsrSOCHWVersion.soc_number = (uint16)(val_tcsrSOCHWVersion>>16);

    DALSYS_DestroyObject(hMem);
   
#endif    //ifdef TCSR_ADDR_PHS_SAME_AS_VIR
}
#endif    //ifndef DEVCFG_MULTICFG_ENABLED

/*
  Called at Runtime by clients
*/
DALProps *
DALSYS_GetPropsInfo(DEVCFG_PROP_INFO_TYPE dwInfoType)
{  
  
   switch(dwInfoType)
   {
      case DEVCFG_PROP_INFO_SOC :
         if(!SOC_PropInfo)
         {
            DevCfg_Init();
         }
         return SOC_PropInfo;
#ifdef DEVCFG_MULTIPLATFORM_ENABLED        
      case DEVCFG_PROP_INFO_PLATFORM:
         if(!PLATFORM_PropInfo)
         {
            DALSYS_Platform_PropsSymLookUp(devcfg_target_soc_info);
         }
         return PLATFORM_PropInfo;
#endif

#ifdef DEVCFG_OEM_ENABLED
      case DEVCFG_PROP_INFO_OEM:
         if(!OEM_PropInfo)
         {
            DALSYS_OEM_PropsSymLookUp(devcfg_target_soc_info);
         }
         return OEM_PropInfo;
#endif         
      default:
         return NULL;
   }
}


DALProps *
DALSYS_GetDAL_Mod(void){
    return (DALProps *)&DAL_Mod_Info;
}
  
void 
DALSYS_GetPropDir(DALPropsDir ** pDALPropsDir, 
				  DEVCFG_PROP_INFO_TYPE dwInfoType)
{
    DALProps * PropsInfo = DALSYS_GetPropsInfo(dwInfoType);
    if (PropsInfo)
    {
       *pDALPropsDir = (DALPropsDir *) PropsInfo->pDALPROP_PropBin;
    }

}

#ifdef DEVCFG__STRUCT_SIZE  
const DALSYSPropStructTblType *
#else
const void ** 
#endif
DALSYS_GetPropStructPtrArray(DALProps *PropsInfo)
{
    return PropsInfo->pDALPROP_StructPtrs;
}

void DevCfg_Init(void)
{
#ifdef DEVCFG_MULTICFG_ENABLED
    DALSYS_ReadSocHwInfo();
#endif
    DALSYS_SOC_PropsSymLookUp(devcfg_target_soc_info);
#ifdef DEVCFG_MULTIPLATFORM_ENABLED
    DALSYS_Platform_PropsSymLookUp(devcfg_target_soc_info);
#endif

#ifdef DEVCFG_OEM_ENABLED
   DALSYS_OEM_PropsSymLookUp((DEVCFG_TARGET_INFO *)DEVCFG_OEM_BASEADDR);
#endif
}
