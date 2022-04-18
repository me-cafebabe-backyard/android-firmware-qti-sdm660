#!/usr/bin/python
'''
 Copyright (c) 2015
 Qualcomm Technologies Incorporated.
 All Rights Reserved.
 Qualcomm Confidential and Proprietary

Script to track usage of the T32 jtag flashign took.

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Tools/storage/UFS/t32_data.py#1 $
$DateTime: 2016/05/23 02:27:48 $
$Author: pwbldsvc $

when        who       what, where, why
----------  --------  -----------------------------------------------------
2016-04-02  wkimberl  Create.

'''

import data_collector
import time

if __name__ == "__main__":
    script_version = "1.0.1"
    dc = data_collector.Data_Colector (application = 'T32_jtagprogrammer', app_version = script_version, screen = 'SDM660', disable = False)
    dc.log_use()

