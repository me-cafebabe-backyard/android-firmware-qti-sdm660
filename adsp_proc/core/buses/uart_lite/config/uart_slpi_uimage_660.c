/*==================================================================================================

FILE: uart_slpi_uimage_[target].c

DESCRIPTION: This module provides the os based functionalities for the UART.

Copyright (c) 2016 Qualcomm Technologies, Inc.
        All Rights Reserved.
Qualcomm Technologies, Inc. Confidential and Proprietary.

==================================================================================================*/
/*==================================================================================================
                                            DESCRIPTION
====================================================================================================


==================================================================================================*/
/*==================================================================================================
Edit History

$Header: //components/rel/core.qdsp6/1.0.c2/buses/uart_lite/config/uart_slpi_uimage_660.c#1 $

when       who     what, where, why
--------   --------     -------------------------------------------------------- 
01/26/15   RC           Initial revision.

==================================================================================================*/

/*-------------------------------------------------------------------------
* Include Files
* ----------------------------------------------------------------------*/
#include "Uart.h"
#include "Uart_defs.h"
#include "uClock.h"

UART_PROPERTIES devices[UART_MAX_PORTS] =
{
   {
      // MAIN_PORT
      0x1542F000,  // uart_base         
      115200,      // bit_rate
      0,           // is_loopback
      0x0001C0C1,  // gpio_tx_config
      0x000080D1,  // gpio_rx_config
      0,           // gpio_cts_config
      0,           // gpio_rfr_config
      0,           // clock_id_index 
      (void*)CLOCK_SCC_BLSP_H_CLK,        // bus_clock_id
      (void*)CLOCK_SCC_UART_DM_UART1_CLK, // core_clock_id
      100000000,   // base_freq;
      178,          // irq number
   },
   {
      // SECOND_PORT
      0x15430000,  // uart_base         
      115200,      // bit_rate
      0,           // is_loopback
      0x0001C0E1,  // gpio_tx_config
      0x000080F1,  // gpio_rx_config
      0,           // gpio_cts_config
      0,           // gpio_rfr_config
      0,           // clock_id_index 
      (void*)CLOCK_SCC_BLSP_H_CLK,        // bus_clock_id
      (void*)CLOCK_SCC_UART_DM_UART2_CLK, // core_clock_id
      100000000,   // base_freq;
      179,          // irq number
   },
   {
      // THIRD_PORT
      0x15431000,  // uart_base         
      115200,      // bit_rate
      0,           // is_loopback
      0x0001C061,  // gpio_tx_config
      0x00008071,  // gpio_rx_config
      0,           // gpio_cts_config
      0,           // gpio_rfr_config
      0,           // clock_id_index 
      (void*)CLOCK_SCC_BLSP_H_CLK,        // bus_clock_id
      (void*)CLOCK_SCC_UART_DM_UART3_CLK, // core_clock_id
      100000000,   // base_freq;
      180,           // irq number
   },
   {
      // FOURTH_PORT
      0x15432000,  // uart_base         
      115200,      // bit_rate
      0,           // is_loopback
      0x0001C106,  // gpio_tx_config
      0x00008116,  // gpio_rx_config
      0,           // gpio_cts_config
      0,           // gpio_rfr_config
      0,           // clock_id_index 
      (void*)CLOCK_SCC_BLSP_H_CLK,        // bus_clock_id
      (void*)CLOCK_SCC_UART_DM_UART4_CLK, // core_clock_id
      100000000,   // base_freq;
      181,           // irq number
   },
};
