#  ===========================================================================
#
#  Copyright (c) 2014-2015 Qualcomm Technologies Incorporated.  
#  All Rights Reserved.
#  QUALCOMM Proprietary and Confidential.
#
#  ===========================================================================


from __future__ import print_function

import logging
logger = logging.getLogger(__name__)

import os
import itertools
import math
from binascii import hexlify
from locators.core_dump import locate as locate_core_dump
from dwarf import decode_object, Structure
from dwarf import Array as darray
from hansei_utils import *

rbcpr_operation_modes = [
    "RBCPR-Disabled",
    "RBCPR-Enabled-Open-Loop",
    "RBCPR-Enabled-Closed-Loop",
]

railway_corner_names = {
    "RAILWAY_NO_REQUEST"            : 0,
    "RAILWAY_RETENTION"             : 1,
    "RAILWAY_SVS_KRAIT"             : 2,
    "RAILWAY_SVS_SOC"               : 3,
    "RAILWAY_SVS_HIGH"              : 4,
    "RAILWAY_NOMINAL"               : 5,
    "RAILWAY_TURBO"                 : 6,
    "RAILWAY_TURBO_HIGH"            : 7,
    "RAILWAY_SUPER_TURBO"           : 8,
    "RAILWAY_SUPER_TURBO_NO_CPR"    : 9,
}

dump_error = 0 # should only be used for error that indicate dump corruption

def dump(debug_data): #dump_path, memory, debug_info, fill_char):
    global dump_error
    dump_error = 0
    memory = debug_data['rpm_memory']
    debug_info = debug_data['debug_info']
    fill_char = debug_data['args'].fill_char
    dump_path = debug_data['dump_path']
    
    debug_data['printer'].p("Dumping rbcpr state...")
    
    address = locate_core_dump(memory, debug_info)
    dump_type = debug_info.variables['rpm_core_dump'].vartype
    rpm_core_dump = decode_object('rpm_core_dump', address, dump_type, memory, debug_info)

    #import pdb; pdb.set_trace()
    rpm = cast(rpm_core_dump.rpmserver_state, 'SystemData', memory, debug_info)

    #save_logger_level = update_logger(logging.DEBUG, logging)
    dump_cpr(dump_path, rpm, memory, debug_info, fill_char)
    #update_logger(save_logger_level, logging)
    
    if dump_error != 0:
      debug_data['printer'].p("\t...Non-critical errors occured in processing dump, continuing")
    else:
      debug_data['printer'].p("\t...DONE")

def dump_cpr(dump_path, rpm, memory, debug_info, fill_char):
  rbcpr_file_name = os.path.join(dump_path, 'rbcpr.txt')
  with open(rbcpr_file_name, 'w') as file:
    # check driver version
    # call correct dumper
    try:
      cpr3_test = debug_info.variables['cpr3_controller_config'].die
      dump_cpr3(dump_path, rpm, memory, debug_info, fill_char, file)
      return
    except:
      dump_rbcpr(dump_path, rpm, memory, debug_info, fill_char, file)
  
def dump_cpr3(dump_path, rpm, memory, debug_info, fill_char, cpr3_file):
  # START THE DUMPING
  print("", file=cpr3_file)
  print("----------------------------------------", file=cpr3_file)
  print("-------------- CPR3 DUMP ---------------", file=cpr3_file)
  print("----------------------------------------\n", file=cpr3_file)
  
  try:
    # cpr3_contoller_config
    '''
    var_type = debug_info.variables['cpr3_controller_config'].die
    var_addr = debug_info.variables['cpr3_controller_config'].address
    cpr3_controller_config = decode_object('cpr3_controller_config', var_addr, 
                                           None, memory, debug_info, die=var_type)
    
    print("cpr3_controller_config", file=cpr3_file)
    print("\t.{0} = {1}".format("initialized",cpr3_controller_config.initialized), file=cpr3_file)
    print("\t.{0} = {1}".format("sensor_count",cpr3_controller_config.sensor_count), file=cpr3_file)
    print("\t.{0} = {1}".format("thread_count",cpr3_controller_config.thread_count), file=cpr3_file)
    print("\t.{0} = {1}".format("sensors_to_bypass_count",cpr3_controller_config.sensors_to_bypass_count), file=cpr3_file)
    print("\t.{0}:".format("sensors_to_bypass"), file=cpr3_file)
    for i in range(cpr3_controller_config.sensors_to_bypass_count):
      print("\t\t[{0}] = {1}".format(i,cpr3_controller_config.sensors_to_bypass[i]), file=cpr3_file)
    '''
    #cpr_bsp_closed_loop_config
    var_type = debug_info.variables['cpr_bsp_closed_loop_config'].die
    var_addr = debug_info.variables['cpr_bsp_closed_loop_config'].address
    cpr_bsp_closed_loop_config = decode_object('cpr_bsp_closed_loop_config',
                                               var_addr, None, memory, debug_info, 
                                               die=var_type)
    
    print("cpr_bsp_closed_loop_config:", file=cpr3_file)
    print("\t.{0} = {1}".format("closed_loop_count",cpr_bsp_closed_loop_config.closed_loop_config_count), file=cpr3_file)
    print("\t.{0}:".format("closed_loop_config"), file=cpr3_file)
    for i in range(cpr_bsp_closed_loop_config.closed_loop_config_count):
      print("\t\t[{0}] @0x{1:0>8x}".format(i, cpr_bsp_closed_loop_config.closed_loop_config[i].address), file=cpr3_file)
      #rail_id
      print("\t\t\t.{0} = {1}".format("rail_id",cpr_bsp_closed_loop_config.closed_loop_config[i].rail_id), file=cpr3_file)
      #ref_clk_resource
      print("\t\t\t.{0} = 0x{1:0>8x}".format("ref_clk_resource",cpr_bsp_closed_loop_config.closed_loop_config[i].ref_clk_resource.address), file=cpr3_file)
      #ahb_clk_resource
      print("\t\t\t.{0} = 0x{1:0>8x}".format("ahb_clk_resource",cpr_bsp_closed_loop_config.closed_loop_config[i].ahb_clk_resource.address), file=cpr3_file)
      #hal_handle
      print("\t\t\t.{0}:".format("hal_handle"), file=cpr3_file)
      print("\t\t\t\t.{0} = 0x{1:0>8x}".format("hw_base_address",cpr_bsp_closed_loop_config.closed_loop_config[i].hal_handle.hw_base_address), file=cpr3_file)
      print("\t\t\t\t.{0} = {1}".format("thread",cpr_bsp_closed_loop_config.closed_loop_config[i].hal_handle.thread), file=cpr3_file)
      #sensors_to_mask
      print("\t\t\t.{0} = {1}".format("sensors_to_mask_count",cpr_bsp_closed_loop_config.closed_loop_config[i].sensors_to_mask_count), file=cpr3_file)
      print("\t\t\t.{0}:".format("sensors_to_mask"), file=cpr3_file)
      for local_i in range(cpr_bsp_closed_loop_config.closed_loop_config[i].sensors_to_mask_count):
        print("\t\t\t\t[{0}] = {1}".format(local_i,cpr_bsp_closed_loop_config.closed_loop_config[i].sensors_to_mask[local_i]), file=cpr3_file)
      #aging_sensor_ids
      print("\t\t\t.{0} = {1}".format("aging_sensor_count",cpr_bsp_closed_loop_config.closed_loop_config[i].aging_sensor_count), file=cpr3_file)
      print("\t\t\t.{0}:".format("aging_sensor_ids"), file=cpr3_file)
      for local_i in range(cpr_bsp_closed_loop_config.closed_loop_config[i].aging_sensor_count):
        print("\t\t\t\t[{0}] = {1}".format(local_i,cpr_bsp_closed_loop_config.closed_loop_config[i].aging_sensor_ids[local_i]), file=cpr3_file)
      #aging_ro_kv_x100
      print("\t\t\t.{0} = {1}".format("aging_ro_kv_x100",cpr_bsp_closed_loop_config.closed_loop_config[i].aging_ro_kv_x100), file=cpr3_file)
      #aging_margin_limit
      print("\t\t\t.{0} = {1}".format("aging_margin_limit",cpr_bsp_closed_loop_config.closed_loop_config[i].aging_margin_limit), file=cpr3_file)
      #aging_voltage_mode
      print("\t\t\t.{0} = {1}".format("aging_voltage_mode",cpr_bsp_closed_loop_config.closed_loop_config[i].aging_voltage_mode), file=cpr3_file)
      #step_quot
      print("\t\t\t.{0} = {1}".format("step_quot",cpr_bsp_closed_loop_config.closed_loop_config[i].step_quot), file=cpr3_file)
      #interrupt_id
      print("\t\t\t.{0} = {1}".format("interrupt_id",cpr_bsp_closed_loop_config.closed_loop_config[i].interrupt_id), file=cpr3_file)
      #up_threshold
      print("\t\t\t.{0} = {1}".format("up_threshold",cpr_bsp_closed_loop_config.closed_loop_config[i].up_threshold), file=cpr3_file)
      #dn_threshold
      print("\t\t\t.{0} = {1}".format("dn_threshold",cpr_bsp_closed_loop_config.closed_loop_config[i].dn_threshold), file=cpr3_file)
      #consecutive_up
      print("\t\t\t.{0} = {1}".format("consecutive_up",cpr_bsp_closed_loop_config.closed_loop_config[i].consecutive_up), file=cpr3_file)
      #consecutive_dn
      print("\t\t\t.{0} = {1}".format("consecutive_dn",cpr_bsp_closed_loop_config.closed_loop_config[i].consecutive_dn), file=cpr3_file)
      #controller_config
      print("\t\t\t.{0}:".format("controller_config"), file=cpr3_file)
      controller_config = cpr_bsp_closed_loop_config.closed_loop_config[i].controller_config
      print("\t\t\t\t.{0} = {1}".format("initialized",controller_config.initialized), file=cpr3_file)
      print("\t\t\t\t.{0} = {1}".format("sensor_count",controller_config.sensor_count), file=cpr3_file)
      print("\t\t\t\t.{0} = {1}".format("thread_count",controller_config.thread_count), file=cpr3_file)
      print("\t\t\t\t.{0} = {1}".format("sensors_to_bypass_count",controller_config.sensors_to_bypass_count), file=cpr3_file)
      print("\t\t\t\t.{0}:".format("sensors_to_bypass"), file=cpr3_file)
      for i in range(controller_config.sensors_to_bypass_count):
        print("\t\t\t\t\t[{0}] = {1}".format(i,controller_config.sensors_to_bypass[i]), file=cpr3_file)
      print("", file=cpr3_file)
    print("", file=cpr3_file)
    
    #cpr_bsp_enablement_config
    var_type = debug_info.variables['cpr_bsp_enablement_config'].die
    var_addr = debug_info.variables['cpr_bsp_enablement_config'].address
    cpr_bsp_enablement_config = decode_object('cpr_bsp_enablement_config',
                                              var_addr, None, memory, debug_info, 
                                              die=var_type)
    
    print("cpr_bsp_enablement_config:", file=cpr3_file)
    print("\t.{0} = {1}".format("rail_enablement_config_count",cpr_bsp_enablement_config.rail_enablement_config_count), file=cpr3_file)
    print("\t.{0}:".format("rail_enablement_config"), file=cpr3_file)
    for i in range(cpr_bsp_enablement_config.rail_enablement_config_count):
      rail_enablement_config = cpr_bsp_enablement_config.rail_enablement_config[i]
      print("\t\t[{0}] @0x{1:0>8x}".format(i, rail_enablement_config.address), file=cpr3_file)
      #rail_id
      print("\t\t\t.{0} = {1}".format("rail_id",rail_enablement_config.rail_id), file=cpr3_file)
      #versioned_rail_config
      print("\t\t\t.{0} = {1}".format("versioned_rail_config_count",rail_enablement_config.versioned_rail_config_count), file=cpr3_file)
      print("\t\t\t.{0}:".format("versioned_rail_config"), file=cpr3_file)
      for local_i in range(rail_enablement_config.versioned_rail_config_count):
        versioned_rail_config = rail_enablement_config.versioned_rail_config[local_i]
        print("\t\t\t\t[{0}] @0x{1:0>8x}".format(local_i, versioned_rail_config.address), file=cpr3_file)
        #hw_version
        print("\t\t\t\t\t.{0}:".format("hw_version"), file=cpr3_file)
        hw_version = versioned_rail_config.hw_versions
        print("\t\t\t\t\t\t.{0} = {1}".format("foundry_range_count",hw_version.foundry_range_count), file=cpr3_file)
        for local_local_i in range(hw_version.foundry_range_count):
          print("\t\t\t\t\t\t\t[{0}]".format(local_local_i), file=cpr3_file)
          foundry_range = hw_version.foundry_range[local_local_i]
          print("\t\t\t\t\t\t\t\t.{0} = {1}".format("foundry_id",foundry_range.foundry_id), file=cpr3_file)
          print("\t\t\t\t\t\t\t\t.{0} = {1}".format("min_version",foundry_range.min_version), file=cpr3_file)
          print("\t\t\t\t\t\t\t\t.{0} = {1}".format("max_version",foundry_range.max_version), file=cpr3_file)
        #enablement_init_params
        print("\t\t\t\t\t.{0}:".format("enablement_init_params"), file=cpr3_file)
        enablement_init_params = versioned_rail_config.enablement_init_params
        print("\t\t\t\t\t\t.{0} = {1}".format("enablement_type",enablement_init_params.enablement_type), file=cpr3_file)
        print("\t\t\t\t\t\t.{0} = 0x{1:0>8x}".format("enablement_fn",enablement_init_params.enablement_fn.address), file=cpr3_file)
        #supported_level
        print("\t\t\t\t\t.{0} = {1}".format("supported_level_count", versioned_rail_config.supported_level_count), file=cpr3_file)
        print("\t\t\t\t\t.{0}:".format("supported_level"), file=cpr3_file)
        for local_local_i in range(versioned_rail_config.supported_level_count):
          supported_level = versioned_rail_config.supported_level[local_local_i]
          print("\t\t\t\t\t\t[{0}]:".format(local_local_i), file=cpr3_file)
          print("\t\t\t\t\t\t\t.{0} = {1}".format("voltage_mode",supported_level.voltage_mode), file=cpr3_file)
          print("\t\t\t\t\t\t\t.{0} = {1}".format("static_margin_mv",supported_level.static_margin_mv), file=cpr3_file)
          print("\t\t\t\t\t\t\t.{0} = 0x{1:0>8x}".format("custom_static_margin_fn",supported_level.custom_static_margin_fn.address), file=cpr3_file)
          print("\t\t\t\t\t\t\t.{0} = {1}".format("aging_scaling_factor",supported_level.aging_scaling_factor), file=cpr3_file)
        #custom_voltage_fn
        print("\t\t\t\t\t.{0} = 0x{1:0>8x}".format("custom_voltage_fn", versioned_rail_config.custom_voltage_fn.address), file=cpr3_file)
        #mode_to_settle
        print("\t\t\t\t\t.{0} = {1}".format("mode_to_settle_count", versioned_rail_config.mode_to_settle_count), file=cpr3_file)
        print("\t\t\t\t\t.{0}:".format("mode_to_settle"), file=cpr3_file)
        for local_local_i in range(versioned_rail_config.mode_to_settle_count):
          print("\t\t\t\t\t\t\t[{0}] = {1}".format(local_local_i, versioned_rail_config.mode_to_settle[local_local_i]), file=cpr3_file)
    print("", file=cpr3_file)
    
    #cpr_bsp_fuse_config
    var_type = debug_info.variables['cpr_bsp_fuse_config'].die
    var_addr = debug_info.variables['cpr_bsp_fuse_config'].address
    cpr_bsp_fuse_config = decode_object('cpr_bsp_fuse_config', var_addr, None,
                                        memory, debug_info, die=var_type)
    
    print("cpr_bsp_fuse_config:", file=cpr3_file)
    print("\t.{0} = {1}".format("number_of_fused_rails",cpr_bsp_fuse_config.number_of_fused_rails), file=cpr3_file)
    print("\t.{0}:".format("rail_fuse_config"), file=cpr3_file)
    for i in range(cpr_bsp_fuse_config.number_of_fused_rails):
      rail_fuse_config = cpr_bsp_fuse_config.rail_fuse_config[i]
      print("\t\t[{0}] @0x{1:0>8x}".format(i, rail_fuse_config.address), file=cpr3_file)
      #rail_id
      print("\t\t\t.{0} = {1}".format("rail_id",rail_fuse_config.rail_id), file=cpr3_file)
      print("\t\t\t.{0} = {1}".format("number_of_fuses",rail_fuse_config.number_of_fuses), file=cpr3_file)
      print("\t\t\t.{0}:".format("individual_fuse_configs"), file=cpr3_file)
      for local_i in range(rail_fuse_config.number_of_fuses):
        individual_fuse_configs = rail_fuse_config.individual_fuse_configs[local_i]
        print("\t\t\t\t[{0}]".format(local_i), file=cpr3_file)
        print("\t\t\t\t\t.{0} = {1}".format("fuse_type", individual_fuse_configs.fuse_type), file=cpr3_file)
        print("\t\t\t\t\t.{0} = {1}".format("fuse_total_bits", individual_fuse_configs.fuse_total_bits), file=cpr3_file)
        print("\t\t\t\t\t.{0} = {1}".format("cpr_fuse_value", individual_fuse_configs.cpr_fuse_value), file=cpr3_file)
        print("\t\t\t\t\t.{0} = {1}".format("number_of_partial_fuse_configs", individual_fuse_configs.number_of_partial_fuse_configs), file=cpr3_file)
        print("\t\t\t\t\t.{0}:".format("partial_individual_fuse_configs"), file=cpr3_file)
        for local_local_i in range(individual_fuse_configs.number_of_partial_fuse_configs):
          partial_individual_fuse_configs = individual_fuse_configs.partial_individual_fuse_configs[local_local_i]
          print("\t\t\t\t\t\t[{0}]".format(local_local_i), file=cpr3_file)
          print("\t\t\t\t\t\t\t.{0} = 0x{1:0>8x}".format("fuse_address", partial_individual_fuse_configs.fuse_address), file=cpr3_file)
          print("\t\t\t\t\t\t\t.{0} = {1}".format("offset", partial_individual_fuse_configs.offset), file=cpr3_file)
          print("\t\t\t\t\t\t\t.{0} = 0x{1:0>8x}".format("mask", partial_individual_fuse_configs.mask), file=cpr3_file)
    print("",file=cpr3_file)
    
    #cpr_bsp_misc_info_config
    var_type = debug_info.variables['cpr_bsp_misc_info_config'].die
    var_addr = debug_info.variables['cpr_bsp_misc_info_config'].address
    cpr_bsp_misc_info_config = decode_object('cpr_bsp_misc_info_config', var_addr, 
                                             None, memory, debug_info, die=var_type)
    
    print("cpr_bsp_misc_info_config:", file=cpr3_file)
    print("\t.{0} = {1}".format("rail_info_count",cpr_bsp_misc_info_config.rail_info_count), file=cpr3_file)
    print("\t.{0}:".format("rail_info"), file=cpr3_file)
    for i in range(cpr_bsp_misc_info_config.rail_info_count):
      rail_info = cpr_bsp_misc_info_config.rail_info[i]
      print("\t\t[{0}] @0x{1:0>8x}".format(i, rail_info.address), file=cpr3_file)
      #rail_id
      print("\t\t\t.{0} = {1}".format("rail_id",rail_info.rail_id), file=cpr3_file)
      print("\t\t\t.{0} = {1}".format("pmic_step_size",rail_info.pmic_step_size), file=cpr3_file)
    print("",file=cpr3_file)
    
    #cpr_bsp_voltage_ranges_config
    var_type = debug_info.variables['cpr_bsp_voltage_ranges_config'].die
    var_addr = debug_info.variables['cpr_bsp_voltage_ranges_config'].address
    cpr_bsp_voltage_ranges_config = decode_object('cpr_bsp_voltage_ranges_config', 
                                                  var_addr, None, memory, 
                                                  debug_info, die=var_type)
    
    print("cpr_bsp_voltage_ranges_config:", file=cpr3_file)
    print("\t.{0} = {1}".format("rail_voltage_range_count",cpr_bsp_voltage_ranges_config.rail_voltage_ranges_count), file=cpr3_file)
    print("\t.{0}:".format("rail_voltage_ranges"), file=cpr3_file)
    for i in range(cpr_bsp_voltage_ranges_config.rail_voltage_ranges_count):
      rail_voltage_ranges = cpr_bsp_voltage_ranges_config.rail_voltage_ranges[i]
      print("\t\t[{0}] @0x{1:0>8x}".format(i, rail_voltage_ranges.address), file=cpr3_file)
      #rail_id
      print("\t\t\t.{0} = {1}".format("rail_id",rail_voltage_ranges.rail_id), file=cpr3_file)
      #disable_fused_floor
      print("\t\t\t.{0} = {1}".format("disable_fused_floor",rail_voltage_ranges.disable_fused_floor), file=cpr3_file)
      #versioned_voltage_range
      print("\t\t\t.{0} = {1}".format("versioned_voltage_range_count",rail_voltage_ranges.versioned_voltage_range_count), file=cpr3_file)
      print("\t\t\t.{0}:".format("versioned_voltage_range"), file=cpr3_file)
      for local_i in range(rail_voltage_ranges.versioned_voltage_range_count):
        versioned_voltage_range = rail_voltage_ranges.versioned_voltage_range[local_i]
        print("\t\t\t\t[{0}]".format(local_i), file=cpr3_file)
        #hw_versions
        print("\t\t\t\t\t.{0}:".format("hw_versions"), file=cpr3_file)
        #foundry_range
        print("\t\t\t\t\t.{0} = {1}".format("foundry_range_count", versioned_voltage_range.hw_versions.foundry_range_count), file=cpr3_file)
        print("\t\t\t\t\t.{0}:".format("foundry_range"), file=cpr3_file)
        for local_local_i in range(versioned_voltage_range.hw_versions.foundry_range_count):
          foundry_range = versioned_voltage_range.hw_versions.foundry_range[local_local_i]
          print("\t\t\t\t\t\t[{0}]".format(local_local_i), file=cpr3_file)
          print("\t\t\t\t\t\t\t.{0} = {1}".format("foundry_id", foundry_range.foundry_id), file=cpr3_file)
          print("\t\t\t\t\t\t\t.{0} = {1}".format("min_version", foundry_range.min_version), file=cpr3_file)
          print("\t\t\t\t\t\t\t.{0} = {1}".format("max_version", foundry_range.max_version), file=cpr3_file)
        #voltage_level
        print("\t\t\t\t\t.{0} = {1}".format("voltage_level_count", versioned_voltage_range.voltage_level_count), file=cpr3_file)
        print("\t\t\t\t\t.{0}:".format("voltage_level"), file=cpr3_file)
        for local_local_i in range(versioned_voltage_range.voltage_level_count):
          voltage_level = versioned_voltage_range.voltage_level[local_local_i]
          print("\t\t\t\t\t\t[{0}]".format(local_local_i), file=cpr3_file)
          print("\t\t\t\t\t\t\t.{0} = {1}".format("voltage_mode", voltage_level.voltage_mode), file=cpr3_file)
          print("\t\t\t\t\t\t\t.{0} = {1}".format("voltage_ceiling", voltage_level.voltage_ceiling), file=cpr3_file)
          print("\t\t\t\t\t\t\t.{0} = {1}".format("voltage_floor", voltage_level.voltage_floor), file=cpr3_file)
          print("\t\t\t\t\t\t\t.{0} = {1}".format("voltage_fuse_ref", voltage_level.voltage_fuse_ref), file=cpr3_file)
          print("\t\t\t\t\t\t\t.{0} = {1}".format("fuse_correction_factor", voltage_level.fuse_correction_factor), file=cpr3_file)
          print("\t\t\t\t\t\t\t.{0} = {1}".format("fuse_type", voltage_level.fuse_type), file=cpr3_file)
    print("",file=cpr3_file)
    
    #cpr_chip_version
    var_type = debug_info.variables['cpr_chip_version'].die
    var_addr = debug_info.variables['cpr_chip_version'].address
    cpr_chip_version = decode_object('cpr_chip_version', var_addr, None, memory, 
                                     debug_info, die=var_type)
    print("cpr_chip_version:", file=cpr3_file)
    print("\t.{0} = 0x{1:0>8x}".format("cpr_chip_version",cpr_chip_version), file=cpr3_file)
    print("", file=cpr3_file)
    
    #cpr_foundry
    var_type = debug_info.variables['cpr_foundry'].die
    var_addr = debug_info.variables['cpr_foundry'].address
    cpr_foundry = decode_object('cpr_foundry', var_addr, None, memory, debug_info, 
                                die=var_type)
    print("cpr_foundry:", file=cpr3_file)
    print("\t.{0} = {1}".format("cpr_foundry",cpr_foundry), file=cpr3_file)
    print("", file=cpr3_file)
    
    #cpr_closed_loop_rail_root
    var_type = debug_info.variables['cpr_closed_loop_rail_root'].die
    var_addr = debug_info.variables['cpr_closed_loop_rail_root'].address
    cpr_closed_loop_rail_root = decode_object('cpr_closed_loop_rail_root', 
                                              var_addr, None, memory, debug_info, 
                                              die=var_type)
    print("cpr_closed_loop_rail_root:", file=cpr3_file)
    link = cpr_closed_loop_rail_root
    tab_depth = "\t"
    
    while link.address != 0:
      #rail_id
      print("{0}.{1} = {2}".format(tab_depth, "rail_id",link.rail_id), file=cpr3_file)
      #rail_config
      print("{0}.{1} = 0x{2:0>8x}".format(tab_depth, "rail_config",link.rail_config.address), file=cpr3_file)
      #voltage_control_handle
      print("{0}.{1} = 0x{2:0>8x}".format(tab_depth, "voltage_control_handle",link.voltage_control_handle.address), file=cpr3_file)
      #pmic_step_size
      print("{0}.{1} = {2}".format(tab_depth, "pmic_step_size",link.pmic_step_size), file=cpr3_file)
      #max_aging_delta
      print("{0}.{1} = {2}".format(tab_depth, "max_aging_delta",link.max_aging_delta), file=cpr3_file)
      #age_min
      print("{0}.{1} = {2}".format(tab_depth, "age_min",link.age_min), file=cpr3_file)
      #age_max
      print("{0}.{1} = {2}".format(tab_depth, "age_max",link.age_max), file=cpr3_file)
      
      #image_rail_state
      #import pdb; pdb.set_trace()
      # typedef 'var_type'_s * to 'var_type'_t makes pyelftools angry, need to cast it to 'var_type'_s
      image_rail_state = cast(link.image_rail_state, 'cpr_image_closed_loop_rail_s', memory, debug_info)
      print("{0}.{1}:".format(tab_depth, "image_rail_state"), file=cpr3_file)
      #image_rail_state.clock
      print("{0}\t.{1}:".format(tab_depth, "clock"), file=cpr3_file)
      count = 0
      for item in image_rail_state.clock:
        print("{0}\t\t[{1}]".format(tab_depth, count), file=cpr3_file)
        print("{0}\t\t\t.{1} = {2}".format(tab_depth, "clk_id",item.clk_id), file=cpr3_file)
        print("{0}\t\t\t.{1} = {2}".format(tab_depth, "enabled",item.enabled), file=cpr3_file)
        count += 1
      #image_rail_state.hal_core_dump
      hal_core_dump = cast(image_rail_state.hal_core_dump, 'HAL_cpr_dump_s', memory, debug_info)
      print("{0}\t.{1}:".format(tab_depth, "hal_core_dump"), file=cpr3_file)
      for item in hal_core_dump.members():
        print("{0}\t\t.{1} = {2}:".format(tab_depth, item[0], item[1]), file=cpr3_file)
      #image_rail_state.corner_lookup_index
      count = 0
      print("{0}\t.{1}:".format(tab_depth, "corner_lookup_index"), file=cpr3_file)
      for item in image_rail_state.corner_lookup_index:
        print("{0}\t\t{2}".format(tab_depth, count, item), file=cpr3_file)
        count += 1
      #image_rail_state.task
      print("{0}\t.{1} = {2}".format(tab_depth, "task", image_rail_state.task), file=cpr3_file)
      
      #block_enabled
      print("{0}.{1} = {2}".format(tab_depth, "block_enabled", link.block_enabled), file=cpr3_file)
      #cpr_handler_in_progress
      print("{0}.{1} = {2}".format(tab_depth, "cpr_handler_in_progress", link.cpr_handler_in_progress), file=cpr3_file)
      #target_params
      print("{0}.{1} = {2}".format(tab_depth, "target_params_count", link.target_params_count), file=cpr3_file)
      print("{0}.{1}:".format(tab_depth, "target_params"), file=cpr3_file)
      for i in range(link.target_params_count):
        target_params = link.target_params[i]
        print("{0}\t[{1}] @0x{2:0>8x}".format(tab_depth, i, target_params.address), file=cpr3_file)
        print("{0}\t\t.{1} = {2}".format(tab_depth, "voltage_mode", target_params.voltage_mode), file=cpr3_file)
        print("{0}\t\t.{1} = {2}".format(tab_depth, "voltage_ceil", target_params.voltage_ceil), file=cpr3_file)
        print("{0}\t\t.{1} = {2}".format(tab_depth, "voltage_floor", target_params.voltage_floor), file=cpr3_file)
        print("{0}\t\t.{1}:".format(tab_depth, "rosc_targets"), file=cpr3_file)
        print("{0}\t\t\t.{1}:".format(tab_depth, "ro_target_quotient"), file=cpr3_file)
        for item in target_params.rosc_targets.ro_target_quotient:
          print("{0}\t\t\t\t{1}".format(tab_depth, item), file=cpr3_file)
      print("{0}.{1} = 0x{2:0>8x}".format(tab_depth, "current_target_params", link.current_target_params.address), file=cpr3_file)
      print("{0}.{1}:".format(tab_depth, "rail_log"), file=cpr3_file)
      for item in link.rail_log.members():
        print("{0}\t.{1} = {2}".format(tab_depth, item[0], item[1]), file=cpr3_file)
      print("{0}.{1} [0x{2:0>8x}]:".format(tab_depth, "next_link", link.next_link.address), file=cpr3_file)
      print("", file=cpr3_file)
      #import pdb; pdb.set_trace()
      tab_depth+="\t"
      link = link.next_link
    
    #cpr_open_loop_rail_root
    var_type = debug_info.variables['cpr_open_loop_rail_root'].die
    var_addr = debug_info.variables['cpr_open_loop_rail_root'].address
    cpr_open_loop_rail_root = decode_object('cpr_open_loop_rail_root', 
                                              var_addr, None, memory, debug_info, 
                                              die=var_type)
    print("cpr_open_loop_rail_root:", file=cpr3_file)
    link = cpr_open_loop_rail_root
    tab_depth = "\t"  
    while link.address != 0:
      #rail_id
      print("{0}.{1} = {2}".format(tab_depth, "rail_id",link.rail_id), file=cpr3_file)
      print("{0}.{1} = 0x{2:0>8x}".format(tab_depth, "voltage_control_handle",link.voltage_control_handle.address), file=cpr3_file)
      print("{0}.{1} = 0x{2:0>8x}".format(tab_depth, "enablement_config",link.enablement_config.address), file=cpr3_file)
      print("{0}.{1} [0x{2:0>8x}]:".format(tab_depth, "next_link", link.next_link.address), file=cpr3_file)
      print("", file=cpr3_file)
      tab_depth+="\t"
      link = link.next_link
    print("----------------------------------------", file=cpr3_file)
    print("------------- END CPR3 DUMP ------------", file=cpr3_file)
    print("----------------------------------------", file=cpr3_file)
    return
  except:
    print("ERROR PARSING CPR3 STRUCTURES", file=cpr3_file)
    print("", file=cpr3_file)
    print("----------------------------------------", file=cpr3_file)
    print("------------- END CPR3 DUMP ------------", file=cpr3_file)
    print("----------------------------------------", file=cpr3_file)
  
  
    
def dump_rbcpr(dump_path, rpm, memory, debug_info, fill_char, rbcpr_file):
    # START THE DUMPING
    print("\n----------------------------------------", file=rbcpr_file)
    print("-------------- RBCPR DUMP --------------", file=rbcpr_file)
    print("----------------------------------------\n", file=rbcpr_file)
    
    # attempt to access rbcpr_bsp_data
    try:
        rbcpr_bsp_data_type = debug_info.variables['rbcpr_bsp_data'].die
        rbcpr_bsp_data_address = debug_info.variables['rbcpr_bsp_data'].address
        rbcpr_bsp_data = decode_object('rbcpr_bsp_data', rbcpr_bsp_data_address, None, memory, debug_info, die=rbcpr_bsp_data_type)
    except:
        print("Failed to find rbcpr_bsp_data variable", file=rbcpr_file)
        print("---------- ENDING RBCPR DUMP ----------", file=rbcpr_file)
        return
    
    rbcpr_bsp_rail_type = debug_info.types['rbcpr_bsp_rail_info']
    rbcpr_bsp_rail_array = darray('rbcpr_bsp_rail', rbcpr_bsp_data.rails.address, rbcpr_bsp_rail_type, rbcpr_bsp_data.num_rails, memory, debug_info)
    
    # attempt to access rbcpr_bsp_fuse_config
    try:
        rbcpr_bsp_fuse_config_type = debug_info.variables['rbcpr_bsp_fuse_config'].die
        rbcpr_bsp_fuse_config_address = debug_info.variables['rbcpr_bsp_fuse_config'].address
        rbcpr_bsp_fuse_config = decode_object('rbcpr_bsp_fuse_config', rbcpr_bsp_fuse_config_address, None, memory, debug_info, die=rbcpr_bsp_fuse_config_type)
    except:
        print("Failed to find rbcpr_bsp_fuse_config variable", file=rbcpr_file)
        print("---------- ENDING RBCPR DUMP ----------", file=rbcpr_file)
        return
    
    # attempt to access railway.rail_state
    try:
        railway_type = debug_info.variables['railway'].die
        railway_address = debug_info.variables['railway'].address
        railway = decode_object('railway', railway_address, None, memory, debug_info, die=railway_type)
    except:
        print("Failed to find railway variable", file=rbcpr_file)
        print("---------- ENDING RBCPR DUMP ----------", file=rbcpr_file)
        return
    
    print("------ RAILWAY AND BSP_DATA DUMP -------", file=rbcpr_file)
    
    for rail_num in range(rbcpr_bsp_data.num_rails):
        
    # RAILWAY DUMP
        rail = rbcpr_bsp_rail_array[rail_num]
        rail_name = pointer_to_str(rail.rail_const_info.rail_name)
        active_level = railway.rail_state[rail.railway_rail_id].current_active.mode
        active_voltage = railway.rail_state[rail.railway_rail_id].current_active.microvolts

        print("\n---------- Rail[%d]: %9s ----------" % (rail_num, rail_name), file=rbcpr_file)
        print("\tcpr_voltage_change_cnt   = %s" % rail.cpr_voltage_change_cnt, file=rbcpr_file)
        print("\tcpr_voltage_hit_floor    = %s" % rail.cpr_voltage_hit_floor, file=rbcpr_file)
        print("\tcpr_voltage_hit_ceiling  = %s" % rail.cpr_voltage_hit_ceiling, file=rbcpr_file)
        print("\tstep_up_count            = %s" % rail.step_up_count, file=rbcpr_file)
        print("\tstep_down_count          = %s" % rail.step_down_count, file=rbcpr_file)
        print("\tignored_readings         = %s\n" % rail.ignored_readings, file=rbcpr_file)
        print("\tactive_state             = %s" % (active_level),file=rbcpr_file)
        print("\tactive_voltage           = %s\n" % (active_voltage),file=rbcpr_file)
    # END RAILWAY DUMP

    # BSP_DATA DUMP
        try:
            bsp_data = rail.bsp_data
            rail_config = debug_info.types['rbcpr_bsp_rail_info']
            rbcpr_bsp_rail_array = darray('rbcpr_bsp_rail', rbcpr_bsp_data.rails.address, rbcpr_bsp_rail_type, rbcpr_bsp_data.num_rails, memory, debug_info)
        
            print("\tbsp_data:\n", file=rbcpr_file)
            print("\t\trbcpr_enablement     = %s\n" % (bsp_data.rbcpr_enablement), file=rbcpr_file)
            print("\t\ttarget_params:", file=rbcpr_file)

            for param in range(bsp_data.number_of_target_params):
                    
                level = bsp_data.target_params[param].corner_params.corner
                voltage_ceil = bsp_data.target_params[param].corner_params.voltage_ceil
                voltage_floor = bsp_data.target_params[param].corner_params.voltage_floor
                voltage = railway.rail_state[rail.railway_rail_id].corner_uvs[railway_corner_names[level]]
                fuse_name = bsp_data.target_params[param].corner_params.fuse
                fuse_value = "N/A"
        
                # find the fuse_value for the given fuse_type
                for fuse_num in range(rbcpr_bsp_fuse_config.rail_fuse_config[rail.railway_rail_id].number_of_fuses):
                    if rbcpr_bsp_fuse_config.rail_fuse_config[rail.railway_rail_id].individual_fuse_configs[fuse_num].fuse_type == fuse_name:
                        fuse_value = rbcpr_bsp_fuse_config.rail_fuse_config[rail.railway_rail_id].individual_fuse_configs[fuse_num].cpr_fuse_value
        
                print("\t\t{", file=rbcpr_file)
                print("\t\t\tlevel            = %s" % (level), file=rbcpr_file)
                print("\t\t\tfuse_name        = %s" % (fuse_name), file=rbcpr_file)
                print("\t\t\tfuse_value       = %s" % (fuse_value), file=rbcpr_file)
                print("\t\t\tceiling          = %s" % (voltage_ceil), file=rbcpr_file)
                print("\t\t\tfloor            = %s" % (voltage_floor), file=rbcpr_file)
                print("\t\t\tvoltage          = %s" % (voltage), file=rbcpr_file)
                print("\t\t}", file=rbcpr_file)
        
            print("----------------------------------------", file=rbcpr_file)
        except:
            print("\t----- Missing rbcpr_bsp_data (0x0 NULL) ------\n", file=rbcpr_file)
    # END BSP_DATA DUMP
        
    print("---- END RAILWAY AND BSP_DATA DUMP -----", file=rbcpr_file)
        
    # FUSE DUMP 
    print("\n----------- FUSE CONFIG DUMP -----------", file=rbcpr_file)
    print("\nNumber of fused rails   = %s" % (rbcpr_bsp_fuse_config.number_of_fused_rails), file=rbcpr_file)
        
    for fuse_count in range(rbcpr_bsp_fuse_config.number_of_fused_rails):
        
        rail_name = pointer_to_str(rbcpr_bsp_fuse_config.rail_fuse_config[fuse_count].rail_name)
        print("\n---------- Rail[%d]: %9s ----------" % (fuse_count, rail_name), file=rbcpr_file)
        
        for ind_fuse in range(rbcpr_bsp_fuse_config.rail_fuse_config[fuse_count].number_of_fuses):
            print("\t{", file=rbcpr_file)
            fuse_type = rbcpr_bsp_fuse_config.rail_fuse_config[fuse_count].individual_fuse_configs[ind_fuse].fuse_type
            cpr_fuse_value = rbcpr_bsp_fuse_config.rail_fuse_config[fuse_count].individual_fuse_configs[ind_fuse].cpr_fuse_value
        
            print("\t\tfuse_type            = %s" % (fuse_type), file=rbcpr_file)
            print("\t\tcpr_fuse_value       = %s" % (cpr_fuse_value), file=rbcpr_file)
            print("\t}", file=rbcpr_file)
        
        print("----------------------------------------", file=rbcpr_file)
        
    print("\n--------- END FUSE CONFIG DUMP ---------\n", file=rbcpr_file)
    # END FUSE DUMP
        
    print("----------------------------------------", file=rbcpr_file)
    print("------------- END RBCPR DUMP -----------", file=rbcpr_file)
    print("----------------------------------------", file=rbcpr_file)
    # END THE DUMPING