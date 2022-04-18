

#
# Target-specific pretty-printing
#

# This variable starts as a dictionary of targets.  When command line arguments
# are read, it is overwritten with only the specific dictionary for the target
# selected.
# 8974 is the default, all other targets are diffs from it
all_targets_data = {
    '8974' : {
        'rail' : {
            0 : 'Cx',
            1 : 'Gfx',
        },
        'corner' : {
            0 : 'OFF [0]',
            1 : 'SVS [1]',
            2 : 'NOMINAL [2]',
            3 : 'TURBO [3]',
            4 : 'COUNT [4]',
        },
        'masters' : {
            0   : '"APSS"',
            1   : '"MSS SW"',
            2   : '"LPASS"',
            3   : '"PRONTO"',
        },
        'sleep_modes' : {
            0   :  '"XO Shutdown"',
            1   :  '"VDD Minimization"',
        },
        'interrupts' : {
            #system level exceptions
            0       : 'Normal Abort', # abort_isr was not called.
            2       : 'NMI',
            3       : 'Hard Fault',
            4       : 'Memory Management',
            5       : 'Bus Fault',
            6       : 'Usage Fault',
            11      : 'SVC',
            12      : 'Debug',
            14      : 'PendSVC',
            15      : 'SysTick',
            #NVIC interrupts
            12+16   : 'TZ Invoked Abort',
            49+16   : 'RPM Wdog Bark',
        },
        'mpm_ints' : {
        },
        'plls' : {
            1  : 'XO',
            2  : 'GPLL0',
            3  : 'GPLL1',
            4  : 'GPLL2',
            5  : 'GPLL3',
            6  : 'MMPLL0',
            7  : 'MMPLL1',
            8  : 'MMPLL2',
            9  : 'MMPLL3',
        },
        'clock_power' : {
            0  : 'Enter',
            1  : 'Done'
        },
        'clock_bimc' : {
            0  : 'Enter',
            1  : 'Enter Self Refresh',
            2  : 'Enter Power Collapsed',
            3  : 'Done',
            4  : 'Set DDR',
            5  : 'DDR done',
            6  : 'Wait for power domain enable',
            7  : 'Wait for power domain disable',
            8  : 'Saving DEHR',
            9  : 'Restoring DEHR',
            10 : 'DEHR done',
        },
        'Voltages' : {
            0  : 'OFF         ',
            1  : 'RETENTION   ',
            3  : 'LOW         ',
            4  : 'NONIMAL     ',
            5  : 'NONIMAL_PLUS',
            6  : 'HIGH        ',
        },
        'icb_masters' : {
            38 : 'MASTER_BAM_DMA',
            21 : 'MASTER_BIMC_SNOC',
            41 : 'MASTER_BLSP_1',
            39 : 'MASTER_BLSP_2',
            22 : 'MASTER_CNOC_SNOC',
            18 : 'MASTER_LPASS_AHB',
            25 : 'MASTER_LPASS_PROC',
            54 : 'MASTER_OVIRT_SNOC',
            29 : 'MASTER_PNOC_SNOC',
            43 : 'MASTER_PNOC_CFG',
            33 : 'MASTER_SDCC_1',
            35 : 'MASTER_SDCC_2',
            34 : 'MASTER_SDCC_3',
            36 : 'MASTER_SDCC_4',
            3  : 'MASTER_SNOC_BIMC',
            52 : 'MASTER_SNOC_CNOC',
            44 : 'MASTER_SNOC_PNOC',
            37 : 'MASTER_TSIF',
            42 : 'MASTER_USB_HS',
            40 : 'MASTER_USB_HSIC',
        },
        'icb_slaves' : {
            1  : 'SLAVE_APPSS_L2',
            36 : 'SLAVE_BAM_DMA',
            2  : 'SLAVE_BIMC_SNOC',
            39 : 'SLAVE_BLSP_1',
            37 : 'SLAVE_BLSP_2',
            75 : 'SLAVE_CNOC_SNOC',
            0  : 'SLAVE_EBI1',
            55 : 'SLAVE_MESSAGE_RAM',
            26 : 'SLAVE_OCIMEM',
            18 : 'SLAVE_OCMEM',
            41 : 'SLAVE_PDM',
            45 : 'SLAVE_PNOC_SNOC',
            59 : 'SLAVE_PMIC_ARB',
            69 : 'SLAVE_PNOC_CFG',
            44 : 'SLAVE_PRNG',
            30 : 'SLAVE_QDSS_STM',
            74 : 'SLAVE_RPM',
            31 : 'SLAVE_SDCC_1',
            33 : 'SLAVE_SDCC_2',
            32 : 'SLAVE_SDCC_3',
            34 : 'SLAVE_SDCC_4',
            24 : 'SLAVE_SNOC_BIMC',
            25 : 'SLAVE_SNOC_CNOC',
            27 : 'SLAVE_SNOC_OVIRT',
            28 : 'SLAVE_SNOC_PNOC',
            51 : 'SLAVE_TLMM',
            35 : 'SLAVE_TSIF',
            40 : 'SLAVE_USB_HS',
            38 : 'SLAVE_USB_HSIC',
        },
        'clk0' : {
            0 : 'CX0',
            1 : 'QDSS',
            2 : 'DCVS',
        },
        'clk1' : {
            0 : 'pnoc',
            1 : 'snoc',
            2 : 'cnoc',
            3 : 'mm/axinoc',
            4 : 'mm/ahbnoc',
            5 : 'mm/ocmemnoc',
        },
        'clk2' : {
            0 : 'bimc',
        },
        'clka' : {
            1  : 'BB clk1',
            2  : 'BB clk2',
            3  : 'not supported',
            4  : 'RF clk1',
            5  : 'RF clk2',
            6  : 'RF clk3',
            7  : 'DIFF clk',
            8  : 'not supported',
            9  : 'not supported',
            10 : 'SLEEP clk',
            11 : 'DIV clk1',
            12 : 'DIV clk2',
            13 : 'DIV clk3',
        },
        'gcc_reset_reason' : {
            0       : 'secure_wdog_expired',
            1       : 'pmic_resin_reset',
            2       : 'msm_tsense0_reset',
            3       : 'srt_reset',
            4       : 'proc_halt_cti',
            5       : 'msm_tsense1_reset',
        },
        'reg_names' : {},
        'bmas' : {}, # will be filled by select_target
        'bslv'  : {}, # will be filled by select_target
    },
    '9x25':{
        'corner' : {
            0 : 'OFF [0]',
            1 : 'RAILWAY_RETENTION [1]',
            2 : 'RAILWAY_SVS_KRAIT [2]',
            3 : 'RAILWAY_SVS_SOC [3]',
            4 : 'RAILWAY_SVS_HIGH [4]',
            5 : 'RAILWAY_NOMINAL [5]',
            6 : 'RAILWAY_TURBO {NOMINAL_L1} [6]',
            7 : 'RAILWAY_TURBO_HIGH [7]',
            8 : 'RAILWAY_SUPER_TURBO [8]',
            9 : 'RAILWAY_SUPER_TURBO_NO_CPR [9]',
            10: 'COUNT [10]',
        },
    },
    '8x10':{
        'corner' : {
            0 : 'OFF [0]',
            1 : 'RAILWAY_RETENTION [1]',
            2 : 'RAILWAY_SVS_KRAIT [2]',
            3 : 'RAILWAY_SVS_SOC [3]',
            4 : 'RAILWAY_SVS_HIGH [4]',
            5 : 'RAILWAY_NOMINAL [5]',
            6 : 'RAILWAY_TURBO {NOMINAL_L1} [6]',
            7 : 'RAILWAY_TURBO_HIGH [7]',
            8 : 'RAILWAY_SUPER_TURBO [8]',
            9 : 'RAILWAY_SUPER_TURBO_NO_CPR [9]',
            10: 'COUNT [10]',
        },
    },
    '8x26':{
        'corner' : {
            0 : 'OFF [0]',
            1 : 'RAILWAY_RETENTION [1]',
            2 : 'RAILWAY_SVS_KRAIT [2]',
            3 : 'RAILWAY_SVS_SOC [3]',
            4 : 'RAILWAY_SVS_HIGH [4]',
            5 : 'RAILWAY_NOMINAL [5]',
            6 : 'RAILWAY_TURBO {NOMINAL_L1} [6]',
            7 : 'RAILWAY_TURBO_HIGH [7]',
            8 : 'RAILWAY_SUPER_TURBO [8]',
            9 : 'RAILWAY_SUPER_TURBO_NO_CPR [9]',
            10: 'COUNT [10]',
        },
    },
    '8974 Pro':{
        'corner' : {
            0 : 'OFF [0]',
            1 : 'RAILWAY_RETENTION [1]',
            2 : 'RAILWAY_SVS_KRAIT [2]',
            3 : 'RAILWAY_SVS_SOC [3]',
            4 : 'RAILWAY_SVS_HIGH [4]',
            5 : 'RAILWAY_NOMINAL [5]',
            6 : 'RAILWAY_TURBO {NOMINAL_L1} [6]',
            7 : 'RAILWAY_TURBO_HIGH [7]',
            8 : 'RAILWAY_SUPER_TURBO [8]',
            9 : 'RAILWAY_SUPER_TURBO_NO_CPR [9]',
            10: 'COUNT [10]',
        },
    },
    '8084':{
        'corner' : {
            0 : 'OFF [0]',
            1 : 'RAILWAY_RETENTION [1]',
            2 : 'RAILWAY_SVS_KRAIT [2]',
            3 : 'RAILWAY_SVS_SOC [3]',
            4 : 'RAILWAY_SVS_HIGH [4]',
            5 : 'RAILWAY_NOMINAL [5]',
            6 : 'RAILWAY_TURBO {NOMINAL_L1} [6]',
            7 : 'RAILWAY_TURBO_HIGH [7]',
            8 : 'RAILWAY_SUPER_TURBO [8]',
            9 : 'RAILWAY_SUPER_TURBO_NO_CPR [9]',
            10: 'COUNT [10]',
        },
    },
    '9x35':{
        'rail' : {
            0 : 'Mx',
            1 : 'Cx',
        },
        'corner' : {
            0 : 'OFF [0]',
            1 : 'RAILWAY_RETENTION [1]',
            2 : 'RAILWAY_SVS_KRAIT [2]',
            3 : 'RAILWAY_SVS_SOC [3]',
            4 : 'RAILWAY_SVS_HIGH [4]',
            5 : 'RAILWAY_NOMINAL [5]',
            6 : 'RAILWAY_TURBO {NOMINAL_L1} [6]',
            7 : 'RAILWAY_TURBO_HIGH [7]',
            8 : 'RAILWAY_SUPER_TURBO [8]',
            9 : 'RAILWAY_SUPER_TURBO_NO_CPR [9]',
            10: 'COUNT [10]',
        },
    },
    '8994':{
        'rail' : {
            0 : 'Mx',
            1 : 'Cx',
            2 : 'Gfx',
            3 : 'EBI',
        },
        'corner' : {
            0 : 'OFF [0]',
            1 : 'RAILWAY_RETENTION [1]',
            2 : 'RAILWAY_SVS_KRAIT [2]',
            3 : 'RAILWAY_SVS_SOC [3]',
            4 : 'RAILWAY_SVS_HIGH [4]',
            5 : 'RAILWAY_NOMINAL [5]',
            6 : 'RAILWAY_TURBO {NOMINAL_L1} [6]',
            7 : 'RAILWAY_TURBO_HIGH [7]',
            8 : 'RAILWAY_SUPER_TURBO [8]',
            9 : 'RAILWAY_SUPER_TURBO_NO_CPR [9]',
            10: 'COUNT [10]',
        },
    },
    '8992':{
        'rail' : {
            0 : 'Mx',
            1 : 'Cx',
            2 : 'Gfx',
            3 : 'EBI',
        },
        'corner' : {
            0 : 'OFF [0]',
            1 : 'RAILWAY_RETENTION [1]',
            2 : 'RAILWAY_SVS_KRAIT [2]',
            3 : 'RAILWAY_SVS_SOC [3]',
            4 : 'RAILWAY_SVS_HIGH [4]',
            5 : 'RAILWAY_NOMINAL [5]',
            6 : 'RAILWAY_TURBO {NOMINAL_L1} [6]',
            7 : 'RAILWAY_TURBO_HIGH [7]',
            8 : 'RAILWAY_SUPER_TURBO [8]',
            9 : 'RAILWAY_SUPER_TURBO_NO_CPR [9]',
            10: 'COUNT [10]',
        },
    },
    '8996':{
        'masters' : {
            0  : '"APSS"',
            1  : '"MSS SW"',
            2  : '"LPASS"',
            3  : '"SSC"',
            4  : '"TZ"',
        },
        'rail' : {
            0 : 'Mx',
            1 : 'Cx',
            2 : 'EBI',
            3 : 'SSC_Mx',
            4 : 'SSC_Cx',
        },
        'corner' : {
            0 : 'OFF [0]',
            1 : 'RAILWAY_RETENTION [1]',
            2 : 'RAILWAY_SVS_KRAIT [2]',
            3 : 'RAILWAY_SVS_SOC [3]',
            4 : 'RAILWAY_SVS_HIGH [4]',
            5 : 'RAILWAY_NOMINAL [5]',
            6 : 'RAILWAY_TURBO {NOMINAL_L1} [6]',
            7 : 'RAILWAY_TURBO_HIGH [7]',
            8 : 'RAILWAY_SUPER_TURBO [8]',
            9 : 'RAILWAY_SUPER_TURBO_NO_CPR [9]',
            10: 'COUNT [10]',
        },
        'sleep_modes' : {
            0   :  '"VDD Low"',
            1   :  '"VDD Minimization"',
        },
        'interrupts' : {
            #system level exceptions
            0       : 'Normal Abort', # abort_isr was not called.
            2       : 'NMI',
            3       : 'Hard Fault',
            4       : 'Memory Management',
            5       : 'Bus Fault',
            6       : 'Usage Fault',
            11      : 'SVC',
            12      : 'Debug',
            14      : 'PendSVC',
            15      : 'SysTick',
            #NVIC interrupts
            4+16    : 'DCC CRC Failure',
            7+16    : 'APPS Non-secure Wdog Bite',
            12+16   : 'TZ Invoked Abort',
            49+16   : 'RPM Wdog Bark',
        },
        'gcc_reset_reason' : {
            0       : 'secure_wdog_expired',
            1       : 'pmic_resin_reset',
            2       : 'msm_tsense0_reset',
            3       : 'srt_reset',
            4       : 'proc_halt_cti',
            5       : 'msm_tsense1_reset',
        },
    },
    '8998':{
        'masters' : {
            0  : '"APSS"',
            1  : '"MSS SW"',
            2  : '"LPASS"',
            3  : '"SSC"',
            4  : '"TZ"',
            5  : '"SPSS"',
        },
        'rail' : {
            0 : 'Mx',
            1 : 'Cx',
            2 : 'EBI',
            3 : 'SSC_Mx',
            4 : 'SSC_Cx',
        },
        'corner' : {
            0 : 'OFF',
            1 : 'RAILWAY_RETENTION',
            2 : 'RAILWAY_SVS_MIN',
            3 : 'RAILWAY_SVS_LOW',
            4 : 'RAILWAY_SVS',
            5 : 'RAILWAY_SVS_HIGH',
            6 : 'RAILWAY_NOMINAL',
            7 : 'RAILWAY_TURBO',
            8 : 'RAILWAY_SUPER_TURBO',
            9 : 'RAILWAY_SUPER_TURBO_NO_CPR',
            10: 'COUNT',
        },
        'cpr_rail' : {
            0x100 : 'MX',
            0x101 : 'CX',
            0x104 : 'VDDA',
            0x300 : 'SSC_MX',
            0x301 : 'SSC_CX',
        },
        'cpr_mode' : {
            0 : 'OFF',
            1 : 'RETENTION',
            2 : 'MIN_SVS',
            3 : 'LOW_SVS',
            4 : 'SVS',
            5 : 'SVS_L1',
            6 : 'NOMINAL',
            7 : 'NOMINAL_L1',
            8 : 'TURBO',
            9 : 'SUPER_TURBO',
            10: 'SUPER_TURBO_NO_CPR',
            11: 'COUNT',
        },
        'cpr_controller' : {
            0x60628000 : 'CPR3',
            0x6062C000 : 'MX_CPR3',
        },
        'sleep_modes' : {
            0   :  '"VDD Low"',
            1   :  '"VDD Minimization"',
        },
        'interrupts' : {
            #system level exceptions
            0       : 'Normal Abort', # abort_isr was not called.
            2       : 'NMI',
            3       : 'Hard Fault',
            4       : 'Memory Management',
            5       : 'Bus Fault',
            6       : 'Usage Fault',
            11      : 'SVC',
            12      : 'Debug',
            14      : 'PendSVC',
            15      : 'SysTick',
            #NVIC interrupts
            4+16    : 'DCC CRC Failure',
            7+16    : 'APPS Non-secure Wdog Bite',
            12+16   : 'TZ Invoked Abort',
            49+16   : 'RPM Wdog Bark',
        },
        'gcc_reset_reason' : {
            0       : 'secure_wdog_expired',
            1       : 'pmic_resin_reset',
            2       : 'msm_tsense0_reset',
            3       : 'srst_reset',
            4       : 'proc_halt_cti',
            5       : 'msm_tsense1_reset',
            6       : 'pmic_abnormal_resin_reset',
            7       : 'eud_srst_reset',
            8       : 'qdss_sw_srst_reset',
            9       : 'PS_HOLD is dropped not because of WDOG_EXPIRY or TSENSE_TRIGGER or because of intentional reset for SoC from reset controller',
        },
        'reg_names' : {
            0x179880b0:'APCS_ALIAS0_CORE_HANG_THRESHOLD',
            0x179880b4:'APCS_ALIAS0_CORE_HANG_VALUE',
            0x179880bc:'APCS_ALIAS0_CORE_HANG_CONFIG',
            0x179980b0:'APCS_ALIAS1_CORE_HANG_THRESHOLD',
            0x179980b4:'APCS_ALIAS1_CORE_HANG_VALUE',
            0x179980bc:'APCS_ALIAS1_CORE_HANG_CONFIG',
            0x179a80b0:'APCS_ALIAS2_CORE_HANG_THRESHOLD',
            0x179a80b4:'APCS_ALIAS2_CORE_HANG_VALUE',
            0x179a80bc:'APCS_ALIAS2_CORE_HANG_CONFIG',
            0x179b80b0:'APCS_ALIAS3_CORE_HANG_THRESHOLD',
            0x179b80b4:'APCS_ALIAS3_CORE_HANG_VALUE',
            0x179b80bc:'APCS_ALIAS3_CORE_HANG_CONFIG',
            0x178880b0:'APCS_ALIAS4_CORE_HANG_THRESHOLD',
            0x178880b4:'APCS_ALIAS4_CORE_HANG_VALUE',
            0x178880bc:'APCS_ALIAS4_CORE_HANG_CONFIG',
            0x178980b0:'APCS_ALIAS5_CORE_HANG_THRESHOLD',
            0x178980b4:'APCS_ALIAS5_CORE_HANG_VALUE',
            0x178980bc:'APCS_ALIAS5_CORE_HANG_CONFIG',
            0x178a80b0:'APCS_ALIAS6_CORE_HANG_THRESHOLD',
            0x178a80b4:'APCS_ALIAS6_CORE_HANG_VALUE',
            0x178a80bc:'APCS_ALIAS6_CORE_HANG_CONFIG',
            0x178b80b0:'APCS_ALIAS7_CORE_HANG_THRESHOLD',
            0x178b80b4:'APCS_ALIAS7_CORE_HANG_VALUE',
            0x178b80bc:'APCS_ALIAS7_CORE_HANG_CONFIG',
            0x179d141c:'APCS_COMMON_THRESHOLD_0',
            0x179d1420:'APCS_COMMON_THRESHOLD_1',
            0x179d1424:'APCS_COMMON_THRESHOLD_2',
            0x179d1428:'APCS_COMMON_THRESHOLD_3',
            0x179d142c:'APCS_COMMON_THRESHOLD_4',
            0x179d1430:'APCS_COMMON_THRESHOLD_5',
            0x179d1404:'APCS_COMMON_GLADIATOR_HANG_COUNTER_0',
            0x179d1408:'APCS_COMMON_GLADIATOR_HANG_COUNTER_1',
            0x179d140c:'APCS_COMMON_GLADIATOR_HANG_COUNTER_2',
            0x179d1410:'APCS_COMMON_GLADIATOR_HANG_COUNTER_3',
            0x179d1414:'APCS_COMMON_GLADIATOR_HANG_COUNTER_4',
            0x179d1418:'APCS_COMMON_GLADIATOR_HANG_COUNTER_5',
        },
    },
    '660':{
        'masters' : {
            0  : '"APSS"',
            1  : '"MSS SW"',
            2  : '"LPASS"',
            3  : '"CDSP"',
            4  : '"TZ"',
        },
        'rail' : {
            0 : 'Mx',
            1 : 'Cx',
            2 : 'LPI_Mx',
            3 : 'LPI_Cx',
        },
        'corner' : {
            0 : 'OFF',
            1 : 'RAILWAY_RETENTION',
            2 : 'RAILWAY_SVS_MIN',
            3 : 'RAILWAY_SVS_LOW',
            4 : 'RAILWAY_SVS',
            5 : 'RAILWAY_SVS_HIGH',
            6 : 'RAILWAY_NOMINAL',
            7 : 'RAILWAY_NOMINAL_HIGH',
            8 : 'RAILWAY_TURBO',
            9 : 'RAILWAY_SUPER_TURBO',
            10 : 'RAILWAY_SUPER_TURBO_NO_CPR',
            11: 'COUNT',
        },
        'cpr_rail' : {
            0x100 : 'MX',
            0x101 : 'CX',
            0x400 : 'LPI_MX',
            0x401 : 'LPI_CX',
        },
        'cpr_mode' : {
            0 : 'OFF',
            1 : 'RETENTION',
            2 : 'MIN_SVS',
            3 : 'LOW_SVS',
            4 : 'SVS',
            5 : 'SVS_L1',
            6 : 'NOMINAL',
            7 : 'NOMINAL_L1',
            8 : 'TURBO',
            9 : 'SUPER_TURBO',
            10: 'SUPER_TURBO_NO_CPR',
            11: 'COUNT',
        },
        'cpr_controller' : {
            0x60628000 : 'CPR3',
            0x6062C000 : 'MX_CPR3',
        },
        'sleep_modes' : {
            0   :  '"VDD Low"',
            1   :  '"VDD Minimization"',
        },
        'interrupts' : {
            #system level exceptions
            0       : 'Normal Abort', # abort_isr was not called.
            2       : 'NMI',
            3       : 'Hard Fault',
            4       : 'Memory Management',
            5       : 'Bus Fault',
            6       : 'Usage Fault',
            11      : 'SVC',
            12      : 'Debug',
            14      : 'PendSVC',
            15      : 'SysTick',
            #NVIC interrupts
            4+16    : 'DCC CRC Failure',
            7+16    : 'APPS Non-secure Wdog Bite',
            12+16   : 'TZ Invoked Abort',
            49+16   : 'RPM Wdog Bark',
        },
        'gcc_reset_reason' : {
            0       : 'secure_wdog_expired',
            1       : 'pmic_resin_reset',
            2       : 'msm_tsense0_reset',
            3       : 'srst_reset',
            4       : 'proc_halt_cti',
            5       : 'msm_tsense1_reset',
            6       : 'pmic_abnormal_resin_reset',
            7       : 'eud_srst_reset',
            8       : 'qdss_sw_srst_reset',
            9       : 'PS_HOLD is dropped not because of WDOG_EXPIRY or TSENSE_TRIGGER or because of intentional reset for SoC from reset controller',
        },
        'reg_names' : {
            0x179880b0:'APCS_ALIAS0_CORE_HANG_THRESHOLD',
            0x179880b4:'APCS_ALIAS0_CORE_HANG_VALUE',
            0x179880bc:'APCS_ALIAS0_CORE_HANG_CONFIG',
            0x179980b0:'APCS_ALIAS1_CORE_HANG_THRESHOLD',
            0x179980b4:'APCS_ALIAS1_CORE_HANG_VALUE',
            0x179980bc:'APCS_ALIAS1_CORE_HANG_CONFIG',
            0x179a80b0:'APCS_ALIAS2_CORE_HANG_THRESHOLD',
            0x179a80b4:'APCS_ALIAS2_CORE_HANG_VALUE',
            0x179a80bc:'APCS_ALIAS2_CORE_HANG_CONFIG',
            0x179b80b0:'APCS_ALIAS3_CORE_HANG_THRESHOLD',
            0x179b80b4:'APCS_ALIAS3_CORE_HANG_VALUE',
            0x179b80bc:'APCS_ALIAS3_CORE_HANG_CONFIG',
            0x178880b0:'APCS_ALIAS4_CORE_HANG_THRESHOLD',
            0x178880b4:'APCS_ALIAS4_CORE_HANG_VALUE',
            0x178880bc:'APCS_ALIAS4_CORE_HANG_CONFIG',
            0x178980b0:'APCS_ALIAS5_CORE_HANG_THRESHOLD',
            0x178980b4:'APCS_ALIAS5_CORE_HANG_VALUE',
            0x178980bc:'APCS_ALIAS5_CORE_HANG_CONFIG',
            0x178a80b0:'APCS_ALIAS6_CORE_HANG_THRESHOLD',
            0x178a80b4:'APCS_ALIAS6_CORE_HANG_VALUE',
            0x178a80bc:'APCS_ALIAS6_CORE_HANG_CONFIG',
            0x178b80b0:'APCS_ALIAS7_CORE_HANG_THRESHOLD',
            0x178b80b4:'APCS_ALIAS7_CORE_HANG_VALUE',
            0x178b80bc:'APCS_ALIAS7_CORE_HANG_CONFIG',
            0x179d141c:'APCS_COMMON_THRESHOLD_0',
            0x179d1420:'APCS_COMMON_THRESHOLD_1',
            0x179d1424:'APCS_COMMON_THRESHOLD_2',
            0x179d1428:'APCS_COMMON_THRESHOLD_3',
            0x179d142c:'APCS_COMMON_THRESHOLD_4',
            0x179d1430:'APCS_COMMON_THRESHOLD_5',
            0x179d1404:'APCS_COMMON_GLADIATOR_HANG_COUNTER_0',
            0x179d1408:'APCS_COMMON_GLADIATOR_HANG_COUNTER_1',
            0x179d140c:'APCS_COMMON_GLADIATOR_HANG_COUNTER_2',
            0x179d1410:'APCS_COMMON_GLADIATOR_HANG_COUNTER_3',
            0x179d1414:'APCS_COMMON_GLADIATOR_HANG_COUNTER_4',
            0x179d1418:'APCS_COMMON_GLADIATOR_HANG_COUNTER_5',
        },
    },
    '8997':{
        'masters' : {
            0  : '"APSS"',
            1  : '"MSS SW"',
            2  : '"LPASS"',
            3  : '"SSC"',
            4  : '"TZ"',
            5  : '"SPSS"',
        },
        'rail' : {
            0 : 'Mx',
            1 : 'Cx',
            2 : 'EBI',
            3 : 'SSC_Mx',
            4 : 'SSC_Cx',
        },
        'corner' : {
            0 : 'OFF',
            1 : 'RAILWAY_RETENTION',
            2 : 'RAILWAY_SVS_MIN',
            3 : 'RAILWAY_SVS_LOW',
            4 : 'RAILWAY_SVS',
            5 : 'RAILWAY_SVS_HIGH',
            6 : 'RAILWAY_NOMINAL',
            7 : 'RAILWAY_TURBO',
            8 : 'RAILWAY_SUPER_TURBO',
            9 : 'RAILWAY_SUPER_TURBO_NO_CPR',
            10: 'COUNT',
        },
        'cpr_rail' : {
            0x100 : 'MX',
            0x101 : 'CX',
            0x104 : 'VDDA',
            0x300 : 'SSC_MX',
            0x301 : 'SSC_CX',
        },
        'cpr_mode' : {
            0 : 'OFF',
            1 : 'RETENTION',
            2 : 'MIN_SVS',
            3 : 'LOW_SVS',
            4 : 'SVS',
            5 : 'SVS_L1',
            6 : 'NOMINAL',
            7 : 'NOMINAL_L1',
            8 : 'TURBO',
            9 : 'SUPER_TURBO',
            10: 'SUPER_TURBO_NO_CPR',
            11: 'COUNT',
        },
        'cpr_controller' : {
            0x60628000 : 'CPR3',
            0x6062C000 : 'MX_CPR3',
        },
        'sleep_modes' : {
            0   :  '"VDD Low"',
            1   :  '"VDD Minimization"',
        },
        'interrupts' : {
            #system level exceptions
            0       : 'Normal Abort', # abort_isr was not called.
            2       : 'NMI',
            3       : 'Hard Fault',
            4       : 'Memory Management',
            5       : 'Bus Fault',
            6       : 'Usage Fault',
            11      : 'SVC',
            12      : 'Debug',
            14      : 'PendSVC',
            15      : 'SysTick',
            #NVIC interrupts
            4+16    : 'DCC CRC Failure',
            7+16    : 'APPS Non-secure Wdog Bite',
            12+16   : 'TZ Invoked Abort',
            49+16   : 'RPM Wdog Bark',
        },
        'gcc_reset_reason' : {
            0       : 'secure_wdog_expired',
            1       : 'pmic_resin_reset',
            2       : 'msm_tsense0_reset',
            3       : 'srst_reset',
            4       : 'proc_halt_cti',
            5       : 'msm_tsense1_reset',
            6       : 'pmic_abnormal_resin_reset',
            7       : 'eud_srst_reset',
            8       : 'qdss_sw_srst_reset',
            9       : 'PS_HOLD is dropped not because of WDOG_EXPIRY or TSENSE_TRIGGER or because of intentional reset for SoC from reset controller',
        },
        'reg_names' : {
            0x179880b0:'APCS_ALIAS0_CORE_HANG_THRESHOLD',
            0x179880b4:'APCS_ALIAS0_CORE_HANG_VALUE',
            0x179880bc:'APCS_ALIAS0_CORE_HANG_CONFIG',
            0x179980b0:'APCS_ALIAS1_CORE_HANG_THRESHOLD',
            0x179980b4:'APCS_ALIAS1_CORE_HANG_VALUE',
            0x179980bc:'APCS_ALIAS1_CORE_HANG_CONFIG',
            0x179a80b0:'APCS_ALIAS2_CORE_HANG_THRESHOLD',
            0x179a80b4:'APCS_ALIAS2_CORE_HANG_VALUE',
            0x179a80bc:'APCS_ALIAS2_CORE_HANG_CONFIG',
            0x179b80b0:'APCS_ALIAS3_CORE_HANG_THRESHOLD',
            0x179b80b4:'APCS_ALIAS3_CORE_HANG_VALUE',
            0x179b80bc:'APCS_ALIAS3_CORE_HANG_CONFIG',
            0x178880b0:'APCS_ALIAS4_CORE_HANG_THRESHOLD',
            0x178880b4:'APCS_ALIAS4_CORE_HANG_VALUE',
            0x178880bc:'APCS_ALIAS4_CORE_HANG_CONFIG',
            0x178980b0:'APCS_ALIAS5_CORE_HANG_THRESHOLD',
            0x178980b4:'APCS_ALIAS5_CORE_HANG_VALUE',
            0x178980bc:'APCS_ALIAS5_CORE_HANG_CONFIG',
            0x178a80b0:'APCS_ALIAS6_CORE_HANG_THRESHOLD',
            0x178a80b4:'APCS_ALIAS6_CORE_HANG_VALUE',
            0x178a80bc:'APCS_ALIAS6_CORE_HANG_CONFIG',
            0x178b80b0:'APCS_ALIAS7_CORE_HANG_THRESHOLD',
            0x178b80b4:'APCS_ALIAS7_CORE_HANG_VALUE',
            0x178b80bc:'APCS_ALIAS7_CORE_HANG_CONFIG',
            0x179d141c:'APCS_COMMON_THRESHOLD_0',
            0x179d1420:'APCS_COMMON_THRESHOLD_1',
            0x179d1424:'APCS_COMMON_THRESHOLD_2',
            0x179d1428:'APCS_COMMON_THRESHOLD_3',
            0x179d142c:'APCS_COMMON_THRESHOLD_4',
            0x179d1430:'APCS_COMMON_THRESHOLD_5',
            0x179d1404:'APCS_COMMON_GLADIATOR_HANG_COUNTER_0',
            0x179d1408:'APCS_COMMON_GLADIATOR_HANG_COUNTER_1',
            0x179d140c:'APCS_COMMON_GLADIATOR_HANG_COUNTER_2',
            0x179d1410:'APCS_COMMON_GLADIATOR_HANG_COUNTER_3',
            0x179d1414:'APCS_COMMON_GLADIATOR_HANG_COUNTER_4',
            0x179d1418:'APCS_COMMON_GLADIATOR_HANG_COUNTER_5',
        },
    },
    '8916':{
        'masters' : {
            0  : '"APSS"',
            1  : '"MSS SW"',
            2  : '"PRONTO"',
        },
        'plls' : {
            1  : 'XO',
            2  : 'GPLL0',
            3  : 'GPLL1',
            4  : 'GPLL2',
            5  : 'GPLL3',
            6  : 'GPLL4',
            7  : 'GPLL5',
            8  : 'BIMC_PLL',
            9  : 'GPLL6',
        },
        'icb_masters' : {
            3   : 'ICBID_MASTER_SNOC_BIMC_0',
            21  : 'ICBID_MASTER_BIMC_SNOC',
            29  : 'ICBID_MASTER_PNOC_SNOC',
            33  : 'ICBID_MASTER_SDCC_1',
            35  : 'ICBID_MASTER_SDCC_2',
            41  : 'ICBID_MASTER_BLSP_1',
            42  : 'ICBID_MASTER_USB_HS',
            76  : 'ICBID_MASTER_SNOC_BIMC_1',
            77  : 'ICBID_MASTER_SNOC_PCNOC',
            78  : 'ICBID_MASTER_AUDIO',
            85  : 'ICBID_MASTER_PCNOC_INT_0',
            86  : 'ICBID_MASTER_PCNOC_INT_1',
            87  : 'ICBID_MASTER_PCNOC_M_0',
            88  : 'ICBID_MASTER_PCNOC_M_1',
            89  : 'ICBID_MASTER_PCNOC_S_0',
            90  : 'ICBID_MASTER_PCNOC_S_1',
            91  : 'ICBID_MASTER_PCNOC_S_2',
            92  : 'ICBID_MASTER_PCNOC_S_3',
            96  : 'ICBID_MASTER_PCNOC_S_8',
            97  : 'ICBID_MASTER_PCNOC_S_9',
            99  : 'ICBID_MASTER_SNOC_INT_0',
            101 : 'ICBID_MASTER_SNOC_INT_BIMC',
        },
        'icb_slaves' : {
            0   : 'ICBID_SLAVE_EBI1',
            1   : 'ICBID_SLAVE_APPSS_L2',
            2   : 'ICBID_SLAVE_BIMC_SNOC',
            24  : 'ICBID_SLAVE_SNOC_BIMC_0',
            26  : 'ICBID_SLAVE_IMEM',
            28  : 'ICBID_SLAVE_SNOC_PCNOC',
            30  : 'ICBID_SLAVE_QDSS_STM',
            31  : 'ICBID_SLAVE_SDCC_1',
            33  : 'ICBID_SLAVE_SDCC_2',
            39  : 'ICBID_SLAVE_BLSP_1',
            40  : 'ICBID_SLAVE_USB_HS',
            41  : 'ICBID_SLAVE_PDM',
            45  : 'ICBID_SLAVE_PCNOC_SNOC',
            50  : 'ICBID_SLAVE_TCSR',
            51  : 'ICBID_SLAVE_TLMM',
            55  : 'ICBID_SLAVE_MESSAGE_RAM',
            59  : 'ICBID_SLAVE_PMIC_ARB',
            70  : 'ICBID_SLAVE_SNOC_CFG',
            104 : 'ICBID_SLAVE_SNOC_BIMC_1',
            105 : 'ICBID_SLAVE_AUDIO',
            114 : 'ICBID_SLAVE_PCNOC_INT_0',
            115 : 'ICBID_SLAVE_PCNOC_INT_1',
            116 : 'ICBID_SLAVE_PCNOC_M_0',
            117 : 'ICBID_SLAVE_PCNOC_M_1',
            118 : 'ICBID_SLAVE_PCNOC_S_0',
            119 : 'ICBID_SLAVE_PCNOC_S_1',
            120 : 'ICBID_SLAVE_PCNOC_S_2',
            121 : 'ICBID_SLAVE_PCNOC_S_3',
            125 : 'ICBID_SLAVE_PCNOC_S_8',
            126 : 'ICBID_SLAVE_PCNOC_S_9',
            130 : 'ICBID_SLAVE_SNOC_INT_0',
            132 : 'ICBID_SLAVE_SNOC_INT_BIMC',
        },
        'corner' : {
            0  : 'OFF [0]',
            1  : 'RAILWAY_RETENTION [1]',
            2  : 'RAILWAY_SVS_KRAIT [2]',
            3  : 'RAILWAY_SVS_SOC [3]',
            4  : 'RAILWAY_SVS_HIGH [4]',
            5  : 'RAILWAY_NOMINAL [5]',
            6  : 'RAILWAY_TURBO {NOMINAL_L1} [6]',
            7  : 'RAILWAY_TURBO_HIGH [7]',
            8  : 'RAILWAY_SUPER_TURBO [8]',
            9  : 'RAILWAY_SUPER_TURBO_NO_CPR [9]',
            10 : 'COUNT [10]',
        },
        'clk0' : {
            0 : 'CX0',
            1 : 'QDSS',
            2 : 'dcvs.ena',
        },
        'clk1' : {
            0 : 'pcnoc',
            1 : 'snoc',
            2 : 'sysmmnoc',
        },
    },
    '8936':{
        'masters' : {
            0  : '"APSS"',
            1  : '"MSS SW"',
            2  : '"PRONTO"',
        },
        'plls' : {
            1  : 'XO',
            2  : 'GPLL0',
            3  : 'GPLL1',
            4  : 'GPLL2',
            5  : 'GPLL3',
            6  : 'GPLL4',
            7  : 'GPLL5',
            8  : 'BIMC_PLL',
            9  : 'GPLL6',
        },
        'icb_masters' : {
            3   : 'ICBID_MASTER_SNOC_BIMC_0',
            21  : 'ICBID_MASTER_BIMC_SNOC',
            29  : 'ICBID_MASTER_PNOC_SNOC',
            33  : 'ICBID_MASTER_SDCC_1',
            35  : 'ICBID_MASTER_SDCC_2',
            41  : 'ICBID_MASTER_BLSP_1',
            42  : 'ICBID_MASTER_USB_HS',
            76  : 'ICBID_MASTER_SNOC_BIMC_1',
            77  : 'ICBID_MASTER_SNOC_PCNOC',
            78  : 'ICBID_MASTER_AUDIO',
            85  : 'ICBID_MASTER_PCNOC_INT_0',
            86  : 'ICBID_MASTER_PCNOC_INT_1',
            87  : 'ICBID_MASTER_PCNOC_M_0',
            88  : 'ICBID_MASTER_PCNOC_M_1',
            89  : 'ICBID_MASTER_PCNOC_S_0',
            90  : 'ICBID_MASTER_PCNOC_S_1',
            91  : 'ICBID_MASTER_PCNOC_S_2',
            92  : 'ICBID_MASTER_PCNOC_S_3',
            96  : 'ICBID_MASTER_PCNOC_S_8',
            97  : 'ICBID_MASTER_PCNOC_S_9',
            99  : 'ICBID_MASTER_SNOC_INT_0',
            101 : 'ICBID_MASTER_SNOC_INT_BIMC',
        },
        'icb_slaves' : {
            0   : 'ICBID_SLAVE_EBI1',
            1   : 'ICBID_SLAVE_APPSS_L2',
            2   : 'ICBID_SLAVE_BIMC_SNOC',
            24  : 'ICBID_SLAVE_SNOC_BIMC_0',
            26  : 'ICBID_SLAVE_IMEM',
            28  : 'ICBID_SLAVE_SNOC_PCNOC',
            30  : 'ICBID_SLAVE_QDSS_STM',
            31  : 'ICBID_SLAVE_SDCC_1',
            33  : 'ICBID_SLAVE_SDCC_2',
            39  : 'ICBID_SLAVE_BLSP_1',
            40  : 'ICBID_SLAVE_USB_HS',
            41  : 'ICBID_SLAVE_PDM',
            45  : 'ICBID_SLAVE_PCNOC_SNOC',
            50  : 'ICBID_SLAVE_TCSR',
            51  : 'ICBID_SLAVE_TLMM',
            55  : 'ICBID_SLAVE_MESSAGE_RAM',
            59  : 'ICBID_SLAVE_PMIC_ARB',
            70  : 'ICBID_SLAVE_SNOC_CFG',
            104 : 'ICBID_SLAVE_SNOC_BIMC_1',
            105 : 'ICBID_SLAVE_AUDIO',
            114 : 'ICBID_SLAVE_PCNOC_INT_0',
            115 : 'ICBID_SLAVE_PCNOC_INT_1',
            116 : 'ICBID_SLAVE_PCNOC_M_0',
            117 : 'ICBID_SLAVE_PCNOC_M_1',
            118 : 'ICBID_SLAVE_PCNOC_S_0',
            119 : 'ICBID_SLAVE_PCNOC_S_1',
            120 : 'ICBID_SLAVE_PCNOC_S_2',
            121 : 'ICBID_SLAVE_PCNOC_S_3',
            125 : 'ICBID_SLAVE_PCNOC_S_8',
            126 : 'ICBID_SLAVE_PCNOC_S_9',
            130 : 'ICBID_SLAVE_SNOC_INT_0',
            132 : 'ICBID_SLAVE_SNOC_INT_BIMC',
        },
        'corner' : {
            0  : 'OFF [0]',
            1  : 'RAILWAY_RETENTION [1]',
            2  : 'RAILWAY_SVS_KRAIT [2]',
            3  : 'RAILWAY_SVS_SOC [3]',
            4  : 'RAILWAY_SVS_HIGH [4]',
            5  : 'RAILWAY_NOMINAL [5]',
            6  : 'RAILWAY_TURBO {NOMINAL_L1} [6]',
            7  : 'RAILWAY_TURBO_HIGH [7]',
            8  : 'RAILWAY_SUPER_TURBO [8]',
            9  : 'RAILWAY_SUPER_TURBO_NO_CPR [9]',
            10 : 'COUNT [10]',
        },
        'clk0' : {
            0 : 'CX0',
            1 : 'QDSS',
            2 : 'dcvs.ena',
        },
        'clk1' : {
            0 : 'pcnoc',
            1 : 'snoc',
            2 : 'sysmmnoc',
        },
    },
}

names = {
    'clk0' : {
        0 : 'CX0',
        1 : 'QDSS',
        2 : 'DCVS',
    },
    'clk1' : {
        0 : 'pnoc',
        1 : 'snoc',
        2 : 'cnoc',
        3 : 'mm/axinoc',
        4 : 'mm/ahbnoc',
        5 : 'mm/ocmemnoc',
    },
    'clk2' : {
        0 : 'bimc',
    },
    'clka' : {
        1  : 'BB clk1',
        2  : 'BB clk2',
        3  : 'not supported',
        4  : 'RF clk1',
        5  : 'RF clk2',
        6  : 'RF clk3',
        7  : 'DIFF clk',
        8  : 'not supported',
        9  : 'not supported',
        10 : 'SLEEP clk',
        11 : 'DIV clk1',
        12 : 'DIV clk2',
        13 : 'DIV clk3',
    },
    'bmas' : {}, # will be filled by select_target from all_targets_data
    'bslv'  : {}, # will be filled by select_target from all_targets_data
}

try:
    target_data
except NameError:
    target_data = None
    
try:
    branch_data
except NameError:
    branch_data = None
    
# return an int if string is just a number
def maybe_int(num):
    try:
        return int(num)
    except:
        return num
    
def store_branch(branch_name):
    global branch_data
    branch_data = {
        'image' : "",
        'family': "",
        'major' : 0,
        'minor' : 0,
        'cpl'   : "",
        'rc'    : "",
        'build' : 0,
    }
    order_names = [
        'image',
        'family',
        'major',
        'minor',
        'cpl',
        'rc',
        'build',
    ]
    try:
        parts = branch_name.split('.')
        branch_data['image']  = parts[0]
        branch_data['family'] = parts[1]
        branch_data['major']  = int(parts[2])
        try:
            i = 3
            while (not('-' in parts[i])) and (i < len(parts)):
                branch_data[order_names[i]] = maybe_int(parts[i])
                i = i+1
            if (i < len(parts)) and ('-' in parts[i]):
                parts2 = parts[i].split('-')
                branch_data[order_names[i]]  = maybe_int(parts2[0])
                branch_data['build']  = int(parts2[1])
            return 0
        except:
            return 0
    except:
        # failed to parse branch
        return 1

def get_branch(element):
    return branch_data[element]

def select_target(target_name):
    global target_data
    target_data = all_targets_data['8974']
    if target_name != '8974':
        for type in all_targets_data[target_name]:
            for key in all_targets_data[target_name][type]:
                if not target_data.has_key(type):
                    target_data[type] = {}
                target_data[type][key] = all_targets_data[target_name][type][key]

    target_data['bmas'] = target_data['icb_masters']
    target_data['bslv'] = target_data['icb_slaves']

def get_name_from_resource_id(name, id):
    out = ''
    try:
        out = target_data[name][id]
    except:
        out = 'Unknown'
    return out
    
def get_resource_name(resource):
    out = ''
    if resource == 0x0:
        return 'NOT LOGGED'
    try:
        for c in reversed([hex(resource)[i:i+2] for i in xrange(2,10,2)]):
            out = out + chr(int(c, 16))
        return out;
    except:
        resource = resource << 8
        return get_resource_name(resource)

def get_gcc_reset_reason(gcc_reset):
    out = ''
    for i in target_data['gcc_reset_reason']:
        if(gcc_reset & (1<<i)):
            out += '\n\t' + target_data['gcc_reset_reason'].get(i, 'Unknown reset bit %i' % i)
    return out

def get_reg_name(reg_addr):
    return target_data['reg_names'].get(reg_addr, 'Unknown')

def get_corner_name(corner):
    return target_data['corner'].get(corner, '"Invalid corner id %i"' % corner)

def get_rail_name(rail):
    return target_data['rail'].get(rail, '"Invalid rail id %i"' % rail)

def get_cpr_rail_name(rail):
    return target_data['cpr_rail'].get(rail, '"Invalid rail id %i"' % rail)

def get_cpr_mode_name(mode):
    return target_data['cpr_mode'].get(mode, '"Invalid mode id %i"' % mode)

def get_cpr_controller_name(base_addr):
    return target_data['cpr_controller'].get(base_addr, '"Unknown controller 0x%08x"' % base_addr)

def get_master_name(master):
    return target_data['masters'].get(master, '"Unknown master %i"' % master)

def get_sleep_mode(mode):
    return target_data['sleep_modes'].get(mode, '"Unknown mode %i"' % mode)

def get_pll(pll):
    return target_data['plls'].get(pll, '"Unknown PLL %i"' % pll)

def get_clock_power(power):
    return target_data['clock_power'].get(power, '"Unknown power state %i"' % power)

def get_clock_bimc(bimc):
    return target_data['clock_bimc'].get(bimc, '"Unknown BIMC state %i"' % bimc)

def get_Voltage(Voltage):
    return target_data['Voltages'].get(Voltage, '"Unknown voltage level %i"' % Voltage)

def get_abort_interrupt_name(interrupt):
    return target_data['interrupts'].get(interrupt, '"Unknown interrupt %i"' % interrupt)

def get_interrupt_name(interrupt):
    rpm_interrupt_ids = {
        0   : '"SPM Shutdown Handshake"',
        1   : '"SPM Bringup Handshake"',
    }
    return rpm_interrupt_ids.get(interrupt, '"Unknown interrupt %i"' % interrupt)

def get_set_name(set):
    rpm_set_ids = {
        0   : '"Active Set"',
        1   : '"Sleep Set"',
        2   : '"Next Active Set"',
    }
    return rpm_set_ids.get(set, '"Unknown set %i"' % set)

def decode_bitfield(name, bit_definitions, data):
    known_bits = 0
    for id in bit_definitions:
        known_bits |= (1 << id)
    unknown_data = data - (data & known_bits)
    string = ' | '.join(['[' + bit_definitions[x] + ']' for x in bit_definitions if (1 << x) & data])
    if unknown_data:
        if string:
            string += ' ...and '
        multi_or_single = ''
        if log(unknown_data, 2) != int(log(unknown_data, 2)):
            multi_or_single = 's'
        string += 'unknown %s%s 0x%0.8x' % (name, multi_or_single, unknown_data)
    return string

def get_action_names(actions):
    rpm_action_ids = {
        0   : 'Request',
        1   : 'Notification',
    }
    return decode_bitfield('action', rpm_action_ids, actions)

def get_interrupt_names(interrupts):
    return decode_bitfield('interrupt', target_data['mpm_ints'], interrupts)

def get_icb_master_name(iden):
    return target_data['icb_masters'].get(iden, '"Unknown master %i"' % iden)

def get_icb_slave_name(iden):
    return target_data['icb_slaves'].get(iden, '"Unknown slave %i"' % iden)
