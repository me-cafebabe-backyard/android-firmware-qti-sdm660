import sys, re, os
from base_parser import Parser
from target_data import *

class RPMBootEnter:
    __metaclass__ = Parser
    id = 0xC0
    def parse(self, data):
        return 'rpm_boot_started (free_heap_space: %d)' % (data[0])

class RPMBootExit:
    __metaclass__ = Parser
    id = 0xC1
    def parse(self, data):
        return 'rpm_boot_finished (free_heap_space: %d)' % (data[0])

class RPMBringupReq:
    __metaclass__ = Parser
    id = 0xC2
    def parse(self, data):
        message = 'rpm_bringup_req (master: %s) (core: %i)' % (get_master_name(data[0]), data[1])
        if (get_branch('major') == 1 and get_branch('minor') >= 4) or get_branch('major') == 2 :
            message += ' (is_soft_transition: %i)' % (data[2])
        return message

class RPMBringupAck:
    __metaclass__ = Parser
    id = 0xC3
    def parse(self, data):
        message = 'rpm_bringup_ack (master: %s) (core: %i)' % (get_master_name(data[0]), data[1])
        if (get_branch('major') == 1 and get_branch('minor') >= 4) or get_branch('major') == 2 :
            message += ' (is_soft_transition: %i)' % (data[2])
        return message

class RPMShutdownReq:
    __metaclass__ = Parser
    id = 0xC4
    def parse(self, data):
        message = 'rpm_shutdown_req (master: %s) (core: %i)' % (get_master_name(data[0]), data[1])
        if (get_branch('major') == 1 and get_branch('minor') >= 4) or get_branch('major') == 2 :
            message += ' (is_soft_transition: %i)' % (data[2])
        return message

class RPMShutdownAck:
    __metaclass__ = Parser
    id = 0xC5
    def parse(self, data):
        message = 'rpm_shutdown_ack (master: %s) (core: %i)' % (get_master_name(data[0]), data[1])
        if (get_branch('major') == 1 and get_branch('minor') >= 4) or get_branch('major') == 2 :
            message += ' (is_soft_transition: %i)' % (data[2])
        return message

class RPMTransitionQueued:
    __metaclass__ = Parser
    id = 0xC6
    def parse(self, data):
        message = 'rpm_transition_queued (master: %s) ' % get_master_name(data[0])
        if data[1] == 0:
            message += '(scheduled: "no")'
        elif data[1]:
            message += '(scheduled: "yes") (deadline: 0x%0.8x%0.8x)' % (data[3], (data[2]))
        return message

class RPMMasterSetTransition:
    __metaclass__ = Parser
    id = 0xC7
    def parse(self, data):
        message = 'rpm_master_set_transition (master: %s) (leaving: %s) (entering: %s)' % (get_master_name(data[0]),
                get_set_name(data[1]), get_set_name(data[2]))
        if get_branch('major') == 1 and get_branch('minor') >= 2 :
            message += ' (cache hit?: %s)' % (('yes' if data[3] else 'no'))
        return message

class RPMTransitionComplete:
    __metaclass__ = Parser
    id = 0xC8
    def parse(self, data):
        return 'rpm_master_set_transition_complete (master: %s) (deadline: 0x%0.8x%0.8x) (exceeded: %s)' % (get_master_name(data[0]), data[1], data[2], ('yes' if data[3] else 'no'))

class RPMHashMismatch:
    __metaclass__ = Parser
    id = 0xC9
    def parse(self, data):
        if data[0] == 0:
            result = ' (system_state: %d) (cache_result_state: %d) (result_state: %d)' % (data[1], data[2], data[3])
        else:
            result = ' (next_task: %d) (pre_state: %d) (next_state: %d) (system_hash: %d)' % (data[0], data[1], data[2], data[3])
        return 'rpm_hash_mismatch' + result

class RPMSvsFastExternalVote:
    __metaclass__ = Parser
    id = 0xCA
    def parse(self, data):
        return 'rpm_svs (mode: RPM_SVS_FAST) (reason: external vote)'

class RPMSvsFastImminentProcessing:
    __metaclass__ = Parser
    id = 0xCB
    def parse(self, data):
        return 'rpm_svs (mode: RPM_SVS_FAST) (reason: imminent processing)'

class RPMSvsFastScheduleIsFull:
    __metaclass__ = Parser
    id = 0xCC
    def parse(self, data):
        return 'rpm_svs (mode: RPM_SVS_FAST) (reason: schedule is full)'

class RPMSvsSlowIdle:
    __metaclass__ = Parser
    id = 0xCD
    def parse(self, data):
        return 'rpm_svs (mode: RPM_SVS_SLOW) (reason: idle)'

class RPMSvsFastSpeedup:
    __metaclass__ = Parser
    id = 0xCE
    def parse(self, data):
        return 'rpm_svs (mode: RPM_SVS_FAST) (reason: speedup) (old_duration: 0x%0.8x) (new_duration: 0x%0.8x) (switch_time: 0x%0.8x)' % (data[0], data[1], data[2])

class RPMSvsFastNoSpeedup:
    __metaclass__ = Parser
    id = 0xCF
    def parse(self, data):
        return 'rpm_svs (mode: RPM_SVS_SLOW) (reason: no speedup) (old_duration: 0x%0.8x) (new_duration: 0x%0.8x) (switch_time: 0x%0.8x)' % (data[0], data[1], data[2])

class RPMMessageReceived:
    __metaclass__ = Parser
    id = 0xD0
    def parse(self, data):
        return 'rpm_message_received (master: %s) (message id: %s) (set: %s)' % (get_master_name(data[0]), data[1], get_set_name(data[2]))

class RPMProcessRequest:
    __metaclass__ = Parser
    id = 0xD1
    def parse(self, data):
        name = get_resource_name(data[1])
        if get_name_from_resource_id(name, data[2]) != 'Unknown':
            full = ' (full name: %s)' % get_name_from_resource_id(name, data[2])
        else:
            full = ''
        return 'rpm_process_request (master: %s) (resource type: %s) (id: %s)%s' % (get_master_name(data[0]), name, data[2], full)

class RPMSendResponse:
    __metaclass__ = Parser
    id = 0xD2
    def parse(self, data):
        message = 'rpm_send_message_response (master: %s)' % (get_master_name(data[0]))
        if (get_branch('major') == 1 and get_branch('minor') >= 4) or (get_branch('major') == 2) :
            message += ' (service: %s)' % (get_resource_name(data[1]))
        return message

class RPMErrFatal:
    __metaclass__ = Parser
    id = 0xD3
    def parse(self, data):
        return 'rpm_err_fatal (lr: 0x%0.8x) (ipsr: 0x%0.8x) - %s' % (data[0], data[1], get_abort_interrupt_name(data[1]))

class RPMXlateRequest:
    __metaclass__ = Parser
    id = 0xD4
    def parse(self, data):
        name = get_resource_name(data[0])
        full = ''
        if get_name_from_resource_id(name, data[1]) != 'Unknown':
            full = ' (full name: %s)' % get_name_from_resource_id(name, data[1])
        else:
            full = ''
        return 'rpm_xlate_request (resource type: %s) (resource id: %s)%s' % (name, data[1], full)

class RPMApplyRequest:
    __metaclass__ = Parser
    id = 0xD5
    def parse(self, data):
        name = get_resource_name(data[0])
        full = ''
        if get_name_from_resource_id(name, data[1]) != 'Unknown':
            full = ' (full name: %s)' % get_name_from_resource_id(name, data[1])
        else:
            full = ''
        return 'rpm_apply_request (resource type: %s) (resource id: %s)%s (bypassed: %d)' % (name, data[1], full, data[2])

class RPMEstimateCacheHit:
    __metaclass__ = Parser
    id = 0xD6
    def parse(self,data):
        return 'rpm_estimate_cache_hit (estimate: 0x%0.8x)' % (data[0])

class RPMTransitionBypass:
    __metaclass__ = Parser
    id = 0xD8
    def parse(self, data):
        return 'rpm_transition_bypass (master: %s) (wake time: 0x%0.8x%0.8x) (work remaining: 0x%x) (pending bringup: %d)' % (get_master_name(data[0] >> 16), data[1], data[2], data[3], data[0] & 0xFFFF)

class RPMResourceSettling:
    __metaclass__ = Parser
    id = 0xD9
    def parse(self, data):
        name = get_resource_name(data[1])
        if get_name_from_resource_id(name, data[2]) != 'Unknown':
            full = ' (full name: %s)' % get_name_from_resource_id(name, data[2])
        else:
            full = ''
        message = 'rpm_resource_settling (master: %s) (resource type: %s) (resource id: %s)' % (get_master_name(data[0]), 
                               get_resource_name(data[1]), data[2])
        message += '%s' % (full)
        if data[3] != 0:
            return 'rpm_message_postponed: ' + message +' (msg id: %s)' % (data[3])
        else:
            return message

class RPMResourceSettlingTime:
    __metaclass__ = Parser
    id = 0xDA
    def parse(self, data):
        return 'rpm_resource_settling_time (settling estimate: 0x%0.8x%0.8x)' % (data[1], data[0]) 

class RPMResourceSettlingComplete:
    __metaclass__ = Parser
    id = 0xDB
    def parse(self, data):
        name = get_resource_name(data[1])
        if get_name_from_resource_id(name, data[2]) != 'Unknown':
            full = ' (full name: %s)' % get_name_from_resource_id(name, data[2])
        else:
            full = ''
        message = 'rpm_resource_settling_complete (master: %s) (resource type: %s) (resource id: %s)' % (get_master_name(data[0]), 
                               get_resource_name(data[1]), data[2])
        message += '%s' % (full)
        if data[3] != 0:
            message += ' (msg id: %s)' % (data[3])
        return message

class RPMResourceSettlingSpin:
    __metaclass__ = Parser
    id = 0xDC
    def parse(self, data):
        return 'rpm_resource_settling_spin master: %s)'

class RPMSettlingMessageRequeued:
    __metaclass__ = Parser
    id = 0xDD
    def parse(self, data):
        return 'rpm_settling_message_requeued (master: %s) (message id: %s)' % (get_master_name(data[0]), data[1])

class RPMSettlingTransitionRequeued:
    __metaclass__ = Parser
    id = 0xDE
    def parse(self, data):
        message = 'rpm_settling_transition_requeued (master: %s) ' % get_master_name(data[0])
        if data[1] == 0:
            message += '(scheduled: "no")'
        elif data[1]:
            message += '(scheduled: "yes") (deadline: 0x%0.8x%0.8x)' % (data[3], (data[2]))
        return message

class RPMTransitionPostponed:
    __metaclass__ = Parser
    id = 0xDF
    def parse(self, data):
        return 'rpm_transition_postponed (master: %s) ' % get_master_name(data[0])
        
class RPMCPRSensorDisabled:
    __metaclass__ = Parser
    id = 0xE0
    def parse(self, data):
        return 'rpm_cpr_sensor_disabled (rail: %d) (disabled: %d)' % (data[0], data[1])
        
class RPMOutOfHeap:
    __metaclass__ = Parser
    id = 0xE1
    def parse(self, data):
        return 'rpm_out_of_heap'

class RPMCommandReceived:
    __metaclass__ = Parser
    id = 0xE2
    def parse(self, data):
        return 'rpm_command_received (master: %s)' % (get_master_name(data[0]))

class RPMHeapCheck:
    __metaclass__ = Parser
    id = 0xE3
    def parse(self, data):
        return 'rpm_heap_check (free_heap_space: %d)' % data[0]

class RPMMasterStates:
    __metaclass__ = Parser
    id = 0xE4
    def parse(self, data):
        return 'rpm_master_states (master_bitmask %d)' % data[0]

class RPMNasStart:
    __metaclass__ = Parser
    id = 0xE5
    def parse(self, data):
        return 'rpm_start_nas_processing'

class RPMRamLogDisable:
    __metaclass__ = Parser
    id = 0xE6
    def parse(self, data):
        return 'rpm_ram_log_disable (num_logs_bef_stop: %d)' % data[0]

class RPMRamLogDisabled:
    __metaclass__ = Parser
    id = 0xE7
    def parse(self, data):
        return 'rpm_ram_log_disabled'

class RPMRamLogEnabled:
    __metaclass__ = Parser
    id = 0xE8
    def parse(self, data):
        return 'rpm_ram_log_enabled'

class RPMTzHaltIntReceived:
    __metaclass__ = Parser
    id = 0xE9
    def parse(self, data):
        return 'rpm_abort_interrupt_received (TZ HALT) ... aborting'

class RPMAppsNonSecWdBiteIntReceived:
    __metaclass__ = Parser
    id = 0xEA
    def parse(self, data):
        return 'rpm_abort_interrupt_received (APPS NON SECURE WD BITE) ... aborting'

class RPMEnqueueScheduledTask:
    __metaclass__ = Parser
    id = 0xEB
    def parse(self, data):
	    return 'rpm_enqueue_scheduled_task (task_id %d)' % data[0]

class RPMExecuteScheduledTask:
    __metaclass__ = Parser
    id = 0xEC
    def parse(self, data):
	    return 'rpm_execute_scheduled_task (task_id %d)' % data[0]

class RPMCompleteScheduledTask:
    __metaclass__ = Parser
    id = 0xED
    def parse(self, data):
	    return 'rpm_complete_scheduled_task (task_id %d)' % data[0]

class RPMPreemptScheduledTask:
    __metaclass__ = Parser
    id = 0xEE
    def parse(self, data):
	    return 'rpm_preempt_scheduled_task (task_id %d)' % data[0]

class RPMClearApcsQgicdrComplete:
    __metaclass__ = Parser
    id = 0xEF
    def parse(self, data):
        return 'rpm_clear_apcs_qgicdr_complete'

class RPMDccCrcErrIntReceived:
    __metaclass__ = Parser
    id = 0xF0
    def parse(self, data):
        return 'rpm_dcc_crc_err_int_received'

class RPMSetTransitionCacheStatus:
    __metaclass__ = Parser
    id = 0xF1
    def parse(self, data):
	    return 'rpm_set_transition_cache_status (startState: 0x%0.8x) (actionHash: 0x%0.8x)' % (data[0], data[1])

class RPMEstimateCacheObserve:
    __metaclass__ = Parser
    id = 0xF2
    def parse(self, data):
	    return 'rpm_estimate_cache_observe (startState: 0x%0.8x) (actionHash: 0x%0.8x) (resultState: 0x%0.8x) (timeElapsed: 0x%0.8x)' % (data[0], data[1], data[2], data[3])

class RPMSoftTriggerBringup:
    __metaclass__ = Parser
    id = 0xF3
    def parse(self, data):
        return 'rpm_soft_trigger_bringup (pending: 0x%0.8x) (mpm_index: 0x%0.8x)' % (data[0], data[1])

class GCCReset:
    __metaclass__ = Parser
    id = 0xF4
    def parse(self, data):
        return 'GCC_RESET... aborting.  gcc_reset_bits_indicate: %s' % get_gcc_reset_reason(data[0])

class RPMBootInitFcnStarted:
    __metaclass__ = Parser
    id = 0xF5
    def parse(self, data):
        return 'rpm_boot_init_fcn_started (init_fcn_id: %d) (free_heap_space: %d)' % (data[0], data[1])

class RPMBootInitFcnFinished:
    __metaclass__ = Parser
    id = 0xF6
    def parse(self, data):
        return 'rpm_boot_init_fcn_finished (init_fcn_id: %d) (free_heap_space: %d)' % (data[0], data[1])

class RPMAppsHangStatus:
    __metaclass__ = Parser
    id = 0xF7
    def parse(self, data):
        return 'rpm_apps_hang_status (Core: 0x%x) (Gladiator: 0x%x) (GIC: 0x%x) (WDOG: 0x%x)' % (data[0], data[1], data[2], data[3])

class RPMResetChip:
    __metaclass__ = Parser
    id = 0xF8
    def parse(self, data):
        return 'rpm_reset_chip'

class RPMLogRegister:
    __metaclass__ = Parser
    id = 0xF9
    def parse(self, data):
        return 'rpm_log_register (0x%0.8x: 0x%0.8x) (%s)' % (data[0], data[1], get_reg_name(data[0]))

class RPMReclaimPool:
    __metaclass__ = Parser
    id = 0xFA
    def parse(self, data):
        return 'rpm_reclaim_pool (Base: 0x%0.8x) (Limit: 0x%0.8x) (free_heap_spaace: %d)' % (data[0], data[1], data[2])

class RPMCciSpmE3EntryWorkaroundStarted:
    __metaclass__ = Parser
    id = 0xFB
    def parse(self, data):
        return 'rpm_cci_spm_e3_entry_workaround_started'

class RPMCciSpmE3ExitWorkaroundStarted:
    __metaclass__ = Parser
    id = 0xFC
    def parse(self, data):
        return 'rpm_cci_spm_e3_exit_workaround_started'

class RPMCciSpmE3WorkaroundFinished:
    __metaclass__ = Parser
    id = 0xFD
    def parse(self, data):
        return 'rpm_cci_spm_e3_workaround_finished'

class RPMGicDisable:
    __metaclass__ = Parser
    id = 0xFE
    def parse(self, data):
        return 'rpm_gic_disable (saved_gicd_ctlr: 0x%x)' % (data[0])

class RPMGicEnable:
    __metaclass__ = Parser
    id = 0xFF
    def parse(self, data):
        return 'rpm_gic_enable'


class SLEEPDeepSleepEnter:
    __metaclass__ = Parser
    id = 0x140
    def parse(self, data):
        return 'deep_sleep_enter: (mode: %s) (count: %i)' % (get_sleep_mode(data[0]), data[1]) 

class SLEEPDeepSleepExit:
    __metaclass__ = Parser
    id = 0x141
    def parse(self, data):
        return 'deep_sleep_exit: (mode: %s)' % get_sleep_mode(data[0]) 

class SLEEPNoDeepSleep:
    __metaclass__ = Parser
    id = 0x142
    def parse(self, data):
        if data[1] == 0:
            return 'no deep sleep, not enough time (mode: %s)' % get_sleep_mode(data[0])
        else:
            return 'no deep sleep, pending interrupt (mode: %s)' % get_sleep_mode(data[0])

class SLEEPRpmHaltEnter:
    __metaclass__ = Parser
    id = 0x143
    def parse(self, data):
        return 'rpm_halt_enter (until: 0x%0.16x)' % ((data[0] << 32) | data[1])

class SLEEPRpmHaltExit:
    __metaclass__ = Parser
    id = 0x144
    def parse(self, data):
        return 'rpm_halt_exit'

class SLEEP_mpm_ints:
    __metaclass__ = Parser
    id = 0x145
    def parse(self, data):
        return 'mpm_wakeup_ints (ints: 0x%0.8x 0x%0.8x 0x%0.8x)' % (data[0], data[1], data[2])

class SLEEPDeepSleepEnterComplete:
    __metaclass__ = Parser
    id = 0x146
    def parse(self, data):
        message = 'deep_sleep_enter_complete: (mode: %s)' % (get_sleep_mode(data[0]))
        if get_branch('major') == 1 and get_branch('minor') >= 3:
            message += ', (duration: 0x%0.8x)' % data[1]
        return message

class SLEEPDeepSleepExitComplete:
    __metaclass__ = Parser
    id = 0x147
    def parse(self, data):
        return 'deep_sleep_exit_complete: (mode: %s)' % get_sleep_mode(data[0]) 

class SLEEP_MSG_x148:
    __metaclass__ = Parser
    id = 0x148
    def parse(self, data):
        return 'mpm_programmed_wakeup_time: (timetick: 0x%0.8x%0.8x)' % (data[1], data[0])

class SLEEP_MSG_x149:
    __metaclass__ = Parser
    id = 0x149
    def parse(self, data):
        return 'mpm_actual_wakeup_time: (timetick: 0x%0.8x%0.8x)' % (data[1], data[0])

class SLEEPCprSvs2Process:
    __metaclass__ = Parser
    id = 0x14A
    def parse(self, data):
        return 'cpr_svs2_process'

class SLEEPMpmVoltage:
    __metaclass__ = Parser
    id = 0x14B
    def parse(self, data):
        return 'mpm_voltages: (mx_off: %d) (mx_on: %d) (cx_off: %d) (cx_on: %d)' % (data[0], data[1], data[2], data[3])

class SLEEPMpmRoDiv:
    __metaclass__ = Parser
    id = 0x14C
    def parse(self, data):
        return 'mpm_ro_divider: (mx: %d) (ro_div: 0x%x)' % (data[0], data[1])

class SLEEPWlanFreezeIoWorkaround:
    __metaclass__ = Parser
    id = 0x14D
    def parse(self, data):
        return 'wlan mpm config: (old_reg: 0x%0.8x) (new_reg: 0x%0.8x)' % (data[0], data[1])

