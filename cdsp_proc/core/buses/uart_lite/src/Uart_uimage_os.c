/*==================================================================================================

FILE: Uart_os.c

DESCRIPTION: This module provides the os based functionalities for the UART.

Copyright (c) 2009-2015 Qualcomm Technologies, Inc.
        All Rights Reserved.
Qualcomm Technologies, Inc. Confidential and Proprietary.

==================================================================================================*/
/*==================================================================================================
                                            DESCRIPTION
====================================================================================================

GLOBAL FUNCTIONS:
   Uart_busy_wait
   Uart_clock_open
   Uart_clock_close
   Uart_get_driver_properties
   Uart_get_properties
   Uart_interrupt_close
   Uart_interrupt_done
   Uart_interrupt_open
   Uart_tlmm_open
   Uart_tlmm_close
   Uart_busy_wait

==================================================================================================*/
/*==================================================================================================
Edit History

$Header: //components/rel/core.qdsp6/1.0.c2/buses/uart_lite/src/Uart_uimage_os.c#1 $

when       who     what, where, why
--------   ---     --------------------------------------------------------
09/25/13   VV      Initial revision.

==================================================================================================*/

/*-------------------------------------------------------------------------
* Include Files
* ----------------------------------------------------------------------*/
#include "DALSys.h"
#include "Uart_os.h"
#include "Uart.h"
#include "Uart_defs.h"
#include "Uart_log.h"
#include "uClock.h"
#include "busywait.h"
#include "string.h"
#include "uTlmm.h"
#include "DDIHWIO.h"
#include "DALDeviceId.h"
#include "DDIInterruptController.h"
#include "DDIChipInfo.h"
#include "qurt_island.h"

extern UART_DRIVER_PROPERTIES uart_driver_props;
extern UART_PROPERTIES devices[UART_MAX_PORTS];
static DalDeviceHandle *dal_hwio = NULL;

#define UART_LOGGING_FILE_ID 40

/*==================================================================================================
                                              TYPEDEFS
==================================================================================================*/
typedef struct
{
   DalDeviceHandle* dal_interrupt_handle;
   uint32  irq_num;
   uint32* uart_tcsr_addr;
   uint32  tcsr_mask;
}UART_INTERRUPT_CONTEXT;

/*==================================================================================================
                                          GLOBAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================

FUNCTION: Uart_busy_wait

DESCRIPTION:

==================================================================================================*/
void Uart_busy_wait(uint32 usecs)
{
   busywait(usecs);
}

/*==================================================================================================

FUNCTION: Uart_clock_close

DESCRIPTION:

==================================================================================================*/
UartResult Uart_clock_close(UART_CONTEXT* h)
{
   boolean            clock_result;
   UartResult         result = UART_SUCCESS;


   UART_LOG_0(INFO,"+Uart_clock_close");

   // Disable the Uart core clock.
   clock_result = uClock_DisableClock((uClockIdType)h->properties.core_clock_id);
   if (clock_result != TRUE)
   {
      UART_LOG_0(ERROR, "DalClock_DisableClock for uart core clock failed.");
      result = UART_ERROR;
   }

   // Disable the AHB clock.
   clock_result = uClock_DisableClock((uClockIdType)h->properties.bus_clock_id);
   if (clock_result != TRUE)
   {
      UART_LOG_0(ERROR, "DalClock_DisableClock for AHB clock failed.");
      result = UART_ERROR;
   }

   UART_LOG_0(INFO,"-Uart_clock_close");
   return result;
}

/*==================================================================================================

FUNCTION: Uart_clock_open

DESCRIPTION:

==================================================================================================*/
UartResult Uart_clock_open(UART_CONTEXT* h, uint32 input_freq)
{
   boolean         result;

   UART_LOG_0(INFO, "+Uart_clock_open");

   result = uClock_SetClockFrequency((uClockIdType)h->properties.core_clock_id, input_freq);
   if (result != TRUE)
   {
      UART_LOG_0(ERROR, "Core clock - uClock_SetClockFrequency failed");
      return UART_ERROR;
   }

   // Enable both the UART and AHB clocks
   result = uClock_EnableClock((uClockIdType)h->properties.core_clock_id);
   if (result != TRUE)
   {
      UART_LOG_0(ERROR, "Core clock - uClock_EnableClock failed");
      return UART_ERROR;
   }

   result = uClock_EnableClock((uClockIdType)h->properties.bus_clock_id);
   if (result != TRUE)
   {
      UART_LOG_0(ERROR, "Bus clock - uClock_EnableClock failed");
      return UART_ERROR;
   }

   UART_LOG_0(INFO, "-Uart_clock_open");
   return UART_SUCCESS;

}

/*==================================================================================================

FUNCTION: Uart_get_driver_propertiess

DESCRIPTION:

==================================================================================================*/
UartResult Uart_get_driver_properties( void )
{

   UART_LOG_0(INFO, "+Uart_get_driver_properties");

   uart_driver_props.device_names[UART_MAIN_PORT]   = "Main_port";
   uart_driver_props.device_names[UART_SECOND_PORT] = "Second_port";
   uart_driver_props.device_names[UART_THIRD_PORT]  = "Third_port";

   UART_LOG_0(INFO, "-Uart_get_driver_properties");
   return UART_SUCCESS;
}

/*==================================================================================================

FUNCTION: Uart_get_properties

DESCRIPTION:

==================================================================================================*/
UartResult Uart_get_properties(UART_CONTEXT* h)
{
   uint32 index = 0;
   UART_PROPERTIES *device;
   static DALResult dal_result = DAL_ERROR;

   UART_LOG_0(INFO, "+Uart_get_properties");

   for (index = 0; index < UART_MAX_PORTS; index++)
   {
      if (strcmp(h->port_id, uart_driver_props.device_names[index]) == 0)
      {
         break;
      }
   }
   if (index == UART_MAX_PORTS)
   {
      UART_LOG_0(INFO, "-Uart_get_properties failed.");
      return UART_ERROR;
   }

   device = &devices[index];

   h->properties.is_loopback     = device->is_loopback;
   h->properties.bit_rate        = device->bit_rate;
   h->properties.uart_base       = device->uart_base;
   h->properties.gpio_tx_config  = device->gpio_tx_config;
   h->properties.gpio_rx_config  = device->gpio_rx_config;
   h->properties.gpio_rfr_config = device->gpio_rfr_config;
   h->properties.gpio_cts_config = device->gpio_cts_config;
   h->properties.base_freq       = device->base_freq;
   h->properties.core_clock_id   = (void *)device->core_clock_id;
   h->properties.bus_clock_id    = (void *)device->bus_clock_id;
   h->properties.irq_num         = device->irq_num;

      // Attach to the HWIO device and get the virtual address of the UART base address.
   if(dal_result == DAL_ERROR)
   {
      if(DAL_HWIODeviceAttach(DALDEVICEID_HWIO, &dal_hwio) == DAL_SUCCESS)
      {
         if(DalDevice_Open(dal_hwio, DAL_OPEN_SHARED) == DAL_SUCCESS)
         {
            dal_result = DAL_SUCCESS;
         }
      }
   }
   index = h->properties.uart_base;
   if(dal_result == DAL_SUCCESS)
   {
      if(DalHWIO_MapRegionByAddress(dal_hwio,
                                    (uint8*)index,
                                    (uint8**)&h->properties.uart_base) == DAL_SUCCESS)
      {
         UART_LOG_0(INFO, "-Uart_get_properties->");
         return UART_SUCCESS;
      }
   }

   UART_LOG_0(INFO, "-Uart_get_properties.");
   return UART_SUCCESS;

}
/*==================================================================================================

FUNCTION: Uart_interrupt_close

DESCRIPTION:

==================================================================================================*/
UartResult Uart_interrupt_close(UART_CONTEXT* h)
{
   UART_INTERRUPT_CONTEXT* uart_interrupt_context;
   DALResult result = DAL_ERROR;

   UART_LOG_0(INFO, "+Uart_interrupt_close");
   if (h->interrupt_context == NULL)
   {
      goto done;
   }
   uart_interrupt_context = (UART_INTERRUPT_CONTEXT * )h->interrupt_context;

   // De-register the interrupt.
   result = DalInterruptController_Unregister(uart_interrupt_context->dal_interrupt_handle,
                                              (DALInterruptID)uart_interrupt_context->irq_num);

   // Close the DAL interrupt device.
   DalDevice_Close(uart_interrupt_context->dal_interrupt_handle);
   DAL_DeviceDetach(uart_interrupt_context->dal_interrupt_handle);

done:
   UART_LOG_0(INFO, "-Uart_interrupt_close");
   return (result == DAL_SUCCESS) ? (UART_SUCCESS) : (UART_ERROR);
}

/*==================================================================================================

FUNCTION: Uart_interrupt_done

DESCRIPTION:

==================================================================================================*/
UartResult Uart_interrupt_done(UART_CONTEXT* h)
{
   DALResult result = DAL_ERROR;
   UART_INTERRUPT_CONTEXT* uart_interrupt_context;

   UART_LOG_0(INFO, "+Uart_interrupt_done");

   if (qurt_island_get_status() == 0)
   {

      uart_interrupt_context = (UART_INTERRUPT_CONTEXT*)h->interrupt_context;
      result = DalInterruptController_InterruptDone(uart_interrupt_context->dal_interrupt_handle,
                                                    (DALInterruptID)uart_interrupt_context->irq_num);

   }

   UART_LOG_0(INFO, "-Uart_interrupt_done");
   return (result == DAL_SUCCESS) ? (UART_SUCCESS) : (UART_ERROR);
}

/*==================================================================================================

FUNCTION: Uart_interrupt_open

DESCRIPTION:

==================================================================================================*/
UartResult Uart_interrupt_open(UART_CONTEXT* h, void* isr)
{
   UART_INTERRUPT_CONTEXT* uart_interrupt_context;
   DalDeviceHandle* interrupt_dal = NULL;
   DALResult result;

   UART_LOG_0(INFO, "+Uart_interrupt_open");


   result = DALSYS_Malloc(sizeof(UART_INTERRUPT_CONTEXT), (void **)(&uart_interrupt_context));
   if (result != DAL_SUCCESS)
   {
      UART_LOG_0(ERROR,"DALSYS_Malloc Attach failed");
      return UART_ERROR;
   }
   h->interrupt_context = (void*)uart_interrupt_context;
   result = DAL_DeviceAttach(DALDEVICEID_INTERRUPTCONTROLLER, &interrupt_dal);
   if (result != DAL_SUCCESS)
   {
      UART_LOG_0(ERROR,"DALDEVICEID_INTERRUPTCONTROLLER Attach failed");
      return UART_ERROR;
   }

   result = DalDevice_Open(interrupt_dal, DAL_OPEN_SHARED);
   if (result != DAL_SUCCESS)
   {
      UART_LOG_0(ERROR,"DALDEVICEID_INTERRUPTCONTROLLER open failed");
      return UART_ERROR;
   }

   // Get the interrupt specific Properties in to the interrupt context.
   uart_interrupt_context->irq_num = h->properties.irq_num;
   uart_interrupt_context->dal_interrupt_handle  =  interrupt_dal;

   result = DalInterruptController_RegisterISR(uart_interrupt_context->dal_interrupt_handle,
                                               (DALInterruptID)uart_interrupt_context->irq_num,
                                               (DALISR)isr, h,
                                               DALINTRCTRL_ENABLE_LEVEL_HIGH_TRIGGER);
   if (result != DAL_SUCCESS)
   {
      UART_LOG_0(ERROR,"DalInterruptController_RegisterISR failed");
      return UART_ERROR;
   }

   UART_LOG_0(INFO, "-Uart_interrupt_open");
   return UART_SUCCESS;
}

/*==================================================================================================

FUNCTION: Uart_tlmm_close

DESCRIPTION:

==================================================================================================*/
UartResult Uart_tlmm_close(UART_CONTEXT* h)
{
   uint32 gpio_group[4];
   uint32 num_gpios = 0;
   uint32 i;
   boolean result;

   UART_LOG_0(INFO, "+Uart_tlmm_close");

   if(h->properties.gpio_tx_config){gpio_group[num_gpios++] = h->properties.gpio_tx_config;}
   if(h->properties.gpio_rx_config){gpio_group[num_gpios++] = h->properties.gpio_rx_config;}


   for (i = 0; i < num_gpios; i++)
   {
      result = uTlmm_ConfigGpio(gpio_group[i], UTLMM_GPIO_DISABLE);
      if (result != TRUE)
      {
         UART_LOG_0(ERROR, "DalTlmm_ConfigGpioGroup Enable failed.");
         return UART_ERROR;
      }
   }

   UART_LOG_0(INFO, "-Uart_tlmm_close");
   return UART_SUCCESS;
}

/*==================================================================================================

FUNCTION: Uart_tlmm_open

DESCRIPTION:

==================================================================================================*/
UartResult Uart_tlmm_open(UART_CONTEXT* h)
{
   uint32 gpio_group[4];
   uint32 num_gpios = 0;
   boolean result;
   uint32 i;

   UART_LOG_0(INFO, "+Uart_tlmm_open");

   if(h->properties.gpio_tx_config){gpio_group[num_gpios++] = h->properties.gpio_tx_config;}
   if(h->properties.gpio_rx_config){gpio_group[num_gpios++] = h->properties.gpio_rx_config;}

   for (i = 0; i < num_gpios; i++)
   {
      result = uTlmm_ConfigGpio(gpio_group[i], UTLMM_GPIO_ENABLE);
      if (result != TRUE)
      {
         UART_LOG_0(ERROR, "DalTlmm_ConfigGpioGroup Enable failed.");
         return UART_ERROR;
      }
}

   UART_LOG_0(INFO, "-Uart_tlmm_open");
   return UART_SUCCESS;
}
