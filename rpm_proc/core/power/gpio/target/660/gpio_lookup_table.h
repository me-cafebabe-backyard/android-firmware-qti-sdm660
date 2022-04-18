#ifndef GPIO_LOOKUP_TABLE_H
#define GPIO_LOOKUP_TABLE_H
/*============================================================================
  FILE:         gpio_lookup_table.h

  OVERVIEW:     TLMM GPIO register lookup API header file for 8998.

  DEPENDENCIES: None

                Copyright (c) 2015 Qualcomm Technologies, Inc.
                All Rights Reserved.
                Qualcomm Confidential and Proprietary

  $Header:
  $DateTime:
  $Author:
============================================================================*/


#include "tlmm_hwio.h"
#include "HALhwio.h"

typedef enum
{
    TLMM_ID_CENTER,
    TLMM_ID_NORTH,
    TLMM_ID_SOUTH,
    TLMM_ID_COUNT
} tlmm_id_t;


/*==============================================================================
**
** gpio_lookup_gpio_cfg_addr
**
** Looks up GPIO_CFG[n] register address.
**
** PARAMs: gpio_num - GPIO pin number
**
** RETURN: GPIO_CFG[n] register address
**
**/
unsigned gpio_lookup_gpio_cfg_addr(unsigned gpio_num);

/*==============================================================================
**
** gpio_lookup_gpio_in_out_addr
**
** Looks up GPIO_IN_OUT[n] register address.
**
** PARAMs: gpio_num - GPIO pin number
**
** RETURN: GPIO_IN_OUT[n] register address
**
**/
unsigned gpio_lookup_gpio_in_out_addr(unsigned gpio_num);

/*==============================================================================
**
** gpio_lookup_gpio_intr_cfg_addr
**
** Looks up GPIO_INTR_CFG[n] register address.
**
** PARAMs: gpio_num - GPIO pin number
**
** RETURN: GPIO_INTR_CFG[n] register address
**
**/
unsigned gpio_lookup_gpio_intr_cfg_addr(unsigned gpio_num);

/*==============================================================================
**
** gpio_lookup_dir_conn_intr_cfg_base_addr
**
** Looks up DIR_CONN_INTR_CFG[n] register base address for the target processor.
**
** PARAMs: tlmm_id - NORTH, EAST, or WEST
**         target  - target processor type
**
** RETURN: DIR_CONN_INTR_CFG[n] register base address
**
**/
unsigned gpio_lookup_dir_conn_intr_cfg_base_addr(tlmm_id_t tlmm_id, unsigned target);

#endif /*GPIO_LOOKUP_TABLE_H*/

