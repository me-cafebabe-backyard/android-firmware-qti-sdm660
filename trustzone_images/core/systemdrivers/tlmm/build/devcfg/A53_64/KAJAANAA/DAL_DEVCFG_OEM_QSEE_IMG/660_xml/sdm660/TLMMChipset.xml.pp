# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/systemdrivers/tlmm/config/sdm660/TLMMChipset.xml"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 327 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/systemdrivers/tlmm/config/sdm660/TLMMChipset.xml" 2
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/systemdrivers/tlmm/config/TlmmPropDef.h" 1
# 33 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/systemdrivers/tlmm/config/TlmmPropDef.h"
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/api/dal/DALStdDef.h" 1
# 28 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/api/dal/DALStdDef.h"
typedef unsigned int uint32;




typedef unsigned short uint16;




typedef unsigned char uint8;




typedef signed int int32;




typedef signed short int16;




typedef signed char int8;
# 64 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/api/dal/DALStdDef.h"
typedef unsigned long long uint64;




typedef long long int64;





typedef unsigned char byte;





typedef unsigned long UINTN;






typedef uint32 DALBOOL;
typedef uint32 DALDEVICEID;
typedef uint32 DalPowerCmd;
typedef uint32 DalPowerDomain;
typedef uint32 DalSysReq;
typedef UINTN DALHandle;
typedef int DALResult;
typedef void * DALEnvHandle;
typedef void * DALSYSEventHandle;
typedef uint32 DALMemAddr;
typedef UINTN DALSYSMemAddr;
typedef uint32 DALInterfaceVersion;
# 108 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/api/dal/DALStdDef.h"
typedef unsigned char * DALDDIParamPtr;

typedef struct DALEventObject DALEventObject;
struct DALEventObject
{
    uint32 obj[8];
};
typedef DALEventObject * DALEventHandle;

typedef struct _DALMemObject
{
   uint32 memAttributes;
   uint32 sysObjInfo[2];
   uint32 dwLen;
   uint32 ownerVirtAddr;
   uint32 virtAddr;
   uint32 physAddr;
}
DALMemObject;

typedef struct _DALDDIMemBufDesc
{
   uint32 dwOffset;
   uint32 dwLen;
   uint32 dwUser;
}
DALDDIMemBufDesc;


typedef struct _DALDDIMemDescList
{
   uint32 dwFlags;
   uint32 dwNumBufs;
   DALDDIMemBufDesc bufList[1];
}
DALDDIMemDescList;





typedef struct DALSysMemDescBuf DALSysMemDescBuf;
struct DALSysMemDescBuf
{
   DALSYSMemAddr VirtualAddr;
   DALSYSMemAddr PhysicalAddr;
   uint32 size;
   uint32 user;
};

typedef struct DALSysMemDescList DALSysMemDescList;
struct DALSysMemDescList
{
   uint32 dwObjInfo; uint32 hOwnerProc; DALSYSMemAddr thisVirtualAddr;
   DALSYSMemAddr PhysicalAddr;
   DALSYSMemAddr VirtualAddr;
   uint32 dwCurBufIdx;
   uint32 dwNumDescBufs;
   DALSysMemDescBuf BufInfo[1];
};
# 34 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/systemdrivers/tlmm/config/TlmmPropDef.h" 2
# 51 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/systemdrivers/tlmm/config/TlmmPropDef.h"
typedef struct {
   uint32 nGpioNumber;
   uint32 nFunctionSelect;
}TLMMGpioIdType;
# 66 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/systemdrivers/tlmm/config/TlmmPropDef.h"
typedef struct {
   uint32 nTileXPU;
   uint32 nTileBase;
}TLMMXPUTileType;
# 2 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/systemdrivers/tlmm/config/sdm660/TLMMChipset.xml" 2
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/kernel/xpu3/hal/inc/HALxpu3.h" 1
# 79 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/kernel/xpu3/hal/inc/HALxpu3.h"
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/kernel/xpu3/hal/inc/660/HALxpu3Target.h" 1
# 80 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/kernel/xpu3/hal/inc/HALxpu3.h" 2
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/api/dal/HALcomdef.h" 1
# 45 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/api/dal/HALcomdef.h"
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/api/services/com_dtypes.h" 1
# 34 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/api/services/com_dtypes.h"
# 1 "/pkg/qct/software/llvm/release/arm/3.7.6/tools/lib64/include/stdint.h" 1
# 20 "/pkg/qct/software/llvm/release/arm/3.7.6/tools/lib64/include/stdint.h"
# 1 "/pkg/qct/software/llvm/release/arm/3.7.6/tools/lib64/include/bits/alltypes.h" 1
# 109 "/pkg/qct/software/llvm/release/arm/3.7.6/tools/lib64/include/bits/alltypes.h"
typedef unsigned long uintptr_t;
# 124 "/pkg/qct/software/llvm/release/arm/3.7.6/tools/lib64/include/bits/alltypes.h"
typedef long intptr_t;
# 140 "/pkg/qct/software/llvm/release/arm/3.7.6/tools/lib64/include/bits/alltypes.h"
typedef signed char int8_t;




typedef short int16_t;




typedef int int32_t;




typedef long int64_t;




typedef long intmax_t;




typedef unsigned char uint8_t;




typedef unsigned short uint16_t;




typedef unsigned int uint32_t;




typedef unsigned long uint64_t;
# 190 "/pkg/qct/software/llvm/release/arm/3.7.6/tools/lib64/include/bits/alltypes.h"
typedef unsigned long uintmax_t;
# 21 "/pkg/qct/software/llvm/release/arm/3.7.6/tools/lib64/include/stdint.h" 2

typedef int8_t int_fast8_t;
typedef int64_t int_fast64_t;

typedef int8_t int_least8_t;
typedef int16_t int_least16_t;
typedef int32_t int_least32_t;
typedef int64_t int_least64_t;

typedef uint8_t uint_fast8_t;
typedef uint64_t uint_fast64_t;

typedef uint8_t uint_least8_t;
typedef uint16_t uint_least16_t;
typedef uint32_t uint_least32_t;
typedef uint64_t uint_least64_t;
# 95 "/pkg/qct/software/llvm/release/arm/3.7.6/tools/lib64/include/stdint.h"
# 1 "/pkg/qct/software/llvm/release/arm/3.7.6/tools/lib64/include/bits/stdint.h" 1
typedef int32_t int_fast16_t;
typedef int32_t int_fast32_t;
typedef uint32_t uint_fast16_t;
typedef uint32_t uint_fast32_t;
# 96 "/pkg/qct/software/llvm/release/arm/3.7.6/tools/lib64/include/stdint.h" 2
# 35 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/api/services/com_dtypes.h" 2
# 88 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/api/services/com_dtypes.h"
typedef unsigned char boolean;







typedef uint32_t bool32;
# 146 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/api/services/com_dtypes.h"
typedef uintptr_t uintnt;
# 159 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/api/services/com_dtypes.h"
typedef unsigned short word;
typedef unsigned int dword;

typedef unsigned char uint1;
typedef unsigned short uint2;
typedef unsigned int uint4;

typedef signed char int1;
typedef signed short int2;
typedef long int int4;

typedef signed int sint31;
typedef signed short sint15;
typedef signed char sint7;

typedef uint16 UWord16 ;
typedef uint32 UWord32 ;
typedef int32 Word32 ;
typedef int16 Word16 ;
typedef uint8 UWord8 ;
typedef int8 Word8 ;
typedef int32 Vect32 ;
# 46 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/api/dal/HALcomdef.h" 2
# 81 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/kernel/xpu3/hal/inc/HALxpu3.h" 2
# 105 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/kernel/xpu3/hal/inc/HALxpu3.h"
typedef enum
{
  HAL_XPU2_NO_ERROR = 0,
  HAL_XPU2_INVALID_INSTANCE,
  HAL_XPU2_UNSUPPORTED_INSTANCE_FOR_TARGET,

  HAL_XPU2_UNSUPPORTED_HANDLER,
  HAL_XPU2_INVALID_BASE_ADDR,
  HAL_XPU2_INVALID_PARAM,
  HAL_XPU2_READ_WRITE_MISMATCH,
  HAL_XPU2_UNSUPPORTED_CFG_FOR_XPU
} HAL_xpu3_Status;


typedef enum
{
  HAL_XPU2_APCS_MPU ,
  HAL_XPU2_CRYPTO0_BAM,
  HAL_XPU2_DCC,
  HAL_XPU2_IPA_0_GSI_TOP,
  HAL_XPU2_IPA,
  HAL_XPU2_MCCC_APU,
  HAL_XPU2_MMSS,
  HAL_XPU2_MMSS_CC,
  HAL_XPU2_BAM_BLSP1_DMA,
  HAL_XPU2_BAM_BLSP2_DMA,
  HAL_XPU2_SKL,
  HAL_XPU2_SP_SCSR,
  HAL_XPU2_SSC_BLSP_BAM,
  HAL_XPU2_TLMM_XPU_EAST,
  HAL_XPU2_TLMM_XPU_NORTH,
  HAL_XPU2_TLMM_XPU_WEST,
  HAL_XPU2_UFS_ICE,
  HAL_XPU2_MNOC,
  HAL_XPU2_GCC_RPU,
  HAL_XPU2_TCSR_MUTEX,
  HAL_XPU2_TCSR_REGS,
  HAL_XPU2_BIMC_APU,
  HAL_XPU2_MCCC_APU2,
  HAL_XPU2_MPM2,
  HAL_XPU2_IMEM_APU,
  HAL_XPU2_RAMBLUR_PIMEM_APU,
  HAL_XPU2_SEC_CTRL_APU,
  HAL_XPU2_SPDM_APU,
  HAL_XPU2_ANOC1_MPU,
  HAL_XPU2_ANOC2_MPU,
  HAL_XPU2_BOOT_ROM,
  HAL_XPU2_CNOC_A1NOC_MPU,
  HAL_XPU2_CNOC_A2NOC_MPU,
  HAL_XPU2_CNOC_QDSS_MPU,
  HAL_XPU2_CNOC_SNOC_MPU,
  HAL_XPU2_CNOC_SNOC_MS_MPU,
  HAL_XPU2_LPASS_Q6SS_MPU,
  HAL_XPU2_MSS_MPU,
  HAL_XPU2_MSS_Q6_MPU,
  HAL_XPU2_IMEM_MPU,
  HAL_XPU2_PMIC_ARB,
  HAL_XPU2_QM_MPU_CFG,
  HAL_XPU2_RAMBLUR_PIMEM_MPU,
  HAL_XPU2_RPM_MSTR_MPU,
  HAL_XPU2_CFG_SSC,
  HAL_XPU2_SSC_Q6_MPU,
  HAL_XPU2_BIMC_MPU0,
  HAL_XPU2_BIMC_MPU1,
  HAL_XPU2_TLMM,
  HAL_XPU2_MSS_NAV_MPU,
  HAL_XPU2_LPASS_CFG_MPU,
  HAL_XPU2_TURING_Q6_MPU,
  HAL_XPU2_LPASS_SENSOR_BLSP_BAM,
  HAL_XPU2_TLMM_XPU_CENTER,
  HAL_XPU2_TLMM_XPU_SOUTH,
  HAL_XPU2_SDC1_SDCC_ICE,
  HAL_XPU2_TITAN_SS_APU,
  HAL_XPU2_CNOC_AOSS_MPU,
  HAL_XPU2_LLCC_BROADCAST_MPU,
  HAL_XPU2_SSC_SDC_MPU,
  HAL_DC_NOC_BROADCAST_MPU,
  HAL_DC_NOC_NON_BROADCAST_MPU,
  HAL_AOSS_MPU,
  HAL_XPU2_BIMC_MPU2,
  HAL_XPU2_BIMC_MPU3,
  HAL_MEMNOC_MS_MPU,

  HAL_XPU2_COUNT,
  HAL_XPU2_SIZE = 0x7FFFFFFF
} HAL_xpu2_XPU2Type;


typedef uint32 HAL_xpu3_ResourceGroupIDType;


typedef struct
{
  uint32 uStartLower;
  uint32 uStartUpper;
  uint32 uEndLower;
  uint32 uEndUpper;
} HAL_xpu3_ResourceGroupAddrType;


typedef enum
{
  HAL_XPU2_CONFIG_SECURE = 0x0,
  HAL_XPU2_CONFIG_NON_SECURE = 0x1,
  HAL_XPU2_CONFIG_MODEM = 0x2,
  HAL_XPU2_CONFIG_SP = 0x3,
  HAL_XPU2_CONFIG_UNOWNED = 0x4,
  HAL_XPU2_CONFIG_COUNT,
  HAL_XPU2_CONFIG_SIZE = 0x7FFFFFFF,
} HAL_xpu3_ConfigType;
# 230 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/kernel/xpu3/hal/inc/HALxpu3.h"
typedef struct
{
  bool32 bMultiVMID;
  union
  {
    struct
    {
      uint32 auVMID[((31/32) + 1)];
      uint32 auVMIDPerm[((31/16) + 1)];
    } multi;
  } Vmid_Type;
} HAL_xpu3_ResourceGroupPermissionType;



typedef struct
{
  boolean bSecureClientROEn : 0x2 +1;



  boolean bNonSecureClientROEn : 0x2 +1;




  boolean bNonSecureClientWOEn : 0x2 +1;




  boolean bSecureClientWOEn : 0x2 +1;


} HAL_xpu3_ResourceGroupClientPermType;


typedef struct
{
  HAL_xpu3_ResourceGroupAddrType resAddr;

  HAL_xpu3_ResourceGroupPermissionType resPerm;

  HAL_xpu3_ResourceGroupClientPermType clientPerm;

  HAL_xpu3_ConfigType eConfig;


} HAL_xpu3_ResourceGroupConfigType;



typedef struct
{
  HAL_xpu3_ResourceGroupPermissionType *pUnmapRGPerm;


  boolean bEnableVmidCheck : 1;

  boolean bEnablexPROTNSCheck : 1;


  boolean bSecureConfigWriteDisable : 1;



  boolean bMSAClientAccessControl : 1;


  boolean bSPClientAccessControl : 1;


  boolean bUnmapMemoryClientROEn : 0x2 +1;


  boolean bUnmapMemoryClientWOEn : 0x2 +1;


  boolean bUnmapMemoryOwnerAPPS :1;
  boolean bUnmapMemoryOwnerSP :1;
  boolean bUnmapMemoryOwnerMSA:1;

  boolean bUnmapMemoryOwnerSecure :1;

  boolean bUnmapMemorySecureROE :1;

  boolean bUnmapMemorySecureWOE :1;

} HAL_xpu3_DefaultxPU3ConfigType;


typedef enum
{
  HAL_XPU2_ERROR_O_CFG_RPT_EN = 0x1,

  HAL_XPU2_ERROR_O_CLIENT_RPT_EN = 0x2,

  HAL_XPU2_ERROR_O_CFG_INT_EN = 0x4,

  HAL_XPU2_ERROR_O_CLIENT_INT_EN = 0x8,

  HAL_XPU2_ERROR_O_SIZE = 0x7FFFFFFF
} HAL_xpu3_ErrorOptionsType;


typedef uint32 HAL_xpu3_ErrorOptionsConfigType;


typedef enum
{
  HAL_XPU2_DEVICE_RPU = 0,
  HAL_XPU2_DEVICE_APU = 1,
  HAL_XPU2_DEVICE_MPU = 2,
  HAL_XPU2_DEVICE_COUNT,
  HAL_XPU2_DEVICE_DNE = 0x7FFFFFFE,
  HAL_XPU2_DEVICE_SIZE = 0x7FFFFFFF,
} HAL_xpu3_XPUDeviceType;


typedef struct
{
  HAL_xpu3_XPUDeviceType eXpu2Type;
  uint32 uResourceGroupCount;
  uint32 uNumVMID;
  uint32 uResourceGroupRes;
  uint64 uResourceGroupResMax;
  boolean bMultiVMID : 1;
  boolean bFullPerm : 1;
  boolean bQADSupport : 0x2 +1;
  boolean bVMID_ACR : 1;
  const char *szXpu2Name;
} HAL_xpu3_XPUDeviceParamsType;


typedef enum
{
  HAL_XPU2_ERROR_F_CONFIG_PORT = 0x1,
  HAL_XPU2_ERROR_F_CLIENT_PORT = 0x2,
  HAL_XPU2_ERROR_F_MULTIPLE = 0x4,
  HAL_XPU2_ERROR_F_MULTI_CONFIG_PORT = 0x8,

  HAL_XPU2_ERROR_F_MULTI_CLIENT_PORT = 0x10,

  HAL_XPU2_ERROR_FLAGS_SIZE = 0x7FFFFFFF
} HAL_xpu3_ErrorFlagsType;


typedef uint32 HAL_xpu3_ErrorFlagsConfigType;


typedef enum
{
  HAL_XPU2_BUS_F_ERROR_AC = 0x1,

  HAL_XPU2_BUS_F_ERROR_DCD = 0x2,
  HAL_XPU2_BUS_F_ASHARED = 0x4,
  HAL_XPU2_BUS_F_AINNERSHARED = 0x8,
  HAL_XPU2_BUS_F_APRIV = 0x10,
  HAL_XPU2_BUS_F_APROTNS = 0x20,
  HAL_XPU2_BUS_F_AINST = 0x40,
  HAL_XPU2_BUS_F_AWRITE = 0x80,
  HAL_XPU2_BUS_F_AOOO = 0x100,
  HAL_XPU2_BUS_F_AFULL = 0x200,
  HAL_XPU2_BUS_F_ABURST = 0x400,
  HAL_XPU2_BUS_F_BURSTLEN = 0x800,
  HAL_XPU2_BUS_F_ARDALLOCATE = 0x1000,
  HAL_XPU2_BUS_F_AEXCLUSIVE = 0x2000,
  HAL_XPU2_BUS_F_ARDBEADNDXEN = 0x4000,
  HAL_XPU2_BUS_F_AMSSSELFAUTH = 0x8000,
  HAL_XPU2_BUS_F_SAVERESTORE_IN_PROG = 0x10000,

  HAL_XPU2_BUS_F_MSA_RG_MATCH = 0x20000,
  HAL_XPU2_BUS_F_SECURE_RG_MATCH = 0x40000,
  HAL_XPU2_BUS_F_NONSECURE_RG_MATCH = 0x80000,
  HAL_XPU2_BUS_F_SP_RG_MATCH = 0x100000,
  HAL_XPU2_BUS_F_SP = 0x200000,
  HAL_XPU2_BUS_FLAGS_SIZE = 0x7FFFFFFF
} HAL_xpu3_BusErrorFlagsType;


typedef uint32 HAL_xpu3_BusErrorFlagsMaskType;


typedef struct
{
  HAL_xpu3_ErrorFlagsConfigType uErrorFlags;
  HAL_xpu3_BusErrorFlagsMaskType uBusFlags;
  uint32 uPhysicalAddressLower32;

  uint32 uPhysicalAddressUpper32;

  uint32 uMasterId;
  uint32 uAVMID;

  uint32 uATID;
  uint32 uABID;
  uint32 uAPID;
  uint32 uALen;
  uint32 uASize;
  uint32 uAMemType;
  uint32 uAPReqPriority;

} HAL_xpu3_ErrorType;
# 454 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/kernel/xpu3/hal/inc/HALxpu3.h"
HAL_xpu3_Status HAL_xpu3_Init
  ( HAL_xpu2_XPU2Type eXpu2,
    const HAL_xpu3_DefaultxPU3ConfigType *pDefaultConfig,
    char ** ppszVersion );
# 470 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/kernel/xpu3/hal/inc/HALxpu3.h"
HAL_xpu3_Status HAL_xpu3_RestoreSecureConfig ( HAL_xpu2_XPU2Type eXpu2 );
# 483 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/kernel/xpu3/hal/inc/HALxpu3.h"
HAL_xpu3_Status HAL_xpu3_Reset ( HAL_xpu2_XPU2Type eXpu2 ) ;
# 510 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/kernel/xpu3/hal/inc/HALxpu3.h"
HAL_xpu3_Status HAL_xpu3_ConfigAccessPermissions
  ( HAL_xpu2_XPU2Type eXpu2,
    const HAL_xpu3_ResourceGroupPermissionType *pAccessConfig );
# 532 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/kernel/xpu3/hal/inc/HALxpu3.h"
HAL_xpu3_Status HAL_xpu3_ConfigUnmappedPartitionPermissions
  ( HAL_xpu2_XPU2Type eXpu2,
    const HAL_xpu3_ResourceGroupPermissionType *pUnmapRGPerm );
# 548 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/kernel/xpu3/hal/inc/HALxpu3.h"
void HAL_xpu3_EnableAPPSAuth( HAL_xpu2_XPU2Type eXpu2 );
# 561 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/kernel/xpu3/hal/inc/HALxpu3.h"
void HAL_xpu3_EnableMSSSelfAuth( HAL_xpu2_XPU2Type eXpu2 );
# 575 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/kernel/xpu3/hal/inc/HALxpu3.h"
void HAL_xpu3_EnableSPAuth( HAL_xpu2_XPU2Type eXpu2 );
# 594 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/kernel/xpu3/hal/inc/HALxpu3.h"
HAL_xpu3_Status HAL_xpu3_EnableMPUPartition
  ( HAL_xpu2_XPU2Type eXpu2,
    HAL_xpu3_ResourceGroupIDType uResID );
# 614 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/kernel/xpu3/hal/inc/HALxpu3.h"
HAL_xpu3_Status HAL_xpu3_DisableMPUPartition
  ( HAL_xpu2_XPU2Type eXpu2,
    HAL_xpu3_ResourceGroupIDType uResID );
# 638 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/kernel/xpu3/hal/inc/HALxpu3.h"
HAL_xpu3_Status HAL_xpu3_ConfigResourceGroup
  ( HAL_xpu2_XPU2Type eXpu2,
    HAL_xpu3_ResourceGroupIDType uResID,
    const HAL_xpu3_ResourceGroupConfigType *pResConfig );
# 666 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/kernel/xpu3/hal/inc/HALxpu3.h"
HAL_xpu3_Status HAL_xpu3_ConfigErrorReporting
  ( HAL_xpu2_XPU2Type eXpu2,
    HAL_xpu3_ConfigType eConfig,
    HAL_xpu3_ErrorOptionsConfigType errOpt );
# 692 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/kernel/xpu3/hal/inc/HALxpu3.h"
void HAL_xpu3_GetDeviceParameters( HAL_xpu2_XPU2Type eXpu2,
                                   HAL_xpu3_XPUDeviceParamsType *pDevParams );
# 708 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/kernel/xpu3/hal/inc/HALxpu3.h"
void HAL_xpu3_GetAccessPermissions
  ( HAL_xpu2_XPU2Type eXpu2,
    HAL_xpu3_ResourceGroupPermissionType *pAccessConfig );
# 728 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/kernel/xpu3/hal/inc/HALxpu3.h"
void HAL_xpu3_GetUnmappedPartitionPermissions
  ( HAL_xpu2_XPU2Type eXpu2,
    HAL_xpu3_ResourceGroupPermissionType *pUnmapRGPerm );
# 747 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/kernel/xpu3/hal/inc/HALxpu3.h"
void HAL_xpu3_GetResourceGroupConfig
  ( HAL_xpu2_XPU2Type eXpu2,
    HAL_xpu3_ResourceGroupIDType uResID,
    HAL_xpu3_ResourceGroupConfigType *pResConfig );
# 773 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/kernel/xpu3/hal/inc/HALxpu3.h"
void HAL_xpu3_GetErrorReportingConfig
  ( HAL_xpu2_XPU2Type eXpu2,
    HAL_xpu3_ConfigType eConfig,
    HAL_xpu3_ErrorOptionsConfigType *pErrConfig );
# 795 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/kernel/xpu3/hal/inc/HALxpu3.h"
bool32 HAL_xpu3_IsError ( HAL_xpu2_XPU2Type eXpu2,
                                   HAL_xpu3_ConfigType eConfig );
# 812 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/kernel/xpu3/hal/inc/HALxpu3.h"
void HAL_xpu3_GetError( HAL_xpu2_XPU2Type eXpu2,
                        HAL_xpu3_ConfigType eConfig,
                        HAL_xpu3_ErrorType *pError );
# 828 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/kernel/xpu3/hal/inc/HALxpu3.h"
HAL_xpu3_Status HAL_xpu3_ClearError( HAL_xpu2_XPU2Type eXpu2,
                                     HAL_xpu3_ConfigType eConfig );
# 846 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/kernel/xpu3/hal/inc/HALxpu3.h"
HAL_xpu3_Status HAL_xpu3_ClearErrorExt( HAL_xpu2_XPU2Type eXpu2,
                                        HAL_xpu3_ConfigType eConfig,
                                        HAL_xpu3_ErrorFlagsConfigType uErrorFlags );
# 866 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/kernel/xpu3/hal/inc/HALxpu3.h"
HAL_xpu3_Status HAL_xpu3_GetResourceGroupOwnerInfo
(
  HAL_xpu2_XPU2Type eXpu2,
  uint32 *puResIDMaskPtr,
  uint32 size,
  uint32 *pNumOwnership
);
# 894 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/kernel/xpu3/hal/inc/HALxpu3.h"
bool32 HAL_xpu3_IsError_NoLock( HAL_xpu2_XPU2Type eXpu2,
                                HAL_xpu3_ConfigType eConfig );
# 909 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/kernel/xpu3/hal/inc/HALxpu3.h"
HAL_xpu3_Status HAL_xpu3_ClearError_NoLock( HAL_xpu2_XPU2Type eXpu2,
                                            HAL_xpu3_ConfigType eConfig );
# 927 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/kernel/xpu3/hal/inc/HALxpu3.h"
void HAL_xpu3_GetError_NoLock( HAL_xpu2_XPU2Type eXpu2,
                               HAL_xpu3_ConfigType eConfig,
                               HAL_xpu3_ErrorType *pError );
# 945 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/kernel/xpu3/hal/inc/HALxpu3.h"
void HAL_xpu3_GetDeviceParameters_NoLock( HAL_xpu2_XPU2Type eXpu2,
                                          HAL_xpu3_XPUDeviceParamsType *pDevParams );
# 964 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/kernel/xpu3/hal/inc/HALxpu3.h"
void HAL_xpu3_GetResourceGroupConfig_NoLock
  ( HAL_xpu2_XPU2Type eXpu2,
    HAL_xpu3_ResourceGroupIDType uResID,
    HAL_xpu3_ResourceGroupConfigType *pResConfig );
# 984 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/kernel/xpu3/hal/inc/HALxpu3.h"
HAL_xpu3_Status HAL_xpu3_GetResourceGroupOwnerInfo_NoLock
(
  HAL_xpu2_XPU2Type eXpu2,
  uint32 *puResIDMaskPtr,
  uint32 size,
  uint32 *pNumOwnership
);
# 1002 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/kernel/xpu3/hal/inc/HALxpu3.h"
HAL_xpu3_Status HAL_xpu3_ClearRG_Owner(HAL_xpu2_XPU2Type eXpu2, uint32 resid);







HAL_xpu3_Status HAL_xpu3_ResetRG_addr(HAL_xpu2_XPU2Type eXpu2);


HAL_xpu3_Status HAL_xpu3_ConfigUnmapPartition
(
  HAL_xpu2_XPU2Type eXpu2,
  const HAL_xpu3_DefaultxPU3ConfigType *pDefaultConfig
);
# 3 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/systemdrivers/tlmm/config/sdm660/TLMMChipset.xml" 2





<driver name="NULL">
  <global_def>
    <var_seq name="tlmm_xpu_pins" type=DALPROP_DATA_TYPE_UINT32_SEQ>
      0xFFFFFFFF, end
    </var_seq>
    <var_seq name="tlmm_xpu_sections" type=DALPROP_DATA_TYPE_UINT32_SEQ>
      HAL_XPU2_TLMM_XPU_SOUTH,
      HAL_XPU2_TLMM_XPU_CENTER,
      HAL_XPU2_TLMM_XPU_NORTH,
      end
    </var_seq>
    <var_seq name="tlmm_tile_bases" type=DALPROP_DATA_TYPE_UINT32_SEQ>
      (0x03000000 + 0x00100000),
      (0x03000000 + 0x00500000),
      (0x03000000 + 0x00900000),
      end
    </var_seq>

  </global_def>
  <device id="/tlmm/configs">
    <props name="blsp_spi_mosi[1]" type="TLMMGpioIdType">{0, 1}</props>
    <props name="blsp_spi_miso[1]" type="TLMMGpioIdType">{1, 1}</props>
    <props name="blsp_spi_cs_n[1]" type="TLMMGpioIdType">{2, 1}</props>
    <props name="blsp_spi_clk[1]" type="TLMMGpioIdType">{3, 1}</props>
    <props name="blsp_spi_mosi[2]" type="TLMMGpioIdType">{4, 1}</props>
    <props name="blsp_spi_miso[2]" type="TLMMGpioIdType">{5, 1}</props>
    <props name="blsp_spi_cs_n[2]" type="TLMMGpioIdType">{6, 1}</props>
    <props name="blsp_spi_clk[2]" type="TLMMGpioIdType">{7, 1}</props>
    <props name="blsp_spi_mosi[3]" type="TLMMGpioIdType">{8, 1}</props>
    <props name="blsp_spi_miso[3]" type="TLMMGpioIdType">{9, 1}</props>
    <props name="blsp_spi_cs_n[3]" type="TLMMGpioIdType">{10, 1}</props>
    <props name="blsp_spi_clk[3]" type="TLMMGpioIdType">{11, 1}</props>
    <props name="blsp_spi_mosi[4]" type="TLMMGpioIdType">{12, 1}</props>
    <props name="blsp_spi_miso[4]" type="TLMMGpioIdType">{13, 1}</props>
    <props name="blsp_spi_cs_n[4]" type="TLMMGpioIdType">{14, 1}</props>
    <props name="blsp_spi_clk[4]" type="TLMMGpioIdType">{15, 1}</props>
    <props name="blsp_spi_mosi[5]" type="TLMMGpioIdType">{16, 2}</props>
    <props name="blsp_spi_miso[5]" type="TLMMGpioIdType">{17, 2}</props>
    <props name="blsp_spi_cs_n[5]" type="TLMMGpioIdType">{18, 2}</props>
    <props name="blsp_spi_clk[5]" type="TLMMGpioIdType">{19, 2}</props>
    <props name="blsp_spi_mosi[6]" type="TLMMGpioIdType">{20, 1}</props>
    <props name="blsp_spi_miso[6]" type="TLMMGpioIdType">{21, 1}</props>
    <props name="blsp_spi_cs_n[6]" type="TLMMGpioIdType">{22, 1}</props>
    <props name="blsp_spi_clk[6]" type="TLMMGpioIdType">{23, 1}</props>
    <props name="blsp_spi_mosi[7]" type="TLMMGpioIdType">{24, 1}</props>
    <props name="blsp_spi_miso[7]" type="TLMMGpioIdType">{25, 1}</props>
    <props name="blsp_spi_cs_n[7]" type="TLMMGpioIdType">{26, 1}</props>
    <props name="blsp_spi_clk[7]" type="TLMMGpioIdType">{27, 1}</props>
    <props name="blsp_spi_mosi8_mira" type="TLMMGpioIdType">{28, 1}</props>
    <props name="blsp_spi_miso8_mira" type="TLMMGpioIdType">{29, 1}</props>
    <props name="blsp_spi_cs_n8_mira" type="TLMMGpioIdType">{30, 1}</props>
    <props name="blsp_spi_cs1_n[3]" type="TLMMGpioIdType">{30, 4}</props>
    <props name="blsp_spi_clk8_mira" type="TLMMGpioIdType">{31, 1}</props>
    <props name="blsp_spi_mosi8_mirb" type="TLMMGpioIdType">{40, 3}</props>
    <props name="blsp_spi_miso8_mirb" type="TLMMGpioIdType">{41, 3}</props>
    <props name="blsp_spi_clk8_mirb" type="TLMMGpioIdType">{44, 3}</props>
    <props name="blsp_spi_cs1_n[1]" type="TLMMGpioIdType">{46, 1}</props>
    <props name="blsp_spi_cs_n8_mirb" type="TLMMGpioIdType">{52, 2}</props>
    <props name="blsp_spi_cs1_n[8]" type="TLMMGpioIdType">{64, 2}</props>
    <props name="blsp_spi_cs2_n[3]" type="TLMMGpioIdType">{65, 2}</props>
    <props name="blsp_spi_cs2_n[8]" type="TLMMGpioIdType">{76, 1}</props>

    <props name="blsp_i2c_sda[1]" type="TLMMGpioIdType">{2, 3}</props>
    <props name="blsp_i2c_scl[1]" type="TLMMGpioIdType">{3, 3}</props>
    <props name="blsp_i2c_sda[2]" type="TLMMGpioIdType">{6, 2}</props>
    <props name="blsp_i2c_scl[2]" type="TLMMGpioIdType">{7, 2}</props>
    <props name="blsp_i2c_sda[3]" type="TLMMGpioIdType">{10, 2}</props>
    <props name="blsp_i2c_scl[3]" type="TLMMGpioIdType">{11, 2}</props>
    <props name="blsp_i2c_sda[4]" type="TLMMGpioIdType">{14, 2}</props>
    <props name="blsp_i2c_scl[4]" type="TLMMGpioIdType">{15, 2}</props>
    <props name="blsp_i2c_sda[5]" type="TLMMGpioIdType">{18, 3}</props>
    <props name="blsp_i2c_scl[5]" type="TLMMGpioIdType">{19, 3}</props>
    <props name="blsp_i2c_sda[6]" type="TLMMGpioIdType">{22, 3}</props>
    <props name="blsp_i2c_scl[6]" type="TLMMGpioIdType">{23, 3}</props>
    <props name="blsp_i2c_sda[7]" type="TLMMGpioIdType">{26, 3}</props>
    <props name="blsp_i2c_scl[7]" type="TLMMGpioIdType">{27, 3}</props>
    <props name="BLSP_I2C_SDA8_MIRA" type="TLMMGpioIdType">{30, 3}</props>
    <props name="BLSP_I2C_SCL8_MIRA" type="TLMMGpioIdType">{31, 3}</props>
    <props name="BLSP_I2C_SCL8_MIRB" type="TLMMGpioIdType">{44, 4}</props>
    <props name="BLSP_I2C_SDA8_MIRB" type="TLMMGpioIdType">{52, 3}</props>

    <props name="tlmm_gpio_test_pin" type="TLMMGpioIdType">{8, 1}</props>

    <props name="blsp_uart_tx[1]" type="TLMMGpioIdType">{0, 2}</props>
    <props name="blsp_uart_rx[1]" type="TLMMGpioIdType">{1, 2}</props>
    <props name="blsp_uart_cts_n[1]" type="TLMMGpioIdType">{2, 2}</props>
    <props name="blsp_uart_rfr_n[1]" type="TLMMGpioIdType">{3, 2}</props>
    <props name="blsp_uart_tx[5]" type="TLMMGpioIdType">{16, 1}</props>
    <props name="blsp_uart_rx[5]" type="TLMMGpioIdType">{17, 1}</props>
    <props name="blsp_uart_cts_n[5]" type="TLMMGpioIdType">{18, 1}</props>
    <props name="blsp_uart_rfr_n[5]" type="TLMMGpioIdType">{19, 1}</props>
    <props name="blsp_uart_tx[2]" type="TLMMGpioIdType">{20, 2}</props>
    <props name="blsp_uart_rx[2]" type="TLMMGpioIdType">{21, 2}</props>
    <props name="blsp_uart_cts_n[2]" type="TLMMGpioIdType">{22, 2}</props>
    <props name="blsp_uart_rfr_n[2]" type="TLMMGpioIdType">{23, 2}</props>
    <props name="BLSP_UART_TX6_MIRA" type="TLMMGpioIdType">{24, 2}</props>
    <props name="BLSP_UART_RX6_MIRA" type="TLMMGpioIdType">{25, 2}</props>
    <props name="BLSP_UART_CTS_N6_MIRA" type="TLMMGpioIdType">{26, 2}</props>
    <props name="BLSP_UART_RFR_N6_MIRA" type="TLMMGpioIdType">{27, 2}</props>
    <props name="BLSP_UART_TX6_MIRB" type="TLMMGpioIdType">{28, 2}</props>
    <props name="BLSP_UART_RX6_MIRB" type="TLMMGpioIdType">{29, 2}</props>
    <props name="BLSP_UART_CTS_N6_MIRB" type="TLMMGpioIdType">{30, 2}</props>
    <props name="BLSP_UART_RFR_N6_MIRB" type="TLMMGpioIdType">{31, 2}</props>


    <props name="tlmm_xpu_protection" type=DALPROP_ATTR_TYPE_UINT32_SEQ_PTR>
      tlmm_xpu_pins
    </props>
    <props name="tlmm_xpu" type=DALPROP_ATTR_TYPE_UINT32_SEQ_PTR>
      tlmm_xpu_sections
    </props>
    <props name="tlmm_tiles" type=DALPROP_ATTR_TYPE_UINT32_SEQ_PTR>
      tlmm_tile_bases
    </props>
    <props name="tlmm_num_tiles" type=DALPROP_ATTR_TYPE_UINT32>
      3
    </props>
    <props name="tlmm_base" type=DALPROP_ATTR_TYPE_UINT32>
      0x01000000
    </props>
    <props name="tlmm_offset" type=DALPROP_ATTR_TYPE_UINT32>
      0x00010000
    </props>
    <props name="tlmm_total_gpio" type=DALPROP_ATTR_TYPE_UINT32>
      114
    </props>
  </device>
</driver>
