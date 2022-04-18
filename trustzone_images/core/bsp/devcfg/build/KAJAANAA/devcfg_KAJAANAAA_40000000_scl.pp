# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/bsp/devcfg/build/KAJAANAA/devcfg_data_dynamic.ld"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 334 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/bsp/devcfg/build/KAJAANAA/devcfg_data_dynamic.ld" 2








# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/build/cust/customer.h" 1
# 80 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/build/cust/customer.h"
# 1 "./custkajaanaaa.h" 1
# 10 "./custkajaanaaa.h"
# 1 "./targkajaanaaa.h" 1
# 11 "./custkajaanaaa.h" 2
# 144 "./custkajaanaaa.h"
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/build/cust/custremoteapis.h" 1
# 145 "./custkajaanaaa.h" 2
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/build/cust/custtarget.h" 1
# 146 "./custkajaanaaa.h" 2
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/build/cust/custsdcc.h" 1
# 147 "./custkajaanaaa.h" 2
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/build/cust/custsurf.h" 1
# 148 "./custkajaanaaa.h" 2
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/build/cust/custdiag.h" 1
# 149 "./custkajaanaaa.h" 2
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/build/cust/custefs.h" 1
# 150 "./custkajaanaaa.h" 2
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/build/cust/custpmic.h" 1
# 151 "./custkajaanaaa.h" 2
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/build/cust/custsio_8660.h" 1
# 152 "./custkajaanaaa.h" 2
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/build/cust/custsec.h" 1
# 121 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/build/cust/custsec.h"
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/build/cust/custsfs.h" 1
# 122 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/build/cust/custsec.h" 2
# 153 "./custkajaanaaa.h" 2
# 81 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/build/cust/customer.h" 2
# 10 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/bsp/devcfg/build/KAJAANAA/devcfg_data_dynamic.ld" 2

PHDRS {
  DEVCFG_DATA_SEG_TZ PT_LOAD;
  DEVCFG_DATA_SEG_HYP PT_LOAD;
}
SECTIONS {

   DEVCFG_DATA_TZ ((0x1C000000 + 0x1E8000)):
   {
      KEEP(*\DevCfgSegInfo_oem_tz.o (.rodata* .data* .sdata*))
      KEEP(*\660_data_oem_tz.o (.rodata* .data* .sdata*))
      KEEP(*\DevCfg_660_oem_tz.o (.rodata* .data* .sdata*))
      KEEP(*\660_devcfg_reset_reason_oem_map.o (.rodata* .data* .sdata*))
      KEEP(*\660_devcfg_ABT_OEM_data.o (.rodata* .data* .sdata*))
      KEEP(*\660_devcfg_BIMC_error_OEM_data.o (.rodata* .data* .sdata*))
      KEEP(*\660_devcfg_NOC_error_OEM_data.o (.rodata* .data* .sdata*))
      KEEP(*\660_devcfg_pm_spmi_config.o (.rodata* .data* .sdata*))
      KEEP(*\660_devcfg_pm_reg_dump_config.o (.rodata* .data* .sdata*))
      KEEP(*\660_devcfg_pm_config.o (.rodata* .data* .sdata*))
      KEEP(*\660_devcfg_pm_ac_config.o (.rodata* .data* .sdata*))
      KEEP(*\660_devcfg_pm_tz_config.o (.rodata* .data* .sdata*))
      ASSERT(SIZEOF(DEVCFG_DATA_TZ) <= 0xA000, "Oversize");
   }:DEVCFG_DATA_SEG_TZ

   DEVCFG_DATA_HYP (0x85DFD000):
   {
      KEEP(*\DevCfgSegInfo_oem_hyp.o (.rodata* .data* .sdata*))
      KEEP(*\DevCfgSegInfo_660_oem_hyp.o (.rodata* .data* .sdata*))
      KEEP(*\660_data_oem_hyp.o (.rodata* .data* .sdata*))
      KEEP(*\DevCfg_660_oem_hyp.o (.rodata* .data* .sdata*))
      KEEP(*\660_devcfg_pm_hyp_config.o (.rodata* .data* .sdata*))
      ASSERT(SIZEOF(DEVCFG_DATA_HYP) <= 0x3000, "Oversize");
     }:DEVCFG_DATA_SEG_HYP

  .got : { * (.got) }
  .got.plt : { * (.got.plt) }
  .debug 0 : { *(.debug) }
  .line 0 : { *(.line) }

  .debug_srcinfo 0 : { *(.debug_srcinfo) }
  .debug_sfnames 0 : { *(.debug_sfnames) }

  .debug_aranges 0 : { *(.debug_aranges) }
  .debug_pubnames 0 : { *(.debug_pubnames) }

  .debug_info 0 : { *(.debug_info .gnu.linkonce.wi.*) }
  .debug_abbrev 0 : { *(.debug_abbrev) }
  .debug_line 0 : { *(.debug_line) }
  .debug_frame 0 : { *(.debug_frame) }
  .debug_str 0 : { *(.debug_str) }
  .debug_loc 0 : { *(.debug_loc) }
  .debug_macinfo 0 : { *(.debug_macinfo) }

  .debug_weaknames 0 : { *(.debug_weaknames) }
  .debug_funcnames 0 : { *(.debug_funcnames) }
  .debug_typenames 0 : { *(.debug_typenames) }
  .debug_varnames 0 : { *(.debug_varnames) }

  .debug_pubtypes 0 : { *(.debug_pubtypes) }
  .debug_ranges 0 : { *(.debug_ranges) }
  .gnu.attributes 0 : { KEEP (*(.gnu.attributes)) }
  .note.gnu.arm.ident 0 : { KEEP (*(.note.gnu.arm.ident)) }
  /DISCARD/ : { *(.ARM.exidx*) *(.note.GNU-stack) *(.gnu_debuglink) *(.gnu.lto_*) *(.init) *(.fini)}
}
