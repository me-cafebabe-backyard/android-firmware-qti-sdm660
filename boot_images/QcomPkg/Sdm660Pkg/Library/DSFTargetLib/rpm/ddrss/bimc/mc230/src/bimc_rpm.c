/****************************************************************************
 QUALCOMM Proprietary Design Data
 Copyright (c) 2015, Qualcomm Technologies Incorporated. All rights reserved.
 ****************************************************************************/
/*==============================================================================
                                EDIT HISTORY

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/DSFTargetLib/rpm/ddrss/bimc/mc230/src/bimc_rpm.c#4 $
$DateTime: 2016/10/12 00:05:04 $
$Author: pwbldsvc $
================================================================================
when       who          what, where, why
--------   ---          --------------------------------------------------------
05/04/14   arindamm     First edit history header. Add new entries at top.
================================================================================*/

#include "bimc_rpm.h"
#include "ddrss_rpm.h"

//================================================================================================//
// BIMC_Enter_Self_Refresh
// disable HW self refresh and enter SW self refresh
//================================================================================================//
void BIMC_Enter_Self_Refresh (DDR_STRUCT *ddr, DDR_CHANNEL channel, DDR_CHIPSELECT chip_select)
{
   uint8 ch = 0;
   uint32 reg_offset_shke = 0;

   for (ch = 0; ch < 2; ch++)
   {
      reg_offset_shke = REG_OFFSET_SHKE(ch);

      if ((channel >> ch) & 0x1)
      {
         // Disable rank and disable HW self refresh
         if (chip_select & DDR_CS0)  {
            BIMC_HW_Self_Refresh_Ctrl (ddr, ch, 0, 0);
         }
         if (chip_select & DDR_CS1)  {
            BIMC_HW_Self_Refresh_Ctrl (ddr, ch, 1, 0);
         }

         // Enter SW self refresh
         HWIO_OUTXF2 (reg_offset_shke, SHKE_DRAM_MANUAL_0, RANK_SEL, ENTER_SELF_REFRESH_IDLE, chip_select, 1);
         while (HWIO_INXF (reg_offset_shke, SHKE_DRAM_MANUAL_0, ENTER_SELF_REFRESH_IDLE));

         while (HWIO_INXF (reg_offset_shke, SHKE_DRAM_STATUS, SW_SELF_RFSH) == 0);
      }
   }
}


//================================================================================================//
// BIMC_Exit_Self_Refresh
// exit SW self refresh and enable HW self refresh
//================================================================================================//
void BIMC_Exit_Self_Refresh (DDR_STRUCT *ddr, DDR_CHANNEL channel, DDR_CHIPSELECT chip_select)
{
   uint8 ch = 0;
   uint32 reg_offset_shke = 0;

   for (ch = 0; ch < 2; ch++)
   {
      reg_offset_shke = REG_OFFSET_SHKE(ch);

      if ((channel >> ch) & 0x1)
      {
         HWIO_OUTXF2 (reg_offset_shke, SHKE_DRAM_MANUAL_0, RANK_SEL, EXIT_SELF_REFRESH, chip_select, 1);
         while (HWIO_INXF (reg_offset_shke, SHKE_DRAM_MANUAL_0, EXIT_SELF_REFRESH));

         while (HWIO_INXF (reg_offset_shke, SHKE_DRAM_STATUS, SW_SELF_RFSH));
         
         //force a manual ZQCAL after Power Collapse
         BIMC_ZQ_Calibration (ddr, CH_1HOT(ch), (DDR_CHIPSELECT)ddr->detected_ddr_device[ch].populated_chipselect);

         //force a refresh rate update
         if (chip_select & DDR_CS0) 
         {
             BIMC_MR_Read (CH_1HOT(ch), DDR_CS0, JEDEC_MR_4);
             // Enable HW self refresh
             BIMC_HW_Self_Refresh_Ctrl (ddr, ch, 0, 1);
         }
         if (chip_select & DDR_CS1) 
         {
             BIMC_MR_Read (CH_1HOT(ch), DDR_CS1, JEDEC_MR_4);
             // Enable HW self refresh
             BIMC_HW_Self_Refresh_Ctrl (ddr, ch, 1, 1);
         }

      }
   }
}

//================================================================================================//
//ZQ Cal function that can either choose lpddr3 or lpddr4
//================================================================================================//
void BIMC_ZQ_Calibration (DDR_STRUCT  *ddr, DDR_CHANNEL channel, DDR_CHIPSELECT chip_select)
{
   uint8 ch      = 0;
   uint8 ch_1hot = 0;

   for (ch = 0; ch < 2; ch++)
   {
      ch_1hot = CH_1HOT(ch);

      if ((channel >> ch) & 0x1)
      {
         if (chip_select & DDR_CS0) {
             BIMC_ZQ_Calibration_Lpddr (ddr, (DDR_CHANNEL)ch_1hot, DDR_CS0);
         }
         if (chip_select & DDR_CS1) {
             BIMC_ZQ_Calibration_Lpddr (ddr, (DDR_CHANNEL)ch_1hot, DDR_CS1);
         }
      }
   }
}



//================================================================================================//
// Enter SW self refresh and ensure RANK0/1 is in self refresh state
//================================================================================================//
void BIMC_Enter_Power_Collapse (DDR_STRUCT *ddr, DDR_CHANNEL channel)

{
   uint32 reg_offset_dpe = 0;
   uint8  ch = 0;

   for (ch = 0; ch < 2; ch++)
   {
      reg_offset_dpe = REG_OFFSET_DPE(ch);

      if ((channel >> ch) & 0x1)
      {

         BIMC_Enter_Self_Refresh (ddr, CH_1HOT(ch), (DDR_CHIPSELECT)ddr->detected_ddr_device[ch].populated_chipselect);

         // Check if it's in self refresh state.
         if (ddr->detected_ddr_device[ch].populated_chipselect & DDR_CS0) {
            while (HWIO_INXF (reg_offset_dpe, DPE_DRAM_STATUS_0, RANK_0_SR) == 0);
         }

         if (ddr->detected_ddr_device[ch].populated_chipselect & DDR_CS1) {
            while (HWIO_INXF (reg_offset_dpe, DPE_DRAM_STATUS_0, RANK_1_SR) == 0);
         }

      }
   }
}

//================================================================================================//
// Power collapse exit sequence for retention mode requires exiting SW self refresh
// Timing parameters and self refresh status in BIMC are already retained by retention registers
//================================================================================================//
void BIMC_Exit_Power_Collapse (DDR_STRUCT *ddr, DDR_CHANNEL channel)
{

   uint8  ch = 0;

   for (ch = 0; ch < 2; ch++)
   {
      if ((channel >> ch) & 0x1)
      {
         BIMC_Exit_Self_Refresh (ddr, CH_1HOT(ch), (DDR_CHIPSELECT)ddr->detected_ddr_device[ch].populated_chipselect);
      }
   }
}



