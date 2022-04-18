typedef unsigned int uint32;
typedef unsigned short uint16;
typedef unsigned char uint8;
typedef signed int int32;
typedef signed short int16;
typedef signed char int8;
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
typedef uintptr_t uintnt;
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
typedef enum
{
   TLMM_GPIO_MODE_PRIMARY,
   TLMM_GPIO_MODE_IO,
   TLMM_PLACEHOLDER_TLMMGpioModeType = 0x7fffffff
}TLMMGpioModeType;
typedef enum
{
  TLMM_GPIO_INPUT = 0,
  TLMM_GPIO_OUTPUT = 1,
  TLMM_PLACEHOLDER_TLMMGpioDirectionType = 0x7fffffff
}TLMMGpioDirectionType;
typedef enum
{
  TLMM_GPIO_NO_PULL = 0,
  TLMM_GPIO_PULL_DOWN = 0x1,
  TLMM_GPIO_KEEPER = 0x2,
  TLMM_GPIO_PULL_UP = 0x3,
  TLMM_PLACEHOLDER_TLMMGpioPullType = 0x7fffffff
}TLMMGpioPullType;
typedef enum
{
  TLMM_GPIO_2MA = 0,
  TLMM_GPIO_4MA = 0x1,
  TLMM_GPIO_6MA = 0x2,
  TLMM_GPIO_8MA = 0x3,
  TLMM_GPIO_10MA = 0x4,
  TLMM_GPIO_12MA = 0x5,
  TLMM_GPIO_14MA = 0x6,
  TLMM_GPIO_16MA = 0x7,
  TLMM_PLACEHOLDER_TLMMGpioDriveType = 0x7fffffff
}TLMMGpioDriveType;
typedef enum
{
  TLMM_GPIO_LOW_VALUE,
  TLMM_GPIO_HIGH_VALUE,
  TLMM_PLACEHOLDER_TLMMGpioValueType = 0x7fffffff
}TLMMGpioValueType;
typedef uint32 TLMMGpioIdKeyType;
typedef enum
{
  TLMM_GPIO_DISABLE,
  TLMM_GPIO_ENABLE,
  TLMM_PLACEHOLDER_TLMMGpioEnableType = 0x7fffffff
}TLMMGpioEnableType;
typedef struct
{
  TLMMGpioDirectionType eDirection;
  TLMMGpioPullType ePull;
  TLMMGpioDriveType eDriveStrength;
}TLMMGpioConfigIdType;
typedef struct
{
  uint32 nGpioNumber;
  uint32 nFunctionSelect;
  TLMMGpioConfigIdType Settings;
  TLMMGpioValueType eOutputDrive;
}TLMMGpioIdSettingsType;
DALResult Tlmm_GetGpioId(const char* pszGpio, TLMMGpioIdKeyType* pnGpioId);
DALResult Tlmm_ConfigGpioId(TLMMGpioIdKeyType nGpioId, TLMMGpioConfigIdType* pUserSettings);
DALResult Tlmm_ConfigGpioIdInactive(TLMMGpioIdKeyType nGpioId);
DALResult Tlmm_GpioIdOut(TLMMGpioIdKeyType nGpioId, TLMMGpioValueType eValue);
DALResult Tlmm_GpioIdIn(TLMMGpioIdKeyType nGpioId, TLMMGpioValueType *eValue);
DALResult Tlmm_ReleaseGpioId(TLMMGpioIdKeyType nGpioId);
DALResult Tlmm_SelectGpioIdMode(TLMMGpioIdKeyType nGpioId, TLMMGpioModeType eMode, TLMMGpioConfigIdType* pUserSettings);
DALResult Tlmm_GetGpioIdSettings(TLMMGpioIdKeyType nGpioId, TLMMGpioIdSettingsType* pGpioSettings);
int Tlmm_Init(void);
typedef enum I2cResult
{
   I2C_RES_SUCCESS =0,
   I2C_RES_ERROR_CLS_I2C_CORE = (int32)0x10000000,
   I2C_RES_ERROR_CLS_QUP_DEV_TIMEOUT = (int32)0x20000000,
   I2C_RES_ERROR_CLS_QUP_DEV = (int32)0x30000000,
   I2C_RES_ERROR_CLS_I2C_DRV = (int32)0x40000000,
   I2C_RES_ERROR_CLS_DEV_PLATFORM = (int32)0xE0000000,
   I2C_RES_ERROR_CLS_DEV_OS = (int32)0xF0000000,
} I2cResult;
typedef struct I2CPLATDEV_PropertyType
{
   uint8 *virtBlockAddr;
   uint32 uI2cInputClkKhz;
   boolean bInterruptBased;
} I2CPLATDEV_PropertyType;
typedef void* I2CPLATDEV_HANDLE;
typedef void (*IST_HOOK)(void *pdata);
typedef void (*ISR_HOOK)(void *pdata);
int32
I2CPLATDEV_DeInitTarget
(
   I2CPLATDEV_HANDLE hPlatDev
);
int32
I2CPLATDEV_InitTarget
(
   uint32 uPlatDevId,
   I2CPLATDEV_HANDLE *phPlatDev
);
int32
I2CPLATDEV_ResetTarget
(
   I2CPLATDEV_HANDLE hPlatDev
);
int32
I2CPLATDEV_SetPowerState
(
   I2CPLATDEV_HANDLE hPlatDev,
   uint32 state
);
int32
I2CPLATDEV_GetPowerState
(
   I2CPLATDEV_HANDLE hPlatDev,
   uint32 *pState
);
int32 I2CPLATDEV_ReadProperties
(
   I2CPLATDEV_HANDLE hPlatDev,
   I2CPLATDEV_PropertyType *pDevProp
);
void
I2CPLATDEV_AcquireIntLock
(
   I2CPLATDEV_HANDLE hPlatDev
);
void
I2CPLATDEV_ReleaseIntLock
(
   I2CPLATDEV_HANDLE hPlatDev
);
boolean
I2CPLATDEV_IsBamEnabled
(
   I2CPLATDEV_HANDLE hPlatDev
);
int32
I2CSYS_RegisterISTHooks
(
   I2CPLATDEV_HANDLE hPlatDev,
   ISR_HOOK IsrHook,
   void* pIsrData,
   IST_HOOK IstHook,
   void* pIstData
);
int32
I2CSYS_UnRegisterISTHooks
(
   I2CPLATDEV_HANDLE hPlatDev
);
<driver name="I2C">
    <global_def>
       <string name="blsp1_i2c_qup1_appsclk" type=DALPROP_DATA_TYPE_STRING> gcc_blsp1_qup1_i2c_apps_clk </string>
       <string name="blsp1_i2c_qup2_appsclk" type=DALPROP_DATA_TYPE_STRING> gcc_blsp1_qup2_i2c_apps_clk </string>
       <string name="blsp1_i2c_qup3_appsclk" type=DALPROP_DATA_TYPE_STRING> gcc_blsp1_qup3_i2c_apps_clk </string>
       <string name="blsp1_i2c_qup4_appsclk" type=DALPROP_DATA_TYPE_STRING> gcc_blsp1_qup4_i2c_apps_clk </string>
       <string name="blsp2_i2c_qup1_appsclk" type=DALPROP_DATA_TYPE_STRING> gcc_blsp2_qup1_i2c_apps_clk </string>
       <string name="blsp2_i2c_qup2_appsclk" type=DALPROP_DATA_TYPE_STRING> gcc_blsp2_qup2_i2c_apps_clk </string>
       <string name="blsp2_i2c_qup3_appsclk" type=DALPROP_DATA_TYPE_STRING> gcc_blsp2_qup3_i2c_apps_clk </string>
       <string name="blsp2_i2c_qup4_appsclk" type=DALPROP_DATA_TYPE_STRING> gcc_blsp2_qup4_i2c_apps_clk </string>
       <string name="blsp1_i2c_qup_ahb_clk" type=DALPROP_DATA_TYPE_STRING> gcc_blsp1_ahb_clk </string>
       <string name="blsp2_i2c_qup_ahb_clk" type=DALPROP_DATA_TYPE_STRING> gcc_blsp2_ahb_clk </string>
       <string name="blsp1_i2c_qup1_gpio_sda" type=DALPROP_DATA_TYPE_STRING> blsp_i2c_sda[1] </string>
       <string name="blsp1_i2c_qup1_gpio_scl" type=DALPROP_DATA_TYPE_STRING> blsp_i2c_scl[1] </string>
       <string name="blsp1_i2c_qup2_gpio_sda" type=DALPROP_DATA_TYPE_STRING> blsp_i2c_sda[2] </string>
       <string name="blsp1_i2c_qup2_gpio_scl" type=DALPROP_DATA_TYPE_STRING> blsp_i2c_scl[2] </string>
       <string name="blsp1_i2c_qup3_gpio_sda" type=DALPROP_DATA_TYPE_STRING> blsp_i2c_sda[3] </string>
       <string name="blsp1_i2c_qup3_gpio_scl" type=DALPROP_DATA_TYPE_STRING> blsp_i2c_scl[3] </string>
       <string name="blsp1_i2c_qup4_gpio_sda" type=DALPROP_DATA_TYPE_STRING> blsp_i2c_sda[4] </string>
       <string name="blsp1_i2c_qup4_gpio_scl" type=DALPROP_DATA_TYPE_STRING> blsp_i2c_scl[4] </string>
       <string name="blsp2_i2c_qup1_gpio_sda" type=DALPROP_DATA_TYPE_STRING> blsp_i2c_sda[5] </string>
       <string name="blsp2_i2c_qup1_gpio_scl" type=DALPROP_DATA_TYPE_STRING> blsp_i2c_scl[5] </string>
       <string name="blsp2_i2c_qup2_gpio_sda" type=DALPROP_DATA_TYPE_STRING> blsp_i2c_sda[6] </string>
       <string name="blsp2_i2c_qup2_gpio_scl" type=DALPROP_DATA_TYPE_STRING> blsp_i2c_scl[6] </string>
       <string name="blsp2_i2c_qup3_gpio_sda" type=DALPROP_DATA_TYPE_STRING> blsp_i2c_sda[7] </string>
       <string name="blsp2_i2c_qup3_gpio_scl" type=DALPROP_DATA_TYPE_STRING> blsp_i2c_scl[7] </string>
       <string name="blsp2_i2c_qup4_gpio_sda" type=DALPROP_DATA_TYPE_STRING> blsp_i2c_sda[8] </string>
       <string name="blsp2_i2c_qup4_gpio_scl" type=DALPROP_DATA_TYPE_STRING> blsp_i2c_scl[8] </string>
    </global_def>
    <device id="/dev/buses/i2c_1">
        <props name="CHIP_BUS_INDEX" type=DALPROP_ATTR_TYPE_UINT32> 0 </props>
        <props name="CHIP_IRQ_NUM" type=DALPROP_ATTR_TYPE_UINT32> 127 </props>
        <props name="CHIP_QUP_BASE_ADDR" type=DALPROP_ATTR_TYPE_UINT32> 0xC175000 </props>
        <props name="CHIP_APPS_CLK_FREQ_KHZ" type=DALPROP_ATTR_TYPE_UINT32> 19200 </props>
        <props name="CHIP_BLSP_NUM" type=DALPROP_ATTR_TYPE_UINT32> 1 </props>
        <props name="SW_ENABLE_INTERRUPTS" type=DALPROP_ATTR_TYPE_UINT32> 0 </props>
        <props name="I2CQUP_APPS_CLK" type=DALPROP_ATTR_TYPE_STRING_PTR> blsp1_i2c_qup1_appsclk </props>
        <props name="I2CQUP_AHB_CLK" type=DALPROP_ATTR_TYPE_STRING_PTR> blsp1_i2c_qup_ahb_clk </props>
        <props name="I2CQUP_GPIO_SDA" type=DALPROP_ATTR_TYPE_STRING_PTR> blsp1_i2c_qup1_gpio_sda </props>
        <props name="I2CQUP_GPIO_SCL" type=DALPROP_ATTR_TYPE_STRING_PTR> blsp1_i2c_qup1_gpio_scl </props>
  <props name="I2CQUP_GPIO_SDA_CFG" type="TLMMGpioConfigIdType"> {TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_UP, TLMM_GPIO_2MA} </props>
  <props name="I2CQUP_GPIO_SCL_CFG" type="TLMMGpioConfigIdType"> {TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_UP, TLMM_GPIO_2MA} </props>
    </device>
    <device id="/dev/buses/i2c_2">
        <props name="CHIP_BUS_INDEX" type=DALPROP_ATTR_TYPE_UINT32> 1 </props>
        <props name="CHIP_IRQ_NUM" type=DALPROP_ATTR_TYPE_UINT32> 128 </props>
        <props name="CHIP_QUP_BASE_ADDR" type=DALPROP_ATTR_TYPE_UINT32> 0xC176000 </props>
        <props name="CHIP_APPS_CLK_FREQ_KHZ" type=DALPROP_ATTR_TYPE_UINT32> 19200 </props>
        <props name="CHIP_BLSP_NUM" type=DALPROP_ATTR_TYPE_UINT32> 1 </props>
        <props name="SW_ENABLE_INTERRUPTS" type=DALPROP_ATTR_TYPE_UINT32> 0 </props>
        <props name="I2CQUP_APPS_CLK" type=DALPROP_ATTR_TYPE_STRING_PTR> blsp1_i2c_qup2_appsclk </props>
        <props name="I2CQUP_AHB_CLK" type=DALPROP_ATTR_TYPE_STRING_PTR> blsp1_i2c_qup_ahb_clk </props>
        <props name="I2CQUP_GPIO_SDA" type=DALPROP_ATTR_TYPE_STRING_PTR> blsp1_i2c_qup2_gpio_sda </props>
        <props name="I2CQUP_GPIO_SCL" type=DALPROP_ATTR_TYPE_STRING_PTR> blsp1_i2c_qup2_gpio_scl </props>
        <props name="I2CQUP_GPIO_SDA_CFG" type="TLMMGpioConfigIdType"> {TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_UP, TLMM_GPIO_2MA} </props>
  <props name="I2CQUP_GPIO_SCL_CFG" type="TLMMGpioConfigIdType"> {TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_UP, TLMM_GPIO_2MA} </props>
    </device>
    <device id="/dev/buses/i2c_3">
        <props name="CHIP_BUS_INDEX" type=DALPROP_ATTR_TYPE_UINT32> 2 </props>
        <props name="CHIP_IRQ_NUM" type=DALPROP_ATTR_TYPE_UINT32> 129 </props>
        <props name="CHIP_QUP_BASE_ADDR" type=DALPROP_ATTR_TYPE_UINT32> 0xC177000 </props>
        <props name="CHIP_APPS_CLK_FREQ_KHZ" type=DALPROP_ATTR_TYPE_UINT32> 19200 </props>
        <props name="CHIP_BLSP_NUM" type=DALPROP_ATTR_TYPE_UINT32> 1 </props>
        <props name="SW_ENABLE_INTERRUPTS" type=DALPROP_ATTR_TYPE_UINT32> 0 </props>
        <props name="I2CQUP_APPS_CLK" type=DALPROP_ATTR_TYPE_STRING_PTR> blsp1_i2c_qup3_appsclk </props>
        <props name="I2CQUP_AHB_CLK" type=DALPROP_ATTR_TYPE_STRING_PTR> blsp1_i2c_qup_ahb_clk </props>
        <props name="I2CQUP_GPIO_SDA" type=DALPROP_ATTR_TYPE_STRING_PTR> blsp1_i2c_qup3_gpio_sda </props>
        <props name="I2CQUP_GPIO_SCL" type=DALPROP_ATTR_TYPE_STRING_PTR> blsp1_i2c_qup3_gpio_scl </props>
  <props name="I2CQUP_GPIO_SDA_CFG" type="TLMMGpioConfigIdType"> {TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_UP, TLMM_GPIO_2MA} </props>
  <props name="I2CQUP_GPIO_SCL_CFG" type="TLMMGpioConfigIdType"> {TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_UP, TLMM_GPIO_2MA} </props>
    </device>
    <device id="/dev/buses/i2c_4">
        <props name="CHIP_BUS_INDEX" type=DALPROP_ATTR_TYPE_UINT32> 3 </props>
        <props name="CHIP_IRQ_NUM" type=DALPROP_ATTR_TYPE_UINT32> 130 </props>
        <props name="CHIP_QUP_BASE_ADDR" type=DALPROP_ATTR_TYPE_UINT32> 0xC178000 </props>
        <props name="CHIP_APPS_CLK_FREQ_KHZ" type=DALPROP_ATTR_TYPE_UINT32> 19200 </props>
  <props name="CHIP_BLSP_NUM" type=DALPROP_ATTR_TYPE_UINT32> 1 </props>
        <props name="SW_ENABLE_INTERRUPTS" type=DALPROP_ATTR_TYPE_UINT32> 0 </props>
        <props name="I2CQUP_APPS_CLK" type=DALPROP_ATTR_TYPE_STRING_PTR> blsp1_i2c_qup4_appsclk </props>
        <props name="I2CQUP_AHB_CLK" type=DALPROP_ATTR_TYPE_STRING_PTR> blsp1_i2c_qup_ahb_clk </props>
        <props name="I2CQUP_GPIO_SDA" type=DALPROP_ATTR_TYPE_STRING_PTR> blsp1_i2c_qup4_gpio_sda </props>
        <props name="I2CQUP_GPIO_SCL" type=DALPROP_ATTR_TYPE_STRING_PTR> blsp1_i2c_qup4_gpio_scl </props>
        <props name="I2CQUP_GPIO_SDA_CFG" type="TLMMGpioConfigIdType"> {TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_UP, TLMM_GPIO_2MA} </props>
  <props name="I2CQUP_GPIO_SCL_CFG" type="TLMMGpioConfigIdType"> {TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_UP, TLMM_GPIO_2MA} </props>
    </device>
    <device id="/dev/buses/i2c_5">
        <props name="CHIP_BUS_INDEX" type=DALPROP_ATTR_TYPE_UINT32> 4 </props>
  <props name="CHIP_IRQ_NUM" type=DALPROP_ATTR_TYPE_UINT32> 133 </props>
        <props name="CHIP_QUP_BASE_ADDR" type=DALPROP_ATTR_TYPE_UINT32> 0xC1B5000 </props>
        <props name="CHIP_APPS_CLK_FREQ_KHZ" type=DALPROP_ATTR_TYPE_UINT32> 19200 </props>
  <props name="CHIP_BLSP_NUM" type=DALPROP_ATTR_TYPE_UINT32> 2 </props>
        <props name="SW_ENABLE_INTERRUPTS" type=DALPROP_ATTR_TYPE_UINT32> 0 </props>
        <props name="I2CQUP_APPS_CLK" type=DALPROP_ATTR_TYPE_STRING_PTR> blsp2_i2c_qup1_appsclk </props>
        <props name="I2CQUP_AHB_CLK" type=DALPROP_ATTR_TYPE_STRING_PTR> blsp2_i2c_qup_ahb_clk </props>
        <props name="I2CQUP_GPIO_SDA" type=DALPROP_ATTR_TYPE_STRING_PTR> blsp2_i2c_qup1_gpio_sda </props>
        <props name="I2CQUP_GPIO_SCL" type=DALPROP_ATTR_TYPE_STRING_PTR> blsp2_i2c_qup1_gpio_scl </props>
        <props name="I2CQUP_GPIO_SDA_CFG" type="TLMMGpioConfigIdType"> {TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_UP, TLMM_GPIO_2MA} </props>
  <props name="I2CQUP_GPIO_SCL_CFG" type="TLMMGpioConfigIdType"> {TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_UP, TLMM_GPIO_2MA} </props>
    </device>
    <device id="/dev/buses/i2c_6">
        <props name="CHIP_BUS_INDEX" type=DALPROP_ATTR_TYPE_UINT32> 5 </props>
  <props name="CHIP_IRQ_NUM" type=DALPROP_ATTR_TYPE_UINT32> 134 </props>
        <props name="CHIP_QUP_BASE_ADDR" type=DALPROP_ATTR_TYPE_UINT32> 0xC1B6000 </props>
        <props name="CHIP_APPS_CLK_FREQ_KHZ" type=DALPROP_ATTR_TYPE_UINT32> 19200 </props>
  <props name="CHIP_BLSP_NUM" type=DALPROP_ATTR_TYPE_UINT32> 2 </props>
        <props name="SW_ENABLE_INTERRUPTS" type=DALPROP_ATTR_TYPE_UINT32> 0 </props>
        <props name="I2CQUP_APPS_CLK" type=DALPROP_ATTR_TYPE_STRING_PTR> blsp2_i2c_qup2_appsclk </props>
        <props name="I2CQUP_AHB_CLK" type=DALPROP_ATTR_TYPE_STRING_PTR> blsp2_i2c_qup_ahb_clk </props>
        <props name="I2CQUP_GPIO_SDA" type=DALPROP_ATTR_TYPE_STRING_PTR> blsp2_i2c_qup2_gpio_sda </props>
        <props name="I2CQUP_GPIO_SCL" type=DALPROP_ATTR_TYPE_STRING_PTR> blsp2_i2c_qup2_gpio_scl </props>
        <props name="I2CQUP_GPIO_SDA_CFG" type="TLMMGpioConfigIdType"> {TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_UP, TLMM_GPIO_2MA} </props>
  <props name="I2CQUP_GPIO_SCL_CFG" type="TLMMGpioConfigIdType"> {TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_UP, TLMM_GPIO_2MA} </props>
    </device>
    <device id="/dev/buses/i2c_7">
        <props name="CHIP_BUS_INDEX" type=DALPROP_ATTR_TYPE_UINT32> 6 </props>
  <props name="CHIP_IRQ_NUM" type=DALPROP_ATTR_TYPE_UINT32> 135 </props>
        <props name="CHIP_QUP_BASE_ADDR" type=DALPROP_ATTR_TYPE_UINT32> 0xC1B7000 </props>
        <props name="CHIP_APPS_CLK_FREQ_KHZ" type=DALPROP_ATTR_TYPE_UINT32> 19200 </props>
        <props name="CHIP_BLSP_NUM" type=DALPROP_ATTR_TYPE_UINT32> 2 </props>
        <props name="SW_ENABLE_INTERRUPTS" type=DALPROP_ATTR_TYPE_UINT32> 0 </props>
        <props name="I2CQUP_APPS_CLK" type=DALPROP_ATTR_TYPE_STRING_PTR> blsp2_i2c_qup3_appsclk </props>
        <props name="I2CQUP_AHB_CLK" type=DALPROP_ATTR_TYPE_STRING_PTR> blsp2_i2c_qup_ahb_clk </props>
        <props name="I2CQUP_GPIO_SDA" type=DALPROP_ATTR_TYPE_STRING_PTR> blsp2_i2c_qup3_gpio_sda </props>
        <props name="I2CQUP_GPIO_SCL" type=DALPROP_ATTR_TYPE_STRING_PTR> blsp2_i2c_qup3_gpio_scl </props>
  <props name="I2CQUP_GPIO_SDA_CFG" type="TLMMGpioConfigIdType"> {TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_UP, TLMM_GPIO_2MA} </props>
  <props name="I2CQUP_GPIO_SCL_CFG" type="TLMMGpioConfigIdType"> {TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_UP, TLMM_GPIO_2MA} </props>
    </device>
    <device id="/dev/buses/i2c_8">
        <props name="CHIP_BUS_INDEX" type=DALPROP_ATTR_TYPE_UINT32> 7 </props>
  <props name="CHIP_IRQ_NUM" type=DALPROP_ATTR_TYPE_UINT32> 136 </props>
        <props name="CHIP_QUP_BASE_ADDR" type=DALPROP_ATTR_TYPE_UINT32> 0xC1B8000 </props>
        <props name="CHIP_APPS_CLK_FREQ_KHZ" type=DALPROP_ATTR_TYPE_UINT32> 19200 </props>
  <props name="CHIP_BLSP_NUM" type=DALPROP_ATTR_TYPE_UINT32> 2 </props>
        <props name="SW_ENABLE_INTERRUPTS" type=DALPROP_ATTR_TYPE_UINT32> 0 </props>
        <props name="I2CQUP_APPS_CLK" type=DALPROP_ATTR_TYPE_STRING_PTR> blsp2_i2c_qup4_appsclk </props>
        <props name="I2CQUP_AHB_CLK" type=DALPROP_ATTR_TYPE_STRING_PTR> blsp2_i2c_qup_ahb_clk </props>
        <props name="I2CQUP_GPIO_SDA" type=DALPROP_ATTR_TYPE_STRING_PTR> blsp2_i2c_qup4_gpio_sda </props>
        <props name="I2CQUP_GPIO_SCL" type=DALPROP_ATTR_TYPE_STRING_PTR> blsp2_i2c_qup4_gpio_scl </props>
  <props name="I2CQUP_GPIO_SDA_CFG" type="TLMMGpioConfigIdType"> {TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_UP, TLMM_GPIO_2MA} </props>
  <props name="I2CQUP_GPIO_SCL_CFG" type="TLMMGpioConfigIdType"> {TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_UP, TLMM_GPIO_2MA} </props>
    </device>
</driver>
