<!--
-->
<driver name="NULL">
  <device id="/dev/core/mproc/glink/xport_rpm">
    <props name="proc_info" type=DALPROP_ATTR_TYPE_STRUCT_PTR>
      xport_rpm_devcfg_proc_info
    </props>
    <props name="remote_procs" type=DALPROP_ATTR_TYPE_STRUCT_PTR>
      xport_rpm_devcfg_remote_procs
    </props>
    <props name="toc" type=DALPROP_ATTR_TYPE_STRUCT_PTR>
      xport_rpm_devcfg_toc
    </props>
  </device>
</driver>
