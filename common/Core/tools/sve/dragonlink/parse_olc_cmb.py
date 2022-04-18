#! /usr/bin/python

# init version: jbenis 20160125
#
# P4: $Author: pwbldsvc $
#     $Change: 11844661 $
#     $DateTime: 2016/11/23 22:06:41 $
#     $Id: //components/rel/core.glue/1.2.1/tools/tools/sve/dragonlink/parse_olc_cmb.py#1 $

import argparse
import sys

#################
### functions ###
#################

def packet_type_osm0( hex_string ):
                              #    6         5         4         3         2         1
                              # 3210987654321098765432109876543210987654321098765432109876543210

   mask_sw_lut_index        = 0b0000000000000000000000000000000000000000000000000000000000111111 # 6 [5:0]
   mask_arch_index          = 0b0000000000000000000000000000000000000000000000000000111111000000 # 6 [11:6]
   mask_lim_freq_index      = 0b0000000000000000000000000000000000000000000000111111000000000000 # 6 [17:12]
   mask_lim_vol_index       = 0b0000000000000000000000000000000000000000111111000000000000000000 # 6 [23:18]
   mask_curr_working_index  = 0b0000000000000000000000000000000000111111000000000000000000000000 # 6 [29:24]
   mask_arch_core_cnt       = 0b0000000000000000000000000000000110000000000000000000000000000000 # 3 [32:30]
   mask_sideband_select     = 0b0000000000000000000000000000001000000000000000000000000000000000 # 1 33
   mask_sideband_lval       = 0b0000000000000000000000111111110000000000000000000000000000000000 # 8 [41:34]
   mask_cluster_power_state = 0b0000000000000000000111000000000000000000000000000000000000000000 # 3 [44:42]
   mask_core_cnt_to_cpr     = 0b0000000000000000111000000000000000000000000000000000000000000000 # 3 [47:45]
   mask_rgen_fsm_state      = 0b0000000000000111000000000000000000000000000000000000000000000000 # 3 [50:48]
   mask_dcvs_fe_fsm_state   = 0b0000000000111000000000000000000000000000000000000000000000000000 # 3 [53:51]
   mask_be_fsm_state        = 0b0000000111000000000000000000000000000000000000000000000000000000 # 3 [56:54]
   mask_dcvs_in_prgs        = 0b0000001000000000000000000000000000000000000000000000000000000000 # 1 57
   mask_freq_chg_in_prgs    = 0b0000010000000000000000000000000000000000000000000000000000000000 # 1 58
   mask_1b0a                = 0b0000100000000000000000000000000000000000000000000000000000000000 # 1 59
   mask_1b0b                = 0b0001000000000000000000000000000000000000000000000000000000000000 # 1 60
   mask_apm_in_prgs         = 0b0010000000000000000000000000000000000000000000000000000000000000 # 1 61
   mask_packet_id           = 0b1100000000000000000000000000000000000000000000000000000000000000 # 2 [63:62]

   field_sw_lut_index        = ((int(hex_string, 16)) & mask_sw_lut_index) >> 0
   field_arch_index          = ((int(hex_string, 16)) & mask_arch_index) >> 6
   field_lim_freq_index      = ((int(hex_string, 16)) & mask_lim_freq_index) >> 12
   field_lim_vol_index       = ((int(hex_string, 16)) & mask_lim_vol_index) >> 18
   field_curr_working_index  = ((int(hex_string, 16)) & mask_curr_working_index) >> 24
   field_arch_core_cnt       = ((int(hex_string, 16)) & mask_arch_core_cnt) >> 30
   field_sideband_select     = ((int(hex_string, 16)) & mask_sideband_select) >> 33
   field_sideband_lval       = ((int(hex_string, 16)) & mask_sideband_lval) >> 34
   field_cluster_power_state = ((int(hex_string, 16)) & mask_cluster_power_state) >> 42
   field_core_cnt_to_cpr     = ((int(hex_string, 16)) & mask_core_cnt_to_cpr) >> 45
   field_rgen_fsm_state      = ((int(hex_string, 16)) & mask_rgen_fsm_state) >> 48
   field_dcvs_fe_fsm_state   = ((int(hex_string, 16)) & mask_dcvs_fe_fsm_state) >> 51
   field_be_fsm_state        = ((int(hex_string, 16)) & mask_be_fsm_state) >> 54
   field_dcvs_in_prgs        = ((int(hex_string, 16)) & mask_dcvs_in_prgs) >> 57
   field_freq_chg_in_prgs    = ((int(hex_string, 16)) & mask_freq_chg_in_prgs) >> 58
   field_1b0a                = ((int(hex_string, 16)) & mask_1b0a) >> 59
   field_1b0b                = ((int(hex_string, 16)) & mask_1b0b) >> 60
   field_apm_in_prgs         = ((int(hex_string, 16)) & mask_apm_in_prgs) >> 61
   field_packet_id           = ((int(hex_string, 16)) & mask_packet_id) >> 62

   print "{0:1} {1:1} {2:1} {3:1} {4:1} {5:1} {6:1} {7:1} {8:1} {9:1} {10:1} {11:3} {12:1} {13:1} {14:2} {15:2} {16:2} {17:2} {18:2}"\
   .format(field_packet_id, field_apm_in_prgs, field_1b0b, field_1b0a, field_freq_chg_in_prgs, field_dcvs_in_prgs,\
           field_be_fsm_state,field_dcvs_fe_fsm_state, field_rgen_fsm_state, field_core_cnt_to_cpr,\
           field_cluster_power_state, field_sideband_lval, field_sideband_select, field_arch_core_cnt,\
           field_curr_working_index, field_lim_vol_index, field_lim_freq_index, field_arch_index, field_sw_lut_index)

   if excel:
      print >> output_file_object, "," + str(field_packet_id),
      print >> output_file_object, "," + str(field_apm_in_prgs),
      print >> output_file_object, "," + str(field_1b0b),
      print >> output_file_object, "," + str(field_1b0a),
      print >> output_file_object, "," + str(field_freq_chg_in_prgs),
      print >> output_file_object, "," + str(field_dcvs_in_prgs),
      print >> output_file_object, "," + str(field_be_fsm_state),
      print >> output_file_object, "," + str(field_dcvs_fe_fsm_state),
      print >> output_file_object, "," + str(field_rgen_fsm_state),
      print >> output_file_object, "," + str(field_core_cnt_to_cpr),
      print >> output_file_object, "," + str(field_cluster_power_state),
      print >> output_file_object, "," + str(field_sideband_lval),
      print >> output_file_object, "," + str(field_sideband_select),
      print >> output_file_object, "," + str(field_arch_core_cnt),
      print >> output_file_object, "," + str(field_curr_working_index),
      print >> output_file_object, "," + str(field_lim_vol_index),
      print >> output_file_object, "," + str(field_lim_freq_index),
      print >> output_file_object, "," + str(field_arch_index),
      print >> output_file_object, "," + str(field_sw_lut_index)
   return

def packet_type_osm1( hex_string ):
                                          #    6         5         4         3         2         1
                                          # 3210987654321098765432109876543210987654321098765432109876543210

   mask_core_cnt_to_cpr                 = 0b0000000000000000000000000000000000000000000000000000000000000111 # 3 [ 2: 0]
   mask_raw_core_cnt                    = 0b0000000000000000000000000000000000000000000000000000000000111000 # 3 [ 5: 3]
   mask_arch_core_cnt                   = 0b0000000000000000000000000000000000000000000000000000000111000000 # 3 [ 8: 6]
   mask_vmin_red_fsm_state              = 0b0000000000000000000000000000000000000000000000000000111000000000 # 3 [11: 9]
   mask_freq_4c_eq_1c                   = 0b0000000000000000000000000000000000000000000000000001000000000000 # 1     12
   mask_vmin_red_fsm_en_from_seq        = 0b0000000000000000000000000000000000000000000000000010000000000000 # 1     13
   mask_vmin_red_fsm_dis_from_seq       = 0b0000000000000000000000000000000000000000000000000100000000000000 # 1     14
   mask_cc_safe_freq_achieved           = 0b0000000000000000000000000000000000000000000000001000000000000000 # 1     15
   mask_cpr_fsm_ack_to_be               = 0b0000000000000000000000000000000000000000000000010000000000000000 # 1     16
   mask_lmh_throttle_amnt               = 0b0000000000000000000000000000000000000000000111100000000000000000 # 4 [20:17]
   mask_ps_computed_droop_code_div2     = 0b0000000000000000000000000000000000000011111000000000000000000000 # 5 [25:21]
   mask_ps_inc_throttle                 = 0b0000000000000000000000000000000000000100000000000000000000000000 # 1     26
   mask_ps_computed_dext_div8           = 0b0000000000000000000000000000000111111000000000000000000000000000 # 6 [32:27]
   mask_ps_freq                         = 0b0000000000000000000000011111111000000000000000000000000000000000 # 8 [40:33]
   mask_ps_boost_fsm_sideband_lval_div2 = 0b0000000000000000111111100000000000000000000000000000000000000000 # 7 [47:41]
   mask_ps_boost_fsm_state              = 0b0000000000001111000000000000000000000000000000000000000000000000 # 4 [51:48]
   mask_ps_droop_fsm_state              = 0b0000000001110000000000000000000000000000000000000000000000000000 # 3 [54:52]
   mask_spare                           = 0b0011111110000000000000000000000000000000000000000000000000000000 # 7 [61:55]
   mask_packed_id                       = 0b1100000000000000000000000000000000000000000000000000000000000000 # 2 [63:62]

   field_core_cnt_to_cpr                 = ((int(hex_string, 16)) & mask_core_cnt_to_cpr                ) >>  0
   field_raw_core_cnt                    = ((int(hex_string, 16)) & mask_raw_core_cnt                   ) >>  3
   field_arch_core_cnt                   = ((int(hex_string, 16)) & mask_arch_core_cnt                  ) >>  6
   field_vmin_red_fsm_state              = ((int(hex_string, 16)) & mask_vmin_red_fsm_state             ) >>  9
   field_freq_4c_eq_1c                   = ((int(hex_string, 16)) & mask_freq_4c_eq_1c                  ) >> 12
   field_vmin_red_fsm_en_from_seq        = ((int(hex_string, 16)) & mask_vmin_red_fsm_en_from_seq       ) >> 13
   field_vmin_red_fsm_dis_from_seq       = ((int(hex_string, 16)) & mask_vmin_red_fsm_dis_from_seq      ) >> 14
   field_cc_safe_freq_achieved           = ((int(hex_string, 16)) & mask_cc_safe_freq_achieved          ) >> 15
   field_cpr_fsm_ack_to_be               = ((int(hex_string, 16)) & mask_cpr_fsm_ack_to_be              ) >> 16
   field_lmh_throttle_amnt               = ((int(hex_string, 16)) & mask_lmh_throttle_amnt              ) >> 17
   field_ps_computed_droop_code_div2     = ((int(hex_string, 16)) & mask_ps_computed_droop_code_div2    ) >> 21
   field_ps_inc_throttle                 = ((int(hex_string, 16)) & mask_ps_inc_throttle                ) >> 26
   field_ps_computed_dext_div8           = ((int(hex_string, 16)) & mask_ps_computed_dext_div8          ) >> 27
   field_ps_freq                         = ((int(hex_string, 16)) & mask_ps_freq                        ) >> 33
   field_ps_boost_fsm_sideband_lval_div2 = ((int(hex_string, 16)) & mask_ps_boost_fsm_sideband_lval_div2) >> 41
   field_ps_boost_fsm_state              = ((int(hex_string, 16)) & mask_ps_boost_fsm_state             ) >> 48
   field_ps_droop_fsm_state              = ((int(hex_string, 16)) & mask_ps_droop_fsm_state             ) >> 52
   field_spare                           = ((int(hex_string, 16)) & mask_spare                          ) >> 55
   field_packed_id                       = ((int(hex_string, 16)) & mask_packed_id                      ) >> 62

   print "{0:1} {1:3} {2:1} {3:2} {4:3} {5:3} {6:2} {7:1} {8:2} {9:2} {10:1} {11:1} {12:1} {13:1} {14:1} {15:1} {16:1} {17:1} {18:1}"\
   .format(field_packed_id,
           field_spare,
           field_ps_droop_fsm_state,
           field_ps_boost_fsm_state,
           field_ps_boost_fsm_sideband_lval_div2,
           field_ps_freq,
           field_ps_computed_dext_div8,
           field_ps_inc_throttle,
           field_ps_computed_droop_code_div2,
           field_lmh_throttle_amnt,
           field_cpr_fsm_ack_to_be,
           field_cc_safe_freq_achieved,
           field_vmin_red_fsm_dis_from_seq,
           field_vmin_red_fsm_en_from_seq,
           field_freq_4c_eq_1c,
           field_vmin_red_fsm_state,
           field_arch_core_cnt,
           field_raw_core_cnt,
           field_core_cnt_to_cpr)

   if excel:
      print >> output_file_object, "," + str(field_packed_id                      ),
      print >> output_file_object, "," + str(field_spare                          ),
      print >> output_file_object, "," + str(field_ps_droop_fsm_state             ),
      print >> output_file_object, "," + str(field_ps_boost_fsm_state             ),
      print >> output_file_object, "," + str(field_ps_boost_fsm_sideband_lval_div2),
      print >> output_file_object, "," + str(field_ps_freq                        ),
      print >> output_file_object, "," + str(field_ps_computed_dext_div8          ),
      print >> output_file_object, "," + str(field_ps_inc_throttle                ),
      print >> output_file_object, "," + str(field_ps_computed_droop_code_div2    ),
      print >> output_file_object, "," + str(field_lmh_throttle_amnt              ),
      print >> output_file_object, "," + str(field_cpr_fsm_ack_to_be              ),
      print >> output_file_object, "," + str(field_cc_safe_freq_achieved          ),
      print >> output_file_object, "," + str(field_vmin_red_fsm_dis_from_seq      ),
      print >> output_file_object, "," + str(field_vmin_red_fsm_en_from_seq       ),
      print >> output_file_object, "," + str(field_freq_4c_eq_1c                  ),
      print >> output_file_object, "," + str(field_vmin_red_fsm_state             ),
      print >> output_file_object, "," + str(field_arch_core_cnt                  ),
      print >> output_file_object, "," + str(field_raw_core_cnt                   ),
      print >> output_file_object, "," + str(field_core_cnt_to_cpr                )
   return

def packet_type_osm2( hex_string ):
                             #    6         5         4         3         2         1
                             # 3210987654321098765432109876543210987654321098765432109876543210

   mask_branch             = 0b0000000000000000000000000000000000001111111111111111111111111111 # 28 [27: 0]
   mask_power_control_bits = 0b0000000000000000011111111111111111110000000000000000000000000000 # 19 [46:28]
   mask_power_event_bits   = 0b0001111111111111100000000000000000000000000000000000000000000000 # 14 [60:47]
   mask_spare              = 0b0010000000000000000000000000000000000000000000000000000000000000 #  1     61
   mask_packed_id          = 0b1100000000000000000000000000000000000000000000000000000000000000 #  2 [63:62]

   field_branch             = ((int(hex_string, 16)) & mask_branch            ) >>  0
   field_power_control_bits = ((int(hex_string, 16)) & mask_power_control_bits) >> 28
   field_power_event_bits   = ((int(hex_string, 16)) & mask_power_event_bits  ) >> 47
   field_spare              = ((int(hex_string, 16)) & mask_spare             ) >> 61
   field_packed_id          = ((int(hex_string, 16)) & mask_packed_id         ) >> 62

   print "{0:1} {1:1} {2:5} {3:6} {4:9}"\
   .format(field_packed_id,
           field_spare,
           field_power_event_bits,
           field_power_control_bits,
           field_branch)

   if excel:
      print >> output_file_object, "," + str(field_packed_id         ),
      print >> output_file_object, "," + str(field_spare             ),
      print >> output_file_object, "," + str(field_power_event_bits  ),
      print >> output_file_object, "," + str(field_power_control_bits),
      print >> output_file_object, "," + str(field_branch            )
   return

def packet_type_osm3( hex_string ):
                                        #    6         5         4         3         2         1
                                        # 3210987654321098765432109876543210987654321098765432109876543210

   mask_force_cfa =                     0b0000000000000000000000000000000000000000000000000000000000000001 # 1      0
   mask_dext_val_div8 =                 0b0000000000000000000000000000000000000000000000000000000011111110 # 7 [ 7: 1]
   mask_sideband_select =               0b0000000000000000000000000000000000000000000000000000000100000000 # 1      8
   mask_sideband_lval_div2 =            0b0000000000000000000000000000000000000000000000001111111000000000 # 7 [15: 9]
   mask_droop_code_div2 =               0b0000000000000000000000000000000000000000001111110000000000000000 # 6 [21:16]
   mask_ps_boost_fsm_state =            0b0000000000000000000000000000000000000011110000000000000000000000 # 4 [25:22]
   mask_dcvs_boost_fsm_state =          0b0000000000000000000000000000000000111100000000000000000000000000 # 4 [29:26]
   mask_cc_boost_fsm_state =            0b0000000000000000000000000000001111000000000000000000000000000000 # 4 [33:30]
   mask_ps_droop_fsm_state =            0b0000000000000000000000000001110000000000000000000000000000000000 # 3 [36:34]
   mask_dcvs_droop_fsm_state =          0b0000000000000000000000001110000000000000000000000000000000000000 # 3 [39:37]
   mask_pc_ret_exit_droop_fsm_state_0 = 0b0000000000000000000001110000000000000000000000000000000000000000 # 3 [42:40]
   mask_pc_ret_exit_droop_fsm_state_1 = 0b0000000000000000001110000000000000000000000000000000000000000000 # 3 [45:43]
   mask_pc_ret_exit_droop_fsm_state_2 = 0b0000000000000001110000000000000000000000000000000000000000000000 # 3 [48:46]
   mask_pc_ret_exit_droop_fsm_state_3 = 0b0000000000001110000000000000000000000000000000000000000000000000 # 3 [51:49]
   mask_wfx_droop_fsm_state_0 =         0b0000000001110000000000000000000000000000000000000000000000000000 # 3 [54:52]
   mask_wfx_droop_fsm_state_1 =         0b0000001110000000000000000000000000000000000000000000000000000000 # 3 [57:55]
   mask_wfx_droop_fsm_state_2 =         0b0001110000000000000000000000000000000000000000000000000000000000 # 3 [60:58]
   mask_wfx_droop_fsm_state_3 =         0b1110000000000000000000000000000000000000000000000000000000000000 # 3 [63:61]
  #mask_packet_id =                     0b1000000000000000000000000000000000000000000000000000000000000000 # 2 [63:62]

   field_force_cfa                     = ((int(hex_string, 16)) &  mask_force_cfa                    ) >>  0
   field_dext_val_div8                 = ((int(hex_string, 16)) &  mask_dext_val_div8                ) >>  1
   field_sideband_select               = ((int(hex_string, 16)) &  mask_sideband_select              ) >>  8
   field_sideband_lval_div2            = ((int(hex_string, 16)) &  mask_sideband_lval_div2           ) >>  9
   field_droop_code_div2               = ((int(hex_string, 16)) &  mask_droop_code_div2              ) >> 16
   field_ps_boost_fsm_state            = ((int(hex_string, 16)) &  mask_ps_boost_fsm_state           ) >> 22
   field_dcvs_boost_fsm_state          = ((int(hex_string, 16)) &  mask_dcvs_boost_fsm_state         ) >> 26
   field_cc_boost_fsm_state            = ((int(hex_string, 16)) &  mask_cc_boost_fsm_state           ) >> 30
   field_ps_droop_fsm_state            = ((int(hex_string, 16)) &  mask_ps_droop_fsm_state           ) >> 34
   field_dcvs_droop_fsm_state          = ((int(hex_string, 16)) &  mask_dcvs_droop_fsm_state         ) >> 37
   field_pc_ret_exit_droop_fsm_state_0 = ((int(hex_string, 16)) &  mask_pc_ret_exit_droop_fsm_state_0) >> 40
   field_pc_ret_exit_droop_fsm_state_1 = ((int(hex_string, 16)) &  mask_pc_ret_exit_droop_fsm_state_1) >> 43
   field_pc_ret_exit_droop_fsm_state_2 = ((int(hex_string, 16)) &  mask_pc_ret_exit_droop_fsm_state_2) >> 46
   field_pc_ret_exit_droop_fsm_state_3 = ((int(hex_string, 16)) &  mask_pc_ret_exit_droop_fsm_state_3) >> 49
   field_wfx_droop_fsm_state_0         = ((int(hex_string, 16)) &  mask_wfx_droop_fsm_state_0        ) >> 52
   field_wfx_droop_fsm_state_1         = ((int(hex_string, 16)) &  mask_wfx_droop_fsm_state_1        ) >> 55
   field_wfx_droop_fsm_state_2         = ((int(hex_string, 16)) &  mask_wfx_droop_fsm_state_2        ) >> 58
   field_wfx_droop_fsm_state_3         = ((int(hex_string, 16)) &  mask_wfx_droop_fsm_state_3        ) >> 61
  #field_packet_id                     = ((int(hex_string, 16)) &  mask_packet_id                    ) >> 63

   print "{0:1} {1:1} {2:1} {3:1} {4:1} {5:1} {6:1} {7:1} {8:1} {9:1} {10:2} {11:2} {12:2} {13:2} {14:3} {15:1} {16:3} {17:1}"\
   .format(field_wfx_droop_fsm_state_3,
           field_wfx_droop_fsm_state_2,
           field_wfx_droop_fsm_state_1,
           field_wfx_droop_fsm_state_0,
           field_pc_ret_exit_droop_fsm_state_3,
           field_pc_ret_exit_droop_fsm_state_2,
           field_pc_ret_exit_droop_fsm_state_1,
           field_pc_ret_exit_droop_fsm_state_0,
           field_dcvs_droop_fsm_state,
           field_ps_droop_fsm_state,
           field_cc_boost_fsm_state,
           field_dcvs_boost_fsm_state,
           field_ps_boost_fsm_state,
           field_droop_code_div2,
           field_sideband_lval_div2,
           field_sideband_select,
           field_dext_val_div8,
           field_force_cfa)

   if excel:
      #print >> output_file_object, "," + str(field_packet_id                    ),
      print >> output_file_object, "," + str(field_wfx_droop_fsm_state_3        ),
      print >> output_file_object, "," + str(field_wfx_droop_fsm_state_2        ),
      print >> output_file_object, "," + str(field_wfx_droop_fsm_state_1        ),
      print >> output_file_object, "," + str(field_wfx_droop_fsm_state_0        ),
      print >> output_file_object, "," + str(field_pc_ret_exit_droop_fsm_state_3),
      print >> output_file_object, "," + str(field_pc_ret_exit_droop_fsm_state_2),
      print >> output_file_object, "," + str(field_pc_ret_exit_droop_fsm_state_1),
      print >> output_file_object, "," + str(field_pc_ret_exit_droop_fsm_state_0),
      print >> output_file_object, "," + str(field_dcvs_droop_fsm_state         ),
      print >> output_file_object, "," + str(field_ps_droop_fsm_state           ),
      print >> output_file_object, "," + str(field_cc_boost_fsm_state           ),
      print >> output_file_object, "," + str(field_dcvs_boost_fsm_state         ),
      print >> output_file_object, "," + str(field_ps_boost_fsm_state           ),
      print >> output_file_object, "," + str(field_droop_code_div2              ),
      print >> output_file_object, "," + str(field_sideband_lval_div2           ),
      print >> output_file_object, "," + str(field_sideband_select              ),
      print >> output_file_object, "," + str(field_dext_val_div8                ),
      print >> output_file_object, "," + str(field_force_cfa                    )
   return

def packet_type_llm( hex_string ):
                                        #    6         5         4         3         2         1
                                        # 3210987654321098765432109876543210987654321098765432109876543210

   mask_active_core_cnt            =         0b0000000000000000000000000000000000000000000000000000000000000011 #  2 [ 1: 0]
   mask_latest_temp_sample         =         0b0000000000000000000000000000000000000000000000000000111111111100 # 10 [11: 2]
   mask_avg_current_violation      =         0b0000000000000000000000000000000000000000000011111111000000000000 #  8 [19:12]
   mask_bcl_violation              =         0b0000000000000000000000000000000000000000011100000000000000000000 #  3 [22:20]
   mask_current_cluster_freq       =         0b0000000000000000000000000000000001111111100000000000000000000000 #  8 [30:23]
   mask_dcvsh_freq_des_current_blk =         0b0000000000000000000000000111111110000000000000000000000000000000 #  8 [38:31]
   mask_dcvsh_freq_des_therm_blk   =         0b0000000000000000011111111000000000000000000000000000000000000000 #  8 [46:39]
   mask_dcvsh_freq_des_bcl_blk     =         0b0000000001111111100000000000000000000000000000000000000000000000 #  8 [54:47]
   mask_voltage_lmt                =         0b1111111110000000000000000000000000000000000000000000000000000000 #  9 [63:55]

   field_active_core_cnt            = ((int(hex_string, 16)) & mask_active_core_cnt           ) >>  0
   field_latest_temp_sample         = ((int(hex_string, 16)) & mask_latest_temp_sample        ) >>  2
   field_avg_current_violation      = ((int(hex_string, 16)) & mask_avg_current_violation     ) >> 12
   field_bcl_violation              = ((int(hex_string, 16)) & mask_bcl_violation             ) >> 20
   field_current_cluster_freq       = ((int(hex_string, 16)) & mask_current_cluster_freq      ) >> 23
   field_dcvsh_freq_des_current_blk = ((int(hex_string, 16)) & mask_dcvsh_freq_des_current_blk) >> 31
   field_dcvsh_freq_des_therm_blk   = ((int(hex_string, 16)) & mask_dcvsh_freq_des_therm_blk  ) >> 39
   field_dcvsh_freq_des_bcl_blk     = ((int(hex_string, 16)) & mask_dcvsh_freq_des_bcl_blk    ) >> 47
   field_voltage_lmt                = ((int(hex_string, 16)) & mask_voltage_lmt               ) >> 55

   print "{0:3} {1:3} {2:3} {3:3} {4:3} {5:1} {6:3} {7:4} {8:1}"\
   .format(field_voltage_lmt,
           field_dcvsh_freq_des_bcl_blk,
           field_dcvsh_freq_des_therm_blk,
           field_dcvsh_freq_des_current_blk,
           field_current_cluster_freq,
           field_bcl_violation,
           field_avg_current_violation,
           field_latest_temp_sample,
           field_active_core_cnt)

   if excel:
      print >> output_file_object, "," + str(field_voltage_lmt               ),
      print >> output_file_object, "," + str(field_dcvsh_freq_des_bcl_blk    ),
      print >> output_file_object, "," + str(field_dcvsh_freq_des_therm_blk  ),
      print >> output_file_object, "," + str(field_dcvsh_freq_des_current_blk),
      print >> output_file_object, "," + str(field_current_cluster_freq      ),
      print >> output_file_object, "," + str(field_bcl_violation             ),
      print >> output_file_object, "," + str(field_avg_current_violation     ),
      print >> output_file_object, "," + str(field_latest_temp_sample        ),
      print >> output_file_object, "," + str(field_active_core_cnt           )

   if vcd:
      print >> vcd_file_object, "r{0} @".format(field_voltage_lmt)
      print >> vcd_file_object, "r{0} #".format(field_dcvsh_freq_des_bcl_blk)
      print >> vcd_file_object, "r{0} %".format(field_dcvsh_freq_des_therm_blk)
      print >> vcd_file_object, "r{0} ^".format(field_dcvsh_freq_des_current_blk)
      print >> vcd_file_object, "r{0} &".format(field_current_cluster_freq)
      print >> vcd_file_object, "r{0} *".format(field_bcl_violation)
      print >> vcd_file_object, "r{0} (".format(field_avg_current_violation)
      print >> vcd_file_object, "r{0} )".format(field_latest_temp_sample)
      print >> vcd_file_object, "r{0} :".format(field_active_core_cnt)

   return

def packet_type_apm( hex_string ):
                                      #    6         5         4         3         2         1
                                      # 3210987654321098765432109876543210987654321098765432109876543210

   mask_pgs_idle_bus                = 0b0000000000000000000000000000000000000000000000000000001111111111 # 10 [ 9: 0]
   mask_mas_idle_int                = 0b0000000000000000000000000000000000000000000011111111110000000000 # 10 [19:10]
   mask_o_apm_ctl_cci_forceclockoff = 0b0000000000000000000000000000000000000000000100000000000000000000 #  1     20
   mask_apmctl_cl_forceclockoff_raw = 0b0000000000000000000000000000000000000000011000000000000000000000 #  2 [22:21]
   mask_apm_ctl_serfreeze_dis       = 0b0000000000000000000000000000000000000001100000000000000000000000 #  2 [24:23]
   mask_apmctl_serfreeze_raw        = 0b0000000000000000000000000000000000000110000000000000000000000000 #  2 [26:25]
   mask_tied_to_zero                = 0b1111111111111111111111111111111111111000000000000000000000000000 # 37 [63:27]

   field_pgs_idle_bus                = ((int(hex_string, 16)) & mask_pgs_idle_bus               ) >>  0
   field_mas_idle_int                = ((int(hex_string, 16)) & mask_mas_idle_int               ) >> 10
   field_o_apm_ctl_cci_forceclockoff = ((int(hex_string, 16)) & mask_o_apm_ctl_cci_forceclockoff) >> 20
   field_apmctl_cl_forceclockoff_raw = ((int(hex_string, 16)) & mask_apmctl_cl_forceclockoff_raw) >> 21
   field_apm_ctl_serfreeze_dis       = ((int(hex_string, 16)) & mask_apm_ctl_serfreeze_dis      ) >> 23
   field_apmctl_serfreeze_raw        = ((int(hex_string, 16)) & mask_apmctl_serfreeze_raw       ) >> 25
   field_tied_to_zero                = ((int(hex_string, 16)) & mask_tied_to_zero               ) >> 27

   print "{0:12} {1:1} {2:1} {3:1} {4:1} {5:4} {6:4}"\
   .format(field_tied_to_zero,
           field_apmctl_serfreeze_raw,
           field_apm_ctl_serfreeze_dis,
           field_apmctl_cl_forceclockoff_raw,
           field_o_apm_ctl_cci_forceclockoff,
           field_mas_idle_int,
           field_pgs_idle_bus)

   if excel:
      print >> output_file_object, "," + str(field_tied_to_zero               ),
      print >> output_file_object, "," + str(field_apmctl_serfreeze_raw       ),
      print >> output_file_object, "," + str(field_apm_ctl_serfreeze_dis      ),
      print >> output_file_object, "," + str(field_apmctl_cl_forceclockoff_raw),
      print >> output_file_object, "," + str(field_o_apm_ctl_cci_forceclockoff),
      print >> output_file_object, "," + str(field_mas_idle_int               ),
      print >> output_file_object, "," + str(field_pgs_idle_bus               )
   return

def packet_type_cprh( hex_string ):
                                       #    6         5         4         3         2         1
                                       # 3210987654321098765432109876543210987654321098765432109876543210

   mask_tied_to_zero_go              = 0b1111111111100000000000000000000000000000000000000000000000000000 # 11 [63:53]
   mask_cpr_saw_steps_go             = 0b0000000000011111111111111110000000000000000000000000000000000000 # 16 [52:37]
   mask_cpr_saw_up_go                = 0b0000000000000000000000000001000000000000000000000000000000000000 #  1     36
   mask_cpr_saw_down_go              = 0b0000000000000000000000000000100000000000000000000000000000000000 #  1     35
   mask_cpr_saw_load_voltage_go      = 0b0000000000000000000000000000010000000000000000000000000000000000 #  1     34
   mask_cpr_saw_load_floor_go        = 0b0000000000000000000000000000001000000000000000000000000000000000 #  1     33
   mask_cpr_saw_load_voltage_ceil_go = 0b0000000000000000000000000000000100000000000000000000000000000000 #  1     32
   mask_tied_to_zero_si              = 0b0000000000000000000000000000000011111111111000000000000000000000 # 11 [31:21]
   mask_cpr_saw_steps_si             = 0b0000000000000000000000000000000000000000000111111111111111100000 # 16 [20: 5]
   mask_cpr_saw_up_si                = 0b0000000000000000000000000000000000000000000000000000000000010000 #  1      4
   mask_cpr_saw_down_si              = 0b0000000000000000000000000000000000000000000000000000000000001000 #  1      3
   mask_cpr_saw_load_voltage_si      = 0b0000000000000000000000000000000000000000000000000000000000000100 #  1      2
   mask_cpr_saw_load_floor_si        = 0b0000000000000000000000000000000000000000000000000000000000000010 #  1      1
   mask_cpr_saw_load_voltage_ceil_si = 0b0000000000000000000000000000000000000000000000000000000000000001 #  1      0

   field_tied_to_zero_go              = ((int(hex_string, 16)) & mask_tied_to_zero_go)              >> 53
   field_cpr_saw_steps_go             = ((int(hex_string, 16)) & mask_cpr_saw_steps_go)             >> 37
   field_cpr_saw_up_go                = ((int(hex_string, 16)) & mask_cpr_saw_up_go)                >> 36
   field_cpr_saw_down_go              = ((int(hex_string, 16)) & mask_cpr_saw_down_go)              >> 35
   field_cpr_saw_load_voltage_go      = ((int(hex_string, 16)) & mask_cpr_saw_load_voltage_go)      >> 34
   field_cpr_saw_load_floor_go        = ((int(hex_string, 16)) & mask_cpr_saw_load_floor_go)        >> 33
   field_cpr_saw_load_voltage_ceil_go = ((int(hex_string, 16)) & mask_cpr_saw_load_voltage_ceil_go) >> 32
   field_tied_to_zero_si              = ((int(hex_string, 16)) & mask_tied_to_zero_si)              >> 21
   field_cpr_saw_steps_si             = ((int(hex_string, 16)) & mask_cpr_saw_steps_si)             >>  5
   field_cpr_saw_up_si                = ((int(hex_string, 16)) & mask_cpr_saw_up_si)                >>  4
   field_cpr_saw_down_si              = ((int(hex_string, 16)) & mask_cpr_saw_down_si)              >>  3
   field_cpr_saw_load_voltage_si      = ((int(hex_string, 16)) & mask_cpr_saw_load_voltage_si)      >>  2
   field_cpr_saw_load_floor_si        = ((int(hex_string, 16)) & mask_cpr_saw_load_floor_si)        >>  1
   field_cpr_saw_load_voltage_ceil_si = ((int(hex_string, 16)) & mask_cpr_saw_load_voltage_ceil_si) >>  0

   print "{0:4} {1:5} {2:1} {3:1} {4:1} {5:1} {6:1} {7:4} {8:5} {9:1} {10:1} {11:1} {12:1} {13:1}"\
   .format(field_tied_to_zero_go,
           field_cpr_saw_steps_go,
           field_cpr_saw_up_go,
           field_cpr_saw_down_go,
           field_cpr_saw_load_voltage_go,
           field_cpr_saw_load_floor_go,
           field_cpr_saw_load_voltage_ceil_go,
           field_tied_to_zero_si,
           field_cpr_saw_steps_si,
           field_cpr_saw_up_si,
           field_cpr_saw_down_si,
           field_cpr_saw_load_voltage_si,
           field_cpr_saw_load_floor_si,
           field_cpr_saw_load_voltage_ceil_si)

   if excel:
      print >> output_file_object, "," + str(field_tied_to_zero_go             ),
      print >> output_file_object, "," + str(field_cpr_saw_steps_go            ),
      print >> output_file_object, "," + str(field_cpr_saw_up_go               ),
      print >> output_file_object, "," + str(field_cpr_saw_down_go             ),
      print >> output_file_object, "," + str(field_cpr_saw_load_voltage_go     ),
      print >> output_file_object, "," + str(field_cpr_saw_load_floor_go       ),
      print >> output_file_object, "," + str(field_cpr_saw_load_voltage_ceil_go),
      print >> output_file_object, "," + str(field_tied_to_zero_si             ),
      print >> output_file_object, "," + str(field_cpr_saw_steps_si            ),
      print >> output_file_object, "," + str(field_cpr_saw_up_si               ),
      print >> output_file_object, "," + str(field_cpr_saw_down_si             ),
      print >> output_file_object, "," + str(field_cpr_saw_load_voltage_si     ),
      print >> output_file_object, "," + str(field_cpr_saw_load_floor_si       ),
      print >> output_file_object, "," + str(field_cpr_saw_load_voltage_ceil_si)
   return

######################
### parse cmd line ###
######################

parser = argparse.ArgumentParser(description="Parse OLC trace data")
parser.add_argument("INPUT_FILE", help="trace data, in JSON/txt format, saved from QTF tool" )
parser.add_argument("TRACE_TYPE", help="type of trace",
                                  choices=["osm0", "osm1", "osm2", "osm3", "llm", "cprh", "apm"])
parser.add_argument("-x", "--excel", help="create Excel/cvs output", action="store_true")
parser.add_argument("-v", "--vcd", help="create vcd output", action="store_true")
args = parser.parse_args()

input_file  = args.INPUT_FILE
packet_type = args.TRACE_TYPE
excel       = args.excel
vcd         = args.vcd

##################
### open files ###
##################

input_file_object = open(input_file, "r")

if excel:
   output_file_object = open(input_file+".csv", "w")

if vcd:
   vcd_file_object = open(input_file+".vcd", "w")

#########################
### print header info ###
#########################

print ""
print "input file: ", input_file
print "packet type:", packet_type
print "excel:      ", excel
print "vcd:        ", vcd
print ""

if packet_type == "osm0":
   print "                                                         sw_lut_index ------------------------------------.          "
   print "                                                           arch_index                                      \         "
   print "                                                       lim_freq_index -------------------------------.      \        "
   print "                                                        lim_vol_index                                 \      \       "
   print "                                                   curr_working_index --------------------------.      \      \      "
   print "                                                        arch_core_cnt                            \      \      \     "
   print "                                                      sideband_select ----------------------.     \      \      \    "
   print "                                                        sideband_lval                        \     \      \      \   "
   print "                                                  cluster_power_state -----------------.      \     \      \      \  "
   print "                                                      core_cnt_to_cpr                   \      \     \      \      \ "
   print "                                                       rgen_fsm_state --------------.    \      \     \      \      |"
   print "                                                    dcvs_fe_fsm_state                \    \      \     \      |     |"
   print "                                                         be_fsm_state -----------.    \    \      \     |     |     |"
   print "                                                         dcvs_in_prgs             \    \    \      |    |     |     |"
   print "                                                     freq_chg_in_prgs --------.    \    \    |     |    |     |     |"
   print "                                                                  1b0          \    \    |   |     |    |     |     |"
   print "                                                                  1b0 -----.    \    |   |   |     |    |     |     |"
   print "                                                          apm_in_prgs       \    |   |   |   |     |    |     |     |"
   print "                                                            packet_id --.    |   |   |   |   |     |    |     |     |"
   print "                                                                         |   |   |   |   |   |     |    |     |     |"
   print "atid  chan            timestamp   ts delta opcode             payload    |   |   |   |   |   |     |    |     |     |"
   print "----  ----            ---------  --------- ------- ------------------    - - - - - - - - - - - --- - - -- -- -- -- --"

   if excel:
      print >> output_file_object, "atid,",
      print >> output_file_object, "chan,",
      print >> output_file_object, "timestamp,",
      print >> output_file_object, "ts delta,",
      print >> output_file_object, "opcode,",
      print >> output_file_object, "payload,",
      print >> output_file_object, "packet_id,",
      print >> output_file_object, "apm_in_prgs,",
      print >> output_file_object, "1b0,",
      print >> output_file_object, "1b0,",
      print >> output_file_object, "freq_chg_in_prgs,",
      print >> output_file_object, "dcvs_in_prgs,",
      print >> output_file_object, "be_fsm_state,",
      print >> output_file_object, "dcvs_fe_fsm_state,",
      print >> output_file_object, "rgen_fsm_state,",
      print >> output_file_object, "core_cnt_to_cpr,",
      print >> output_file_object, "cluster_power_state,",
      print >> output_file_object, "sideband_lval,",
      print >> output_file_object, "sideband_select,",
      print >> output_file_object, "arch_core_cnt,",
      print >> output_file_object, "curr_working_index,",
      print >> output_file_object, "lim_vol_index,",
      print >> output_file_object, "lim_freq_index,",
      print >> output_file_object, "arch_index,",
      print >> output_file_object, "sw_lut_index"

if packet_type == "osm1":
   print "                                                      core_cnt_to_cpr -----------------------------------------.        "
   print "                                                         raw_core_cnt                                           \       "
   print "                                                        arch_core_cnt -------------------------------------.     \      "
   print "                                                   vmin_red_fsm_state                                       \     \     "
   print "                                                        freq_4c_eq_1c ----------------------------------.    \     \    "
   print "                                             vmin_red_fsm_en_from_seq                                    \    \     \   "
   print "                                            vmin_red_fsm_dis_from_seq -------------------------------.    \    \     \  "
   print "                                                cc_safe_freq_achieved                                 \    \    \     \ "
   print "                                                    cpr_fsm_ack_to_be ---------------------------.     \    \    \     |"
   print "                                                    lmh_throttle_amnt                             \     \    \    \    |"
   print "                                          ps_computed_droop_code_div2 -----------------------.     \     \    \    |   |"
   print "                                                      ps_inc_throttle                         \     \     \    |   |   |"
   print "                                                ps_computed_dext_div8 -------------------.     \     \     |   |   |   |"
   print "                                                              ps_freq                     \     \     \    |   |   |   |"
   print "                                      ps_boost_fsm_sideband_lval_div2 ------------.        \     \     |   |   |   |   |"
   print "                                                   ps_boost_fsm_state              \        \     |    |   |   |   |   |"
   print "                                                   ps_droop_fsm_state -------.      \        |    |    |   |   |   |   |"
   print "                                                                spare         \      |       |    |    |   |   |   |   |"
   print "                                                            packed_id --.      |     |       |    |    |   |   |   |   |"
   print "                                                                         |     |     |       |    |    |   |   |   |   |"
   print "atid  chan            timestamp   ts delta opcode             payload    |     |     |       |    |    |   |   |   |   |"
   print "----  ----            ---------  --------- ------- ------------------    - --- - -- --- --- -- - -- -- - - - - - - - - -"

   if excel:
      print >> output_file_object, "atid,",
      print >> output_file_object, "chan,",
      print >> output_file_object, "timestamp,",
      print >> output_file_object, "ts delta,",
      print >> output_file_object, "opcode,",
      print >> output_file_object, "payload,",
      print >> output_file_object, "packed_id,",
      print >> output_file_object, "spare,",
      print >> output_file_object, "ps_droop_fsm_state,",
      print >> output_file_object, "ps_boost_fsm_state,",
      print >> output_file_object, "ps_boost_fsm_sideband_lval_div2,",
      print >> output_file_object, "ps_freq,",
      print >> output_file_object, "ps_computed_dext_div8,",
      print >> output_file_object, "ps_inc_throttle,",
      print >> output_file_object, "ps_computed_droop_code_div2,",
      print >> output_file_object, "lmh_throttle_amnt,",
      print >> output_file_object, "cpr_fsm_ack_to_be,",
      print >> output_file_object, "cc_safe_freq_achieved,",
      print >> output_file_object, "vmin_red_fsm_dis_from_seq,",
      print >> output_file_object, "vmin_red_fsm_en_from_seq,",
      print >> output_file_object, "freq_4c_eq_1c,",
      print >> output_file_object, "vmin_red_fsm_state,",
      print >> output_file_object, "arch_core_cnt,",
      print >> output_file_object, "raw_core_cnt,",
      print >> output_file_object, "core_cnt_to_cpr"

if packet_type == "osm2":
   print "                                                               branch ---------------------.   "
   print "                                                   power_control_bits                       \  "
   print "                                                     power_event_bits -------.               \ "
   print "                                                                spare         \               |"
   print "                                                            packed_id --.      |              |"
   print "                                                                         |     |              |"
   print "atid  chan            timestamp   ts delta opcode             payload    |     |              |"
   print "----  ----            ---------  --------- ------- ------------------    - - ----- ------ ---------"

   if excel:
      print >> output_file_object, "atid,",
      print >> output_file_object, "chan,",
      print >> output_file_object, "timestamp,",
      print >> output_file_object, "ts delta,",
      print >> output_file_object, "opcode,",
      print >> output_file_object, "payload,",
      print >> output_file_object, "packed_id,",
      print >> output_file_object, "spare,",
      print >> output_file_object, "power_event_bits,",
      print >> output_file_object, "power_control_bits,",
      print >> output_file_object, "branch,"

if packet_type == "osm3":
   print "                                                                                                                    "
   print "   NOTE: This parser uses droop_code_div2 of 6 bits, not 5 bits as per documentation, and dext_val_div8             "
   print "         of 7 bits, not 6 bits as per documentation.  This pushes all following fields down by 2 bits,              "
   print "         resulting in packet_id being dropped.  See Kapila for details.                                             "
   print "                                                                                                                    "
   print "                                                                                                                    "
   print "                                                            force_cfa                                               "
   print "                                                        dext_val_div8 ---------------------------------.            "
   print "                                                      sideband_select                                   \           "
   print "                                                   sideband_lval_div2 ----------------------------.      \          "
   print "                                                      droop_code_div2                              \      \         "
   print "                                                   ps_boost_fsm_state -----------------------.      \      \        "
   print "                                                 dcvs_boost_fsm_state                         \      \      \       "
   print "                                                   cc_boost_fsm_state ------------------.      \      \      \      "
   print "                                                   ps_droop_fsm_state                    \      \      \      \     "
   print "                                                 dcvs_droop_fsm_state --------------.     \      \      \      \    "
   print "                                        pc_ret_exit_droop_fsm_state_0                \     \      \      \      |   "
   print "                                        pc_ret_exit_droop_fsm_state_1 -----------.    \     \      \      |     |   "
   print "                                        pc_ret_exit_droop_fsm_state_2             \    \     \      |     |     |   "
   print "                                        pc_ret_exit_droop_fsm_state_3 --------.    \    \     |     |     |     |   "
   print "                                                wfx_droop_fsm_state_0          \    \    |    |     |     |     |   "
   print "                                                wfx_droop_fsm_state_1 -----.    \    |   |    |     |     |     |   "
   print "                                                wfx_droop_fsm_state_2       \    |   |   |    |     |     |     |   "
   print "                                                wfx_droop_fsm_state_3 --.    |   |   |   |    |     |     |     |   "
   print "                                                  packet_id (dropped)    |   |   |   |   |    |     |     |     |   "
   print "                                                                         |   |   |   |   |    |     |     |     |   "
   print "atid  chan            timestamp   ts delta opcode             payload    |   |   |   |   |    |     |     |     |   "
   print "----  ----            ---------  --------- ------- ------------------    - - - - - - - - - - -- -- -- -- --- - --- -"

   if excel:
      print >> output_file_object, "atid,",
      print >> output_file_object, "chan,",
      print >> output_file_object, "timestamp,",
      print >> output_file_object, "ts delta,",
      print >> output_file_object, "opcode,",
      print >> output_file_object, "payload,",
      #print >> output_file_object, "packet_id,",
      print >> output_file_object, "wfx_droop_fsm_state_3,",
      print >> output_file_object, "wfx_droop_fsm_state_2,",
      print >> output_file_object, "wfx_droop_fsm_state_1,",
      print >> output_file_object, "wfx_droop_fsm_state_0,",
      print >> output_file_object, "pc_ret_exit_droop_fsm_state_3,",
      print >> output_file_object, "pc_ret_exit_droop_fsm_state_2,",
      print >> output_file_object, "pc_ret_exit_droop_fsm_state_1,",
      print >> output_file_object, "pc_ret_exit_droop_fsm_state_0,",
      print >> output_file_object, "dcvs_droop_fsm_state,",
      print >> output_file_object, "ps_droop_fsm_state,",
      print >> output_file_object, "cc_boost_fsm_state,",
      print >> output_file_object, "dcvs_boost_fsm_state,",
      print >> output_file_object, "ps_boost_fsm_state,",
      print >> output_file_object, "droop_code_div2,",
      print >> output_file_object, "sideband_lval_div2,",
      print >> output_file_object, "sideband_select,",
      print >> output_file_object, "dext_val_div8,",
      print >> output_file_object, "force_cfa"

if packet_type == "llm":
   print "                                                    active core count ----------------------------.      "
   print "                       the latest temperature sample (2 lsbs dropped)                              \     "
   print "                                            average current violation ---------------------.        \    "
   print "                                                        bcl violation                       \        \   "
   print "                                     current frequency of the cluster ----------------.      \        \  "
   print "                          dcvsh frequency decision from current block                  \      \        \ "
   print "                          dcvsh frequency decision from thermal block ---------.        \      \        |"
   print "                              dcvsh frequency decision from bcl block           \        \      |       |"
   print "                                 voltage limit from reliability block ---.       \        |     |       |"
   print "                                                                          |       |       |     |       |"
   print "atid  chan            timestamp   ts delta opcode             payload     |       |       |     |       |"
   print "----  ----            ---------  --------- ------- ------------------    --- --- --- --- --- - --- ---- -"

   if excel:
      print >> output_file_object, "atid,",
      print >> output_file_object, "chan,",
      print >> output_file_object, "timestamp,",
      print >> output_file_object, "ts delta,",
      print >> output_file_object, "opcode,",
      print >> output_file_object, "payload,",
      print >> output_file_object, "voltage_lmt,",
      print >> output_file_object, "dcvsh_freq_des_bcl_blk,",
      print >> output_file_object, "dcvsh_freq_des_therm_blk,",
      print >> output_file_object, "dcvsh_freq_des_current_blk,",
      print >> output_file_object, "current_cluster_freq,",
      print >> output_file_object, "bcl_violation,",
      print >> output_file_object, "avg_current_violation,",
      print >> output_file_object, "latest_temp_sample,",
      print >> output_file_object, "active_core_cnt,"

   if vcd:
      print >> vcd_file_object, "$timescale 1 ns $end"
      print >> vcd_file_object, "$var integer 7 ? atid $end"
      print >> vcd_file_object, "$var integer 16 ! chan $end"
      print >> vcd_file_object, "$var integer 9 @ voltage_lmt $end"
      print >> vcd_file_object, "$var integer 8 # dcvsh_freq_des_bcl_blk $end"
      print >> vcd_file_object, "$var integer 8 % dcvsh_freq_des_therm_blk $end"
      print >> vcd_file_object, "$var integer 8 ^ dcvsh_freq_des_current_blk $end"
      print >> vcd_file_object, "$var integer 8 & current_cluster_freq $end"
      print >> vcd_file_object, "$var integer 3 * bcl_violation $end"
      print >> vcd_file_object, "$var integer 8 ( avg_current_violation $end"
      print >> vcd_file_object, "$var integer 10 ) latest_temp_sample $end"
      print >> vcd_file_object, "$var integer 2 : active_core_cnt $end"
      print >> vcd_file_object, "$enddefinitions $end"

if packet_type == "apm":
   print "                                                         pgs_idle_bus ---------------------------.     "
   print "                                                         mas_idle_int                             \    "
   print "                                          o_apm_ctl_cci_forceclockoff -------------------.         \   "
   print "                                          apmctl_cl_forceclockoff_raw                     \         \  "
   print "                                                apm_ctl_serfreeze_dis ----------------.    \         | "
   print "                                                 apmctl_serfreeze_raw                  \    |        | "
   print "                                                         tied_to_zero --------.         |   |        | "
   print "                                                                               |        |   |        | "
   print "atid  chan            timestamp   ts delta opcode             payload          |        |   |        | "
   print "----  ----            ---------  --------- ------- ------------------    ------------ - - - - ---- ----"

   if excel:
      print >> output_file_object, "atid,",
      print >> output_file_object, "chan,",
      print >> output_file_object, "timestamp,",
      print >> output_file_object, "ts delta,",
      print >> output_file_object, "opcode,",
      print >> output_file_object, "payload,",
      print >> output_file_object, "field_tied_to_zero,",
      print >> output_file_object, "field_apmctl_serfreeze_raw,",
      print >> output_file_object, "field_apm_ctl_serfreeze_dis,",
      print >> output_file_object, "field_apmctl_cl_forceclockoff_raw,",
      print >> output_file_object, "field_o_apm_ctl_cci_forceclockoff,",
      print >> output_file_object, "field_mas_idle_int,",
      print >> output_file_object, "field_pgs_idle_bus,"

if packet_type == "cprh":
   print "                                         cpr_saw_load_voltage_ceil_si                                             "
   print "                                                cpr_saw_load_floor_si -------------------------------------.      "
   print "                                              cpr_saw_load_voltage_si                                       \     "
   print "                                                      cpr_saw_down_si ----------------------------------.    \    "
   print "                                                        cpr_saw_up_si                                    \    \   "
   print "                                                     cpr_saw_steps_si ----------------------------.       \    |  "
   print "                                                      tied_to_zero_si                              \       |   |  "
   print "                                                                                                    \      |   |  "  
   print "                                         cpr_saw_load_voltage_ceil_go ------------------.            |     |   |  "
   print "                                                cpr_saw_load_floor_go                    \           |     |   |  "
   print "                                              cpr_saw_load_voltage_go ---------------.    \          |     |   |  "
   print "                                                      cpr_saw_down_go                 \    \         |     |   |  "
   print "                                                        cpr_saw_up_go ------------.    \    |        |     |   |  "
   print "                                                     cpr_saw_steps_go              \    |   |        |     |   |  "
   print "                                                      tied_to_zero_go ----.         |   |   |        |     |   |  "
   print "                                                                           |        |   |   |        |     |   |  "
   print "atid  chan            timestamp   ts delta opcode             payload      |        |   |   |        |     |   |  "
   print "----  ----            ---------  --------- ------- ------------------    ---- ----- - - - - - ---- ----- - - - - -"
   
   if excel:
      print >> output_file_object, "atid,",
      print >> output_file_object, "chan,",
      print >> output_file_object, "timestamp,",
      print >> output_file_object, "ts delta,",
      print >> output_file_object, "opcode,",
      print >> output_file_object, "payload,",
      print >> output_file_object, "field_tied_to_zero_go,",
      print >> output_file_object, "field_cpr_saw_steps_go,",
      print >> output_file_object, "field_cpr_saw_up_go,",
      print >> output_file_object, "field_cpr_saw_down_go,",
      print >> output_file_object, "field_cpr_saw_load_voltage_go,",
      print >> output_file_object, "field_cpr_saw_load_floor_go,",
      print >> output_file_object, "field_cpr_saw_load_voltage_ceil_go,",
      print >> output_file_object, "field_tied_to_zero_si,",
      print >> output_file_object, "field_cpr_saw_steps_si,",
      print >> output_file_object, "field_cpr_saw_up_si,",
      print >> output_file_object, "field_cpr_saw_down_si,",
      print >> output_file_object, "field_cpr_saw_load_voltage_si,",
      print >> output_file_object, "field_cpr_saw_load_floor_si,",
      print >> output_file_object, "field_cpr_saw_load_voltage_ceil_si,"

#################
### main loop ###
#################

channel   = 0
prev_ts   = 0

for line in input_file_object:
   atid      = 0
   opcode    = ""
   payload   = ""
   timestamp = 0

   line = line.rstrip("\r\n")
   line = line.strip("{}")
   line = line.replace("\"", "")

   fields = line.split(",")

   for field in fields:
      field = field.replace(" ", "")
      data = field.split(":")

      if data[0] == "ATID":      atid      = int(data[1], 10)
      if data[0] == "OpCode":    opcode    = data[1]
      if data[0] == "Payload":   payload   = data[1]
      if data[0] == "Timestamp": timestamp = int(data[1], 10)

   if (opcode.lower().startswith("c")):
      channel = int(payload, 16)

   if (opcode.lower().startswith("d")):
      print "{0:4} {1:5} {2:20} {3:10} {4:7} {5:>18}   ".format(atid, channel, timestamp, (timestamp-prev_ts), opcode, payload),
      if excel:
         print >> output_file_object, str(atid) + "," + str(channel) + "," + str(timestamp) + ",",
         print >> output_file_object, str(timestamp-prev_ts) + "," + opcode + "," + payload,
      if vcd:
         print >> vcd_file_object, "#{0}".format(timestamp)
         print >> vcd_file_object, "r{0} ?".format(atid)
         print >> vcd_file_object, "r{0} !".format(channel)

      if packet_type == "osm0":
         packet_type_osm0(payload)
      elif packet_type == "osm1":
         packet_type_osm1(payload)
      elif packet_type == "osm2":
         packet_type_osm2(payload)
      elif packet_type == "osm3":
         packet_type_osm3(payload)
      elif packet_type == "llm":
         packet_type_llm(payload)
      elif packet_type == "cprh":
         packet_type_cprh(payload)
      elif packet_type == "apm":
         packet_type_apm(payload)
      else:
         print ""
         if excel:
            print >> output_file_object, ""

      prev_ts = timestamp

   if (opcode.lower().startswith("flag_ts")):
      print "{0:4} {1:5} {2:20} {3:10} {4:7}                      ".format(atid, channel, timestamp, (timestamp-prev_ts), opcode)
      if excel:
         print >> output_file_object, str(atid) + "," + str(channel) + "," + str(timestamp) + ",",
         print >> output_file_object, str(timestamp-prev_ts) + "," + opcode + ",,"

      prev_ts = timestamp

############################
### close files and exit ###
############################

input_file_object.close()

if excel:
   output_file_object.close()

if vcd:
   vcd_file_object.close()
