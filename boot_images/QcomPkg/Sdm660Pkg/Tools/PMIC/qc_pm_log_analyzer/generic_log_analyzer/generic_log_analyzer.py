#!/usr/bin/python
# ===== Py 2/3 Compatibility Layer =====
from __future__ import absolute_import, division, print_function
from future.builtins import (ascii, bytes, chr, dict, filter, hex, input,
                             int, map, next, oct, open, pow, range, round,
                             str, super, zip)
from future.builtins.disabled import *
# ======================================
from framework.log_analyzer_config import *
from framework.log_data_set import *
from framework.log_parser import *
from framework.log_plot import *
from generic_log_analyzer.gui.log_analyzer_gui_main import LogAnalyzerGuiMain
import sys
import argparse
from argparse import RawTextHelpFormatter


def main():
    """
    Launcher of the Generic Log Analyzer.

    """
    arg_parser = argparse.ArgumentParser(description='Generic Log Analyzer.\n'
                                                     'This generic log analyzer takes in configure XML file and '
                                                     'log/data file to plot specified graphs.\n\n'
                                                     'Examples:\n'
                                                     '  Text log parsing & plotting (without data CSV output):\n'
                                                     '      python log_analyzer.py --text -c config.xml -l log.txt -p plot.xlsx\n'
                                                     '  Text log parsing & plotting (with CSV output):\n'
                                                     '      python log_analyzer.py --text -c config.xml -l log.txt -d data.csv -p plot.xlsx\n'
                                                     '  Log plotting from data CSV:\n'
                                                     '      python log_analyzer.py --csv -c config.xml -d data.csv -p plot.xlsx\n'
                                                     '  SRAM log parsing & plotting:\n'
                                                     '      python log_analyzer.py --sram -c config.xml -e enc.csv -l dump.txt -d data.csv -p plot.xlsx\n',
                                         formatter_class=RawTextHelpFormatter)

    arg_parser.add_argument("--text", help="Operation to parse from text log", action="store_true")
    arg_parser.add_argument("--csv", help="Operation to parse from CSV data", action="store_true")
    arg_parser.add_argument("--sram", help="Operation to parse SRAM dump", action="store_true")
    arg_parser.add_argument("-c", "--config", help="Path to the configuration XML", type=str)
    arg_parser.add_argument("-l", "--log", help="Path to the log file", type=str)
    arg_parser.add_argument("-d", "--data", help="CSV data file to load/store", type=str)
    arg_parser.add_argument("-p", "--plot", help="Path to the plot output", type=str)
    arg_parser.add_argument("-e", "--encoding", help="Register encoding map path for SRAM dump", type=str)
    args = arg_parser.parse_args()

    analyzer_config = LogAnalyzerConfig()
    parser = None
    data_set = None
    plot = None

    # Text option
    if args.text:
        if args.config is not None and args.log is not None and args.plot is not None:
            analyzer_config.load_config(args.config)
            parser = LogParser(analyzer_config)
            data_set = parser.parse_file(args.log)
            # Output data CSV if data path is specified
            if args.data is not None:
                data_set.to_csv_file(args.data)
            plot = LogPlot(analyzer_config, data_set)
            plot.plot_to_xlsx(args.plot)
        else:
            print("Insufficient arguments.")
            exit(1)

    # CSV option
    elif args.csv:
        if args.config is not None and args.data is not None and args.plot is not None:
            analyzer_config.load_config(args.config)
            data_set = LogGroupSet(args.data)
            plot = LogPlot(analyzer_config, data_set)
            plot.plot_to_xlsx(args.plot)
        else:
            print("Insufficient arguments.")
            exit(1)

    # SRAM dump option
    elif args.sram:
        if args.config is not None and \
                        args.log is not None and \
                        args.plot is not None and \
                        args.encoding is not None and \
                        args.data is not None:
            from log_parser_8998sram import LogParser_8998Sram
            sram_parser = LogParser_8998Sram(args.encoding, args.log)
            sram_parser.to_csv_file(args.data)
            data_set = LogGroupSet(args.data)
            plot = LogPlot(analyzer_config, data_set)
            plot.plot_to_xlsx(args.plot)
        else:
            print("Insufficient arguments.")
            exit(1)

    # Launch GUI
    else:
        # Instantiate GUI
        gui_main = LogAnalyzerGuiMain()
        gui_main.start()


# Program entry point
if __name__ == '__main__':
    main()
