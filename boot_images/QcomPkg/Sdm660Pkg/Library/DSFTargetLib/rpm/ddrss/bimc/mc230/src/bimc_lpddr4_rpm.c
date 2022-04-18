/****************************************************************************
 QUALCOMM Proprietary Design Data
 Copyright (c) 2015, Qualcomm Technologies Incorporated. All rights reserved.
 ****************************************************************************/
/*==============================================================================
                                EDIT HISTORY

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/DSFTargetLib/rpm/ddrss/bimc/mc230/src/bimc_lpddr4_rpm.c#4 $
$DateTime: 2016/10/12 00:05:04 $
$Author: pwbldsvc $
================================================================================
when       who          what, where, why
--------   ---          --------------------------------------------------------
05/04/14   arindamm     First edit history header. Add new entries at top.
================================================================================*/

#include "bimc_rpm.h"
#include "ddr_ss_seq_hwioreg.h"

//================================================================================================//
// Manual ZQ calibration for LPDDR4
// This function supports ZQ Cal per rank and both ranks. While using for both ranks, ZQCAL_START
// is issued for one rank followed by next rank. ZQCAL_LATCH for both ranks are issued together.
//================================================================================================//
void BIMC_ZQ_Calibration_Lpddr (DDR_STRUCT  *ddr, DDR_CHANNEL channel, DDR_CHIPSELECT chip_select)
{
   uint8  ch = 0;
   uint8  cs = 0;
   uint8  ch_1hot = 0;
   uint32 reg_offset_shke = 0;

   for (ch = 0; ch < 2; ch++)
   {
      ch_1hot = CH_1HOT(ch);
      reg_offset_shke = REG_OFFSET_SHKE(ch);

      if ((channel >> ch) & 0x1)
      {
         // tZQCAL has 100ps resolution, first multiply by 100 to convert resolution to 1ps,
         // then convert to XO_PERIOD. Rounding up using div_ceil function which rounds up
         // any decimal value to the next integer.
         BIMC_Wait_Timer_Setup ((DDR_CHANNEL)ch_1hot, WAIT_XO_CLOCK,
                                  (div_ceil((ddr->cdt_params.lpddr.tZQCAL * 100), XO_PERIOD_IN_PS)));

         for (cs = 0; cs < 2; cs++)
         {
            if ((chip_select >> cs) & 0x1)
            {
            HWIO_OUTXF2 (reg_offset_shke, SHKE_DRAM_MANUAL_0, RANK_SEL, ZQCAL_START, CS_1HOT(cs), 1);
            while (HWIO_INXF (reg_offset_shke, SHKE_DRAM_MANUAL_0, ZQCAL_START));
            }
         }

         // ZQCAL_LATCH doesnot need wait timer. tZQLAT timing is already taken care while
         // executing ZQCAL_LATCH. Hence set the wait timer to 0.
         BIMC_Wait_Timer_Setup ((DDR_CHANNEL)ch_1hot, WAIT_XO_CLOCK, 0);

         HWIO_OUTXF2 (reg_offset_shke, SHKE_DRAM_MANUAL_0, RANK_SEL, ZQCAL_LATCH, chip_select, 1);
         while (HWIO_INXF (reg_offset_shke, SHKE_DRAM_MANUAL_0, ZQCAL_LATCH));
      }
   }
}

//================================================================================================//
// Enter Deep Power Down
//================================================================================================//
boolean BIMC_Enter_Deep_Power_Down (DDR_STRUCT *ddr, DDR_CHANNEL channel, DDR_CHIPSELECT chip_select)
{
    return FALSE;
}

//================================================================================================//
// Exit Deep Power Down
//================================================================================================//
boolean BIMC_Exit_Deep_Power_Down (DDR_STRUCT *ddr, DDR_CHANNEL channel, DDR_CHIPSELECT chip_select)
{
    return FALSE;
}

//================================================================================================//
// Power collapse pre-exit sequence 
//================================================================================================//
void BIMC_Pre_Exit_Power_Collapse (DDR_STRUCT *ddr, DDR_CHANNEL channel)
{
  // Device reset register in DDRSS gets reset during power collapse. Hence set this register
   // to drive reset deasserted to the device before unfreezing the IOs.
   HWIO_OUTX (DDR_PHY_SS_BASE + SEQ_DDR_SS_DDR_REG_DDR_SS_REGS_OFFSET, DDR_SS_REGS_RESET_CMD, 1);
}

