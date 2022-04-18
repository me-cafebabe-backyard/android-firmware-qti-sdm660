<driver name="NULL">
   <device id="/pmic/periph">
      <props name="arb_priority_cfg" type=DALPROP_ATTR_TYPE_STRUCT_PTR>
         pm_arb_priorities
      </props>
      <props name="number_priorities" type=DALPROP_ATTR_TYPE_STRUCT_PTR>
         pm_num_prio
      </props>
      <props name="number_pvc_port" type=DALPROP_ATTR_TYPE_STRUCT_PTR>
         pm_num_pvc_port
      </props>
      <props name="pvc_port_cfg" type=DALPROP_ATTR_TYPE_STRUCT_PTR>
         pm_arb_pvc_cfg
      </props>
      <props name="spmi_channel_cfg" type=DALPROP_ATTR_TYPE_STRUCT_PTR>
         pm_spmi_pheriph_cfg
      </props>
      <props name="spmi_channel_cfg_size" type=DALPROP_ATTR_TYPE_STRUCT_PTR>
         pm_spmi_pheriph_cfg_sz
      </props>
      <props name="tz_mpu_rg_cfg" type=DALPROP_ATTR_TYPE_STRUCT_PTR>
       pm_mpu_rg_cfg
      </props>
      <props name="rg_cfg_size" type=DALPROP_ATTR_TYPE_STRUCT_PTR>
        pm_spmi_rg_sz
      </props>
      <props name="pmic_arb_hal_id_xpu" type=DALPROP_ATTR_TYPE_STRUCT_PTR>
         pm_hal_id_xpu
      </props>
      <props name="spmi_rg_config" type=DALPROP_ATTR_TYPE_STRUCT_PTR>
       pm_spmi_rg_cfg
      </props>
   </device>
</driver>
