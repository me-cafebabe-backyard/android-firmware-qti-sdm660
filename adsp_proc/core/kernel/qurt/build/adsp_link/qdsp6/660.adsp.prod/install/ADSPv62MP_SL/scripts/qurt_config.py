#=============================================================================
#
#                                    qurt_config.py
#
# GENERAL DESCRIPTION
#
# EXTERNAL FUNCTIONS
#        None.
#
# INITIALIZATION AND SEQUENCING REQUIREMENTS
#        None.
#
#             Copyright (c) 2013  by Qualcomm Technologies, Inc.  All Rights Reserved.
#=============================================================================
#!/usr/bin/env python

class qurt_config:
    def genheader_subcommand(self, arglist):
        from lib.genheader import genheader_cmd
        return genheader_cmd(arglist)
    def genkernel_subcommand(self, arglist):
        from lib.genkernel import genkernel_cmd
        return genkernel_cmd(arglist)
    def update_subcommand(self, arglist):
        from lib.merge import merge_cmd
        return merge_cmd(arglist)
    def usage(self):
        cmds = sorted([z.rsplit('_',1)[0] for z in dir(self) if z.endswith('_subcommand')])
        str = 'First argument must be one of:\n  ' + ', '.join(cmds)
        raise Exception(str)
    def run_command(self, argv):
        from traceback import format_exc as tbstr
        progname = argv[0]
        try:
            print ' '.join(argv)
            raw_args = argv[1:]
            args = [s for s in raw_args if not s == '--traceback']
            if args == raw_args:
                tbstr = None
            try:
                subfunc = getattr(self, '%s_subcommand' % args[0])
            except StandardError:
                self.usage()
            return subfunc(args[1:])
        except (SystemExit, KeyboardInterrupt):
            raise
        except Exception, err:
            if tbstr:
                print tbstr()
            print '%s: Error:\n*** %s' % (progname, err)
        except:
            raise
        return 1
    def main(self):
        import sys
        sys.exit(self.run_command(sys.argv))

def attach_config_vars(cfg):
    #
    #  This function is called by the kernel build procedure
    #   to get access to the configuration variable database.
    #
    import os
    import imp
    lib = imp.load_module('lib',*imp.find_module('lib',[os.path.dirname(__file__)]))
    from lib.genkernel import QurtVars
    QurtVars(cfg)

if __name__ == '__main__':
    qurt_config().main()    # Never returns

# Signatures of the files that this depends on
# a877b492061511b96c315a35adfb0cb1 /local/mnt/workspace/CRMBuilds/ADSP.VT.4.1.c1-00009-SDM660-1_20200317_234851/b/adsp_proc/core/kernel/qurt/build/adsp_link/qdsp6/660.adsp.prod/install/ADSPv62MP_SL/scripts/Input/cust_config_template.c
# 3f114449f7ba834f3d3900584ab8d806 /local/mnt/workspace/CRMBuilds/ADSP.VT.4.1.c1-00009-SDM660-1_20200317_234851/b/adsp_proc/core/kernel/qurt/build/adsp_link/qdsp6/660.adsp.prod/install/ADSPv62MP_SL/scripts/Input/default_build_config.def
# 43a26aebdc1b496c2ed300185d8024c1 /local/mnt/workspace/CRMBuilds/ADSP.VT.4.1.c1-00009-SDM660-1_20200317_234851/b/adsp_proc/core/kernel/qurt/build/adsp_link/qdsp6/660.adsp.prod/install/ADSPv62MP_SL/scripts/Input/static_build_config.def
# 5bdb8cd95cf82507b4b103ed57bad354 /local/mnt/workspace/CRMBuilds/ADSP.VT.4.1.c1-00009-SDM660-1_20200317_234851/b/adsp_proc/core/kernel/qurt/build/adsp_link/qdsp6/660.adsp.prod/install/ADSPv62MP_SL/scripts/Input/qurt_tlb_unlock.xml
# 357936a3e2668e37b2423e69f63511d9 /local/mnt/workspace/CRMBuilds/ADSP.VT.4.1.c1-00009-SDM660-1_20200317_234851/b/adsp_proc/core/kernel/qurt/build/adsp_link/qdsp6/660.adsp.prod/install/ADSPv62MP_SL/scripts/Input/qurt_default.lcs
# 485f49b52fe138e5fc728546f35ccb41 /local/mnt/workspace/CRMBuilds/ADSP.VT.4.1.c1-00009-SDM660-1_20200317_234851/b/adsp_proc/core/kernel/qurt/build/adsp_link/qdsp6/660.adsp.prod/install/ADSPv62MP_SL/scripts/Input/qurt_whitelist.txt
# 82fc44b8836571a8c447b8f56aec59d9 /local/mnt/workspace/CRMBuilds/ADSP.VT.4.1.c1-00009-SDM660-1_20200317_234851/b/adsp_proc/core/kernel/qurt/build/adsp_link/qdsp6/660.adsp.prod/install/ADSPv62MP_SL/scripts/lib/__init__.py
# df95cfea7f7213272a0c81d88cce6d91 /local/mnt/workspace/CRMBuilds/ADSP.VT.4.1.c1-00009-SDM660-1_20200317_234851/b/adsp_proc/core/kernel/qurt/build/adsp_link/qdsp6/660.adsp.prod/install/ADSPv62MP_SL/scripts/lib/basefile.py
# df17614f28c51ab38b54bb1bd381ea97 /local/mnt/workspace/CRMBuilds/ADSP.VT.4.1.c1-00009-SDM660-1_20200317_234851/b/adsp_proc/core/kernel/qurt/build/adsp_link/qdsp6/660.adsp.prod/install/ADSPv62MP_SL/scripts/lib/build_qurt_config.py
# 55dbbf6bfbb4d869adbf951edf632611 /local/mnt/workspace/CRMBuilds/ADSP.VT.4.1.c1-00009-SDM660-1_20200317_234851/b/adsp_proc/core/kernel/qurt/build/adsp_link/qdsp6/660.adsp.prod/install/ADSPv62MP_SL/scripts/lib/build_xml.py
# 952d05c38d72c0f75c1cbf105f489ad1 /local/mnt/workspace/CRMBuilds/ADSP.VT.4.1.c1-00009-SDM660-1_20200317_234851/b/adsp_proc/core/kernel/qurt/build/adsp_link/qdsp6/660.adsp.prod/install/ADSPv62MP_SL/scripts/lib/cfgvars.py
# 1b614f46846760bbbebc471128041064 /local/mnt/workspace/CRMBuilds/ADSP.VT.4.1.c1-00009-SDM660-1_20200317_234851/b/adsp_proc/core/kernel/qurt/build/adsp_link/qdsp6/660.adsp.prod/install/ADSPv62MP_SL/scripts/lib/elf_info_patch.py
# 92948080d10d75e5f94f4777d21bb646 /local/mnt/workspace/CRMBuilds/ADSP.VT.4.1.c1-00009-SDM660-1_20200317_234851/b/adsp_proc/core/kernel/qurt/build/adsp_link/qdsp6/660.adsp.prod/install/ADSPv62MP_SL/scripts/lib/ezxml.py
# 9abba5ff04b9d874acb683fe26123b2b /local/mnt/workspace/CRMBuilds/ADSP.VT.4.1.c1-00009-SDM660-1_20200317_234851/b/adsp_proc/core/kernel/qurt/build/adsp_link/qdsp6/660.adsp.prod/install/ADSPv62MP_SL/scripts/lib/genheader.py
# eda9be7c3853fffca337d5b205c0c3c7 /local/mnt/workspace/CRMBuilds/ADSP.VT.4.1.c1-00009-SDM660-1_20200317_234851/b/adsp_proc/core/kernel/qurt/build/adsp_link/qdsp6/660.adsp.prod/install/ADSPv62MP_SL/scripts/lib/genkernel.py
# c083132b08dbc9fe4f0e2ad37e4cab81 /local/mnt/workspace/CRMBuilds/ADSP.VT.4.1.c1-00009-SDM660-1_20200317_234851/b/adsp_proc/core/kernel/qurt/build/adsp_link/qdsp6/660.adsp.prod/install/ADSPv62MP_SL/scripts/lib/interrupt_xml.py
# 1fa861ccb7f25be1d60859f6c370037c /local/mnt/workspace/CRMBuilds/ADSP.VT.4.1.c1-00009-SDM660-1_20200317_234851/b/adsp_proc/core/kernel/qurt/build/adsp_link/qdsp6/660.adsp.prod/install/ADSPv62MP_SL/scripts/lib/kernel_xml.py
# 4ab754595cd8d1cc58e2a372c9234b28 /local/mnt/workspace/CRMBuilds/ADSP.VT.4.1.c1-00009-SDM660-1_20200317_234851/b/adsp_proc/core/kernel/qurt/build/adsp_link/qdsp6/660.adsp.prod/install/ADSPv62MP_SL/scripts/lib/machine_xml.py
# faa356cf7e46cd1096f7776d4b4e7aea /local/mnt/workspace/CRMBuilds/ADSP.VT.4.1.c1-00009-SDM660-1_20200317_234851/b/adsp_proc/core/kernel/qurt/build/adsp_link/qdsp6/660.adsp.prod/install/ADSPv62MP_SL/scripts/lib/memsection_xml.py
# d5c56c97196c8a756fae305c82631324 /local/mnt/workspace/CRMBuilds/ADSP.VT.4.1.c1-00009-SDM660-1_20200317_234851/b/adsp_proc/core/kernel/qurt/build/adsp_link/qdsp6/660.adsp.prod/install/ADSPv62MP_SL/scripts/lib/merge.py
# 3d5008ec9d0bc9b925dc044210fbdc25 /local/mnt/workspace/CRMBuilds/ADSP.VT.4.1.c1-00009-SDM660-1_20200317_234851/b/adsp_proc/core/kernel/qurt/build/adsp_link/qdsp6/660.adsp.prod/install/ADSPv62MP_SL/scripts/lib/parse_build_params.py
# bd6df427f9ce5c7e75f767ee4df4a1e5 /local/mnt/workspace/CRMBuilds/ADSP.VT.4.1.c1-00009-SDM660-1_20200317_234851/b/adsp_proc/core/kernel/qurt/build/adsp_link/qdsp6/660.adsp.prod/install/ADSPv62MP_SL/scripts/lib/parse_spec.py
# 7f09404895b6db485e8915c27a6a5710 /local/mnt/workspace/CRMBuilds/ADSP.VT.4.1.c1-00009-SDM660-1_20200317_234851/b/adsp_proc/core/kernel/qurt/build/adsp_link/qdsp6/660.adsp.prod/install/ADSPv62MP_SL/scripts/lib/physpool_xml.py
# 1b2b5e6ad0d1b31735166cdc0d119b77 /local/mnt/workspace/CRMBuilds/ADSP.VT.4.1.c1-00009-SDM660-1_20200317_234851/b/adsp_proc/core/kernel/qurt/build/adsp_link/qdsp6/660.adsp.prod/install/ADSPv62MP_SL/scripts/lib/program_xml.py
# fde416f3ce37be6f4265d4b9416f63fd /local/mnt/workspace/CRMBuilds/ADSP.VT.4.1.c1-00009-SDM660-1_20200317_234851/b/adsp_proc/core/kernel/qurt/build/adsp_link/qdsp6/660.adsp.prod/install/ADSPv62MP_SL/scripts/lib/qurt.py
# 8a168a9721a97d6d67c2bd6763cc729c /local/mnt/workspace/CRMBuilds/ADSP.VT.4.1.c1-00009-SDM660-1_20200317_234851/b/adsp_proc/core/kernel/qurt/build/adsp_link/qdsp6/660.adsp.prod/install/ADSPv62MP_SL/scripts/Input/build_params.txt
# a877b492061511b96c315a35adfb0cb1 /local/mnt/workspace/CRMBuilds/ADSP.VT.4.1.c1-00009-SDM660-1_20200317_234851/b/adsp_proc/core/kernel/qurt/build/adsp_link/qdsp6/660.adsp.prod/install/ADSPv62MP_SL/scripts/Input/cust_config.c
# 049d3f93f35872bd7f928dd9f094aacd /local/mnt/workspace/CRMBuilds/ADSP.VT.4.1.c1-00009-SDM660-1_20200317_234851/b/adsp_proc/core/kernel/qurt/build/adsp_link/qdsp6/660.adsp.prod/install/ADSPv62MP_SL/scripts/qurt-image-build.py
# 744095ad105d4490a6adbc21c1fe2530 /local/mnt/workspace/CRMBuilds/ADSP.VT.4.1.c1-00009-SDM660-1_20200317_234851/b/adsp_proc/core/kernel/qurt/build/adsp_link/qdsp6/660.adsp.prod/install/ADSPv62MP_SL/scripts/lib/qurt_consts.py
