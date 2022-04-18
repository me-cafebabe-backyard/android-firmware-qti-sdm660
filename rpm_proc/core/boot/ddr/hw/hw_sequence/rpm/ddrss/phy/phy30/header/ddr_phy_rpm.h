////////////////////////////////////////////////////////////////////////////////////////////////
//===========================================================================
//  Copyright (c) 2016 QUALCOMM Technologies Incorporated.  All Rights Reserved.  
//  QUALCOMM Proprietary and Confidential. 
//===========================================================================
////////////////////////////////////////////////////////////////////////////////////////////////
#include "HAL_SNS_DDR.h"
#include "ddr_ss_seq_hwiobase.h"
#include "ddr_ss_seq_hwioreg.h"


//===========================================================================
void DDR_PHY_hal_cfg_sw_iocal( uint32 _inst_);
void DDR_PHY_hal_cfg_sw_handshake_start(DDR_STRUCT *ddr, uint32 _inst_ );
void DDR_PHY_hal_cfg_sw_handshake_stop(DDR_STRUCT *ddr, uint32 _inst_ );
void DDR_PHY_hal_cfg_sw_handshake_complete( uint32 _inst_ );
void DDR_PHY_hal_hpcdc_enable( uint8 enable);


/***************************************************************************************************
 DDR PHY PCC
 ***************************************************************************************************/
void DDR_PHY_rtn_pcc_pre_collapse (DDR_STRUCT *ddr, uint8 pcc_mode, uint32 clk_freq_khz);
void DDR_PHY_rtn_pcc_post_collapse (DDR_STRUCT *ddr, uint8 pcc_mode, uint32 clk_freq_khz);

void DDR_PHY_hal_pcc_start (DDR_STRUCT *ddr, uint8 pcc_mode);
void DDR_PHY_hal_pcc_stop (DDR_STRUCT *ddr, uint8 pcc_mode);
void DDR_PHY_hal_pcc_complete (DDR_STRUCT *ddr, uint8 pcc_mode, uint32 clk_freq_khz);

