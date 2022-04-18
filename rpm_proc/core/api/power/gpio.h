#ifndef GPIO_H
#define GPIO_H

/*============================================================================
  FILE:         gpio.h

  OVERVIEW:     TLMM GPIO API include file.

  DEPENDENCIES: None

                Copyright (c) 2015 Qualcomm Technologies, Inc.
                All Rights Reserved.
                Qualcomm Confidential and Proprietary

  $Header:
  $DateTime:
  $Author:
============================================================================*/


#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <DALSys.h>

typedef enum
{
    GPIO_TARGET_PROC_ID_SENSORS = 0x0,
    GPIO_TARGET_PROC_ID_LPASS   = 0x1,
    GPIO_TARGET_PROC_ID_RPM     = 0x2,
    GPIO_TARGET_PROC_ID_HMSS    = 0x3,
    GPIO_TARGET_PROC_ID_KPSS    = GPIO_TARGET_PROC_ID_HMSS,
    GPIO_TARGET_PROC_ID_GSS     = 0x4,
    GPIO_TARGET_PROC_ID_MSS     = GPIO_TARGET_PROC_ID_GSS,
    GPIO_TARGET_PROC_ID_TZ      = 0x5,
    GPIO_TARGET_PROC_ID_CDSP    = 0x6,
    GPIO_TARGET_PROC_ID_NONE    = 0x7,
    GPIO_TARGET_PROC_ID_WCSS    = GPIO_TARGET_PROC_ID_NONE,
} gpio_target_id_t;


/*==============================================================================
**
** gpio_configure_gpio
**
** Writes the config value to GPIO_CFG[n] register.
**
** PARAMs: gpio_num - GPIO pin number
**         config   - CPIO_CFG[n] configuration value
**
** RETURN: None
**
**/
void gpio_configure_gpio(uint32 gpio_num, uint32 config);

/*==============================================================================
**
** gpio_read_gpio_in
**
** Reads and returns the GPIO_IN bit of GPIO_IN_OUT[n] register.
**
** PARAMs: gpio_num - GPIO pin number
**
** RETURN: GPIO_IN bit
**
**/
uint32 gpio_read_gpio_in(uint32 gpio_num);

/*==============================================================================
**
** gpio_write_gpio_out
**
** Writes the value to GPIO_OUT bit of GPIO_IN_OUT[n] register.
**
** PARAMs: gpio_num - GPIO pin number
**         value    - the value of GPIO_OUT bit
**
** RETURN: None
**
**/
void gpio_write_gpio_out(uint32 gpio_num, uint32 value);

/*==============================================================================
**
** gpio_is_summary_intr
**
** Checks if a summary interrupt from GPIO[n] is routed to the target processor.
**
** PARAMs: target   - Target processor type
**         gpio_num - GPIO pin number
**
** RETURN: TRUE if routed, FALSE if not routed
**
**/
bool gpio_is_summary_intr(gpio_target_id_t target, uint32 gpio_num);

/*==============================================================================
**
** gpio_is_dir_conn_intr_enabled
**
** Checks if GPIO[n] is being used as a Direct Connect Interrupt.
**
** PARAMs: gpio_num - GPIO pin number
**
** RETURN: TRUE if enabled, FALSE if not enabled
**
**/
bool gpio_is_dir_conn_intr_enabled(uint32 gpio_num);

/*==============================================================================
**
** gpio_is_dir_conn_intr
**
** Checks if there exists a direct connect interrupt connected to GPIO[n]
** routed to the target processor.
**
** PARAMs: target   - Target processor type
**         gpio_num - GPIO pin number
**
** RETURN: TRUE if exists, FALSE if doesn't exist
**
**/
bool gpio_is_dir_conn_intr(gpio_target_id_t target, uint32 gpio_num);

#ifdef __cplusplus
}
#endif

#endif /*GPIO_H*/
