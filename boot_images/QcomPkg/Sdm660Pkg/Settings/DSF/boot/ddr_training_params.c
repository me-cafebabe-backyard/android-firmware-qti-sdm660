/****************************************************************************
 QUALCOMM Proprietary Design Data
 Copyright (c) 2015, Qualcomm Technologies Incorporated. All rights reserved.
 ****************************************************************************/
/*==============================================================================
                                EDIT HISTORY

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Settings/DSF/boot/ddr_training_params.c#8 $
$DateTime: 2017/09/27 02:13:08 $
$Author: pwbldsvc $
================================================================================
when       who          what, where, why
--------   ---          --------------------------------------------------------
06/20/14   ejose        First edit history header. Add new entries at top.
================================================================================*/

#include "ddrss.h"

void DDRSS_set_training_params (training_params_t *training_params_ptr)
{

   training_params_ptr->dit.max_loopcnt = 10;
   training_params_ptr->dcc.max_loopcnt = 0;

   training_params_ptr->ca_vref.max_loopcnt              = 5;
   training_params_ptr->ca_vref.cdc_training_enable      = 0;
   training_params_ptr->ca_vref.coarse_vref_start_value  = 0;
   training_params_ptr->ca_vref.coarse_vref_max_value    = 80; //cover both range0 and range1.
   training_params_ptr->ca_vref.coarse_vref_step         = 1;  //step size of 1 would violate the array size of 0x32.
   training_params_ptr->ca_vref.coarse_cdc_start_value   = 0;
   training_params_ptr->ca_vref.coarse_cdc_max_value     = 0;  //set to 0 if cdc_training_enable = 0
   training_params_ptr->ca_vref.coarse_cdc_step          = 1;
   training_params_ptr->ca_vref.fine_training_enable     = 0; // set to 0 if cdc_training_enable = 0
   training_params_ptr->ca_vref.fine_cdc_max_value       = 0; // set to 0 if cdc_training_enable = 0
   training_params_ptr->ca_vref.fine_cdc_step            = 1;
   training_params_ptr->ca_vref.fine_vref_enable         = 1;
   training_params_ptr->ca_vref.fine_vref_step           = 1;
   training_params_ptr->ca_vref.fine_perbit_start_value  = 0;

   training_params_ptr->wrlvl.max_loopcnt       = 5;
   training_params_ptr->wrlvl.max_coarse_cdc    = 24;
   training_params_ptr->wrlvl.max_fine_cdc      = 12;
   training_params_ptr->wrlvl.coarse_cdc_step   = 1;
   training_params_ptr->wrlvl.fine_cdc_step     = 1;
   training_params_ptr->wrlvl.feedback_percent  = 100;

   training_params_ptr->rcw.max_loopcnt         = 1;
   training_params_ptr->rcw.max_coarse_cdc      = 24;
   training_params_ptr->rcw.max_fine_cdc        = 6;
   training_params_ptr->rcw.coarse_cdc_step     = COARSE_STEP_IN_PS;
   training_params_ptr->rcw.fine_cdc_step       = FINE_STEP_IN_PS;

   training_params_ptr->rd_dqdqs.max_loopcnt                    = 5;
   training_params_ptr->rd_dqdqs.coarse_vref_start_mprx         = 15;//15
   training_params_ptr->rd_dqdqs.coarse_vref_min_mprx           = 15;
   training_params_ptr->rd_dqdqs.coarse_vref_max_mprx           = 30;
   training_params_ptr->rd_dqdqs.coarse_vref_start_hprx         = 8;
   training_params_ptr->rd_dqdqs.coarse_vref_min_hprx           = 0; //Changed to 0 from 2
   training_params_ptr->rd_dqdqs.coarse_vref_max_hprx           = 18;//LPDDR4x = 8 LPDDR4 = 32;
   training_params_ptr->rd_dqdqs.coarse_vref_start_value        = 6;
   training_params_ptr->rd_dqdqs.coarse_vref_max_value          = 55;
   training_params_ptr->rd_dqdqs.coarse_vref_step               = 1;
   training_params_ptr->rd_dqdqs.coarse_cdc_start_value         = 0;
   training_params_ptr->rd_dqdqs.coarse_cdc_max_value           = 24;
   training_params_ptr->rd_dqdqs.coarse_cdc_step                = 1;
   training_params_ptr->rd_dqdqs.coarse_cdc_min_width_lf        = 6;
   training_params_ptr->rd_dqdqs.coarse_cdc_min_width_hf        = 4;
   training_params_ptr->rd_dqdqs.coarse_cdc_max_window_width   = 16;// max passing window to be detected
   training_params_ptr->rd_dqdqs.coarse_hp_vref_mask_max_delta  = 1; // Terminated   // 18mv Steps, 0 = 50mV
   training_params_ptr->rd_dqdqs.coarse_hp_vref_mask_min_delta  = 1; // Terminated   // 18mV Steps, 0 = 50mV
   training_params_ptr->rd_dqdqs.coarse_mp_vref_mask_max_delta  = 1; // Unterminated // 11mV Steps, 0 = 11mV 
   training_params_ptr->rd_dqdqs.coarse_mp_vref_mask_min_delta  = 1; // Unterminated // 11mV Steps, 0 = 11mV 
   training_params_ptr->rd_dqdqs.coarse_cdc_min_width_value     = 2;
   training_params_ptr->rd_dqdqs.coarse_vref_low_limit_hprx     = 5; //Changed from 6
   training_params_ptr->rd_dqdqs.fine_training_enable           = 1;
   training_params_ptr->rd_dqdqs.fine_vref_start_value          = 5;
   training_params_ptr->rd_dqdqs.fine_vref_max_value            = 11;
   training_params_ptr->rd_dqdqs.fine_cdc_start_value           = 0;
   training_params_ptr->rd_dqdqs.fine_cdc_max_value             = 15;
   training_params_ptr->rd_dqdqs.fine_cdc_step                  = 1;
   training_params_ptr->rd_dqdqs.fine_vref_enable               = 1;
   training_params_ptr->rd_dqdqs.fine_vref_step                 = 1;
   training_params_ptr->rd_dqdqs.pbit_start_value               = 0;

   training_params_ptr->wr_dqdqs.max_loopcnt                        = 5;
   training_params_ptr->wr_dqdqs.coarse_vref_start_value            = 0;
   training_params_ptr->wr_dqdqs.coarse_vref_max_value              = 50;
   training_params_ptr->wr_dqdqs.coarse_vref_step                   = 1;
   training_params_ptr->wr_dqdqs.coarse_cdc_start_value             = 0;
   training_params_ptr->wr_dqdqs.coarse_cdc_max_value               = 24;
   training_params_ptr->wr_dqdqs.coarse_cdc_step                    = 1;
   training_params_ptr->wr_dqdqs.coarse_MR14_0_vref_mask_max_delta  = 1; // Terminated    4.4mV Steps
   training_params_ptr->wr_dqdqs.coarse_MR14_0_vref_mask_min_delta  = 1; // Terminated    4.4mV Steps
   training_params_ptr->wr_dqdqs.coarse_MR14_1_vref_mask_max_delta  = 1; // Unterminated  4.4mV steps 
   training_params_ptr->wr_dqdqs.coarse_MR14_1_vref_mask_min_delta  = 1; // Unterminated  4.4mV steps 
   training_params_ptr->wr_dqdqs.coarse_cdc_min_width_lf            = 6;//2;
   training_params_ptr->wr_dqdqs.coarse_cdc_min_width_hf            = 4;//2;
   training_params_ptr->wr_dqdqs.coarse_cdc_min_window_width        = 2; //min passing window to be detected --> 100ps opening 
   training_params_ptr->wr_dqdqs.coarse_cdc_max_window_width        = 16;// max passing window to be detected
   training_params_ptr->wr_dqdqs.fine_training_enable               = 1;
   training_params_ptr->wr_dqdqs.fine_cdc_top_freq_start_value      = 10;
   training_params_ptr->wr_dqdqs.fine_cdc_start_value               = 0;
   training_params_ptr->wr_dqdqs.fine_cdc_top_freq_max_value        = 11;
   training_params_ptr->wr_dqdqs.fine_cdc_max_value                 = 0xF;
   training_params_ptr->wr_dqdqs.fine_cdc_step                      = 1;
   training_params_ptr->wr_dqdqs.fine_vref_enable                   = 1;
   training_params_ptr->wr_dqdqs.fine_vref_step                     = 1;
   training_params_ptr->wr_dqdqs.pbit_start_value                   = 0;
   training_params_ptr->wr_dqdqs.coarse_cdc_min_width_value         = 2;

}

