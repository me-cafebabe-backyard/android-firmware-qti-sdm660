# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/securemsm/trustzone/qsee/mink/oem/config/common/keymaster_oem_config.xml"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 327 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/securemsm/trustzone/qsee/mink/oem/config/common/keymaster_oem_config.xml" 2
<driver name="NULL">

  <global_def>

    <var_seq name="fpta_name_str" type=DALPROP_DATA_TYPE_STRING>
      fingerprint
    </var_seq>
    <var_seq name="fp_sensor_name_str" type=DALPROP_DATA_TYPE_STRING>
      Stargate
    </var_seq>
    <var_seq name="irista_name_str" type=DALPROP_DATA_TYPE_STRING>
      iris
    </var_seq>

  </global_def>

  <device id="keymaster">

    <props name="fpta_name" type=DALPROP_ATTR_TYPE_STRING_PTR>
      fpta_name_str
    </props>
<!--
    OEM specific requirement for GK Retry Timeout, default is 0.
-->
    <props name="gk_timeout_config" type=DALPROP_ATTR_TYPE_UINT32>
      0
    </props>
    <props name="fp_sensor_name" type=DALPROP_ATTR_TYPE_STRING_PTR>
      fp_sensor_name_str
    </props>
    <props name="fp_sensor_version" type=DALPROP_ATTR_TYPE_UINT32>
      1
    </props>
    <props name="enable_finger_id" type=DALPROP_ATTR_TYPE_UINT32>
      0
    </props>
    <props name="enable_soter" type=DALPROP_ATTR_TYPE_UINT32>
      0
    </props>
    <props name="irista_name" type=DALPROP_ATTR_TYPE_STRING_PTR>
      irista_name_str
    </props>

  </device>

    <device id="keymaster64">

    <props name="fpta_name" type=DALPROP_ATTR_TYPE_STRING_PTR>
      fpta_name_str
    </props>
<!--
    OEM specific requirement for GK Retry Timeout, default is 0.
-->
    <props name="gk_timeout_config" type=DALPROP_ATTR_TYPE_UINT32>
      0
    </props>
    <props name="gk_enable_soter_test" type=DALPROP_ATTR_TYPE_UINT32>
     0
    </props>
    <props name="fp_sensor_name" type=DALPROP_ATTR_TYPE_STRING_PTR>
      fp_sensor_name_str
    </props>
    <props name="fp_sensor_version" type=DALPROP_ATTR_TYPE_UINT32>
      1
    </props>
    <props name="enable_finger_id" type=DALPROP_ATTR_TYPE_UINT32>



      0

    </props>
    <props name="enable_soter" type=DALPROP_ATTR_TYPE_UINT32>



      0

    </props>
    <props name="irista_name" type=DALPROP_ATTR_TYPE_STRING_PTR>
      irista_name_str
    </props>
    <props name="allow_reprovision" type=DALPROP_ATTR_TYPE_UINT32>
      0
    </props>

  </device>
</driver>
