/*! \file  pm_config_target_pbs_ram.c
 *  
 *  \brief  File Contains the PMIC Set Mode Driver Implementation
 *  \details Set Mode Driver implementation is responsible for setting and getting 
 *  all mode settings such as Register values, memory values, etc.
 *  
 *    PMIC code generation Version: 1.0.0.0
 *    Date: 2018-09-12
 *    PMIC SBL Version: SD660M-SBL-20180912-b0x10_v0x31 - Approved
 *    PBS RAM Version: PM660_RAM_b0x00_v0x1B
 *    PBS RAM Version: PM660L_RAM_b0x10_v0x20
 *    This file contains code for Target specific settings and modes.
 *  
 *  &copy; Copyright 2018 Qualcomm Technologies Inc., All Rights Reserved
 */

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This document is created by a code generator, therefore this section will
  not contain comments describing changes made to the module.

$Header: //components/rel/boot.xf/1.4/QcomPkg/Library/PmicLib/target/sdm660_pm660_pm660l/psi/pm_config_target_pbs_ram.c#24 $ 
$DateTime: 2018/09/24 07:48:32 $  $Author: pwbldsvc $

when       who     what, where, why
--------   ---     ---------------------------------------------------------- 

===========================================================================*/

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/

#include "pm_target_information.h"
#include "pm_config_sbl.h"

/*========================== PBS RAM LUT =============================*/

// To handle multiple PBS RAM configuration for different rev of the same PMIC or for multiple PMICs,
// a double dimension array of PBS RAM data is used. The data field of the specific command (in pm_config_target_sbl_sequence.c)
// to program PBS RAM will hold the index to the PBS RAM that needs to be used. during programming.
// Example:
// 1.sid; 2.data; 3.base_address; 4.offset;  5.reg_operation; 6.rev_id_operation; 7.rev_id;
// {0, 0x00, 0x0000, 0x000, PM_SBL_PBS_RAM, EQUAL, REV_ID_2_0},  //data = 0:  Use the 1st set of PBS RAM data if PMIC Rev ID = REV_ID_2_0
// {0, 0x01, 0x0000, 0x000, PM_SBL_PBS_RAM, EQUAL, REV_ID_1_0},  //data = 1:  Use the 2nd set of PBS RAM data if PMIC Rev ID = REV_ID_1_0

pm_pbs_ram_data_type
pm_pbs_seq [ ][PBS_RAM_DATA_SIZE] =
{
   // "PM660_RAM_b0x00_v0x1B"
   {
      //data  offset  base_addr  sid
      { 0x52,	0x53,	0x42,	0x50},	// W#0 - 	0x800 RAM signature PBSR" Checksum"
      { 0x00,	0x1B,	0x01,	0x18},	// W#1 - 	0x804 Header offset, Header Version, PBS RAM Revision, PBS RAM Branch
      { 0x2C,	0x08,	0xFF,	0x83},	// W#2 - 	0x808 Start of trigger jump table:
      { 0x68,	0x08,	0xFF,	0x83},	// W#3 - 	0x80C
      { 0xC4,	0x08,	0xFF,	0x83},	// W#4 - 	0x810
      { 0x38,	0x09,	0xFF,	0x83},	// W#5 - 	0x814
      { 0xC4,	0x0F,	0xFF,	0x83},	// W#6 - 	0x818 Fixed Offset = RAM-Base-Addr + 0x18 + 0x00 => SLEEP-SET
      { 0xCC,	0x0F,	0xFF,	0x83},	// W#7 - 	0x81C Fixed Offset = RAM-Base-Addr + 0x18 + 0x04 => PON X Reasons
      { 0xFF,	0xFF,	0xFF,	0xFB},	// W#8 - 	0x820 Fixed Offset = RAM-Base-Addr + 0x18 + 0x08 => Empty (No RTRR)/Spare
      { 0xFF,	0xFF,	0xFF,	0xFB},	// W#9 - 	0x824 Fixed Offset = RAM-Base-Addr + 0x18 + 0x0C => Empty (No HLOS)/Spare
      { 0xFF,	0xFF,	0xFF,	0xFB},	// W#10 - 	0x828 Fixed Offset = RAM-Base-Addr + 0x18 + 0x10 => Empty (Spare registers)/LPG
      { 0xFF,	0x48,	0x71,	0x00},	// W#11 - 	1BYTE WRITE 0xFF TO PBS_CLIENT0__TRIG_LATCHED_CLR; Clear all latched sequences in PBS PON Client 0
      { 0xFB,	0x08,	0x08,	0x40},	// W#12 - 	1BYTE READ PON__FSM_STATUS TO RB; Readback PON FSM Status and store to Buffer RB
      { 0x04,	0xB0,	0xFF,	0x90},	// W#13 - 	SKIP 1 Lines if RB NOT EQUAL 0x04 (MASK=0xFF); DVDD_CONFIG = State 4
      { 0x14,	0x00,	0xFF,	0x9B},	// W#14 - 	GOTO OTP_DVDD_CONFIG (OTP) & End there
      { 0x01,	0xB0,	0xFF,	0x91},	// W#15 - 	Skip if RB NOT EQUAL 0x01 (PON = State 1)
      { 0x00,	0x57,	0x08,	0x00},	// W#16 - 	PMICPR-475: Disable PMIC_WD only at the beginning of PON or WR
      { 0x14,	0x00,	0xFF,	0x9B},	// W#17 - 	GOTO OTP_DVDD_CONFIG (OTP) & End there
      { 0x06,	0xB0,	0xFF,	0x90},	// W#18 - 	Skip if RB NOT EQUAL 0x06 (FAULT = State 6)
      { 0xA0,	0x09,	0xFF,	0x83},	// W#19 - 	GOTO CLIENT0_FAULT_SEQUENCE & End there
      { 0x02,	0xB0,	0xFF,	0x90},	// W#20 - 	Skip if RB NOT EQUAL 0x02 (POFF = State 2)
      { 0x08,	0x0A,	0xFF,	0x83},	// W#21 - 	GOTO CLIENT0_POFF_SEQUENCE & End there
      { 0x07,	0xB0,	0xFF,	0x90},	// W#22 - 	Skip if RB NOT EQUAL 0x07 (WARM RESET = State 7)
      { 0x48,	0x0B,	0xFF,	0x83},	// W#23 - 	GOTO CLIENT0_WARM_RESET_SEQUENCE & End there
      { 0x00,	0x91,	0x08,	0x00},	// W#24 - 	Undefined State - NACK PON
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#25 - 	End Sequence
      { 0xF3,	0x0A,	0x72,	0x40},	// W#26 - 	Read Client 1 trigger latch status and store to Buffer R3
      { 0x01,	0x30,	0x01,	0x91},	// W#27 - 	Skip if not Bit 0 = LN_BB_CLK1_EN
      { 0x01,	0x48,	0x72,	0x00},	// W#28 - 	1BYTE WRITE 0x01 TO PBS_CLIENT1__TRIG_LATCHED_CLR; Clear Latched Trigger - Bit 0
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#29 - 	CL1_TRIG0:EMPTY => Replace with GOTO once defined.
      { 0x02,	0x30,	0x02,	0x91},	// W#30 - 	Skip if not Bit 1 = NC (SL/SH PowerGrid use it for Type-C UFP crude sensing WA)
      { 0x02,	0x48,	0x72,	0x00},	// W#31 - 	Clear Latched Trigger - Bit 1
      { 0x8C,	0x0C,	0xFF,	0x83},	// W#32 - 	CL1_TRIG1: CLIENT1_TRIG1_SCHG_WA
      { 0x04,	0x30,	0x04,	0x91},	// W#33 - 	Skip if not Bit 2 = EOSR_TIMER ; Client1_SCHG_EOSR
      { 0x04,	0x48,	0x72,	0x00},	// W#34 - 	Clear Latched Trigger - Bit 2
      { 0x5C,	0x0C,	0xFF,	0x83},	// W#35 - 	CL1_TRIG2: GOTO_CLIENT1_SCHG_EOSR & End there
      { 0x08,	0x30,	0x08,	0x91},	// W#36 - 	Skip if not Bit 3 = PRM (KPDPWR_N || CBLPWR_N || PS_HOLD)
      { 0x08,	0x48,	0x72,	0x00},	// W#37 - 	Clear Latched Trigger - Bit 3
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#38 - 	CL1_TRIG3:EMPTY => Replace with GOTO once defined.
      { 0x10,	0x30,	0x10,	0x91},	// W#39 - 	Skip if not Bit 4 = SLEEP_b
      { 0x10,	0x48,	0x72,	0x00},	// W#40 - 	Clear Latched Trigger - Bit 4
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#41 - 	CL1_TRIG4:EMPTY => Replace with GOTO once defined.
      { 0x40,	0x30,	0x40,	0x91},	// W#42 - 	Skip if not Bit 6 = OTS2
      { 0x40,	0x48,	0x72,	0x00},	// W#43 - 	Clear Latched Trigger - Bit 6
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#44 - 	CL1_TRIG6:EMPTY => Replace with GOTO once defined.
      { 0x80,	0x30,	0x80,	0x91},	// W#45 - 	Skip if not Bit 7 = SW Trigger (Sleep/Wake)
      { 0x80,	0x48,	0x72,	0x00},	// W#46 - 	Clear Latched Trigger - Bit 7
      { 0x90,	0x0C,	0xFF,	0x83},	// W#47 - 	CL1_TRIG7: CLIENT1_SYSTEM_SLEEP_WAKE_SEQUENCE
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#48 - 	
      { 0xFC,	0x54,	0x09,	0x40},	// W#49 - 	PBSREG.RC will store MISC_SPARE_5 (used in CL2_TRIG0 & CL2_TRIG7)
      { 0xFB,	0x69,	0x41,	0x40},	// W#50 - 	PBSREG.RB will store the latest value of FG_BATT_INFO.ESR_PULL_DOWN_CFG (used in CL2_TRIG0 & CL2_TRIG7)
      { 0x00,	0x15,	0x73,	0x00},	// W#51 - 	Disable PBS_Client2 SEQ_ENDED Interrupt - won't fire for any of CLIENT2 Sequences, except when re-enabled
      { 0xF4,	0x0A,	0x73,	0x40},	// W#52 - 	1BYTE READ PBS_CLIENT2__TRIG_LATCHED TO R4; Read Client 2 trigger latch status and store to Buffer R4
      { 0x01,	0x40,	0x01,	0x91},	// W#53 - 	Skip if not Bit 0 = DTEST MUX / EOSR_TIMER
      { 0x01,	0x48,	0x73,	0x00},	// W#54 - 	1BYTE WRITE 0x01 TO PBS_CLIENT2__TRIG_LATCHED_CLR; Clear Latched Trigger - Bit 0
      { 0x70,	0x0D,	0xFF,	0x83},	// W#55 - 	CL2_TRIG0: CLIENT2_EOSR_TIMER_EXPIRED_SEQUENCE
      { 0x02,	0x40,	0x02,	0x91},	// W#56 - 	Skip if not Bit 1 = EUD(SCHG)
      { 0x02,	0x48,	0x73,	0x00},	// W#57 - 	1BYTE WRITE 0x02 TO PBS_CLIENT2__TRIG_LATCHED_CLR; Clear Latched Trigger - Bit 1
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#58 - 	CL2_TRIG1:EMPTY => Replace with GOTO once defined.
      { 0x04,	0x40,	0x04,	0x91},	// W#59 - 	Skip if not Bit 2 = GPIO09 (WCSS_VCTRL)
      { 0x04,	0x48,	0x73,	0x00},	// W#60 - 	1BYTE WRITE 0x04 TO PBS_CLIENT2__TRIG_LATCHED_CLR; Clear Latched Trigger - Bit 2
      { 0xF4,	0x0D,	0xFF,	0x83},	// W#61 - 	CL2_TRIG2: CLIENT2_WCSS_VCTRL_SEQUENCE
      { 0x08,	0x40,	0x08,	0x91},	// W#62 - 	Skip if not Bit 3 = GPIO05 (WLAN_RF_VCTRL)
      { 0x08,	0x48,	0x73,	0x00},	// W#63 - 	1BYTE WRITE 0x08 TO PBS_CLIENT2__TRIG_LATCHED_CLR; Clear Latched Trigger - Bit 3
      { 0x38,	0x0E,	0xFF,	0x83},	// W#64 - 	CL2_TRIG3: CLIENT2_WLAN_RF_VCTRL_SEQUENCE
      { 0x10,	0x40,	0x10,	0x91},	// W#65 - 	Skip if not Bit 4 = GPIO04 (LNBBCLK3_EN)
      { 0x10,	0x48,	0x73,	0x00},	// W#66 - 	1BYTE WRITE 0x10 TO PBS_CLIENT2__TRIG_LATCHED_CLR; Clear Latched Trigger - Bit 4
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#67 - 	CL2_TRIG4:EMPTY => Replace with GOTO once defined.
      { 0x20,	0x40,	0x20,	0x91},	// W#68 - 	Skip if not Bit 5 - GPIO08 (SLB trigger from Drax)
      { 0x20,	0x48,	0x73,	0x00},	// W#69 - 	
      { 0x1C,	0x0F,	0xFF,	0x83},	// W#70 - 	Reschedule using CLIENT2_COMMON_END_RESCHED_EVAL_SEQUENCE
      { 0x40,	0x40,	0x40,	0x91},	// W#71 - 	Skip if not Bit 6 = BUA
      { 0x40,	0x48,	0x73,	0x00},	// W#72 - 	
      { 0x5C,	0x0E,	0xFF,	0x83},	// W#73 - 	CL2_TRIG6: CLIENT2_BUA_SEQUENCE
      { 0x80,	0x40,	0x80,	0x91},	// W#74 - 	Skip if not Bit 7 = SW Trigger
      { 0x80,	0x48,	0x73,	0x00},	// W#75 - 	
      { 0x80,	0x0E,	0xFF,	0x83},	// W#76 - 	CL2_TRIG7: CLIENT2_SW_TRIGGER
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#77 - 	
      { 0xF5,	0x0A,	0x74,	0x40},	// W#78 - 	Read Client 3 trigger latch status and store to Buffer R5
      { 0x01,	0x50,	0x01,	0x91},	// W#79 - 	Skip if NOT Bit 0 = DTEST MUX / PD_PHY_IRQ_MUX
      { 0x01,	0x48,	0x74,	0x00},	// W#80 - 	Clear Latched Trigger - Bit 0
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#81 - 	CL3_TRIG0:EMPTY => Replace with GOTO once defined. (DTEST MUX / PD_PHY_IRQ_MUX)
      { 0x02,	0x50,	0x02,	0x91},	// W#82 - 	Skip if NOT Bit 1 = SCHG Snarl Timer
      { 0x02,	0x48,	0x74,	0x00},	// W#83 - 	Clear Latched Trigger - Bit 1
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#84 - 	CL3_TRIG1:EMPTY => Replace with GOTO once defined. (SCHG Snarl Timer)
      { 0x04,	0x50,	0x04,	0x91},	// W#85 - 	Skip if NOT Bit 2 = Charger Test MUX
      { 0x04,	0x48,	0x74,	0x00},	// W#86 - 	Clear Latched Trigger - Bit 2
      { 0x3C,	0x0F,	0xFF,	0x83},	// W#87 - 	CL3_TRIG2: Client3_SCHG_PD_WA1_Crude_Sensor
      { 0x08,	0x50,	0x08,	0x91},	// W#88 - 	Skip if NOT Bit 3 = QI_PMA_ON
      { 0x08,	0x48,	0x74,	0x00},	// W#89 - 	Clear Latched Trigger - Bit 3
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#90 - 	CL3_TRIG3:EMPTY => Replace with GOTO once defined. (QI_PMA_ON)
      { 0x10,	0x50,	0x10,	0x91},	// W#91 - 	Skip if NOT Bit 4 = BATFET OCP
      { 0x10,	0x48,	0x74,	0x00},	// W#92 - 	Clear Latched Trigger - Bit 4
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#93 - 	CL3_TRIG4:EMPTY => Replace with GOTO once defined. (BATFET OCP)
      { 0x20,	0x50,	0x20,	0x91},	// W#94 - 	Skip if NOT Bit 5 = FG BCL
      { 0x20,	0x48,	0x74,	0x00},	// W#95 - 	Clear Latched Trigger - Bit 5
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#96 - 	CL3_TRIG5:EMPTY => Replace with GOTO once defined. (FG BCL)
      { 0x40,	0x50,	0x40,	0x91},	// W#97 - 	Skip if NOT Bit 6 - Fuel Gauge Test MUX
      { 0x40,	0x48,	0x74,	0x00},	// W#98 - 	Clear Latched Trigger - Bit 6
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#99 - 	CL3_TRIG6:EMPTY => Replace with GOTO once defined. (FG_TEST_MUX)
      { 0x80,	0x50,	0x80,	0x91},	// W#100 - 	Skip if NOT Bit 7 = SW Trigger
      { 0x80,	0x48,	0x74,	0x00},	// W#101 - 	1BYTE WRITE 0x80 TO PBS_CLIENT3__TRIG_LATCHED_CLR; Clear Latched Trigger - Bit 7
      { 0x8C,	0x0F,	0xFF,	0x83},	// W#102 - 	CL3_TRIG7: CLIENT3_SW_TRIGGER
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#103 - 	
      { 0x05,	0xDA,	0x2C,	0x10},	// W#104 - 	PMICPR-827: PM660 (Groot) REF_BYP stays on after fault POFF (due to fix in PMICPR-801)
      { 0x2E,	0x44,	0x60,	0x00},	// W#105 - 	PMICPR-942: CalRC offset compensation (+55ppm offset for RTC when PMIC is OFF)
      { 0xEC,	0x0B,	0xFF,	0x9B},	// W#106 - 	Record PON REASONS into dataset (Circular Buffer with History-Size = 3)
      { 0xF4,	0x80,	0x08,	0x00},	// W#107 - 	When configuring the KPDPWR_N Stage 1 reset timer, corresponding PON trigger must be disabled during the re-configuration;PMICPR-356
      { 0x0B,	0x00,	0xFF,	0xC1},	// W#108 - 	Wait 300us to REGISTER get updated.
      { 0x42,	0x90,	0x16,	0x00},	// W#109 - 	1BYTE WRITE Force STAT low ([7:6]=b'01) so that SMB goes to suspend
      { 0x02,	0x66,	0x13,	0x00},	// W#110 - 	1BYTE WRITE Revert USB5/1 setting to 500mA
      { 0x38,	0x63,	0x13,	0x00},	// W#111 - 	0x1363 [7] WIPWR_RST_EUD_CFG = 0
      { 0x00,	0x53,	0x10,	0x00},	// W#112 - 	1BYTE WRITE 0x00 TO SCHG_CHGR__CFG; Disable VDISCHG_EN_CFG to reduce off current.
      { 0x01,	0x45,	0x16,	0x00},	// W#113 - 	Enable Charger Shutdown CR- 0000171925
      { 0x24,	0x68,	0x13,	0x00},	// W#114 - 	Charger WA-31. Revert to UFP mode (same as FTRIM setting) to avoid unexpected PON
      { 0x04,	0xDF,	0x14,	0x00},	// W#115 - 	CR176140: Set chicken bit high to avoid lockup at following PON
      { 0x88,	0x48,	0x14,	0x01},	// W#116 - 	1BYTE WRITE 0x88 TO S1_CTRL__PD_CTL; Enable strong + leak pulldown
      { 0x88,	0x48,	0x17,	0x01},	// W#117 - 	1BYTE WRITE 0x88 TO S2_CTRL__PD_CTL; Enable strong + leak pulldown
      { 0x88,	0x48,	0x1A,	0x01},	// W#118 - 	1BYTE WRITE 0x88 TO S3_CTRL__PD_CTL; Enable strong + leak pulldown
      { 0x88,	0x48,	0x1D,	0x01},	// W#119 - 	1BYTE WRITE 0x88 TO S4_CTRL__PD_CTL; Enable strong + leak pulldown
      { 0x88,	0x48,	0x20,	0x01},	// W#120 - 	1BYTE WRITE 0x88 TO S5_CTRL__PD_CTL; Enable strong + leak pulldown
      { 0x88,	0x48,	0x23,	0x01},	// W#121 - 	1BYTE WRITE 0x88 TO S6_CTRL__PD_CTL; Enable strong + leak pulldown
      { 0x80,	0x48,	0x52,	0x01},	// W#122 - 	PMICPR-711: Re-enable L19A PD in FAULT (since it was disabled in SBL)
      { 0xEA,	0x01,	0xFF,	0xC1},	// W#123 - 	WAIT 15016 us; Wait 15ms for VREGs to discharge completely before allowing the next PON trigger
      { 0xF6,	0xC8,	0x08,	0x40},	// W#124 - 	1BYTE READ PON__FAULT_REASON1 TO R6; Read FAULT_REASON1 and store to Buffer R6
      { 0x40,	0x61,	0x40,	0x91},	// W#125 - 	SKIP 2 Lines if R6 EQUAL 0x40 (MASK=0x40); Skip next 2 lines if Bit-6 (UVLO) = 1
      { 0x00,	0x7F,	0x08,	0x00},	// W#126 - 	1BYTE WRITE 0x00 TO PON__SMPL_CTL; Disable SMPL
      { 0x00,	0x46,	0x40,	0x00},	// W#127 - 	PMICPR-407; This is to fix the issue of REF_BYP stays ON during a fault due to a FG write which ignores all resets.
      { 0x40,	0x91,	0x08,	0x00},	// W#128 - 	1BYTE WRITE 0x40 TO PON__PBS_INTERFACE; ACK PON
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#129 - 	End of Sequence
      { 0x00,	0x7F,	0x08,	0x00},	// W#130 - 	1BYTE WRITE 0x00 TO PON__SMPL_CTL; Disable SMPL
      { 0xF4,	0x80,	0x08,	0x00},	// W#131 - 	PMICPR-1039: Groot: Re-enable KPDPWR_N PON_TRIGGER in POFF-Sequence
      { 0x2E,	0x44,	0x60,	0x00},	// W#132 - 	PMICPR-942: CalRC offset compensation (+55ppm offset for RTC when PMIC is OFF)
      { 0xD8,	0x0B,	0xFF,	0x9B},	// W#133 - 	GOTO_SUB_NOID ASSERT_EXT_RESET; Set PON_RESET_N and PON_OUT low
      { 0xEC,	0x0B,	0xFF,	0x9B},	// W#134 - 	Record PON REASONS into dataset (Circular Buffer with History-Size = 3)
      { 0x04,	0x98,	0x08,	0x10},	// W#135 - 	1BYTE WRITE 0x04 TO PON__RESET_CTL; Assert shutdown1_rb
      { 0x03,	0x00,	0xFF,	0xC1},	// W#136 - 	WAIT 91 us; Wait 3 SLEEP_CLK cycles for reset changes to propagate through clock domains
      { 0x06,	0x98,	0x08,	0x10},	// W#137 - 	1BYTE WRITE 0x06 TO PON__RESET_CTL; De-assert shutdown1_rb
      { 0x00,	0x40,	0xC7,	0x00},	// W#138 - 	Configure GPIO08 to Dig INPUT
      { 0x04,	0x42,	0xC7,	0x00},	// W#139 - 	Set SLB to PD 10uA
      { 0x38,	0x63,	0x13,	0x00},	// W#140 - 	0x1363 [7] WIPWR_RST_EUD_CFG = 0
      { 0xE0,	0x0A,	0x51,	0x88},	// W#141 - 	GOTO DISABLE_WAIT_FUNCTION_LOCAL LN_BB_CLK1; LNBBCLK1
      { 0xE0,	0x0A,	0x40,	0x89},	// W#142 - 	GOTO DISABLE_WAIT_FUNCTION_LOCAL LDO1; VDDA_GPSADC/MIPI 1.25V
      { 0xE0,	0x0A,	0x4D,	0x89},	// W#143 - 	GOTO DISABLE_WAIT_FUNCTION_LOCAL LDO14; SENSORS (1.8V)
      { 0xE0,	0x0A,	0x14,	0x89},	// W#144 - 	GOTO DISABLE_WAIT_FUNCTION_LOCAL S1_CTRL; APC0 (Kryo Silver) 0.87V SLORD
      { 0xE0,	0x0A,	0x1A,	0x89},	// W#145 - 	GOTO DISABLE_WAIT_FUNCTION_LOCAL S3_CTRL; APC1 (Kryo Silver) 0.87V SHW
      { 0xE0,	0x0A,	0x47,	0x89},	// W#146 - 	GOTO DISABLE_WAIT_FUNCTION_LOCAL LDO08; EMMC/UFS 1.8V
      { 0xA5,	0xD0,	0x17,	0x01},	// W#147 - 	Check why this is done? (Mak 2017-02-20) TODO
      { 0xE0,	0x0A,	0x17,	0x89},	// W#148 - 	GOTO DISABLE_WAIT_FUNCTION_LOCAL S2_CTRL; S2A, LP4x internal regulator
      { 0xF4,	0x01,	0x76,	0x29},	// W#149 - 	WAIT 15250 us; Wait 15.25ms.  Store to Buffer R6. 146
      { 0x18,	0x0B,	0xFF,	0x9B},	// W#150 - 	
      { 0xA3,	0x00,	0x76,	0x29},	// W#151 - 	WAIT 10010 us; Wait 10ms.  Store to Buffer R6.  0x146
      { 0xEC,	0x0A,	0xFF,	0x9B},	// W#152 - 	
      { 0xE0,	0x0A,	0xC1,	0x88},	// W#153 - 	o SF1 (ALT_SLEEP_CLK)
      { 0xE0,	0x0A,	0x54,	0x88},	// W#154 - 	GOTO DISABLE_WAIT_FUNCTION_LOCAL  WLAN 38.4MHz
      { 0xE0,	0x0A,	0x5A,	0x88},	// W#155 - 	GOTO DISABLE_WAIT_FUNCTION_LOCAL  SLEEP_CLK1
      { 0xE0,	0x0A,	0x0B,	0x88},	// W#156 - 	GOTO DISABLE_WAIT_FUNCTION_LOCAL VREF_MSM; 1.25V reference for UIM and SD
      { 0xE0,	0x0A,	0x4A,	0x89},	// W#157 - 	GOTO DISABLE_WAIT_FUNCTION_LOCAL LDO11; USB_SS_Retimer
      { 0x80,	0x48,	0x52,	0x01},	// W#158 - 	PMICPR-711: Re-enable L19A PD in POFF (since it was disabled in SBL)
      { 0xE0,	0x0A,	0x52,	0x89},	// W#159 - 	GOTO DISABLE_WAIT_FUNCTION_LOCAL LDO19; WCN3990 CHAIN0 (Wipwr)
      { 0xE0,	0x0A,	0x45,	0x89},	// W#160 - 	GOTO DISABLE_WAIT_FUNCTION_LOCAL LDO06; WCN RF,GPS, Metis (Wipwr)
      { 0xE0,	0x0A,	0x48,	0x89},	// W#161 - 	GOTO DISABLE_WAIT_FUNCTION_LOCAL LDO09; WCN_XO (Wipwr)
      { 0xE0,	0x0A,	0x49,	0x89},	// W#162 - 	GOTO DISABLE_WAIT_FUNCTION_LOCAL LDO10; PHY-PLL-BB_CLK-USB
      { 0xE0,	0x0A,	0xC5,	0x88},	// W#163 - 	GOTO DISABLE_WAIT_FUNCTION_LOCAL Set GPIO06 (PMK SLEEP_CLK_IN)
      { 0xE0,	0x0A,	0x4C,	0x89},	// W#164 - 	GOTO DISABLE_WAIT_FUNCTION_LOCAL LDO13; PX3 1.8v
      { 0xE0,	0x0A,	0x20,	0x89},	// W#165 - 	GOTO DISABLE_WAIT_FUNCTION_LOCAL S5_CTRL; MV sub
      { 0xE0,	0x0A,	0x50,	0x88},	// W#166 - 	GOTO DISABLE_WAIT_FUNCTION_LOCAL XO; OK to Skip LDO_XO?
      { 0xE0,	0x0A,	0x1D,	0x89},	// W#167 - 	GOTO DISABLE_WAIT_FUNCTION_LOCAL S4_CTRL; HV sub
      { 0xE0,	0x0A,	0x42,	0x89},	// W#168 - 	GOTO DISABLE_WAIT_FUNCTION_LOCAL LDO03A, WTR 1V
      { 0x46,	0x01,	0x76,	0x29},	// W#169 - 	WAIT 10010 us; Wait 10ms.  Store to Buffer R6. 146
      { 0x18,	0x0B,	0xFF,	0x9B},	// W#170 - 	
      { 0xA3,	0x00,	0xFF,	0xC1},	// W#171 - 	WAIT 4972 us; Wait 5ms
      { 0x42,	0x90,	0x16,	0x00},	// W#172 - 	1BYTE WRITE Force STAT low ([7:6]=b'01) so that SMB goes to suspend
      { 0x01,	0x45,	0x16,	0x00},	// W#173 - 	eNABLE cHARGER Shutdown CR- 0000171925
      { 0x00,	0x46,	0x40,	0x00},	// W#174 - 	1BYTE WRITE 0x00 TO FG_BATT_SOC__EN_CTL; disable FG algorithm (CR-0000171925).  This bit emulatoes what the SHDN_N HW signal did on earlier PMIs.
      { 0x05,	0x52,	0x45,	0x00},	// W#175 - 	Put RRADC in Shutdown (not shutdown , just pause RRADC)
      { 0x02,	0x66,	0x13,	0x00},	// W#176 - 	1BYTE WRITE Revert USB5/1 setting to 500mA
      { 0x24,	0x68,	0x13,	0x00},	// W#177 - 	Charger WA-31. Revert to UFP mode (same as FTRIM setting) to avoid unexpected PON
      { 0x04,	0xDF,	0x14,	0x00},	// W#178 - 	CR176140: Set chicken bit high to avoid lockup at following PON
      { 0xE0,	0x0A,	0x24,	0x88},	// W#179 - 	
      { 0xE0,	0x0A,	0x2C,	0x88},	// W#180 - 	
      { 0x46,	0x01,	0xFF,	0xC1},	// W#181 - 	WAIT 10010 us; Wait 10ms for VREGs to discharge completely before allowing the next PON trigger
      { 0x40,	0x91,	0x08,	0x00},	// W#182 - 	1BYTE WRITE 0x40 TO PON__PBS_INTERFACE; ACK PON
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#183 - 	End of Sequence
      { 0x00,	0x46,	0xFF,	0x04},	// W#184 - 	1BYTE WRITE 0x00 TO 0x46; Write 0x00 to 0x46 (enable register in the peripheral)
      { 0x21,	0x00,	0xFF,	0xC1},	// W#185 - 	WAIT 1068 us; Wait 33+2 32kHz clock cycles.  Increased for PM8019 2.0.
      { 0xFF,	0xFF,	0xFF,	0x8F},	// W#186 - 	End of subroutine. PC = Stored PC.; Go back to next line of the calling function
      { 0x01,	0x00,	0xFF,	0xC1},	// W#187 - 	Wait 1 CLK Cycle before checking
      { 0xF1,	0x08,	0xC7,	0x40},	// W#188 - 	Read GPIO08 Status (GPIO_VAL) and store to Buffer R1
      { 0x01,	0x10,	0x01,	0x92},	// W#189 - 	We will exit  = '1'
      { 0x01,	0x40,	0xC7,	0x00},	// W#190 - 	Configure GPIO08 to Dig Output
      { 0x00,	0x44,	0xC7,	0x00},	// W#191 - 	Set SLB LOW and continue
      { 0xFF,	0xFF,	0xFF,	0x8F},	// W#192 - 	
      { 0x01,	0x00,	0x76,	0x25},	// W#193 - 	Subtract 1 from the loop count (R6)
      { 0x00,	0x06,	0x00,	0x90},	// W#194 - 	If the subi in the previous command resulted in a carry then we have reached the terminal count.
      { 0xEC,	0x0A,	0xFF,	0x83},	// W#195 - 	
      { 0x00,	0x91,	0x08,	0x00},	// W#196 - 	Time count expired.  Nack the PON! SID=0, PID=8, Addr = 0x91
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#197 - 	End of Sequence
      { 0x00,	0x40,	0xC7,	0x00},	// W#198 - 	Configure GPIO08 to Dig INPUT
      { 0x00,	0x42,	0xC7,	0x00},	// W#199 - 	Set SLB to PU
      { 0x01,	0x00,	0xFF,	0xC1},	// W#200 - 	Wait 30us before trying again
      { 0xF1,	0x08,	0xC7,	0x40},	// W#201 - 	Read GPIO08 Status (GPIO_VAL) and store to Buffer R1
      { 0x00,	0x10,	0x01,	0x91},	// W#202 - 	Skip the next line if GPIO08_STATUS1 (bit 0) is high
      { 0x05,	0x42,	0xC7,	0x00},	// W#203 - 	Set SLB to No pull
      { 0xFF,	0xFF,	0xFF,	0x8F},	// W#204 - 	return to the next linE of the calling routing
      { 0x01,	0x00,	0x76,	0x25},	// W#205 - 	Subtract 1 from the loop count (R6)
      { 0x00,	0x06,	0x00,	0x90},	// W#206 - 	If the subi in the previous command resulted in a carry then we have reached the terminal count.
      { 0x20,	0x0B,	0xFF,	0x83},	// W#207 - 	
      { 0x00,	0x91,	0x08,	0x00},	// W#208 - 	Time count expired.  Nack the PON! SID=0, PID=8, Addr = 0x91
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#209 - 	End of Sequence; Return
      { 0x00,	0x57,	0x08,	0x00},	// W#210 - 	PMICPR-475: Disable PMIC_WD only at the beginning of WR (here) & PON
      { 0xD8,	0x0B,	0xFF,	0x9B},	// W#211 - 	GOTO_SUB_NOID ASSERT_EXT_RESET; Set PON_RESET_N and PON_OUT low
      { 0x8E,	0x01,	0xFF,	0xC1},	// W#212 - 	WAIT 12.2 ms = 400 SLEEP_CLK cycles before setting PON_OUT high again (to signal Warm Reset to slave PMICs)
      { 0x40,	0x49,	0x09,	0x10},	// W#213 - 	Send PON_OUT high to all PMICs.
      { 0xEC,	0x0B,	0xFF,	0x9B},	// W#214 - 	Record PON REASONS into dataset (Circular Buffer with History-Size = 3)
      { 0xC6,	0x44,	0x1D,	0x01},	// W#215 - 	Restore this setting, in case warm reset occurred in sleep
      { 0x02,	0x5A,	0x1D,	0x11},	// W#216 - 	Restore this setting, in case warm reset occurred in sleep
      { 0x06,	0x45,	0x1D,	0x01},	// W#217 - 	Change to Auto mode, in case it were in Retention (after Sleep)
      { 0x06,	0x49,	0x1D,	0x01},	// W#218 - 	Change to Auto mode, in case it were FORCE_PFM (after Sleep)
      { 0xF8,	0x40,	0x1D,	0x01},	// W#219 - 	S4A: LB for Default-VSET = 0x07_F8 => 2040 mV
      { 0x07,	0x41,	0x1D,	0x01},	// W#220 - 	S4A: UB for Default-VSET = 0x07_F8 => 2040 mV
      { 0x02,	0x98,	0x08,	0x10},	// W#221 - 	1BYTE WRITE 0x02 TO PON__RESET_CTL; Assert warm_rb
      { 0x03,	0x00,	0xFF,	0xC1},	// W#222 - 	WAIT 91.5 us; Wait 3 SLEEP_CLK cycles for reset changes to propagate through clock domains
      { 0x06,	0x98,	0x08,	0x10},	// W#223 - 	1BYTE WRITE 0x06 TO PON__RESET_CTL; De-assert warm_rb
      { 0x07,	0x45,	0x40,	0x01},	// W#224 - 	: 27
      { 0x07,	0x45,	0x42,	0x01},	// W#225 - 	: 05
      { 0x07,	0x45,	0x47,	0x01},	// W#226 - 	: 24
      { 0x07,	0x45,	0x4A,	0x01},	// W#227 - 	: 13
      { 0x07,	0x45,	0x4C,	0x01},	// W#228 - 	: 08
      { 0x07,	0x45,	0x4D,	0x01},	// W#229 - 	: 26
      { 0x07,	0x45,	0x52,	0x01},	// W#230 - 	: 12
      { 0x07,	0x45,	0x4E,	0x01},	// W#231 - 	: N/A
      { 0x07,	0x45,	0x4F,	0x01},	// W#232 - 	: N/A
      { 0x07,	0x45,	0x50,	0x01},	// W#233 - 	: N/A
      { 0x07,	0x45,	0x51,	0x01},	// W#234 - 	: N/A
      { 0x42,	0x90,	0x16,	0x00},	// W#235 - 	1BYTE WRITE Force STAT low ([7:6]=b'01) so that SMB goes to suspend
      { 0xC4,	0x80,	0x13,	0x00},	// W#236 - 	REVERT REGISTER TO ftrim SETTINGS upon WARM RESET
      { 0x00,	0x52,	0x11,	0x00},	// W#237 - 	REVERT REGISTER TO ftrim SETTINGS upon WARM RESET
      { 0x00,	0xC2,	0x14,	0x10},	// W#238 - 	REVERT REGISTER TO ftrim SETTINGS upon WARM RESET
      { 0x04,	0xDF,	0x14,	0x00},	// W#239 - 	CR176140: Set chicken bit high to avoid lockup at following PON
      { 0xAA,	0x04,	0xFF,	0xC1},	// W#240 - 	WAIT 36417 us; Wait 1194 cycles of SLEEP_CLK (36.4 ms) for MSM prep time during warm reset
      { 0x9B,	0x19,	0x76,	0x29},	// W#241 - 	2BYTE R6 = 0x199B; (2+0x199b) X 30.5 uS = 200 mS.  Pass this into enable wait pon as a parameter
      { 0x99,	0x00,	0x7D,	0x28},	// W#242 - 	1BYTE OFFSET = 0x99; Set offset to PON_RESET_N_CTL register (0x99)
      { 0x18,	0x10,	0x08,	0x88},	// W#243 - 	GOTO ROM_ENABLE_WAIT_RELATIVE (ROM) PON; enable wait PON subroutine will deassert PON_RESET_N and wait for PS_HOLD to go high
      { 0x40,	0x91,	0x08,	0x00},	// W#244 - 	1BYTE WRITE 0x40 TO PON__PBS_INTERFACE; ACK PON
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#245 - 	End of Warm-Reset Sequence
      { 0x00,	0x43,	0x08,	0x02},	// W#246 - 	1BYTE WRITE 0x00 TO SID:2 0x0800__0x43; Set SPMI_SLAVE_RB to 0 to tolerate glitches during power down
      { 0x00,	0x99,	0x08,	0x00},	// W#247 - 	1BYTE WRITE 0x00 TO PON__PON_RESET_N_CTL; Assert PON_RESET_N low
      { 0x00,	0x49,	0x09,	0x10},	// W#248 - 	1BYTE WRITE 0x00 TO MISC__PON_OUT_CTL; Send PON_OUT low to all PMIC's.  Changing to SEC ACCESS (to updated in next .csv).
      { 0x01,	0x43,	0x08,	0x02},	// W#249 - 	1BYTE WRITE 0x01 TO SID:2 0x0800__0x43; Set SPMI_SLAVE_RB back to 1
      { 0xFF,	0xFF,	0xFF,	0x8F},	// W#250 - 	
      { 0x1C,	0x08,	0x70,	0xA1},	// W#251 - 	
      { 0x0C,	0x00,	0x70,	0x21},	// W#252 - 	2BYTE R0 = R0 + 0x0C (3 Rows + 0x04 Addr-Offset per Row)
      { 0x1C,	0x08,	0x72,	0xA1},	// W#253 - 	
      { 0x14,	0x00,	0x72,	0x21},	// W#254 - 	2BYTE R2 = R2 + 0x14 (5 Rows + 0x04 Addr-Offset per Row)
      { 0x04,	0x00,	0x78,	0x28},	// W#255 - 	1BYTE R8 = 0x04; Loop 4 times (Shift 4 DWords)
      { 0xF0,	0xFF,	0xF4,	0xA3},	// W#256 - 	4BYTE R4 = MEMADDR(R0); copy the last reason registers into a buffer
      { 0xF2,	0xFF,	0xF4,	0xA7},	// W#257 - 	4BYTE MEMADDR(R2) = R4; write the reasons to the location pointed to by the paste pointer
      { 0x01,	0x00,	0x78,	0x24},	// W#258 - 	
      { 0x00,	0x81,	0xFF,	0x92},	// W#259 - 	SKIP 3 Lines if R8 EQUAL 0x00 (MASK=0xFF); Loop Until loop count (R8) = 4
      { 0x04,	0x00,	0x70,	0x25},	// W#260 - 	2BYTE R0 = R0 - 0x04; Move read pointer to next (upper) DWORD
      { 0x04,	0x00,	0x72,	0x25},	// W#261 - 	2BYTE R2 = R2 - 0x04; Move write pointer to next (upper) DWORD
      { 0x00,	0x0C,	0xFF,	0x83},	// W#262 - 	
      { 0xF4,	0xC0,	0x08,	0x40},	// W#263 - 	
      { 0xF5,	0xC2,	0x08,	0x40},	// W#264 - 	
      { 0xF6,	0xC4,	0x08,	0x40},	// W#265 - 	
      { 0xF7,	0xC5,	0x08,	0x40},	// W#266 - 	
      { 0xF0,	0xFF,	0xF4,	0xA7},	// W#267 - 	4BYTE MEMADDR(R0) = R4
      { 0x04,	0x00,	0x70,	0x21},	// W#268 - 	2BYTE R0 = R0 + 0x04
      { 0xF4,	0xC7,	0x08,	0x40},	// W#269 - 	
      { 0xF5,	0xC8,	0x08,	0x40},	// W#270 - 	
      { 0xF6,	0xC9,	0x08,	0x40},	// W#271 - 	
      { 0xF7,	0x48,	0x60,	0x40},	// W#272 - 	1BYTE READ RTC_RW__RDATA0 TO R7; Fill the last byte with the RTC value.
      { 0xF8,	0x48,	0x60,	0x40},	// W#273 - 	1BYTE READ RTC_RW__RDATA0 TO R8; Fill the last byte with the RTC value.
      { 0xF8,	0xF7,	0x79,	0x26},	// W#274 - 	1BYTE R9 = R8 - R7
      { 0x00,	0x91,	0xFF,	0x90},	// W#275 - 	SKIP 1 Lines if R9 EQUAL 0x00 (MASK=0xFF); If data didn't match we retry.
      { 0x40,	0x0C,	0xFF,	0x83},	// W#276 - 	
      { 0xF0,	0xFF,	0xF4,	0xA7},	// W#277 - 	4BYTE MEMADDR(R0) = R4; Write data to address stored in R0
      { 0xFF,	0xFF,	0xFF,	0x8F},	// W#278 - 	End of subroutine. PC = Stored PC
      { 0x68,	0x0F,	0xFF,	0x9B},	// W#279 - 	Assert CHG Clock Req
      { 0xF1,	0x68,	0x13,	0x40},	// W#280 - 	R1 = 0x1368
      { 0x04,	0x11,	0x04,	0x94},	// W#281 - 	Skip next 5 lines if 0x1368[2]=1
      { 0x04,	0x00,	0xF1,	0x30},	// W#282 - 	Set R1[2]=1 --> SNK_EN_CMD=1
      { 0xF1,	0x68,	0x13,	0x08},	// W#283 - 	0x1368=R1 --> SNK_EN_CMD=1
      { 0x01,	0x59,	0x13,	0x00},	// W#284 - 	Set 0x1359[1]=0 --> Enable Crude Sensor
      { 0x78,	0x0F,	0xFF,	0x9B},	// W#285 - 	Revert PBS CHG Clock Req (SW Req is kept)
      { 0x42,	0x00,	0xFF,	0xC5},	// W#286 - 	Start 2ms timer
      { 0xFB,	0x00,	0xF1,	0x2C},	// W#287 - 	1BYTE R1 = R1 AND 0xFB ; Set R1[2]=0 --> SNK_EN_CMD=0
      { 0xF1,	0x68,	0x13,	0x08},	// W#288 - 	0x1368=R1 --> SNK_EN_CMD=0
      { 0x78,	0x0F,	0xFF,	0x9B},	// W#289 - 	Revert PBS CHG Clock Req (SW Req is kept)
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#290 - 	
      { 0x42,	0x00,	0xFF,	0xC5},	// W#291 - 	Start 2ms timer
      { 0xF7,	0x50,	0x72,	0x40},	// W#292 - 	Readback PBS_CLIENT1_SCRATCH1 and store to Buffer R7
      { 0x02,	0x70,	0xFF,	0x90},	// W#293 - 	If PBS_CLIENT1_SCRATCH1 != 0x02
      { 0x20,	0x0D,	0xFF,	0x83},	// W#294 - 	GOTO WAKE_SEQUENCE_START; Else
      { 0x01,	0x70,	0xFF,	0x90},	// W#295 - 	If PBS_CLIENT1_SCRATCH1 != 0x01
      { 0xA8,	0x0C,	0xFF,	0x83},	// W#296 - 	GOTO SLEEP_SEQUENCE_START; Else
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#297 - 	End of Sequence
      { 0xF7,	0x40,	0x11,	0x40},	// W#298 - 	Load R7 with the value in 0x1140 => SCHG_OTG_CMD_OTG
      { 0x01,	0x00,	0xF7,	0x2C},	// W#299 - 	Redundant: Mask-out other bits in R7 to only preserve Bit-0 = OTG_EN
      { 0xF8,	0x0B,	0x16,	0x40},	// W#300 - 	Load R8 with the value in 0x160B => SCHG_MISC_POWER_PATH_STATUS
      { 0x01,	0x00,	0xF8,	0x2C},	// W#301 - 	Redundant: Mask-out other bits in R8 to only preserve Bit-0 = VALID_INPUT_POWER_SOURCE
      { 0xF7,	0xF8,	0xF7,	0x32},	// W#302 - 	R7 = R7 || R8 = OTG_EN || VALID_INPUT_POWER_SOURCE
      { 0x01,	0x71,	0x01,	0x90},	// W#303 - 	Skip next config (that sets SCHG Clock to 200kHz) if OTG-Enabled or Valid Charger-Input present
      { 0x02,	0xDF,	0x14,	0x00},	// W#304 - 	USE 200K CLK instead of 19.2Mhz - only if OTG-Disabled or Charger-Input absent
      { 0x18,	0x08,	0x76,	0xA1},	// W#305 - 	Using Location stored in GOTO-Pointer at LOC_SLEEP_BACKUP_DATASET_HEAD
      { 0x10,	0x0D,	0x1D,	0x89},	// W#306 - 	Backup S4 Primary-Mode so that it can be restored during Wake-Up
      { 0x10,	0x0D,	0x20,	0x89},	// W#307 - 	Backup S5 Primary-Mode so that it can be restored during Wake-Up
      { 0x00,	0x5A,	0x1D,	0x11},	// W#308 - 	1BYTE WRITE 0x00 TO S4_CTRL__PS_THRES_ERRAMP; Set PS_VRST to 0mV to prevent mode under/overshoots (CR-175088)
      { 0x06,	0x45,	0x1D,	0x01},	// W#309 - 	PMICPR-1046: Set S4 Primary-Mode to AUTO
      { 0x05,	0x44,	0x1D,	0x11},	// W#310 - 	Disable PFM_IBOOST
      { 0x05,	0x49,	0x1D,	0x01},	// W#311 - 	Set S4 Secondary-Mode to FORCE_PFM
      { 0x04,	0x45,	0x20,	0x01},	// W#312 - 	Set S5 to RM
      { 0x05,	0x44,	0x20,	0x11},	// W#313 - 	Disable PFM_IBOOST
      { 0xF8,	0x43,	0x4E,	0x41},	// W#314 - 	Read LDO15A.VSET_VALID_UB (UIM1_LDO Enable & VSET_UB) & Store in R8
      { 0x07,	0x85,	0xFF,	0x92},	// W#315 - 	Skip Disabling VREF_MSM if UIM1 VALID_UB > 0x07 (i.e On @ ~3V)
      { 0xF8,	0x43,	0x50,	0x41},	// W#316 - 	Else Read LDO17A.VSET_VALID_UB (UIM2_LDO Enable & VSET_UB) & Store in R8
      { 0x07,	0x85,	0xFF,	0x90},	// W#317 - 	Skip Disabling VREF_MSM if UIM2 VALID_UB > 0x07 (i.e On @ ~3V)
      { 0x00,	0x46,	0x0B,	0x00},	// W#318 - 	Disable VREF_MSM if None of the UIM_LDOs are On @3V (Can be either On @1.8V or Off)
      { 0x00,	0x40,	0x38,	0x00},	// W#319 - 	1BYTE WRITE 0x00 TO VADC_HC9_BTM_2__MODE_CTL; Disable ADC comparators (saves 10uA on 9655)
      { 0x01,	0x46,	0x51,	0x00},	// W#320 - 	Configure LN_BB_CLK1 to follow Pin Control
      { 0x00,	0x57,	0x08,	0x00},	// W#321 - 	Disable PMIC WD - TODO (check if this needs to be conditionally re-enabled in Wake)
      { 0x01,	0x51,	0x72,	0x00},	// W#322 - 	Set SCRATCH2 to 0x01 (to indicate to SW that sleep sequence just ran)
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#323 - 	End of the Sleep entry sequence
      { 0xF4,	0x45,	0xFF,	0x44},	// W#324 - 	Store MODE_CTL1 into R4
      { 0xF6,	0xFF,	0x74,	0xA6},	// W#325 - 	Load data into location pointed to by R6
      { 0x04,	0x00,	0x76,	0x21},	// W#326 - 	Increment pointer by 4 to point at the next set
      { 0xFF,	0xFF,	0xFF,	0x8F},	// W#327 - 	End of subroutine.
      { 0x81,	0x46,	0x51,	0x00},	// W#328 - 	1BYTE WRITE 0x81 TO LN_BB_CLK1__EN_CTL; Enable LN_BB_CLK1
      { 0x1C,	0x04,	0x38,	0x00},	// W#329 - 	1BYTE WRITE 0x1C TO VADC_HC9_BTM_2__PERPH_TYPE; Re-enable ADC comparators
      { 0x80,	0x46,	0x0B,	0x00},	// W#330 - 	1BYTE WRITE 0x80 TO VREF_MSM__EN_CTL1; Enable VREF_MSM
      { 0x18,	0x08,	0x76,	0xA1},	// W#331 - 	Using Location stored in GOTO-Pointer at LOC_SLEEP_BACKUP_DATASET_HEAD
      { 0x60,	0x0D,	0x1D,	0x89},	// W#332 - 	Restore S4 Primary-Mode to the one before entering sleep
      { 0x60,	0x0D,	0x20,	0x89},	// W#333 - 	Restore S5 Primary-Mode to the one before entering sleep
      { 0xC6,	0x44,	0x20,	0x11},	// W#334 - 	Enable PFM_IBOOST. In SBL, Value = 0xC6
      { 0xC5,	0x44,	0x1D,	0x11},	// W#335 - 	Enable PFM_IBOOST
      { 0x02,	0x5A,	0x1D,	0x11},	// W#336 - 	In SBL, value = 0x02
      { 0x06,	0x49,	0x1D,	0x01},	// W#337 - 	Restore S4 Secondary-Mode to AUTO
      { 0x00,	0xDF,	0x14,	0x00},	// W#338 - 	Use 200k=0. Charger clock may lock up at this command CR-0000176241
      { 0x04,	0xDF,	0x14,	0x00},	// W#339 - 	Toggle chicken bit high to unlock charger
      { 0xC0,	0x03,	0xFE,	0xC1},	// W#340 - 	Wait 50us = 960 x 19.2MHz clock-cycles
      { 0x00,	0xDF,	0x14,	0x00},	// W#341 - 	Toggle chicken bit low
      { 0x02,	0x51,	0x72,	0x00},	// W#342 - 	Set SCRATCH2 to 0x02 (to indicate to SW that wake sequence just ran)
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#343 - 	End of wake sequence
      { 0xF6,	0xFF,	0x74,	0xA2},	// W#344 - 	Load R2 to R5 with data from location pointed to by R6
      { 0xF4,	0x45,	0xFF,	0x0C},	// W#345 - 	ReStore MODE_CTL1 from R4
      { 0x04,	0x00,	0x76,	0x21},	// W#346 - 	Increment pointer by 4 to point at the next set
      { 0xFF,	0xFF,	0xFF,	0x8F},	// W#347 - 	End of subroutine.
      { 0x7F,	0x00,	0xFC,	0x2C},	// W#348 - 	Clear EOSR_IN_QUEUE_STS = MISC_SPARE_5<7> [AND RC with 0x7F = 0'b0111_1111]
      { 0x20,	0xC1,	0x20,	0x90},	// W#349 - 	GOTO(AFP_BATT_TEMP_CHECK_SEQUENCE) if AFP_BATT_TEMP_STS = MISC_SPARE_5<5> is Set [Mask = 0x20 = 0'b0010_0000]
      { 0xC4,	0x0D,	0xFF,	0x83},	// W#350 - 	Else, proceed to check FG_ESR_QM_STS if AFP_BATT_TEMP_STS is Clear
      { 0xF4,	0x53,	0x09,	0x40},	// W#351 - 	R4 <= HOT_THRESHOLD [MISC_SPARE_4]
      { 0xF3,	0x52,	0x09,	0x40},	// W#352 - 	R3 <= COLD_THRESHOLD [MISC_SPARE_3]
      { 0xF1,	0x51,	0x41,	0x40},	// W#353 - 	R1 <= Current BATT_TEMP_MSB
      { 0xF0,	0x50,	0x41,	0x40},	// W#354 - 	R0 <= Current BATT_TEMP_LSB
      { 0xFF,	0xFF,	0x71,	0x38},	// W#355 - 	SHIFT R1 MSB Left 5-times to make Orig <2:0> to New <7:5>
      { 0xFF,	0xFF,	0x71,	0x38},	// W#356 - 	
      { 0xFF,	0xFF,	0x71,	0x38},	// W#357 - 	
      { 0xFF,	0xFF,	0x71,	0x38},	// W#358 - 	
      { 0xFF,	0xFF,	0x71,	0x38},	// W#359 - 	
      { 0xFF,	0xFF,	0x70,	0x3C},	// W#360 - 	SHIFT R0 LSB Right 3-times to make Orig <7:3> to New <4:0>
      { 0xFF,	0xFF,	0x70,	0x3C},	// W#361 - 	
      { 0xFF,	0xFF,	0x70,	0x3C},	// W#362 - 	
      { 0xF0,	0xF1,	0xF2,	0x32},	// W#363 - 	R2 = R1 <7:5> OR R0 <4:0> = REAL_TEMP
      { 0xF2,	0xF3,	0x75,	0x26},	// W#364 - 	R5 (DIFF) = R2 (REAL) - R3 (COLD_TH)
      { 0xFF,	0xF6,	0xFF,	0x91},	// W#365 - 	Carry=1 if DIFF < 0 i.e. REAL < COLD_TH => Open BATFET
      { 0xF2,	0xF4,	0x75,	0x26},	// W#366 - 	R5 (DIFF) = R2 (REAL) - R4 (HOT_TH)
      { 0xFF,	0xF6,	0xFF,	0x90},	// W#367 - 	Carry=1 if DIFF < 0 i.e. REAL < HOT_TH => Bat-Temp is Safe. Skip AFP, Proceed to Next Step.
      { 0x01,	0x41,	0x16,	0x10},	// W#368 - 	REAL not in <HOT_TH:COLD_TH> Range => Execute AFP-Shutdown
      { 0x10,	0xC1,	0x10,	0x90},	// W#369 - 	GOTO(FG_ESR_FAILSAFE_TIMER_EVAL) if FG_ESR_QM_STS = MISC_SPARE_5<4> is Set [Mask = 0x10 = 0'b0001_0000]
      { 0x1C,	0x0F,	0xFF,	0x83},	// W#370 - 	Else (FG Not in ESR_QUIET_MODE). Finish-Up using CLIENT2_COMMON_END_RESCHED_EVAL_SEQUENCE
      { 0xF0,	0x55,	0x09,	0x40},	// W#371 - 	Load the Loop counter into R0
      { 0x00,	0x01,	0xFF,	0x92},	// W#372 - 	If Timer is expired - enable ESR_PD and Set Interrupt
      { 0x01,	0x00,	0x70,	0x24},	// W#373 - 	Else Decrement Loop counter
      { 0xF0,	0x55,	0x09,	0x08},	// W#374 - 	Store updated Loop counter back to MISC_SPARE_6
      { 0x1C,	0x0F,	0xFF,	0x83},	// W#375 - 	Reschedule using CLIENT2_COMMON_END_RESCHED_EVAL_SEQUENCE
      { 0x02,	0x15,	0x73,	0x00},	// W#376 - 	Enable PBS_Client2 SEQ_ENDED Interrupt - will fire after this seq exits
      { 0xF4,	0x50,	0x73,	0x40},	// W#377 - 	Read the Scratch1 register to point to the requested sequence
      { 0x02,	0x00,	0xF4,	0x30},	// W#378 - 	R4 is loaded with Flags Bit<1>=1 --> FG_ESR_SEQ [OR R4 with Mask = 0x02 = 0'b0000_0010]
      { 0xEF,	0x00,	0xF4,	0x2C},	// W#379 - 	R4 is loaded with Flags Bit<4>=0 --> EXIT_QUIET [AND R4 with Mask = 0xEF = 0'b1110_1111]
      { 0xF4,	0x0E,	0xFF,	0x83},	// W#380 - 	Goto FG_ESR_QUIET_MODE_EXIT with appropraite Flags configured for Forced FG_ESR_QUIET_MODE_EXIT
      { 0xF8,	0x08,	0xC9,	0x40},	// W#381 - 	Readback GPIO10 (WCSS_VCTRL) status and store to Buffer R8
      { 0x01,	0x81,	0x01,	0x90},	// W#382 - 	If GPIO09 is high
      { 0x1C,	0x0E,	0xFF,	0x83},	// W#383 - 	GPI009 is low
      { 0xF9,	0x4E,	0x09,	0x40},	// W#384 - 	Read MISC register for L5 active voltage and store LSB to Buffer R9
      { 0xFA,	0x4F,	0x09,	0x40},	// W#385 - 	Read MISC register for L5 active voltage and store MSB to Buffer RA
      { 0xF9,	0x40,	0x44,	0x09},	// W#386 - 	Write Buffer R9 value to L5A VSET (LSB) (note: PDM error incorrectly shows 2BYTE)
      { 0xFA,	0x41,	0x44,	0x09},	// W#387 - 	Write Buffer RA value to L5A VSET (MSB) (note: PDM error incorrectly shows 2BYTE)
      { 0x07,	0x45,	0x44,	0x01},	// W#388 - 	Set LDO05 mode to NPM [GDG] There is no HW_EN to follow for this. And no PBS Vote for secondary mode
      { 0x01,	0x5A,	0x09,	0x00},	// W#389 - 	Indicate that the sequence set regulators to active state
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#390 - 	
      { 0xF9,	0x4C,	0x09,	0x40},	// W#391 - 	Read MISC register for L5 retention voltage and store LSB to Buffer R9
      { 0xFA,	0x4D,	0x09,	0x40},	// W#392 - 	Read MISC register for L5 retention voltage and store MSB to Buffer RA
      { 0xF9,	0x40,	0x44,	0x09},	// W#393 - 	Write Buffer R9 value to L5A VSET (LSB)
      { 0xFA,	0x41,	0x44,	0x09},	// W#394 - 	Write Buffer RA value to L5A VSET (MSB)
      { 0x04,	0x45,	0x44,	0x01},	// W#395 - 	Set LDO05 mode to RET [GDG] There is no HW_EN to follow for this. And no PBS Vote for secondary mode
      { 0x00,	0x5A,	0x09,	0x00},	// W#396 - 	Indicate that the sequence set regulators to retention state
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#397 - 	
      { 0xF8,	0x08,	0xC4,	0x40},	// W#398 - 	Readback GPIO05 (WLAN_RF_VCTRL) status and store to Buffer R8
      { 0x01,	0x81,	0x01,	0x90},	// W#399 - 	SKIP If GPIO3 is high
      { 0x50,	0x0E,	0xFF,	0x83},	// W#400 - 	GPI005 is low
      { 0x40,	0x4F,	0x20,	0x01},	// W#401 - 	Set PBS_EN and PBS_MODE to use Secondary Mode [GDG] set MODE Secondary to Auto in MODE_CTL2
      { 0x01,	0x5B,	0x09,	0x00},	// W#402 - 	set state to 0x1 to indicate that active state was executed
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#403 - 	
      { 0x00,	0x4F,	0x20,	0x01},	// W#404 - 	Clear PBS_EN and PBS_MODE and go to primary mode
      { 0x00,	0x5B,	0x09,	0x00},	// W#405 - 	Set state to 0x0 to indicate that retention state was executed
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#406 - 	
      { 0xF2,	0x18,	0x1C,	0x40},	// W#407 - 	Readback BUA interrupts and store status to Buffer R2
      { 0x01,	0x20,	0x01,	0x91},	// W#408 - 	If not BATT_ALARM_INT latched
      { 0x01,	0xDB,	0x4E,	0x11},	// W#409 - 	1BYTE WRITE 0x01 TO LDO015__PERPH_RESET_CTL4; SW Reset for LDO15
      { 0x01,	0xDB,	0x50,	0x11},	// W#410 - 	1BYTE WRITE 0x01 TO LDO17__PERPH_RESET_CTL4; SW Reset for LDO17
      { 0x02,	0x20,	0x02,	0x90},	// W#411 - 	If not UICC1_INT latched
      { 0x01,	0xDB,	0x4E,	0x11},	// W#412 - 	SW Reset for LDO15A (UIM1)
      { 0x04,	0x20,	0x04,	0x90},	// W#413 - 	If not UICC2_INT latched
      { 0x01,	0xDB,	0x50,	0x11},	// W#414 - 	SW Reset for LDO17 (UIM2)
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#415 - 	
      { 0xF4,	0x50,	0x73,	0x40},	// W#416 - 	Read the Scratch1 register to point to the requested sequence
      { 0x01,	0x40,	0x01,	0x91},	// W#417 - 	Skip if Bit 0 not set (S6 voltage check)
      { 0xF4,	0x51,	0x73,	0x08},	// W#418 - 	Set Scratch2 to value in Scratch1 to show SW that request was read
      { 0xA0,	0x0E,	0xFF,	0x83},	// W#419 - 	
      { 0x02,	0x40,	0x02,	0x90},	// W#420 - 	Skip if Bit 1 not set (FG_ESR_QUIET_MODE_CTRL_SEQUENCE)
      { 0xEC,	0x0E,	0xFF,	0x83},	// W#421 - 	
      { 0xFF,	0x51,	0x73,	0x00},	// W#422 - 	Only Bits <3:0> supported for CMDs. Set Scratch2 to 0xFF to indicate an error if none of those were set.
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#423 - 	
      { 0xF8,	0x42,	0x23,	0x41},	// W#424 - 	
      { 0xF9,	0x43,	0x23,	0x41},	// W#425 - 	
      { 0xEE,	0x02,	0x7A,	0x29},	// W#426 - 	Load R11:R10 with 0x2ee (750mV)
      { 0xF8,	0xFA,	0x7A,	0x27},	// W#427 - 	
      { 0x00,	0xA6,	0x00,	0x90},	// W#428 - 	If the voltage setting is less than 700mV
      { 0xC4,	0x0E,	0xFF,	0x83},	// W#429 - 	
      { 0xC5,	0x44,	0x23,	0x01},	// W#430 - 	S6_CTRL_PFM_CTL = 0xC5
      { 0x88,	0x4B,	0x24,	0x11},	// W#431 - 	
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#432 - 	
      { 0x08,	0x02,	0x7A,	0x29},	// W#433 - 	Load R11:R10 with 0x208 (520mV)
      { 0xF8,	0xFA,	0x7A,	0x27},	// W#434 - 	
      { 0x00,	0xA6,	0x00,	0x90},	// W#435 - 	If the voltage setting is less than 700mV
      { 0xE0,	0x0E,	0xFF,	0x83},	// W#436 - 	
      { 0xC6,	0x44,	0x23,	0x01},	// W#437 - 	S6_CTRL_PFM_CTL = 0xC6
      { 0x86,	0x4B,	0x24,	0x11},	// W#438 - 	
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#439 - 	
      { 0xC7,	0x44,	0x23,	0x01},	// W#440 - 	S6_CTRL_PFM_CTL = 0xC7
      { 0x86,	0x4B,	0x24,	0x11},	// W#441 - 	
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#442 - 	
      { 0x10,	0x40,	0x10,	0x90},	// W#443 - 	Skip over to FG_ESR_QUIET_MODE_EXIT if Bit-4 of R4 was Clear
      { 0x04,	0x0F,	0xFF,	0x83},	// W#444 - 	
      { 0xEF,	0x00,	0xFC,	0x2C},	// W#445 - 	Clear FG_ESR_QM_STS = MISC_SPARE_5<4> [AND RC with 0xEF = 0'b1110_1111]
      { 0x02,	0x00,	0xFB,	0x30},	// W#446 - 	Set ESR_PD_MODE to CRG_DSC PD --> ESR_PULSES_ALLOWED
      { 0x00,	0x00,	0x70,	0x28},	// W#447 - 	Update FG_ESR_QM_FAILSAFE_TIMER Value to Min 0x00 = 0 secs (Redundant)
      { 0x10,	0x0F,	0xFF,	0x83},	// W#448 - 	
      { 0x10,	0x00,	0xFC,	0x30},	// W#449 - 	Set FG_ESR_QM_STS = MISC_SPARE_5<4> [OR RC with 0x10 = 0'b0001_0000]
      { 0x0C,	0x00,	0xFB,	0x2C},	// W#450 - 	Set ESR_PD_MODE to NO_PULL --> ESR_PULSES_STOPPED
      { 0xFF,	0x00,	0x70,	0x28},	// W#451 - 	Update FG_ESR_QM_FAILSAFE_TIMER Value to Max 0xFF = 255 (=> Min 8.5 minutes)
      { 0xFB,	0x69,	0x41,	0x08},	// W#452 - 	Configure ESR_PD_CFG as per updated value
      { 0xF0,	0x55,	0x09,	0x08},	// W#453 - 	Load FG_ESR_QM_FAILSAFE_TIMER as per updated value into MISC_SPARE_6
      { 0xF4,	0x51,	0x73,	0x08},	// W#454 - 	Set PBS_CLIENT2.SCRATCH2 to ACK to SW the Return-Value of the Calling-Sequence
      { 0x00,	0xC5,	0x30,	0x90},	// W#455 - 	Check MISC_SPARE_5 Bits <5> & <4> (Mask = 0x30 = 0'b0011_0000) for EOSR Requirements on AFP or FG
      { 0x34,	0x0F,	0xFF,	0x83},	// W#456 - 	GOTO End of this Check, if None of AFP & FG need a Rescheduled Trigger
      { 0x80,	0xC1,	0x80,	0x92},	// W#457 - 	Check EOSR_IN_QUEUE_STS = MISC_SPARE_5<7> (Mask = 0x80 = 0'b1000_0000) if any EOSR was initiated before current seq execution
      { 0x80,	0x00,	0xFC,	0x30},	// W#458 - 	EOSR was not initiated before. Set EOSR_IN_QUEUE_STS = MISC_SPARE_5<7> here (Mask 0x80 = 0'b1000_0000)
      { 0xFC,	0x54,	0x09,	0x08},	// W#459 - 	Set EOSR_IN_QUEUE_STS Flag to inform any future CLIENT2_SW_TRIGGER Seq to not Reset/Disturb EOSR-Timer (unless EOSR_OVERRIDE_STS is Set)
      { 0xFF,	0xFF,	0xFF,	0xC5},	// W#460 - 	Fire EOSR-Timer to expire after 2-secs & then --> Trigger CLIENT2_EOSR_TIMER_EXPIRED_SEQUENCE
      { 0xFC,	0x54,	0x09,	0x08},	// W#461 - 	Update the Final Value of RC (modified in certain flows) to MISC_SPARE_5
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#462 - 	End this Sequence here. EOSR-Trigger may or may-not happen later based on current EOSR_IN_QUEUE_STS
      { 0x68,	0x0F,	0xFF,	0x9B},	// W#463 - 	Assert CHG Clock Req
      { 0xF0,	0x0E,	0x13,	0x40},	// W#464 - 	R0 = Read [7] UFP_DFP_MODE
      { 0x00,	0x01,	0x80,	0x92},	// W#465 - 	Skip next 3 lines if [7]=0 i.e. UFP mode
      { 0x03,	0x59,	0x13,	0x00},	// W#466 - 	UFP_DFP_MODE=1 --> In DFP mode --> Disable crude sensor 1359[1]=1
      { 0x78,	0x0F,	0xFF,	0x9B},	// W#467 - 	Revert PBS CHG Clock Req (SW Req is kept)
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#468 - 	
      { 0xF1,	0x68,	0x13,	0x40},	// W#469 - 	Check if SCHG is in DRP-Mode
      { 0x00,	0x10,	0x06,	0x90},	// W#470 - 	Skip next 1 line if [2:1] != 0 i.e. EOS if SCHG not in DRP-Mode
      { 0x02,	0x42,	0x72,	0x00},	// W#471 - 	Trigger PBS Client1, Trigger 1(NC)
      { 0x78,	0x0F,	0xFF,	0x9B},	// W#472 - 	Revert PBS CHG Clock Req (SW Req is kept)
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#473 - 	
      { 0xF0,	0xDF,	0x14,	0x40},	// W#474 - 	
      { 0x01,	0x00,	0xF0,	0x30},	// W#475 - 	R0 = R0 || 0x01 i.e. Set Bit-0 to High
      { 0xF0,	0xDF,	0x14,	0x08},	// W#476 - 	Writeback SCHG_DC.CLOCK_CONTROL with updated R0 (with Bit-0 set High)
      { 0xFF,	0xFF,	0xFF,	0x8F},	// W#477 - 	
      { 0xF0,	0xDF,	0x14,	0x40},	// W#478 - 	
      { 0x08,	0x01,	0x08,	0x91},	// W#479 - 	Bit-3 = 1 => APPS is awake, leave Bit-0 High
      { 0xFE,	0x00,	0xF0,	0x2C},	// W#480 - 	Bit-3 = 0 => APPS is asleep, clear CLK_REQ. R0 = R0 && 0xFE
      { 0xF0,	0xDF,	0x14,	0x08},	// W#481 - 	Write back SCHG_DC.CLOCK_CONTROL with updated R0 (with Bit-0 cleared low)
      { 0xFF,	0xFF,	0xFF,	0x8F},	// W#482 - 	
      { 0xF4,	0x50,	0x74,	0x40},	// W#483 - 	Read the Argument Register to point to the requested sequence
      { 0x01,	0x40,	0x01,	0x90},	// W#484 - 	Skip if Bit 0 not set (AFP BATT_TEMP CTRL)
      { 0xA0,	0x0F,	0xFF,	0x83},	// W#485 - 	
      { 0xFF,	0x51,	0x74,	0x00},	// W#486 - 	Only Bit <0> supported for CMDs. Set Scratch2 to 0xFF to indicate an error if none of those were set.
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#487 - 	
      { 0xFC,	0x54,	0x09,	0x40},	// W#488 - 	PBSREG.RC will store MISC_SPARE_5
      { 0x10,	0x40,	0x10,	0x91},	// W#489 - 	Skip over to AFP_BATT_TEMP_CHECK_DISABLE if Bit-4 of R4 was Clear
      { 0x20,	0x00,	0xFC,	0x30},	// W#490 - 	Set AFP_BATT_TEMP_CHK_STS = MISC_SPARE_5<5> [OR RC with 0x20 = 0'b0010_0000]
      { 0xB4,	0x0F,	0xFF,	0x83},	// W#491 - 	End with AFP_BATT_TEMP_CTRL_DONE
      { 0xDF,	0x00,	0xFC,	0x2C},	// W#492 - 	Clear AFP_BATT_TEMP_CHK_STS = MISC_SPARE_5<5> [AND RC with 0xDF = 0'b1101_1111]
      { 0xFC,	0x54,	0x09,	0x08},	// W#493 - 	Update MISC_SPARE_5 with updated AFP_BATT_TEMP_CHK_STS
      { 0xF4,	0x51,	0x74,	0x08},	// W#494 - 	Set PBS_CLIENT3.SCRATCH2 to value in PBS_CLIENT3.SCRATCH1 to show SW that request was executed
      { 0x20,	0x42,	0x73,	0x00},	// W#495 - 	Initiate PBS_CLIENT2.TRIG5 [CLIENT2_BIT5_CHECK]. Round about way, since Client3 has NO EOSR
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#496 - 	
      { 0x44,	0x44,	0x44,	0x44},	// W#497 - 	; S4: B3: Reserved
      { 0x55,	0x55,	0x55,	0x55},	// W#498 - 	; S5: B3: Reserved
      { 0xFF,	0xFF,	0xFF,	0xFF},	// W#499 - 	| B3:POFF_REASON  | B2:ON_REASON      | B1:WARM_RESET_REASON1 | B0:PON_REASON1
      { 0xFF,	0xFF,	0xFF,	0xFF},	// W#500 - 	| B3:RTC_LSB      | B2:FAULT_REASON2  | B1:FAULT_REASON1      | B0:OFF_REASON
      { 0xFF,	0xFF,	0xFF,	0xFF},	// W#501 - 	| B3:POFF_REASON  | B2:ON_REASON      | B1:WARM_RESET_REASON1 | B0:PON_REASON1
      { 0xFF,	0xFF,	0xFF,	0xFF},	// W#502 - 	| B3:RTC_LSB      | B2:FAULT_REASON2  | B1:FAULT_REASON1      | B0:OFF_REASON
      { 0xFF,	0xFF,	0xFF,	0xFF},	// W#503 - 	| B3:POFF_REASON  | B2:ON_REASON      | B1:WARM_RESET_REASON1 | B0:PON_REASON1
      { 0xFF,	0xFF,	0xFF,	0xFF},	// W#504 - 	| B3:RTC_LSB      | B2:FAULT_REASON2  | B1:FAULT_REASON1      | B0:OFF_REASON
      { 0xFF,	0xFF,	0xFF,	0xFF},	// W#505 - 	Inserted by compiler.
      { 0xFF,	0xFF,	0xFF,	0xFF},	// W#506 - 	Inserted by compiler.
      { 0xFF,	0xFF,	0xFF,	0xFF},	// W#507 - 	Inserted by compiler.
      { 0xFF,	0xFF,	0xFF,	0xFF},	// W#508 - 	Inserted by compiler.
      { 0xFF,	0xFF,	0xFF,	0xFF},	// W#509 - 	Inserted by compiler.
      { 0xFF,	0xFF,	0xFF,	0xFF},	// W#510 - 	Inserted by compiler.
      { 0x00,	0x1B,	0xFF,	0xF8},	// W#511 - 	Inserted by compiler.
   },
   // "PM660L_RAM_b0x10_v0x20"
   {
      //data  offset  base_addr  sid
      { 0x52,	0x53,	0x42,	0x50},	// W#0 - 	0x600 RAM signature PBSR""
      { 0x10,	0x20,	0x01,	0x18},	// W#1 - 	0x604 Header offset, Header Version, PBS RAM Revision, PBS RAM Branch
      { 0x34,	0x06,	0xFF,	0x83},	// W#2 - 	0x608 start of trigger jump table:
      { 0x6C,	0x06,	0xFF,	0x83},	// W#3 - 	0x60C Client-1 Trigger
      { 0xD4,	0x06,	0xFF,	0x83},	// W#4 - 	0x610 Client-2 Trigger
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#5 - 	0x614 Empty (Drax does not have Client-3)
      { 0x98,	0x0C,	0xFF,	0x83},	// W#6 - 	0x618 Fixed Offset = RAM-Base-Addr + 0x18 + 0x00 => SLEEP-SET
      { 0xAC,	0x0C,	0xFF,	0x83},	// W#7 - 	0x61C Fixed Offset = RAM-Base-Addr + 0x18 + 0x04 => (PON X Reasons
      { 0xFF,	0xFF,	0xFF,	0xFB},	// W#8 - 	0x620 Fixed Offset = RAM-Base-Addr + 0x18 + 0x08 => (NO RTRR)
      { 0xFF,	0xFF,	0xFF,	0xFB},	// W#9 - 	0x624 Fixed Offset = RAM-Base-Addr + 0x18 + 0x0C => (No HLOS) / Spare
      { 0xFF,	0xFF,	0xFF,	0xFB},	// W#10 - 	0x628 Fixed Offset = RAM-Base-Addr + 0x18 + 0x10 => (Spare registers) / LPG
      { 0xFF,	0xFF,	0xFF,	0xFB},	// W#11 - 	0x62C Fixed Offset = RAM-Base-Addr + 0x18 + 0x14 => (LPG Dataset)
      { 0xC8,	0x0C,	0xFF,	0x83},	// W#12 - 	0x630 Fixed Offset = RAM-Base-Addr + 0x18 + 0x18 => (USER-Space: AMOLED Panel-Specific Implementation)
      { 0xFF,	0x48,	0x71,	0x00},	// W#13 - 	Clear all latched sequences in PBS PON Client 0
      { 0xFB,	0x08,	0x08,	0x40},	// W#14 - 	Readback PON FSM Status and store to Buffer RB
      { 0x04,	0xB0,	0xFF,	0x90},	// W#15 - 	Skip if NOT DVDD_CONFIG (State 4)
      { 0x14,	0x00,	0xFF,	0x83},	// W#16 - 	GOTO OTP_DVDD_CONFIG (OTP); Is there a scenario where this is ever used?
      { 0x01,	0xB0,	0xFF,	0x90},	// W#17 - 	Skip if NOT PON (State 1)
      { 0x14,	0x00,	0xFF,	0x83},	// W#18 - 	GOTO OTP_DVDD_CONFIG (OTP); Is there a scenario where this is ever used?
      { 0x06,	0xB0,	0xFF,	0x90},	// W#19 - 	Skip if NOT FAULT (State 6)
      { 0x48,	0x07,	0xFF,	0x83},	// W#20 - 	
      { 0x02,	0xB0,	0xFF,	0x90},	// W#21 - 	Skip if NOT POFF (State 2)
      { 0xE4,	0x07,	0xFF,	0x83},	// W#22 - 	
      { 0x07,	0xB0,	0xFF,	0x90},	// W#23 - 	Skip if NOT WARM RESET (State 7)
      { 0x6C,	0x07,	0xFF,	0x83},	// W#24 - 	
      { 0x00,	0x91,	0x08,	0x00},	// W#25 - 	Undefined State - NACK PON (Note:  None of the Client GOTOs have a 'RETURN'; the ACK is done in each subroutine)
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#26 - 	End of Sequence; Byte-2
      { 0xF3,	0x0A,	0x72,	0x40},	// W#27 - 	Read Client 1 trigger latch status and store to Buffer R3
      { 0x01,	0x30,	0x01,	0x91},	// W#28 - 	Skip if NOT Bit 0 (DTEST MUX)
      { 0x01,	0x48,	0x72,	0x00},	// W#29 - 	Clear Latched Trigger - Bit 0
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#30 - 	CL1_TRIG0:EMPTY => Replace with GOTO once defined.
      { 0x02,	0x30,	0x02,	0x91},	// W#31 - 	Skip if NOT Bit 1 (BoB)
      { 0x02,	0x48,	0x72,	0x00},	// W#32 - 	Clear Latched Trigger - Bit 1
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#33 - 	CL1_TRIG1:EMPTY => Replace with GOTO once defined.
      { 0x04,	0x30,	0x04,	0x91},	// W#34 - 	Skip if NOT Bit 2 (BA_N)
      { 0x04,	0x48,	0x72,	0x00},	// W#35 - 	Clear Latched Trigger - Bit 2
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#36 - 	CL1_TRIG2:EMPTY => Replace with GOTO once defined.
      { 0x08,	0x30,	0x08,	0x91},	// W#37 - 	Skip if NOT Bit 3 (LAB_IBB_SCP)
      { 0x08,	0x48,	0x72,	0x00},	// W#38 - 	Clear Latched Trigger - Bit 3
      { 0x3C,	0x09,	0xFF,	0x83},	// W#39 - 	CL1_TRIG3: LAB_IBB_SCP
      { 0x10,	0x30,	0x10,	0x91},	// W#40 - 	Skip if NOT Bit 4 (EOSR_Timer)
      { 0x10,	0x48,	0x72,	0x00},	// W#41 - 	Clear Latched Trigger - Bit 4
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#42 - 	CL1_TRIG4:EMPTY => Replace with GOTO once defined.
      { 0x20,	0x30,	0x20,	0x91},	// W#43 - 	Skip if NOT Bit 5 (BCL)
      { 0x20,	0x48,	0x72,	0x00},	// W#44 - 	Clear Latched Trigger - Bit 5
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#45 - 	CL1_TRIG5:EMPTY => Replace with GOTO once defined.
      { 0x40,	0x30,	0x40,	0x91},	// W#46 - 	Skip if NOT Bit 6 (OTS2)
      { 0x40,	0x48,	0x72,	0x00},	// W#47 - 	Clear Latched Trigger - Bit 6
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#48 - 	CL1_TRIG6:EMPTY => Replace with GOTO once defined.
      { 0x80,	0x30,	0x80,	0x91},	// W#49 - 	Bit 7 = SW Trigger (System Sleep/Wake)
      { 0x80,	0x48,	0x72,	0x00},	// W#50 - 	Clear Latched Trigger - Bit 7
      { 0x54,	0x09,	0xFF,	0x83},	// W#51 - 	CL1_TRIG7: CLIENT1_SYSTEM_SLEEP_WAKE_SEQUENCE
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#52 - 	
      { 0xF4,	0x0A,	0x73,	0x40},	// W#53 - 	Read Client 2 trigger latch status and store to Buffer R4
      { 0x01,	0x40,	0x01,	0x91},	// W#54 - 	Skip if not Bit 0 (WCSS pin control, Was EUD from Groot)
      { 0x01,	0x48,	0x73,	0x00},	// W#55 - 	Clear Latched Trigger - Bit 0
      { 0x64,	0x0A,	0xFF,	0x83},	// W#56 - 	CL2_TRIG0: WCSS_CTRL_PIN_STATE_CHECK
      { 0x02,	0x40,	0x02,	0x91},	// W#57 - 	Skip if not Bit 1 (uSD switch detect, GPIO08)
      { 0x02,	0x48,	0x73,	0x00},	// W#58 - 	Clear Latched Trigger - Bit 1
      { 0xA4,	0x0A,	0xFF,	0x83},	// W#59 - 	CL2_TRIG1: MULTICARDTRAY_UICC_PROTECTION_SEQ
      { 0x04,	0x40,	0x04,	0x91},	// W#60 - 	Skip if not Bit 2 (SWIRE decode from AOMLED)
      { 0x04,	0x48,	0x73,	0x00},	// W#61 - 	Clear Latched Trigger - Client2 Bit 2
      { 0xCC,	0x0C,	0xFF,	0x83},	// W#62 - 	CL2_TRIG2: USER_SPACE_POINTER1
      { 0x08,	0x40,	0x08,	0x91},	// W#63 - 	Skip if not Bit 3 (SSC_PWR_EN from MSM)
      { 0x08,	0x48,	0x73,	0x00},	// W#64 - 	Clear Latched Trigger - Bit 3
      { 0xEC,	0x0A,	0xFF,	0x83},	// W#65 - 	CL2_TRIG3: SSC_CTRL_PIN_STATE_CHECK
      { 0x10,	0x40,	0x10,	0x91},	// W#66 - 	Skip if not Bit 4 (SLB, GPIO10, Trigger from Groot)
      { 0x10,	0x48,	0x73,	0x00},	// W#67 - 	Clear Latched Trigger - Bit 4
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#68 - 	CL2_TRIG4:EMPTY => Replace with GOTO once defined.
      { 0x20,	0x40,	0x20,	0x91},	// W#69 - 	Skip if not Bit 5 (EOSR_Timer)
      { 0x20,	0x48,	0x73,	0x00},	// W#70 - 	Clear Latched Trigger - Bit 5
      { 0x1C,	0x0C,	0xFF,	0x83},	// W#71 - 	CL2_TRIG5: LAB_PSRR_EOSR_SEQUENCE
      { 0x40,	0x40,	0x40,	0x94},	// W#72 - 	Skip if not Bit 6 (LAB_BANDING_DETECTION)
      { 0xF1,	0x40,	0x73,	0x40},	// W#73 - 	Read RE trigger config for RMW
      { 0xBF,	0x00,	0xF1,	0x2C},	// W#74 - 	clear bit 6 to disable RE trigger
      { 0xF1,	0x40,	0x73,	0x08},	// W#75 - 	RE disabled for client2 bit 6
      { 0x40,	0x48,	0x73,	0x00},	// W#76 - 	Clear PBS_CLIENT2 Bit6 Trig-Latch after disabling RE on corresponding Bit6 above
      { 0x08,	0x0C,	0xFF,	0x83},	// W#77 - 	CL2_TRIG6: LAB_BANDING_DETECTION
      { 0x80,	0x40,	0x80,	0x91},	// W#78 - 	Skip if not Bit 7 (SW Trigger)
      { 0x80,	0x48,	0x73,	0x00},	// W#79 - 	1BYTE WRITE 0x80 TO PBS_CLIENT3__TRIG_LATCHED_CLR; Clear Latched Trigger - Bit 7
      { 0x84,	0x0C,	0xFF,	0x83},	// W#80 - 	CL2_TRIG7: CLIENT2_SW_TRIGGER
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#81 - 	
      { 0xFF,	0xFF,	0xFF,	0xFB},	// W#82 - 	
      { 0xDC,	0x08,	0xFF,	0x9B},	// W#83 - 	Record PON REASONS into dataset (Circular Buffer with History-Size = 3)
      { 0x88,	0x48,	0x14,	0x01},	// W#84 - 	1BYTE WRITE 0x88 TO S1_CTRL__PD_CTL; Enable strong + leak pulldown
      { 0x88,	0x48,	0x17,	0x01},	// W#85 - 	1BYTE WRITE 0x88 TO S2_CTRL__PD_CTL; Enable strong + leak pulldown
      { 0x88,	0x48,	0x1A,	0x01},	// W#86 - 	1BYTE WRITE 0x88 TO S3_CTRL__PD_CTL; Enable strong + leak pulldown
      { 0x88,	0x48,	0x20,	0x01},	// W#87 - 	1BYTE WRITE 0x88 TO S5_CTRL__PD_CTL; Enable strong + leak pulldown
      { 0xEA,	0x01,	0xFF,	0xC1},	// W#88 - 	WAIT 15016 us; Wait 15ms for VREGs to discharge completely before allowing the next PON trigger
      { 0x40,	0x91,	0x08,	0x00},	// W#89 - 	1BYTE WRITE 0x40 TO PON__PBS_INTERFACE; ACK PON
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#90 - 	
      { 0xFF,	0xFF,	0xFF,	0xFB},	// W#91 - 	
      { 0xDC,	0x08,	0xFF,	0x9B},	// W#92 - 	Record PON REASONS into dataset (Circular Buffer with History-Size = 3)
      { 0xC0,	0x07,	0x41,	0x89},	// W#93 - 	
      { 0xC0,	0x07,	0x44,	0x89},	// W#94 - 	
      { 0x02,	0x00,	0x70,	0x28},	// W#95 - 	1BYTE R0 = 0x02; R0 = 0x2
      { 0xC0,	0x08,	0xFF,	0x9B},	// W#96 - 	GOTO INIT_RESET PON. Do reset stuff common to warm reset and POFF
      { 0x07,	0x45,	0x40,	0x01},	// W#97 - 	: 17
      { 0x07,	0x45,	0x41,	0x01},	// W#98 - 	: 19
      { 0x07,	0x45,	0x43,	0x01},	// W#99 - 	: 23
      { 0x07,	0x45,	0x44,	0x01},	// W#100 - 	: 20
      { 0x07,	0x45,	0x46,	0x01},	// W#101 - 	: 18
      { 0x07,	0x45,	0x42,	0x01},	// W#102 - 	: N/A
      { 0x07,	0x45,	0x45,	0x01},	// W#103 - 	: N/A
      { 0x07,	0x45,	0x47,	0x01},	// W#104 - 	: N/A
      { 0xE0,	0x40,	0xA0,	0x01},	// W#105 - 	1BYTE WRITE 0xE0 TO BOB_CONFIG__VOUT_LB; Set VBOB to 3.296V since BOB ignores warm_rb
      { 0x0C,	0x41,	0xA0,	0x01},	// W#106 - 	1BYTE WRITE 0x0C TO BOB_CONFIG__VOUT_UB; Set VBOB to 3.296V since BOB ignores warm_rb
      { 0x02,	0x45,	0xA0,	0x01},	// W#107 - 	1BYTE WRITE 0x02 TO BOB_CONFIG__VOUT_MODE_CTRL; Set BOB to auto mode since BOB ignores warm_rb
      { 0x00,	0x36,	0xA0,	0x01},	// W#108 - 	1BYTE WRITE 0x00 TO BOB_CONFIG__EXT_CTRL_FOLLOW; Ignore EXT_CTRL1 & 2. Explicit command since BOB ignores warm_rb
      { 0xD0,	0x07,	0xFF,	0x9B},	// W#109 - 	GOTO_SUB_NOID WR_MSM_BOOT_VOLTAGE_SS_NOM; Set CX/MX/APC to SS Nominal (new values
      { 0x40,	0x91,	0x08,	0x00},	// W#110 - 	1BYTE WRITE 0x40 TO PON__PBS_INTERFACE; ACK PON
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#111 - 	End of Sequence; Byte-2
      { 0xD2,	0x66,	0xFF,	0x04},	// W#112 - 	Assert OCP_CTL1.Bit1 <OCP_STATUS_CLR> = 1
      { 0x03,	0x00,	0xFF,	0xC1},	// W#113 - 	WAIT 91 us = 3 cycles of 32k clock
      { 0xD0,	0x66,	0xFF,	0x04},	// W#114 - 	De-Assert OCP_CTL1.Bit1 <OCP_STATUS_CLR> = 0
      { 0xFF,	0xFF,	0xFF,	0x8F},	// W#115 - 	
      { 0x68,	0x40,	0x1A,	0x01},	// W#116 - 	1BYTE WRITE 0x80 TO S1_CTRL__VSET_LB; Bump S3+S4 (CX) to 0.87V
      { 0x03,	0x41,	0x1A,	0x01},	// W#117 - 	1BYTE WRITE 0x03 TO S1_CTRL__VSET_UB; Bump S3+S4 (CX) to 0.87V
      { 0x94,	0x40,	0x20,	0x01},	// W#118 - 	1BYTE WRITE 0xA0 TO S5_CTRL__VSET_LB; Bump S5 (MX) to 0.915V
      { 0x03,	0x41,	0x20,	0x01},	// W#119 - 	1BYTE WRITE 0x03 TO S5_CTRL__VSET_UB; Bump S5 (MX) to 0.915V
      { 0xFF,	0xFF,	0xFF,	0x8F},	// W#120 - 	End of subroutine. PC = Stored PC.; Byte-2
      { 0xFF,	0xFF,	0xFF,	0xFB},	// W#121 - 	
      { 0xDC,	0x08,	0xFF,	0x9B},	// W#122 - 	Record PON REASONS into dataset (Circular Buffer with History-Size = 3)
      { 0x04,	0x00,	0x70,	0x28},	// W#123 - 	1BYTE R0 = 0x04; R0=0x4. This value will be applied to the PON_RESET_CTL register in PON (bit 2 warm_rb
      { 0xC0,	0x08,	0xFF,	0x9B},	// W#124 - 	GOTO INIT_RESET PON. Do reset stuff common to warm reset and POFF
      { 0x00,	0x40,	0xC9,	0x00},	// W#125 - 	Configure GPIO10 to Dig INPUT
      { 0x05,	0x42,	0xC9,	0x00},	// W#126 - 	Set SLB to NO PULL
      { 0x46,	0x01,	0x76,	0x29},	// W#127 - 	WAIT 10010 us; Wait 10ms.  Store to Buffer R6. 146
      { 0x64,	0x08,	0xFF,	0x9B},	// W#128 - 	
      { 0x0C,	0x0E,	0x43,	0x89},	// W#129 - 	
      { 0xF1,	0x92,	0x09,	0x40},	// W#130 - 	
      { 0x00,	0x11,	0x01,	0x91},	// W#131 - 	If LP4x is present enable the LP4x external regulator
      { 0x00,	0x44,	0xCB,	0x00},	// W#132 - 	Configure GPIO12 LOW - PMICPR-644
      { 0x00,	0x44,	0xCA,	0x00},	// W#133 - 	Configure GPIO11 LOW
      { 0x0C,	0x0E,	0x14,	0x89},	// W#134 - 	S1B, LPDDR4
      { 0x0C,	0x0E,	0x44,	0x89},	// W#135 - 	LDO5B, SD/MMC Card
      { 0x0C,	0x0E,	0x41,	0x89},	// W#136 - 	LDO2B, VDDPX_2 (SD_MMC) - PMICPR-644
      { 0x0C,	0x0E,	0x46,	0x89},	// W#137 - 	LDO7B, USB (EUD)
      { 0x0C,	0x0E,	0x40,	0x89},	// W#138 - 	LDO1, PHY:USB (EUD)
      { 0x0C,	0x0E,	0x48,	0x89},	// W#139 - 	LDO9, LPI_Cx
      { 0x0C,	0x0E,	0x49,	0x89},	// W#140 - 	LDO10, LPI Mx
      { 0xA3,	0x00,	0x76,	0x29},	// W#141 - 	WAIT 10010 us; Wait 10ms.  Store to Buffer R6. 146
      { 0x90,	0x08,	0xFF,	0x9B},	// W#142 - 	
      { 0xF4,	0x01,	0x76,	0x29},	// W#143 - 	WAIT 10010 us; Wait 10ms.  Store to Buffer R6.  0x146
      { 0x64,	0x08,	0xFF,	0x9B},	// W#144 - 	
      { 0x0C,	0x0E,	0x17,	0x89},	// W#145 - 	LV, 1.05V
      { 0x0C,	0x0E,	0x1A,	0x89},	// W#146 - 	CX+GPU+cDSP
      { 0x0C,	0x0E,	0x20,	0x89},	// W#147 - 	MX+EBI
      { 0x0C,	0x0E,	0xA0,	0x89},	// W#148 - 	Disable BOB
      { 0x00,	0x46,	0x05,	0x00},	// W#149 - 	1BYTE WRITE 0x00 TO INT__EN_CTL1; Disable INT
      { 0x46,	0x01,	0xFF,	0xC1},	// W#150 - 	WAIT 10010 us; Wait 10ms for VREGs to discharge completely before allowing the next PON trigger
      { 0x40,	0x91,	0x08,	0x00},	// W#151 - 	1BYTE WRITE 0x40 TO PON__PBS_INTERFACE; ACK PON
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#152 - 	
      { 0x01,	0x00,	0xFF,	0xC1},	// W#153 - 	wait 1 CLK CYCLE BEFORE CHECKING
      { 0xF1,	0x08,	0xC9,	0x40},	// W#154 - 	Read GPIO10 Status (GPIO_VAL) and store to Buffer R1
      { 0x01,	0x10,	0x01,	0x92},	// W#155 - 	We will exit  = '1'
      { 0x01,	0x40,	0xC9,	0x00},	// W#156 - 	Configure GPIO10 to Dig Output
      { 0x00,	0x44,	0xC9,	0x00},	// W#157 - 	Set SLB LOW and continue
      { 0xFF,	0xFF,	0xFF,	0x8F},	// W#158 - 	
      { 0x01,	0x00,	0x76,	0x25},	// W#159 - 	Subtract 1 from the loop count (R6)
      { 0x00,	0x06,	0x00,	0x90},	// W#160 - 	If the subi in the previous command resulted in a carry then we have reached the terminal count.
      { 0x64,	0x08,	0xFF,	0x83},	// W#161 - 	
      { 0x00,	0x91,	0x08,	0x00},	// W#162 - 	Time count expired.  Nack the PON! SID=0, PID=8, Addr = 0x91
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#163 - 	End of Sequence; Return
      { 0x00,	0x40,	0xC9,	0x00},	// W#164 - 	Configure GPIO10 to Dig INPUT
      { 0x00,	0x42,	0xC9,	0x00},	// W#165 - 	Set SLB to PU
      { 0x01,	0x00,	0xFF,	0xC1},	// W#166 - 	wait 30us before trying again
      { 0xF1,	0x08,	0xC9,	0x40},	// W#167 - 	Read GPIO10 Status (GPIO_VAL) and store to Buffer R1
      { 0x00,	0x10,	0x01,	0x91},	// W#168 - 	Skip the next line if GPIO10_STATUS1 (bit 0) is high
      { 0x05,	0x42,	0xC9,	0x00},	// W#169 - 	Set SLB to No pull
      { 0xFF,	0xFF,	0xFF,	0x8F},	// W#170 - 	return to the next linE of the calling routing
      { 0x01,	0x00,	0x76,	0x25},	// W#171 - 	Subtract 1 from the loop count (R6)
      { 0x00,	0x06,	0x00,	0x90},	// W#172 - 	If the subi in the previous command resulted in a carry then we have reached the terminal count.
      { 0x98,	0x08,	0xFF,	0x83},	// W#173 - 	
      { 0x00,	0x91,	0x08,	0x00},	// W#174 - 	Time count expired.  Nack the PON! SID=0, PID=8, Addr = 0x91
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#175 - 	End of Sequence; Return
      { 0xFF,	0xFF,	0xFF,	0xFB},	// W#176 - 	NOP; //This Subroutine does several things that are common to the Warm Reset and POFF seqeunces.  1) disable SPMI to avoid lockup
      { 0x00,	0x43,	0x08,	0x02},	// W#177 - 	1BYTE WRITE 0x00 TO SID:2 0x0800__0x43; Set SPMI_SLAVE_RB to 0 to tolerate glitches during power down
      { 0xF0,	0x98,	0x08,	0x18},	// W#178 - 	1BYTE WRITE R0 TO SID:0 0x0800__0x98; Assert whatever resets are defined in R0
      { 0x03,	0x00,	0xFF,	0xC1},	// W#179 - 	WAIT 91.5 us; Wait 3 SLEEP_CLK cycles for reset changes to propagate through clock domains
      { 0x06,	0x98,	0x08,	0x10},	// W#180 - 	1BYTE WRITE 0x06 TO SID:0 0x0800__0x98; Deassert Resets
      { 0x01,	0x43,	0x08,	0x02},	// W#181 - 	Set SPMI_SLAVE_RB back to 1
      { 0xFF,	0xFF,	0xFF,	0x8F},	// W#182 - 	
      { 0x1C,	0x06,	0x70,	0xA1},	// W#183 - 	
      { 0x0C,	0x00,	0x70,	0x21},	// W#184 - 	2BYTE R0 = R0 + 0x0C (3 Rows + 0x04 Addr-Offset per Row)
      { 0x1C,	0x06,	0x72,	0xA1},	// W#185 - 	
      { 0x14,	0x00,	0x72,	0x21},	// W#186 - 	2BYTE R2 = R2 + 0x14 (5 Rows + 0x04 Addr-Offset per Row)
      { 0x04,	0x00,	0x78,	0x28},	// W#187 - 	1BYTE R8 = 0x04; Loop 4 times (Shift 4 DWords)
      { 0xF0,	0xFF,	0xF4,	0xA3},	// W#188 - 	4BYTE R4 = MEMADDR(R0); copy the last reason registers into a buffer
      { 0xF2,	0xFF,	0xF4,	0xA7},	// W#189 - 	4BYTE MEMADDR(R2) = R4; write the reasons to the location pointed to by the paste pointer
      { 0x01,	0x00,	0x78,	0x24},	// W#190 - 	
      { 0x00,	0x81,	0xFF,	0x92},	// W#191 - 	SKIP 3 Lines if R8 EQUAL 0x00 (MASK=0xFF); Loop Until loop count (R8) = 4
      { 0x04,	0x00,	0x70,	0x25},	// W#192 - 	2BYTE R0 = R0 - 0x04; Move read pointer to next (upper) DWORD
      { 0x04,	0x00,	0x72,	0x25},	// W#193 - 	2BYTE R2 = R2 - 0x04; Move write pointer to next (upper) DWORD
      { 0xF0,	0x08,	0xFF,	0x83},	// W#194 - 	
      { 0xF4,	0xC0,	0x08,	0x40},	// W#195 - 	
      { 0xF5,	0xC2,	0x08,	0x40},	// W#196 - 	
      { 0xF6,	0xC4,	0x08,	0x40},	// W#197 - 	
      { 0xF7,	0xC5,	0x08,	0x40},	// W#198 - 	
      { 0xF0,	0xFF,	0xF4,	0xA7},	// W#199 - 	4BYTE MEMADDR(R0) = R4
      { 0x04,	0x00,	0x70,	0x21},	// W#200 - 	2BYTE R0 = R0 + 0x04
      { 0xF4,	0xC7,	0x08,	0x40},	// W#201 - 	
      { 0xF5,	0xC8,	0x08,	0x40},	// W#202 - 	
      { 0xF6,	0xC9,	0x08,	0x40},	// W#203 - 	
      { 0xFF,	0x00,	0x77,	0x28},	// W#204 - 	1BYTE R7 = 0xFF
      { 0xF0,	0xFF,	0xF4,	0xA7},	// W#205 - 	4BYTE MEMADDR(R0) = R4; Write data to address stored in R0
      { 0xFF,	0xFF,	0xFF,	0x8F},	// W#206 - 	End of subroutine. PC = Stored PC.; Byte-2
      { 0xF0,	0x58,	0xDC,	0x11},	// W#207 - 	PMICPR-1051: Minimize delay b/w IBB & LAB discharge
      { 0x00,	0x46,	0xDC,	0x01},	// W#208 - 	Disable IBB
      { 0x00,	0x46,	0xDE,	0x01},	// W#209 - 	Disable LAB
      { 0x00,	0x47,	0xE0,	0x01},	// W#210 - 	Disable OLEDB pin control
      { 0x00,	0x46,	0xE0,	0x01},	// W#211 - 	Disable OLEDB module
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#212 - 	
      { 0xFF,	0xFF,	0xFF,	0xFB},	// W#213 - 	
      { 0xF7,	0x50,	0x72,	0x40},	// W#214 - 	1BYTE READ PBS_CLIENT1__SCRATCH1 TO R7; Readback PBS_CLIENT1_SCRATCH1 and store to Buffer R7
      { 0x02,	0x70,	0xFF,	0x90},	// W#215 - 	SKIP 1 Lines if R7 NOT EQUAL 0x02 (MASK=0xFF); If PBS_CLIENT1_SCRATCH1 != 0x02
      { 0xF0,	0x09,	0xFF,	0x83},	// W#216 - 	GOTO SYSTEM_WAKE_SEQUENCE_START; Else
      { 0x01,	0x70,	0xFF,	0x90},	// W#217 - 	SKIP 1 Lines if R7 NOT EQUAL 0x01 (MASK=0xFF); If PBS_CLIENT1_SCRATCH1 != 0x01
      { 0x70,	0x09,	0xFF,	0x83},	// W#218 - 	GOTO SYSTEM_SLEEP_SEQUENCE_START; Else
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#219 - 	
      { 0x18,	0x06,	0x76,	0xA1},	// W#220 - 	Using Location stored in GOTO-Pointer at LOC_SLEEP_BACKUP_DATASET_HEAD
      { 0xE0,	0x09,	0x14,	0x89},	// W#221 - 	
      { 0xE0,	0x09,	0x17,	0x89},	// W#222 - 	
      { 0xE0,	0x09,	0x1A,	0x89},	// W#223 - 	
      { 0xE0,	0x09,	0x20,	0x89},	// W#224 - 	
      { 0x01,	0x71,	0x14,	0x11},	// W#225 - 	Disable S1 VDIP comparator; keep 15mV threshold
      { 0x50,	0xA6,	0x14,	0x11},	// W#226 - 	Disable S1 PFM_EXIT_DIP_EN to prevent using HCPFM CL
      { 0x92,	0xA9,	0x14,	0x11},	// W#227 - 	Disable S1 PFM_EXIT_CL_EN to prevent using HCPFM CL
      { 0x04,	0x45,	0x14,	0x01},	// W#228 - 	Set S1 to Retention Mode
      { 0x01,	0x71,	0x17,	0x11},	// W#229 - 	Disable S2 VDIP comparator; keep 15mV threshold
      { 0x50,	0xA6,	0x17,	0x11},	// W#230 - 	Disable S2 PFM_EXIT_DIP_EN to prevent using HCPFM CL
      { 0x92,	0xA9,	0x17,	0x11},	// W#231 - 	Disable S2 PFM_EXIT_CL_EN to prevent using HCPFM CL
      { 0x04,	0x45,	0x17,	0x01},	// W#232 - 	Set S2 to Retention Mode
      { 0x01,	0x71,	0x1A,	0x11},	// W#233 - 	Disable S3 VDIP comparator; keep 15mV threshold
      { 0x50,	0xA6,	0x1A,	0x11},	// W#234 - 	Disable S3 PFM_EXIT_DIP_EN to prevent using HCPFM CL
      { 0x92,	0xA9,	0x1A,	0x11},	// W#235 - 	Disable S3 PFM_EXIT_CL_EN to prevent using HCPFM CL
      { 0x04,	0x45,	0x1A,	0x01},	// W#236 - 	Set S3 to Retention Mode
      { 0x01,	0x71,	0x20,	0x11},	// W#237 - 	Disable S5 VDIP comparator; keep 15mV threshold
      { 0x50,	0xA6,	0x20,	0x11},	// W#238 - 	Disable S5 PFM_EXIT_DIP_EN to prevent using HCPFM CL
      { 0x92,	0xA9,	0x20,	0x11},	// W#239 - 	Disable S5 PFM_EXIT_CL_EN to prevent using HCPFM CL
      { 0x04,	0x45,	0x20,	0x01},	// W#240 - 	Set S5 to Retention Mode
      { 0x00,	0x4A,	0x59,	0x10},	// W#241 - 	Force SLEEP_B low
      { 0xF6,	0x8F,	0x09,	0x40},	// W#242 - 	Load R6 with the value in MISC.VSET6_UB [Bit-0 = BoB Sleep-Instruction]
      { 0x00,	0x61,	0x01,	0x90},	// W#243 - 	If Bit-0 = 0 SKIP putting BoB to Bypass (needs to be done for Groot 1.0)
      { 0x00,	0x45,	0xA0,	0x01},	// W#244 - 	Put BOB in Bypass
      { 0xFF,	0xFF,	0xFF,	0xFB},	// W#245 - 	
      { 0x01,	0x51,	0x72,	0x00},	// W#246 - 	Set SCRATCH2 to 0x01 (to indicate to SW that sleep sequence just ran)
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#247 - 	
      { 0xF4,	0x45,	0xFF,	0x44},	// W#248 - 	Store MODE_CTL1 into R4
      { 0xF6,	0xFF,	0x74,	0xA6},	// W#249 - 	Load data into location pointed to by R6
      { 0x04,	0x00,	0x76,	0x21},	// W#250 - 	Increment pointer by 4 to point at the next set
      { 0xFF,	0xFF,	0xFF,	0x8F},	// W#251 - 	End of subroutine.
      { 0xFF,	0xFF,	0xFF,	0xFB},	// W#252 - 	
      { 0xFF,	0xFF,	0xFF,	0xFB},	// W#253 - 	
      { 0xFF,	0xFF,	0xFF,	0xFB},	// W#254 - 	
      { 0x02,	0x45,	0xA0,	0x01},	// W#255 - 	1BYTE WRITE 0x02 TO BOB_CONFIG__VOUT_MODE_CTRL; Put BOB in Auto Mode
      { 0x01,	0x4A,	0x59,	0x10},	// W#256 - 	1BYTE WRITE 0x01 TO CLK_DIST__PMIC_SLEEP_CTL; Set SLEEP_B to follow HW
      { 0x90,	0xA6,	0x14,	0x11},	// W#257 - 	Re-enable S1 PFM_EXIT_DIP_EN with DIP_LAT_BYP Disabled
      { 0x32,	0xA9,	0x14,	0x11},	// W#258 - 	Re-enable S1 PFM_EXIT_CL_EN (Disable CLL LPM entry method)
      { 0x09,	0x71,	0x14,	0x11},	// W#259 - 	Enable S1 VDIP comparator; keep 15mV threshold
      { 0x90,	0xA6,	0x17,	0x11},	// W#260 - 	Re-enable S2 PFM_EXIT_DIP_EN with DIP_LAT_BYP Disabled
      { 0x32,	0xA9,	0x17,	0x11},	// W#261 - 	Re-enable S2 PFM_EXIT_CL_EN (Disable CLL LPM entry method)
      { 0x09,	0x71,	0x17,	0x11},	// W#262 - 	Enable S2 VDIP comparator; keep 15mV threshold
      { 0x90,	0xA6,	0x1A,	0x11},	// W#263 - 	Re-enable S3 PFM_EXIT_DIP_EN with DIP_LAT_BYP Disabled
      { 0x32,	0xA9,	0x1A,	0x11},	// W#264 - 	Re-enable S3 PFM_EXIT_CL_EN (Disable CLL LPM entry method)
      { 0x09,	0x71,	0x1A,	0x11},	// W#265 - 	Enable S3 VDIP comparator; keep 15mV threshold
      { 0x90,	0xA6,	0x20,	0x11},	// W#266 - 	Re-enable S5 PFM_EXIT_DIP_EN with DIP_LAT_BYP Disabled
      { 0x32,	0xA9,	0x20,	0x11},	// W#267 - 	Re-enable S5 PFM_EXIT_CL_EN (Disable CLL LPM entry method)
      { 0x09,	0x71,	0x20,	0x11},	// W#268 - 	Enable S5 VDIP comparator; keep 15mV threshold
      { 0x18,	0x06,	0x76,	0xA1},	// W#269 - 	Using Location stored in GOTO-Pointer at LOC_SLEEP_BACKUP_DATASET_HEAD
      { 0x54,	0x0A,	0x14,	0x89},	// W#270 - 	
      { 0x54,	0x0A,	0x17,	0x89},	// W#271 - 	
      { 0x54,	0x0A,	0x1A,	0x89},	// W#272 - 	
      { 0x54,	0x0A,	0x20,	0x89},	// W#273 - 	
      { 0x87,	0x00,	0xFE,	0xC1},	// W#274 - 	WAIT 7083 ns; Wait 7us (part of CR-175088)
      { 0x02,	0x51,	0x72,	0x00},	// W#275 - 	Set SCRATCH2 to 0x02 (to indicate to SW that wake sequence just ran)
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#276 - 	
      { 0xF6,	0xFF,	0x74,	0xA2},	// W#277 - 	Load R2 to R5 with data from location pointed to by R6
      { 0xF4,	0x45,	0xFF,	0x0C},	// W#278 - 	ReStore MODE_CTL1 from R4
      { 0x04,	0x00,	0x76,	0x21},	// W#279 - 	Increment pointer by 4 to point at the next set
      { 0xFF,	0xFF,	0xFF,	0x8F},	// W#280 - 	End of subroutine.
      { 0xFF,	0xFF,	0xFF,	0xFB},	// W#281 - 	WCSS Debug Placeholder-0
      { 0xF8,	0x08,	0xC8,	0x40},	// W#282 - 	Read GPIO09B Pin STATUS & Load into R8
      { 0x01,	0x81,	0x01,	0x90},	// W#283 - 	If GPIO9B PIN = High => Set-WCSS-to-Active Trigger was detected
      { 0x88,	0x0A,	0xFF,	0x83},	// W#284 - 	Else If GPIO9 PIN = Low => Set-WCSS-to-Retention Trigger was detected
      { 0xFF,	0xFF,	0xFF,	0xFB},	// W#285 - 	WCSS Debug Placeholder-1
      { 0x40,	0x4F,	0x17,	0x01},	// W#286 - 	PBS VOTE for S2B secondary mode (AUTO)
      { 0x01,	0x94,	0x09,	0x10},	// W#287 - 	Set WCSS_STATE register with updated value (Bit-0 = 1) => WCSS_ACTIVE
      { 0xFF,	0xFF,	0xFF,	0xFB},	// W#288 - 	WCSS Debug Placeholder-2
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#289 - 	
      { 0xFF,	0xFF,	0xFF,	0xFB},	// W#290 - 	Do nothing. (Buffer to apply separate Tags to appropriate TAGs to this & next line)
      { 0xF8,	0x93,	0x09,	0x40},	// W#291 - 	Read present value of MISC.SSC_STATE & Load into R8
      { 0x01,	0x81,	0x01,	0x90},	// W#292 - 	Check SSC_STATE<0>. If = High => proceed w/o touching S2B.PBS_VOTE
      { 0x00,	0x4F,	0x17,	0x01},	// W#293 - 	Else If SSC_STATE = Low => Disable S2B PBS vote for secondary MODE & proceed
      { 0x00,	0x94,	0x09,	0x10},	// W#294 - 	Clear WCSS_STATE register with updated value (Bit-0 = 0) => WCSS_RETENTION
      { 0xFF,	0xFF,	0xFF,	0xFB},	// W#295 - 	WCSS Debug Placeholder-4
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#296 - 	
      { 0xF2,	0x1A,	0xC7,	0x40},	// W#297 - 	Read GPIO08.INT_MID_SEL for SD-Card to UICC PairingInfo
      { 0x00,	0x20,	0x03,	0x90},	// W#298 - 	
      { 0xE8,	0x0A,	0xFF,	0x83},	// W#299 - 	End the sequence if SD-card is NOT paired with any UICC-Card in the tray
      { 0xF5,	0x11,	0xC7,	0x40},	// W#300 - 	Read GPIO08.INT_SET_TYPE into R5 for Expected-state of SD_CARD_PRESENCE
      { 0xF6,	0x08,	0xC7,	0x40},	// W#301 - 	Read GPIO08.STATUS1 into R6 for current-state of GPIO (High/Low)
      { 0xF5,	0xF6,	0x77,	0x22},	// W#302 - 	Update R7 = R6 + R5, Ignore Carry
      { 0x01,	0x71,	0x01,	0x90},	// W#303 - 	IF   R7<0> == 1'b1 ==> ACTUAL_STATE != SD_PRESENCE_STATE --> Proceed to Debounce
      { 0xE8,	0x0A,	0xFF,	0x83},	// W#304 - 	ELSE R7<0> == 1'b0 ==> ACTUAL_STATE == SD_PRESENCE_STATE --> End Sequence
      { 0xFA,	0x8C,	0x09,	0x40},	// W#305 - 	Read MISC.VSET5_LB into RA for Num_Cycles_19M parameter_LSB
      { 0xFB,	0x8D,	0x09,	0x40},	// W#306 - 	Read MISC.VSET5_UB into RB for Num_Cycles_19M parameter_MSB
      { 0xFA,	0xFF,	0xFE,	0xC3},	// W#307 - 	Apply a Debounce of the same Num_Cycles_19M from RB:RA
      { 0x02,	0x48,	0x73,	0x00},	// W#308 - 	Clear Latched Trigger - Bit 1 (Again, in-case it got set again during above debounce-time)
      { 0xF6,	0x08,	0xC7,	0x40},	// W#309 - 	Read GPIO08.STATUS1 into R6 for updated-state of GPIO (High/Low)
      { 0xF5,	0xF6,	0x77,	0x22},	// W#310 - 	Update R7 = R6 + R5, Ignore Carry
      { 0x00,	0x71,	0x01,	0x91},	// W#311 - 	IF   R7<0> == 1'b0 ==> ACTUAL_STATE == SD_PRESENCE_STATE --> End Sequence
      { 0x00,	0x46,	0x41,	0x01},	// W#312 - 	Disable LDO02B
      { 0x00,	0x46,	0x44,	0x01},	// W#313 - 	Disable LDO05B
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#314 - 	
      { 0xFF,	0xFF,	0xFF,	0xFB},	// W#315 - 	SSC Debug Placeholder-0
      { 0xF8,	0x08,	0xC1,	0x40},	// W#316 - 	Read GPIO02B Pin STATUS & Load into R8
      { 0x01,	0x81,	0x01,	0x90},	// W#317 - 	If GPIO2B PIN = High => Set-SSC-to-Active Trigger was detected
      { 0x5C,	0x0B,	0xFF,	0x83},	// W#318 - 	Else If GPIO2 PIN = Low => Set-SSC-to-Retention Trigger was detected
      { 0xFF,	0xFF,	0xFF,	0xFB},	// W#319 - 	SSC Debug Placeholder-1
      { 0xF8,	0x93,	0x09,	0x40},	// W#320 - 	Read present value of MISC.SSC_STATE & Load into R8
      { 0x00,	0x81,	0x01,	0x90},	// W#321 - 	Execute Active-Entry if SSC_STATE<0> = 0 => Previous-state was Retention
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#322 - 	Just END, do nothing if Previous-state was Active already
      { 0xFF,	0xFF,	0xFF,	0xFB},	// W#323 - 	SSC Debug Placeholder-2
      { 0x40,	0x4F,	0x17,	0x01},	// W#324 - 	PBS VOTE for S2B secondary mode (AUTO)
      { 0x07,	0x45,	0x49,	0x01},	// W#325 - 	Set L10B (SSC_MX) to NPM
      { 0x07,	0x45,	0x48,	0x01},	// W#326 - 	Set L09B (SSC_CX) to NPM
      { 0xF8,	0x8E,	0x09,	0x40},	// W#327 - 	Read MISC.VSET6_LB & Load into R8
      { 0x80,	0x81,	0x80,	0x90},	// W#328 - 	If MISC.VSET6_LB<7> = 1 => Update LPI MX/CX VSETs from MISC_VSET4/2 (Active)
      { 0x48,	0x0B,	0xFF,	0x83},	// W#329 - 	Else If MISC.VSET6_LB<7> = 0 => Do Nothing on VSETs but Proceed
      { 0xF9,	0x8A,	0x09,	0x40},	// W#330 - 	Read LB of MISC.VSET4 i.e. Last-Active-VSET on SSC_MX (L10B) & Load it in R9
      { 0xFA,	0x8B,	0x09,	0x40},	// W#331 - 	Read UB of MISC.VSET4 i.e. Last-Active-VSET on SSC_MX (L10B) & Load it in RA
      { 0xF9,	0x40,	0x49,	0x09},	// W#332 - 	Write LB for LDO10B VSET with the value in R9
      { 0xFA,	0x41,	0x49,	0x09},	// W#333 - 	Write UB for LDO10B VSET with the value in RA
      { 0xF9,	0x86,	0x09,	0x40},	// W#334 - 	Read LB of MISC.VSET2 i.e. Last-Active-VSET on SSC_CX (L09B) & Load it in R9
      { 0xFA,	0x87,	0x09,	0x40},	// W#335 - 	Read UB of MISC.VSET2 i.e. Last-Active-VSET on SSC_CX (L09B) & Load it in RA
      { 0xF9,	0x40,	0x48,	0x09},	// W#336 - 	Write LB for LDO09B VSET with the value in R9
      { 0xFA,	0x41,	0x48,	0x09},	// W#337 - 	Write UB for LDO09B VSET with the value in RA
      { 0xF8,	0x93,	0x09,	0x40},	// W#338 - 	Read present value of MISC.SSC_STATE & Load into R8
      { 0x01,	0x00,	0xF8,	0x30},	// W#339 - 	Set Bit<0> High in R8
      { 0xF8,	0x93,	0x09,	0x18},	// W#340 - 	Overwrite SSC_STATE register with updated value (Bit-0 = 1) => SSC_ACTIVE
      { 0xFF,	0xFF,	0xFF,	0xFB},	// W#341 - 	SSC Debug Placeholder-3
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#342 - 	
      { 0xFF,	0xFF,	0xFF,	0xFB},	// W#343 - 	SSC Debug Placeholder-4
      { 0xF8,	0x93,	0x09,	0x40},	// W#344 - 	Read present value of MISC.SSC_STATE & Load into R8
      { 0x01,	0x81,	0x01,	0x90},	// W#345 - 	Execute Retention-Entry if MISC.SSC_STATE<0> = 1 => Previous-state was Active
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#346 - 	Just END, do nothing if Previous-state was Retention already
      { 0xFF,	0xFF,	0xFF,	0xFB},	// W#347 - 	SSC Debug Placeholder-5
      { 0xF8,	0x8E,	0x09,	0x40},	// W#348 - 	Read MISC.VSET6_LB & Load into R8
      { 0x04,	0x81,	0x04,	0x90},	// W#349 - 	If MISC.VSET6_LB<2> = 1 => Backup Last-Active-VSETs of LPI_CX/MX onto MISC-2/4 (Active)
      { 0x9C,	0x0B,	0xFF,	0x83},	// W#350 - 	Else If MISC.VSET6_LB<2> = 0 => Do Nothing (Last-Active-VSETs not backed-up)
      { 0xF9,	0x40,	0x48,	0x41},	// W#351 - 	Read LB of Current-Active-VSET on LDO09B (SSC_CX) & Load it in R9
      { 0xFA,	0x41,	0x48,	0x41},	// W#352 - 	Read UB of Current-Active-VSET on LDO09B (SSC_CX) & Load it in RA
      { 0xF9,	0x86,	0x09,	0x08},	// W#353 - 	Write LB for MISC.VSET2 with R9 - to back it up for use in next Active-Entry Transition
      { 0xFA,	0x87,	0x09,	0x08},	// W#354 - 	Write UB for MISC.VSET2 with RA - to back it up for use in next Active-Entry Transition
      { 0xF9,	0x40,	0x49,	0x41},	// W#355 - 	Read LB of Current-Active-VSET on LDO10B (SSC_MX) & Load it in R9
      { 0xFA,	0x41,	0x49,	0x41},	// W#356 - 	Read UB of Current-Active-VSET on LDO10B (SSC_MX) & Load it in RA
      { 0xF9,	0x8A,	0x09,	0x08},	// W#357 - 	Write LB for MISC.VSET4 with R9 - to back it up for use in next Active-Entry Transition
      { 0xFA,	0x8B,	0x09,	0x08},	// W#358 - 	Write UB for MISC.VSET4 with RA - to back it up for use in next Active-Entry Transition
      { 0x02,	0x81,	0x02,	0x90},	// W#359 - 	If MISC.VSET6_LB<1> = 1 => Update LPI CX/MX Modes to LPM at first
      { 0xAC,	0x0B,	0xFF,	0x83},	// W#360 - 	Else If MISC.VSET6_LB<3> = 0 => Do Nothing (LPI CX/MX modes untouched here)
      { 0x05,	0x45,	0x48,	0x01},	// W#361 - 	Set L09B (SSC_CX) MODE to LPM
      { 0x05,	0x45,	0x49,	0x01},	// W#362 - 	Set L10B (SSC_MX) MODE to LPM
      { 0x08,	0x81,	0x08,	0x90},	// W#363 - 	If MISC.VSET6_LB<3> = 1 => Update LPI CX/MX VSETs from MISC_1/3 (Retention)
      { 0xD4,	0x0B,	0xFF,	0x83},	// W#364 - 	Else If MISC.VSET6_LB<3> = 0 => Do Nothing (VSETs not touched)
      { 0xF9,	0x84,	0x09,	0x40},	// W#365 - 	Read LB of MISC.VSET1 i.e. Preconfigured-Retention-VSET on SSC_CX (L09B) & Load it in R9
      { 0xFA,	0x85,	0x09,	0x40},	// W#366 - 	Read UB of MISC.VSET1 i.e. Preconfigured-Retention-VSET on SSC_CX (L09B) & Load it in RA
      { 0xF9,	0x40,	0x48,	0x09},	// W#367 - 	Write LB for LDO09B VSET with the value in R9
      { 0xFA,	0x41,	0x48,	0x09},	// W#368 - 	Write UB for LDO09B VSET with the value in RA
      { 0xF9,	0x88,	0x09,	0x40},	// W#369 - 	Read LB of MISC.VSET3 i.e. Preconfigured-Retention-VSET on SSC_MX (L10B) & Load it in R9
      { 0xFA,	0x89,	0x09,	0x40},	// W#370 - 	Read UB of MISC.VSET3 i.e. Preconfigured-Retention-VSET on SSC_MX (L10B) & Load it in RA
      { 0xF9,	0x40,	0x49,	0x09},	// W#371 - 	Write LB for LDO10B VSET with the value in R9
      { 0xFA,	0x41,	0x49,	0x09},	// W#372 - 	Write UB for LDO10B VSET with the value in RA
      { 0x01,	0x81,	0x01,	0x90},	// W#373 - 	If MISC.VSET6_LB<0> = 1 => Update LPI CX/MX Modes to RM at last
      { 0xE8,	0x0B,	0xFF,	0x83},	// W#374 - 	Else If MISC.VSET6_LB<0> = 0 => 0=Do Nothing (LPI CX/MX modes untouched here)
      { 0xC0,	0x00,	0xFE,	0xC1},	// W#375 - 	Wait 10us = 192 x 19.2MHz clock-cycles prior to setting Retention-Mode on LDOs
      { 0x04,	0x45,	0x48,	0x01},	// W#376 - 	Set L09B (SSC_CX) MODE to RETENTION
      { 0x04,	0x45,	0x49,	0x01},	// W#377 - 	Set L10B (SSC_MX) MODE to RETENTION
      { 0xF8,	0x94,	0x09,	0x40},	// W#378 - 	Read the register that is sed to store the WCSS state
      { 0x01,	0x81,	0x01,	0x90},	// W#379 - 	Check WCSS_STATE<0>. If WCSS_State = Active, proceed w/o touching S2B.PBS_VOTE
      { 0x00,	0x4F,	0x17,	0x01},	// W#380 - 	Else If WCSS_STATE = Retention => Disable S2B PBS vote for secondary MODE & Proceed
      { 0xF8,	0x93,	0x09,	0x40},	// W#381 - 	Load R8 with present value of MISC.SSC_STATE
      { 0xFE,	0x00,	0xF8,	0x2C},	// W#382 - 	Clear Bit<0> Low in R8
      { 0xF8,	0x93,	0x09,	0x18},	// W#383 - 	Overwrite SSC_STATE register with updated value (Bit-0 = 0) => SSC_RETENTION
      { 0xFF,	0xFF,	0xFF,	0xFB},	// W#384 - 	SSC Debug Placeholder-6
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#385 - 	
      { 0x01,	0x7D,	0xDE,	0x01},	// W#386 - 	PMICPR-636: Increase LDO Headroom to 200mV
      { 0x60,	0x61,	0xDE,	0x01},	// W#387 - 	PMICPR-636: PWM_CTRL_3 = 8CLK
      { 0x80,	0x01,	0xFE,	0xC1},	// W#388 - 	PMICPR-636: Wait 20us (0x180 = 384 x 19.2M pulses = 20us)
      { 0x78,	0x64,	0xDE,	0x01},	// W#389 - 	Variant-1: Enable Clamp, Full-Curr, 1.8V [PMICPR-1031: Mainlining as per 2017-07-10 update]
      { 0x00,	0x80,	0xFF,	0xC5},	// W#390 - 	Start timer for 1 second
      { 0x0E,	0xE5,	0xDE,	0x11},	// W#391 - 	Set DTEST4 to high_psrr_req output
      { 0xF4,	0x09,	0x09,	0x40},	// W#392 - 	read all DTESTs into R4. Bit 3 is DTEST4
      { 0x00,	0xE5,	0xDE,	0x11},	// W#393 - 	free DTEST4
      { 0x00,	0x41,	0x08,	0x90},	// W#394 - 	if bit 3 (DTEST4) is low continue with cool down
      { 0x08,	0x0C,	0xFF,	0x83},	// W#395 - 	otherwise start the whole process over
      { 0xF1,	0x40,	0x73,	0x40},	// W#396 - 	Read RE trigger config to determine what triggered this sequence
      { 0x40,	0x11,	0x40,	0x92},	// W#397 - 	if bit 6 trigger is set then this sequence was triggered after cool down so if is safe to end PSRR mitigation
      { 0x40,	0x00,	0xF1,	0x30},	// W#398 - 	bit 6 was clear. Set it to enable RE trigger
      { 0xF1,	0x40,	0x73,	0x08},	// W#399 - 	RE enabled for client2 bit 6
      { 0x99,	0x19,	0xFF,	0xC5},	// W#400 - 	if bit 6 trigger was cleared then this sequence was triggered by the Detection sequence and cool down needs to run.
      { 0x00,	0x7D,	0xDE,	0x01},	// W#401 - 	PMICPR-636: Decrease LDO Headroom to 100mV
      { 0x80,	0x01,	0xFE,	0xC1},	// W#402 - 	PMICPR-636: Wait 20us (0x180 = 384 x 19.2M pulses = 20us)
      { 0x74,	0x64,	0xDE,	0x01},	// W#403 - 	Enable Clamp, Full-Curr, 1.6V
      { 0x80,	0x07,	0xFE,	0xC1},	// W#404 - 	0x0780 = d'1920 x 19.2M cycles = 100 us
      { 0x5C,	0x64,	0xDE,	0x01},	// W#405 - 	Enable Clamp, Half-Curr, 1.4V
      { 0x80,	0x07,	0xFE,	0xC1},	// W#406 - 	0x0780 = d'1920 x 19.2M cycles = 100 us
      { 0x58,	0x64,	0xDE,	0x01},	// W#407 - 	Enable Clamp, Half-Curr, 1.2V
      { 0x80,	0x07,	0xFE,	0xC1},	// W#408 - 	0x0780 = d'1920 x 19.2M cycles = 100 us
      { 0x54,	0x64,	0xDE,	0x01},	// W#409 - 	Enable Clamp, Half-Curr, 1.0V
      { 0x80,	0x07,	0xFE,	0xC1},	// W#410 - 	0x0780 = d'1920 x 19.2M cycles = 100 us
      { 0x50,	0x64,	0xDE,	0x01},	// W#411 - 	Enable Clamp, Half-Curr, 0.8V
      { 0x80,	0x07,	0xFE,	0xC1},	// W#412 - 	0x0780 = d'1920 x 19.2M cycles = 100 us
      { 0x40,	0x64,	0xDE,	0x01},	// W#413 - 	Disable Clamp
      { 0x80,	0x07,	0xFE,	0xC1},	// W#414 - 	0x0780 = d'1920 x 19.2M cycles = 100 us
      { 0x20,	0x61,	0xDE,	0x01},	// W#415 - 	PMICPR-636: PWM_CTRL_3 = 2CLK
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#416 - 	
      { 0xF4,	0x50,	0x73,	0x40},	// W#417 - 	Read the PBS_CLIENT2.SCRATCH1 register written by SW
      { 0x01,	0x40,	0x01,	0x90},	// W#418 - 	Skip if Bit 0 not set
      { 0xD0,	0x0C,	0xFF,	0x83},	// W#419 - 	Scratch1 Bit-0 was Set, jump to OLEDB_SW_TRIG_CHANGE_PD_STATE
      { 0xFF,	0x51,	0x73,	0x00},	// W#420 - 	Only bit 0 is assigned. If here then there is an error. Set Scratch2 to 0xFF to indicate an error
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#421 - 	
      { 0x11,	0x11,	0x11,	0x11},	// W#422 - 	; S1, B2,B1 = voltage (not used), B0 = mode
      { 0x22,	0x22,	0x22,	0x22},	// W#423 - 	; S2, B2,B1 = voltage (not used), B0 = mode
      { 0x33,	0x33,	0x33,	0x33},	// W#424 - 	; S3  B2,B1 = voltage (not used), B0 = mode
      { 0x55,	0x55,	0x55,	0x55},	// W#425 - 	; S5 voltage, mode
      { 0xFF,	0xFF,	0xFF,	0xFF},	// W#426 - 	Buffer Separation (redundant)
      { 0xFF,	0xFF,	0xFF,	0xFF},	// W#427 - 	| B3:POFF_REASON  | B2:ON_REASON      | B1:WARM_RESET_REASON1 | B0:PON_REASON1
      { 0xFF,	0xFF,	0xFF,	0xFF},	// W#428 - 	| B3:0xFF         | B2:FAULT_REASON2  | B1:FAULT_REASON1      | B0:OFF_REASON
      { 0xFF,	0xFF,	0xFF,	0xFF},	// W#429 - 	| B3:POFF_REASON  | B2:ON_REASON      | B1:WARM_RESET_REASON1 | B0:PON_REASON1
      { 0xFF,	0xFF,	0xFF,	0xFF},	// W#430 - 	| B3:0xFF         | B2:FAULT_REASON2  | B1:FAULT_REASON1      | B0:OFF_REASON
      { 0xFF,	0xFF,	0xFF,	0xFF},	// W#431 - 	| B3:POFF_REASON  | B2:ON_REASON      | B1:WARM_RESET_REASON1 | B0:PON_REASON1
      { 0xFF,	0xFF,	0xFF,	0xFF},	// W#432 - 	| B3:0xFF         | B2:FAULT_REASON2  | B1:FAULT_REASON1      | B0:OFF_REASON
      { 0xFF,	0xFF,	0xFF,	0xFF},	// W#433 - 	Buffer Separation (redundant)
      { 0xED,	0x01,	0xA3,	0xFF},	// W#434 - 	Random Unique RAW DWord (tried to spell 'FF_AMOLED' in Hex)
      { 0x84,	0x0D,	0xFF,	0x83},	// W#435 - 	NOP() or SWIRE_DECODE_SEQUENCE_LGE()
      { 0x58,	0x0D,	0xFF,	0x83},	// W#436 - 	NOP()
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#437 - 	
      { 0x28,	0x41,	0xDC,	0x01},	// W#438 - 	Set IBB Voltage to -4.0V
      { 0x08,	0x49,	0xE0,	0x01},	// W#439 - 	Set OLEDB Voltage to 5.8V
      { 0x00,	0x41,	0xDE,	0x01},	// W#440 - 	Set LAB Voltage to 4.6V
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#441 - 	
      { 0xF6,	0x47,	0xDC,	0x41},	// W#442 - 	Load R6 with IBB.PD_CTL
      { 0x3F,	0x00,	0xF6,	0x2C},	// W#443 - 	AND R6 with 0x3F (b'0000_0011) => Clear Bit-7 (<6:3> absent)
      { 0xF6,	0x47,	0xDC,	0x09},	// W#444 - 	IBB.PD_CTL: ENABLE_PD = 0
      { 0xF6,	0xE9,	0xE0,	0x41},	// W#445 - 	PMICPR-714: Read existing value of OLEDB.TEST6 into R6
      { 0x80,	0x00,	0xF6,	0x30},	// W#446 - 	PMICPR-714: OR R6 with 0x80 (b'1000_0000) => Set Bit-7
      { 0xF6,	0xE9,	0xE0,	0x19},	// W#447 - 	PMICPR-714: Copy updated R6 value back to OLEDB.TEST6
      { 0xF6,	0x78,	0xDE,	0x41},	// W#448 - 	Load R6 with LAB.LDO_PD_CTL [PMICPR-971]
      { 0x7F,	0x00,	0xF6,	0x2C},	// W#449 - 	AND R6 with 0x7F (b'0111_1111) => Clear Bit-7
      { 0xF6,	0x78,	0xDE,	0x09},	// W#450 - 	LAB.LDO_PD_CTL: Disable PD [PMICPR-971]
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#451 - 	
      { 0xF6,	0x47,	0xDC,	0x41},	// W#452 - 	Load R6 with IBB.PD_CTL
      { 0x80,	0x00,	0xF6,	0x30},	// W#453 - 	OR R6 with 0x80 (b'1000_0000) => Set Bit-7
      { 0xF6,	0x47,	0xDC,	0x09},	// W#454 - 	IBB.PD_CTL: ENABLE_PD = 1
      { 0xF6,	0x4B,	0xE0,	0x41},	// W#455 - 	Load R6 with OLEDB.PD_CTL
      { 0x01,	0x00,	0xF6,	0x30},	// W#456 - 	OR R6 with 0x01 (b'0000_0001) => Set Bit-0
      { 0xF6,	0x4B,	0xE0,	0x09},	// W#457 - 	OLEDB.PD_CTL: Set PD_EN
      { 0xF6,	0x78,	0xDE,	0x41},	// W#458 - 	Load R6 with LAB.LDO_PD_CTL [PMICPR-971]
      { 0x80,	0x00,	0xF6,	0x30},	// W#459 - 	OR R6 with 0x80 (b'1000_0000) => Set Bit-7
      { 0xF6,	0x78,	0xDE,	0x09},	// W#460 - 	LAB.LDO_PD_CTL: Enable PD [PMICPR-971]
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#461 - 	
      { 0xF6,	0x5D,	0xDC,	0x41},	// W#462 - 	Load R6 with IBB.OUTPUT_SLEW_CTL
      { 0x40,	0x00,	0xF6,	0x30},	// W#463 - 	OR R6 with 0x40 (b'0100_0000) => Set Bit-6
      { 0xF6,	0x5D,	0xDC,	0x09},	// W#464 - 	Set IBB Slew Rate = FAST
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#465 - 	
      { 0xF6,	0x5D,	0xDC,	0x41},	// W#466 - 	Load R6 with IBB.OUTPUT_SLEW_CTL
      { 0xBF,	0x00,	0xF6,	0x2C},	// W#467 - 	AND R6 with 0xBF (b'1011_1111) => Clear Bit-6
      { 0xF6,	0x5D,	0xDC,	0x09},	// W#468 - 	Set IBB Slew Rate = SLOW
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#469 - 	
      { 0x24,	0x5A,	0xE0,	0x01},	// W#470 - 	1. 0xE05A = 0x24 // disable fast precharge
      { 0x1A,	0xE7,	0xE0,	0x11},	// W#471 - 	3. 0xE0E7 = 0x1A // disable slow precharge
      { 0x80,	0x46,	0xE0,	0x01},	// W#472 - 	4. 0xE046 > 0x80 // enable OLEDB module
      { 0x00,	0x4B,	0xE0,	0x01},	// W#473 - 	5. 0xE04B > 0x00 // disable the pulldown
      { 0x00,	0x46,	0xE0,	0x01},	// W#474 - 	6. 0xE046 > 0x00 // disable OLEDB module
      { 0xA4,	0x5A,	0xE0,	0x01},	// W#475 - 	7. 0xE05A = 0xA4 // enable fast precharge
      { 0x9A,	0xE7,	0xE0,	0x11},	// W#476 - 	9. 0xE0E7 = 0x9A // enable slow precharge
      { 0xF4,	0x51,	0x73,	0x40},	// W#477 - 	Read PBS_CLIENT2.SCRATCH2 & Store Value in PBSREG.R4
      { 0x01,	0x00,	0xF4,	0x30},	// W#478 - 	Set Bit-0 to High (leaving other bits intact)
      { 0xF4,	0x51,	0x73,	0x08},	// W#479 - 	Copy PBSREG.R4 to in PBS_CLIENT2.SCRATCH2 effectively just setting Bit-0
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#480 - 	
      { 0x01,	0x0B,	0xDC,	0x01},	// W#481 - 	Write any value into Status4 to tranfer edge count into Status4 register
      { 0xF4,	0x0B,	0xDC,	0x41},	// W#482 - 	Read SWIRE command data into R4. Could be up to d'57 for SS [Mak]
      { 0x00,	0x40,	0xFF,	0x90},	// W#483 - 	Jump to COUNT_LE_41_CHECK if SWIRE_EDGE_COUNT > 0
      { 0xD8,	0x0C,	0xFF,	0x83},	// W#484 - 	
      { 0x29,	0x45,	0xFF,	0x93},	// W#485 - 	Jump to COUNT_LE_49_CHECK if SWIRE_EDGE_COUNT > 41
      { 0x37,	0x00,	0x76,	0x28},	// W#486 - 	Load R6 with Constant 0x37 (d'55)
      { 0xF6,	0xF4,	0x74,	0x26},	// W#487 - 	R4 = R6 (d'55) - R4 (SWIRE_EDGE_COUNT {1:41})
      { 0xF4,	0x41,	0xDC,	0x09},	// W#488 - 	Set IBB Voltage
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#489 - 	
      { 0x31,	0x45,	0xFF,	0x96},	// W#490 - 	Jump to COUNT_EQ_50_CHECK if SWIRE_EDGE_COUNT > 49
      { 0x2A,	0x00,	0x74,	0x24},	// W#491 - 	R4 = R4 (SWIRE_EDGE_COUNT {42:49}) - 0x2A (d'42)
      { 0xF4,	0xF4,	0x76,	0x22},	// W#492 - 	R6 = R4 + R4 = 2 x R4
      { 0xF4,	0xF6,	0x76,	0x22},	// W#493 - 	R6 = R4 + R6 = 3 x R4
      { 0x1D,	0x00,	0x74,	0x28},	// W#494 - 	Load R4 with Constant 0x1D (d'29 = d'79 - d'50)
      { 0xF4,	0xF6,	0x74,	0x26},	// W#495 - 	R4 = R4 (d'29) - R6
      { 0xF4,	0x49,	0xE0,	0x09},	// W#496 - 	Set OLEDB Voltage
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#497 - 	
      { 0x32,	0x45,	0xFF,	0x90},	// W#498 - 	Jump to COUNT_EQ_51_CHECK if SWIRE_EDGE_COUNT > 50
      { 0x10,	0x0D,	0xFF,	0x83},	// W#499 - 	
      { 0x33,	0x45,	0xFF,	0x90},	// W#500 - 	Jump to COUNT_EQ_52_CHECK if SWIRE_EDGE_COUNT > 51
      { 0xE8,	0x0C,	0xFF,	0x83},	// W#501 - 	
      { 0x34,	0x45,	0xFF,	0x90},	// W#502 - 	Jump to COUNT_EQ_53_CHECK if SWIRE_EDGE_COUNT > 52
      { 0x38,	0x0D,	0xFF,	0x83},	// W#503 - 	
      { 0x35,	0x45,	0xFF,	0x90},	// W#504 - 	Jump to COUNT_LE_57_CHECK if SWIRE_EDGE_COUNT > 53
      { 0x48,	0x0D,	0xFF,	0x83},	// W#505 - 	
      { 0x39,	0x45,	0xFF,	0x92},	// W#506 - 	Jump to COUNT_CHECK_DONE if SWIRE_EDGE_COUNT > 57
      { 0x35,	0x00,	0x76,	0x28},	// W#507 - 	Load R6 with Constant 0x35 (d'53)
      { 0xF4,	0xF6,	0x74,	0x26},	// W#508 - 	R4 = R4 (SWIRE_EDGE_COUNT {54:57}) - R6 (d'53)
      { 0xF4,	0x41,	0xDE,	0x09},	// W#509 - 	Set LAB Voltage
      { 0xFF,	0xFF,	0xFF,	0xFC},	// W#510 - 	
      { 0x10,	0x20,	0xFF,	0xF8},	// W#511 - 	Inserted by compiler.
   },
};
