#  ===========================================================================
#
#  Copyright (c) 2016 Qualcomm Technologies, Inc.
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
import struct
import traceback


INDENT = ''


def dump(debug_data):
    global memory, debug_info

    memory     = debug_data['rpm_memory']
    debug_info = debug_data['debug_info']
    dump_path  = debug_data['dump_path']

    debug_data['printer'].p("Dumping MSG RAM...")

    #save_logger_level = update_logger(logging.DEBUG, logging)

    dump_msgram(dump_path)

    #update_logger(save_logger_level, logging)

    debug_data['printer'].p("\t...DONE")


def get_variable(name):
    global memory, debug_info

    #address    = debug_info.variables[name].address
    #dump_type  = debug_info.variables[name].vartype
    #variable   = decode_object(name, address, dump_type, memory, debug_info)
    type     = debug_info.variables[name].die
    address  = debug_info.variables[name].address
    variable = decode_object(name, address, None, memory, debug_info, die=type)

    return variable


def cast_address(typename, address):
    global memory, debug_info
    return cast(None, typename, memory, debug_info, address=address)


def cast_value(typename, value):
    global memory, debug_info
    return cast(value, typename, memory, debug_info)


def dump_msgram(dump_path):
    global dump_file

    #import pdb; pdb.set_trace()
    xport_rpm_ctx     = get_variable('xport_rpm_ctx')
    xport_rpm_msg_ram = get_variable('xport_rpm_msg_ram')
    rpm               = get_variable('rpm')
    msgram            = cast_address('message_ram_s', xport_rpm_msg_ram.address)

    for i in range(len(msgram.master)):
        ee_name = pointer_to_str(rpm.ees[i].remote_ss)

        with open(os.path.join(dump_path, 'msgram_dump_{0}_{1}.txt'.format(i, ee_name)), 'w') as f:
            try:
                dump_file = f
                dump_master_stats(msgram.master[i].master_stats, indent=INDENT)
                dump_vmpm(msgram.master[i].vmpm, indent=INDENT)
                dump_glink_packets(ee_name, xport_rpm_ctx[i], indent=INDENT)
            except:
                write(traceback.format_exc())


def write(str):
    global dump_file

    print(str, file=dump_file)


def dump_master_stats(stats, indent='    '):
    write("")
    write("================================================================================")
    write("{0:^80}".format('%s @ 0x%08X' % ("Master Stats", stats.address)))
    write("================================================================================")
    write('active_cores                   : %d' % stats.active_cores )
    write('num_shutdowns                  : %d' % stats.num_shutdowns)
    write('shutdown_req                   : 0x%016X' % stats.shutdown_req)
    write('wakeup_ind                     : 0x%016X' % stats.wakeup_ind)
    write('bringup_req                    : 0x%016X' % stats.bringup_req)
    write('bringup_ack                    : 0x%016X' % stats.bringup_ack)
    write('wakeup_reason                  : %s' % {0:'RUDE_WAKEUP', 1:'SCHEDULED_WAKEUP'}.get(stats.wakeup_reason, str(stats.wakeup_reason)))
    write('last_sleep_transition_duration : 0x%08X (%u usec)' % (stats.last_sleep_transition_duration, stats.last_sleep_transition_duration/19.2))
    write('last_wake_transition_duration  : 0x%08X (%u usec)' % (stats.last_wake_transition_duration, stats.last_wake_transition_duration/19.2))
    write('xo_count                       : %d' % stats.xo_count)
    write('xo_last_entered_at             : 0x%016X' % stats.xo_last_entered_at)
    write('xo_last_exited_at              : 0x%016X' % stats.xo_last_exited_at)
    write('xo_accumulated_duration        : 0x%016X (%u usec)' % (stats.xo_accumulated_duration, stats.xo_accumulated_duration/19.2))
    write('reserved[6]                    : {%s}' % (', '.join(['0x%08X' % stats.reserved[i] for i in range(len(stats.reserved))])))
    write("")


def dump_vmpm(vmpm, indent='    '):
    write("")
    write("================================================================================")
    write("{0:^80}".format('%s @ 0x%08X' % ("VMPM", vmpm.address)))
    write("================================================================================")
    write('wakeup_time        : 0x%016X' % vmpm.wakeup_time)
    write('vmpm_enable        : {%s}' % (', '.join(['0x%08X' % vmpm.vmpm_enable[i] for i in range(len(vmpm.vmpm_enable))])))
    write('vmpm_detect_lower  : {%s}' % (', '.join(['0x%08X' % vmpm.vmpm_detect_lower[i] for i in range(len(vmpm.vmpm_detect_lower))])))
    write('vmpm_detect_higher : {%s}' % (', '.join(['0x%08X' % vmpm.vmpm_detect_higher[i] for i in range(len(vmpm.vmpm_detect_higher))])))
    write('vmpm_polarity      : {%s}' % (', '.join(['0x%08X' % vmpm.vmpm_polarity[i] for i in range(len(vmpm.vmpm_polarity))])))
    write('vmpm_status        : {%s}' % (', '.join(['0x%08X' % vmpm.vmpm_status[i] for i in range(len(vmpm.vmpm_status))])))
    write('mpm_proxy_register : 0x%08X' % vmpm.mpm_proxy_register)
    write("")


def dump_glink_packets(ee_name, ctx, indent='    '):
    write("")
    write("================================================================================")
    write("{0:^80}".format('RX: {name}-->RPM'.format(name=ee_name.upper())))
    write("================================================================================")

    #import pdb; pdb.set_trace()
    dump_rx_fifo(ctx, indent)

    write("")
    write("================================================================================")
    write("{0:^80}".format('TX: RPM-->{name}'.format(name=ee_name.upper())))
    write("================================================================================")

    dump_tx_fifo(ctx, indent)


def increment_index(inc_size):
    global count, write_index, fifo_size

    write_index = write_index + inc_size

    if write_index >= fifo_size:
        write_index = write_index - fifo_size

    count += inc_size


def dump_rx_fifo(ctx, indent='    '):
    global memory, debug_info, count, write_index, fifo_size

    info      = ctx.rx_desc
    fifo      = ctx.rx_fifo
    fifo_size = ctx.rx_fifo_size

    read_index  = info.read_ind
    write_index = info.write_ind

    write("[RX Info @ 0x%08X]" % info.address)
    write(indent + "READ_INDEX  : 0x%X (%d)" % (read_index, read_index))
    write(indent + "WRITE_INDEX : 0x%X (%d)" % (write_index, write_index))
    write("")

    write("[RX FIFO @ 0x%08X (SIZE: 0x%X)]" % (fifo.address, fifo_size))

    msg_version = None

    count = 0
    while count < fifo_size:
        #import pdb; pdb.set_trace()

        raw_data = memory.read(fifo.address + write_index, 4)
        data_v0  = struct.unpack('<I', raw_data)[0]
        data_v1  = cast_address('RPMRequestHeaderV1', fifo.address + write_index)

        if data_v0 == 0x716572: # req\x00 in little endian
            if not msg_version:
                write(indent + '+-{0:-^19}-+-{1:-^8}-+-{2:-^8}-+-{3:-^25}-+-{4:-^15}-+-{5:-^10}-+-{6:-^9}-+-{7:-^60}-+'.format('', '', '', '', '', '', '', ''))
                write(indent + '| {0:^19} | {1:^8} | {2:^8} | {3:^25} | {4:^15} | {5:^10} | {6:^9} | {7:^60} |'.format('LOCATION', 'MSG TYPE', 'MSG SIZE', 'MSG_ID', 'SET', 'RESOURCE', 'DATA_SIZE', 'KVPs'))
                write(indent + '+-{0:-^19}-+-{1:-^8}-+-{2:-^8}-+-{3:-^25}-+-{4:-^15}-+-{5:-^10}-+-{6:-^9}-+-{7:-^60}-+'.format('', '', '', '', '', '', '', ''))
                msg_version = 'v0'
            dump_req_v0(fifo, indent)
        elif data_v1.version == 1 and data_v1.type == 0:
            if not msg_version:
                write(indent + '+-{0:-^19}-+-{1:-^11}-+-{2:-^8}-+-{3:-^25}-+-{4:-^15}-+-{5:-^10}-+-{6:-^9}-+-{7:-^60}-+'.format('', '', '', '', '', '', '', ''))
                write(indent + '| {0:^19} | {1:^11} | {2:^8} | {3:^25} | {4:^15} | {5:^10} | {6:^9} | {7:^60} |'.format('LOCATION', 'MSG TYPE', 'MSG SIZE', 'MSG_ID', 'SET', 'RESOURCE', 'DATA_SIZE', 'KVPs'))
                write(indent + '+-{0:-^19}-+-{1:-^11}-+-{2:-^8}-+-{3:-^25}-+-{4:-^15}-+-{5:-^10}-+-{6:-^9}-+-{7:-^60}-+'.format('', '', '', '', '', '', '', ''))
                msg_version = 'v1'
            dump_req_v1(fifo, indent)
        else:
            increment_index(4)

    if msg_version == 'v0':
        write(indent + '+-{0:-^19}-+-{1:-^8}-+-{2:-^8}-+-{3:-^25}-+-{4:-^15}-+-{5:-^10}-+-{6:-^9}-+-{7:-^60}-+'.format('', '', '', '', '', '', '', ''))
    elif msg_version == 'v1':
        write(indent + '+-{0:-^19}-+-{1:-^11}-+-{2:-^8}-+-{3:-^25}-+-{4:-^15}-+-{5:-^10}-+-{6:-^9}-+-{7:-^60}-+'.format('', '', '', '', '', '', '', ''))
    write("")


def dump_req_v0(fifo, indent='    '):
    global memory, debug_info, count, write_index, fifo_size

    addr = '0x%08X + 0x%04X' % (fifo.address, write_index)

    msg_type = memory.read(fifo.address + write_index, 4).replace('\x00',' ')
    increment_index(4)

    msg_size = struct.unpack('I', memory.read(fifo.address + write_index, 4))[0]
    increment_index(4)

    msg_id = struct.unpack('<I', memory.read(fifo.address + write_index, 4))[0]
    increment_index(4)
    msg_id_str = '{0:>10} ({1: >10})'.format('0x%X' % msg_id, msg_id)

    set_id = struct.unpack('<I', memory.read(fifo.address + write_index, 4))[0]
    increment_index(4)
    set_str = cast_value('rpm_set_type', set_id)

    rsrc_type = memory.read(fifo.address + write_index, 4).replace('\x00',' ')
    increment_index(4)
    rsrc_id   = struct.unpack('<I', memory.read(fifo.address + write_index, 4))[0]
    increment_index(4)
    rsrc_str = '{0:<4}, {1:>3}'.format(rsrc_type, rsrc_id)

    data_size = struct.unpack('<I', memory.read(fifo.address + write_index, 4))[0]
    increment_index(4)

    kvps = dump_kvps(fifo, data_size, indent)
    kvps_str = ('\n%s| {0:19} | {1:8} | {2:8} | {3:25} | {4:15} | {5:10} | {6:9} |' % indent).format('','','','','','','').join(
                [' {0:<60} |'.format(kvp) for kvp in kvps])

    write(indent + '| {0:<19} | {1:<8} | {2:>8} | {3:>25} | {4:<15} | {5:<10} | {6:>9} |'.format(
        addr, msg_type, msg_size, msg_id_str, set_str, rsrc_str, data_size) + kvps_str)


def dump_req_v1(fifo, indent='    '):
    global memory, debug_info, count, write_index, fifo_size

    addr = '0x%08X + 0x%04X' % (fifo.address, write_index)

    data_v1  = cast_address('RPMRequestHeaderV1', fifo.address + write_index)
    type_str = cast_value('rpm_v1_service_type', data_v1.type).replace('RPM_','').replace('_SERVICE','')
    increment_index(4)

    msg_id = struct.unpack('<I', memory.read(fifo.address + write_index, 4))[0]
    increment_index(4)
    msg_id_str = '{0:>10} ({1: >10})'.format('0x%X' % msg_id, msg_id)

    rsrc_type = memory.read(fifo.address + write_index, 4).replace('\x00',' ')
    increment_index(4)

    details = cast_address('RPMRequestDetailsV1', fifo.address + write_index)
    increment_index(4)

    set_str = cast_value('rpm_set_type', details.set).replace('RPM_','')
    rsrc_str = '{0:<4}, {1:>3}'.format(rsrc_type, details.resource_id)

    kvps = dump_kvps(fifo, details.data_len, indent)
    kvps_str = ('\n%s| {0:19} | {1:11} | {2:8} | {3:25} | {4:15} | {5:10} | {6:9} |' % indent).format('','','','','','','').join(
                [' {0:<60} |'.format(kvp) for kvp in kvps])

    write(indent + '| {0:<19} | {1:<11} | {2:>8} | {3:>25} | {4:<15} | {5:<10} | {6:>9} |'.format(
        addr, type_str, data_v1.size, msg_id_str, set_str, rsrc_str, details.data_len) + kvps_str)


def dump_tx_fifo(ctx, indent='    '):
    global memory, debug_info, count, write_index, fifo_size

    info      = ctx.tx_desc
    fifo      = ctx.tx_fifo
    fifo_size = ctx.tx_fifo_size

    read_index  = info.read_ind
    write_index = info.write_ind

    write("[TX Info @ 0x%08X]" % info.address)
    write(indent + "READ_INDEX  : 0x%X (%d)" % (read_index, read_index))
    write(indent + "WRITE_INDEX : 0x%X (%d)" % (write_index, write_index))
    write("")

    write("[TX FIFO @ 0x%08X (SIZE: 0x%X)]" % (fifo.address, fifo_size))

    msg_version = None

    count = 0
    while count < fifo_size:
        #import pdb; pdb.set_trace()

        raw_data = memory.read(fifo.address + write_index, 4)
        data_v0  = struct.unpack('<I', raw_data)[0]
        data_v1  = cast_address('RPMRequestHeaderV1', fifo.address + write_index)

        if data_v0 == 0x716572: # req\x00 in little endian
            if not msg_version:
                write(indent + '+-{0:-^19}-+-{1:-^8}-+-{2:-^8}-+-{3:-^60}-+'.format('', '', '', ''))
                write(indent + '| {0:^19} | {1:^8} | {2:^8} | {3:^60} |'.format('LOCATION', 'MSG TYPE', 'MSG SIZE', 'KVPs'))
                write(indent + '+-{0:-^19}-+-{1:-^8}-+-{2:-^8}-+-{3:-^60}-+'.format('', '', '', ''))
                msg_version = 'v0'
            dump_ack_v0(fifo, indent)
        elif data_v1.version == 1 and (data_v1.type == 3 or data_v1.type == 4):
            if not msg_version:
                write(indent + '+-{0:-^19}-+-{1:-^11}-+-{2:-^8}-+-{3:-^25}-+-{4:-^25}-+'.format('', '', '', '', ''))
                write(indent + '| {0:^19} | {1:^11} | {2:^8} | {3:^25} | {4:^25} |'.format('LOCATION', 'MSG TYPE', 'MSG SIZE', 'MSG ID', 'MSG ERR'))
                write(indent + '+-{0:-^19}-+-{1:-^11}-+-{2:-^8}-+-{3:-^25}-+-{4:-^25}-+'.format('', '', '', '', ''))
                msg_version = 'v1'
            dump_ack_v1(fifo, indent)
        else:
            increment_index(4)

    if msg_version == 'v0':
        write(indent + '+-{0:-^19}-+-{1:-^8}-+-{2:-^8}-+-{3:-^60}-+'.format('', '', '', ''))
    elif msg_version == 'v1':
        write(indent + '+-{0:-^19}-+-{1:-^11}-+-{2:-^8}-+-{3:-^25}-+-{4:-^25}-+'.format('', '', '', '', ''))
    write("")


def dump_ack_v0(fifo, indent='    '):
    global memory, debug_info, count, write_index, fifo_size

    addr = '0x%08X + 0x%04X' % (fifo.address, write_index)

    msg_type = memory.read(fifo.address + write_index, 4).replace('\x00',' ')
    increment_index(4)

    msg_size = struct.unpack('I', memory.read(fifo.address + write_index, 4))[0]
    increment_index(4)

    kvps = dump_kvps(fifo, msg_size, indent)
    kvps_str = '\n| {0:19} | {1:<8} | {2:>8} | '.format('','','').join(['{0:<60} |'.format(kvp) for kvp in kvps])

    write(indent + '| {0:19} | {1:<8} | {2:>8} | '.format(addr, msg_type, msg_size) + kvps_str)


def dump_ack_v1(fifo, indent='    '):
    global memory, debug_info, count, write_index, fifo_size

    addr = '0x%08X + 0x%04X' % (fifo.address, write_index)

    data_v1  = cast_address('RPMRequestHeaderV1', fifo.address + write_index)
    type_str = cast_value('rpm_v1_service_type', data_v1.type).replace('RPM_','').replace('_SERVICE','')
    increment_index(4)

    msg_id = struct.unpack('<I', memory.read(fifo.address + write_index, 4))[0]
    increment_index(4)
    msg_id_str = '{0:>10} ({1: >10})'.format('0x%X' % msg_id, msg_id)

    if data_v1.type == 4:
        err     = struct.unpack('<I', memory.read(fifo.address + write_index, 4))[0]
        err_str = cast_value('rpm_message_error_type', err).replace('RPM_MESSAGE_ERROR_','')
        increment_index(4)
    else:
        err_str = ''

    write(indent + '| {0:19} | {1:<11} | {2:>8} | {3:>25} | {4:<25} |'.format(addr, type_str, data_v1.size, msg_id_str, err_str))


def dump_kvps(fifo, kvp_size, indent='    '):
    global memory, debug_info, count, write_index, fifo_size

    kvps = []

    size=0

    while size < kvp_size:
        key = memory.read(fifo.address + write_index, 4)

        increment_index(4)
        size += 4

        length = struct.unpack('<I', memory.read(fifo.address + write_index, 4))[0]

        increment_index(4)
        size += 4

        raw_data = memory.read(fifo.address + write_index, length)

        if length == 4:
            value = struct.unpack('<I', raw_data)[0]
            value_str = '{0:>10} ({1: >10})'.format('0x%X' % value, value)
        elif length == 8:
            value = struct.unpack('<Q', raw_data)[0]
            value_str = '{0:>18} ({1: >20})'.format('0x%X' % value, value)
        else:
            value_str = struct.unpack('%dc' % length, raw_data)[0]

        increment_index(length)
        size += length

        kvps.append('{0:4}, {1:2}, {2}'.format(key.replace('\x00',' '), length, value_str))

    return kvps


