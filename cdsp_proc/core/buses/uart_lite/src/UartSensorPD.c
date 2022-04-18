/*==================================================================================================

FILE: Uart.c

DESCRIPTION: This module provides the driver Software for the UART.

Copyright (c) 2013-2016 Qualcomm Technologies, Inc.
        All Rights Reserved.
Qualcomm Technologies, Inc. Confidential and Proprietary.

==================================================================================================*/
/*==================================================================================================
                                            DESCRIPTION
====================================================================================================

GLOBAL FUNCTIONS:
   Uart_Deinit
   Uart_Init
   Uart_Receive
   Uart_Transmit

==================================================================================================*/
/*==================================================================================================
Edit History

$Header: //components/rel/core.qdsp6/1.0.c2/buses/uart_lite/src/UartSensorPD.c#1 $

==================================================================================================*/

/*==================================================================================================
                                           INCLUDE FILES
==================================================================================================*/
#include "Uart.h"
#include "Uart_log.h"
#include "qdi_uart.h"
#include "err.h"

/*==================================================================================================
                                              TYPEDEFS
==================================================================================================*/
typedef struct
{
   DALDEVICEHANDLE      dal_device_handle;
   DALSYSWorkLoopHandle workloop_handle;
   DALSYSEventHandle    event_handle;
   UART_CALLBACK        client_cb;
   void                *client_cb_data;
   uint32               bytes_available;
   EventCbCtxt          cb_ctxt;
} UART_SENSOR_CONTEXT;

typedef struct
{
   UartHandle           handle;
   UART_SENSOR_CONTEXT *sensor_ctxt;
} UART_NODE;

/*==================================================================================================
                                          LOCAL VARIABLES
==================================================================================================*/
#define UART_LOGGING_FILE_ID 30
#define MAX_ID_LENGTH        40
#define MAX_PORTS            3
#define THREAD_STACK_SIZE    1024
#define STACK_ALIGNMENT      8

static UART_NODE uart_status_list[MAX_PORTS] = {
                                                {0, NULL}
                                               };

UART_SENSOR_CONTEXT uart_sensor_handles[MAX_PORTS];

static qurt_signal_t interrupt_sig;

static char interrupt_thread_stack[THREAD_STACK_SIZE + STACK_ALIGNMENT - 1];

/*==================================================================================================
                                     LOCAL FUNCTION PROTOTYPES
==================================================================================================*/
static UartResult get_sensor_context(UartHandle h, UART_SENSOR_CONTEXT **ptr);
static void       thread_main(void *unused);

/*==================================================================================================
                                          LOCAL FUNCTIONS
==================================================================================================*/
/*==================================================================================================
 
FUNCTION: get_sensor_context
 
DESCRIPTION: stores the pointer to the sensor context struct in the location pointed to by ptr
 
==================================================================================================*/
static UartResult get_sensor_context(UartHandle h, UART_SENSOR_CONTEXT **ptr)
{
   uint32 i;
   for (i = 0; i < MAX_PORTS; i++)
   {
      if (uart_status_list[i].handle == h)
      {
         *ptr = uart_status_list[i].sensor_ctxt;
         return UART_SUCCESS;
      }
   }
   return UART_ERROR;
}

/*==================================================================================================
 
FUNCTION: thread_main
 
DESCRIPTION: main function for our worker thread. waits to be signaled that an interrupt has 
happened, and then calls the appropriate callback 
 
==================================================================================================*/
static void thread_main(void *unused)
{
   uint32 sig_mask;
   uint32 i;

   sig_mask = 0;
   for (i = 0; i < MAX_PORTS; i++)
   {
      sig_mask |= 1 << i;
   }

   while (1)
   {
      uint32 rec_sig = qurt_signal_wait_any(&interrupt_sig, sig_mask);
      uint32 i;
      //check to see which uart needs to be serviced
      for (i = 0; i < MAX_PORTS; i++)
      {
         if (rec_sig & 1 << i)
         {
            qurt_signal_clear(&interrupt_sig, 1 << i);
            //call client callback and clear the signal
            UART_SENSOR_CONTEXT *uart_ctxt = uart_status_list[i].sensor_ctxt;
            uart_ctxt->client_cb(uart_ctxt->cb_ctxt.intr_event, uart_ctxt->cb_ctxt.bytes_available,
                                 uart_ctxt->client_cb_data);
         }
      }
   }
}

/*==================================================================================================
                                          GLOBAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================

FUNCTION: Uart_spawn_thread

DESCRIPTION: init function for the driver used by the RC_INIT function

==================================================================================================*/
void Uart_spawn_thread()
{
   int result;
   char *addr;
   qurt_thread_attr_t attr;
   qurt_thread_t tid;
   qurt_thread_attr_init(&attr);
   qurt_thread_attr_set_name(&attr, "uart interrupt thread");
   qurt_thread_attr_set_stack_size(&attr, THREAD_STACK_SIZE);

   //force stack alignment to 8 byte boundry, per QURT thread specs.

   //make sure aligned address will fall inside our allocated stack
   addr = (char *)((unsigned long long) interrupt_thread_stack + STACK_ALIGNMENT - 1);
   //align to 8 byte boundary
   addr = (char *)((unsigned long long) addr & ~(STACK_ALIGNMENT - 1));
   
   qurt_thread_attr_set_stack_addr(&attr, addr);
   qurt_signal_init(&interrupt_sig);
   result = qurt_thread_create(&tid, &attr, thread_main, NULL);
   if (result != QURT_EOK)
   {
      ERR_FATAL("uart interrupt thread creation failed", 0, 0, 0);
   }
}

/*==================================================================================================

FUNCTION: Uart_deinit

DESCRIPTION:

==================================================================================================*/
UartResult Uart_deinit(UartHandle h)
{
  UART_SENSOR_CONTEXT *uart_ctxt = NULL;

   if (NULL == h)
   {
      UART_LOG_0(ERROR,"Calling Uart_deinit with a NULL handle.");
      return UART_ERROR;
   }

   if (get_sensor_context(h, &uart_ctxt) != UART_SUCCESS)
   {
      return UART_ERROR;
   }

   //close uart connection w/qdi driver
   if (qurt_qdi_close((int) h) < 0)
   {
      return UART_ERROR;
   }

   return UART_SUCCESS;
}

/*==================================================================================================

FUNCTION: Uart_init

DESCRIPTION:

==================================================================================================*/
UartResult Uart_init(UartHandle *h, UartPortID id)
{
   UART_SENSOR_CONTEXT *uart_ctxt = NULL;
 
   if (NULL == h)
   {
      UART_LOG_0(ERROR,"Calling Uart_init with a NULL handle.");
      goto error;
   }

   if (id >= MAX_PORTS)
   {
      UART_LOG_0(ERROR,"Calling Uart_init with a invalid device id.");
      goto error;
   }

   uart_ctxt = &uart_sensor_handles[id];

   memset(uart_ctxt, 0, sizeof(UART_SENSOR_CONTEXT));
   
   int handle = qurt_qdi_open("uart", id, &uart_ctxt->cb_ctxt);
   if (handle < 0)
   {
      *h = (UartHandle) -1;
      goto error;
   }
   else
   {
      *h = (UartHandle) handle;
   }

   //store sensor context for later use in callback
   uart_status_list[id].handle = *h;
   uart_status_list[id].sensor_ctxt = uart_ctxt;

   return UART_SUCCESS;

error:
   Uart_deinit(uart_ctxt);
   return UART_ERROR;
}

/*==================================================================================================

FUNCTION: Uart_receive

DESCRIPTION:

==================================================================================================*/
uint32 Uart_receive(UartHandle h, char *buf, uint32 bytes_to_rx)
{
   uint32 bytes_read;

   UART_LOG_0(INFO,"+Uart_receive");

   if (NULL == h)
   {
      UART_LOG_0(ERROR,"Calling Uart_receive with a NULL handle.");
      return 0;
   }

   bytes_read = qurt_qdi_handle_invoke((int) h, UART_RECEIVE, buf, bytes_to_rx);

   UART_LOG_0(INFO,"-Uart_receive");

   return bytes_read;
}


/*==================================================================================================

FUNCTION: Uart_register_callback

DESCRIPTION:

==================================================================================================*/
UartResult Uart_register_event_callback(UartHandle h, UART_CALLBACK client_callback, void *cb_data)
{
   UART_SENSOR_CONTEXT *uart_ctxt;
   
   if (NULL == h)
   {
      UART_LOG_0(ERROR,"Calling Uart_register_callback with a NULL handle");
      return UART_ERROR;
   }

   if (NULL == client_callback)
   {
      UART_LOG_0(ERROR,"Calling Uart_register_callback with a NULL callback function");
      return UART_ERROR;
   }

   if (get_sensor_context(h, &uart_ctxt) != UART_SUCCESS)
   {
      return UART_ERROR;
   }

   uart_ctxt->client_cb      = client_callback;
   uart_ctxt->client_cb_data = cb_data;

   if (qurt_qdi_handle_invoke((int) h, UART_REG_CB, &interrupt_sig) < 0)
   {
      return UART_ERROR;
   }

   return UART_SUCCESS;
}


/*==================================================================================================

FUNCTION: Uart_transmit

DESCRIPTION:

==================================================================================================*/
uint32 Uart_transmit(UartHandle h, char *buf, uint32 bytes_to_tx)
{
   uint32 bytes_sent = 0;

   if (NULL == h)
   {
      UART_LOG_0(ERROR,"Calling Uart_transmit with a NULL handle.");
      return 0;
   }
   if (NULL == buf)
   {
      UART_LOG_0(ERROR,"Calling Uart_transmit with a NULL buffer.");
      return 0;
   }

   UART_LOG(INFO, "+Uart_transmit");

   bytes_sent = qurt_qdi_handle_invoke((int) h, UART_TRANSMIT, buf, bytes_to_tx);

   UART_LOG(INFO, "-Uart_transmit");

   return bytes_sent;
}
