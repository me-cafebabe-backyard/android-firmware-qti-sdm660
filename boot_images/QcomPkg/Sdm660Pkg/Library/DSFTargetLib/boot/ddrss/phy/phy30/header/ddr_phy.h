////////////////////////////////////////////////////////////////////////////////////////////////
//===========================================================================
//  Copyright (c) 2016 QUALCOMM Technologies Incorporated.  All Rights Reserved.  
//  QUALCOMM Proprietary and Confidential. 
//===========================================================================
////////////////////////////////////////////////////////////////////////////////////////////////
#include "HAL_SNS_DDR.h"
#include "ddr_ss_seq_hwiobase.h"
#include "ddr_ss_seq_hwioreg.h"

#define DQ_PER_BYTE  9

//===========================================================================
uint32 DDR_PHY_hal_sta_ca_vref( uint32 _inst_ );
void DDR_PHY_hal_cfg_ca_vref_dq_out_entry( uint32 _inst_ );
void  DDR_PHY_hal_cfg_ca_vref_dq_in_entry( uint32 _inst_ );
void DDR_PHY_hal_cfg_ca_vref_dq_out_exit ( uint32 _inst_ );
void DDR_PHY_hal_cfg_ca_vref_dq_exit( uint32 _inst_ );
void  DDR_PHY_hal_cfg_ca_vref_dq_in_exit ( uint32 _inst_ );
//void DDR_PHY_hal_cfg_ca_vref_ca( uint32 _inst_ );

uint8 DDR_PHY_cdcext_msb_lsb( uint32 _inst_, uint16 rank, uint16 coarse_delay, uint16 hp_mode, uint16 prfs_no, uint8 msb_lsb );
void DDR_PHY_hal_cfg_cdcext_slave_rcw( uint32 _inst_, uint16 rank, uint32 delay, uint16 coarse_delay, uint16 hp_mode, uint16 prfs_no );
void DDR_PHY_hal_cfg_cdcext_slave_rd( uint32 _inst_, uint16 rank, uint32 delay, uint16 coarse_delay, uint16 hp_mode, uint16 prfs_no );
void DDR_PHY_hal_cfg_cdcext_slave_rdt2( uint32 _inst_, uint16 rank, uint32 delay, uint16 coarse_delay, uint16 hp_mode, uint16 prfs_no );
void DDR_PHY_hal_cfg_cdcext_slave_wrlvl( uint32 _inst_, uint16 rank, uint32 delay, uint16 coarse_delay, uint16 hp_mode, uint16 prfs_no );
void DDR_PHY_hal_cfg_cdcext_slave_wr( uint32 _inst_, uint16 rank, uint32 delay, uint16 coarse_delay, uint16 hp_mode, uint16 prfs_no );
void DDR_PHY_hal_cfg_wrlvlext_ctl_dqs_dq_struct_half( uint32 _inst_, uint8 period_index, uint8 dqs_half, uint8 dq_half );

void DDR_PHY_hal_cfg_cdc_rcw( uint32 _inst_, uint32 enable, uint32 num_cycle );
void DDR_PHY_hal_cfg_cdc_slave_rcw( uint32 _inst_, uint32 delay, uint16 coarse_delay, uint16 hp_mode, uint8 rank );
void DDR_PHY_hal_cfg_cdc_slave_rd( uint32 _inst_, uint32 delay, uint16 coarse_delay, uint16 hp_mode, uint8 rank );
void DDR_PHY_hal_cfg_cdc_slave_wrlvl( uint32 _inst_, uint32 delay, uint16 coarse_delay, uint16 hp_mode, uint8 rank );
void DDR_PHY_hal_cfg_cdc_slave_wr( uint32 _inst_, uint32 delay, uint16 coarse_delay, uint16 hp_mode, uint8 rank );

void DDR_PHY_hal_cfg_pbit_dq_all( uint32 _inst_, uint32 txrx, uint16 rank, uint16 delay, uint16 all, uint8 vector[DQ_PER_BYTE] );
void DDR_PHY_hal_cfg_pbit_dq_delay( uint32 _inst_, uint16 dq_num, uint16 txrx, uint16 sel, uint16 delay );
void DDR_PHY_hal_cfg_wr_dqs_dcc_adj( uint32 _inst_, uint8 rank, uint16 wr_dqs_dcc_adj);

void DDR_PHY_hal_cfg_pbit_dqs_delay( uint32 _inst_, uint16 txrx, uint16 rank, uint16 delay );

void DDR_PHY_hal_cfg_local_vref( uint32 _inst_, uint32 local_vref_trim, uint16 local_vref_rank_select, uint32 local_vref_slice_select );

void DDR_PHY_hal_cfg_global_vref( uint32 _inst_, uint32 vref_val, uint32 clk_freq_khz, uint8 cs);

uint32 DDR_PHY_hal_sta_wrlvl_coarse( uint32 _inst_, uint8 rank );
uint32 DDR_PHY_hal_sta_wrlvl_fine( uint32 _inst_, uint8 rank );
uint32 DDR_PHY_hal_sta_wrlvl_training( uint32 _inst_ );
uint32 DDR_PHY_hal_sta_wrlvl_retmr( uint32 _inst_, uint8 rank );
uint32 DDR_PHY_hal_sta_wrlvl_half( uint32 _inst_, uint8 rank );
uint32 DDR_PHY_hal_sta_wrlvl_dq_half( uint32 _inst_, uint8 rank );
uint32 DDR_PHY_hal_sta_wrlvl_full( uint32 _inst_, uint8 rank );
uint32 DDR_PHY_hal_sta_wrlvl_dq_full( uint32 _inst_, uint8 rank );
uint32 DDR_PHY_hal_sta_wrlvl_dq_retmr( uint32 _inst_, uint8 rank );

uint8 DDR_PHY_hal_sta_rcw_coarse( uint32 _inst_, uint8 rank );
uint8 DDR_PHY_hal_sta_rcw_fine( uint32 _inst_, uint8 rank );
uint8 DDR_PHY_hal_sta_rcw_num_cycle( uint32 _inst_ );
void DDR_PHY_rd_mon_status( uint32 _inst_, uint8 pass[1] );
void DDR_PHY_hal_cfg_cdc_rcw( uint32 _inst_, uint32 enable, uint32 num_cycle );
void DDR_PHY_hal_cfg_cdc_slave_rcw( uint32 _inst_, uint32 delay, uint16 coarse_delay, uint16 hp_mode, uint8 rank );
void DDR_PHY_hal_cfg_wrlvl_delay_set( uint32 _inst_, uint8 rank, uint32 fine_delay, uint32 coarse_delay );
void DDR_PHY_hal_cfg_cdcext_wrlvl_update( uint32 _inst_, uint8 period_index, uint8 rank, uint32 fine_delay, uint32 coarse_delay );
void DDR_PHY_hal_cfg_wrlvl_set( uint32 _inst_, uint32 rank, uint32 dqs_retmr, uint32 dqs_half_cycle, uint32 dqs_full_cycle );
void DDR_PHY_hal_cfg_wrlvl_retmr( uint32 _inst_, uint32 rank, uint32 dqs_retmr );
void DDR_PHY_hal_cfg_wrlvlext_ctl_update( uint32 _inst_, uint8 period_index, uint8 rank, uint8 retmr);
void DDR_PHY_hal_cfg_wrext_ctl_update( uint32 _inst_, uint8 period_index, uint8 rank, uint32 retmr, uint32 half_cycle, uint32 full_cycle );
void DDR_PHY_hal_cfg_wrlvl_half( uint32 _inst_, uint32 rank, uint32 dq_half_cycle );
void DDR_PHY_hal_cfg_wrlvl_full( uint32 _inst_, uint32 rank, uint32 dq_full_cycle );

uint32 DDR_PHY_rtn_training_dcc_wrlvl(DDR_STRUCT *ddr, uint32 _inst_);//, uint8 pll);
uint32 DDR_PHY_rtn_training_dcc_t90(DDR_STRUCT *ddr, uint32 _inst_);
uint32 DDR_PHY_rtn_training_dcc_io_dqs(DDR_STRUCT *ddr, uint32 _inst_);
void DDR_PHY_hal_cfg_rd_dqs_dcc_adj(uint32 _inst_, uint8 ch, uint8 cs,  uint8 delay_indx);

void DDR_PHY_hal_cfg_dq_vref_dqs2dq_max( uint32 _inst_, uint8 rank, uint8 prfs_num, uint8 delay, uint8 coarse_dly );
void DDR_PHY_hal_cfg_dq_vref_dqs2dq_min( uint32 _inst_, uint8 rank, uint8 prfs_num, uint8 delay, uint8 coarse_dly );
void DDR_PHY_hal_cfg_dq_vref_cen_cfg_min( uint32 _inst_, uint8 rank, uint8 prfs_num, uint8 full_cycle, uint8 half_cycle, uint8 retimer );
void DDR_PHY_hal_cfg_dq_vref_cen_cfg_max( uint32 _inst_, uint8 rank, uint8 prfs_num, uint8 full_cycle, uint8 half_cycle, uint8 retimer );

void DDR_PHY_hal_cfg_ca_vref_dq_retmr( uint32 _inst_, uint8 rank, uint32 dq_retmr );



