/****************************************************************************
 QUALCOMM Proprietary Design Data
 Copyright (c) 2015, Qualcomm Technologies Incorporated. All rights reserved.
 ****************************************************************************/
/*==============================================================================
                                EDIT HISTORY

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/DSFTargetLib/rpm/ddrss/src/ddrss_common_rpm.c#4 $
$DateTime: 2016/10/12 00:05:04 $
$Author: pwbldsvc $
================================================================================
when       who          what, where, why
--------   ---          --------------------------------------------------------
05/11/14   arindamm     First edit history header. Add new entries at top.
================================================================================*/

#include "ddrss_rpm.h"
#include "target_config_rpm.h"


void DDRSS_ddr_phy_sw_freq_switch (DDR_STRUCT *ddr, uint8 ch)
{

    uint32   reg_offset_ddr_phy = 0;
    uint32   reg_offset_dpe     = 0;
    uint8 sw_handshake_complete = 1;

    // Base pointer to BIMC
    reg_offset_dpe   = REG_OFFSET_DPE(ch);

    // Configure the DDR PHY address offset
    reg_offset_ddr_phy = REG_OFFSET_DDR_PHY_CH(ch);

    // Turn on continuous GCC clock per channel 
    HWIO_OUTXF2 (reg_offset_dpe, DPE_CONFIG_6, IOSTAGE_WR_DEBUG_MODE, IOSTAGE_CA_DEBUG_MODE, 0x1, 0x1);
    HWIO_OUTXF (reg_offset_dpe, DPE_CONFIG_4, LOAD_ALL_CONFIG, 0x1);
	
    // Enable broadcast mode for 4 DQ PHYs and 2 CA PHYs
    HWIO_OUTX((DDR_PHY_SS_BASE + SEQ_DDR_SS_DDRSS_AHB2PHY_SWMAN_OFFSET), AHB2PHY_SWMAN_AHB2PHY_BROADCAST_EN_CFG_LOWER, 0x3F << (ch * 7));

    /// set FPM_INIT_START to 1 to start frequency switch
    DDR_PHY_hal_cfg_sw_handshake_start (ddr, BROADCAST_BASE);

    /// Poll for DDRPHY_FPM_TOP_STA[FPM_SW_INIT_COMP]
    while (sw_handshake_complete == 0x1) {
      sw_handshake_complete = ((0x00000001 & ((HWIO_INX (reg_offset_ddr_phy + CA0_DDR_PHY_OFFSET, DDR_PHY_DDRPHY_FPM_TOP_STA))>>1)) |
                               (0x00000001 & ((HWIO_INX (reg_offset_ddr_phy + DQ0_DDR_PHY_OFFSET, DDR_PHY_DDRPHY_FPM_TOP_STA))>>1)) |
                               (0x00000001 & ((HWIO_INX (reg_offset_ddr_phy + DQ1_DDR_PHY_OFFSET, DDR_PHY_DDRPHY_FPM_TOP_STA))>>1)));// |
    }

    /// set FPM_INIT_START to 0 to stop frequency switch
    DDR_PHY_hal_cfg_sw_handshake_stop (ddr, BROADCAST_BASE);

    // Poll for handshake complete
    while (sw_handshake_complete == 0x0) {
      sw_handshake_complete = ((0x00000001 & ((HWIO_INX (reg_offset_ddr_phy + CA0_DDR_PHY_OFFSET, DDR_PHY_DDRPHY_FPM_TOP_STA))>>1)) &
                               (0x00000001 & ((HWIO_INX (reg_offset_ddr_phy + DQ0_DDR_PHY_OFFSET, DDR_PHY_DDRPHY_FPM_TOP_STA))>>1)) &
                               (0x00000001 & ((HWIO_INX (reg_offset_ddr_phy + DQ1_DDR_PHY_OFFSET, DDR_PHY_DDRPHY_FPM_TOP_STA))>>1)));// &
    }

    /// disable software trigger handshake, and enable hardware FPM
    DDR_PHY_hal_cfg_sw_handshake_complete (BROADCAST_BASE);

    // Disable broadcast mode
    HWIO_OUTX((DDR_PHY_SS_BASE + SEQ_DDR_SS_DDRSS_AHB2PHY_SWMAN_OFFSET), AHB2PHY_SWMAN_AHB2PHY_BROADCAST_EN_CFG_LOWER, 0x0);
}

void DDRSS_ddr_phy_sw_freq_switch_PC (DDR_STRUCT *ddr)
{
    uint32   reg_offset_ddr_phy0 = 0;
    uint32   reg_offset_ddr_phy1 = 0;
    uint32   reg_offset_dpe0     = 0;
    uint32   reg_offset_dpe1     = 0;
    uint8 sw_handshake_complete  = 1;

    // Base pointer to BIMC
    reg_offset_dpe0   = REG_OFFSET_DPE(0);
    reg_offset_dpe1   = REG_OFFSET_DPE(1);

    // Configure the DDR PHY address offset
    reg_offset_ddr_phy0 = REG_OFFSET_DDR_PHY_CH(0);
    reg_offset_ddr_phy1 = REG_OFFSET_DDR_PHY_CH(1);

    // Turn on continuous GCC clock per channel 
    HWIO_OUTXF2(reg_offset_dpe0, DPE_CONFIG_6, IOSTAGE_WR_DEBUG_MODE, IOSTAGE_CA_DEBUG_MODE, 0x1, 0x1);
    HWIO_OUTXF (reg_offset_dpe0, DPE_CONFIG_4, LOAD_ALL_CONFIG, 0x1);
    HWIO_OUTXF2(reg_offset_dpe1, DPE_CONFIG_6, IOSTAGE_WR_DEBUG_MODE, IOSTAGE_CA_DEBUG_MODE, 0x1, 0x1);
    HWIO_OUTXF (reg_offset_dpe1, DPE_CONFIG_4, LOAD_ALL_CONFIG, 0x1);

    // Enable broadcast mode for 4 DQ PHYs and 2 CA PHYs
    HWIO_OUTX((DDR_PHY_SS_BASE + SEQ_DDR_SS_DDRSS_AHB2PHY_SWMAN_OFFSET),
               AHB2PHY_SWMAN_AHB2PHY_BROADCAST_EN_CFG_LOWER, 
               PC_PHY_CA_DQ_BROADCAST
             );

    /// set FPM_INIT_START to 1 to start frequency switch
    DDR_PHY_hal_cfg_sw_handshake_start (ddr, BROADCAST_BASE);

    /// Poll for DDRPHY_FPM_TOP_STA[FPM_SW_INIT_COMP]
    while (sw_handshake_complete == 0x1) 
    {
      sw_handshake_complete = ((0x00000001 & ((HWIO_INX (reg_offset_ddr_phy0 + CA0_DDR_PHY_OFFSET, DDR_PHY_DDRPHY_FPM_TOP_STA))>>1)) |
                               (0x00000001 & ((HWIO_INX (reg_offset_ddr_phy0 + DQ0_DDR_PHY_OFFSET, DDR_PHY_DDRPHY_FPM_TOP_STA))>>1)) |
                               (0x00000001 & ((HWIO_INX (reg_offset_ddr_phy0 + DQ1_DDR_PHY_OFFSET, DDR_PHY_DDRPHY_FPM_TOP_STA))>>1)) |

                               (0x00000001 & ((HWIO_INX (reg_offset_ddr_phy1 + CA0_DDR_PHY_OFFSET, DDR_PHY_DDRPHY_FPM_TOP_STA))>>1)) |
                               (0x00000001 & ((HWIO_INX (reg_offset_ddr_phy1 + DQ0_DDR_PHY_OFFSET, DDR_PHY_DDRPHY_FPM_TOP_STA))>>1)) |
                               (0x00000001 & ((HWIO_INX (reg_offset_ddr_phy1 + DQ1_DDR_PHY_OFFSET, DDR_PHY_DDRPHY_FPM_TOP_STA))>>1)));// |
    }

    /// set FPM_INIT_START to 0 to stop frequency switch
    DDR_PHY_hal_cfg_sw_handshake_stop (ddr, BROADCAST_BASE);

    // Poll for handshake complete
    while (sw_handshake_complete == 0x0) 
    {
      sw_handshake_complete = ((0x00000001 & ((HWIO_INX (reg_offset_ddr_phy0 + CA0_DDR_PHY_OFFSET, DDR_PHY_DDRPHY_FPM_TOP_STA))>>1)) &
                               (0x00000001 & ((HWIO_INX (reg_offset_ddr_phy0 + DQ0_DDR_PHY_OFFSET, DDR_PHY_DDRPHY_FPM_TOP_STA))>>1)) &
                               (0x00000001 & ((HWIO_INX (reg_offset_ddr_phy0 + DQ1_DDR_PHY_OFFSET, DDR_PHY_DDRPHY_FPM_TOP_STA))>>1)) &

                               (0x00000001 & ((HWIO_INX (reg_offset_ddr_phy1 + CA0_DDR_PHY_OFFSET, DDR_PHY_DDRPHY_FPM_TOP_STA))>>1)) &
                               (0x00000001 & ((HWIO_INX (reg_offset_ddr_phy1 + DQ0_DDR_PHY_OFFSET, DDR_PHY_DDRPHY_FPM_TOP_STA))>>1)) &
                               (0x00000001 & ((HWIO_INX (reg_offset_ddr_phy1 + DQ1_DDR_PHY_OFFSET, DDR_PHY_DDRPHY_FPM_TOP_STA))>>1)));// &
    }

    /// disable software trigger handshake, and enable hardware FPM
    DDR_PHY_hal_cfg_sw_handshake_complete (BROADCAST_BASE);
    
}



