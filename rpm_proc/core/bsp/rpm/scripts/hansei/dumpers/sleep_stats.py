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
from dwarf import Array as darray
from hansei_utils import *

def dump(debug_data): #dump_path, memory, debug_info):
    memory = debug_data['rpm_memory']
    debug_info = debug_data['debug_info']
    dump_path = debug_data['dump_path']

    debug_data['printer'].p("Dumping sleep stats...")

    address = locate_core_dump(memory, debug_info)
    dump_type = debug_info.variables['rpm_core_dump'].vartype
    rpm_core_dump = decode_object('rpm_core_dump', address, dump_type, memory, debug_info)

    rpm = cast(rpm_core_dump.rpmserver_state, 'SystemData', memory, debug_info)

    if (check_member('sleep_stats', rpm_core_dump)):
        #sleep_stats in in core dump
        sleep = rpm_core_dump.sleep_stats
        sleep = cast(sleep, 'sleep_stats_type', memory, debug_info)
    else:
        try:
            sleep_type = debug_info.variables['sleep_stats'].die
        except:
            sleep_file_name = os.path.join(dump_path, 'sleep_stats.txt')
            with open(sleep_file_name, 'w') as sleep_file:
                print("\n !!! SLEEP_STATS DOES NOT EXIST, SLEEP IS LIKELY NOT ENABLED !!! \n", file=sleep_file)
            return
        try:
            #not in core dump, but elf is close enough to provide a correct pointer
            sleep_address = debug_info.variables['sleep_stats'].address # FIXME: get right address by magic
            sleep = decode_object('sleep_stats', sleep_address, None, memory, debug_info, die=sleep_type)
        except:
            #not correct in elf, find absolute address (very hacky)
            sleep_address = find_value(0x0019DBA0, 4, 0x00190000, 0x0019FFFF, memory)
            sleep = decode_object('sleep_stats', sleep_address, None, memory, debug_info, die=sleep_type)

    '''
    print(debug_info.variables['sleep_stats'].die)
    #sleep_address = 0x0019DBA0
    sleep_address = debug_info.variables['sleep_stats'].address
    sleep = decode_object('sleep_stats', sleep_address, sleep_type, memory, debug_info)
    '''

    #save_logger_level = update_logger(logging.DEBUG, logging)
    dump_sleep(dump_path, rpm, sleep, memory, debug_info)
    #update_logger(save_logger_level, logging)

def dump_sleep(dump_path, rpm, sleep, memory, debug_info):
    sleep_file_name = os.path.join(dump_path, 'sleep_stats.txt')
    with open(sleep_file_name, 'w') as sleep_file:

        print("\n ~~Sleep Stats Dump~~", file=sleep_file)
        print("\n\tVDD Low:", file=sleep_file)
        try:
            print('\t\tsleep_count:            %d' % sleep[0].count, file=sleep_file)
            print('\t\tlast_entered_at:        %s' % hex(sleep[0].last_entered_at), file=sleep_file)
            print('\t\tlast_exited_at:         %s' % hex(sleep[0].last_exited_at), file=sleep_file)
            print('\t\taccumulated_duration:   %s' % hex(sleep[0].accumulated_duration), file=sleep_file)
            print('\t\tclient_votes:           0x%08X' % (sleep[0].client_votes), file=sleep_file)
            print('', file=sleep_file)
            print('\t\tNOTE: This is history of XO clock votes. Each byte represents XO clock votes.', file=sleep_file)
            print('\t\t      MSB: Oldest XO clock votes.', file=sleep_file)
            print('\t\t      LSB: Current XO clock votes.', file=sleep_file)
            print('\t\t      For each byte:', file=sleep_file)
            print('\t\t          Bit 7 (0x%02X): Clock driver XO clock vote' % (1<<7), file=sleep_file)
            print('\t\t          Bit 6 (0x%02X): reserved' % (1<<6), file=sleep_file)
            print('\t\t          Bit 5 (0x%02X): SPSS         XO clock vote' % (1<<5), file=sleep_file)
            print('\t\t          Bit 4 (0x%02X): TZ           XO clock vote' % (1<<4), file=sleep_file)
            print('\t\t          Bit 3 (0x%02X): SSC          XO clock vote' % (1<<3), file=sleep_file)
            print('\t\t          Bit 2 (0x%02X): LPASS        XO clock vote' % (1<<2), file=sleep_file)
            print('\t\t          Bit 1 (0x%02X): MPSS         XO clock vote' % (1<<1), file=sleep_file)
            print('\t\t          Bit 0 (0x%02X): APSS         XO clock vote' % (1<<0), file=sleep_file)
            print('\t\t      For each bit:', file=sleep_file)
            print('\t\t          1: Need XO Clock          (Not ready for XO Shutdown.)', file=sleep_file)
            print('\t\t          0: Does not need XO clock (Ready for XO Shutdown.)', file=sleep_file)
        except:
            print('\t\tERROR READING sleep_stats[0]', file=sleep_file)
        print("\n\tVDD Min:", file=sleep_file)
        try:
            print('\t\tsleep_count:            %d' % sleep[1].count, file=sleep_file)
            print('\t\tlast_entered_at:        %s' % hex(sleep[1].last_entered_at), file=sleep_file)
            print('\t\tlast_exited_at:         %s' % hex(sleep[1].last_exited_at), file=sleep_file)
            print('\t\taccumulated_duration:   %s' % hex(sleep[1].accumulated_duration), file=sleep_file)
        except:
            print('\t\tERROR READING sleep_stats[1]', file=sleep_file)

