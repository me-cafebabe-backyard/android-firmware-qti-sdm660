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
typedef struct
{
    char* name;
    void* base_addr;
    uintptr_t intr_vector;
    uint32 errlog_filter;
    void* sb_base_addr;
}NOCERR_info_type;
typedef struct
{
    char* name;
    uint8 intr_enable;
    uint8 error_fatal;
    uint32 sb_enable_mask;
}NOCERR_info_type_oem;
typedef struct
{
    uint8 len;
    const NOCERR_info_type* NOCInfo;
    const char *const *BIMC_reg_names;
    const uint64 *BIMC_reg_addr;
    uint8 BIMC_num_reg;
    const uint64 *clock_reg_addr;
    uint8 clock_num_reg;
}NOCERR_propdata_type;
typedef struct
{
    uint8 len;
    const NOCERR_info_type_oem* NOCInfoOEM;
}NOCERR_propdata_type_oem;
typedef struct
{
    char* name;
    uint32 ERRLOG0;
    uint32 ERRLOG1;
    uint32 ERRLOG2;
    uint32 ERRLOG3;
    uint32 ERRLOG4;
    uint32 ERRLOG5;
    uint32 ERRLOG6;
    uint32 FLAGINSTATUS0;
    uint32 SENSEIN0;
}NOCERR_syndrome_type;
void NOC_Error_Init(void);
const NOCERR_info_type_oem NOCERR_cfgdata_oem[] =
{
  { "CNOC", 1, 1, 0x0000000F, },
  { "SNOC", 1, 1, 0x0000003F, },
  { "MNOC", 1, 1, 0x00000003, },
  { "A2_NOC_AGGRE2_NOC", 1, 1, 0x00000001, },
};
const NOCERR_propdata_type_oem NOCERR_propdata_oem =
{
    sizeof(NOCERR_cfgdata_oem)/sizeof(NOCERR_info_type_oem),
    NOCERR_cfgdata_oem,
};
