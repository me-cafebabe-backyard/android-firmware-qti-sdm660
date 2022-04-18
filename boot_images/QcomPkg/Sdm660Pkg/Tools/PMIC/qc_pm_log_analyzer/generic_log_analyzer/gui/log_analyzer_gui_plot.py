#!/usr/bin/python
# ===== Py 2/3 Compatibility Layer =====
from __future__ import absolute_import, division, print_function
from future.builtins import (ascii, bytes, chr, dict, filter, hex, input,
                             int, map, next, oct, open, pow, range, round,
                             str, super, zip)
from future.builtins.disabled import *
# ======================================
from framework.log_analyzer_config import PlotDataSeries
import sys

if sys.version_info[0] < 3:
    import Tkinter as tk
    import ttk
else:
    import tkinter as tk
    from tkinter import ttk
import matplotlib

matplotlib.use('TkAgg')
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg, NavigationToolbar2TkAgg
from matplotlib.figure import Figure
from matplotlib.ticker import MultipleLocator
import numpy as np
import linecache


class PlotModel(object):
    """
    Model for the plot window
    """
    def __init__(self, view, plot_config, data_set, plot_group_id, plot_title, log_path):
        """
        Constructor.

        :param view: View object of the plot window
        :param plot_config: plot config exported from LogAnalyzerConfig, as PlotGroup named tuple
        :param data_set: LogGroupSet object
        :param plot_group_id: group id of the plot in string
        :param plot_title: title of the plot in string
        :param log_path: path to the original parsed log
        """
        self.view = view
        self.plot_config = plot_config
        self.data_set = data_set
        self.plot_group_id = plot_group_id
        self.plot_title = plot_title
        self.log_path = log_path
        self.matrix = None
        self.mat_row_dict = None
        self.pick_index = None
        self.canvas_bg = None
        self.top_axis = None
        self._setup()

    def _setup(self):
        """
        Export needed data as a matrix

        """
        # Find specified plot, add needed data series to data series set
        data_series_set = set()
        for group in self.plot_config:
            if group.group_id == self.plot_group_id:
                for plot in group.plot_list:
                    if plot.title == self.plot_title:
                        self.target_plot = plot
                        if plot.y_axis.config_1 is not None:
                            data_series_set.update(plot.y_axis.config_1.data_series_list)
                        if plot.y_axis.config_2 is not None:
                            data_series_set.update(plot.y_axis.config_2.data_series_list)
                        if plot.x_axis.config_1 is not None:
                            data_series_set.update(plot.x_axis.config_1.data_series_list)
                        if plot.x_axis.config_2 is not None:
                            data_series_set.update(plot.x_axis.config_2.data_series_list)
                        break
                break
        # Export the required data as a matrix
        data_mat, self.mat_row_dict = self.data_set.export_matrix(list(data_series_set))
        self.matrix = list(np.array(data_mat).transpose()) # Transpose matrix

    def plot(self):
        """
        Plot the graph with matplotlib in the window.

        """
        def make_format(current, other):
            """
            Function to format the display of the cursor location for both axis.

            :param current: Axis 1
            :param other: Axis 2
            """
            def format_coord(x, y):
                """
                Format the coordinate string.

                :param x: X position of the Axis 1
                :param y: Y position of the Axis 1
                :return: formatted coordinates string
                """
                # convert to display coordinates
                display_coord = current.transData.transform((x, y))
                inv = other.transData.inverted()
                # convert back to data coords with respect to ax
                ax_coord = inv.transform(display_coord)
                coords = [ax_coord, (x, y)]
                return ('Left: {:<40}    Right: {:<}'
                        .format(*['({:.3f}, {:.3f})'.format(x, y) for x, y in coords]))
            return format_coord

        def data_picker(line, event):
            """
            Define the criteria of picking a point on line.

            :param line: line to be picked on
            :param event: event object
            :return: tuple (whether successfully picked, data dictionary)
            """
            if event.xdata is None:
                return False, dict()
            xdata = line.get_xdata().astype('float64')
            d = np.absolute(xdata - event.xdata)

            index = np.argmin(d)
            if index is not None:
                pickx = np.take(xdata, index)
                props = dict(index=index, pickx=pickx)
                return True, props
            else:
                return False, dict()

        # Init
        all_lines = []
        self.top_axis = self.view.axis1

        # Set plot min/max limits on X axis as the beginning/ending of the data if not specified in the config
        x_min = self.target_plot.x_axis.config_1.min_val
        x_max = self.target_plot.x_axis.config_1.max_val
        if x_min is None:
            x_min = float(self.matrix[self.mat_row_dict[self.target_plot.x_axis.config_1.data_series_list[0]]][1])
        if x_max is None:
            x_max = float(self.matrix[self.mat_row_dict[self.target_plot.x_axis.config_1.data_series_list[0]]][-1])

        # Plot on primary axis
        for data_series in self.target_plot.y_axis.config_1.data_series_list:
            all_lines.append(self.view.axis1.plot(
                self.matrix[self.mat_row_dict[self.target_plot.x_axis.config_1.data_series_list[0]]][1:],
                self.matrix[self.mat_row_dict[data_series]][1:],
                label=self.matrix[self.mat_row_dict[data_series]][0],
                linewidth=1,
                marker='+',
                picker=data_picker))
        # Set axis limits
        self.view.axis1.set_ylim(self.target_plot.y_axis.config_1.min_val,
                                 self.target_plot.y_axis.config_1.max_val)
        self.view.axis1.set_xlim(x_min,
                                 x_max)
        # Set major/minor ticks
        if self.target_plot.y_axis.config_1.major_tick is not None:
            self.view.axis1.yaxis.set_major_locator(MultipleLocator(self.target_plot.y_axis.config_1.major_tick))
        if self.target_plot.y_axis.config_1.minor_tick is not None:
            self.view.axis1.yaxis.set_minor_locator(MultipleLocator(self.target_plot.y_axis.config_1.minor_tick))
        if self.target_plot.x_axis.config_1.major_tick is not None:
            self.view.axis1.xaxis.set_major_locator(MultipleLocator(self.target_plot.x_axis.config_1.major_tick))
        if self.target_plot.x_axis.config_1.minor_tick is not None:
            self.view.axis1.xaxis.set_minor_locator(MultipleLocator(self.target_plot.x_axis.config_1.minor_tick))
        # Set axis labels
        self.view.axis1.set_ylabel(self.target_plot.y_axis.config_1.label)
        self.view.axis1.set_xlabel(self.target_plot.x_axis.config_1.label)
        # Set plot title
        self.view.axis1.set_title(self.plot_title)
        # Set Grid Lines
        self.view.axis1.yaxis.grid(True, 'major', linestyle='-')
        self.view.axis1.yaxis.grid(True, 'minor', linestyle='--')
        self.view.axis1.xaxis.grid(True, 'minor', linestyle='-')

        # Plot on secondary axis
        if self.target_plot.y_axis.config_2 is not None:
            self.view.axis2 = self.view.axis1.twinx()
            self.top_axis = self.view.axis2
            # Increase the line color count on the secondary axis (need matplotlib >= 1.5)
            for i in range(len(all_lines)):
                next(self.view.axis2._get_lines.prop_cycler)
            for data_series in self.target_plot.y_axis.config_2.data_series_list:
                all_lines.append(self.view.axis2.plot(
                    self.matrix[self.mat_row_dict[self.target_plot.x_axis.config_1.data_series_list[0]]][1:],
                    self.matrix[self.mat_row_dict[data_series]][1:],
                    label=self.matrix[self.mat_row_dict[data_series]][0],
                    linewidth=1,
                    marker='+',
                    picker=data_picker))
            # Set axis limits
            self.view.axis2.set_ylim(self.target_plot.y_axis.config_2.min_val,
                                     self.target_plot.y_axis.config_2.max_val)
            self.view.axis2.set_xlim(x_min,
                                     x_max)
            # Set major/minor ticks
            if self.target_plot.y_axis.config_2.major_tick is not None:
                self.view.axis2.yaxis.set_major_locator(MultipleLocator(self.target_plot.y_axis.config_2.major_tick))
            if self.target_plot.y_axis.config_2.minor_tick is not None:
                self.view.axis2.yaxis.set_minor_locator(MultipleLocator(self.target_plot.y_axis.config_2.minor_tick))
            # Set axis labels
            self.view.axis2.set_ylabel(self.target_plot.y_axis.config_2.label)
            # Set Grid Lines
            self.view.axis2.yaxis.grid(True, 'major', linestyle='-')
            self.view.axis2.yaxis.grid(True, 'minor', linestyle=':')
            self.view.axis2.format_coord = make_format(self.view.axis2, self.view.axis1)

        # Adjust axis 1 size
        box = self.view.axis1.get_position()
        self.view.axis1.set_position([box.x0, box.y0 + box.height * 0.1, box.width, box.height * 0.9])

        if self.target_plot.y_axis.config_2 is not None:
            # Adjust axis 2 size
            box = self.view.axis2.get_position()
            self.view.axis2.set_position([box.x0, box.y0 + box.height * 0.1, box.width, box.height * 0.9])
            # Combine legends from both axis
            lines_sum = all_lines[0]
            for i in range(1, len(all_lines)):
                lines_sum += all_lines[i]
            # Set legend
            self.view.axis2.legend(lines_sum, [l.get_label() for l in lines_sum],
                                   loc='upper center', bbox_to_anchor=(0.5, -0.1), ncol=3, fontsize='small')
        else:
            # Set legend
            self.view.axis1.legend(loc='upper center', bbox_to_anchor=(0.5, -0.1), ncol=3, fontsize='small')

        # Create data cursor
        self.view.vert_cursor = self.top_axis.axvline(self.top_axis.get_ybound()[0], color='r')

    def load_log(self, index):
        """
        Load and display lines in the log been parsed.

        :param index: data point index in the current data series
        """
        line_num = self.matrix[self.mat_row_dict[PlotDataSeries(label='line#', param='')]][index + 1].astype(np.int)
        self.view.logTxt.config(state='normal')
        self.view.logTxt.delete('1.0', tk.END)
        if linecache.getline(self.log_path, 1) != '':
            for i, shift in enumerate(range(-50, 51), 1):
                line = linecache.getline(self.log_path, line_num + shift)
                line_num_str = str(line_num + shift) + ':'
                self.view.logTxt.insert(tk.END, line_num_str)
                self.view.logTxt.insert(tk.END, line)
                # Add tags to highlight
                if shift == 0:
                    self.view.logTxt.tag_add('highlight', str(i) + '.' + str(len(line_num_str)), str(i + 1) + '.0')
                    # Move cursor to the highlighted line
                    self.view.logTxt.mark_set('insert', str(i) + '.0')
                    self.view.logTxt.see('insert')
                self.view.logTxt.tag_add('line_num', str(i) + '.0', str(i) + '.' + str(len(line_num_str)))
            # Highlight tags and line numbers
            self.view.logTxt.tag_config('highlight', background='yellow')
            self.view.logTxt.tag_config('line_num', background='brown4', foreground='white', font='-size 10 -weight bold')
        else:
            if self.log_path == '':
                self.view.logTxt.insert(tk.END, 'Log Path Not Specified.\n')
            else:
                self.view.logTxt.insert(tk.END, 'Invalid Log Path.\n')
        self.view.logTxt.config(state='disabled')

    def change_top_axis(self, axis):
        """
        Switch the top Y-axis when display.

        :param axis: Y-axis to be on the top; 1 or 2.
        """
        if axis == 1:
            self.view.axis1.set_zorder(10)
            self.view.axis2.set_zorder(5)
            self.top_axis = self.view.axis1
            self.view.axis1.patch.set_visible(False)
            self.view.axis2.patch.set_visible(True)
        elif axis == 2:
            self.view.axis1.set_zorder(5)
            self.view.axis2.set_zorder(10)
            self.top_axis = self.view.axis2
            self.view.axis1.patch.set_visible(True)
            self.view.axis2.patch.set_visible(False)


class PlotView(object):
    """
    View object to the plot window.
    """
    def __init__(self, root):
        self.root = root
        self._add_components()

    def _add_components(self):
        """
        Add components in the plot window.

        """
        self.figure = Figure()
        self.axis1 = self.figure.add_subplot(111)
        self.axis2 = None
        self.toolbarFrm = ttk.Frame(self.root)
        self.toolbarFrm.pack(side=tk.TOP, fill=tk.X, expand=0)
        self.canvas = FigureCanvasTkAgg(figure=self.figure, master=self.root)
        self.canvas.show()
        self.canvas.get_tk_widget().pack(side=tk.TOP, fill=tk.BOTH, expand=1)
        self.toolbar = NavigationToolbar2TkAgg(self.canvas, self.toolbarFrm)
        self.toolbar.update()
        self.vert_cursor = None

        # Crate Text Box for log traceback
        self.logTxtFrm = ttk.Frame(self.root)
        self.logTxtFrm.pack(side=tk.BOTTOM, fill=tk.X, expand=0)
        self.logTxt = tk.Text(master=self.logTxtFrm, height=6, wrap='none')
        ysb = ttk.Scrollbar(master=self.logTxtFrm, orient=tk.VERTICAL, command=self.logTxt.yview)
        ysb.grid(row=0, column=1, sticky='ns')
        xsb = ttk.Scrollbar(master=self.logTxtFrm, orient=tk.HORIZONTAL, command=self.logTxt.xview)
        xsb.grid(row=1, column=0, sticky='ew')
        self.logTxt.config(xscrollcommand=xsb.set, yscrollcommand=ysb.set)
        self.logTxt.grid(row=0, column=0, sticky='nsew')
        self.logTxtFrm.columnconfigure(0, weight=1)


class PlotController(object):
    """
    Controller for plot window.
    """
    def __init__(self, root, model, view):
        """
        Constructor.

        :param root: Tk root
        :param model: Model for the plot window
        :param view: View for the plot window
        """
        self.root = root
        self.model = model
        self.view = view
        self._add_commands()

    def _add_commands(self):
        """
        Link commands to the controllers in the plot window.

        """
        def _canvas_on_pick(event):
            """
            Todo on picking event.

            :param event:
            """
            if self.model.pick_index != event.index:
                self.model.pick_index = event.index
                self.model.load_log(event.index)

        def _canvas_on_move(event):
            """
            Todo on mouse moving event.

            :param event:
            """
            if not event.inaxes:
                return
            self.view.vert_cursor.set_xdata(event.xdata)
            self.view.vert_cursor.set_visible(True)
            if self.view.canvas.supports_blit:
                if self.model.canvas_bg is not None:
                    self.view.canvas.restore_region(self.model.canvas_bg)
                self.model.top_axis.draw_artist(self.view.vert_cursor)
                self.view.canvas.blit(self.model.top_axis.bbox)
            else:
                self.view.canvas.draw_idle()

        def _canvas_on_draw(event):
            """
            Todo on drawing on canvas event.

            :param event:
            """
            self.model.canvas_bg = self.view.canvas.copy_from_bbox(self.model.top_axis.bbox)
            self.view.vert_cursor.set_visible(False)

        def _canvas_on_resize(event):
            """
            Todo on resizing the canvas.

            :param event:
            """
            if self.model.canvas_bg is not None:
                self.view.canvas.restore_region(self.model.canvas_bg)
            self.view.vert_cursor.set_visible(False)

        def _canvas_on_click(event):
            """
            Todo on clicking on the canvas.

            :param event:
            """
            if self.model.canvas_bg is not None:
                self.view.canvas.restore_region(self.model.canvas_bg)
            self.view.vert_cursor.set_visible(False)

        def _on_key(event):
            """
            Todo on pressing keys on the keyboard.

            :param event:
            """
            # Resize log backtrace Text Box
            if event.char == '[' and self.view.logTxt['height'] > 3:
                self.view.logTxt['height'] -= 1
            elif event.char == ']' and self.view.logTxt['height'] < 25:
                self.view.logTxt['height'] += 1

        # Setup events
        self.view.canvas.mpl_connect('motion_notify_event', _canvas_on_move)
        self.view.canvas.mpl_connect('draw_event', _canvas_on_draw)
        self.view.canvas.mpl_connect('resize_event', _canvas_on_resize)
        self.view.canvas.mpl_connect('pick_event', _canvas_on_pick)
        self.view.canvas.mpl_connect('button_press_event', _canvas_on_click)
        self.root.bind('<Key>', _on_key)


class LogAnalyzerGuiPlot:
    """
    Wrapper to start the GUI plot.
    """
    def __init__(self, root, analyzer_config, log_group_set, plot_group_id, plot_title, log_path):
        """
        Constructor.

        :param root: Tk root
        :param analyzer_config: LogAnalyzerConfig object
        :param log_group_set: LogGroupSet object
        :param plot_group_id: plot group id string
        :param plot_title: plot title string
        :param log_path: log path to the parsed log
        """
        self.top_level = tk.Toplevel(root)
        self.top_level.title(plot_group_id + ' // ' + plot_title)
        self.view = PlotView(self.top_level)
        self.model = PlotModel(self.view,
                               analyzer_config.export_plot_config(),
                               log_group_set,
                               plot_group_id,
                               plot_title,
                               log_path)
        self.controller = PlotController(self.top_level, self.model, self.view)
        self.model.plot()
