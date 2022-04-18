# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/systemdrivers/pmic/config/sdm660_pm660/src/pm_spmi_config.xml"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 327 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/systemdrivers/pmic/config/sdm660_pm660/src/pm_spmi_config.xml" 2
# 22 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/systemdrivers/pmic/config/sdm660_pm660/src/pm_spmi_config.xml"
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
