#!/usr/bin/python
# ===== Py 2/3 Compatibility Layer =====
from __future__ import absolute_import, division, print_function
from future.builtins import (ascii, bytes, chr, dict, filter, hex, input,
                             int, map, next, oct, open, pow, range, round,
                             str, super, zip)
from future.builtins.disabled import *
# ======================================
from xml.etree import ElementTree
from xml.etree.ElementTree import Element, SubElement
from xml.dom import minidom
from collections import namedtuple

# Parse configuration tuples
ParseParam = namedtuple('ParseParam', ['name', 'unit'])
ParseEntry = namedtuple('ParseEntry', ['key', 'label', 'param_list', 'delim'])
ParseConfig = namedtuple('ParseConfig', ['time_regex', 'time_format', 'entry_list'])
# Plot configuration tuples
PlotDataSeries = namedtuple('PlotDataSeries', ['label', 'param'])
PlotAxisConfig = namedtuple('PlotAxisConfig',
                            ['label', 'major_tick', 'minor_tick', 'min_val', 'max_val', 'data_series_list'])
PlotAxis = namedtuple('PlotAxis', ['config_1', 'config_2'])
Plot = namedtuple('Plot', ['title', 'y_axis', 'x_axis'])
PlotGroup = namedtuple('PlotGroup', ['group_id', 'plot_list'])


class LogAnalyzerConfig:
    """
    Construct/Load log parsing configuration XML file.
    """

    def __init__(self, path=None):
        """
        Constructor.

        Construct a new log parsing configuration or load a configuration from an external XML file.

        :param path: Optional; Load the configuration from the external XML file when specified
        """
        self._root = None
        self._parse_config_elem = None
        self._plot_config_elem = None
        if path is None:
            self.new_config()
        else:
            self.load_config(path)

    def new_config(self):
        """
        Create a new log parsing configuration file.

        """
        self._root = Element('LogAnalyzerConfig')
        self._parse_config_elem = SubElement(self._root, 'ParseConfig')
        self._plot_config_elem = SubElement(self._root, 'PlotsCollection')

    def load_config(self, path, parse=True, plot=True):
        """
        Load a existing log parsing configuration file.

        :param path: Path to existing log parsing configuration XML file
        :param parse: whether to load parse config
        :param plot: whether to load plot config
        """
        self._root = ElementTree.parse(path).getroot()
        if parse:
            self._parse_config_elem = self._root.find('./ParseConfig')
        if plot:
            self._plot_config_elem = self._root.find('./PlotsCollection')

    def add_time_format(self, regex_str, format_str):
        """
        Add time format config in the XML config file.

        :param regex_str: Regex string to parse the timestamp in the logs
        :param format_str: format string to interpret the timestamp; Refer to https://docs.python.org/2/library/datetime.html#strftime-and-strptime-behavior for more details
        """
        SubElement(self._parse_config_elem, 'Timestamp', regex=regex_str, format=format_str)

    def add_parse_entry(self, label_str, key_str, param_tuple_list, delim):
        """
        Add a new searching keyword in searching the log.

        :param label_str: Label string
        :param key_str: Keyword for matching in the log
        :param param_tuple_list: List of parameters in (parameter_name, unit) tuple format
        :param delim: Delimiter for the key-value pair to be parsed
        """
        label = SubElement(self._parse_config_elem, 'Entry', label=label_str, key=key_str, delim=delim)
        params = [Element('Param', name=param[0],
                          unit=param[1] if (len(param) > 1) else '') for param in param_tuple_list]
        label.extend(params)

    def export_parse_config(self):
        """
        Convert parsing configuration to ParseConfig named tuple.

        :return: ParseConfig named tuple
        """
        if self._parse_config_elem is None:
            raise Exception('LogConfig: export_parse_config: Parse configuration is not loaded.')
        time_regex = self._parse_config_elem.find('./Timestamp').attrib['regex']
        time_format = self._parse_config_elem.find('./Timestamp').attrib['format']
        config_list = []
        count = 0
        for entry in self._parse_config_elem.findall('./Entry'):
            config_list.append(
                ParseEntry(key=entry.attrib['key'], label=entry.attrib['label'],
                           param_list=[], delim=entry.attrib['delim']))
            for param in entry:
                config_list[count].param_list.append(
                    ParseParam(name=param.attrib['name'], unit=param.attrib['unit']))
            count += 1
        return ParseConfig(time_regex=time_regex, time_format=time_format, entry_list=config_list)

    def export_plot_config(self):
        """
        Convert plotting configuration to PlotGroup named tuple.

        :return: PlotGroup named tuple
        """
        if self._plot_config_elem is None:
            raise Exception('LogConfig: export_plot_config: Plot configuration is not loaded.')
        plot_group_list = []
        for group in self._plot_config_elem.findall('./Group'):  # <Group>
            group_id = group.find('GroupID').text
            plot_list = []
            for plot in group.findall('Plot'):  # <Plot>
                title = plot.find('Title').text
                y_axis = plot.find('Y-Axis')
                x_axis = plot.find('X-Axis')
                y_config_1_ds_list = []
                y_config_1 = None
                y_config_2_ds_list = []
                y_config_2 = None
                x_config_1_ds_list = []
                x_config_1 = None
                x_config_2_ds_list = []
                x_config_2 = None
                for ds in y_axis.findall('DataSeries'):  # <Y-Axis>/<DataSeries>
                    axis_group = int(ds.find('AxisGroup').text)
                    series_name = ds.find('SeriesName').attrib
                    if axis_group == 1:
                        y_config_1_ds_list.append(PlotDataSeries(label=series_name['label'],
                                                                 param=series_name['param']))
                    elif axis_group == 2:
                        y_config_2_ds_list.append(PlotDataSeries(label=series_name['label'],
                                                                 param=series_name['param']))
                for ds in x_axis.findall('DataSeries'):  # <X-Axis>/<DataSeries>
                    axis_group = int(ds.find('AxisGroup').text)
                    series_name = ds.find('SeriesName').attrib
                    if axis_group == 1:
                        x_config_1_ds_list.append(PlotDataSeries(label=series_name['label'],
                                                                 param=series_name['param']))
                    elif axis_group == 2:
                        x_config_2_ds_list.append(PlotDataSeries(label=series_name['label'],
                                                                 param=series_name['param']))
                for i, config in enumerate(y_axis.findall('AxisConfig')):  # <Y-Axis>/<AxisConfig>
                    label = config.find('Label').text
                    major_tick = float(config.find('MajorTick').text) if config.find(
                        'MajorTick').text is not None else None
                    minor_tick = float(config.find('MinorTick').text) if config.find(
                        'MinorTick').text is not None else None
                    min_val = float(config.find('MinValue').text) if config.find('MinValue').text is not None else None
                    max_val = float(config.find('MaxValue').text) if config.find('MaxValue').text is not None else None
                    if i == 0:
                        y_config_1 = PlotAxisConfig(label=label,
                                                    major_tick=major_tick,
                                                    minor_tick=minor_tick,
                                                    min_val=min_val,
                                                    max_val=max_val,
                                                    data_series_list=y_config_1_ds_list)
                    elif i == 1:
                        y_config_2 = PlotAxisConfig(label=label,
                                                    major_tick=major_tick,
                                                    minor_tick=minor_tick,
                                                    min_val=min_val,
                                                    max_val=max_val,
                                                    data_series_list=y_config_2_ds_list)
                for i, config in enumerate(x_axis.findall('AxisConfig')):  # <X-Axis>/<AxisConfig>
                    label = config.find('Label').text
                    major_tick = float(config.find('MajorTick').text) if config.find(
                        'MajorTick').text is not None else None
                    minor_tick = float(config.find('MinorTick').text) if config.find(
                        'MinorTick').text is not None else None
                    min_val = float(config.find('MinValue').text) if config.find('MinValue').text is not None else None
                    max_val = float(config.find('MaxValue').text) if config.find('MaxValue').text is not None else None
                    if i == 0:
                        x_config_1 = PlotAxisConfig(label=label,
                                                    major_tick=major_tick,
                                                    minor_tick=minor_tick,
                                                    min_val=min_val,
                                                    max_val=max_val,
                                                    data_series_list=x_config_1_ds_list)
                    elif i == 1:
                        x_config_2 = PlotAxisConfig(label=label,
                                                    major_tick=major_tick,
                                                    minor_tick=minor_tick,
                                                    min_val=min_val,
                                                    max_val=max_val,
                                                    data_series_list=x_config_2_ds_list)
                plot_list.append(Plot(title=title,
                                      y_axis=PlotAxis(config_1=y_config_1, config_2=y_config_2),
                                      x_axis=PlotAxis(config_1=x_config_1, config_2=x_config_2)))

            plot_group_list.append(PlotGroup(group_id=group_id, plot_list=plot_list))
        return plot_group_list

    def to_xml_string(self):
        """
        Output current configuration as an XML format string.

        :return: XML format of the current configuration in a string
        """
        raw_str = ElementTree.tostring(self._root, 'utf-8')
        parsed = minidom.parseString(raw_str)
        return '\n'.join([line for line in parsed.toprettyxml(indent=' ' * 4).split('\n') if line.strip()])

    def to_xml_file(self, path):
        """
        Output current configuration as an XML file.

        :param path: Output path for XML file
        """
        with open(path, 'w') as xml_out_file:
            xml_out_file.write(self.to_xml_string())
