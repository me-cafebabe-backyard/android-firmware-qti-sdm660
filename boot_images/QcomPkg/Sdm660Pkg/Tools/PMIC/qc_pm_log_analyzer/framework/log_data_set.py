#!/usr/bin/python
# ===== Py 2/3 Compatibility Layer =====
from __future__ import absolute_import, division, print_function
from future.builtins import (ascii, bytes, chr, dict, filter, hex, input,
                             int, map, next, oct, open, pow, range, round,
                             str, super, zip)
from future.builtins.disabled import *
# ======================================
from datetime import datetime
from datetime import timedelta
from collections import namedtuple
from framework.log_analyzer_config import PlotDataSeries, LogAnalyzerConfig, ParseParam

DataGroupEntry = namedtuple('DataGroupEntry', ['label', 'line_num', 'time_delta', 'param_val_dict'])


class LogDataGroup:
    """
    A group of log data which have the same keyword, label and parameter list (aka. parsing configuration entry)
    """

    _DataRecord = namedtuple('DataRecord', ['line_num', 'time_delta', 'param_val_list'])

    def __init__(self, label, param_unit_tuple_list):
        """
        Constructor.

        :param label: Label of a parsing configuration entry
        :param param_unit_tuple_list: Parameter list (format: [(Parameter Name, Unit), ...]) of a parsing configuration entry
        """
        self.label = label
        self.param_name_list = []
        self.param_unit_list = []
        for param in param_unit_tuple_list:
            self.param_name_list.append(param[0])
            self.param_unit_list.append(param[1])
        self._data_set = []
        # data set format: [(line_num, timestamp, [param1_val, ...]), ...]

    def add_data(self, line_num, time_delta, param_val_dict):
        """
        Add a data point to the log data group.

        :param line_num: Line number of the data in the log file
        :param time_delta: Timestamp of the log line as a timedelta object
        :param param_val_dict: Parameter_name-(value, unit) dictionary of the parsed log line
        """
        # Convert param-val dict to a value list which matches the order of the param_name_list
        param_val_list = []
        for param in self.param_name_list:
            if param in param_val_dict:
                param_val_list.append(param_val_dict[param][0])
            else:
                param_val_list.append(None)
        self._data_set.append(self._DataRecord(line_num, time_delta, param_val_list))

    def get_unit(self, param_name):
        """
        Get the unit of a parameter in the current LogDataGroup.

        :param param_name: parameter name
        :return: a string representation of the unit for the specified parameter
        """
        for i, param in enumerate(self.param_name_list):
            if param == param_name:
                return self.param_unit_list[i]
        raise Exception('LogDataGroup: ' + self.label + ' ' + param_name + 'is not exist in the data set.')

    def export(self, param_name=None):
        """
        Convert current log data group into a DataGroupEntry named tuple list format.

        :return: list of DataGroupEntry named tuple
        """
        log_list = []
        for record in self._data_set:
            param_dict = {}
            for i, curr_param_name in enumerate(self.param_name_list):
                if (param_name is None) or (curr_param_name == param_name):
                    param_dict.update({self.param_name_list[i]: (record.param_val_list[i], self.param_unit_list[i])})
            log_list.append(DataGroupEntry(self.label, record.line_num, record.time_delta, param_dict))
        return log_list


class LogGroupSet:
    """
    Container of parsed log data.
    """

    def __init__(self, analyzer_config):
        """
        Constructor.

        :param analyzer_config: LogAnalyzerConfig object, which used to group log data
        """
        self._data_group_dict = {}
        self._config(analyzer_config)

    def __eq__(self, other):
        return self.to_csv_string() == other.to_csv_string()

    def _config(self, analyzer_config):
        """
        Construct Label-LogDataGroup dictionary from the log parsing config object.

        :param analyzer_config: LogAnalyzerConfig object OR path to the CSV file
        """
        # From LogAnalyzerConfig
        if isinstance(analyzer_config, LogAnalyzerConfig):
            config = analyzer_config.export_parse_config()
            for entry in config.entry_list:
                data_group = LogDataGroup(entry.label, entry.param_list)
                self._data_group_dict.update({entry.label: data_group})
        # From CSV file
        elif isinstance(analyzer_config, str):
            with open(analyzer_config, 'r') as csv_in:
                entry_list = []
                for i, line in enumerate(csv_in):
                    if i > 0:
                        line_split = line[:-1].split(',')
                        label = line_split[2]
                        param = line_split[3]
                        unit = line_split[5]
                        if (label, param, unit) not in entry_list:
                            entry_list.append((label, param, unit))
                # Sort by line number
                entry_list = sorted(entry_list, key=lambda cur_entry: cur_entry[0])
                param_list = []
                for i, entry in enumerate(entry_list):
                    if i != 0 and entry[0] != entry_list[i - 1][0]:
                        data_group = LogDataGroup(entry_list[i - 1][0], param_list)
                        self._data_group_dict.update({entry_list[i - 1][0]: data_group})
                        param_list = []
                    param_list.append(ParseParam(name=entry[1], unit=entry[2]))
                    if i == len(entry_list) - 1:
                        data_group = LogDataGroup(entry[0], param_list)
                        self._data_group_dict.update({entry[0]: data_group})
            self.load_csv_file(analyzer_config)

    def add_data(self, label, line_num, time_delta, param_val_dict):
        """
        Add a log data point to the log group set.

        :param label: Label of the log data point to be added
        :param line_num: Line number in the log file of the log data point
        :param time_delta: Timestamp, which in datetime object, of the data point
        :param param_val_dict: ParameterTuple-Value dictionary of the log data point
        """
        self._data_group_dict[label].add_data(line_num, time_delta, param_val_dict)

    def get_unit(self, label, param_name):
        """
        Get the unit of a specified parameter.

        :param label: label for the parameter
        :param param_name: parameter name
        :return: unit of the parameter in a string
        """
        return self._data_group_dict[label].get_unit(param_name)

    def export_data_group(self, label, param_name=None):
        """
        Get exported data from the current log group set.

        :param label: label of the data
        :param param_name: Optional; If not specified, export all data under the label, otherwise only output the data with specified parameter name.
        :return: list of DataGroupEntry named tuple
        """
        return self._data_group_dict[label].export(param_name)

    def export_matrix(self, data_series_list=None):
        """
        Export the data as the a matrix.

        :param data_series_list: Optional; If not specified, export all the data in the current LogGroupSet, otherwise only export data in the data_series_list (list of PlotDataSeries named tuple).
        :return: tuple (exported matrix, dict{PlotDataSeries: column # in the matrix})
        """
        data_mat = [['line#', 'timestamp']]
        empty_data_line = [None, None]
        data_col_dict = {PlotDataSeries(label='line#', param=''): 0,
                         PlotDataSeries(label='timestamp', param=''): 1}
        data_list = []

        if data_series_list is None:
            # collect all data series from current data group
            data_series_list = []
            for data_group in self._data_group_dict.values():
                for param in data_group.param_name_list:
                    data_series_list.append(PlotDataSeries(label=data_group.label, param=param))
        else:
            # Sanitize, only sanitize when there are inputs from caller
            for data_series in data_series_list:
                # timestamp and line# already included in the matrix by default
                if data_series.label == 'timestamp':
                    data_series_list.remove(data_series)
                elif data_series.label == 'line#':
                    data_series_list.remove(data_series)

        for i, data_series in enumerate(data_series_list, 2):  # Init
            data_col_dict.update({PlotDataSeries(label=data_series.label, param=data_series.param): i})
            unit = self.get_unit(data_series.label, data_series.param)
            # TODO: Do not add '_' if label = ''
            if unit != '':
                data_mat[0].append(data_series.label + '_' + data_series.param + '[' + unit + ']')
            else:
                data_mat[0].append(data_series.label + '_' + data_series.param)
            empty_data_line.append(None)
            data_list += self.export_data_group(data_series.label, data_series.param)

        data_list = sorted(data_list, key=lambda line: line.line_num)
        # Merge lines which have the same line number and build the matrix
        curr_data_line = list(empty_data_line)
        for i, data_group in enumerate(data_list):
            if curr_data_line[0] != data_group.line_num:
                if i != 0:
                    data_mat.append(curr_data_line)
                    curr_data_line = list(curr_data_line)
                curr_data_line[0] = data_group.line_num  # line number
                curr_data_line[1] = data_group.time_delta.total_seconds()  # timestamp
                label = data_group.label
                param = list(data_group.param_val_dict.keys())[0]
                col = data_col_dict[PlotDataSeries(label=label, param=param)]
                val = list(data_group.param_val_dict.values())[0][0]
                curr_data_line[col] = val
            else:
                label = data_group.label
                param = list(data_group.param_val_dict.keys())[0]
                col = data_col_dict[PlotDataSeries(label=label, param=param)]
                val = list(data_group.param_val_dict.values())[0][0]
                curr_data_line[col] = val
        data_mat.append(curr_data_line)
        # Propagate values
        for i in range(2, len(data_mat[0])):
            if data_mat[1][i] is None:
                data_pos = None
                for j in range(1, len(data_mat)):
                    if data_mat[j][i] is not None:
                        data_pos = j
                        break
                if data_pos is not None:
                    for j in range(1, data_pos):
                        data_mat[j][i] = data_mat[data_pos][i]
        return data_mat, data_col_dict

    def to_csv_string(self, label=None, param_name=None):
        """
        Convert log data points to a CSV formatted string.

        - Format:
            [Line in the log],[Timestamp],[Label],[Parameter Name],[value],[Parameter Unit]

            [Line in the log],[Timestamp],[Label],[Parameter Name],[value],[Parameter Unit]

            ...

        :param label: Optional; Only convert logs with the specified label
        :param param_name: Optional; Should only be specified when 'label' argument is also specified; Only convert logs with the specified label and parameter
        :return: CSV formatted string
        """
        # aggregate logs from each log data group
        data_list = []
        if label is None:
            for group in list(self._data_group_dict.values()):
                group_data_list = group.export()
                if len(group_data_list) != 0:
                    for data_line in group_data_list:
                        data_list.append(data_line)
        else:
            data_list = self._data_group_dict[label].export(param_name)

        # sort by log line number
        data_list = sorted(data_list, key=lambda line: line.line_num)

        csv_str = ''
        for data_line in data_list:
            for param, val in sorted(data_line.param_val_dict.items()):
                csv_str += str(data_line.line_num) + ',' + str(data_line.time_delta.total_seconds()) + ',' \
                           + data_line.label + ',' + param + ',' + str(val[0]) + ',' + val[1] + '\n'

        return csv_str

    def to_csv_file(self, path, label=None, param_name=None):
        """
        Output the log data points to a CSV formatted file.

        :param path: Location to output the CSV file
        :param label: Optional; Only output logs with the specified label
        :param param_name: Optional; Should only be specified when 'label' argument is also specified; Only output logs with the specified label and parameter
        """
        with open(path, 'w') as csv_out:
            csv_out.write('LINE#,TIMESTAMP,LABEL,PARAMETER,VALUE,UNIT\n' + self.to_csv_string(label, param_name))

    def load_csv_file(self, path):
        """
        Load parsed log data from a CSV file.

        Only need to be called on purpose if this object is initialized with a LogAnalyzerConfig object;
        If this object is initialized with a CSV file path, this function is executed on initialization.

        :param path: Path to the CSV file
        """
        with open(path, 'r') as csv_in:
            last_line_split = ['', '', '', '', '', '']
            param_val_dict = {}
            line_num = 0
            for line_num, line in enumerate(csv_in, 1):
                line_split = line[:-1].split(',')
                if line_num == 2:  # First line of data
                    param_val_dict.update({line_split[3]: (float(line_split[4]), line_split[5])})
                    last_line_split = line_split
                elif line_num > 2:  # Second and later line of data
                    if line_split[0] == last_line_split[0] and line_split[2] == last_line_split[2]:  # Data from the same original log line
                        param_val_dict.update({line_split[3]: (float(line_split[4]), line_split[5])})
                    else:  # Data from different original log line
                        timestamp = timedelta(0, float(last_line_split[1]))
                        self.add_data(last_line_split[2], int(last_line_split[0]), timestamp, param_val_dict)
                        param_val_dict = {line_split[3]: (float(line_split[4]), line_split[5])}
                        last_line_split = line_split
            if line_num > 1:
                # Add the last data point in the CSV file
                timestamp = timedelta(0, float(last_line_split[1]))
                self.add_data(last_line_split[2], int(last_line_split[0]), timestamp, param_val_dict)
            else:
                raise Exception('LogGroupSet: load_csv_file: Input CSV is too short.')
