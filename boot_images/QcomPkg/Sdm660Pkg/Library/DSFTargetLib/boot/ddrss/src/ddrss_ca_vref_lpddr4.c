/****************************************************************************
 QUALCOMM Proprietary Design Data
 Copyright (c) 2015, Qualcomm Technologies Incorporated. All rights reserved.
 ****************************************************************************/
/*==============================================================================
                                EDIT HISTORY

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/DSFTargetLib/boot/ddrss/src/ddrss_ca_vref_lpddr4.c#6 $
$DateTime: 2016/12/30 05:44:11 $
$Author: pwbldsvc $
================================================================================
when       who          what, where, why
--------   ---          --------------------------------------------------------
05/04/16   amoussav     replaced DDRSS_ca_vref_lpddr4 with DDRSS_Vrefonly_lpddr4 and remved extra function 
05/04/14   arindamm     First edit history header. Add new entries at top.
================================================================================*/

#include "ddrss.h"
#include <string.h>

//================================================================================================//
// DDR PHY CA VREF training
//================================================================================================//

boolean DDRSS_Vrefonly_lpddr4  (DDR_STRUCT    *ddr,
                       uint8         ch,  
                       uint8         cs, 
                       PHY_BUS       ca,
                       uint8         prfs_index,
                       training_params_t *training_params_ptr,
                       ddrss_ca_vref_local_vars *local_vars,
                       uint32 clk_freq_khz
                      )
{
    uint8               loop_cnt = 0;
    uint8                phy_inx = 0;
    uint8          pattern_index = 0;
    uint8             vref_value = 0;
    uint8              vref_data = 0;
    uint8             cs_pattern = 0;
    uint16        expect_pattern = 0;   
    uint32        reg_offset_dpe = 0;
    uint32   reg_offset_ddr_dq_1 = 0;
//    uint32   reg_offset_ddr_dq_2 = 0;
    uint8               min_vref = 0;
    uint8               max_vref = 0;
    uint8               mid_vref = 0;
    uint16 feedback_data[NUM_CA_PCH] = {0};
    training_data *training_data_ptr;
 
 training_data_ptr     = (training_data *)(&ddr->flash_params.training_data);
    reg_offset_dpe        = REG_OFFSET_DPE(ch);
    reg_offset_ddr_dq_1   = REG_OFFSET_DDR_PHY_CH (ch) + DQ1_DDR_PHY_OFFSET;
//    reg_offset_ddr_dq_2   = REG_OFFSET_DDR_PHY_CH (ch) + DQ2_DDR_PHY_OFFSET;   
    
    for (vref_value  = 0;          vref_value <80;          vref_value ++) 
    {
        // Add MR12_vref_range_bit as the bit 6
        if (vref_value <= CA_VREF_RANGE_THRESHOLD)
        {
            vref_data =  vref_value;    
        }
        else //for range 1
        {
            vref_data = ( 1 << 6) | (vref_value - CA_VREF_RANGE_THRESHOLD) ;  
        }
        // Send Vref for both CA0 and CA1
        BIMC_Send_Vref_Data (ch, cs, vref_data/*vref_data_ch_a*/, vref_data/*vref_data_ch_b*/);  
        // failures counters reset to 0
        local_vars->vref_fail_count_table[0][vref_value]=0; 
//        local_vars->vref_fail_count_table[1][vref_value]=0; 
        // Different CA patterns are sent out to enchance training result
        for (pattern_index = 0; pattern_index < CA_PATTERN_NUM; pattern_index++) 
        { 
             BIMC_write_CA_Pattern (reg_offset_dpe,  ca_training_pattern_lpddr4[pattern_index]);
            cs_pattern     = ca_training_pattern_lpddr4[pattern_index][1];
            expect_pattern = DDRSS_dq_remapping(cs_pattern & 0x3F);     // Only lower 6-bit is valid;
            // For each pattern, each point of histogram will be tested for 16 times,
            for (loop_cnt = training_params_ptr->ca_vref.max_loopcnt; loop_cnt > 0; loop_cnt --) 
            {
                // The MC sends the VREF setting through DQ PHY0 to DRAM on DQ[6:0]
                BIMC_Send_CA_Pattern (ch, cs);
                feedback_data[0] = DDR_PHY_hal_sta_ca_vref (reg_offset_ddr_dq_1); 
                if (feedback_data[0] != expect_pattern)  { local_vars->vref_fail_count_table[0][vref_value]++; }
                if (feedback_data[0] == expect_pattern)/* || feedback_data[1] == expect_pattern) \*/
                {
                    cs_pattern = ~cs_pattern;   //Invert CS_Pattern if passes  
                    expect_pattern = DDRSS_dq_remapping (cs_pattern & 0x3F);   
                    HWIO_OUTX (reg_offset_dpe, DPE_CA_TRAIN_CS, cs_pattern);
                }
            }
        }
    }//End of Vref loop

    // Process the histogram of both CA0 and CA1 and save to data structure
    for (phy_inx = 0; phy_inx < ca; phy_inx ++)     
    {
        DDRSS_passing_region_scan( &min_vref, &max_vref,  local_vars->vref_fail_count_table[phy_inx], 80);
        mid_vref = ( min_vref + max_vref ) / 2; 
        if (min_vref==max_vref)
        {
            return(FALSE);
        }
        if (mid_vref<=CA_VREF_RANGE_THRESHOLD)
        {
            training_data_ptr->results.ca_vref.range_vref[prfs_index][ch][cs][phy_inx] =  mid_vref;
        }
        else 
        {
            training_data_ptr->results.ca_vref.range_vref[prfs_index][ch][cs][phy_inx] = (1 << 6) |(mid_vref-CA_VREF_RANGE_THRESHOLD);
        }
    }
    return(TRUE);
}
void DDRSS_passing_region_scan( uint8 *start, uint8 *stop, uint8 fail_count_histogram[], uint32 histogram_size)
{
    uint8 lenght_cur = 0;
    uint8 start_cur = 0;
    uint8 stop_cur = 0;
    uint8 lenght_stop = 0;
    uint8 sweep;

    *stop  = 0;
    *start = 0;
    for(sweep = 1; sweep < histogram_size - 1; sweep++)
    {
        if((fail_count_histogram[sweep - 1] != 0) && (fail_count_histogram[sweep] == 0))
        {
            start_cur  = sweep;
            stop_cur   = sweep;
            lenght_cur = 0;
        }
        if((fail_count_histogram[sweep] == 0) && (fail_count_histogram[sweep + 1] != 0))
        {
            stop_cur   = sweep;
            lenght_cur = stop_cur - start_cur + 1;
        }
        if((sweep == histogram_size - 2) && (fail_count_histogram[sweep] == 0) && (fail_count_histogram[sweep + 1] == 0))
        {
            stop_cur   = sweep + 1;
            lenght_cur = stop_cur - start_cur + 1;
            }
        if(lenght_cur > lenght_stop)
        {
            lenght_stop = lenght_cur;
            *start      = start_cur ;
            *stop       = stop_cur  ;
        }
    }
}

