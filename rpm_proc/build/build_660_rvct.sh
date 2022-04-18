# ==========================================================================
#
#  RPM build system launcher
#
# Copyright (c) 2015-2016 by Qualcomm Technologies, Inc.
# All Rights Reserved.
# QUALCOMM Proprietary/GTDR
# ==========================================================================
# $Header: //components/rel/rpm.bf/1.8/build/build_660_rvct.sh#1 $

export BUILD_ASIC=660
export MSM_ID=660
export HAL_PLATFORM=660
export TARGET_FAMILY=660
export CHIPSET=sdm660
export SECPOLICY=USES_SEC_POLICY_MULTIPLE_DEFAULT_SIGN
export COMPILER_TYPE=rvct_compiler

cd './rpm_proc/build/'

python ./build_common.py $@

