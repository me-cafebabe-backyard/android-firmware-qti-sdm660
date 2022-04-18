/*===========================================================================

                    BOOT DDI TARGET DEFINITIONS

DESCRIPTION
  Contains target specific code for Boot DDR Debug Image tool.

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None

Copyright 2016 by Qualcomm Technologies, Inc.  All Rights Reserved.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


when        who      what, where, why
--------    ---      ----------------------------------------------------------
01/03/2017  zhz     Make an SCM call to unlock the TZ region in OCIMEM.
20/12/2016  zhz     Added the target related function
09/14/2016  jh       Initial file creation
===========================================================================*/

#include "ddi_target.h"
#include "ddi_tool.h"
#include "ddi_firehose.h"
#include "boot_cache_mmu.h"
#include "boothw_target.h"
#include "busywait.h"
#include "pm_ldo.h"
#include "boot_fastcall_tz.h"

#define regLo    0
#define regHi    1

#define ixDQ     0
#define ixDQs    1
#define ixCA     2
#define ixCK     3

#define ovrDrv   0
#define pU       1
#define oDt      2
#define vOh      3

extern DDR_STRUCT *share_data;
uint8 Data[4][MAX_PRFS_LEVELS][4][2][64]  __attribute__ ((section (".bss.DDITRAINING_BUFFER_SECTION")));

uint32 ddr_phy_dq_config_tool[16]=
{

    HWIO_ADDRX(0, DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_LO_CFG),
    HWIO_ADDRX(0, DDR_PHY_DDRPHY_FPM_PRFS_1_PWRS_1_LO_CFG),
    HWIO_ADDRX(0, DDR_PHY_DDRPHY_FPM_PRFS_2_PWRS_1_LO_CFG),
    HWIO_ADDRX(0, DDR_PHY_DDRPHY_FPM_PRFS_3_PWRS_1_LO_CFG),
    HWIO_ADDRX(0, DDR_PHY_DDRPHY_FPM_PRFS_4_PWRS_1_LO_CFG),
    HWIO_ADDRX(0, DDR_PHY_DDRPHY_FPM_PRFS_5_PWRS_1_LO_CFG),
    HWIO_ADDRX(0, DDR_PHY_DDRPHY_FPM_PRFS_6_PWRS_1_LO_CFG),
    HWIO_ADDRX(0, DDR_PHY_DDRPHY_FPM_PRFS_7_PWRS_1_LO_CFG),

    HWIO_ADDRX(0, DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_HI_CFG),
    HWIO_ADDRX(0, DDR_PHY_DDRPHY_FPM_PRFS_1_PWRS_1_HI_CFG),
    HWIO_ADDRX(0, DDR_PHY_DDRPHY_FPM_PRFS_2_PWRS_1_HI_CFG),
    HWIO_ADDRX(0, DDR_PHY_DDRPHY_FPM_PRFS_3_PWRS_1_HI_CFG),
    HWIO_ADDRX(0, DDR_PHY_DDRPHY_FPM_PRFS_4_PWRS_1_HI_CFG),
    HWIO_ADDRX(0, DDR_PHY_DDRPHY_FPM_PRFS_5_PWRS_1_HI_CFG),
    HWIO_ADDRX(0, DDR_PHY_DDRPHY_FPM_PRFS_6_PWRS_1_HI_CFG),
    HWIO_ADDRX(0, DDR_PHY_DDRPHY_FPM_PRFS_7_PWRS_1_HI_CFG)
};


uint32 ddr_phy_ca_config_tool[16]=
{
    HWIO_ADDRX(0, DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_LO_CFG),
    HWIO_ADDRX(0, DDR_PHY_DDRPHY_FPM_PRFS_1_PWRS_1_LO_CFG),
    HWIO_ADDRX(0, DDR_PHY_DDRPHY_FPM_PRFS_2_PWRS_1_LO_CFG),
    HWIO_ADDRX(0, DDR_PHY_DDRPHY_FPM_PRFS_3_PWRS_1_LO_CFG),
    HWIO_ADDRX(0, DDR_PHY_DDRPHY_FPM_PRFS_4_PWRS_1_LO_CFG),
    HWIO_ADDRX(0, DDR_PHY_DDRPHY_FPM_PRFS_5_PWRS_1_LO_CFG),
    HWIO_ADDRX(0, DDR_PHY_DDRPHY_FPM_PRFS_6_PWRS_1_LO_CFG),
    HWIO_ADDRX(0, DDR_PHY_DDRPHY_FPM_PRFS_7_PWRS_1_LO_CFG),

    HWIO_ADDRX(0, DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_HI_CFG),
    HWIO_ADDRX(0, DDR_PHY_DDRPHY_FPM_PRFS_1_PWRS_1_HI_CFG),
    HWIO_ADDRX(0, DDR_PHY_DDRPHY_FPM_PRFS_2_PWRS_1_HI_CFG),
    HWIO_ADDRX(0, DDR_PHY_DDRPHY_FPM_PRFS_3_PWRS_1_HI_CFG),
    HWIO_ADDRX(0, DDR_PHY_DDRPHY_FPM_PRFS_4_PWRS_1_HI_CFG),
    HWIO_ADDRX(0, DDR_PHY_DDRPHY_FPM_PRFS_5_PWRS_1_HI_CFG),
    HWIO_ADDRX(0, DDR_PHY_DDRPHY_FPM_PRFS_6_PWRS_1_HI_CFG),
    HWIO_ADDRX(0, DDR_PHY_DDRPHY_FPM_PRFS_7_PWRS_1_HI_CFG)
};

uint32 ddr_phy_ca_config_lo_tool[] =
{
    //CH0 CA0 //CH0_CA0_  DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_LO_CFG
    HWIO_ADDRX(DDI_DDR_PHY_CH0_CA0_BASE, DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_LO_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH0_CA0_BASE, DDR_PHY_DDRPHY_FPM_PRFS_1_PWRS_1_LO_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH0_CA0_BASE, DDR_PHY_DDRPHY_FPM_PRFS_2_PWRS_1_LO_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH0_CA0_BASE, DDR_PHY_DDRPHY_FPM_PRFS_3_PWRS_1_LO_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH0_CA0_BASE, DDR_PHY_DDRPHY_FPM_PRFS_4_PWRS_1_LO_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH0_CA0_BASE, DDR_PHY_DDRPHY_FPM_PRFS_5_PWRS_1_LO_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH0_CA0_BASE, DDR_PHY_DDRPHY_FPM_PRFS_6_PWRS_1_LO_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH0_CA0_BASE, DDR_PHY_DDRPHY_FPM_PRFS_7_PWRS_1_LO_CFG),
    //CH1 CA0
    HWIO_ADDRX(DDI_DDR_PHY_CH1_CA0_BASE, DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_LO_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH1_CA0_BASE, DDR_PHY_DDRPHY_FPM_PRFS_1_PWRS_1_LO_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH1_CA0_BASE, DDR_PHY_DDRPHY_FPM_PRFS_2_PWRS_1_LO_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH1_CA0_BASE, DDR_PHY_DDRPHY_FPM_PRFS_3_PWRS_1_LO_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH1_CA0_BASE, DDR_PHY_DDRPHY_FPM_PRFS_4_PWRS_1_LO_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH1_CA0_BASE, DDR_PHY_DDRPHY_FPM_PRFS_5_PWRS_1_LO_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH1_CA0_BASE, DDR_PHY_DDRPHY_FPM_PRFS_6_PWRS_1_LO_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH1_CA0_BASE, DDR_PHY_DDRPHY_FPM_PRFS_7_PWRS_1_LO_CFG)

};


uint32 ddr_phy_ca_config_hi_tool[] =
{
    //CH0 CA0
    HWIO_ADDRX(DDI_DDR_PHY_CH0_CA0_BASE, DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_HI_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH0_CA0_BASE, DDR_PHY_DDRPHY_FPM_PRFS_1_PWRS_1_HI_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH0_CA0_BASE, DDR_PHY_DDRPHY_FPM_PRFS_2_PWRS_1_HI_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH0_CA0_BASE, DDR_PHY_DDRPHY_FPM_PRFS_3_PWRS_1_HI_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH0_CA0_BASE, DDR_PHY_DDRPHY_FPM_PRFS_4_PWRS_1_HI_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH0_CA0_BASE, DDR_PHY_DDRPHY_FPM_PRFS_5_PWRS_1_HI_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH0_CA0_BASE, DDR_PHY_DDRPHY_FPM_PRFS_6_PWRS_1_HI_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH0_CA0_BASE, DDR_PHY_DDRPHY_FPM_PRFS_7_PWRS_1_HI_CFG),

    //CH1 CA0
    HWIO_ADDRX(DDI_DDR_PHY_CH1_CA0_BASE, DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_HI_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH1_CA0_BASE, DDR_PHY_DDRPHY_FPM_PRFS_1_PWRS_1_HI_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH1_CA0_BASE, DDR_PHY_DDRPHY_FPM_PRFS_2_PWRS_1_HI_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH1_CA0_BASE, DDR_PHY_DDRPHY_FPM_PRFS_3_PWRS_1_HI_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH1_CA0_BASE, DDR_PHY_DDRPHY_FPM_PRFS_4_PWRS_1_HI_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH1_CA0_BASE, DDR_PHY_DDRPHY_FPM_PRFS_5_PWRS_1_HI_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH1_CA0_BASE, DDR_PHY_DDRPHY_FPM_PRFS_6_PWRS_1_HI_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH1_CA0_BASE, DDR_PHY_DDRPHY_FPM_PRFS_7_PWRS_1_HI_CFG)

};


// register access definitions for DQ/DQS drive strength from SOC side
uint32 ddr_phy_dq_config_lo_tool[] =
{
    //CH0 DQ0
    HWIO_ADDRX(DDI_DDR_PHY_CH0_DQ0_BASE, DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_LO_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH0_DQ0_BASE, DDR_PHY_DDRPHY_FPM_PRFS_1_PWRS_1_LO_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH0_DQ0_BASE, DDR_PHY_DDRPHY_FPM_PRFS_2_PWRS_1_LO_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH0_DQ0_BASE, DDR_PHY_DDRPHY_FPM_PRFS_3_PWRS_1_LO_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH0_DQ0_BASE, DDR_PHY_DDRPHY_FPM_PRFS_4_PWRS_1_LO_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH0_DQ0_BASE, DDR_PHY_DDRPHY_FPM_PRFS_5_PWRS_1_LO_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH0_DQ0_BASE, DDR_PHY_DDRPHY_FPM_PRFS_6_PWRS_1_LO_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH0_DQ0_BASE, DDR_PHY_DDRPHY_FPM_PRFS_7_PWRS_1_LO_CFG),

    //CH0 DQ1
    HWIO_ADDRX(DDI_DDR_PHY_CH0_DQ1_BASE, DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_LO_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH0_DQ1_BASE, DDR_PHY_DDRPHY_FPM_PRFS_1_PWRS_1_LO_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH0_DQ1_BASE, DDR_PHY_DDRPHY_FPM_PRFS_2_PWRS_1_LO_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH0_DQ1_BASE, DDR_PHY_DDRPHY_FPM_PRFS_3_PWRS_1_LO_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH0_DQ1_BASE, DDR_PHY_DDRPHY_FPM_PRFS_4_PWRS_1_LO_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH0_DQ1_BASE, DDR_PHY_DDRPHY_FPM_PRFS_5_PWRS_1_LO_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH0_DQ1_BASE, DDR_PHY_DDRPHY_FPM_PRFS_6_PWRS_1_LO_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH0_DQ1_BASE, DDR_PHY_DDRPHY_FPM_PRFS_7_PWRS_1_LO_CFG),

    //CH1 DQ0
    HWIO_ADDRX(DDI_DDR_PHY_CH1_DQ0_BASE, DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_LO_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH1_DQ0_BASE, DDR_PHY_DDRPHY_FPM_PRFS_1_PWRS_1_LO_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH1_DQ0_BASE, DDR_PHY_DDRPHY_FPM_PRFS_2_PWRS_1_LO_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH1_DQ0_BASE, DDR_PHY_DDRPHY_FPM_PRFS_3_PWRS_1_LO_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH1_DQ0_BASE, DDR_PHY_DDRPHY_FPM_PRFS_4_PWRS_1_LO_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH1_DQ0_BASE, DDR_PHY_DDRPHY_FPM_PRFS_5_PWRS_1_LO_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH1_DQ0_BASE, DDR_PHY_DDRPHY_FPM_PRFS_6_PWRS_1_LO_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH1_DQ0_BASE, DDR_PHY_DDRPHY_FPM_PRFS_7_PWRS_1_LO_CFG),

    //CH1 DQ1
    HWIO_ADDRX(DDI_DDR_PHY_CH1_DQ1_BASE, DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_LO_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH1_DQ1_BASE, DDR_PHY_DDRPHY_FPM_PRFS_1_PWRS_1_LO_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH1_DQ1_BASE, DDR_PHY_DDRPHY_FPM_PRFS_2_PWRS_1_LO_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH1_DQ1_BASE, DDR_PHY_DDRPHY_FPM_PRFS_3_PWRS_1_LO_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH1_DQ1_BASE, DDR_PHY_DDRPHY_FPM_PRFS_4_PWRS_1_LO_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH1_DQ1_BASE, DDR_PHY_DDRPHY_FPM_PRFS_5_PWRS_1_LO_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH1_DQ1_BASE, DDR_PHY_DDRPHY_FPM_PRFS_6_PWRS_1_LO_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH1_DQ1_BASE, DDR_PHY_DDRPHY_FPM_PRFS_7_PWRS_1_LO_CFG)
};


uint32 ddr_phy_dq_config_hi_tool[] =
{
    //CH0 DQ0
    HWIO_ADDRX(DDI_DDR_PHY_CH0_DQ0_BASE, DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_HI_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH0_DQ0_BASE, DDR_PHY_DDRPHY_FPM_PRFS_1_PWRS_1_HI_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH0_DQ0_BASE, DDR_PHY_DDRPHY_FPM_PRFS_2_PWRS_1_HI_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH0_DQ0_BASE, DDR_PHY_DDRPHY_FPM_PRFS_3_PWRS_1_HI_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH0_DQ0_BASE, DDR_PHY_DDRPHY_FPM_PRFS_4_PWRS_1_HI_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH0_DQ0_BASE, DDR_PHY_DDRPHY_FPM_PRFS_5_PWRS_1_HI_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH0_DQ0_BASE, DDR_PHY_DDRPHY_FPM_PRFS_6_PWRS_1_HI_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH0_DQ0_BASE, DDR_PHY_DDRPHY_FPM_PRFS_7_PWRS_1_HI_CFG),

    //CH0 DQ1
    HWIO_ADDRX(DDI_DDR_PHY_CH0_DQ1_BASE, DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_HI_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH0_DQ1_BASE, DDR_PHY_DDRPHY_FPM_PRFS_1_PWRS_1_HI_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH0_DQ1_BASE, DDR_PHY_DDRPHY_FPM_PRFS_2_PWRS_1_HI_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH0_DQ1_BASE, DDR_PHY_DDRPHY_FPM_PRFS_3_PWRS_1_HI_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH0_DQ1_BASE, DDR_PHY_DDRPHY_FPM_PRFS_4_PWRS_1_HI_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH0_DQ1_BASE, DDR_PHY_DDRPHY_FPM_PRFS_5_PWRS_1_HI_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH0_DQ1_BASE, DDR_PHY_DDRPHY_FPM_PRFS_6_PWRS_1_HI_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH0_DQ1_BASE, DDR_PHY_DDRPHY_FPM_PRFS_7_PWRS_1_HI_CFG),
    //CH1 DQ0
    HWIO_ADDRX(DDI_DDR_PHY_CH1_DQ0_BASE, DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_HI_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH1_DQ0_BASE, DDR_PHY_DDRPHY_FPM_PRFS_1_PWRS_1_HI_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH1_DQ0_BASE, DDR_PHY_DDRPHY_FPM_PRFS_2_PWRS_1_HI_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH1_DQ0_BASE, DDR_PHY_DDRPHY_FPM_PRFS_3_PWRS_1_HI_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH1_DQ0_BASE, DDR_PHY_DDRPHY_FPM_PRFS_4_PWRS_1_HI_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH1_DQ0_BASE, DDR_PHY_DDRPHY_FPM_PRFS_5_PWRS_1_HI_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH1_DQ0_BASE, DDR_PHY_DDRPHY_FPM_PRFS_6_PWRS_1_HI_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH1_DQ0_BASE, DDR_PHY_DDRPHY_FPM_PRFS_7_PWRS_1_HI_CFG),

    //CH1 DQ1
    HWIO_ADDRX(DDI_DDR_PHY_CH1_DQ1_BASE, DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_HI_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH1_DQ1_BASE, DDR_PHY_DDRPHY_FPM_PRFS_1_PWRS_1_HI_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH1_DQ1_BASE, DDR_PHY_DDRPHY_FPM_PRFS_2_PWRS_1_HI_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH1_DQ1_BASE, DDR_PHY_DDRPHY_FPM_PRFS_3_PWRS_1_HI_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH1_DQ1_BASE, DDR_PHY_DDRPHY_FPM_PRFS_4_PWRS_1_HI_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH1_DQ1_BASE, DDR_PHY_DDRPHY_FPM_PRFS_5_PWRS_1_HI_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH1_DQ1_BASE, DDR_PHY_DDRPHY_FPM_PRFS_6_PWRS_1_HI_CFG),
    HWIO_ADDRX(DDI_DDR_PHY_CH1_DQ1_BASE, DDR_PHY_DDRPHY_FPM_PRFS_7_PWRS_1_HI_CFG)
};


uint32 ddi_ReadVDD1()
{
    //LDO13A   Groot
    uint32 voltage = 0;
    pm_ldo_volt_level_status(0, PM_LDO_13, &voltage);
    return voltage;
}

uint32 ddi_ReadVDD2()
{
    //S1B    Drax
    return ddi_ReadVoltage(1, PM_SMPS_1);
}

uint32 ddi_ReadVDDQ()
{
    switch (getDDRType())
    {
        case DDR_TYPE_LPDDR4X:
            // LPDDR4X -> S2C    Drax
            return ddi_ReadVoltage(1, PM_SMPS_2);
        case DDR_TYPE_LPDDR4:
            // LPDDR4 -> S1B    Drax
            return ddi_ReadVoltage(1, PM_SMPS_1);
        default:
            return 0;
    }
}

uint16 ddi_WriteVDD1(uint32 voltage)
{
    //LDO13A   Groot
    return pm_ldo_volt_level(0, PM_LDO_13, voltage);
}

uint16 ddi_WriteVDD2(uint32 voltage)
{
    //S1B    Drax
    return ddi_WriteVoltage(1, PM_SMPS_1, voltage);
}

uint16 ddi_WriteVDDQ(uint32 voltage)
{
    switch (getDDRType())
    {
        case DDR_TYPE_LPDDR4X:
            // LPDDR4X -> S2C    Drax
            return ddi_WriteVoltage(1, PM_SMPS_2, voltage);
        case DDR_TYPE_LPDDR4:
            // LPDDR4 -> S1B    Drax
            return ddi_WriteVoltage(1, PM_SMPS_1, voltage);
        default:
            // unsupported DDR type
            return 0;
    }
}

void enableBroadcastDQ()
{
    // Enable broadcast mode for all DQ PHYs on both channels
    HWIO_OUTX((DDR_PHY_SS_BASE + SEQ_DDR_SS_DDRSS_AHB2PHY_SWMAN_OFFSET),
              AHB2PHY_SWMAN_AHB2PHY_BROADCAST_EN_CFG_LOWER, 0x1E3C);
}

void enableBroadcastCA()
{
    // Enable broadcast mode for all CA PHYs on both channels
    HWIO_OUTX((DDR_PHY_SS_BASE + SEQ_DDR_SS_DDRSS_AHB2PHY_SWMAN_OFFSET),
              AHB2PHY_SWMAN_AHB2PHY_BROADCAST_EN_CFG_LOWER, 0x0183);
}

void disableBroadcast()
{
    // Disable broadcast mode
    HWIO_OUTX((DDR_PHY_SS_BASE + SEQ_DDR_SS_DDRSS_AHB2PHY_SWMAN_OFFSET),
              AHB2PHY_SWMAN_AHB2PHY_BROADCAST_EN_CFG_LOWER, 0x0);
}


void update_soc_drive_strength(void)
{
    uint32 prfs_level =0;
    if( share_data->ddi_buf[2] != 0)
    {
        enableBroadcastDQ();

        for (prfs_level =0; prfs_level < MAX_PRFS_LEVELS ; prfs_level++)
        {
            out_dword(ddr_phy_dq_config_tool[prfs_level] + BROADCAST_BASE, share_data->ddi_buf[prfs_level+2]);
            out_dword(ddr_phy_dq_config_tool[prfs_level+MAX_PRFS_LEVELS] + BROADCAST_BASE, share_data->ddi_buf[prfs_level+10]);
        }
    }
    if ( share_data->ddi_buf[18] != 0)
    {
        enableBroadcastCA();

        for (prfs_level =0; prfs_level < MAX_PRFS_LEVELS ; prfs_level++)
        {
            out_dword(ddr_phy_ca_config_tool[prfs_level] + BROADCAST_BASE, share_data->ddi_buf[prfs_level+18]);
            out_dword(ddr_phy_ca_config_tool[prfs_level+MAX_PRFS_LEVELS] + BROADCAST_BASE, share_data->ddi_buf[prfs_level+26]);
        }
    }

    if (share_data->ddi_buf[2] != 0 || share_data->ddi_buf[18] != 0 )
    {
        disableBroadcast();
    }
}

boolean disableDBI()
{
    HWIO_DPE_CONFIG_9_OUTM(DDI_BIMC_DDR0_DPE_BASE, HWIO_DPE_CONFIG_9_DBI_MRR_BMSK, HWIO_DPE_CONFIG_9_DBI_MRR_DISABLED_FVAL);
    HWIO_DPE_CONFIG_9_OUTM(DDI_BIMC_DDR0_DPE_BASE, HWIO_DPE_CONFIG_9_DBI_RD_BMSK,  HWIO_DPE_CONFIG_9_DBI_RD_DISABLED_FVAL);
    HWIO_DPE_CONFIG_9_OUTM(DDI_BIMC_DDR0_DPE_BASE, HWIO_DPE_CONFIG_9_DBI_WR_BMSK,  HWIO_DPE_CONFIG_9_DBI_WR_DISABLED_FVAL);

    HWIO_DPE_CONFIG_9_OUTM(DDI_BIMC_DDR1_DPE_BASE, HWIO_DPE_CONFIG_9_DBI_MRR_BMSK, HWIO_DPE_CONFIG_9_DBI_MRR_DISABLED_FVAL);
    HWIO_DPE_CONFIG_9_OUTM(DDI_BIMC_DDR1_DPE_BASE, HWIO_DPE_CONFIG_9_DBI_RD_BMSK,  HWIO_DPE_CONFIG_9_DBI_RD_DISABLED_FVAL);
    HWIO_DPE_CONFIG_9_OUTM(DDI_BIMC_DDR1_DPE_BASE, HWIO_DPE_CONFIG_9_DBI_WR_BMSK,  HWIO_DPE_CONFIG_9_DBI_WR_DISABLED_FVAL);

    //HWIO_DPE_CONFIG_4_OUTM(DDI_BIMC_DDR0_DPE_BASE, HWIO_DPE_CONFIG_4_LOAD_ALL_CONFIG_BMSK,  HWIO_DPE_CONFIG_4_LOAD_ALL_CONFIG_LOAD_FVAL);
    //HWIO_DPE_CONFIG_4_OUTM(DDI_BIMC_DDR1_DPE_BASE, HWIO_DPE_CONFIG_4_LOAD_ALL_CONFIG_BMSK,  HWIO_DPE_CONFIG_4_LOAD_ALL_CONFIG_LOAD_FVAL);
    return TRUE;
}

boolean readPHYSettings(uint8 prfs)
{
    uint32 i = 0;
    uint8 perfLevel = prfs;

    if(perfLevel >= MAX_PRFS_LEVELS)
        return FALSE;

    // do it for DQ
    for(i=perfLevel ; i<(sizeof(ddr_phy_dq_config_lo_tool)/sizeof(uint32)-1); i+=MAX_PRFS_LEVELS)
    {
        Data[ixDQ][perfLevel][ovrDrv][regLo][i] = (in_dword(ddr_phy_dq_config_lo_tool[i]) & MASKDQCAOVRDRV)>>SHIFTDQCAOVRDRV;
    }

    for(i=perfLevel ; i<(sizeof(ddr_phy_dq_config_lo_tool)/sizeof(uint32)-1); i+=MAX_PRFS_LEVELS)
    {
        Data[ixDQ][perfLevel][pU][regLo][i] = (in_dword(ddr_phy_dq_config_lo_tool[i]) & MASKDQCAPU)>>SHIFTDQCAPU;
    }

    for(i=perfLevel ; i<(sizeof(ddr_phy_dq_config_lo_tool)/sizeof(uint32)-1); i+=MAX_PRFS_LEVELS)
    {
        Data[ixDQ][perfLevel][oDt][regLo][i] = (in_dword(ddr_phy_dq_config_hi_tool[i]) & MASKDQCAHIODT)<<SHIFTDQCAHIODT;
        Data[ixDQ][perfLevel][oDt][regLo][i] = (Data[ixDQ][perfLevel][oDt][regLo][i] | ((in_dword(ddr_phy_dq_config_lo_tool[i]) & MASKDQCALOODT ) >> SHIFTDQCALOODT));
    }

    for(i=perfLevel ; i<(sizeof(ddr_phy_dq_config_lo_tool)/sizeof(uint32)-1); i+=MAX_PRFS_LEVELS)
    {
        Data[ixDQ][perfLevel][vOh][regLo][i] = (in_dword(ddr_phy_dq_config_lo_tool[i]) & MASKDQDQSCACKVOH )>>SHIFTDQDQSCACKVOH;
    }

    // do it for DQS
    for(i=perfLevel ; i<(sizeof(ddr_phy_dq_config_lo_tool)/sizeof(uint32)-1); i+=MAX_PRFS_LEVELS)
    {
        Data[ixDQs][perfLevel][ovrDrv][regLo][i] = (in_dword(ddr_phy_dq_config_lo_tool[i]) & MASKDQSCKOVRDRV)>>SHIFTDQSCKOVRDRV;
    }

    for(i=perfLevel ; i<(sizeof(ddr_phy_dq_config_lo_tool)/sizeof(uint32)-1); i+=MAX_PRFS_LEVELS)
    {
        Data[ixDQs][perfLevel][pU][regLo][i] = (in_dword(ddr_phy_dq_config_lo_tool[i]) & MASKDQSCKPU)>>SHIFTDQSCKPU;
    }

    for(i=perfLevel ; i<(sizeof(ddr_phy_dq_config_lo_tool)/sizeof(uint32)-1); i+=MAX_PRFS_LEVELS)
    {
        Data[ixDQs][perfLevel][oDt][regLo][i] = (in_dword(ddr_phy_dq_config_hi_tool[i]) & MASKDQSCKODT)>>SHIFTDQSCKODT;
    }

    for(i=perfLevel ; i<(sizeof(ddr_phy_dq_config_lo_tool)/sizeof(uint32)-1); i+=MAX_PRFS_LEVELS)
    {
        Data[ixDQs][perfLevel][vOh][regLo][i] = (in_dword(ddr_phy_dq_config_lo_tool[i]) & MASKDQDQSCACKVOH)>>SHIFTDQDQSCACKVOH;
    }

    // do it for CA
    for(i=perfLevel ; i<(sizeof(ddr_phy_ca_config_lo_tool)/sizeof(uint32)-1); i+=MAX_PRFS_LEVELS)
    {
        Data[ixCA][perfLevel][ovrDrv][regLo][i] = (in_dword(ddr_phy_ca_config_lo_tool[i]) & MASKDQCAOVRDRV)>>SHIFTDQCAOVRDRV;
    }

    for(i=perfLevel ; i<(sizeof(ddr_phy_ca_config_lo_tool)/sizeof(uint32)-1); i+=MAX_PRFS_LEVELS)
    {
        Data[ixCA][perfLevel][pU][regLo][i] = (in_dword(ddr_phy_ca_config_lo_tool[i]) & MASKDQCAPU)>>SHIFTDQCAPU;
    }

    for(i=perfLevel ; i<(sizeof(ddr_phy_ca_config_lo_tool)/sizeof(uint32)-1); i+=MAX_PRFS_LEVELS)
    {
        Data[ixCA][perfLevel][oDt][regLo][i] = (in_dword(ddr_phy_ca_config_hi_tool[i]) & MASKDQCAHIODT)<<SHIFTDQCAHIODT;
        Data[ixCA][perfLevel][oDt][regLo][i] = (Data[ixCA][perfLevel][oDt][regLo][i] | ((in_dword(ddr_phy_dq_config_lo_tool[i]) & MASKDQCALOODT ) >> SHIFTDQCALOODT));
    }

    for(i=perfLevel ; i<(sizeof(ddr_phy_ca_config_lo_tool)/sizeof(uint32)-1); i+=MAX_PRFS_LEVELS)
    {
        Data[ixCA][perfLevel][vOh][regLo][i] = (in_dword(ddr_phy_ca_config_lo_tool[i]) & MASKDQDQSCACKVOH)>>SHIFTDQDQSCACKVOH;
    }

    // DO it for CK
    for(i=perfLevel ; i<(sizeof(ddr_phy_ca_config_lo_tool)/sizeof(uint32)-1); i+=MAX_PRFS_LEVELS)
    {
        Data[ixCK][perfLevel][ovrDrv][regLo][i] = (in_dword(ddr_phy_ca_config_lo_tool[i]) & MASKDQSCKOVRDRV)>>SHIFTDQSCKOVRDRV;
    }

    for(i=perfLevel ; i<(sizeof(ddr_phy_ca_config_lo_tool)/sizeof(uint32)-1); i+=MAX_PRFS_LEVELS)
    {
        Data[ixCK][perfLevel][pU][regLo][i] = (in_dword(ddr_phy_ca_config_lo_tool[i]) & MASKDQSCKPU)>>SHIFTDQSCKPU;
    }

    for(i=perfLevel ; i<(sizeof(ddr_phy_ca_config_lo_tool)/sizeof(uint32)-1); i+=MAX_PRFS_LEVELS)
    {
        Data[ixCK][perfLevel][oDt][regLo][i] = (in_dword(ddr_phy_ca_config_hi_tool[i]) & MASKDQSCKODT)>>SHIFTDQSCKODT;
    }

    for(i=perfLevel ; i<(sizeof(ddr_phy_ca_config_lo_tool)/sizeof(uint32)-1); i+=MAX_PRFS_LEVELS)
    {
        Data[ixCK][perfLevel][vOh][regLo][i] = (in_dword(ddr_phy_ca_config_lo_tool[i]) & MASKDQDQSCACKVOH)>>SHIFTDQDQSCACKVOH;
    }

    return TRUE;

}

boolean ddi_ReadPHYSettings(uint8 testline, uint8 prfs)
{
    uint8 OverDrive= 0;
    uint8 ODT = 0;
    uint8 PullUp = 0;
    uint8 VoH = 0;

    if(prfs >= MAX_PRFS_LEVELS)
        return FALSE;

    if(FALSE == readPHYSettings(prfs))
        return FALSE;

    OverDrive = Data[testline][prfs][ovrDrv][regLo][prfs];
    ODT = Data[testline][prfs][oDt][regLo][prfs];
    PullUp = Data[testline][prfs][pU][regLo][prfs];
    VoH = Data[testline][prfs][vOh][regLo][prfs];

    ddi_firehose_print_log("OverDrive = %d", OverDrive);
    ddi_firehose_print_log("ODT = %d", ODT);
    ddi_firehose_print_log("PullUp = %d", PullUp);
    ddi_firehose_print_log("VoH = %d", VoH);

    return TRUE;
}

void HAL_SDRAM_PHY_Update_Drive_Strength(int testline,uint32 prfs_level,uint32 odrv, uint32 pullup, uint32 odt, uint32 VOH)
{
    uint32 mask = 0;
    uint8 odt_hi = 0;
    uint8 odt_lo = 0;
    uint8 shift_bits = 0;
    uint8 i = 0;

    if(testline == 0)
    {
        for(i = prfs_level; i < (sizeof(ddr_phy_dq_config_lo_tool)/sizeof(uint32)-1); i += MAX_PRFS_LEVELS)
        {
            // setting DQ odrv value
            mask = 0x38;
            shift_bits = 3;
            out_dword_masked_ns(ddr_phy_dq_config_lo_tool[i], mask, (odrv << shift_bits), in_dword(ddr_phy_dq_config_lo_tool[i]));

            // setting DQ pull up value
            mask = 0xE00;
            shift_bits = 9;
            out_dword_masked_ns(ddr_phy_dq_config_lo_tool[i], mask, (pullup << shift_bits), in_dword(ddr_phy_dq_config_lo_tool[i]));

            //Setting DQ odt value
            odt_lo = odt&0x1;
            mask = 0x80000000;
            shift_bits = 31;
            out_dword_masked_ns(ddr_phy_dq_config_lo_tool[i], mask, (odt_lo << shift_bits), in_dword(ddr_phy_dq_config_lo_tool[i]));

            odt_hi = (odt&0x6) >> 1;
            mask = 0x3;
            out_dword_masked_ns(ddr_phy_dq_config_hi_tool[i], mask, odt_hi, in_dword(ddr_phy_dq_config_hi_tool[i]));

            //Setting DQ voh value
            mask = 0x18000;
            shift_bits = 15;
            out_dword_masked_ns(ddr_phy_dq_config_lo_tool[i], mask, (VOH << shift_bits), in_dword(ddr_phy_dq_config_lo_tool[i]));
        }
    }
    else if(testline == 1)
    {
        for(i = prfs_level; i < (sizeof(ddr_phy_dq_config_lo_tool)/sizeof(uint32)-1); i += MAX_PRFS_LEVELS)
        {
            // setting DQS odrv value
            mask = 0x1C0;
            shift_bits = 6;
            out_dword_masked_ns(ddr_phy_dq_config_lo_tool[i], mask, (odrv << shift_bits), in_dword(ddr_phy_dq_config_lo_tool[i]));

            // setting DQS pull up value
            mask = 0x7000;
            shift_bits = 12;
            out_dword_masked_ns(ddr_phy_dq_config_lo_tool[i], mask, (pullup << shift_bits), in_dword(ddr_phy_dq_config_lo_tool[i]));

            // setting DQS odt value
            mask = 0x1C;
            shift_bits = 2;
            out_dword_masked_ns(ddr_phy_dq_config_hi_tool[i], mask, (odt << shift_bits), in_dword(ddr_phy_dq_config_hi_tool[i]));

            //Setting DQS voh value
            mask=0x18000;
            shift_bits = 15;
            out_dword_masked_ns(ddr_phy_dq_config_lo_tool[i], mask, (VOH << shift_bits), in_dword(ddr_phy_dq_config_lo_tool[i]));
        }
    }
    else if(testline == 2)
    {
        for(i = prfs_level; i < (sizeof(ddr_phy_ca_config_lo_tool)/sizeof(uint32)-1); i += MAX_PRFS_LEVELS)
        {
            // setting CA odrv value
            mask = 0x38;
            shift_bits = 3;
            out_dword_masked_ns(ddr_phy_ca_config_lo_tool[i], mask, (odrv << shift_bits), in_dword(ddr_phy_ca_config_lo_tool[i]));

            // setting CA pull up value
            mask = 0xE00;
            shift_bits = 9;
            out_dword_masked_ns(ddr_phy_ca_config_lo_tool[i], mask, (pullup << shift_bits), in_dword(ddr_phy_ca_config_lo_tool[i]));

            //Setting CA odt value
            odt_lo = odt&0x1;
            mask=0x80000000;
            shift_bits = 31;

            out_dword_masked_ns(ddr_phy_ca_config_lo_tool[i], mask, (odt_lo << shift_bits), in_dword(ddr_phy_ca_config_lo_tool[i]));
            odt_hi = (odt&0x6)>>1;
            mask = 0x3;
            out_dword_masked_ns(ddr_phy_ca_config_hi_tool[i], mask, odt_hi, in_dword(ddr_phy_ca_config_hi_tool[i]));

            //Setting CA voh value
            mask = 0x18000;
            shift_bits = 15;
            out_dword_masked_ns(ddr_phy_ca_config_lo_tool[i], mask, (VOH << shift_bits), in_dword(ddr_phy_ca_config_lo_tool[i]));
        }
    }
    else if(testline == 3)
    {
        for(i = prfs_level; i < (sizeof(ddr_phy_ca_config_lo_tool)/sizeof(uint32)-1); i += MAX_PRFS_LEVELS)
        {
            // setting CK odrv value
            mask = 0x1C0;
            shift_bits = 6;
            out_dword_masked_ns(ddr_phy_ca_config_lo_tool[i], mask, (odrv << shift_bits), in_dword(ddr_phy_ca_config_lo_tool[i]));

            // setting CK pull up value
            mask = 0x7000;
            shift_bits = 12;
            out_dword_masked_ns(ddr_phy_ca_config_lo_tool[i], mask, (pullup << shift_bits), in_dword(ddr_phy_ca_config_lo_tool[i]));

            //setting CK odt value
            mask = 0x1C;
            shift_bits = 2;
            out_dword_masked_ns(ddr_phy_ca_config_hi_tool[i], mask, (odt << shift_bits), in_dword(ddr_phy_ca_config_hi_tool[i]));

            //setting CK voh value
            mask = 0x18000;
            shift_bits = 15;
            out_dword_masked_ns(ddr_phy_ca_config_lo_tool[i], mask, (VOH << shift_bits), in_dword(ddr_phy_ca_config_lo_tool[i]));
        }
    }

}

boolean ddi_ChangePHYSettings(int testline,int prfs,int ovrdrv,int PU,int ODT,int VOH,int ODTE )
{
    uint32 prfs_level = 0;
    uint32 mask = 0;
    uint8 shift_bits = 0;

    if (prfs >= MAX_PRFS_LEVELS)
        return FALSE;

    HAL_SDRAM_PHY_Update_Drive_Strength(testline, prfs, ovrdrv, PU, ODT, VOH);

    if (testline == 0)
    {
        // DQ - 5th bith (starting from 0) need  to be set to set odt enable
        mask = 0x20;
        shift_bits = 5;
        out_dword_masked_ns(ddr_phy_dq_config_hi_tool[prfs], mask, ODTE << 5, in_dword(ddr_phy_dq_config_hi_tool[prfs]));
    }
    else if (testline == 1)
    {
        // DQS - 6th bith (starting from 0) need  to be set to set odt enable
        mask = 0x40;
        shift_bits = 6;
        out_dword_masked_ns(ddr_phy_dq_config_hi_tool[prfs], mask, ODTE << 6, in_dword(ddr_phy_dq_config_hi_tool[prfs]));
    }
    else if (testline == 2)
    {
        // CA - 5th bith (starting from 0) need  to be set to set odt enable
        mask = 0x20;
        shift_bits = 5;
        out_dword_masked_ns(ddr_phy_ca_config_hi_tool[prfs], mask, ODTE << 5, in_dword(ddr_phy_ca_config_hi_tool[prfs]));
    }
    else if (testline == 3)
    {
        // CK - 6th bith (starting from 0) need  to be set to set odt enable
        mask = 0x40;
        shift_bits = 6;
        out_dword_masked_ns(ddr_phy_ca_config_hi_tool[prfs], mask, ODTE << 6, in_dword(ddr_phy_ca_config_hi_tool[prfs]));
    }

    for(prfs_level = 0; prfs_level < MAX_PRFS_LEVELS; prfs_level++)
    {
        share_data->ddi_buf[prfs_level+2] = in_dword (ddr_phy_dq_config_lo_tool[prfs_level]);
        share_data->ddi_buf[prfs_level+10] = in_dword (ddr_phy_dq_config_hi_tool[prfs_level]);
        share_data->ddi_buf[prfs_level+18] = in_dword (ddr_phy_ca_config_lo_tool[prfs_level]);
        share_data->ddi_buf[prfs_level+26] = in_dword (ddr_phy_ca_config_hi_tool[prfs_level]);
    }

    return TRUE;
}

/* =============================================================================
**  Function :  ddr_do_phy_training_DDI
** =============================================================================
*/
/**
*   @brief
*   Indicates that PHY training needs to be done in SBL1 from DDI.
*
*   @param  None
*
*   @retval
*   @retval
*
*   @dependencies
*   None
*
*   @sideeffects
*   None
*
*   @sa
*   None
*/
void ddr_do_phy_training_in_ddi( void )
{

     boot_fastcall_tz_no_rsp(TZ_UNLOCK_CMD, TZ_UNLOCK_CMD_PARAM_ID, 1, 0, 0, 0);
	 
    if (share_data->ddi_buf[0] == DDI_MAGIC_IS_RETRAINED)
    {
        boot_log_message("[DDI] start, HAL_DDR_Boot_Training_Restore");
        HAL_DDR_Boot_Training_Restore(share_data, DDR_CH_BOTH, DDR_CS_BOTH);
        boot_log_message("[DDI] end, HAL_DDR_Boot_Training_Restore");
    }

    if (share_data->ddi_buf[0] == DDI_MAGIC_RETRAIN_REQUIRED_A && share_data->ddi_buf[1] == DDI_MAGIC_RETRAIN_REQUIRED_B)
    {
        applyMRVal();

        if( share_data->ddi_buf[2] != 0 || share_data->ddi_buf[14] != 0 )
        {
            update_soc_drive_strength();
        }
        InitDDITransport();
        clearFlashParams();

        boot_log_message("[DDI] start, HAL_DDR_Boot_Training_Init");
        HAL_DDR_Boot_Training_Init(share_data, DDR_CH_BOTH, DDR_CS_BOTH );
        boot_log_message("[DDI] end, HAL_DDR_Boot_Training_Init");
        clearDDIBuff();
        initMRStruct();

        // flush the region containing the share data sctructure
        dcache_flush_region((void *)share_data, sizeof(*share_data));

        sendTrainingRsp();

        busywait_init();
        busywait(10000000);

        boot_log_message("Reload DDI...");
        deInitTransport();

        boot_hw_reset(BOOT_WARM_RESET_TYPE);
    }
}

