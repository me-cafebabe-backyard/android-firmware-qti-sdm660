@echo off
rem ==========================================================================
rem
rem  RPM build system launcher for LLVM
rem
rem Copyright (c) 2015-2016 Qualcomm Technologies, Inc.
rem All Rights Reserved.
rem QUALCOMM Proprietary/GTDR
rem ==========================================================================
rem $Header: //components/rel/rpm.bf/1.8/build/build_nicobar.bat#1 $

SET BUILD_ASIC=NICOBAR
SET MSM_ID=nicobar
SET HAL_PLATFORM=nicobar
SET TARGET_FAMILY=nicobar
SET CHIPSET=sdm_nicobar
SET SECPOLICY=USES_SEC_POLICY_MULTIPLE_DEFAULT_SIGN

SET COMPILER_TYPE=llvm_compiler

set SD_LLVM_ROOT=C:\Apps\LLVM\3.9.2
set SD_LLVM_LIB=C:\Apps\LLVM\3.9.2\armv7m-none-eabi\lib
set SD_LLVM_LIBC=C:\Apps\LLVM\3.9.2\armv7m-none-eabi\libc
set SD_LLVM_RTLIB=C:\Apps\LLVM\3.9.2\lib\clang\3.9.2\lib\baremetal

python build_common.py %*
