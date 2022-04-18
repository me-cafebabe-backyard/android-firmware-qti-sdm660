/*============================================================================
  FILE:         gpio.c

  OVERVIEW:     TLMM GPIO API source file for 8998.

  DEPENDENCIES: None

                Copyright (c) 2015 Qualcomm Technologies, Inc.
                All Rights Reserved.
                Qualcomm Confidential and Proprietary

  $Header:
  $DateTime:
  $Author:
============================================================================*/

#include "gpio.h"
#include "gpio_lookup_table.h"

/*
 * NORTH, WEST, EAST have the same MAXn.
 */
#define TLMM_DIR_CONN_INTRn_CFG_MAXn_SENSORS   HWIO_TLMM_NORTH_DIR_CONN_INTRn_CFG_SENSORS_MAXn
#define TLMM_DIR_CONN_INTRn_CFG_MAXn_LPASS     HWIO_TLMM_NORTH_DIR_CONN_INTRn_CFG_LPA_DSP_MAXn
#define TLMM_DIR_CONN_INTRn_CFG_MAXn_RPM       HWIO_TLMM_NORTH_DIR_CONN_INTRn_CFG_RPM_MAXn
#define TLMM_DIR_CONN_INTRn_CFG_MAXn_HMSS      HWIO_TLMM_NORTH_DIR_CONN_INTRn_CFG_HMSS_MAXn
#define TLMM_DIR_CONN_INTRn_CFG_MAXn_MSS       HWIO_TLMM_NORTH_DIR_CONN_INTRn_CFG_GSS_MAXn
#define TLMM_DIR_CONN_INTRn_CFG_MAXn_CDSP       HWIO_TLMM_NORTH_DIR_CONN_INTRn_CFG_CDSP_MAXn


/*==============================================================================
**
**      Function Definitions
**
**==============================================================================
*/

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
void gpio_configure_gpio(uint32 gpio_num, uint32 config)
{
    out_dword(gpio_lookup_gpio_cfg_addr(gpio_num), config);
}

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
uint32 gpio_read_gpio_in(uint32 gpio_num)
{
    return (0x1 & in_dword(gpio_lookup_gpio_in_out_addr(gpio_num)));
}

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
void gpio_write_gpio_out(uint32 gpio_num, uint32 value)
{
    out_dword(gpio_lookup_gpio_in_out_addr(gpio_num), (0x2 & (value << 1)));
}

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
bool gpio_is_summary_intr(gpio_target_id_t target, uint32 gpio_num)
{
    return (target == (0x7 & (in_dword(gpio_lookup_gpio_intr_cfg_addr(gpio_num)) >> 5)));
}

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
bool gpio_is_dir_conn_intr_enabled(uint32 gpio_num)
{
    return (0x1 & (in_dword(gpio_lookup_gpio_intr_cfg_addr(gpio_num)) >> 8));
}

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
bool gpio_is_dir_conn_intr(gpio_target_id_t target, uint32 gpio_num)
{
    int tlmm_id = 0;
    bool gpio_found = FALSE;
    int max_n = 0;

    switch (target)
    {
        case GPIO_TARGET_PROC_ID_SENSORS: max_n = TLMM_DIR_CONN_INTRn_CFG_MAXn_SENSORS; break;
        case GPIO_TARGET_PROC_ID_LPASS  : max_n = TLMM_DIR_CONN_INTRn_CFG_MAXn_LPASS; break;
        case GPIO_TARGET_PROC_ID_RPM    : max_n = TLMM_DIR_CONN_INTRn_CFG_MAXn_RPM; break;
        case GPIO_TARGET_PROC_ID_HMSS   : max_n = TLMM_DIR_CONN_INTRn_CFG_MAXn_HMSS; break;
        case GPIO_TARGET_PROC_ID_MSS    : max_n = TLMM_DIR_CONN_INTRn_CFG_MAXn_MSS; break;
        case GPIO_TARGET_PROC_ID_CDSP   : max_n = TLMM_DIR_CONN_INTRn_CFG_MAXn_CDSP; break;
        default: return FALSE;
    }

    for(tlmm_id = 0; tlmm_id < TLMM_ID_COUNT && !gpio_found; tlmm_id++)
    {
        int n;
        uint32 base_addr = gpio_lookup_dir_conn_intr_cfg_base_addr((tlmm_id_t)tlmm_id, target);

        for(n = 0; n <= max_n; n++)
        {
            int offset = 0x4 * n;
            if(gpio_num == (0xFF & in_dword(base_addr + offset)))
            {
                gpio_found = TRUE;
                break;
            }
        }
    }

    return gpio_found;
}
