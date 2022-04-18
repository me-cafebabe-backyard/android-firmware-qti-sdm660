/*===========================================================================

  gpio_toggle.h - resource to allow masters to toggle GPIO pins

  Copyright (c) 2013 Qualcomm Technologies, Inc.  
  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ===========================================================================*/

#include "comdef.h"

#define REQ_GPIO_NUM    0x626d756e  // 'numb' in little endian
#define REQ_GPIO_STATE  0x74617473  // 'stat' in little endian
#define REQ_GPIO_ENABLE 0x62616e65  // 'enab' in little endian

#define GPIO_ADR_BASE (TLMM_CSR_REG_BASE + 0x00003020)
#define GPIO_BNK_OFFSET 0x4
#define GPIO_STATE_OFFSET 0x20

/* The internal representation of the GPIO toggle config                     *
 * reserved_0 - reserved for future use                                      *
 * reserved_1 - reserved for future use                                      *
 * state      - state of the pin: 0(clear), 1(set)                           *
 * pin        - GPIO pin to toggle                                           */
typedef struct
{
  uint8 reserved_0;
  uint8 reserved_1;
  uint8 state;
  uint8 pin;
} gpio_toggle_inrep;

