# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/securemsm/trustzone/qsee/mink/oem/config/sdm660/oem_config.xml"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 327 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/securemsm/trustzone/qsee/mink/oem/config/sdm660/oem_config.xml" 2
<driver name="NULL">
  <global_def>

  </global_def>
  <device id="/tz/oem">
    <props name="OEM_keystore_enable_rpmb" type=DALPROP_ATTR_TYPE_UINT32>
      1
    </props>
    <props name="OEM_keystore_wrong_passwd_penalty" type=DALPROP_ATTR_TYPE_UINT32>
      2000
    </props>
    <props name="OEM_keystore_retain_wrong_passwd_attempt" type=DALPROP_ATTR_TYPE_UINT32>
      1
    </props>
    <props name="OEM_counter_enable_rpmb" type=DALPROP_ATTR_TYPE_UINT32>
      1
    </props>

    <!-- Note !!! The OEM_allow_rpmb_key_provision property is used for the below condition only: !!!
      A customer wants to replace the storage part (eMMC/UFS), but since RPMB key provision fuse is blown,
      RPMB auto production key provision wont happen for the new part.
      The return TRUE value can override RPMB key provision fuse and let RPMB be provsioned with
      the new storage part.
      This functions MUST always return FALSE for production devices.
      Otherwise the security of the RPMB will be compromised -->
    <props name="OEM_allow_rpmb_key_provision" type=DALPROP_ATTR_TYPE_UINT32>
      0
    </props>

    <props name="OEM_disable_rpmb_autoprovisioning" type=DALPROP_ATTR_TYPE_UINT32>
      0
    </props>
    <props name="OEM_sec_wdog_bark_time" type="0x00000002">
      6000
    </props>
    <props name="OEM_sec_wdog_bite_time" type=DALPROP_ATTR_TYPE_UINT32>
      22000
    </props>
    <props name="OEM_reset_reason_list" type=DALPROP_ATTR_TYPE_STRUCT_PTR>
      oem_rst_reason_list
    </props>
    <props name="OEM_l2_wa_enable" type="0x00000002">
    1
    </props>

    <!-- PIL load region information -->
    <props name="OEM_pil_secure_app_load_region_size" type=DALPROP_ATTR_TYPE_UINT32>
      0x02200000
    </props>
    <props name="OEM_pil_subsys_load_region_start" type=DALPROP_ATTR_TYPE_UINT32>
      0x8AC00000
    </props>
    <props name="OEM_pil_subsys_load_region_size" type=DALPROP_ATTR_TYPE_UINT32>
      0xA400000
    </props>
    <props name="OEM_pil_enable_clear_pil_region" type=DALPROP_ATTR_TYPE_UINT32>
      0
    </props>

    <!--
 <props name="oem_spare_region26_read_vmid" type=DALPROP_ATTR_TYPE_UINT32>
      0x10000000
    </props>
 <props name="oem_spare_region26_write_vmid" type=DALPROP_ATTR_TYPE_UINT32>
      0x10000000
    </props>

 <props name="oem_spare_region27_read_vmid" type=DALPROP_ATTR_TYPE_UINT32>
      0x10000000
    </props>
 <props name="oem_spare_region27_write_vmid" type=DALPROP_ATTR_TYPE_UINT32>
      0x10000000
    </props>

 <props name="oem_spare_region28_read_vmid" type=DALPROP_ATTR_TYPE_UINT32>
      0x10000000
    </props>
 <props name="oem_spare_region28_write_vmid" type=DALPROP_ATTR_TYPE_UINT32>
      0x10000000
    </props>
 <props name="oem_spare_region29_read_vmid" type=DALPROP_ATTR_TYPE_UINT32>
      0x10000000
    </props>
 <props name="oem_spare_region29_write_vmid" type=DALPROP_ATTR_TYPE_UINT32>
      0x10000000
    </props>
 <props name="oem_spare_region30_read_vmid" type=DALPROP_ATTR_TYPE_UINT32>
      0x10000000
    </props>
 <props name="oem_spare_region30_write_vmid" type=DALPROP_ATTR_TYPE_UINT32>
      0x10000000
    </props>
  -->

    <!-- Mark 3rd party signed secure applications sandboxed by default -->
    <props name="OEM_app_sandbox_default" type=DALPROP_ATTR_TYPE_UINT32>
      1
    </props>

        <!-- Mark 3rd party signed secure applications sandboxed by default -->
    <props name="OEM_enablecrashdumps_before_arb" type=DALPROP_ATTR_TYPE_UINT32>
      0
    </props>
    <!-- Enable TZ counter measure for hlos boot tampering -->
    <props name="OEM_counter_measure_enable" type=DALPROP_ATTR_TYPE_UINT32>
      1
   </props>
  </device>

  <device id="eseservice">
    <!-- Embedded Secure Element information information -->
    <props name="OEM_ese_spi_device_id" type=DALPROP_ATTR_TYPE_UINT32>
      0x00 <!--The SPI device ID which maps on to the BLSP QUP core use -->
    </props>
    <props name="OEM_ese_spi_chip_select_id" type=DALPROP_ATTR_TYPE_UINT32>
      0x00 <!--The Chip Select index (0 to 3) on with Secure Element is connected -->
    </props>
    <props name="OEM_ese_spi_max_frequency" type=DALPROP_ATTR_TYPE_UINT32>
      9600000 <!-- SPI clock frequency as detailed in the Secure Element T=1 specification -->
    </props>
    <props name="OEM_ese_spi_bits_per_word" type=DALPROP_ATTR_TYPE_UINT32>
      8 <!--The bits per word transmitted from/to the Interface device over SPI -->
    </props>
    <props name="OEM_ese_spi_nad_command" type=DALPROP_ATTR_TYPE_UINT32>
      0x5A <!-- NAD for commands to Secure Element. Should be changed to 0x00 for NQ220 -->
    </props>
    <props name="OEM_ese_spi_nad_response" type=DALPROP_ATTR_TYPE_UINT32>
      0xA5 <!-- NAD for responses from the secure element -->
    </props>
    <props name="OEM_ese_feature_mask" type=DALPROP_ATTR_TYPE_UINT32>
      <!-- 0x00000001 - Enable QSEE Secure Element Access Control -->
      <!-- 0x00000002 - Enable QSEE Secure Element Access Control APDU Filtering -->
      <!-- 0x00000004 - Allow SELECT Command for GP TEE SE API TEE_SEChannelTransmit -->
      <!-- 0x00000008 - Support for SPI Soft Reset of ESE -->
      <!-- 0x00000010 - Support sending SPI end of APDU session command -->
      <!-- 0x00000020 - Block access to Secure Element basic channel -->
      <!-- 0x00000040 - Block access to Secure Element default applet -->
      <!-- 0x00000080 - Use multi-byte NAD when polling for response -->
      <!-- 0xFFFFFFFF - All features mask -->
      0x00000000
    </props>
    <props name="OEM_ese_timers" type=DALPROP_ATTR_TYPE_UINT32>
      <!-- 0x000007FF - Mask for Secure Element BWT - 1624ms maximum -->
      <!-- 0x003FF000 - Mask for Secure Element Response polling time - default 50ms -->
      0x00032658
    </props>

 <props name="OEM_kdf_app_key_workaround" type=DALPROP_ATTR_TYPE_UINT32>
 <!-- 0 - suppport for lowercase letters for app id -->
 <!-- 1 - suppport app id backward compatability -->
      0
     </props>
  </device>

</driver>
