//===========================================================================
//  Copyright (c) 2015 QUALCOMM Technologies Incorporated.  All Rights Reserved.  
//  QUALCOMM Proprietary and Confidential. 
//===========================================================================
////////////////////////////////////////////////////////////////////////////////////////////////

#include "ddr_phy.h"
#include "target_config.h"
#include "ddrss_rpm.h"

// ***********************************************************************
/// Calculate CDC mask
// ***********************************************************************
uint32 DDR_PHY_hal_cfg_cdc_mask( uint16 coarse_fine, uint8 rank, uint16 hp_mode )
{
    uint32 mask = 0;

    if (rank == 0) {
        if (hp_mode == 1) {
            if (coarse_fine == 1) { //[4:0]
                mask = 0xFFFFFFE0; 
            }
            else { // fine delay [9:5]
                mask  = 0xFFFFFC1F; 
            }
        }
        else {
            mask = 0xFE0FFFFF; // lpcdc [24:20]
        }
    }
    else {
        if (hp_mode == 1) {
            if (coarse_fine == 1) { // [14:10]
                mask  = 0xFFFF83FF; 
            } 
            else { // Fine delay [19:15]
                mask  = 0xFFF07FFF; 
            }
        }
        else {
            mask = 0xC1FFFFFF; // lpcdc [29:25]
        }
    }    

    return mask;

} 

// ***********************************************************************
/// Calculate CDC shift
// ***********************************************************************

uint32 DDR_PHY_hal_cfg_cdc_shift( uint16 coarse_fine, uint8 rank, uint16 hp_mode )
{
    uint32 shift = 0;

    if (rank == 0) {
        if (hp_mode == 1) {
            if (coarse_fine == 1) { //[4:0]
                shift = 0;
            }
            else { // fine delay [9:5]
                shift  = 5; 
            }
        }
        else {
            shift = 20;
        }
    }
    else {
        if (hp_mode == 1) {    
            if (coarse_fine == 1) { // [14:10]
                shift  = 10; 
            } 
            else { // Fine delay [19:15]
                shift  = 15; 
            }
        }
        else {
            shift = 25;
        }
    }

    return shift;
}

void DDR_PHY_hal_cfg_wrlvl_half( uint32 _inst_, uint32 rank, uint32 dq_half_cycle )
{

  if (rank == 1) {
      HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_CMHUB_TOP_1_CFG, DQ_HALF_CYCLE_R1, dq_half_cycle);
  } else {
      HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_CMHUB_TOP_1_CFG, DQ_HALF_CYCLE_R0, dq_half_cycle);
  }
  HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_CMHUB_TOP_0_CFG, TRIG_WRLVL_LATCH, 0x1);
  HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_CMHUB_TOP_0_CFG, TRIG_WRLVL_LATCH, 0x0);

}

void DDR_PHY_hal_cfg_wrlvl_retmr( uint32 _inst_, uint32 rank, uint32 dqs_retmr )
{

    if (rank == 1) {
        HWIO_OUTXF2 (_inst_, DDR_PHY_DDRPHY_CMHUB_TOP_1_CFG, DQS_RETMR_R1, DQ_RETMR_R1, dqs_retmr, dqs_retmr);
    } else {
        HWIO_OUTXF2 (_inst_, DDR_PHY_DDRPHY_CMHUB_TOP_1_CFG, DQS_RETMR_R0, DQ_RETMR_R0, dqs_retmr, dqs_retmr);
    }
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_CMHUB_TOP_0_CFG, TRIG_WRLVL_LATCH, 0x1);
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_CMHUB_TOP_0_CFG, TRIG_WRLVL_LATCH, 0x0);   
}


void DDR_PHY_hal_cfg_cdcext_wrlvl_update( uint32 _inst_, uint8 period_index, uint8 rank, uint32 fine_delay, uint32 coarse_delay )
{
    uint32 ctl;

    ///  read corresponding extension wrlvl delay value out
     ctl = HWIO_INX (_inst_+(4*period_index), DDR_PHY_DDRPHY_CDCEXT_WRLVL_0_CTL_CFG);
  if (rank) {
        ctl = ctl & 0xFFFF83FF;
        coarse_delay = coarse_delay << 10;
        ctl = ctl | coarse_delay;
        ctl = ctl & 0xFFF07FFF;
        fine_delay = fine_delay << 15;
        ctl = ctl | fine_delay;
    } else {
        ctl = ctl & 0xFFFFFFE0;
        ctl = ctl | coarse_delay;
        fine_delay = fine_delay << 5;
        ctl = ctl & 0xFFFFFC1F;
        ctl = ctl | fine_delay;
    }
    ///  write wrlvl delay value back to the corresponding cdc extension cfg
       HWIO_OUTX (_inst_+(period_index*4), DDR_PHY_DDRPHY_CDCEXT_WRLVL_0_CTL_CFG, ctl);
}


// ***********************************************************************
/// ----------------------------------------------------------
///  HAL           : RCW
///  status        : 1: enable rcw training, 0: disable
/// ----------------------------------------------------------
// ***********************************************************************
void DDR_PHY_rd_mon_status( uint32 _inst_, uint8 pass[1] )
{
    uint32 tmp;


    tmp = HWIO_INX (_inst_, DDR_PHY_DDRPHY_BISC_TRAINING_STA );
    pass[0] = (tmp >> 10) & 0x1;
}

// ***********************************************************************
/// ----------------------------------------------------------
///  Read valude of rcw coarse delay
/// ----------------------------------------------------------
// ***********************************************************************
uint8 DDR_PHY_hal_sta_rcw_fine( uint32 _inst_, uint8 rank )
{

    if (rank) {
        return (((HWIO_INX (_inst_, DDR_PHY_DDRPHY_CMCDCRCW_CTL_CFG ) & 0x7C00) >> 15));
    } else {
        return (((HWIO_INX (_inst_, DDR_PHY_DDRPHY_CMCDCRCW_CTL_CFG ) & 0x3E0) >> 5));
    }
}

// ***********************************************************************
/// ----------------------------------------------------------
///  Read value of rcw coarse delay
/// ----------------------------------------------------------
// ***********************************************************************
uint8 DDR_PHY_hal_sta_rcw_coarse( uint32 _inst_, uint8 rank )
{

    if (rank) {
        return (((HWIO_INX (_inst_, DDR_PHY_DDRPHY_CMCDCRCW_CTL_CFG ) & 0x7C00) >> 10));
    } else {
        return ((HWIO_INX (_inst_, DDR_PHY_DDRPHY_CMCDCRCW_CTL_CFG ) & 0x1F));
    }
}

// ***********************************************************************
/// ----------------------------------------------------------
///  Read value of number of half cycle
/// ----------------------------------------------------------
// ***********************************************************************

uint8 DDR_PHY_hal_sta_rcw_num_cycle( uint32 _inst_ )
{
    uint8 half;
    uint8 full;

    half = HWIO_INXF (_inst_, DDR_PHY_DDRPHY_CMHUB_TOP_2_CFG, RD_EN_IST_HALF_CYCLE_R0);
    full = HWIO_INXF (_inst_, DDR_PHY_DDRPHY_CMHUB_TOP_2_CFG, RD_EN_IST_FULL_CYCLE_R0);

    
    switch(half) {
       case 0  :  return (full<<1);   
       case 1  :  return ((full<<1) +1);
       default :  return(16);
      }           
}



// ***********************************************************************
/// ----------------------------------------------------------
///  HAL : CONFIG WRLV SLAVE
/// ----------------------------------------------------------
// ***********************************************************************
void DDR_PHY_hal_cfg_cdc_slave_wrlvl( uint32 _inst_, uint32 delay, uint16 coarse_delay, uint16 hp_mode, uint8 rank )
{
    uint32 cdc;
    uint32 mask;
    uint32 shift;

        // Read the CDC delay register
    cdc = HWIO_INX (_inst_, DDR_PHY_DDRPHY_CMCDCWRLVL_CTL_CFG);

        mask  = DDR_PHY_hal_cfg_cdc_mask(coarse_delay, rank, hp_mode);
        shift = DDR_PHY_hal_cfg_cdc_shift(coarse_delay, rank, hp_mode);

        // Clear space for delay in CDC
        cdc = cdc & mask;

        // Shift delay to insert in CDC
        delay = delay<<shift;

        // Insert delay into CDC
        cdc = cdc | delay;

        // Write CDC delay register 
    HWIO_OUTX (_inst_, DDR_PHY_DDRPHY_CMCDCWRLVL_CTL_CFG, cdc); 

    // Disable load 
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_CMCDCWRLVL_TOP_CFG, LOAD, 0);

        // Gate the clock
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_CMCDCWRLVL_TOP_CFG, GATE, 1);

        // Disable the register
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_CMCDCWRLVL_TOP_CFG, EN  , 0);

        // Pulse load
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_CMCDCWRLVL_TOP_CFG, LOAD, 1);
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_CMCDCWRLVL_TOP_CFG, LOAD, 0);

        // Enable the register
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_CMCDCWRLVL_TOP_CFG, EN  , 1);

        // Un-Gate the clock
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_CMCDCWRLVL_TOP_CFG, GATE, 0);
}


/// ----------------------------------------------------------
///  HAL : CONFIG WR SLAVE
/// ----------------------------------------------------------
// ***********************************************************************
void DDR_PHY_hal_cfg_cdc_slave_wr( uint32 _inst_, uint32 delay, uint16 coarse_delay, uint16 hp_mode, uint8 rank )
{
    uint32 cdc;
    uint32 mask;
    uint32 shift;
     
    // Read the CDC delay register
    cdc = HWIO_INX (_inst_, DDR_PHY_DDRPHY_CMCDCWR_CTL_CFG);

    mask  = DDR_PHY_hal_cfg_cdc_mask(coarse_delay, rank, hp_mode);
    shift = DDR_PHY_hal_cfg_cdc_shift(coarse_delay, rank, hp_mode);

    // Clear space for delay in CDC
    cdc = cdc & mask;

    // Shift delay to insert in CDC
    delay = delay<<shift;

    // Insert delay into CDC
    cdc = cdc | delay;

    // Write CDC delay register 
    HWIO_OUTX (_inst_, DDR_PHY_DDRPHY_CMCDCWR_CTL_CFG, cdc); 

    // Disable load 
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_CMCDCWR_TOP_CFG, LOAD, 0);
    
    // Gate the clock
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_CMCDCWR_TOP_CFG, GATE, 1);
    
    // Disable the register
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_CMCDCWR_TOP_CFG, EN  , 0);
    
    // Pulse load
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_CMCDCWR_TOP_CFG, LOAD, 1);
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_CMCDCWR_TOP_CFG, LOAD, 0);
    
    // Enable the register
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_CMCDCWR_TOP_CFG, EN  , 1);
    
    // Un-Gate the clock
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_CMCDCWR_TOP_CFG, GATE, 0);
    cdc = HWIO_INXF  (_inst_, DDR_PHY_DDRPHY_CMCDCWR_TOP_CFG, GATE);

}


// ***********************************************************************
/// ----------------------------------------------------------
///  HAL           : CONFIG RCW SLAVE
///  rank          : rank  0 - 1, select rank of ddr
///  delay         : delay value 0-31
///  coarse_delay  : 0: fine delay 1: coarse delay
///  hp_mode       : 0: lp mode, 1 : hp mode
/// ----------------------------------------------------------
// ***********************************************************************
void DDR_PHY_hal_cfg_cdc_slave_rcw( uint32 _inst_, uint32 delay, uint16 coarse_delay, uint16 hp_mode, uint8 rank )
{
    uint32 cdc;
    uint32 mask;
    uint32 shift;
    uint32 t_delay;

	
	//for (rank = 0 ; rank < NUM_CS; rank++)
	//{
	//	t_delay = 0;
        // Read the CDC delay register
        cdc = HWIO_INX (_inst_, DDR_PHY_DDRPHY_CMCDCRCW_CTL_CFG);

        mask  = DDR_PHY_hal_cfg_cdc_mask(coarse_delay, rank, hp_mode);
        shift = DDR_PHY_hal_cfg_cdc_shift(coarse_delay, rank, hp_mode);

        // Clear space for delay in CDC
        cdc = cdc & mask;

        // Shift delay to insert in CDC
        t_delay = delay<<shift;

        // Insert delay into CDC
        cdc = cdc | t_delay;

        // Write CDC delay register 
        HWIO_OUTX (_inst_, DDR_PHY_DDRPHY_CMCDCRCW_CTL_CFG, cdc); 

        // Disable load 
        // Gate the clock
        // Disable the register
        HWIO_OUTXF3 (_inst_, DDR_PHY_DDRPHY_CMCDCRCW_TOP_CFG, EN, LOAD, GATE, 0, 0, 1);

        // Pulse load
        HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_CMCDCRCW_TOP_CFG, LOAD, 1);
        HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_CMCDCRCW_TOP_CFG, LOAD, 0);

        // Enable the register
        // Un-Gate the clock
        HWIO_OUTXF2 (_inst_, DDR_PHY_DDRPHY_CMCDCRCW_TOP_CFG, GATE, EN, 0, 1);
   // }
}

// ***********************************************************************
/// ----------------------------------------------------------
///  HAL           : RCW
///  enable        : 1: enable rcw training, 0: disable
///  num_cycle     : 1: half cycle, 2: full cycle , 3: one and half cycle
/// ----------------------------------------------------------
// ***********************************************************************

void DDR_PHY_hal_cfg_cdc_rcw( uint32 _inst_, uint32 enable, uint32 num_cycle )
{
        HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_CMCDCRDT2_I0_TOP_CFG, RCW_TYPE_EN, enable);    
        HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_CMHUB_TOP_2_CFG, LPDDR4_MODE, enable);
        HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_CMHUB_TOP_0_CFG, RCW_TRAINING_EN, enable);
        HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_CMHUB_TOP_2_CFG, RCW_COARSE_CTL, 0x0);
        HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_CMHUB_TOP_0_CFG, TRIG_WRLVL_LATCH, 0x1);
        HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_CMHUB_TOP_0_CFG, TRIG_WRLVL_LATCH, 0x0); 
    switch(enable) {
     case 1  : {
       
        HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_CMHUB_TOP_2_CFG, RD_EN_IST_HALF_CYCLE_R0, (num_cycle&0x1));  //Gets the LSB 
        HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_CMHUB_TOP_2_CFG, RD_EN_IST_FULL_CYCLE_R0, (num_cycle>>0x1)); 
        HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_CMHUB_TOP_0_CFG, TRIG_WRLVL_LATCH, 0x1);
        HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_CMHUB_TOP_0_CFG, TRIG_WRLVL_LATCH, 0x0); 
        break; 
    }
    case 0 : {
      break;   
    }
  } 
}


// ***********************************************************************
/// ----------------------------------------------------------
///  HAL : CONFIG RD SLAVE
/// ----------------------------------------------------------
// ***********************************************************************
void DDR_PHY_hal_cfg_cdc_slave_rd( uint32 _inst_, uint32 delay, uint16 coarse_delay, uint16 hp_mode, uint8 rank )
{
    uint32 cdc;
    uint32 mask;
    uint32 shift;
	uint32 t_delay;
	for (rank = 0 ; rank < NUM_CS; rank++)
	{
		t_delay = 0;
        // Read the CDC delay register
    cdc = HWIO_INX (_inst_, DDR_PHY_DDRPHY_CMCDCRD_CTL_CFG);

        mask  = DDR_PHY_hal_cfg_cdc_mask(coarse_delay, rank, hp_mode);
        shift = DDR_PHY_hal_cfg_cdc_shift(coarse_delay, rank, hp_mode);

        // Clear space for delay in CDC
        cdc = cdc & mask;

        // Shift delay to insert in CDC
        t_delay = delay<<shift;
		
//		if ((coarse_delay == 0) && (rank == 1))
//		{
//       	delay = 0;
//		}
		
        // Insert delay into CDC
        cdc = cdc | t_delay;
	
        // Write CDC delay register 
    HWIO_OUTX (_inst_, DDR_PHY_DDRPHY_CMCDCRD_CTL_CFG, cdc); 
	
    // Disable load 
        // Gate the clock
        // Disable the register
    HWIO_OUTXF3 (_inst_, DDR_PHY_DDRPHY_CMCDCRD_TOP_CFG, EN, LOAD, GATE, 0, 0, 1);

        // Pulse load
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_CMCDCRD_TOP_CFG, LOAD, 1);
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_CMCDCRD_TOP_CFG, LOAD, 0);

        // Enable the register
        // Un-Gate the clock
    HWIO_OUTXF2 (_inst_, DDR_PHY_DDRPHY_CMCDCRD_TOP_CFG, GATE, EN, 0, 1);
	}

}

void DDR_PHY_hal_cfg_pbit_dq_delay( uint32 _inst_, uint16 dq_num, uint16 txrx, uint16 sel, uint16 delay )
{
    uint32 temp = 0;
    uint32 shift = 0;
    uint32 mask = 0;
    
    shift = (0x5 * sel);
    mask = (~(0x1F << shift));
  
    /// select source of rank select b/w memory controller and csr default is from memory controller
    /// DDRPHY_CMHUB_TOP_0_CFG.BIT_RANK_SRC_SEL = rank_src_sel;
 
            switch(txrx) {  
            case 1 : {          
                    if(dq_num < 2) {
                     temp = HWIO_INXF(_inst_+(dq_num*8), DDR_PHY_DDRPHY_CMSLICE0_PBIT_CTL_DQ_0_RXTX_CFG, TX0_CTL);
                            temp = ((delay << shift) | (mask & temp));
               HWIO_OUTXF (_inst_+(dq_num*8), DDR_PHY_DDRPHY_CMSLICE0_PBIT_CTL_DQ_0_RXTX_CFG, TX0_CTL, temp);
                                }
                    else  { 
                    temp = HWIO_INXF(_inst_+((dq_num*8)+4), DDR_PHY_DDRPHY_CMSLICE0_PBIT_CTL_DQ_0_RXTX_CFG, TX0_CTL);
                    temp = ((delay << shift) | (mask & temp));
                      HWIO_OUTXF (_inst_+((dq_num*8)+4), DDR_PHY_DDRPHY_CMSLICE0_PBIT_CTL_DQ_0_RXTX_CFG, TX0_CTL, temp);
                          } 
                     break;
                    }
           case 0 :  
            {
                     if(dq_num < 2) {
                     temp = HWIO_INXF(_inst_+(dq_num*8), DDR_PHY_DDRPHY_CMSLICE0_PBIT_CTL_DQ_0_RXTX_CFG, RX0_CTL);
                            temp = ((delay << shift) | (mask & temp));
               HWIO_OUTXF (_inst_+(dq_num*8), DDR_PHY_DDRPHY_CMSLICE0_PBIT_CTL_DQ_0_RXTX_CFG, RX0_CTL, temp);
                                }
                     else { 
                    temp = HWIO_INXF(_inst_+((dq_num*8)+4), DDR_PHY_DDRPHY_CMSLICE0_PBIT_CTL_DQ_0_RXTX_CFG, RX0_CTL);
                    temp = ((delay << shift) | (mask & temp));
                      HWIO_OUTXF (_inst_+((dq_num*8)+4), DDR_PHY_DDRPHY_CMSLICE0_PBIT_CTL_DQ_0_RXTX_CFG, RX0_CTL, temp);
                          } 
                 break;
            }
      }
}




// ***********************************************************************
/// DDRPHY write leveling ROUTINE
/// seq_msg(INFO, 0, "DDRPHY Write Leveling CFG delay value setting");
/// -----------------------------------------------------------------
///     HALs for write leveling ROUTINE
/// 
/// -----------------------------------------------------------------
// ***********************************************************************
uint32 DDR_PHY_hal_sta_wrlvl_coarse( uint32 _inst_, uint8 rank )
{

    if (rank) {
        return (((HWIO_INX (_inst_, DDR_PHY_DDRPHY_CMCDCWRLVL_CTL_CFG) & 0x7C00) >> 10));
    } else {
        return ((HWIO_INX (_inst_, DDR_PHY_DDRPHY_CMCDCWRLVL_CTL_CFG) & 0x1F));
    }
}


uint32 DDR_PHY_hal_sta_wrlvl_fine( uint32 _inst_, uint8 rank )
{

    if (rank) {
        return (((HWIO_INX (_inst_, DDR_PHY_DDRPHY_CMCDCWRLVL_CTL_CFG) & 0xF8000) >> 15));
    } else {
        return (((HWIO_INX (_inst_, DDR_PHY_DDRPHY_CMCDCWRLVL_CTL_CFG) & 0x3E0) >> 5));
    }
}


uint32 DDR_PHY_hal_sta_wrlvl_training( uint32 _inst_ )
{

    return ((HWIO_INXF (_inst_, DDR_PHY_DDRPHY_BISC_TRAINING_STA, TRAINING_STATUS) & 0xFF));
}


uint32 DDR_PHY_hal_sta_wrlvl_retmr( uint32 _inst_, uint8 rank )
{
    uint32 retmr;


    if (rank) {
        retmr = HWIO_INXF (_inst_, DDR_PHY_DDRPHY_CMHUB_TOP_1_CFG, DQS_RETMR_R1);
    } else {
        retmr = HWIO_INXF (_inst_, DDR_PHY_DDRPHY_CMHUB_TOP_1_CFG, DQS_RETMR_R0);
    }
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_CMHUB_TOP_0_CFG, TRIG_WRLVL_LATCH, 0x1);
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_CMHUB_TOP_0_CFG, TRIG_WRLVL_LATCH, 0x0);
    
    return ((retmr));
}


uint32 DDR_PHY_hal_sta_wrlvl_dq_retmr( uint32 _inst_, uint8 rank )
{
    uint32 retmr;


    if (rank) {
        retmr = HWIO_INXF (_inst_, DDR_PHY_DDRPHY_CMHUB_TOP_1_CFG, DQ_RETMR_R1);
    } else {
        retmr = HWIO_INXF (_inst_, DDR_PHY_DDRPHY_CMHUB_TOP_1_CFG, DQ_RETMR_R0);
    }
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_CMHUB_TOP_0_CFG, TRIG_WRLVL_LATCH, 0x1);
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_CMHUB_TOP_0_CFG, TRIG_WRLVL_LATCH, 0x0);
    
    return ((retmr));
}


uint32 DDR_PHY_hal_sta_wrlvl_half( uint32 _inst_, uint8 rank )
{
    uint32 half;


    if (rank) {
        half = HWIO_INXF (_inst_, DDR_PHY_DDRPHY_CMHUB_TOP_1_CFG, DQS_HALF_CYCLE_R1);
    } else {
        half = HWIO_INXF (_inst_, DDR_PHY_DDRPHY_CMHUB_TOP_1_CFG, DQS_HALF_CYCLE_R0);
    }
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_CMHUB_TOP_0_CFG, TRIG_WRLVL_LATCH, 0x1);
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_CMHUB_TOP_0_CFG, TRIG_WRLVL_LATCH, 0x0);
    
    return ((half));
}

uint32 DDR_PHY_hal_sta_wrlvl_dq_half( uint32 _inst_, uint8 rank )
{
    uint32 half;


    if (rank) {
        half = HWIO_INXF (_inst_, DDR_PHY_DDRPHY_CMHUB_TOP_1_CFG, DQ_HALF_CYCLE_R1);
    } else {
        half = HWIO_INXF (_inst_, DDR_PHY_DDRPHY_CMHUB_TOP_1_CFG, DQ_HALF_CYCLE_R0);
    }
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_CMHUB_TOP_0_CFG, TRIG_WRLVL_LATCH, 0x1);
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_CMHUB_TOP_0_CFG, TRIG_WRLVL_LATCH, 0x0);
    
    return ((half));
}

uint32 DDR_PHY_hal_sta_wrlvl_full( uint32 _inst_, uint8 rank )
{
    uint32 full;


    if (rank) {
        full = HWIO_INXF (_inst_, DDR_PHY_DDRPHY_CMHUB_TOP_1_CFG, DQS_FULL_CYCLE_R1);
    } else {
        full = HWIO_INXF (_inst_, DDR_PHY_DDRPHY_CMHUB_TOP_1_CFG, DQS_FULL_CYCLE_R0);
    }
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_CMHUB_TOP_0_CFG, TRIG_WRLVL_LATCH, 0x1);
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_CMHUB_TOP_0_CFG, TRIG_WRLVL_LATCH, 0x0);
    
    return ((full));
}

uint32 DDR_PHY_hal_sta_wrlvl_dq_full( uint32 _inst_, uint8 rank )
{
    uint32 full;


    if (rank) {
        full = HWIO_INXF (_inst_, DDR_PHY_DDRPHY_CMHUB_TOP_1_CFG, DQ_FULL_CYCLE_R1);
    } else {
        full = HWIO_INXF (_inst_, DDR_PHY_DDRPHY_CMHUB_TOP_1_CFG, DQ_FULL_CYCLE_R0);
    }
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_CMHUB_TOP_0_CFG, TRIG_WRLVL_LATCH, 0x1);
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_CMHUB_TOP_0_CFG, TRIG_WRLVL_LATCH, 0x0);
    
    return ((full));
}

uint32 DDR_PHY_cdcext_shift_mask( uint16 rank, uint16 coarse_delay, uint16 hp_mode, uint8 shift_mask)
{
    uint32 shift;
    uint32 mask;

    ///  Decode Mode, Delay and Rank
    if (hp_mode == 1) {
        if (coarse_delay == 1) {
            ///  Rank 0
            if (rank == 1) {
                shift = 10; // 0xA
                                mask  = 0xFFFF83FF; 
            } else {
                shift = 0;
                                mask  = 0xFFFFFFE0; 
            }
        } else         ///  Fine delay
        if (rank == 1) {
            shift = 15; // 0xF
                        mask  = 0xFFF07FFF; 
        } else {
            shift = 5;
                        mask  = 0xFFFFFC1F; 
        }
    } else     if (rank == 1) {   //lp mode
        shift = 25; // 0x19
                mask  = 0xC1FFFFFF; 
    } else {
        shift = 20; // 0x12
                mask  = 0xFE0FFFFF; 
    }
    ///  Return selected range
    if (shift_mask == 0) {
        return (shift);
    } 
        else  {
        return (mask);
    }
}

uint32 DDR_PHY_cdcext_shift_mask_reg(uint32 reg, uint32 delay, uint32 shift, uint32 mask)
{
  reg   = reg & mask;
  delay = delay << shift;
  reg   = reg | delay;
  
  return (reg);
  
}

void DDR_PHY_hal_cfg_cdcext_slave_rd( uint32 _inst_, uint16 rank, uint32 delay, uint16 coarse_delay, uint16 hp_mode, uint16 prfs_no )
{
    uint32 reg;
    uint32 shift;
    uint32 mask;

    shift = DDR_PHY_cdcext_shift_mask(rank, coarse_delay, hp_mode, 0);
    mask  = DDR_PHY_cdcext_shift_mask(rank, coarse_delay, hp_mode, 1);
          
          reg = HWIO_INX (_inst_+(prfs_no*4), DDR_PHY_DDRPHY_CDCEXT_RD_0_CTL_CFG);
          reg = DDR_PHY_cdcext_shift_mask_reg(reg,delay,shift,mask);
          HWIO_OUTX (_inst_+(prfs_no*4), DDR_PHY_DDRPHY_CDCEXT_RD_0_CTL_CFG, reg);
}



void DDR_PHY_hal_cfg_cdcext_slave_wr( uint32 _inst_, uint16 rank, uint32 delay, uint16 coarse_delay, uint16 hp_mode, uint16 prfs_no )
{
    uint32 reg;
    uint32 shift;
    uint32 mask;

    shift = DDR_PHY_cdcext_shift_mask(rank, coarse_delay, hp_mode, 0);
    mask  = DDR_PHY_cdcext_shift_mask(rank, coarse_delay, hp_mode, 1);        
          
          reg = HWIO_INX (_inst_+(prfs_no*4), DDR_PHY_DDRPHY_CDCEXT_WR_0_CTL_CFG);
          reg = DDR_PHY_cdcext_shift_mask_reg(reg,delay,shift,mask);
          HWIO_OUTX (_inst_+(prfs_no*4), DDR_PHY_DDRPHY_CDCEXT_WR_0_CTL_CFG, reg);
}


void DDR_PHY_hal_cfg_wrlvlext_ctl_update( uint32 _inst_, uint8 period_index, uint8 rank, uint8 retmr )
{
    ///  wrlvl extension retmr and delay values
            if (rank == 1) {
                HWIO_OUTXF2 (_inst_+(period_index*4), DDR_PHY_DDRPHY_WRLVLEXT_CTL_0_CFG, DQS_RETMR_R1, DQ_RETMR_R1, retmr, retmr);            
            } else {
                HWIO_OUTXF2 (_inst_+(period_index*4), DDR_PHY_DDRPHY_WRLVLEXT_CTL_0_CFG, DQS_RETMR_R0, DQ_RETMR_R0, retmr, retmr);
            }
}


void DDR_PHY_hal_cfg_wrext_ctl_update( uint32 _inst_, uint8 period_index, uint8 rank, uint32 retmr, uint32 half_cycle, uint32 full_cycle )
{

    ///  wrlvl extension retmr and delay values
          switch(rank) { 
          case 1  : {
                HWIO_OUTXF (_inst_+(period_index*4), DDR_PHY_DDRPHY_WRLVLEXT_CTL_0_CFG, DQ_RETMR_R1, retmr);
                HWIO_OUTXF (_inst_+(period_index*4), DDR_PHY_DDRPHY_WRLVLEXT_CTL_0_CFG, DQ_HALF_CYCLE_R1, half_cycle);
                HWIO_OUTXF (_inst_+(period_index*4), DDR_PHY_DDRPHY_WRLVLEXT_CTL_0_CFG, DQ_FULL_CYCLE_R1, full_cycle);
                                 break;
            } 
         case 0 : {
                HWIO_OUTXF (_inst_+(period_index*4), DDR_PHY_DDRPHY_WRLVLEXT_CTL_0_CFG, DQ_RETMR_R0, retmr);
                HWIO_OUTXF (_inst_+(period_index*4), DDR_PHY_DDRPHY_WRLVLEXT_CTL_0_CFG, DQ_HALF_CYCLE_R0, half_cycle);
                HWIO_OUTXF (_inst_+(period_index*4), DDR_PHY_DDRPHY_WRLVLEXT_CTL_0_CFG, DQ_FULL_CYCLE_R0, full_cycle);
                                 break;
            }
       }
}


void DDR_PHY_hal_cfg_wrlvl_full( uint32 _inst_, uint32 rank, uint32 dq_full_cycle )
 {

   if (rank == 1) {
       HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_CMHUB_TOP_1_CFG, DQ_FULL_CYCLE_R1, dq_full_cycle);
   } else {
       HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_CMHUB_TOP_1_CFG, DQ_FULL_CYCLE_R0, dq_full_cycle);
   }
   HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_CMHUB_TOP_0_CFG, TRIG_WRLVL_LATCH, 0x1);
   HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_CMHUB_TOP_0_CFG, TRIG_WRLVL_LATCH, 0x0);

 }


void DDR_PHY_hal_cfg_wrlvlext_ctl_dqs_dq_struct_half( uint32 _inst_, uint8 period_index, uint8 dqs_half, uint8 dq_half )
{

    ///  wrlvl extension half
                HWIO_OUTXF (_inst_+(period_index*4), DDR_PHY_DDRPHY_WRLVLEXT_CTL_0_CFG, DQS_STRUCT_HALF_CYCLE_R1,dqs_half);
                HWIO_OUTXF (_inst_+(period_index*4), DDR_PHY_DDRPHY_WRLVLEXT_CTL_0_CFG, DQS_STRUCT_HALF_CYCLE_R0,dqs_half);
                HWIO_OUTXF (_inst_+(period_index*4), DDR_PHY_DDRPHY_WRLVLEXT_CTL_0_CFG, DQ_STRUCT_HALF_CYCLE_R1, dq_half);
                HWIO_OUTXF (_inst_+(period_index*4), DDR_PHY_DDRPHY_WRLVLEXT_CTL_0_CFG, DQ_STRUCT_HALF_CYCLE_R0, dq_half);
}

