@echo off
rem ==========================================================================
rem
rem  CBSP Buils system
rem
rem  General Description
rem     build batch file.
rem
rem Copyright (c) 2009-2009 by QUALCOMM, Incorporated.
rem All Rights Reserved.
rem QUALCOMM Proprietary/GTDR
rem
rem --------------------------------------------------------------------------
rem
rem $Header: //components/rel/core.tz/1.0.7.1/bsp/build/build.cmd#1 $
rem $DateTime: 2020/01/14 12:35:09 $
rem $Author: pwbldsvc $
rem $Change: 22186835 $
rem                      EDIT HISTORY FOR FILE
rem
rem  This section contains comments describing changes made to the module.
rem  Notice that changes are listed in reverse chronological order.
rem
rem when       who     what, where, why
rem --------   ---     ---------------------------------------------------------
rem
rem ==========================================================================

setlocal
REM if we have a set environment batch file, call it.
IF EXIST setenv.cmd CALL setenv.cmd

REM Brew Config
SET BUILD_ID=AAABQNBB
rem SET BUILD_ID=TSGCHBAA
rem SET BUILD_ID=TFGCHAAA
SET BUILD_VER=1007

REM Common
SET BUILD_ASIC=8660
SET MSM_ID=8660
SET HAL_PLATFORM=8660
SET TARGET_FAMILY=8600
SET CHIPSET=msm8660

set BUILD_CMD=BUILD_ID=%BUILD_ID% BUILD_VER=%BUILD_VER% MSM_ID=%MSM_ID% HAL_PLATFORM=%HAL_PLATFORM% TARGET_FAMILY=%TARGET_FAMILY% BUILD_ASIC=%BUILD_ASIC% CHIPSET=%CHIPSET% %*

call %~dp0..\build\tools\rename-log.cmd
call %~dp0..\build\tools\build.cmd %BUILD_CMD%
