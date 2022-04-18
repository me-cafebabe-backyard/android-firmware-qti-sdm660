#===========================================================================
#  Copyright (c) 2016-2019 Qualcomm Technologies Incorporated.
#  All Rights Reserved.
#  Qualcomm Confidential and Proprietary
#===========================================================================

#initialize empty dict
app_params_dict = dict()

# Initialize parameters for aptcryptotestapp
def addParams(app_name, app_dict):
  app_params_dict[app_name] = dict()
  app_params_dict[app_name] = app_dict

# Load the Secure app builder in the environment
def callInit(env, app_dict):

  env.InitImageVars(
    alias_list = app_dict['aliases'] + ['all'],
    proc = app_dict['arch'],
    config = 'apps',
    build_tags = app_dict['tags'] + ['APPS_PROC']
  )
  libs_path = '${BUILD_ROOT}/apps/bsp/trustzone/build/'
  env.Replace(INSTALL_PATH_FOR_LIBS = env.subst(libs_path))
  #this can be used by the library to identify the app name in cleanpack
  env.Replace(APP_NAME = app_dict['aliases'][0])
  #this allows the apps to use their own name in cleanpack
  env[app_dict['aliases'][0]] = app_dict
  # load the psuedo builder - secure_app_builder
  env.LoadToolScript('${BUILD_ROOT}/core/bsp/build/scripts/secure_app_builder.py')
  env.InitBuildConfig()



#======================================================
# aptcrytpotestapp
aptcryptotestapp_dict = {
  'aliases' : ['aptcryptotestapp','aptcryptotestapp64'],
  'arch' : 'scorpion',
  'tags' : ['APTCRYPTOTESTAPP_IMAGE'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/aptcryptotestapp/src/SConscript',
}
addParams('aptcryptotestapp', aptcryptotestapp_dict)
#======================================================
# aptcrytpotestapp64
aptcryptotestapp64_dict = {
  'aliases' : ['aptcryptotestapp64'],
  'arch' : 'A53_64',
  'tags' : ['APTCRYPTOTESTAPP64_IMAGE'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/aptcryptotestapp/src/SConscript',
}
addParams('aptcryptotestapp64', aptcryptotestapp64_dict)

#======================================================
# aptlksecapp
aptlksecapp_dict = {
  'aliases' : ['aptlksecapp', 'aptlksecapp64'],
  'arch' : 'scorpion',
  'tags' : ['APTLKSECAPP_IMAGE'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/aptlksecapp/src/SConscript',
}
addParams('aptlksecapp', aptlksecapp_dict)
#======================================================
# aptlksecapp64
aptlksecapp64_dict = {
  'aliases' : ['aptlksecapp64'],
  'arch' : 'A53_64',
  'tags' : ['APTLKSECAPP64_IMAGE'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/aptlksecapp/src/SConscript',
}
addParams('aptlksecapp64', aptlksecapp64_dict)


#======================================================
# apttestapp
apttestapp_dict = {
  'aliases' : ['apttestapp', 'apttestapp64'],
  'arch' : 'scorpion',
  'tags' : ['APTTESTAPP_IMAGE'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/apttestapp/src/SConscript',
}
addParams('apttestapp', apttestapp_dict)
#======================================================
# apttestapp64
apttestapp64_dict = {
  'aliases' : ['apttestapp64'],
  'arch' : 'A53_64',
  'tags' : ['APTTESTAPP64_IMAGE'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/apttestapp/src/SConscript',
}
addParams('apttestapp64', apttestapp64_dict)

#======================================================
# assurancetest
assurancetest_dict = {
  'aliases' : ['assurancetest', 'assurancetest64'],
  'arch' : 'scorpion',
  'tags' : ['ASSURANCETEST_IMAGE'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/assurancetest/src/SConscript',
}
addParams('assurancetest', assurancetest_dict)
#======================================================
# assurancetest64
assurancetest64_dict = {
  'aliases' : ['assurancetest64'],
  'arch' : 'A53_64',
  'tags' : ['ASSURANCETEST64_IMAGE'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/assurancetest/src/SConscript',
}
addParams('assurancetest64', assurancetest64_dict)

#======================================================
# cpsbtest
cpsbtest_dict = {
  'aliases' : ['cpsbtest'],
  'arch' : 'scorpion',
  'tags' : ['CPSBTEST_IMAGE'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/cpsbtest/src/SConscript',
}
addParams('cpsbtest', cpsbtest_dict)
#======================================================
# cpsbtest64
cpsbtest64_dict = {
  'aliases' : ['cpsbtest64'],
  'arch' : 'A53_64',
  'tags' : ['CPSBTEST64_IMAGE'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/cpsbtest/src/SConscript',
}
addParams('cpsbtest64', cpsbtest64_dict)

#======================================================
# celerity
celerity_dict = {
  'aliases' : ['celerity', 'celerity64'],
  'arch' : 'scorpion',
  'tags' : ['CELERITY_IMAGE'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/celerity/SConscript',
}
addParams('celerity', celerity_dict)

#======================================================
# celerity64
celerity64_dict = {
  'aliases' : ['celerity64'],
  'arch' : 'A53_64',
  'tags' : ['CELERITY64_IMAGE'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/celerity/SConscript',
}
addParams('celerity64', celerity64_dict)

#======================================================
# crikeymgmtapp
crikeymgmt_dict = {
  'aliases' : ['crikeymgmtapp'],
  'arch' : 'scorpion',
  'tags' : ['CRIKEYMGMTAPP_IMAGE'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/CRIKeyMgmtApp/src/SConscript',
}
addParams('crikeymgmtapp', crikeymgmt_dict)

#======================================================
# crikeymgmtapp64
crikeymgmt64_dict = {
  'aliases' : ['crikeymgmtapp64'],
  'arch' : 'A53_64',
  'tags' : ['CRIKEYMGMTAPP64_IMAGE'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/CRIKeyMgmtApp/src/SConscript',
}
addParams('crikeymgmtapp64', crikeymgmt64_dict)

#======================================================
# dhsecapp aka devicehealth
dhsecapp_dict = {
  'aliases' : ['dhsecapp'],
  'arch' : 'A53_64',
  'tags' : ['DHSECAPP_IMAGE'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/devicehealth/src/SConscript',
}
addParams('dhsecapp', dhsecapp_dict)

#======================================================
# drmtestapp
drmtestapp_dict = {
  'aliases' : ['drmtestapp'],
  'arch' : 'A53_64',
  'tags' : ['DRMTESTAPP_IMAGE'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/drmtestapp/src/SConscript',
}
addParams('drmtestapp', drmtestapp_dict)

#======================================================
# rtic_test - test app for dhsecapp aka devicehealth
# Should not be released externally
rtic_test_dict = {
  'aliases' : ['rtic_test'],
  'arch' : 'A53_64',
  'tags' : ['RTIC_TEST_IMAGE'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/rtic_test/src/SConscript',
}
addParams('rtic_test', rtic_test_dict)

#======================================================
# dxhdcp2
dxhdcp2_dict = {
  'aliases' : ['dxhdcp2'],
  'arch' : 'A53_64',
  'tags' : ['DXHDCP2_IMAGE'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/dxhdcp2/src/SConscript',
}
addParams('dxhdcp2', dxhdcp2_dict)

#======================================================
# dxhdcp2dbg
dxhdcp2dbg_dict = {
  'aliases' : ['dxhdcp2dbg'],
  'arch' : 'A53_64',
  'tags' : ['DXHDCP2DBG_IMAGE'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/dxhdcp2dbg/src/SConscript',
}
addParams('dxhdcp2dbg', dxhdcp2dbg_dict)

#======================================================
# chamomile
chamomile_dict = {
  'aliases' : ['chamomile'],
  'arch' : 'A53_64',
  'tags' : ['CHAMOMILE_IMAGE'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/chamomile/app/src/SConscript',
}
addParams('chamomile', chamomile_dict)

#======================================================
# cppf
cppf_dict = {
  'aliases' : ['cppf'],
  'arch' : 'A53_64',
  'tags' : ['CPPF_IMAGE'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/tzdrm/cppf/cppf_svc/shared/src/SConscript',
}
addParams('cppf', cppf_dict)

#======================================================
# fidocfg
fidocfg_dict = {
  'aliases' : ['fidocfg'],
  'arch' : 'A53_64',
  'tags' : ['FIDOCONFIG_IMAGE'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/fidoconfig/src/SConscript',
}
addParams('fidocfg', fidocfg_dict)

#======================================================
# fidocrypto
fidocrypto_dict = {
  'aliases' : ['fidocrypto'],
  'arch' : 'A53_64',
  'tags' : ['FIDOCRYPTO_IMAGE'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/fidocrypto/app/src/SConscript',
}
addParams('fidocrypto', fidocrypto_dict)

#======================================================
# fidosui
fidosui_dict = {
  'aliases' : ['fidosui'],
  'arch' : 'scorpion',
  'tags' : ['FIDOSUI_IMAGE'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/fidosui/app/src/SConscript',
}
addParams('fidosui', fidosui_dict)

#======================================================
# fingerprint
fingerprint_dict = {
  'aliases' : ['fingerprint'],
  'arch' : 'scorpion',
  'tags' : ['FINGERPRINT_IMAGE'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/biometrics/fingerprint/build/SConscript',
}
addParams('fingerprint', fingerprint_dict)

#======================================================
# fingerprint64
fingerprint64_dict = {
  'aliases' : ['fingerprint64'],
  'arch' : 'A53_64',
  'tags' : ['FINGERPRINT64_IMAGE'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/biometrics/fingerprint/build/SConscript',
}
addParams('fingerprint64', fingerprint64_dict)

#======================================================
# fingerprintdbg
fingerprintdbg_dict = {
  'aliases' : ['fingerprintdbg'],
  'arch' : 'scorpion',
  'tags' : ['FINGERPRINTDBG_IMAGE'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/biometrics/fingerprint/build/SConscript',
}
addParams('fingerprintdbg', fingerprintdbg_dict)

#======================================================
# fingerprint64dbg
fingerprint64dbg_dict = {
  'aliases' : ['fingerprint64dbg'],
  'arch' : 'A53_64',
  'tags' : ['FINGERPRINT64DBG_IMAGE'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/biometrics/fingerprint/build/SConscript',
}
addParams('fingerprint64dbg', fingerprint64dbg_dict)

#======================================================
# gpsample
gpsample_dict = {
  'aliases' : ['gpsample'],
  'arch' : 'scorpion',
  'tags' : ['GPSAMPLE'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/gpsample/src/SConscript',
}
addParams('gpsample', gpsample_dict)

#======================================================
# hdcp1
hdcp1_dict = {
  'aliases' : ['hdcp1'],
  'arch' : 'scorpion',
  'tags' : ['HDCP1_IMAGE'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/hdcp1/src/SConscript',
}
addParams('hdcp1', hdcp1_dict)

#======================================================
# hdcp2p2
hdcp2p2_dict = {
  'aliases' : ['hdcp2p2'],
  'arch' : 'scorpion',
  'tags' : ['HDCP2P2_IMAGE'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/hdcp2p2/core/SConscript',
}
addParams('hdcp2p2', hdcp2p2_dict)

#======================================================
# hdcptest
hdcptest_dict = {
  'aliases' : ['hdcptest'],
  'arch' : 'scorpion',
  'tags' : ['HDCPTEST_IMAGE'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/hdcp2p2/hdcptest/src/SConscript',
}
addParams('hdcptest', hdcptest_dict)

#======================================================
# hdcpsrm !! This app does not compile. Also not included in build_all.sh script
hdcpsrm_dict = {
  'aliases' : ['hdcpsrm'],
  'arch' : 'scorpion',
  'tags' : ['HDCPSRM_IMAGE'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/tzdrm/hdcpsrm/src/SConscript',
}
addParams('hdcpsrm', hdcpsrm_dict)
#======================================================
# iris
iris_dict = {
  'aliases' : ['iris'],
  'arch' : 'scorpion',
  'tags' : ['IRIS_IMAGE'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/biometrics/iris/build/SConscript',
}
addParams('iris', iris_dict)
#======================================================
# isdbtmm
isdbtmm_dict = {
  'aliases' : ['isdbtmm'],
  'arch' : 'scorpion',
  'tags' : ['ISDBTMM_IMAGE'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/tzdrm/isdbtmm/core/shared/src/SConscript',
}
addParams('isdbtmm', isdbtmm_dict)
#======================================================
# keymaster
keymaster_dict = {
  'aliases' : ['keymaster','keymaster64','km4'],
  'arch' : 'scorpion',
  'tags' : ['KEYMASTER_IMAGE'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/keymaster/km1/src/SConscript',
}
addParams('keymaster', keymaster_dict)
#======================================================
# keymaster64
keymaster64_dict = {
  'aliases' : ['keymaster64'],
  'arch' : 'A53_64',
  'tags' : ['KEYMASTER_IMAGE'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/keymaster/km3/src/SConscript',
}
addParams('keymaster64', keymaster64_dict)
#======================================================
# km4
km4_dict = {
  'aliases' : ['km4'],
  'arch' : 'A53_64',
  'tags' : ['KEYMASTER_IMAGE'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/keymaster/km4/src/SConscript',
}
addParams('km4', km4_dict)
#======================================================
# soter
soter_dict = {
  'aliases' : ['soter'],
  'arch' : 'A53_64',
  'tags' : ['SOTER_IMAGE'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/soter/src/SConscript',
}
addParams('soter', soter_dict)
#======================================================
# lksecapp
lksecapp_dict = {
  'aliases' : ['lksecapp'],
  'arch' : 'scorpion',
  'tags' : ['LKSECAPP_IMAGE'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/lksecapp/src/SConscript',
}
addParams('lksecapp', lksecapp_dict)
#======================================================
# lksecapp64
lksecapp64_dict = {
  'aliases' : ['lksecapp64'],
  'arch' : 'A53_64',
  'tags' : ['LKSECAPP64_IMAGE'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/lksecapp/src/SConscript',
}
addParams('lksecapp64', lksecapp64_dict)
#======================================================
# macchiato
macchiato_dict = {
  'aliases' : ['macchiato_sample'],
  'arch' : 'A53_64',
  'tags' : ['MACCHIATO_SAMPLE_IMAGE'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/macchiato_sample/src/SConscript',
}
addParams('macchiato_sample', macchiato_dict)
#======================================================
# mdtpsecapp
mdtp_dict = {
  'aliases' : ['mdtpsecapp'],
  'arch' : 'scorpion',
  'tags' : ['MDTP_IMAGE'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/mdtp/src/SConscript',
}
addParams('mdtpsecapp', mdtp_dict)
#======================================================
# qmpsecapp
qmpsecap_dict = {
  'aliases' : ['qmpsecap'],
  'arch' : 'scorpion',
  'tags' : ['QMPSECAPP_IMAGE'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/qmpsecapp/src/SConscript',
}
addParams('qmpsecap', qmpsecap_dict)
#======================================================
# qpay
qpay_dict = {
  'aliases' : ['qpay', 'qpay64'],
  'arch' : 'scorpion',
  'tags' : ['QPAY_IMAGE'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/qpay/src/SConscript',
}
addParams('qpay', qpay_dict)
#======================================================
# qpay64
qpay64_dict = {
  'aliases' : ['qpay64'],
  'arch' : 'A53_64',
  'tags' : ['QPAY64_IMAGE'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/qpay/src/SConscript',
}
addParams('qpay64', qpay64_dict)
#======================================================
# gpqese
gpqese_dict = {
  'aliases' : ['gpqese'],
  'arch' : 'scorpion',
  'tags' : ['GPQESE_IMAGE'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/gpqese/src/SConscript',
}
addParams('gpqese', gpqese_dict)
#======================================================
# eseservice
eseservice_dict = {
  'aliases' : ['eseservice'],
  'arch' : 'A53_64',
  'tags' : ['ESESERVICE_IMAGE'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/eseservice/src/SConscript',
}
addParams('eseservice', eseservice_dict)
#======================================================
# sampleauth
sampleauth_dict = {
  'aliases' : ['sampleauth'],
  'arch' : 'A53_64',
  'tags' : ['SAMPLEAUTH_IMAGE'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/sampleauth/src/SConscript',
}
addParams('sampleauth', sampleauth_dict)
#======================================================
# sampleextauth
sampleextauth_dict = {
  'aliases' : ['sampleextauth'],
  'arch' : 'A53_64',
  'tags' : ['SAMPLEEXTAUTH_IMAGE'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/sampleextauth/src/SConscript',
}
addParams('sampleextauth', sampleextauth_dict)
#======================================================
# sbtest
sbtest_dict = {
  'aliases' : ['sbtest'],
  'arch' : 'scorpion',
  'tags' : ['SBTEST_IMAGE'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/sbtest/src/SConscript',
}
addParams('sbtest', sbtest_dict)
#======================================================
# secotacl
secotacl_dict = {
  'aliases' : ['secotacl'],
  'arch' : 'A53_64',
  'tags' : ['SECOTACL_IMAGE'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/secotacl/src/SConscript',
}
addParams('secotacl', secotacl_dict)
#======================================================
# haventoken
haventkn_dict = {
  'aliases' : ['haventkn'],
  'arch' : 'A53_64',
  'tags' : ['HAVENTOKEN_IMAGE'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/haventoken/src/SConscript',
}
addParams('haventkn', haventkn_dict)
#======================================================
# haventokentest
haventst_dict = {
  'aliases' : ['haventst'],
  'arch' : 'A53_64',
  'tags' : ['HAVENTOKENTEST_IMAGE'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/haventokentest/src/SConscript',
}
addParams('haventst', haventst_dict)
#======================================================
# secureindicator
secureindicator_dict = {
  'aliases' : ['secureindicator'],
  'arch' : 'scorpion',
  'tags' : ['SECUREINDICATOR_IMAGE'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/secureindicator/src/SConscript',
}
addParams('secureindicator', secureindicator_dict)
#======================================================
# securemm
securemm_dict = {
  'aliases' : ['securemm'],
  'arch' : 'A53_64',
  'tags' : ['SECUREMM_IMAGE'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/securemm/src/SConscript',
}
addParams('securemm', securemm_dict)
#======================================================
# seccamdemo64
seccamdemo64_dict = {
  'aliases' : ['seccamdemo64'],
  'arch' : 'A53_64',
  'tags' : ['SECCAMDEMO64_IMAGE'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/seccamdemo64/src/SConscript',
}
addParams('seccamdemo64', seccamdemo64_dict)
#======================================================
# secure_ui_sample
secure_ui_sample_dict = {
  'aliases' : ['secure_ui_sample', 'secure_ui_sample64'],
  'arch' : 'scorpion',
  'tags' : ['SECUREUISAMPLE_IMAGE'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/secure_ui_sample/src/SConscript',
}
addParams('secure_ui_sample', secure_ui_sample_dict)
#======================================================
# secure_ui_sample64
secure_ui_sample_dict64 = {
  'aliases' : ['secure_ui_sample64'],
  'arch' : 'A53_64',
  'tags' : ['SECUREUISAMPLE64_IMAGE'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/secure_ui_sample/src/SConscript',
}
addParams('secure_ui_sample64', secure_ui_sample_dict64)
#======================================================
# ssmapp
ssmapp_dict = {
  'aliases' : ['ssmapp'],
  'arch' : 'scorpion',
  'tags' : ['SSMAPP_IMAGE'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/ssmapp/src/SConscript',
}
addParams('ssmapp', ssmapp_dict)
#======================================================
# skeleton
skeleton_dict = {
  'aliases' : ['skeleton'],
  'arch' : 'A53_64',
  'tags' : ['SKELETON_IMAGE'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/skeleton/src/SConscript',
}
addParams('skeleton', skeleton_dict)
#======================================================
# ttaari1
ttaari1_dict = {
  'aliases' : ['ttaari1'],
  'arch' : 'scorpion',
  'tags' : ['TTAARI1'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/gp-TTAs/TTA_Arithmetical/TTA_Arithmetical/SConscript',
}
addParams('ttaari1', ttaari1_dict)
#======================================================
# ttacapi1
ttacapi1_dict = {
  'aliases' : ['ttacapi1'],
  'arch' : 'scorpion',
  'tags' : ['TTACAPI1'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/gp-TTAs/TTA_ClientAPI/TTA_error_Invoke/SConscript',
}
addParams('ttacapi1', ttacapi1_dict)
#======================================================
# ttacapi2
ttacapi2_dict = {
  'aliases' : ['ttacapi2'],
  'arch' : 'scorpion',
  'tags' : ['TTACAPI2'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/gp-TTAs/TTA_ClientAPI/TTA_error_OpenSession/SConscript',
}
addParams('ttacapi2', ttacapi2_dict)
#======================================================
# ttacapi3
ttacapi3_dict = {
  'aliases' : ['ttacapi3'],
  'arch' : 'scorpion',
  'tags' : ['TTACAPI3'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/gp-TTAs/TTA_ClientAPI/TTA_success_OpenSession_Invoke/SConscript',
}
addParams('ttacapi3', ttacapi3_dict)
#======================================================
# ttacapi4
ttacapi4_dict = {
  'aliases' : ['ttacapi4'],
  'arch' : 'scorpion',
  'tags' : ['TTACAPI4'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/gp-TTAs/TTA_ClientAPI/TTA_OpenSession_with_4_params/SConscript',
}
addParams('ttacapi4', ttacapi4_dict)
#======================================================
# ttacapi5
ttacapi5_dict = {
  'aliases' : ['ttacapi5'],
  'arch' : 'scorpion',
  'tags' : ['TTACAPI5'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/gp-TTAs/TTA_ClientAPI/TTA_ClientAPI/SConscript',
}
addParams('ttacapi5', ttacapi5_dict)
#======================================================
# ttacapi6
ttacapi6_dict = {
  'aliases' : ['ttacapi6'],
  'arch' : 'scorpion',
  'tags' : ['TTACAPI6'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/gp-TTAs/TTA_ClientAPI/TTA_ClientAPI_Params/Invoke/SConscript',
}
addParams('ttacapi6', ttacapi6_dict)
#======================================================
# ttacapi7
ttacapi7_dict = {
  'aliases' : ['ttacapi7'],
  'arch' : 'scorpion',
  'tags' : ['TTACAPI7'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/gp-TTAs/TTA_ClientAPI/TTA_ClientAPI_Params/OpenSession/SConscript',
}
addParams('ttacapi7', ttacapi7_dict)
#======================================================
# ttacrp1
ttacrp1_dict = {
  'aliases' : ['ttacrp1'],
  'arch' : 'scorpion',
  'tags' : ['TTACRP1'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/gp-TTAs/TTA_Crypto/TTA_Crypto/SConscript',
}
addParams('ttacrp1', ttacrp1_dict)
#======================================================
# ttads1
ttads1_dict = {
  'aliases' : ['ttads1'],
  'arch' : 'scorpion',
  'tags' : ['TTADS1'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/gp-TTAs/TTA_DS/TTA_DS/SConscript',
}
addParams('ttads1', ttads1_dict)
#======================================================
# ttasecac
ttasecac_dict = {
  'aliases' : ['ttasecac'],
  'arch' : 'scorpion',
  'tags' : ['TTASECAC'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/gp-TTAs/TTA_TCF/Security_TTA_Abuse_Callee/SConscript',
}
addParams('ttasecac', ttasecac_dict)
#======================================================
# ttascapi
ttascapi_dict = {
  'aliases' : ['ttascapi'],
  'arch' : 'scorpion',
  'tags' : ['TTASCAPI'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/gp-TTAs/TTA_SE_API/TTA_SecureChannel/SConscript',
}
addParams('ttascapi', ttascapi_dict)
#======================================================
# ttatlapi
ttatlapi_dict = {
  'aliases' : ['ttatlapi'],
  'arch' : 'scorpion',
  'tags' : ['TTATLAPI'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/gp-TTAs/TTA_SE_API/TTA_TransportLayer/SConscript',
}
addParams('ttatlapi', ttatlapi_dict)
#======================================================
# ttaseccrp
ttaseccrp_dict = {
  'aliases' : ['ttaseccrp'],
  'arch' : 'scorpion',
  'tags' : ['TTASECCRP'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/gp-TTAs/TTA_Crypto/Security_TTA_Crypto/SConscript',
}
addParams('ttaseccrp', ttaseccrp_dict)
#======================================================
# ttasecds
ttasecds_dict = {
  'aliases' : ['ttasecds'],
  'arch' : 'scorpion',
  'tags' : ['TTASECDS'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/gp-TTAs/TTA_DS/Security_TTA_DS/SConscript',
}
addParams('ttasecds', ttasecds_dict)
#======================================================
# ttasecmem
ttasecmem_dict = {
  'aliases' : ['ttasecmem'],
  'arch' : 'scorpion',
  'tags' : ['TTASECMEM'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/gp-TTAs/TTA_Sec_Memory/TTA_Sec_Memory/SConscript',
}
addParams('ttasecmem', ttasecmem_dict)
#======================================================
# ttasectcf
ttasectcf_dict = {
  'aliases' : ['ttasectcf'],
  'arch' : 'scorpion',
  'tags' : ['TTASECTCF'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/gp-TTAs/TTA_TCF/Security_TTA_TCF/SConscript',
}
addParams('ttasectcf', ttasectcf_dict)
#======================================================
# ttatcf1
ttatcf1_dict = {
  'aliases' : ['ttatcf1'],
  'arch' : 'scorpion',
  'tags' : ['TTATCF1'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/gp-TTAs/TTA_TCF/TTA_TCF/SConscript',
}
addParams('ttatcf1', ttatcf1_dict)
#======================================================
# ttatcf2
ttatcf2_dict = {
  'aliases' : ['ttatcf2'],
  'arch' : 'scorpion',
  'tags' : ['TTATCF2'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/gp-TTAs/TTA_TCF/TTA_TCF_ICA/SConscript',
}
addParams('ttatcf2', ttatcf2_dict)
#======================================================
# ttatcf3
ttatcf3_dict = {
  'aliases' : ['ttatcf3'],
  'arch' : 'scorpion',
  'tags' : ['TTATCF3'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/gp-TTAs/TTA_TCF/TTA_TCF_ICA2/SConscript',
}
addParams('ttatcf3', ttatcf3_dict)
#======================================================
# ttatcf4
ttatcf4_dict = {
  'aliases' : ['ttatcf4'],
  'arch' : 'scorpion',
  'tags' : ['TTATCF4'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/gp-TTAs/TTA_TCF/TTA_TCF_MultipleInstanceTA/SConscript',
}
addParams('ttatcf4', ttatcf4_dict)
#======================================================
# ttatcf5
ttatcf5_dict = {
  'aliases' : ['ttatcf5'],
  'arch' : 'scorpion',
  'tags' : ['TTATCF5'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/gp-TTAs/TTA_TCF/TTA_TCF_SingleInstanceTA/SConscript',
}
addParams('ttatcf5', ttatcf5_dict)
#======================================================
# ttatcf6
ttatcf6_dict = {
  'aliases' : ['ttatcf6'],
  'arch' : 'scorpion',
  'tags' : ['TTATCF6'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/gp-TTAs/TTA_TCF/TTA_TCF_PanicAtCloseSession/SConscript',
}
addParams('ttatcf6', ttatcf6_dict)
#======================================================
# ttatcf7
ttatcf7_dict = {
  'aliases' : ['ttatcf7'],
  'arch' : 'scorpion',
  'tags' : ['TTATCF7'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/gp-TTAs/TTA_TCF/TTA_TCF_PanicAtCreation/SConscript',
}
addParams('ttatcf7', ttatcf7_dict)
#======================================================
# ttatime1
ttatime1_dict = {
  'aliases' : ['ttatime1'],
  'arch' : 'scorpion',
  'tags' : ['TTATIME1'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/gp-TTAs/TTA_Time/TTA_Time/SConscript',
}
addParams('ttatime1', ttatime1_dict)
#======================================================
# playready
playready_dict = {
  'aliases' : ['playready'],
  'arch' : 'A53_64',
  'tags' : ['PLAYREADY_IMAGE'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/tzdrm/playready/core/shared/src/SConscript',
}
addParams('playready', playready_dict)
#======================================================
# playready
pr_3_0_dict = {
  'aliases' : ['pr_3_0'],
  'arch' : 'A53_64',
  'tags' : ['PR_3_0_IMAGE'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/tzdrm/playready_3_0/build/SConscript',
}
addParams('pr_3_0', pr_3_0_dict)
#======================================================
# storsecapp
storsecapp_dict = {
  'aliases' : ['storsec'],
  'arch' : 'scorpion',
  'tags' : ['STORSECAPP_IMAGE'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/storsecapp/src/SConscript',
}
addParams('storsec', storsecapp_dict)
#======================================================
# widewine
widevine_dict = {
  'aliases' : ['widevine'],
  'arch' : 'A53_64',
  'tags' : ['WIDEVINE_IMAGE'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/tzdrm/widevine/build/SConscript',
}
addParams('widevine', widevine_dict)
#======================================================
# voiceprint
voiceprint_dict = {
  'aliases' : ['voiceprint'],
  'arch' : 'scorpion',
  'tags' : ['VOICEPRINT_IMAGE'],
  'sconspath' : '${BUILD_ROOT}/apps/securemsm/trustzone/qsapps/biometrics/voiceprint/build/SConscript',
}
addParams('voiceprint', voiceprint_dict)
