/*==================================================================================================

FILE: qdi_uart.c

DESCRIPTION: Defines the interface and functionality of a QDI Driver for the needed UART functions 
while in the micro image. 

                     Copyright (c) 2015 Qualcomm Technologies Incorporated
                                        All Rights Reserved
                                     QUALCOMM Proprietary/GTDR

==================================================================================================*/

/*==================================================================================================
                                           INCLUDE FILES
==================================================================================================*/
#include "qdi_uart.h"

/*==================================================================================================
                                              TYPEDEFS               
==================================================================================================*/
typedef struct
{
   qurt_qdi_obj_t obj;
} QDI_UART_opener;

typedef struct
{
   qurt_qdi_obj_t obj;
   UartHandle handle;
   UartPortID port_id;
   EventCbCtxt *cb_ctxt;
} QDI_UART;

/*==================================================================================================
                                     LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

static int QDI_UART_invocation(int client_handle, qurt_qdi_obj_t *obj, int method,
                               qurt_qdi_arg_t a1, qurt_qdi_arg_t a2, qurt_qdi_arg_t a3,
                               qurt_qdi_arg_t a4, qurt_qdi_arg_t a5, qurt_qdi_arg_t a6,
                               qurt_qdi_arg_t a7, qurt_qdi_arg_t a8, qurt_qdi_arg_t a9);

static void QDI_UART_release(qurt_qdi_obj_t *obj);

static void thread_cb(UartEvent ue, uint32 num_bytes, void *cb_data);

/*==================================================================================================
                                             LOCAL VARIABLES
==================================================================================================*/

static QDI_UART_opener opener = 
{
   {QDI_UART_invocation,
    QDI_REFCNT_PERM,
    QDI_UART_release
   }
};

qurt_signal_t *sensor_sig_obj = NULL;

static QDI_UART qdi_uart_handles[UART_MAX_PORTS];

/*==================================================================================================
                                             LOCAL FUNCTIONS
==================================================================================================*/
/*==================================================================================================
 
FUNCTION: QDI_UART_invocation
 
DESCRIPTION: function to handle calling all necessary functions in the Root PD
 
==================================================================================================*/
static int QDI_UART_invocation(int client_handle, qurt_qdi_obj_t *obj, int method,
                               qurt_qdi_arg_t a1, qurt_qdi_arg_t a2, qurt_qdi_arg_t a3,
                               qurt_qdi_arg_t a4, qurt_qdi_arg_t a5, qurt_qdi_arg_t a6,
                               qurt_qdi_arg_t a7, qurt_qdi_arg_t a8, qurt_qdi_arg_t a9)
{

   QDI_UART *uart_obj = (QDI_UART *) obj;
   switch (method)
   {
   case QDI_OPEN:
      //allocate our struct
      uart_obj = &qdi_uart_handles[a2.num];
      //set up our functions
      uart_obj->obj.invoke = QDI_UART_invocation;
      uart_obj->obj.refcnt = QDI_REFCNT_INIT;
      uart_obj->obj.release = QDI_UART_release;
      //store cb_txt and port id for use in thread callback
      uart_obj->port_id = a2.num;
      uart_obj->cb_ctxt = a3.ptr;
      //call root init function
      if (Uart_init(&uart_obj->handle, (UartPortID) a2.num) != UART_ERROR)
      {
         //return our new qdi handle to the sensor PD. second argument expects a pointer to the
         //qdi_obj. since this is the first thing in our struct, we just handle it the struct pointer
         //cast to the appropriate type
         return qurt_qdi_handle_create_from_obj_t(client_handle, (qurt_qdi_obj_t *) uart_obj);
      }
      else
      {
         //don't free the struct. let deinit function handle that in error case for uart_init fcn
         return -1;
      }
   case QDI_CLOSE:
      return Uart_deinit(uart_obj->handle);
   case UART_TRANSMIT:
      return Uart_transmit(uart_obj->handle, a1.ptr, (uint32) a2.num);
   case UART_RECEIVE:
      return Uart_receive(uart_obj->handle, a1.ptr, (uint32) a2.num);
   case UART_REG_CB:
      if (sensor_sig_obj == NULL)
      {
         sensor_sig_obj = a1.ptr;
      }
      if (Uart_register_event_callback(uart_obj->handle, thread_cb, uart_obj) != UART_SUCCESS)
      {
         return -1;
      }
      else
      {
         return 0;
      }
   default:
      return qurt_qdi_method_default(client_handle, obj, method, a1, a2, a3, a4, a5, a6,
                                     a7, a8, a9);
   }
}

/*==================================================================================================
 
FUNCTION: QDI_UART_release
 
DESCRIPTION: Free resources used by the QDI structs
 
==================================================================================================*/
static void QDI_UART_release(qurt_qdi_obj_t *obj)
{
}

/*==================================================================================================
 
FUNCTION: thread_cb
 
DESCRIPTION: callback function registered with the underlying UART code to be called when interrupts 
are received. simply records which event has occured, the number of bytes available in our buffer, 
and signals the worker thread which UART needs its interrupt serviced in the Sensor PD
 
==================================================================================================*/
static void thread_cb(UartEvent ue, uint32 num_bytes, void *cb_data)
{
   QDI_UART *uart_obj = (QDI_UART *) cb_data;
   //store event and number of bytes available for the client callback to use
   uart_obj->cb_ctxt->intr_event = ue;
   uart_obj->cb_ctxt->bytes_available = num_bytes;
   //send worker thread the signal corresponding to the uart that needs servicing
   qurt_signal_set(sensor_sig_obj, 1 << (uint32) uart_obj->port_id);
}

/*==================================================================================================
                                             GLOBAL FUNCTIONS
==================================================================================================*/
/*==================================================================================================
 
FUNCTION: qdi_uart_init
 
DESCRIPTION: Registers the UART QDI driver
 
==================================================================================================*/
void qdi_uart_init()
{
  qurt_qdi_register_devname("uart", &opener);
}
