# 1 "/local/mnt/workspace/CRMBuilds/RPM.BF.1.8-00067-SDM660AAAAANAZR-1_20200203_034924/b/rpm_proc/core/mproc/smem/config/smem_devcfg_sdm660.xml"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 324 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "/local/mnt/workspace/CRMBuilds/RPM.BF.1.8-00067-SDM660AAAAANAZR-1_20200203_034924/b/rpm_proc/core/mproc/smem/config/smem_devcfg_sdm660.xml" 2
<!--
# 23 "/local/mnt/workspace/CRMBuilds/RPM.BF.1.8-00067-SDM660AAAAANAZR-1_20200203_034924/b/rpm_proc/core/mproc/smem/config/smem_devcfg_sdm660.xml"
-->







<driver name="NULL">
  <global_def>
    <var_seq name="core_top_csr_str" type=DALPROP_DATA_TYPE_STRING>
      CORE_TOP_CSR
    </var_seq>

    <var_seq name="mutex_offsets_data" type=DALPROP_DATA_TYPE_UINT32_SEQ>
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

    <var_seq name="wonce_offsets_data" type=DALPROP_DATA_TYPE_UINT32_SEQ>
      ((0x000c0000) + 0x00014000 + 0x4 * (0)),
      ((0x000c0000) + 0x00014000 + 0x4 * (1)),
      end
    </var_seq>

  </global_def>

  <device id="/dev/core/mproc/smem">

    <!-- tcsr_base_name, which is TCSR base name used to get
         the virtual address -->
    <props name="tcsr_base_name" type=DALPROP_ATTR_TYPE_STRING_PTR>
      core_top_csr_str
    </props>

    <!-- tcsr_base, TCSR base physical address -->
    <props name="tcsr_base" type=DALPROP_ATTR_TYPE_UINT32>
      0x01F00000
    </props>

    <props name="mutex_offsets" type=DALPROP_ATTR_TYPE_UINT32_SEQ_PTR>
      mutex_offsets_data
    </props>

    <props name="wonce_offsets" type=DALPROP_ATTR_TYPE_UINT32_SEQ_PTR>
      wonce_offsets_data
    </props>

  </device>
</driver>
