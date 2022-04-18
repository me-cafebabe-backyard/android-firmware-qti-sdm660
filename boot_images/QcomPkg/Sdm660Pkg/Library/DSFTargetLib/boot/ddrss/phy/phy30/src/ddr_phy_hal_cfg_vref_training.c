//===========================================================================
//  Copyright (c) 2015 QUALCOMM Technologies Incorporated.  All Rights Reserved.  
//  QUALCOMM Proprietary and Confidential. 
//===========================================================================
////////////////////////////////////////////////////////////////////////////////////////////////

#include "ddr_phy.h"
#include "ddrss.h"

void DDR_PHY_hal_cfg_local_vref( uint32 _inst_, uint32 local_vref_trim, uint16 local_vref_rank_select, uint32 local_vref_slice_select )
{

           switch (local_vref_rank_select) {
             case 1 :    if(local_vref_slice_select < 2 ) 
                          HWIO_OUTXF (_inst_+(8*local_vref_slice_select), DDR_PHY_DDRPHY_CMSLICE0_DQ_LOCAL_VREF_CFG, VREF_TRIM_R1, local_vref_trim); 
                          else 
                          HWIO_OUTXF (_inst_+((8*local_vref_slice_select)+4), DDR_PHY_DDRPHY_CMSLICE0_DQ_LOCAL_VREF_CFG, VREF_TRIM_R1, local_vref_trim); 
                          break;
               
             case 0 :   if(local_vref_slice_select < 2 ) 
                        HWIO_OUTXF (_inst_+(8*local_vref_slice_select), DDR_PHY_DDRPHY_CMSLICE0_DQ_LOCAL_VREF_CFG, VREF_TRIM_R0, local_vref_trim);
                        else
                        HWIO_OUTXF (_inst_+((8*local_vref_slice_select)+4), DDR_PHY_DDRPHY_CMSLICE0_DQ_LOCAL_VREF_CFG, VREF_TRIM_R0, local_vref_trim);
                        break;
            }
}

void DDR_PHY_hal_cfg_global_vref( uint32 _inst_, uint32 vref_val, uint32 clk_freq_khz, uint8 cs)
{

    //if (clk_freq_khz <= F_RANGE_3)
    if (clk_freq_khz <= HIGHEST_MPVREF_PRFS_FREQ)
    {
      if (cs == 0) {
        HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_PAD_VREF_CFG, VREF_PAD_RFU_R0, vref_val);
      }
      else {
        HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_PAD_VREF_CFG, VREF_PAD_RFU_R1, vref_val);
      }
    }
    else 
    {
        HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_PAD_VREF_CFG, VREF_TRIM, vref_val);
    }
    
}
void DDR_PHY_hal_cfg_ca_vref_dq_exit( uint32 _inst_ )
{
    HWIO_OUTX   ( _inst_ , DDR_PHY_DDRPHY_CMIO_PAD_IE_CFG    , 0 );
    HWIO_OUTX   ( _inst_ , DDR_PHY_DDRPHY_CMIO_PAD_OE_CFG    , 0 );
    HWIO_OUTXF  ( _inst_ , DDR_PHY_DDRPHY_FPM_CNTRL_CFG      , FPM_BYPASS        , 0x1);
    HWIO_OUTXF  ( _inst_ , DDR_PHY_DDRPHY_CMHUB_TOP_0_CFG    , CA_TRAINING_MODE  , 0x0);
    HWIO_OUTXF  ( _inst_ , DDR_PHY_DDRPHY_FPM_CNTRL_CFG      , FPM_BYPASS        , 0x0);
    HWIO_OUTX   ( _inst_ , DDR_PHY_DDRPHY_CMIO_PAD_MODE_CFG  , 0 );
	// Enable DQS weak pulls
	HWIO_OUTXF  (_inst_,DDR_PHY_DDRPHY_PAD_CNTL_0_CFG    , PULL_N_DQS           , 3     );
    HWIO_OUTXF  (_inst_,DDR_PHY_DDRPHY_PAD_CNTL_0_CFG    , PULL_DQS             , 1     );
}               


void DDR_PHY_hal_cfg_ca_vref_dq_out_entry( uint32 _inst_ )
{
    uint32 tmp;
    
    ///  program Software OE enable s to DQ and DQS pads of DQ0 instance
    tmp = HWIO_INX (_inst_, DDR_PHY_DDRPHY_CMIO_PAD_MODE_CFG );
    tmp = (tmp & ~(HWIO_DDR_PHY_DDRPHY_CMIO_PAD_MODE_CFG_SW_PAD_MODE_DQS_BMSK)) | ((0x1u) << HWIO_DDR_PHY_DDRPHY_CMIO_PAD_MODE_CFG_SW_PAD_MODE_DQS_SHFT ) ;
    tmp = (tmp & ~(HWIO_DDR_PHY_DDRPHY_CMIO_PAD_MODE_CFG_SW_PAD_MODE_DQ_BMSK )) | ((0x3FFu) << HWIO_DDR_PHY_DDRPHY_CMIO_PAD_MODE_CFG_SW_PAD_MODE_DQ_SHFT ) ;
    HWIO_OUTX (_inst_, DDR_PHY_DDRPHY_CMIO_PAD_MODE_CFG, tmp );
    ///  SW Override for the DQ PAD mode
    tmp = HWIO_INX (_inst_, DDR_PHY_DDRPHY_CMIO_PAD_OE_CFG );
    tmp = (tmp & ~(HWIO_DDR_PHY_DDRPHY_CMIO_PAD_OE_CFG_SW_PAD_ENABLE_OE_DQS_BMSK)) | ((0x1u) << HWIO_DDR_PHY_DDRPHY_CMIO_PAD_OE_CFG_SW_PAD_ENABLE_OE_DQS_SHFT ) ;
    tmp = (tmp & ~(HWIO_DDR_PHY_DDRPHY_CMIO_PAD_OE_CFG_SW_PAD_ENABLE_OE_DQ_BMSK )) | ((0x3FFu) << HWIO_DDR_PHY_DDRPHY_CMIO_PAD_OE_CFG_SW_PAD_ENABLE_OE_DQ_SHFT ) ;
    HWIO_OUTX (_inst_, DDR_PHY_DDRPHY_CMIO_PAD_OE_CFG, tmp );
    ///  SW Override for the DQ PAD OE
    ///  set DQS/DQSN floating during CA VREF

    HWIO_OUTXF  (_inst_,DDR_PHY_DDRPHY_PAD_CNTL_0_CFG    , PULL_N_DQS           , 0     );
    HWIO_OUTXF  (_inst_,DDR_PHY_DDRPHY_PAD_CNTL_0_CFG    , PULL_DQS             , 0     );
    HWIO_OUTXF  (_inst_,DDR_PHY_DDRPHY_PAD_CNTL_0_CFG    , PULL                 , 0     );
    
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_FPM_CNTRL_CFG, FPM_BYPASS, 0x1);
    ///  disable FPM to keep the above settings for IO pads
    ///  set the following CSR to disable ODT
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_PAD_DQ_0_CFG, ODT_EN, 0x0);
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_PAD_DQS_0_CFG, ODT_EN, 0x0);
    ///  enable FPM for frequency switch in the future steps
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_FPM_CNTRL_CFG, FPM_BYPASS, 0x0);
    ///  enable FPM
}

void DDR_PHY_hal_cfg_ca_vref_dq_in_entry( uint32 _inst_ )
{
 //   uint32 tmp;

    ///  program Software IE enables of DQ and DQs pads of DQ1 instance 
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_CMIO_PAD_MODE_CFG , SW_PAD_MODE_DQS      , 0x1   );
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_CMIO_PAD_MODE_CFG , SW_PAD_MODE_DQ       , 0x3ff );
    ///  SW Override for the DQ PAD mode
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_CMIO_PAD_IE_CFG   , SW_PAD_ENABLE_IE_DQS , 0x1   );
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_CMIO_PAD_IE_CFG   , SW_PAD_ENABLE_IE_DQ  , 0x3FF );
    ///  SW Override for the DQ PAD IE
    ///  set DQS/DQSN floating during CA VREF
 //   HWIO_OUTXF  (_inst_,DDR_PHY_DDRPHY_CMIO_PAD_IE_CFG   , SW_PAD_MODE_IE_DQS   , 0x1   );
 //   HWIO_OUTXF  (_inst_,DDR_PHY_DDRPHY_CMIO_PAD_IE_CFG   , SW_PAD_MODE_IE_DQ    , 0x3FF );//10 bit ONE

    HWIO_OUTXF  (_inst_,DDR_PHY_DDRPHY_PAD_CNTL_0_CFG    , PULL_N_DQS           , 0     );
    HWIO_OUTXF  (_inst_,DDR_PHY_DDRPHY_PAD_CNTL_0_CFG    , PULL_DQS             , 0     );
    HWIO_OUTXF  (_inst_,DDR_PHY_DDRPHY_PAD_CNTL_0_CFG    , PULL                 , 0     );


    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_FPM_CNTRL_CFG, FPM_BYPASS, 0x1);
    ///  disable FPM to keep the above settings for IO pads
    ///  also DQ1 should be in CA_TRAINING_MODE
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_CMHUB_TOP_0_CFG, CA_TRAINING_MODE, 0x1);
    ///  put DQ1 in CA_TRAINING_MODE
    ///  set the following CSR to disable ODT
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_PAD_DQ_0_CFG, ODT_EN, 0x0);
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_PAD_DQS_0_CFG, ODT_EN, 0x0);
    ///  enable FPM for frequency switch in the future steps
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_FPM_CNTRL_CFG, FPM_BYPASS, 0x0);
    ///  enable FPM
}

void DDR_PHY_hal_cfg_ca_vref_dq_in_exit( uint32 _inst_ )
{
 
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_CMIO_PAD_OE_CFG  , SW_PAD_ENABLE_OE_DQ , 0x3FF);
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_CMIO_PAD_OE_CFG  , SW_PAD_ENABLE_OE_DQS,  0x01);

    ///  SW Override for the DQ PAD mode
    HWIO_OUTX (_inst_, DDR_PHY_DDRPHY_CMIO_PAD_IE_CFG  , 0 );

    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_FPM_CNTRL_CFG      , FPM_BYPASS      , 0x1);
    ///  disable FPM to keep the above settings for IO pads
    ///  also DQ1 should be in CA_TRAINING_MODE
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_CMHUB_TOP_0_CFG    , CA_TRAINING_MODE, 0  );
    ///  put DQ1 in CA_TRAINING_MODE
    ///  set the following CSR to disable ODT

    ///  enable FPM for frequency switch in the future steps
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_FPM_CNTRL_CFG      , FPM_BYPASS      , 0x0);
    ///  enable FPM                    
     ///  program Software IE enables of DQ and DQs pads of DQ1 instance 
    HWIO_OUTX (_inst_, DDR_PHY_DDRPHY_CMIO_PAD_MODE_CFG ,  0 );

}

// ***********************************************************************
/// DDRPHY BISC STA READ
/// seq_msg(INFO, 0, "DDRPHY CA VREF STA READ");
/// -----------------------------------------------------------------
///     HALs for BISC STA READ
/// -----------------------------------------------------------------
// ***********************************************************************
uint32 DDR_PHY_hal_sta_ca_vref( uint32 _inst_ )
{

    ///  only the lower 6 bits are feedback data from DRAM for CA training
    ///  but due to bit remapping, all 10 bits need to be saved. Then the
    ///  correct remap needs to take place before the comparison can happen.
  return ((HWIO_INXF (_inst_, DDR_PHY_DDRPHY_BISC_TRAINING_STA, TRAINING_STATUS) & 0x3FF));
 
}


// ***********************************************************************
///  the following hal sets the CDC delay values in the write datapath for the maximum corner of DQS2DQ training.
// ***********************************************************************
void DDR_PHY_hal_cfg_dq_vref_dqs2dq_max( uint32 _inst_, uint8 rank, uint8 prfs_num, uint8 delay, uint8 coarse_dly )
{
    uint32 ctl = 0;
    
    
    ///  <19:15> HP fine delay rank1 <14:10> HP coarse delay rank1 <9:5> HP fine delay rank0 <4:0> HP coarse delay rank0
    ///  read DQS2DQ delay information out from the corresponding CFG register
    switch(prfs_num){
        case 0 :
            ///  load ctl with DQS2DQ_0_MAC_CFG
          //ctl = HWIO_INX (_inst_, DDR_PHY_DDRPHY_BISC_DQS2DQ_0_MAX_CFG );
            break;
        case 1 :
            ///  load ctl with DQS2DQ_1_MAC_CFG
          //ctl = HWIO_INX (_inst_, DDR_PHY_DDRPHY_BISC_DQS2DQ_1_MAX_CFG );
            break;
        case 2 :
            ///  load ctl with DQS2DQ_2_MAC_CFG
          //ctl = HWIO_INX (_inst_, DDR_PHY_DDRPHY_BISC_DQS2DQ_2_MAX_CFG );
            break;
        case 3 :
            ///  load ctl with DQS2DQ_3_MAC_CFG
          //ctl = HWIO_INX (_inst_, DDR_PHY_DDRPHY_BISC_DQS2DQ_3_MAX_CFG );
            break;
        case 4 :
            ///  load ctl with DQS2DQ_4_MAC_CFG
          //ctl = HWIO_INX (_inst_, DDR_PHY_DDRPHY_BISC_DQS2DQ_4_MAX_CFG );
            break;
        default :
            ///  load ctl with DQS2DQ_5_MAC_CFG
          //ctl = HWIO_INX (_inst_, DDR_PHY_DDRPHY_BISC_DQS2DQ_5_MAX_CFG );
            break;
    }
    ///  modify the corresponding delay, based on rank, and coarse/fine delay
    if (rank) {
        ///  rank 1
        if (coarse_dly) {
            ///  coarse delay
            ctl = ctl & 0xFFFF83FF;
            ///  mask out bits 14:10
            ctl = ctl | (delay << 10);
        } else {
            ///  fine delay
            ctl = ctl & 0xFFF07FFF;
            ///  mask out bits 19:15
            ctl = ctl | (delay << 15);
        }
    } else {
        ///  rank 0
        if (coarse_dly) {
            ///  coarse delay
            ctl = ctl & 0xFFFFFFE0;
            ///  mask out bits 4:0
            ctl = ctl | (delay);
        } else {
            ///  fine delay
            ctl = ctl & 0xFFFFFC1F;
            ///  mask out bits 9:5
            ctl = ctl | (delay << 5);
        }
    }
    ///  write the modified delay value back
    switch(prfs_num){
        case 0 :
          //HWIO_OUTX (_inst_, DDR_PHY_DDRPHY_BISC_DQS2DQ_0_MAX_CFG, ctl);
            break;
        case 1 :
          //HWIO_OUTX (_inst_, DDR_PHY_DDRPHY_BISC_DQS2DQ_1_MAX_CFG, ctl);
            break;
        case 2 :
          //HWIO_OUTX (_inst_, DDR_PHY_DDRPHY_BISC_DQS2DQ_2_MAX_CFG, ctl);
            break;
        case 3 :
          //HWIO_OUTX (_inst_, DDR_PHY_DDRPHY_BISC_DQS2DQ_3_MAX_CFG, ctl);
            break;
        case 4 :
          //HWIO_OUTX (_inst_, DDR_PHY_DDRPHY_BISC_DQS2DQ_4_MAX_CFG, ctl);
            break;
        default :
          //HWIO_OUTX (_inst_, DDR_PHY_DDRPHY_BISC_DQS2DQ_5_MAX_CFG, ctl);
            break;
    }
}


// ***********************************************************************
///  the following hal sets the CDC delay values in the write datapath for the minimum corner of DQS2DQ training.
// ***********************************************************************
void DDR_PHY_hal_cfg_dq_vref_dqs2dq_min( uint32 _inst_, uint8 rank, uint8 prfs_num, uint8 delay, uint8 coarse_dly )
{
  uint32 ctl = 0;

    ///  <19:15> HP fine delay rank1 <14:10> HP coarse delay rank1 <9:5> HP fine delay rank0 <4:0> HP coarse delay rank0
    ///  read DQS2DQ delay information out from the corresponding CFG register
    switch(prfs_num){
        case 0 :
          //ctl = HWIO_INX (_inst_, DDR_PHY_DDRPHY_BISC_DQS2DQ_0_MIN_CFG );
            break;
        case 1 :
          //ctl = HWIO_INX (_inst_, DDR_PHY_DDRPHY_BISC_DQS2DQ_1_MIN_CFG );
            break;
        case 2 :
          //ctl = HWIO_INX (_inst_, DDR_PHY_DDRPHY_BISC_DQS2DQ_2_MIN_CFG );
            break;
        case 3 :
          //ctl = HWIO_INX (_inst_, DDR_PHY_DDRPHY_BISC_DQS2DQ_3_MIN_CFG );
            break;
        case 4 :
          //ctl = HWIO_INX (_inst_, DDR_PHY_DDRPHY_BISC_DQS2DQ_4_MIN_CFG );
            break;
        default :
          //ctl = HWIO_INX (_inst_, DDR_PHY_DDRPHY_BISC_DQS2DQ_5_MIN_CFG );
            break;
    }
    ///  modify the corresponding delay, based on rank, and coarse/fine delay
    if (rank) {
        ///  rank 1
        if (coarse_dly) {
            ///  coarse delay
            ctl = ctl & 0xFFFF83FF;
            ///  mask out bits 14:10
            ctl = ctl | (delay << 10);
        } else {
            ///  fine delay
            ctl = ctl & 0xFFF07FFF;
            ///  mask out bits 19:15
            ctl = ctl | (delay << 15);
        }
    } else {
        ///  rank 0
        if (coarse_dly) {
            ///  coarse delay
            ctl = ctl & 0xFFFFFFE0;
            ///  mask out bits 4:0
            ctl = ctl | (delay);
        } else {
            ///  fine delay
            ctl = ctl & 0xFFFFFC1F;
            ///  mask out bits 9:5
            ctl = ctl | (delay << 5);
        }
    }
    ///  write the modified delay value back
    switch(prfs_num){
        case 0 :
          //HWIO_OUTX (_inst_, DDR_PHY_DDRPHY_BISC_DQS2DQ_0_MIN_CFG, ctl);
            break;
        case 1 :
          //HWIO_OUTX (_inst_, DDR_PHY_DDRPHY_BISC_DQS2DQ_1_MIN_CFG, ctl);
            break;
        case 2 :
          //HWIO_OUTX (_inst_, DDR_PHY_DDRPHY_BISC_DQS2DQ_2_MIN_CFG, ctl);
            break;
        case 3 :
          //HWIO_OUTX (_inst_, DDR_PHY_DDRPHY_BISC_DQS2DQ_3_MIN_CFG, ctl);
            break;
        case 4 :
          //HWIO_OUTX (_inst_, DDR_PHY_DDRPHY_BISC_DQS2DQ_4_MIN_CFG, ctl);
            break;
        default :
          //HWIO_OUTX (_inst_, DDR_PHY_DDRPHY_BISC_DQS2DQ_5_MIN_CFG, ctl);
            break;
    }
}

void DDR_PHY_hal_cfg_ca_vref_dq_retmr( uint32 _inst_, uint8 rank, uint32 dq_retmr )
{

    if (rank) {
        ///  rank 1
        HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_CMHUB_TOP_1_CFG, DQ_RETMR_R1, dq_retmr);
    } else {
        ///  rank 0
        HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_CMHUB_TOP_1_CFG, DQ_RETMR_R0, dq_retmr);
    }
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_CMHUB_TOP_0_CFG, TRIG_WRLVL_LATCH, 0x1);
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_CMHUB_TOP_0_CFG, TRIG_WRLVL_LATCH, 0x0);
}



