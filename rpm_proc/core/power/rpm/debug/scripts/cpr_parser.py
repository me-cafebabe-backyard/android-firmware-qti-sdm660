import sys, re, os, struct
from base_parser import Parser
from target_data import *

def parse_rail_mode(rail_mode):
    rail = 0xffff & (rail_mode >> 16)
    mode = 0xffff & rail_mode
    return get_cpr_rail_name(rail), get_cpr_mode_name(mode)

class CprInit:
    __metaclass__ = Parser
    id = 670
    def parse(self, data):
        return 'cpr_init (chip_version 0x%x) (foundry 0x%x) (cpr_rev 0x%x)' % \
                (data[0], data[1], data[2])

class CprRailInit:
    __metaclass__ = Parser
    id = 671
    def parse(self, data):
        rail, mode = parse_rail_mode(data[0])
        return 'cpr_rail_init (rail %s) (mode %s) (global_ceiling_uv %d) (global_floor_uv %d)' % \
                (rail, mode, data[1], data[2])

class CprRailInitOpenLoop:
    __metaclass__ = Parser
    id = 672
    def parse(self, data):
        rail, mode = parse_rail_mode(data[0])
        return 'cpr_rail_init_open_loop (rail %s) (mode %s) (ceiling_uv %d) (floor_uv %d)' % \
                (rail, mode, data[1], data[2])

class CprRailInitSmem:
    __metaclass__ = Parser
    id = 673
    def parse(self, data):
        rail, mode = parse_rail_mode(data[0])
        return 'cpr_rail_init_smem (rail %s) (mode %s) (ceiling_uv %d) (floor_uv %d) (total_margin_mv %d)' % \
                (rail, mode, data[1], data[2], data[3])

class CprRailEnable:
    __metaclass__ = Parser
    id = 674
    def parse(self, data):
        rail, mode = parse_rail_mode(data[0])
        up_count, down_count = (0xffff&(data[2]>>16)), (0xffff&data[2])
        return 'cpr_rail_enable (rail %s) (mode %s) (current_uv %d) (up_count %d) (down_count %d)' % \
                (rail, mode, data[1], up_count, down_count)

class CprRailIsr:
    __metaclass__ = Parser
    id = 675
    def parse(self, data):
        rail, mode = parse_rail_mode(data[0])
        up_int, down_int = (0xffff&(data[2]>>16)), (0xffff&data[2])
        return 'cpr_rail_isr (rail %s) (mode %s) (recommendation_uv %d) (up_int %d) (down_int %d)' % \
                (rail, mode, data[1], up_int, down_int)

class CprHalSetTempBands:
    __metaclass__ = Parser
    id = 676
    def parse(self, data):
        hot_temp    = (0xfff & (data[3]))/10.0
        hot_sensor  = 0xf & (data[3] >> 12)
        cold_temp   = (0xfff & (data[3] >> 16))/10.0
        cold_sensor = 0xf & (data[3] >> 28)
        return 'cpr_hal_set_temp_bands (%s controller) (mode %s) (temp_bands 0x%0.8x) (hot_temp %.1f) (hot_sensor %d) (cold_temp %.1f) (cold_sensor %d)' % \
                (get_cpr_controller_name(data[0]), get_cpr_mode_name(data[1]), data[2], hot_temp, hot_sensor, cold_temp, cold_sensor)

class CprRailDisableMode:
    __metaclass__ = Parser
    id = 677
    def parse(self, data):
        rail, mode = parse_rail_mode(data[0])
        return 'cpr_rail_disable_mode (rail %s) (mode %s) (use_openloop_mode %s) (use_closedloop_mode %s)' % \
                (rail, mode, get_cpr_mode_name(data[1]), get_cpr_mode_name(data[2]))

