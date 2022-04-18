#include "Uart.h"
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

#define WAIT_FOR_RCV_DATA_QTY 1024

static UartHandle serial_port;
static uint32 test_results = 0;
static char msg[] = "TX works!!!TX works!!!TX works!!!TX works!!!TX works!!!TX works!!!\r\n";
static uint32 index, bytes_rcvd;

void uartlite_test_callback(UartEvent ue, uint32 num_bytes, void *cb_data)
{
   uint32 bytes_rcvd = Uart_receive(serial_port, msg, sizeof(msg));
   if (bytes_rcvd < num_bytes)
   {
      test_results |= (1 << 4);
   }

   index += bytes_rcvd;
}

void uartlite_test(void)
{   
   uint32 num_bytes;

   for (index=0; index<100; index++) {
      if (UART_SUCCESS != Uart_init(&serial_port, UART_MAIN_PORT)) 
      {
         test_results |= (1 << 0);
      }
      else
      {
         if (UART_SUCCESS != Uart_deinit(serial_port))
         {
            test_results |= (1 << 31);
         }
      }
   }

   if (UART_SUCCESS != Uart_init(&serial_port, UART_MAIN_PORT)) 
   {
      test_results |= (1 << 0);
   }

   for (index=0; index<100; index++) {
      if (strlen(msg) != (num_bytes = Uart_transmit(serial_port, msg, strlen(msg)))) 
      {
         test_results |= (1 << 1);
      }
   }

   if (UART_SUCCESS != Uart_register_event_callback(serial_port, uartlite_test_callback, &serial_port))
   {
      test_results |= (1 << 3);
   }

   bytes_rcvd = 0;
   while (bytes_rcvd < WAIT_FOR_RCV_DATA_QTY) { ;}

   if (UART_SUCCESS != Uart_deinit(serial_port))
   {
      test_results |= (1 << 31);
   }

   assert(test_results == 0);
}

