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
     <var_seq name = "BLSP_QUP1_BAM_OFFSETS" type=DALPROP_DATA_TYPE_UINT32_SEQ>0xC15B000, 0xC15C000, end </var_seq>
     <var_seq name = "BLSP_QUP2_BAM_OFFSETS" type=DALPROP_DATA_TYPE_UINT32_SEQ>0xC15D000, 0xC15E000, end </var_seq>
     <var_seq name = "BLSP_QUP3_BAM_OFFSETS" type=DALPROP_DATA_TYPE_UINT32_SEQ>0xC15F000, 0xC160000, end </var_seq>
     <var_seq name = "BLSP_QUP4_BAM_OFFSETS" type=DALPROP_DATA_TYPE_UINT32_SEQ>0xC161000, 0xC162000, end </var_seq>
  <var_seq name = "BLSP_QUP5_BAM_OFFSETS" type=DALPROP_DATA_TYPE_UINT32_SEQ>0xC19B000, 0xC19C000, end </var_seq>
     <var_seq name = "BLSP_QUP6_BAM_OFFSETS" type=DALPROP_DATA_TYPE_UINT32_SEQ>0xC19D000, 0xC19E000, end </var_seq>
     <var_seq name = "BLSP_QUP7_BAM_OFFSETS" type=DALPROP_DATA_TYPE_UINT32_SEQ>0xC19F000, 0xC1a0000, end </var_seq>
     <var_seq name = "BLSP_QUP8_BAM_OFFSETS" type=DALPROP_DATA_TYPE_UINT32_SEQ>0xC1a1000, 0xC1a2000, end </var_seq>
     <var_seq name = "BLSP_UART1_BAM_OFFSETS" type=DALPROP_DATA_TYPE_UINT32_SEQ>0xC157000, 0xC158000, end </var_seq>
     <var_seq name = "BLSP_UART2_BAM_OFFSETS" type=DALPROP_DATA_TYPE_UINT32_SEQ>0xC159000, 0xC15A000, end </var_seq>
     <var_seq name = "BLSP_UART3_BAM_OFFSETS" type=DALPROP_DATA_TYPE_UINT32_SEQ>0xC197000, 0xC198000, end </var_seq>
     <var_seq name = "BLSP_UART4_BAM_OFFSETS" type=DALPROP_DATA_TYPE_UINT32_SEQ>0xC199000, 0xC19A000, end </var_seq>
     <var_seq name = "SENSOR_QUP1_BAM_OFFSETS" type=DALPROP_DATA_TYPE_UINT32_SEQ>0x1541F000, 0x15420000, end </var_seq>
     <var_seq name = "SENSOR_QUP2_BAM_OFFSETS" type=DALPROP_DATA_TYPE_UINT32_SEQ>0x15421000, 0x15422000, end </var_seq>
     <var_seq name = "SENSOR_QUP3_BAM_OFFSETS" type=DALPROP_DATA_TYPE_UINT32_SEQ>0x15423000, 0x15424000, end </var_seq>
  <var_seq name = "SENSOR_UART1_BAM_OFFSETS" type=DALPROP_DATA_TYPE_UINT32_SEQ>0x15417000, 0x15418000, end </var_seq>
     <var_seq name = "SENSOR_UART2_BAM_OFFSETS" type=DALPROP_DATA_TYPE_UINT32_SEQ>0x15419000, 0x1541A000, end </var_seq>
     <var_seq name = "SENSOR_UART3_BAM_OFFSETS" type=DALPROP_DATA_TYPE_UINT32_SEQ>0x1541B000, 0x1541C000, end </var_seq>
  <var_seq name = "SENSOR_UART4_BAM_OFFSETS" type=DALPROP_DATA_TYPE_UINT32_SEQ>0x1541D000, 0x1541E000, end </var_seq>
   </global_def>
   <device id="/dev/buses/qup/blsp_qup1_cfg">
      <props name="QUP_OFFSET" type=DALPROP_ATTR_TYPE_UINT32> 0xC175000 </props>
      <props name="BAM_OFFSETS" type=DALPROP_ATTR_TYPE_UINT32_SEQ_PTR> BLSP_QUP1_BAM_OFFSETS </props>
   </device>
   <device id="/dev/buses/uart/blsp_uart1_cfg">
      <props name="UART_OFFSET" type=DALPROP_ATTR_TYPE_UINT32> 0xC16F000 </props>
      <props name="BAM_OFFSETS" type=DALPROP_ATTR_TYPE_UINT32_SEQ_PTR> BLSP_UART1_BAM_OFFSETS </props>
   </device>
   <device id="/dev/buses/qup/blsp_qup2_cfg">
      <props name="QUP_OFFSET" type=DALPROP_ATTR_TYPE_UINT32> 0xC176000 </props>
      <props name="BAM_OFFSETS" type=DALPROP_ATTR_TYPE_UINT32_SEQ_PTR>BLSP_QUP2_BAM_OFFSETS </props>
   </device>
   <device id="/dev/buses/uart/blsp_uart2_cfg">
      <props name="UART_OFFSET" type=DALPROP_ATTR_TYPE_UINT32> 0xC170000 </props>
      <props name="BAM_OFFSETS" type=DALPROP_ATTR_TYPE_UINT32_SEQ_PTR>BLSP_UART2_BAM_OFFSETS</props>
   </device>
   <device id="/dev/buses/qup/blsp_qup3_cfg">
      <props name="QUP_OFFSET" type=DALPROP_ATTR_TYPE_UINT32> 0xC177000 </props>
      <props name="BAM_OFFSETS" type=DALPROP_ATTR_TYPE_UINT32_SEQ_PTR>BLSP_QUP3_BAM_OFFSETS</props>
   </device>
   <device id="/dev/buses/qup/blsp_qup4_cfg">
      <props name="QUP_OFFSET" type=DALPROP_ATTR_TYPE_UINT32> 0xC178000 </props>
      <props name="BAM_OFFSETS" type=DALPROP_ATTR_TYPE_UINT32_SEQ_PTR>BLSP_QUP4_BAM_OFFSETS</props>
   </device>
   <device id="/dev/buses/qup/blsp_qup5_cfg">
     <props name="QUP_OFFSET" type=DALPROP_ATTR_TYPE_UINT32> 0xC1B5000 </props>
     <props name="BAM_OFFSETS" type=DALPROP_ATTR_TYPE_UINT32_SEQ_PTR>BLSP_QUP5_BAM_OFFSETS</props>
   </device>
   <device id="/dev/buses/uart/blsp_uart3_cfg">
      <props name="UART_OFFSET" type=DALPROP_ATTR_TYPE_UINT32> 0xC1AF000 </props>
      <props name="BAM_OFFSETS" type=DALPROP_ATTR_TYPE_UINT32_SEQ_PTR>BLSP_UART3_BAM_OFFSETS</props>
   </device>
   <device id="/dev/buses/qup/blsp_qup6_cfg">
      <props name="QUP_OFFSET" type=DALPROP_ATTR_TYPE_UINT32> 0xC1B6000 </props>
      <props name="BAM_OFFSETS" type=DALPROP_ATTR_TYPE_UINT32_SEQ_PTR>BLSP_QUP6_BAM_OFFSETS</props>
   </device>
   <device id="/dev/buses/uart/blsp_uart4_cfg">
      <props name="UART_OFFSET" type=DALPROP_ATTR_TYPE_UINT32> 0xC1B0000 </props>
      <props name="BAM_OFFSETS" type=DALPROP_ATTR_TYPE_UINT32_SEQ_PTR>BLSP_UART4_BAM_OFFSETS</props>
   </device>
   <device id="/dev/buses/qup/blsp_qup7_cfg">
      <props name="QUP_OFFSET" type=DALPROP_ATTR_TYPE_UINT32> 0xC1B7000 </props>
      <props name="BAM_OFFSETS" type=DALPROP_ATTR_TYPE_UINT32_SEQ_PTR>BLSP_QUP7_BAM_OFFSETS</props>
   </device>
   <device id="/dev/buses/qup/blsp_qup8_cfg">
      <props name="QUP_OFFSET" type=DALPROP_ATTR_TYPE_UINT32> 0xC1B8000 </props>
      <props name="BAM_OFFSETS" type=DALPROP_ATTR_TYPE_UINT32_SEQ_PTR>BLSP_QUP8_BAM_OFFSETS</props>
   </device>
   <device id="/dev/buses/qup/sensor_qup1_cfg">
      <props name="QUP_OFFSET" type=DALPROP_ATTR_TYPE_UINT32> 0x15435000 </props>
      <props name="BAM_OFFSETS" type=DALPROP_ATTR_TYPE_UINT32_SEQ_PTR>SENSOR_QUP1_BAM_OFFSETS</props>
   </device>
   <device id="/dev/buses/uart/sensor_uart1_cfg">
      <props name="UART_OFFSET" type=DALPROP_ATTR_TYPE_UINT32> 0x1542F000 </props>
      <props name="BAM_OFFSETS" type=DALPROP_ATTR_TYPE_UINT32_SEQ_PTR>SENSOR_UART1_BAM_OFFSETS</props>
   </device>
   <device id="/dev/buses/qup/sensor_qup2_cfg">
      <props name="QUP_OFFSET" type=DALPROP_ATTR_TYPE_UINT32> 0x15436000 </props>
      <props name="BAM_OFFSETS" type=DALPROP_ATTR_TYPE_UINT32_SEQ_PTR>SENSOR_QUP2_BAM_OFFSETS</props>
   </device>
   <device id="/dev/buses/uart/sensor_uart2_cfg">
      <props name="UART_OFFSET" type=DALPROP_ATTR_TYPE_UINT32> 0x15430000 </props>
      <props name="BAM_OFFSETS" type=DALPROP_ATTR_TYPE_UINT32_SEQ_PTR>SENSOR_UART2_BAM_OFFSETS</props>
   </device>
   <device id="/dev/buses/qup/sensor_qup3_cfg">
      <props name="QUP_OFFSET" type=DALPROP_ATTR_TYPE_UINT32> 0x15437000 </props>
      <props name="BAM_OFFSETS" type=DALPROP_ATTR_TYPE_UINT32_SEQ_PTR>SENSOR_QUP3_BAM_OFFSETS</props>
   </device>
   <device id="/dev/buses/uart/sensor_uart3_cfg">
      <props name="UART_OFFSET" type=DALPROP_ATTR_TYPE_UINT32> 0x15431000 </props>
      <props name="BAM_OFFSETS" type=DALPROP_ATTR_TYPE_UINT32_SEQ_PTR>SENSOR_UART3_BAM_OFFSETS</props>
   </device>
   <device id="/dev/buses/uart/sensor_uart4_cfg">
      <props name="UART_OFFSET" type=DALPROP_ATTR_TYPE_UINT32> 0x15432000 </props>
      <props name="BAM_OFFSETS" type=DALPROP_ATTR_TYPE_UINT32_SEQ_PTR>SENSOR_UART4_BAM_OFFSETS</props>
   </device>
</driver>
