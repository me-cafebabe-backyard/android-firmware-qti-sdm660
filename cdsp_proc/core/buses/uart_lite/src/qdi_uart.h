/*==================================================================================================

FILE: qdi_uart.h

DESCRIPTION: Defines the interface and functionality of a QDI Driver for the needed UART functions 
while in the micro image. 

                     Copyright (c) 2015 Qualcomm Technologies Incorporated
                                        All Rights Reserved
                                     QUALCOMM Proprietary/GTDR

==================================================================================================*/

/*==================================================================================================
                                           INCLUDE FILES
==================================================================================================*/
#include "qurt.h"
#include "DalDevice.h"
#include "DALSys.h"
#include "Uart.h"
#include "qurt_qdi_driver.h"
#include "err.h"

/*==================================================================================================
                                             CONSTANTS
==================================================================================================*/
#define UART_TRANSMIT  (0 + QDI_PRIVATE)
#define UART_RECEIVE   (1 + QDI_PRIVATE)
#define UART_REG_CB    (2 + QDI_PRIVATE)

/*==================================================================================================
                                             TYPEDEFS
==================================================================================================*/

typedef struct
{
   DALSYSEventHandle  cb_event;
   uint32             bytes_available; 
   UartEvent          intr_event;
} EventCbCtxt;
