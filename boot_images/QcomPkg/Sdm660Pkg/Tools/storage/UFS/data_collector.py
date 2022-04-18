#!/usr/bin/python
'''
 Copyright (c) 2015
 Qualcomm Technologies Incorporated.
 All Rights Reserved.
 Qualcomm Confidential and Proprietary

Script to track usage of the tools with different analytics

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Tools/storage/UFS/data_collector.py#1 $
$DateTime: 2016/05/23 02:27:48 $
$Author: pwbldsvc $

when        who       what, where, why
----------  --------  -----------------------------------------------------
2015-10-23  wkimberl  Create.

'''

import socket
import getpass
import random
import string
import hashlib
import urllib2
import uuid
import logging
import data_collector_pw


class Data_Colector:
    ''' Collects usage data and logs it into google analytics '''
    def __init__ (self, application, app_version, screen, disable = False):
        ''' '''
        self.disable = disable
        self.collector = []
        if disable == True:
            return

        piwik = data_collector_pw.Data_Collector(application, app_version, screen)
        self.collector.append(piwik)

    def log_use(self):
        ''' Log that the tools was called and is beeing used.'''
        for collect in self.collector:
            collect.log_use()

    def total_write(self, byte_count):
        ''' Log the number of bytes written by the tool. '''
        for collect in self.collector:
            collect.total_write(byte_count)

    def total_read(self, byte_count):
        ''' Log the number of bytes read by the tool. '''
        for collect in self.collector:
            collect.total_read(byte_count)

    def total_erase(self, byte_count):
        ''' Log the number of bytes erased by the tool. '''
        for collect in self.collector:
            collect.total_erase(byte_count)

    def total_time(self, time_seconds):
        ''' Log the total time spent in flashing. '''
        for collect in self.collector:
            collect.total_time(time_seconds)




