#===========================================================================
#
#  @file PBSDumpParser.py
#  @brief Python script for parsing PBS dump and giving the current status
#  of PBS Core and Clients along with PBS sequences decoded.
#
#  This file can be invoked directly by calling:
#
#  PBSDumpParser.py --file=<pbs_dump_file> --output=<parsed_output>
#  pbs_dump_file is required argument
#  parsed_output is optional argument
#
#  ===========================================================================
#
#  Copyright (c) 2015 QUALCOMM Technologies Incorporated.  
#  All Rights Reserved.
#  QUALCOMM Proprietary and Confidential.
#
#  ===========================================================================
#
#  $Header: //components/rel/core.glue/1.2.1/tools/tools/systemdrivers/pmic/honeybadger/PBSDumpParser.py#1 $
#  $DateTime: 2017/01/19 09:08:15 $
#  $Author: pwbldsvc $
#
#  ===========================================================================

# ============================================================================
# Imports
# ============================================================================

import re
import os
import sys
import argparse
import math
import pdb
 

# ============================================================================
#  Globals used by PBS dump analyze
# ============================================================================

# PBS status keys used in parsed_dump dictionary
PBS_CORE_KEY = 'PBS_CORE'
PBS_CLIENT_KEY = 'PBS_CLIENT'
PBS_MEM_KEY = 'PBS_MEM'

# pbs core and client addresses
PBS_CORE_BASE_ADDR = 0x7000
PBS_CLIENT0_BASE_ADDR = 0x7100
PBS_CLIENT0_TRIG_ADDR_LSB = 0x7050
PBS_CLIENT0_TRIG_ADDR_MSB = 0x7051

PBS_ADDR_FORMAT = '#0006x'


# ============================================================================
class PbsInstruction:
  '''
  Class capturing the single pbs instruction instruction info. Used mainly to
  decode the instruction to understandable string format
  '''

  # PBS OpCodes
  PBS_OP_CODES = {
    '0x0' : 'WRITE_REG',
    '0x2' : 'WRITE_REG',
    '0x4' : 'WRITE_REG_SUB',
    '0x6' : 'WRITE_REG_SUBR',
    '0x8' : 'WRITE_REG_BUF',
    '0xc' : 'WRITE_REG_BUF_SUB',
    '0x10': 'SECWRITE_REG',
    '0x12': 'SECWRITE_REG',
    '0x14': 'SECWRITE_REG_SUB',
    '0x16': 'SECWRITE_REG_SUBR',
    '0x18': 'SECWRITE_REG_BUF',
    '0x1a': 'SECWRITE_REG_BUF',
    '0x1c': 'SECWRITE_REG_BUF_SUB',
    '0x1e': 'SECWRITE_REG_BUF_SUBR',
    '0x20': 'ADDI',
    '0x22': 'ADD',
    '0x24': 'SUBI',
    '0x26': 'SUB',
    '0x28': 'MOVI',
    '0x2a': 'MOV',
    '0x2c': 'ANDI',
    '0x2e': 'AND',
    '0x30': 'ORI',
    '0x32': 'OR',
    '0x34': 'NOTI',
    '0x36': 'NOT',
    '0x38': 'SHIFTL',
    '0x3c': 'SHIFTR',
    '0x40': 'READ_REG',
    '0x42': 'READ_REG',
    '0x44': 'READ_REG_SUB',
    '0x46': 'READ_REG_SUBR',
    '0x48': 'READ_REG_SUB_RZ',
    '0x4a': 'READ_REG_SUBR_RZ',
    '0x80': 'GOTO',
    '0x84': 'GOTO_RELATIVE',
    '0x88': 'GOTO_SUB',
    '0x8a': 'GOTO_SUB',
    '0x8c': 'RETURN',
    '0x90': 'SKIP_IF',
    '0x92': 'SKIP_IF',
    '0x94': 'SKIP_IF',
    '0x96': 'SKIP_IF',
    '0x98': 'GOTO_SUB_NOID',
    '0xa0': 'MEMRDI',
    '0xa2': 'MEMRD',
    '0xa4': 'MEMWRI',
    '0xa6': 'MEMWR',
    '0xa8': 'FIFO_PUSH',
    '0xaa': 'FIFO_PUSHR',
    '0xc0': 'WAIT',
    '0xc2': 'WAITR',
    '0xc4': 'EOS_RESCHED',
    '0xc6': 'EOS_RESCHEDR',
    '0xfc': 'EOS End of Sequence',
    '0xf8': 'PBS_INFO',
    #'0xf8': 'NOP (No Operation)',
    #'0xff': 'UNINITIALIZED',
  }

  SKIP_IF_OPCODES = ['0x90', '0x92', '0x94', '0x96']

  SEQ_END_OPCODES = ['0xfc', '0xff', '0x8c']

  def __init__ (self, instruction, instr_addr):

    self.instruction = instruction
    self.instr_addr = instr_addr
    self.goto_addr = None
    self.goto_sub = None
    self.skipif_addr = None

    byte_arr = re.split(',', instruction[1])

    self.opcode_int = int(byte_arr[0],base=16)&0xFE
    self.opcode_str = hex(self.opcode_int)
    self.instr_str = instruction[0].lower() + ': ' + instruction[1]

    if (instruction[1].lower() == '0xf8,0xff,0xff,0xff'):
      self.instr_str += ' -> ' + 'NOP No Operation'
    elif (byte_arr[0].lower() != '0xff'):
      self.instr_str += ' -> ' + PbsInstruction.PBS_OP_CODES.get(self.opcode_str, 'UNKNOWN_OPCODE')
    else:
      self.opcode_int = int(byte_arr[0],base=16)
      self.opcode_str = hex(self.opcode_int)
      self.instr_str += ' -> ' + 'UNINITIALIZED'

    # WRITE, READ and SECWRITE variables
    if (self.opcode_int <= 0x1e) or ((self.opcode_int >= 0x40) and (self.opcode_int <= 0x4a)):
      reg_addr = ((int(byte_arr[0],base=16) & 0x3)<<16) | (int(byte_arr[1],base=16)<<8) | (int(byte_arr[2],base=16))
      reg_data = int(byte_arr[3],base=16)
      reg_offset = (int(byte_arr[2],base=16))
      reg_next = int(byte_arr[0],base=16)&0x1
      rn_addr = (int(byte_arr[2],base=16))&0xF
      rn_data = (int(byte_arr[3],base=16))&0xF

    # ADD, SUB, MOV, AND,OR, NOT and SHIFT variables  
    elif (self.opcode_int >= 0x20) and (self.opcode_int <= 0x3c):
      imm = (int(byte_arr[2],base=16)<<8) | (int(byte_arr[3],base=16))
      carry = ((int(byte_arr[1],base=16))>>7)&0x1
      word_flag = int(byte_arr[0],base=16)&0x1
      rn_dest = (int(byte_arr[1],base=16))&0xF
      rn_sr1 = (int(byte_arr[2],base=16))&0xF
      rn_sr0 = (int(byte_arr[3],base=16))&0xF

    # GOTO and SKIPIF variables  
    elif (self.opcode_int >= 0x80) and (self.opcode_int <= 0x98):
      pbs_addr = (int(byte_arr[2],base=16)<<8) | (int(byte_arr[3],base=16))
      sid = int(byte_arr[0],base=16)&0x3
      pid = int(byte_arr[1],base=16)
      skipby = int(byte_arr[0],base=16)&0x7
      mask = int(byte_arr[1],base=16)
      oper = (int(byte_arr[2],base=16))&0xF
      rn_buffer = ((int(byte_arr[2],base=16))>>4)&0xF
      data = int(byte_arr[3],base=16)

    # MEM and FIFO variables  
    elif (self.opcode_int >= 0xa0) and (self.opcode_int <= 0xaa):
      pbs_addr = (int(byte_arr[2],base=16)<<8) | (int(byte_arr[3],base=16))
      word_flag = int(byte_arr[0],base=16)&0x1
      dword_flag = (int(byte_arr[1],base=16)>>7)&0x1
      rn_byte1 = int(byte_arr[1],base=16)&0xF
      rn_byte3 = int(byte_arr[3],base=16)&0xF
      rn_addr = (int(byte_arr[2],base=16))&0xF
      reg_offset = (int(byte_arr[2],base=16))
      if dword_flag == 1:
        word_flag = 3

    # WAIT and EOS variables  
    elif (self.opcode_int >= 0xc0) and (self.opcode_int <= 0xc6):
      time_count = (int(byte_arr[2],base=16)<<8) | (int(byte_arr[3],base=16))
      unit = int(byte_arr[1],base=16)&0x1
      rn_time = int(byte_arr[3],base=16)&0xF
      clock_cycles = 0

    #WRITE_REG, SECWRITE_REG
    if (self.opcode_str == '0x0') or (self.opcode_str == '0x2') or (self.opcode_str == '0x10') or (self.opcode_str == '0x12'):
      self.instr_str += ' Write ' + hex(reg_data) + ' to register ' + hex(reg_addr)

    #WRITE_REG_SUB or SECWRITE_REG_SUB
    elif (self.opcode_str == '0x4') or (self.opcode_str == '0x14'):
      self.instr_str += ' Write ' + hex(reg_data) + ' to register offset(s) ' + hex(reg_offset)
      if reg_next == 1:
        self.instr_str += ' and ' + hex(reg_offset + 1)

    #WRITE_REG_SUBR or SECWRITE_REG_SUBR
    elif (self.opcode_str == '0x6') or (self.opcode_str == '0x16'):
      self.instr_str += ' Write ' + hex(reg_data) + ' to register stored in ' + RnValueToStr(rn_addr)
      if reg_next == 1:
        self.instr_str += ' and register+1'

    #WRITE_REG_BUF or SECWRITE_REG_BUF
    elif (self.opcode_str == '0x8') or (self.opcode_str == '0x18'):
      self.instr_str += ' write data stored in ' + RnValueToStr(rn_data) + ' to register ' + hex(reg_addr) 

    #WRITE_REG_BUF_SUB or SECWRITE_REG_BUF_SUB
    elif (self.opcode_str == '0xc') or (self.opcode_str == '0x1c'):
      self.instr_str += ' write data stored in ' + RnValueToStr(rn_data) + ' to register offset(s) ' + hex(reg_offset)
      if reg_next == 1:
        self.instr_str += ' and ' + hex(reg_offset + 1)

    #WRITE_REG_BUF_SUBR or SECWRITE_REG_BUF_SUBR
    elif (self.opcode_str == '0xe') or (self.opcode_str == '0x1e'):
      self.instr_str += ' write data stored in ' + RnValueToStr(rn_data) + ' to register stored in ' + RnValueToStr(rn_addr)
      if reg_next == 1:
        self.instr_str += ' and register+1'

    #READ_REG
    elif (self.opcode_str == '0x40') or (self.opcode_str == '0x42'):
      self.instr_str += ' read from register ' + hex(reg_addr) + ' and store data in ' + RnValueToStr(rn_data)

    #READ_REG_SUB or READ_REG_SUB_RZ
    elif (self.opcode_str == '0x44') or (self.opcode_str == '0x48'):
      if reg_next == 1:
        self.instr_str += ' 2 Bytes'
      self.instr_str += ' read from register offset ' + hex(reg_offset) + ' and store data in ' + RnValueToStr(rn_data)
      if reg_next == 1:
        self.instr_str += ' and ' + RnValueToStr(rn_data + 1)

    #READ_REG_SUBR or READ_REG_SUBR_RZ
    elif (self.opcode_str == '0x46') or (self.opcode_str == '0x4a'):
      if reg_next == 1:
        self.instr_str += ' 2 Bytes'
      self.instr_str += ' read from register offset stored in ' + RnValueToStr(rn_addr) + ' and store data in ' + RnValueToStr(rn_data)
      if reg_next == 1:
        self.instr_str += ' and ' + RnValueToStr(rn_data + 1)

    #ADDI
    elif (self.opcode_str == '0x20'):
      self.instr_str += ' ' + str(word_flag + 1) + 'BYTE ' + RnValueToStr(rn_dest) + ' = '
      self.instr_str += RnValueToStr(rn_dest) + ' + ' + hex(imm)
      if (carry == 0x1):
        self.instr_str += ' (Uses carry)'

    #ADD
    elif (self.opcode_str == '0x22'):
      self.instr_str += ' ' + str(word_flag + 1) + 'BYTE ' + RnValueToStr(rn_dest) + ' = '
      self.instr_str += RnValueToStr(rn_sr0) + ' + ' + RnValueToStr(rn_sr1)
      if (carry == 0x1):
        self.instr_str += ' (Uses carry)'

    #SUBI
    elif (self.opcode_str == '0x24'):
      self.instr_str += ' ' + str(word_flag + 1) + 'BYTE ' + RnValueToStr(rn_dest) + ' = '
      self.instr_str += RnValueToStr(rn_dest) + ' - ' + hex(imm)
      if (carry == 0x1):
        self.instr_str += ' (Uses carry borrow)'

    #SUB
    elif (self.opcode_str == '0x26'):
      self.instr_str += ' ' + str(word_flag + 1) + 'BYTE ' + RnValueToStr(rn_dest) + ' = '
      self.instr_str += RnValueToStr(rn_sr0) + ' - ' + RnValueToStr(rn_sr1)
      if (carry == 0x1):
        self.instr_str += ' (Uses carry borrow)'

    #MOVI
    elif (self.opcode_str == '0x28'):
      self.instr_str += ' ' + str(word_flag + 1) + 'BYTE ' + RnValueToStr(rn_dest) + ' = ' + hex(imm)
      if (carry == 0x1):
        self.instr_str += ' (Uses carry)'

    #MOV
    elif (self.opcode_str == '0x2a'):
      self.instr_str += ' ' + str(word_flag + 1) + 'BYTE ' + RnValueToStr(rn_dest) + ' = ' + RnValueToStr(rn_sr1)
      if (carry == 0x1):
        self.instr_str += ' (Uses carry)'

    #ANDI
    elif (self.opcode_str == '0x2c'):
      self.instr_str += ' ' + str(word_flag + 1) + 'BYTE ' + RnValueToStr(rn_dest) + ' = '
      self.instr_str += RnValueToStr(rn_dest) + ' AND ' + hex(imm)

    #AND
    elif (self.opcode_str == '0x2e'):
      self.instr_str += ' ' + str(word_flag + 1) + 'BYTE ' + RnValueToStr(rn_dest) + ' = '
      self.instr_str += RnValueToStr(rn_sr0) + ' AND ' + RnValueToStr(rn_sr1)

    #ORI
    elif (self.opcode_str == '0x30'):
      self.instr_str += ' ' + str(word_flag + 1) + 'BYTE ' + RnValueToStr(rn_dest) + ' = '
      self.instr_str += RnValueToStr(rn_dest) + ' OR ' + hex(imm)

    #OR
    elif (self.opcode_str == '0x32'):
      self.instr_str += ' ' + str(word_flag + 1) + 'BYTE ' + RnValueToStr(rn_dest) + ' = '
      self.instr_str += RnValueToStr(rn_sr0) + ' OR ' + RnValueToStr(rn_sr1)

    #NOTI
    elif (self.opcode_str == '0x34'):
      self.instr_str += ' ' + str(word_flag + 1) + 'BYTE ' + RnValueToStr(rn_dest) + ' = ~' + hex(imm)
      if (carry == 0x1):
        self.instr_str += ' (Uses carry borrow)'

    #NOT
    elif (self.opcode_str == '0x36'):
      self.instr_str += ' ' + str(word_flag + 1) + 'BYTE ' + RnValueToStr(rn_dest) + ' = ~' + RnValueToStr(rn_sr1)
      if (carry == 0x1):
        self.instr_str += ' (Uses carry borrow)'

    #SHIFTL
    elif (self.opcode_str == '0x38'):
      self.instr_str += ' shift ' + RnValueToStr(rn_dest) + ' left by ' + str(word_flag + 1) + ' bit(s)'
      if (carry == 0x1):
        self.instr_str += ' (Uses carry)'

    #SHIFTR
    elif (self.opcode_str == '0x3c'):
      self.instr_str += ' shift ' + RnValueToStr(rn_dest) + ' right by ' + str(word_flag + 1) + ' bit(s)'
      if (carry == 0x1):
        self.instr_str += ' (Uses carry)'

    #GOTO
    elif (self.opcode_str == '0x80'):
      self.goto_addr = pbs_addr
      self.instr_str += ' go to absolute PBS address ' + format(pbs_addr,PBS_ADDR_FORMAT)

    #GOTO_RELATIVE
    elif (self.opcode_str == '0x84'):
      if (pbs_addr & 0x8000):
        pbs_addr =  math.pow(2, 16) - pbs_addr
        pbs_addr = (pbs_addr/4)
        pbs_addr = int(pbs_addr)
        self.instr_str += ' jump -' 
      else:
        pbs_addr = (pbs_addr/4)
        self.instr_str += ' jump +' 
      self.instr_str += str(pbs_addr) + ' instructions'

    #GOTO_SUB
    elif (self.opcode_str == '0x88'):
      self.goto_sub = pbs_addr
      self.instr_str += ' go to subroutine at absolute PBS address ' + format(pbs_addr,PBS_ADDR_FORMAT)
      self.instr_str += ' sid:' + hex(sid) + ' pid:' + hex(pid)

    #RETURN
    elif (self.opcode_str == '0x8c'):
      self.instr_str += ' return from subroutine'

    #GOTO_SUB_NOID
    elif (self.opcode_str == '0x98'):
      self.goto_sub = pbs_addr
      self.instr_str += ' go to subroutine at absolute PBS address ' + format(pbs_addr,PBS_ADDR_FORMAT)

    #MEMRDI
    elif (self.opcode_str == '0xa0'):
      self.instr_str += ' ' + str(word_flag + 1) + 'BYTE ' + RnValueToStr(rn_byte1) + ' = '
      self.instr_str += 'value at pbs address ' + format(pbs_addr,PBS_ADDR_FORMAT)

    #MEMRD
    elif (self.opcode_str == '0xa2'):
      self.instr_str += ' ' + str(word_flag + 1) + 'BYTE ' + RnValueToStr(rn_byte1) + ' = '
      self.instr_str += 'value at pbs address stored in ' + RnValueToStr(rn_byte3)

    #MEMWRI
    elif (self.opcode_str == '0xa4'):
      self.instr_str += ' ' + str(word_flag + 1) + 'BYTE write to pbs address ' + format(pbs_addr,PBS_ADDR_FORMAT) + ' = '
      self.instr_str += 'value stored in ' + RnValueToStr(rn_byte1)

    #MEMWR
    elif (self.opcode_str == '0xa6'):
      self.instr_str += ' ' + str(word_flag + 1) + 'BYTE write to pbs address stored in ' + RnValueToStr(rn_byte3) + ' = '
      self.instr_str += 'value stored in ' + RnValueToStr(rn_byte1)

    #FIFO_PUSH
    elif (self.opcode_str == '0xa8'):
      self.instr_str += ' ' + str(word_flag + 1) + 'BYTE write to MEM(FIFOWRPTR++) = '
      self.instr_str += 'register read from sid, pid and register offset ' + hex(reg_offset)

    #FIFO_PUSHR
    elif (self.opcode_str == '0xaa'):
      self.instr_str += ' ' + str(word_flag + 1) + 'BYTE write to MEM(FIFOWRPTR++) = '
      self.instr_str += 'register read from sid, pid and register offset stored in ' + RnValueToStr(rn_addr)

    #SKIP_IF
    elif self.opcode_str in PbsInstruction.SKIP_IF_OPCODES:
      self.skipif_addr = self.instr_addr + ((skipby + 2) * 0x4)
      self.instr_str += ' skip to pbs address ' + format(self.skipif_addr, PBS_ADDR_FORMAT)
      #self.instr_str += ' (' + str(skipby + 1) + ' instruction(s))'
      self.instr_str += ' if ' + RnValueToStr(rn_buffer) + SkipIfOperator(oper) + hex(int(data))
      self.instr_str += ' (Mask = ' + hex(int(mask)) + ')'

    #WAIT
    elif (self.opcode_str == '0xc0'):
      if unit == 1:
        clock_cycles = 0.0328
        time_count = time_count + 2
      else:
        clock_cycles = 19.2
        time_count = time_count + 1

      time = time_count/clock_cycles
      self.instr_str += ' wait for ' + str(time) + ' micro seconds'

    #WAITR
    elif (self.opcode_str == '0xc2'):
      self.instr_str += ' wait for (' + RnValueToStr(rn_time) + '+1,'+ RnValueToStr(rn_time)+')'
      if unit == 1:
        self.instr_str += ' 32KHz clock cycles'
      else:
        self.instr_str += ' 19.2MHz clock cycles'

    #EOS_RESCHED
    elif (self.opcode_str == '0xc4'):
      self.instr_str += ' release pbs for execution and schedule to retrigger after '
      self.instr_str += str(time_count) + ' clock cycles(32KHz)'

    #EOS_RESCHEDR
    elif (self.opcode_str == '0xc6'):
      self.instr_str += ' release pbs for execution and schedule to retrigger after '
      self.instr_str += '(' + RnValueToStr(rn_time) + '+1,'+ RnValueToStr(rn_time)+')' + ' clock cycles(32KHz)'

    self.instr_str += '\n'

  def GetParsedInstruction (self):
    '''
    Returns the parsed pbs instruction in string format
    '''

    return self.instr_str

  def GetGoToAddr(self):
    '''
    Returns the pbs address where the instruction would go to 
    after executing GOTO instruction
    '''

    return self.goto_addr

  def GetGoToSubAddr(self):
    '''
    Returns the pbs address where the instruction would go to 
    after executing GOTO_SUB instructions
    '''

    return self.goto_sub

  def GetSkipIfAddr(self):
    '''
    Returns the pbs address where the SKIP_IF instructions would skip to
    if the condition is satisfied
    '''

    return self.skipif_addr

# ============================================================================
# SkipIfOperator
#
# Converts the machine register values to string
# ============================================================================

def SkipIfOperator(oper):

  oper_str = ''
  
  if oper == 0x0:
    oper_str = ' != '
  elif oper == 0x1:
    oper_str = ' == '
  elif oper == 0x2:
    oper_str = ' <= '
  elif oper == 0x3:
    oper_str = ' < '
  elif oper == 0x4:
    oper_str = ' >= '
  elif oper == 0x5:
    oper_str = ' > '
  elif oper == 0x6:
    oper_str = ' Carry '
  elif oper == 0x7:
    oper_str = ' Overflow '

  return oper_str


# ============================================================================
# RnValueToStr
#
# Converts the machine register values to string
# ============================================================================

def RnValueToStr(rn_value):

  rn_str = ''
  
  if rn_value < 0xA:
    rn_str = 'R' + str(rn_value)
  elif rn_value == 0xA:
    rn_str = 'RA'
  elif rn_value == 0xB:
    rn_str = 'RB'
  elif rn_value == 0xC:
    rn_str = 'RC'
  elif rn_value == 0xD:
    rn_str = 'OFFSET'
  elif rn_value == 0xE:
    rn_str = 'PID'
  elif rn_value == 0xF:
    rn_str = 'SID'

  return rn_str


# ============================================================================
# HwTriggerNumStr
#
# Returns the hardware trigger number as a string
# ============================================================================

def HwTriggerNumStr(reg_value):

  hw_trig_str = ''

  if (reg_value&0xF) == 0:
    return 'NONE'
  
  if (reg_value & 0x01) == 0x01:
    hw_trig_str += 'HW_TRIG0; '
  
  if (reg_value & 0x02) == 0x02:
    hw_trig_str += 'HW_TRIG1; '
  
  if (reg_value & 0x04) == 0x04:
    hw_trig_str += 'HW_TRIG2; '
  
  if (reg_value & 0x08) == 0x08:
    hw_trig_str += 'HW_TRIG3;'

  return hw_trig_str


# ============================================================================
# GetPbsCoreStatus
#
# Returns the PBS core status in string format
# ============================================================================

def GetPbsCoreStatus(core_dump):

  base_addr = PBS_CORE_BASE_ADDR
  digmajor = base_addr + 0x1
  status0 = base_addr + 0x8
  status1 = base_addr + 0x90
  status2 = base_addr + 0x91
  pc_status0 = base_addr + 0xa
  pc_status1 = base_addr + 0xb
  ir_status0 = base_addr + 0xc
  ir_status1 = base_addr + 0xd
  ir_status2 = base_addr + 0xe
  ir_status3 = base_addr + 0xf
  err_pc_status0 = base_addr + 0x92
  err_pc_status1 = base_addr + 0x93
  err_ir_status0 = base_addr + 0x94
  err_ir_status1 = base_addr + 0x95
  err_ir_status2 = base_addr + 0x96
  err_ir_status3 = base_addr + 0x97
  trig_status0 = base_addr + 0x98
  trig_status1 = base_addr + 0x99
  trig_status2 = base_addr + 0x9a
  digmajor_rev = 0
  status_arr = ['UNKNOWN', 'NORMAL', 'ERROR', 'ABORT']
  parsed_str = '\n'
  parsed_str += '**PBS_CORE_STATUS**\n'

  if (digmajor in core_dump): 
    digmajor_rev = core_dump[digmajor]

  if (pc_status0 in core_dump) and (pc_status1 in core_dump): 
    curr_pc = (core_dump[pc_status1]<<8)|core_dump[pc_status0]
    parsed_str += 'CURRENT_PROGRAM_COUNTER: ' + format(curr_pc, "#0006x") + '\n'
  
  if (ir_status0 in core_dump) and (ir_status1 in core_dump) and (ir_status2 in core_dump) and (ir_status3 in core_dump): 
    curr_ins = hex(core_dump[ir_status3]) + ',' + hex(core_dump[ir_status2]) 
    curr_ins += ',' + hex(core_dump[ir_status1]) + ',' + hex(core_dump[ir_status0]) 
    parsed_str += 'CURRENT_INSTRUCTION: ' + curr_ins + '\n'
  
  if (status0 in core_dump): 
    if (digmajor_rev >= 3) and ((core_dump[status0]&0xF) == 0xF):
      parsed_str += 'LAST_SEQUENCE_COMPLETED: NONE\n'
    else:
      parsed_str += 'LAST_SEQUENCE_COMPLETED: CLIENT' + str(core_dump[status0]&0xF)
      parsed_str += ' ' + status_arr[(core_dump[status0]>>4)&0x3] + '_COMPLETION\n'
  
  if (status1 in core_dump): 
    if (digmajor_rev >= 3) and (((core_dump[status1]>>4)&0xF) == 0xF): 
      parsed_str += 'LAST_SEQUENCE_IN_SERVICE: NONE\n'
    else:
      parsed_str += 'LAST_SEQUENCE_IN_SERVICE: CLIENT' + str((core_dump[status1]>>4)&0xF) + '\n'
       
    if (digmajor_rev >= 3) and ((core_dump[status1]&0xF) == 0xF):
      parsed_str += 'LAST_SEQUENCE_NORMAL: NONE\n'
    else:
      parsed_str += 'LAST_SEQUENCE_NORMAL: CLIENT' + str(core_dump[status1]&0xF) + '\n'
  
  if (status2 in core_dump):        
    if (digmajor_rev >= 3) and (((core_dump[status2]>>4)&0xF) == 0xF):
      parsed_str += 'LAST_SEQUENCE_ABORTED: NONE\n'
    else:  
      parsed_str += 'LAST_SEQUENCE_ABORTED: CLIENT' + str((core_dump[status2]>>4)&0xF) + '\n'
           
    if (digmajor_rev >= 3) and ((core_dump[status2]&0xF) == 0xF):
      parsed_str += 'LAST_SEQUENCE_ERROR: NONE\n'
    else:
      parsed_str += 'LAST_SEQUENCE_ERROR: CLIENT' + str(core_dump[status2]&0xF) + '\n'
  
  if (err_pc_status0 in core_dump) and (err_pc_status1 in core_dump): 
    err_pc = (core_dump[err_pc_status1]<<8)|core_dump[err_pc_status0]
    parsed_str += 'LAST_ERROR_PROGRAM_COUNTER: ' + format(err_pc, "#0006x") + '\n'
  
  if (err_ir_status0 in core_dump) and (err_ir_status1 in core_dump) and (err_ir_status2 in core_dump) and (err_ir_status3 in core_dump): 
    err_ins = hex(core_dump[err_ir_status3]) + ',' + hex(core_dump[err_ir_status2]) 
    err_ins += ',' + hex(core_dump[err_ir_status1]) + ',' + hex(core_dump[err_ir_status0]) 
    parsed_str += 'LAST_ERROR_INSTRUCTION: ' + err_ins + '\n'
  
  if (trig_status0 in core_dump) and (trig_status1 in core_dump) and (trig_status2 in core_dump): 
    parsed_str += 'LAST_TRIGGER_COMPLETED_ON: ' + HwTriggerNumStr(core_dump[trig_status0]) + '\n'
    parsed_str += 'LAST_TRIGGER_IN_SERVICE: ' + HwTriggerNumStr(core_dump[trig_status1]>>4) + '\n'
    parsed_str += 'LAST_TRIGGER_NORMAL: ' + HwTriggerNumStr(core_dump[trig_status1]) + '\n'
    parsed_str += 'LAST_TRIGGER_ABORTED: ' + HwTriggerNumStr(core_dump[trig_status2]>>4) + '\n'
    parsed_str += 'LAST_TRIGGER_ERROR: ' + HwTriggerNumStr(core_dump[trig_status2]) + '\n'

  parsed_str += '\n'

  return parsed_str


# ============================================================================
# GetPbsClientTriggerAddr
#
# Returns the PBS client status in string format
# ============================================================================

def GetPbsClientTriggerAddr(client_index, client_dump):

  trig_addr_lsb = PBS_CLIENT0_TRIG_ADDR_LSB + (client_index * 0x4)
  trig_addr_msb = PBS_CLIENT0_TRIG_ADDR_MSB + (client_index * 0x4)
  trig_addr = None

  if trig_addr_lsb in client_dump:  
    trig_addr = (client_dump[trig_addr_msb]<<8)|client_dump[trig_addr_lsb]

  return trig_addr

# ============================================================================
# GetPbsClientStatus
#
# Returns the PBS client status in string format
# ============================================================================

def GetPbsClientStatus(client_index, client_dump):

  base_addr = PBS_CLIENT0_BASE_ADDR + (client_index * 0x100)
  perph_subtype = base_addr + 0x5
  status0 = base_addr + 0x8
  status1 = base_addr + 0x9
  trig_latched = base_addr + 0xa
  trig_cfg0 = base_addr + 0x40
  trig_cfg1 = base_addr + 0x41
  en_ctl = base_addr + 0x46
  trig_addr_lsb = PBS_CLIENT0_TRIG_ADDR_LSB + (client_index * 0x4)
  trig_addr_msb = PBS_CLIENT0_TRIG_ADDR_MSB + (client_index * 0x4)
  trig_addr = 0
  perph_subtype_val = 0
  comp_status_arr = ['EXECUTING', 'NORMAL_COMPLETION', 'ERROR_COMPLETION', 'ABORT_COMPLETION']
  parsed_str = '\n'
  parsed_str += '**PBS_CLIENT' + str(client_index) + '_STATUS**\n'

  if perph_subtype in client_dump:
    perph_subtype_val = client_dump[perph_subtype]
  
  if status0 in client_dump:
    parsed_str += 'CLIENT_ENABLED: '

    if (client_dump[status0] & 0x80) == 0x80:
      parsed_str += 'TRUE\n'
    else:
      parsed_str += 'FALSE\n'

    if (perph_subtype_val >= 0x9):
      parsed_str += 'HW_CLIENT_ENABLED: '
  
      if (client_dump[status0] & 0x1) == 0x1:
        parsed_str += 'TRUE\n'
      else:
        parsed_str += 'FALSE\n'
    else:
      parsed_str += 'HW_TRIGGER_ENABLED: '
  
      if (client_dump[status0] & 0x40) == 0x40:
        parsed_str += 'TRUE\n'
      else:
        parsed_str += 'FALSE\n'
  
  if trig_latched in client_dump:  
    parsed_str += 'SW_TRIGGER_LATCHED: '
    if (client_dump[trig_latched] & 0x80) == 0x80:
      parsed_str += 'TRUE\n'
    else:
      parsed_str += 'FALSE\n'
    parsed_str += 'HW_TRIGGERS_LATCHED: ' + HwTriggerNumStr(client_dump[trig_latched]) + '\n'

  if trig_cfg0 in client_dump: 
    if (perph_subtype_val >= 0x9): 
      parsed_str += 'HW_TRIGGERS_RISING_EDGE_ENABLED: ' + HwTriggerNumStr(client_dump[trig_cfg0]) + '\n'
    else:
      parsed_str += 'TRIGGER_RISING_EDGE_ENABLED: '
      if (client_dump[trig_cfg0] & 0x80) == 0x80:
        parsed_str += 'TRUE\n'
      else:
        parsed_str += 'FALSE\n'

      parsed_str += 'TRIGGER_FALLING_EDGE_ENABLED: '
      if (client_dump[trig_cfg0] & 0x40) == 0x40:
        parsed_str += 'TRUE\n'
      else:
        parsed_str += 'FALSE\n'

  if trig_cfg1 in client_dump:  
    parsed_str += 'HW_TRIGGERS_FALLING_EDGE_ENABLED: ' + HwTriggerNumStr(client_dump[trig_cfg1]) + '\n'
  
  if status1 in client_dump:
    parsed_str += 'CLIENT_COMP_STATUS: ' + comp_status_arr[(client_dump[status1]>>4)&0x3] + '\n'

  trig_addr = GetPbsClientTriggerAddr(client_index, client_dump)

  if trig_addr != None:
    parsed_str += 'TRIGGER_ADDRESS: ' + format(trig_addr, PBS_ADDR_FORMAT) + '\n'

  parsed_str += '\n'

  return parsed_str

# ============================================================================
# ConstructPbsClientSequence
#
# Constructs the PBS sequence for each client
# ============================================================================

def ConstructPbsClientSequence (trig_addr, pbs_mem_dump):

  parsed_str = ''
  curr_addr = trig_addr
  sub_addr = None
  goto_addr = None
  skipif_addr = None

  while (curr_addr in pbs_mem_dump) and (pbs_mem_dump[curr_addr].opcode_str not in PbsInstruction.SEQ_END_OPCODES):
    parsed_str += pbs_mem_dump[curr_addr].GetParsedInstruction()
    if (pbs_mem_dump[curr_addr].GetSkipIfAddr() != None):
      skipif_addr = pbs_mem_dump[curr_addr].GetSkipIfAddr()
      curr_addr = curr_addr + 0x4
      continue
    elif (pbs_mem_dump[curr_addr].GetGoToAddr() != None):
      goto_addr = pbs_mem_dump[curr_addr].GetGoToAddr()
      # this condition is a do-while loop so break out of it
      if goto_addr == trig_addr:
        return parsed_str
      parsed_str += '\goto sequence at absolute pbs address ' + format(goto_addr, PBS_ADDR_FORMAT) + ' start\n'
      parsed_str += ConstructPbsClientSequence(goto_addr, pbs_mem_dump)
      parsed_str += '\goto sequence at absolute pbs address ' + format(goto_addr, PBS_ADDR_FORMAT) + ' end\n'
      curr_addr = curr_addr + 0x4
      if skipif_addr == None:
        return parsed_str
        
    elif pbs_mem_dump[curr_addr].GetGoToSubAddr() != None:
      sub_addr = pbs_mem_dump[curr_addr].GetGoToSubAddr()
      parsed_str += '\subroutine at absolute pbs address ' + format(sub_addr, PBS_ADDR_FORMAT) + ' start\n'
      parsed_str += ConstructPbsClientSequence(sub_addr, pbs_mem_dump)
      parsed_str += '\subroutine at absolute pbs address ' + format(sub_addr, PBS_ADDR_FORMAT) + ' end\n'
      curr_addr = curr_addr + 0x4
    else:
      curr_addr = curr_addr + 0x4

    # end construct pbs sequence recurssion if the skipif address is reached
    if curr_addr == skipif_addr:
      skipif_addr = None

  if (curr_addr in pbs_mem_dump):
    parsed_str += pbs_mem_dump[curr_addr].GetParsedInstruction()
  else:
    parsed_str += '\pbs instruction not found for pbs address: ' + format(curr_addr, PBS_ADDR_FORMAT) + '\n'

  return parsed_str

# ============================================================================
# AnalyzePbsDump
#
# Parses the PBS dump
# ============================================================================

def AnalyzePbsDump(config):

  pbs_dump_keys = [PBS_CORE_KEY, PBS_CLIENT_KEY, PBS_MEM_KEY]
  new_key_found = False
  current_key = None
  
  pbs_core_dump = {}
  pbs_mem_dump = {}
  pbs_mem_dump_key = 0

  pbs_client_dump = {}
  pbs_client_status = []
  pbs_client_index = 0

  instruction = []

  for element in config['input_dump_list']:

    if not element.strip():
      continue

    for key in pbs_dump_keys:
      found = None
      found = re.match(key, element)
      if found == None:
        new_key_found = False
      else:
        if key == PBS_MEM_KEY:
          # Using an invalid PBS instruction address as key for PBS memory headings
          if pbs_mem_dump_key == 0:
            pbs_mem_dump.update({(pbs_mem_dump_key - 2): '\n\n' + element + '\n'})
          else:
            pbs_mem_dump.update({(pbs_mem_dump_key + 2): '\n\n' + element + '\n'})
        new_key_found = True
        current_key = key
        break

    if new_key_found == False:
      if current_key == PBS_MEM_KEY:
        instruction = re.split(': ', element)
        pbs_mem_dump_key = int(instruction[0], 16)
        pbs_mem_dump.update({pbs_mem_dump_key:PbsInstruction(instruction, pbs_mem_dump_key)})
      elif current_key == PBS_CORE_KEY:
        reg_status = re.split(': ', element)
        pbs_core_dump.update({int(reg_status[0],16): int(reg_status[1],16)})
      elif current_key == PBS_CLIENT_KEY:
        found = None
        found = re.match("CLIENT", element)
        if found != None:
          reg_status = re.split(': ', element)
          config['client_base_addr'].append(int(reg_status[1],16))
          continue
        reg_status = re.split(': ', element)
        pbs_client_dump.update({int(reg_status[0],16): int(reg_status[1],16)})
      elif re.match('\w{2,3}\d{4}', element):
        config['pmic_rev_info'] = element

  #pdb.set_trace()
  return {PBS_CORE_KEY: pbs_core_dump, PBS_CLIENT_KEY: pbs_client_dump, PBS_MEM_KEY: pbs_mem_dump}

# ============================================================================
# ReadInputFile
#
# Reads the input pbs dump file and updates the parsed_dump dictionary with 
# parsed pbs dump.
# ============================================================================

def ReadInputFile(config):
  file = config['input_file']

  try:
    input = open(file, 'r')
    print('Input PBS dump file:' + file)
  except:
    print('Cannot open "%s"' % file)
    sys.exit(1)

  config['input_dump_list'] = input.read().splitlines()
    
  config['parsed_dump'].update(AnalyzePbsDump(config))

# ============================================================================
# WriteOutputFile
#
# Creates an output file and writes the parsed pbs dump to output file.
# ============================================================================

def WriteOutputFile(config):
  output_flag = False
  
  if config['std_output']:
    output = sys.stdout
  elif 'output_file' in config:
    try:
      # Create and open an output file.
      output = open(config['output_file'], 'w+')
      output_flag = True
    except:
      print('Unable to create and open output file so diverting output to cmd prompt')
      output = sys.stdout
  else:
    print('Unable to create and open output file so diverting output to cmd prompt')
    output = sys.stdout

  output.write(config['pmic_rev_info'] + 'PBS DUMP')
  output.write('\n')

  output.write(GetPbsCoreStatus(config['parsed_dump'][PBS_CORE_KEY]))

  for base_addr in config['client_base_addr']:
    client_index = (base_addr - PBS_CLIENT0_BASE_ADDR)/0x100
    output.write(GetPbsClientStatus(client_index, config['parsed_dump'][PBS_CLIENT_KEY]))
    trig_addr = GetPbsClientTriggerAddr(client_index, config['parsed_dump'][PBS_CLIENT_KEY])
    output.write('PBS_CLIENT' + str(client_index) + '_SEQUENCE:\n')
    output.write(ConstructPbsClientSequence(trig_addr, config['parsed_dump'][PBS_MEM_KEY]))

  output.write('\n**PBS_MEMORY_DUMP**\n')
  for pbs_key in sorted(config['parsed_dump'][PBS_MEM_KEY].keys()):
    if type(config['parsed_dump'][PBS_MEM_KEY][pbs_key]) is str:
      output.write(config['parsed_dump'][PBS_MEM_KEY][pbs_key])
    else:
      output.write(config['parsed_dump'][PBS_MEM_KEY][pbs_key].GetParsedInstruction())

  if output_flag ==  True:
    print('PBS dump parsed to "%s" file' % config['output_file'])

  if 'output_file' in config:
    output.close()

# ============================================================================
# ParseCommandLine
#
# Parse command line arguments.
# ============================================================================

def ParseCommandLine (argv, config):
  parser = argparse.ArgumentParser(description='Parses PBS dump file')
  parser.add_argument('--file', type=str, required=True, help='required argument to provide input pbs dump text file location')
  parser.add_argument('--output', type=str, help='optional argument to provide location for parsed pbs dump output file')
  args = parser.parse_args()
  config['input_file'] = args.file
  if (args.output != None):
    if (args.output == 'std') | (args.output == 'cmd'):
      config['std_output'] = True
    else:
      # Check for // or \\ or [A-Z]: to make sure current dir is not used
      matches = re.match('(^[A-Za-z]:)|(^\\\\)|(^\/\/)', args.output)
      if matches != None:
        config['output_file'] = args.output
      else:
        print('Cannot use the given output location so using default output location!')

# ============================================================================
# Main
#
# Entry point.
# ============================================================================

if __name__ == "__main__":

  config = {
    'parsed_dump': {},
    'input_dump_list': [],
    'pmic_rev_info': '',
    'client_base_addr': [],
    'input_file': False,
    'output_file': 'C:\\Temp\\pbsdump_parsed.txt',
    'std_output': False,
  }

  # Parse the command line
  ParseCommandLine(sys.argv[1:], config)

  # Read the input file
  ReadInputFile(config)

  # Write to output file
  WriteOutputFile(config)

