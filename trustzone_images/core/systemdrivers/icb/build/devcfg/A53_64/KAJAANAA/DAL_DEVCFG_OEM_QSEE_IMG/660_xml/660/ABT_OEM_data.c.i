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
    uint8 slave_id;
    void* base_addr;
    char* clk_name;
    uint8 local;
    uint8 shared;
}ABT_slave_info_type;
typedef struct
{
    char* name;
    uint8 slave_enable;
    uint8 intr_enable;
    uint8 timeout_val;
}ABT_slave_info_type_oem;
typedef struct
{
    char* name;
    const void *const *intr_map_addr;
    const void *const *intr_status_addr;
    void* globa_en_addr;
    uint32 intr_vector;
    uint32 intr_priority;
    uint32 num_status_reg;
    void* local_global_en_addr;
    uint32 local_global_mask;
}ABT_platform_info_type;
typedef struct
{
    uint8 len;
    const ABT_slave_info_type* slave_info;
    const ABT_platform_info_type *platform_info;
}ABT_propdata_type;
typedef struct
{
    uint8 len;
    const ABT_slave_info_type_oem* slave_info_oem;
    uint8 local_global_enable;
}ABT_propdata_type_oem;
typedef enum
{
  ABT_SUCCESS = 0,
  ABT_ERROR_INVALID_PARAM,
  ABT_ERROR_INIT_FAILURE,
  ABT_ERROR_SIZE = 0x7FFFFFFF,
  ABT_ERROR = -1
}ABT_error_type;
void ABT_Init(void);
const ABT_slave_info_type_oem ABT_cfgdata_oem[] =
{
  { "CNOC_0_CENTER_LEFT", 1, 1, 0xFF, },
  { "CNOC_0_CENTER_RIGHT", 1, 1, 0xFF, },
  { "CNOC_0_NORTH", 1, 1, 0xFF, },
  { "CNOC_0_SOUTH", 1, 1, 0xFF, },
  { "CNOC_1_CENTER_LEFT", 1, 1, 0xFF, },
  { "CNOC_1_CENTER_RIGHT", 1, 1, 0xFF, },
  { "CNOC_1_NORTH", 1, 1, 0xFF, },
  { "CNOC_2_CENTER_RIGHT", 1, 1, 0xFF, },
  { "CNOC_2_NORTH", 1, 1, 0xFF, },
  { "CNOC_3_CENTER_RIGHT", 1, 1, 0xFF, },
  { "CNOC_4_CENTER_RIGHT", 1, 1, 0xFF, },
  { "CNOC_5_CENTER_RIGHT", 1, 1, 0xFF, },
  { "CNOC_MM", 1, 1, 0xFF, },
  { "CNOC_USB2", 1, 1, 0xFF, },
  { "CNOC_USB3", 1, 1, 0xFF, },
  { "SNOC_1", 1, 1, 0xFF, },
  { "SNOC_2", 1, 1, 0xFF, },
  { "SNOC_3", 1, 1, 0xFF, },
  { "SNOC_4", 1, 1, 0xFF, },
  { "MMSS_0", 1, 1, 0xFF, },
  { "MMSS_1", 1, 1, 0xFF, },
  { "MMSS_2", 1, 1, 0xFF, },
  { "MMSS_3", 1, 1, 0xFF, },
};
const ABT_propdata_type_oem ABT_propdata_oem =
{
    sizeof(ABT_cfgdata_oem)/sizeof(ABT_slave_info_type_oem),
    ABT_cfgdata_oem,
    1
};
