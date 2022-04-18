#===========================================================================
#
#  @file hwio_sdm660.py
#  @brief HWIO config file for the HWIO generation scripts for SDM660
#         LPASS.
#
#  This file can be invoked by calling:
#
#    HWIOGen.py --cfg=hwio_sdm660.py --flat=..\..\..\..\..\api\systemdrivers\hwio\sdm660\ARM_ADDRESS_FILE.FLAT
#
#  ===========================================================================
#
#  Copyright (c) 2016 Qualcomm Technologies Incorporated.  
#  All Rights Reserved.
#  QUALCOMM Proprietary and Confidential.
#
#  ===========================================================================
#
#  $Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/hwio/build/sdm660/cdsp/hwio_sdm660.py#1 $
#  $DateTime: 2020/02/10 01:57:30 $
#  $Author: pwbldsvc $
#
#  ===========================================================================

CHIPSET = 'sdm660'
IMAGE = 'cdsp'

# ============================================================================
# HWIO_BASE_FILES
# ============================================================================

bases = [
  # General bases
  'RPM',
  'RPM_SS_MSG_RAM_START_ADDRESS',
  'RPM_SS_MSG_RAM_END_ADDRESS',
  'SPDM_WRAPPER_TOP',
  'MPM2_MPM',
  'PERIPH_SS_PDM_PERPH_WEB',
  'PERIPH_SS_AHB2PHY_WEST',
  'PERIPH_SS_SDC1_SDCC5_TOP',
  'PERIPH_SS_SDC2_SDCC5_TOP',
  'PERIPH_SS_BLSP1_BLSP_XPU3',
  'PMIC_ARB',
  'QDSS_SOC_DBG',
  'CLK_CTL',
  'CONFIG_NOC_WRAPPER',
  'CORE_TOP_CSR',
  'SECURITY_CONTROL',
  'SYSTEM_NOC',
  'TLMM',
  'USB30_PRIM',
  'DDR_SS',
  'PRNG_CFG_PRNG_TOP',

  # CDSP bases
  'TURING',
]

base_resize = {
  'RPM_SS_MSG_RAM_START_ADDRESS':    0x7000,
  'RPM_SS_MSG_RAM_END_ADDRESS':         0x0,
}


HWIO_BASE_FILES = [
  {
    'filename': '../../../../../api/systemdrivers/hwio/' + CHIPSET + '/' + IMAGE + '/msmhwiobase.h',
    'bases': bases,
    'map-type': 'qurt',
    'virtual-address-start': 0xA0000000,
    'virtual-address-end': 0xF0000000,
    'resize': base_resize,
    'qurt-memsection-filename': '../../../../../api/systemdrivers/hwio/' + CHIPSET + '/' + IMAGE + '/msmhwioplat.xml',
    'default-cache-policy': 'uncached',
    'devcfg-filename': '../../../config/' + CHIPSET + '/' + IMAGE + '/HWIOBaseMap.c',
    'check-sizes': True,
    'check-for-overlaps': True,
    
    # We need to manually map the LPASS region because the LPM region
    # which is right in the middle of LPASS needs special cache
    # attributes.  This is handled in the top-level qdsp6.xml file.
    'fixed-virtual-address': { 'TURING': 0xe8000000 },
    'skip-memsection': ['TURING'],
  }
]


# ============================================================================
# HWIO_T32VIEW_FILES
# ============================================================================

HWIO_T32VIEW_FILES = [
  {
    'symbol-filename': '../../../scripts/' + CHIPSET + '/hwio.cmm',
    'limit-array-size': [ 10, 4 ],
    'per-filename': '../../../scripts/' + CHIPSET + '/hwioreg',
    'filter-exclude': ['RESERVED', 'DUMMY']
  },
]


# ============================================================================
# HWIO_REGISTER_FILES
# ============================================================================

HWIO_REGISTER_FILES = [
  {
    'filename': '../../../hw/' + CHIPSET + '/' + IMAGE + '/msmhwioreg.h.ref',
    'bases': bases,
    'filter-exclude': ['RESERVED', 'DUMMY'],
    'header': '''
#error This file is for reference only and cannot be included.  See "go/hwio" or mail corebsp.sysdrv.hwio for help.
'''
  }
]


# ============================================================================
# Main
#
# Entry point when invoking this directly.
# ============================================================================

if __name__ == "__main__":
  from subprocess import Popen
  Popen(["\\\\ben\\corebsp_labdata_0001\\sysdrv\\hwio\\HWIOGen.py", "--cfg=hwio_" + CHIPSET + ".py", "--flat=../../../../../api/systemdrivers/hwio/" + CHIPSET + "/" + IMAGE + "/ARM_ADDRESS_FILE.FLAT"], shell=True)
