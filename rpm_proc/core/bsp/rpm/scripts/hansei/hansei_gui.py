#  ===========================================================================
#
#  Copyright (c) 2016 Qualcomm Technologies, Inc.
#  All Rights Reserved.
#  QUALCOMM Proprietary and Confidential.
#
#  ===========================================================================
from Tkinter import *
import ttk
import os

class Application(Frame):

    def __init__(self, master):
        Frame.__init__(self, master)
        self.grid(sticky=N+W+E+S)
        self.create_widgets()
        self.columnconfigure(1, weight=1)

    def create_widgets(self):
        row = 1

        label = Label(self, text="hansei.py Path:")
        label.grid(row=row, column=0, sticky=W)

        self.hansei_path = Entry(self, width=100)
        self.hansei_path.grid(row=row, column=1, sticky=W+E)
        this_dir = os.path.dirname(os.path.abspath(__file__))
        self.hansei_path.insert(0, os.path.join(this_dir, 'hansei.py'))

        row += 1

        label = Label(self, text="ELF Path:")
        label.grid(row=row, column=0, sticky=W)

        self.elf_path = Entry(self, width=100)
        self.elf_path.grid(row=row, column=1, sticky=W+E)

        elf_dir = os.path.join(os.sep.join(this_dir.split(os.sep)[:-2]), 'build')
        if os.path.exists(os.path.join(elf_dir, 'RPM_AAAAANAAR.elf')):
            self.elf_path.insert(0, os.path.join(elf_dir, 'RPM_AAAAANAAR.elf'))
        elif os.path.exists(os.path.join(elf_dir, 'RPM_AAAAANAZR.elf')):
            self.elf_path.insert(0, os.path.join(elf_dir, 'RPM_AAAAANAZR.elf'))

        row += 1

        sv = StringVar()
        sv.trace("w", lambda name, index, mode, sv=sv: self.on_changed(sv))

        label = Label(self, text="Dump Path:")
        label.grid(row=row, column=0, sticky=W)

        self.dump_path = Entry(self, width=100, textvariable=sv)
        self.dump_path.grid(row=row, column=1, sticky=W+E)

        #row += 1

        #label = Label(self, text="Target:")
        #label.grid(row=row, column=0, sticky=W)

        #self.target = Entry(self)
        #self.target.grid(row=row, column=1, sticky=W+E)

        row += 1

        label = Label(self, text="Output Path:")
        label.grid(row=row, column=0, sticky=W)

        self.out_path = Entry(self, width=100)
        self.out_path.grid(row=row, column=1, sticky=W+E)

        row += 1
        label = Label(self, text="")
        label.grid(row=row, column=0, sticky=W)

        row += 1

        label = Label(self, text="Specify File Name (Optional):")
        label.grid(row=row, column=0, sticky=W)

        row += 1

        label = Label(self, text="CODERAM:")
        label.grid(row=row, column=0, sticky=W)

        self.coderam_name = ttk.Combobox(self, width=80)
        self.coderam_name.grid(row=row, column=1, sticky=W)

        row += 1

        label = Label(self, text="DATARAM:")
        label.grid(row=row, column=0, sticky=W)

        self.dataram_name = ttk.Combobox(self, width=80)
        self.dataram_name.grid(row=row, column=1, sticky=W)

        row += 1

        label = Label(self, text="MSGRAM:")
        label.grid(row=row, column=0, sticky=W)

        self.msgram_name = ttk.Combobox(self, width=80)
        self.msgram_name.grid(row=row, column=1, sticky=W)

        row += 1

        label = Label(self, text="OCIMEM:")
        label.grid(row=row, column=0, sticky=W)

        self.ocimem_name = ttk.Combobox(self, width=80)
        self.ocimem_name.grid(row=row, column=1, sticky=W)

        row += 1

        label = Label(self, text="DDRCS0:")
        label.grid(row=row, column=0, sticky=W)

        self.ddr0_name = ttk.Combobox(self, width=80)
        self.ddr0_name.grid(row=row, column=1, sticky=W)

        row += 1

        label = Label(self, text="DDRCS1:")
        label.grid(row=row, column=0, sticky=W)

        self.ddr1_name = ttk.Combobox(self, width=80)
        self.ddr1_name.grid(row=row, column=1, sticky=W)

        row += 1

        label = Label(self, text="")
        label.grid(row=row, column=0, sticky=W)

        row += 1

        self.run_btn = Button(self, text="Run Hansei")
        self.run_btn.grid(row=row, column=0, columnspan=2)
        self.run_btn['command'] = self.run_hansei

    def on_changed(self, sv):
        dump_path = self.dump_path.get()
        if os.path.isdir(dump_path):
            filelist = tuple([f for f in os.listdir(dump_path) if os.path.isfile(os.path.join(dump_path,f))])
            self.coderam_name['values'] = filelist
            self.coderam_name.set('')
            self.dataram_name['values'] = filelist
            self.dataram_name.set('')
            self.msgram_name['values'] = filelist
            self.msgram_name.set('')
            self.ocimem_name['values'] = filelist
            self.ocimem_name.set('')
            self.ddr0_name['values'] = filelist
            self.ddr0_name.set('')
            self.ddr1_name['values'] = filelist
            self.ddr1_name.set('')

    def run_hansei(self):
        cmd = 'python %s --elf %s --output %s' % (
                self.hansei_path.get(),
                self.elf_path.get(),
                self.out_path.get()
                )
        if self.coderam_name.get().strip():
            cmd = '%s --coderam_name %s' % (cmd, self.coderam_name.get())
        if self.dataram_name.get().strip():
            cmd = '%s --dataram_name %s' % (cmd, self.dataram_name.get())
        if self.msgram_name.get().strip():
            cmd = '%s --msgram_name %s' % (cmd, self.msgram_name.get())
        if self.ocimem_name.get().strip():
            cmd = '%s --ocimem_name %s' % (cmd, self.ocimem_name.get())
        if self.ddr0_name.get().strip():
            cmd = '%s --ddr0_name %s' % (cmd, self.ddr0_name.get())
        if self.ddr1_name.get().strip():
            cmd = '%s --ddr1_name %s' % (cmd, self.ddr1_name.get())
        cmd = '%s %s' % (cmd, self.dump_path.get())
        print
        print 'Hansei Command: %s' % cmd
        ret = os.system(cmd)
        if ret == 0:
            os.system('explorer %s' % self.out_path.get())
        print 'Done'


if __name__ == '__main__':
    root = Tk()
    root.title("Hansei GUI")
    root.geometry("800x320")
    root.columnconfigure(0, weight=1)

    app = Application(root)

    root.mainloop()


