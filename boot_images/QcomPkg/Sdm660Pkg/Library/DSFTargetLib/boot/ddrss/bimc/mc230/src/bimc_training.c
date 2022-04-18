/****************************************************************************
 QUALCOMM Proprietary Design Data
 Copyright (c) 2015, Qualcomm Technologies Incorporated. All rights reserved.
 ****************************************************************************/
/*==============================================================================
                                EDIT HISTORY

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/DSFTargetLib/boot/ddrss/bimc/mc230/src/bimc_training.c#4 $
$DateTime: 2016/10/12 00:05:04 $
$Author: pwbldsvc $
================================================================================
when       who          what, where, why
--------   ---          --------------------------------------------------------
05/04/14   arindamm     First edit history header. Add new entries at top.
================================================================================*/

#include "bimc.h"
#include "bimc_rpm.h"

//================================================================================================//
// BIMC_CA_Training_Entry
// Enter Vref CA training 
//================================================================================================//
void BIMC_CA_Training_Entry(uint8 ch, DDR_CHIPSELECT chip_select, uint8 FSP_OP)
{
   uint8 FSP_WR = (~FSP_OP & 0x1);
   uint8 opcode_enter =((FSP_OP << 7) | (FSP_WR << 6) | 0x09); //7th bit: FSP_OP, 
                                                               //6th bit: FSP_WR, 
                                                               //3rd bit: VRCG, 
                                                               //0th bit: CBT
   uint32 reg_offset_shke = 0;

   reg_offset_shke = REG_OFFSET_SHKE(ch);

   //Enter CA training mode for the intended FSP_OP and set FSP_WR=1 for the intended training FSP 
   BIMC_MR_Write (CH_1HOT(ch), chip_select, JEDEC_MR_13/*Addr=MR13*/, opcode_enter/*opcode*/);

   // Reset rank init complete so that manual CKE_OFF can be driven out from SHKE
   if (chip_select & DDR_CS0) {
      HWIO_OUTXF (reg_offset_shke, SHKE_CONFIG, RANK0_INITCOMPLETE, 0);
   }
   if (chip_select & DDR_CS1) {
      HWIO_OUTXF (reg_offset_shke, SHKE_CONFIG, RANK1_INITCOMPLETE, 0);
   }   
   //Deassert CKE, FSP automatically changed (enter target freq)
   HWIO_OUTXF (reg_offset_shke, SHKE_DRAM_MANUAL_0, CKE_OFF, 1);
   while (HWIO_INXF(reg_offset_shke, SHKE_DRAM_MANUAL_0, CKE_OFF))
;  // moved semi-colon to silence KW warning

   
    HWIO_OUTXI (REG_OFFSET_GLOBAL0, BIMC_MISC_GLOBAL_CSR_DDR_CHn_HFSC_STAGE1_HANDSHAKE_CTRL, ch, 0xE);
    HWIO_OUTXI (REG_OFFSET_GLOBAL0, BIMC_MISC_GLOBAL_CSR_DDR_CHn_HFSC_STAGE2_HANDSHAKE_CTRL, ch, 0x6);
   
   
   
}


//================================================================================================//
// BIMC_CA_Training_Exit
// exit training by setting MR
//================================================================================================//
void BIMC_CA_Training_Exit_MR (uint8 ch, DDR_CHIPSELECT chip_select, uint8 FSP_OP)
{
   uint8 FSP_WR = (~FSP_OP & 0x1);
   uint8 opcode_exit =((FSP_OP << 7) | (FSP_WR << 6) | 0x00); //7th bit: FSP_OP, 
                                                               //6th bit: FSP_WR, 
                                                               //3rd bit: VRCG, 
                                                               //0th bit: CBT
   //exit current FSP_OP CA training
   BIMC_MR_Write (CH_1HOT(ch), chip_select, JEDEC_MR_13/*Addr=MR13*/, opcode_exit/*opcode*/);

}


//================================================================================================//
// BIMC_CA_Training_Exit
// turn CKE on before exit training
//================================================================================================//
void BIMC_CA_Training_Exit_CKE_ON (uint8 ch, DDR_CHIPSELECT chip_select)
{
   uint32 reg_offset_shke = 0;

   reg_offset_shke = REG_OFFSET_SHKE(ch);

   // tVREF_LONG delay after CKE on, tVREF_LONG = 200ns
   // Convet tVREF_LONG = 200ns to XO clock, 200ns/52ns = 4 after roundup
   BIMC_Wait_Timer_Setup (CH_1HOT(ch), WAIT_XO_CLOCK, 4);

   //assert CKE, FSP auto changed  (enter current freq)
   HWIO_OUTXF (reg_offset_shke, SHKE_DRAM_MANUAL_0, CKE_ON, 1);
   while (HWIO_INXF (reg_offset_shke, SHKE_DRAM_MANUAL_0, CKE_ON));

   // Set rank init complete so that SHKE is put to operating state.
   if (chip_select & DDR_CS0) {
      HWIO_OUTXF (reg_offset_shke, SHKE_CONFIG, RANK0_INITCOMPLETE, 1);
   }
   if (chip_select & DDR_CS1) {
      HWIO_OUTXF (reg_offset_shke, SHKE_CONFIG, RANK1_INITCOMPLETE, 1);
   }

   // Reset manual_1 timer
   BIMC_Wait_Timer_Setup (CH_1HOT(ch), WAIT_XO_CLOCK, 0);
 HWIO_OUTXI (REG_OFFSET_GLOBAL0, BIMC_MISC_GLOBAL_CSR_DDR_CHn_HFSC_STAGE1_HANDSHAKE_CTRL, ch, 0xF);
 HWIO_OUTXI (REG_OFFSET_GLOBAL0, BIMC_MISC_GLOBAL_CSR_DDR_CHn_HFSC_STAGE2_HANDSHAKE_CTRL, ch, 0x7);

}



//================================================================================================//
// BIMC_Send_CA_Pattern
// sending out and receiving CA pattern on DQ bus
// chip_select = CS_BOTH is not supported
//================================================================================================//
void BIMC_Send_CA_Pattern (uint8 ch, uint8 cs)
{
   uint32 reg_offset_shke = 0;

   reg_offset_shke = REG_OFFSET_SHKE(ch);

   //send out CA pattern
   //RANK_SEL cannot be set to '11'
   HWIO_OUTXF2 (reg_offset_shke, SHKE_DRAM_MANUAL_0, RANK_SEL, CA_TRAIN_PATTERN_CMD, CS_1HOT(cs), 1);
   while (HWIO_INXF (reg_offset_shke, SHKE_DRAM_MANUAL_0, CA_TRAIN_PATTERN_CMD));
}


//================================================================================================//
// BIMC_Send_CA_Pattern
// sending out and receiving CA pattern on DQ bus
// chip_select = CS_BOTH is not supported
//================================================================================================//
void BIMC_write_CA_Pattern (uint32 _inst_, uint8 pattern[3])
{
 
    HWIO_OUTX (_inst_, DPE_CA_TRAIN_PRE_CS  , pattern[0]);
    HWIO_OUTX (_inst_, DPE_CA_TRAIN_CS      , pattern[1]);
    HWIO_OUTX (_inst_, DPE_CA_TRAIN_POST_CS , pattern[2]);
}


//================================================================================================//
// BIMC_Send_Vref_value
// setting vref value, sending out and receiving pattern on DQ bus
//================================================================================================//
void BIMC_Send_Vref_Data (uint8 ch, uint8 cs, uint8 vref_data_ch_a, uint8 vref_data_ch_b)
{
   uint32 reg_offset_shke = 0;


   reg_offset_shke = REG_OFFSET_SHKE(ch);

   //Vref training, valid for lpddr4
   HWIO_OUTXF2 (reg_offset_shke, SHKE_VREF_TRAINING_CNTL,
                VREF_DATA_CH_B, VREF_DATA_CH_A, vref_data_ch_b, vref_data_ch_a);

   // tVREF_LONG delay
   // Convet tVREF_LONG = 200ns to XO clock, 200ns/52ns = 4 after roundup
   BIMC_Wait_Timer_Setup (CH_1HOT(ch), WAIT_XO_CLOCK, 0x4);

   HWIO_OUTXF2 (reg_offset_shke, SHKE_DRAM_MANUAL_0, RANK_SEL, VREF_SETUP, CS_1HOT(cs), 1);
   while (HWIO_INXF (reg_offset_shke, SHKE_DRAM_MANUAL_0, VREF_SETUP));

   // Reset manual_1 timer
   BIMC_Wait_Timer_Setup (CH_1HOT(ch), WAIT_XO_CLOCK, 0);

}


//================================================================================================//
// BIMC_CA_Training_Pulse_Ctrl
// Enable/disable 2 pulse mode during CA training
//================================================================================================//
void BIMC_CA_Training_Pulse_Ctrl (uint8 ch, uint8 enable)
{
    HWIO_OUTXF (REG_OFFSET_DPE(ch), DPE_CONFIG_9, DISPATCH_PULSE_DISABLE_CLK, enable);

}


