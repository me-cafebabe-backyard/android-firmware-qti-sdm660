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
from locators.core_dump import locate as locate_core_dump
from dwarf import decode_object
from hansei_utils import *
import traceback


INDENT = '    '


def dump(debug_data):
    global memory, debug_info

    memory     = debug_data['rpm_memory']
    debug_info = debug_data['debug_info']
    dump_path  = debug_data['dump_path']

    debug_data['printer'].p("Dumping cpr state...")

    #save_logger_level = update_logger(logging.DEBUG, logging)
    dump_cpr(dump_path)
    #update_logger(save_logger_level, logging)

    debug_data['printer'].p("\t...DONE")


def get_variable(name):
    global memory, debug_info

    address    = debug_info.variables[name].address
    dump_type  = debug_info.variables[name].vartype
    variable   = decode_object(name, address, dump_type, memory, debug_info)

    return variable


def dump_cpr(dump_path):
    global memory, debug_info, dump_file

    with open(os.path.join(dump_path, 'cpr.txt'), 'w') as f:
        dump_file = f
        dump_cpr3()


def write(str):
    global dump_file

    print(str, file=dump_file)


def dump_cpr3():
    global memory, debug_info

    try:
        address       = locate_core_dump(memory, debug_info)
        dump_type     = debug_info.variables['rpm_core_dump'].vartype
        rpm_core_dump = decode_object('rpm_core_dump', address, dump_type, memory, debug_info)
        if rpm_core_dump.cpr_info is not None:
            cpr_info  = cast(rpm_core_dump.cpr_info, 'cpr_information', memory, debug_info)
        else:
            cpr_info  = get_variable('cpr_info')

        dump_cpr_info(cpr_info, indent=INDENT)
    except:
        write("ERROR PARSING CPR STRUCTURES\n")
        write(traceback.format_exc())


def dump_cpr_info(cpr_info, indent='    '):
    global memory, debug_info

    write("CPR INFO:")
    write(indent+"ChipVersion : 0x%08X" % cpr_info.chipVersion)
    write(indent+"CPR Rev     : 0x%X" % cpr_info.cprRev)
    write(indent+"Foundry     : %s" % (cpr_info.foundry.replace('CPR_FOUNDRY_','')))
    write(indent+"DataInit    : %d" % (cpr_info.dataInit))
    write(indent+"CfgInit     : %d" % (cpr_info.cfgInit))
    write(indent+"FullInit    : %d" % (cpr_info.fullInit))
    write(indent+"VP Hash     : %s" % pointer_to_str(cpr_info.settings.hashValue))
    write(indent+"Rail Info   :")

    for i in range(cpr_info.settings.railsCount):
        dump_cpr_rail(cpr_info, i, indent)


def dump_cpr_rail(cpr_info, i, indent='    '):
    global memory, debug_info

    rail_state = cpr_info.railStates[i]
    rail_cfg   = cpr_info.settings.rails[i]
    enab       = rail_cfg.enablement
    #import pdb; pdb.set_trace()

    write(indent*2 + "Rail    : %s" % rail_state.id)
    write(indent*3 + "CtrlMode    : %s" % rail_state.cMode.replace('CPR_CONTROL_',''))
    write(indent*3 + "PmicStepSize: {0:7} uV".format(enab.stepSize))
    write(indent*3 + "FuseMult    : {0:7} uV".format(enab.fuseMultiplier))

    if "SW_CLOSED_LOOP" in rail_state.cMode:
        write(indent*3 + "Margins     : (Aging: {0:7} uV), (Thermal: {1:7} uV)".format(rail_state.marginAdjustments[0], rail_state.marginAdjustments[1]))
        write(indent*3 + "DisableVotes: 0x%08X" % (rail_state.disableVotes))
        #import pdb; pdb.set_trace()
        write(indent*3 + "Modes       : (Active: %s) (Prev: %s)" % (
            'NULL' if rail_state.activeMode.address == 0 else rail_state.activeMode.mode.replace('CPR_VOLTAGE_MODE_',''),
            'NULL' if rail_state.previousMode.address == 0 else rail_state.previousMode.mode.replace('CPR_VOLTAGE_MODE_','')))
        dump_controller(rail_cfg, indent)

    dump_modes(cpr_info, rail_state, rail_cfg, indent)

    if "SW_CLOSED_LOOP" in rail_state.cMode:
        dump_quotients(rail_state, indent)
        dump_cpr_stats(rail_state, indent)

    write('')


def dump_controller(rail_cfg, indent='    '):
    global memory, debug_info

    ctrl = rail_cfg.hal.controller
    mask = ctrl.roMask

    write(indent*3 + "HAL Info    :")
    write(indent*4 + "Controller:")
    write(indent*5 + "Base             : 0x%08X" % (ctrl.base))
    write(indent*5 + "Init             : %d" % (ctrl.init))
    write(indent*5 + "Enabled          : %d" % (ctrl.enabled))
    write(indent*5 + "marginAdjEnabled : %d" % (ctrl.marginAdjEnabled))
    write(indent*5 + "roMask           : 0x%04X (ROs Enabled: %s)" % (mask, ', '.join([str(i) for i in range(16) if (mask & (1<<i)) == 0])))

    data = cast(ctrl.tempSensorData, 'uint32', memory, debug_info)
    if data:
        write(indent*5 + "TempSensorData   : 0x%08X (HOT: Sensor: %d, Temp: %.1f degC)  (COLD: Sensor: %d, Temp: %.1f degC)" % (
            data,
            ctrl.tempSensorData.hotSensor,
            ctrl.tempSensorData.hotTempCx10/10.0,
            ctrl.tempSensorData.coldSensor,
            ctrl.tempSensorData.coldTempCx10/10.0
            ))

    write(indent*4 + "Threads   :")
    write(indent*5 + "+-----+------+---------+---------------+")
    write(indent*5 + "| {0:3} | {1:4} | {2:7} | {3:13} |".format('TID', 'Init', 'Enabled', 'RoMask4Thread'))
    write(indent*5 + "+-----+------+---------+---------------+")
    for i in range(ctrl.threadsCount):
        thread = ctrl.threads[i]
        write(indent*5 + "| {0:3} | {1:4} | {2:7} | {3:>13} |".format(
            thread.id, thread.init, thread.enabled, '0x%04X'%thread.roMask4Thread
            ))
    write(indent*5 + "+-----+------+---------+---------------+")

def get_margin(cpr_info, vpmode):
    if vpmode.margins.address is 0:
        return None

    for margin in vpmode.margins.data:
        if cpr_info.cprRev >= margin.cprRevMin and cpr_info.cprRev <= margin.cprRevMax:
            return margin

def dump_modes(cpr_info, rail_state, rail_cfg, indent='    '):
    global memory, debug_info

    cpr_data_format = [
        {'name' : 'Mode'       , 'clOnly' : False, 'width' :  7, 'align' : '^'},
        {'name' : 'VoltFuse'   , 'clOnly' : False, 'width' :  8, 'align' : '>'},
        {'name' : 'OffsFuse'   , 'clOnly' : False, 'width' :  8, 'align' : '>'},
        {'name' : 'EnabCount'  , 'clOnly' : False, 'width' : 10, 'align' : '>'},
        {'name' : 'IntrplEn'   , 'clOnly' : False, 'width' :  8, 'align' : '>'},
        {'name' : 'FreqKHz'    , 'clOnly' : False, 'width' :  7, 'align' : '>'},
        {'name' : 'GCeiling'   , 'clOnly' : False, 'width' :  8, 'align' : '>'},
        {'name' : 'FuseRef'    , 'clOnly' : False, 'width' :  8, 'align' : '>'},
        {'name' : 'Ceiling'    , 'clOnly' : False, 'width' :  8, 'align' : '>'},
        {'name' : 'Current'    , 'clOnly' : False, 'width' :  8, 'align' : '>'},
        {'name' : 'Min'        , 'clOnly' : False, 'width' :  8, 'align' : '>'},
        {'name' : 'Floor'      , 'clOnly' : False, 'width' :  8, 'align' : '>'},
        {'name' : 'GFloor'     , 'clOnly' : False, 'width' :  8, 'align' : '>'},
        {'name' : 'OMargin'    , 'clOnly' : True , 'width' :  7, 'align' : '>'},
        {'name' : 'CMargin'    , 'clOnly' : True , 'width' :  7, 'align' : '>'},
        {'name' : 'MaxF2C'     , 'clOnly' : True , 'width' :  6, 'align' : '>'},
        {'name' : "UpInt"      , 'clOnly' : True , 'width' : 10, 'align' : '>'},
        {'name' : "DownInt"    , 'clOnly' : True , 'width' : 10, 'align' : '>'},
        {'name' : "HitCeiling" , 'clOnly' : True , 'width' : 10, 'align' : '>'},
        {'name' : "HitFloor"   , 'clOnly' : True , 'width' : 10, 'align' : '>'},
        {'name' : "Ignored"    , 'clOnly' : True , 'width' : 10, 'align' : '>'},
    ]

    write(indent*3 + 'Mode Info   :')

    line = ''
    header = ''

    if "SW_CLOSED_LOOP" in rail_state.cMode:
        line   = '+%s+' % ('+'.join(['-%s-' % ('-'*data['width']) for data in cpr_data_format]))
        header =  '|%s|' % ('|'.join([(' {0:^%d} ' % (data['width'])).format(data['name']) for data in cpr_data_format]))
    else:
        line   = '+%s+' % ('+'.join(['-%s-' % ('-'*data['width']) for data in cpr_data_format if not data['clOnly']]))
        header =  '|%s|' % ('|'.join([(' {0:^%d} ' % (data['width'])).format(data['name']) for data in cpr_data_format if not data['clOnly']]))

    write(indent*4 + line)
    write(indent*4 + header)
    write(indent*4 + line)

    for i in range(rail_state.modeSettingsCount):
        mode      = rail_state.modeSettings[i]
        submode   = mode.subModes[0]
        vpmode    = rail_cfg.vp.modes[i]
        vpsubmode = vpmode.subModes[0]

        cpr_data = {
            'Mode'      : mode.mode.replace('CPR_VOLTAGE_MODE_',''),
            'VoltFuse'  : mode.decodedFuseSteps,
            'OffsFuse'  : mode.decodedFuseOffset,
            'EnabCount' : mode.enableCount,
            'IntrplEn'  : vpsubmode.interplEnabled,
            'FreqKHz'   : submode.freq,
            'GCeiling'  : vpsubmode.ceiling,
            'FuseRef'   : vpmode.fref,
            'Ceiling'   : submode.ceiling,
            'Current'   : submode.current,
            'Min'       : submode.min,
            'Floor'     : submode.floor,
            'GFloor'    : vpsubmode.floor,
        }

        if "SW_CLOSED_LOOP" in rail_state.cMode:
            debug = submode.debug
            margin = get_margin(cpr_info, vpmode)

            fmt =  '|%s|' % ('|'.join([' {%s:%s%d} ' % (data['name'], data['align'], data['width']) for data in cpr_data_format]))
            cpr_data.update({
                'OMargin'    :' ' if margin is None else margin.openLoop,
                'CMargin'    :' ' if mode.totalMarginMV is None else mode.totalMarginMV*1000,
                'MaxF2C'     :' ' if margin is None else margin.maxFloorToCeil,
                "UpInt"      :debug.up,
                "DownInt"    :debug.down,
                "HitCeiling" :debug.ceiling,
                "HitFloor"   :debug.floor,
                "Ignored"    :debug.ignored,
            })
        else:
            fmt =  '|%s|' % ('|'.join([' {%s:%s%d} ' % (data['name'], data['align'], data['width']) for data in cpr_data_format if not data['clOnly']]))

        write(indent*4 + fmt.format(**cpr_data))

    write(indent*4 + line)


def dump_quotients(rail_state, indent='    '):
    global memory, debug_info

    write(indent*3 + 'Quotients   :')
    write(indent*4 + '+---------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+')
    write(indent*4 + '| {0:^7} | '.format('Mode') + ' | '.join(['{0:^5}'.format('RO %d' % i) for i in range(16)]) + ' |')
    write(indent*4 + '+---------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+')

    for i in range(rail_state.modeSettingsCount):
        mode = rail_state.modeSettings[i]
        s = '| {0:^7} |'.format(mode.mode.replace('CPR_VOLTAGE_MODE_',''))
        t = 0
        for ro in range(16):
            if t < mode.targetsCount and ro == mode.targets[t].ro:
                s = s + ' {0:>5}'.format(mode.targets[t].quotient) + " |"
                t += 1
            else:
                s = s + ' {0:>5}'.format(' ') + " |"

        write(indent*4 + s)

    write(indent*4 + '+---------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+')


def dump_cpr_stats(rail_state, indent='    '):
    global memory, debug_info

    #var_type  = debug_info.variables['cpr_stats'].die
    #var_addr  = debug_info.variables['cpr_stats'].address
    #cpr_stats = decode_object('cpr_stats', var_addr, None, memory, debug_info, die = var_type)
    cpr_stats = get_variable('cpr_stats')

    write(indent*3 + "ISR Log     :")

    for i in range(len(cpr_stats)):
        cpr_stat = cpr_stats[i]
        if cpr_stat.id != rail_state.id:
            continue
        write(indent*4 + '+--------------------+---------+----------------+------------+------------+------------+------------+------------+---------+-------+')
        write(indent*4 + '| {0:^18} | {1:^7} | {2:^14} | {3:^10} | {4:^10} | {5:^10} | {6:^10} | {7:^10} | {8:^7} | {9:^5} |'.format(
            'Timestamp', 'Mode', 'Recommendation', 'Upint', 'DownInt', 'HitCeiling', 'HitFloor', 'Ignored', 'Changed', 'Acked'
            ))
        write(indent*4 + '+--------------------+---------+----------------+------------+------------+------------+------------+------------+---------+-------+')

        idx = cpr_stat.idx + 1
        if idx >= len(cpr_stat.logs):
            idx = 0
        s = ''
        for j in range(len(cpr_stat.logs)):
            log = cpr_stat.logs[idx]
            mode = cast(log.data.mode, 'cpr_voltage_mode', memory, debug_info).replace('CPR_VOLTAGE_MODE_','')
            s = '| {0:>18} | {1:^7} | {2:>14} | {3:>10} | {4:>10} | {5:>10} | {6:>10} | {7:>10} | {8:>7} | {9:>5} |'.format(
                    '0x{0:0>16}'.format('%08X%08X' % (log.timestamp[1], log.timestamp[0])),
                    mode,
                    log.data.up,
                    log.data.down,
                    log.data.recommendation,
                    log.data.hit_ceiling,
                    log.data.hit_floor,
                    log.data.ignored,
                    log.data.changed,
                    log.data.ackResult
                    )
            idx += 1
            if idx >= len(cpr_stat.logs):
                idx = 0

            write(indent*4 + s)

        write(indent*4 + '+--------------------+---------+----------------+------------+------------+------------+------------+------------+---------+-------+')

