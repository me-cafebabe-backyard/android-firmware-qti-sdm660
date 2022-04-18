/****************************************************************************
 QUALCOMM Proprietary Design Data
 Copyright (c) 2015, Qualcomm Technologies Incorporated. All rights reserved.
 ****************************************************************************/
/*==============================================================================
                                EDIT HISTORY

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/DSFTargetLib/boot/ddrss/src/ddrss_phy_cc_init.c#9 $
$DateTime: 2017/09/27 02:13:08 $
$Author: pwbldsvc $
================================================================================
when       who          what, where, why
--------   ---          --------------------------------------------------------
05/30/14   jeasley      Create separate CA and DQ PHY settings routines
05/20/14   jeasley      Correct SW handshake and Broadcast
05/08/14   jeasley      Move initialization of polling variables to the inside of the loop.
05/06/14   jeasley      Invert the polarity of sw_handshake_complete poll.
05/06/14   jeasley      Updated DDR_PHY_CC_init to use broadcast.
05/04/14   arindamm     First edit history header. Add new entries at top.
================================================================================*/

#include "ddrss.h"

//===========================================================================
// PHY structures.
//===========================================================================
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_LO_CFG_PULL_UP_DQS_CNTL_BMSK 0x00007000
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_LO_CFG_PULL_UP_DQS_CNTL_SHFT        0xc
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_1_PWRS_1_LO_CFG_PULL_UP_DQS_CNTL_BMSK 0x00007000
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_1_PWRS_1_LO_CFG_PULL_UP_DQS_CNTL_SHFT        0xc
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_2_PWRS_1_LO_CFG_PULL_UP_DQS_CNTL_BMSK 0x00007000
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_2_PWRS_1_LO_CFG_PULL_UP_DQS_CNTL_SHFT        0xc
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_3_PWRS_1_LO_CFG_PULL_UP_DQS_CNTL_BMSK 0x00007000
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_3_PWRS_1_LO_CFG_PULL_UP_DQS_CNTL_SHFT        0xc
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_4_PWRS_1_LO_CFG_PULL_UP_DQS_CNTL_BMSK 0x00007000
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_4_PWRS_1_LO_CFG_PULL_UP_DQS_CNTL_SHFT        0xc
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_5_PWRS_1_LO_CFG_PULL_UP_DQS_CNTL_BMSK 0x00007000
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_5_PWRS_1_LO_CFG_PULL_UP_DQS_CNTL_SHFT        0xc
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_6_PWRS_1_LO_CFG_PULL_UP_DQS_CNTL_BMSK 0x00007000
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_6_PWRS_1_LO_CFG_PULL_UP_DQS_CNTL_SHFT        0xc
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_7_PWRS_1_LO_CFG_PULL_UP_DQS_CNTL_BMSK 0x00007000
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_7_PWRS_1_LO_CFG_PULL_UP_DQS_CNTL_SHFT        0xc

#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_LO_CFG_PULL_UP_DQ_CNTL_BMSK 0x00000e00
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_LO_CFG_PULL_UP_DQ_CNTL_SHFT        0x9
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_1_PWRS_1_LO_CFG_PULL_UP_DQ_CNTL_BMSK 0x00000e00
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_1_PWRS_1_LO_CFG_PULL_UP_DQ_CNTL_SHFT        0x9
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_2_PWRS_1_LO_CFG_PULL_UP_DQ_CNTL_BMSK 0x00000e00
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_2_PWRS_1_LO_CFG_PULL_UP_DQ_CNTL_SHFT        0x9
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_3_PWRS_1_LO_CFG_PULL_UP_DQ_CNTL_BMSK 0x00000e00
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_3_PWRS_1_LO_CFG_PULL_UP_DQ_CNTL_SHFT        0x9
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_4_PWRS_1_LO_CFG_PULL_UP_DQ_CNTL_BMSK 0x00000e00
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_4_PWRS_1_LO_CFG_PULL_UP_DQ_CNTL_SHFT        0x9
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_5_PWRS_1_LO_CFG_PULL_UP_DQ_CNTL_BMSK 0x00000e00
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_5_PWRS_1_LO_CFG_PULL_UP_DQ_CNTL_SHFT        0x9
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_6_PWRS_1_LO_CFG_PULL_UP_DQ_CNTL_BMSK 0x00000e00
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_6_PWRS_1_LO_CFG_PULL_UP_DQ_CNTL_SHFT        0x9
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_7_PWRS_1_LO_CFG_PULL_UP_DQ_CNTL_BMSK 0x00000e00
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_7_PWRS_1_LO_CFG_PULL_UP_DQ_CNTL_SHFT        0x9

#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_LO_CFG_ODRV_DQS_BMSK 0x000001c0
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_LO_CFG_ODRV_DQS_SHFT        0x6
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_1_PWRS_1_LO_CFG_ODRV_DQS_BMSK 0x000001c0
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_1_PWRS_1_LO_CFG_ODRV_DQS_SHFT        0x6
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_2_PWRS_1_LO_CFG_ODRV_DQS_BMSK 0x000001c0
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_2_PWRS_1_LO_CFG_ODRV_DQS_SHFT        0x6
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_3_PWRS_1_LO_CFG_ODRV_DQS_BMSK 0x000001c0
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_3_PWRS_1_LO_CFG_ODRV_DQS_SHFT        0x6
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_4_PWRS_1_LO_CFG_ODRV_DQS_BMSK 0x000001c0
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_4_PWRS_1_LO_CFG_ODRV_DQS_SHFT        0x6
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_5_PWRS_1_LO_CFG_ODRV_DQS_BMSK 0x000001c0
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_5_PWRS_1_LO_CFG_ODRV_DQS_SHFT        0x6
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_6_PWRS_1_LO_CFG_ODRV_DQS_BMSK 0x000001c0
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_6_PWRS_1_LO_CFG_ODRV_DQS_SHFT        0x6
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_7_PWRS_1_LO_CFG_ODRV_DQS_BMSK 0x000001c0
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_7_PWRS_1_LO_CFG_ODRV_DQS_SHFT        0x6

#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_3_PWRS_1_LO_CFG_ODRV_DQ_BMSK 0x00000038
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_3_PWRS_1_LO_CFG_ODRV_DQ_SHFT        0x3
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_4_PWRS_1_LO_CFG_ODRV_DQS_BMSK 0x000001c0
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_4_PWRS_1_LO_CFG_ODRV_DQS_SHFT        0x6
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_4_PWRS_1_LO_CFG_ODRV_DQ_BMSK 0x00000038
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_4_PWRS_1_LO_CFG_ODRV_DQ_SHFT        0x3
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_5_PWRS_1_LO_CFG_ODRV_DQS_BMSK 0x000001c0
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_5_PWRS_1_LO_CFG_ODRV_DQS_SHFT        0x6
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_5_PWRS_1_LO_CFG_ODRV_DQ_BMSK 0x00000038
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_5_PWRS_1_LO_CFG_ODRV_DQ_SHFT        0x3
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_6_PWRS_1_LO_CFG_ODRV_DQS_BMSK 0x000001c0
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_6_PWRS_1_LO_CFG_ODRV_DQS_SHFT        0x6
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_6_PWRS_1_LO_CFG_ODRV_DQ_BMSK 0x00000038
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_6_PWRS_1_LO_CFG_ODRV_DQ_SHFT        0x3
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_7_PWRS_1_LO_CFG_ODRV_DQS_BMSK 0x000001c0
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_7_PWRS_1_LO_CFG_ODRV_DQS_SHFT        0x6
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_7_PWRS_1_LO_CFG_ODRV_DQ_BMSK 0x00000038
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_7_PWRS_1_LO_CFG_ODRV_DQ_SHFT        0x3

#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_LO_CFG_DRIVER_VOH_MODE_BMSK 0x00018000
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_LO_CFG_DRIVER_VOH_MODE_SHFT        0xf
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_1_PWRS_1_LO_CFG_DRIVER_VOH_MODE_BMSK 0x00018000
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_1_PWRS_1_LO_CFG_DRIVER_VOH_MODE_SHFT        0xf
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_2_PWRS_1_LO_CFG_DRIVER_VOH_MODE_BMSK 0x00018000
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_2_PWRS_1_LO_CFG_DRIVER_VOH_MODE_SHFT        0xf
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_3_PWRS_1_LO_CFG_DRIVER_VOH_MODE_BMSK 0x00018000
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_3_PWRS_1_LO_CFG_DRIVER_VOH_MODE_SHFT        0xf
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_4_PWRS_1_LO_CFG_DRIVER_VOH_MODE_BMSK 0x00018000
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_4_PWRS_1_LO_CFG_DRIVER_VOH_MODE_SHFT        0xf
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_5_PWRS_1_LO_CFG_DRIVER_VOH_MODE_BMSK 0x00018000
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_5_PWRS_1_LO_CFG_DRIVER_VOH_MODE_SHFT        0xf
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_6_PWRS_1_LO_CFG_DRIVER_VOH_MODE_BMSK 0x00018000
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_6_PWRS_1_LO_CFG_DRIVER_VOH_MODE_SHFT        0xf
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_7_PWRS_1_LO_CFG_DRIVER_VOH_MODE_BMSK 0x00018000
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_7_PWRS_1_LO_CFG_DRIVER_VOH_MODE_SHFT        0xf

#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_HI_CFG_DQS_ODT_ENABLE_BMSK 0x00000040
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_HI_CFG_DQS_ODT_ENABLE_SHFT        0x6
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_1_PWRS_1_HI_CFG_DQS_ODT_ENABLE_BMSK 0x00000040
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_1_PWRS_1_HI_CFG_DQS_ODT_ENABLE_SHFT        0x6
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_2_PWRS_1_HI_CFG_DQS_ODT_ENABLE_BMSK 0x00000040
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_2_PWRS_1_HI_CFG_DQS_ODT_ENABLE_SHFT        0x6
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_3_PWRS_1_HI_CFG_DQS_ODT_ENABLE_BMSK 0x00000040
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_3_PWRS_1_HI_CFG_DQS_ODT_ENABLE_SHFT        0x6
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_4_PWRS_1_HI_CFG_DQS_ODT_ENABLE_BMSK 0x00000040
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_4_PWRS_1_HI_CFG_DQS_ODT_ENABLE_SHFT        0x6
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_5_PWRS_1_HI_CFG_DQS_ODT_ENABLE_BMSK 0x00000040
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_5_PWRS_1_HI_CFG_DQS_ODT_ENABLE_SHFT        0x6
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_6_PWRS_1_HI_CFG_DQS_ODT_ENABLE_BMSK 0x00000040
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_6_PWRS_1_HI_CFG_DQS_ODT_ENABLE_SHFT        0x6
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_7_PWRS_1_HI_CFG_DQS_ODT_ENABLE_BMSK 0x00000040
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_7_PWRS_1_HI_CFG_DQS_ODT_ENABLE_SHFT        0x6

#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_HI_CFG_ODT_IN_DQS_BMSK 0x0000001c
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_HI_CFG_ODT_IN_DQS_SHFT        0x2
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_1_PWRS_1_HI_CFG_ODT_IN_DQS_BMSK 0x0000001c
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_1_PWRS_1_HI_CFG_ODT_IN_DQS_SHFT        0x2
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_2_PWRS_1_HI_CFG_ODT_IN_DQS_BMSK 0x0000001c
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_2_PWRS_1_HI_CFG_ODT_IN_DQS_SHFT        0x2
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_3_PWRS_1_HI_CFG_ODT_IN_DQS_BMSK 0x0000001c
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_3_PWRS_1_HI_CFG_ODT_IN_DQS_SHFT        0x2
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_4_PWRS_1_HI_CFG_ODT_IN_DQS_BMSK 0x0000001c
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_4_PWRS_1_HI_CFG_ODT_IN_DQS_SHFT        0x2
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_5_PWRS_1_HI_CFG_ODT_IN_DQS_BMSK 0x0000001c
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_5_PWRS_1_HI_CFG_ODT_IN_DQS_SHFT        0x2
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_6_PWRS_1_HI_CFG_ODT_IN_DQS_BMSK 0x0000001c
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_6_PWRS_1_HI_CFG_ODT_IN_DQS_SHFT        0x2
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_7_PWRS_1_HI_CFG_ODT_IN_DQS_BMSK 0x0000001c
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_7_PWRS_1_HI_CFG_ODT_IN_DQS_SHFT        0x2

#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_HI_CFG_DQ_ODT_ENABLE_BMSK 0x00000020
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_HI_CFG_DQ_ODT_ENABLE_SHFT        0x5
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_1_PWRS_1_HI_CFG_DQ_ODT_ENABLE_BMSK 0x00000020
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_1_PWRS_1_HI_CFG_DQ_ODT_ENABLE_SHFT        0x5
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_2_PWRS_1_HI_CFG_DQ_ODT_ENABLE_BMSK 0x00000020
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_2_PWRS_1_HI_CFG_DQ_ODT_ENABLE_SHFT        0x5
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_3_PWRS_1_HI_CFG_DQ_ODT_ENABLE_BMSK 0x00000020
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_3_PWRS_1_HI_CFG_DQ_ODT_ENABLE_SHFT        0x5
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_4_PWRS_1_HI_CFG_DQ_ODT_ENABLE_BMSK 0x00000020
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_4_PWRS_1_HI_CFG_DQ_ODT_ENABLE_SHFT        0x5
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_5_PWRS_1_HI_CFG_DQ_ODT_ENABLE_BMSK 0x00000020
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_5_PWRS_1_HI_CFG_DQ_ODT_ENABLE_SHFT        0x5
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_6_PWRS_1_HI_CFG_DQ_ODT_ENABLE_BMSK 0x00000020
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_6_PWRS_1_HI_CFG_DQ_ODT_ENABLE_SHFT        0x5
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_7_PWRS_1_HI_CFG_DQ_ODT_ENABLE_BMSK 0x00000020
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_7_PWRS_1_HI_CFG_DQ_ODT_ENABLE_SHFT        0x5

#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_HI_CFG_ODT_IN_DQ_H_BMSK 0x00000003
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_HI_CFG_ODT_IN_DQ_H_SHFT        0x0
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_1_PWRS_1_HI_CFG_ODT_IN_DQ_H_BMSK 0x00000003
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_1_PWRS_1_HI_CFG_ODT_IN_DQ_H_SHFT        0x0
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_2_PWRS_1_HI_CFG_ODT_IN_DQ_H_BMSK 0x00000003
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_2_PWRS_1_HI_CFG_ODT_IN_DQ_H_SHFT        0x0
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_3_PWRS_1_HI_CFG_ODT_IN_DQ_H_BMSK 0x00000003
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_3_PWRS_1_HI_CFG_ODT_IN_DQ_H_SHFT        0x0
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_4_PWRS_1_HI_CFG_ODT_IN_DQ_H_BMSK 0x00000003
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_4_PWRS_1_HI_CFG_ODT_IN_DQ_H_SHFT        0x0
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_5_PWRS_1_HI_CFG_ODT_IN_DQ_H_BMSK 0x00000003
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_5_PWRS_1_HI_CFG_ODT_IN_DQ_H_SHFT        0x0
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_6_PWRS_1_HI_CFG_ODT_IN_DQ_H_BMSK 0x00000003
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_6_PWRS_1_HI_CFG_ODT_IN_DQ_H_SHFT        0x0
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_7_PWRS_1_HI_CFG_ODT_IN_DQ_H_BMSK 0x00000003
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_7_PWRS_1_HI_CFG_ODT_IN_DQ_H_SHFT        0x0

#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_LO_CFG_ODT_IN_DQ_L_BMSK 0x80000000
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_LO_CFG_ODT_IN_DQ_L_SHFT       0x1f
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_1_PWRS_1_LO_CFG_ODT_IN_DQ_L_BMSK 0x80000000
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_1_PWRS_1_LO_CFG_ODT_IN_DQ_L_SHFT       0x1f
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_2_PWRS_1_LO_CFG_ODT_IN_DQ_L_BMSK 0x80000000
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_2_PWRS_1_LO_CFG_ODT_IN_DQ_L_SHFT       0x1f
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_3_PWRS_1_LO_CFG_ODT_IN_DQ_L_BMSK 0x80000000
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_3_PWRS_1_LO_CFG_ODT_IN_DQ_L_SHFT       0x1f
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_4_PWRS_1_LO_CFG_ODT_IN_DQ_L_BMSK 0x80000000
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_4_PWRS_1_LO_CFG_ODT_IN_DQ_L_SHFT       0x1f
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_5_PWRS_1_LO_CFG_ODT_IN_DQ_L_BMSK 0x80000000
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_5_PWRS_1_LO_CFG_ODT_IN_DQ_L_SHFT       0x1f
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_6_PWRS_1_LO_CFG_ODT_IN_DQ_L_BMSK 0x80000000
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_6_PWRS_1_LO_CFG_ODT_IN_DQ_L_SHFT       0x1f
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_7_PWRS_1_LO_CFG_ODT_IN_DQ_L_BMSK 0x80000000
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_7_PWRS_1_LO_CFG_ODT_IN_DQ_L_SHFT       0x1f

#define HWIO_DDR_PHY_DDRPHY_CMCDCRDT2_I0_CTL_CFG_HP_COARSE_R0_BMSK 0x0000001f
#define HWIO_DDR_PHY_DDRPHY_CMCDCRDT2_I0_CTL_CFG_HP_COARSE_R0_SHFT        0x0
#define HWIO_DDR_PHY_DDRPHY_CDCEXT_RDT2_0_CTL_CFG_HP_COARSE_R0_BMSK 0x0000001f
#define HWIO_DDR_PHY_DDRPHY_CDCEXT_RDT2_0_CTL_CFG_HP_COARSE_R0_SHFT        0x0
#define HWIO_DDR_PHY_DDRPHY_CDCEXT_RDT2_1_CTL_CFG_HP_COARSE_R0_BMSK 0x0000001f
#define HWIO_DDR_PHY_DDRPHY_CDCEXT_RDT2_1_CTL_CFG_HP_COARSE_R0_SHFT        0x0
#define HWIO_DDR_PHY_DDRPHY_CDCEXT_RDT2_2_CTL_CFG_HP_COARSE_R0_BMSK 0x0000001f
#define HWIO_DDR_PHY_DDRPHY_CDCEXT_RDT2_2_CTL_CFG_HP_COARSE_R0_SHFT        0x0
#define HWIO_DDR_PHY_DDRPHY_CDCEXT_RDT2_3_CTL_CFG_HP_COARSE_R0_BMSK 0x0000001f
#define HWIO_DDR_PHY_DDRPHY_CDCEXT_RDT2_3_CTL_CFG_HP_COARSE_R0_SHFT        0x0
#define HWIO_DDR_PHY_DDRPHY_CDCEXT_RDT2_4_CTL_CFG_HP_COARSE_R0_BMSK 0x0000001f
#define HWIO_DDR_PHY_DDRPHY_CDCEXT_RDT2_4_CTL_CFG_HP_COARSE_R0_SHFT        0x0
#define HWIO_DDR_PHY_DDRPHY_CDCEXT_RDT2_5_CTL_CFG_HP_COARSE_R0_BMSK 0x0000001f
#define HWIO_DDR_PHY_DDRPHY_CDCEXT_RDT2_5_CTL_CFG_HP_COARSE_R0_SHFT        0x0
#define HWIO_DDR_PHY_DDRPHY_CDCEXT_RDT2_6_CTL_CFG_HP_COARSE_R0_BMSK 0x0000001f
#define HWIO_DDR_PHY_DDRPHY_CDCEXT_RDT2_6_CTL_CFG_HP_COARSE_R0_SHFT        0x0
#define HWIO_DDR_PHY_DDRPHY_CDCEXT_RDT2_7_CTL_CFG_HP_COARSE_R0_BMSK 0x0000001f
#define HWIO_DDR_PHY_DDRPHY_CDCEXT_RDT2_7_CTL_CFG_HP_COARSE_R0_SHFT        0x0

#define HWIO_DDR_PHY_DDRPHY_CMCDCRDT2_I0_CTL_CFG_HP_COARSE_R1_BMSK 0x00007c00
#define HWIO_DDR_PHY_DDRPHY_CMCDCRDT2_I0_CTL_CFG_HP_COARSE_R1_SHFT        0xa
#define HWIO_DDR_PHY_DDRPHY_CDCEXT_RDT2_0_CTL_CFG_HP_COARSE_R1_BMSK 0x00007c00
#define HWIO_DDR_PHY_DDRPHY_CDCEXT_RDT2_0_CTL_CFG_HP_COARSE_R1_SHFT        0xa
#define HWIO_DDR_PHY_DDRPHY_CDCEXT_RDT2_1_CTL_CFG_HP_COARSE_R1_BMSK 0x00007c00
#define HWIO_DDR_PHY_DDRPHY_CDCEXT_RDT2_1_CTL_CFG_HP_COARSE_R1_SHFT        0xa
#define HWIO_DDR_PHY_DDRPHY_CDCEXT_RDT2_2_CTL_CFG_HP_COARSE_R1_BMSK 0x00007c00
#define HWIO_DDR_PHY_DDRPHY_CDCEXT_RDT2_2_CTL_CFG_HP_COARSE_R1_SHFT        0xa
#define HWIO_DDR_PHY_DDRPHY_CDCEXT_RDT2_3_CTL_CFG_HP_COARSE_R1_BMSK 0x00007c00
#define HWIO_DDR_PHY_DDRPHY_CDCEXT_RDT2_3_CTL_CFG_HP_COARSE_R1_SHFT        0xa
#define HWIO_DDR_PHY_DDRPHY_CDCEXT_RDT2_4_CTL_CFG_HP_COARSE_R1_BMSK 0x00007c00
#define HWIO_DDR_PHY_DDRPHY_CDCEXT_RDT2_4_CTL_CFG_HP_COARSE_R1_SHFT        0xa
#define HWIO_DDR_PHY_DDRPHY_CDCEXT_RDT2_5_CTL_CFG_HP_COARSE_R1_BMSK 0x00007c00
#define HWIO_DDR_PHY_DDRPHY_CDCEXT_RDT2_5_CTL_CFG_HP_COARSE_R1_SHFT        0xa
#define HWIO_DDR_PHY_DDRPHY_CDCEXT_RDT2_6_CTL_CFG_HP_COARSE_R1_BMSK 0x00007c00
#define HWIO_DDR_PHY_DDRPHY_CDCEXT_RDT2_6_CTL_CFG_HP_COARSE_R1_SHFT        0xa
#define HWIO_DDR_PHY_DDRPHY_CDCEXT_RDT2_7_CTL_CFG_HP_COARSE_R1_BMSK 0x00007c00
#define HWIO_DDR_PHY_DDRPHY_CDCEXT_RDT2_7_CTL_CFG_HP_COARSE_R1_SHFT        0xa

#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_LO_CFG_PULL_UP_DQS_CNTL_BMSK 0x00007000
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_LO_CFG_PULL_UP_DQS_CNTL_SHFT        0xc
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_1_PWRS_1_LO_CFG_PULL_UP_DQS_CNTL_BMSK 0x00007000
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_1_PWRS_1_LO_CFG_PULL_UP_DQS_CNTL_SHFT        0xc
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_2_PWRS_1_LO_CFG_PULL_UP_DQS_CNTL_BMSK 0x00007000
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_2_PWRS_1_LO_CFG_PULL_UP_DQS_CNTL_SHFT        0xc
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_3_PWRS_1_LO_CFG_PULL_UP_DQS_CNTL_BMSK 0x00007000
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_3_PWRS_1_LO_CFG_PULL_UP_DQS_CNTL_SHFT        0xc
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_4_PWRS_1_LO_CFG_PULL_UP_DQS_CNTL_BMSK 0x00007000
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_4_PWRS_1_LO_CFG_PULL_UP_DQS_CNTL_SHFT        0xc
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_5_PWRS_1_LO_CFG_PULL_UP_DQS_CNTL_BMSK 0x00007000
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_5_PWRS_1_LO_CFG_PULL_UP_DQS_CNTL_SHFT        0xc
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_6_PWRS_1_LO_CFG_PULL_UP_DQS_CNTL_BMSK 0x00007000
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_6_PWRS_1_LO_CFG_PULL_UP_DQS_CNTL_SHFT        0xc
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_7_PWRS_1_LO_CFG_PULL_UP_DQS_CNTL_BMSK 0x00007000
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_7_PWRS_1_LO_CFG_PULL_UP_DQS_CNTL_SHFT        0xc

#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_LO_CFG_PULL_UP_DQ_CNTL_BMSK 0x00000e00
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_LO_CFG_PULL_UP_DQ_CNTL_SHFT        0x9
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_1_PWRS_1_LO_CFG_PULL_UP_DQ_CNTL_BMSK 0x00000e00
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_1_PWRS_1_LO_CFG_PULL_UP_DQ_CNTL_SHFT        0x9
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_2_PWRS_1_LO_CFG_PULL_UP_DQ_CNTL_BMSK 0x00000e00
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_2_PWRS_1_LO_CFG_PULL_UP_DQ_CNTL_SHFT        0x9
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_3_PWRS_1_LO_CFG_PULL_UP_DQ_CNTL_BMSK 0x00000e00
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_3_PWRS_1_LO_CFG_PULL_UP_DQ_CNTL_SHFT        0x9
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_4_PWRS_1_LO_CFG_PULL_UP_DQ_CNTL_BMSK 0x00000e00
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_4_PWRS_1_LO_CFG_PULL_UP_DQ_CNTL_SHFT        0x9
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_5_PWRS_1_LO_CFG_PULL_UP_DQ_CNTL_BMSK 0x00000e00
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_5_PWRS_1_LO_CFG_PULL_UP_DQ_CNTL_SHFT        0x9
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_6_PWRS_1_LO_CFG_PULL_UP_DQ_CNTL_BMSK 0x00000e00
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_6_PWRS_1_LO_CFG_PULL_UP_DQ_CNTL_SHFT        0x9
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_7_PWRS_1_LO_CFG_PULL_UP_DQ_CNTL_BMSK 0x00000e00
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_7_PWRS_1_LO_CFG_PULL_UP_DQ_CNTL_SHFT        0x9

#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_LO_CFG_ODRV_DQS_BMSK 0x000001c0
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_LO_CFG_ODRV_DQS_SHFT        0x6
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_1_PWRS_1_LO_CFG_ODRV_DQS_BMSK 0x000001c0
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_1_PWRS_1_LO_CFG_ODRV_DQS_SHFT        0x6
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_2_PWRS_1_LO_CFG_ODRV_DQS_BMSK 0x000001c0
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_2_PWRS_1_LO_CFG_ODRV_DQS_SHFT        0x6
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_3_PWRS_1_LO_CFG_ODRV_DQS_BMSK 0x000001c0
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_3_PWRS_1_LO_CFG_ODRV_DQS_SHFT        0x6
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_4_PWRS_1_LO_CFG_ODRV_DQS_BMSK 0x000001c0
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_4_PWRS_1_LO_CFG_ODRV_DQS_SHFT        0x6
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_5_PWRS_1_LO_CFG_ODRV_DQS_BMSK 0x000001c0
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_5_PWRS_1_LO_CFG_ODRV_DQS_SHFT        0x6
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_6_PWRS_1_LO_CFG_ODRV_DQS_BMSK 0x000001c0
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_6_PWRS_1_LO_CFG_ODRV_DQS_SHFT        0x6
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_7_PWRS_1_LO_CFG_ODRV_DQS_BMSK 0x000001c0
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_7_PWRS_1_LO_CFG_ODRV_DQS_SHFT        0x6

#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_LO_CFG_ODRV_DQ_BMSK 0x00000038
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_LO_CFG_ODRV_DQ_SHFT        0x3
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_1_PWRS_1_LO_CFG_ODRV_DQ_BMSK 0x00000038
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_1_PWRS_1_LO_CFG_ODRV_DQ_SHFT        0x3
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_2_PWRS_1_LO_CFG_ODRV_DQ_BMSK 0x00000038
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_2_PWRS_1_LO_CFG_ODRV_DQ_SHFT        0x3
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_3_PWRS_1_LO_CFG_ODRV_DQ_BMSK 0x00000038
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_3_PWRS_1_LO_CFG_ODRV_DQ_SHFT        0x3
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_4_PWRS_1_LO_CFG_ODRV_DQ_BMSK 0x00000038
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_4_PWRS_1_LO_CFG_ODRV_DQ_SHFT        0x3
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_5_PWRS_1_LO_CFG_ODRV_DQ_BMSK 0x00000038
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_5_PWRS_1_LO_CFG_ODRV_DQ_SHFT        0x3
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_6_PWRS_1_LO_CFG_ODRV_DQ_BMSK 0x00000038
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_6_PWRS_1_LO_CFG_ODRV_DQ_SHFT        0x3
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_7_PWRS_1_LO_CFG_ODRV_DQ_BMSK 0x00000038
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_7_PWRS_1_LO_CFG_ODRV_DQ_SHFT        0x3

#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_LO_CFG_DRIVER_VOH_MODE_BMSK 0x00018000
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_LO_CFG_DRIVER_VOH_MODE_SHFT        0xf
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_1_PWRS_1_LO_CFG_DRIVER_VOH_MODE_BMSK 0x00018000
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_1_PWRS_1_LO_CFG_DRIVER_VOH_MODE_SHFT        0xf
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_2_PWRS_1_LO_CFG_DRIVER_VOH_MODE_BMSK 0x00018000
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_2_PWRS_1_LO_CFG_DRIVER_VOH_MODE_SHFT        0xf
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_3_PWRS_1_LO_CFG_DRIVER_VOH_MODE_BMSK 0x00018000
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_3_PWRS_1_LO_CFG_DRIVER_VOH_MODE_SHFT        0xf
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_4_PWRS_1_LO_CFG_DRIVER_VOH_MODE_BMSK 0x00018000
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_4_PWRS_1_LO_CFG_DRIVER_VOH_MODE_SHFT        0xf
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_5_PWRS_1_LO_CFG_DRIVER_VOH_MODE_BMSK 0x00018000
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_5_PWRS_1_LO_CFG_DRIVER_VOH_MODE_SHFT        0xf
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_6_PWRS_1_LO_CFG_DRIVER_VOH_MODE_BMSK 0x00018000
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_6_PWRS_1_LO_CFG_DRIVER_VOH_MODE_SHFT        0xf
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_7_PWRS_1_LO_CFG_DRIVER_VOH_MODE_BMSK 0x00018000
#define HWIO_DDR_PHY_DDRPHY_FPM_PRFS_7_PWRS_1_LO_CFG_DRIVER_VOH_MODE_SHFT        0xf

#if DSF_ECDT_EN
extern struct ecdt_msm_drive_strength_input_struct     msm_drive_strength_ca;
extern struct ecdt_msm_drive_strength_input_struct     msm_drive_strength_dq;
extern struct ecdt_msm_odt_input_struct                msm_odt;
extern struct ecdt_msm_rd_t2_input_struct              msm_rd_t2;
extern struct ecdt_dram_soc_odt_input_struct           dram_soc_odt[];
extern struct ecdt_msm_drv_str_odt_rdt2_input_struct   msm_drv_str_odt_rdt2[];
#endif

uint32 prfs_offset_LO[8] = 
{
    0,
    HWIO_DDR_PHY_DDRPHY_FPM_PRFS_1_PWRS_1_LO_CFG_ADDR(0)- HWIO_DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_LO_CFG_ADDR(0),
    HWIO_DDR_PHY_DDRPHY_FPM_PRFS_2_PWRS_1_LO_CFG_ADDR(0)- HWIO_DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_LO_CFG_ADDR(0),
    HWIO_DDR_PHY_DDRPHY_FPM_PRFS_3_PWRS_1_LO_CFG_ADDR(0)- HWIO_DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_LO_CFG_ADDR(0),
    HWIO_DDR_PHY_DDRPHY_FPM_PRFS_4_PWRS_1_LO_CFG_ADDR(0)- HWIO_DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_LO_CFG_ADDR(0),
    HWIO_DDR_PHY_DDRPHY_FPM_PRFS_5_PWRS_1_LO_CFG_ADDR(0)- HWIO_DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_LO_CFG_ADDR(0),
    HWIO_DDR_PHY_DDRPHY_FPM_PRFS_6_PWRS_1_LO_CFG_ADDR(0)- HWIO_DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_LO_CFG_ADDR(0),
    HWIO_DDR_PHY_DDRPHY_FPM_PRFS_7_PWRS_1_LO_CFG_ADDR(0)- HWIO_DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_LO_CFG_ADDR(0)
};

uint32 prfs_offset_HI[8] = 
{
    0,
    HWIO_DDR_PHY_DDRPHY_FPM_PRFS_1_PWRS_1_HI_CFG_ADDR(0)- HWIO_DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_HI_CFG_ADDR(0),
    HWIO_DDR_PHY_DDRPHY_FPM_PRFS_2_PWRS_1_HI_CFG_ADDR(0)- HWIO_DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_HI_CFG_ADDR(0),
    HWIO_DDR_PHY_DDRPHY_FPM_PRFS_3_PWRS_1_HI_CFG_ADDR(0)- HWIO_DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_HI_CFG_ADDR(0),
    HWIO_DDR_PHY_DDRPHY_FPM_PRFS_4_PWRS_1_HI_CFG_ADDR(0)- HWIO_DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_HI_CFG_ADDR(0),
    HWIO_DDR_PHY_DDRPHY_FPM_PRFS_5_PWRS_1_HI_CFG_ADDR(0)- HWIO_DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_HI_CFG_ADDR(0),
    HWIO_DDR_PHY_DDRPHY_FPM_PRFS_6_PWRS_1_HI_CFG_ADDR(0)- HWIO_DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_HI_CFG_ADDR(0),
    HWIO_DDR_PHY_DDRPHY_FPM_PRFS_7_PWRS_1_HI_CFG_ADDR(0)- HWIO_DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_HI_CFG_ADDR(0)
};

//================================================================================================//
// DDR PHY and CC one-time settings
//================================================================================================//
void DDR_PHY_CC_Config(DDR_STRUCT *ddr)
{
    
   // Enable broadcast mode for all DQ PHYs on both channels
   HWIO_OUTX((DDR_PHY_SS_BASE + SEQ_DDR_SS_DDRSS_AHB2PHY_SWMAN_OFFSET),
             AHB2PHY_SWMAN_AHB2PHY_BROADCAST_EN_CFG_LOWER, ALL_DQs);
   ddr_phy_dq_set_config(ddr, 
                         BROADCAST_BASE, 
                         ddr_phy_dq_config_base,
                         ddr_phy_dq_lp4x_config_base,
						 ddr_phy_dq_starlord_config_base);

   // Enable broadcast mode for all CA PHYs on both channels
   HWIO_OUTX((DDR_PHY_SS_BASE + SEQ_DDR_SS_DDRSS_AHB2PHY_SWMAN_OFFSET),
             AHB2PHY_SWMAN_AHB2PHY_BROADCAST_EN_CFG_LOWER, ALL_CAs);
   ddr_phy_ca_set_config(ddr, 
                         BROADCAST_BASE, 
                         ddr_phy_ca_config_base,
                         ddr_phy_ca_lp4x_config_base,
						 ddr_phy_ca_starlord_config_base);

   // Enable broadcast mode for all CCs on both channels
   HWIO_OUTX((DDR_PHY_SS_BASE + SEQ_DDR_SS_DDRSS_AHB2PHY_SWMAN_OFFSET),
             AHB2PHY_SWMAN_AHB2PHY_BROADCAST_EN_CFG_LOWER, ALL_CCs);
   ddr_cc_set_config(ddr, 
                     BROADCAST_BASE, 
                     ddr_cc_config_base);

   // Disable broadcast mode 
   HWIO_OUTX((DDR_PHY_SS_BASE + SEQ_DDR_SS_DDRSS_AHB2PHY_SWMAN_OFFSET),
             AHB2PHY_SWMAN_AHB2PHY_BROADCAST_EN_CFG_LOWER, PHY_BC_DISABLE);


}


//================================================================================================//
// DDR PHY and CC Initialization
//================================================================================================//
//boolean DDR_PHY_Init_GHS (DDR_STRUCT *ddr, DDR_CHANNEL channel)
//{
//   // uint32 init_clk_khz;
//
//   // init_clk_khz = ddr->misc.current_clk_in_kHz;
//   
//   // Add any needed code for DDR Phy init in GHS mode...
//   
//   return TRUE;
//}


//================================================================================================//
// DDR PHY and CC Initialization
//================================================================================================//
void DDR_PHY_CC_init (DDR_STRUCT *ddr, DDR_CHANNEL channel)
{
   uint8 ch = 0;
   uint8 dq = 0;
   uint8 ca = 0;
   uint32 reg_offset_ddr_cc;
   uint32 reg_offset_ddr_phy;
   
   for (ch = 0; ch < NUM_CH; ch++)
   {
      reg_offset_ddr_phy = REG_OFFSET_DDR_PHY_CH(ch);
      reg_offset_ddr_cc = REG_OFFSET_DDR_CC_CH(ch);
      
      if ((channel >> ch) & 0x1)
      {
         // Load the register settings by doing a SW freq switch
         DDRSS_ddr_phy_sw_freq_switch(ddr, ch);
       
           
           //// Initialize PCC Link Lists

           for (dq=0;dq<NUM_DQ_PCH;dq++)
           {
             // Disable freeze_io control in DDRPHYs
             HWIO_OUTXF2(reg_offset_ddr_phy + DQ0_DDR_PHY_OFFSET + (dq * DDR_PHY_OFFSET),
                         DDR_PHY_DDRPHY_PCC_PC_CFG,
                         SW_PC_FREEZE_IO,SW_PC_FREEZE_IO_EN,
                         0x0,
                         0x1);
           }
  
           for (ca=0;ca<NUM_CA_PCH;ca++)
           {
             // Disable freeze_io control in DDRPHYs
             HWIO_OUTXF2(reg_offset_ddr_phy + CA0_DDR_PHY_OFFSET + (ca * DDR_PHY_OFFSET),
                         DDR_PHY_DDRPHY_PCC_PC_CFG,
                         SW_PC_FREEZE_IO,
                         SW_PC_FREEZE_IO_EN,
                         0x0,
                         0x1);
           }
                   
           // Enable freeze_io control in DDRCC
           HWIO_OUTXF2(reg_offset_ddr_cc + DDR_CC_OFFSET,DDR_CC_DDRCC_PCC_PC_CFG,SW_PC_FREEZE_IO,SW_PC_FREEZE_IO_EN,0x0,0x0);
                                
           // Enable broadcast mode for 2 DQ PHYs 
           HWIO_OUTX((DDR_PHY_SS_BASE + SEQ_DDR_SS_DDRSS_AHB2PHY_SWMAN_OFFSET), 
                      AHB2PHY_SWMAN_AHB2PHY_BROADCAST_EN_CFG_LOWER, 
                      PCH_DQs(ch));

           // Initialize the DDR PHY DQ PCC Link List
           DDR_PHY_rtn_dq_pcc_link_list_load (BROADCAST_BASE);

           // Enable broadcast mode for 1 CA PHYs 
           HWIO_OUTX((DDR_PHY_SS_BASE + SEQ_DDR_SS_DDRSS_AHB2PHY_SWMAN_OFFSET), 
                      AHB2PHY_SWMAN_AHB2PHY_BROADCAST_EN_CFG_LOWER, 
                      PCH_CAs(ch));

           // Initialize the DDR PHY CA PCC Link List
           DDR_PHY_rtn_ca_pcc_link_list_load (BROADCAST_BASE);

           // Initialize the DDR CC PCC Link List
           DDR_CC_rtn_pcc_link_list_load (reg_offset_ddr_cc + DDR_CC_OFFSET);
      
  

          // Disable broadcast mask
          HWIO_OUTX((DDR_PHY_SS_BASE + SEQ_DDR_SS_DDRSS_AHB2PHY_SWMAN_OFFSET),
                    AHB2PHY_SWMAN_AHB2PHY_BROADCAST_EN_CFG_LOWER, 0x0);   

           // Set master CA PHY, enable automatic IO calibration, and perform manual IO calibration
           //HWIO_OUTX(reg_offset_ddr_phy + CA0_DDR_PHY_OFFSET, DDR_PHY_DDRPHY_UPDATE_INTF_CFG, 0x3000);
           //HWIO_OUTXF(reg_offset_ddr_phy + CA0_DDR_PHY_OFFSET, DDR_PHY_DDRPHY_IOCTLR_CTRL_CFG, IO_CAL_AUTO, 1);

                  
      }    
   }
   		   HWIO_OUTX(REG_OFFSET_DDR_PHY_CH(1) + CA0_DDR_PHY_OFFSET, DDR_PHY_DDRPHY_UPDATE_INTF_CFG, 0x3000);		//1/13/17 Channel1 master enabled
           HWIO_OUTXF(REG_OFFSET_DDR_PHY_CH(1) + CA0_DDR_PHY_OFFSET, DDR_PHY_DDRPHY_IOCTLR_CTRL_CFG, IO_CAL_AUTO, 1);
           DDR_PHY_hal_cfg_sw_iocal (REG_OFFSET_DDR_PHY_CH(1) + CA0_DDR_PHY_OFFSET);
}
 
#if DSF_ECDT_EN
//================================================================================================//
// PHY eCDT.
//================================================================================================//
void DDR_PHY_CC_eCDT_Override(DDR_STRUCT *ddr, EXTENDED_CDT_STRUCT *ecdt, DDR_CHANNEL channel)
{
    uint8  ch           = 0;
    uint8  prfs_index   = 0;
    uint8  freq_index   = 0;
    uint8  dq_index     = 0;
    uint8  ca_index     = 0;

    uint32 reg_offset_ddr_phy_ca[NUM_CA_PCH] = {0};
    uint32 reg_offset_ddr_phy_dq[NUM_DQ_PCH] = {0};
    
    PHY_BUS  dq     = DQ;
    PHY_BUS  ca     = CA;

    for (ch = 0; ch < NUM_CH; ch++)
    {    
        if ((channel >> ch) & 0x1)
        { 
            reg_offset_ddr_phy_dq[0] = REG_OFFSET_DDR_PHY_CH(ch) + DQ0_DDR_PHY_OFFSET;
            reg_offset_ddr_phy_dq[1] = REG_OFFSET_DDR_PHY_CH(ch) + DQ1_DDR_PHY_OFFSET;
           // reg_offset_ddr_phy_dq[2] = REG_OFFSET_DDR_PHY_CH(ch) + DQ2_DDR_PHY_OFFSET;
           // reg_offset_ddr_phy_dq[3] = REG_OFFSET_DDR_PHY_CH(ch) + DQ3_DDR_PHY_OFFSET;
            reg_offset_ddr_phy_ca[0] = REG_OFFSET_DDR_PHY_CH(ch) + CA0_DDR_PHY_OFFSET;
           // reg_offset_ddr_phy_ca[1] = REG_OFFSET_DDR_PHY_CH(ch) + CA1_DDR_PHY_OFFSET;
            
            for (freq_index = 0; freq_index < NUM_ECDT_PRFS_BANDS; freq_index++)
            {               
                prfs_index = DDRSS_Get_Freq_Index (ddr, ecdt->extended_cdt_ecdt.msm_drv_str_odt_rdt2[freq_index].frequency_in_kHz);        
                
                // Array bounds exceed check for KlockWork error suppression - simply return. 
                // DSF behavior unpredictable after this point. This condition is not expected to happen since 
                // it will only occur when frequency_in_kHz exceeds the highest frequency in the supported frequency plan.
                if(prfs_index >= NUM_ECDT_PRFS_BANDS)
                {
                    return;
                }
                
                // DQ byte_lane loop.
                for(dq_index = 0; dq_index < dq; dq_index++)
                {
                    if(ecdt->extended_cdt_ecdt.msm_drv_str_odt_rdt2[prfs_index].msm_drive_strength_dq.apply_override == 1)
                    {
                        // Note: The pull-up values for both DQS and DQ are from the same element in the structure.
                        HWIO_OUTXF(reg_offset_ddr_phy_dq[dq_index] + prfs_offset_LO[prfs_index], DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_LO_CFG, PULL_UP_DQS_CNTL, 
                                    ecdt->extended_cdt_ecdt.msm_drv_str_odt_rdt2[prfs_index].msm_drive_strength_dq.pull_up_drive_strength);
                        HWIO_OUTXF(reg_offset_ddr_phy_dq[dq_index] + prfs_offset_LO[prfs_index], DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_LO_CFG, PULL_UP_DQ_CNTL, 
                                    ecdt->extended_cdt_ecdt.msm_drv_str_odt_rdt2[prfs_index].msm_drive_strength_dq.pull_up_drive_strength);
                                            
                        // Note: The pull-down values for both DQS and DQ are from the same element in the structure.
                        HWIO_OUTXF(reg_offset_ddr_phy_dq[dq_index] + prfs_offset_LO[prfs_index], DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_LO_CFG, ODRV_DQS, 
                                    ecdt->extended_cdt_ecdt.msm_drv_str_odt_rdt2[prfs_index].msm_drive_strength_dq.pull_down_drive_strength);
                        HWIO_OUTXF(reg_offset_ddr_phy_dq[dq_index] + prfs_offset_LO[prfs_index], DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_LO_CFG, ODRV_DQ, 
                                    ecdt->extended_cdt_ecdt.msm_drv_str_odt_rdt2[prfs_index].msm_drive_strength_dq.pull_down_drive_strength);
                        
                        HWIO_OUTXF(reg_offset_ddr_phy_dq[dq_index] + prfs_offset_LO[prfs_index], DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_LO_CFG, DRIVER_VOH_MODE, 
                                    ecdt->extended_cdt_ecdt.msm_drv_str_odt_rdt2[prfs_index].msm_drive_strength_dq.vOH);                        
                    }
                    if(ecdt->extended_cdt_ecdt.msm_drv_str_odt_rdt2[prfs_index].msm_odt.apply_override == 1)
                    {
                        HWIO_OUTXF(reg_offset_ddr_phy_dq[dq_index] + prfs_offset_HI[prfs_index], DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_HI_CFG, DQS_ODT_ENABLE, 
                                    ecdt->extended_cdt_ecdt.msm_drv_str_odt_rdt2[prfs_index].msm_odt.dqs_odt_enable);                        
                        
                        HWIO_OUTXF(reg_offset_ddr_phy_dq[dq_index] + prfs_offset_HI[prfs_index], DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_HI_CFG, ODT_IN_DQS, 
                                    ecdt->extended_cdt_ecdt.msm_drv_str_odt_rdt2[prfs_index].msm_odt.dqs_odt);
                        
                        HWIO_OUTXF(reg_offset_ddr_phy_dq[dq_index] + prfs_offset_HI[prfs_index], DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_HI_CFG, DQ_ODT_ENABLE, 
                                    ecdt->extended_cdt_ecdt.msm_drv_str_odt_rdt2[prfs_index].msm_odt.dq_odt_enable);
    
                        HWIO_OUTXF(reg_offset_ddr_phy_dq[dq_index] + prfs_offset_HI[prfs_index], DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_HI_CFG, ODT_IN_DQ_H, 
                                    (ecdt->extended_cdt_ecdt.msm_drv_str_odt_rdt2[prfs_index].msm_odt.dq_odt >> 1));
                        HWIO_OUTXF(reg_offset_ddr_phy_dq[dq_index] + prfs_offset_LO[prfs_index], DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_LO_CFG, ODT_IN_DQ_L, 
                                    ecdt->extended_cdt_ecdt.msm_drv_str_odt_rdt2[prfs_index].msm_odt.dq_odt);
                    }
                    if(ecdt->extended_cdt_ecdt.msm_drv_str_odt_rdt2[prfs_index].msm_rd_t2.apply_override == 1)
                    {
                        HWIO_OUTXF(reg_offset_ddr_phy_dq[dq_index] + prfs_index * 4, DDR_PHY_DDRPHY_CDCEXT_RDT2_0_CTL_CFG, HP_COARSE_R0, 
                                ecdt->extended_cdt_ecdt.msm_drv_str_odt_rdt2[prfs_index].msm_rd_t2.rd_t2_coarse_cdc);
                        HWIO_OUTXF(reg_offset_ddr_phy_dq[dq_index] + prfs_index * 4, DDR_PHY_DDRPHY_CDCEXT_RDT2_0_CTL_CFG, HP_COARSE_R1, 
                                ecdt->extended_cdt_ecdt.msm_drv_str_odt_rdt2[prfs_index].msm_rd_t2.rd_t2_coarse_cdc);
                    }
                } // DQ byte_lane loop.
                
                // CA byte_lane loop.
                for(ca_index = 0; ca_index < ca; ca_index++)
                {
                    if(ecdt->extended_cdt_ecdt.msm_drv_str_odt_rdt2[prfs_index].msm_drive_strength_ca.apply_override == 1)
                    {
                        // Note: The pull-up values for both DQS and DQ are from the same element in the structure.
                        HWIO_OUTXF(reg_offset_ddr_phy_ca[ca_index] + prfs_offset_LO[prfs_index], DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_LO_CFG, PULL_UP_DQS_CNTL, 
                                    ecdt->extended_cdt_ecdt.msm_drv_str_odt_rdt2[prfs_index].msm_drive_strength_ca.pull_up_drive_strength);
                        HWIO_OUTXF(reg_offset_ddr_phy_ca[ca_index] + prfs_offset_LO[prfs_index], DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_LO_CFG, PULL_UP_DQ_CNTL, 
                                    ecdt->extended_cdt_ecdt.msm_drv_str_odt_rdt2[prfs_index].msm_drive_strength_ca.pull_up_drive_strength);
                        
                        // Note: The pull-down values for both DQS and DQ are from the same element in the structure.
                        HWIO_OUTXF(reg_offset_ddr_phy_ca[ca_index] + prfs_offset_LO[prfs_index], DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_LO_CFG, ODRV_DQS, 
                                    ecdt->extended_cdt_ecdt.msm_drv_str_odt_rdt2[prfs_index].msm_drive_strength_ca.pull_down_drive_strength);
                        HWIO_OUTXF(reg_offset_ddr_phy_ca[ca_index] + prfs_offset_LO[prfs_index], DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_LO_CFG, ODRV_DQ, 
                                    ecdt->extended_cdt_ecdt.msm_drv_str_odt_rdt2[prfs_index].msm_drive_strength_ca.pull_down_drive_strength);
                                            
                        HWIO_OUTXF(reg_offset_ddr_phy_ca[ca_index] + prfs_offset_LO[prfs_index], DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_LO_CFG, DRIVER_VOH_MODE, 
                                    ecdt->extended_cdt_ecdt.msm_drv_str_odt_rdt2[prfs_index].msm_drive_strength_ca.vOH);
                    }
                } // CA byte_lane loop.
            
            } // freq_index loop.
            
        }        
    } // ch.
 
}
#endif
