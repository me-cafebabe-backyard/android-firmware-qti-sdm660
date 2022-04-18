/****************************************************************************
 QUALCOMM Proprietary Design Data
 Copyright (c) 2015, Qualcomm Technologies Incorporated. All rights reserved.
 ****************************************************************************/
/*==============================================================================
                                EDIT HISTORY

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/DSFTargetLib/boot/target/SDM630_660/sdi/ddrss_init_sdi.h#25 $
$DateTime: 2018/12/26 02:55:51 $
$Author: pwbldsvc $
================================================================================
when       who          what, where, why
--------   ---          --------------------------------------------------------
05/04/14   arindamm     First edit history header. Add new entries at top.
================================================================================*/

#include "bimc_seq_hwioreg_sdi.h"
//#include "ddr_ss_seq_hwioreg_sdi.h"
#include "ddr_ss_seq_hwioreg.h"
#include "mccc_seq_hwioreg_sdi.h"
#include "seq_hwio_sdi.h"

#include "HAL_SNS_DDR.h"

// DDR System Firmware Version
#define TARGET_DDR_SYSTEM_FIRMWARE_MAJOR_VERSION            37
#define TARGET_DDR_SYSTEM_FIRMWARE_MINOR_VERSION            0

#define TARGET_DDR_SYSTEM_FIRMWARE_RPM_MAJOR_VERSION        22
#define TARGET_DDR_SYSTEM_FIRMWARE_RPM_MINOR_VERSION        0
// Updated only when RPM files change



#define TARGET_DDR_SYSTEM_FIRMWARE_MAJOR_VERSION_SHIFT     16
#define TARGET_DDR_SYSTEM_FIRMWARE_MINOR_VERSION_SHIFT      0
#define TARGET_DDR_SYSTEM_FIRMWARE_VERSION   ((TARGET_DDR_SYSTEM_FIRMWARE_MAJOR_VERSION << TARGET_DDR_SYSTEM_FIRMWARE_MAJOR_VERSION_SHIFT) \
                                            | (TARGET_DDR_SYSTEM_FIRMWARE_MINOR_VERSION << TARGET_DDR_SYSTEM_FIRMWARE_MINOR_VERSION_SHIFT))

#define TARGET_DDR_SYSTEM_FIRMWARE_RPM_MAJOR_VERSION_SHIFT     16
#define TARGET_DDR_SYSTEM_FIRMWARE_RPM_MINOR_VERSION_SHIFT      0
#define TARGET_DDR_SYSTEM_FIRMWARE_RPM_VERSION   ((TARGET_DDR_SYSTEM_FIRMWARE_RPM_MAJOR_VERSION << TARGET_DDR_SYSTEM_FIRMWARE_RPM_MAJOR_VERSION_SHIFT) \
                                                | (TARGET_DDR_SYSTEM_FIRMWARE_RPM_MINOR_VERSION << TARGET_DDR_SYSTEM_FIRMWARE_RPM_MINOR_VERSION_SHIFT))

// Define silicon target or emulation target. Some portions of the DDR System Firmware will or will not
// be compiled depending on what this macro is defined as. 
// If TARGET_SILICON is defined as a 0, it implies an emulation build.
// If TARGET_SILICON is defined as a 1, it implies a real-silicon build.
// If TARGET_SILICON is already defined (on the compiler command line), do not override that definition.
//    This will allow users to override this emulation/silicon flag at compile time without changing the DSF.
#ifndef TARGET_SILICON
#define TARGET_SILICON                         1 
#endif // #ifndef TARGET_SILICON

// BIMC and PHY Core Architecture, Major and Minor versions.
#define TARGET_BIMC_ARCH_VERSION               2
#define TARGET_BIMC_CORE_MAJOR_VERSION         3
#define TARGET_BIMC_CORE_MINOR_VERSION         3
#define TARGET_PHY_CORE_MAJOR_VERSION          4
#define TARGET_PHY_CORE_MINOR_VERSION          0

// Define DDR base address in the chip address map from APPS viewpoint.
//    From the RPM viewpoint, DDR is also at 0x80000000, but this address
//    is remapped to 0x60000000 by setting RPM_PAGE_SELECT to 2.
#define DDR_BASE                        0x80000000
#define STARLORD_PLATFORM_ID               0x3006
// COMPILING_RPM_PROC is a SVE-specific build flag that kicks in for RPM build in the VI environment.
#ifdef COMPILING_RPM_PROC
    // Define DDR base address in the chip address map from RPM viewpoint
    // The RPM maps the BIMC area to 0x61000000
    #define DDR_PHY_SS_BASE             0x61080000
    #define BIMC_BASE                   0x61000000
    #define MCCC_BASE                   0x60FFD000
#else
    #define DDR_PHY_SS_BASE             0x01080000
    #define BIMC_BASE                   0x01000000
    #define MCCC_BASE                   0x00FFD000
#endif // COMPILING_RPM_PROC

#define NUM_CH                          2 // Number of DDR channels

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
										
#define REG_OFFSET_MCCC                 (MCCC_BASE + SEQ_MCCC_MCCC_MCCC_REGS_OFFSET)


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

#define     MCCC_CH_OFFSET  (SEQ_MCCC_MCCC_CH1_MCCC_CH_REGS_OFFSET-SEQ_MCCC_MCCC_CH0_MCCC_CH_REGS_OFFSET)

#define REG_OFFSET_MCCC_CH(uint8)       ((uint8 == 0) ? \
                                        (MCCC_BASE + SEQ_MCCC_MCCC_CH0_MCCC_CH_REGS_OFFSET) : \
                                        (MCCC_BASE + SEQ_MCCC_MCCC_CH1_MCCC_CH_REGS_OFFSET))
										

#define MCCC_INT_FREQ_SWITCH_STATE_EXIT_COND_CFG  0x30008000
#define MCCC_INIT_FREQ_SWITCH_STATE_EXIT_COND_CFG 0x3000801C


#define CONVERT_CYC_TO_PS        1000000000

#define DDR_PHY_OFFSET           0x1000     // DDR PHY Address offset (4k Bytes)
#define CA0_DDR_PHY_OFFSET       0x0000
#define DQ0_DDR_PHY_OFFSET       0x2000
#define DQ1_DDR_PHY_OFFSET       0x3000
#define DDR_CC_OFFSET            0x6000
#define DDR_CC_MCCC_OFFSET       0xF000

#define REG_OFFSET_DDR_PHY_CH(ch) ((ch == 0)  ? \
                                  DDR_PHY_SS_BASE : \
                                  DDR_PHY_SS_BASE + 0x7000)
                                  
#define REG_OFFSET_DDR_CC_CH(ch)  ((ch == 0)  ? \
                                  DDR_PHY_SS_BASE :\
                                  DDR_PHY_SS_BASE )

#define BROADCAST_BASE DDR_PHY_SS_BASE + SEQ_DDR_SS_DDRSS_AHB2PHY_BROADCAST_SWMAN1_OFFSET



typedef enum
{
    WAIT_TIMER_CLOCK  = 0x0 ,
    WAIT_XO_CLOCK     = 0x1
} BIMC_Wait_Timer_Domain;

typedef enum
{
    
    RL_DBI_OFF_x16 = 0x0 ,
    RL_DBI_ON_x16  = 0x1 ,
    RL_DBI_OFF_x8  = 0x2 ,
    RL_DBI_ON_x8   = 0x3 ,
    WL             = 0x4 ,
    MR2_WR_VAL     = 0x5
} RL_WL_Table_Sel;



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
#define JEDEC_MR_31  0x1F
#define JEDEC_MR_32  0x20
#define JEDEC_MR_40  0x28



// The addresses of the MPM low power control registers
#define REG_ADDR__MPM2_MPM_LOW_POWER_CFG 0x004A0070
#define REG_ADDR__MPM2_MPM_DDR_PHY_FREEZEIO_EBI1 0x004AB004

// Code from ddrss.c
boolean HAL_DDR_Init_sdi (DDR_STRUCT *ddr, DDR_CHANNEL channel, DDR_CHIPSELECT chip_select, uint32 clk_freq_khz);

// Similar to bimc_config.c or ddr_phy_config.c
void Set_config_sdi (uint32 offset, uint32 config_base[][2] );

// Code from bimc_init.c
void BIMC_Config_sdi(DDR_STRUCT *ddr);
boolean BIMC_Init_Pre_MCCC_Init_GHS_sdi(DDR_STRUCT *ddr, DDR_CHANNEL channel);
boolean BIMC_Init_Post_MCCC_Init_GHS_sdi(DDR_STRUCT *ddr, DDR_CHANNEL channel);
void BIMC_Pre_Init_Setup_sdi (DDR_STRUCT *ddr, DDR_CHANNEL channel, DDR_CHIPSELECT chip_select);
void BIMC_Memory_Device_Init_sdi (DDR_STRUCT *ddr, DDR_CHANNEL channel, DDR_CHIPSELECT chip_select);
void BIMC_DDR_Addr_Setup_Warm_sdi (DDR_STRUCT *ddr, uint8 ch, uint8 cs);
DDR_CHIPSELECT BIMC_DDR_Access_Enable_sdi(DDR_STRUCT *ddr, DDR_CHANNEL channel, DDR_CHIPSELECT chip_select);
void BIMC_Post_Init_Setup_Warm_sdi (DDR_STRUCT *ddr, DDR_CHANNEL channel, DDR_CHIPSELECT chip_select);

// From bimc_rpm.c
void BIMC_Exit_Self_Refresh_sdi (DDR_STRUCT *ddr, DDR_CHANNEL channel, DDR_CHIPSELECT chip_select);  
void BIMC_Enter_Self_Refresh_sdi (DDR_STRUCT *ddr, DDR_CHANNEL channel, DDR_CHIPSELECT chip_select);  
void BIMC_ZQ_Calibration_sdi (DDR_STRUCT  *ddr, DDR_CHANNEL channel, DDR_CHIPSELECT chip_select); 

// From bimc_common_rpm.c
void BIMC_Wait_Timer_Setup_sdi (DDR_CHANNEL channel, BIMC_Wait_Timer_Domain one_xo_zero_timer_clk, uint32 timer_value); 
void BIMC_MR_Write_sdi (DDR_CHANNEL channel, DDR_CHIPSELECT chip_select, uint32 MR_addr, uint32 MR_data); 
uint32 BIMC_MR_Read_sdi (DDR_CHANNEL channel, DDR_CHIPSELECT chip_select, uint32 MR_addr);  
void BIMC_HW_Self_Refresh_Ctrl_sdi (DDR_STRUCT *ddr, uint8 ch, uint8 cs, uint8 enable);  
void BIMC_All_Periodic_Ctrl_sdi (DDR_STRUCT *ddr, DDR_CHANNEL channel, DDR_CHIPSELECT chip_select, uint8 enable); 

// Code from bimc_data_rpm.c
uint8 BIMC_RL_WL_Freq_Index_sdi (DDR_STRUCT *ddr, uint32 clk_freq_khz);

// Code from bimc_lpddr4.c
void BIMC_Program_Lpddr_AC_Parameters_sdi(DDR_STRUCT *ddr, DDR_CHANNEL channel);
void BIMC_Memory_Device_Init_Lpddr_sdi (DDR_STRUCT *ddr, DDR_CHANNEL channel , DDR_CHIPSELECT chip_select);

// Code from bimc_lpddr4_rpm.c
void BIMC_ZQ_Calibration_Lpddr_sdi (DDR_STRUCT  *ddr, DDR_CHANNEL channel, DDR_CHIPSELECT chip_select);

// Code from ddrss_common_rpm.c
void DDRSS_ddr_phy_sw_freq_switch_sdi (DDR_STRUCT *ddr, uint8 ch);

// Code from ddrss_phy_cc_init.c
void DDR_PHY_CC_Config_sdi(DDR_STRUCT *ddr);
boolean DDR_PHY_Init_GHS_sdi (DDR_STRUCT *ddr, DDR_CHANNEL channel);
void DDR_PHY_CC_init_sdi (DDR_STRUCT *ddr, DDR_CHANNEL channel);


// Code from ddr_phy_hal_cfg_init.c
void DDR_PHY_hal_cfg_sw_handshake_complete_sdi( uint32 _inst_ );
void DDR_PHY_hal_cfg_sw_handshake_stop_sdi( DDR_STRUCT *ddr, uint32 _inst_ );
void DDR_PHY_hal_cfg_sw_handshake_start_sdi( DDR_STRUCT *ddr, uint32 _inst_ );
void DDR_PHY_hal_cfg_sw_iocal_sdi( uint32 _inst_, uint8 master_phy );


// Code from mccc.c
void MCCC_Config_sdi(DDR_STRUCT *ddr);
boolean MCCC_Init_sdi(DDR_STRUCT *ddr, DDR_CHANNEL channel);
void MCCC_Clk_CBCR_Enable_sdi(DDR_STRUCT *ddr, DDR_CHANNEL channel);

void DDR_CC_MCCC_Config_sdi(DDR_STRUCT *ddr);


