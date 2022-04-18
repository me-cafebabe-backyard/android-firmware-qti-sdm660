/*==================================================================================================

FILE: uart.c

DESCRIPTION: UEFI driver for UARTDM/UARTBAM

                    Copyright (c) 2013-2017 Qualcomm Technologies, Incorporated
                                        All Rights Reserved
                                     QUALCOMM Proprietary/GTDR

==================================================================================================*/
/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


when       who        what, where, why
--------   --------   ----------------------------------------------------------
05/01/17   AG         Fix Regression issue on SDX20 for GPIO Config failure
12/16/16   AG         Fix issue with GPIO config on different Tiles
10/27/16   PR         Initial version
============================================================================*/
/*==================================================================================================
                                            DESCRIPTION
====================================================================================================

GLOBAL FUNCTIONS:
   uart_initialize
   uart_poll
   uart_read
   uart_write

==================================================================================================*/
/*==================================================================================================
                                           INCLUDE FILES
==================================================================================================*/

#include <Library/BaseLib.h>  // AsciiStrCmp()
#include <Library/IoLib.h>    // MmioWrite32(), etc.
#include <Library/PcdLib.h>   // PcdGetPtr()
#include <Uart_settings.h>

/*==================================================================================================
                                             CONSTANTS
==================================================================================================*/

#define RX_XFER_SIZE  4096  // size of RX transfer (must be greater than or equal to RX FIFO size)
#define RING_SIZE      256  // size of the ring buffer (must be a power of 2)

#define TX_FIFO_SIZE   256  // size (in bytes) allocated for TX in the UART HW FIFO

/* Command Register */
#define UARTDM_CR_ENA_RX         0x00000001   // Enable Receiver
#define UARTDM_CR_DIS_RX         0x00000002   // Disable Receiver
#define UARTDM_CR_ENA_TX         0x00000004   // Enable Transmitter
#define UARTDM_CR_DIS_TX         0x00000008   // Disable Transmitter
#define UARTDM_CR_RESET_RX       0x00000010   // Reset Receiver
#define UARTDM_CR_RESET_TX       0x00000020   // Reset Transmitter
#define UARTDM_CR_RESET_ERR      0x00000030   // Reset Error Status
#define UARTDM_CR_STA_BRK        0x00000050   // Start Break
#define UARTDM_CR_STO_BRK        0x00000060   // Stop Break
#define UARTDM_CR_RESET_STALE    0x00000080   // Clears the stale interrupt
#define UARTDM_CR_SET_RFR        0x000000D0   // Set RFR
#define UARTDM_CR_RESET_RFR      0x000000E0   // Reset RFR
#define UARTDM_CR_ENA_CR_PROT    0x00000100   // Enable CR protection
#define UARTDM_CR_DIS_CR_PROT    0x00000200   // Disable CR protection
#define UARTDM_CR_ENA_STALE_EVT  0x00000500   // Enables Stale Event
#define UARTDM_CR_DIS_STALE_EVT  0x00000600   // Disables Stale Event

/* Status Register */
#define UARTDM_SR_RX_START_LAST 0x00000100   // Rx break detected
#define UARTDM_SR_RXHUNT        0x00000080   // Hunt Character Received
#define UARTDM_SR_RXBREAK       0x00000040   // Break Received
#define UARTDM_SR_PF_ERR        0x00000020   // Parity of Framing Error
#define UARTDM_SR_OVR_ERR       0x00000010   // Overrun Error
#define UARTDM_SR_TXEMT         0x00000008   // Transmitter Empty
#define UARTDM_SR_TXRDY         0x00000004   // Transmitter Ready
#define UARTDM_SR_RXFULL        0x00000002   // Receiver Full
#define UARTDM_SR_RXRDY         0x00000001   // Receiver Ready

/* Interrupt Status Register */
#define UARTDM_ISR_TX_DONE    0x00000200   // TX Done
#define UARTDM_ISR_TX_ERROR   0x00000100   // TX Ready
#define UARTDM_ISR_TX_READY   0x00000080   // TX Done
#define UARTDM_ISR_CUR_CTS    0x00000040   // Current CTS
#define UARTDM_ISR_DELTA_CTS  0x00000020   // Delta CTS
#define UARTDM_ISR_RXLEV      0x00000010   // RX Level exceeded
#define UARTDM_ISR_RXSTALE    0x00000008   // Stale RX character occurred
#define UARTDM_ISR_RXBREAK    0x00000004   // RX Break occurred
#define UARTDM_ISR_RXHUNT     0x00000002   // RX Hunt character received
#define UARTDM_ISR_TXLEV      0x00000001   // TX Level or below met

/* RX FIFO State Register */
#define UARTDM_RXFS_FIFO_STATE_MSB_MASK   0xFFFFC000
#define UARTDM_RXFS_FIFO_STATE_MSB_SHIFT  2
#define UARTDM_RXFS_FIFO_STATE_LSB_MASK   0x0000007F
#define UARTDM_RXFS_FIFO_STATE_LSB_SHIFT  0

/*==================================================================================================
                                               MACROS
==================================================================================================*/

// The read/write indices do not wrap around to zero until integer overflow occurs.  This keeps
// the logic simple when determining the number of bytes in the ring buffer.  But they must be
// masked before subscripting and the size of the ring buffer must be a power of 2.

#define BYTES_IN_RING()     ( write_index - read_index )
#define ROOM_IN_RING()      ( RING_SIZE - BYTES_IN_RING() - 1 )  // always leave one empty slot
#define RING_GET_BYTE()     ( ring_buffer[read_index++  & (RING_SIZE - 1)] )
#define RING_PUT_BYTE(data) { ring_buffer[write_index++ & (RING_SIZE - 1)] = data; }

#define REG(x) (props->uart_base + (props->family == LEGACY ? legacy_offsets.x : badger_offsets.x))

/*==================================================================================================
                                              TYPEDEFS
==================================================================================================*/


typedef struct
{
   UINT32 mr1;
   UINT32 mr2;
   UINT32 csr;
   UINT32 sr;
   UINT32 cr;
   UINT32 misr;
   UINT32 imr;
   UINT32 isr;
   UINT32 ipr;
   UINT32 tfwr;
   UINT32 rfwr;
   UINT32 hcr;
   UINT32 dmrx;
   UINT32 irda;
   UINT32 snap;
   UINT32 dmen;
   UINT32 ncft;
   UINT32 badr;
   UINT32 txfs;
   UINT32 rxfs;
   UINT32 tf;
   UINT32 rf;
   UINT32 sim;
} REGISTER_OFFSETS;

typedef struct
{
   UINT32 blsp_cbcr;    // GCCSN_BLSPx_AHB_CBCR register offset
   UINT32 uart_cbcr;    // GCCSN_BLSPx_UARTx_APPS_CBCR register offset
   UINT32 uart_offset;  // GCCSN_BLSPx_UARTx_CMD_RCGR register offset for the specified UART
} QDF_CLOCK_CONFIG;

typedef struct
{
   UINT32 branch_vote_offset;  // GCC_APCS_CLOCK_BRANCH_ENA_VOTE register offset
   UINT32 blsp1_ahb_vote;      // bit position to enable BLSP1 AHB clock
   UINT32 blsp2_ahb_vote;      // bit position to enable BLSP2 AHB clock
   UINT32 tx_tlmm_ahb_vote;       // bit position to enable TLMM AHB clock
   UINT32 rx_tlmm_ahb_vote;       // bit position to enable TLMM AHB clock
   UINT32 tlmm_vote;           // bit position to enable TLMM clock
   UINT32 blsp_instance;       // BLSP instance for the specified UART
   UINT32 uart_offset;         // GCC_BLSPx_UARTx_BCR register offset for the specified UART
} CLOCK_CONFIG;

/*==================================================================================================
                                     LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

static void   configure_clocks(void);
static void   configure_clocks_badger(CLOCK_CONFIG *cfg);
static void   configure_clocks_dragonfly(QDF_CLOCK_CONFIG *cfg);
static void   configure_clocks_legacy(void);
static void   configure_gsbi(void);
static void   configure_tlmm(void);
static UINT32 gpio_cfg_addr(UINT32 tlmm_base, UINT32 n);
static void   reg_init(void);
static void   rx_transfer_start(void);
static void   service_rx_fifo(void);
static UINT32 transmit_data(UINT8 *user_buffer, UINT32 bytes_to_send);

/*==================================================================================================
                                          LOCAL VARIABLES
==================================================================================================*/

static UART_PROPS  *props = NULL;
static UINT32 rx_bytes_left = 0;  // number of bytes left in the current RX transfer
                                  // that have not yet been read out of the RX FIFO

static UINT8 ring_buffer[RING_SIZE];  // size must be a power of 2
static UINT32 read_index = 0;   // must be masked before subscripting
static UINT32 write_index = 0;  // must be masked before subscripting

static const REGISTER_OFFSETS legacy_offsets =
{
   0x00,  // MR1
   0x04,  // MR2
   0x08,  // CSR   (write only)
   0x08,  // SR    (read only)
   0x10,  // CR    (write only)
   0x10,  // MISR  (read only)
   0x14,  // IMR   (write only)
   0x14,  // ISR   (read only)
   0x18,  // IPR
   0x1C,  // TFWR
   0x20,  // RFWR
   0x24,  // HCR
   0x34,  // DMRX
   0x38,  // IRDA  (write only)
   0x38,  // SNAP  (read only)
   0x3C,  // DMEN
   0x40,  // NCFT
   0x44,  // BADR
   0x4C,  // TXFS
   0x50,  // RXFS
   0x70,  // TF    (write only)
   0x70,  // RF    (read only)
   0x80,  // SIM
};

static const REGISTER_OFFSETS badger_offsets =
{
   0x00,   // MR1
   0x04,   // MR2
   0xA0,   // CSR   (new location)
   0xA4,   // SR    (new location)
   0xA8,   // CR    (new location)
   0xAC,   // MISR  (new location)
   0xB0,   // IMR   (new location)
   0xB4,   // ISR   (new location)
   0x18,   // IPR
   0x1C,   // TFWR
   0x20,   // RFWR
   0x24,   // HCR
   0x34,   // DMRX
   0xB8,   // IRDA  (new location)
   0xBC,   // SNAP  (new location)
   0x3C,   // DMEN
   0x40,   // NCFT
   0x44,   // BADR
   0x4C,   // TXFS
   0x50,   // RXFS
   0x100,  // TF    (new location)
   0x140,  // RF    (new location)
   0x80,   // SIM
};


/*==================================================================================================
                                          LOCAL FUNCTIONS
==================================================================================================*/
/*==================================================================================================

FUNCTION: configure_clocks

DESCRIPTION:
   This function performs all necessary clock configuration for UART enablement.

==================================================================================================*/
static void configure_clocks(void)
{
   CLOCK_CONFIG cfg;
   QDF_CLOCK_CONFIG dc;

   if (props->clock_base == 0) { return; }

   if (props->family == LEGACY)
   {
      configure_clocks_legacy();
   }
   else if (props->family == BADGER)
   {
      cfg.branch_vote_offset = 0x1484;
      cfg.blsp1_ahb_vote = 17;
      cfg.blsp2_ahb_vote = 15;
      cfg.tx_tlmm_ahb_vote  =  8;
      cfg.rx_tlmm_ahb_vote  =  8;
      cfg.tlmm_vote      =  7;

      switch (props->uart_instance)
      {
         case  1: cfg.blsp_instance = 1; cfg.uart_offset = 0x0680; break;
         case  2: cfg.blsp_instance = 1; cfg.uart_offset = 0x0700; break;
         case  3: cfg.blsp_instance = 1; cfg.uart_offset = 0x0780; break;
         case  4: cfg.blsp_instance = 1; cfg.uart_offset = 0x0800; break;
         case  5: cfg.blsp_instance = 1; cfg.uart_offset = 0x0880; break;
         case  6: cfg.blsp_instance = 1; cfg.uart_offset = 0x0900; break;
         case  7: cfg.blsp_instance = 2; cfg.uart_offset = 0x09C0; break;
         case  8: cfg.blsp_instance = 2; cfg.uart_offset = 0x0A40; break;
         case  9: cfg.blsp_instance = 2; cfg.uart_offset = 0x0AC0; break;
         case 10: cfg.blsp_instance = 2; cfg.uart_offset = 0x0B40; break;
         case 11: cfg.blsp_instance = 2; cfg.uart_offset = 0x0BC0; break;
         case 12: cfg.blsp_instance = 2; cfg.uart_offset = 0x0C40; break;
         default: return;
      }

      configure_clocks_badger(&cfg);
   }
   else if (props->family == BEAR)
   {
      cfg.branch_vote_offset = 0x45004;
      cfg.blsp1_ahb_vote = 10;
      cfg.blsp2_ahb_vote =  0;  // BLSP2 vote does not exist on this target
      cfg.tx_tlmm_ahb_vote  =  5;
      cfg.rx_tlmm_ahb_vote  =  5;
      cfg.tlmm_vote      =  4;

      switch (props->uart_instance)
      {
         case 1: cfg.blsp_instance = 1; cfg.uart_offset = 0x2038; break;
         case 2: cfg.blsp_instance = 1; cfg.uart_offset = 0x3028; break;
         case 3: cfg.blsp_instance = 1; cfg.uart_offset = 0x4038; break;
         case 4: cfg.blsp_instance = 1; cfg.uart_offset = 0x5038; break;
         default: return;
      }

      configure_clocks_badger(&cfg);
   }
   else if (props->family == HONEYBADGER)
   {
      cfg.branch_vote_offset = 0x52004;
      cfg.blsp1_ahb_vote = 17;
      cfg.blsp2_ahb_vote = 15;
      cfg.tx_tlmm_ahb_vote  = (props->platform == 8998) ? (11) : (8);
      cfg.rx_tlmm_ahb_vote  = (props->platform == 8998) ? (11) : (8);
      cfg.tlmm_vote      = 7;

      if (props->platform == 8998)
      {
         switch (props->uart_instance)
         {
            case  1: cfg.blsp_instance = 1; cfg.uart_offset = 0x1a000; break;
            case  2: cfg.blsp_instance = 1; cfg.uart_offset = 0x1c000; break;
            case  3: cfg.blsp_instance = 1; cfg.uart_offset = 0x1e000; break;
            case  4: cfg.blsp_instance = 2; cfg.uart_offset = 0x27000; break;
            case  5: cfg.blsp_instance = 2; cfg.uart_offset = 0x29000; break;
            case  6: cfg.blsp_instance = 2; cfg.uart_offset = 0x2b000; break;
            default: return;
         }
      }
      else if (props->platform == 660)
      {
      
         switch (props->uart_instance)
         {
            case  1: cfg.blsp_instance = 1; cfg.uart_offset = 0x1a000; break;
				// Both GPIO's 0 & 1 are on South Tile
				cfg.tx_tlmm_ahb_vote  = 8;
				cfg.rx_tlmm_ahb_vote  = 8;
            case  2: cfg.blsp_instance = 1; cfg.uart_offset = 0x1c000; 
				cfg.tx_tlmm_ahb_vote  = 11;
				cfg.rx_tlmm_ahb_vote  = 8;
				break;
            case  3: cfg.blsp_instance = 2; cfg.uart_offset = 0x27000; break;
				// Both GPIO's 0 & 1 are on Center Tile
				cfg.tx_tlmm_ahb_vote  = 12;
				cfg.rx_tlmm_ahb_vote  = 12;
            case  4: cfg.blsp_instance = 2; cfg.uart_offset = 0x29000; break;
				// Both GPIO's 0 & 1 are on North Tile
				cfg.tx_tlmm_ahb_vote  = 11;
				cfg.rx_tlmm_ahb_vote  = 11;
            default: return;
         }
      }
      else
      {
         switch (props->uart_instance)
         {
            case  1: cfg.blsp_instance = 1; cfg.uart_offset = 0x1a000; break;
            case  2: cfg.blsp_instance = 1; cfg.uart_offset = 0x1c000; break;
            case  3: cfg.blsp_instance = 1; cfg.uart_offset = 0x1e000; break;
            case  4: cfg.blsp_instance = 1; cfg.uart_offset = 0x20000; break;
            case  5: cfg.blsp_instance = 1; cfg.uart_offset = 0x22000; break;
            case  6: cfg.blsp_instance = 1; cfg.uart_offset = 0x24000; break;
            case  7: cfg.blsp_instance = 2; cfg.uart_offset = 0x27000; break;
            case  8: cfg.blsp_instance = 2; cfg.uart_offset = 0x29000; break;
            case  9: cfg.blsp_instance = 2; cfg.uart_offset = 0x2b000; break;
            case 10: cfg.blsp_instance = 2; cfg.uart_offset = 0x2d000; break;
            case 11: cfg.blsp_instance = 2; cfg.uart_offset = 0x2f000; break;
            case 12: cfg.blsp_instance = 2; cfg.uart_offset = 0x31000; break;
            default: return;
         }
      }

      configure_clocks_badger(&cfg);
   }
   else if (props->family == DRAGONFLY)
   {
      switch (props->uart_instance)
      {
         case 1: dc.blsp_cbcr = 0x200BC; dc.uart_cbcr = 0x20088; dc.uart_offset = 0x20004; break;
         case 2: dc.blsp_cbcr = 0x200BC; dc.uart_cbcr = 0x2008C; dc.uart_offset = 0x20018; break;
         case 3: dc.blsp_cbcr = 0x200BC; dc.uart_cbcr = 0x20090; dc.uart_offset = 0x2002C; break;
         case 4: dc.blsp_cbcr = 0x200BC; dc.uart_cbcr = 0x20094; dc.uart_offset = 0x20040; break;
         case 5: dc.blsp_cbcr = 0x9003C; dc.uart_cbcr = 0x30088; dc.uart_offset = 0x30004; break;
         case 6: dc.blsp_cbcr = 0x9003C; dc.uart_cbcr = 0x3008C; dc.uart_offset = 0x30018; break;
         case 7: dc.blsp_cbcr = 0x9003C; dc.uart_cbcr = 0x30090; dc.uart_offset = 0x3002C; break;
         case 8: dc.blsp_cbcr = 0x9003C; dc.uart_cbcr = 0x30094; dc.uart_offset = 0x30040; break;
         default: return;
      }

      configure_clocks_dragonfly(&dc);
   }
}

/*==================================================================================================

FUNCTION: configure_clocks_badger

DESCRIPTION:
   This function enables the peripheral clocks for BLSP/UART/TLMM.  It also enables the UART core
   clock and sets the input frequency to 1.8432 MHz.

==================================================================================================*/
static void configure_clocks_badger(CLOCK_CONFIG *cfg)
{
   UINT32 branch_enable;
   UINT32 mode, src_sel, src_div, root_config;
   UINT32 m, n, m_reg, n_reg, d_reg;

   #define GCC_APCS_CLOCK_BRANCH_ENA_VOTE_ADDR  (props->clock_base + cfg->branch_vote_offset)
   #define GCC_BLSP_UART_APPS_CBCR_ADDR         (props->clock_base + cfg->uart_offset + 0x04)
   #define GCC_BLSP_UART_APPS_CMD_RCGR_ADDR     (props->clock_base + cfg->uart_offset + 0x0c)
   #define GCC_BLSP_UART_APPS_CFG_RCGR_ADDR     (props->clock_base + cfg->uart_offset + 0x10)
   #define GCC_BLSP_UART_APPS_M_ADDR            (props->clock_base + cfg->uart_offset + 0x14)
   #define GCC_BLSP_UART_APPS_N_ADDR            (props->clock_base + cfg->uart_offset + 0x18)
   #define GCC_BLSP_UART_APPS_D_ADDR            (props->clock_base + cfg->uart_offset + 0x1c)

   #define GCC_BLSP_UART_APPS_CFG_RCGR_MODE_SHFT     12
   #define GCC_BLSP_UART_APPS_CFG_RCGR_SRC_SEL_SHFT   8
   #define GCC_BLSP_UART_APPS_CFG_RCGR_SRC_DIV_SHFT   0

   branch_enable = MmioRead32(GCC_APCS_CLOCK_BRANCH_ENA_VOTE_ADDR);
   if (cfg->blsp_instance == 1) { branch_enable |= (1 << cfg->blsp1_ahb_vote); }
   if (cfg->blsp_instance == 2) { branch_enable |= (1 << cfg->blsp2_ahb_vote); }
   branch_enable |= (1 << cfg->tx_tlmm_ahb_vote);
   branch_enable |= (1 << cfg->rx_tlmm_ahb_vote);
   branch_enable |= (1 << cfg->tlmm_vote);

   mode    = 2;  // dual edge
   src_sel = 0;  // CXO (19,200,000)
   src_div = 0;  // bypass predivider
   root_config = (mode    << GCC_BLSP_UART_APPS_CFG_RCGR_MODE_SHFT)    |
                 (src_sel << GCC_BLSP_UART_APPS_CFG_RCGR_SRC_SEL_SHFT) |
                 (src_div << GCC_BLSP_UART_APPS_CFG_RCGR_SRC_DIV_SHFT);

   // select M/N:D values for BLSP_UART_APPS clock:
   //    input_clock * M / N   = output_clock
   //    19,200,000 * 12 / 125 = 1,843,200

   m = 12;
   n = 125;
   m_reg =        m & 0xFFFF;
   n_reg = ~(n - m) & 0xFFFF;
   d_reg =       ~n & 0xFFFF;  // set duty cycle to 0.5 (duty cycle = d / n; d_val = ~(2 * d))

   MmioWrite32(GCC_APCS_CLOCK_BRANCH_ENA_VOTE_ADDR, branch_enable);
   MmioWrite32(GCC_BLSP_UART_APPS_CBCR_ADDR,        0);
   MmioWrite32(GCC_BLSP_UART_APPS_CMD_RCGR_ADDR,    0);
   MmioWrite32(GCC_BLSP_UART_APPS_CFG_RCGR_ADDR,    root_config);
   MmioWrite32(GCC_BLSP_UART_APPS_M_ADDR,           m_reg);
   MmioWrite32(GCC_BLSP_UART_APPS_N_ADDR,           n_reg);
   MmioWrite32(GCC_BLSP_UART_APPS_D_ADDR,           d_reg);
   MmioWrite32(GCC_BLSP_UART_APPS_CMD_RCGR_ADDR,    1);  // UPDATE, begin clock switch
   while( (MmioRead32(GCC_BLSP_UART_APPS_CMD_RCGR_ADDR) & 1) != 0) ;  // wait for switch to complete
   MmioWrite32(GCC_BLSP_UART_APPS_CBCR_ADDR,        1);  // Now enable the branch (and root)
    
}

/*==================================================================================================

FUNCTION: configure_clocks_dragonfly

DESCRIPTION:
   This function enables the peripheral clocks for BLSP/UART.  It also enables the UART core
   clock and sets the input frequency to 1.8432 MHz.

==================================================================================================*/
static void configure_clocks_dragonfly(QDF_CLOCK_CONFIG *cfg)
{
   UINT32 blsp_cbcr;
   UINT32 mode, src_sel, src_div, root_config;
   UINT32 m, n, m_reg, n_reg, d_reg;

   #define GCCSN_BLSP_AHB_CBCR_ADDR        (props->clock_base + cfg->blsp_cbcr)
   #define GCCSN_BLSP_UART_APPS_CBCR_ADDR  (props->clock_base + cfg->uart_cbcr)
   #define GCCSN_BLSP_UART_CMD_RCGR_ADDR   (props->clock_base + cfg->uart_offset + 0x00)
   #define GCCSN_BLSP_UART_CFG_RCGR_ADDR   (props->clock_base + cfg->uart_offset + 0x04)
   #define GCCSN_BLSP_UART_M_ADDR          (props->clock_base + cfg->uart_offset + 0x08)
   #define GCCSN_BLSP_UART_N_ADDR          (props->clock_base + cfg->uart_offset + 0x0C)
   #define GCCSN_BLSP_UART_D_ADDR          (props->clock_base + cfg->uart_offset + 0x10)

   #define GCCSN_BLSP_UART_CFG_RCGR_MODE_SHFT     12
   #define GCCSN_BLSP_UART_CFG_RCGR_SRC_SEL_SHFT   8
   #define GCCSN_BLSP_UART_CFG_RCGR_SRC_DIV_SHFT   0

   blsp_cbcr = MmioRead32(GCCSN_BLSP_AHB_CBCR_ADDR);
   blsp_cbcr |= 1;  // CLK_ENABLE

   mode    = 2;  // dual edge
   src_sel = 0;  // CXO (20,000,000)
   src_div = 0;  // bypass predivider
   root_config = (mode    << GCCSN_BLSP_UART_CFG_RCGR_MODE_SHFT)    |
                 (src_sel << GCCSN_BLSP_UART_CFG_RCGR_SRC_SEL_SHFT) |
                 (src_div << GCCSN_BLSP_UART_CFG_RCGR_SRC_DIV_SHFT);

   // select M/N:D values for BLSP_UART_APPS clock:
   //    input_clock * M / N   = output_clock
   //    20,000,000 * 288 / 3125 = 1,843,200

   m = 288;
   n = 3125;
   m_reg =        m & 0xFFFF;
   n_reg = ~(n - m) & 0xFFFF;
   d_reg =       ~n & 0xFFFF;  // set duty cycle to 0.5 (duty cycle = d / n; d_val = ~(2 * d))

   MmioWrite32(GCCSN_BLSP_AHB_CBCR_ADDR,       blsp_cbcr);
   MmioWrite32(GCCSN_BLSP_UART_CFG_RCGR_ADDR,  root_config);
   MmioWrite32(GCCSN_BLSP_UART_M_ADDR,         m_reg);
   MmioWrite32(GCCSN_BLSP_UART_N_ADDR,         n_reg);
   MmioWrite32(GCCSN_BLSP_UART_D_ADDR,         d_reg);
   MmioWrite32(GCCSN_BLSP_UART_CMD_RCGR_ADDR,  3);  // ROOT_EN and UPDATE
   MmioWrite32(GCCSN_BLSP_UART_APPS_CBCR_ADDR, 1);  // CLK_ENABLE
}

/*==================================================================================================

FUNCTION: configure_clocks_legacy

DESCRIPTION:
   This function enables the peripheral clock for GSBI/UARTDM.  It also enables the UART core
   clock and sets the input frequency to 1.8432 MHz.

==================================================================================================*/
static void configure_clocks_legacy(void)
{
   UINT32 gsbi_number = props->uart_instance;
   UINT32 clock_base = props->clock_base;
   UINT32 src_sel;
   UINT32 m, n;
   UINT32 m_val, n_val, d_val;
   UINT32 md_reg, ns_reg;

   #define GSBIn_HCLK_CTL_ADDR(n)      (clock_base + 0x29c0 + 32 * ((n)-1))
   #define GSBIn_UART_APPS_MD_ADDR(n)  (clock_base + 0x29d0 + 32 * ((n)-1))
   #define GSBIn_UART_APPS_NS_ADDR(n)  (clock_base + 0x29d4 + 32 * ((n)-1))

   #define GSBIn_UART_APPS_MD_M_VAL_SHFT  16

   #define GSBIn_UART_APPS_NS_N_VAL_SHFT           16
   #define GSBIn_UART_APPS_NS_CLK_ROOT_ENA_SHFT    11
   #define GSBIn_UART_APPS_NS_CLK_INV_SHFT         10
   #define GSBIn_UART_APPS_NS_CLK_BRANCH_ENA_SHFT   9
   #define GSBIn_UART_APPS_NS_MNCNTR_EN_SHFT        8
   #define GSBIn_UART_APPS_NS_MNCNTR_RST_SHFT       7
   #define GSBIn_UART_APPS_NS_MNCNTR_MODE_SHFT      5
   #define GSBIn_UART_APPS_NS_PRE_DIV_SEL_SHFT      3
   #define GSBIn_UART_APPS_NS_SRC_SEL_SHFT          0

   // select clock source for GSBIn_UART_APPS clock:
   //    0 =  PXO ( 24,576,000 on 8660 V1 SURF) ( 27,000,000 on 8660 V2 SURF)
   //    1 =  MXO ( 27,000,000 on 8660 V1 SURF) (          0 on 8660 V2 SURF)
   //    3 = PLL8 (384,000,000 on 8660 V1 SURF) (384,000,000 on 8660 V2 SURF)

   src_sel = 3;

   // select M/N:D values for GSBIn_UART_APPS clock:
   //    input_clock * M / N   = output_clock
   //    384,000,000 * 3 / 625 = 1,843,200

   m = 3;
   n = 625;
   m_val =        m & 0xFFFF;
   n_val = ~(n - m) & 0xFFFF;
   d_val =       ~n & 0xFFFF;  // set duty cycle to 0.5 (duty cycle = d / n; d_val = ~(2 * d))

   md_reg = (m_val << GSBIn_UART_APPS_MD_M_VAL_SHFT) | d_val;

   ns_reg = (  n_val << GSBIn_UART_APPS_NS_N_VAL_SHFT)          |
            (      1 << GSBIn_UART_APPS_NS_CLK_ROOT_ENA_SHFT)   |
            (      0 << GSBIn_UART_APPS_NS_CLK_INV_SHFT)        |
            (      1 << GSBIn_UART_APPS_NS_CLK_BRANCH_ENA_SHFT) |
            (      1 << GSBIn_UART_APPS_NS_MNCNTR_EN_SHFT)      |
            (      0 << GSBIn_UART_APPS_NS_MNCNTR_RST_SHFT)     |
            (      2 << GSBIn_UART_APPS_NS_MNCNTR_MODE_SHFT)    |
            (      0 << GSBIn_UART_APPS_NS_PRE_DIV_SEL_SHFT)    |
            (src_sel << GSBIn_UART_APPS_NS_SRC_SEL_SHFT);

   MmioWrite32(GSBIn_HCLK_CTL_ADDR(gsbi_number), 0x10);        // enable GSBI HCLK branch
   MmioWrite32(GSBIn_UART_APPS_MD_ADDR(gsbi_number), md_reg);  // set M_VAL and D_VAL
   MmioWrite32(GSBIn_UART_APPS_NS_ADDR(gsbi_number), ns_reg);  // set N_VAL, enable UART clock
}

/*==================================================================================================

FUNCTION: configure_gsbi

DESCRIPTION:
   This function configures the mode of the selected GSBI as a 4-wire UART.

==================================================================================================*/
static void configure_gsbi(void)
{
   if (props->gsbi_base) { MmioWrite32(props->gsbi_base + 0x00, 0x40); }
}

/*==================================================================================================

FUNCTION: configure_tlmm

DESCRIPTION:
   This function configures the TLMM to route the GPIOs to the GSBI block.

==================================================================================================*/
static void configure_tlmm(void)
{
   if (props->rts) { MmioWrite32(gpio_cfg_addr(props->rts_tlmm_base, props->rts >> 16), props->rts & 0xFFFF); }
   if (props->cts) { MmioWrite32(gpio_cfg_addr(props->cts_tlmm_base, props->cts >> 16), props->cts & 0xFFFF); }
   if (props->rx)  { MmioWrite32(gpio_cfg_addr(props->rx_tlmm_base, props->rx  >> 16), props->rx  & 0xFFFF); }
   if (props->tx)  { MmioWrite32(gpio_cfg_addr(props->tx_tlmm_base, props->tx  >> 16), props->tx  & 0xFFFF); }
}


/*==================================================================================================

FUNCTION: gpio_cfg_addr

DESCRIPTION:
   This function calculates the GPIO_CFGn_ADDR for a given GPIO number.  This is the address
   of the register that is used to configure the GPIO.

==================================================================================================*/
static UINT32 gpio_cfg_addr(UINT32 tlmm_base, UINT32 n)
{
   if (props->family == BEAR || props->family == HONEYBADGER)
   {
      return(tlmm_base + 0x1000 * n);
   }
   else  // The PW is unique for SDM660 so we should not get in the else condition at all.
   {
      return(0x0);
   }
}

/*==================================================================================================

FUNCTION: reg_init

DESCRIPTION:
   This function initializes the UART registers and puts the UART into a known state.

==================================================================================================*/
static void reg_init(void)
{
   UINT32 tx_fifo_words = TX_FIFO_SIZE >> 2;

   MmioWrite32(REG(cr),   UARTDM_CR_ENA_CR_PROT);
   MmioWrite32(REG(cr),   UARTDM_CR_RESET_RFR);  // deassert RTS (active low)
   MmioWrite32(REG(cr),   UARTDM_CR_RESET_RX);
   MmioWrite32(REG(cr),   UARTDM_CR_RESET_TX);
   MmioWrite32(REG(cr),   UARTDM_CR_RESET_ERR);
   MmioWrite32(REG(cr),   UARTDM_CR_RESET_STALE);

   MmioWrite32(REG(mr1),  0);              // disable RTS/CTS flow control
   MmioWrite32(REG(mr2),  0x134);          // set char format to 8N1 and set RX_BREAK_ZERO_CHAR_OFF
   MmioWrite32(REG(csr),  0xFF);           // set dividers to 16 (1,843,200 / 16 = 115200 baud)
   MmioWrite32(REG(imr),  0);              // mask all interrupts
   MmioWrite32(REG(ipr),  0x0F);           // 15 characters (10 x bit time) until stale timeout
   MmioWrite32(REG(tfwr), 0);              // TX FIFO watermark
   MmioWrite32(REG(rfwr), 0);              // RX FIFO watermark
   MmioWrite32(REG(hcr),  0);              // hunt character
   MmioWrite32(REG(irda), 0);              // bypass the IrDA transceiver
   MmioWrite32(REG(dmen), 0);              // disable RX/TX DM interfaces
   MmioWrite32(REG(badr), tx_fifo_words);  // set TX FIFO size to 64 words (256 characters)
   MmioWrite32(REG(sim),  0);              // disable UIM_IF mode of operation

   MmioWrite32(REG(cr),   UARTDM_CR_RESET_RX);  // do this again because we cleared RX_DM_EN
   MmioWrite32(REG(cr),   UARTDM_CR_ENA_RX);    // enable receiver
   MmioWrite32(REG(cr),   UARTDM_CR_ENA_TX);    // enable transmitter
   MmioWrite32(REG(cr),   UARTDM_CR_SET_RFR);   // assert RTS (active low)
}

/*==================================================================================================

FUNCTION: rx_transfer_start

DESCRIPTION:
   This function starts a new RX transfer.

==================================================================================================*/
static void rx_transfer_start(void)
{
   // We must write DMRX (start a new rx transfer) and then CR (enable stale
   // event), in that order.  If we reverse this order it is possible to get
   // a stale interrupt without a corresponding update to the SNAP register.

   MmioWrite32(REG(dmrx), RX_XFER_SIZE);
   MmioWrite32(REG(cr),   UARTDM_CR_ENA_STALE_EVT);

   rx_bytes_left = RX_XFER_SIZE;
}

/*==================================================================================================

FUNCTION: service_rx_fifo

DESCRIPTION:
   This function moves data out of the RX FIFO into our ring buffer.  It also processes any
   stale events and starts new RX transfers as needed.

==================================================================================================*/
static void service_rx_fifo(void)
{
   UINT32 rxfs, isr, snap;
   UINT32 words_in_fifo;
   UINT32 bytes_to_copy;
   UINT32 valid_bytes;  // valid bytes in the next RXFIFO slot (1 to 4)
   UINT32 fifo_word;
   UINT32 i;

   // The following call to rx_transfer_start() will only occur the first time a client
   // calls uart_poll() or uart_read().  We are relying on the assumption that
   // only one client will call these APIs.

   if (rx_bytes_left == 0) { rx_transfer_start(); }

   while (1)  // loop until RXFIFO is empty or ring buffer is full
   {
      // The order of these two register reads is important (ISR must be read last) due to
      // the possibility of a stale event occurring between them.  If we reversed the order
      // we might incorrectly assume there are 4 valid bytes in the RX FIFO slot that was
      // filled after a stale event.

      rxfs = MmioRead32(REG(rxfs));
      isr  = MmioRead32(REG(isr));

      // A stale event will occur under two conditions:
      //
      // 1) At least one byte has been received and then a gap has been detected in the
      //    incoming byte stream equal to the time specified in the IPR.
      //
      // 2) All the characters specified in DMRX have been received.  This will immediately
      //    trigger a stale event even if the incoming byte stream continues without a gap.
      //
      // In both cases the SNAP register will be updated with a snapshot of the incoming
      // byte counter and the ISR_RXSTALE bit will be set.

      if (isr & UARTDM_ISR_RXSTALE)
      {
         MmioWrite32(REG(cr), UARTDM_CR_RESET_STALE);  // clear ISR_RXSTALE
         snap = MmioRead32(REG(snap));
         rx_bytes_left -= (RX_XFER_SIZE - snap);  // rx_bytes_left should be nonzero
                                                  // due to the precautions taken below
      }

      // HW bug: If the packing buffer and the RXFIFO are both empty when a stale event
      // occurs then the SNAP register will be updated but the ISR_RXSTALE bit will not be
      // set and future stale events will not be detected.  To avoid this scenario we must
      // make sure we do not empty the RXFIFO unless we are at the end of an RX transfer.

      words_in_fifo  = (rxfs & UARTDM_RXFS_FIFO_STATE_MSB_MASK) >> UARTDM_RXFS_FIFO_STATE_MSB_SHIFT;
      words_in_fifo |= (rxfs & UARTDM_RXFS_FIFO_STATE_LSB_MASK) >> UARTDM_RXFS_FIFO_STATE_LSB_SHIFT;

      if (words_in_fifo == 0)
      {
         bytes_to_copy = 0;
      }
      else if ( (words_in_fifo * 4) < rx_bytes_left )
      {
         bytes_to_copy = (words_in_fifo - 1) * 4;  // leave one slot full due to HW bug
      }
      else
      {
         bytes_to_copy = rx_bytes_left;
      }

      if ( ROOM_IN_RING() < bytes_to_copy )
      {
         bytes_to_copy = ROOM_IN_RING() & ~0x3;  // no partial words
      }

      if (bytes_to_copy == 0) { break; }

      while (bytes_to_copy)
      {
         valid_bytes = (bytes_to_copy < 4) ? (bytes_to_copy) : (4);
         fifo_word = MmioRead32(REG(rf));

         for (i = 0; i < valid_bytes; i++) { RING_PUT_BYTE((UINT8)(fifo_word >> i * 8)); }
         bytes_to_copy -= valid_bytes;
         rx_bytes_left -= valid_bytes;
      }

      if (rx_bytes_left == 0) { rx_transfer_start(); }
   }
}

/*==================================================================================================

FUNCTION: transmit_data

DESCRIPTION:
   This function attempts to transmit the requested number of bytes.  It returns the number of
   bytes successfully sent.

==================================================================================================*/
static UINT32 transmit_data(UINT8 *user_buffer, UINT32 bytes_to_send)
{
   UINT8 *ptr = user_buffer;
   UINT32 num_bytes;
   UINT32 tx_bytes_left;
   UINT32 fifo_word;
   UINT32 valid_bytes;  // number of bytes to write to the next TXFIFO slot (1 to 4)
   UINT32 i;

   if (bytes_to_send == 0) { return 0; }  // nothing to send
   if ((MmioRead32(REG(isr)) & UARTDM_ISR_TXLEV) == 0) { return 0; } // previous xfer in progress

   num_bytes = (bytes_to_send > TX_FIFO_SIZE) ? (TX_FIFO_SIZE) : (bytes_to_send);
   tx_bytes_left = num_bytes;

   MmioWrite32(REG(ncft), num_bytes);

   while (tx_bytes_left)
   {
      fifo_word = 0;
      valid_bytes = (tx_bytes_left < 4) ? (tx_bytes_left) : (4);
      for (i = 0; i < valid_bytes; i++) { fifo_word |= *ptr++ << i * 8; }

      MmioWrite32(REG(tf), fifo_word);
      tx_bytes_left -= valid_bytes;
   }

   return(num_bytes);
}

/*==================================================================================================
                                          GLOBAL FUNCTIONS
==================================================================================================*/
/*==================================================================================================

FUNCTION: uart_initialize

DESCRIPTION:

==================================================================================================*/
RETURN_STATUS EFIAPI
uart_initialize(void)
{
   props = uart_get_properties();
   if (props == NULL) { return RETURN_UNSUPPORTED; }

   configure_clocks();  // must be done before touching GSBI or UARTDM registers
   configure_gsbi();
   configure_tlmm();
   reg_init();

   return RETURN_SUCCESS;
}

/*==================================================================================================

FUNCTION: uart_poll

DESCRIPTION:

==================================================================================================*/
BOOLEAN EFIAPI
uart_poll(void)
{
   if (props == NULL) { props = uart_get_properties(); }
   if (props == NULL) { return FALSE; }

   service_rx_fifo();
   return( BYTES_IN_RING() > 0 );
}

/*==================================================================================================

FUNCTION: uart_read

DESCRIPTION:

==================================================================================================*/
UINTN EFIAPI
uart_read(OUT UINT8 *user_buffer, IN UINTN bytes_requested)
{
   UINT8 *ptr = user_buffer;
   UINT32 room_avail = (UINT32)bytes_requested;
   UINT32 bytes_read = 0;
   UINT32 bytes_avail;
   UINT32 num_bytes;
   UINT32 i;

   if (props == NULL) { props = uart_get_properties(); }
   if (props == NULL) { return 0; }

   while (1)  // loop until user buffer is full or no more bytes are available
   {
      service_rx_fifo();
      bytes_avail = BYTES_IN_RING();
      num_bytes = (room_avail < bytes_avail) ? (room_avail) : (bytes_avail);
      if (num_bytes == 0) { break; }
      for (i = 0; i < num_bytes; i++) { *ptr++ = RING_GET_BYTE(); }
      bytes_read += num_bytes;
      room_avail -= num_bytes;
   }

   return(bytes_read);
}

/*==================================================================================================

FUNCTION: uart_write

DESCRIPTION:

==================================================================================================*/
UINTN EFIAPI
uart_write(IN UINT8 *user_buffer, IN UINTN bytes_to_send)
{
   UINT32 bytes_sent;

   if (props == NULL) { props = uart_get_properties(); }
   if (props == NULL) { return 0; }

   bytes_sent = transmit_data(user_buffer, (UINT32)bytes_to_send);

   return(bytes_sent);
}


/*================================================================================================
    
FUNCTION: uart_rxBreakonDetection

DESCRIPTION: Check Break Detection Condition
            
================================================================================================*/
BOOLEAN EFIAPI
uart_rxBreakonDetected(void)
{
   return ((MmioRead32(REG(sr)) & UARTDM_SR_RX_START_LAST) != 0);
}
