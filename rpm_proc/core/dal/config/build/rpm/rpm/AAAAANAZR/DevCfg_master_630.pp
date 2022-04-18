# 1 "/local/mnt/workspace/CRMBuilds/RPM.BF.1.8-00067-SDM660AAAAANAZR-1_20200203_034924/b/rpm_proc/core/dal/config/build/rpm/rpm/AAAAANAZR/DevCfg_master_630.xml"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 324 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "/local/mnt/workspace/CRMBuilds/RPM.BF.1.8-00067-SDM660AAAAANAZR-1_20200203_034924/b/rpm_proc/core/dal/config/build/rpm/rpm/AAAAANAZR/DevCfg_master_630.xml" 2
# 1 "/local/mnt/workspace/CRMBuilds/RPM.BF.1.8-00067-SDM660AAAAANAZR-1_20200203_034924/b/rpm_proc/core/api/dal/DALPropDef.h" 1
# 2 "/local/mnt/workspace/CRMBuilds/RPM.BF.1.8-00067-SDM660AAAAANAZR-1_20200203_034924/b/rpm_proc/core/dal/config/build/rpm/rpm/AAAAANAZR/DevCfg_master_630.xml" 2
# 1 "/local/mnt/workspace/CRMBuilds/RPM.BF.1.8-00067-SDM660AAAAANAZR-1_20200203_034924/b/rpm_proc/core/api/dal/DALDeviceId.h" 1
# 3 "/local/mnt/workspace/CRMBuilds/RPM.BF.1.8-00067-SDM660AAAAANAZR-1_20200203_034924/b/rpm_proc/core/dal/config/build/rpm/rpm/AAAAANAZR/DevCfg_master_630.xml" 2
# 1 "/local/mnt/workspace/CRMBuilds/RPM.BF.1.8-00067-SDM660AAAAANAZR-1_20200203_034924/b/rpm_proc/core/dal/config/dalconfig.h" 1
# 4 "/local/mnt/workspace/CRMBuilds/RPM.BF.1.8-00067-SDM660AAAAANAZR-1_20200203_034924/b/rpm_proc/core/dal/config/build/rpm/rpm/AAAAANAZR/DevCfg_master_630.xml" 2

<?xml version="1.0"?>
<dal>
<module name="rpm">

<!--
-->
<driver name="NULL">
  <device id="/dev/core/mproc/glink/ssr">
    <props name="config" type=0x00000012>
      glink_ssr_devcfg_config
    </props>
  </device>
</driver>

<!--
-->
<driver name="NULL">
  <device id="/dev/core/mproc/glink/xport_rpm">
    <props name="proc_info" type=0x00000012>
      xport_rpm_devcfg_proc_info
    </props>
    <props name="remote_procs" type=0x00000012>
      xport_rpm_devcfg_remote_procs
    </props>
    <props name="toc" type=0x00000012>
      xport_rpm_devcfg_toc
    </props>
  </device>
</driver>

<!--
-->
<driver name="NULL">
  <global_def>
    <var_seq name="core_top_csr_str" type=0x00000001>
      CORE_TOP_CSR
    </var_seq>
    <var_seq name="mutex_offsets_data" type=0x00000003>
      ((0x00040000) + 0x00000000 + 0x1000 * (0)),
      ((0x00040000) + 0x00000000 + 0x1000 * (1)),
      ((0x00040000) + 0x00000000 + 0x1000 * (2)),
      ((0x00040000) + 0x00000000 + 0x1000 * (3)),
      ((0x00040000) + 0x00000000 + 0x1000 * (4)),
      ((0x00040000) + 0x00000000 + 0x1000 * (5)),
      ((0x00040000) + 0x00000000 + 0x1000 * (6)),
      ((0x00040000) + 0x00000000 + 0x1000 * (7)),
      end
    </var_seq>
    <var_seq name="wonce_offsets_data" type=0x00000003>
      ((0x000c0000) + 0x00014000 + 0x4 * (0)),
      ((0x000c0000) + 0x00014000 + 0x4 * (1)),
      end
    </var_seq>
  </global_def>
  <device id="/dev/core/mproc/smem">
    <!-- tcsr_base_name, which is TCSR base name used to get
         the virtual address -->
    <props name="tcsr_base_name" type=0x00000011>
      core_top_csr_str
    </props>
    <!-- tcsr_base, TCSR base physical address -->
    <props name="tcsr_base" type=0x00000002>
      0x01F00000
    </props>
    <props name="mutex_offsets" type=0x00000014>
      mutex_offsets_data
    </props>
    <props name="wonce_offsets" type=0x00000014>
      wonce_offsets_data
    </props>
  </device>
</driver>

<driver name="icb_rpm">
   <global_def>
   </global_def>
   <device id="/dev/icb/rpm">
     <props name="system" type=0x00000012>
        icb_rpm_system
     </props>
   </device>
</driver>

<driver name="Timetick">
  <device id=0x0200009B>
     <props name="DEFAULT_FREQUENCY" type=0x00000002>
       19200000
     </props>
     <props name="QTIMER_AC_BASE" type=0x00000002>
       0x00082000
     </props>
     <props name="QTIMER_BASE" type=0x00000002>
       0x00084000
     </props>
  </device>
</driver>

</module>
</dal>
