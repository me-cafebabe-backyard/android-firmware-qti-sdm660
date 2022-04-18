/****************************************************************************
 QUALCOMM Proprietary Design Data
 Copyright (c) 2015, Qualcomm Technologies Incorporated. All rights reserved.
 ****************************************************************************/
/*==============================================================================
                                EDIT HISTORY

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/DSFTargetLib/rpm/ddrss/phy/phy30/src/ddr_phy_power_collapse_rpm.c#6 $
$DateTime: 2016/12/30 05:44:11 $
$Author: pwbldsvc $
================================================================================
when       who          what, where, why
--------   ---          --------------------------------------------------------
03/31/15   jeasley      First edit history header. Add new entries at top.
================================================================================*/
#include "ddrss_rpm.h"

//==============================================================================//
// DDR PHY and CC Power Collapse Sequences
//==============================================================================//
// Main entry point (DDR_PHY_rtn_pcc)
//==============================================================================//

void DDR_PHY_rtn_pcc_pre_collapse (DDR_STRUCT *ddr,
                                   uint8  pc_mode,
                                   uint32 clk_freq_khz
                                   )
{
  // Local variables
  uint8  pc_ack = 0;

  // Start the DDR PHY power collapse sequence
  DDR_PHY_hal_pcc_start (ddr,
                         pc_mode
                         );
 
  // Aggregate poll for PC ACK assertion  
  while (pc_ack == 0x0) 
  {
    pc_ack = ((HWIO_INXF(REG_OFFSET_DDR_PHY_CH(0) + CA0_DDR_PHY_OFFSET, DDR_PHY_DDRPHY_PCC_PC_STA,PC_ACK)) & 
              (HWIO_INXF(REG_OFFSET_DDR_PHY_CH(0) + DQ0_DDR_PHY_OFFSET, DDR_PHY_DDRPHY_PCC_PC_STA,PC_ACK)) & 
              (HWIO_INXF(REG_OFFSET_DDR_PHY_CH(0) + DQ1_DDR_PHY_OFFSET, DDR_PHY_DDRPHY_PCC_PC_STA,PC_ACK)) & 
              (HWIO_INXF(REG_OFFSET_DDR_CC_CH(0) + DDR_CC_OFFSET,      DDR_CC_DDRCC_PCC_PC_STA  ,PC_ACK)) &
              (HWIO_INXF(REG_OFFSET_DDR_PHY_CH(1) + CA0_DDR_PHY_OFFSET, DDR_PHY_DDRPHY_PCC_PC_STA,PC_ACK)) & 
              (HWIO_INXF(REG_OFFSET_DDR_PHY_CH(1) + DQ0_DDR_PHY_OFFSET, DDR_PHY_DDRPHY_PCC_PC_STA,PC_ACK)) & 
              (HWIO_INXF(REG_OFFSET_DDR_PHY_CH(1) + DQ1_DDR_PHY_OFFSET, DDR_PHY_DDRPHY_PCC_PC_STA,PC_ACK)) & 
              (HWIO_INXF(REG_OFFSET_DDR_CC_CH(1) + DDR_CC_OFFSET,      DDR_CC_DDRCC_PCC_PC_STA  ,PC_ACK)));
  }
  
  // Enable DDRCC freeze IO
  HWIO_OUTXF2(REG_OFFSET_DDR_PHY_CH(0) + DDR_CC_OFFSET, DDR_CC_DDRCC_PCC_PC_CFG, SW_PC_FREEZE_IO_EN, SW_PC_FREEZE_IO, 1, 1);
  HWIO_OUTXF2(REG_OFFSET_DDR_PHY_CH(1) + DDR_CC_OFFSET, DDR_CC_DDRCC_PCC_PC_CFG, SW_PC_FREEZE_IO_EN, SW_PC_FREEZE_IO, 1, 1);
}//DDR_PHY_rtn_pcc_pre_collapse 

void DDR_PHY_rtn_pcc_post_collapse (DDR_STRUCT *ddr,
                                    uint8  pc_mode,
                                    uint32 clk_freq_khz
                                   )
    
{
  // Local variables
  uint8  pc_ack = 1;
  // Disable DDRCC freeze IO
  HWIO_OUTXF2(REG_OFFSET_DDR_PHY_CH(0) + DDR_CC_OFFSET, DDR_CC_DDRCC_PCC_PC_CFG, SW_PC_FREEZE_IO_EN, SW_PC_FREEZE_IO, 0, 0);
  HWIO_OUTXF2(REG_OFFSET_DDR_PHY_CH(1) + DDR_CC_OFFSET, DDR_CC_DDRCC_PCC_PC_CFG, SW_PC_FREEZE_IO_EN, SW_PC_FREEZE_IO, 0, 0);
  // Stop the DDR PHY power collapse sequence
  DDR_PHY_hal_pcc_stop (ddr,
                        pc_mode
                       );

  // Poll for PC ACK deassertion
  if ((pc_mode == PHY_POWER_CLPS_RESTORE) || (pc_mode == PHY_POWER_CLPS_SAVE_RESTORE))
  {
    while (pc_ack == 0x1) 
    {
      pc_ack = ((HWIO_INXF(REG_OFFSET_DDR_PHY_CH(0) + CA0_DDR_PHY_OFFSET, DDR_PHY_DDRPHY_PCC_PC_STA,PC_ACK)) | 
                (HWIO_INXF(REG_OFFSET_DDR_PHY_CH(0) + DQ0_DDR_PHY_OFFSET, DDR_PHY_DDRPHY_PCC_PC_STA,PC_ACK)) | 
                (HWIO_INXF(REG_OFFSET_DDR_PHY_CH(0) + DQ1_DDR_PHY_OFFSET, DDR_PHY_DDRPHY_PCC_PC_STA,PC_ACK)) | 
                (HWIO_INXF(REG_OFFSET_DDR_CC_CH(0) + DDR_CC_OFFSET     , DDR_CC_DDRCC_PCC_PC_STA,  PC_ACK)) |
                (HWIO_INXF(REG_OFFSET_DDR_PHY_CH(1) + CA0_DDR_PHY_OFFSET, DDR_PHY_DDRPHY_PCC_PC_STA,PC_ACK)) | 
                (HWIO_INXF(REG_OFFSET_DDR_PHY_CH(1) + DQ0_DDR_PHY_OFFSET, DDR_PHY_DDRPHY_PCC_PC_STA,PC_ACK)) | 
                (HWIO_INXF(REG_OFFSET_DDR_PHY_CH(1) + DQ1_DDR_PHY_OFFSET, DDR_PHY_DDRPHY_PCC_PC_STA,PC_ACK)) | 
                (HWIO_INXF(REG_OFFSET_DDR_CC_CH(1) + DDR_CC_OFFSET     , DDR_CC_DDRCC_PCC_PC_STA,  PC_ACK)));
    }

  }


  // Complete DDR PHY the power collapse sequence
  DDR_PHY_hal_pcc_complete (ddr,
                            pc_mode,
                            clk_freq_khz
                            );

  if ((pc_mode == PHY_POWER_CLPS_RESTORE) || (pc_mode == PHY_POWER_CLPS_SAVE_RESTORE))
  {
    //stop_tick = VVDRV_clk_getTick();
    //delta_tick_us = (((stop_tick - start_tick) * 1000000)/19200000);
    //ddr_printf(DDR_NORMAL, "PC Restore Post %d usec\n\n", delta_tick_us);
    //start_tick = VVDRV_clk_getTick();
    
    //Reset DDR PHY DCC
 //   if (((ddr->misc.platform_id == PLATFORM_ID_ISTARI) && ((ddr->misc.chip_version >= 0x0200) && (ddr->misc.chip_version <= 0x0210))))
 //   {
 //     DDR_PHY_DCC_Reset (0); // Channel 0
 //     DDR_PHY_DCC_Reset (1); // Channel 1
 //   }

    //stop_tick = VVDRV_clk_getTick();
    //delta_tick_us = (((stop_tick - start_tick) * 1000000)/19200000);
    //ddr_printf(DDR_NORMAL, "DCC Reset both channels %d usec\n\n", delta_tick_us);
    //start_tick = VVDRV_clk_getTick();

    DDRSS_ddr_phy_sw_freq_switch_PC(ddr);//,clk_freq_khz); 

  //  DDR_PHY_hal_cfg_sw_iocal (REG_OFFSET_DDR_PHY_CH(0) + CA0_DDR_PHY_OFFSET ); 

  //  DDR_PHY_hal_cfg_sw_iocal (REG_OFFSET_DDR_PHY_CH(1) + CA0_DDR_PHY_OFFSET ); 
  }
} // End of DDR_PHY_rtn_pcc_post_collapse 

//===============================================================================
//This API Saves the DDR PHY and DDRCC CSRs before VDDA power collapse into the 
//balloon retention flops in VDDCX domain.

//===============================================================================

void DDR_PHY_hal_pcc_start (DDR_STRUCT *ddr,
                            uint8 pc_mode
                           )

{
  // Enable broadcast mode CA and DQ PHYs
  HWIO_OUTX((DDR_PHY_SS_BASE + SEQ_DDR_SS_DDRSS_AHB2PHY_SWMAN_OFFSET),
             AHB2PHY_SWMAN_AHB2PHY_BROADCAST_EN_CFG_LOWER, 
             PC_PHY_CA_DQ_BROADCAST
           );
  
  /// Set the Link and Memory index pointers
  HWIO_OUTX(BROADCAST_BASE,DDR_PHY_DDRPHY_PCC_LL_CFG, 0x00000000); //LL_IDX
  HWIO_OUTX(BROADCAST_BASE,DDR_PHY_DDRPHY_PCC_MEM_CFG,0x00000000); //MEM_IDX

  if (pc_mode == PHY_POWER_CLPS_RESTORE)
  {
    /// Set the CPR sensor into bypass mode 0x28064  CPR_SENSOR_BYPASS
    HWIO_OUTX(BROADCAST_BASE, DDR_PHY_DDRPHY_PCC_PC_CFG, 0x28064);

    /// Set the CSR chain into bypass mode // PHY_CSR_CHAIN_BYPASS 0x2C064
    HWIO_OUTX(BROADCAST_BASE, DDR_PHY_DDRPHY_PCC_PC_CFG, 0x2C064);

    /// Set the request type  0x2C068  SW_PC_REQ_TYPE
    HWIO_OUTX(BROADCAST_BASE,DDR_PHY_DDRPHY_PCC_PC_CFG, 0x2C068);

    /// Set the SW request enable  // SW_PC_REQ_EN 0x2C069
    HWIO_OUTX(BROADCAST_BASE,DDR_PHY_DDRPHY_PCC_PC_CFG, 0x2C069);
  
    /// Set the PCC request  // SW_PC_REQ  0x2C06B
    HWIO_OUTX(BROADCAST_BASE,DDR_PHY_DDRPHY_PCC_PC_CFG, 0x2C06B);
  }
  else // SAVE
  {
    /// Set the CSR chain into bypass mode 0x24061 // PHY_CSR_CHAIN_BYPASS
    HWIO_OUTX(BROADCAST_BASE, DDR_PHY_DDRPHY_PCC_PC_CFG, 0x24061);

    // Set the PCC Type field //0x24065  // PCC_TYPE
    HWIO_OUTX(BROADCAST_BASE,DDR_PHY_DDRPHY_PCC_PC_CFG, 0x24065);

    /// Set the SW request enable  0x24065 // SW_PC_REQ_EN
    HWIO_OUTX(BROADCAST_BASE,DDR_PHY_DDRPHY_PCC_PC_CFG, 0x24065);
  
    /// Set the PCC request  0x24067  // SW_PC_REQ
    HWIO_OUTX(BROADCAST_BASE,DDR_PHY_DDRPHY_PCC_PC_CFG, 0x24067);
  }

  //-----------------------------------------
  // Repeat the sequence for the DDR CCs
  //-----------------------------------------
  // Enable broadcast mode DDR CCs
  HWIO_OUTX((DDR_PHY_SS_BASE + SEQ_DDR_SS_DDRSS_AHB2PHY_SWMAN_OFFSET),
             AHB2PHY_SWMAN_AHB2PHY_BROADCAST_EN_CFG_LOWER, 
             PC_CC_BROADCAST
           );
  
  /// Set the Link and Memory index pointers
  HWIO_OUTX(BROADCAST_BASE,DDR_CC_DDRCC_PCC_LL_CFG, 0x0); // LL_IDX
  HWIO_OUTX(BROADCAST_BASE,DDR_CC_DDRCC_PCC_MEM_CFG,0x0); // MEM_IDX

  if (pc_mode == PHY_POWER_CLPS_RESTORE)
  {
    // PHY_CSR_CHAIN_BYPASS   0x24024
    HWIO_OUTX(BROADCAST_BASE, DDR_CC_DDRCC_PCC_PC_CFG, 0x24024);

    /// Set the request type   SW_PC_REQ_TYPE 0x24028
    HWIO_OUTX(BROADCAST_BASE, DDR_CC_DDRCC_PCC_PC_CFG, 0x24028);

    /// Set the SW request enable // SW_PC_REQ_EN 0x24029
    HWIO_OUTX(BROADCAST_BASE, DDR_CC_DDRCC_PCC_PC_CFG, 0x24029);
  
    /// Set the PCC request  0x2402B SW_PC_REQ
    HWIO_OUTX(BROADCAST_BASE, DDR_CC_DDRCC_PCC_PC_CFG, 0x2402B);
  }
  else // SAVE
  { 
    // PHY_CSR_CHAIN_BYPASS   0x24021
    HWIO_OUTX(BROADCAST_BASE, DDR_CC_DDRCC_PCC_PC_CFG, 0x24021);

    // PCC_TYPE  0x24025
    HWIO_OUTX(BROADCAST_BASE, DDR_CC_DDRCC_PCC_PC_CFG, 0x24025);

    /// Set the SW request enable 0x24025 // SW_PC_REQ_EN
    HWIO_OUTX(BROADCAST_BASE, DDR_CC_DDRCC_PCC_PC_CFG, 0x24025);
  
    /// Set the PCC request  0x24027
    HWIO_OUTX(BROADCAST_BASE, DDR_CC_DDRCC_PCC_PC_CFG, 0x24027);
  }

} // End of ddr_phy_hal_pcc_start 

void DDR_PHY_hal_pcc_stop (DDR_STRUCT *ddr,
                           uint8  pc_mode
                          )

{
  // Enable broadcast mode CA and DQ PHYs
  HWIO_OUTX((DDR_PHY_SS_BASE + SEQ_DDR_SS_DDRSS_AHB2PHY_SWMAN_OFFSET),
             AHB2PHY_SWMAN_AHB2PHY_BROADCAST_EN_CFG_LOWER, 
             PC_PHY_CA_DQ_BROADCAST
           );

  /// Set the Link and Memory index pointers
  HWIO_OUTX(BROADCAST_BASE,DDR_PHY_DDRPHY_PCC_LL_CFG, 0x0); // LL_IDX
  HWIO_OUTX(BROADCAST_BASE,DDR_PHY_DDRPHY_PCC_MEM_CFG,0x0); // MEM_IDX

  /// Deassert the PCC request
  if (pc_mode == PHY_POWER_CLPS_RESTORE)
  {     // SW_PC_REQ  ->0x2C069
    HWIO_OUTX(BROADCAST_BASE,DDR_PHY_DDRPHY_PCC_PC_CFG, 0x2C069);
  }
  else  // SAVE  SW_PC_REQ 0x24065
  {
    HWIO_OUTX(BROADCAST_BASE,DDR_PHY_DDRPHY_PCC_PC_CFG, 0x24065);
  }

  //----------------------------------------
  // Repeat the sequence for the DDR CC
  //----------------------------------------

  // Enable broadcast mode DDR CCs
  HWIO_OUTX((DDR_PHY_SS_BASE + SEQ_DDR_SS_DDRSS_AHB2PHY_SWMAN_OFFSET),
             AHB2PHY_SWMAN_AHB2PHY_BROADCAST_EN_CFG_LOWER, 
             PC_CC_BROADCAST
           );

  /// Set the Link and Memory index pointers
  HWIO_OUTX(BROADCAST_BASE,DDR_CC_DDRCC_PCC_LL_CFG, 0x0); // LL_IDX
  HWIO_OUTX(BROADCAST_BASE,DDR_CC_DDRCC_PCC_MEM_CFG,0x0); // MEM_IDX

  /// Deassert the PCC request
  if (pc_mode == PHY_POWER_CLPS_RESTORE)
  {
    // SW_PC_PC_REQ
    HWIO_OUTX(BROADCAST_BASE, DDR_CC_DDRCC_PCC_PC_CFG,0x24029);
  }
  else  // SAVE
  {  // SW_PC_REQ 0x24025
    HWIO_OUTX(BROADCAST_BASE, DDR_CC_DDRCC_PCC_PC_CFG,0x24025);
  }
}

void DDR_PHY_hal_pcc_complete (DDR_STRUCT *ddr,
                               uint8  pc_mode,
                               uint32 clk_freq_khz
                              )
{
  // Enable broadcast mode CA and DQ PHYs
  HWIO_OUTX((DDR_PHY_SS_BASE + SEQ_DDR_SS_DDRSS_AHB2PHY_SWMAN_OFFSET),
             AHB2PHY_SWMAN_AHB2PHY_BROADCAST_EN_CFG_LOWER, 
             PC_PHY_CA_DQ_BROADCAST
           );

  if (pc_mode == PHY_POWER_CLPS_RESTORE)
  {
    /// Deassert the CPR sensor bypass  0x24069 // CPR_SENSOR_BYPASS
    HWIO_OUTX(BROADCAST_BASE, DDR_PHY_DDRPHY_PCC_PC_CFG, 0x24069);

    /// Deassert CSR chain bypass  PHY_CSR_CHAIN_BYPASS
    HWIO_OUTX(BROADCAST_BASE,DDR_PHY_DDRPHY_PCC_PC_CFG, 0x20069);
  
    /// Deassert the SW request enable  // SW_PC_REQ_EN
    HWIO_OUTX(BROADCAST_BASE,DDR_PHY_DDRPHY_PCC_PC_CFG, 0x20068);
  }
  else  // SAVE
  {
    /// Deassert CSR chain bypass  0x20065 PHY_CSR_CHAIN_BYPASS
    HWIO_OUTX(BROADCAST_BASE,DDR_PHY_DDRPHY_PCC_PC_CFG, 0x20065);

    /// Deassert the SW request enable  SW_PC_REQ_EN  0x20064
    HWIO_OUTX(BROADCAST_BASE,DDR_PHY_DDRPHY_PCC_PC_CFG, 0x20064);
  }

  //----------------------------------------
  // Repeat the sequence for the DDR CC
  //----------------------------------------
  // Enable broadcast mode DDR CCs
  HWIO_OUTX((DDR_PHY_SS_BASE + SEQ_DDR_SS_DDRSS_AHB2PHY_SWMAN_OFFSET),
             AHB2PHY_SWMAN_AHB2PHY_BROADCAST_EN_CFG_LOWER, 
             PC_CC_BROADCAST
           );

  if (pc_mode == PHY_POWER_CLPS_RESTORE)
  {
    /// Deassert CSR chain bypass  //PHY_CSR_CHAIN_BYPASS 0x20029
    HWIO_OUTX(BROADCAST_BASE, DDR_CC_DDRCC_PCC_PC_CFG, 0x20029);
  
    /// Deassert the SW request enable // SW_PC_REQ_EN
    HWIO_OUTX(BROADCAST_BASE, DDR_CC_DDRCC_PCC_PC_CFG, 0x20028);
  }
  else // SAVE
  {
    /// Deassert CSR chain bypass  0x20025  PHY_CSR_CHAIN_BYPASS
    HWIO_OUTX(BROADCAST_BASE, DDR_CC_DDRCC_PCC_PC_CFG, 0x20025);
  
    /// Deassert the SW request enable  SW_PC_REQ_EN  0x20024
    HWIO_OUTX(BROADCAST_BASE, DDR_CC_DDRCC_PCC_PC_CFG,  0x20024);
  }

} // End of ddr_phy_hal_pcc_complete 


