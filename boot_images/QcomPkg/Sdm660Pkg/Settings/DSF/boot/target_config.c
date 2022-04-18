/****************************************************************************
 QUALCOMM Proprietary Design Data
 Copyright (c) 2015, Qualcomm Technologies Incorporated. All rights reserved.
 ****************************************************************************/
/*==============================================================================
                                EDIT HISTORY

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Settings/DSF/boot/target_config.c#13 $
$DateTime: 2018/01/31 04:21:03 $
$Author: pwbldsvc $
================================================================================
when       who          what, where, why
--------   ---          --------------------------------------------------------
05/11/14   arindamm     Initial creation for 8994 V1-only code.
================================================================================*/

#include "ddrss.h"
#include "target_config.h"
#ifdef SVE_ENABLE
	#include "math.h"
#else 
	#include "math.h"
	#include "tgmath.h"
#endif
// Numbers used in calculating PLL fractional-divider ratios
#define TWO_TO_THE_18TH  ((double) 262144.0)  // Like it says on the box.
#define VCO_MIN_IN_KHZ 1000000


// =============================================================================
// Bit-byte remapping per the bump map. 
// =============================================================================

const uint8 dq_dbi_bit    = 7;
const uint8 dq_spare_bit  = 9;

#define DQ_DBI_BIT     0xFF
#define DQ_SPARE_BIT   0x1F
#define CA_SPARE_BIT   0x1F

uint8  bit_remapping_phy2bimc_DQ[NUM_CH][NUM_DQ_PCH][PINS_PER_PHY] = {
       {//channel 0
         //0  1  2  3  4  5  6  7           8 9
         { 2, 1, 3, 0, 4, 6, 5, DQ_DBI_BIT, 7, DQ_SPARE_BIT}, //byte0
         { 2, 1, 3, 0, 4, 6, 5, DQ_DBI_BIT, 7, DQ_SPARE_BIT}  //byte1
       }, 
       {//channel 1
         //0  1  2  3  4  5  6  7           8 9 
         { 2, 1, 3, 0, 4, 6, 5, DQ_DBI_BIT, 7, DQ_SPARE_BIT}, //byte0
         { 2, 1, 3, 0, 4, 6, 5, DQ_DBI_BIT, 7, DQ_SPARE_BIT}  //byte1
       }
       
       };
//                                   2      2           8
uint8  bit_remapping_bimc2phy_DQ[NUM_CH][NUM_DQ_PCH][PINS_PER_PHY_CONNECTED_NO_DBI] = {
       {//channel 0
       //  0  1  2  3  4  5  6  7
         { 3, 1, 0, 2, 4, 6, 5, 8}, //byte0
         { 3, 1, 0, 2, 4, 6, 5, 8}  //byte1
       },
       {//channel 1
       //  0  1  2  3  4  5  6  7
         { 3, 1, 0, 2, 4, 6, 5, 8}, //byte0
         { 3, 1, 0, 2, 4, 6, 5, 8}  //byte1
       }

       };

uint8  bit_remapping_bimc2phy_CA[NUM_CH][NUM_CA_PHY_BIT] = {
      //channel 0
      //0  1  2  3  4  5  
      { 8, 5, 2, 0, 1, 3}, //ch0, bit

      //channel 1
      
	  //0  1  2  3	4  5  
	  { 8, 5, 2, 0, 1, 3} //ch1, bit
      
    
     };

uint8  bit_remapping_phy2bimc_CA[NUM_CH][PINS_PER_PHY] = {
      //channel 0
      //channel 0
      //0  1  2  3  4  5  6  7  8  9
      { 3, 4, 2, 5, CA_SPARE_BIT, 1, CA_SPARE_BIT, CA_SPARE_BIT, 0, CA_SPARE_BIT}, //ch0, bit

      //channel 1
      //0  1  2  3  4  5  6  7  8  9
      { 3, 4, 2, 5, CA_SPARE_BIT, 1, CA_SPARE_BIT, CA_SPARE_BIT, 0, CA_SPARE_BIT}, //ch0, bit    
     }; 

uint8 byte_remapping_table [NUM_CH][NUM_DQ_PCH] = {{0, 1}, {0, 1}};

 
uint8 connected_bit_mapping_no_DBI_A [PINS_PER_PHY_CONNECTED_NO_DBI]     = {0, 1, 2, 3, 4, 5, 6, 8   }; // These PHY DQ pads are connected to BIMC DQ pads
uint8 connected_bit_mapping_with_DBI_A [PINS_PER_PHY_CONNECTED_WITH_DBI] = {0, 1, 2, 3, 4, 5, 6, 7, 8}; // PHY DQ[7] is DBI
uint8 connected_bit_mapping_CA [PINS_PER_PHY_CONNECTED_CA]               = {0, 1, 2, 3, 5, 8}; // These PHY CA pads are connected to BIMC CA pads

            // CA value sent back on DQ pads: CA: {0, 1, 2, 3, 4, 5} = DQ: {8, 9, 10, 11, 12, 13}
uint8 connected_bit_mapping_CA_PHY [PINS_PER_PHY_CONNECTED_CA]           = {0, 1, 2, 3, 4, 6}; //These are the odd DQ byte pads in PHY that contain data sent on the CA bus


// Map for write datapath retimer in DDRCC PLL mode /*values represent t/4 and 3t/4*/
uint32 retimer_map_DDRCC[NUM_DDRCC_RETIMER_FREQ][NUM_RETIMER] = 
{
    { 681600, 367, 1100}, // 1878},
    { 768000, 326,  977}, // 1818},
    {1017600, 246,  737}, // 1200}, 
    {1296000, 193,  579}, //  819},
    {1353600, 184,  554}, //  814}, 
    {1555200, 161,  482}, //  774},
    {1804800, 139,  416}  //  668}
};
                  
// Map for write datapath retimer in GCC PLL mode
uint32 retimer_map_GCC[NUM_GCC_RETIMER_FREQ][NUM_RETIMER] = 
{
    {200000, 1250, 3750}, // 3750},
    {412800,  606, 1817}, // 2712},
    {547200,  457, 1371}, // 1818}, 
    {681600,  367, 1100}, // 1740},
    {768000,  326,  977}, // 1740}, 
    {931200,  268,  805}  //  290}
};
// extern struct ecdt_dram_latency_runtime_struct                  RL_WL_lpddr_struct[];
// extern struct ecdt_bimc_frequency_switch_params_runtime_struct  bimc_frequency_switch_params_struct[];

// =============================================================================
// Fill in the ddr->misc.clock_plan[] structure.
// When this function is called, at the beginning of HAL_DDR_Init(), ddr->misc.clock_plan[] should contain an
//    in-order list of valid DDR frequencies.  This function will fill in the rest of the PLL parameters contained in
//    ddr->misc.clock_plan[].
void DDRSS_Copy_Clock_Plan_Struct(DDR_STRUCT *ddr)
{
    uint32 ddr_low_range_array[3] = {1300, 1800, 2300};
	uint32 ddr_high_range_array[3] = {1800, 2300, 2600};
	uint32 ddr_KVCO_code[3] = {8, 12, 15};
	uint32 refclk_dbler_en = 0; //1:doubled refclk frequency 0:normal refclk frequency
	//uint32 fref_in_khz = 19200; 
	float fref = 19200;
	uint32 post_div_factor = 1;
	float fvco = 1804.8;
	float clk_freq_in_mhz;
	uint32 KVCO_code ;
	uint32 dec_start_value ;
	uint32 frac_value;
	uint32 shft_frac_val;
	uint32 div_frac_start3_value ;
	uint32 pll_lock_cmp1 ;
	uint32 pll_lock_cmp2;
	uint32 vco_meas_time = 5; //us per VCO code bit(max:53us, min:0.05us)
	uint32 vco_count1;
	uint32 vco_count2;
	uint32 pll_lpf_res1 = 3;
	uint32 pll_lpf2_postdiv ;
	uint32 KVCO_value=0;
	float pll_lock_cmp_value;
	uint32 vco_count_value;
	//float pll_lpf2_postdiv_flt; 
	double log_factor;
	float pll_lock_cmp_value_rnd;
    uint32 request;
	uint32 max_supported_freq=DSF_MAX_SUPPORTED_DDR_FREQ;

    
/* 
 // Reference table of settings for different legal DDR frequencies.  Generated by 
 
    struct ddr_clock_plan clock_plan[] =
        {       
            // ddr->misc.clock_plan[] fields:
            // 0 - Frequency (in kHz)
            // 1 - GCC/DDRCC mode
            // 2 - DDRCC_RATIO
            // 3 - PLL_PROP_GAIN_RATE_1
            // 4 - PLL_OUTDIV_RATE
            // 5 - PLL_LOCKDET_RATE_1
            // 6 - DECIMAL_DIV_START
            // 7 - FRAC_DIV_START_LOW
            // 8 - FRAC_DIV_START_MID
            // 9 - FRAC_DIV_START_HIGH
            // 10 - RESERVED
            // 11 - RESERVED
            // 12 - RESERVED
            { 100000,  0, 0,   0, 0,   0,  0,   0, 0,  0,  0, 0, 0 },   // clock_plan[ 0] in misc
            { 150000,  0, 0,   0, 0,   0,  0,   0, 0,  0,  0, 0, 0 },   // clock_plan[ 1] in misc
            { 200000,  0, 0,   0, 0,   0,  0,   0, 0,  0,  0, 0, 0 },   // clock_plan[ 2] in misc
            { 300000,  0, 0,   0, 0,   0,  0,   0, 0,  0,  0, 0, 0 },   // clock_plan[ 3] in misc
            { 412800,  0, 0,   0, 0,   0,  0,   0, 0,  0,  0, 0, 0 },   // clock_plan[ 4] in misc
            { 547200,  1, 114, 0, 102, 11, 70,  4, 35, 44, 0, 0, 0 },   // clock_plan[ 5] in misc
            { 681600,  1, 71,  0, 26,  7,  169, 2, 19, 40, 0, 0, 0 },   // clock_plan[ 6] in misc
            { 768000,  1, 80,  0, 0,   8,  0,   3, 19, 40, 0, 0, 0 },   // clock_plan[ 7] in misc
            { 1017600, 1, 106, 0, 154, 10, 249, 3, 19, 44, 0, 0, 0 },   // clock_plan[ 8] in misc
            { 1353600, 1, 70,  8, 13,  7,  164, 2, 3,  40, 0, 0, 0 },   // clock_plan[ 9] in misc
            { 1555200, 1, 81,  0, 26,  8,  9,   3, 3,  40, 0, 0, 0 },   // clock_plan[10] in misc
            { 1804800, 1, 94,  0, 102, 9,  134, 3, 3,  44, 0, 0, 0 },   // clock_plan[11] in misc
            { 1862400, 1, 97,  0, 179, 9,  163, 3, 3,  44, 0, 0, 0 },   // clock_plan[12] in misc
            { 2112000, 1, 110, 0, 0,  11,  32,  4, 3,  44, 0, 0, 0 },   // clock_plan[13] in misc
            { 2112000, 1, 110, 0, 0,  11,  32,  4, 3,  44, 0, 0, 0 }    // clock_plan[14] in misc
        };
*/
    
    for (request = 0; request < MAX_NUM_CLOCK_PLAN; request++)
    {
        // For each requested frequency, calculate the clock_plan parameters

        if (ddr->misc.clock_plan[request].clk_mode != 0)
        {
            // We are in DDRCC mode, so we need to fill in the whole table.
			
			clk_freq_in_mhz = (float)ddr->misc.clock_plan[request].clk_freq_in_khz/1000; // converting the clock frequency to MHz
			
			/*Calculating post divider based on requested frequency*/
			if ((clk_freq_in_mhz >= 1300) && (clk_freq_in_mhz < 2600))
				{
				  post_div_factor = 1;
				}
			else if (((clk_freq_in_mhz*2) >= 1300) && ((clk_freq_in_mhz*2) < 2600))
				{
				  post_div_factor = 2;
				}
			else if (((clk_freq_in_mhz*4) >= 1300) && ((clk_freq_in_mhz*4) < 2600))
				{
				  post_div_factor = 4;
				}
			else if (((clk_freq_in_mhz*8) >= 1300) && ((clk_freq_in_mhz*8) < 2600))
				{
				  post_div_factor = 8;
				}
			else 
				{
				 ddr_printf(DDR_ERROR,"\nCLOCK FREQUENCY OUT OF RANGE!!");
				 ddr_abort();
				}
         
		 
		 
			 /*Calculating the VCO frequency based on requested frequency*/
			fvco = clk_freq_in_mhz * post_div_factor ;	

			/*Selecting the KVCO code */
			if (((clk_freq_in_mhz*post_div_factor) >= ddr_low_range_array[0]) && ((clk_freq_in_mhz*post_div_factor) <= ddr_high_range_array[0]))	
				{
				 KVCO_value = ddr_KVCO_code[0];
				}
			else if (((clk_freq_in_mhz*post_div_factor) > ddr_low_range_array[1]) && ((clk_freq_in_mhz*post_div_factor) <= ddr_high_range_array[1]))	
				{
				 KVCO_value = ddr_KVCO_code[1];
				}
			else if (((clk_freq_in_mhz*post_div_factor) > ddr_low_range_array[2]) && ((clk_freq_in_mhz*post_div_factor) <= ddr_high_range_array[2]))	
				{
				 KVCO_value = ddr_KVCO_code[2];
				}
			else
				{
				 ddr_printf(DDR_ERROR,"\nInvalid KVCO code!!");
				 ddr_abort();
				}
				
			/*Calculating the decimal start value and fractional start value for PLL*/
			dec_start_value = floor(((fvco * 1000)/fref)/(1 + refclk_dbler_en));

			frac_value = 1048576 * ((((fvco * 1000)/fref)/(1 + refclk_dbler_en)) - dec_start_value);
			shft_frac_val = frac_value >> 16 ;

			div_frac_start3_value = shft_frac_val & 0xFF;

			/*Calculating the PLL lock compare values 
			Note: Some of the values in the calculation is hardcoded. May need to be changed based on requirement*/

			pll_lock_cmp_value = 256 * ((float)dec_start_value + ((float)frac_value / 1048576)) / 10;
			pll_lock_cmp_value_rnd = pll_lock_cmp_value * 10;
			
			if ((((int)pll_lock_cmp_value_rnd)%10) < 5)
				{
				  pll_lock_cmp_value = floor(pll_lock_cmp_value);
				}
			else
				{
				  pll_lock_cmp_value = ceil(pll_lock_cmp_value);
				}
				
				
			pll_lock_cmp1 = (int)pll_lock_cmp_value & 0xFF;
			pll_lock_cmp2 = ((int)pll_lock_cmp_value >> 8) & 0xFF;

			/*Calculating the VCO count values 
			Note: Some of the values in the calculation is hardcoded. May need to be changed based on requirement*/

			vco_count_value = floor(vco_meas_time * fvco / 10);
			vco_count1 = vco_count_value & 0xFF;
			vco_count2 = (vco_count_value >> 8) & 0xFF;

			/*Calculates the pll_lpf2_postdiv value for PLL*/
			log_factor = log (post_div_factor)/log (2);
			pll_lpf2_postdiv = (16 * (int)log_factor) + pll_lpf_res1 ;
			
			
			/*calculates the KVCO code value for DDRC PLL*/
			if (((clk_freq_in_mhz*post_div_factor) < ddr_low_range_array[0]) || ((clk_freq_in_mhz*post_div_factor) > ddr_high_range_array[2]))
				{
				  KVCO_code = 0;
				}
			else
				{
				  KVCO_code = 32 + KVCO_value ;
				}
				
				
				
			// update all the calculated PLL params in to the ddr struct
			
			ddr->misc.clock_plan[request].pll_dec_start         =  dec_start_value ;
			ddr->misc.clock_plan[request].pll_div_frac_start3   =  div_frac_start3_value;
			ddr->misc.clock_plan[request].pll_plllock_cmp1      =  pll_lock_cmp1;
			ddr->misc.clock_plan[request].pll_plllock_cmp2      =  pll_lock_cmp2;
			ddr->misc.clock_plan[request].pll_vco_count1        =  vco_count1;
			ddr->misc.clock_plan[request].pll_vco_count2        =  vco_count2;
			ddr->misc.clock_plan[request].pll_pll_lpf2_postdiv  =  pll_lpf2_postdiv;
			ddr->misc.clock_plan[request].pll_kvco_code         =  KVCO_code ;
            ddr->misc.clock_plan[request].clk_ratio = 1;
		}
	}
	
	
	// added on SW team's request to restrict max frequency from outside DSF. 
	
	max_supported_freq = DSF_MAX_SUPPORTED_DDR_FREQ ;
	
	if (ddr->misc.max_ddr_frequency != 0)
	{
	  max_supported_freq = MIN(max_supported_freq,ddr->misc.max_ddr_frequency);
	}
	
	
    // Find the highest valid frequency point (not greater than the max training freq)
    for (request = 0; request < MAX_NUM_CLOCK_PLAN; request++)
    {
        // If this frequency is not greater than the max training freq, count it as a valid level
        ddr->misc.ddr_num_clock_levels = request + 1;

        // If we have reached the max frequency, stop counting.
        if (ddr->misc.clock_plan[request].clk_freq_in_khz >= max_supported_freq) 
        {
            break;
        }
        
        // If the listed frequency is 0 meaning that we have gone through all permissible frequencies), stop counting.
        if (ddr->misc.clock_plan[request].clk_freq_in_khz == 0)
        {
            ddr->misc.ddr_num_clock_levels = request;
            break;
        }
    }
    // Once we have found the max frequency we can use, save it in the ddr_struct.
    ddr->misc.max_ddr_frequency = ddr->misc.clock_plan[ddr->misc.ddr_num_clock_levels-1].clk_freq_in_khz;
}

void DDRSS_Copy_Dram_Latency_Struct(struct ecdt_dram_latency_runtime_struct *source_ptr, struct ecdt_dram_latency_runtime_struct *dest_ptr)
{
    dest_ptr->RL_DBI_Off_x16        = source_ptr->RL_DBI_Off_x16;
    dest_ptr->RL_DBI_On_x16         = source_ptr->RL_DBI_On_x16;
    dest_ptr->RL_DBI_Off_x8         = source_ptr->RL_DBI_Off_x8;
    dest_ptr->RL_DBI_On_x8          = source_ptr->RL_DBI_On_x8;
    dest_ptr->WL                    = source_ptr->WL;
    dest_ptr->MR2                   = source_ptr->MR2;
    dest_ptr->rl_wl_freq_in_kHz     = source_ptr->rl_wl_freq_in_kHz;
}

void DDRSS_Copy_Frequency_Switch_Params_Struct(struct ecdt_bimc_freq_switch_params_runtime_struct *source_ptr, struct ecdt_bimc_freq_switch_params_runtime_struct *dest_ptr)
{
    dest_ptr->rd_dbi                   = source_ptr->rd_dbi;                   
    dest_ptr->odt                      = source_ptr->odt;                      
    dest_ptr->fsp                      = source_ptr->fsp;                      
    dest_ptr->MR1                      = source_ptr->MR1;                      
    dest_ptr->MR3                      = source_ptr->MR3;                      
    dest_ptr->MR11                     = source_ptr->MR11;                     
    dest_ptr->freq_switch_range_in_kHz = source_ptr->freq_switch_range_in_kHz; 
}

void DDRSS_Create_Ecdt_Runtime_Structs(DDR_STRUCT *ddr, EXTENDED_CDT_STRUCT *ecdt)
{

    uint8 runtime_index; 

#if DSF_ECDT_EN
    uint8 ecdt_index;
    if(ecdt != NULL)
    {    
        // Create DRAM latency run-time structures.
        ddr->extended_cdt_runtime.hw_self_refresh_enable[0]   = ecdt->hw_self_refresh_enable[0];
        ddr->extended_cdt_runtime.hw_self_refresh_enable[1]   = ecdt->hw_self_refresh_enable[1];
        ddr->extended_cdt_runtime.MR4_polling_enable       = ecdt->MR4_polling_enable;      
        ddr->extended_cdt_runtime.periodic_training_enable = ecdt->periodic_training_enable;
        ddr->extended_cdt_runtime.page_close_timer         = ecdt->page_close_timer;   
    }
    else
#endif      
    {
        ddr->extended_cdt_runtime.hw_self_refresh_enable[0]   = 1;
        ddr->extended_cdt_runtime.hw_self_refresh_enable[1]   = 1;
        ddr->extended_cdt_runtime.MR4_polling_enable          = 1;      
        ddr->extended_cdt_runtime.periodic_training_enable    = 0;
        ddr->extended_cdt_runtime.page_close_timer            = 256;       
    }
    
    // First copy all elements of default DRAM latency structures into DDR_STRUCT.extended_cdt_runtime.
    for(runtime_index = 0; runtime_index < NUM_ECDT_DRAM_LATENCY_STRUCTS; runtime_index++) 
    {
        DDRSS_Copy_Dram_Latency_Struct(&RL_WL_lpddr_struct[runtime_index], &ddr->extended_cdt_runtime.dram_latency[runtime_index]);
    }
#if DSF_ECDT_EN    
    // Then run thru the ECDT DRAM Latency input structures, and for those which have the apply_override flag set, find which band its
    // frequency falls into from in the default tables (RL_WL_lpddr_struct[]). Then copy the ECDT structure into the same band in the 
    // DDR_STRUCT.extended_cdt_runtime.dram_latency. At the end of this process, the runtime DDR latency structures in DDR_STRUCT will
    // contain structures from the ECDT if they were apply_override'd, or from the default RL_WL_lpddr_struct[] if they were not. Subsequent
    // DSF operations, both boot- and run-time will refer to the runtime structures in DDR_STRUCT, which are visible to both boot code and 
    // run-time code. 
    if(ecdt != NULL)
    {
        for(ecdt_index = 0; ecdt_index < NUM_ECDT_DRAM_LATENCY_STRUCTS; ecdt_index++) 
        {
            if(ecdt->extended_cdt_ecdt.dram_latency[ecdt_index].apply_override == 1)
            {
                runtime_index = BIMC_RL_WL_Freq_Index(ddr, ecdt->extended_cdt_ecdt.dram_latency[ecdt_index].dram_latency.rl_wl_freq_in_kHz);
                if(runtime_index >= NUM_ECDT_DRAM_LATENCY_STRUCTS)
                {
                    ddr_printf(DDR_ERROR, "Error: ECDT DRAM latency structure: Frequency out of limits: %uMHz\n\n", 
                                            ecdt->extended_cdt_ecdt.dram_latency[ecdt_index].dram_latency.rl_wl_freq_in_kHz);
                }
                else
                {
                    DDRSS_Copy_Dram_Latency_Struct(&ecdt->extended_cdt_ecdt.dram_latency[ecdt_index].dram_latency, 
                                                &ddr->extended_cdt_runtime.dram_latency[runtime_index]);
                }
            }
        }
    }
#endif
    // Create frequency switch parameter run-time structures.
    // First copy all elements of default DRAM frequency switch parameter structures into DDR_STRUCT.extended_cdt_runtime.bimc_freq_switch[].
    for(runtime_index = 0; runtime_index < NUM_ECDT_FREQ_SWITCH_STRUCTS; runtime_index++) 
    {
        if (ddr->detected_ddr_device[0].device_type == DDR_TYPE_LPDDR4X)
        {
            DDRSS_Copy_Frequency_Switch_Params_Struct(&bimc_freq_switch_params_struct_lp4x[runtime_index], &ddr->extended_cdt_runtime.bimc_freq_switch[runtime_index]);
        }
        else
        {
            DDRSS_Copy_Frequency_Switch_Params_Struct(&bimc_freq_switch_params_struct[runtime_index], &ddr->extended_cdt_runtime.bimc_freq_switch[runtime_index]);
        }
        
    }
#if DSF_ECDT_EN
    // Then run thru the ECDT frequency switch parameter input structures, and for those with the apply_override flag set, copy them to the appropriate
    // frequency band in the run-time structures in DDR_STRUCT. 
    if(ecdt != NULL)
    {
        for(ecdt_index = 0; ecdt_index < NUM_ECDT_FREQ_SWITCH_STRUCTS; ecdt_index++) 
        {
            if(ecdt->extended_cdt_ecdt.bimc_freq_switch[ecdt_index].apply_override == 1)
            {
                runtime_index = BIMC_Freq_Switch_Params_Index(ddr, ecdt->extended_cdt_ecdt.bimc_freq_switch[ecdt_index].bimc_freq_switch_params.freq_switch_range_in_kHz);   
                if(runtime_index >= NUM_ECDT_FREQ_SWITCH_STRUCTS)
                {
                    ddr_printf(DDR_ERROR, "Error: ECDT Frequency Switch structure: Frequency out of limits: %uMHz\n\n", 
                                            ecdt->extended_cdt_ecdt.bimc_freq_switch[ecdt_index].bimc_freq_switch_params.freq_switch_range_in_kHz);
                }
                else
                {
                    DDRSS_Copy_Frequency_Switch_Params_Struct(&ecdt->extended_cdt_ecdt.bimc_freq_switch[ecdt_index].bimc_freq_switch_params, 
                                                        &ddr->extended_cdt_runtime.bimc_freq_switch[runtime_index]);
                }
            }
        }
    }
#endif    
}

//================================================================================================//
// DDR Pre-Init function. Used to apply target- and revision-specific workaournds if any.
//================================================================================================//
uint32 DDRSS_Pre_Init(DDR_STRUCT *ddr, EXTENDED_CDT_STRUCT *ecdt)
{
    DDRSS_Copy_Clock_Plan_Struct(ddr);
    
    DDRSS_Create_Ecdt_Runtime_Structs(ddr, ecdt);
    return TRUE;
}
//================================================================================================//
// DDR Post-Init function. Used to apply target- and revision-specific workaournds if any.
//================================================================================================//
uint32 DDRSS_Post_Init(DDR_STRUCT *ddr, EXTENDED_CDT_STRUCT *ecdt, DDR_CHANNEL channel , DDR_CHIPSELECT chip_select)
{
  #if 0	//1/15/18 reverted back weak pulls setting based on customer issues 
  uint32 total_ddr_size=0;
  uint32 ch=0;
  PHY_BUS  dq        = DQ;
  uint32 dq0_ddr_phy_base  = 0;
  uint32 byte_lane  = 0;
  // Figure out how much DDR we actually have.
    total_ddr_size = ddr->ddr_size_info.ddr0_cs0_mb
                        + ddr->ddr_size_info.ddr0_cs1_mb
                        + ddr->ddr_size_info.ddr1_cs0_mb
                        + ddr->ddr_size_info.ddr1_cs1_mb;
	//For all Hynix 4GB devices, enable weak pulls (WA based on SLT/RMA issues)
  if(((ddr->detected_ddr_device[0].manufacture_name == HYNIX)&&(total_ddr_size==0x1000)))
  {
        if ((channel >> ch) & 0x1)
        {
            // DDR PHY DQ base address
            dq0_ddr_phy_base  = REG_OFFSET_DDR_PHY_CH(ch) + DQ0_DDR_PHY_OFFSET;
             for (byte_lane = 0; byte_lane < dq; byte_lane++) 
            {
			//Enable weak pulls for DQS
          HWIO_OUTXF((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)),     
                DDR_PHY_DDRPHY_PAD_CNTL_0_CFG,         
                PULL_N_DQS,                 
                0x3); 
          HWIO_OUTXF((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)),     
                DDR_PHY_DDRPHY_PAD_CNTL_0_CFG,         
                PULL_DQS,                 
                0x1);
			}
	  
		}
  }
  #endif//#if 0
    return TRUE;
}

/* =============================================================================
**  Function : DDR_CC_Pre_Clock_Switch
** =============================================================================
*/
/**
*   @brief
*   DDRCC PLL programming in the pre-clock-switch routine. Platform-specific code,
*   as DDRCC PLL programming characteristics and CSRs are different across targets.
*   Targets 8992 and 8994 are the same, 8996 is different.
*
*   @param[in]  ddr          	 Pointer to ddr conifiguration struct
*   @param[in]  new_clk_index    Index into the clock plan structure corresponding to the requested frequency.
*   @param[in]  ddrcc_target_pll Parameter that selects which PLL to program.
*
*   @retval  None.
*
*   @dependencies
*   None
*
*   @sideeffects
*   None
*
*   @sa
*   None
*/


//================================================================================================//
// IO Calibration workaround for 8996 V1 and V2.
//================================================================================================//
void PHY_IO_Cal_Workaround_En_Dis(DDR_CHANNEL channel, uint8 enable)
{
    uint8 ch = 0;
    uint8 byte_lane = 0;
    uint8 ca_slave = 0;
    uint32 dq0_ddr_phy_base = 0;
    uint32 ca0_ddr_phy_base = 0;
    
    for (ch = 0; ch < NUM_CH; ch++)
    {
        if((channel >> ch) & 0x1) {
            dq0_ddr_phy_base = REG_OFFSET_DDR_PHY_CH(ch) + DQ0_DDR_PHY_OFFSET;
            ca0_ddr_phy_base = REG_OFFSET_DDR_PHY_CH(ch) + CA0_DDR_PHY_OFFSET;
            
            ca_slave = (ch == 0) ? 1 : 0; // Only program slave CA PHY
            
            if(1 == enable) {
                HWIO_OUTX ((ca0_ddr_phy_base + (ca_slave * DDR_PHY_OFFSET)), DDR_PHY_DDRPHY_IOCTLR_BYP_CFG, 0x00100000);                   // Override IO cal. PNCNT=0
                HWIO_OUTXF ((ca0_ddr_phy_base + (ca_slave * DDR_PHY_OFFSET)), DDR_PHY_DDRPHY_PAD_CNTL_3_CFG, LEFT_EXT_VREFB_EN, 1);        // Connect IO cal. Vref to floating external Vref pad
                HWIO_OUTXF ((ca0_ddr_phy_base + (ca_slave * DDR_PHY_OFFSET)), DDR_PHY_DDRPHY_PAD_CNTL_4_CFG, RIGHT_EXT_VREFB_EN, 1);       // Connect IO cal. Vref to floating external Vref pad
                HWIO_OUTXF ((ca0_ddr_phy_base + (ca_slave * DDR_PHY_OFFSET)), DDR_PHY_DDRPHY_PAD_CAL_CFG, CAL_PAD_RFU, 4);                 // Enable IO cal. comparator
                
                for(byte_lane = 0; byte_lane < NUM_DQ_PCH; byte_lane++)
                {
                    HWIO_OUTX ((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), DDR_PHY_DDRPHY_IOCTLR_BYP_CFG, 0x00110000);               // Override IO cal. PNCNT=0
                }
            }
            else {
                HWIO_OUTX ((ca0_ddr_phy_base + (ca_slave * DDR_PHY_OFFSET)), DDR_PHY_DDRPHY_IOCTLR_BYP_CFG, 0x00000000);
                HWIO_OUTXF ((ca0_ddr_phy_base + (ca_slave * DDR_PHY_OFFSET)), DDR_PHY_DDRPHY_PAD_CNTL_3_CFG, LEFT_EXT_VREFB_EN, 0);
                HWIO_OUTXF ((ca0_ddr_phy_base + (ca_slave * DDR_PHY_OFFSET)), DDR_PHY_DDRPHY_PAD_CNTL_4_CFG, RIGHT_EXT_VREFB_EN, 0);
                HWIO_OUTXF ((ca0_ddr_phy_base + (ca_slave * DDR_PHY_OFFSET)), DDR_PHY_DDRPHY_PAD_CAL_CFG, CAL_PAD_RFU, 0);
                
                for(byte_lane = 0; byte_lane < NUM_DQ_PCH; byte_lane++)
                {
                    HWIO_OUTX ((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), DDR_PHY_DDRPHY_IOCTLR_BYP_CFG, 0x00000000);
                }
            }
        }
    }
}


