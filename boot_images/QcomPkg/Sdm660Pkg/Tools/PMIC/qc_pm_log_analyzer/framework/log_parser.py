#!/usr/bin/python
# ===== Py 2/3 Compatibility Layer =====
from __future__ import absolute_import, division, print_function
from future.builtins import (ascii, bytes, chr, dict, filter, hex, input,
                             int, map, next, oct, open, pow, range, round,
                             str, super, zip)
from future.builtins.disabled import *
# ======================================
import re
from time import strftime, gmtime
from datetime import datetime
from framework.log_data_set import LogGroupSet

def _convRawSecsToFormatedDateTime(rawSecs, defTimeFormat = '%H:%M:%S'):
    """ Convert raw time (int, 1, 2 ... 93 ...) to datetime format (obj) """
    #Convert raw time (assumed to be in seconds) to formated time string. 
    rawToFormatedTimeStr = gmtime(int(rawSecs))
    #Convert formated time string to formated date string. 
    timeToDateFormatStr = strftime(defTimeFormat, rawToFormatedTimeStr)
    #Convert formated date string to formated datetime object. Note: used extra local variables 
    # to make the code easier to read.    
    return datetime.strptime(timeToDateFormatStr, defTimeFormat) 

class LogParser:
    """
    Generic text log parser.
    """
    _timestamp_pattern = None

    def __init__(self, analyzer_config):
        """
        Constructor. Loads parsing configuration.

        :param analyzer_config: LogAnalyzerConfig object
        """
        self.config = None
        self.data_set = None
        self.set_config(analyzer_config)
        self._log_start_time = None

    def set_config(self, analyzer_config):
        """
        Imports log parsing configuration.

        :param analyzer_config: LogAnalyzerConfig object
        """
        self.config = analyzer_config.export_parse_config()
        self._timestamp_pattern = re.compile(self.config.time_regex)
        self.data_set = LogGroupSet(analyzer_config)

    def _parse_time(self, line):
        """
        Parse the formatted timestamp in the log line to a datetime object.

        Timestamp format: MM/DD/YYYY-HH:MM:SS.mmm

        :param line: Log line
        :return: A datetime object contains the timestamp
        """
        re_match = re.search(self._timestamp_pattern, line)
        if re_match is not None:
            if self.config.time_format != '':
                return datetime.strptime(re_match.group(), self.config.time_format) - self._log_start_time
            else:
                # Convert raw time to datatime
                return _convRawSecsToFormatedDateTime(re_match.group()) - self._log_start_time                            
        else:
            raise Exception('LogParser: parse_time: No formatted timestamp matched.')

    def _parse_params(self, line):
        """
        Parse the parameters contains in the log line.

        :param line: Log line
        :return: (Label, Parameter dictionary) when the content of line matches one of the configuration entry; (None, None) on mismatch.
        """
        param_dict = {}
        for entry in self.config.entry_list:
            if re.search(entry.key, line) is not None:  # matches key in the current entry
                for param in entry.param_list:  # in param list
                    delim_esc = re.escape(entry.delim)
                    param_match = re.search(param.name + r'\s?' + delim_esc + r'\s?-?(0x|0X)?[0-9]+(\.[0-9]+)?', line)
                    if param_match is not None:
                        param_split = param_match.group().replace(' ', '').split(entry.delim)
                        param_dict.update({param.name: (float(param_split[-1]), param.unit)})
                    else:
                        raise Exception('LogParser: parse_params: Mismatch on required parameter.')
                return entry.label, param_dict
        return None, None

    def _parse_line(self, line):
        """
        Parse the log line into a list.

        List format: [Label, Timestamp in datetime.timedelta, {Parameter-Value Dictionary}]

        :param line: Log line
        :return: Parsed data as a list
        """
        label, param_val_dict = self._parse_params(line)
        if label is None or param_val_dict is None:
            return None
        timestamp = self._parse_time(line)
        return label, timestamp, param_val_dict

    def parse_file(self, path):
        """
        Parse a log file into a LogGroupSet object.

        :param path: Path to the log file
        :return: A LocDataSet object
        """
        self._log_start_time = None
        with open(path, 'r') as log_file:
            for line_num, line in enumerate(log_file, 1):              
                # Continue to check until you find the first line with a valid time stamp.
                if self._log_start_time is None:
                    re_match = re.search(self._timestamp_pattern, line)                                        
                    if re_match is not None:
                        if self.config.time_format != '':
                            self._log_start_time = datetime.strptime(re_match.group(), self.config.time_format)
                        else:
                            self._log_start_time = _convRawSecsToFormatedDateTime(re_match.group())                                                   
                parsed_line = self._parse_line(line)

                if parsed_line is not None:
                    self.data_set.add_data(parsed_line[0], line_num, parsed_line[1], parsed_line[2])
        return self.data_set
