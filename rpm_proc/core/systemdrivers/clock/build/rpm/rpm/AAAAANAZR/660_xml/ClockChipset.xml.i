<driver name="Clock">
   <device id=DALDEVICEID_CLOCK>
      <!-- Clock sources -->
      <props name="ClockSources" type=DALPROP_ATTR_TYPE_STRUCT_PTR>
        SourceConfig
      </props>
      <!-- RPM Clocks -->
      <props name="gcc_rpm_proc_hclk" type=DALPROP_ATTR_TYPE_STRUCT_PTR>
        RPMClockConfig
      </props>
      <!-- System NOC Clocks -->
      <props name="gcc_sys_noc_axi_clk" type=DALPROP_ATTR_TYPE_STRUCT_PTR>
        SystemNOCClockConfig
      </props>
     <!-- Aggre2NOC Clocks -->
      <props name="gcc_aggre2_snoc_axi_clk" type=DALPROP_ATTR_TYPE_STRUCT_PTR>
        SystemNOCClockConfig
      </props>
     <!-- System NOC Clocks -->
     <props name="gcc_sys_noc_pimem_axi_clk" type=DALPROP_ATTR_TYPE_STRUCT_PTR>
       PIMEMClockConfig
     </props>
     <!-- System NOC HS Clocks -->
     <props name="gcc_sys_noc_hs_axi_clk" type=DALPROP_ATTR_TYPE_STRUCT_PTR>
       SYSNOCHSAXIClockConfig
     </props>
     <!-- Config NOC Clocks -->
      <props name="gcc_cfg_noc_ahb_clk" type=DALPROP_ATTR_TYPE_STRUCT_PTR>
        ConfigNOCClockConfig
      </props>
      <!-- Peripheral NOC Clocks -->
      <props name="gcc_cnoc_periph_north_ahb_clk" type=DALPROP_ATTR_TYPE_STRUCT_PTR>
        PeriphNOCClockConfig
      </props>
     <!-- QDSS ATBA Clocks -->
      <props name="gcc_sys_noc_at_clk" type=DALPROP_ATTR_TYPE_STRUCT_PTR>
        QDSSATBAClockConfig
      </props>
     <!-- QDSS ATBB Clocks -->
      <props name="gcc_bimc_at_clk" type=DALPROP_ATTR_TYPE_STRUCT_PTR>
        QDSSATBBClockConfig
      </props>
     <!-- QDSS ATBC Clocks -->
      <props name="gcc_lpass_at_clk" type=DALPROP_ATTR_TYPE_STRUCT_PTR>
        QDSSATBCClockConfig
      </props>
      <!-- QDSS Trace Clocks -->
      <props name="gcc_qdss_traceclkin_clk" type=DALPROP_ATTR_TYPE_STRUCT_PTR>
        QDSSTraceClockConfig
      </props>
      <!-- QDSS STM Clocks -->
      <props name="gcc_qdss_stm_clk" type=DALPROP_ATTR_TYPE_STRUCT_PTR>
        QDSSSTMClockConfig
      </props>
      <!-- QDSS TSCTR Div2 Clocks -->
      <props name="gcc_qdss_tsctr_div2_clk" type=DALPROP_ATTR_TYPE_STRUCT_PTR>
        QDSSTSCTRDiv2ClockConfig
      </props>
      <!-- QDSS Trig Clocks -->
      <props name="gcc_qdss_trig_clk" type=DALPROP_ATTR_TYPE_STRUCT_PTR>
        QDSSAPBTRIGClockConfig
      </props>
      <!-- IPA Clocks -->
      <props name="gcc_ipa_clk" type=DALPROP_ATTR_TYPE_STRUCT_PTR>
        IPAClockConfig
      </props>
      <!-- CE1 Clocks -->
      <props name="gcc_ce1_clk" type=DALPROP_ATTR_TYPE_STRUCT_PTR>
        CEClockConfig
      </props>
      <!-- SPMI AHB Clocks -->
      <props name="gcc_spmi_ahb_clk" type=DALPROP_ATTR_TYPE_STRUCT_PTR>
        SPMIAHBClockConfig
      </props>
      <!-- SPMI SER Clocks -->
      <props name="gcc_spmi_ser_clk" type=DALPROP_ATTR_TYPE_STRUCT_PTR>
        SPMISERClockConfig
      </props>
      <!-- HMSS AHB Clocks -->
      <props name="gcc_hmss_ahb_clk" type=DALPROP_ATTR_TYPE_STRUCT_PTR>
        HMSSAHBClockConfig
      </props>
     <!-- VSense VDDA Clocks -->
     <props name="gcc_vdda_vs_clk" type=DALPROP_ATTR_TYPE_STRUCT_PTR>
       VSenseClockConfig
     </props>
     <!-- VSense VDD Cx Clocks -->
     <props name="gcc_vddcx_vs_clk" type=DALPROP_ATTR_TYPE_STRUCT_PTR>
       VSenseClockConfig
     </props>
     <!-- VSense VDD Mx Clocks -->
     <props name="gcc_vddmx_vs_clk" type=DALPROP_ATTR_TYPE_STRUCT_PTR>
       VSenseClockConfig
     </props>
     <!-- VSense VDD MSS Clocks -->
     <props name="gcc_mss_vs_clk" type=DALPROP_ATTR_TYPE_STRUCT_PTR>
       VSenseClockConfig
     </props>
     <!-- MMSS NOC AXI Clocks -->
     <props name="mmss_mnoc_axi_clk" type=DALPROP_ATTR_TYPE_STRUCT_PTR>
       MMSSAXIClockConfig
     </props>
     <!-- Clock Log Defaults -->
      <props name="ClockLogDefaults" type=DALPROP_ATTR_TYPE_STRUCT_PTR>
        ClockLogDefaultConfig
      </props>
   </device>
</driver>
