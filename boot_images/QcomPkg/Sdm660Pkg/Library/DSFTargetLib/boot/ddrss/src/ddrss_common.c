/****************************************************************************
 QUALCOMM Proprietary Design Data
 Copyright (c) 2015, Qualcomm Technologies Incorporated. All rights reserved.
 ****************************************************************************/
/*==============================================================================
                                EDIT HISTORY

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/DSFTargetLib/boot/ddrss/src/ddrss_common.c#8 $
$DateTime: 2017/09/27 02:13:08 $
$Author: pwbldsvc $
================================================================================
when       who          what, where, why
--------   ---          --------------------------------------------------------
05/11/14   arindamm     First edit history header. Add new entries at top.
================================================================================*/

#include "ddrss.h"
#include "target_config.h"

extern uint8 dq_dbi_bit;
extern uint8 dq_spare_bit;
extern uint8 connected_bit_mapping_CA [PINS_PER_PHY_CONNECTED_CA];
extern uint32 retimer_map_DDRCC[NUM_DDRCC_RETIMER_FREQ][NUM_RETIMER];
extern uint32 retimer_map_GCC[NUM_GCC_RETIMER_FREQ][NUM_RETIMER];

uint32 PRFS_index_table[] = {F_RANGE_0, F_RANGE_1, F_RANGE_2, F_RANGE_3, F_RANGE_4, F_RANGE_5, F_RANGE_6, F_RANGE_7};

#if DSF_PXI_TRAINING_EN

#else
//================================================================================================//
// Get the flat 32-bit system address to which training patterns will be written to and read from.
// Adjust address for execution from RPM if needed.
// ===============================================================================================//
void DDRSS_Get_Training_Address(DDR_STRUCT *ddr)
{

    // Adjust if needed for RPM view of system DRAM address map.
    training_address[0][0] = (ddr->ddr_size_info.ddr0_cs0_remapped_addr) + TRAINING_BASE_ADDRESS_OFFSET;

    training_address[0][1] = (ddr->ddr_size_info.ddr0_cs1_remapped_addr) + TRAINING_BASE_ADDRESS_OFFSET;

    training_address[1][0] = (ddr->ddr_size_info.ddr1_cs0_remapped_addr + TRAINING_BASE_ADDRESS_OFFSET +
                             ((ddr->detected_ddr_device[0].interleave_en & DDR_CS0_INTERLEAVE) ? TRAINING_INTERLEAVE_ADDRESS_OFFSET : 0));

    training_address[1][1] = (ddr->ddr_size_info.ddr1_cs1_remapped_addr + TRAINING_BASE_ADDRESS_OFFSET +
                             ((ddr->detected_ddr_device[0].interleave_en & DDR_CS1_INTERLEAVE) ? TRAINING_INTERLEAVE_ADDRESS_OFFSET : 0));

}
#endif

//================================================================================================//
// Get an index based on Frequency provided.
//================================================================================================//
uint8 DDRSS_Get_Freq_Index (DDR_STRUCT *ddr, uint32 clk_freq_khz)
{
   uint8 prfs_index;

   for (prfs_index = 0; (prfs_index < sizeof(PRFS_index_table)/sizeof(uint32)); prfs_index++)
   {
      if (clk_freq_khz < PRFS_index_table[prfs_index])
         break;
   }

   return prfs_index;
}

//================================================================================================//
// Get highest frequency from the clock plan in the PRFS band
//================================================================================================//
uint32 DDRSS_Get_Highest_Freq_In_PRFS_Band (DDR_STRUCT *ddr, uint32 prfs_index)
{
   uint8 i = 0;                     // clock plan index
   uint32 pfrs_band_max_freq = 0;   // maximum frequency for the PRFS band
   uint32 clock_plan_freq = 0;      // clock plan frequency
   
   pfrs_band_max_freq = PRFS_index_table[prfs_index];
   
   for (i = MAX_NUM_CLOCK_PLAN; i > 0;)
   {
       i--;
       
       clock_plan_freq = ddr->misc.clock_plan[i].clk_freq_in_khz;
       
       if ((clock_plan_freq != 0) && (clock_plan_freq <= pfrs_band_max_freq))
       {
           break;
       }
   }

   return clock_plan_freq;
}

//================================================================================================//
// Memory read from DRAM.
// This function will read data of a given size to a given address supplied by the caller.
//================================================================================================//
void ddr_mem_copy(uint32 * source, uint32 * destination, uint32 size, uint32 burst)
{
    uint32 i;

    if(burst)
    {
        /* perform a burst write */
        #ifndef CDVI_SVTB
        __blocksCopy(source, destination, size);
        #endif
    }
    else
    {
        for(i = 0; i < size; i++)
        {
            destination[i] = source[i];
        }
    }
}





//================================================================================================//
// Process coarse histogram to find horizon eye
//================================================================================================//
void DDRSS_Post_Histogram_Coarse_Horizon_Eye (best_eye_struct *best_eye_ptr,
                                              uint8 (*coarse_fail_count_ptr)[COARSE_VREF][COARSE_CDC],
                                              training_data *training_data_ptr,
                                              training_params_t *training_params_ptr,
                                              uint8 training_type,  /* 0: CA Vref training; 1:wr_dqdqs training; 2: rd_dqdqs*/
                                              uint8 phy_inx,
                                              uint32 clk_freq_khz
                                             )
{
   uint8       left_boundary_eye_cdc_value = 0xFF;
   uint8      right_boundary_eye_cdc_value = 0xFF;
   uint8  temp_left_boundary_eye_cdc_value = 0xFF;
   uint8 temp_right_boundary_eye_cdc_value = 0xFF;

   uint8                   first_pass_flag = 0;
   uint8                         cdc_value = 0;
   uint8                        vref_value = 0;
   uint8                         cdc_index = 0;
   uint8                        vref_index = 0;
   uint8            max_eye_width_all_vref = 0;
   uint8         max_eye_width_single_vref = 0;
   uint8                         eye_width = 0;
   uint8                   eye_width_count = 0;
   uint8                        start_vref = 0;
   uint8                         start_cdc = 0;
   uint8                          max_vref = 0;
   uint8                           max_cdc = 0;
   uint8                         vref_step = 0;
   uint8                          cdc_step = 0;
 

   if (training_type == TRAINING_TYPE_CA_VREF)
   {
      start_vref = training_params_ptr->ca_vref.coarse_vref_start_value;
      start_cdc  = training_params_ptr->ca_vref.coarse_cdc_start_value;
      max_vref   = training_params_ptr->ca_vref.coarse_vref_max_value;
      max_cdc    = training_params_ptr->ca_vref.coarse_cdc_max_value;
      vref_step  = training_params_ptr->ca_vref.coarse_vref_step;
      cdc_step   = training_params_ptr->ca_vref.coarse_cdc_step;
   }
   else if (training_type == TRAINING_TYPE_WR_DQDQS)
   {
      start_vref = training_params_ptr->wr_dqdqs.coarse_vref_start_value;
      start_cdc  = training_params_ptr->wr_dqdqs.coarse_cdc_start_value;
      max_vref   = training_params_ptr->wr_dqdqs.coarse_vref_max_value;
      max_cdc    = training_params_ptr->wr_dqdqs.coarse_cdc_max_value;
      vref_step  = training_params_ptr->wr_dqdqs.coarse_vref_step;
      cdc_step   = training_params_ptr->wr_dqdqs.coarse_cdc_step;
   }
   else if (training_type == TRAINING_TYPE_RD_DQDQS )
   {
      // Check for frequency range (HP or MP global vref)
      if ((clk_freq_khz >= ODT_FPRS_THRESHOLD_FREQ) && (training_params_ptr->rd_dqdqs.coarse_vref_max_value > 32))
      {
         max_vref = 32;
      }
      else
      {
         max_vref = training_params_ptr->rd_dqdqs.coarse_vref_max_value;
      }
      start_vref = 0; //read pass band info always starts from 0  
      start_cdc  = training_params_ptr->rd_dqdqs.coarse_cdc_start_value;
      max_cdc    = training_params_ptr->rd_dqdqs.coarse_cdc_max_value;
      vref_step  = training_params_ptr->rd_dqdqs.coarse_vref_step;
      cdc_step   = training_params_ptr->rd_dqdqs.coarse_cdc_step;
   }

   best_eye_ptr[phy_inx].bottom_max_eye_vref_value = 0xFF;
   best_eye_ptr[phy_inx].top_max_eye_vref_value    = 0xFF;
   best_eye_ptr[phy_inx].vref_all_fail_flag        = 0;

   // Scan the eye histogram in Y-axis from bottom to top (vref increases)
   for (vref_value = start_vref; vref_value <= max_vref; vref_value += vref_step)
   {
      vref_index = (vref_value - start_vref) / vref_step;   // Vref_step is never to be 0, truncation is expected

      first_pass_flag           = 0;
      eye_width_count           = 0;
      max_eye_width_single_vref = 0;

      // Scan the eye histogram in X-axis from left to right (cdc increases)
      for (cdc_value = start_cdc; cdc_value <= max_cdc; cdc_value += cdc_step)
      {
         cdc_index = (cdc_value - start_cdc) / cdc_step;    // CDC_step is never to be 0, truncation is expected

         // Record each of the eye band width info (width, left/right boundary) for this line
         // When the current point is PASS, eye_width_count ++
         if (coarse_fail_count_ptr[phy_inx][vref_index][cdc_index] == 0)   // When the current point is PASS
         {
            eye_width_count ++;

            if (first_pass_flag == 0) {      // Record the first PASS point as left boundary
               temp_left_boundary_eye_cdc_value = cdc_value;
            }

            // If the max_cdc point is PASS, also record it as right boundary
            if (cdc_index == (max_cdc - start_cdc) / cdc_step)
            {
               temp_right_boundary_eye_cdc_value = cdc_value;

               // In case several eye bands are in same width, choose the rightmost one
               if (eye_width_count >= max_eye_width_single_vref)
               {
                  max_eye_width_single_vref = eye_width_count;
                  left_boundary_eye_cdc_value  = temp_left_boundary_eye_cdc_value;
                  right_boundary_eye_cdc_value = temp_right_boundary_eye_cdc_value;
               }
            }

            first_pass_flag = 1;
         }

         // Current point is FAIL and previous point is PASS
         else if (cdc_index >= 1 && coarse_fail_count_ptr[phy_inx][vref_index][cdc_index-1] == 0)
         {
            temp_right_boundary_eye_cdc_value = cdc_value - cdc_step;

            // In case several eye bands are in same width, choose the rightmost one
            if (eye_width_count >= max_eye_width_single_vref)
            {
               max_eye_width_single_vref = eye_width_count;
               left_boundary_eye_cdc_value  = temp_left_boundary_eye_cdc_value;
               right_boundary_eye_cdc_value = temp_right_boundary_eye_cdc_value;
            }

            eye_width_count = 0;
            first_pass_flag = 0;
         }

         // max_eye_width_single_vref can only be 0 when all points in this line are FAIL
         // set both left and right boundary to 0xFF to be invalid
         if (max_eye_width_single_vref == 0)
         {
            left_boundary_eye_cdc_value  = 0xFF ;
            right_boundary_eye_cdc_value = 0xFF ;
         }
      } // END of CDC loop

      eye_width = max_eye_width_single_vref;

      // In case that several vref values have the same eye_width, using bottom_max_eye_vref_value and top_max_eye_vref_value to record
      if (eye_width > max_eye_width_all_vref)
      {
         best_eye_ptr[phy_inx].bottom_max_eye_vref_value = vref_value;
         max_eye_width_all_vref = eye_width;
         best_eye_ptr[phy_inx].max_eye_right_boundary_cdc_value = right_boundary_eye_cdc_value;
         best_eye_ptr[phy_inx].max_eye_left_boundary_cdc_value = left_boundary_eye_cdc_value;
      }

      else if (eye_width == max_eye_width_all_vref && eye_width != 0) {
         best_eye_ptr[phy_inx].top_max_eye_vref_value = vref_value;
      }
   }   //END of Vref Loop

   // max_eye_width_all_vref can only be 0 when all points of entire histogram are FAIL
   // set both max eye left and right boundary, best_vref_value and best_cdc_value to 0xFF
   // and set vref_all_fail_flag to 1 as well
   if (max_eye_width_all_vref == 0)
   {
      best_eye_ptr[phy_inx].max_eye_right_boundary_cdc_value = 0xFF;    // 0xFF means an invalid value
      best_eye_ptr[phy_inx].max_eye_left_boundary_cdc_value = 0xFF;     // 0xFF means an invalid value
      best_eye_ptr[phy_inx].best_vref_value = 0xFF;                     // 0xFF means an invalid value
      best_eye_ptr[phy_inx].best_cdc_value  = 0xFF;                     // 0xFF means an invalid value
      best_eye_ptr[phy_inx].vref_all_fail_flag = 1;
   }
   else  // We have at least one valid horizontal open eye in the histogram
   {
      best_eye_ptr[phy_inx].vref_all_fail_flag = 0;
      best_eye_ptr[phy_inx].best_cdc_value     = ( best_eye_ptr[phy_inx].max_eye_right_boundary_cdc_value
                                                 + best_eye_ptr[phy_inx].max_eye_left_boundary_cdc_value ) / 2; 

      // When top_max_eye_vref_value(not 0xFF) is greater than the bottom, their average is the best_vref_value
      if (( best_eye_ptr[phy_inx].top_max_eye_vref_value > best_eye_ptr[phy_inx].bottom_max_eye_vref_value)
         && best_eye_ptr[phy_inx].top_max_eye_vref_value != 0xFF)   {
         best_eye_ptr[phy_inx].best_vref_value = ( best_eye_ptr[phy_inx].bottom_max_eye_vref_value
                                                 + best_eye_ptr[phy_inx].top_max_eye_vref_value ) / 2;
      }
      // The case that top_max_eye_vref_value is smaller than bottom or top_max_eye_vref_value is still 0xFF but bottom is not
      // means that we have only one vref having max_eye_width, so bottom_max_eye_vref_value is the best vref
      if ((  best_eye_ptr[phy_inx].top_max_eye_vref_value < best_eye_ptr[phy_inx].bottom_max_eye_vref_value)
         || (best_eye_ptr[phy_inx].top_max_eye_vref_value == 0xFF && best_eye_ptr[phy_inx].bottom_max_eye_vref_value != 0xFF))
      {
         best_eye_ptr[phy_inx].best_vref_value = best_eye_ptr[phy_inx].bottom_max_eye_vref_value;
      }
   }
}


/*This APi selects the coordinates of the maximum area rectangle that can be fit and selects the best Vref and CDC based on that*/
void DDRSS_Post_Histogram_Coarse_Horizon_Eye_Max_Rectangle (DDR_STRUCT *ddr,
                                              uint8 ch,
                                              uint8 cs,
                                              best_eye_struct *best_eye_ptr,
                                              uint8 (*coarse_fail_count_ptr)[COARSE_VREF][COARSE_CDC],
                                              training_data *training_data_ptr,
                                              training_params_t *training_params_ptr,
                                              uint8 training_type,  /* 0: CA Vref training; 1:wr_dqdqs training; 2: rd_dqdqs*/
                                              uint8 phy_inx,
                                              uint32 clk_freq_khz,
                                              uint8 current_clk_inx,
                                              uint8 max_prfs_index
                                              )
{
    uint8                rectangle_bottom_vref_value = 0xFF;
    uint8                   rectangle_top_vref_value = 0xFF;
    uint8           temp_rectangle_bottom_vref_value = 0xFF;
    uint8                   rectangle_left_cdc_value = 0xFF;
    uint8                  rectangle_right_cdc_value = 0xFF;
    uint8              temp_rectangle_left_cdc_value = 0xFF;
    uint8             temp_rectangle_right_cdc_value = 0xFF;
    uint8  histogram_sum_array[COARSE_CDC_MAX_VALUE] = {0};
    uint8                                  min_width = 1;
    uint8                              max_eye_width = 0;
    uint8                                  cdc_value = 0;
    uint8                                 vref_value = 0;
    uint8                                  cdc_index = 0;
    uint8                                 vref_index = 0;
    uint8                                 start_vref = 0;
    uint8                                  start_cdc = 0;
    uint8                                   max_vref = 0;
    uint8                                    max_cdc = 0;
    uint8                                  vref_step = 0;
    uint8                                   cdc_step = 0;
    uint8                            first_pass_flag = 0;
    uint8                              best_vref_val = 0;
    uint8                                      mp_hp = 0;
    uint8                                  hist_rank = 0;
    uint8                          start_width_value = 0;
    uint8                            max_width_value = 0;
    uint8                                read_byte   = 0;
    uint16                   temp_max_area_rectangle = 0;
    uint16                        max_area_rectangle = 0;
    

    
    if (training_type == TRAINING_TYPE_WR_DQDQS)
    {
          start_vref = training_params_ptr->wr_dqdqs.coarse_vref_start_value;
          start_cdc  = training_params_ptr->wr_dqdqs.coarse_cdc_start_value;
          max_vref   = training_params_ptr->wr_dqdqs.coarse_vref_max_value;
          max_cdc    = training_params_ptr->wr_dqdqs.coarse_cdc_max_value;
          vref_step  = training_params_ptr->wr_dqdqs.coarse_vref_step;
          cdc_step   = training_params_ptr->wr_dqdqs.coarse_cdc_step;
#if DSF_WR_DQDQS_EYE_MASK
          min_width  = training_params_ptr->wr_dqdqs.coarse_cdc_min_width_value;
#endif
    }
    else if (training_type == TRAINING_TYPE_RD_DQDQS )
    {
          // Check for frequency range (HP or MP global vref)
          if ((clk_freq_khz >= ODT_FPRS_THRESHOLD_FREQ) && (training_params_ptr->rd_dqdqs.coarse_vref_max_value > 32))            
          {
             max_vref = 32;
          }
          else
          {
             max_vref = training_params_ptr->rd_dqdqs.coarse_vref_max_value;
          }
          start_vref = 0; //read pass band info always starts from 0  
          start_cdc  = training_params_ptr->rd_dqdqs.coarse_cdc_start_value;
          max_cdc    = training_params_ptr->rd_dqdqs.coarse_cdc_max_value;
          vref_step  = training_params_ptr->rd_dqdqs.coarse_vref_step;
          cdc_step   = training_params_ptr->rd_dqdqs.coarse_cdc_step;
#if DSF_RD_DQDQS_EYE_MASK
          min_width  = training_params_ptr->rd_dqdqs.coarse_cdc_min_width_value;
#endif
    }
    best_eye_ptr[phy_inx].bottom_max_eye_vref_value = 0xFF;
    best_eye_ptr[phy_inx].top_max_eye_vref_value    = 0xFF;
    best_eye_ptr[phy_inx].vref_all_fail_flag        = 0;

    //ddr_printf(DDR_NORMAL,"Byte = %d\n",phy_inx);

    hist_rank = (training_type == TRAINING_TYPE_RD_DQDQS) ?
                                     ((cs == 0) ? 1: 0) : 
                                     1;
    //full Vref range only for top HPRX and MPRX speed.  
    //if(((current_clk_inx == max_prfs_index) && hist_rank) || (clk_freq_khz <= F_RANGE_3))
    if(((current_clk_inx == max_prfs_index) && hist_rank) || (clk_freq_khz <= LOWEST_TRAINED_FPRS_FREQ))
    {
        start_width_value = (training_type == TRAINING_TYPE_RD_DQDQS) ? 
                            //(clk_freq_khz <= F_RANGE_3 ? 
                            (clk_freq_khz <= LOWEST_TRAINED_FPRS_FREQ ? 
                                training_params_ptr->rd_dqdqs.coarse_cdc_min_width_lf :
                                training_params_ptr->rd_dqdqs.coarse_cdc_min_width_hf)
                            :
                            //(clk_freq_khz <= F_RANGE_3 ?
                            (clk_freq_khz <= LOWEST_TRAINED_FPRS_FREQ ?                             
                                training_params_ptr->wr_dqdqs.coarse_cdc_min_width_lf :
                                training_params_ptr->wr_dqdqs.coarse_cdc_min_width_hf); 

        max_width_value = (training_type == TRAINING_TYPE_RD_DQDQS) ? 
                            training_params_ptr->rd_dqdqs.coarse_cdc_max_window_width : 
                            training_params_ptr->wr_dqdqs.coarse_cdc_max_window_width;
        
        while(start_width_value >= min_width)
        {
            max_area_rectangle = 0;
                            
    //Copy the first row of the *coarse_fail_count_ptr[COARSE_VREF][COARSE_CDC] to histogram_sum_array[COARSE_CDC_MAX_VALUE] 
            for (cdc_value = start_cdc; cdc_value < max_cdc; cdc_value += cdc_step)
            {
                cdc_index = (cdc_value - start_cdc) / cdc_step;    // CDC_step is never to be 0, truncation is expected
                if(coarse_fail_count_ptr[phy_inx][start_vref][cdc_index] == 0)
                {
                    histogram_sum_array[cdc_index] = 1;
                }
                else
                {
                    histogram_sum_array[cdc_index] = 0;    
                }
            }
            
            temp_max_area_rectangle = sub_histogram_max_rect_area(histogram_sum_array,
                                                                  &temp_rectangle_left_cdc_value,
                                                                  &temp_rectangle_right_cdc_value,
                                                                  &temp_rectangle_bottom_vref_value,
                                                                  start_width_value,
                                                                  max_width_value
                                                                  );

            max_area_rectangle = temp_max_area_rectangle;
            rectangle_bottom_vref_value = start_vref ;
            rectangle_top_vref_value = start_vref;
            rectangle_left_cdc_value = temp_rectangle_left_cdc_value;
            rectangle_right_cdc_value = temp_rectangle_right_cdc_value;                                                         
      
            for (vref_value = start_vref + 1; vref_value < max_vref; vref_value += vref_step)
            {      
                vref_index = vref_value  / vref_step;   // Vref_step is never to be 0, truncation is expecte

            //   curr_vref_pass_flag = 0; // zero out the curr_vref_pass_flag before traversing cdc pass/failinfo.
            // Scan the eye histogram in X-axis from left to right (cdc increases)
                for (cdc_value = start_cdc; cdc_value < max_cdc; cdc_value += cdc_step)
                {
                     cdc_index = (cdc_value - start_cdc) / cdc_step;    // CDC_step is never to be 0, truncation is expected
                    if(coarse_fail_count_ptr[phy_inx][vref_index][cdc_index] == 0)
                    {
                      histogram_sum_array[cdc_index]++;
                      //curr_vref_pass_flag = 1; // passing cdc value detected
                    }
                    else
                    {
                     histogram_sum_array[cdc_index] = 0;    
                    }
                }// end of cdc schmoo
                
                temp_max_area_rectangle = sub_histogram_max_rect_area(histogram_sum_array,
                                                          &temp_rectangle_left_cdc_value,
                                                          &temp_rectangle_right_cdc_value,
                                                          &temp_rectangle_bottom_vref_value,
                                                          start_width_value,
                                                          max_width_value
                                                          );
                 
                if (temp_max_area_rectangle == max_area_rectangle)
                {
                    if((temp_rectangle_right_cdc_value - temp_rectangle_left_cdc_value) >= (rectangle_right_cdc_value - rectangle_left_cdc_value) )
                    {                                                    // copy the coordinates of the current largest rectangle    
                     max_area_rectangle = temp_max_area_rectangle;
                     rectangle_bottom_vref_value = (vref_index+1) - temp_rectangle_bottom_vref_value ;
                     rectangle_top_vref_value = vref_index;
                     rectangle_left_cdc_value = temp_rectangle_left_cdc_value;
                     rectangle_right_cdc_value = temp_rectangle_right_cdc_value;
                    }
                }
                else if (temp_max_area_rectangle > max_area_rectangle)
                {
                    max_area_rectangle = temp_max_area_rectangle;
                    rectangle_bottom_vref_value = (vref_index+1) - temp_rectangle_bottom_vref_value ;
                    rectangle_top_vref_value = vref_index;
                    rectangle_left_cdc_value = temp_rectangle_left_cdc_value;
                    rectangle_right_cdc_value = temp_rectangle_right_cdc_value;                
                }
            //}
            }
           if((( rectangle_top_vref_value - rectangle_bottom_vref_value) < 1) || (max_area_rectangle == 0))
           {
                start_width_value--;
           }
           else
           {
                break;
           }

        }
#if DSF_RD_DQDQS_EYE_MASK || DSF_WR_DQDQS_EYE_MASK
        if((start_width_value < min_width) &&
            ((( rectangle_top_vref_value - rectangle_bottom_vref_value) < 1) ||  // height
             (max_area_rectangle == 0)))                                         // width
        {
//#if   (DSF_RD_DQDQS_EYE_MASK == 1) && (DSF_WR_DQDQS_EYE_MASK == 0)
//            if(training_type == TRAINING_TYPE_RD_DQDQS)
//#elif (DSF_RD_DQDQS_EYE_MASK == 0) && (DSF_WR_DQDQS_EYE_MASK == 1)
//            if(training_type == TRAINING_TYPE_WR_DQDQS)
//#endif
//            {
                //Abort training.
                ddr_printf(DDR_ERROR,"\n");
                ddr_printf(DDR_ERROR,"    Abort %s coarse due to minimum eye size violation\n", (training_type == TRAINING_TYPE_RD_DQDQS ) ? 
                                                                                                                      "RD": "WR");
                ddr_printf(DDR_ERROR,"    Channel         = %d\n",ch);
                ddr_printf(DDR_ERROR,"    Rank            = %d\n",cs);
                ddr_printf(DDR_ERROR,"    Byte            = %d\n",phy_inx);
                if(( rectangle_top_vref_value - rectangle_bottom_vref_value) < 1)
                    ddr_printf(DDR_ERROR,"    VREF violation \n\n");
                else if(max_area_rectangle == 0)
                    ddr_printf(DDR_ERROR,"    Width violation \n\n");
                ddr->misc.misc_cfg[0] = 1;
                ddr_abort();
//             }
        }
#endif // DSF_RD_DQDQS_EYE_MASK || DSF_WR_DQDQS_EYE_MASK
#if DSF_RD_DQDQS_TRAINING_LOG || DSF_WR_DQDQS_TRAINING_LOG
        ddr_printf(DDR_NORMAL, "max_rectangle_area = %d \n", max_area_rectangle);
        ddr_printf(DDR_NORMAL,"Rectangle bottom vref value = %d,  Rectangle top vref value = %d \n",rectangle_bottom_vref_value,rectangle_top_vref_value);
#endif
        best_vref_val = (rectangle_bottom_vref_value + rectangle_top_vref_value + 1 ) / 2;

    }
    else
    {    // Determine starting VREF and minimum and maximum limits based on MPRX or HPRX
         //mp_hp = (clk_freq_khz <= F_RANGE_3) ? MPRX : HPRX;
         mp_hp = (clk_freq_khz <= HIGHEST_MPVREF_PRFS_FREQ) ? MPVREF : HPVREF;
         read_byte = phy_inx;// / 2;
         best_vref_val = (training_type == TRAINING_TYPE_RD_DQDQS ) ? 
                                           training_data_ptr->results.rd_dqdqs.coarse_vref[mp_hp][ch][0][read_byte] : 
                                           training_data_ptr->results.wr_dqdqs.coarse_vref[max_prfs_index][ch][cs][phy_inx];
                                           // for non HPRX/TX frequency perform 1D histogram analysis to find best CDC only
    }                                      //for read ;cdc is populated on HPRX trained Vref index of cs = 0 in the coarse_fail_count_ptr
                                           //for write; cdc is populated on max_prfs Vref index in the coarse_fail_count_ptr
    // Array out of bounds condition for KW                                       
    if (best_vref_val >= COARSE_VREF)
    {
      best_vref_val = COARSE_VREF - 1;
    }
    
    best_eye_ptr[phy_inx].best_vref_value = best_vref_val;
#if DSF_RD_DQDQS_TRAINING_LOG || DSF_WR_DQDQS_TRAINING_LOG
    ddr_printf(DDR_NORMAL, "Best Vref = %d\n",best_vref_val );
#endif

    //Find the passsing CDC width for the best Vref
    for (cdc_value = start_cdc; cdc_value < max_cdc; cdc_value += cdc_step)
    {
        cdc_index = (cdc_value - start_cdc) / cdc_step;    // CDC_step is never to be 0, truncation is expected

         // Record each of the eye band width info (width, left/right boundary) for this line
         // When the current point is PASS, eye_width_count ++
        if (coarse_fail_count_ptr[phy_inx][best_vref_val][cdc_index] == 0)   // When the current point is PASS
        {
            max_eye_width++;
            if (first_pass_flag == 0) {      // Record the first PASS point as left boundary
                best_eye_ptr[phy_inx].max_eye_left_boundary_cdc_value = cdc_value;
            }
            // If the max_cdc  is PASS, also record it as right boundary
            if (cdc_index == (max_cdc - start_cdc-1) / cdc_step)
            {
            best_eye_ptr[phy_inx].max_eye_right_boundary_cdc_value = cdc_value;
            }
            first_pass_flag = 1;
        }
// Current point is FAIL and previous point is PASS
        else if (cdc_index >= 1 && coarse_fail_count_ptr[phy_inx][best_vref_val][cdc_index-1] == 0)
        {
            best_eye_ptr[phy_inx].max_eye_right_boundary_cdc_value = cdc_value - cdc_step;
        }

    } // END of CDC loop
             // max_eye_width_single_vref can only be 0 when all points in this line are FAIL
         // set both left and right boundary to 0xFF to be invalid
#if DSF_RD_DQDQS_TRAINING_LOG || DSF_WR_DQDQS_TRAINING_LOG
    if (max_eye_width < min_width)
    {
#if   (DSF_RD_DQDQS_EYE_MASK == 1) && (DSF_WR_DQDQS_EYE_MASK == 0)
        if(training_type == TRAINING_TYPE_RD_DQDQS)
#elif (DSF_RD_DQDQS_EYE_MASK == 0) && (DSF_WR_DQDQS_EYE_MASK == 1)
        if(training_type == TRAINING_TYPE_WR_DQDQS)
#endif
        {
             ddr_printf(DDR_ERROR,"\n");
             ddr_printf(DDR_ERROR,"    Abort %s coarse due to minimum eye size violation\n", (training_type == TRAINING_TYPE_RD_DQDQS ) ? 
                                                                                                               "RD": "WR");
             ddr_printf(DDR_ERROR,"    Channel         = %d\n",ch);
             ddr_printf(DDR_ERROR,"    Rank            = %d\n",cs);
             ddr_printf(DDR_ERROR,"    Byte            = %d\n",phy_inx);
             ddr_printf(DDR_ERROR,"    Width violation \n\n");
             ddr->misc.misc_cfg[0] = 1;
             ddr_abort();
        }
    }
#endif // DSF_RD_DQDQS_EYE_MASK || DSF_WR_DQDQS_EYE_MASK
    
    best_eye_ptr[phy_inx].best_cdc_value     = ( best_eye_ptr[phy_inx].max_eye_right_boundary_cdc_value
                                                 + best_eye_ptr[phy_inx].max_eye_left_boundary_cdc_value  ) / 2;
#if DSF_RD_DQDQS_TRAINING_LOG || DSF_WR_DQDQS_TRAINING_LOG
    ddr_printf(DDR_NORMAL, "left_boundary = %d, right_boundary = %d \nBest cdc = %d\n\n", best_eye_ptr[phy_inx].max_eye_left_boundary_cdc_value,
                                                                   best_eye_ptr[phy_inx].max_eye_right_boundary_cdc_value,
                                                                    best_eye_ptr[phy_inx].best_cdc_value);
#endif
}

uint16 Max_sub_area_histogram(uint8 *sub_area_histogram_ptr,
                                       uint8 *rectangle_left_cdc,
                                       uint8 *rectangle_right_cdc,
                                       uint8 *rectangle_bottom_vref,
                                       uint8 start_width_value,
                                       uint8 max_width_value
                                       )
{
    uint8               width_index = 0;
    uint8              window_index = 0;
    uint8           window_iterator = 0;
    uint8              best_height  = 0;
    uint8   temp_rectangle_left_cdc = 0;
    uint8  temp_rectangle_right_cdc = 0;
    uint16            window_area   = 0;
    uint16       max_rectangle_area = 0;   

    for (width_index = start_width_value - 1; // since window index starts from 0 we subract 1 from start_width_value
        width_index < max_width_value;
        width_index++)
    {
        for (window_index = 0; width_index + window_index < COARSE_CDC_MAX_VALUE; window_index++ )
        {
            for (window_iterator = window_index;window_iterator <= width_index + window_index; window_iterator++  )
            {
                if(sub_area_histogram_ptr[window_iterator] <= sub_area_histogram_ptr[window_index])//find the least height of the histogram
                {
                    best_height = sub_area_histogram_ptr[window_iterator];
                }     
            }
            window_area = best_height * (width_index + 1);
            temp_rectangle_left_cdc = window_index;
            temp_rectangle_right_cdc = window_index + width_index; 
            if(window_area == max_rectangle_area)// if areas are equal select the area with widest opening
            {
                if((temp_rectangle_right_cdc - temp_rectangle_left_cdc) //width comparison
                    >= (*rectangle_right_cdc - *rectangle_left_cdc))
                {
                    max_rectangle_area   = window_area;
                    *rectangle_left_cdc  = temp_rectangle_left_cdc;
                    *rectangle_right_cdc = temp_rectangle_right_cdc;
                    *rectangle_bottom_vref = best_height;
                }
            }
            else if(window_area > max_rectangle_area)
            {
                max_rectangle_area   = window_area;
                *rectangle_left_cdc  = temp_rectangle_left_cdc;
                *rectangle_right_cdc = temp_rectangle_right_cdc;
                *rectangle_bottom_vref = best_height;
            }
        }
    }

    return max_rectangle_area;

}

//-----------------------------------------------------------------------------
// This is a stacked based algorithm to find the maximum rectangular area in a histogram
//-----------------------------------------------------------------------------
uint16 sub_histogram_max_rect_area(uint8 *hist_sum_arr_ptr,
                                       uint8 *rectangle_left_cdc,
                                       uint8 *rectangle_right_cdc,
                                       uint8 *rectangle_bottom_vref,
                                       uint8 start_width_value,
                                       uint8 max_width_value
                                       )
{
  int8 popd_s_top     = -1; //popped stack top . -1 => empty stack
  int8 s_top          = -1; // stack top. -1 => empty stack
    uint8 hist_stk[COARSE_CDC_MAX_VALUE] = { 0 }; // stack to hold the sum_array indices
  uint16 area         = 0;
  uint16 max_area     = 0;
  uint8 width         = 0;
    uint8 best_width    = 0;
  uint8 index         = 0;

  for (index = 0; index < COARSE_CDC_MAX_VALUE; index++)
  {
      //Check if empty stack or height of current index in hist_sum_arr is greater or equal than the index pointed by stack
    if ((s_top == -1) || (hist_sum_arr_ptr[index] >= hist_sum_arr_ptr[hist_stk[s_top]])) 
    {
      hist_stk[++s_top] = index; // add the index to the top of the stack
    }
    else  
    {
          //if height of current index is less than that of index pointed by stack top,
              //pop from the stack until stack is empty or height pointed
          //stack top is less than or equal to that of current index.
      while ((s_top != -1) && (hist_sum_arr_ptr[index] < hist_sum_arr_ptr[hist_stk[s_top]]))
      {
        popd_s_top = s_top; //store the stack top in a temp variable
        s_top--; // pop the stack.
        
                
        area = hist_sum_arr_ptr[hist_stk[popd_s_top]] * ((s_top == -1) ?
              index:
              (index - hist_stk[s_top] - 1));
        width = ((s_top == -1) ?
          index :
          (index - hist_stk[s_top] - 1));
        if ((area > max_area) && (width >= start_width_value) && (hist_sum_arr_ptr[hist_stk[popd_s_top]] >= 4) )
        {
          max_area = area;
          *rectangle_bottom_vref = hist_sum_arr_ptr[hist_stk[popd_s_top]];
          *rectangle_right_cdc = index - 1;
          *rectangle_left_cdc  = ((s_top == -1) ? 0 : (hist_stk[s_top] + 1));
                    best_width = width;
        }
                else if ((area == max_area) && (width >= best_width)&& (width >= start_width_value) && (hist_sum_arr_ptr[hist_stk[popd_s_top]] >= 4))
                {
                    max_area = area;
          *rectangle_bottom_vref = hist_sum_arr_ptr[hist_stk[popd_s_top]];
          *rectangle_right_cdc = index - 1;
          *rectangle_left_cdc  = ((s_top == -1) ? 0 : (hist_stk[s_top] + 1));
                    best_width = width;
                }
      }      
      
      hist_stk[++s_top] = index;
    }
  }
    // After the sum array has been traversed, index = COARSE_CDC_MAX_VALUE
    //The last element in the stack will be the smallest in the array, thus width of  rectangular area with its height = index.
  while (s_top != -1)
  {  
    popd_s_top = s_top;
    s_top--;
    area = hist_sum_arr_ptr[hist_stk[popd_s_top]] * ((s_top == -1) ?
          index :
          (index - hist_stk[s_top] - 1));
    width = ((s_top == -1) ?
      index :
      (index - hist_stk[s_top] - 1));
    if ((area > max_area) && (width >= start_width_value) && (hist_sum_arr_ptr[hist_stk[popd_s_top]] >= 4))
    {
      max_area = area;
      *rectangle_bottom_vref = hist_sum_arr_ptr[hist_stk[popd_s_top]];
      *rectangle_right_cdc   = index- 1;
      *rectangle_left_cdc    = ((s_top == -1) ? 0 : (hist_stk[s_top] + 1));
    }
        else if ((area == max_area) && (width >= best_width)&& (width >= start_width_value) && (hist_sum_arr_ptr[hist_stk[popd_s_top]] >= 4))
        {
            max_area = area;
      *rectangle_bottom_vref = hist_sum_arr_ptr[hist_stk[popd_s_top]];
      *rectangle_right_cdc = index - 1;
      *rectangle_left_cdc  = ((s_top == -1) ? 0 : (hist_stk[s_top] + 1));
            best_width = width;
        }            
  }
  return max_area;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//================================================================================================//
// Process fine histogram of each boundary
//================================================================================================//
void DDRSS_Post_Histogram_Fine_Each_Boundary (uint8 (*fine_fail_count_ptr)[PINS_PER_PHY][FINE_VREF][FINE_CDC],
                                              uint8 (*boundary_fine_cdc_ptr)[PINS_PER_PHY][FINE_VREF],
                                              uint8 start_vref,
                                              uint8 max_vref,
                                              training_data *training_data_ptr,
                                              training_params_t *training_params_ptr,
                                              uint8 left_right,  // 0:Left side fine training; 1:Right side fine training
                                              uint8 training_type, /* 0: CA Vref training; 1:wr_dqdqs training; 2: rd_dqdqs*/
                                              uint8 phy_inx,
                                              uint8 bit
                                             )
{
   uint8   cdc_value = 0;
   uint8  vref_value = 0;
   uint8   cdc_index = 0;
   uint8  vref_index = 0;
   uint8     max_cdc = 0;
   uint8   vref_step = 0;
   uint8    cdc_step = 0;
   
   if (training_type == TRAINING_TYPE_CA_VREF)
   {
      max_cdc     = training_params_ptr->ca_vref.fine_cdc_max_value;
      vref_step   = training_params_ptr->ca_vref.fine_vref_step;
      cdc_step    = training_params_ptr->ca_vref.fine_cdc_step;
   }
   else if (training_type == TRAINING_TYPE_WR_DQDQS)
   {
      max_cdc     = training_params_ptr->wr_dqdqs.fine_cdc_max_value;
      vref_step   = training_params_ptr->wr_dqdqs.fine_vref_step;
      cdc_step    = training_params_ptr->wr_dqdqs.fine_cdc_step;
   }

   // Scan the eye histogram in Y-axis from bottom to top (vref increases)
   for (vref_value = start_vref; vref_value <= max_vref; vref_value+=vref_step)
   {
      vref_index = (vref_value - start_vref) / vref_step;

      // Fine training for left boundary
      if (left_right == 0)
      {         
         // Scan the eye histogram in X-axis from right to left (cdc decreases) and find the pass-to-fail point.
         for (cdc_value = (max_cdc +1); cdc_value >= 1; cdc_value -= cdc_step)
         {
            cdc_index = ((cdc_value - 1) /cdc_step);

            // If fail at cdc max_value, then that point is the failed boundary value itself.
            if ((cdc_value == (max_cdc +1)) && (fine_fail_count_ptr[phy_inx][bit][vref_index][cdc_index] != 0)) 
            { 
               boundary_fine_cdc_ptr[phy_inx][bit][vref_index] = cdc_value - 1;  
               break;
            }
            // If fail at some cdc value, then the last passing point was one cdc higher due to our direction.
            else if ((cdc_value != (max_cdc +1)) && (fine_fail_count_ptr[phy_inx][bit][vref_index][cdc_index] != 0)) 
            {
               boundary_fine_cdc_ptr[phy_inx][bit][vref_index] = cdc_value - 1 + cdc_step;
               break;
            }
            // In case that all CDC values pass, left_boundary is 0
            boundary_fine_cdc_ptr[phy_inx][bit][vref_index] = 0;

         }// CDC Loop
      }

      // Fine training for right boundary
      else
      {
         // Scan the eye histogram in X-axis from left to right (cdc increases) and find the pass-to-fail point.         
         for (cdc_value = 0; cdc_value <= max_cdc; cdc_value += cdc_step)
         {
            cdc_index = (cdc_value/cdc_step);

            // If fail at cdc value 0, then that point is the failed boundary value itself.
            if ((cdc_value == 0) && (fine_fail_count_ptr[phy_inx][bit][vref_index][cdc_index] != 0)) 
            {
               boundary_fine_cdc_ptr[phy_inx][bit][vref_index] = cdc_value;
               break;
            }
            // if fail at some cdc value, then the last passing point was one cdc before due to our direction.
            else if ((cdc_value != 0) && (fine_fail_count_ptr[phy_inx][bit][vref_index][cdc_index] != 0)) 
            {
               boundary_fine_cdc_ptr[phy_inx][bit][vref_index] = cdc_value - cdc_step;
               break;
            }
            // In case that all CDC values pass, right_boundary is set to max_cdc
            boundary_fine_cdc_ptr[phy_inx][bit][vref_index] = max_cdc;

         }  // CDC Loop
      }
   }  // Vref Loop

}
//================================================================================================//
// Process fine histogram of each boundary
//================================================================================================//
void DDRSS_Post_Histogram_RD_Fine_Each_Boundary (uint8 (*fine_fail_count_ptr)[PINS_PER_PHY][FINE_VREF][FINE_RD_CDC],
                                                 uint8 (*boundary_fine_cdc_ptr)[PINS_PER_PHY][FINE_VREF],
                                                 uint8 start_vref,
                                                 uint8 max_vref,
                                                training_data *training_data_ptr,
                                                 training_params_t *training_params_ptr,
                                                 uint8 left_right,  // 0:Left side fine training; 1:Right side fine training
                                                 uint8 phy_inx,
                                                 uint8 bit
                                                )
{
   uint8   cdc_value = 0;
   uint8  vref_value = 0;
   uint8   cdc_index = 0;
   uint8  vref_index = 0;
   uint8     max_cdc = 0;
   uint8   vref_step = 0;
   uint8    cdc_step = 0;
   
   max_cdc     = training_params_ptr->rd_dqdqs.fine_cdc_max_value;
   vref_step   = training_params_ptr->rd_dqdqs.fine_vref_step;
   cdc_step    = training_params_ptr->rd_dqdqs.fine_cdc_step;


   // Scan the eye histogram in Y-axis from bottom to top (vref increases)
   for (vref_value = start_vref; vref_value <= max_vref; vref_value+=vref_step)
   {
      vref_index = (vref_value - start_vref) / vref_step;

      // Fine training for left boundary
      if (left_right == 0)
      {         
         // Scan the eye histogram in X-axis from right to left (cdc decreases) and find the pass-to-fail point.
         for (cdc_value = (max_cdc +1); cdc_value >= 1; cdc_value -= cdc_step)
         {
            cdc_index = ((cdc_value - 1) /cdc_step);

            // If fail at cdc max_value, then that point is the failed boundary value itself.
            if ((cdc_value == (max_cdc +1)) && (fine_fail_count_ptr[phy_inx][bit][vref_index][cdc_index] != 0)) 
            { 
               boundary_fine_cdc_ptr[phy_inx][bit][vref_index] = cdc_value - 1;  
               break;
            }
            // If fail at some cdc value, then the last passing point was one cdc higher due to our direction.
            else if ((cdc_value != (max_cdc +1)) && (fine_fail_count_ptr[phy_inx][bit][vref_index][cdc_index] != 0)) 
            {
               boundary_fine_cdc_ptr[phy_inx][bit][vref_index] = cdc_value - 1 + cdc_step;
               break;
            }
            // In case that all CDC values pass, left_boundary is 0
            boundary_fine_cdc_ptr[phy_inx][bit][vref_index] = 0;

         }// CDC Loop
      }

      // Fine training for right boundary
      else
      {
         // Scan the eye histogram in X-axis from left to right (cdc increases) and find the pass-to-fail point.         
         for (cdc_value = 0; cdc_value <= max_cdc; cdc_value += cdc_step)
         {
            cdc_index = (cdc_value/cdc_step);

            // If fail at cdc value 0, then that point is the failed boundary value itself.
            if ((cdc_value == 0) && (fine_fail_count_ptr[phy_inx][bit][vref_index][cdc_index] != 0)) 
            {
               boundary_fine_cdc_ptr[phy_inx][bit][vref_index] = cdc_value;
               break;
            }
            // if fail at some cdc value, then the last passing point was one cdc before due to our direction.
            else if ((cdc_value != 0) && (fine_fail_count_ptr[phy_inx][bit][vref_index][cdc_index] != 0)) 
            {
               boundary_fine_cdc_ptr[phy_inx][bit][vref_index] = cdc_value - cdc_step;
               break;
            }
            // In case that all CDC values pass, right_boundary is set to max_cdc
            boundary_fine_cdc_ptr[phy_inx][bit][vref_index] = max_cdc;

         }  // CDC Loop
      }
   }  // Vref Loop

}

//================================================================================================//
// Process fine histogram to find best eye
//================================================================================================//
 void DDRSS_Post_Histogram_Fine_Best_Eye_Cal (best_eye_struct (*best_eye_ptr)[PINS_PER_PHY],
                                              uint8 (*left_boundary_fine_cdc_ptr)[PINS_PER_PHY][FINE_VREF],
                                              uint8 (*right_boundary_fine_cdc_ptr)[PINS_PER_PHY][FINE_VREF],
                                              uint8 start_vref,
                                              uint8 max_vref,
                                              training_data *training_data_ptr,
                                              training_params_t *training_params_ptr,
                                              uint8 training_type, /* 0: CA Vref training; 1:wr_dqdqs training; 2: rd_dqdqs*/
                                              uint8 phy_inx,
                                              uint8 bit
                                             )
 {
    uint8    vref_value = 0;
    uint8    vref_index = 0;
    uint8     eye_width = 0;
    uint8 max_eye_width = 0;
    uint8       max_cdc = 0;
    uint8     vref_step = 0;

    best_eye_ptr[phy_inx][bit].bottom_max_eye_vref_value = 0xFF;
    best_eye_ptr[phy_inx][bit].top_max_eye_vref_value    = 0xFF;
    
    if (training_type == TRAINING_TYPE_CA_VREF)
    {
       max_cdc    = training_params_ptr->ca_vref.fine_cdc_max_value;
       vref_step  = training_params_ptr->ca_vref.fine_vref_step;
    }
    else if (training_type == TRAINING_TYPE_WR_DQDQS)
    {
       max_cdc    = training_params_ptr->wr_dqdqs.fine_cdc_max_value;
       vref_step  = training_params_ptr->wr_dqdqs.fine_vref_step;
    }
    else if (training_type == TRAINING_TYPE_RD_DQDQS )
    {
       max_cdc    = training_params_ptr->rd_dqdqs.fine_cdc_max_value;
       vref_step  = training_params_ptr->rd_dqdqs.fine_vref_step;
    }

    for (vref_value = start_vref; vref_value <= max_vref; vref_value+=vref_step)
    {
       vref_index = (vref_value - start_vref) / vref_step;   // Vref_step is never to be 0, truncation is expected

       // When this vref value is valid, calculate correct eye_width, otherwise, eye_width = 0xFF
       if (right_boundary_fine_cdc_ptr[phy_inx][bit][vref_index] != 0xFF && left_boundary_fine_cdc_ptr[phy_inx][bit][vref_index] != 0xFF)   {
          eye_width = (right_boundary_fine_cdc_ptr[phy_inx][bit][vref_index] + max_cdc - left_boundary_fine_cdc_ptr[phy_inx][bit][vref_index]);
       }
       else  {  //It is not possible that eye_width for all the vref_value are 0xFF, at least one value is valid
          eye_width = 0xFF;
       }
       // In case that several vref values have the same eye_width, using bottom_max_eye_vref_value and top_max_eye_vref_value to record
       if (eye_width > max_eye_width && eye_width != 0xFF)
       {
          best_eye_ptr[phy_inx][bit].bottom_max_eye_vref_value = vref_value;
          max_eye_width = eye_width;
          best_eye_ptr[phy_inx][bit].max_eye_right_boundary_cdc_value = right_boundary_fine_cdc_ptr[phy_inx][bit][vref_index];
          best_eye_ptr[phy_inx][bit].max_eye_left_boundary_cdc_value  = left_boundary_fine_cdc_ptr[phy_inx][bit][vref_index];
       }

       else if (eye_width == max_eye_width) {
          best_eye_ptr[phy_inx][bit].top_max_eye_vref_value = vref_value;
       }
    }   //END of Vref Loop

    // The case that we have several vref values with the same max_eye_width,
    // the best vref is the medium value of top_max_eye_vref_value and bottom_max_eye_vref_value
    if (( best_eye_ptr[phy_inx][bit].top_max_eye_vref_value > best_eye_ptr[phy_inx][bit].bottom_max_eye_vref_value)
       && best_eye_ptr[phy_inx][bit].top_max_eye_vref_value != 0xFF)   {
       best_eye_ptr[phy_inx][bit].best_vref_value = ( best_eye_ptr[phy_inx][bit].bottom_max_eye_vref_value
                                               + best_eye_ptr[phy_inx][bit].top_max_eye_vref_value ) / 2;
    }

    // The case that top_max_eye_vref_value is smaller than bottom or top_max_eye_vref_value is still 0xFF
    // means the we have only one vref having max_eye_width, so bottom_max_eye_vref_value is the best vref
    if ((best_eye_ptr[phy_inx][bit].top_max_eye_vref_value < best_eye_ptr[phy_inx][bit].bottom_max_eye_vref_value && max_eye_width != 0)
       || (best_eye_ptr[phy_inx][bit].top_max_eye_vref_value == 0xFF && best_eye_ptr[phy_inx][bit].bottom_max_eye_vref_value != 0xFF))  {
       best_eye_ptr[phy_inx][bit].best_vref_value = best_eye_ptr[phy_inx][bit].bottom_max_eye_vref_value;
    }

    // max_eye_width == 0 can only occur when eye_width is always 0 except for cases eye_width is 0xFF
    if (max_eye_width == 0)
    {
       best_eye_ptr[phy_inx][bit].best_vref_value = (best_eye_ptr[phy_inx][bit].top_max_eye_vref_value + start_vref) / 2;
       best_eye_ptr[phy_inx][bit].max_eye_right_boundary_cdc_value = 0;
       best_eye_ptr[phy_inx][bit].max_eye_left_boundary_cdc_value  = max_cdc;
    }
 }


//================================================================================================//
// CDC retimer
//================================================================================================//
void DDRSS_CDC_Retimer (DDR_STRUCT *ddr,
                        uint8 cs,
                        uint8 coarse_dqs_delay,
                        uint8 fine_dqs_delay,
                        uint8 coarse_wrlvl_delay,
                        uint8 fine_wrlvl_delay,
                        uint32 cadq_ddr_phy_base,
                        uint32 clk_freq_khz
                       )
{
  uint8          dq_retmr = 0;
  dq_retmr = DDRSS_CDC_Retimer_Value(
                        coarse_dqs_delay,
                        fine_dqs_delay,
                        coarse_wrlvl_delay,
                        fine_wrlvl_delay,
                        clk_freq_khz);
  // Update the re-timer register
  DDR_PHY_hal_cfg_ca_vref_dq_retmr(cadq_ddr_phy_base, cs, dq_retmr);
}

uint8 DDRSS_CDC_Retimer_Value (uint8 coarse_dqs_delay,
                        uint8 fine_dqs_delay,
                        uint8 coarse_wrlvl_delay,
                        uint8 fine_wrlvl_delay,
                        uint32 clk_freq_khz
                       )
{
  uint8          dq_retmr = 0;
  uint32   retmr_freq_inx = 0;
  uint32  coarse_delay_ps = 0;
  uint32    fine_delay_ps = 0;
  uint32   total_delay_ps = 0;
  
  coarse_delay_ps = (coarse_dqs_delay + coarse_wrlvl_delay) * COARSE_STEP_IN_PS;
  fine_delay_ps   = (fine_dqs_delay   +   fine_wrlvl_delay) * FINE_STEP_IN_PS;
  total_delay_ps  = coarse_delay_ps + fine_delay_ps;
  
  if(clk_freq_khz <= HIGHEST_GCC_PLL_FREQ)
  {
      // Use GCC retimer map
      for(retmr_freq_inx = 0; retmr_freq_inx < (NUM_GCC_RETIMER_FREQ - 1); retmr_freq_inx++)
      {
          if(clk_freq_khz <= retimer_map_GCC[retmr_freq_inx][0])
          {
              break;
          }
      }
      
      for(dq_retmr = 0; dq_retmr < (NUM_RETIMER - 1); dq_retmr++)
      {
          if(total_delay_ps <= retimer_map_GCC[retmr_freq_inx][dq_retmr + 1])
          {
              break;
          }
      }
  }
  else
  {
      // Use DDRCC retimer map
      for(retmr_freq_inx = 0; retmr_freq_inx < (NUM_DDRCC_RETIMER_FREQ - 1); retmr_freq_inx++)
      {
          if(clk_freq_khz <= retimer_map_DDRCC[retmr_freq_inx][0])
          {
              break;
          }
      }
      
      for(dq_retmr = 0; dq_retmr < (NUM_RETIMER - 1); dq_retmr++)
      {
          if(total_delay_ps <= retimer_map_DDRCC[retmr_freq_inx][dq_retmr + 1])
          {
              break;
          }
      }
  }

  return dq_retmr;
}

//================================================================================================//
// Frequency Scaling
//================================================================================================//

// Divide and remainder calculation functions for WRLVL CDC conversion
uint32 calc (uint32 step, uint32 i_delay, uint8 set_rem_out)
{
   uint32 div_rem = 0;

   // Divide or Mod depending on set_rem_out decode
   if ((step <= i_delay) && (step != 0)) {
      // Mod delay by step
      if (set_rem_out == 1) {
         div_rem   = (i_delay % step);
      }
      else {
         // Divide delay by step
         div_rem   = (i_delay / step);
         if (set_rem_out == 2) {
             div_rem = div_rem  * step;
         }
      }
   }
   // Bypass the result if illegal
   else {
       if (set_rem_out == 1) {
           div_rem = i_delay;
       }
   }

   // Return the result
   return div_rem;
}

// Optimize Coarse and Fine CDC, Half, and Retimer values based on trained results
void DDRSS_cdc_convert (DDR_STRUCT *ddr, wrlvl_params_struct *wrlvl_params_ptr, uint32 wrlvl_delay, 
                        uint32 period, uint8  training_type, /*1:wr_dqdqs training*/
                        uint8 half_cycle, uint8 full_cycle)
{

    //  Calculation Constants
    uint8  opt_unit_cdcc   = COARSE_STEP_IN_PS; // CDC coarse unit delay (ps)
    uint8  opt_unit_cdcf   = FINE_STEP_IN_PS;   // CDC fine unit delay (ps)
    uint8  opt_step_cdcc   = 25;                // Number of CDC coarse delay steps

    // Calculation variables
    uint16 dqs_wrlvl_delay;
    uint16 dqs_wrlvl_full_setting;
    uint16 dqs_wrlvl_half_rem_delay;
    uint16 dqs_wrlvl_half_setting;
    uint16 dqs_wrlvl_cdcc_setting;
    uint16 dqs_wrlvl_cdcc_rem_delay;
    uint16 dqs_wrlvl_cdcf_setting;
    uint16 dqs_wrlvl_cdc_delay;
    uint16 dqs_retimer_sel;
    uint16 t2;
    uint16 t34;
    uint16 t4;

    //--------------------------------------------------------------------
    //DQS WRLVL CDC Calculations
    //--------------------------------------------------------------------

     // Calculate t/4 and 3t/4
    t2  = period / 2;
    t4  = period / 4;
    t34 = 3 * t4;

    // Trained WRLVL skew relative to CK
    dqs_wrlvl_delay = wrlvl_delay;

    // Do not calculate full setting due to CDC range requirement
    dqs_wrlvl_full_setting = 0;

    // Use the full_cycle value found from WR DQDQS training.
    if (training_type == TRAINING_TYPE_WR_DQDQS)
    {
        dqs_wrlvl_full_setting = full_cycle;
    }
    
    
    // Use the half delay only if the total delay exceeds the coarse CDC limit and period is less than 2.5ns
    if ((dqs_wrlvl_delay > (opt_step_cdcc * opt_unit_cdcc)) && (period < 2500)) {
      dqs_wrlvl_half_setting   = calc(t2,dqs_wrlvl_delay,0x0);
      dqs_wrlvl_half_rem_delay = calc(t2,dqs_wrlvl_delay,0x1);
    }
      else {
        dqs_wrlvl_half_setting   = 0;
        if (dqs_wrlvl_delay > COARSE_STEP_IN_PS * opt_step_cdcc)
        {
         dqs_wrlvl_delay = COARSE_STEP_IN_PS * opt_step_cdcc;
          
        }
        dqs_wrlvl_half_rem_delay = dqs_wrlvl_delay;
    }

    // Correct half setting if greater than one
    if (dqs_wrlvl_half_setting > 1) {
       dqs_wrlvl_half_rem_delay += (dqs_wrlvl_half_setting - 1) * t2;
       dqs_wrlvl_half_setting = 1;
    }

    // Use the half_cycle value found from WR DQDQS training.
    if (training_type == TRAINING_TYPE_WR_DQDQS)
    {
        dqs_wrlvl_half_setting = half_cycle;
    }
    
    // Calculate WRLVL CDC Coarse Settings
    dqs_wrlvl_cdcc_setting   = calc(opt_unit_cdcc,dqs_wrlvl_half_rem_delay,0x0);
    dqs_wrlvl_cdcc_rem_delay = calc(opt_unit_cdcc,dqs_wrlvl_half_rem_delay,0x1);

    // Check WRLVL CDC coarse setting against the maximum
    if (dqs_wrlvl_cdcc_setting > opt_step_cdcc) {
       dqs_wrlvl_cdcc_setting = opt_step_cdcc;
       dqs_wrlvl_cdcc_rem_delay = dqs_wrlvl_half_rem_delay - (opt_step_cdcc * opt_unit_cdcc);
    }

    // Calculate WRLVL Fine setting
    dqs_wrlvl_cdcf_setting   = calc(opt_unit_cdcf,dqs_wrlvl_cdcc_rem_delay,0x0);

    // Round up fine delay if the a half delay is used and the coarse CDC remainder
    //is greater than the fine CDC unit
    if ((dqs_wrlvl_half_setting == 1) && (dqs_wrlvl_cdcc_rem_delay > 0)) {
       dqs_wrlvl_cdcf_setting++;
    }

    // Adjust the fine value to have at least 4 for DTTS periodic training
    if ((dqs_wrlvl_cdcc_setting > 0) && (dqs_wrlvl_cdcf_setting < ((NUM_DIT_COUNT/2)-1))) 
    {
      dqs_wrlvl_cdcc_setting--;
      dqs_wrlvl_cdcf_setting += FINE_STEPS_PER_COARSE;
    }

    // Calculate the WRLVL CDC delay
    dqs_wrlvl_cdc_delay = (dqs_wrlvl_cdcc_setting * opt_unit_cdcc) +
                          (dqs_wrlvl_cdcf_setting * opt_unit_cdcf);

    // Determine Optimal Retimer Settings
    if (dqs_wrlvl_cdc_delay <= t4) {
       dqs_retimer_sel = 0;
    }
    else if ((dqs_wrlvl_cdc_delay >  t4) && (dqs_wrlvl_cdc_delay <= t34)) {
       dqs_retimer_sel = 1;
    }
    else /* if (dqs_wrlvl_cdc_delay >  t34) */ {  
       dqs_retimer_sel = 2;
    }

    // Push the converted values into the wrlvl_delay struct
    wrlvl_params_ptr->dqs_retmr        = dqs_retimer_sel;
    wrlvl_params_ptr->coarse_dqs_delay = dqs_wrlvl_cdcc_setting;
    wrlvl_params_ptr->fine_dqs_delay   = dqs_wrlvl_cdcf_setting;
    wrlvl_params_ptr->dqs_full_cycle   = dqs_wrlvl_full_setting;
    wrlvl_params_ptr->dqs_half_cycle   = dqs_wrlvl_half_setting;
    
} // DDR_PHY_cdc_convert



