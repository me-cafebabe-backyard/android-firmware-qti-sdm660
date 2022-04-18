/****************************************************************************
 QUALCOMM Proprietary Design Data
 Copyright (c) 2015, Qualcomm Technologies Incorporated. All rights reserved.
 ****************************************************************************/
/*==============================================================================
                                EDIT HISTORY

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/DSFTargetLib/rpm/ddrss/bimc/mc230/src/bimc_common_rpm.c#4 $
$DateTime: 2016/10/12 00:05:04 $
$Author: pwbldsvc $
================================================================================
when       who          what, where, why
--------   ---          --------------------------------------------------------
05/04/14   arindamm     First edit history header. Add new entries at top.
================================================================================*/

#include "bimc_rpm.h"

//================================================================================================//
//Timer function is called before triggering DRAM_MANUAL_0 command
//WAIT_TIMER_DOMAIN has 2 options: XO clock(19.2MHz) and Timer clock(32KHz), enum defined in ddr_common.h
//================================================================================================//
void BIMC_Wait_Timer_Setup (DDR_CHANNEL channel, BIMC_Wait_Timer_Domain one_xo_zero_timer_clk, uint32 timer_value)
{
   uint8  ch = 0;
   uint32 reg_offset_shke = 0;

   for (ch = 0; ch < 2; ch++)
   {
      reg_offset_shke = REG_OFFSET_SHKE(ch);
      if ((channel >> ch) & 0x1)
      {
         HWIO_OUTXF2 (reg_offset_shke, SHKE_DRAM_MANUAL_1, WAIT_TIMER_DOMAIN, WAIT_TIMER_BEFORE_HW_CLEAR, one_xo_zero_timer_clk, timer_value);
      }
   }

}
//================================================================================================//
//Mode Register write can use for both channels and both ranks
//================================================================================================//
void BIMC_MR_Write (DDR_CHANNEL channel, DDR_CHIPSELECT chip_select, uint32 MR_addr, uint32 MR_data)
{
   uint8 ch = 0;
   uint32 reg_offset_shke = 0;

   for (ch = 0; ch < 2; ch++)
   {
      reg_offset_shke = REG_OFFSET_SHKE(ch);
      if ((channel >> ch) & 0x1)
      {
         HWIO_OUTXF2 (reg_offset_shke, SHKE_MREG_ADDR_WDATA_CNTL, MREG_ADDR, MREG_WDATA, MR_addr, MR_data);
         HWIO_OUTXF2 (reg_offset_shke, SHKE_DRAM_MANUAL_0, RANK_SEL, MODE_REGISTER_WRITE, chip_select, 1);
         while (HWIO_INXF (reg_offset_shke, SHKE_DRAM_MANUAL_0, MODE_REGISTER_WRITE));
      }
   }

}

//================================================================================================//
//Mode register read function only returns a single MR value, it reads on per channel per rank basis
//Both-channel option is not supported for DDR_CHANNEL
//================================================================================================//
uint32 BIMC_MR_Read (DDR_CHANNEL channel, DDR_CHIPSELECT chip_select, uint32 MR_addr)
{
   uint32  read_value = 0;
   uint32 reg_offset_shke = 0;

   reg_offset_shke = REG_OFFSET_SHKE(CH_INX(channel));

   HWIO_OUTXF (reg_offset_shke, SHKE_MREG_ADDR_WDATA_CNTL, MREG_ADDR, MR_addr);

   HWIO_OUTXF2 (reg_offset_shke, SHKE_DRAM_MANUAL_0, RANK_SEL, MODE_REGISTER_READ, chip_select, 1);
   while (HWIO_INXF (reg_offset_shke, SHKE_DRAM_MANUAL_0, MODE_REGISTER_READ));

   if(chip_select == DDR_CS0) {
      read_value = HWIO_INX (reg_offset_shke, SHKE_MREG_RDATA_RANK0_L);
   }
   if(chip_select == DDR_CS1) {
      read_value = HWIO_INX (reg_offset_shke, SHKE_MREG_RDATA_RANK1_L);
   }


   return read_value;
}

//================================================================================================//
// Enable/Disable HW activity based self refresh
//================================================================================================//
void BIMC_HW_Self_Refresh_Ctrl (DDR_STRUCT *ddr, uint8 ch, uint8 cs, uint8 enable)
{

   // Check if this feature is enabled in the DDR_STRUCT
   if (ddr->extended_cdt_runtime.hw_self_refresh_enable[ch] == 1) {
      if (cs == 0) {
         HWIO_OUTXF (REG_OFFSET_SHKE(ch), SHKE_SELF_REFRESH_CNTL, HW_SELF_RFSH_ENABLE_RANK0, enable);
      }
      if (cs == 1) {
         HWIO_OUTXF (REG_OFFSET_SHKE(ch), SHKE_SELF_REFRESH_CNTL, HW_SELF_RFSH_ENABLE_RANK1, enable);
      }
   }
}

//================================================================================================//
// enable signals controls whether enable or disable auto refresh
//================================================================================================//
void BIMC_Auto_Refresh_Ctrl (DDR_CHANNEL channel, DDR_CHIPSELECT chip_select, uint8 enable)
{
   uint8  ch        = 0;
   uint32 reg_offset_shke = 0;

   for (ch = 0; ch < 2; ch++)
   {
      reg_offset_shke = REG_OFFSET_SHKE(ch);

      if ((channel >> ch) & 0x1)
      {
         if (chip_select & DDR_CS0) {
            HWIO_OUTXF (reg_offset_shke, SHKE_AUTO_REFRESH_CNTL, AUTO_RFSH_ENABLE_RANK0, enable);
         }
         if (chip_select & DDR_CS1) {
            HWIO_OUTXF (reg_offset_shke, SHKE_AUTO_REFRESH_CNTL, AUTO_RFSH_ENABLE_RANK1, enable);
         }
      }
   }
}


//================================================================================================//
// Enable and disable TUF bit override
//================================================================================================//
void BIMC_Refresh_Rate_Ctrl (DDR_CHANNEL channel, DDR_CHIPSELECT chip_select)  //TODO: PVP 06092015: Move to bimc_common.c. 
{
   uint8  ch        = 0;
   uint32 reg_offset_dpe = 0;

   for (ch = 0; ch < 2; ch++)
   {
      reg_offset_dpe = REG_OFFSET_DPE(ch);

      if ((channel >> ch) & 0x1)
      {
        HWIO_OUTXF (reg_offset_dpe, DPE_DERATE_TEMP_CTRL, TUF_OVERRIDE_VALUE, 1);
        if (chip_select & DDR_CS0) 
        {
            BIMC_MR_Read (CH_1HOT(ch), DDR_CS0, JEDEC_MR_4);
        }
        if (chip_select & DDR_CS1) 
        {
            BIMC_MR_Read (CH_1HOT(ch), DDR_CS1, JEDEC_MR_4);
        }
        HWIO_OUTXF (reg_offset_dpe, DPE_DERATE_TEMP_CTRL, TUF_OVERRIDE_VALUE, 0);       
      }
   }
}


//================================================================================================//
// Periodic events controlled through this function are
// 1. Auto refresh
// 2. HW self refresh (activity based)
// 3. ZQ calibration
// 4. Temperature status read
//================================================================================================//
void BIMC_All_Periodic_Ctrl (DDR_STRUCT *ddr, DDR_CHANNEL channel, DDR_CHIPSELECT chip_select, uint8 enable)
{
   uint8  rank_ctrl = 0;
   uint8  ch        = 0;
   uint32 reg_offset_shke = 0;

   for (ch = 0; ch < 2; ch++)
   {
      reg_offset_shke = REG_OFFSET_SHKE(ch);

      if ((channel >> ch) & 0x1)
      {
        // Auto refresh and HW activity based self refresh
        if (chip_select & DDR_CS0) {
           HWIO_OUTXF (reg_offset_shke, SHKE_AUTO_REFRESH_CNTL, AUTO_RFSH_ENABLE_RANK0,    enable);
           BIMC_HW_Self_Refresh_Ctrl (ddr, ch, 0, enable);
        }
        if (chip_select & DDR_CS1) {
           HWIO_OUTXF (reg_offset_shke, SHKE_AUTO_REFRESH_CNTL, AUTO_RFSH_ENABLE_RANK1,    enable);
           BIMC_HW_Self_Refresh_Ctrl (ddr, ch, 1, enable);
        }

        // Periodic ZQ calibration
        rank_ctrl = HWIO_INXF (reg_offset_shke, SHKE_PERIODIC_ZQCAL, RANK_SEL);
        rank_ctrl = enable ? (rank_ctrl | chip_select) : (rank_ctrl & ~chip_select);
        HWIO_OUTXF  (reg_offset_shke, SHKE_PERIODIC_ZQCAL, RANK_SEL, rank_ctrl);

        // Periodic temperature status read (SRR)
        if (ddr->extended_cdt_runtime.MR4_polling_enable == 1) 
        {
           rank_ctrl = HWIO_INXF  (reg_offset_shke, SHKE_PERIODIC_MRR, MRR_RANK_SEL);
           rank_ctrl = enable ? (rank_ctrl | chip_select) : (rank_ctrl & ~chip_select);
           HWIO_OUTXF  (reg_offset_shke, SHKE_PERIODIC_MRR, MRR_RANK_SEL, rank_ctrl);
        }
      }
   }
}

//================================================================================================//
// Enable or disable DownTime requests from SHKE (for periodic training) and QoS_FSSH (for freq switch)
//================================================================================================//
void BIMC_Downtime_Request_Ctrl (DDR_CHANNEL channel, uint8 enable)
{
   uint8  ch        = 0;
   uint32 reg_offset_shke = 0;

   for (ch = 0; ch < 2; ch++)
   {
      reg_offset_shke = REG_OFFSET_SHKE(ch);

      if ((channel >> ch) & 0x1)
      {
        HWIO_OUTXF (reg_offset_shke, SHKE_SAFE_CTRL, SAFE_EN, enable);
      }
   }

   HWIO_OUTXF (REG_OFFSET_GLOBAL0, BIMC_MISC_GLOBAL_CSR_QOS_FSSH_CTRL, FSSH_DISABLE, ~enable);
}


//================================================================================================//
// Temperature controlled minimim frequency is dictated by the refresh rate at which DRAM
// device has to operate
//================================================================================================//
uint32 BIMC_Temp_Ctrl_Min_Freq (DDR_STRUCT *ddr, DDR_CHANNEL channel)
{
 
   uint8  ch = 0;
   uint32 reg_offset_dpe = 0;
   uint32 rank0_temp_info[2] = {0};
   uint32 rank1_temp_info[2] = {0};
   uint32 max_temp_info = 0;
   uint32 min_freq = 0;

   for (ch = 0; ch < 2; ch++)
   {
      reg_offset_dpe = REG_OFFSET_DPE(ch);

      if ((channel >> ch) & 0x1)
      {
         if (ddr->detected_ddr_device[ch].populated_chipselect & DDR_CS0) {
            rank0_temp_info[ch] = HWIO_INXF (reg_offset_dpe, DPE_INTERRUPT_STATUS, RANK0_TEMP_INFO);
         }

         if (ddr->detected_ddr_device[ch].populated_chipselect & DDR_CS1) {
            rank1_temp_info[ch] = HWIO_INXF (reg_offset_dpe, DPE_INTERRUPT_STATUS, RANK1_TEMP_INFO);
         }

      }
   }

   if ((rank0_temp_info[0] >= rank1_temp_info[0]) &&
       (rank0_temp_info[0] >= rank0_temp_info[1]) &&
       (rank0_temp_info[0] >= rank1_temp_info[1]))
   {
      max_temp_info = rank0_temp_info[0];
   }
   else if ((rank0_temp_info[1] >= rank0_temp_info[0]) &&
            (rank0_temp_info[1] >= rank1_temp_info[0]) &&
            (rank0_temp_info[1] >= rank1_temp_info[1]))
   {
      max_temp_info = rank0_temp_info[1];
   }
   else if ((rank1_temp_info[0] >= rank0_temp_info[0]) &&
            (rank1_temp_info[0] >= rank0_temp_info[1]) &&
            (rank1_temp_info[0] >= rank1_temp_info[1]))
   {
      max_temp_info = rank1_temp_info[0];
   }
   else if ((rank1_temp_info[1] >= rank0_temp_info[0]) &&
            (rank1_temp_info[1] >= rank0_temp_info[1]) &&
            (rank1_temp_info[1] >= rank1_temp_info[0]))
   {
      max_temp_info = rank1_temp_info[1];
   }

   // Check for refresh rate greater than 1x
   if (max_temp_info > 0x3)
   {
      // Check for 0.5x refresh rate
      if (max_temp_info == 0x4)
      {
         // 0.5x
         min_freq = 50000;
      }
      else
      {
         // 0.25x or higher
         min_freq = 100000;
      }
   }
   else
   {
      // 1x or lower
      min_freq = 19200;
   }

   return min_freq;

}

