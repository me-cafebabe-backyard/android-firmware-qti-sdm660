/*==================================================================================================

FILE: quadspi.c

DESCRIPTION: driver for the Atheros-based QSPI (quad SPI) first used in 8996 v2.1

                       Copyright (c) 2015 - 2016 Qualcomm Technologies, Incorporated
                                        All Rights Reserved
                                     QUALCOMM Proprietary/GTDR

==================================================================================================*/
/*==================================================================================================
                                            DESCRIPTION
====================================================================================================

GLOBAL FUNCTIONS:
   quadspi_cmd
   quadspi_deinit
   quadspi_init
   quadspi_read
   quadspi_write

==================================================================================================*/
/*==================================================================================================
                                           INCLUDE FILES
==================================================================================================*/

#include <api/systemdrivers/ClockBoot.h>  // Clock_SetQSPIFrequency()
#include <DDITlmm.h>                      // Tlmm_ConfigGpioGroup()
#include <Library/PrintLib.h>             // AsciiVSPrint()
#include <Library/SerialPortLib.h>        // SerialPortWrite()

#include "qspi_hwio.h"
#include "quadspi.h"

/*==================================================================================================
                                             CONSTANTS
==================================================================================================*/

#define LOG_TO_UART 0  // TRUE to enable real-time logging over the UART
#define LOG_TO_RAM  0  // TRUE to enable logging to a circular buffer in DDR RAM
#define LOG_REG     0  // TRUE to log all register reads/writes

// GPIO's 

#define QSPI_DATA_0     33
#define QSPI_DATA_1     34
#define QSPI_DATA_2     35
#define QSPI_DATA_3     51
#define QSPI_CLK        47
#define QSPI_CS_N_0     43

// GPIO's Function Config

#define QSPI_DATA_0_FUNC_CONFIG     2
#define QSPI_DATA_1_FUNC_CONFIG     2
#define QSPI_DATA_2_FUNC_CONFIG     2
#define QSPI_DATA_3_FUNC_CONFIG     1
#define QSPI_CLK_FUNC_CONFIG        1
#define QSPI_CS_N_0_FUNC_CONFIG     3

/*==================================================================================================
                                               MACROS
==================================================================================================*/

#define REG_IN(reg, value_ptr) \
   *(value_ptr) = *(volatile uint32_t *)(reg); \
   if (LOG_REG) { log("REG_IN:  %21a = 0x%08X\n", #reg, *(value_ptr)); }

#define REG_OUT(reg, value) \
   if (LOG_REG) { log("REG_OUT: %21a = 0x%08X\n", #reg, (value)); } \
   *(volatile uint32_t *)(reg) = (value);

#define INT_TO_PTR(x) (void *)(uintptr_t)(x)

/*==================================================================================================
                                              TYPEDEFS
==================================================================================================*/

// descriptor offset  0 = data address[ 7: 0]
// descriptor offset  1 = data address[15: 8]
// descriptor offset  2 = data address[23:16]
// descriptor offset  3 = data address[31:24]
// descriptor offset  4 = next descriptor[ 7: 0]
// descriptor offset  5 = next descriptor[15: 8]
// descriptor offset  6 = next descriptor[23:16]
// descriptor offset  7 = next descriptor[31:24]
// descriptor offset  8 = mode/dir
// descriptor offset  9 = fragment
// descriptor offset 10 = transfer length[ 7:0]
// descriptor offset 11 = transfer length[15:8]

typedef struct
{
   uint32_t  data_address;
   uint32_t  next_descriptor;
   uint32_t  direction:1;
   uint32_t  multi_io_mode:3;
   uint32_t  reserved1:4;
   uint32_t  fragment:1;
   uint32_t  reserved2:7;
   uint32_t  length:16;
   //------------------------//
   uint32_t  bounce_src;
   uint32_t  bounce_dst;
   uint32_t  bounce_length;
   uint32_t  padding[2];  // force 32-byte alignment between descriptors in array
} DESCRIPTOR;

typedef enum
{
   MASTER_READ = 0,
   MASTER_WRITE = 1,
} BUS_XFER_DIRECTION;

/*==================================================================================================
                                          LOCAL VARIABLES
==================================================================================================*/

#if LOG_TO_RAM
#define LOG_SIZE 64 * 1024 * 3
static char log_buffer[LOG_SIZE] SECTION(".bss.BOOT_DDR_ZI_DATA_ZONE");
static uint32_t log_index = 0;
static uint32_t log_end = 0;
#endif

// The DMA descriptors and DMA buffer must be uncached, 32-byte aligned, and a multiple
// of 4-bytes in length.  They must also be accessible to external AHB masters.  OCIMEM
// and DDR are accessible but TCM is not (TCM is L2 cache that is repurposed as tightly
// coupled memory).  The stack and file scope variables use TCM in the XBL loader.
//
// see QcomPkg/Msm8996Pkg/Library/XBLLoaderLib/sbl1.ld for available memory zones
// see QcomPkg/Msm8996Pkg/Include/Target_cust.h        for base addresses and sizes

static DESCRIPTOR dma_descriptors[8] ALIGN(32) SECTION(".bss.BOOT_OCIMEM_PAGE_TABLE_ZONE");
static uint8_t    dma_buffer[32*4]   ALIGN(32) SECTION(".bss.BOOT_OCIMEM_PAGE_TABLE_ZONE");

static DESCRIPTOR *dma_chain = NULL;
static uint8_t *dma_free_ptr = dma_buffer;
static bool dma_enabled = false;

/*==================================================================================================
                                     LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

static DESCRIPTOR *allocate_descriptor(uint32_t bytes_needed, bool dma_mode);
static uint32_t    available_room(DESCRIPTOR *last);
static bool        configure_clocks(QSPI_MASTER_CONFIG *cfg);
static void        configure_dma_mode(bool enable_dma);
static bool        configure_gpios(void);
static void        dma_transfer_chain(DESCRIPTOR *chain);
static void        dump_chain(void);
static void        dump_log(void);
static void        flush_chain(bool dma_mode);
static DESCRIPTOR *get_last_descriptor(void);
static void        log(const char *fmt, ...);
static void        pio_read(uint8_t *buffer, uint32_t num_bytes, uint32_t pio_transfer_config);
static void        pio_transfer_chain(DESCRIPTOR *chain);
static void        pio_write(uint8_t *buffer, uint32_t num_bytes, uint32_t pio_transfer_config);
static void        queue_addr(uint32_t addr, uint8_t addr_bytes,
                              QSPI_MODE addr_mode, bool dma_mode);
static void        queue_bounce_data(uint8_t *data, uint32_t data_bytes,
                                     QSPI_MODE data_mode, bool write, bool dma_mode);
static void        queue_data(uint8_t *data, uint32_t data_bytes,
                              QSPI_MODE data_mode, bool write, bool dma_mode);
static void        queue_direct_data(uint8_t *data, uint32_t data_bytes,
                                     QSPI_MODE data_mode, bool write, bool dma_mode);
static void        queue_dummy(uint8_t dummy_clocks, bool dma_mode);
static void        queue_opcode(uint8_t opcode, QSPI_MODE cmd_mode, bool dma_mode);
static void        reg_init(QSPI_MASTER_CONFIG *cfg);
static uint32_t    service_rx_fifo(uint8_t *ptr, uint32_t num_bytes);
static uint32_t    service_tx_fifo(uint8_t *ptr, uint32_t num_bytes);

/*==================================================================================================
                                          LOCAL FUNCTIONS
==================================================================================================*/
/*==================================================================================================

FUNCTION: allocate_descriptor

DESCRIPTION:
   This function allocates a new descriptor, adds it to the chain, and returns a pointer to the
   new descriptor.  If no descriptors are available or there is not enough free space in the DMA
   buffer then the existing chain will be flushed to HW and a new chain will be created.

   We assume bytes_needed <= sizeof(dma_buffer).  We also assume that dma_buffer ends on a
   32-byte boundary (if not, the free_ptr calculation below can fail).

==================================================================================================*/
static DESCRIPTOR *allocate_descriptor(uint32_t bytes_needed, bool dma_mode)
{
   uint32_t alignment;
   uint8_t *free_ptr;
   uint32_t room;
   DESCRIPTOR *current;
   DESCRIPTOR *next;

   // get pointer to free space in DMA buffer and calculate room available

   alignment = dma_mode ? 32 : 4;
   free_ptr = dma_free_ptr;
   free_ptr = (uint8_t *)(((uintptr_t)free_ptr + alignment - 1) & ~(alignment - 1));
   room = dma_buffer + sizeof(dma_buffer) - free_ptr;

   // get pointer to next free descriptor

   current = get_last_descriptor();
   if (current) { next = current + 1; }
   else         { next = &dma_descriptors[0]; }

   if ((uint8_t *)next >= (uint8_t *)dma_descriptors + sizeof(dma_descriptors)) { next = NULL; }

   // flush existing chain if necessary

   if (room < bytes_needed || next == NULL)
   {
      flush_chain(dma_mode);
      free_ptr = dma_buffer;
      current = NULL;
      next = &dma_descriptors[0];
   }

   // populate descriptor

   next->data_address    = bytes_needed ? (uint32_t)free_ptr : 0;
   next->next_descriptor = 0;
   next->direction       = MASTER_READ;
   next->multi_io_mode   = 0;
   next->reserved1       = 0;
   next->fragment        = 1;
   next->reserved2       = 0;
   next->length          = 0;
   next->bounce_src      = 0;
   next->bounce_dst      = 0;
   next->bounce_length   = 0;

   // add descriptor to chain

   if (current) { current->next_descriptor = (uint32_t)next; }
   else         { dma_chain = next; }

   return(next);
}

/*==================================================================================================

FUNCTION: available_room

DESCRIPTION:
   This function calculates the room available in the last descriptor in the chain (the caller
   must pass in a pointer to the *last* descriptor).

==================================================================================================*/
static uint32_t available_room(DESCRIPTOR *last)
{
   uint8_t *end_of_buffer = dma_buffer + sizeof(dma_buffer);

   if (INT_TO_PTR(last->data_address) <  (void *)dma_buffer)    { return(0); }
   if (INT_TO_PTR(last->data_address) >= (void *)end_of_buffer) { return(0); }

   return (uint32_t)(end_of_buffer - (last->data_address + last->length));
}

/*==================================================================================================

FUNCTION: configure_clocks

DESCRIPTION:
   Turn on the clocks to QSPI.

==================================================================================================*/
static bool configure_clocks(QSPI_MASTER_CONFIG *cfg)
{
   // Set PNOC to its maximum frequency (100 MHz).  Configure the QSPI reference clock as
   // needed to get the requested bus frequency (reference clock is 4 times the bus clock
   // when SBL_EN is set).  The reference clock is specified in kHz and the bus clock is
   // specified in Hz.  Note that Clock_SetQSPIFrequency() returns the actual frequency
   // configured which may not be the same as the requested frequency.  It chooses the
   // closest match that is less than requested.  If no match is found it returns 0.

   if ( !Clock_SetSysPerfLevel(CLOCK_BOOT_PERF_MAX)       ) { return false; }
   if ( !Clock_SetQSPIFrequency(cfg->clk_freq * 4 / 1000) ) { return false; }

   return true;
}

/*==================================================================================================

FUNCTION: configure_dma_mode

DESCRIPTION:
   This function enables/disables DMA mode via the HWIO_QSPI_MSTR_CONFIG_ADDR register.  The current DMA
   mode is cached to avoid unnecessary register access.

==================================================================================================*/
static void configure_dma_mode(bool enable_dma)
{
   uint32_t mstr_config;

   if (enable_dma && !dma_enabled)
   {
      REG_IN(HWIO_QSPI_MSTR_CONFIG_ADDR, &mstr_config);
      mstr_config |= HWIO_QSPI_MSTR_CONFIG_DMA_ENABLE_BMSK;
      REG_OUT(HWIO_QSPI_MSTR_CONFIG_ADDR, mstr_config);
      dma_enabled = true;
   }
   else if (!enable_dma && dma_enabled)
   {
      REG_IN(HWIO_QSPI_MSTR_CONFIG_ADDR, &mstr_config);
      mstr_config &= ~HWIO_QSPI_MSTR_CONFIG_DMA_ENABLE_BMSK;
      REG_OUT(HWIO_QSPI_MSTR_CONFIG_ADDR, mstr_config);
      dma_enabled = false;
   }
}

/*==================================================================================================

FUNCTION: configure_gpios

DESCRIPTION:
   Configure TLMM so that QSPI signals are routed to the GPIO pads.

==================================================================================================*/
static bool configure_gpios(void)
{
   DALGpioSignalType gpio_group[] =
   {
      DAL_GPIO_CFG(QSPI_CS_N_0, QSPI_CS_N_0_FUNC_CONFIG, DAL_GPIO_INPUT, DAL_GPIO_PULL_UP,   DAL_GPIO_2MA),
      DAL_GPIO_CFG(QSPI_CLK, QSPI_CLK_FUNC_CONFIG, DAL_GPIO_INPUT, DAL_GPIO_PULL_UP,   DAL_GPIO_2MA),
      DAL_GPIO_CFG(QSPI_DATA_0, QSPI_DATA_0_FUNC_CONFIG, DAL_GPIO_INPUT, DAL_GPIO_PULL_DOWN, DAL_GPIO_2MA),
      DAL_GPIO_CFG(QSPI_DATA_1, QSPI_DATA_1_FUNC_CONFIG, DAL_GPIO_INPUT, DAL_GPIO_PULL_DOWN, DAL_GPIO_2MA),
      DAL_GPIO_CFG(QSPI_DATA_2, QSPI_DATA_2_FUNC_CONFIG, DAL_GPIO_INPUT, DAL_GPIO_PULL_DOWN, DAL_GPIO_2MA),
      DAL_GPIO_CFG(QSPI_DATA_3, QSPI_DATA_3_FUNC_CONFIG, DAL_GPIO_INPUT, DAL_GPIO_PULL_DOWN, DAL_GPIO_2MA),
   };
   uint32_t num_gpios = sizeof(gpio_group)/sizeof(gpio_group[0]);
   DALResult result;

   result = Tlmm_ConfigGpioGroup(DAL_TLMM_GPIO_ENABLE, gpio_group, num_gpios);

   return (result == DAL_SUCCESS) ? (true) : (false);
}

/*==================================================================================================

FUNCTION: dma_transfer_chain

DESCRIPTION:
   This function transfers a chain of descriptors over the bus using DMA mode.

==================================================================================================*/
static void dma_transfer_chain(DESCRIPTOR *chain)
{
   uint32_t mstr_int_status;

   REG_OUT(HWIO_QSPI_MSTR_INT_STATUS_ADDR, 0xFFFFFFFF);  // clear latched status bits
   REG_OUT(HWIO_QSPI_NEXT_DMA_DESC_ADDR_ADDR, (uint32_t)chain);

   while (1)  // poll until DMA transfer completes
   {
      REG_IN(HWIO_QSPI_MSTR_INT_STATUS_ADDR, &mstr_int_status);
      if (mstr_int_status & HWIO_QSPI_MSTR_INT_ENABLE_EN_DMA_CHAIN_DONE_BMSK) { break; }
   }
}

/*==================================================================================================

FUNCTION: dump_chain

DESCRIPTION:
   This function dumps the contents of the DMA descriptor chain.

==================================================================================================*/
static void dump_chain(void)
{
#if LOG_TO_UART || LOG_TO_RAM
   DESCRIPTOR *desc = dma_chain;

   log("----------------------------------------\n");
   log("dma_chain = %p\n", dma_chain);

   while (desc)
   {
      log("\n");
      log("data_address    = 0x%08X\n", desc->data_address);
      log("next_descriptor = 0x%08X\n", desc->next_descriptor);
      log("direction       = 0x%08X\n", desc->direction);
      log("multi_io_mode   = 0x%08X\n", desc->multi_io_mode);
      log("reserved1       = 0x%08X\n", desc->reserved1);
      log("fragment        = 0x%08X\n", desc->fragment);
      log("reserved2       = 0x%08X\n", desc->reserved2);
      log("length          = 0x%08X\n", desc->length);

      if (desc->length)
      {
//         log("\n");
//         hex_dump(INT_TO_PTR(desc->data_address), desc->length > 64 ? 64 : desc->length);
      }

      desc = INT_TO_PTR(desc->next_descriptor);
   }

   log("----------------------------------------\n");
#endif
}

/*==================================================================================================

FUNCTION: dump_log

DESCRIPTION:
   This function dumps the contents of the log buffer to the UART.

==================================================================================================*/
static void dump_log(void)
{
#if LOG_TO_RAM
   uint8_t *ptr = (uint8_t *)log_buffer;

   if (log_end) { SerialPortWrite(ptr + log_index + 1, log_end - log_index - 1); }
   SerialPortWrite(ptr, log_index);
#endif
}

/*==================================================================================================

FUNCTION: flush_chain

DESCRIPTION:
   This function flushes the existing DMA chain to hardware.

==================================================================================================*/
static void flush_chain(bool dma_mode)
{
   DESCRIPTOR *desc = dma_chain;
   uint8_t *src;
   uint8_t *dst;
   uint32_t i;

   configure_dma_mode(dma_mode);

   // Execute the transfers specified in the chain of descriptors.

   if (dma_mode) { dma_transfer_chain(dma_chain); }
   else          { pio_transfer_chain(dma_chain); }

   // Copy any bounce data from the descriptors to the client buffer (for reads only).

   while (desc)
   {
      src = INT_TO_PTR(desc->bounce_src);
      dst = INT_TO_PTR(desc->bounce_dst);

      for (i = 0; i < desc->bounce_length; i++) { dst[i] = src[i]; }

      desc = INT_TO_PTR(desc->next_descriptor);
   }

   dma_free_ptr = dma_buffer;
   dma_chain = NULL;
}

/*==================================================================================================

FUNCTION: get_last_descriptor

DESCRIPTION:
   This function returns a pointer to the last descriptor in the chain.  If no chain exists
   then NULL is returned.

==================================================================================================*/
static DESCRIPTOR *get_last_descriptor(void)
{
   DESCRIPTOR *desc = dma_chain;

   if (desc)
   {
      while (desc->next_descriptor) { desc = INT_TO_PTR(desc->next_descriptor); }
   }

   return(desc);
}

/*==================================================================================================

FUNCTION: log

DESCRIPTION:
   This function sends a printf() style message to the UART or a circular RAM buffer.

==================================================================================================*/
static void log(const char *fmt, ...)
#if LOG_TO_UART
{
   VA_LIST ap;
   uint8_t buf[256];
   uint32_t num_chars;

   VA_START(ap, fmt);
   num_chars = AsciiVSPrint((char *)buf, sizeof(buf), fmt, ap);
   VA_END(ap);

   SerialPortWrite(buf, num_chars);
}
#elif LOG_TO_RAM
{
   VA_LIST ap;
   char *ptr;
   uint32_t room_left;
   uint32_t num_chars;

   VA_START(ap, fmt);
   ptr = log_buffer + log_index;
   room_left = LOG_SIZE - log_index;
   num_chars = AsciiVSPrint(ptr, room_left, fmt, ap);  // num_chars doesn't include NULL terminator

   if (log_index && (num_chars >= room_left - 1))
   {
      log_end = log_index;  // index of NULL byte after last log message
      log_index = 0;
      num_chars = AsciiVSPrint(log_buffer, LOG_SIZE, fmt, ap);
   }

   log_index += num_chars;
   VA_END(ap);
}
#else
{
}
#endif

/*==================================================================================================

FUNCTION: pio_read

DESCRIPTION:
   This function performs a PIO read transfer using a single transaction.

==================================================================================================*/
static void pio_read(uint8_t *buffer, uint32_t num_bytes, uint32_t pio_transfer_config)
{
   uint8_t *ptr = buffer;
   uint32_t bytes_left = num_bytes;
   uint32_t bytes_read;

   REG_OUT(HWIO_QSPI_PIO_TRANSFER_CONFIG_ADDR, pio_transfer_config);
   REG_OUT(HWIO_QSPI_PIO_TRANSFER_CONTROL_ADDR, num_bytes);

   while (bytes_left)  // poll until all data has been read from the RX FIFO
   {
      bytes_read = service_rx_fifo(ptr, bytes_left);
      bytes_left -= bytes_read;
      ptr += bytes_read;
   }
}

/*==================================================================================================

FUNCTION: pio_transfer_chain

DESCRIPTION:
   This function transfers a chain of descriptors over the bus using PIO mode.

==================================================================================================*/
static void pio_transfer_chain(DESCRIPTOR *chain)
{
   DESCRIPTOR *desc = chain;
   bool write;
   uint8_t *buffer;
   uint32_t num_bytes;
   uint32_t pio_transfer_config;

   while (desc)
   {
      write = (desc->direction == MASTER_WRITE);
      buffer = INT_TO_PTR(desc->data_address);
      num_bytes = desc->length;
      pio_transfer_config = (desc->fragment ? HWIO_QSPI_PIO_TRANSFER_CONFIG_TRANSFER_FRAGMENT_BMSK : 0) |
                            (desc->multi_io_mode << HWIO_QSPI_PIO_TRANSFER_CONFIG_MULTI_IO_MODE_SHFT) |
                            (write ? HWIO_QSPI_PIO_TRANSFER_CONFIG_TRANSFER_DIRECTION_BMSK : 0);

      if (write) { pio_write(buffer, num_bytes, pio_transfer_config); }
      else       { pio_read (buffer, num_bytes, pio_transfer_config); }

      desc = INT_TO_PTR(desc->next_descriptor);
   }
}

/*==================================================================================================

FUNCTION: pio_write

DESCRIPTION:
   This function performs a PIO write transfer using a single transaction.

==================================================================================================*/
static void pio_write(uint8_t *buffer, uint32_t num_bytes, uint32_t pio_transfer_config)
{
   uint8_t *ptr = buffer;
   uint32_t bytes_left = num_bytes;
   uint32_t bytes_written;
   uint32_t mstr_int_status;

   REG_OUT(HWIO_QSPI_MSTR_INT_STATUS_ADDR, 0xFFFFFFFF);  // clear latched status bits
   REG_OUT(HWIO_QSPI_PIO_TRANSFER_CONFIG_ADDR, pio_transfer_config);
   REG_OUT(HWIO_QSPI_PIO_TRANSFER_CONTROL_ADDR, num_bytes);

   while (bytes_left)  // poll until all data has been written to the TX FIFO
   {
      bytes_written = service_tx_fifo(ptr, bytes_left);
      bytes_left -= bytes_written;
      ptr += bytes_written;
   }

   while (1)  // poll until transfer completes over the wire
   {
      REG_IN(HWIO_QSPI_MSTR_INT_STATUS_ADDR, &mstr_int_status);
      if (mstr_int_status & HWIO_QSPI_MSTR_INT_ENABLE_EN_TRANSACTION_DONE_BMSK) { break; }
   }
}

/*==================================================================================================

FUNCTION: queue_addr

DESCRIPTION:
   Queue the 3-byte or 4-byte address (cmd-ADDR-dummy-data).

==================================================================================================*/
static void queue_addr(uint32_t addr, uint8_t addr_bytes, QSPI_MODE addr_mode, bool dma_mode)
{
   DESCRIPTOR *desc;
   uint8_t *ptr;
   uint32_t i;

   if (addr_bytes == 0) { return; }
   desc = get_last_descriptor();

   // Check if we can add to the last descriptor else allocate a new one.

   if (desc &&
       desc->direction == MASTER_WRITE &&
       desc->multi_io_mode == addr_mode &&
       available_room(desc) >= addr_bytes)
   {
      ptr = INT_TO_PTR(desc->data_address + desc->length);
   }
   else
   {
      desc = allocate_descriptor(addr_bytes, dma_mode);
      desc->direction = MASTER_WRITE;
      desc->multi_io_mode = addr_mode;
      ptr = INT_TO_PTR(desc->data_address);
   }

   // Write the address to the descriptor.

   for (i = addr_bytes; i > 0; i--) { *ptr++ = (uint8_t)(addr >> (i - 1) * 8); }
   desc->length += addr_bytes;
   dma_free_ptr = INT_TO_PTR(desc->data_address + desc->length);
}

/*==================================================================================================

FUNCTION: queue_bounce_data

DESCRIPTION:
   Queue bounce data.  This is data that will use a bounce buffer that sits between the
   client buffer and hardware.  The bounce buffer is used to accommodate misaligned data.

==================================================================================================*/
static void queue_bounce_data(uint8_t *data, uint32_t data_bytes,
                              QSPI_MODE data_mode, bool write, bool dma_mode)
{
   DESCRIPTOR *desc;
   uint8_t *ptr;
   uint32_t i;

   desc = get_last_descriptor();

   // Check if we can add to the last descriptor else allocate a new one.

   if (desc &&
       desc->direction == write &&
       desc->multi_io_mode == data_mode &&
       available_room(desc) >= data_bytes)
   {
      ptr = INT_TO_PTR(desc->data_address + desc->length);
   }
   else
   {
      desc = allocate_descriptor(data_bytes, dma_mode);
      desc->direction = write;
      desc->multi_io_mode = data_mode;
      ptr = INT_TO_PTR(desc->data_address);
   }

   // Write the bounce data to the descriptor now or save the parameters
   // needed to read the bounce data from the descriptor later.

   if (write)
   {
      for (i = 0; i < data_bytes; i++) { ptr[i] = data[i]; }
   }
   else
   {
      desc->bounce_src = (uint32_t)ptr;
      desc->bounce_dst = (uint32_t)data;
      desc->bounce_length = data_bytes;
   }

   desc->length += data_bytes;
   dma_free_ptr = INT_TO_PTR(desc->data_address + desc->length);
}

/*==================================================================================================

FUNCTION: queue_data

DESCRIPTION:
   Queue the data from the client buffer.  The data may be split into multiple parts to
   ensure the following:

   1) the buffer starts on a 32-byte boundary (for DMA) or a 4-byte boundary (for PIO)
   2) the buffer ends on a 4-byte boundary (only required for DMA reads)
   3) the buffer is no larger than 65535 (0xFFFF) bytes

   It is straightforward to handle (3) by splitting the buffer across multiple descriptors.
   Bounce buffers are used to handle (1) and (2).

==================================================================================================*/
static void queue_data(uint8_t *data, uint32_t data_bytes,
                       QSPI_MODE data_mode, bool write, bool dma_mode)
{
   uint32_t alignment;
   uint8_t *aligned_ptr;
   uint8_t *epilog_ptr;
   uint32_t prolog_bytes, aligned_bytes, epilog_bytes;

   if (data_bytes == 0) { return; }

   alignment = dma_mode ? 32 : 4;
   aligned_ptr = (uint8_t *)(((uintptr_t)data + alignment - 1) & ~(alignment - 1));
   prolog_bytes = ((aligned_ptr - data) > data_bytes) ? (data_bytes) : (aligned_ptr - data);
   epilog_bytes = (dma_mode && !write) ? ((data_bytes - prolog_bytes) & 0x03) : (0);
   aligned_bytes = data_bytes - prolog_bytes - epilog_bytes;
   epilog_ptr = data + prolog_bytes + aligned_bytes;

   if (aligned_bytes == 0)
   {
      // Combine prolog and epilog if there is nothing between them.  This avoids
      // the need to have two bounce buffers in the same descriptor.

      prolog_bytes += epilog_bytes;
      epilog_bytes = 0;
   }

   if (prolog_bytes)  { queue_bounce_data(data,        prolog_bytes,  data_mode, write, dma_mode); }
   if (aligned_bytes) { queue_direct_data(aligned_ptr, aligned_bytes, data_mode, write, dma_mode); }
   if (epilog_bytes)  { queue_bounce_data(epilog_ptr,  epilog_bytes,  data_mode, write, dma_mode); }
}

/*==================================================================================================

FUNCTION: queue_direct_data

DESCRIPTION:
   Queue direct data.  This is data that will be copied directly between the client buffer
   and the hardware (and must be properly aligned).

==================================================================================================*/
static void queue_direct_data(uint8_t *data, uint32_t data_bytes,
                              QSPI_MODE data_mode, bool write, bool dma_mode)
{
   DESCRIPTOR *desc;
   uint32_t chunk_size;

   while (data_bytes)
   {
      // Maximum transfer size is 0xFFFF bytes but 0xFFE0 is the largest size that
      // maintains 32-byte alignment between chunks.

      chunk_size = (data_bytes > 0xFFE0) ? (0xFFE0) : (data_bytes);

      // Allocate a new descriptor and point it to the client buffer.

      desc = allocate_descriptor(0, dma_mode);
      desc->direction = write;
      desc->multi_io_mode = data_mode;
      desc->data_address = (uint32_t)data;
      desc->length = chunk_size;

      data += chunk_size;
      data_bytes -= chunk_size;
   }
}

/*==================================================================================================

FUNCTION: queue_dummy

DESCRIPTION:
   Queue dummy bytes to generate dummy clock cycles (cmd-addr-DUMMY-data).

   Note that we must use a write to drive DQ3 (HOLD_N) high when generating dummy clock cycles
   in 4-wire mode.  If we use a read then we will release DQ2 (WP_N) and DQ3 (HOLD_N) which will
   cause them to go low (assert).  This will cause the slave to ignore all but one of the dummy
   clock cycles (the first one gets through because it takes some time for HOLD_N to go low).

==================================================================================================*/
static void queue_dummy(uint8_t dummy_clocks, bool dma_mode)
{
   DESCRIPTOR *desc;
   uint8_t *ptr = NULL;
   uint32_t dummy_bytes;
   uint32_t clocks_per_byte;
   uint32_t remainder;
   uint32_t i;

   if (dummy_clocks == 0) { return; }
   desc = get_last_descriptor();

   // Check if we can add to the last descriptor else allocate a new one.

   if (desc &&
       desc->direction == MASTER_WRITE)
   {
      switch (desc->multi_io_mode)
      {
         case SDR_1BIT: clocks_per_byte = 8; break;
         case SDR_2BIT: clocks_per_byte = 4; break;
         case SDR_4BIT: clocks_per_byte = 2; break;
         case DDR_1BIT: clocks_per_byte = 4; break;
         case DDR_2BIT: clocks_per_byte = 2; break;
         case DDR_4BIT: clocks_per_byte = 1; break;
         default:                            return;  // fatal error
      }

      dummy_bytes = dummy_clocks / clocks_per_byte;
      remainder   = dummy_clocks % clocks_per_byte;

      if (remainder == 0 && available_room(desc) >= dummy_bytes)
      {
         ptr = INT_TO_PTR(desc->data_address + desc->length);
      }
   }

   if (ptr == NULL)
   {
      dummy_bytes = dummy_clocks;
      desc = allocate_descriptor(dummy_bytes, dma_mode);
      desc->direction = MASTER_WRITE;
      desc->multi_io_mode = DDR_4BIT;
      ptr = INT_TO_PTR(desc->data_address);
   }

   // Write the dummy bytes to the descriptor.

   for (i = 0; i < dummy_bytes; i++) { *ptr++ = 0xFF; }
   desc->length += dummy_bytes;
   dma_free_ptr = INT_TO_PTR(desc->data_address + desc->length);
}

/*==================================================================================================

FUNCTION: queue_opcode

DESCRIPTION:
   Queue the 1-byte command opcode (CMD-addr-dummy-data).

==================================================================================================*/
static void queue_opcode(uint8_t opcode, QSPI_MODE cmd_mode, bool dma_mode)
{
   DESCRIPTOR *desc;
   uint8_t *ptr;
   uint32_t opcode_bytes = 1;

   desc = get_last_descriptor();

   // Check if we can add to the last descriptor else allocate a new one.

   if (desc &&
       desc->direction == MASTER_WRITE &&
       desc->multi_io_mode == cmd_mode &&
       available_room(desc) >= opcode_bytes)
   {
      ptr = INT_TO_PTR(desc->data_address + desc->length);
   }
   else
   {
      desc = allocate_descriptor(opcode_bytes, dma_mode);
      desc->direction = MASTER_WRITE;
      desc->multi_io_mode = cmd_mode;
      ptr = INT_TO_PTR(desc->data_address);
   }

   // Write the opcode to the descriptor.

   *ptr = opcode;
   desc->length += opcode_bytes;
   dma_free_ptr = INT_TO_PTR(desc->data_address + desc->length);
}

/*==================================================================================================

FUNCTION: reg_init

DESCRIPTION:
   This function initializes the QSPI registers and puts the QSPI into a known state.

==================================================================================================*/
static void reg_init(QSPI_MASTER_CONFIG *cfg)
{
   uint32_t spi_mode;
   uint32_t tx_data_oe_delay, tx_data_delay;
   uint32_t mstr_config;

   spi_mode = (cfg->clk_polarity == 0 && cfg->clk_phase == 0) ? 0 :
              (cfg->clk_polarity == 0 && cfg->clk_phase == 1) ? 1 :
              (cfg->clk_polarity == 1 && cfg->clk_phase == 0) ? 2 :
              (cfg->clk_polarity == 1 && cfg->clk_phase == 1) ? 3 :
                                                                0;

   // The TX DATA delay is needed for writes in DDR mode using the Micron SPI NOR flash.
   // Note that a half cycle of the reference clock is 1/8 cycle of the SPI clock when
   // SBL_EN=1 and 1/4 cycle of the SPI clock when SBL_EN=0.

   tx_data_oe_delay = 1;  // delay half cycle of reference clock
   tx_data_delay    = 1;  // delay half cycle of reference clock

   mstr_config = (tx_data_oe_delay << HWIO_QSPI_MSTR_CONFIG_TX_DATA_OE_DELAY_SHFT) |
                 (tx_data_delay    << HWIO_QSPI_MSTR_CONFIG_TX_CS_N_DELAY_SHFT) |
                 (HWIO_QSPI_MSTR_CONFIG_SBL_EN_BMSK) |
                 (cfg->chip_select ? HWIO_QSPI_MSTR_CONFIG_CHIP_SELECT_NUM_BMSK : 0) |
                 (spi_mode << HWIO_QSPI_MSTR_CONFIG_SPI_MODE_SHFT) |
                 (HWIO_QSPI_MSTR_CONFIG_PIN_WPN_BMSK) |
                 (HWIO_QSPI_MSTR_CONFIG_PIN_HOLDN_BMSK) |
                 (HWIO_QSPI_MSTR_CONFIG_FB_CLK_EN_BMSK);

   // Do not set the CONTINUOUS_MODE bit in RD_FIFO_CONFIG.  If CONTINUOUS_MODE is
   // used transfers will hang when we are slow to service the RD_FIFO.  When the
   // RD_FIFO is full the QSPI master continues clocking in data over the bus (and
   // decrementing REQUEST_COUNT in PIO_TRANSFER_CONTROL) but just drops the data
   // with no indication to SW.  This causes the transfer to end before SW has read
   // the expected number of bytes from the RD_FIFO.

   REG_OUT(HWIO_QSPI_MSTR_CONFIG_ADDR,     mstr_config);
   REG_OUT(HWIO_QSPI_AHB_MASTER_CFG_ADDR,  0x00001a02);   // this is the reset state
   REG_OUT(HWIO_QSPI_MSTR_INT_ENABLE_ADDR, 0x00000000);
   REG_OUT(HWIO_QSPI_MSTR_INT_STATUS_ADDR, 0xFFFFFFFF);   // clear latched status bits
   REG_OUT(HWIO_QSPI_RD_FIFO_CONFIG_ADDR,  0x00000000);
   REG_OUT(HWIO_QSPI_RD_FIFO_RESET_ADDR,   HWIO_QSPI_RD_FIFO_RESET_RESET_FIFO_BMSK);
}

/*==================================================================================================

FUNCTION: service_rx_fifo

DESCRIPTION:
   This function reads data from the RX FIFO.

==================================================================================================*/
static uint32_t service_rx_fifo(uint8_t *ptr, uint32_t num_bytes)
{
   uint32_t full_words = num_bytes >> 2;
   uint32_t partial_bytes = num_bytes & 0x03;
   uint32_t rd_fifo_status;
   uint8_t  bytes_in_fifo;
   uint8_t  words_in_fifo;
   uint32_t words_to_read;
   uint32_t bytes_to_read;
   uint32_t word_value;
   uint32_t i;

   REG_IN(HWIO_QSPI_RD_FIFO_STATUS_ADDR, &rd_fifo_status);
   bytes_in_fifo = (rd_fifo_status & HWIO_QSPI_RD_FIFO_STATUS_WR_CNTS_BMSK) >> HWIO_QSPI_RD_FIFO_STATUS_WR_CNTS_SHFT;
   words_in_fifo = bytes_in_fifo >> 2;

   words_to_read = (words_in_fifo < full_words) ? (words_in_fifo) : (full_words);
   bytes_to_read = (bytes_in_fifo < num_bytes)  ?             (0) : (partial_bytes);

   for (i = 0; i < words_to_read; i++)
   {
      REG_IN(HWIO_QSPI_RD_FIFOn_ADDR(0), &word_value);
      *(uint32_t *)ptr = word_value;  // ptr is word aligned
      ptr += 4;
   }

   if (bytes_to_read)
   {
      REG_IN(HWIO_QSPI_RD_FIFOn_ADDR(0), &word_value);
      for (i = 0; i < bytes_to_read; i++) { ptr[i] = (uint8_t)(word_value >> i * 8); }
   }

   return(words_to_read * 4 + bytes_to_read);
}

/*==================================================================================================

FUNCTION: service_tx_fifo

DESCRIPTION:
   This function writes data to the TX FIFO.

==================================================================================================*/
static uint32_t service_tx_fifo(uint8_t *ptr, uint32_t num_bytes)
{
   uint32_t full_words = num_bytes >> 2;
   uint32_t partial_bytes = num_bytes & 0x03;
   uint32_t pio_transfer_status;
   uint32_t room_in_bytes;
   uint32_t room_in_words;
   uint32_t words_to_send;
   uint32_t bytes_to_send;
   uint32_t word_value;
   uint32_t i;

   REG_IN(HWIO_QSPI_PIO_TRANSFER_STATUS_ADDR, &pio_transfer_status);
   room_in_bytes = (pio_transfer_status & HWIO_QSPI_PIO_TRANSFER_STATUS_WR_FIFO_BYTES_BMSK) >> HWIO_QSPI_PIO_TRANSFER_STATUS_WR_FIFO_BYTES_SHFT;
   room_in_words = room_in_bytes >> 2;

   words_to_send = (full_words > room_in_words) ? (room_in_words) : (full_words);
   bytes_to_send = (num_bytes  > room_in_bytes) ?             (0) : (partial_bytes);

   for (i = 0; i < words_to_send; i++)
   {
      word_value = *(uint32_t *)ptr;  // ptr is word aligned
      REG_OUT(HWIO_QSPI_PIO_DATAOUT_4BYTE_ADDR, word_value);
      ptr += 4;
   }

   for (i = 0; i < bytes_to_send; i++)
   {
      REG_OUT(HWIO_QSPI_PIO_DATAOUT_1BYTE_ADDR, *ptr);
      ptr++;
   }

   return(words_to_send * 4 + bytes_to_send);
}

/*==================================================================================================
                                          GLOBAL FUNCTIONS
==================================================================================================*/
/*==================================================================================================

FUNCTION: quadspi_cmd

DESCRIPTION:
   This function executes a complete SPI NOR flash transaction including the command, address,
   dummy clock cycles, and data.  In most cases, this function should be used instead of the
   low level read/write APIs.

==================================================================================================*/
bool quadspi_cmd(QSPI_CMD *cmd, uint32_t addr, uint8_t *data, uint32_t data_bytes, bool enable_dma)
{
   DESCRIPTOR *last;

   if (cmd->addr_bytes   > 4)  { return false; }
   if (cmd->dummy_clocks > 16) { return false; }

   queue_opcode(cmd->opcode, cmd->cmd_mode, enable_dma);
   queue_addr(addr, cmd->addr_bytes, cmd->addr_mode, enable_dma);
   queue_dummy(cmd->dummy_clocks, enable_dma);
   queue_data(data, data_bytes, cmd->data_mode, cmd->write, enable_dma);

   last = get_last_descriptor();
   last->fragment = 0;  // deassert chip select after completing the last descriptor
   flush_chain(enable_dma);

   return true;
}

/*==================================================================================================

FUNCTION: quadspi_deinit

DESCRIPTION:
   Deinitialize the QSPI and the HW it depends on (clocks, TLMM).  This function is used to put
   the HW into a low power state.

==================================================================================================*/
bool quadspi_deinit(void)
{
   return true;
}

/*==================================================================================================

FUNCTION: quadspi_init

DESCRIPTION:
   Initialize the QSPI and the HW it depends on (clocks, TLMM).  This function can be called
   between transfers to change the bus clock frequency, chip select, etc.

==================================================================================================*/
bool quadspi_init(QSPI_MASTER_CONFIG *cfg)
{
   if ( !configure_clocks(cfg) ) { return false; }
   if ( !configure_gpios()     ) { return false; }

   reg_init(cfg);
   return true;
}

/*==================================================================================================

FUNCTION: quadspi_read

DESCRIPTION:
   Perform a read transaction on the QSPI bus.

==================================================================================================*/
bool quadspi_read(uint8_t *buffer, uint32_t num_bytes, QSPI_TRANSFER_CONFIG *cfg)
{
   DESCRIPTOR *last;

   queue_data(buffer, num_bytes, cfg->mode, false, cfg->enable_dma);
   last = get_last_descriptor();
   last->fragment = cfg->terminate ? 0 : 1;
   flush_chain(cfg->enable_dma);

   return true;
}

/*==================================================================================================

FUNCTION: quadspi_write

DESCRIPTION:
   Perform a write transaction on the QSPI bus.

==================================================================================================*/
bool quadspi_write(uint8_t *buffer, uint32_t num_bytes, QSPI_TRANSFER_CONFIG *cfg)
{
   DESCRIPTOR *last;

   queue_data(buffer, num_bytes, cfg->mode, true, cfg->enable_dma);
   last = get_last_descriptor();
   last->fragment = cfg->terminate ? 0 : 1;
   flush_chain(cfg->enable_dma);

   return true;
}
