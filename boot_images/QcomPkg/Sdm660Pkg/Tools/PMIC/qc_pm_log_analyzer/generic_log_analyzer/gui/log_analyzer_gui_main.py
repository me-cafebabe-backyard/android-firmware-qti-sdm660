#!/usr/bin/python
# ===== Py 2/3 Compatibility Layer =====
from __future__ import absolute_import, division, print_function
from future.builtins import (ascii, bytes, chr, dict, filter, hex, input,
                             int, map, next, oct, open, pow, range, round,
                             str, super, zip)
from future.builtins.disabled import *
# ======================================
import sys

if sys.version_info[0] < 3:
    import Tkinter as tk
    import ttk
    import tkFileDialog as tkFd
    import tkMessageBox as tkMb
else:
    import tkinter as tk
    from tkinter import ttk
    from tkinter import filedialog as tkFd
    from tkinter import messagebox as tkMb
from framework.log_analyzer_config import *
from framework.log_data_set import *
from framework.log_parser import *
from framework.log_plot import *
from generic_log_analyzer.gui.log_analyzer_gui_plot import LogAnalyzerGuiPlot


class MainModel(object):
    """
    Model for the main window.
    """

    def __init__(self, root, view):
        """
        Constructor.

        :param root: Tk root
        :param view: View object for the main window
        """
        self.root = root
        self.view = view
        self.option = 1
        self.log_path = ''
        self.config_path = ''
        self.csv_path = ''
        self.plot_out_path = ''
        self.reg_enc_path = ''
        self.plot_sel = None

        self.analyzer_config = LogAnalyzerConfig()
        self.parser = None
        self.data_set = None
        self.plot = None

        self._plot_config = None
        self._plot_dict = {}

    def set_option(self, option):
        """
        Change the option state and change the GUI accordingly.

        :param option: int number for the option
        """
        self.option = option
        if self.option == 1: # Text log
            self.view.csvPathBtn.config(text="CSV Output Path")
            self.view.regEncPathBtn.grid_forget()
            self.view.regEncPathEty.grid_forget()
        elif self.option == 2: # CSV
            self.view.csvPathBtn.config(text="CSV Input Path")
            self.view.regEncPathBtn.grid_forget()
            self.view.regEncPathEty.grid_forget()
        elif self.option == 3: # SRAM
            self.view.csvPathBtn.config(text="CSV Output Path")
            self.view.regEncPathBtn.grid(row=1, column=0, sticky='we')
            self.view.regEncPathEty.grid(row=1, column=1, sticky='we')

    def load_config(self):
        """
        Load the plot config and display in the TreeView object.

        """
        try:
            self.analyzer_config.load_config(self.config_path)
            self._plot_config = self.analyzer_config.export_plot_config()

            # Display plot tree
            iid_count = 1
            self._plot_dict.clear()
            self.view.plotSelTv.delete(*self.view.plotSelTv.get_children())
            for group in self._plot_config:
                # Add parent
                parent_iid = -iid_count # Add all parents as negative iid
                self.view.plotSelTv.insert(parent='', index='end', iid=str(parent_iid), text=group.group_id)
                iid_count += 1
                # Add children
                children_list = []
                for plot in group.plot_list:
                    self.view.plotSelTv.insert(parent=str(parent_iid), index='end', iid=str(iid_count), text=plot.title)
                    self._plot_dict.update({iid_count: (group.group_id, plot.title)})
                    children_list.append(iid_count)
                    iid_count += 1
                self._plot_dict.update({parent_iid: children_list}) # Link the parent with children list

            # Parse in different ways depending on option selected
            if self.option == 1: # Text log
                self.parser = LogParser(self.analyzer_config)
                self.data_set = self.parser.parse_file(self.log_path)
                if self.csv_path != '':
                    self.data_set.to_csv_file(self.csv_path)
            elif self.option == 2: # CSV
                self.data_set = LogGroupSet(self.csv_path)
            elif self.option == 3: # SRAM dump
                from framework.log_parser_8998sram import LogParser_8998Sram
                sram_parser = LogParser_8998Sram(self.reg_enc_path, self.log_path)
                sram_parser.to_csv_file(self.csv_path)
                self.data_set = LogGroupSet(self.csv_path)
        except IOError:
            tkMb.showinfo('Error', 'Invalid Config File Path.')

    def open_plots(self):
        """
        Open selected plots in the TreeView object.

        """
        to_plot = set()
        for iid_str in self.plot_sel:
            iid = int(iid_str)
            if iid >= 0:
                to_plot.add(iid)
            else:
                to_plot.update(self._plot_dict[iid])

        for plot_iid in list(to_plot):
            LogAnalyzerGuiPlot(self.root, self.analyzer_config, self.data_set,
                               self._plot_dict[plot_iid][0], self._plot_dict[plot_iid][1], self.log_path)

    def open_all_plots(self):
        """
        Open all plots listed in the TreeView object.

        """
        for pair in list(self._plot_dict.items()):
            if pair[0] >= 0:
                LogAnalyzerGuiPlot(self.root, self.analyzer_config, self.data_set,
                                   pair[1][0], pair[1][1], self.log_path)

    def plot_xlsx(self):
        """
        Perform operations to output xlsx plots.

        """
        try:
            # Load Config
            self.analyzer_config.load_config(self.config_path)

            # Parse by different options
            if self.option == 1: # Text log
                self.parser = LogParser(self.analyzer_config)
                self.data_set = self.parser.parse_file(self.log_path)
                if self.csv_path != '':
                    self.data_set.to_csv_file(self.csv_path)
            elif self.option == 2: # CSV
                self.data_set = LogGroupSet(self.csv_path)
            elif self.option == 3: # SRAM
                from framework.log_parser_8998sram import LogParser_8998Sram
                sram_parser = LogParser_8998Sram(self.reg_enc_path, self.log_path)
                sram_parser.to_csv_file(self.csv_path)
                self.data_set = LogGroupSet(self.csv_path)

            # Plotting
            self.plot = LogPlot(self.analyzer_config, self.data_set)
            self.plot.plot_to_xlsx(self.plot_out_path)
            tkMb.showinfo('Complete', 'Plot Complete!')
        except IOError:
            tkMb.showinfo('Error', 'Invalid File Path(s).')


class MainView(object):
    """
    View for the main window.
    """
    def __init__(self, root):
        """
        Constructor.

        :param root: Tk root
        """
        self.root = root
        self._add_components()

    def _add_components(self):
        """
        Add components to the main window.

        """
        # Label
        self.titleLb = ttk.Label(master=self.root,
                                 text="Generic Log Analyzer",
                                 font=('Courier', 18, 'bold'),
                                 anchor=tk.CENTER,
                                 justify=tk.CENTER,
                                 relief=tk.GROOVE)
        self.titleLb.grid(row=0, column=0, columnspan=2, sticky='ew', padx=10, pady=5)

        self._add_optionLf()
        self._add_pathLf()
        self._add_opLf()
        self.root.resizable(0, 0)

    def _add_optionLf(self):
        """
        Add components in the option LabelFrame.

        """
        # Analyzing Options
        self.optionLf = ttk.LabelFrame(master=self.root,
                                       text='Analyzing Options',
                                       padding=(15, 7))
        self.optionLf.grid(row=1, column=0, sticky='ewn', padx=15, pady=10)

        self.genTxtRb = ttk.Radiobutton(master=self.optionLf,
                                        text='Generic Text Log Parsing & Plotting',
                                        value=1)
        self.genTxtRb.pack(anchor=tk.W)
        self.csvRb = ttk.Radiobutton(master=self.optionLf,
                                     text='Log Plotting from CSV',
                                     value=2)
        self.csvRb.pack(anchor=tk.W)
        self.sramRb = ttk.Radiobutton(master=self.optionLf,
                                      text='SRAM Dump Parsing & Plotting',
                                      value=3)
        self.sramRb.pack(anchor=tk.W)

    def _add_pathLf(self):
        """
        Add components in the path select LabelFrame

        """
        # File Path Settings
        self.pathLf = ttk.LabelFrame(master=self.root,
                                     text='File Path Settings',
                                     padding=(15, 7))
        self.pathLf.grid(row=2, column=0, sticky='ewn', padx=15, pady=10)

        # Config Path
        self.configPathBtn = ttk.Button(master=self.pathLf,
                                        text='Configuration Path')
        self.configPathBtn.grid(row=0, column=0, sticky='we')
        self.configPathEty = ttk.Entry(master=self.pathLf)
        self.configPathEty.grid(row=0, column=1, sticky='we')

        # Register Encoding Map
        self.regEncPathBtn = ttk.Button(master=self.pathLf,
                                        text='Register Encoding Path')
        self.regEncPathEty = ttk.Entry(master=self.pathLf)

        # Log Path
        self.logPathBtn = ttk.Button(master=self.pathLf,
                                     text='Log Path')
        self.logPathBtn.grid(row=2, column=0, sticky='we')
        self.logPathEty = ttk.Entry(master=self.pathLf)
        self.logPathEty.grid(row=2, column=1, sticky='we')

        # CSV Path
        self.csvPathBtn = ttk.Button(master=self.pathLf,
                                     text='CSV Output Path')
        self.csvPathBtn.grid(row=3, column=0, sticky='we')
        self.csvPathEty = ttk.Entry(master=self.pathLf)
        self.csvPathEty.grid(row=3, column=1, sticky='we')

        # Plot Output Path
        self.plotOutPathBtn = ttk.Button(master=self.pathLf,
                                         text='Plot Output Path')
        self.plotOutPathBtn.grid(row=4, column=0, sticky='we')
        self.plotOutPathEty = ttk.Entry(master=self.pathLf)
        self.plotOutPathEty.grid(row=4, column=1, sticky='we')

    def _add_opLf(self):
        """
        Add components in the operations LabelFrame

        """
        # Operations
        self.opLf = ttk.LabelFrame(master=self.root,
                                   text='Operations',
                                   padding=(15, 7))
        self.opLf.grid(row=1, column=1, rowspan=2, sticky='ewns', padx=15, pady=10)

        self.loadConfigBtn = ttk.Button(master=self.opLf,
                                        text='Load Config & Parse')
        self.loadConfigBtn.grid(row=0, column=0, columnspan=2, sticky='we')

        self.treeViewFrm = ttk.Frame(self.opLf)
        self.treeViewFrm.grid(row=1, column=0, columnspan=2, sticky='we', pady=5)
        self.plotSelTv = ttk.Treeview(master=self.treeViewFrm)
        ysb = ttk.Scrollbar(master=self.treeViewFrm, orient=tk.VERTICAL, command=self.plotSelTv.yview)
        xsb = ttk.Scrollbar(master=self.treeViewFrm, orient=tk.HORIZONTAL, command=self.plotSelTv.xview)
        self.plotSelTv.config(yscroll=ysb.set, xscroll=xsb.set)
        self.plotSelTv.column('#0', width='250')
        self.plotSelTv.heading('#0', text='Plots')
        self.plotSelTv.grid(row=0, column=0, sticky='nsew')
        ysb.grid(row=0, column=1, sticky='ns')
        xsb.grid(row=1, column=0, sticky='ew')

        self.openPlotBtn = ttk.Button(master=self.opLf,
                                      text='Open Selected Plot(s)')
        self.openPlotBtn.grid(row=2, column=0, columnspan=1, sticky='we')
        self.openAllPlotBtn = ttk.Button(master=self.opLf,
                                         text='Open All Plots')
        self.openAllPlotBtn.grid(row=2, column=1, columnspan=1, sticky='we')
        self.plotXlsxBtn = ttk.Button(master=self.opLf,
                                      text='Parse & Plot to XLSX')
        self.plotXlsxBtn.grid(row=3, column=0, columnspan=2, sticky='we', pady=12)


class MainController(object):
    """
    Controller for the main window.
    """
    def __init__(self, root, model, view):
        """
        Constructor.

        :param root: Tk root
        :param model: model object to the main window
        :param view: view object to the main window
        """
        self.root = root
        self.model = model
        self.view = view
        self._add_commands()

    def _add_commands(self):
        """
        Linking commands the controllers in the main window.

        """
        self._add_optionLf()
        self._add_pathLf()
        self._add_opLf()

    def _add_optionLf(self):
        """
        Link commands to the parsing option LabelFrame.

        """
        self.option = tk.IntVar(value=1)
        self.view.genTxtRb.config(variable=self.option, command=self._cmd_rb)
        self.view.csvRb.config(variable=self.option, command=self._cmd_rb)
        self.view.sramRb.config(variable=self.option, command=self._cmd_rb)

    def _add_pathLf(self):
        """
        Link commands to the parsing option LabelFrame.

        """
        self.logPath = tk.StringVar()

        def _update_log_path(name, index, mode):
            """
            Operation on the content of log path Entry object changes.

            :param name:
            :param index:
            :param mode:
            :return:
            """
            self.model.log_path = self.logPath.get()

        self.logPath.trace(mode='w', callback=_update_log_path)
        self.view.logPathBtn.config(command=self._cmd_logPathBtn)
        self.view.logPathEty.config(textvariable=self.logPath)

        self.configPath = tk.StringVar()

        def _update_config_path(name, index, mode):
            """
            Operation on the content of config path Entry object changes.

            :param name:
            :param index:
            :param mode:
            :return:
            """
            self.model.config_path = self.configPath.get()

        self.configPath.trace(mode='w', callback=_update_config_path)
        self.view.configPathBtn.config(command=self._cmd_configPathBtn)
        self.view.configPathEty.config(textvariable=self.configPath)

        self.regEncPath = tk.StringVar()

        def _update_reg_enc_path(name, index, mode):
            """
            Operation on the content of register encoding map path Entry object changes.

            :param name:
            :param index:
            :param mode:
            :return:
            """
            self.model.reg_enc_path = self.regEncPath.get()

        self.regEncPath.trace(mode='w', callback=_update_reg_enc_path)
        self.view.regEncPathBtn.config(command=self._cmd_regEncPathBtn)
        self.view.regEncPathEty.config(textvariable=self.regEncPath)

        self.csvPath = tk.StringVar()

        def _update_csv_path(name, index, mode):
            """
            Operation on the content of csv path Entry object changes.

            :param name:
            :param index:
            :param mode:
            :return:
            """
            self.model.csv_path = self.csvPath.get()

        self.csvPath.trace(mode='w', callback=_update_csv_path)
        self.view.csvPathBtn.config(command=self._cmd_csvPathBtn)
        self.view.csvPathEty.config(textvariable=self.csvPath)

        self.plotOutPath = tk.StringVar()

        def _update_plot_out_path(name, index, mode):
            """
            Operation on the content of log path Entry object changes.

            :param name:
            :param index:
            :param mode:
            :return:
            """
            self.model.plot_out_path = self.plotOutPath.get()

        self.plotOutPath.trace(mode='w', callback=_update_plot_out_path)
        self.view.plotOutPathBtn.config(command=self._cmd_plotOutPathBtn)
        self.view.plotOutPathEty.config(textvariable=self.plotOutPath)

    def _add_opLf(self):
        """
        Link commands to the operations LabelFrame.

        """
        self.view.loadConfigBtn.config(command=self._cmd_loadConfigBtn)
        self.view.plotSelTv.bind('<<TreeviewSelect>>', self._cmd_plotSelTv_select)
        self.view.openPlotBtn.config(command=self._cmd_openPlotBtn)
        self.view.openAllPlotBtn.config(command=self._cmd_openAllPlotBtn)
        self.view.plotXlsxBtn.config(command=self._cmd_plotXlsxBtn)

    def _cmd_rb(self):
        """
        Command on clicking on RadioButtons.

        """
        self.model.set_option(self.option.get())

    def _cmd_logPathBtn(self):
        """
        Command on clicking on log path button.

        """
        self.logPath.set(
            tkFd.askopenfilename(filetypes=[('Text Files', '.txt'), ('Log Files', '.log'), ('All Files', '.*')]))
        self.model.log_path = self.logPath.get()

    def _cmd_regEncPathBtn(self):
        """
        Command on clicking on register encoding map path button.

        """
        self.regEncPath.set(
            tkFd.askopenfilename(filetypes=[('Register Encoding Map Files', '.csv'), ('All Files', '.*')]))
        self.model.reg_enc_path = self.regEncPath.get()

    def _cmd_configPathBtn(self):
        """
        Command on clicking on register config path button.

        """
        self.configPath.set(tkFd.askopenfilename(filetypes=[('XML Files', '.xml'), ('All Files', '.*')]))
        self.model.config_path = self.configPath.get()

    def _cmd_csvPathBtn(self):
        """
        Command on clicking on csv path button.

        """
        if self.model.option == 2:
            self.csvPath.set(tkFd.askopenfilename(filetypes=[('CSV Files', '.csv'), ('All Files', '.*')]))
        elif self.model.option == 1 or self.model.option == 3:
            self.csvPath.set(tkFd.asksaveasfilename(filetypes=[('CSV Files', '.csv'), ('All Files', '.*')],
                                                    defaultextension='.csv'))
        self.model.csv_path = self.csvPath.get()

    def _cmd_plotOutPathBtn(self):
        """
        Command on clicking on plot output path button.

        """
        self.plotOutPath.set(tkFd.asksaveasfilename(filetypes=[('Excel Files', '.xlsx'), ('All Files', '.*')],
                                                    defaultextension='.xlsx'))
        self.model.plot_out_path = self.plotOutPath.get()

    def _cmd_loadConfigBtn(self):
        """
        Command on clicking on plot load config button.

        """
        self.model.load_config()

    def _cmd_plotSelTv_select(self, event):
        """
        Command on clicking on selecting items in plot select TreeView.

        :param event: event object
        """
        self.model.plot_sel = self.view.plotSelTv.selection()

    def _cmd_openPlotBtn(self):
        """
        Command on clicking on open plot button.

        """
        self.model.open_plots()

    def _cmd_openAllPlotBtn(self):
        """
        Command on clicking on open all plots button.

        """
        self.model.open_all_plots()

    def _cmd_plotXlsxBtn(self):
        """
        Command on clicking on plot xlsx button.

        """
        self.model.plot_xlsx()


class LogAnalyzerGuiMain:
    """
    Wrapper to start the main GUI of the Generic Log Analyzer.
    """
    def __init__(self):
        """
        Constructor.
        """
        self.root = tk.Tk()
        self.root.title("Generic Log Analyzer")
        self.view = MainView(self.root)
        self.model = MainModel(self.root, self.view)
        self.controller = MainController(self.root, self.model, self.view)

    def start(self):
        """
        Open the main window.

        """
        self.root.mainloop()
