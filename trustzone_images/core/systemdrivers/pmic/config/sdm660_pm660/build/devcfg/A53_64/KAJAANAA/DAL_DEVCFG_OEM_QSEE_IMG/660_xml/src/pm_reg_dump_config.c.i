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
typedef enum
{
  PM_PERIPH_TYPE_LDO,
  PM_PERIPH_TYPE_SMPS,
  PM_PERIPH_TYPE_FULL_PERI_REG,
  PM_PERIPH_TYPE_SINGLE_REG,
  PM_PERIPH_TYPE_INVALID,
} pm_periph_type;
typedef struct
{
  uint32 slave_id;
  uint32 base_addr;
  pm_periph_type periph;
} pm_reg_dump_list_type;
const pm_reg_dump_list_type pm_reg_dump_list[] =
{
   {0x3, 0x1A00, PM_PERIPH_TYPE_SMPS},
   {0x3, 0x1C00, PM_PERIPH_TYPE_SMPS},
   {0x3, 0x2000, PM_PERIPH_TYPE_SMPS},
   {0x3, 0x2200, PM_PERIPH_TYPE_SMPS},
   {0x3, 0x1400, PM_PERIPH_TYPE_SMPS},
   {0x3, 0x1600, PM_PERIPH_TYPE_SMPS},
   {0x1, 0x1D00, PM_PERIPH_TYPE_SMPS},
   {0x1, 0x4C00, PM_PERIPH_TYPE_SMPS},
   {0x1, 0x2649, PM_PERIPH_TYPE_SINGLE_REG},
   {0x1, 0x264F, PM_PERIPH_TYPE_SINGLE_REG},
   {0xf, 0xffff, PM_PERIPH_TYPE_INVALID}
};
