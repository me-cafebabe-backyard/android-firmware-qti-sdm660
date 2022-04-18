/****************************************************************************
 QUALCOMM Proprietary Design Data
 Copyright (c) 2015, Qualcomm Technologies Incorporated. All rights reserved.
 ****************************************************************************/
/*==============================================================================
                              EDIT HISTORY
$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/DSFTargetLib/boot/target/SDM630_660/header/ddr_phy_technology.h#3 $
$DateTime: 2017/01/08 08:21:59 $
$Author: pwbldsvc $

==============================================================================*/

#define CA_PATTERN_NUM              4

#define NUM_CA_PHY_BIT             6

#define COARSE_VREF_MAX_VALUE       0x37
#define COARSE_VREF_MAX_VALUE_WRITE 0x32 //Limit VREF to max number of possible steps.
#define COARSE_CDC_MAX_VALUE        0x18
#define MIN_WIDTH                   0x1
#define COARSE_VREF                 (COARSE_VREF_MAX_VALUE + 1)
#define COARSE_CDC                  (COARSE_CDC_MAX_VALUE + 1)

#define FINE_VREF_MAX_VALUE         0x8 
#define FINE_CDC_MAX_VALUE          0x8 
#define FINE_VREF                   (FINE_VREF_MAX_VALUE + 1)
#define FINE_CDC                    (FINE_CDC_MAX_VALUE + 1)
#define FINE_RD_CDC                 0x10
#define PERBIT_CDC_MAX_VALUE        0xF 
#define DBI_WR_PBIT_OFFSET          0

#define COARSE_STEP_IN_PS           50//60 // 58ps at high voltage // New value updated as per istari
#define FINE_STEP_IN_PS             8//9  // 9.5ps at high voltage
#define FINE_STEPS_PER_COARSE       6  // changed for periodic training purposes, was 7

#define WRITE_FINE_CDC_MIN          5
#define WRITE_FINE_CDC_MAX          10
#define WRITE_TERMINATED_MR14_VREF  0x19
#define WRITE_UNTERMINATED_MR14_VREF 0x4B
#define MAX_TDQS2DQ_IN_PS           800

#define DQS_VREF                   0x8// 0xF // Need to check
#define MIN_DTTS_TRACKING_PRFS      0x6

#define LOW_SPEED_HALF_CYC_CONV_THRESHOLD       400  //((COARSE_CDC_MAX_VALUE * COARSE_STEP_IN_PS)/2) //=600ps.
#define LOW_SPEED_NO_HALF_CYC_COARSE_CDC_VALUE  0x10 //0x12 //0x14 //0x10
#define LOW_SPEED_NO_HALF_CYC_FINE_CDC_VALUE    0x0
#define LOW_SPEED_RD_COARSE_CDC_VALUE           0xA
#define LOW_SPEED_HALF_CYC_RETIMER_VALUE        0
#define LOW_SPEED_NO_HALF_CYC_RETIMER_VALUE     1


#define F_RANGE_0                   250000
#define F_RANGE_1                   450000 //600000
#define F_RANGE_2                   600000 //700000
#define F_RANGE_3                   800000 //900000
#define F_RANGE_4                   1050000 //1150000
#define F_RANGE_5                   1500000 
#define F_RANGE_6                   1600000 //1750000
#define F_RANGE_7                   1866000 //2133000

