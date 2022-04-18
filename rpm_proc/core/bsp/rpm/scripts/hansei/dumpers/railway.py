#  ===========================================================================
#
#  Copyright (c) 2013-2016 Qualcomm Technologies, Inc.
#  All Rights Reserved.
#  QUALCOMM Proprietary and Confidential.
#
#  ===========================================================================


from __future__ import print_function

import logging
logger = logging.getLogger(__name__)

import os
import itertools
from binascii import hexlify
from locators.core_dump import locate as locate_core_dump
from dwarf import decode_object, Structure
from hansei_utils import *
import struct
import traceback


dump_error = 0 # should only be used for error that indicate dump corruption

def dump(debug_data): #dump_path, memory, debug_info):
    global dump_error, memory, debug_info
    dump_error = 0
    memory = debug_data['rpm_memory']
    debug_info = debug_data['debug_info']
    dump_path = debug_data['dump_path']

    debug_data['printer'].p("Dumping railway state...")

    address = locate_core_dump(memory, debug_info)
    dump_type = debug_info.variables['rpm_core_dump'].vartype
    rpm_core_dump = decode_object('rpm_core_dump', address, dump_type, memory, debug_info)

    #import pdb; pdb.set_trace()
    rpm = cast(rpm_core_dump.rpmserver_state, 'SystemData', memory, debug_info)

    #save_logger_level = logging.getLogger('dwarf').getEffectiveLevel()
    #print(save_logger_level)
    #logging.getLogger('dwarf').setLevel(logging.DEBUG)
    #print(logging.getLogger('dwarf').getEffectiveLevel())
    dump_railway(dump_path, rpm)
    #logging.getLogger('dwarf').setLevel(save_logger_level)

    if dump_error != 0:
      debug_data['printer'].p("\t...Non-critical errors occured in processing dump, continuing")
    else:
      debug_data['printer'].p("\t...DONE")


def write(str):
    global dump_file

    print(str, file=dump_file)

def get_variable(name):
    global memory, debug_info

    address    = debug_info.variables[name].address
    dump_type  = debug_info.variables[name].vartype
    variable   = decode_object(name, address, dump_type, memory, debug_info)

    return variable

def dump_railway(dump_path, rpm):
    global dump_error, dump_file
    ee_status_file_name = os.path.join(dump_path, 'railway.txt')

    rail_config_data = get_variable('RAILWAY_CONFIG_DATA')

    num_rails = rail_config_data.num_rails

    with open(ee_status_file_name, 'w') as f:
        dump_file = f
        railway = get_variable('railway')

        for rail_num in range(num_rails):
            try:
                rail = railway.rail_state[rail_num]
                rail_name = pointer_to_str(rail_config_data.rails[rail_num].vreg_name)
                write('\n\n ~~ RAIL %s ~~' % rail_name)

                write('\tCURRENT ACTIVE:')
                write('\t\tmode:                 %s' % rail.current_active.mode.replace('RAILWAY_',''))
                write('\t\tmicrovolts:           %d' % rail.current_active.microvolts)

                write('\tUNCONSTRAINED TARGET:')
                write('\t\tmode:                 %s' % rail.unconstrained_target.replace('RAILWAY_',''))

                write('\tCONSTRAINED TARGET:')
                write('\t\tmode:                 %s' % rail.constrained_target.mode.replace('RAILWAY_',''))
                write('\t\tmicrovolts:           %d' % rail.constrained_target.microvolts)

                write('\tVOTER LIST:')
                voter = rail.voter_list_head
                voter = cast(voter, 'railway_voter_s', memory, debug_info)
                tabs = "\t\t"
                write(tabs + '+-{0:-^30}-+-{1:-^20}-+-{2:-^20}-+-{3:-^14}-+'.format('-----', '--------------', '------------', '------------'))
                write(tabs + '| {0:^30} | {1:^20} | {2:^20} | {3:^14} |'.format('VOTER', 'VOLTAGE CORNER', 'ACTIVE_FLOOR', 'SUPPRESSIBLE'))
                write(tabs + '+-{0:-^30}-+-{1:-^20}-+-{2:-^20}-+-{3:-^14}-+'.format('-----', '--------------', '------------', '------------'))
                while(voter.address != 0):
                    try:
                        if voter.id < 100:
                            rpm_ee_type = ['APSS', 'MPSS', 'LPASS', 'WCNSS', 'TZ', 'SPSS']
                            voter_id = rpm_ee_type[voter.id]
                            #voter_id = cast(voter.id, 'rpm_ee_type', memory, debug_info).replace('RPM_EE_','')
                        else:
                            railway_voter_id = ['CPU','RPM_CX','RPM_MX','DDR_TRAINING','RPM_BRINGUP','RPM_INIT ','CLOCK_DRIVER',
                                                'CPR_SETTLING','RPM_CX_SLEEP','RPM_MX_SLEEP','OXILI_WORKAROUND','MISC_CX_MODULE',
                                                'MISC_GFX_MODULE','RPM_CX_NOMINAL_PIN','RPM_EBI','RPM_EBI_SLEEP','RPM_GFX_NOMINAL_PIN',
                                                'RPM_HALT_SVS2']
                            voter_id = railway_voter_id[voter.id-100]
                            #voter_id = cast(voter.id, 'railway_voter_id', memory, debug_info).replace('RAILWAY_','').replace('_ID','')
                        write(tabs + '| {0:<30} | {1:<20} | {2:<20} | {3:>14} |'.format(
                            voter_id,
                            voter.voltage_corner.replace('RAILWAY_',''),
                            voter.active_floor.replace('RAILWAY_',''),
                            voter.suppressible))
                        voter = voter.voter_link
                        voter = cast(voter, 'railway_voter_s', memory, debug_info)
                    except:
                        dump_error += 1
                        break
                write(tabs + '+-{0:-^30}-+-{1:-^20}-+-{2:-^20}-+-{3:-^14}-+'.format('-----', '--------------', '------------', '------------'))
                dump_rail_residence(rail_name)
            except:
                write('\t Failed to parse current state of rail #%d' % rail_num)
                write(traceback.format_exc())
                dump_error += 1

def dump_rail_residence(rail_name):
    rail_residence = get_variable('rail_residence')

    if rail_name == 'vddmx':
        dump_rail_residence_info(rail_residence.mx, rail_residence.mx_residence)
    elif rail_name == 'vddcx':
        dump_rail_residence_info(rail_residence.cx, rail_residence.cx_residence)
    elif rail_name == 'vdd_lpi_mx':
        dump_rail_residence_info(rail_residence.lpi_mx, rail_residence.lpi_mx_residence)
    elif rail_name == 'vdd_lpi_cx':
        dump_rail_residence_info(rail_residence.lpi_cx, rail_residence.lpi_cx_residence)

def dump_rail_residence_info(rail_info, rail_stat):
    global memory, debug_info
    corner_lut = {
        0x00746572 : 'RETENTION',
        0x32737673 : 'SVS2',
        0x00737673 : 'SVS',
        0x006d6f6e : 'NOMINAL',
        0x62727574 : 'TURBO',
    }
    write('\tRAIL RESIDENCE:')
    corner = rail_stat[rail_info.current_corner].corner
    write('\t\t{0:14} : {1}'.format('current_corner', corner_lut.get(corner,struct.pack('<I',corner).upper())))
    write('\t\t{0:14} : {1}'.format('last_entered', '0x%016X' % rail_info.last_entered))

    for i in range(rail_info.num_corners):
        corner = rail_stat[i].corner
        write('\t\t{0:14} : {1}'.format(corner_lut.get(corner,struct.pack('<I',corner).upper()), '0x%016X' % rail_stat[i].time))

