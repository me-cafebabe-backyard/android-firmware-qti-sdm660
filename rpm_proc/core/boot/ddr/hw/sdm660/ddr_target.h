#ifndef __DDR_TARGET_H__
#define __DDR_TARGET_H__

/*=============================================================================

                                   DDR HAL
                            Header File
GENERAL DESCRIPTION
This is the target header file for DDR HAL.

Copyright 2014 by Qualcomm Technologies, Inc.  All Rights Reserved.

===========================================================================

                            EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  $Header: //components/rel/rpm.bf/1.8/core/boot/ddr/hw/sdm660/ddr_target.h#1 $

when       who     what, where, why
--------   ---     ------------------------------------------------------------
01/03/14   sr      Initial revision.
=============================================================================*/
/*==============================================================================
                                  INCLUDES
==============================================================================*/
#include "ddr_common.h"
#include "HALhwio.h"


/*==============================================================================
                                  MACROS
==============================================================================*/
#define DDR_ADDR(ddr_reg) BIMC_S_DDR0_##ddr_reg
#define PHY_DQ_ADDR(dim_reg) CH0_DQ0_##dim_reg
#define PHY_CA_ADDR(dim_reg) CH0_CA_##dim_reg
#define SITE_ADDR(dim_reg) CH0_SITE_CA_##dim_reg

/* Define the chip select information based on controller register definition */
#define CS0_ONLY 1ul << HWIO_SHFT(DDR_ADDR(DDR_MANUAL_CMD), RANK_SEL)
#define CS1_ONLY 2ul << HWIO_SHFT(DDR_ADDR(DDR_MANUAL_CMD), RANK_SEL)
#define CS_BOTH  3ul << HWIO_SHFT(DDR_ADDR(DDR_MANUAL_CMD), RANK_SEL)

// Define the ddr base
#define EBI1_PHY_CFG_BASE 0xfc4e0000

/* Define target specific offsets on each interface */
#define SDRAM_0_OFFSET 0
#define SDRAM_1_OFFSET (BIMC_S_DDR1_REG_BASE - BIMC_S_DDR0_REG_BASE)

#define DIM_0_OFFSET 0
#define DIM_1_OFFSET (CH1_DQ0_DDRPHY_DQ_REG_BASE - CH0_DQ0_DDRPHY_DQ_REG_BASE)

#define SITE_0_OFFSET 0
#define SITE_1_OFFSET (CH1_SITE_CA_SITE_REG_BASE - CH0_SITE_CA_SITE_REG_BASE)

/* Define target specific ddr type on each interface */
#define SDRAM_0_TYPE DDR_TYPE_LPDDR3
#define SDRAM_1_TYPE DDR_TYPE_LPDDR3

/* Define DQ off set and IO CAL offsets */
#define SDRAM_DQ0_OFFSET 0x0
#define SDRAM_DQ1_OFFSET 0x800
#define SDRAM_DQ2_OFFSET 0x1000
#define SDRAM_DQ3_OFFSET 0x1800
#define SDRAM_CA_OFFSET  0x0

/* Broadcast offsets */
#define CA_BCAST_OFFSET (HWIO_EBI1_AHB2PHY_BROADCAST_ADDRESS_SPACE_n_ADDR(0) \
        - CH0_CA_DDRPHY_CA_REG_BASE)
#define DQ_BCAST_OFFSET (HWIO_EBI1_AHB2PHY_BROADCAST_ADDRESS_SPACE_n_ADDR(0) \
        - CH0_DQ0_DDRPHY_DQ_REG_BASE)
#define SITE_BCAST_OFFSET (HWIO_EBI1_AHB2PHY_BROADCAST_ADDRESS_SPACE_n_ADDR(0) \
        - CH0_SITE_CA_SITE_REG_BASE)

/* SITE broadcast offsets */
#define SITE_CA_OFFSET 0
#define SITE_DQ00_OFFSET (CH0_SITE_DQ0_SITE_REG_BASE - CH0_SITE_CA_SITE_REG_BASE)
#define SITE_DQ01_OFFSET (CH0_SITE_DQ1_SITE_REG_BASE - CH0_SITE_CA_SITE_REG_BASE)
#define SITE_DQ02_OFFSET (CH0_SITE_DQ2_SITE_REG_BASE - CH0_SITE_CA_SITE_REG_BASE)
#define SITE_DQ03_OFFSET (CH0_SITE_DQ3_SITE_REG_BASE - CH0_SITE_CA_SITE_REG_BASE)

/* Define DDR frequencies */
#define DDR_CLK_FREQ_LV1 166000
#define DDR_CLK_FREQ_LV2 200000
#define DDR_CLK_FREQ_LV3 400000
#define DDR_CLK_FREQ_MAX_IN_KHZ  800000

/* Define DIM register broadcast offset */
#define DDR_DIM_BROADCAST_OFFSET 0x00080000

/* Define the XO speed used for ddr counters (auto refresh, zqcal, srr) */
#define XO_SPEED_IN_KHZ  19200

/* DQ bit mask */
#define DQ0_MASK  0x1
#define DQ1_MASK  0x2
#define DQ2_MASK  0x4
#define DQ3_MASK  0x8
#define DQ4_MASK  0x10
#define DQ5_MASK  0x20
#define DQ6_MASK  0x40
#define DQ7_MASK  0x80
#define DQ8_MASK  0x1
#define DQ9_MASK  0x2
#define DQ10_MASK 0x4
#define DQ11_MASK 0x8
#define DQ12_MASK 0x10
#define DQ13_MASK 0x20
#define DQ14_MASK 0x40
#define DQ15_MASK 0x80

#define DQ0_SHIFT 0x0
#define DQ1_SHIFT 0x1
#define DQ2_SHIFT 0x2
#define DQ3_SHIFT 0x3
#define DQ4_SHIFT 0x4
#define DQ5_SHIFT 0x5
#define DQ6_SHIFT 0x6
#define DQ7_SHIFT 0x7
#define DQ8_SHIFT 0x0
#define DQ9_SHIFT 0x1
#define DQ10_SHIFT 0x2
#define DQ11_SHIFT 0x3
#define DQ12_SHIFT 0x4
#define DQ13_SHIFT 0x5
#define DQ14_SHIFT 0x6
#define DQ15_SHIFT 0x7

/* Define the SITE training threshold */
#define DDR_SITE_TRAINING_MIN_FREQ_KHZ 400000

/* Define CA training count value */
#define DDR_LOOP_COUNT_VALUE 128

/* Define ddr training address */
#define DDR_TRAINING_TEST_ADDRESS_CS0 0x10000000

/* Define the PHY CDC delay mode thresholds */
#define DDR_PHY_DELAY0_THRESHOLD 667000
#define DDR_PHY_DELAY1_THRESHOLD 533000
#define DDR_PHY_DELAY2_THRESHOLD 400000

/* Define the frequency where we can start using PMIC auto mode */
#define DDR_PMIC_AUTOMODE_THRESHOLD_0 307200
#define DDR_PMIC_AUTOMODE_THRESHOLD_1 460800
#define DDR_PMIC_AUTOMODE_THRESHOLD_2 700000

/* Define the current DDR RPM version number */
#define RPM_MAJOR_VERSION 0x01
#define RPM_MINOR_VERSION 0x01

#define PCLP64 TRUE
#define APQ8084 TRUE

#endif /* __DDR_TARGET_H__ */
