#!/usr/bin/python
# -*- coding: cp1252 -*-
#===============================================================================
#
# tz_diag_parser.py
#
# GENERAL DESCRIPTION
#    Generic TZ diag region parser [ MSM8996 ]
#
# Copyright (c) 2015 by QUALCOMM Technologies, Incorporated.
# All Rights Reserved. 
#
#-------------------------------------------------------------------------------
#
#  $DateTime: 2020/01/14 12:35:09 $
#  $Manager       : Min Guo <mguo@qualcomm.com> $
#  $Author        : Anil Varma Biruduraju <abirudur@qualcomm.com> $
#
#                      EDIT HISTORY FOR FILE
#
#  This section contains comments describing changes made to the module.
#  Notice that changes are listed in ascending date order.
#
# when       who       what, where, why
# --------   ---       ---------------------------------------------------------
# 11/17/15   abirudur  INITIAL VERSION
# 11/17/15   abirudur  ADDED [LOGGING] --> MAIN MODULE 
# 11/17/15   abirudur  ADDED [THREADING] --> LOGGING MODULE
# 11/17/15   abirudur  ADDED [THREAD SUB-CLASSING] --> THREADING MODULE
# 11/18/15   abirudur  ADDED PRINT FORMATED OUTPUT MODULE [FILE-IO]
#===============================================================================
#===============================================================================
#[ DO-NOT DISTRIBUTE WITHOUT PROIR APPROVAL FROM THE Manager/Author  ]
#===============================================================================

import sys
import re
import os
import struct
import time
import array
import string
import bisect
import traceback
import platform
import functools
import threading
import logging

from struct import unpack
from struct import pack
from string import Template

#----------------------------------------------------------------------------
# GLOBAL VARIABLES BEGIN
#----------------------------------------------------------------------------

# ===-- DEBUG & ERROR FLAGS & FORMATING --===
logging.basicConfig(
                    filename="tz_debug_scan_out.txt",
                    filemode="w",
                    level=logging.ERROR,
                    format='(ThreadID:%(thread)d) \n'
                    '\t:Time-stamp   ::%(asctime)s \n'                    
                    '\t:ThreadName   ::%(threadName)-10s \n'
                    '\t:ModuleName   ::%(module)s \n'
                    '\t:FunctionName ::%(funcName)s \n'
                    '\t:LineNo.      ::%(lineno)d \n'
                    '\t:Message      ::%(message)s',
                    )

# ===-- SYNC & ASYNC & LOCKS --===
G_ASYNC_ON = 1
managerThreadLock = threading.Lock()
diagRegionFound_Lock = threading.Lock();

# [Thread ID,Binary Buffer]
G_DIAG_REGION_FOUND  = [] # [DIAG, BACKUP-DIAG REGION]
G_DIAG_REGIONS_LIMIT = 2

# ===-- MANAGER & WORKER THREAD-ID's --===
G_MANAGER_THREAD_BASE_ID = 0x10000000
G_WORKER_THREAD_BASE_ID  = 0x01000000

# ===-- ENABLE_FILE_LOGGING --===
G_ENABLE_FILE_LOGGING = 1

# Sizes
_4KB                            = 0x1000  
_16KB                           = 0x4000  
_24KB                           = 0x6000  
_32KB                           = 0x8000 
_232KB                          = 0x3A000 
_256KB                          = 0x40000 
_512KB                          = 0x80000 
_1MB                            = 0x100000
_512MB                          = 0x20000000 
_1GB                            = 0x40000000             

# TUNING FOR FASTER LOOKUP [MODIFY AS NEEDED]
G_DIAG_REGION_JUMP_OFFSET = 0x6000000 
G_SCAN_RANGE              = 20 * _1MB

# Data type sizes 
H_WORD                         = 2
WORD                           = 4
D_WORD                         = 8
BYTE                           = 1

# Fixed value for B-Family chipsets 
TZBSP_DIAG_NUM_OF_VMID         = 16
TZBSP_DIAG_VMID_DESC_LEN       = 7
TZBSP_DIAG_INT_NUM             = 32
TZBSP_MAX_INT_DESC             = 16

# TZ Diag magic number [ Used for force check !!! ]
TZBSP_DIAG_MAGIC_NUM           = 0x747A6461 

# Possible reasons for a reset 
g_reset_reason_map = \
        [("NO_ERROR_FATAL",0),
         ("NON_SECURE_WDT",1),
         ("SECURE_WDT",2),
         ("AHB_TIMEOUT",3),
         ("RPM_WDOG",4),
         ("RPM_ERR",5),
         ("NOC_ERROR",6),
         ("BIMC_ERROR",7),
         ("FATAL_SMEM",8),
         ("XPU_VIOLATION",9),
         ("SMMU_FAULT",10),
         ("QSEE_ERR",11),
         ("EL3_SP_EL0_SYNCH",12),
         ("EL3_SP_EL0_IRQ",13),
         ("EL3_SP_EL0_FIQ",14),
         ("EL3_SP_EL0_ERR",15),
         ("EL3_SP_EL3_SYNCH",16),
         ("EL3_SP_EL3_IRQ",17),
         ("EL3_SP_EL3_FIQ",18),
         ("EL3_SP_EL3_ERR",19),
         ("EL3_LEL64_SYNCH",20),
         ("EL3_LEL64_IRQ",21),
         ("EL3_LEL64_FIQ",22),
         ("EL3_LEL64_ERR",23),
         ("EL3_LEL32_SYNCH",24),
         ("EL3_LEL32_IRQ",25),
         ("EL3_LEL32_FIQ",26),
         ("EL3_LEL32_ERR",27),
         ("EL1_SP_EL0_SYNCH",28),
         ("EL1_SP_EL0_IRQ",29),
         ("EL1_SP_EL0_FIQ",30),
         ("EL1_SP_EL0_ERR",31),
         ("EL1_SP_EL1_SYNCH",32),
         ("EL1_SP_EL1_IRQ",33),
         ("EL1_SP_EL1_FIQ",34),
         ("EL1_SP_EL1_ERR",35),
         ("EL1_LEL64_SYNCH",36),
         ("EL1_LEL64_IRQ",37),
         ("EL1_LEL64_FIQ",38),
         ("EL1_LEL64_ERR",39),
         ("EL1_LEL32_SYNCH",40),
         ("EL1_LEL32_IRQ",41),
         ("EL1_LEL32_FIQ",42),
         ("EL1_LEL32_ERR",43),
         ("RPM_DRIVER_ERR",44),
         ("RESET_TIMER_EXP",45),
         ("FATAL_ICE_ERR",46),
         ("LMH_DRIVER_ERR",47),
         ("ACCESS_CONTROL",48),
         ("FATAL_CLOCK",49),
		 ("SEC_WDT_TIM_TRIG",51),]

#----------------------------------------------------------------------------
# GLOBAL VARIABLES END
#----------------------------------------------------------------------------

#----------------------------------------------------------------------------
# CLASS DEFINITIONS BEGIN 
#----------------------------------------------------------------------------
class setup_env() :       
    def __init__ (self,                  
                  p_file_list,
                  ) :
        self.l_file_list = p_file_list          
        self.l_manager_thread_list = []           
        self.l_worker_thread_list = []                                  
        self.tzbsp_diag_struct_general_map = []
        self.tzbsp_diag_struct_vmid_map    = []
        self.tzbsp_diag_struct_boot_map    = []
        self.tzbsp_diag_struct_reset_map   = []
        self.tzbsp_diag_struct_int_map     = []
        self.tzbsp_diag_wakeup_info_map    = []
        self.preprocess_meta_info()      
        self.error_state = 0
        
    #-------------------------------------------------------------------------------
    # Preprocessing meta info to use the right files for a given TZBSP instance
    #-------------------------------------------------------------------------------
    def preprocess_meta_info(self) :
      try:      
        if G_ENABLE_FILE_LOGGING is 1:
          if os.path.exists("tz_diag_log.txt"):
            os.remove("tz_diag_log.txt")
        logging.debug("CREATING MANGER THREADS")
        l_cur_dir_processing_done = 0
        l_file_idx = 0
        for l_file in l_file_list:
          #Special cases
          if l_file[0] in '.' and len(l_file[0]) is 1 and l_cur_dir_processing_done is 0:
            for l_root, l_dirnames, l_filenames in os.walk("./"):
              for l_filename in l_filenames:
                l_file_list.append([l_filename,os.path.getsize(l_filename)])             
            l_cur_dir_processing_done = 1            
            continue;

          self.l_manager_thread_list.append(
                manager_thread(l_file_idx + G_MANAGER_THREAD_BASE_ID, # THREAD_ID
                l_file[0], # FILE_NAME                                                  
                l_file[1])) # FILE_SIZE
            
          l_file_idx = l_file_idx + 1;                      
      except:          
           logging.error("Unexpected error: %s" %(str(sys.exc_info())))           

    #-------------------------------------------------------------------------------
    # STARTING POINT FOR ACTUAL WORK [ MANAGER THREAD --> WORKER THREADS ]
    #-------------------------------------------------------------------------------
    def START_PIPELINE(self):
      logging.debug("START PIPLINE WITH MANAGER THREADS")
      for l_manager in self.l_manager_thread_list:
        l_manager.start()

    #-------------------------------------------------------------------------------
    # ENDING POINT FOR RESULT [ WORKER THREAD --> MANAGER THREADS ]
    #-------------------------------------------------------------------------------
    def END_PIPELINE(self):
      logging.debug("END PIPLINE WITH MANAGER THREADS")
      # CLEAN-UP MANAGER THREADS
      for l_manager in self.l_manager_thread_list:
        l_manager.join()

    #-------------------------------------------------------------------------------
    # PRINT OUTPUT [ FINAL STAGE]
    #-------------------------------------------------------------------------------
    def PRINT_OUTPUT(self):
      logging.debug("PRINT FORMATED OUPUT")
      
      # PROCESS BUFFER FOR PRETTY OUTPUT 
      for diag_buff in G_DIAG_REGION_FOUND:
        self.processDiagData(diag_buff[1],diag_buff[2])

    #-------------------------------------------------------------------------------
    # Mapping the data structure that is of interest
    #-------------------------------------------------------------------------------
    def createSymbolMap(self,symbol) :
        if symbol in "g_tzbsp_diag":                      
             self.tzbsp_diag_struct_general_map = \
                     [["MAGIC NUMBER          ",'I',0], #0
                      ["VERSION               ",'I',0], #4
                      ["CPU COUNT             ",'I',0], #8
                      ["VMID INFO OFFSET      ",'I',0], #12
                      ["BOOT INFO OFFSET      ",'I',0], #16
                      ["RESET INFO OFFSET     ",'I',0], #20
                      ["INTERRUPT INFO OFFSET ",'I',0], #24
                      ["RING BUFFER OFFSET    ",'I',0], #28
                      ["RING BUFFER LENGTH    ",'I',0], #32
                      ["WAKEUP INFO OFFSET    ",'I',0]] #36
                     
             self.tzbsp_diag_struct_vmid_map    = \
                     [["VMID",'B'],                                  #40
                      ["DESC","S-" + str(TZBSP_DIAG_VMID_DESC_LEN)]] #167
                     
             self.tzbsp_diag_struct_boot_map    = \
                     [["WARM ENTRY CNT ",'I'], #168
                      ["WARM EXIT CNT  ",'I'], #...
                      ["TERM ENTRY CNT ",'I'], #...
                      ["TERM EXIT CNT  ",'I'], #...                      
                      ["PSCI ENTRY CNT ",'I'], #...
                      ["PSCI EXIT CNT  ",'I'], #...
                      ["WARM JUMP ADDR ",'Q'], #...
                      ["WARM JUMP INST ",'Q']] #324
                               
             self.tzbsp_diag_struct_reset_map   = \
                     [("RESET TYPE ",'I'), #328
                      ("RESET CNT  ",'I')] #356
                     
             self.tzbsp_diag_struct_int_map     = \
                     [["INT INFO ",'H'], #364
                      ["AVAIL    ",'B'], #...
                      ["SPARE    ",'B'], #...
                      ["INT NUM  ",'I'], #...
                      ["INT DESC ","S-" + str(TZBSP_MAX_INT_DESC)], #4
                      ["INT CNT  ",'I']] #2920

             self.tzbsp_diag_wakeup_info_map  = \
                     [["HPPIR  ",'I'], #2924
                      ["AHPPIR ",'I']] #2952
                      

    #-------------------------------------------------------------------------------
    # Process/Decode the diag buff region
    #-------------------------------------------------------------------------------
    def processDiagData(self,p_buffer,p_buffer_size) :        
        try:
            
            # CREATE DIAG PACKING & SYMBOLS LAYOUT MAP
            self.createSymbolMap("g_tzbsp_diag")
            
            # Get the TZ Diag header 
            l_unpack_info = build_unpack_structure_string(self.tzbsp_diag_struct_general_map,1,1)               

            l_interim_data = unpack(l_unpack_info[1],p_buffer[0:l_unpack_info[0]])
            if len(l_interim_data) == 0:         
               error_state = 0x100       
               raise          

            fill_unpacked_data(self.tzbsp_diag_struct_general_map,l_interim_data,2)            

            # Place holder to get the No. of CPU count used for banner display
            self.tzbsp_diag_struct_int_map[5][1] = "I-" + \
                                                   str(self.tzbsp_diag_struct_general_map[2][2])                         
                        
            if self.tzbsp_diag_struct_general_map[0][2] != TZBSP_DIAG_MAGIC_NUM:
               error_state = 0x200
               raise            
            
            # ===-------------------------[HEADER]----------------------------------------START]
            # ==================================================
            #     HEADER
            # ==================================================
            display_side_banner("TZ BSP DIAG INFO BEGIN",40,"=")
            log('\n')
            display_side_banner("GENERAL BASE INFO",15,"=")

            # ===========================================================
            #      CONTENTS
            # ===========================================================
            for general_info_entry in self.tzbsp_diag_struct_general_map:
                log(" %-14s -> [0x%08x]" %(general_info_entry[0],
                                           general_info_entry[2]))
            # ======================
            #      FOOTER
            # ======================
            display_line(38,"=","+") 
            log("\n")   
            # ===-------------------------[HEADER]-----------------------------------------END]
            
            #MOVE HEAD TO NEXT OFFSET
            p_buffer = p_buffer[l_unpack_info[0]:-1] 
            
            l_unpack_info = build_unpack_structure_string(self.tzbsp_diag_struct_vmid_map,
                                                          1,
                                                          TZBSP_DIAG_NUM_OF_VMID)

            l_interim_data = unpack(l_unpack_info[1],p_buffer[0:l_unpack_info[0]])
            if len(l_interim_data) == 0: 
               error_state = 0x300               
               raise           
            
            # ===-------------------------[HEADER]----------------------------------------START]
            # =====================================
            #     HEADER
            # =====================================
            display_inline_banner("VMID MAP",5,"-")            
            display_line(27,"-","+")
            log(" + %-5s | %-5s | %-7s +" %("INDEX",
                                            self.tzbsp_diag_struct_vmid_map[0][0],
                                            self.tzbsp_diag_struct_vmid_map[1][0]))
            display_line(27,"-","+")

            # ==========================================================================
            #      CONTENTS
            # ==========================================================================
            l_loop_index = 0           
            for index in range(0,len(l_interim_data),2):
                l_string = str(l_interim_data[index + 1]).decode('ascii',errors='ignore') 
                l_string = l_string.replace("\0","")               
                match = re.match(r'(\S*)',l_string)
                if match:                   
                    l_string = match.group(1)
                log(" + %-5d | 0x%-3x | %-7s +" %(l_loop_index,
                                                l_interim_data[index],
                                                l_string))
                l_loop_index += 1
            
            # ======================
            #      FOOTER
            # ======================                
            display_line(27,"-","+")
            log("\n")
            # ===-------------------------[HEADER]-----------------------------------------END]

            #MOVE HEAD TO NEXT OFFSET
            p_buffer = p_buffer[l_unpack_info[0]:-1] 
           
            l_unpack_info = build_unpack_structure_string(self.tzbsp_diag_struct_boot_map,
                                                          1,
                                                          self.tzbsp_diag_struct_general_map[2][2])
            
            
            l_interim_data = unpack(l_unpack_info[1],p_buffer[0:l_unpack_info[0]])        

            if len(l_interim_data) == 0:  
               error_state = 0x400
               raise

            # ===-------------------------[HEADER]----------------------------------------START]
            # =========================================
            #     HEADER
            # =========================================
            display_inline_banner("BOOT STATUS",68,"-")
            display_line(158,"-","+")
            log(" + %-4s | %-8s | %-10s | %-10s | %-10s | %-15s | %-15s | %-18s | %-18s +" %("CPU",
                                            self.tzbsp_diag_struct_boot_map[0][0],
                                            self.tzbsp_diag_struct_boot_map[1][0],
                                            self.tzbsp_diag_struct_boot_map[2][0],
                                            self.tzbsp_diag_struct_boot_map[3][0],
                                            self.tzbsp_diag_struct_boot_map[4][0],
                                            self.tzbsp_diag_struct_boot_map[5][0],
                                            self.tzbsp_diag_struct_boot_map[6][0],
                                            self.tzbsp_diag_struct_boot_map[7][0]))

            display_line(158,"-","+")            
            # =========================================================================
            #      CONTENTS
            # =========================================================================
            l_loop_index = 0
            for index in range(0,len(l_interim_data),8):               
                log(" + %-4d | 0x%08x      "
                            "| 0x%08x      "
                            "| 0x%08x      "
                            "| 0x%08x      "
                            "| 0x%08x      "
                            "| 0x%08x      "
                            "| 0x%016x | 0x%016x +"
                    %(l_loop_index,
                      l_interim_data[index],
                      l_interim_data[index + 1],
                      l_interim_data[index + 2],
                      l_interim_data[index + 3],
                      l_interim_data[index + 4],
                      l_interim_data[index + 5],
                      l_interim_data[index + 6],
                      l_interim_data[index + 7]))
                l_loop_index += 1

            # =======================
            #      FOOTER
            # =======================    
            display_line(158,"-","+")   
            log("\n")
            # ===-------------------------[HEADER]-----------------------------------------END]
            
            #MOVE HEAD TO NEXT OFFSET
            p_buffer = p_buffer[l_unpack_info[0]:-1] 

            l_unpack_info = build_unpack_structure_string(self.tzbsp_diag_struct_reset_map,
                                                          1,
                                                          self.tzbsp_diag_struct_general_map[2][2])            
                        
            l_interim_data = unpack(l_unpack_info[1],p_buffer[0:l_unpack_info[0]])    
            if len(l_interim_data) == 0:    
                error_state = 0x400            
                raise
            
            # ===-------------------------[HEADER]----------------------------------------START]
            # ========================================
            #     HEADER
            # ========================================            
            display_inline_banner("RESET INFO",15,"-")
            display_line(50,"-","+")
            log(" + %-8s | %-20s | %-12s +" %("CPU",
                                            self.tzbsp_diag_struct_reset_map[0][0],
                                            self.tzbsp_diag_struct_reset_map[1][0]))                                            
            display_line(50,"-","+")   

            # ====================================================
            #      CONTENTS
            # ====================================================
            l_loop_index = 0
            for index in range(0,len(l_interim_data),2):
                log(" + %-8d | (%02d)[%-14s] | 0x%08x   +"
                    %(l_loop_index,
                      l_interim_data[index],
                      str(g_reset_reason_map[l_interim_data[index]][0]),
                      l_interim_data[index + 1]))
                l_loop_index += 1

            # ======================
            #      FOOTER
            # ======================
            display_line(50,"-","+")
            log("\n")
            # ===-------------------------[HEADER]-----------------------------------------END]

            #MOVE HEAD TO NEXT OFFSET
            p_buffer = p_buffer[l_unpack_info[0]:-1]


            # Get total int count            
            l_interim_data = unpack("<I",p_buffer[0:4])            
            if len(l_interim_data) == 0:
               error_state = 0x500                
               raise

            #MOVE HEAD TO NEXT OFFSET
            p_buffer = p_buffer[4:-1] 
                        
            l_unpack_info = build_unpack_structure_string(self.tzbsp_diag_struct_int_map,
                                                          1,
                                                          l_interim_data[0])    
            
            l_interim_data = unpack(l_unpack_info[1],p_buffer[0:l_unpack_info[0]])   
            if len(l_interim_data) == 0:  
               error_state = 0x600                 
               raise
           
            # ===-------------------------[HEADER]----------------------------------------START]
            # ==============================================
            #     HEADER
            # ==============================================
            display_inline_banner("INTERRUPT INFO",59,"-")
            display_line(145,"-","+")
            
            
            log(" + %-6s | %-10s | %-10s | %-10s | %-10s | %-15s  "\
                    "| IntrCnts => %-10s | %-10s | %-10s | %-10s +"
                    %("INDEX",
                      self.tzbsp_diag_struct_int_map[0][0],
                      self.tzbsp_diag_struct_int_map[1][0],
                      self.tzbsp_diag_struct_int_map[2][0],
                      self.tzbsp_diag_struct_int_map[3][0],
                      self.tzbsp_diag_struct_int_map[4][0],
                      "CPU0",
                      "CPU1",
                      "CPU2",
                      "CPU3",))                

            display_line(145,"-","+")
            
            # ======================================================================
            #      CONTENTS
            # ======================================================================
            l_loop_index = 0     
       
            for index in range(0,len(l_interim_data),9):
                l_string = str(l_interim_data[index + 4]).decode('ascii',errors='ignore')
                l_entry  = ''
                
                for char in l_string:
                    if ord(char) < 127:
                        match = re.match(r'(\w)',char)
                        if match or char == ' ':
                            l_entry += char
                    else:
                        break
                
                log(" + %-6d | 0x%08x | 0x%08x | 0x%08x | 0x%08x | %-16s "\
                    "| IntrCnts => 0x%08x | 0x%08x | 0x%08x | 0x%08x +"
                    %(l_loop_index,
                      l_interim_data[index],
                      l_interim_data[index + 1],
                      l_interim_data[index + 2],
                      l_interim_data[index + 3],
                      l_entry,
                      l_interim_data[index + 5],
                      l_interim_data[index + 6],
                      l_interim_data[index + 7],
                      l_interim_data[index + 8]))
                l_loop_index += 1
                
            # ================================================
            #      FOOTER
            # ================================================
            display_line(145,"-","+")
            log("\n")
            # ===-------------------------[HEADER]-----------------------------------------END]

            #MOVE HEAD TO NEXT OFFSET
            p_buffer = p_buffer[l_unpack_info[0]:-1] 

            l_unpack_info = build_unpack_structure_string(self.tzbsp_diag_wakeup_info_map,
                                                          1,
                                                          self.tzbsp_diag_struct_general_map[2][2])            
                        
            l_interim_data = unpack(l_unpack_info[1],p_buffer[0:l_unpack_info[0]])    
            if len(l_interim_data) == 0:    
                error_state = 0x700            
                raise          
            
            # ===-------------------------[HEADER]----------------------------------------START]
            # ========================================
            #     HEADER
            # ========================================            
            display_inline_banner("WAKEUP INFO",10,"-")
            display_line(41,"-","+")
            log(" + %-8s | %-10s |  %-12s +" %("CPU",
                                            self.tzbsp_diag_wakeup_info_map[0][0],
                                            self.tzbsp_diag_wakeup_info_map[1][0]))                                            
            display_line(41,"-","+")   

            # ====================================================
            #      CONTENTS
            # ====================================================
            l_loop_index = 0
            for index in range(0,len(l_interim_data),2):
                log(" + %-8d | 0x%08x |  0x%08x   +"
                    %(l_loop_index,
                      l_interim_data[index],                      
                      l_interim_data[index + 1]))
                l_loop_index += 1

            # ======================
            #      FOOTER
            # ======================
            display_line(41,"-","+")
            log("\n")
            # ===-------------------------[HEADER]-----------------------------------------END]    

            #MOVE HEAD TO NEXT OFFSET
            p_buffer = p_buffer[l_unpack_info[0]:-1]         
            
            # ===-------------------------[HEADER]----------------------------------------START]
            # =======================================================
            #     HEADER
            # =======================================================
            display_inline_banner("TZBSP LOG [ RING BUFFER ]",25,"=")
            
            l_log_warp   = unpack("<H",p_buffer[0:2])            

            if l_log_warp[0] is not 0:
              log("WRAPPED %d TIMES" %(l_log_warp[0]))

            l_log_offset = unpack("<H",p_buffer[2:4]) # next write position              

            #MOVE HEAD TO NEXT OFFSET
            p_buffer = p_buffer[4:-1]

            # =========================================================================================
            #      CONTENTS
            # =========================================================================================

            l_ring_buffer_len = self.tzbsp_diag_struct_general_map[8][2]   
            l_interim_data = (p_buffer[l_log_offset[0]:l_ring_buffer_len]).decode('ascii',errors='ignore')  
            l_interim_data = l_interim_data.replace("\r\n","\n") # Line De-limiter 
            l_interim_data = l_interim_data.replace("\0","") # Remove NULL to display only log content            
            if len(l_interim_data) !=  0:            
               log(l_interim_data)
            
            if l_log_offset[0] is not 0:
              l_interim_data = (p_buffer[0:l_log_offset[0]]).decode('ascii',errors='ignore')  
              l_interim_data = l_interim_data.replace("\r\n","\n") # Line De-limiter 
              l_interim_data = l_interim_data.replace("\0","") # Remove NULL to display only log content            
              if len(l_interim_data) !=  0:
                 log(l_interim_data) 

            # ===============================================
            #      FOOTER
            # ===============================================
            display_line(100,"=","+")        
            # ===-------------------------[HEADER]-----------------------------------------END]   
                
        except:            
                logging.debug("ERROR STATE:- [0x%x]" %(self.error_state))
                # Tried force check [ Need proper dump to proceed !!! Giving up]               
                print sys.exc_info()         
                sys.exit(0)                
    
    
#-------------------------------------------------------------------------------
# CLASS DEFINITIONS END 
#-------------------------------------------------------------------------------

#-------------------------------------------------------------------------------
# HELPER FUNCTIONS 
#-------------------------------------------------------------------------------

#----------------------------------------------------------------------------
# GENERIC WORKER THREAD DEFINITION
#----------------------------------------------------------------------------
def worker_thread_routine(p_thread_id,p_binary_buf,p_binary_buf_size):  
  logging.debug("[0x%x] [0x%x]" %(p_thread_id,p_binary_buf_size))
  l_bin_offset = 0
  l_binary_buf = p_binary_buf  
  l_binary_buf_size = p_binary_buf_size

  diagRegionFound_Lock.acquire() 

  if len(G_DIAG_REGION_FOUND) < G_DIAG_REGIONS_LIMIT:    
    diagRegionFound_Lock.release()
    while l_bin_offset < l_binary_buf_size:
      l_value = unpack('<L',l_binary_buf[0:4])
      if l_value[0] == TZBSP_DIAG_MAGIC_NUM:
        logging.debug("TZ_DIAG_FOUND")
        diagRegionFound_Lock.acquire()
        G_DIAG_REGION_FOUND.append([p_thread_id,l_binary_buf,len(l_binary_buf)])        
        diagRegionFound_Lock.release()
        break;

      l_bin_offset = l_bin_offset + _4KB  #Time Saver
      if len(l_binary_buf) >= _4KB:
        l_binary_buf = l_binary_buf[_4KB:-1]
  else:
    diagRegionFound_Lock.release()

#----------------------------------------------------------------------------
# CLASS - WORKER THREAD #ASYNC
#----------------------------------------------------------------------------
class worker_thread (threading.Thread):
    def __init__(self,p_thread_id,p_binary_buf,p_binary_buf_size,p_lock):
        threading.Thread.__init__(self)
        self.c_local_thread_id = p_thread_id
        self.c_binary_buf = p_binary_buf
        self.c_binary_buf_size = p_binary_buf_size
        self.c_manager_lock = p_lock
        self.setDaemon(True) # IF MAIN THREAD IS DOWN THEN SAME WITH OTHERS
        
    def run(self):
        if G_ASYNC_ON is not 1:
          self.c_manager_lock.acquire()

        logging.debug("__entry__ Worker Thread-ID[0x%x]" %(self.c_local_thread_id))
        #logging.debug("[%d] [%s] [%d]" %(self.c_local_thread_id,self.c_binary_buf,self.c_binary_buf_size))      

        worker_thread_routine(self.c_local_thread_id,self.c_binary_buf,self.c_binary_buf_size)
        
        logging.debug("__exit__ Worker Thread-ID[0x%x]" %(self.c_local_thread_id))
        if G_ASYNC_ON is not 1:
          self.c_manager_lock.release()        

#----------------------------------------------------------------------------
# GENERIC MANAGER THREAD DEFINITION #ASYNC
#----------------------------------------------------------------------------
def manager_thread_routine(p_thread_id,p_file_name,p_file_size): 
  logging.debug("__entry__ [0x%x] [%s] [0x%x]" %(p_thread_id,p_file_name,p_file_size)) 
  l_worker_thread_list = []
  l_file_start_offset  = 0
  l_file_end_offset    = p_file_size   
  l_workerThreadLock   = threading.Lock()
  l_garbage_collect    = 1  
  l_file_handle        = open(p_file_name, "rb") 

  if(p_file_size > _512MB):    
    l_file_start_offset = G_DIAG_REGION_JUMP_OFFSET    
    l_file_handle.seek(l_file_start_offset)
    l_file_end_offset = l_file_start_offset + G_SCAN_RANGE    

  while l_file_start_offset < l_file_end_offset:    
    l_file_handle.seek(l_file_start_offset)
    l_binary_buf = l_file_handle.read(_1MB)     

    # Using SYNC scan (If RAID disk then we can use ASYNC) // General case
    l_worker_thread_list.append(
                  worker_thread(p_thread_id + G_WORKER_THREAD_BASE_ID, # THREAD_ID
                  l_binary_buf, # BINARY_BUFFER
                  len(l_binary_buf), #BINARY_BUFFER_SIZE                                                  
                  l_workerThreadLock)) # MANAGER_LOCK

    l_file_start_offset = l_file_start_offset + _1MB

    l_worker_thread_list[-1].start()

    # CLEAN-UP EVERY 1GB // To scan the buffer from RAM 
    if l_file_start_offset >= (_1GB * l_garbage_collect):
      for l_worker_thread in l_worker_thread_list:
        l_worker_thread.join() 
      l_garbage_collect = l_garbage_collect + 1

  # CLEAN-UP WORKER THREADS
  for l_worker_thread in l_worker_thread_list:
    l_worker_thread.join()   

  l_file_handle.close() 

  logging.debug("__exit__ [0x%x] [%s] [0x%x]" %(p_thread_id,p_file_name,p_file_size)) 

   

#----------------------------------------------------------------------------
# CLASS - MANAGER THREAD #ASYNC
#----------------------------------------------------------------------------
class manager_thread (threading.Thread):
    def __init__(self,p_thread_id,p_file_name,p_file_size):
        threading.Thread.__init__(self)
        self.c_local_thread_id = p_thread_id
        self.c_file_name = p_file_name
        self.c_file_size = p_file_size
        self.setDaemon(True) # IF MAIN THREAD IS DOWN THEN SAME WITH OTHERS

        
    def run(self):
        if G_ASYNC_ON is not 1:
          managerThreadLock.acquire()

        logging.debug("__entry__ Manager Thread-ID[0x%x]" %(self.c_local_thread_id))
        logging.debug("[0x%x] [%s] [0x%x]" %(self.c_local_thread_id,self.c_file_name,self.c_file_size))        
        manager_thread_routine(self.c_local_thread_id,self.c_file_name,self.c_file_size)
        
        logging.debug("__exit__ Manager Thread-ID[0x%x]" %(self.c_local_thread_id))
        if G_ASYNC_ON is not 1:
          managerThreadLock.release()

#-------------------------------------------------------------------------------
# Logging to io streams 
#-------------------------------------------------------------------------------
def log(p_log):
    try:         
          if G_ENABLE_FILE_LOGGING is 1:
            l_cur_stdout = sys.stdout            
            sys.stdout = open("tz_diag_log.txt","a+")            
            print(p_log)
            sys.stdout = l_cur_stdout           
          print(p_log) #REGULAR CONSOLE IO            
    except:
        print("Cannot log to output stream")

#-------------------------------------------------------------------------------
# Convert to string 
#-------------------------------------------------------------------------------
def get_string(p_value):
    try:
        return str(p_value)
    except:
        log("Cannot convert to string")

#-------------------------------------------------------------------------------
# Convert to hex 
#-------------------------------------------------------------------------------
def get_hex(p_value):
    try:
        return hex(p_value)
    except:
        log("Cannot convert to hex")

#-------------------------------------------------------------------------------
# Display line
#-------------------------------------------------------------------------------
def display_line(p_len,p_decorator,p_limiter):
    l_line_str = ""

    if p_limiter != " ":
        p_len -= 2
                
    for index in range(0,p_len):
        l_line_str += p_decorator

    if p_limiter != " ":
        l_line_str = " " + p_limiter + l_line_str + p_limiter
    else:
        l_line_str = " " + l_line_str

    log(l_line_str)

#-------------------------------------------------------------------------------
# Display inline banner
#-------------------------------------------------------------------------------
def display_inline_banner(p_inline_banner,p_extra,p_decorator):
    l_banner_str = " "
    
    for index in range(0,len(p_inline_banner)/2 + p_extra):
        l_banner_str  += p_decorator
        
    l_banner_str += p_inline_banner
    
    for index in range(0,len(p_inline_banner)/2 + p_extra):
        l_banner_str  += p_decorator
        
    log(l_banner_str)
    return len(l_banner_str)

#-------------------------------------------------------------------------------
# Display banner line
#-------------------------------------------------------------------------------
def display_banner_line(p_side_banner,p_repeat,p_extra,p_decorator):
    l_banner_str = " "
    
    for index in range(0,len(p_side_banner)+len(" [  ] ")+p_extra):
        l_banner_str  += p_decorator
    for index in range(0,p_repeat):
        log(l_banner_str)
        
    return len(l_banner_str)

#-------------------------------------------------------------------------------
# Display side banner 
#-------------------------------------------------------------------------------
def display_side_banner(p_side_banner,p_extra,p_decorator):
    l_display_banner = ' '
    l_align_center = display_banner_line(p_side_banner,1,p_extra,p_decorator)
    l_align_center = l_align_center/2 - len(p_side_banner)/2 - 1       
    for index in range(0,l_align_center):
        l_display_banner += ' '

    l_display_banner += p_side_banner    
    log((" %s " %(l_display_banner)))
    display_banner_line(p_side_banner,1,p_extra,p_decorator)


#-------------------------------------------------------------------------------
# Build unpack string to get bytes from file with specified data types 
#-------------------------------------------------------------------------------
def build_unpack_structure_string(p_struct,p_type_pos,p_multiplier):
    l_little_end = "<" # Used to specify the target as little endian
    l_unpack_str = "" 
    l_struct_len = 0
    
    for l_var in p_struct:        
        if l_var[p_type_pos] == 'I': #4
            l_unpack_str += 'I'
            l_struct_len += WORD  
        elif 'I' in l_var[p_type_pos]: #4(*)
            match = re.match(r'I-(\d*)',l_var[p_type_pos])
            if match:
                byte_count = int(match.group(1)) * WORD
                l_struct_len += byte_count
                for index in range(0,int(match.group(1))):
                    l_unpack_str += 'I'
            else:
                return [0,0]
        elif l_var[p_type_pos] == 'B': #1
            l_unpack_str += 'B'
            l_struct_len += BYTE
        elif l_var[p_type_pos] == 'H': #2
            l_unpack_str += 'H'
            l_struct_len += H_WORD
        elif l_var[p_type_pos] == 'Q': #8
            l_unpack_str += 'Q'
            l_struct_len += D_WORD
        elif 'Q' in l_var[p_type_pos]: #8(*)
            match = re.match(r'Q-(\d*)',l_var[p_type_pos])
            if match:
                byte_count = int(match.group(1)) * D_WORD
                l_struct_len += byte_count
                for index in range(0,int(match.group(1))):
                    l_unpack_str += 'Q'
            else:
                return [0,0]
        elif 'S' in l_var[p_type_pos]: #1(*)            
            match = re.match(r'S-(\d*)',l_var[p_type_pos])
            if match:
                byte_count = match.group(1)
                l_struct_len += int(byte_count)                
                l_unpack_str += str(byte_count) + 's'
            else:
                return [0,0]
        else:             
             return [0,0]
    
    if p_multiplier > 1:
        l_tmp_unpack_repeater = l_unpack_str
        for multipler in range(0,p_multiplier-1):  
            l_unpack_str += l_tmp_unpack_repeater
            
        l_struct_len  = l_struct_len * p_multiplier

    l_unpack_str = l_little_end  + l_unpack_str 
    return [l_struct_len,l_unpack_str]       
            

#-------------------------------------------------------------------------------
# Display script usable arguments
#-------------------------------------------------------------------------------
def display_help():
   print " ---------------------------------------------------------------------"
   print(' Usage: python tz_diag_parser.py <options> [args]                  \n'               
         '        *[arg]+  --- OCIMEM/DDR/PIMEM                              \n' 
         '         .       --- Scan all files in current dir                 \n'      
         '      <--help>   --- Displays tool usage commands/options          \n'
         ' NOTE: <options> with a * are mandatory                            \n'
         ' Supported chipsets::  [ MSM8996 ]                                 \n'         
         ' Example:-                                                         \n'
         ' --> tz_diag_parser.py pimem.bin ocimem.bin ddr0.bin ddr1.bin      \n'
         ' --> tz_diag_parser.py .                                           \n')         
   print " --------------------------------------------------------------------"
   sys.exit()


#-------------------------------------------------------------------------------
# Fill unpacked structure at the specified offset of the list passed in
#-------------------------------------------------------------------------------
def fill_unpacked_data(p_container,p_unpacked_data,p_index):    
    l_unpack_index = 0
    for entry in p_container:        
        entry[p_index] = p_unpacked_data[l_unpack_index]
        l_unpack_index += 1
        
#-------------------------------------------------------------------------------
# Check command line length
#-------------------------------------------------------------------------------
def check_cmd_len_in_range(count,next_index):
    if next_index <= count:        
        return True
    else:        
        return False

#-------------------------------------------------------------------------------
# Get next index of the cmd arguments
#-------------------------------------------------------------------------------
def get_next_index(count,cur_index):
    cur_index = cur_index + 1
    if check_cmd_len_in_range(count,cur_index) is True:        
        return cur_index
    else:       
        return -1       
#-------------------------------------------------------------------------------
# Preprocessing and error handling of command line arguments
#-------------------------------------------------------------------------------
def validate_input():   
  l_input_file_list = []         
   
  arguments = sys.argv[1:]
  arg_count = len(arguments)

  if arg_count == 0:
    display_side_banner("Reason :: Please enter an option to process",6,"-")
    display_help()      
   
  # Command line book keeping
  l_cur_index = 0
  l_tmp_index = 0
  l_validation_status = 0
  l_end_of_args = -1
  l_cur_interim_file_size = 0
  l_cur_interim_filename = ""   
  
  l_cur_index = get_next_index(arg_count,l_cur_index) 
   
  while l_cur_index != l_end_of_args:

    if sys.argv[l_cur_index] in '--help':
      display_help()  

    l_interim_filename = sys.argv[l_cur_index]
    
    if not os.path.exists(l_interim_filename):      
      logging.debug("[FILE DOES NOT EXISTS] !!! ") 
      l_validation_status = 1     
      break              

    l_cur_interim_file_size = os.path.getsize(l_interim_filename) # [FILE,SIZE_IN_BYTES]

    if '..' in sys.argv[l_cur_index] and int(os.path.getsize(sys.argv[l_cur_index])) is 0:
      logging.debug("[FILE PATH NOT VALID] !!! ") 
      l_validation_status = 1     
      break          

    l_input_file_list.append([l_interim_filename,l_cur_interim_file_size])      

    l_cur_index = get_next_index(arg_count,l_cur_index)

  if l_validation_status is 1:
    print ' Syntax error at :: <' + sys.argv[l_cur_index] + '>'
    display_help()
     
  if len(l_input_file_list) is 0:
      # We cannot proceed forward without mandatory data
      display_side_banner("Reason :: Please enter mandatory fields",1,"-")      
      display_help()
  
  return l_input_file_list


#-------------------------------------------------------------------------------
# Preprocessing and error handling of command line arguments
#-------------------------------------------------------------------------------
def perform_force_check(p_tzbsp_handle):            
    
    result = p_tzbsp_handle.forceCheckTZDiagMG()
    if result == 0:
        display_side_banner("No TZ BSP Diag Info Present !!",6,"-")        
        tzbsp_enable_memory_dump();
        sys.exit()
    else:
        return result

#----------------------------------------------------------------------------
# MAIN SCRIPT BEGIN
#----------------------------------------------------------------------------

# START TIME
l_processing_start = time.time()

# Validate Input and return file list
l_file_list = validate_input()

# Initialization pass in the meta info
l_handle = setup_env(l_file_list)

# |-- START PIPELINE 
l_handle.START_PIPELINE() 

# --> END PIPELINE --> 
l_handle.END_PIPELINE()

# --> FORMAT OUTPUT --|
l_handle.PRINT_OUTPUT()

# END TIME
l_processing_end = time.time()

log("==-------------------------------------------==")
log("| Total Processing Time :: %g sec              "  %(l_processing_end - l_processing_start))
log("==-------------------------------------------==")

#----------------------------------------------------------------------------
# MAIN SCRIPT END 
#----------------------------------------------------------------------------

