@echo off
rem ==========================================================================
rem
rem  RPM build system launcher
rem
rem Copyright (c) 2015-2016 Qualcomm Technologies, Inc.
rem All Rights Reserved.
rem QUALCOMM Proprietary/GTDR
rem ==========================================================================
rem $Header: //components/rel/rpm.bf/1.8/build/build_660_rvct.bat#1 $

SET BUILD_ASIC=660
SET MSM_ID=660
SET HAL_PLATFORM=660
SET TARGET_FAMILY=660
SET CHIPSET=sdm660
SET SECPOLICY=USES_SEC_POLICY_MULTIPLE_DEFAULT_SIGN
SET COMPILER_TYPE=rvct_compiler

python build_common.py %*