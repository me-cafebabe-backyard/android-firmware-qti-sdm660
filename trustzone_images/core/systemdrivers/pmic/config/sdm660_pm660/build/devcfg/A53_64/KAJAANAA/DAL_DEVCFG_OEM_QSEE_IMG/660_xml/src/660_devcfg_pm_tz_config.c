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
static SpmiCfg_Ppid pm_pvc_apps0_addr[] =
{
  {0x1, 0x1440},
  {0x1, 0x1441},
  {0x1, 0x1445},
  {0x1, 0x1446},
};
static SpmiCfg_Ppid pm_pvc_apps1_addr[] =
{
  {0x1, 0x1A40},
  {0x1, 0x1A41},
  {0x1, 0x1A45},
  {0x1, 0x1A46},
};
static SpmiCfg_Ppid pm_pvc_mss_addr[] =
{
  {0x1, 0x2340},
  {0x1, 0x2341},
  {0x0, 0x7350},
  {0x0, 0x7342},
};
static SpmiCfg_Ppid pm_pvc_mgpi_addr[] =
{
  {0x2, 0x094A},
};
const SpmiCfg_PvcPortCfg pm_arb_pvc_cfg[] =
{
  {
                        1,
                       SPMI_ACCESS_PRIORITY_LOW,
                       pm_pvc_apps0_addr,
                       sizeof(pm_pvc_apps0_addr)/sizeof(SpmiCfg_Ppid)
  },
  {
                        2,
                       SPMI_ACCESS_PRIORITY_LOW,
                       pm_pvc_apps1_addr,
                       sizeof(pm_pvc_apps1_addr)/sizeof(SpmiCfg_Ppid)
  },
  {
                        5,
                       SPMI_ACCESS_PRIORITY_LOW,
                       pm_pvc_mss_addr,
                       sizeof(pm_pvc_mss_addr)/sizeof(SpmiCfg_Ppid)
  },
};
const uint32 pm_num_pvc_port = sizeof(pm_arb_pvc_cfg) / sizeof(SpmiCfg_PvcPortCfg);
const uint8 pm_arb_priorities[] =
{
    0,
    (1 +1),
    (2 +1),
    (5 +1),
};
const uint32 pm_num_prio = sizeof(pm_arb_priorities) / sizeof(uint8);
