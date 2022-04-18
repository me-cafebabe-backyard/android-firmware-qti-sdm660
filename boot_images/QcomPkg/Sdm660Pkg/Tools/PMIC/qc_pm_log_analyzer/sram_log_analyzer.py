#!/usr/bin/python
#SRAM command line reader

# ===== Py 2/3 Compatibility Layer =====
from __future__ import absolute_import, division, print_function
from future.builtins import (ascii, bytes, chr, dict, filter, hex, input,
                             int, map, next, oct, open, pow, range, round,
                             str, super, zip)
from future.builtins.disabled import *
# ======================================
from framework.log_analyzer_config import *
from framework.log_data_set import *
from framework.log_plot import *

import sys
import argparse
from framework.formatFgSramDump import *
from os import getcwd

#print "Number of arguments:", len(sys.argv)
#print "Argument List:", str(sys.argv)

#Main Function
def main(args):
    
    print('\nsram_log_analyzer: Started with the following arguments:\n')
    
    for argNum, argument in enumerate(vars(args), start = 1):
        print("  {}. {}: {}".format(argNum, argument, getattr(args, argument)))
    
    analyzer_config = LogAnalyzerConfig()
    
    config = getcwd() + '\\sram_log_analyzer\\' + args.config + '\\config_8998sram.xml' 
    analyzer_config.load_config(config)
    
    from framework.log_parser_8998sram import LogParser_8998Sram
    encoding = getcwd() + '\\sram_log_analyzer\\' + args.config + '\\EncMapTable.csv'    
    sram_parser = None
    
    print('\nsram_log_analyzer: Start parsing input log file')
    
    if (args.type.lower() == 'hex'):
        sram_parser = LogParser_8998Sram(encoding, args.dump)
    elif (args.type.lower() == 'log'):
        orientation = args.orientation
        outfile = getcwd() + '\\parsed_dump.txt'
        if (orientation.lower() == 'ahlos'):
            parseHlosLog(args.dump, outfile)
        elif (orientation.lower() == 'dhlos'):
            reverseLines(args.dump, tempFileName)
            parseHlosLog(tempFileName, outfile)
        elif (orientation.lower() == 'uefi'):
            parseUefiLog(args.dump, outfile)
        else:
            print ('Incorrect orientation. Please select a correct option.')
        sram_parser = LogParser_8998Sram(encoding, outfile)
    else:
        print ('Incorrect dump file type. Please select a correct option.')
        
    print('sram_log_analyzer: Done parsing')
    print('sram_log_analyzer: Creating data csv file')
    
    sram_parser.to_csv_file(args.plotData)
    data_set = LogGroupSet(args.plotData)
    
    print('sram_log_analyzer: Done creating csv file')
    print('sram_log_analyzer: Start plotting')
    
    plot = LogPlot(analyzer_config, data_set)
    plot.plot_to_xlsx(args.plot)
    
    print ("\nPlot saved to " + getcwd())


# Program entry point
if __name__ == '__main__':
    arg_parser = argparse.ArgumentParser(description='SRAM Log Analyzer:\n'
                                                      'This log analyzer takes in log data (txt/XML), log data format (string),\n' 
                                                      'and configuration folder name (string) in order to organize the data and\n' 
                                                      'plot graphs in an excel worksheet.\n\n'
                                                      'Type options: \'hex\'\n'
                                                      '              \'log\'\n'
                                                      '\'hex\' is raw data that has been parsed and formatted correctly by this program.\n'
                                                      '\'log\' is for raw data taken directly from the device.\n\n'
                                                      'Orientation options: \'AHLOS\' - Ascending \n'
                                                      '                     \'DHLOS\' - Descending\n'
                                                      '                     \'UEFI\'  - UEFI log\n\n'

                                                      'The configuration folder must be listed under the main \'sram_log_analyzer\' folder.\n\n'

                                                      'Input:\n'
                                                      '  Log Data (Required)\n'
                                                      '  Log file format (Optional) - default \'hex\'\n'
                                                      '  Raw log file orientation (Optional)\n'
                                                      '  Configuration folder name (Optional) - default \'8998\'\n'
                                                      'Output:\n'
                                                      '  Excel Data file (Optional) - default path \'current directory\'\n'
                                                      '  Excel Graph file (Optional) - default path \'current directory\'\n\n'

                                                      'Example:\n'
                                                      '    python sram_log_analyzer.py dump.txt -t type -o orientation -c MSM_Number -pd data.csv -p plot.xlsx\n',
                                     formatter_class=argparse.RawTextHelpFormatter)

    arg_parser.add_argument("dump", help="Path to the dump file", type=str)
    arg_parser.add_argument("-t", "--type", help="Specify if the dump file format. \n(default: %(default)s)", default='hex', type=str)
    arg_parser.add_argument("-o", "--orientation", help="The orientation of the raw dump file.", type=str)
    arg_parser.add_argument("-c", "--config", help="Folder name for configuration files \n(default: %(default)s)", default='8998', type=str)
    arg_parser.add_argument("-pd", "--plotData", help="Path to generate the CSV file \n(default: %(default)s)", default=getcwd() + '\data.csv', type=str)
    arg_parser.add_argument("-p", "--plot", help="Path to generate the excel file \n(default: %(default)s)", default=getcwd() + '\plot.xlsx', type=str)
    args = arg_parser.parse_args()
    main(args)
