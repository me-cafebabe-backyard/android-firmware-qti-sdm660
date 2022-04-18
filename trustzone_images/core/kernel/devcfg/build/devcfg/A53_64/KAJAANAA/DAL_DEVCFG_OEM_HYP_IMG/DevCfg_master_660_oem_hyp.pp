# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/kernel/devcfg/build/devcfg/A53_64/KAJAANAA/DAL_DEVCFG_OEM_HYP_IMG/DevCfg_master_660_oem_hyp.xml"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 334 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/kernel/devcfg/build/devcfg/A53_64/KAJAANAA/DAL_DEVCFG_OEM_HYP_IMG/DevCfg_master_660_oem_hyp.xml" 2
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/api/dal/DALPropDef.h" 1
# 2 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/kernel/devcfg/build/devcfg/A53_64/KAJAANAA/DAL_DEVCFG_OEM_HYP_IMG/DevCfg_master_660_oem_hyp.xml" 2
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/api/dal/DALDeviceId.h" 1
# 3 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/kernel/devcfg/build/devcfg/A53_64/KAJAANAA/DAL_DEVCFG_OEM_HYP_IMG/DevCfg_master_660_oem_hyp.xml" 2
<?xml version="1.0"?>
<dal>
<module name="devcfg">
enum_header_path "QupACCommonIds.h"
enum_header_path "comdef.h"
enum_header_path "com_dtypes.h"
enum_header_path "target.h"
enum_header_path "customer.h"
enum_header_path "custkajaanaaa.h"
enum_header_path "targkajaanaaa.h"
enum_header_path "custremoteapis.h"
enum_header_path "custtarget.h"
enum_header_path "custsdcc.h"
enum_header_path "custsurf.h"
enum_header_path "custdiag.h"
enum_header_path "custefs.h"
enum_header_path "custpmic.h"
enum_header_path "custsio_8660.h"
enum_header_path "custsec.h"
enum_header_path "custsfs.h"
enum_header_path "armasm.h"
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
typedef enum {
   PERIPH_ENUM_MIN = 0,
   BLSP_QUPID_START = PERIPH_ENUM_MIN,
   BLSP_QUP1 = BLSP_QUPID_START,
   BLSP_QUP2,
   BLSP_QUP3,
   BLSP_QUP4,
   BLSP_QUP5,
   BLSP_QUP6,
   BLSP_QUP7,
   BLSP_QUP8,
   BLSP_QUP9,
   BLSP_QUP10,
   BLSP_QUP11,
   BLSP_QUP12,
   SENSOR_QUPID_START,
   SENSOR_QUP1 = SENSOR_QUPID_START,
   SENSOR_QUP2,
   SENSOR_QUP3,
   SENSOR_QUP4,
   SENSOR_QUP5,
   SENSOR_QUP6,
   BLSP_UARTID_START,
   BLSP_UART1 = BLSP_UARTID_START,
   BLSP_UART2,
   BLSP_UART3,
   BLSP_UART4,
   BLSP_UART5,
   BLSP_UART6,
   BLSP_UART7,
   BLSP_UART8,
   BLSP_UART9,
   BLSP_UART10,
   BLSP_UART11,
   BLSP_UART12,
   SENSOR_UARTID_START,
   SENSOR_UART1 = SENSOR_UARTID_START,
   SENSOR_UART2,
   SENSOR_UART3,
   SENSOR_UART4,
   SENSOR_UART5,
   SENSOR_UART6,
   PERIPH_MAX_ID
} BLSP_PERIPHID;
typedef enum {
   PERIPH_BLSP1 = 1,
   PERIPH_BLSP2 = 2,
   SENSOR_BLSP = 3
}QUPAC_BLSPID;
<driver name="NULL">
   <global_def>
      <var_seq name = "SENSOR_QUP1_GPIO_ADDR" type=0x00000003> 0x15075000, 0x15075010, 0x15075020, 0x15075030, end </var_seq>
      <var_seq name = "SENSOR_UART1_GPIO_ADDR" type=0x00000003> 0x15076000, 0x15076010, end </var_seq>
      <var_seq name = "SENSOR_QUP2_GPIO_ADDR" type=0x00000003> 0x15073000, 0x15073010, 0x15074000, 0x15074010, end </var_seq>
      <var_seq name = "SENSOR_UART2_GPIO_ADDR" type=0x00000003> 0x15077000, 0x15077010, end </var_seq>
      <var_seq name = "SENSOR_QUP3_GPIO_ADDR" type=0x00000003> 0x15076000, 0x15076010, 0x15077000, 0x15077010, end </var_seq>
      <var_seq name = "SENSOR_UART3_GPIO_ADDR" type=0x00000003> 0x15074000, 0x15074010, end </var_seq>
      <var_seq name = "SENSOR_UART4_GPIO_ADDR" type=0x00000003> 0x15075040, 0x15075050, end </var_seq>
   </global_def>
   <device id="/dev/buses/qup/blsp_qup1">
      <props name="PERIPH ID" type=0x00000002> BLSP_QUP1 </props>
   <props name="GPIO range" type=0x00000008> 0, 1, 2, 3, end </props>
   <props name="IS_GPIO_PROTECTED" type=0x00000002> 1 </props>
      <props name="RW_ACCESS_LIST" type=0x00000008> 1, end </props>
      <props name="IS_PERSISTENT" type=0x00000002> 0 </props>
   </device>
   <device id="/dev/buses/uart/blsp_uart1">
      <props name="PERIPH ID" type=0x00000002> BLSP_UART1 </props>
      <props name="GPIO range" type=0x00000008> 0, 1, 2, 3, end </props>
      <props name="IS_GPIO_PROTECTED" type=0x00000002> 1 </props>
      <props name="RW_ACCESS_LIST" type=0x00000008> 0xFF, end </props>
      <props name="IS_PERSISTENT" type=0x00000002> 0 </props>
   </device>
   <device id="/dev/buses/qup/blsp_qup2">
      <props name="PERIPH ID" type=0x00000002> BLSP_QUP2 </props>
      <props name="GPIO range" type=0x00000008> 6, 7, end </props>
      <props name="IS_GPIO_PROTECTED" type=0x00000002> 1 </props>
      <props name="RW_ACCESS_LIST" type=0x00000008> 3, end </props>
      <props name="IS_PERSISTENT" type=0x00000002> 0 </props>
   </device>
   <device id="/dev/buses/uart/blsp_uart2">
      <props name="PERIPH ID" type=0x00000002> BLSP_UART2 </props>
      <props name="GPIO range" type=0x00000008> 4, 5, end </props>
      <props name="IS_GPIO_PROTECTED" type=0x00000002> 1 </props>
      <props name="RW_ACCESS_LIST" type=0x00000008> 3, end </props>
      <props name="IS_PERSISTENT" type=0x00000002> 0 </props>
   </device>
   <device id="/dev/buses/qup/blsp_qup3">
      <props name="PERIPH ID" type=0x00000002> BLSP_QUP3 </props>
      <props name="GPIO range" type=0x00000008> 8, 9, 10, 11, end </props>
   <props name="IS_GPIO_PROTECTED" type=0x00000002> 1 </props>
      <props name="RW_ACCESS_LIST" type=0x00000008> 1, end </props>
      <props name="IS_PERSISTENT" type=0x00000002> 0 </props>
   </device>
   <device id="/dev/buses/qup/blsp_qup4">
      <props name="PERIPH ID" type=0x00000002> BLSP_QUP4 </props>
      <props name="GPIO range" type=0x00000008> 14, 15, end </props>
      <props name="IS_GPIO_PROTECTED" type=0x00000002> 1 </props>
      <props name="RW_ACCESS_LIST" type=0x00000008> 3, end </props>
      <props name="IS_PERSISTENT" type=0x00000002> 0 </props>
   </device>
   <device id="/dev/buses/qup/blsp_qup5">
      <props name="PERIPH ID" type=0x00000002> BLSP_QUP5 </props>
      <props name="GPIO range" type=0x00000008> 16, 17, 18, 19, end </props>
      <props name="IS_GPIO_PROTECTED" type=0x00000002> 1 </props>
      <props name="RW_ACCESS_LIST" type=0x00000008> 0xFF, end </props>
      <props name="IS_PERSISTENT" type=0x00000002> 0 </props>
   </device>
   <device id="/dev/buses/uart/blsp_uart3">
      <props name="PERIPH ID" type=0x00000002> BLSP_UART3 </props>
      <props name="GPIO range" type=0x00000008> 16, 17, 18, 19, end </props>
      <props name="IS_GPIO_PROTECTED" type=0x00000002> 1 </props>
      <props name="RW_ACCESS_LIST" type=0x00000008> 3, end </props>
      <props name="IS_PERSISTENT" type=0x00000002> 0 </props>
   </device>
   <device id="/dev/buses/qup/blsp_qup6">
      <props name="PERIPH ID" type=0x00000002> BLSP_QUP6 </props>
      <props name="GPIO range" type=0x00000008> 22, 23, end </props>
   <props name="IS_GPIO_PROTECTED" type=0x00000002> 1 </props>
      <props name="RW_ACCESS_LIST" type=0x00000008> 3, end </props>
      <props name="IS_PERSISTENT" type=0x00000002> 0 </props>
   </device>
   <device id="/dev/buses/uart/blsp_uart4">
      <props name="PERIPH ID" type=0x00000002> BLSP_UART4 </props>
      <props name="GPIO range" type=0x00000008> 24, 25, 26, 27, end </props>
      <props name="IS_GPIO_PROTECTED" type=0x00000002> 1 </props>
      <props name="RW_ACCESS_LIST" type=0x00000008> 0xFF, end </props>
      <props name="IS_PERSISTENT" type=0x00000002> 0 </props>
   </device>
   <device id="/dev/buses/qup/blsp_qup7">
      <props name="PERIPH ID" type=0x00000002> BLSP_QUP7 </props>
      <props name="GPIO range" type=0x00000008> 24, 25, 26, 27, end </props>
      <props name="IS_GPIO_PROTECTED" type=0x00000002> 1 </props>
      <props name="RW_ACCESS_LIST" type=0x00000008> 3, end </props>
      <props name="IS_PERSISTENT" type=0x00000002> 0 </props>
   </device>
   <device id="/dev/buses/qup/blsp_qup8">
      <props name="PERIPH ID" type=0x00000002> BLSP_QUP8 </props>
      <props name="GPIO range" type=0x00000008> 28, 29, 30, 31, end </props>
      <props name="IS_GPIO_PROTECTED" type=0x00000002> 1 </props>
      <props name="RW_ACCESS_LIST" type=0x00000008> 0xFF, end </props>
      <props name="IS_PERSISTENT" type=0x00000002> 0 </props>
   </device>
   <device id="/dev/buses/qup/sensor_qup1">
      <props name="PERIPH ID" type=0x00000002> SENSOR_QUP1 </props>
      <props name="GPIO_ADDR" type=0x00000014> SENSOR_QUP1_GPIO_ADDR </props>
      <props name="SENSOR_Q6_MPU_RG_INDEX" type=0x00000008> end </props>
      <props name="SENSOR_CFG_MPU_RG_INDEX" type=0x00000008> end </props>
      <props name="IS_GPIO_PROTECTED" type=0x00000002> 0 </props>
      <props name="RW_ACCESS_LIST" type=0x00000008> 22, end </props>
      <props name="IS_PERSISTENT" type=0x00000002> 0 </props>
   </device>
   <device id="/dev/buses/uart/sensor_uart1">
      <props name="PERIPH ID" type=0x00000002> SENSOR_UART1 </props>
      <props name="GPIO_ADDR" type=0x00000014> SENSOR_UART1_GPIO_ADDR </props>
      <props name="SENSOR_Q6_MPU_RG_INDEX" type=0x00000008> end </props>
      <props name="SENSOR_CFG_MPU_RG_INDEX" type=0x00000008> end </props>
      <props name="IS_GPIO_PROTECTED" type=0x00000002> 0 </props>
      <props name="RW_ACCESS_LIST" type=0x00000008> 22, end </props>
      <props name="IS_PERSISTENT" type=0x00000002> 0 </props>
   </device>
   <device id="/dev/buses/qup/sensor_qup2">
      <props name="PERIPH ID" type=0x00000002> SENSOR_QUP2 </props>
      <props name="GPIO_ADDR" type=0x00000014> SENSOR_QUP2_GPIO_ADDR </props>
      <props name="SENSOR_Q6_MPU_RG_INDEX" type=0x00000008> end </props>
      <props name="SENSOR_CFG_MPU_RG_INDEX" type=0x00000008> end </props>
      <props name="IS_GPIO_PROTECTED" type=0x00000002> 0 </props>
      <props name="RW_ACCESS_LIST" type=0x00000008> 22, end </props>
      <props name="IS_PERSISTENT" type=0x00000002> 0 </props>
   </device>
   <device id="/dev/buses/uart/sensor_uart2">
      <props name="PERIPH ID" type=0x00000002> SENSOR_UART2 </props>
      <props name="GPIO_ADDR" type=0x00000014> SENSOR_UART2_GPIO_ADDR </props>
      <props name="SENSOR_Q6_MPU_RG_INDEX" type=0x00000008> end </props>
      <props name="SENSOR_CFG_MPU_RG_INDEX" type=0x00000008> end </props>
      <props name="IS_GPIO_PROTECTED" type=0x00000002> 0 </props>
      <props name="RW_ACCESS_LIST" type=0x00000008> 22, end </props>
      <props name="IS_PERSISTENT" type=0x00000002> 0 </props>
   </device>
   <device id="/dev/buses/qup/sensor_qup3">
      <props name="PERIPH ID" type=0x00000002> SENSOR_QUP3 </props>
      <props name="GPIO_ADDR" type=0x00000014> SENSOR_QUP3_GPIO_ADDR </props>
      <props name="SENSOR_Q6_MPU_RG_INDEX" type=0x00000008> end </props>
      <props name="SENSOR_CFG_MPU_RG_INDEX" type=0x00000008> end </props>
      <props name="IS_GPIO_PROTECTED" type=0x00000002> 0 </props>
      <props name="RW_ACCESS_LIST" type=0x00000008> 22, end </props>
      <props name="IS_PERSISTENT" type=0x00000002> 0 </props>
   </device>
   <device id="/dev/buses/uart/sensor_uart3">
      <props name="PERIPH ID" type=0x00000002> SENSOR_UART3 </props>
      <props name="GPIO_ADDR" type=0x00000014> SENSOR_UART3_GPIO_ADDR </props>
      <props name="SENSOR_Q6_MPU_RG_INDEX" type=0x00000008> end </props>
      <props name="SENSOR_CFG_MPU_RG_INDEX" type=0x00000008> end </props>
      <props name="IS_GPIO_PROTECTED" type=0x00000002> 0 </props>
      <props name="RW_ACCESS_LIST" type=0x00000008> 22, end </props>
      <props name="IS_PERSISTENT" type=0x00000002> 0 </props>
   </device>
   <device id="/dev/buses/uart/sensor_uart4">
      <props name="PERIPH ID" type=0x00000002> SENSOR_UART4 </props>
      <props name="GPIO_ADDR" type=0x00000014> SENSOR_UART4_GPIO_ADDR </props>
      <props name="SENSOR_Q6_MPU_RG_INDEX" type=0x00000008> end </props>
      <props name="SENSOR_CFG_MPU_RG_INDEX" type=0x00000008> end </props>
      <props name="IS_GPIO_PROTECTED" type=0x00000002> 0 </props>
      <props name="RW_ACCESS_LIST" type=0x00000008> 22, end </props>
      <props name="IS_PERSISTENT" type=0x00000002> 0 </props>
   </device>
</driver>

<driver name="NULL">
 <global_def>
 </global_def>
 <device id="/ac/smmu">
  <props name="disable_smmu_ac" type=0x00000002>
   0
  </props>
 </device>
</driver>

<driver name="NULL">
   <device id="/pmic/hyp/cfg">
      <props name="spmi_channel_cfg" type=0x00000012>
        pm_hyp_spmi_cfg
      </props>
      <props name="spmi_channel_cfg_size" type=0x00000012>
         pm_hyp_spmi_cfg_sz
      </props>
   </device>
</driver>

</module>
</dal>
