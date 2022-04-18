#include "../src/devcfg_pm_spmi_config.h"
#include "../src/devcfg_tz_config.h"
typedef unsigned long uintptr_t;
typedef long intptr_t;
typedef signed char int8_t;
typedef short int16_t;
typedef int int32_t;
typedef long int64_t;
typedef long intmax_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long uint64_t;
typedef unsigned long uintmax_t;
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
typedef int32_t int_fast16_t;
typedef int32_t int_fast32_t;
typedef uint32_t uint_fast16_t;
typedef uint32_t uint_fast32_t;
typedef unsigned char boolean;
typedef uint32_t bool32;
typedef uint32_t uint32;
typedef uint16_t uint16;
typedef uint8_t uint8;
typedef int32_t int32;
typedef int16_t int16;
typedef int8_t int8;
typedef uintptr_t uintnt;
typedef uint8_t byte;
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
      typedef long long int64;
      typedef unsigned long long uint64;
static inline uint8 spmiEncodeVSid(uint8 busId, uint8 slaveId) {
    return (busId << 4) | (slaveId & 0x0F);
}
static inline void spmiDecodeVSid(uint8 vSlaveId, uint8* busId, uint8* slaveId) {
    if(busId) *busId = vSlaveId >> 4;
    if(slaveId) *slaveId = vSlaveId & 0x0F;
}
typedef enum
{
    SPMI_SUCCESS,
    SPMI_FAILURE_BUS_BUSY,
    SPMI_FAILURE_BUS_DISABLED,
    SPMI_FAILURE_COMMAND_NOT_SUPPORTED,
    SPMI_FAILURE_COMMAND_NOT_ALLOWED,
    SPMI_FAILURE_TRANSACTION_FAILED,
    SPMI_FAILURE_TRANSACTION_DENIED,
    SPMI_FAILURE_TRANSACTION_DROPPED,
    SPMI_FAILURE_TRANSACTION_TIMEOUT,
    SPMI_FAILURE_SERIAL_CLK_IS_OFF,
    SPMI_FAILURE_AHB_CLK_IS_OFF,
    SPMI_FAILURE_FUNCTIONALITY_NOT_SUPPORTED,
    SPMI_FAILURE_INVALID_PARAMETER,
    SPMI_FAILURE_INIT_FAILED,
    SPMI_FAILURE_NOT_INITIALIZED,
    SPMI_FAILURE_INVALID_BUFFER,
    SPMI_FAILURE_TOO_MANY_ENTRIES,
    SPMI_FAILURE_NOT_ENOUGH_RGS,
    SPMI_FAILURE_INVALID_BUS_ID,
    SPMI_FAILURE_INVALID_MASTER_ID,
    SPMI_FAILURE_INVALID_SLAVE_ID,
    SPMI_FAILURE_INVALID_ADDRESS,
    SPMI_FAILURE_INVALID_PERIPH_ID,
    SPMI_FAILURE_INVALID_PORT_ID,
    SPMI_FAILURE_INVALID_OWNER,
    SPMI_FAILURE_INVALID_CHAN_NUM,
    SPMI_FAILURE_CHANNEL_RESERVED,
    SPMI_FAILURE_CHANNEL_NOT_FOUND,
    SPMI_FAILURE_MEMORY_NOT_AVAILABLE,
    SPMI_FAILURE_INVALID_TOKEN,
    SPMI_RESULT_MAX
} Spmi_Result;
typedef enum
{
    SPMI_ACCESS_PRIORITY_LOW = 0,
    SPMI_ACCESS_PRIORITY_HIGH = 1,
    SPMI_ACCESS_PRIORITY_COUNT = 2
} Spmi_AccessPriority;
typedef enum
{
    SPMI_COMMAND_RESET,
    SPMI_COMMAND_SLEEP,
    SPMI_COMMAND_SHUTDOWN,
    SPMI_COMMAND_WAKEUP,
    SPMI_COMMAND_COUNT
} Spmi_Command;
typedef void* (*SpmiIsr)(void* ctx, uint32 mask);
typedef Spmi_Result SpmiBus_ResultType;
typedef Spmi_Result SpmiCfg_ResultType;
typedef Spmi_Result SpmiIntrCtlr_ResultType;
typedef Spmi_Command SpmiBus_CommandType;
typedef Spmi_AccessPriority SpmiBus_AccessPriorityType;
typedef struct
{
    uint8 slaveId;
    uint8 periphId;
    uint16 channel;
    uint8 intOwner;
    uint8 periphOwner;
} SpmiBusCfg_ChannelCfg;
typedef struct
{
    uint8 slaveId;
    uint16 address;
} SpmiBusCfg_Ppid;
typedef struct
{
    uint8 pvcPortId;
    Spmi_AccessPriority priority;
    SpmiBusCfg_Ppid* ppids;
    uint32 numPpids;
} SpmiBusCfg_PvcPortCfg;
typedef struct
{
    uint8 owner;
    uint32 startAddr;
    uint32 size;
    uint16 startIdx;
    uint16 endIdx;
} SpmiBusCfg_RGConfig;
Spmi_Result SpmiBusCfg_Init(boolean initHw);
Spmi_Result SpmiBusCfg_DeInit(void);
Spmi_Result SpmiBusCfg_GetChannelInfo(uint8 busId, uint16 channel, uint8* slaveId, uint8* periphId, uint8* owner);
Spmi_Result SpmiBusCfg_GetPeripherialInfo(uint8 busId, uint8 slaveId, uint8 periphId, uint16* channel, uint8* owner);
Spmi_Result SpmiBusCfg_SetDynamicChannelMode(uint8 busId, boolean enabled);
Spmi_Result SpmiBusCfg_ConfigureChannels(SpmiBusCfg_ChannelCfg* entries, uint32 numEntries);
Spmi_Result SpmiBusCfg_ConfigurePeripherals(uint8 busId, SpmiBusCfg_ChannelCfg* entries, uint32 numEntries,
                                            SpmiBusCfg_RGConfig* rgCfg, uint32* rgCount);
Spmi_Result SpmiBusCfg_CalculateRGConfig(uint8 busId, SpmiBusCfg_ChannelCfg* entries, uint32 numEntries,
                                         SpmiBusCfg_RGConfig* rgCfg, uint32* rgCount);
Spmi_Result SpmiBusCfg_ConfigurePvcPort(uint8 busId, const SpmiBusCfg_PvcPortCfg* portCfg);
Spmi_Result SpmiBusCfg_SetPortPriorities(uint8 busId, uint8* ports, uint32 numPorts);
Spmi_Result SpmiBusCfg_SetPVCPortsEnabled(uint8 busId, boolean enable);
typedef SpmiBusCfg_ChannelCfg SpmiCfg_ChannelCfg;
typedef SpmiBusCfg_Ppid SpmiCfg_Ppid;
typedef SpmiBusCfg_PvcPortCfg SpmiCfg_PvcPortCfg;
typedef SpmiBusCfg_RGConfig SpmiCfg_RGConfig;
inline Spmi_Result SpmiCfg_Init(boolean initHw)
{
    return SpmiBusCfg_Init(initHw);
}
inline Spmi_Result SpmiCfg_DeInit(void)
{
    return SpmiBusCfg_DeInit();
}
inline Spmi_Result SpmiCfg_GetChannelInfo(uint16 channel, uint8* slaveId, uint8* periphId, uint8* owner)
{
    return SpmiBusCfg_GetChannelInfo(0, channel, slaveId, periphId, owner);
}
inline Spmi_Result SpmiCfg_GetPeripherialInfo(uint8 slaveId, uint8 periphId, uint16* channel, uint8* owner)
{
    return SpmiBusCfg_GetPeripherialInfo(0, slaveId, periphId, channel, owner);
}
inline Spmi_Result SpmiCfg_SetDynamicChannelMode(boolean enabled)
{
    return SpmiBusCfg_SetDynamicChannelMode(0, enabled);
}
inline Spmi_Result SpmiCfg_ConfigureChannels(SpmiCfg_ChannelCfg* entries, uint32 numEntries)
{
    return SpmiBusCfg_ConfigureChannels(entries, numEntries);
}
inline Spmi_Result SpmiCfg_ConfigurePeripherals(SpmiCfg_ChannelCfg* entries, uint32 numEntries,
                                                SpmiCfg_RGConfig* rgCfg, uint32* rgCount)
{
    return SpmiBusCfg_ConfigurePeripherals(0, entries, numEntries, rgCfg, rgCount);
}
inline Spmi_Result SpmiCfg_CalculateRGConfig(SpmiCfg_ChannelCfg* entries, uint32 numEntries,
                                             SpmiCfg_RGConfig* rgCfg, uint32* rgCount)
{
    return SpmiBusCfg_CalculateRGConfig(0, entries, numEntries, rgCfg, rgCount);
}
inline Spmi_Result SpmiCfg_ConfigurePvcPort(const SpmiCfg_PvcPortCfg* portCfg)
{
    return SpmiBusCfg_ConfigurePvcPort(0, portCfg);
}
inline Spmi_Result SpmiCfg_SetPortPriorities(uint8* ports, uint32 numPorts)
{
    return SpmiBusCfg_SetPortPriorities(0, ports, numPorts);
}
inline Spmi_Result SpmiCfg_SetPVCPortsEnabled(boolean enable)
{
    return SpmiBusCfg_SetPVCPortsEnabled(0, enable);
}
typedef enum
{
  HAL_XPU2_NO_ERROR = 0,
  HAL_XPU2_INVALID_INSTANCE,
  HAL_XPU2_UNSUPPORTED_INSTANCE_FOR_TARGET,
  HAL_XPU2_UNSUPPORTED_HANDLER,
  HAL_XPU2_INVALID_BASE_ADDR,
  HAL_XPU2_INVALID_PARAM,
  HAL_XPU2_READ_WRITE_MISMATCH
} HAL_xpu2_Status;
typedef enum
{
  HAL_XPU2_KPSS_MPU = 0,
  HAL_XPU2_APCS_MPU = HAL_XPU2_KPSS_MPU,
  HAL_XPU2_KPSS_L2,
  HAL_XPU2_BIMC_APU,
  HAL_XPU2_BIMC_MPU0,
  HAL_XPU2_BIMC_MPU1,
  HAL_XPU2_BOOT_ROM,
  HAL_XPU2_CRYPTO0_BAM,
  HAL_XPU2_CRYPTO1_BAM,
  HAL_XPU2_DEHR,
  HAL_XPU2_CLK_CTL,
  HAL_XPU2_LPASS_COMMON,
  HAL_XPU2_LPASS_CORE_CSR,
  HAL_XPU2_LPASS_LCC,
  HAL_XPU2_LPASS_LPAIF,
  HAL_XPU2_LPASS_LPM,
  HAL_XPU2_LPASS_QDSP6SS,
  HAL_XPU2_LPASS_RSMPLR,
  HAL_XPU2_LPASS_SLIMBUS,
  HAL_XPU2_LPASS_TOP,
  HAL_XPU2_CAMERA_SS,
  HAL_XPU2_MMSS_A_VBIF_JPEG,
  HAL_XPU2_MMSS_A_VBIF_VFE,
  HAL_XPU2_MMSS_DM_APU,
  HAL_XPU2_MMSS_DM_MPU,
  HAL_XPU2_MMSS_OCMEM_MPU0,
  HAL_XPU2_MMSS_OCMEM_MPU1,
  HAL_XPU2_MMSS_OCMEM_APU,
  HAL_XPU2_MMSS_OXILI_CX,
  HAL_XPU2_MMSS_OXILI_VBIF,
  HAL_XPU2_MMSS_SNOC,
  HAL_XPU2_MMSS_MDSS_VBIF,
  HAL_XPU2_MMSS_VENUS,
  HAL_XPU2_MMSS_VENUS_VBIF,
  HAL_XPU2_MDSS_APU,
  HAL_XPU2_MMSS_CC,
  HAL_XPU2_MMSS_MISC,
  HAL_XPU2_MMSS_MNOC,
  HAL_XPU2_MMSS_ONOC,
  HAL_XPU2_MMSS_RBCPR,
  HAL_XPU2_MPM2,
  HAL_XPU2_MSS,
  HAL_XPU2_IMEM_APU,
  HAL_XPU2_IMEM_MPU,
  HAL_XPU2_PERIPH_SS_APU,
  HAL_XPU2_BAM_DMA,
  HAL_XPU2_BAM_BLSP1_DMA,
  HAL_XPU2_BLSP_BAM = HAL_XPU2_BAM_BLSP1_DMA,
  HAL_XPU2_BAM_BLSP2_DMA,
  HAL_XPU2_PNOC_MPU,
  HAL_XPU2_BAM_SDCC1,
  HAL_XPU2_BAM_SDCC2,
  HAL_XPU2_BAM_SDCC3,
  HAL_XPU2_BAM_SDCC4,
  HAL_XPU2_TSIF,
  HAL_XPU2_USB1_HS,
  HAL_XPU2_USB2_HSIC,
  HAL_XPU2_PMIC_ARB,
  HAL_XPU2_PMIC_ARB_SPMI,
  HAL_XPU2_RPM_APU,
  HAL_XPU2_RPM_M3,
  HAL_XPU2_RPM_MSG_RAM,
  HAL_XPU2_SEC_CTRL_APU,
  HAL_XPU2_SPDM_APU,
  HAL_XPU2_TCSR_MUTEX,
  HAL_XPU2_TCSR_REGS,
  HAL_XPU2_TLMM,
  HAL_XPU2_USB30,
  HAL_XPU2_PRONTO,
  HAL_XPU2_EBI1_CFG,
  HAL_XPU2_RBCR_QDSS,
  HAL_XPU2_SNOC_CFG,
  HAL_XPU2_QPIC_BAM,
  HAL_XPU2_QPIC_NAND,
  HAL_XPU2_IPA,
  HAL_XPU2_CRYPTO2_BAM,
  HAL_XPU2_VBIF_APU,
  HAL_XPU2_BCSS_APU,
  HAL_XPU2_EMAC,
  HAL_XPU2_KLM,
  HAL_XPU2_MMSS_VPU_MAPLE,
  HAL_XPU2_MMSS_VPU_VBIF_APU,
  HAL_XPU2_MMSS_VCAP_APU,
  HAL_XPU2_MMSS_VCAP_VBIF_APU,
  HAL_XPU2_PCIE20_MPU,
  HAL_XPU2_PCIE20_APU,
  HAL_XPU2_USB_HS_SEC,
  HAL_XPU2_SATA_APU,
  HAL_XPU2_MMSS_APU,
  HAL_XPU2_USB3_HSIC,
  HAL_XPU2_SPSS_APU,
  HAL_XPU2_LPASS_CORE,
  HAL_XPU2_LPASS_QDSP6,
  HAL_XPU2_MMSS_MM_AVSYNC,
  HAL_XPU2_PCIE0_APU,
  HAL_XPU2_PCIE1_APU,
  HAL_XPU2_SMMUV2,
  HAL_XPU2_UFS,
  HAL_XPU2_PCIE0_MPU,
  HAL_XPU2_PCIE1_MPU,
  HAL_XPU2_LPASS_SB1,
  HAL_XPU2_MMSS_A_RICA,
  HAL_XPU2_MMSS_A_VBIF_CPP_VBIF,
  HAL_XPU2_FD_XPU2,
  HAL_XPU2_UFS_ICE,
  HAL_XPU2_MMSS_A_VBIF_FD_VBIF,
  HAL_XPU2_MMSS_A_VBIF_RICA_VBIF,
  HAL_XPU2_PCNOC_CFG,
  HAL_XPU2_PRNG_CFG,
  HAL_XPU2_RPM_CFG,
  HAL_XPU2_SMMU_500_DIME_MPU,
  HAL_XPU2_SMMU_500_GPS_MPU,
  HAL_XPU2_SMMU_500_QDSP_MPU,
  HAL_XPU2_SMMU_500_TCU_MPU,
  HAL_XPU2_DCC,
  HAL_XPU2_MMAGIC_DSA_MPU,
  HAL_XPU2_MMAGIC_XPU2_MNOC,
  HAL_XPU2_SSC_BLSP_BAM,
  HAL_XPU2_CFG_ANOC0_CFG,
  HAL_XPU2_CFG_ANOC1_CFG,
  HAL_XPU2_CFG_ANOC2_CFG,
  HAL_XPU2_CFG_CPR,
  HAL_XPU2_CFG_SSC,
  HAL_XPU2_RAMBLUR_PIMEM_MPU,
  HAL_XPU2_RPM_MSTR_MPU,
  HAL_XPU2_SSC_Q6_MPU,
  HAL_XPU2_RAMBLUR_PIMEM_APU,
  HAL_XPU2_SDC1_SDCC_ICE,
  HAL_XPU2_SKL,
  HAL_XPU2_ANOC1_MPU,
  HAL_XPU2_ANOC2_MPU,
  HAL_XPU2_MSS_MPU,
  HAL_XPU2_MSS_Q6_MPU,
  HAL_XPU2_BIMC_S_APP,
  HAL_XPU2_SDC1_SDCC,
  HAL_XPU2_SDC2_SDCC,
  HAL_XPU2_IPA_BAM_NDP,
  HAL_XPU2_CFG_DSA,
  HAL_XPU2_Q6PCNOC_CFG,
  HAL_XPU2_A5X,
  HAL_XPU2_CE_SMMU_SS_MPU,
  HAL_XPU2_IPA_SMMU_SS_MPU,
  HAL_XPU2_QPIC_QPIC,
  HAL_XPU2_QPIC_QPIC_MPU,
  HAL_XPU2_SEC_CTRL_APU_V2,
  HAL_XPU2_COUNT,
  HAL_XPU2_SIZE = 0x7FFFFFFF
} HAL_xpu2_XPU2Type;
typedef uint32 HAL_xpu2_ResourceGroupIDType;
typedef struct
{
  uint32 uStartLower;
  uint32 uStartUpper;
  uint32 uEndLower;
  uint32 uEndUpper;
} HAL_xpu2_ResourceGroupAddrType;
typedef enum
{
  HAL_XPU2_CONFIG_SECURE = 0x0,
  HAL_XPU2_CONFIG_NON_SECURE = 0x1,
  HAL_XPU2_CONFIG_MODEM = 0x2,
  HAL_XPU2_CONFIG_COUNT,
  HAL_XPU2_CONFIG_SIZE = 0x7FFFFFFF,
} HAL_xpu2_ConfigType;
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
    struct
    {
      bool32 bRWGlobalEn;
      bool32 bRWVMIDValid;
      uint32 uRWVMID;
      bool32 bROGlobalEn;
      bool32 bROVMIDValid;
      uint32 uROVMID;
    } single;
  } Vmid_Type;
} HAL_xpu2_ResourceGroupPermissionType;
typedef struct
{
  boolean bSecureClientROEn : 1;
  boolean bNonSecureClientROEn : 1;
  boolean bMSAClientROEn : 1;
  boolean bNonSecureClientRWEn : 1;
  boolean bMSAClientRWEn : 1;
  boolean bSecureClientRWEn : 1;
} HAL_xpu2_ResourceGroupClientPermType;
typedef struct
{
  HAL_xpu2_ResourceGroupAddrType resAddr;
  HAL_xpu2_ResourceGroupPermissionType resPerm;
  HAL_xpu2_ResourceGroupClientPermType clientPerm;
  HAL_xpu2_ConfigType eConfig;
} HAL_xpu2_ResourceGroupConfigType;
typedef struct
{
  HAL_xpu2_ResourceGroupPermissionType *pUnmapRGPerm;
  HAL_xpu2_ResourceGroupPermissionType *pAccessMaskTablePerm;
  boolean bEnableSecureAMT : 1;
  boolean bEnableNonSecureAMT : 1;
  boolean bEnableVmidCheck : 1;
  boolean bEnablexPROTNSCheck : 1;
  boolean bSecureConfigWriteDisable : 1;
  boolean bEnableSecureAMT2MegPageSize : 1;
  boolean bEnableNonSecureAMT2MegPageSize : 1;
  boolean bMSAClientAccessControl : 1;
  boolean bAMTMSAClientROEn : 1;
  boolean bAMTMSAClientRWEn : 1;
  boolean bMSAUnmapMemoryClientROEn : 1;
  boolean bMSAUnmapMemoryClientRWEn : 1;
} HAL_xpu2_DefaultxPU2ConfigType;
typedef enum
{
  HAL_XPU2_ERROR_O_DECODE_EN = 0x1,
  HAL_XPU2_ERROR_O_INTERRUPT_EN = 0x2,
  HAL_XPU2_ERROR_O_CLIENT_RPT_EN = 0x4,
  HAL_XPU2_ERROR_O_CFG_RPT_EN = 0x8,
  HAL_XPU2_ERROR_O_NS_RES_CLIENT_EN = 0x10,
  HAL_XPU2_ERROR_O_NS_RES_CFG_EN = 0x20,
  HAL_XPU2_ERROR_O_CLIENT_INT_EN = 0x40,
  HAL_XPU2_ERROR_O_CFG_INT_EN = 0x80,
  HAL_XPU2_ERROR_O_SIZE = 0x7FFFFFFF
} HAL_xpu2_ErrorOptionsType;
typedef uint32 HAL_xpu2_ErrorOptionsConfigType;
typedef enum
{
  HAL_XPU2_DEVICE_RPU = 0,
  HAL_XPU2_DEVICE_APU = 1,
  HAL_XPU2_DEVICE_MPU = 2,
  HAL_XPU2_DEVICE_COUNT,
  HAL_XPU2_DEVICE_DNE = 0x7FFFFFFE,
  HAL_XPU2_DEVICE_SIZE = 0x7FFFFFFF,
} HAL_xpu2_XPUDeviceType;
typedef enum
{
  HAL_XPU2_AMT_1MB_PAGE,
  HAL_XPU2_AMT_2MB_PAGE,
  HAL_XPU2_AMT_DNE_PAGE = 0x7FFFFFFE,
  HAL_XPU2_AMT_SIZE = 0x7FFFFFFF,
} HAL_xpu2_AMTPageSizeType;
typedef struct
{
  HAL_xpu2_XPUDeviceType eXpu2Type;
  uint32 uResourceGroupCount;
  uint32 uNumVMID;
  uint32 uResourceGroupRes;
  uint32 uResourceGroupResMax;
  boolean bMultiVMID : 1;
  boolean bFullPerm : 1;
  boolean bAMTSupport : 1;
  boolean bMSASupport : 1;
  HAL_xpu2_AMTPageSizeType eAMTPageSize;
  const char *szXpu2Name;
} HAL_xpu2_XPUDeviceParamsType;
typedef enum
{
  HAL_XPU2_ERROR_F_CONFIG_PORT = 0x1,
  HAL_XPU2_ERROR_F_CLIENT_PORT = 0x2,
  HAL_XPU2_ERROR_F_MULTIPLE = 0x4,
  HAL_XPU2_ERROR_F_MULTI_CONFIG_PORT = 0x8,
  HAL_XPU2_ERROR_F_MULTI_CLIENT_PORT = 0x10,
  HAL_XPU2_ERROR_FLAGS_SIZE = 0x7FFFFFFF
} HAL_xpu2_ErrorFlagsType;
typedef uint32 HAL_xpu2_ErrorFlagsConfigType;
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
  HAL_XPU2_BUS_FLAGS_SIZE = 0x7FFFFFFF
} HAL_xpu2_BusErrorFlagsType;
typedef uint32 HAL_xpu2_BusErrorFlagsMaskType;
typedef struct
{
  HAL_xpu2_ErrorFlagsConfigType uErrorFlags;
  HAL_xpu2_BusErrorFlagsMaskType uBusFlags;
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
} HAL_xpu2_ErrorType;
HAL_xpu2_Status HAL_xpu2_Init
  ( HAL_xpu2_XPU2Type eXpu2,
    const HAL_xpu2_DefaultxPU2ConfigType *pDefaultConfig,
    char ** ppszVersion );
HAL_xpu2_Status HAL_xpu2_RestoreSecureConfig ( HAL_xpu2_XPU2Type eXpu2 );
HAL_xpu2_Status HAL_xpu2_Reset ( HAL_xpu2_XPU2Type eXpu2 ) ;
void HAL_xpu2_Save ( HAL_xpu2_XPU2Type eXpu2 );
void HAL_xpu2_Restore ( HAL_xpu2_XPU2Type eXpu2 );
HAL_xpu2_Status HAL_xpu2_ConfigAccessPermissions
  ( HAL_xpu2_XPU2Type eXpu2,
    const HAL_xpu2_ResourceGroupPermissionType *pAccessConfig );
HAL_xpu2_Status HAL_xpu2_ConfigAccessMaskTablePermissions
  ( HAL_xpu2_XPU2Type eXpu2,
    const HAL_xpu2_ResourceGroupPermissionType *pAMTPerm );
HAL_xpu2_Status HAL_xpu2_ConfigUnmappedPartitionPermissions
  ( HAL_xpu2_XPU2Type eXpu2,
    const HAL_xpu2_ResourceGroupPermissionType *pUnmapRGPerm );
void HAL_xpu2_EnableMSSSelfAuth( HAL_xpu2_XPU2Type eXpu2 );
HAL_xpu2_Status HAL_xpu2_EnableMPUPartition
  ( HAL_xpu2_XPU2Type eXpu2,
    HAL_xpu2_ResourceGroupIDType uResID );
HAL_xpu2_Status HAL_xpu2_DisableMPUPartition
  ( HAL_xpu2_XPU2Type eXpu2,
    HAL_xpu2_ResourceGroupIDType uResID );
HAL_xpu2_Status HAL_xpu2_ConfigResourceGroup
  ( HAL_xpu2_XPU2Type eXpu2,
    HAL_xpu2_ResourceGroupIDType uResID,
    const HAL_xpu2_ResourceGroupConfigType *pResConfig );
HAL_xpu2_Status HAL_xpu2_ConfigAccessMaskTable
  ( HAL_xpu2_XPU2Type eXpu2,
    const uint32 *pMaskAttribArray,
    uint32 uNumElements );
HAL_xpu2_Status HAL_xpu2_ClearAccessMaskTable
  ( HAL_xpu2_XPU2Type eXpu2,
    const uint32 *pMaskAttribArray,
    uint32 uNumElements );
HAL_xpu2_Status HAL_xpu2_ConfigAccessMaskTablePageSize
  ( HAL_xpu2_XPU2Type eXpu2,
    HAL_xpu2_AMTPageSizeType eAMTPageSize,
    HAL_xpu2_ConfigType eConfig );
HAL_xpu2_Status HAL_xpu2_ConfigErrorReporting
  ( HAL_xpu2_XPU2Type eXpu2,
    HAL_xpu2_ConfigType eConfig,
    HAL_xpu2_ErrorOptionsConfigType errOpt );
void HAL_xpu2_GetDeviceParameters( HAL_xpu2_XPU2Type eXpu2,
                                   HAL_xpu2_XPUDeviceParamsType *pDevParams );
void HAL_xpu2_GetAccessPermissions
  ( HAL_xpu2_XPU2Type eXpu2,
    HAL_xpu2_ResourceGroupPermissionType *pAccessConfig );
void HAL_xpu2_GetAccessMaskTablePermissions
  ( HAL_xpu2_XPU2Type eXpu2,
    HAL_xpu2_ResourceGroupPermissionType *pAMTPerm );
void HAL_xpu2_GetUnmappedPartitionPermissions
  ( HAL_xpu2_XPU2Type eXpu2,
    HAL_xpu2_ResourceGroupPermissionType *pUnmapRGPerm );
void HAL_xpu2_GetResourceGroupConfig
  ( HAL_xpu2_XPU2Type eXpu2,
    HAL_xpu2_ResourceGroupIDType uResID,
    HAL_xpu2_ResourceGroupConfigType *pResConfig );
void HAL_xpu2_GetAccessMaskTable
  ( HAL_xpu2_XPU2Type eXpu2,
    uint16 *pMaskAttribArray,
    uint32 *puNumElements );
bool32 HAL_xpu2_AreAMTBitsSet
  ( HAL_xpu2_XPU2Type eXpu2,
    const uint16 *pMaskAttribArray,
    uint32 uNumElements );
void HAL_xpu2_GetErrorReportingConfig
  ( HAL_xpu2_XPU2Type eXpu2,
    HAL_xpu2_ConfigType eConfig,
    HAL_xpu2_ErrorOptionsConfigType *pErrConfig );
bool32 HAL_xpu2_IsError ( HAL_xpu2_XPU2Type eXpu2,
                                   HAL_xpu2_ConfigType eConfig );
void HAL_xpu2_GetError( HAL_xpu2_XPU2Type eXpu2,
                        HAL_xpu2_ConfigType eConfig,
                        HAL_xpu2_ErrorType *pError );
HAL_xpu2_Status HAL_xpu2_ClearError( HAL_xpu2_XPU2Type eXpu2,
                                     HAL_xpu2_ConfigType eConfig );
HAL_xpu2_Status HAL_xpu2_ClearErrorExt( HAL_xpu2_XPU2Type eXpu2,
                                        HAL_xpu2_ConfigType eConfig,
                                        HAL_xpu2_ErrorFlagsConfigType uErrorFlags );
bool32 HAL_xpu2_IsError_NoLock( HAL_xpu2_XPU2Type eXpu2,
                                HAL_xpu2_ConfigType eConfig );
HAL_xpu2_Status HAL_xpu2_ClearError_NoLock( HAL_xpu2_XPU2Type eXpu2,
                                            HAL_xpu2_ConfigType eConfig );
void HAL_xpu2_GetError_NoLock( HAL_xpu2_XPU2Type eXpu2,
                               HAL_xpu2_ConfigType eConfig,
                               HAL_xpu2_ErrorType *pError );
void HAL_xpu2_GetDeviceParameters_NoLock( HAL_xpu2_XPU2Type eXpu2,
                                          HAL_xpu2_XPUDeviceParamsType *pDevParams );
void HAL_xpu2_GetResourceGroupConfig_NoLock
  ( HAL_xpu2_XPU2Type eXpu2,
    HAL_xpu2_ResourceGroupIDType uResID,
    HAL_xpu2_ResourceGroupConfigType *pResConfig );
        typedef struct __attribute__((packed))
        { uint16 x; }
        unaligned_uint16;
        typedef struct __attribute__((packed))
        { uint32 x; }
        unaligned_uint32;
        typedef struct __attribute__((packed))
        { uint64 x; }
        unaligned_uint64;
        typedef struct __attribute__((packed))
        { int16 x; }
        unaligned_int16;
        typedef struct __attribute__((packed))
        { int32 x; }
        unaligned_int32;
        typedef struct __attribute__((packed))
        { int64 x; }
        unaligned_int64;
  extern dword rex_int_lock(void);
  extern dword rex_int_free(void);
    extern dword rex_fiq_lock(void);
    extern void rex_fiq_free(void);
   extern void rex_task_lock( void);
   extern void rex_task_free( void);
typedef unsigned wchar_t;
typedef struct { long long __ll; long double __ld; } max_align_t;
typedef unsigned long size_t;
typedef long ptrdiff_t;
static inline boolean IS_OWNER_TRUSTED_OS(uint32_t owner_id)
{
  return ((owner_id >= 50) && (owner_id <= 63));
}
typedef enum
{
  SMC_INTERRUPTED = 1,
  SMC_SUCCESS = 0,
  SMC_ERR_UNKNOWN_SMC_ID = -1L,
  SMC_ERR_SYSCALL_FAILED = -2L,
  SMC_ERR_SYSCALL_NOT_AVAILABLE = -3L,
  SMC_ERR_RESERVED_FIELD_MBZ = -4L,
  SMC_ERR_NUM_ARGS_MISMATCH = -5L,
  SMC_ERR_INDIRECT_PARAM_PTR_NOT_NS = -6L,
  SMC_ERR_BUF_LEN_NOT_FOUND = -7L,
  SMC_ERR_BUF_PTR_NOT_NS = -8L,
  SMC_ERR_NO_MEMORY = -9L,
  SMC_ERR_PARAM_ID_MISMATCH = -10L,
  SMC_ERR_BUF_PTR_INVALID = -11L,
  SMC_ERR_BUSY = -12L,
  SMC_ERR_SESSION_ID_MISMATCH = -13L,
  SMC_ERR_NOT_FOUND_IN_HYP = -14L,
  SMC_ERR_TEE_SERVICE_NOT_FOUND = -15L,
  SMC_ERR_STANDARD_CALL_NOT_ALLOWED = -16L,
  SMC_ERR_SYSCALL_NOT_SUPPORTED = SMC_ERR_UNKNOWN_SMC_ID,
  SMC_ERR_AARCH64_NOT_SUPPORTED = SMC_ERR_UNKNOWN_SMC_ID,
  SMC_ERR_FAILURE = -(0x7fffffff)
} SmcErrnoType;
typedef struct tz_syscall_req_s
{
   uint32 len;
   uint32 command_start_off;
   uint32 response_write_off;
   uint32 command_id;
} __attribute__ ((packed)) tz_syscall_req_t;
typedef struct tz_syscall_rsp_s
{
   int status;
} __attribute__ ((packed)) tz_syscall_rsp_t;
typedef struct tz_va_range_s
{
  uint64 va_start;
  uint32 va_size;
}tz_va_range_t;
typedef struct tz_set_boot_addr_s
{
  uint32 boot_addr;
  uint32 affl0_bmsk;
  uint32 affl1_bmsk;
  uint32 affl2_bmsk;
  uint32 affl3_bmsk;
  uint32 flags;
} __attribute__ ((packed)) tz_set_boot_addr_t;
typedef struct tz_set_milestone_s
{
  uint64 e_entry;
  uint32 mode;
  uint32 ei_class;
} __attribute__ ((packed)) tz_set_milestone_t;
typedef struct hlos_boot_params_s
{
  uint64 el1_x0;
  uint64 el1_x1;
  uint64 el1_x2;
  uint64 el1_x3;
  uint64 el1_x4;
  uint64 el1_x5;
  uint64 el1_x6;
  uint64 el1_x7;
  uint64 el1_x8;
  uint64 el1_elr;
} hlos_boot_params_t;
typedef struct tz_do_modeswitch_s
{
  hlos_boot_params_t hlos_boot_info;
} __attribute__ ((packed)) tz_do_modeswitch_t;
typedef struct tz_secure_wdog_disable_req_s
{
  boolean disable;
} __attribute__ ((packed)) tz_secure_wdog_disable_req_t;
typedef struct tz_secure_wdog_trigger_req_s
{
  boolean disable_debug;
} __attribute__ ((packed)) tz_secure_wdog_trigger_req_t;
typedef struct tz_lock_xpu_s
{
  uint64 elf_header_addr;
  uint32 program_header;
  uint32 proc_id;
  uint32 dummy;
} __attribute__ ((packed)) tz_lock_xpu_t;
typedef struct tz_config_hw_for_ram_dump_req_s
{
  uint32 disable_wd_dbg;
  uint32 boot_partition_sel;
} __attribute__ ((packed)) tz_config_hw_for_ram_dump_req_t;
typedef enum
{
  TZ_SUBSYS_STATE_SUSPEND = 0,
  TZ_SUBSYS_STATE_RESUME,
  TZ_SUBSYS_STATE_VENUS_RESTORE_THRESHOLD
} tz_subsys_state_e_type;
typedef struct tz_video_set_state_req_s
{
  uint32 state;
  uint32 spare;
} __attribute__ ((packed)) tz_video_set_state_req_t;
typedef struct tz_spin_with_irqs_fiqs_disabled_s
{
  uint32 spare;
} __attribute__ ((packed)) tz_spin_with_irqs_fiqs_disabled_t;
typedef enum
{
  TZ_PIL_AUTH_MODEM_PROC,
  TZ_PIL_AUTH_QDSP6_PROC,
  TZ_PIL_AUTH_SPS_PROC,
  TZ_PIL_AUTH_EXEC,
  TZ_PIL_AUTH_MODEM_SW_PROC,
  TZ_PIL_AUTH_MODEM_FW_PROC,
  TZ_PIL_AUTH_WLAN_PROC,
  TZ_PIL_AUTH_SEC_APP,
  TZ_PIL_AUTH_GNSS_PROC,
  TZ_PIL_AUTH_VIDEO_PROC,
  TZ_PIL_AUTH_VPU_PROC,
  TZ_PIL_AUTH_BCSS_PROC,
  TZ_PIL_AUTH_SSC_PROC,
  TZ_PIL_AUTH_GPU_UCODE_PROC,
  TZ_PIL_AUTH_SPSS_PROC,
  TZ_PIL_AUTH_IPA_GSI_PROC,
  TZ_PIL_AUTH_SEC_TEE,
  TZ_PIL_AUTH_SEC_LIB,
  TZ_PIL_AUTH_CDSP_PROC,
  TZ_PIL_AUTH_UNSUPPORTED_PROC
} tz_pil_proc_e_type;
typedef struct tz_pil_init_req_s
{
  uint32 proc;
  uint8* image_hdr_ptr;
} __attribute__ ((packed)) tz_pil_init_req_t;
typedef struct tz_pil_mem_req_s
{
  uint32 proc;
  uint64 start_addr;
  uint32 image_len;
} __attribute__ ((packed)) tz_pil_mem_req_t;
typedef struct tz_pil_auth_reset_req_s
{
  uint32 proc;
} __attribute__ ((packed)) tz_pil_auth_reset_req_t;
typedef struct tz_pil_unlock_req_s
{
  uint32 proc;
} __attribute__ ((packed)) tz_pil_unlock_req_t;
typedef struct tz_pil_subsystem_query_req_s
{
  uint32 proc;
} __attribute__ ((packed)) tz_pil_subsystem_query_req_t;
typedef struct tz_pil_subsystem_query_rsp_s
{
  uint32 verdict;
} __attribute__ ((packed)) tz_pil_subsystem_query_rsp_t;
typedef struct tz_pil_mem_area_query_req_s
{
  uint32 spare;
} __attribute__ ((packed)) tz_pil_mem_area_query_req_t;
typedef struct tz_pil_mem_area_query_rsp_s
{
  uint64 start;
  uint64 end;
} __attribute__ ((packed)) tz_pil_mem_area_query_rsp_t;
typedef struct tz_pil_modem_restart_s
{
  uint32 config;
  uint32 spare;
} __attribute__ ((packed)) tz_pil_modem_restart_t;
typedef struct tz_pil_share_memory_s
{
  uint32 start;
  uint32 size;
  uint32 proc;
  uint32 share_type;
} __attribute__ ((packed)) tz_pil_share_memory_t;
typedef struct tz_pil_protect_memory_s
{
  uint32 subsystem_id;
  uint64 phy_base;
  uint32 size;
} __attribute__ ((packed)) tz_pil_protect_memory_t;
typedef struct tz_pil_clear_protect_memory_s
{
  uint32 subsystem_id;
  uint64 phy_base;
  uint32 size;
  uint32 auth_key;
} __attribute__ ((packed)) tz_pil_clear_protect_memory_t;
typedef struct tz_pil_get_rollback_version_req_s
{
  uint32_t subsys_id;
} __attribute__ ((packed)) tz_pil_get_rollback_version_req_t;
typedef struct tz_pil_get_rollback_version_rsp_s
{
  uint32_t version;
} __attribute__ ((packed)) tz_pil_get_rollback_version_rsp_t;
typedef enum
{
  TZ_DEVICE_VIDEO = 0,
  TZ_DEVICE_MDSS = 1,
  TZ_DEVICE_LPASS = 2,
  TZ_DEVICE_MDSS_BOOT = 3,
  TZ_DEVICE_USB1_HS = 4,
  TZ_DEVICE_OCMEM = 5,
  TZ_DEVICE_LPASS_CORE = 6,
  TZ_DEVICE_VPU = 7,
  TZ_DEVICE_COPSS_SMMU = 8,
  TZ_DEVICE_USB3_0 = 9,
  TZ_DEVICE_USB3_1 = 10,
  TZ_DEVICE_PCIE_0 = 11,
  TZ_DEVICE_PCIE_1 = 12,
  TZ_DEVICE_BCSS = 13,
  TZ_DEVICE_VCAP = 14,
  TZ_DEVICE_PCIE20 = 15,
  TZ_DEVICE_IPA = 16,
  TZ_DEVICE_APPS = 17,
  TZ_DEVICE_GPU = 18,
  TZ_DEVICE_UFS = 19,
  TZ_DEVICE_ICE = 20,
  TZ_DEVICE_ROT = 21,
  TZ_DEVICE_VFE = 22,
  TZ_DEVICE_ANOC0 = 23,
  TZ_DEVICE_ANOC1 = 24,
  TZ_DEVICE_ANOC2 = 25,
  TZ_DEVICE_CPP = 26,
  TZ_DEVICE_JPEG = 27,
  TZ_DEVICE_SLPI = 28,
  TZ_DEVICE_RPM = 29,
  TZ_DEVICE_MODEM = 30,
  TZ_DEVICE_GPU_UCODE = 31,
  TZ_DEVICE_MMNOC = 32,
  TZ_DEVICE_SP = 33,
  TZ_DEVICE_CDSP = 34,
  TZ_DEVICE_MSS_NAV = 35,
  TZ_DEVICE_COUNT,
  TZ_DEVICE_MAX = 0x7FFFFFFF,
}tz_device_e_type;
typedef enum
{
  TZ_RETURN_FROM_ENTRY = 0,
  TZ_RETURN_FROM_EXIT = 1,
  TZ_RETURN_MAX = 0x7FFFFFFF,
} tz_ddr_self_refresh_return_type;
typedef struct tz_pil_qdsp6_nmi_req_s
{
  uint32 val;
} __attribute__ ((packed)) tz_pil_qdsp6_nmi_req_t;
typedef struct tz_dump_set_cpu_ctx_buf_req_s
{
  uint32* addr;
  uint32 size;
} __attribute__ ((packed)) tz_dump_set_cpu_ctx_buf_req_t;
typedef struct tz_dump_set_cache_buf_req_s
{
  uint32* addr;
  uint32 size;
} __attribute__ ((packed)) tz_dump_set_cache_buf_req_t;
typedef struct tz_dump_query_cache_buf_size_req_s
{
  uint32 spare;
} __attribute__ ((packed)) tz_dump_query_cache_buf_size_req_t;
typedef struct tz_dump_query_cache_buf_size_rsp_s
{
  uint32 size;
} __attribute__ ((packed)) tz_dump_query_cache_buf_size_rsp_t;
typedef struct tz_dump_set_ocmem_buf_req_s
{
  uint32* addr;
  uint32 size;
} __attribute__ ((packed)) tz_dump_set_ocmem_buf_req_t;
typedef struct tz_dump_query_ocmem_buf_size_req_s
{
  uint32 spare;
} __attribute__ ((packed)) tz_dump_query_ocmem_buf_size_req_t;
typedef struct tz_dump_query_ocmem_buf_size_rsp_s
{
  uint32 size;
} __attribute__ ((packed)) tz_dump_query_ocmem_buf_size_rsp_t;
typedef struct tz_security_allows_mem_dump_rsp_s
{
  uint32 allowed;
} __attribute__ ((packed)) tz_security_allows_mem_dump_rsp_t;
typedef struct tz_security_is_retail_unlock_rsp_s
{
  uint32 enabled;
} __attribute__ ((packed)) tz_security_is_retail_unlock_rsp_t;
typedef struct tz_ddr_self_refresh_return_req_s
{
  uint32 return_type;
} __attribute__ ((packed)) tz_ddr_self_refresh_return_req_s;
typedef struct tz_os_ice_set_context_config_req_s
{
  uint32 ce;
  uint32 pipe;
  boolean default_cntx_flag;
  uint8 encr_key_size;
  uint8 decr_bypass;
  uint8 encr_bypass;
} __attribute__ ((packed)) tz_os_ice_set_context_config_req_t;
typedef struct tz_os_ice_key_config_restore_req_s
{
  uint32 ce;
} __attribute__ ((packed)) tz_os_ice_key_config_restore_req_t;
typedef struct tz_os_ice_disable_sequence_req_s
{
  uint32 pipe;
  uint32 ce;
} __attribute__ ((packed)) tz_os_ice_disable_sequence_req_t;
typedef enum
{
  TZ_RESOURCE_CE1 = 1,
  TZ_RESOURCE_CE_MSS = 1,
  TZ_RESOURCE_CE2 = 2,
  TZ_RESOURCE_CE_AP = 2,
  TZ_RESOURCE_RNG = 3
} TZ_XPU_RESOURCE_ET;
typedef struct tz_lock_resource_req_s
{
  uint32 res;
  uint32 lock;
} __attribute__ ((packed)) tz_lock_resource_req_t;
typedef struct tz_lock_resource_rsp_s
{
  int32 ret;
} __attribute__ ((packed)) tz_lock_resource_rsp_t;
typedef struct tz_config_resource_req_s
{
  uint32 res;
  uint32 arg;
} __attribute__ ((packed)) tz_config_resource_req_t;
typedef enum
{
  tzbsp_blsp_owner_none = 0,
  tzbsp_blsp_owner_apss = 1,
  tzbsp_blsp_owner_adsp = 2,
  tzbsp_blsp_owner_tz = 3
} tzbsp_blsp_owner_ss_type;
typedef struct tz_modify_blsp_ownership_req_s
{
  uint32 blsp_periph_num;
  tzbsp_blsp_owner_ss_type owner_ss;
} __attribute__ ((packed)) tz_modify_blsp_ownership_req_t;
typedef struct tz_info_is_svc_available_req_s
{
  uint32 id;
} __attribute__ ((packed)) tz_info_is_svc_available_req_t;
typedef struct tz_info_is_svc_available_rsp_s
{
  boolean found;
} __attribute__ ((packed)) tz_info_is_svc_available_rsp_t;
typedef struct tz_info_get_diag_req_s
{
  uint8* buffer;
  uint32 buffer_size;
} __attribute__ ((packed)) tz_info_get_diag_req_t;
typedef struct tz_feature_version_req_s
{
  uint32 feature_id;
} __attribute__ ((packed)) tz_feature_version_req_t;
typedef struct tz_feature_version_rsp_s
{
  uint32 version;
} __attribute__ ((packed)) tz_feature_version_rsp_t;
typedef struct tz_get_secure_state_rsp_s
{
  uint32 status_0;
  uint32 status_1;
}__attribute__ ((packed)) tz_get_secure_state_rsp_t;
typedef struct tz_get_secure_state_legacy_req_s
{
  uint32* status_ptr;
  uint32 status_len;
}__attribute__ ((packed)) tz_get_secure_state_legacy_req_t;
typedef struct tz_bw_prof_req_s
{
  uint32* req_ptr;
  uint32 req_len;
  uint32* rsp_ptr;
  uint32 rsp_len;
}__attribute__ ((packed)) tz_bw_prof_req_t;
typedef struct tz_ssd_decrypt_img_req_s
{
  uint64 img_ptr;
  uint32 img_len_ptr;
} __attribute__ ((packed)) tz_ssd_decrypt_img_req_t;
typedef struct tz_ssd_encrypt_keystore_req_s
{
  uint64 keystore_ptr;
  uint32 keystore_len_ptr;
} __attribute__ ((packed)) tz_ssd_encrypt_keystore_req_t;
typedef struct tz_ssd_protect_keystore_req_s
{
  uint32* keystore_ptr;
  uint32 keystore_len;
} __attribute__ ((packed)) tz_ssd_protect_keystore_req_t;
typedef enum
{
  TZ_SSD_PKS_SUCCESS = 0,
  TZ_SSD_PKS_INVALID_PTR = 1,
  TZ_SSD_PKS_INVALID_LEN = 2,
  TZ_SSD_PKS_UNALIGNED_PTR = 3,
  TZ_SSD_PKS_PROTECT_MEM_FAILED = 4,
  TZ_SSD_PKS_INVALID_NUM_KEYS = 5,
  TZ_SSD_PKS_DECRYPT_FAILED = 6
} tz_ssd_pks_return_type;
typedef struct tz_ssd_protect_keystore_rsp_s
{
  uintptr_t status;
} __attribute__ ((packed)) tz_ssd_protect_keystore_rsp_t;
typedef struct tz_ssd_parse_md_req_s
{
  uint32 md_len;
  uint32* md;
} __attribute__ ((packed)) tz_ssd_parse_md_req_t;
typedef enum
{
  TZ_SSD_PMD_ENCRYPTED = 0,
  TZ_SSD_PMD_NOT_ENCRYPTED = 1,
  TZ_SSD_PMD_NO_MD_FOUND = 3,
  TZ_SSD_PMD_BUSY = 4,
  TZ_SSD_PMD_BAD_MD_PTR_OR_LEN = 5,
  TZ_SSD_PMD_PARSING_INCOMPLETE = 6,
  TZ_SSD_PMD_PARSING_FAILED = 7,
  TZ_SSD_PMD_SETUP_CIPHER_FAILED = 8,
} tz_ssd_pmd_return_type;
typedef struct tz_ssd_parse_md_rsp_info_s
{
  uintptr_t status;
  uintptr_t md_ctx_id;
  uintptr_t md_end_ptr;
} __attribute__ ((packed)) tz_ssd_parse_md_rsp_info_t;
typedef struct tz_ssd_parse_md_rsp_s
{
  struct tz_ssd_parse_md_rsp_info_s rsp;
} __attribute__ ((packed)) tz_ssd_parse_md_rsp_t;
typedef struct tz_ssd_decrypt_img_frag_req_s
{
  uint32 md_ctx_id;
  uint32 last_frag;
  uint32 frag_len;
  uint32* frag;
} __attribute__ ((packed)) tz_ssd_decrypt_frag_req_t;
typedef struct tz_ssd_decrypt_elf_seg_frag_req_s
{
  uint32 md_ctx_id;
  uint32 segment_num;
  uint32 last_seg;
  uint32 last_frag;
  uint32 frag_len;
  uint32* frag;
} __attribute__ ((packed)) tz_ssd_decrypt_elf_seg_frag_req_t;
typedef enum
{
  TZ_SSD_DF_SUCCESS = 0,
  TZ_SSD_DF_BAD_FRAG_PTR_OR_LEN = 1,
  TZ_SSD_DF_CTX_NOT_FOUND = 2,
  TZ_SSD_DF_LEN_ALIGNMENT_FAILED = 3,
  TZ_SSD_DF_DECRYPTION_FAILED = 4
} tz_ssd_df_return_type;
typedef struct tz_ssd_decrypt_frag_rsp_s
{
  uintptr_t status;
} __attribute__ ((packed)) tz_ssd_decrypt_frag_rsp_t;
typedef struct tz_sw_fuse_req_s
{
  uint32 fuse_id;
} __attribute__ ((packed)) tz_sw_fuse_req_t;
typedef struct tz_sw_fuse_rsp_s
{
  boolean fuse_blown;
} __attribute__ ((packed)) tz_sw_fuse_rsp_t;
typedef struct tz_qfprom_write_row_s
{
  uint32 bus_clk_khz;
  uint32 raw_row_address;
  uint32* row_data;
  uint32 row_data_len;
} __attribute__ ((packed)) tz_qfprom_write_row_req_t;
typedef struct tz_qfprom_write_multiple_rows_s
{
  uint32* row_array;
  uint32 row_array_size;
  uint32 bus_clk_khz;
  uint32* qfprom_api_status;
} __attribute__ ((packed)) tz_qfprom_write_multiple_rows_t;
typedef struct tz_qfprom_read_row_s
{
  uint32 row_address;
  int32 addr_type;
  uint32* row_data;
  uint32* qfprom_api_status;
} __attribute__ ((packed)) tz_qfprom_read_row_t;
typedef struct tz_qfprom_rollback_write_row_s
{
  uint32 bus_clk_khz;
  uint32 raw_row_address;
  uint32* row_data;
  uint32 row_data_len;
} __attribute__ ((packed)) tz_qfprom_rollback_write_row_t;
typedef struct tz_get_prng_data_s
{
  uint8* out_buf;
  uint32 out_buf_sz;
} __attribute__ ((packed)) tz_get_prng_data_t;
typedef struct tz_sc_init_s
{
  uint32 ssid;
  void* address_ptr;
  uint32 len;
  int* status_ptr;
} __attribute__ ((packed)) tz_sc_init_t;
typedef struct tz_sc_deinit_s
{
  uint32 ssid;
  int* status_ptr;
} __attribute__ ((packed)) tz_sc_deinit_t;
typedef struct hyp_memprot_ipa_info_s
{
  uint64 IPAaddr;
  uint64 IPAsize;
} __attribute__ ((packed)) hyp_memprot_ipa_info_t;
typedef struct hyp_memprot_dstVM_perm_info_s
{
  uint32 dstVM;
  uint32 dstVMperm;
  uint64 ctx;
  uint32 ctxsize;
} hyp_memprot_dstVM_perm_info_t;
typedef struct hyp_memprot_assign_s
{
  const hyp_memprot_ipa_info_t *IPAinfolist;
  uint32 IPAinfolistsize;
  const uint32 *sourceVMlist;
  uint32 srcVMlistsize;
  const hyp_memprot_dstVM_perm_info_t *destVMlist;
  uint32 destVMlistsize;
  uint64 spare;
} hyp_memprot_assign_t;
typedef struct tz_memprot_tagVM_t
{
  const hyp_memprot_ipa_info_t *IPAinfolist;
  uint32 IPAinfolistsize;
  const uint32 *destVMlist;
  uint32 dstVMlistsize;
  uint64 flags;
} __attribute__ ((packed)) tz_memprot_tagVM_t;
typedef struct tz_protect_memory_s
{
  uint64 start;
  uint64 end;
  uint32 tag_id;
  boolean lock;
} __attribute__ ((packed)) tz_protect_memory_t;
typedef struct tz_assign_io_range_s
{
  uint64 start;
  uint64 end;
  uint32 dest;
  uint32 perm;
  uint32 lock;
} __attribute__ ((packed)) tz_assign_io_range_t;
typedef struct tz_restore_sec_cfg_req_s
{
  uint32 device;
  uint32 spare;
} __attribute__ ((packed)) tz_restore_sec_cfg_req_t;
typedef struct tz_set_vmidmt_memtype_req_s
{
  uint32 device;
  uint32 vmid_idx;
  uint32 memtype;
} __attribute__ ((packed)) tz_set_vmidmt_memtype_req_t;
typedef struct tz_memprot_video_var_req_s
{
  uint64 cp_start;
  uint32 cp_size;
  uint64 cp_nonpixel_start;
  uint32 cp_nonpixel_size;
} __attribute__ ((packed)) tz_memprot_video_var_req_t;
typedef struct tz_memprot_dev_var_req_s
{
  uint32 device_id;
  tz_va_range_t *va_list;
  uint32 list_size;
} __attribute__ ((packed)) tz_memprot_dev_var_req_t;
typedef struct tz_memprot_ptbl_mem_size_req_s
{
   uint32 spare;
} __attribute__ ((packed)) tz_memprot_ptbl_mem_size_req_t;
typedef struct tz_memprot_ptbl_mem_size_rsp_s
{
  uint32 mem_size;
  int32 ret;
} __attribute__ ((packed)) tz_memprot_ptbl_mem_size_rsp_t;
typedef struct tz_memprot_ptbl_mem_init_req_s
{
  uint64 addr;
  uint32 size;
  uint32 spare;
} __attribute__ ((packed)) tz_memprot_ptbl_mem_init_req_t;
typedef struct tz_memprot_rsp_s
{
  uint32 rsp;
} __attribute__ ((packed)) tz_memprot_rsp_t;
typedef struct tz_memprot_set_cp_pool_size_req_s
{
   uint32 size;
   uint32 spare;
} __attribute__ ((packed)) tz_memprot_set_cp_pool_size_req_t;
typedef enum
{
  TZ_MEM_USAGE_CP_VIDEO_BITSTREAM = 0x1,
  TZ_MEM_USAGE_CP_VIDEO_PIXEL = 0x2,
  TZ_MEM_USAGE_CP_VIDEO_NONPIXEL = 0x3,
  TZ_MEM_USAGE_CP_SD = 0x4,
  TZ_MEM_USAGE_CP_SC = 0x5,
  TZ_MEM_USAGE_CP_APP = 0x6,
  TZ_MEM_USAGE_COUNT,
  TZ_MEM_USAGE_UNKNOWN = 0x7fffffff
}tz_mem_usage_e_type;
typedef struct tz_memprot_chunks_info_s
{
  uint32* chunk_list;
  uint32 chunk_list_size;
  uint32 chunk_size;
} __attribute__ ((packed)) tz_memprot_chunks_info_t;
typedef struct tz_memprot_map_info_s
{
  uint32 device_id;
  uint32 ctxt_bank_id;
  uint32 dva_start;
  uint32 size;
} __attribute__ ((packed)) tz_memprot_map_info_t;
typedef struct tz_memprot_lock2_req_s
{
  tz_memprot_chunks_info_t chunks;
  uint32 mem_usage;
  uint32 lock;
  uint32 flags;
} __attribute__ ((packed)) tz_memprot_lock2_req_t;
typedef struct tz_memprot_map2_req_s
{
  tz_memprot_chunks_info_t chunks;
  tz_memprot_map_info_t map;
  uint32 flags;
} __attribute__ ((packed)) tz_memprot_map2_req_t;
typedef struct tz_memprot_unmap2_req_s
{
  tz_memprot_map_info_t map;
  uint32 flags;
} __attribute__ ((packed)) tz_memprot_unmap2_req_t;
typedef struct tz_memprot_tlbinval_req_s
{
  uint32 device_id;
  uint32 ctxt_bank_id;
  uint32 flags;
  uint32 spare;
} __attribute__ ((packed)) tz_memprot_tlbinval_req_t;
typedef enum
{
  TZ_XPU_VIOLATION_ERR_FATAL_ENABLE = 0,
  TZ_XPU_VIOLATION_ERR_FATAL_DISABLE = 1,
  TZ_XPU_VIOLATION_ERR_FATAL_NOOP = 2,
} tz_xpu_violation_err_fatal_t;
typedef struct tz_xpu_violation_err_fatal_req_s
{
  tz_xpu_violation_err_fatal_t config;
  uint32 spare;
} __attribute__ ((packed)) tz_xpu_violation_err_fatal_req_t;
typedef struct tz_xpu_violation_err_fatal_rsp_s
{
  tz_xpu_violation_err_fatal_t status ;
} __attribute__ ((packed)) tz_xpu_violation_err_fatal_rsp_t;
typedef struct tz_memprot_sd_ctrl_req_s
{
  uint32 enable;
} __attribute__ ((packed)) tz_memprot_sd_ctrl_req_t;
typedef enum
{
  TZ_OCMEM_CLNT_UNUSED,
  TZ_OCMEM_CLNT_GRAPHICS,
  TZ_OCMEM_CLNT_VIDEO,
  TZ_OCMEM_CLNT_LP_AUDIO,
  TZ_OCMEM_CLNT_SENSORS,
  TZ_OCMEM_CLNT_BLAST,
  TZ_OCMEM_CLNT_DEBUG,
}tz_ocmem_client_e_type;
typedef enum
{
  TZ_OCMEM_OP_MODE_WIDE,
  TZ_OCMEM_OP_MODE_THIN,
  TZ_OCMEM_OP_MODE_NOT_SET,
}tz_ocmem_op_mode_e_type;
typedef struct tz_ocmem_lock_region_req_s
{
  uint32 client_id;
  uint32 offset;
  uint32 size;
  uint32 mode;
}__attribute__ ((packed)) tz_ocmem_lock_region_req_t;
typedef struct tz_ocmem_unlock_region_req_s
{
  uint32 client_id;
  uint32 offset;
  uint32 size;
}__attribute__ ((packed)) tz_ocmem_unlock_region_req_t;
typedef struct tz_ocmem_enable_mem_dump_req_s
{
  uint32 client_id;
  uint32 offset;
  uint32 size;
}__attribute__ ((packed)) tz_ocmem_enable_mem_dump_req_t;
typedef struct tz_ocmem_disable_mem_dump_req_s
{
  uint32 client_id;
  uint32 offset;
  uint32 size;
}__attribute__ ((packed)) tz_ocmem_disable_mem_dump_req_t;
typedef enum
{
    TZ_ES_PARTITION_ID_KERNEL = 0,
    TZ_ES_PARTITION_ID_SYSTEM = 1,
    TZ_ES_PARTITION_ID_RECOVERY = 2,
    TZ_ES_MAX_PARTITIONS
}tz_partition_id_e_type;
typedef struct tz_es_save_partition_hash_req_s
{
  uint32 partition_id;
  uint8* hash;
  uint32 hash_sz;
}__attribute__ ((packed)) tz_es_save_partition_hash_req_t;
typedef struct tz_config_ns_debug_fiq_req_s
{
  const uint32* vector;
  const uint32* stack;
  uint32* ctx_buf;
  uint32 ctx_size;
  uint32 intnum;
  uint32 flags;
} __attribute__ ((packed)) tz_config_ns_debug_fiq_t;
typedef struct tz_config_ns_debug_fiq_ctx_size_rsp_s
{
  uint32 size;
} __attribute__ ((packed)) tz_config_ns_debug_fiq_ctx_size_rsp_t;
typedef struct tz_config_ns_debug_fiq_int_ok_req_s
{
  uint32 intnum;
} __attribute__ ((packed)) tz_config_ns_debug_fiq_int_ok_req_t;
typedef struct tz_config_ns_debug_fiq_int_ok_rsp_s
{
  uint32 verdict;
} __attribute__ ((packed)) tz_config_ns_debug_fiq_int_ok_rsp_t;
typedef struct tz_cpu_config_req_s
{
  uint32 id;
  uint32 arg0;
  uint32 arg1;
  uint32 arg2;
} __attribute__ ((packed)) tz_cpu_config_req_t;
typedef struct tz_cpu_config_query_req_s
{
  uint32 id;
  uint32 arg0;
  uint32 arg1;
  uint32 arg2;
} __attribute__ ((packed)) tz_cpu_config_query_req_t;
typedef struct tz_cpu_config_query_rsp_s
{
  uint32 ret0;
  uint32 ret1;
  uint32 ret2;
  uint32 ret3;
} __attribute__ ((packed)) tz_cpu_config_query_rsp_t;
typedef struct tz_hdcp_write_registers_req_s
{
  uint32 addr1;
  uint32 value1;
  uint32 addr2;
  uint32 value2;
  uint32 addr3;
  uint32 value3;
  uint32 addr4;
  uint32 value4;
  uint32 addr5;
  uint32 value5;
} __attribute__ ((packed)) tz_hdcp_write_registers_req_t;
typedef enum
{
  QSEE_APP_ID = 0xEE01ULL,
  QSEE_LISTENER_ID = 0xEE02ULL,
  QSEE_APP_STATE = 0xEE03ULL,
  QSEE_NONE = 0xEE04ULL,
  QSEE_GENERAL = 0xEE05ULL,
  QSEE_RESERVED = 0xFFFFFFFFFFFFFFFF
}tz_os_resp_type;
typedef struct tz_os_app_start_req_s
{
  size_t mdt_len;
  size_t img_len;
  uintptr_t pa;
} __attribute__ ((packed)) tz_os_app_start_req_t;
typedef struct tz_os_rsp_s
{
  int32_t result;
  tz_os_resp_type resp_type;
  uint32 data;
} __attribute__ ((packed)) tz_os_rsp_t;
typedef struct tz_os_app_shutdown_req_s
{
  uint32_t app_id;
} __attribute__ ((packed)) tz_os_app_shutdown_req_t;
typedef struct tz_os_app_lookup_req_s
{
  char* app_name;
  size_t len;
} __attribute__ ((packed)) tz_os_app_lookup_req_t;
typedef struct tz_os_app_get_state_req_s
{
  uint32_t app_id;
} __attribute__ ((packed)) tz_os_app_get_state_req_t;
typedef struct tz_os_app_region_notification_req_s
{
  uintptr_t applications_region_addr;
  size_t applications_region_size;
} __attribute__ ((packed)) tz_os_app_region_notification_req_t;
typedef struct tz_os_register_log_buffer_req_s
{
  void* phys_addr;
  size_t len;
} __attribute__ ((packed)) tz_os_register_log_buffer_req_t;
typedef struct tz_os_load_services_image_req_s
{
  size_t mdt_len;
  size_t img_len;
  uintptr_t pa;
} __attribute__ ((packed)) tz_os_load_services_image_req_t;
typedef struct tz_os_register_listener_req_s
{
  uint32_t listener_id;
  void* sb_ptr;
  size_t sb_len;
} __attribute__ ((packed)) tz_os_register_listener_req_t;
typedef struct tz_os_register_delistener_req_s
{
  uint32_t listener_id;
} __attribute__ ((packed)) tz_os_deregister_listener_req_t;
typedef struct tz_os_listener_response_handler_req_s
{
  uint32_t listener_id;
  int32_t status;
} __attribute__ ((packed)) tz_os_listener_response_handler_req_t;
typedef struct tz_os_listener_response_wlist_handler_req_s
{
  uint32_t listener_id;
  int32_t status;
  const void* qwl;
  size_t qwl_len;
} __attribute__ ((packed)) tz_os_listener_response_wlist_handler_req_t;
typedef struct tz_os_continue_blocked_request_req_s
{
  uint32_t app_id;
} __attribute__ ((packed)) tz_os_continue_blocked_request_req_t;
typedef struct tz_os_load_external_image_req_s
{
  size_t mdt_len;
  size_t img_len;
  uintptr_t pa;
} __attribute__ ((packed)) tz_os_load_external_image_req_t;
typedef struct tz_os_rpmb_provision_key_req_s
{
  size_t key_type;
} __attribute__ ((packed)) tz_os_rpmb_provision_key_req_t;
typedef struct tz_os_ks_req_s
{
  uintptr_t* req;
  size_t req_len;
} __attribute__ ((packed)) tz_os_ks_req_s;
typedef struct tz_os_ks_get_max_keys_req_s
{
  size_t flags;
} __attribute__ ((packed)) tz_os_ks_get_max_keys_req_s;
typedef struct tz_os_smc_invoke_req_s
{
  void* inBuf;
  size_t inBuf_len;
  void* outBuf;
  size_t outBuf_len;
} __attribute__ ((packed)) tz_os_smc_invoke_req_t;
typedef struct tz_os_smc_invoke_rsp_s
{
  int32_t result;
  uint32_t resp_data;
  uint32_t data;
} __attribute__ ((packed)) tz_os_smc_invoke_rsp_t;
typedef struct tz_app_send_data_req_s
{
  uint32_t app_id;
  void* req;
  size_t req_len;
  void* rsp;
  size_t rsp_len;
} __attribute__ ((packed)) tz_app_send_data_req_t;
typedef struct ScatterListEntryAA64 {
  uint64_t addr;
  uint32_t len;
} __attribute__ ((packed)) ScatterListEntryAA64;
typedef struct ScatterListEntryAA32 {
  uint32_t addr;
  uint32_t len;
} __attribute__ ((packed)) ScatterListEntryAA32;
typedef struct QWLEntry {
  uint32_t offsetAndFlags;
  uint32_t sizeOrCount;
} __attribute__ ((packed)) QWLEntry;
typedef struct tz_app_send_data_wlist_req_s
{
  uint32_t app_id;
  void* req;
  size_t req_len;
  void* rsp;
  size_t rsp_len;
  const void* qwl;
  size_t qwl_len;
} __attribute__ ((packed)) tz_app_send_data_wlist_req_t;
typedef enum
{
   TZ_CIPHER_MODE_XTS_128 = 0,
   TZ_CIPHER_MODE_CBC_128 = 1,
   TZ_CIPHER_MODE_XTS_256 = 3,
   TZ_CIPHER_MODE_CBC_256 = 4
} tz_ice_capability_index_type;
typedef enum
{
    TZ_ICE_DATA_UNIT_SIZE_INVALID = 0x00,
    TZ_ICE_DATA_UNIT_SIZE_512 = 0x01,
    TZ_ICE_DATA_UNIT_SIZE_1024 = 0x02,
    TZ_ICE_DATA_UNIT_SIZE_2048 = 0x04,
    TZ_ICE_DATA_UNIT_SIZE_4096 = 0x08,
    TZ_ICE_DATA_UNIT_SIZE_8192 = 0x10,
    TZ_ICE_DATA_UNIT_SIZE_16384 = 0x20,
    TZ_ICE_DATA_UNIT_SIZE_32768 = 0x40,
    TZ_ICE_DATA_UNIT_SIZE_65536 = 0x80,
} tz_ice_data_unit_type;
typedef struct tz_set_config_ice_key_req_s
{
  uint32 pipe;
  uint64 key_ptr_base;
  uint32 key_ptr_len;
  uint32 capability_index;
  uint32 data_unit_size;
} __attribute__ ((packed)) tz_set_config_ice_key_req_t;
typedef struct tzbsp_gfx_dcvs_update_data_s
{
  uint32 active_pwrlevel;
  uint32 total;
  uint32 inBusy;
  uint32 ctxt_aware_ctxt_count;
} __attribute__ ((packed)) tzbsp_gfx_dcvs_update_data_t;
typedef struct tzbsp_gfx_dcvs_update_req_s
{
  tzbsp_gfx_dcvs_update_data_t* data;
} __attribute__ ((packed)) tzbsp_gfx_dcvs_update_req_t;
typedef struct tzbsp_gfx_dcvs_update_rsp_s
{
  int32 decision;
} __attribute__ ((packed)) tzbsp_gfx_dcvs_update_rsp_t;
typedef struct tzbsp_gfx_dcvs_init_data_s
{
  uint32 nlevels;
  uint32 freq[10];
} __attribute__ ((packed)) tzbsp_gfx_dcvs_init_data_t;
typedef struct tzbsp_gfx_dcvs_init_rsp_s
{
  uint32 version;
} __attribute__ ((packed)) tzbsp_gfx_dcvs_init_rsp_t;
typedef struct tzbsp_gfx_dcvs_init_req_s
{
  tzbsp_gfx_dcvs_init_data_t* data;
} __attribute__ ((packed)) tzbsp_gfx_dcvs_init_req_t;
typedef struct tzbsp_gfx_dcvs_init_ca_data_s
{
  uint32 ctxt_aware_target_pwrlevel;
  uint32 ctxt_aware_busy_penalty;
} __attribute__ ((packed)) tzbsp_gfx_dcvs_init_ca_data_t;
typedef struct tzbsp_gfx_dcvs_init_ca_req_s
{
  tzbsp_gfx_dcvs_init_ca_data_t* data;
} __attribute__ ((packed)) tzbsp_gfx_dcvs_init_ca_req_t;
typedef struct tz_get_ablfv_entry_point_rsp_s
{
  uint64 e_entry;
} __attribute__ ((packed)) tz_get_ablfv_entry_point_rsp_t;
typedef struct tz_lmh_node_info_s
{
  uint32 node;
  uint32 node_id;
  uint32 intensity;
  uint32 max_intensity;
  uint32 type;
} __attribute__ ((packed)) tz_lmh_node_info_t;
typedef struct tz_lmh_node_packet_s
{
  uint32 count;
  tz_lmh_node_info_t nodes[10];
} __attribute__ ((packed)) tz_lmh_node_packet_t;
typedef struct tz_lmh_debug_header_s
{
  uint32 node;
  uint32 node_id;
  uint32 data_type;
  uint64 timestamp;
} __attribute__ ((packed)) tz_lmh_debug_header_t;
typedef struct tz_lmh_debug_packet_s
{
  tz_lmh_debug_header_t header;
  uint32 data[5];
} __attribute__ ((packed)) tz_lmh_debug_packet_t;
typedef struct tzbsp_lmh_change_profile_req_s
{
  uint32 profile;
} __attribute__ ((packed)) tzbsp_lmh_change_profile_req_t;
typedef struct tzbsp_lmh_get_profiles_req_s
{
  uint32 profile_list_addr;
  uint32 size;
  uint32 start;
} __attribute__ ((packed)) tzbsp_lmh_get_profiles_req_t;
typedef struct tzbsp_tzbsp_lmh_enable_qpmda_s
{
  uint32 enable;
  uint32 rate;
} __attribute__ ((packed)) tzbsp_lmh_enable_qpmda_req_t;
typedef struct tzbsp_lmh_set_current_limit_req_s
{
  uint32 limit;
  uint32 limit_type;
  uint32 limit_id;
} __attribute__ ((packed)) tzbsp_lmh_set_current_limit_req_t;
typedef struct tzbsp_lmh_intensity_req_s
{
  tz_lmh_node_packet_t* packet;
  uint32 size;
} __attribute__ ((packed)) tzbsp_lmh_intensity_req_t;
typedef struct tzbsp_lmh_get_sensor_list_req_s
{
  tz_lmh_node_packet_t* packet;
  uint32 size;
} __attribute__ ((packed)) tzbsp_lmh_get_sensor_list_req_t;
typedef struct tzbsp_lmh_debug_set_req_s
{
  uint32 debug_param_addr;
  uint32 size;
  uint32 node;
  uint32 node_id;
  uint32 debug_type;
} __attribute__ ((packed)) tzbsp_lmh_debug_set_req_t;
typedef struct tzbsp_lmh_debug_config_read_req_s
{
  uint32 read_param_addr;
  uint32 size;
  uint32 node;
  uint32 node_id;
  uint32 read_type;
} __attribute__ ((packed)) tzbsp_lmh_debug_config_read_req_t;
typedef struct tzbsp_lmh_debug_read_req_s
{
  tz_lmh_debug_packet_t* debug_packets;
  uint32 size;
} __attribute__ ((packed)) tzbsp_lmh_debug_read_req_t;
typedef struct tzbsp_lmh_debug_get_commands_req_s
{
  uint32 command_list_addr;
  uint32 size;
  uint32 command_type;
  uint32 start;
} __attribute__ ((packed)) tzbsp_lmh_debug_get_commands_req_t;
typedef struct tzbsp_lmh_analytics_set_req_s
{
  uint32 node;
  uint32 node_id;
  uint32 analytics_type;
  uint32 enable;
} __attribute__ ((packed)) tzbsp_lmh_analytics_set_req_t;
typedef struct tzbsp_lmh_analytics_read_req_s
{
  uint32 node;
  uint32 node_id;
} __attribute__ ((packed)) tzbsp_lmh_analytics_read_req_t;
typedef struct tzbsp_lmh_analytics_get_types_req_s
{
  uint32 analytics_list_addr;
  uint32 size;
  uint32 start;
} __attribute__ ((packed)) tzbsp_lmh_analytics_get_types_req_t;
typedef struct tzbsp_lmh_config_limit_req_s
{
  uint32 node;
  uint32 node_id;
  uint32 limit_type;
  uint32 limit;
  uint32 option;
} __attribute__ ((packed)) tzbsp_lmh_config_limit_req_t;
typedef struct tzbsp_lmh_dcvsh_config_req_s
{
  uint32 data_addr;
  uint32 data_len;
  uint32 node;
  uint32 node_id;
  uint32 version;
} __attribute__ ((packed)) tzbsp_lmh_dcvsh_config_req_t;
typedef struct tzbsp_lmh_sensor_init_req_s
{
  uint64 sensor_id;
  uint64 cmd_id;
  uint64 arg0;
  uint64 arg1;
  uint64 arg2;
  uint64 arg3;
} __attribute__ ((packed)) tzbsp_lmh_sensor_init_req_t;
typedef enum
{
  E_SUCCESS = 0,
  E_FAILURE = 1,
  E_NOT_ALLOWED = 2,
  E_NOT_AVAILABLE = 3,
  E_NOT_SUPPORTED = 4,
  E_CANCELED = 5,
  E_ABORTED = 6,
  E_INTERRUPTED = 7,
  E_DEADLOCK = 8,
  E_AGAIN = 9,
  E_RESET = 10,
  E_WOULD_BLOCK = 11,
  E_IN_PROGRESS = 12,
  E_ALREADY_DONE = 13,
  E_NO_DSM_ITEMS = 14,
  E_NO_MEMORY = 15,
  E_INVALID_ARG = 16,
  E_OUT_OF_RANGE = 17,
  E_BAD_ADDRESS = 18,
  E_NO_DATA = 19,
  E_BAD_DATA = 20,
  E_DATA_INVALID = 21,
  E_DATA_EXPIRED = 22,
  E_DATA_TOO_LARGE = 23,
  E_NO_DEV = 24,
  E_DEV_FAILURE = 25,
  E_NV_READ_ERR = 26,
  E_NV_WRITE_ERR = 27,
  E_EFS_ERROR = 28,
  E_DSP_ERROR = 29,
  E_TIMER_EXP = 30,
  E_VERSION_MISMATCH = 31,
  E_TASK_SIG_ERR = 32,
  E_TASK_Q_FULL = 33,
  E_PROT_Q_FULL = 34,
  E_PROT_TX_Q_FULL = 35,
  E_PROT_RX_Q_FULL = 36,
  E_PROT_UNKN_CMD = 37,
  E_PROT_UNKN_IND = 38,
  E_PROT_UNKN_MSG = 39,
  E_PROT_UNKN_SIG = 40,
  E_NO_ENTRY = 41,
  E_FILENAME_TOO_LONG = 42,
  E_DIR_NOT_EMPTY = 43,
  E_IS_DIR = 44,
  E_EOF = 45,
  E_XDEV = 46,
  E_BAD_F = 47,
  E_MAX_OPEN_FILES = 48,
  E_BAD_FMT = 49,
  E_FILE_EXISTS = 50,
  E_EFS_FULL = 51,
  E_NOT_DIR = 52,
  E_NOT_EFS_ITEM = 53,
  E_ALREADY_OPEN = 54,
  E_BUSY = 55,
  E_OUT_OF_NODES = 56,
  E_SQL_INTERNAL = 57,
  E_SQL_BUSY = 58,
  E_SQL_LOCKED = 59,
  E_SQL_READONLY = 60,
  E_SQL_IOERR = 61,
  E_SQL_CORRUPT = 62,
  E_SQL_NOTFOUND = 63,
  E_SQL_FULL = 64,
  E_SQL_CANTOPEN = 65,
  E_SQL_PROTOCOL = 66,
  E_SQL_EMPTY = 67,
  E_SQL_SCHEMA = 68,
  E_SQL_CONSTRAINT = 69,
  E_SQL_MISMATCH = 70,
  E_SQL_MISUSE = 71,
  E_SQL_NOLFS = 72,
  E_SQL_FORMAT = 73,
  E_SQL_NOTADB = 74,
  E_SQL_ROW = 75,
  E_SQL_DONE = 76,
  E_NO_ATTR = 77,
  E_INVALID_ITEM = 78,
  E_NO_NET = 100,
  E_NOT_SOCKET = 101,
  E_NO_PROTO_OPT = 102,
  E_SHUTDOWN = 103,
  E_CONN_REFUSED = 104,
  E_CONN_ABORTED = 105,
  E_IS_CONNECTED = 106,
  E_NET_UNREACH = 107,
  E_HOST_UNREACH = 108,
  E_NO_ROUTE = 109,
  E_ADDR_IN_USE = 110,
  E_DB_INVALID = 111,
  E_FLOW_NOT_IN_ZONE = 112,
  E_ZONE_NOT_IN_DB = 113,
  E_BUF_OVERFLOW = 114,
  E_DB_OVERFLOW = 116,
  E_DB_NO_OVERWRITE = 117,
  E_NOT_FOUND = 118,
  E_NO_RIGHTS = 119,
  E_HASH_VERIF_FAIL = 120,
  E_INVALID_STORE_PSWD = 121,
  E_MACHINE_ID_MISMATCH = 122,
  E_CONTINUE = 200,
  IxSUCCESS = E_SUCCESS,
  IxFAILED,
  IxNOMEMORY,
  IxBADPARAM,
  IxNOTSUPPORTED,
  E_RESERVED = 0x7FFFFFFF
} IxErrnoType;
typedef IxErrnoType errno_enum_type;
typedef struct tzbsp_ddr_region_s
{
  uint64 start;
  uint64 size;
} tzbsp_ddr_region_t;
void tzbsp_abort(const char* fmt, ...);
boolean tzbsp_is_hlos_range(const void* start, uint64 len);
boolean tzbsp_is_hyp_range(const void* start, uint64 len);
boolean tzbsp_is_pil_range(const void* start, uint64 len);
boolean tzbsp_is_tz_range(const void* start, uint64 len);
boolean tzbsp_is_s_range(const void* start, uint64 len);
void tzbsp_heap_init(void);
void* tzbsp_malloc(uint64_t size);
void tzbsp_free(void* ptr);
int tzbsp_vtop_iovec(uint64 v_addr, uint32 length, const void *pIoVecPhys);
boolean tzbsp_ddr_contains_area(const void* start_ptr, size_t len);
boolean tzbsp_ddr_get_range(uint64 * start, uint64 * end);
uint32 tzbsp_coalesce_ddr_regions( tzbsp_ddr_region_t *regions, uint32 num_regions );
int tzbsp_mem_map_device(uint32 mmp);
int tzbsp_mem_unmap_device(uint32 mmp);
int tzbsp_mem_unmap_all_devices(void);
int tzbsp_ddr_init(void);
_Bool tzbsp_validate_shmb_access(const void* start, size_t len, uint32_t opts);
struct tzbsp_regs_s;
typedef struct tzbsp_smc_rsp_s {
  uintnt rsp[6];
  uintnt return_to_tee;
} tzbsp_smc_rsp_t;
extern const void * _tz_syscall$$Base;
extern const void * _tz_syscall$$Limit;
extern const void * _tztest_syscall$$Base;
extern const void * _tztest_syscall$$Limit;
typedef int (*tzbsp_syscall_func_t) ();
typedef struct tzbsp_syscall_entry_s
{
  uint32 mink_service_id;
  uint32 smc_id;
  uint32 param_id;
  uint32 flags;
  tzbsp_syscall_func_t func;
} tzbsp_syscall_entry_t;
int tzbsp_syscall(struct tzbsp_regs_s * regs);
typedef enum
{
    AC_SUCCESS = 0,
    AC_FAILURE = 1,
    AC_ERR_VM_CREATE_FAIL = 2,
    AC_ERR_VM_MAP_FAIL1 = 3,
    AC_ERR_RAM_PARTITION_TABLE = 4,
    AC_ERR_VM_MAP_FAIL2 = 5,
    AC_ERR_VM_UNMAP_FAIL1 = 6,
    AC_ERR_VM_MAP_FAIL3 = 7,
    AC_ERR_VM_UNMAP_FAIL2 = 8,
    AC_ERR_TRANSLATION_SET1 = 9,
    AC_ERR_TRANSLATION_SET2 = 10,
    AC_ERR_TRANSLATION_SET3 = 11,
    AC_ERR_VALIDATION_FAIL1 = 12,
    AC_ERR_INCORRECT_VM = 13,
    AC_ERR_IO_ADDRESS_MISMATCH = 14,
    AC_ERR_SHARED_MEMORY_SINGLE_SOURCE = 15,
    AC_ERR_SHARED_MEMORY_SOURCE_MISMATCH = 16,
    AC_ERR_NOT_SHARED_MEMORY_MULTIPLE_SOURCE_GIVEN = 17,
    AC_ERR_MAPPING_TYPE_NOT_SUPPORTED = 18,
    AC_ERR_MAPPING_NOT_FOUND = 19,
    AC_ERR_REMOVE_MEMORY_FROM_LIST_FAIL = 20,
    AC_ERR_CLEAR_MEMORY_FAIL = 21,
    AC_ERR_IS_DEVICE_MEMORY = 22,
    AC_ERR_VMISMAPPED_FAILED = 23,
    AC_ERR_UNCACHED_ALLOC_FAILED = 24,
    AC_ERR_MEMORY_NOT_OWNED_BY_SOURCE_VM = 25,
    AC_ERR_TZ_ASSIGN_SMC_FAILED = 26,
    AC_ERR_VM_UNMAP_FAIL3 = 27,
    AC_ERR_VM_MAP_FAIL4 = 28,
    AC_ERR_MALLOC_FAILED = 29,
    AC_ERR_MEMORY_IN_OWNED_BY_TZ = 30,
    AC_ERR_MEMORY_IN_USE_BY_TZ = 31,
    AC_ERR_XPU_TYPE_NOT_SUPPORTED = 32,
    AC_ERR_XPU_REMOVE_MAPPING_FAILED = 33,
    AC_ERR_XPU_ADD_MAPPING_FAILED = 34,
    AC_ERR_MEMORY_NOT_FOUND_IN_LIST = 35,
    AC_ERR_MEMORY_ALREADY_IN_LIST = 36,
    AC_ERR_ADD_MEMORY_FROM_LIST_FAIL = 37,
    AC_ERR_SIZE_GREATER_THAN_32BITS = 38,
    AC_ERR_INVALID_INDEX = 39,
    AC_ERR_UPDATING_RAM_PARTITION_TABLE = 40,
    AC_ERR_NOT_4K_ALIGNED = 41,
    AC_ERR_MEMORY_NOT_IN_LIST = 42,
    AC_ERR_NOT_DDR_MEMORY = 43,
    AC_ERR_IPA_OVERFLOW = 44,
    AC_ERR_SRC_SIZE_ZERO = 45,
    AC_ERR_SRC_LIST_NULL = 46,
    AC_ERR_DST_SIZE_ZERO = 47,
    AC_ERR_DST_LIST_NULL = 48,
    AC_ERR_SID2VM_SMMU_API_FAILED = 49,
    AC_ERR_SID_VALIDATION_FAIL = 50,
    AC_ERR_UNABLE_TO_XPU_LOCK = 51,
    AC_ERR_STRUCT_SIZE_LESS_THAN_EXPECTED = 52,
    AC_ERR_INVALID_POINTER = 53,
    AC_ERR_IPA_IST_NULL = 54,
    AC_ERR_IPA_LIST_SIZE_ZER0 = 55,
    AC_ERR_MMU_ADD_MAPPING_FAILED = 56,
    AC_ERR_MMU_REMOVE_MAPPING_FAILED = 57,
    AC_ERR_INVALID_PERM_TYPE = 58,
    AC_ERR_MPU_LOCK_MEMORY_FAILED = 59,
    AC_ERR_MPU_UNLOCK_MEMORY_FAILED = 60,
    AC_ERR_USECASE_NOT_SUPPORTED = 61,
    AC_ERR_SRC_VM_TZ_INVALID = 62,
    AC_ERR_NULL_POINTER = 63,
    AC_ERR_TZ_IO_ASSIGN_SMC_FAILED = 64,
    AC_ERR_NOT_DEVICE_MEMORY = 65,
    AC_ERR_SMMU_CFG_TYPE_INVALID = 66,
    AC_ERR_INCORRECT_PERM = 67,
    AC_ERR_MEMORY_IS_SHARED = 68,
    AC_ERR_CANNOT_CHANGE_HLOS_RO_MEMORY = 69,
    AC_ERR_UNABLE_TO_XPU_UNLOCK = 70,
    AC_ERR_ADD_CLEAR_REGION_FAILED = 71,
    AC_ERR_REMOVE_CLEAR_REGION_FAILED = 72,
    AC_ERR_OVERLAPPING_MEMORY = 73,
    AC_ERR_DEVICE_RANGE_CHECK_OVERFLOW = 74,
    AC_ERR_ITS_A_SECURE_DEVICE = 75,
    AC_ERR_NOT_IN_WHITELIST = 76,
    AC_ERR_API_FAILED = 77,
    AC_ERR_SRC_NUM_INVALID = 78,
    AC_ERR_NUM_MAPPING_OVERFLOW = 79,
    AC_ERR_DST_NUM_INVALID = 80,
    AC_ERR_INCORRECT_DEVICE = 81,
    AC_ERR_DEVICE_NOT_FOUND = 82,
    AC_ERR_XPU_PARTIAL_MAPPING_NOT_ALLOWED =83,
    AC_ERR_HASH_OVERFLOW = 84,
    AC_ERR_RULE_NOT_FOUND = 85,
 AC_ERR_VM_SIZE_OVERFLOW = 86,
 AC_VM_RULE_FAILURE1 = 87,
 AC_VM_RULE_FAILURE2 = 88,
 AC_VM_RULE_FAILURE3 = 89,
 AC_VM_RULE_FAILURE4 = 90,
    AC_ERR_DDR_MPU_STATIC_CFG_BLACKLIST_UPDATE = 91,
    AC_ERR_LAST,
    AC_ERR_MAX = 0x7FFFFFFF,
}AC_ERROR_CODE;
typedef enum
{
    AC_COMPLETE,
    AC_ABSENT,
    AC_PARTIAL,
    AC_STATUS_LAST,
    AC_STATUS_MAX = 0x7FFFFFFF,
}ACStatusTypeId;
typedef enum
{
    AC_SMMU,
    AC_MASTER_XPU,
    AC_OTHER,
    AC_SMMU_NO_INIT,
    AC_SMMU_NO_ATTACH,
    AC_SEC,
    AC_LAST,
    AC_MAX = 0x7FFFFFFF,
} ACVMTypeId;
typedef enum
{
    AC_VM_NONE = 0,
    AC_VM_TZ = 1,
    AC_VM_RPM = 2,
    AC_VM_HLOS = 3,
    AC_VM_HYP = 4,
    AC_VM_SSC_Q6_ELF = 5,
    AC_VM_ADSP_Q6_ELF = 6,
    AC_VM_SSC_HLOS = 7,
    AC_VM_CP_TOUCH = 8,
    AC_VM_CP_BITSTREAM = 9,
    AC_VM_CP_PIXEL = 10,
    AC_VM_CP_NON_PIXEL = 11,
    AC_VM_VIDEO_FW = 12,
    AC_VM_CP_CAMERA = 13,
    AC_VM_HLOS_UNMAPPED = 14,
    AC_VM_MSS_MSA = 15,
    AC_VM_MSS_NONMSA = 16,
    AC_VM_CP_SECDISP = 17,
    AC_VM_CP_APP = 18,
    AC_VM_UNMAPPED = 19,
    AC_VM_TZ_UNMAPPED = 20,
    AC_VM_TZ_STATIC = 21,
    AC_VM_LPASS = 22,
    AC_VM_ALL = 23,
    AC_VM_WLAN = 24,
    AC_VM_WLAN_COPYENG = 25,
    AC_VM_SPSS_SP = 26,
    AC_VM_SPSS_NONSP = 27,
    RESERVED_AC_VM1 = 28,
    AC_VM_CP_CAMERA_PREVIEW = 29,
    AC_VM_CDSP_Q6_ELF = 30,
    RESERVED_AC_VM2 = 31,
    AC_VM_HLOS_GSI = 32,
 AC_VM_ADSP_HEAP_SHARED = 33,
 AC_VM_ADSP_SHARED = 34,
    AC_VM_PCIE = 35,
 AC_VM_SHARED_SSC_HEAP = 38,
 AC_VM_SHARED_GPU_PIL = 39,
 AC_VM_SPSS_SP_SHARED = 40,
    AC_VM_LAST = 41,
    AC_VM_MAX = 0x7FFFFFFF,
}ACVirtualMachineId;
typedef enum
{
  SMMU_ERR_OK = 0,
  SMMU_ERR_HAL_SUCCESS = 0,
  SMMU_ERR_GENERIC_ERROR,
  SMMU_ERR_INVALID_PARAM,
  SMMU_ERR_NULL_POINTER,
  SMMU_ERR_OUT_OF_RANGE,
  SMMU_ERR_VMID_NOT_FOUND,
  SMMU_ERR_VMID_NOT_INIT,
  SMMU_ERR_INIT_PT_FAILED,
  SMMU_ERR_REGISTER_MMU_FAILED,
  SMMU_ERR_GET_PT_ATTR_FAILED,
  SMMU_ERR_INVALID_CACHE_ATTR,
  SMMU_ERR_MAP_FAILED,
  SMMU_ERR_UNMAP_FAILED,
  SMMU_ERR_INIT_CLOCK_FAILED,
  SMMU_ERR_ENABLE_CLOCK_FAILED,
  SMMU_ERR_DISABLE_CLOCK_FAILED,
  SMMU_ERR_PAGETABLE_NOT_INIT,
  SMMU_ERR_MALLOC_FAILED,
  SMMU_ERR_GET_DAL_PROP_HANDLE_FAILED,
  SMMU_ERR_UNSUPPORTED_INSTANCE_FOR_TARGET,
  SMMU_ERR_RESULT_SIZE = 0x7FFFFFFF,
} SMMUResult_t;
typedef uint32 SMMUAddr_t;
typedef enum
{
  SMMU_INSTANCE_VIDEO = 0,
  SMMU_INSTANCE_MDP = 1,
  SMMU_INSTANCE_LPASS_Q6 = 2,
  SMMU_INSTANCE_LPASS_CORE = 6,
  SMMU_INSTANCE_GPU = 18,
  SMMU_INSTANCE_ROT = 21,
  SMMU_INSTANCE_VFE = 22,
  SMMU_INSTANCE_ANOC0 = 23,
  SMMU_INSTANCE_ANOC1 = 24,
  SMMU_INSTANCE_ANOC2 = 25,
  SMMU_INSTANCE_CPP = 26,
  SMMU_INSTANCE_JPEG = 27,
  SMMU_INSTANCE_COUNT,
  SMMU_INSTANCE_MAX = 0x7FFFFFFF,
} SMMU_Instance_e_type;
uint64 SMMU_SetDynamicSID2VMID( SMMU_Instance_e_type esmmu_instance, uint32 *sid_list,
                                uint32 num_entries, ACVirtualMachineId dest_vmid);
int SMMU_TZ_SetDynamicSID2VMID( SMMU_Instance_e_type esmmu_instance, uint32 *sid_list,
                                uint32 num_entries, ACVirtualMachineId dest_vmid);
int ACMapSidToVM(SMMU_Instance_e_type uSmmuInstance,
        uint32 *pSIDList,
        uint32 uNumSIDs,
        ACVirtualMachineId uDestinationVm);
struct _ACMemoryVmInfo
{
    uint64 uStart;
    uint32 uSize;
    uint64 uReadVmMask;
    uint64 uWriteVmMask;
};
typedef struct _ACMemoryVmInfo ACMemoryVmInfo;
struct _ACPagesInfo
{
    uint32 uNumExclusivePages;
    uint32 uNumSharedPages;
};
typedef struct _ACPagesInfo ACPagesInfo;
typedef struct tzbsp_mpu_rg_s
{
  uint16 index;
  uint32 flags;
  uint32 read_vmid;
  uint32 write_vmid;
  uint64 start;
  uint64 end;
} tzbsp_mpu_rg_t;
typedef struct tzbsp_rpu_rg_s
{
  uint16 index;
  uint32 flags;
  uint32 read_vmid;
  uint32 write_vmid;
} tzbsp_rpu_rg_t;
typedef struct
{
  uintptr_t phys_addr;
  uint16 id;
  uint16 flags;
  uint32 unmapped_rvmid;
  uint32 unmapped_wvmid;
  uint32 superuser_vmid;
  uint16 nrg;
  union
  {
    const void* any;
    const tzbsp_rpu_rg_t* rpu;
    const tzbsp_mpu_rg_t* mpu;
  } rg;
} tzbsp_xpu_cfg_t;
typedef struct
{
  uint64 xpu2_qrib_init_addr;
  uint64 xpu2_qrib_acr_addr;
  uint64 xpu2_qrib_vmid_en_init_addr;
  uint8 nsen_init;
  uint8 en_tz;
  uint32 xpu_acr_vmid;
  uint8 vmiden_init;
  uint32 vmiden_init_en_hv;
}tzbsp_qrib_cfg_t;
typedef enum
{
  XPU_DISABLE_NONE,
  XPU_DISABLE_NON_MSS,
  XPU_DISABLE_ALL
} xpu_level_t;
typedef struct{
 uint32 index;
 uint32 read_vmid;
 uint32 write_vmid;
}tzbsp_spare_rgn_cfg_details_t;
int ACTzInit(void);
int tzbsp_xpu_lock_area(uint32 id, uintnt start, uintnt end,
                               uint32 rvmid, uint32 wvmid);
int tzbsp_xpu_unlock_area(uint32 id);
int tzbsp_rpu_reconfigure(uint32 xpu_id, const tzbsp_rpu_rg_t *rpu,
                          boolean sec);
int tzbsp_rpu_reconfigure_ext(uint32 xpu_id, const tzbsp_rpu_rg_t *rpu,
                              uint32 domain);
int tzbsp_xpu_config_violation_err_fatal(
                               tz_xpu_violation_err_fatal_t config,
                               uint32 spare,
                               tzbsp_smc_rsp_t *rsp );
int tzbsp_xpu_mpu_reconfigure(uint32 xpu_id, const tzbsp_mpu_rg_t *mpu);
tz_xpu_violation_err_fatal_t tzbsp_xpu_get_violation_err_fatal_status(void);
int tzbsp_xpu_disable(uintptr_t xpu_base_address);
int ACVmidmtRestoreDevice(tz_device_e_type device);
int ACXpuRestoreConfig(tz_device_e_type device);
uint32 ACPrintXpuLogs(void);
uint32 ACLogMutexLock(void);
uint32 ACLogMutexUnLock(void);
uint32 ACValidations(const hyp_memprot_ipa_info_t *IPAinfo,
        uint32 IPAinfolistsize,
        const uint32 *sourceVMlist,
        uint32 srcVMlistsize,
        const hyp_memprot_dstVM_perm_info_t *destVMlist,
        uint32 dstVMlistsize);
uint32 ACValidateParams(uint64 uStart, uint64 uSize, uint32 eVm);
int tzbsp_mpu_lock_area(uint32 mpu, uint32 index, uint64 start,
                        uint64 end, uint32 rvmids, uint32 wvmids);
int tzbsp_mpu_unlock_area(uint32 mpu, uint32 index);
int tzbsp_rpu_unlock_area(uint32 rpu_id, uint32 index);
int tzbsp_unlock_all_xpus();
AC_ERROR_CODE ACTZAssign(const hyp_memprot_ipa_info_t *IPAinfo_tz,
        uint32 IPAinfolistsize,
        const uint32 *sourceVMlist,
        uint32 srcVMlistsize,
        const hyp_memprot_dstVM_perm_info_t *destVMlist,
        uint32 dstVMlistsize);
uint32 ACGetMemoryVmPerm(uint64 uStart, uint64 uSize, uint32 uVm, uint32 *pRetVal);
uint32 ACGetMemoryPerm(uint64 uStart, uint64 uSize, ACMemoryVmInfo *pVMInfo, uint32 uVMInfoSize);
uint32 ACGetNumPagesOwnedByVM(uint32 uVm, ACPagesInfo *pPagesInfo);
uint32 ACIsMemoryOwnedByVMs(uint64 uStart,
        uint64 uSize,
        uint64 uVmMask,
        boolean bExclusive,
        boolean *pRetVal);
uint32 ACIsMemoryOwnedByAnyVMs(uint64 uStart,
        uint64 uSize,
        uint64 uVmMask,
        boolean bExclusive,
        boolean *pRetVal);
AC_ERROR_CODE ACTzClearVmMemory(ACVirtualMachineId eVm);
int ACTzPostMilestoneConfig(void);
int ACClearSecureMem(void);
int ACIsCPZExclusiveMem(uint64 uStartAddr, uint64 uSize, boolean *pRetVal);
uint32 pm_mpu_mapping
(
  tzbsp_mpu_rg_t* cfg_ptr,
  const SpmiCfg_RGConfig* rg_ptr,
  uint32 rg_size
);
tzbsp_mpu_rg_t pm_mpu_rg_cfg [18] =
{
  {0x0, 0x0200 | 0x0800, 0x0, 0x0, 0x0, 0x0},
  {0x0, 0x0200 | 0x0800, 0x0, 0x0, 0x0, 0x0},
  {0x0, 0x0200 | 0x0800, 0x0, 0x0, 0x0, 0x0},
  {0x0, 0x0200 | 0x0800, 0x0, 0x0, 0x0, 0x0},
  {0x0, 0x0200 | 0x0800, 0x0, 0x0, 0x0, 0x0},
  {0x0, 0x0200 | 0x0800, 0x0, 0x0, 0x0, 0x0},
  {0x0, 0x0200 | 0x0800, 0x0, 0x0, 0x0, 0x0},
  {0x0, 0x0200 | 0x0800, 0x0, 0x0, 0x0, 0x0},
  {0x0, 0x0200 | 0x0800, 0x0, 0x0, 0x0, 0x0},
  {0x0, 0x0200 | 0x0800, 0x0, 0x0, 0x0, 0x0},
  {0x0, 0x0200 | 0x0800, 0x0, 0x0, 0x0, 0x0},
  {0x0, 0x0200 | 0x0800, 0x0, 0x0, 0x0, 0x0},
  {0x0, 0x0200 | 0x0800, 0x0, 0x0, 0x0, 0x0},
  {0x0, 0x0200 | 0x0800, 0x0, 0x0, 0x0, 0x0},
  {0x0, 0x0200 | 0x0800, 0x0, 0x0, 0x0, 0x0},
  {0x0, 0x0200 | 0x0800, 0x0, 0x0, 0x0, 0x0},
  {0x0, 0x0200 | 0x0800, 0x0, 0x0, 0x0, 0x0},
  {0x0, 0x0200 | 0x0800, 0x0, 0x0, 0x0, 0x0}
};
SpmiCfg_RGConfig pm_spmi_rg_cfg [18] =
{
    {0x0, 0x0, 0x0, 0x0, 0x0},
    {0x0, 0x0, 0x0, 0x0, 0x0},
    {0x0, 0x0, 0x0, 0x0, 0x0},
    {0x0, 0x0, 0x0, 0x0, 0x0},
    {0x0, 0x0, 0x0, 0x0, 0x0},
    {0x0, 0x0, 0x0, 0x0, 0x0},
    {0x0, 0x0, 0x0, 0x0, 0x0},
    {0x0, 0x0, 0x0, 0x0, 0x0},
    {0x0, 0x0, 0x0, 0x0, 0x0},
    {0x0, 0x0, 0x0, 0x0, 0x0},
    {0x0, 0x0, 0x0, 0x0, 0x0},
    {0x0, 0x0, 0x0, 0x0, 0x0},
    {0x0, 0x0, 0x0, 0x0, 0x0},
    {0x0, 0x0, 0x0, 0x0, 0x0},
    {0x0, 0x0, 0x0, 0x0, 0x0},
    {0x0, 0x0, 0x0, 0x0, 0x0},
    {0x0, 0x0, 0x0, 0x0, 0x0},
    {0x0, 0x0, 0x0, 0x0, 0x0}
};
const uint32 pm_spmi_rg_sz = sizeof(pm_spmi_rg_cfg) / sizeof(SpmiCfg_RGConfig);
const HAL_xpu2_XPU2Type pm_hal_id_xpu = HAL_XPU2_PMIC_ARB;
