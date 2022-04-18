/****************************************************************************
 QUALCOMM Proprietary Design Data
 Copyright (c) 2015, Qualcomm Technologies Incorporated. All rights reserved.
 ****************************************************************************/
/*==============================================================================
                                EDIT HISTORY

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/DSFTargetLib/rpm/ddrss/bimc/mc230/header/bimc_rpm.h#5 $
$DateTime: 2017/01/08 08:21:59 $
$Author: pwbldsvc $
================================================================================
when       who          what, where, why
--------   ---          --------------------------------------------------------
05/04/14   arindamm     First edit history header. Add new entries at top.
================================================================================*/

#ifndef __BIMC_RPM_H__
#define __BIMC_RPM_H__

#include "HALhwio.h"
#include "HAL_SNS_DDR.h"
#include "bimc_seq_hwiobase.h"
#include "bimc_seq_hwioreg.h"
#include "target_config_rpm.h"
#include "bimc_data_rpm.h"

#define REG_OFFSET_GLOBAL0              (BIMC_BASE + SEQ_BIMC_GLOBAL0_OFFSET)

#define REG_OFFSET_GLOBAL1              (BIMC_BASE + SEQ_BIMC_GLOBAL1_OFFSET)

#define REG_OFFSET_SCMO(uint8)          ((uint8 == 0) ? \
                                        (BIMC_BASE + SEQ_BIMC_BIMC_S_DDR0_SCMO_OFFSET) : \
                                        (BIMC_BASE + SEQ_BIMC_BIMC_S_DDR1_SCMO_OFFSET))

#define REG_OFFSET_DPE(uint8)           ((uint8 == 0) ? \
                                        (BIMC_BASE + SEQ_BIMC_BIMC_S_DDR0_DPE_OFFSET)  : \
                                        (BIMC_BASE + SEQ_BIMC_BIMC_S_DDR1_DPE_OFFSET))

#define REG_OFFSET_SHKE(uint8)          ((uint8 == 0) ? \
                                        (BIMC_BASE + SEQ_BIMC_BIMC_S_DDR0_SHKE_OFFSET) : \
                                        (BIMC_BASE + SEQ_BIMC_BIMC_S_DDR1_SHKE_OFFSET))

#define REG_OFFSET_DTTS(uint8)          ((uint8 == 0) ? \
                                        (BIMC_BASE + SEQ_BIMC_BIMC_S_DDR0_DTTS_CFG_OFFSET) : \
                                        (BIMC_BASE + SEQ_BIMC_BIMC_S_DDR1_DTTS_CFG_OFFSET))


#define CH_1HOT(uint8)                  ((uint8 == 0) ? \
                                        DDR_CH0 : \
                                        DDR_CH1)

#define CS_1HOT(uint8)                  ((uint8 == 0) ? \
                                        DDR_CS0 : \
                                        DDR_CS1)

#define CH_INX(DDR_CHANNEL)             ((DDR_CHANNEL == DDR_CH0) ? \
                                        0: \
                                        1)

#define CS_INX(DDR_CHIPSELECT)          ((DDR_CHIPSELECT == DDR_CS0) ? \
                                        0 : \
                                        1)


#define     XO_PERIOD_IN_PS 52080   //52.08ns 

#define     BIMC_CH_OFFSET  (SEQ_BIMC_BIMC_S_DDR1_OFFSET-SEQ_BIMC_BIMC_S_DDR0_OFFSET)

#define     PERIODIC_TRAINING_FREQ_THRESHOLD  770000

#define     TMRW_FREQ_THRESHOLD  714286

#define     PHY_LVDS_GATING_DELAY   0

typedef enum
{
    WAIT_TIMER_CLOCK  = 0x0 ,
    WAIT_XO_CLOCK     = 0x1
} BIMC_Wait_Timer_Domain;

typedef enum
{
    RL_DBI_OFF = 0x0 ,
    RL_DBI_ON  = 0x1 ,
    WL         = 0x2 ,
    MR2_WR_VAL = 0x3
} RL_WL_Table_Sel;

typedef enum
{
    DEVICE_WIDTH_IS_x16 = 0x0 ,
    DEVICE_WIDTH_IS_x8  = 0x1 
} Device_Io_Width_sel;

// #defines for all valid MRs
#define JEDEC_MR_0   0x0
#define JEDEC_MR_1   0x1
#define JEDEC_MR_2   0x2
#define JEDEC_MR_3   0x3
#define JEDEC_MR_4   0x4
#define JEDEC_MR_5   0x5
#define JEDEC_MR_6   0x6
#define JEDEC_MR_7   0x7
#define JEDEC_MR_8   0x8
#define JEDEC_MR_9   0x9
#define JEDEC_MR_11  0xB
#define JEDEC_MR_12  0xC
#define JEDEC_MR_13  0xD
#define JEDEC_MR_14  0xE
#define JEDEC_MR_15  0xF
#define JEDEC_MR_16  0x10
#define JEDEC_MR_17  0x11
#define JEDEC_MR_18  0x12
#define JEDEC_MR_19  0x13
#define JEDEC_MR_20  0x14
#define JEDEC_MR_22  0x16
#define JEDEC_MR_23  0x17
#define JEDEC_MR_24  0x18
#define JEDEC_MR_31	 0x1F
#define JEDEC_MR_32  0x20
#define JEDEC_MR_39  0x27
#define JEDEC_MR_40  0x28


// Common functions
void BIMC_Wait_Timer_Setup(DDR_CHANNEL ChannelSel,BIMC_Wait_Timer_Domain one_xo_zero_timer_clk, uint32 timer_value);
void BIMC_MR_Write (DDR_CHANNEL ChannelSel, DDR_CHIPSELECT chip_select, uint32 Addr, uint32 Data);
void BIMC_Extended_MR_Write (DDR_CHANNEL channel, DDR_CHIPSELECT chip_select, uint32 MR_addr, uint32 MR_data);
uint32 BIMC_MR_Read (DDR_CHANNEL ChannelSel, DDR_CHIPSELECT chip_select,uint32 Addr);
void BIMC_ZQ_Calibration_Lpddr (DDR_STRUCT *ddr, DDR_CHANNEL ChannelSel, DDR_CHIPSELECT chip_select);
void BIMC_ZQ_Calibration (DDR_STRUCT  *ddr, DDR_CHANNEL channel, DDR_CHIPSELECT chip_select);
void BIMC_All_Periodic_Ctrl (DDR_STRUCT *ddr, DDR_CHANNEL channel, DDR_CHIPSELECT chip_select, uint8 periodic_enable);
uint32 BIMC_Temp_Ctrl_Min_Freq (DDR_STRUCT *ddr, DDR_CHANNEL channel);
void BIMC_Downtime_Request_Ctrl (DDR_CHANNEL channel, uint8 enable);


// Freq switch functions
uint8 BIMC_RL_WL_Freq_Index (DDR_STRUCT *ddr, uint32 clk_freq_khz);
uint8 BIMC_Freq_Switch_Params_Index (DDR_STRUCT *ddr, uint32 clk_freq_khz);
boolean BIMC_Pre_Clock_Switch (DDR_STRUCT *ddr, DDR_CHANNEL channel);
boolean BIMC_Post_Clock_Switch (DDR_STRUCT *ddr,DDR_CHANNEL channel);

// Self refresh functions
void BIMC_HW_Self_Refresh_Ctrl (DDR_STRUCT *ddr, uint8 ch, uint8 cs, uint8 enable);
void BIMC_Enter_Self_Refresh (DDR_STRUCT *ddr, DDR_CHANNEL ChannelSel, DDR_CHIPSELECT chip_select);
void BIMC_Exit_Self_Refresh (DDR_STRUCT *ddr, DDR_CHANNEL ChannelSel, DDR_CHIPSELECT chip_select);

// Power Collapse functions
void BIMC_Enter_Power_Collapse (DDR_STRUCT *ddr, DDR_CHANNEL channel);
void BIMC_Pre_Exit_Power_Collapse (DDR_STRUCT *ddr, DDR_CHANNEL channel);
void BIMC_Exit_Power_Collapse (DDR_STRUCT *ddr, DDR_CHANNEL channel);

// LPDDRx Deep Power Down
boolean BIMC_Enter_Deep_Power_Down (DDR_STRUCT *ddr, DDR_CHANNEL channel, DDR_CHIPSELECT chip_select);
boolean BIMC_Exit_Deep_Power_Down (DDR_STRUCT *ddr, DDR_CHANNEL channel, DDR_CHIPSELECT chip_select);

#endif
