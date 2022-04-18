#  ===========================================================================
#
#  Copyright (c) 2015-2016 Qualcomm Technologies, Inc.
#  All Rights Reserved.
#  QUALCOMM Proprietary and Confidential.
#
#  ===========================================================================


dump_file_types = [
    #
    # Core stuff, most important.
    #
    {   # The place all of the code lives
        'display_name'  : "CODERAM",
        'name'          : {'rpm_code_ram.bin', 'CODERAM.BIN', 'RPM0.bin'},
        'ext'           : {'.BIN', '.LST'},
        'basename'      : {'RPM_CODE_RAM', 'CODERAM', 'RPM0'},
        'required'      : True,
        'no_load'       : False,
        'base'          : {
                            'badger' : 0x100000,
                            'bear'   : 0x000000,
                            'honey'  : 0x000000,
                          },
    },
    {   # The place all of the data lives
        'display_name'  : "DATARAM",
        'name'          : {'rpm_data_ram.bin', 'DATARAM.BIN', 'RPM1.bin'},
        'ext'           : {'.BIN', '.LST'},
        'basename'      : {'RPM_DATA_RAM', 'DATARAM', 'RPM1'},
        'required'      : True,
        'no_load'       : False,
        'base'          : {
                              'badger' : 0x190000,
                              'bear'   : 0x090000,
                              'honey'  : 0x090000,
                          },
    },
    {   # The place all of IPC messages live
        'display_name'  : "MSGRAM",
        'name'          : {'rpm_msg_ram.bin', 'MSGRAM.BIN', 'RPM2.bin'},
        'ext'           : {'.BIN', '.LST'},
        'basename'      : {'RPM_MSG_RAM', 'MSGRAM', 'RPM2'},
        'required'      : True,
        'no_load'       : False,
        'base'          : {
                              'badger' : 0xFC428000,
                              'bear'   : 0x60060000,
                              'honey'  : {
                                            '8996': 0x60068000,
                                            '8998': 0x60778000,
                                            '660' : 0x60778000,
                                         },
                          },
    },
    {   # Certain system data is stored in OCIMEM
        'display_name'  : "OCIMEM",
        'name'          : {'OCIMEM.BIN'},
        'ext'           : {'.BIN', '.LST'},
        'basename'      : {'OCIMEM', 'OCIMEM_0X6680000--0X66BFFFF'},
        'no_load'       : True,
        'path'          : "",
        'base'          : {
                              'badger' : 0x0,
                              'bear'   : 0x0,
                              'honey'  : {
                                            '8996':0x6680000,
                                            '8998':0x14680000,
                                            '660' :0x14680000,
                                         }
                          },
        'data'          : {
                              'dumptable' : {
                                                '8996'   : 0x066BF000 + 0x10,
                                                '8998'   : 0x146BF000 + 0x10,
                                                '660'    : 0x146BF000 + 0x10,
                                                '8997'   : 0x146BF000 + 0x10,
                                            },
                          },
    },
    {   # Heap is copied to DDR before overwritting
        'display_name'  : "DDRCS0",
        'name'          : {'DDRCS0.BIN', 'sectionDDRCS0.BIN'},
        'ext'           : {'.BIN', '.LST'},
        'basename'      : {'DDRCS0', 'DRAM_0X80000000--0XFFFFFFFF'},
        'no_load'       : True,
        'path'          : "",
        'size'          : 0x0,
        'update'        : True,
        'base'          : {
                              'badger' : 0x0,
                              'bear'   : 0x0,
                              'honey'  : {  #Size      : base address
                                            0x60000000 : 0x80000000,
                                            0x80000000 : 0x80000000,
                                         },
                          },
    },
    {   # Heap is copied to DDR before overwritting
        'display_name'  : "DDRCS1",
        'name'          : {'DDRCS1.BIN', 'sectionDDRCS1.BIN'},
        'ext'           : {'.BIN', '.LST'},
        'basename'      : {'DDRCS1', 'dram1_0x100000000--0x17fffffff'},
        'no_load'       : True,
        'path'          : "",
        'update'        : True,
        'size'          : 0x0,
        'base'          : {
                              'badger' : 0x0,
                              'bear'   : 0x0,
                              'honey'  : {  #Size      : base address
                                            0x60000000 : 0x20000000,
                                            0x80000000 : 0x100000000,
                                         },
                          },
    },
    #{   # The values of RPM registers. Only consulted if there was no core dump.
    #    'name'     : 'rpm_registers.cmm',
    #    # FIXME: need some parser here to make this file useful...
    #},

    #
    # Generic RPM peripherals, less important
    #
    {   # RPM's generic Cortex-M3 hardware.
        'display_name'  : "RPM_SCS",
        'name'          : {'rpm_scs.bin'},
        'ext'           : {'.BIN'},
        'basename'      : {'RPM_SCS'},
        'base'          : {
                              'badger' : 0xE000E000,
                              'bear'   : 0xE000E000,
                              'honey'  : 0xE000E000,
                          },
    },
    {   # RPM's Qualcomm-written hardware.
        'display_name'  : "RPM_DEC",
        'name'          : {'rpm__dec.bin'},
        'ext'           : {'.BIN'},
        'basename'      : {'RPM__DEC'},
        'base'          : {
                              'badger' : 0x180000,
                              'bear'   : 0x080000,
                              'honey'  : 0x280000,
                          },
    },
    {   # RPM's timer-related hardware (next 3)
        'display_name'  : "RPM_QTMR_AC",
        'name'          : {'rpm__qtmr_ac.bin'},
        'ext'           : {'.BIN'},
        'basename'      : {'RPM__QTMR_AC'},
        'base'          : {
                              'badger' : 0x182000,
                              'bear'   : 0x082000,
                              'honey'  : 0x282000,
                          },
    },
    {
        'display_name'  : "RPM_QTMR_F0",
        'name'          : {'rpm__qtmr_f0.bin'},
        'ext'           : {'.BIN'},
        'basename'      : {'RPM__QTMR_F0'},
        'base'          : {
                              'badger' : 0x183000,
                              'bear'   : 0x083000,
                              'honey'  : 0x283000,
                          },
    },
    {
        'display_name'  : "RPM_QTMR_F1",
        'name'          : {'rpm__qtmr_f1.bin'},
        'ext'           : {'.BIN'},
        'basename'      : {'RPM__QTMR_F1'},
        'base'          : {
                              'badger' : 0x184000,
                              'bear'   : 0x084000,
                              'honey'  : 0x284000,
                          },
    },
    {   # RPM data RAM access control unit.
        'display_name'  : "RPM_MPU",
        'name'          : {'rpm__mpu.bin'},
        'ext'           : {'.BIN'},
        'basename'      : {'RPM__MPU'},
        'base'          : {
                              'badger' : 0x186000,
                              'bear'   : -1, #does not exist on bear?
                              'honey'  : 0x289000,
                          },
    },
    {   # RPM code RAM access control unit.
        'display_name'  : "RPM_APU",
        'name'          : {'rpm__apu.bin'},
        'ext'           : {'.BIN'},
        'basename'      : {'RPM__APU'},
        'base'          : {
                              'badger' : 0x187000,
                              'bear'   : 0x087000,
                              'honey'  : 0x087000,
                          },
    },
    {   # RPM message RAM access control unit.
        'display_name'  : "RPM_RPU",
        'name'          : {'rpm__rpu.bin'},
        'ext'           : {'.BIN'},
        'basename'      : {'RPM__RPU'},
        'base'          : {
                              'badger' : 0xFC420000,
                              'bear'   : -1, #does not exist on bear?
                              'honey'  : -1,
                          },
    },

    #
    # System peripherals, vaguely RPM related.
    #
    {   # The bits of the MPM that control low power states.
        'display_name'  : "RPM_MPM",
        'name'          : {'mpm.bin'},
        'ext'           : {'.BIN'},
        'basename'      : {'MPM'},
        'base'          : {
                              'badger' : 0xFC4A0000,
                              'bear'   : 0x004A0000,
                              'honey'  : 0x004A0000,
                          },
    },
    {   # The global clock controller.
        'display_name'  : "RPM_CLK_CTL",
        'name'          : {'clk_ctl.bin'},
        'ext'           : {'.BIN'},
        'basename'      : {'CLK_CTL'},
        'base'          : {
                              'badger' : 0xFC400000,
                              'bear'   : -1, #not captured for bear?
                              'honey'  : 0x00300000,
                          },
    },
    {   # Some parts of the TCSR.
        'display_name'  : "RPM_TCSR_REGS",
        'name'          : {'tcsr_regs.bin'},
        'ext'           : {'.BIN'},
        'basename'      : {'TCSR_REGS'},
        'base'          : {
                              'badger' : 0xFD4A1300,
                              'bear'   : 0x01937300,
                              'honey'  : 0x007A0000,
                          },
    },
]

known_targets = {
    '8974' : 'badger',
    '9x25' : 'badger',
    '8x10' : 'badger',
    '8x26' : 'badger',
    '8084' : 'badger',
    '9x35' : 'badger',
    '8994' : 'badger',
    '8996' : 'honey',
    '8998' : 'honey',
    '660'  : 'honey',
    '8997' : 'honey',
    '8916' : 'bear',
    '8936' : 'bear',
    '8939' : 'bear',
    '9x45' : 'bear',
}

known_families = {
    'badger'        : 'badger',
    'b'             : 'badger',
    'bear'          : 'bear',
    'bagheera'      : 'bear',
    'h'             : 'honey',
    'honeybadger'   : 'honey',
    'honey'         : 'honey',
}

default_target_family = {
    'target'        : '660',
    'family'        : 'honey',
    'family_name'   : 'Honeybadger',
    'branch'        : 'RPM.BF.1.8',
}

dumptable_version_map = {
    '8996'    : '1.4',
    '8998'    : '1.4',
    '660'     : '1.4',
    '8997'    : '1.4',
    'default' : '1.4',
}

dumptable_config = {
    '1.4' :  {
                'version' : 0x200000,
                'data'    : {
                              'size'        : 0x3C,
                              'version'     : 0x0,
                              'magic'       : 0x4,
                              'magic_value' : 0x0, #need to actually figure this one out
                              'name'        : 0x8,
                              'name_size'   : 0x20,
                              'addr'        : 0x28,
                              'len'         : 0x30,
                              'reserved'    : 0x38,
                            },
                'entry'   : {
                              'size'        : 0x30,
                              'id'          : 0x0,
                              'name'        : 0x4,
                              'name_size'   : 0x20,
                              'type'        : 0x24,
                              'addr'        : 0x28,
                            },
                'table'   : {
                              'size'        : 0x30,
                              'version'     : 0x0,
                              'num_entries' : 0x4,
                              'entries'     : 0x8,
                            },
              },
}
