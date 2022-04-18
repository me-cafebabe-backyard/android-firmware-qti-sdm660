# ==========================================================================
#
#  RPM build system launcher
#
# Copyright (c) 2015-2016 by Qualcomm Technologies, Inc.
# All Rights Reserved.
# QUALCOMM Proprietary/GTDR
# ==========================================================================
# $Header: //components/rel/rpm.bf/1.8/build/build_nicobar.sh#1 $

export BUILD_ASIC=nicobar
export MSM_ID=nicobar
export HAL_PLATFORM=nicobar
export TARGET_FAMILY=nicobar
export CHIPSET=sdm_nicobar
export SECPOLICY=USES_SEC_POLICY_MULTIPLE_DEFAULT_SIGN
export COMPILER_TYPE=llvm_compiler
CLANG=/pkg/qct/software/llvm/release/arm/3.9.2/bin/clang
export SD_LLVM_ROOT=`dirname $CLANG`/..

cd './rpm_proc/build/'

python ./build_common.py $@

