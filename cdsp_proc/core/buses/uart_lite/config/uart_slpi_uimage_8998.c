/*==================================================================================================

FILE: uart_slpi_uimage_[target].c

DESCRIPTION: This module provides the os based functionalities for the UART.

Copyright (c) 2009-2015 Qualcomm Technologies, Inc.
        All Rights Reserved.
Qualcomm Technologies, Inc. Confidential and Proprietary.

==================================================================================================*/
/*==================================================================================================
                                            DESCRIPTION
====================================================================================================


==================================================================================================*/
/*==================================================================================================
Edit History

$Header: //components/rel/core.qdsp6/1.0.c2/buses/uart_lite/config/uart_slpi_uimage_8998.c#1 $

when       who     what, where, why
--------   --------     -------------------------------------------------------- 
08/12/15   stranche     Added irq numbers to structs
01/26/15   VV      Initial revision.

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
      0x05EAF000,  // uart_base         
      115200,      // bit_rate
      0,           // is_loopback
      0x2001C0C1,  // gpio_tx_config
      0x200080D1,  // gpio_rx_config
      0,           // gpio_cts_config
      0,           // gpio_rfr_config
      0,           // clock_id_index 
      (void*)CLOCK_SCC_BLSP_H_CLK,        // bus_clock_id
      (void*)CLOCK_SCC_UART_DM_UART1_CLK, // core_clock_id
      100000000,   // base_freq;
      22,          // irq number
   },
   {
      // SECOND_PORT
      0x05EB0000,  // uart_base         
      115200,      // bit_rate
      0,           // is_loopback
      0x2001C0E1,  // gpio_tx_config
      0x200080F1,  // gpio_rx_config
      0,           // gpio_cts_config
      0,           // gpio_rfr_config
      0,           // clock_id_index 
      (void*)CLOCK_SCC_BLSP_H_CLK,        // bus_clock_id
      (void*)CLOCK_SCC_UART_DM_UART2_CLK, // core_clock_id
      100000000,   // base_freq;
      23,          // irq number
   },
   {
      // THIRD_PORT
      0x05EB1000,  // uart_base         
      115200,      // bit_rate
      0,           // is_loopback
      0x2001C061,  // gpio_tx_config
      0x20008071,  // gpio_rx_config
      0,           // gpio_cts_config
      0,           // gpio_rfr_config
      0,           // clock_id_index 
      (void*)CLOCK_SCC_BLSP_H_CLK,        // bus_clock_id
      (void*)CLOCK_SCC_UART_DM_UART3_CLK, // core_clock_id
      100000000,   // base_freq;
      24           // irq number
   }
};
