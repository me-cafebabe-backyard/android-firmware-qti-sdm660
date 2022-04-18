<!--
===================================================================================== -->
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
<driver name="NULL">
   <global_def>
     <string name="gpio_spi1_clk_str" type=DALPROP_DATA_TYPE_STRING>blsp_spi_clk[1]</string>
  <string name="gpio_spi1_cs_str" type=DALPROP_DATA_TYPE_STRING>blsp_spi_cs_n[1]</string>
  <string name="gpio_spi1_cs1_str" type=DALPROP_DATA_TYPE_STRING>blsp_spi_cs1_n[1]</string>
  <string name="gpio_spi1_mosi_str" type=DALPROP_DATA_TYPE_STRING>blsp_spi_mosi[1]</string>
  <string name="gpio_spi1_miso_str" type=DALPROP_DATA_TYPE_STRING>blsp_spi_miso[1]</string>
  <string name="gpio_spi2_clk_str" type=DALPROP_DATA_TYPE_STRING>blsp_spi_clk[2]</string>
  <string name="gpio_spi2_cs_str" type=DALPROP_DATA_TYPE_STRING>blsp_spi_cs_n[2]</string>
   <string name="gpio_spi2_mosi_str" type=DALPROP_DATA_TYPE_STRING>blsp_spi_mosi[2]</string>
  <string name="gpio_spi2_miso_str" type=DALPROP_DATA_TYPE_STRING>blsp_spi_miso[2]</string>
  <string name="gpio_spi3_clk_str" type=DALPROP_DATA_TYPE_STRING>blsp_spi_clk[3]</string>
  <string name="gpio_spi3_cs_str" type=DALPROP_DATA_TYPE_STRING>blsp_spi_cs_n[3]</string>
  <string name="gpio_spi3_cs1_str" type=DALPROP_DATA_TYPE_STRING>blsp_spi_cs1_n[3]</string>
  <string name="gpio_spi3_cs2_str" type=DALPROP_DATA_TYPE_STRING>blsp_spi_cs2_n[3]</string>
  <string name="gpio_spi3_mosi_str" type=DALPROP_DATA_TYPE_STRING>blsp_spi_mosi[3]</string>
  <string name="gpio_spi3_miso_str" type=DALPROP_DATA_TYPE_STRING>blsp_spi_miso[3]</string>
  <string name="gpio_spi4_clk_str" type=DALPROP_DATA_TYPE_STRING>blsp_spi_clk[4]</string>
  <string name="gpio_spi4_cs_str" type=DALPROP_DATA_TYPE_STRING>blsp_spi_cs_n[4]</string>
  <string name="gpio_spi4_mosi_str" type=DALPROP_DATA_TYPE_STRING>blsp_spi_mosi[4]</string>
  <string name="gpio_spi4_miso_str" type=DALPROP_DATA_TYPE_STRING>blsp_spi_miso[4]</string>
  <string name="gpio_spi5_clk_str" type=DALPROP_DATA_TYPE_STRING>blsp_spi_clk[5]</string>
  <string name="gpio_spi5_cs_str" type=DALPROP_DATA_TYPE_STRING>blsp_spi_cs_n[5]</string>
  <string name="gpio_spi5_mosi_str" type=DALPROP_DATA_TYPE_STRING>blsp_spi_mosi[5]</string>
  <string name="gpio_spi5_miso_str" type=DALPROP_DATA_TYPE_STRING>blsp_spi_miso[5]</string>
  <string name="gpio_spi6_clk_str" type=DALPROP_DATA_TYPE_STRING>blsp_spi_clk[6]</string>
  <string name="gpio_spi6_cs_str" type=DALPROP_DATA_TYPE_STRING>blsp_spi_cs_n[6]</string>
  <string name="gpio_spi6_mosi_str" type=DALPROP_DATA_TYPE_STRING>blsp_spi_mosi[6]</string>
  <string name="gpio_spi6_miso_str" type=DALPROP_DATA_TYPE_STRING>blsp_spi_miso[6]</string>
  <string name="gpio_spi7_clk_str" type=DALPROP_DATA_TYPE_STRING>blsp_spi_clk[7]</string>
  <string name="gpio_spi7_cs_str" type=DALPROP_DATA_TYPE_STRING>blsp_spi_cs_n[7]</string>
  <string name="gpio_spi7_mosi_str" type=DALPROP_DATA_TYPE_STRING>blsp_spi_mosi[7]</string>
  <string name="gpio_spi7_miso_str" type=DALPROP_DATA_TYPE_STRING>blsp_spi_miso[7]</string>
  <string name="gpio_spi8_clk_str" type=DALPROP_DATA_TYPE_STRING>blsp_spi_clk8_mira</string>
  <string name="gpio_spi8_cs_str" type=DALPROP_DATA_TYPE_STRING>blsp_spi_cs_n8_mira</string>
  <string name="gpio_spi8_cs1_str" type=DALPROP_DATA_TYPE_STRING>blsp_spi_cs1_n[8]</string>
  <string name="gpio_spi8_cs2_str" type=DALPROP_DATA_TYPE_STRING>blsp_spi_cs2_n[8]</string>
  <string name="gpio_spi8_mosi_str" type=DALPROP_DATA_TYPE_STRING>blsp_spi_mosi8_mira</string>
  <string name="gpio_spi8_miso_str" type=DALPROP_DATA_TYPE_STRING>blsp_spi_miso8_mira</string>
     <var_seq name="spiqup1_appclk_name" type=DALPROP_DATA_TYPE_STRING> gcc_blsp1_qup1_spi_apps_clk </var_seq>
  <var_seq name="spiqup2_appclk_name" type=DALPROP_DATA_TYPE_STRING> gcc_blsp1_qup2_spi_apps_clk </var_seq>
  <var_seq name="spiqup3_appclk_name" type=DALPROP_DATA_TYPE_STRING> gcc_blsp1_qup3_spi_apps_clk </var_seq>
  <var_seq name="spiqup4_appclk_name" type=DALPROP_DATA_TYPE_STRING> gcc_blsp1_qup4_spi_apps_clk </var_seq>
  <var_seq name="spiqup5_appclk_name" type=DALPROP_DATA_TYPE_STRING> gcc_blsp2_qup1_spi_apps_clk </var_seq>
  <var_seq name="spiqup6_appclk_name" type=DALPROP_DATA_TYPE_STRING> gcc_blsp2_qup2_spi_apps_clk </var_seq>
     <var_seq name="spiqup7_appclk_name" type=DALPROP_DATA_TYPE_STRING> gcc_blsp2_qup3_spi_apps_clk </var_seq>
  <var_seq name="spiqup8_appclk_name" type=DALPROP_DATA_TYPE_STRING> gcc_blsp2_qup4_spi_apps_clk </var_seq>
  <var_seq name="spi_blsp1_hclk_name" type=DALPROP_DATA_TYPE_STRING> gcc_blsp1_ahb_clk </var_seq>
     <var_seq name="spi_blsp2_hclk_name" type=DALPROP_DATA_TYPE_STRING> gcc_blsp2_ahb_clk </var_seq>
    </global_def>
    <device id="/dev/buses/spi_1">
        <props name="QUP_CORE_NUM" type=DALPROP_ATTR_TYPE_UINT32> 1 </props>
        <props name="QUP_BASE_ADDR" type=DALPROP_ATTR_TYPE_UINT32> 0xC175000 </props>
        <props name="SW_ENABLE_BAM" type=DALPROP_ATTR_TYPE_UINT32> 1 </props>
        <props name="BAM_BLSP_ID" type=DALPROP_ATTR_TYPE_UINT32> 1 </props>
        <props name="BAM_BASE_ADDR" type=DALPROP_ATTR_TYPE_UINT32> 0xC144000 </props>
        <props name="BAM_INTERRUPT_ID" type=DALPROP_ATTR_TYPE_UINT32> 270 </props>
        <props name="BAM_TX_PIPE_NUM" type=DALPROP_ATTR_TYPE_UINT32> 4 </props>
        <props name="BAM_RX_PIPE_NUM" type=DALPROP_ATTR_TYPE_UINT32> 5 </props>
        <props name="is_multi_cs" type=DALPROP_ATTR_TYPE_UINT32> 0 </props>
        <props name="gpio_spi_clk_str" type=DALPROP_ATTR_TYPE_STRING_PTR>gpio_spi1_clk_str</props>
        <props name="gpio_spi_cs_str" type=DALPROP_ATTR_TYPE_STRING_PTR>gpio_spi1_cs_str</props>
        <props name="gpio_spi_cs1_str" type=DALPROP_ATTR_TYPE_STRING_PTR>gpio_spi1_cs1_str</props>
        <props name="gpio_spi_mosi_str" type=DALPROP_ATTR_TYPE_STRING_PTR>gpio_spi1_mosi_str</props>
        <props name="gpio_spi_miso_str" type=DALPROP_ATTR_TYPE_STRING_PTR>gpio_spi1_miso_str</props>
        <props name="GpioClkConfig" type="TLMMGpioConfigIdType"> {TLMM_GPIO_INPUT, TLMM_GPIO_PULL_DOWN, TLMM_GPIO_8MA} </props>
        <props name="GpioCsConfig" type="TLMMGpioConfigIdType"> {TLMM_GPIO_INPUT, TLMM_GPIO_PULL_DOWN, TLMM_GPIO_8MA} </props>
        <props name="GpioCs1Config" type="TLMMGpioConfigIdType"> {TLMM_GPIO_INPUT, TLMM_GPIO_PULL_DOWN, TLMM_GPIO_8MA} </props>
        <props name="GpioMosiConfig" type="TLMMGpioConfigIdType"> {TLMM_GPIO_INPUT, TLMM_GPIO_PULL_DOWN, TLMM_GPIO_8MA} </props>
        <props name="GpioMisoConfig" type="TLMMGpioConfigIdType"> {TLMM_GPIO_INPUT, TLMM_GPIO_PULL_DOWN, TLMM_GPIO_8MA} </props>
        <props name="CHIP_APP_CLK_NAME" type=DALPROP_ATTR_TYPE_STRING_PTR> spiqup1_appclk_name </props>
        <props name="CHIP_HCLK_NAME" type=DALPROP_ATTR_TYPE_STRING_PTR> spi_blsp1_hclk_name </props>
    </device>
    <device id="/dev/buses/spi_2">
        <props name="QUP_CORE_NUM" type=DALPROP_ATTR_TYPE_UINT32> 2 </props>
        <props name="QUP_BASE_ADDR" type=DALPROP_ATTR_TYPE_UINT32> 0xC176000 </props>
        <props name="SW_ENABLE_BAM" type=DALPROP_ATTR_TYPE_UINT32> 1 </props>
        <props name="BAM_BLSP_ID" type=DALPROP_ATTR_TYPE_UINT32> 1 </props>
        <props name="BAM_BASE_ADDR" type=DALPROP_ATTR_TYPE_UINT32> 0xC144000 </props>
        <props name="BAM_INTERRUPT_ID" type=DALPROP_ATTR_TYPE_UINT32> 270 </props>
        <props name="BAM_TX_PIPE_NUM" type=DALPROP_ATTR_TYPE_UINT32> 6 </props>
        <props name="BAM_RX_PIPE_NUM" type=DALPROP_ATTR_TYPE_UINT32> 7 </props>
        <props name="gpio_spi_clk_str" type=DALPROP_ATTR_TYPE_STRING_PTR>gpio_spi2_clk_str</props>
        <props name="gpio_spi_cs_str" type=DALPROP_ATTR_TYPE_STRING_PTR>gpio_spi2_cs_str</props>
        <props name="gpio_spi_mosi_str" type=DALPROP_ATTR_TYPE_STRING_PTR>gpio_spi2_mosi_str</props>
        <props name="gpio_spi_miso_str" type=DALPROP_ATTR_TYPE_STRING_PTR>gpio_spi2_miso_str</props>
        <props name="GpioClkConfig" type="TLMMGpioConfigIdType"> {TLMM_GPIO_INPUT, TLMM_GPIO_PULL_DOWN, TLMM_GPIO_8MA} </props>
        <props name="GpioCsConfig" type="TLMMGpioConfigIdType"> {TLMM_GPIO_INPUT, TLMM_GPIO_PULL_DOWN, TLMM_GPIO_8MA} </props>
        <props name="GpioMosiConfig" type="TLMMGpioConfigIdType"> {TLMM_GPIO_INPUT, TLMM_GPIO_PULL_DOWN, TLMM_GPIO_8MA} </props>
        <props name="GpioMisoConfig" type="TLMMGpioConfigIdType"> {TLMM_GPIO_INPUT, TLMM_GPIO_PULL_DOWN, TLMM_GPIO_8MA} </props>
        <props name="CHIP_APP_CLK_NAME" type=DALPROP_ATTR_TYPE_STRING_PTR> spiqup2_appclk_name </props>
        <props name="CHIP_HCLK_NAME" type=DALPROP_ATTR_TYPE_STRING_PTR> spi_blsp1_hclk_name </props>
    </device>
    <device id="/dev/buses/spi_3">
        <props name="QUP_CORE_NUM" type=DALPROP_ATTR_TYPE_UINT32> 3 </props>
        <props name="QUP_BASE_ADDR" type=DALPROP_ATTR_TYPE_UINT32> 0xC177000 </props>
        <props name="SW_ENABLE_BAM" type=DALPROP_ATTR_TYPE_UINT32> 1 </props>
        <props name="BAM_BLSP_ID" type=DALPROP_ATTR_TYPE_UINT32> 1 </props>
        <props name="BAM_BASE_ADDR" type=DALPROP_ATTR_TYPE_UINT32> 0xC144000 </props>
        <props name="BAM_INTERRUPT_ID" type=DALPROP_ATTR_TYPE_UINT32> 270 </props>
        <props name="BAM_TX_PIPE_NUM" type=DALPROP_ATTR_TYPE_UINT32> 8 </props>
        <props name="BAM_RX_PIPE_NUM" type=DALPROP_ATTR_TYPE_UINT32> 9 </props>
        <props name="is_multi_cs" type=DALPROP_ATTR_TYPE_UINT32> 0 </props>
        <props name="gpio_spi_clk_str" type=DALPROP_ATTR_TYPE_STRING_PTR>gpio_spi3_clk_str</props>
        <props name="gpio_spi_cs_str" type=DALPROP_ATTR_TYPE_STRING_PTR>gpio_spi3_cs_str</props>
        <props name="gpio_spi_cs1_str" type=DALPROP_ATTR_TYPE_STRING_PTR>gpio_spi3_cs1_str</props>
        <props name="gpio_spi_cs2_str" type=DALPROP_ATTR_TYPE_STRING_PTR>gpio_spi3_cs2_str</props>
        <props name="gpio_spi_mosi_str" type=DALPROP_ATTR_TYPE_STRING_PTR>gpio_spi3_mosi_str</props>
        <props name="gpio_spi_miso_str" type=DALPROP_ATTR_TYPE_STRING_PTR>gpio_spi3_miso_str</props>
        <props name="GpioClkConfig" type="TLMMGpioConfigIdType"> {TLMM_GPIO_INPUT, TLMM_GPIO_PULL_DOWN, TLMM_GPIO_8MA} </props>
        <props name="GpioCsConfig" type="TLMMGpioConfigIdType"> {TLMM_GPIO_INPUT, TLMM_GPIO_PULL_DOWN, TLMM_GPIO_8MA} </props>
        <props name="GpioCs1Config" type="TLMMGpioConfigIdType"> {TLMM_GPIO_INPUT, TLMM_GPIO_PULL_DOWN, TLMM_GPIO_8MA} </props>
        <props name="GpioCs2Config" type="TLMMGpioConfigIdType"> {TLMM_GPIO_INPUT, TLMM_GPIO_PULL_DOWN, TLMM_GPIO_8MA} </props>
        <props name="GpioMosiConfig" type="TLMMGpioConfigIdType"> {TLMM_GPIO_INPUT, TLMM_GPIO_PULL_DOWN, TLMM_GPIO_8MA} </props>
        <props name="GpioMisoConfig" type="TLMMGpioConfigIdType"> {TLMM_GPIO_INPUT, TLMM_GPIO_PULL_DOWN, TLMM_GPIO_8MA} </props>
        <props name="CHIP_APP_CLK_NAME" type=DALPROP_ATTR_TYPE_STRING_PTR> spiqup3_appclk_name </props>
        <props name="CHIP_HCLK_NAME" type=DALPROP_ATTR_TYPE_STRING_PTR> spi_blsp1_hclk_name </props>
    </device>
    <device id="/dev/buses/spi_4">
        <props name="QUP_CORE_NUM" type=DALPROP_ATTR_TYPE_UINT32> 4 </props>
        <props name="QUP_BASE_ADDR" type=DALPROP_ATTR_TYPE_UINT32> 0xC178000 </props>
        <props name="SW_ENABLE_BAM" type=DALPROP_ATTR_TYPE_UINT32> 1 </props>
        <props name="BAM_BLSP_ID" type=DALPROP_ATTR_TYPE_UINT32> 1 </props>
        <props name="BAM_BASE_ADDR" type=DALPROP_ATTR_TYPE_UINT32> 0xC144000 </props>
        <props name="BAM_INTERRUPT_ID" type=DALPROP_ATTR_TYPE_UINT32> 270 </props>
        <props name="BAM_TX_PIPE_NUM" type=DALPROP_ATTR_TYPE_UINT32> 10 </props>
        <props name="BAM_RX_PIPE_NUM" type=DALPROP_ATTR_TYPE_UINT32> 11 </props>
        <props name="gpio_spi_clk_str" type=DALPROP_ATTR_TYPE_STRING_PTR>gpio_spi4_clk_str</props>
        <props name="gpio_spi_cs_str" type=DALPROP_ATTR_TYPE_STRING_PTR>gpio_spi4_cs_str</props>
        <props name="gpio_spi_mosi_str" type=DALPROP_ATTR_TYPE_STRING_PTR>gpio_spi4_mosi_str</props>
        <props name="gpio_spi_miso_str" type=DALPROP_ATTR_TYPE_STRING_PTR>gpio_spi4_miso_str</props>
        <props name="GpioClkConfig" type="TLMMGpioConfigIdType"> {TLMM_GPIO_INPUT, TLMM_GPIO_PULL_DOWN, TLMM_GPIO_8MA} </props>
        <props name="GpioCsConfig" type="TLMMGpioConfigIdType"> {TLMM_GPIO_INPUT, TLMM_GPIO_PULL_DOWN, TLMM_GPIO_8MA} </props>
        <props name="GpioMosiConfig" type="TLMMGpioConfigIdType"> {TLMM_GPIO_INPUT, TLMM_GPIO_PULL_DOWN, TLMM_GPIO_8MA} </props>
        <props name="GpioMisoConfig" type="TLMMGpioConfigIdType"> {TLMM_GPIO_INPUT, TLMM_GPIO_PULL_DOWN, TLMM_GPIO_8MA} </props>
        <props name="CHIP_APP_CLK_NAME" type=DALPROP_ATTR_TYPE_STRING_PTR> spiqup4_appclk_name </props>
        <props name="CHIP_HCLK_NAME" type=DALPROP_ATTR_TYPE_STRING_PTR> spi_blsp1_hclk_name </props>
    </device>
    <device id="/dev/buses/spi_5">
        <props name="QUP_CORE_NUM" type=DALPROP_ATTR_TYPE_UINT32> 5 </props>
        <props name="QUP_BASE_ADDR" type=DALPROP_ATTR_TYPE_UINT32> 0xC1B5000 </props>
        <props name="SW_ENABLE_BAM" type=DALPROP_ATTR_TYPE_UINT32> 1 </props>
        <props name="BAM_BLSP_ID" type=DALPROP_ATTR_TYPE_UINT32> 2 </props>
        <props name="BAM_BASE_ADDR" type=DALPROP_ATTR_TYPE_UINT32> 0xC184000 </props>
        <props name="BAM_INTERRUPT_ID" type=DALPROP_ATTR_TYPE_UINT32> 271 </props>
        <props name="BAM_TX_PIPE_NUM" type=DALPROP_ATTR_TYPE_UINT32> 4 </props>
        <props name="BAM_RX_PIPE_NUM" type=DALPROP_ATTR_TYPE_UINT32> 5 </props>
        <props name="gpio_spi_clk_str" type=DALPROP_ATTR_TYPE_STRING_PTR>gpio_spi5_clk_str</props>
        <props name="gpio_spi_cs_str" type=DALPROP_ATTR_TYPE_STRING_PTR>gpio_spi5_cs_str</props>
        <props name="gpio_spi_mosi_str" type=DALPROP_ATTR_TYPE_STRING_PTR>gpio_spi5_mosi_str</props>
        <props name="gpio_spi_miso_str" type=DALPROP_ATTR_TYPE_STRING_PTR>gpio_spi5_miso_str</props>
        <props name="GpioClkConfig" type="TLMMGpioConfigIdType"> {TLMM_GPIO_INPUT, TLMM_GPIO_PULL_DOWN, TLMM_GPIO_8MA} </props>
        <props name="GpioCsConfig" type="TLMMGpioConfigIdType"> {TLMM_GPIO_INPUT, TLMM_GPIO_PULL_DOWN, TLMM_GPIO_8MA} </props>
        <props name="GpioMosiConfig" type="TLMMGpioConfigIdType"> {TLMM_GPIO_INPUT, TLMM_GPIO_PULL_DOWN, TLMM_GPIO_8MA} </props>
        <props name="GpioMisoConfig" type="TLMMGpioConfigIdType"> {TLMM_GPIO_INPUT, TLMM_GPIO_PULL_DOWN, TLMM_GPIO_8MA} </props>
        <props name="CHIP_APP_CLK_NAME" type=DALPROP_ATTR_TYPE_STRING_PTR> spiqup5_appclk_name </props>
        <props name="CHIP_HCLK_NAME" type=DALPROP_ATTR_TYPE_STRING_PTR> spi_blsp2_hclk_name </props>
    </device>
    <device id="/dev/buses/spi_6">
        <props name="QUP_CORE_NUM" type=DALPROP_ATTR_TYPE_UINT32> 6 </props>
        <props name="QUP_BASE_ADDR" type=DALPROP_ATTR_TYPE_UINT32> 0xC1B6000 </props>
        <props name="SW_ENABLE_BAM" type=DALPROP_ATTR_TYPE_UINT32> 1 </props>
        <props name="BAM_BLSP_ID" type=DALPROP_ATTR_TYPE_UINT32> 2 </props>
        <props name="BAM_BASE_ADDR" type=DALPROP_ATTR_TYPE_UINT32> 0xC184000 </props>
        <props name="BAM_INTERRUPT_ID" type=DALPROP_ATTR_TYPE_UINT32> 271 </props>
        <props name="BAM_TX_PIPE_NUM" type=DALPROP_ATTR_TYPE_UINT32> 6 </props>
        <props name="BAM_RX_PIPE_NUM" type=DALPROP_ATTR_TYPE_UINT32> 7 </props>
        <props name="gpio_spi_clk_str" type=DALPROP_ATTR_TYPE_STRING_PTR>gpio_spi6_clk_str</props>
        <props name="gpio_spi_cs_str" type=DALPROP_ATTR_TYPE_STRING_PTR>gpio_spi6_cs_str</props>
        <props name="gpio_spi_mosi_str" type=DALPROP_ATTR_TYPE_STRING_PTR>gpio_spi6_mosi_str</props>
        <props name="gpio_spi_miso_str" type=DALPROP_ATTR_TYPE_STRING_PTR>gpio_spi6_miso_str</props>
        <props name="GpioClkConfig" type="TLMMGpioConfigIdType"> {TLMM_GPIO_INPUT, TLMM_GPIO_PULL_DOWN, TLMM_GPIO_8MA} </props>
        <props name="GpioCsConfig" type="TLMMGpioConfigIdType"> {TLMM_GPIO_INPUT, TLMM_GPIO_PULL_DOWN, TLMM_GPIO_8MA} </props>
        <props name="GpioMosiConfig" type="TLMMGpioConfigIdType"> {TLMM_GPIO_INPUT, TLMM_GPIO_PULL_DOWN, TLMM_GPIO_8MA} </props>
        <props name="GpioMisoConfig" type="TLMMGpioConfigIdType"> {TLMM_GPIO_INPUT, TLMM_GPIO_PULL_DOWN, TLMM_GPIO_8MA} </props>
        <props name="CHIP_APP_CLK_NAME" type=DALPROP_ATTR_TYPE_STRING_PTR> spiqup6_appclk_name </props>
        <props name="CHIP_HCLK_NAME" type=DALPROP_ATTR_TYPE_STRING_PTR> spi_blsp2_hclk_name </props>
    </device>
    <device id="/dev/buses/spi_7">
        <props name="QUP_CORE_NUM" type=DALPROP_ATTR_TYPE_UINT32> 7 </props>
        <props name="QUP_BASE_ADDR" type=DALPROP_ATTR_TYPE_UINT32> 0xC1B7000 </props>
        <props name="SW_ENABLE_BAM" type=DALPROP_ATTR_TYPE_UINT32> 1 </props>
        <props name="BAM_BLSP_ID" type=DALPROP_ATTR_TYPE_UINT32> 2 </props>
        <props name="BAM_BASE_ADDR" type=DALPROP_ATTR_TYPE_UINT32> 0xC184000 </props>
        <props name="BAM_INTERRUPT_ID" type=DALPROP_ATTR_TYPE_UINT32> 271 </props>
        <props name="BAM_TX_PIPE_NUM" type=DALPROP_ATTR_TYPE_UINT32> 8 </props>
        <props name="BAM_RX_PIPE_NUM" type=DALPROP_ATTR_TYPE_UINT32> 9 </props>
        <props name="gpio_spi_clk_str" type=DALPROP_ATTR_TYPE_STRING_PTR>gpio_spi7_clk_str</props>
        <props name="gpio_spi_cs_str" type=DALPROP_ATTR_TYPE_STRING_PTR>gpio_spi7_cs_str</props>
        <props name="gpio_spi_mosi_str" type=DALPROP_ATTR_TYPE_STRING_PTR>gpio_spi7_mosi_str</props>
        <props name="gpio_spi_miso_str" type=DALPROP_ATTR_TYPE_STRING_PTR>gpio_spi7_miso_str</props>
        <props name="GpioClkConfig" type="TLMMGpioConfigIdType"> {TLMM_GPIO_INPUT, TLMM_GPIO_PULL_DOWN, TLMM_GPIO_8MA} </props>
        <props name="GpioCsConfig" type="TLMMGpioConfigIdType"> {TLMM_GPIO_INPUT, TLMM_GPIO_PULL_DOWN, TLMM_GPIO_8MA} </props>
        <props name="GpioMosiConfig" type="TLMMGpioConfigIdType"> {TLMM_GPIO_INPUT, TLMM_GPIO_PULL_DOWN, TLMM_GPIO_8MA} </props>
        <props name="GpioMisoConfig" type="TLMMGpioConfigIdType"> {TLMM_GPIO_INPUT, TLMM_GPIO_PULL_DOWN, TLMM_GPIO_8MA} </props>
        <props name="CHIP_APP_CLK_NAME" type=DALPROP_ATTR_TYPE_STRING_PTR> spiqup7_appclk_name </props>
        <props name="CHIP_HCLK_NAME" type=DALPROP_ATTR_TYPE_STRING_PTR> spi_blsp2_hclk_name </props>
    </device>
    <device id="/dev/buses/spi_8">
        <props name="QUP_CORE_NUM" type=DALPROP_ATTR_TYPE_UINT32> 8 </props>
        <props name="QUP_BASE_ADDR" type=DALPROP_ATTR_TYPE_UINT32> 0xC1B8000 </props>
        <props name="SW_ENABLE_BAM" type=DALPROP_ATTR_TYPE_UINT32> 1 </props>
        <props name="BAM_BLSP_ID" type=DALPROP_ATTR_TYPE_UINT32> 2 </props>
        <props name="BAM_BASE_ADDR" type=DALPROP_ATTR_TYPE_UINT32> 0xC184000 </props>
        <props name="BAM_INTERRUPT_ID" type=DALPROP_ATTR_TYPE_UINT32> 271 </props>
        <props name="BAM_TX_PIPE_NUM" type=DALPROP_ATTR_TYPE_UINT32> 10 </props>
        <props name="BAM_RX_PIPE_NUM" type=DALPROP_ATTR_TYPE_UINT32> 11 </props>
        <props name="is_multi_cs" type=DALPROP_ATTR_TYPE_UINT32> 0 </props>
        <props name="gpio_spi_clk_str" type=DALPROP_ATTR_TYPE_STRING_PTR>gpio_spi8_clk_str</props>
        <props name="gpio_spi_cs_str" type=DALPROP_ATTR_TYPE_STRING_PTR>gpio_spi8_cs_str</props>
        <props name="gpio_spi_cs1_str" type=DALPROP_ATTR_TYPE_STRING_PTR>gpio_spi8_cs1_str</props>
        <props name="gpio_spi_cs2_str" type=DALPROP_ATTR_TYPE_STRING_PTR>gpio_spi8_cs2_str</props>
        <props name="gpio_spi_mosi_str" type=DALPROP_ATTR_TYPE_STRING_PTR>gpio_spi8_mosi_str</props>
        <props name="gpio_spi_miso_str" type=DALPROP_ATTR_TYPE_STRING_PTR>gpio_spi8_miso_str</props>
        <props name="GpioClkConfig" type="TLMMGpioConfigIdType"> {TLMM_GPIO_INPUT, TLMM_GPIO_PULL_DOWN, TLMM_GPIO_8MA} </props>
        <props name="GpioCsConfig" type="TLMMGpioConfigIdType"> {TLMM_GPIO_INPUT, TLMM_GPIO_PULL_DOWN, TLMM_GPIO_8MA} </props>
        <props name="GpioCs1Config" type="TLMMGpioConfigIdType"> {TLMM_GPIO_INPUT, TLMM_GPIO_PULL_DOWN, TLMM_GPIO_8MA} </props>
        <props name="GpioCs2Config" type="TLMMGpioConfigIdType"> {TLMM_GPIO_INPUT, TLMM_GPIO_PULL_DOWN, TLMM_GPIO_8MA} </props>
        <props name="GpioMosiConfig" type="TLMMGpioConfigIdType"> {TLMM_GPIO_INPUT, TLMM_GPIO_PULL_DOWN, TLMM_GPIO_8MA} </props>
        <props name="GpioMisoConfig" type="TLMMGpioConfigIdType"> {TLMM_GPIO_INPUT, TLMM_GPIO_PULL_DOWN, TLMM_GPIO_8MA} </props>
        <props name="CHIP_APP_CLK_NAME" type=DALPROP_ATTR_TYPE_STRING_PTR> spiqup8_appclk_name </props>
        <props name="CHIP_HCLK_NAME" type=DALPROP_ATTR_TYPE_STRING_PTR> spi_blsp2_hclk_name </props>
    </device>
    <device id="/dev/buses/spi_sensor_1">
        <props name="QUP_CORE_NUM" type=DALPROP_ATTR_TYPE_UINT32> 1 </props>
        <props name="QUP_BASE_ADDR" type=DALPROP_ATTR_TYPE_UINT32> 0x15435000 </props>
        <props name="SW_ENABLE_BAM" type=DALPROP_ATTR_TYPE_UINT32> 1 </props>
        <props name="BAM_BLSP_ID" type=DALPROP_ATTR_TYPE_UINT32> 1 </props>
        <props name="BAM_BASE_ADDR" type=DALPROP_ATTR_TYPE_UINT32> 0x15404000 </props>
        <props name="BAM_INTERRUPT_ID" type=DALPROP_ATTR_TYPE_UINT32> 182 </props>
        <props name="BAM_TX_PIPE_NUM" type=DALPROP_ATTR_TYPE_UINT32> 8 </props>
        <props name="BAM_RX_PIPE_NUM" type=DALPROP_ATTR_TYPE_UINT32> 9 </props>
    </device>
    <device id="/dev/buses/spi_sensor_2">
        <props name="QUP_CORE_NUM" type=DALPROP_ATTR_TYPE_UINT32> 2 </props>
        <props name="QUP_BASE_ADDR" type=DALPROP_ATTR_TYPE_UINT32> 0x15436000 </props>
        <props name="SW_ENABLE_BAM" type=DALPROP_ATTR_TYPE_UINT32> 1 </props>
        <props name="BAM_BLSP_ID" type=DALPROP_ATTR_TYPE_UINT32> 1 </props>
        <props name="BAM_BASE_ADDR" type=DALPROP_ATTR_TYPE_UINT32> 0x15404000 </props>
        <props name="BAM_INTERRUPT_ID" type=DALPROP_ATTR_TYPE_UINT32> 182 </props>
        <props name="BAM_TX_PIPE_NUM" type=DALPROP_ATTR_TYPE_UINT32> 10 </props>
        <props name="BAM_RX_PIPE_NUM" type=DALPROP_ATTR_TYPE_UINT32> 11 </props>
    </device>
    <device id="/dev/buses/spi_sensor_3">
        <props name="QUP_CORE_NUM" type=DALPROP_ATTR_TYPE_UINT32> 3 </props>
        <props name="QUP_BASE_ADDR" type=DALPROP_ATTR_TYPE_UINT32> 0x15437000 </props>
        <props name="SW_ENABLE_BAM" type=DALPROP_ATTR_TYPE_UINT32> 1 </props>
        <props name="BAM_BLSP_ID" type=DALPROP_ATTR_TYPE_UINT32> 1 </props>
        <props name="BAM_BASE_ADDR" type=DALPROP_ATTR_TYPE_UINT32> 0x15404000 </props>
        <props name="BAM_INTERRUPT_ID" type=DALPROP_ATTR_TYPE_UINT32> 182 </props>
        <props name="BAM_TX_PIPE_NUM" type=DALPROP_ATTR_TYPE_UINT32> 12 </props>
        <props name="BAM_RX_PIPE_NUM" type=DALPROP_ATTR_TYPE_UINT32> 13 </props>
    </device>
</driver>
