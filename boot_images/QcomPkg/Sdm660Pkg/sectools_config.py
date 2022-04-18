#!/usr/bin/env python

#============================================================================
#
# @file sectools_config.py
#
# Copyright 2016 by Qualcomm Technologies, Incorporated.
#                 All Rights Reserved.
#               QUALCOMM Proprietary/GTDR
#
#----------------------------------------------------------------------------
#
#                          EDIT HISTORY FOR MODULE
#
# This section contains comments describing changes made to the module.
# Notice that changes are listed in reverse chronological order.
#
# when       who     what, where, why
# --------   ---     -----------------------------------------------------------
# 04/18/16   et      Initial release

def get_config():
  config = {'soc_hw_version' :'0x30060000',
            'soc_vers'       :'0x3007',
            'config_xml'     :'secimagev2.xml'}
  return config