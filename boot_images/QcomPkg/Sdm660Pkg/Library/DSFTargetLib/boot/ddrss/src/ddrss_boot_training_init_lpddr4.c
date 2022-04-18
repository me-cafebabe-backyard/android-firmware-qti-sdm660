/****************************************************************************
 QUALCOMM Proprietary Design Data
 Copyright (c) 2015, Qualcomm Technologies Incorporated. All rights reserved.
 ****************************************************************************/
/*==============================================================================
                                EDIT HISTORY

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/DSFTargetLib/boot/ddrss/src/ddrss_boot_training_init_lpddr4.c#12 $
$DateTime: 2018/12/26 02:55:51 $
$Author: pwbldsvc $
================================================================================
when       who          what, where, why
--------   ---          --------------------------------------------------------
05/08/14   jeasley      Change wrlvl to zero based channel and chip select.
                        Moved DRAM routines from wrlvl.
05/04/14   arindamm     First edit history header. Add new entries at top.
================================================================================*/
#include "ddrss.h"
#include "target_config.h"


// Needed for the perbit Restore sequence.
extern uint8 dq_dbi_bit;
extern uint8 dq_spare_bit;
extern uint8 connected_bit_mapping_CA [PINS_PER_PHY_CONNECTED_CA];


boolean HAL_DDR_Boot_Training_Init(DDR_STRUCT *ddr, DDR_CHANNEL channel, DDR_CHIPSELECT chip_select)
{

     if ((ddr->misc.platform_id == STARLORD_PLATFORM_ID) && (ddr->misc.chip_version == 0x0100))
	 {
	   //sanaths - disable periodic events on the unusable channel (channel 0)
       BIMC_All_Periodic_Ctrl (ddr, DDR_CH0, DDR_CS_BOTH, FEATURE_DISABLE/*0 for disable*/);
       // Executes training and returns TRUE if called with DDR_TRAINING_MODE_INIT
       DDRSS_boot_training_lpddr4 (ddr, DDR_CH1, chip_select); //train only for 1 channel that is working
	 }
	 else
	 {
       // Executes training and returns TRUE if called with DDR_TRAINING_MODE_INIT
       DDRSS_boot_training_lpddr4 (ddr, channel, chip_select);
	 }
    ddr->flash_params.version = TARGET_DDR_SYSTEM_FIRMWARE_VERSION;
    
    // Post Boot Training setup.
    DDRSS_Post_Boot_Training(ddr, channel, chip_select);
    
    return TRUE; 
}


//================================================================================================//
// DDRSS Boot Training
//================================================================================================//

boolean DDRSS_boot_training_lpddr4 (DDR_STRUCT *ddr, DDR_CHANNEL channel, DDR_CHIPSELECT chip_select)
{
  
    uint8  byte_lane = 0;
    uint8  ch        = 0;
    uint8  cs        = 0;
    PHY_BUS  dq     = DQ;
    PHY_BUS  ca     = CA;
    uint8 training_ddr_freq_indx_eq_training_table_index = 0;
    uint32 dq0_ddr_phy_base  = 0;
    uint32 ca0_ddr_phy_base  = 0;

    uint32 reg_offset_dpe    = 0;

    uint32 temp_MPVref_bit[NUM_DQ_PCH] = {0};
	uint32 temp_WRLVLEXT_dq        = 0;
	uint32 temp_WRLVLEXT_ca        = 0;
	uint32 en_dis_WR_fcycle_bit_dq = 0;
	uint32 en_dis_WR_fcycle_bit_ca = 0;
	uint8  fcycle_bfields[4]       = {2, 10, 18, 26};
	uint32 temp_RCWEXT_dq        = 0;
	uint32 temp_RCWEXT_ca        = 0;
	uint32 en_dis_RCW_fcycle_bit_dq = 0;
	uint32 en_dis_RCW_fcycle_bit_ca = 0;
	uint8  fcycle_bfields_rcw[2]       = {5, 13};
	uint8  fcycle_ind              = 0;
    
    DDR_CHIPSELECT qualified_cs = (DDR_CHIPSELECT)(chip_select & ddr->detected_ddr_device[0].populated_chipselect);
    
    uint32  training_freq_to_prfs_table_map[MAX_TRAINING_FREQ_NUM] = {0};
    
#if  DSF_WRLVL_TRAINING_EN
    uint8   RL_WL_idx  = 0;
    uint32  MR2_wrlvl_opcode    = 0;
    uint8   wrlvl_clk_freq_idx  = 0;
    uint32  wrlvl_clk_freq_khz  = 0;
    uint32  wrlvl_freq_khz_pass1  = 0;
    uint32  wrlvl_prfs_index_pass1  = 0;
#endif

#if DSF_RCW_TRAINING_EN
    uint32 rcw_training_ddr_freq_index = 0;
    uint8 rcw_start_clk_idx = 0;
    uint8 rcw_clk_idx = 0;
#endif

#if DSF_CA_VREF_TRAINING_EN
    boolean ca_vref_fail_flag = FALSE;
    
    uint32 reg_offset_ddr_phy = 0; 
#endif

#if DSF_PERIODIC_TRAINING_EN    
    uint8   dit_ave                                =  0;
#endif

#if (DSF_CA_VREF_TRAINING_EN || DSF_WR_DQDQS_TRAINING_EN)
    uint8  MR13_value        = 0;
#endif 

#if DSF_WR_DQDQS_TRAINING_EN
    uint8  fsp_op            = 0;
    uint8  fsp_wr            = 0;
    uint8  high_current_mode = 1;
#endif 

#if (DSF_CA_VREF_TRAINING_EN || DSF_WR_DQDQS_TRAINING_EN || DSF_RD_DQDQS_TRAINING_EN)
    ddr_training_args tArgs;
#endif 

    uint8 low_speed_clk_idx = 0;
    uint8  training_ddr_freq_indx = 0;
    uint8  ddr_freq_indx = 0;
    uint32 PRFS_BAND_THRESHOLD[NUM_PRFS_BANDS]  = {F_RANGE_0, F_RANGE_1, F_RANGE_2, F_RANGE_3, F_RANGE_4, F_RANGE_5, F_RANGE_6, F_RANGE_7};
    uint32 training_freq_table[MAX_TRAINING_FREQ_NUM] = {0};
    uint8  prfs_index = TRAINING_START_PRFS; 
    uint8  training_table_index = 0; 
    uint8  min_training_prfs_index = 0xFF; 
    static training_params_t training_params;
    training_params_t *training_params_ptr;
    
#if DSF_PXI_TRAINING_EN
    uint64 pxi_addr = 0;
    uint32* pxi_ptr = 0;
    uint32 pxi_data = 0;
#endif
    
#if DSF_WR_DQDQS_TRAINING_TDQS2DQ_CAL_EN
    uint32 temp_rd_cdc_value[NUM_DQ_PCH] = {0};
#endif

#if (DSF_WR_DQDQS_TRAINING_TDQS2DQ_CAL_EN || DSF_PERIODIC_TRAINING_EN)
    uint16 dit_count[NUM_CH][NUM_CS][NUM_DIE_PCH] = {{{0}}};
#endif
    // Set aside an area to be used by training algorithm for computation local_vars area.
    // This area is declared as a static local array so as to get it into the ZI data section
    // of the executable. Training algorithms will receive a pointer to this area, and can
    // use it as a storage for what would otherwise have been local variables, consuming
    // huge amounts of stack space.
    static   uint8   *local_vars;
    boolean bResult;
    uint32 local_var_size = LOCAL_VARS_AREA_SIZE;
    
#if (DSF_CA_VREF_TRAINING_EN || DSF_PERIODIC_TRAINING_EN || DSF_WR_DQDQS_TRAINING_EN)
     // Training data structure pointer
    training_data *training_data_ptr;   
    training_data_ptr = (training_data *)(&ddr->flash_params.training_data);   
#endif   
 
    bResult = ddr_external_get_buffer((void **)&local_vars, &local_var_size);
    
    if (bResult != TRUE)
    {
         return bResult;
    }
    // Training params structure pointer
    training_params_ptr = &training_params;
    
//================================================================================================//
// Pre training setup
//================================================================================================//
    // Set all training parameters to recommended values
    DDRSS_set_training_params(training_params_ptr);
    
    // Enable broadcast mode for all DQ and CA PHYs on both channels
    HWIO_OUTX((DDR_PHY_SS_BASE + SEQ_DDR_SS_DDRSS_AHB2PHY_SWMAN_OFFSET),
              AHB2PHY_SWMAN_AHB2PHY_BROADCAST_EN_CFG_LOWER, ALL_CAsDQs);

#if DSF_PXI_TRAINING_EN

#else
    DDRSS_Get_Training_Address(ddr);
    
    // Repopulate write_in_pattern with x8 training data
    DDRSS_Create_Training_Data(ddr->misc.bus_width_pch);
#endif
    
#if DSF_PERIODIC_TRAINING_EN    
    training_data_ptr->results.dit.dit_fine_step_limit  = DIT_FINE_STEP_LIMIT;
    training_data_ptr->results.dit.dit_interval_per_sec = DIT_INTERVAL_PER_SEC;
#endif

    //search through frequency table to automatically identify training frequency
    for (training_ddr_freq_indx = 0; training_ddr_freq_indx < ddr->misc.ddr_num_clock_levels; training_ddr_freq_indx++)
    { 
        if ((ddr->misc.clock_plan[training_ddr_freq_indx].clk_freq_in_khz) > PRFS_BAND_THRESHOLD[prfs_index])
        {
            if ((ddr->misc.clock_plan[training_ddr_freq_indx-1].clk_freq_in_khz) > PRFS_BAND_THRESHOLD[prfs_index - 1]) //make sure we have a frequency in this band
            {
                training_freq_table[training_table_index] = ddr->misc.clock_plan[training_ddr_freq_indx -1].clk_freq_in_khz;
                
                if (min_training_prfs_index > prfs_index)
                {
                    min_training_prfs_index = prfs_index;
                }
#if DSF_RCW_TRAINING_EN
                if (prfs_index == TRAINING_START_PRFS) 
                {
                    rcw_training_ddr_freq_index = training_table_index + 1;   //1056000
                }
                // Get first rcw clk index in the clock plan
                for (rcw_start_clk_idx = 0; rcw_start_clk_idx < ddr->misc.ddr_num_clock_levels; rcw_start_clk_idx++)
                { 
                    if (RCW_THRESHOLD_FREQ < ddr->misc.clock_plan[rcw_start_clk_idx].clk_freq_in_khz)
                    break;            
                }
    
                // Get RCW clk index in the clock plan
                //for (rcw_clk_idx = 0; rcw_clk_idx < ddr->misc.ddr_num_clock_levels; rcw_clk_idx++)
                //{ 
                //    if (training_freq_table[rcw_training_ddr_freq_index] == ddr->misc.clock_plan[rcw_clk_idx].clk_freq_in_khz)
                //        break;
                //}
#endif
                training_freq_to_prfs_table_map[training_table_index] = prfs_index;
                training_table_index++;
                prfs_index++;
            }
            else
            {
                prfs_index++;  //don't advance training table index
            }
        }
        if (training_ddr_freq_indx == ddr->misc.ddr_num_clock_levels-1) 
        {
            training_freq_table[training_table_index] = ddr->misc.clock_plan[training_ddr_freq_indx].clk_freq_in_khz;
            training_freq_to_prfs_table_map[training_table_index] = prfs_index;
        }
    }
    #if DSF_RCW_TRAINING_EN
    // Get RCW clk index in the clock plan
    for (rcw_clk_idx = 0; rcw_clk_idx < ddr->misc.ddr_num_clock_levels; rcw_clk_idx++)
    { 
        if (training_freq_table[rcw_training_ddr_freq_index] == ddr->misc.clock_plan[rcw_clk_idx].clk_freq_in_khz)
            break;
    }
	#endif
#if DSF_PERIODIC_TRAINING_EN
    if( prfs_index >= MIN_DTTS_TRACKING_PRFS)  //> 1555Mhz
    {
        training_data_ptr->results.dit.dit_acq_ndx  = (training_ddr_freq_indx -2) ;  //for now, acquiring index is ONE less than tracking index
        training_data_ptr->results.dit.dit_trac_ndx = training_ddr_freq_indx-1;
    }
    else //no periodic training required
    {
        training_data_ptr->results.dit.dit_acq_ndx  = 255 ;  //for now, acquiring index is ONE less than tracking index
        training_data_ptr->results.dit.dit_trac_ndx = 255;
    }
#endif

    // Disable all periodic functions: auto refresh, hw self refresh, periodic ZQCAL, periodic SRR
    BIMC_All_Periodic_Ctrl (ddr, channel, DDR_CS_BOTH, FEATURE_DISABLE/*0 for disable*/);

    for (ch = 0; ch < NUM_CH; ch++)
    {
        reg_offset_dpe = REG_OFFSET_DPE(ch);
        if ((channel >> ch) & 0x1)
        {
            // Disable Power Down
            HWIO_OUTXF2 (reg_offset_dpe, DPE_PWR_CTRL_0, PWR_DN_EN, CLK_STOP_PWR_DN_EN, 0x0, 0x0);
            
            HWIO_OUTXF  (reg_offset_dpe, DPE_CONFIG_4, LOAD_ALL_CONFIG, 0x1);
        }
    }
     
    //Determine highest band0 frequency as low speed frequency
    for (low_speed_clk_idx = 0; low_speed_clk_idx < ddr->misc.ddr_num_clock_levels; low_speed_clk_idx++)
    { 
        if ( LOWEST_FPRS_FREQ < ddr->misc.clock_plan[low_speed_clk_idx].clk_freq_in_khz)          
        {
            low_speed_clk_idx--;
            break;
        }
    }
        
#if DSF_RCW_TRAINING_EN
                        
    // Switch to rcw_training_ddr_freq to do RCW training only
    //ddr_external_set_clk_speed (training_freq_table[rcw_training_ddr_freq_index]);
    
    for (ch = 0; ch < NUM_CH; ch++)
    {
        if ((channel >> ch) & 0x1)
        {
            for(cs = 0; cs < NUM_CS; cs++)
            {
                if((qualified_cs >> cs) & 0x1)
                {  
                    ddr_printf(DDR_NORMAL, "START: RCW training on Ch: %u Rank: %u\n", ch, cs);
                    DDRSS_rcw (ddr, 
                               ch, 
                               cs, 
                               dq, 
                               training_params_ptr, 
                               rcw_start_clk_idx, 
                               rcw_clk_idx, 
                               low_speed_clk_idx);
                    ddr_printf(DDR_NORMAL, "END: RCW training on Ch: %u Rank: %u\n", ch, cs);
                }
            }
        }
    }

 #endif  // DSF_RCW_TRAINING_EN
   
    // Increment the training index before the training loop
    training_ddr_freq_indx = training_table_index + 1;
    
    // MAIN LOOP : Train at each frequency in the training_freq_table
    for (ddr_freq_indx = 0;ddr_freq_indx < training_table_index +1; ddr_freq_indx++)
    {		
        //  decrement the index to track the training frequencies from high to low
        training_ddr_freq_indx--;
        
        training_ddr_freq_indx_eq_training_table_index = (training_ddr_freq_indx == training_table_index) ? 1 : 0;
        ddr_printf(DDR_NORMAL, "START: DDR training at freq: %u, PRFS index = %u\n", training_freq_table[training_ddr_freq_indx], training_freq_to_prfs_table_map[training_ddr_freq_indx]);
        
        // Set the clock to the training frequency
        ddr_external_set_clk_speed (training_freq_table[training_ddr_freq_indx]);

        // Train single rank only for 1066MHz and 800MHz frequencies
        if ((training_freq_table[training_ddr_freq_indx] == training_freq_table[0]) || (training_freq_table[training_ddr_freq_indx] == training_freq_table[1]))
        {
            chip_select = DDR_CS0;
        }
        else
        {
            chip_select = qualified_cs;
        }
        
        // Turn on MP_VREFin DQ PHY. DQ needs to be master(bit10 pad_vref_cfg)and ENABLED (LDO bypass in prfs = 1) .
        for (ch = 0; ch < NUM_CH; ch++)
        {
         ca0_ddr_phy_base  = REG_OFFSET_DDR_PHY_CH(ch) + CA0_DDR_PHY_OFFSET;
		 dq0_ddr_phy_base  = REG_OFFSET_DDR_PHY_CH(ch) + DQ0_DDR_PHY_OFFSET;
            if((channel >> ch) & 0x1)
            {
                for(byte_lane = 0; byte_lane < dq; byte_lane++)
                {
                    temp_MPVref_bit[byte_lane] = 0;
					en_dis_WR_fcycle_bit_ca    = 0;
					en_dis_WR_fcycle_bit_dq    = 0;
					
                    if((training_freq_table[training_ddr_freq_indx] <= F_RANGE_4) && 
                       (training_freq_table[training_ddr_freq_indx] >  F_RANGE_3)) 
                    { 
                        temp_MPVref_bit[byte_lane] = HWIO_INX ((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), DDR_PHY_DDRPHY_FPM_PRFS_4_PWRS_1_HI_CFG);
                        temp_MPVref_bit[byte_lane] = (temp_MPVref_bit[byte_lane] | (1 << 21));
                        HWIO_OUTX ((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), DDR_PHY_DDRPHY_FPM_PRFS_4_PWRS_1_HI_CFG, temp_MPVref_bit[byte_lane]);
                    }
                    else if((training_freq_table[training_ddr_freq_indx] <= F_RANGE_5) && 
                            (training_freq_table[training_ddr_freq_indx] >  F_RANGE_4))                    
                    { 
                        temp_MPVref_bit[byte_lane] = HWIO_INX ((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), DDR_PHY_DDRPHY_FPM_PRFS_5_PWRS_1_HI_CFG);
                        temp_MPVref_bit[byte_lane] = (temp_MPVref_bit[byte_lane] | (1 << 21));
                        HWIO_OUTX ((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), DDR_PHY_DDRPHY_FPM_PRFS_5_PWRS_1_HI_CFG, temp_MPVref_bit[byte_lane]);
                    }
                    else if((training_freq_table[training_ddr_freq_indx] <= F_RANGE_6) && 
                            (training_freq_table[training_ddr_freq_indx] >  F_RANGE_5))
                    { 
                        temp_MPVref_bit[byte_lane] = HWIO_INX ((dq0_ddr_phy_base + (byte_lane  * DDR_PHY_OFFSET)), DDR_PHY_DDRPHY_FPM_PRFS_6_PWRS_1_HI_CFG);
                        temp_MPVref_bit[byte_lane] = (temp_MPVref_bit[byte_lane] | (1 << 21));
                        HWIO_OUTX ((dq0_ddr_phy_base + (byte_lane  * DDR_PHY_OFFSET)), DDR_PHY_DDRPHY_FPM_PRFS_6_PWRS_1_HI_CFG, temp_MPVref_bit[byte_lane]);
						//WR_Full cycle Changes
						// De assert Full cycle on DQ, DQS, CA and CK
						//Read DDRPHY_WRLVLEXT_CTL_6_CFG from DQ PHY
						temp_WRLVLEXT_dq = HWIO_INX ((dq0_ddr_phy_base + (byte_lane  * DDR_PHY_OFFSET)), DDR_PHY_DDRPHY_WRLVLEXT_CTL_6_CFG);
						en_dis_WR_fcycle_bit_dq = temp_WRLVLEXT_dq;
						//Clear DQ, DQS full cycle bits
						en_dis_WR_fcycle_bit_dq &= ~(( 0x7 << 2) | (0x7 << 10) | (0x7 << 18) | (0x7 << 26));
						// Write to the register
						HWIO_OUTX ((dq0_ddr_phy_base + (byte_lane  * DDR_PHY_OFFSET)), DDR_PHY_DDRPHY_WRLVLEXT_CTL_6_CFG, en_dis_WR_fcycle_bit_dq);

						//Read DDRPHY_WRLVLEXT_CTL_6_CFG from CA PHY
						temp_WRLVLEXT_ca = HWIO_INX (ca0_ddr_phy_base, DDR_PHY_DDRPHY_WRLVLEXT_CTL_6_CFG);
						en_dis_WR_fcycle_bit_ca = temp_WRLVLEXT_ca;
						//Clear CA, CK full cycle bits
						en_dis_WR_fcycle_bit_ca &= ~((0x7 << 2) | (0x7 << 10) | (0x7 << 18) | (0x7 << 26));
						// Write to the register
						HWIO_OUTX (ca0_ddr_phy_base, DDR_PHY_DDRPHY_WRLVLEXT_CTL_6_CFG, en_dis_WR_fcycle_bit_ca);	
						
						//RCW_Full cycle Changes
						// De assert Full cycle on DQ, DQS, CA and CK
						//Read DDR_PHY_DDRPHY_RCWPREAMBEXT_TOP_6_CFG from DQ PHY
						temp_RCWEXT_dq = HWIO_INX ((dq0_ddr_phy_base + (byte_lane  * DDR_PHY_OFFSET)), DDR_PHY_DDRPHY_RCWPREAMBEXT_TOP_6_CFG);
						en_dis_RCW_fcycle_bit_dq = temp_RCWEXT_dq;
						//Clear DQ, DQS full cycle bits
						en_dis_RCW_fcycle_bit_dq &= ~(( 0x7 << 5) | (0x7 << 13));
						// Write to the register
						HWIO_OUTX ((dq0_ddr_phy_base + (byte_lane  * DDR_PHY_OFFSET)), DDR_PHY_DDRPHY_RCWPREAMBEXT_TOP_6_CFG, en_dis_RCW_fcycle_bit_dq);

						//Read DDR_PHY_DDRPHY_RCWPREAMBEXT_TOP_6_CFG from CA PHY
						temp_RCWEXT_ca = HWIO_INX (ca0_ddr_phy_base, DDR_PHY_DDRPHY_RCWPREAMBEXT_TOP_6_CFG);
						en_dis_RCW_fcycle_bit_ca = temp_RCWEXT_ca;
						//Clear CA, CK full cycle bits
						en_dis_RCW_fcycle_bit_ca &= ~((0x7 << 5) | (0x7 << 13));
						// Write to the register
						HWIO_OUTX (ca0_ddr_phy_base, DDR_PHY_DDRPHY_RCWPREAMBEXT_TOP_6_CFG, en_dis_RCW_fcycle_bit_ca);					
						
					
                    }
                    else if((training_freq_table[training_ddr_freq_indx] <= F_RANGE_7) &&
                            (training_freq_table[training_ddr_freq_indx] >  F_RANGE_6))
                    { 
                        temp_MPVref_bit[byte_lane] = HWIO_INX ((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), DDR_PHY_DDRPHY_FPM_PRFS_7_PWRS_1_HI_CFG);
                        temp_MPVref_bit[byte_lane] = (temp_MPVref_bit[byte_lane] | (1 << 21));
                        HWIO_OUTX ((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), DDR_PHY_DDRPHY_FPM_PRFS_7_PWRS_1_HI_CFG, temp_MPVref_bit[byte_lane]);

						//WR_Full cycle Changes
						// De assert Full cycle on DQ, DQS, CA and CK
						//Read DDRPHY_WRLVLEXT_CTL_7_CFG from DQ PHY
						temp_WRLVLEXT_dq = HWIO_INX ((dq0_ddr_phy_base + (byte_lane  * DDR_PHY_OFFSET)), DDR_PHY_DDRPHY_WRLVLEXT_CTL_7_CFG);
						en_dis_WR_fcycle_bit_dq = temp_WRLVLEXT_dq;
						//Clear DQ, DQS full cycle bits
						en_dis_WR_fcycle_bit_dq &= ~((0x7 << 2) | (0x7 << 10) | (0x7 << 18) | (0x7 << 26));
						// Write to the register
						HWIO_OUTX ((dq0_ddr_phy_base + (byte_lane  * DDR_PHY_OFFSET)), DDR_PHY_DDRPHY_WRLVLEXT_CTL_7_CFG, en_dis_WR_fcycle_bit_dq);

						//Read DDRPHY_WRLVLEXT_CTL_7_CFG from CA PHY
						temp_WRLVLEXT_ca = HWIO_INX (ca0_ddr_phy_base, DDR_PHY_DDRPHY_WRLVLEXT_CTL_7_CFG);
						en_dis_WR_fcycle_bit_ca = temp_WRLVLEXT_ca;
						//Clear CA, CK full cycle bits
						en_dis_WR_fcycle_bit_ca &= ~((0x7 << 2) | (0x7 << 10) | (0x7 << 18) | (0x7 << 26));
						// Write to the register
						HWIO_OUTX (ca0_ddr_phy_base, DDR_PHY_DDRPHY_WRLVLEXT_CTL_7_CFG, en_dis_WR_fcycle_bit_ca);	
						
						//RCW_Full cycle Changes
						// De assert Full cycle on DQ, DQS, CA and CK
						//Read DDR_PHY_DDRPHY_RCWPREAMBEXT_TOP_6_CFG from DQ PHY
						temp_RCWEXT_dq = HWIO_INX ((dq0_ddr_phy_base + (byte_lane  * DDR_PHY_OFFSET)), DDR_PHY_DDRPHY_RCWPREAMBEXT_TOP_7_CFG);
						en_dis_RCW_fcycle_bit_dq = temp_RCWEXT_dq;
						//Clear DQ, DQS full cycle bits
						en_dis_RCW_fcycle_bit_dq &= ~(( 0x7 << 5) | (0x7 << 13));
						// Write to the register
						HWIO_OUTX ((dq0_ddr_phy_base + (byte_lane  * DDR_PHY_OFFSET)), DDR_PHY_DDRPHY_RCWPREAMBEXT_TOP_7_CFG, en_dis_RCW_fcycle_bit_dq);

						//Read DDR_PHY_DDRPHY_RCWPREAMBEXT_TOP_6_CFG from CA PHY
						temp_RCWEXT_ca = HWIO_INX (ca0_ddr_phy_base, DDR_PHY_DDRPHY_RCWPREAMBEXT_TOP_7_CFG);
						en_dis_RCW_fcycle_bit_ca = temp_RCWEXT_ca;
						//Clear CA, CK full cycle bits
						en_dis_RCW_fcycle_bit_ca &= ~((0x7 << 5) | (0x7 << 13));
						// Write to the register
						HWIO_OUTX (ca0_ddr_phy_base, DDR_PHY_DDRPHY_RCWPREAMBEXT_TOP_7_CFG, en_dis_RCW_fcycle_bit_ca);		
											
                    }
                }
            }
        }

#if DSF_PASS_1_DCC_TRAINING_EN 
        //================================================================================================//
        // DCC
        //================================================================================================//
   
        if (training_ddr_freq_indx_eq_training_table_index)
        {
          ddr_printf(DDR_NORMAL, "START: DCC training PASS 1  \n");  

            DDRSS_dcc_boot (ddr, 
                            channel, 
                            DCC_TRAINING_WRLVL_WR90_IO, 
                            training_freq_table[training_ddr_freq_indx]);
          ddr_printf(DDR_NORMAL, "END: DCC training PASS 1  \n");  
        }        
        
#endif// DSF_PASS_1_DCC_TRAINING_EN

   
#if DSF_CA_VREF_TRAINING_EN
//================================================================================================//
// CA-Vref
//================================================================================================//
 
 
        fsp_op = (training_freq_table[training_ddr_freq_indx] > ODT_FSP_EN_FREQ_THRESHOLD) ? 1 : 0 ;
        fsp_wr = (training_freq_table[training_ddr_freq_indx] > ODT_FSP_EN_FREQ_THRESHOLD) ? 1 : 0 ;
        if (training_ddr_freq_indx == training_table_index)
        {
        ddr_printf(DDR_NORMAL, "START: CA Vref training.  \n");
        // Switch to boot freq to do CA Vref training 
        //  ddr_external_set_clk_speed (ddr->misc.clock_plan[low_speed_clk_idx].clk_freq_in_khz);
        
        // Command Bus Training - CBT (CA, CS and Vref)
        for (ch = 0; ch < NUM_CH; ch++)
        {
            reg_offset_ddr_phy = REG_OFFSET_DDR_PHY_CH (ch);
            if((channel >> ch) & 0x1)
            {
        
                // Only train Rank0
                cs = 0;                       
        
                ddr_printf(DDR_NORMAL, "    START: CA Vref training on Ch: %u Rank: %u\n", ch, cs);
     
                tArgs.currentChannel    = ch;
                tArgs.currentChipSelect = cs;
                tArgs.trainingType      = DDR_TRAINING_CACK;
                tArgs.currentFreqIndex  = training_ddr_freq_indx+TRAINING_START_PRFS;
                tArgs.FreqInKhz         = training_freq_table[training_ddr_freq_indx];
        
        
                // PHY CA0 training entry
                DDR_PHY_hal_cfg_ca_vref_dq_out_entry (reg_offset_ddr_phy + DQ0_DDR_PHY_OFFSET);
                DDR_PHY_hal_cfg_ca_vref_dq_in_entry  (reg_offset_ddr_phy + DQ1_DDR_PHY_OFFSET);

        
                //BIMC CA training Entry
                BIMC_CA_Training_Entry (ch, CS_1HOT(cs), fsp_op/*FSP_OP*/);
        
         
                ca_vref_fail_flag = DDRSS_Vrefonly_lpddr4 (ddr,
                                                ch,
                                                cs,
                                                ca,
                                                prfs_index,
                                                training_params_ptr,
                                                (ddrss_ca_vref_local_vars *)local_vars,
                                                training_freq_table[training_ddr_freq_indx]
                                                );
        
        
                BIMC_CA_Training_Exit_CKE_ON (ch, CS_1HOT(cs));
                BIMC_CA_Training_Exit_MR     (ch, CS_1HOT(cs), fsp_op/*FSP_OP*/);
                
                DDR_PHY_hal_cfg_ca_vref_dq_exit (reg_offset_ddr_phy + DQ0_DDR_PHY_OFFSET);
                DDR_PHY_hal_cfg_ca_vref_dq_exit (reg_offset_ddr_phy + DQ1_DDR_PHY_OFFSET);
        
                //copy rank01 to rank 1   
                training_data_ptr->results.ca_vref.range_vref[prfs_index][ch][1][0] = training_data_ptr->results.ca_vref.range_vref[prfs_index][ch][0][0];

                DDRSS_MR_Write_on_die (ddr, ch, 0, JEDEC_MR_12, 
                training_data_ptr->results.ca_vref.range_vref[prfs_index][ch][0][0],0);

                DDRSS_MR_Write_on_die (ddr, ch, 1, JEDEC_MR_12, 
                training_data_ptr->results.ca_vref.range_vref[prfs_index][ch][1][0],0);

                
                ddr_external_send_data_to_ddi(local_vars, LOCAL_VARS_AREA_SIZE, &tArgs, (void*)training_params_ptr);
        
                // Store local vars in flash and zero-initialize for use by the next training function.
                ddr_external_page_to_storage(local_vars, LOCAL_VARS_AREA_SIZE);
        
 #if DSF_CA_VREF_TRAINING_LOG        
                ddr_printf(DDR_NORMAL,"ca_vref.range_vref ch=%x,00 = %x \n",ch, training_data_ptr->results.ca_vref.range_vref[prfs_index][ch][0][0]);
          //      ddr_printf(DDR_NORMAL,"ca_vref.range_vref ch=%x,01 = %x \n",ch, training_data_ptr->results.ca_vref.range_vref[prfs_index][ch][0][1]);
                ddr_printf(DDR_NORMAL,"ca_vref.range_vref ch=%x,10 = %x \n",ch, training_data_ptr->results.ca_vref.range_vref[prfs_index][ch][1][0]);
          //      ddr_printf(DDR_NORMAL,"ca_vref.range_vref ch=%x,11 = %x \n",ch, training_data_ptr->results.ca_vref.range_vref[prfs_index][ch][1][1]);
#endif  // DSF_CA_VREF_TRAINING_LOG
                ddr_printf(DDR_NORMAL, "    END  : CA Vref training on Ch: %u Rank: %u\n", ch, cs);
       
            } // if (ch)
        } // for (ch)
        } // if (training_freq)


        // Restore the clock to the training frequency
        //ddr_external_set_clk_speed (training_freq_table[training_ddr_freq_indx]);

        ddr_printf(DDR_NORMAL, "END: CA training.  \n");     

        if (!ca_vref_fail_flag)  
        {
             ddr_printf(DDR_NORMAL, "FAIL: CA training.  \n");     
        }      

#endif  // DSF_CA_VREF_TRAINING_EN


#if DSF_WR_DQDQS_TRAINING_TDQS2DQ_CAL_EN 
//================================================================================================//
// WR DQDQS Training for band0/1.
//================================================================================================//

		//switch to Low frequency clock
		ddr_external_set_clk_speed (ddr->misc.clock_plan[low_speed_clk_idx].clk_freq_in_khz);

        // Need to do only once at the beginning before any WR is done.
        if (training_ddr_freq_indx_eq_training_table_index)
        {
            for (ch = 0; ch < NUM_CH; ch++)
            {
                dq0_ddr_phy_base  = REG_OFFSET_DDR_PHY_CH(ch) + DQ0_DDR_PHY_OFFSET;
                
                if((channel >> ch) & 0x1)
                {
                    for(cs = 0; cs < NUM_CS; cs++)
                    {
                        if((chip_select >> cs) & 0x1)
                        {
                            // Ensure more setup margin.
                            for(byte_lane = 0; byte_lane < dq; byte_lane++)
                            {
                                // Store the original cdc value.
                                temp_rd_cdc_value[byte_lane] = HWIO_INX((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), DDR_PHY_DDRPHY_CMCDCRD_CTL_CFG);
                                
                                DDR_PHY_hal_cfg_cdc_slave_rd((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), 
                                                            LOW_SPEED_RD_COARSE_CDC_VALUE, 
                                                            0x1,  /*coarse_cdc */ 
                                                            0x1,  /*hp_mode */
                                                            cs);   
                            }
                            
                           // if(cs == 0)
                           // {                            
                                ddr_printf(DDR_NORMAL, "START: DIT runtime calculation on Ch: %u Rank: %u\n", ch, cs);
                                DDRSS_DIT_Runtime(ddr, ch, cs, training_params_ptr,  dit_count,ddr->misc.clock_plan[low_speed_clk_idx].clk_freq_in_khz);
                                ddr_printf(DDR_NORMAL, "END: DIT runtime calculation  Ch: %u Rank: %u\n", ch, cs);
                            
                                ddr_printf(DDR_NORMAL, "START: WR training for band0/1 on Ch: %u Rank: %u\n", ch, cs);
                                DDRSS_wr_dqdqs_lpddr4_tdqs2dq_cal (ddr, 
                                                                ch, 
                                                                cs, 
                                                                dq,
                                                                training_params_ptr, 
                                                                ddr->misc.clock_plan[low_speed_clk_idx].clk_freq_in_khz);
                                ddr_printf(DDR_NORMAL, "END: WR training for band0/1 on Ch: %u Rank: %u\n", ch, cs);
                           // }
                            
                            // Restore the original CDC value.
                            for(byte_lane = 0; byte_lane < dq; byte_lane++)
                            {
                                HWIO_OUTX((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), DDR_PHY_DDRPHY_CMCDCRD_CTL_CFG, temp_rd_cdc_value[byte_lane]);
                            }
                        }
                    } // cs
                }
            } // ch
        }
        // Switch to max freq to do dq-dqs training
        ddr_external_set_clk_speed (training_freq_table[training_ddr_freq_indx]);

#endif  // End of DSF_WR_DQDQS_TRAINING_TDQS2DQ_CAL_EN   


#if DSF_CLK_DCC_RD_DQDQS
//================================================================================================//
// CLK DCC training.
//================================================================================================//
      if (training_ddr_freq_indx_eq_training_table_index)
      {
            ddr_printf(DDR_NORMAL, "START: CLK RD DCC training.  \n");
            // Switch to boot freq to do a low speed memory write to be used for read back during training
            ddr_external_set_clk_speed (ddr->misc.clock_plan[low_speed_clk_idx].clk_freq_in_khz);
        
            // Enable refresh so that memory contents are retained after low speed write
            BIMC_Auto_Refresh_Ctrl (channel, chip_select, FEATURE_ENABLE/*1 for enable*/);
            
            // Memory write at low speed
            for (ch = 0; ch < NUM_CH; ch++)
            {
                if ((channel >> ch) & 0x1)
                {
                    for (cs = 0; cs < NUM_CS; cs++)
                    {
                        if ((chip_select >> cs) & 0x1)
                        {
#if DSF_PXI_TRAINING_EN
                            Initialize_PXI_Tables (ddr, ch, cs, 0, 0); //ch, cs, wr/rd, dbi
              DDRSS_mem_write_PXI (ddr, ch, cs, 0, 1); //ddr, ch, cs, dbi, prbs
#else
                            DDRSS_mem_write (ddr, ch, cs);
#endif
                        }
                    }
                }
            }

        // Switch to max freq to do dq-dqs training
        ddr_external_set_clk_speed (training_freq_table[training_ddr_freq_indx]);
        
            for (ch = 0; ch < NUM_CH; ch++)
            {
                if ((channel >> ch) & 0x1)
                {
                    for (cs = 0; cs < NUM_CS;cs++)
                    {
                        if ((chip_select >> cs) & 0x1)
                        {
                            ddr_printf(DDR_NORMAL, "  CLK DCC training on Ch: %u Rank: %u\n", ch, cs);
                            DDRSS_clk_dcc_rd_dqdqs_schmoo (ddr, 
                                                           ch, 
                                                           cs,  
                                                           ca,
                                                           dq,
                                                           training_params_ptr, 
                                                           (ddrss_rdwr_dqdqs_local_vars *)local_vars, 
                                                           training_freq_table[training_ddr_freq_indx],
                                                           training_ddr_freq_indx_eq_training_table_index);	
                        }
                    }
                }
            }
        }
        
        BIMC_Auto_Refresh_Ctrl (channel, chip_select, FEATURE_DISABLE/*0 for disable*/);  
        
#endif // DSF_RD_DQDQS_DCC


#if DSF_WRLVL_TRAINING_EN
 //================================================================================================//
 // Write Leveling
 // This training needs to be done for NUM_TRAINING_FREQS starting from the max freq.
 //================================================================================================//
        if (training_ddr_freq_indx_eq_training_table_index)
        {
            ddr_printf(DDR_NORMAL, "START: WRLVL training.  \n");
            
			wrlvl_clk_freq_khz = training_freq_table[training_ddr_freq_indx];
            wrlvl_clk_freq_idx = training_freq_to_prfs_table_map[training_ddr_freq_indx];
			//First do WRLVL training at 1017MHz for both CA and DQS, then for DQS only at 1804MHz 
			wrlvl_freq_khz_pass1 = WRLVL_PASS1_FREQ;
            wrlvl_prfs_index_pass1 = WRLVL_PASS1_PRFS_INDEX;			
			ddr_external_set_clk_speed (wrlvl_freq_khz_pass1);         
			
            RL_WL_idx  = BIMC_RL_WL_Freq_Index (ddr, wrlvl_freq_khz_pass1);
            for (ch = 0; ch < NUM_CH; ch++)
            {
              if ((channel >> ch) & 0x1)
              {
                // Enable write leveling in the DRAM using MR2 write
                MR2_wrlvl_opcode = ((1 << 7) | ddr->extended_cdt_runtime.dram_latency[RL_WL_idx].MR2);
                  for (cs = 0; cs <= NUM_CS; cs++)
                  {
                      if ((chip_select >> cs) & 0x1)
                      {
                          BIMC_MR_Write (CH_1HOT(ch), CS_1HOT(cs), JEDEC_MR_2, MR2_wrlvl_opcode);
                          DDRSS_wrlvl_ca (ddr, 
                                          ch, 
                                          cs, 
                                          ca,
                                          dq,
                                          wrlvl_freq_khz_pass1, 
                                          training_params_ptr, 
                                          wrlvl_prfs_index_pass1);
                          BIMC_MR_Write (CH_1HOT(ch), CS_1HOT(cs), JEDEC_MR_2, (ddr->extended_cdt_runtime.dram_latency[RL_WL_idx].MR2));
                      }
                  }  //End of cs loop            
			
			for (cs = 0; cs <= NUM_CS; cs++)
                  {
                      if ((chip_select >> cs) & 0x1)
                      {
                          BIMC_MR_Write (CH_1HOT(ch), CS_1HOT(cs), JEDEC_MR_2, MR2_wrlvl_opcode);    
                          DDRSS_wrlvl (ddr, 
                                       ch, 
                                       cs, 
                                       dq,
                                       ca,
                                       wrlvl_freq_khz_pass1, 
                                       wrlvl_prfs_index_pass1,
                                       training_params_ptr);
                          BIMC_MR_Write (CH_1HOT(ch), CS_1HOT(cs), JEDEC_MR_2, (ddr->extended_cdt_runtime.dram_latency[RL_WL_idx].MR2));
                      }
                  }  //End of cs loop
				}
			}
			//Do WRLVL training for DQS at 1804MHz
			RL_WL_idx  = BIMC_RL_WL_Freq_Index (ddr, wrlvl_clk_freq_khz);
			ddr_external_set_clk_speed (wrlvl_clk_freq_khz);		
            for (ch = 0; ch < NUM_CH; ch++)
            {
              if ((channel >> ch) & 0x1)
              {			
            for (cs = 0; cs <= NUM_CS; cs++)
                  {
                      if ((chip_select >> cs) & 0x1)
                      {
                          BIMC_MR_Write (CH_1HOT(ch), CS_1HOT(cs), JEDEC_MR_2, MR2_wrlvl_opcode);    
                          DDRSS_wrlvl (ddr, 
                                       ch, 
                                       cs, 
                                       dq,
                                       ca,
                                       wrlvl_clk_freq_khz, 
                                       wrlvl_clk_freq_idx, 
                                       training_params_ptr);
                          BIMC_MR_Write (CH_1HOT(ch), CS_1HOT(cs), JEDEC_MR_2, (ddr->extended_cdt_runtime.dram_latency[RL_WL_idx].MR2));
                      }
                  }  //End of cs loop
              }
            }   
            // Disable write leveling in the DRAM using MR2 write
            //BIMC_MR_Write (channel,DDR_CS_BOTH,JEDEC_MR_2,BIMC_RL_WL_Table_Sel(ddr, MR2_WR_VAL, wrlvl_clk_freq_khz));
            ddr_printf(DDR_NORMAL, "END: WRLVL training.  \n");
            
        }
#endif  // DSF_WRLVL_TRAINING_EN


//================================================================================================//
// Read Training (DQ-DQS and RCW)
//================================================================================================//
        // Switch to boot freq to do a low speed memory write to be used for read back during training
        ddr_external_set_clk_speed (ddr->misc.clock_plan[low_speed_clk_idx].clk_freq_in_khz);
    
        // Enable refresh so that memory contents are retained after low speed write
        BIMC_Auto_Refresh_Ctrl (channel, chip_select, FEATURE_ENABLE/*1 for enable*/);
         
        // Memory write at low speed
        for (ch = 0; ch < NUM_CH; ch++)
        {
            if ((channel >> ch) & 0x1)
            {
                for (cs = 0; cs < NUM_CS; cs++)
                {
                    if ((chip_select >> cs) & 0x1)
                    {
#if DSF_PXI_TRAINING_EN
                        Initialize_PXI_Tables (ddr, ch, cs, 0, 0); //ch, cs, wr/rd, dbi
            DDRSS_mem_write_PXI (ddr, ch, cs, 0, 1); //ddr, ch, cs, dbi, prbs
#else
                        DDRSS_mem_write (ddr, ch, cs);
#endif
                    }
                }
            }
        }

        // Switch to max freq to do dq-dqs training
        ddr_external_set_clk_speed (training_freq_table[training_ddr_freq_indx]);
           
#if DSF_RD_DQDQS_TRAINING_EN
        for (ch = 0; ch < NUM_CH; ch++)
        {
            if ((channel >> ch) & 0x1)
            {
#if DSF_RD_DQDQS_DCC 
//================================================================================================//
// Read_DCC at 1866MHz.
//================================================================================================//
                if (training_ddr_freq_indx_eq_training_table_index)
                {   
                  for (cs = 0; cs < NUM_CS;cs++)
                  {
                      if ((chip_select >> cs) & 0x1)
                      {
                          ddr_printf(DDR_NORMAL, "  RD_DCC training on Ch: %u Rank: %u\n", ch, cs);
                          DDRSS_rd_dqdqs_dcc_schmoo (ddr, 
                                                     ch, 
                                                     cs, 
                                                     dq,
                                                     training_params_ptr, 
                                                     (ddrss_rdwr_dqdqs_local_vars *)local_vars, 
                                                     training_freq_table[training_ddr_freq_indx]);      
                      }
                  }
                }
#endif // DSF_RD_DQDQS_DCC

                for (cs = 0; cs < NUM_CS; cs++)
                {
                    if ((chip_select >> cs) & 0x1)
                    {
                        ddr_printf(DDR_NORMAL, "START: Read training on Ch: %u Rank: %u\n", ch, cs);
                        tArgs.currentChannel = ch;
                        tArgs.currentChipSelect = cs;
                        tArgs.trainingType = DDR_TRAINING_READ;
                        tArgs.currentFreqIndex = training_ddr_freq_indx+TRAINING_START_PRFS;
                        tArgs.FreqInKhz = training_freq_table[training_ddr_freq_indx];

                        DDRSS_rd_dqdqs_lpddr4  (ddr, 
                                                ch, 
                                                cs, 
                                                ca,
                                                dq,
                                                training_params_ptr, 
                                                (ddrss_rdwr_dqdqs_local_vars *)local_vars, 
                                                training_freq_table[training_ddr_freq_indx],
                                                prfs_index);
                        ddr_printf(DDR_NORMAL, "END: Read training on Ch: %u Rank: %u\n", ch, cs);
                        ddr_external_send_data_to_ddi(local_vars, LOCAL_VARS_AREA_SIZE, &tArgs, (void*)training_params_ptr);
        
                        // Store local vars in flash and zero-initialize for use by the next training function.
                        ddr_external_page_to_storage(local_vars, LOCAL_VARS_AREA_SIZE);
                    }
                }
            }
        }
        // do a frequency switch to load the trained values
        ddr_external_set_clk_speed (training_freq_table[training_ddr_freq_indx]);
#if DSF_RD_DQDQS_COARSE_FINE_PLOT_PIVOT
        if (training_freq_table[training_ddr_freq_indx] == DSF_RD_DQDQS_COARSE_FINE_PLOT_FREQ)
        {
            DDRSS_rd_dqdqs_coarse_fine_plot_pivot (ddr, 
                                                   "C:\\Temp\\RD_pivot.csv",
                                                   training_params_ptr, 
                                                   training_freq_table[training_ddr_freq_indx]);
          //ddr_abort();
        }
#endif  // DSF_RD_DQDQS_COARSE_FINE_PLOT

#endif  // DSF_RD_DQDQS_TRAINING_EN

#if DSF_PERIODIC_TRAINING_EN
//================================================================================================//
// DIT Training
//================================================================================================//
       if ((training_ddr_freq_indx_eq_training_table_index) && ( prfs_index >= MIN_DTTS_TRACKING_PRFS))
       {
            for (ch = 0; ch < NUM_CH; ch++)
            {
                if((channel >> ch) & 0x1)
                {
                    for(cs = 0; cs < NUM_CS; cs++)
                    {
                        if((chip_select >> cs) & 0x1)
                        {
                            ddr_printf(DDR_NORMAL, "START: DIT pre_wr_dqdqs training on Ch: %u Rank: %u\n", ch, cs);
                            DDRSS_DIT_Read (ddr, 
                                            ch, 
                                            cs, 
                                            training_params_ptr, 
                                            dit_ave, 
                                            dit_count,training_freq_table[training_ddr_freq_indx]);
                            ddr_printf(DDR_NORMAL, "END: DIT pre_wr_dqdqs training on Ch: %u Rank: %u\n", ch, cs);
                        }
                    }
                }
            }
            dit_ave = 1;
            
        }
#endif  // End of DSF_PERIODIC_TRAINING_EN     

#if DSF_WR_DQDQS_TRAINING_EN
//================================================================================================//
// Write DQ-DQS Training
//================================================================================================//
    
       fsp_op = (training_freq_table[training_ddr_freq_indx] > ODT_FSP_EN_FREQ_THRESHOLD) ? 1 : 0 ;
        fsp_wr = (training_freq_table[training_ddr_freq_indx] > ODT_FSP_EN_FREQ_THRESHOLD) ? 1 : 0 ;
        for (ch = 0; ch < NUM_CH; ch++)
        {
            if((channel >> ch) & 0x1)
            {
                for(cs = 0; cs < NUM_CS; cs++)
                {
                    if((chip_select >> cs) & 0x1)
                    {
                        ddr_printf(DDR_NORMAL, "START: Write training on Ch: %u Rank: %u\n", ch, cs);
                        // Enter WR_Training. MR13, VRCG (bit 3) set to high-current mode for WR training.
                        high_current_mode = 1; 
                        MR13_value = (fsp_op << 7) | (fsp_wr << 6) | (0 << 5) | (high_current_mode << 3) | (0 << 2) | (0 << 0);
                     // Satisfy tVRCG_ENABLE=200ns. ROUNDUP(200ns/52ns)=0x4
                        BIMC_Wait_Timer_Setup ((DDR_CHANNEL)CH_1HOT(ch), WAIT_XO_CLOCK, 0x04);
                        
                        BIMC_MR_Write (CH_1HOT(ch), CS_1HOT(cs), JEDEC_MR_13, MR13_value);
                        
                        // Reset manual_1 timer
                        BIMC_Wait_Timer_Setup ((DDR_CHANNEL)CH_1HOT(ch), WAIT_XO_CLOCK, 0x00);
                        tArgs.currentChannel = ch;
                        tArgs.currentChipSelect = cs;
                        tArgs.trainingType = DDR_TRAINING_WRITE;
                        tArgs.currentFreqIndex = training_ddr_freq_indx+TRAINING_START_PRFS;
                        tArgs.FreqInKhz = training_freq_table[training_ddr_freq_indx];
                        
                        DDRSS_wr_dqdqs_lpddr4 (ddr, 
                                               ch, 
                                               cs, 
                                               dq,
                                               training_params_ptr, 
                                               (ddrss_rdwr_dqdqs_local_vars *)local_vars, 
                                               training_freq_table[training_ddr_freq_indx], 
                                               prfs_index);
                        
                        // Exit WR Training. MR13. (VRCG, bit 3 = 0, normal current mode).
                        high_current_mode = 0;
                        MR13_value = (fsp_op << 7) | (fsp_wr << 6) | (0 << 5) | (high_current_mode << 3) | (0 << 2) | (0 << 0);
                       // Satisfy tVRCG_ENABLE=200ns. ROUNDUP(200ns/52ns)=0x4
                        BIMC_Wait_Timer_Setup ((DDR_CHANNEL)CH_1HOT(ch), WAIT_XO_CLOCK, 0x04);
                        
                        BIMC_MR_Write (CH_1HOT(ch), CS_1HOT(cs), JEDEC_MR_13, MR13_value);
                        
                        // Reset manual_1 timer
                        BIMC_Wait_Timer_Setup ((DDR_CHANNEL)CH_1HOT(ch), WAIT_XO_CLOCK, 0x00);
                        ddr_printf(DDR_NORMAL, "END: Write training on Ch: %u Rank: %u\n", ch, cs);
                        ddr_external_send_data_to_ddi(local_vars, LOCAL_VARS_AREA_SIZE, &tArgs, (void*)training_params_ptr);
                        
                        // Store local vars in flash and zero-initialize for use by the next training function.
                        ddr_external_page_to_storage(local_vars, LOCAL_VARS_AREA_SIZE);
                    }
                }
            }
        }
        
#if DSF_WR_DQDQS_COARSE_FINE_PLOT
        if (training_freq_table[training_ddr_freq_indx] == DSF_WR_DQDQS_COARSE_FINE_PLOT_FREQ)
        {
            DDRSS_wr_dqdqs_coarse_fine_plot (ddr, training_params_ptr, training_freq_table[training_ddr_freq_indx]);
            ddr_abort();
        }
#endif  // DSF_WR_DQDQS_COARSE_FINE_PLOT

#if DSF_WR_DQDQS_COARSE_FINE_PLOT_PIVOT
        if (training_freq_table[training_ddr_freq_indx] == DSF_WR_DQDQS_COARSE_FINE_PLOT_FREQ)
        {
            DDRSS_wr_dqdqs_coarse_fine_plot_pivot (ddr, 
                                                   "C:\\Temp\\WR_pivot.csv",
                                                   training_params_ptr, 
                                                   training_freq_table[training_ddr_freq_indx]);
          //ddr_abort();
        }
#endif  // DSF_WR_DQDQS_COARSE_FINE_PLOT

#endif  // DSF_WR_DQDQS_TRAINING_EN


#if DSF_PERIODIC_TRAINING_EN
//================================================================================================//
// DIT Training
//================================================================================================//

        // Capture DIT for the highest two training frequencies
        if ((training_ddr_freq_indx_eq_training_table_index) && ( prfs_index >= MIN_DTTS_TRACKING_PRFS))
        {
            // Write the DIT capture frequency in to the data structure
            training_data_ptr->results.dit.dit_training_freq = training_freq_table[training_ddr_freq_indx] ;
            
            for (ch = 0; ch < NUM_CH; ch++)
            {
                if((channel >> ch) & 0x1)
                {
                    for(cs = 0; cs < NUM_CS; cs++)
                    {
                        if((chip_select >> cs) & 0x1)
                        {                                                                    
                            ddr_printf(DDR_NORMAL, "START: DIT post_wr_dqdqs training on Ch: %u Rank: %u\n", ch, cs);
                            DDRSS_DIT_Read (ddr, 
                                            ch, 
                                            cs, 
                                            training_params_ptr, 
                                            dit_ave, 
                                            dit_count,
                                            training_freq_table[training_ddr_freq_indx]);
                
                            // Store the DIT count in the data structure
                           // for (die=0;die<=1;die++) 
                           // {
                                training_data_ptr->results.dit.dit_count[ch][cs][0] = dit_count[ch][cs][0];
                           // }
                
                            ddr_printf(DDR_NORMAL, "END: DIT post_wr_dqdqs training on Ch: %u Rank: %u\n", ch, cs);
                        }
                    }
                }
            }
        }
#endif  // End of DSF_PERIODIC_TRAINING_EN    

        // Disable Auto refresh at the beginning of training of each frequency
        BIMC_Auto_Refresh_Ctrl (channel, chip_select, FEATURE_DISABLE/*0 for disable*/);        

        // Put back the passed in chip_select saved at the beginning    
        chip_select = qualified_cs;   
        ddr_printf(DDR_NORMAL, " END:   DDR training at freq: %u\n", training_freq_table[training_ddr_freq_indx]);
        
//================================================================================================//        
        // Restore MPVref
        for (ch = 0; ch < NUM_CH; ch++)
        {
            ca0_ddr_phy_base  = REG_OFFSET_DDR_PHY_CH(ch) + CA0_DDR_PHY_OFFSET;
            dq0_ddr_phy_base  = REG_OFFSET_DDR_PHY_CH(ch) + DQ0_DDR_PHY_OFFSET;
            if((channel >> ch) & 0x1)
            {
                for(byte_lane = 0; byte_lane < dq; byte_lane++)
                {
                    // Restore the MPVref bit.
                    if((training_freq_table[training_ddr_freq_indx] <= F_RANGE_4) && 
                       (training_freq_table[training_ddr_freq_indx] >  F_RANGE_3)) 
                    {            
                        temp_MPVref_bit[byte_lane] = HWIO_INX ((dq0_ddr_phy_base + (byte_lane* DDR_PHY_OFFSET)), DDR_PHY_DDRPHY_FPM_PRFS_4_PWRS_1_HI_CFG);
                        temp_MPVref_bit[byte_lane] = (temp_MPVref_bit[byte_lane] & 0xFFDFFFFF); // zero out bit 21.
                        HWIO_OUTX ((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), DDR_PHY_DDRPHY_FPM_PRFS_4_PWRS_1_HI_CFG, temp_MPVref_bit[byte_lane]);
                    }

                    else if((training_freq_table[training_ddr_freq_indx] <= F_RANGE_5) && 
                            (training_freq_table[training_ddr_freq_indx] >  F_RANGE_4))
                    {            
                        temp_MPVref_bit[byte_lane] = HWIO_INX ((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), DDR_PHY_DDRPHY_FPM_PRFS_5_PWRS_1_HI_CFG);
                        temp_MPVref_bit[byte_lane] = (temp_MPVref_bit[byte_lane] & 0xFFDFFFFF);
                        HWIO_OUTX ((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), DDR_PHY_DDRPHY_FPM_PRFS_5_PWRS_1_HI_CFG, temp_MPVref_bit[byte_lane]);
                    }

                    else if((training_freq_table[training_ddr_freq_indx] <= F_RANGE_6) && 
                            (training_freq_table[training_ddr_freq_indx] >  F_RANGE_5))
                    {            
                        temp_MPVref_bit[byte_lane] = HWIO_INX ((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), DDR_PHY_DDRPHY_FPM_PRFS_6_PWRS_1_HI_CFG);
                        temp_MPVref_bit[byte_lane] = (temp_MPVref_bit[byte_lane] & 0xFFDFFFFF);
                        HWIO_OUTX ((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), DDR_PHY_DDRPHY_FPM_PRFS_6_PWRS_1_HI_CFG, temp_MPVref_bit[byte_lane]);
						
						//WR_Full cycle Changes
						// assert Full cycle on DQ, DQS, CA and CK
						//Read DDRPHY_WRLVLEXT_CTL_6_CFG from DQ PHY
						training_data_ptr->results.wr_dqdqs.dq_full_cycle[6][ch][0][byte_lane] += 1;
						training_data_ptr->results.wr_dqdqs.dq_full_cycle[6][ch][1][byte_lane] += 1;
						temp_WRLVLEXT_dq = HWIO_INX ((dq0_ddr_phy_base + (byte_lane  * DDR_PHY_OFFSET)), DDR_PHY_DDRPHY_WRLVLEXT_CTL_6_CFG);
						en_dis_WR_fcycle_bit_dq = temp_WRLVLEXT_dq;
						en_dis_WR_fcycle_bit_dq &= ~((0x7 << 2) | (0x7 << 10) | (0x7 << 18) | (0x7 << 26));
						for (fcycle_ind = 0 ; fcycle_ind < 4; fcycle_ind++)
						{
						//Add 1 to trained DQ and DQS full cycles
							en_dis_WR_fcycle_bit_dq |= ((temp_WRLVLEXT_dq & (0x7 << fcycle_bfields[fcycle_ind])) + (1 << fcycle_bfields[fcycle_ind])) ;
						
						}
//						//Set DQ, DQS full cycle bits
//						en_dis_WR_fcycle_bit_dq |= ((1<<2) | (1 << 10) | (1 << 18) | (1 << 26));
						// Write to the register
						HWIO_OUTX ((dq0_ddr_phy_base + (byte_lane  * DDR_PHY_OFFSET)), DDR_PHY_DDRPHY_WRLVLEXT_CTL_6_CFG, en_dis_WR_fcycle_bit_dq);
						if (byte_lane == 0)
						{
						//Read DDRPHY_WRLVLEXT_CTL_6_CFG from CA PHY
						  temp_WRLVLEXT_ca = HWIO_INX (ca0_ddr_phy_base, DDR_PHY_DDRPHY_WRLVLEXT_CTL_6_CFG);
						  en_dis_WR_fcycle_bit_ca = temp_WRLVLEXT_ca;
						  en_dis_WR_fcycle_bit_ca &= ~((0x7 << 2) | (0x7 << 10) | (0x7 << 18) | (0x7 << 26));
						  for (fcycle_ind = 0 ; fcycle_ind < 4; fcycle_ind++)
						  {
						//Add 1 to trained CA and CK full cycles
							en_dis_WR_fcycle_bit_ca |= ((temp_WRLVLEXT_ca & (0x7 << fcycle_bfields[fcycle_ind])) + (1 << fcycle_bfields[fcycle_ind])) ;
						  }

						// Write to the register
						  HWIO_OUTX (ca0_ddr_phy_base, DDR_PHY_DDRPHY_WRLVLEXT_CTL_6_CFG, en_dis_WR_fcycle_bit_ca);							
						}
						
						//RCW_Full cycle Changes
						// assert Full cycle on DQ and CA 
						//Read DDRPHY_RCWEXT_CTL_7_CFG from DQ PHY
						temp_RCWEXT_dq = HWIO_INX ((dq0_ddr_phy_base + (byte_lane  * DDR_PHY_OFFSET)), DDR_PHY_DDRPHY_RCWPREAMBEXT_TOP_6_CFG);
						en_dis_RCW_fcycle_bit_dq = temp_RCWEXT_dq;
						en_dis_RCW_fcycle_bit_dq &= ~((0x7 << 5) | (0x7 << 13));
						for (fcycle_ind = 0 ; fcycle_ind < 2; fcycle_ind++)
						{
						//Add 1 to trained DQ and DQS full cycles
							en_dis_RCW_fcycle_bit_dq |= ((temp_RCWEXT_dq & (0x7 << fcycle_bfields_rcw[fcycle_ind])) + (1 << fcycle_bfields_rcw[fcycle_ind])) ;
						
						}
//						//Set DQ full cycle bits
//						en_dis_RCW_fcycle_bit_dq |= ((1<<5) | (1 << 13)) ;
						// Write to the register
						HWIO_OUTX ((dq0_ddr_phy_base + (byte_lane  * DDR_PHY_OFFSET)), DDR_PHY_DDRPHY_RCWPREAMBEXT_TOP_6_CFG, en_dis_RCW_fcycle_bit_dq);
						if (byte_lane == 0)
						{
						//Read DDRPHY_RCWEXT_CTL_7_CFG from CA PHY
						  temp_RCWEXT_ca = HWIO_INX (ca0_ddr_phy_base, DDR_PHY_DDRPHY_RCWPREAMBEXT_TOP_6_CFG);
						  en_dis_RCW_fcycle_bit_ca = temp_RCWEXT_ca;
						  en_dis_RCW_fcycle_bit_ca &= ~((0x7 << 5) | (0x7 << 13));
						  for (fcycle_ind = 0 ; fcycle_ind < 2; fcycle_ind++)
						  {
						//Add 1 to trained CA and CK full cycles
							en_dis_RCW_fcycle_bit_ca |= ((temp_WRLVLEXT_ca & (0x7 << fcycle_bfields_rcw[fcycle_ind])) + (1 << fcycle_bfields_rcw[fcycle_ind])) ;
						  }

						// Write to the register
						  HWIO_OUTX (ca0_ddr_phy_base, DDR_PHY_DDRPHY_RCWPREAMBEXT_TOP_6_CFG, en_dis_RCW_fcycle_bit_ca);							
										
						}	
                    }
                    else if((training_freq_table[training_ddr_freq_indx] <= F_RANGE_7) && 
                            (training_freq_table[training_ddr_freq_indx] >  F_RANGE_6))
                    {            
                        temp_MPVref_bit[byte_lane] = HWIO_INX ((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), DDR_PHY_DDRPHY_FPM_PRFS_7_PWRS_1_HI_CFG);
                        temp_MPVref_bit[byte_lane] = (temp_MPVref_bit[byte_lane] & 0xFFDFFFFF);
                        HWIO_OUTX ((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), DDR_PHY_DDRPHY_FPM_PRFS_7_PWRS_1_HI_CFG, temp_MPVref_bit[byte_lane]);
						//WR_Full cycle Changes
						// assert Full cycle on DQ, DQS, CA and CK
						//Read DDRPHY_WRLVLEXT_CTL_7_CFG from DQ PHY
						training_data_ptr->results.wr_dqdqs.dq_full_cycle[7][ch][0][byte_lane] += 1;
						training_data_ptr->results.wr_dqdqs.dq_full_cycle[7][ch][1][byte_lane] += 1;
						temp_WRLVLEXT_dq = HWIO_INX ((dq0_ddr_phy_base + (byte_lane  * DDR_PHY_OFFSET)), DDR_PHY_DDRPHY_WRLVLEXT_CTL_7_CFG);
						en_dis_WR_fcycle_bit_dq = temp_WRLVLEXT_dq;
						en_dis_WR_fcycle_bit_dq &= ~((0x7 << 2) | (0x7 << 10) | (0x7 << 18) | (0x7 << 26));
						for (fcycle_ind = 0 ; fcycle_ind < 4; fcycle_ind++)
						{
						//Add 1 to trained DQ and DQS full cycles
					
						en_dis_WR_fcycle_bit_dq |= ((temp_WRLVLEXT_dq & (0x7 << fcycle_bfields[fcycle_ind])) + (1 << fcycle_bfields[fcycle_ind])) ;
					
						}
						// Write to the register
						HWIO_OUTX ((dq0_ddr_phy_base + (byte_lane  * DDR_PHY_OFFSET)), DDR_PHY_DDRPHY_WRLVLEXT_CTL_7_CFG, en_dis_WR_fcycle_bit_dq);

						if (byte_lane == 0)
						{
						//Read DDRPHY_WRLVLEXT_CTL_7_CFG from CA PHY
						  temp_WRLVLEXT_ca = HWIO_INX (ca0_ddr_phy_base, DDR_PHY_DDRPHY_WRLVLEXT_CTL_7_CFG);
						  en_dis_WR_fcycle_bit_ca = temp_WRLVLEXT_ca;
						  en_dis_WR_fcycle_bit_ca &= ~((0x7 << 2) | (0x7 << 10) | (0x7 << 18) | (0x7 << 26));
						  for (fcycle_ind = 0 ; fcycle_ind < 4; fcycle_ind++)
						  {
						//Add 1 to trained CA and CK full cycles
							en_dis_WR_fcycle_bit_ca |= ((temp_WRLVLEXT_ca & (0x7 << fcycle_bfields[fcycle_ind])) + (1 << fcycle_bfields[fcycle_ind])) ;
						  }

						// Write to the register
						  HWIO_OUTX (ca0_ddr_phy_base, DDR_PHY_DDRPHY_WRLVLEXT_CTL_7_CFG, en_dis_WR_fcycle_bit_ca);							
						}	
						
						//RCW_Full cycle Changes
						// assert Full cycle on DQ and CA 
						//Read DDRPHY_RCWEXT_CTL_7_CFG from DQ PHY
						temp_RCWEXT_dq = HWIO_INX ((dq0_ddr_phy_base + (byte_lane  * DDR_PHY_OFFSET)), DDR_PHY_DDRPHY_RCWPREAMBEXT_TOP_7_CFG);
						en_dis_RCW_fcycle_bit_dq = temp_RCWEXT_dq;
						en_dis_RCW_fcycle_bit_dq &= ~((0x7 << 5) | (0x7 << 13));
						for (fcycle_ind = 0 ; fcycle_ind < 2; fcycle_ind++)
						{
						//Add 1 to trained DQ and DQS full cycles
							en_dis_RCW_fcycle_bit_dq |= ((temp_RCWEXT_dq & (0x7 << fcycle_bfields_rcw[fcycle_ind])) + (1 << fcycle_bfields_rcw[fcycle_ind])) ;
						
						}
//						//Set DQ full cycle bits
//						en_dis_RCW_fcycle_bit_dq |= ((1<<5) | (1 << 13)) ;
						// Write to the register
						HWIO_OUTX ((dq0_ddr_phy_base + (byte_lane  * DDR_PHY_OFFSET)), DDR_PHY_DDRPHY_RCWPREAMBEXT_TOP_7_CFG, en_dis_RCW_fcycle_bit_dq);
						if (byte_lane == 0)
						{
						//Read DDRPHY_RCWEXT_CTL_7_CFG from CA PHY
						  temp_RCWEXT_ca = HWIO_INX (ca0_ddr_phy_base, DDR_PHY_DDRPHY_RCWPREAMBEXT_TOP_7_CFG);
						  en_dis_RCW_fcycle_bit_ca = temp_RCWEXT_ca;
						  en_dis_RCW_fcycle_bit_ca &= ~((0x7 << 5) | (0x7 << 13));
						  for (fcycle_ind = 0 ; fcycle_ind < 2; fcycle_ind++)
						  {
						//Add 1 to trained CA and CK full cycles
							en_dis_RCW_fcycle_bit_ca |= ((temp_WRLVLEXT_ca & (0x7 << fcycle_bfields_rcw[fcycle_ind])) + (1 << fcycle_bfields_rcw[fcycle_ind])) ;
						  }

						// Write to the register
						  HWIO_OUTX (ca0_ddr_phy_base, DDR_PHY_DDRPHY_RCWPREAMBEXT_TOP_7_CFG, en_dis_RCW_fcycle_bit_ca);							
										
						}						
                    }
                }
            }
        }
   
    } // end of freq loop.
    

//================================================================================================//
// Post training cleanup
//================================================================================================//
#if DSF_PXI_TRAINING_EN
    // Workaround for corrupt data during first read after training with PXI generated traffic
    
    // Channel 0
    pxi_addr = ((ddr->ddr_size_info.ddr0_cs0_remapped_addr) + TRAINING_BASE_ADDRESS_OFFSET);
    pxi_ptr = 0;
    pxi_ptr += (pxi_addr / sizeof(uint32)); // Workaround for compiler error (integer to pointer conversion)
    pxi_data = *pxi_ptr; // Workaround for actual issue
    *pxi_ptr = pxi_data; // Workaround for compiler error (not using pxi_data)
    
    // Channel 1
    pxi_addr = ((ddr->ddr_size_info.ddr1_cs0_remapped_addr + TRAINING_BASE_ADDRESS_OFFSET +
                ((ddr->detected_ddr_device[0].interleave_en & DDR_CS0_INTERLEAVE) ?
                TRAINING_INTERLEAVE_ADDRESS_OFFSET : 0)));
    pxi_ptr = 0;
    pxi_ptr += (pxi_addr / sizeof(uint32)); // Workaround for compiler error (integer to pointer conversion)
    pxi_data = *pxi_ptr; // Workaround for actual issue
    *pxi_ptr = pxi_data; // Workaround for compiler error (not using pxi_data)
#endif

    for (ch = 0; ch < NUM_CH; ch++)
    {
        reg_offset_dpe = REG_OFFSET_DPE(ch);
        dq0_ddr_phy_base  = REG_OFFSET_DDR_PHY_CH(ch) + DQ0_DDR_PHY_OFFSET;
        //ca0_ddr_phy_base  = REG_OFFSET_DDR_PHY_CH(ch) + CA0_DDR_PHY_OFFSET;        
        
        if ((channel >> ch) & 0x1)
        {
            // Enable all periodic functions: auto refresh, hw self refresh, periodic ZQCAL, periodic SRR
            BIMC_All_Periodic_Ctrl (ddr, CH_1HOT(ch), (DDR_CHIPSELECT)ddr->detected_ddr_device[ch].populated_chipselect, FEATURE_ENABLE/*1 for enable*/);

            // Enable Power Down
            HWIO_OUTXF2 (reg_offset_dpe, DPE_PWR_CTRL_0, PWR_DN_EN, CLK_STOP_PWR_DN_EN, 0x1, 0x1);
            
            HWIO_OUTXF  (reg_offset_dpe, DPE_CONFIG_4, LOAD_ALL_CONFIG, 0x1);

            //Disable DM RX to save power       
            //for(byte_lane = 0; byte_lane < NUM_DQ_PCH; byte_lane++)
            //{
            //    HWIO_OUTX ((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), DDR_PHY_DDRPHY_CMIO_PAD_MODE_CFG, 0x220);
            //    HWIO_OUTX ((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), DDR_PHY_DDRPHY_CMIO_PAD_OE_CFG, 0x200);
            //    HWIO_OUTX ((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), DDR_PHY_DDRPHY_CMIO_PAD_IE_CFG, 0x0);
            //} 

            // Restore the traffic_cfg registers after training
      // Restore the wrlvl_mode_cfg registers after training
            // Restore the pad_mode_cfg registers after training
/*            for (byte_lane=0;byte_lane<dq;byte_lane++)
            {
               HWIO_OUTX(dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET),DDR_PHY_DDRPHY_CMCDCWR_TRAFFIC_BYP_CFG,cmcdcwr_traffic_byp_cfg_dq[ch][byte_lane]);
         HWIO_OUTX(dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET),DDR_PHY_DDRPHY_CMCDCWRLVL_MODE_CFG,cmcdcwrlvl_mode_cfg_dq[ch][byte_lane]);// WRLVL CGC CTL = 1  enable WRLVL cgc to follow traffic signal 
               HWIO_OUTX(dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET),DDR_PHY_DDRPHY_CMIO_PAD_MODE_CFG,cmio_pad_mode_cfg_dq[ch][byte_lane]);
            }
            for (ca_lane=0;ca_lane<ca;ca_lane++)
            {
              HWIO_OUTX(ca0_ddr_phy_base + (ca_lane * DDR_PHY_OFFSET),DDR_PHY_DDRPHY_CMCDCWR_TRAFFIC_BYP_CFG,cmcdcwr_traffic_byp_cfg_ca[ch][ca_lane]);
        HWIO_OUTX(ca0_ddr_phy_base + (ca_lane * DDR_PHY_OFFSET),DDR_PHY_DDRPHY_CMCDCWRLVL_MODE_CFG,cmcdcwrlvl_mode_cfg_ca[ch][ca_lane]);// WRLVL CGC CTL = 1  enable WRLVL cgc to follow traffic signal 
              HWIO_OUTX(ca0_ddr_phy_base + (ca_lane * DDR_PHY_OFFSET),DDR_PHY_DDRPHY_CMIO_PAD_MODE_CFG,cmio_pad_mode_cfg_ca[ch][ca_lane]);
            }*/
        }
    }
    
    return TRUE;
    
}  // END of DDRSS_boot_training.


