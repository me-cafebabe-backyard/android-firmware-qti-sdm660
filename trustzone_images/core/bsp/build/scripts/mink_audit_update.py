# ----------------------------------------------------------------------------
# Copyright (c) 2016 by Qualcomm Technologies, Incorporated.
# All Rights Reserved.
# QUALCOMM Proprietary/GTDR
# ----------------------------------------------------------------------------

"""---------
    USAGE:
        Approve/Add a specific file, or space-separated list of files:
            mink_audit_update.py -a [FILE_PATH]

        Remove all hashes of specific file(s):
        	mink_audit_update.py -r [FILE_PATH]

        Find and Update all relevant files / generate all hashes for config file:
            mink_audit_update.py -u

        Use a different config file for read/update:
            mink_audit_update.py -c [FILE_PATH]

---------"""

from mink_audit_cfgrw import ConfigReadWriter
import os
import argparse

parser = argparse.ArgumentParser(description='Compare hashes of critical files to mark modifications')
parser.add_argument('-c', '--config', dest="config_file_name",
                    help='Path of config file containing filename:hash mappings.', default='mink_audit.cfg',
                    metavar="FILE")
parser.add_argument('-u', '--updateall', dest="update_all", help='Search for interfaces and add all to config file.',
                    action='store_true', default=False)
parser.add_argument('-a', '--add', dest="add_file_name",
                    help='Path of file(s) to add to future checks. Add a file and it\'s hash to the config file. If the file is already listed, the hash will be updated.',
                    nargs='+', metavar="FILE")  # , default = os.getcwd())           #optional
parser.add_argument('-r', '--remove', dest="remove_file_name",
                    help='Path of file(s) to remove from future checks. Remove a file and it\'s hash from the config file.',
                    nargs='+', metavar="FILE")  # , default = os.getcwd())           #optional

args = parser.parse_args()
cr = ConfigReadWriter(args.config_file_name, os.path.join(os.getcwd(), '..', '..', '..', '..'))

if args.add_file_name:
    cr.add_interface(args.add_file_name)
elif args.remove_file_name:
    cr.remove_interface(args.remove_file_name)
elif args.update_all:
    cr.find_and_update_interfaces()
else:
    cr.read_and_dispatch()
