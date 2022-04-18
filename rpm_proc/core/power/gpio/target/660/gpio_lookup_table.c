/*============================================================================
  FILE:         gpio_lookup_table.c

  OVERVIEW:     TLMM GPIO register lookup API source file for 8998.

  DEPENDENCIES: None

                Copyright (c) 2015 Qualcomm Technologies, Inc.
                All Rights Reserved.
                Qualcomm Confidential and Proprietary

  $Header:
  $DateTime:
  $Author:
============================================================================*/

#include "gpio_lookup_table.h"
#include "CoreVerify.h"


#define GPIO_IN_OUT_OFFSET          0x4
#define GPIO_INTR_CFG_OFFSET        0x8
#define GPIO_INTR_STATUS_OFFSET     0xc
#define GPIO_ID_OFFSET              0x10

#define DIR_CONN_INTRn_CFG_BASE_ADDR(tlmm_id, target_id) \
    (HWIO_TLMM_##tlmm_id##_DIR_CONN_INTRn_CFG_SENSORS_ADDR(0) + (0x1000 * (target_id)))


/*
 * GPIO_CFG[n] address lookup table.
 */
static const unsigned gpio_cfg_lookup_table[] =
{
    HWIO_ADDR(TLMM_GPIO_CFG0),
    HWIO_ADDR(TLMM_GPIO_CFG1),
    HWIO_ADDR(TLMM_GPIO_CFG2),
    HWIO_ADDR(TLMM_GPIO_CFG3),
    HWIO_ADDR(TLMM_GPIO_CFG4),
    HWIO_ADDR(TLMM_GPIO_CFG5),
    HWIO_ADDR(TLMM_GPIO_CFG6),
    HWIO_ADDR(TLMM_GPIO_CFG7),
    HWIO_ADDR(TLMM_GPIO_CFG8),
    HWIO_ADDR(TLMM_GPIO_CFG9),
    HWIO_ADDR(TLMM_GPIO_CFG10),
    HWIO_ADDR(TLMM_GPIO_CFG11),
    HWIO_ADDR(TLMM_GPIO_CFG12),
    HWIO_ADDR(TLMM_GPIO_CFG13),
    HWIO_ADDR(TLMM_GPIO_CFG14),
    HWIO_ADDR(TLMM_GPIO_CFG15),
    HWIO_ADDR(TLMM_GPIO_CFG16),
    HWIO_ADDR(TLMM_GPIO_CFG17),
    HWIO_ADDR(TLMM_GPIO_CFG18),
    HWIO_ADDR(TLMM_GPIO_CFG19),
    HWIO_ADDR(TLMM_GPIO_CFG20),
    HWIO_ADDR(TLMM_GPIO_CFG21),
    HWIO_ADDR(TLMM_GPIO_CFG22),
    HWIO_ADDR(TLMM_GPIO_CFG23),
    HWIO_ADDR(TLMM_GPIO_CFG24),
    HWIO_ADDR(TLMM_GPIO_CFG25),
    HWIO_ADDR(TLMM_GPIO_CFG26),
    HWIO_ADDR(TLMM_GPIO_CFG27),
    HWIO_ADDR(TLMM_GPIO_CFG28),
    HWIO_ADDR(TLMM_GPIO_CFG29),
    HWIO_ADDR(TLMM_GPIO_CFG30),
    HWIO_ADDR(TLMM_GPIO_CFG31),
    HWIO_ADDR(TLMM_GPIO_CFG32),
    HWIO_ADDR(TLMM_GPIO_CFG33),
    HWIO_ADDR(TLMM_GPIO_CFG34),
    HWIO_ADDR(TLMM_GPIO_CFG35),
    HWIO_ADDR(TLMM_GPIO_CFG36),
    HWIO_ADDR(TLMM_GPIO_CFG37),
    HWIO_ADDR(TLMM_GPIO_CFG38),
    HWIO_ADDR(TLMM_GPIO_CFG39),
    HWIO_ADDR(TLMM_GPIO_CFG40),
    HWIO_ADDR(TLMM_GPIO_CFG41),
    HWIO_ADDR(TLMM_GPIO_CFG42),
    HWIO_ADDR(TLMM_GPIO_CFG43),
    HWIO_ADDR(TLMM_GPIO_CFG44),
    HWIO_ADDR(TLMM_GPIO_CFG45),
    HWIO_ADDR(TLMM_GPIO_CFG46),
    HWIO_ADDR(TLMM_GPIO_CFG47),
    HWIO_ADDR(TLMM_GPIO_CFG48),
    HWIO_ADDR(TLMM_GPIO_CFG49),
    HWIO_ADDR(TLMM_GPIO_CFG50),
    HWIO_ADDR(TLMM_GPIO_CFG51),
    HWIO_ADDR(TLMM_GPIO_CFG52),
    HWIO_ADDR(TLMM_GPIO_CFG53),
    HWIO_ADDR(TLMM_GPIO_CFG54),
    HWIO_ADDR(TLMM_GPIO_CFG55),
    HWIO_ADDR(TLMM_GPIO_CFG56),
    HWIO_ADDR(TLMM_GPIO_CFG57),
    HWIO_ADDR(TLMM_GPIO_CFG58),
    HWIO_ADDR(TLMM_GPIO_CFG59),
    HWIO_ADDR(TLMM_GPIO_CFG60),
    HWIO_ADDR(TLMM_GPIO_CFG61),
    HWIO_ADDR(TLMM_GPIO_CFG62),
    HWIO_ADDR(TLMM_GPIO_CFG63),
    HWIO_ADDR(TLMM_GPIO_CFG64),
    HWIO_ADDR(TLMM_GPIO_CFG65),
    HWIO_ADDR(TLMM_GPIO_CFG66),
    HWIO_ADDR(TLMM_GPIO_CFG67),
    HWIO_ADDR(TLMM_GPIO_CFG68),
    HWIO_ADDR(TLMM_GPIO_CFG69),
    HWIO_ADDR(TLMM_GPIO_CFG70),
    HWIO_ADDR(TLMM_GPIO_CFG71),
    HWIO_ADDR(TLMM_GPIO_CFG72),
    HWIO_ADDR(TLMM_GPIO_CFG73),
    HWIO_ADDR(TLMM_GPIO_CFG74),
    HWIO_ADDR(TLMM_GPIO_CFG75),
    HWIO_ADDR(TLMM_GPIO_CFG76),
    HWIO_ADDR(TLMM_GPIO_CFG77),
    HWIO_ADDR(TLMM_GPIO_CFG78),
    HWIO_ADDR(TLMM_GPIO_CFG79),
    HWIO_ADDR(TLMM_GPIO_CFG80),
    HWIO_ADDR(TLMM_GPIO_CFG81),
    HWIO_ADDR(TLMM_GPIO_CFG82),
    HWIO_ADDR(TLMM_GPIO_CFG83),
    HWIO_ADDR(TLMM_GPIO_CFG84),
    HWIO_ADDR(TLMM_GPIO_CFG85),
    HWIO_ADDR(TLMM_GPIO_CFG86),
    HWIO_ADDR(TLMM_GPIO_CFG87),
    HWIO_ADDR(TLMM_GPIO_CFG88),
    HWIO_ADDR(TLMM_GPIO_CFG89),
    HWIO_ADDR(TLMM_GPIO_CFG90),
    HWIO_ADDR(TLMM_GPIO_CFG91),
    HWIO_ADDR(TLMM_GPIO_CFG92),
    HWIO_ADDR(TLMM_GPIO_CFG93),
    HWIO_ADDR(TLMM_GPIO_CFG94),
    HWIO_ADDR(TLMM_GPIO_CFG95),
    HWIO_ADDR(TLMM_GPIO_CFG96),
    HWIO_ADDR(TLMM_GPIO_CFG97),
    HWIO_ADDR(TLMM_GPIO_CFG98),
    HWIO_ADDR(TLMM_GPIO_CFG99),
    HWIO_ADDR(TLMM_GPIO_CFG100),
    HWIO_ADDR(TLMM_GPIO_CFG101),
    HWIO_ADDR(TLMM_GPIO_CFG102),
    HWIO_ADDR(TLMM_GPIO_CFG103),
    HWIO_ADDR(TLMM_GPIO_CFG104),
    HWIO_ADDR(TLMM_GPIO_CFG105),
    HWIO_ADDR(TLMM_GPIO_CFG106),
    HWIO_ADDR(TLMM_GPIO_CFG107),
    HWIO_ADDR(TLMM_GPIO_CFG108),
    HWIO_ADDR(TLMM_GPIO_CFG109),
    HWIO_ADDR(TLMM_GPIO_CFG110),
    HWIO_ADDR(TLMM_GPIO_CFG111),
    HWIO_ADDR(TLMM_GPIO_CFG112),
    HWIO_ADDR(TLMM_GPIO_CFG113),
};


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
unsigned gpio_lookup_gpio_cfg_addr(unsigned gpio_num)
{
    CORE_VERIFY(gpio_num < sizeof(gpio_cfg_lookup_table)/sizeof(unsigned));

    return gpio_cfg_lookup_table[gpio_num];
}

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
unsigned gpio_lookup_gpio_in_out_addr(unsigned gpio_num)
{
    CORE_VERIFY(gpio_num < sizeof(gpio_cfg_lookup_table)/sizeof(unsigned));

    return gpio_cfg_lookup_table[gpio_num] + GPIO_IN_OUT_OFFSET;
}

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
unsigned gpio_lookup_gpio_intr_cfg_addr(unsigned gpio_num)
{
    CORE_VERIFY(gpio_num < sizeof(gpio_cfg_lookup_table)/sizeof(unsigned));

    return gpio_cfg_lookup_table[gpio_num] + GPIO_INTR_CFG_OFFSET;
}

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
unsigned gpio_lookup_dir_conn_intr_cfg_base_addr(tlmm_id_t tlmm_id, unsigned target)
{
    switch(tlmm_id)
    {
        case TLMM_ID_CENTER: return DIR_CONN_INTRn_CFG_BASE_ADDR(CENTER, target);
        case TLMM_ID_NORTH : return DIR_CONN_INTRn_CFG_BASE_ADDR(NORTH, target);
        case TLMM_ID_SOUTH : return DIR_CONN_INTRn_CFG_BASE_ADDR(SOUTH, target);
		case TLMM_ID_COUNT : return 0;
    }

    return 0;
}

