# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/securemsm/trustzone/qsee/mink/oem/config/common/kdf_fix_oem_config.xml"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 327 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/securemsm/trustzone/qsee/mink/oem/config/common/kdf_fix_oem_config.xml" 2
<driver name="NULL">

  <device id="/tz/oem/kdf_fix">

<!--
  OEM configurable fix for KDF issue
  where in-place key derivation results in
  reducing key strength. Enabling the fix will break
  backward compatibility for the features which depend
  on KDF key derived from stored persistent key (e.g. OTA
  update when FDE is enable)
  0: Disables KDF fix
  1: Enables KDF fix
-->
    <props name="is_kdf_fix_enable" type=DALPROP_ATTR_TYPE_UINT32>
      1
    </props>

  </device>
</driver>
