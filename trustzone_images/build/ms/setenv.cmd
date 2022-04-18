@echo off
rem ==========================================================================
rem
rem  CBSP Buils system
rem
rem  General Description
rem     SetEnv batch file.
rem
rem Copyright (c) 2011 by QUALCOMM, Incorporated.
rem All Rights Reserved.
rem QUALCOMM Proprietary/GTDR
rem
rem --------------------------------------------------------------------------
rem
rem $Header: //components/rel/build.tz/1.0.7.1/ms/setenv.cmd#1 $
rem $DateTime: 2020/01/14 12:33:59 $
rem $Author: pwbldsvc $
rem $Change $
rem                      EDIT HISTORY FOR FILE 
rem
rem  This section contains comments describing changes made to the module.
rem  Notice that changes are listed in reverse chronological order.
rem
rem when       who     what, where, why
rem --------   ---     ---------------------------------------------------------
rem  09/19/11  sy    Initial revision
rem  03/15/16  pdosi changed for LLVM 3.7 and qcld
rem  03/15/16  pdosi changed to older version since we do not use this for 3.7.* llvm
rem ==========================================================================

rem ======== Set Klocwork =============================
SET BUILDSPEC=KLOCWORK

set ROOT_DRIVE=C:
set APPS_DIR=Apps
set APPS_PATH=%ROOT_DRIVE%\%APPS_DIR%
set UTILROOT=%ROOT_DRIVE%\utils

rem
rem GNU, Perl and Python paths
rem
set GNUPATH=%UTILROOT%\cygwin\bin
set CRMPERL=C:\CRMApps\apps\Perl\bin
set PERLPATH=C:\perl\bin
set PYTHON_PATH=C:\CRMApps\apps\Python276-64

rem
rem ARM General Definitions used by Qualcomm build goo
rem
set ARMTOOLS=ARMCT6

rem
rem Path for ARM, GNU, Python, and Perl tools
rem

set LLVMTOOLS=LLVM
set LLVMROOT=C:\Apps\LLVM\3.5.2.4
set LLVMBIN=%LLVMROOT%\bin
set LLVMLIB=%LLVMROOT%\lib\clang\3.5.2\lib\linux
set LLVMTOOLPATH=%LLVMROOT%\tools\bin
set MUSLPATH=%LLVMROOT%\tools\lib64
set MUSL32PATH=%LLVMROOT%\tools\lib32
set LLVMINC=%MUSLPATH%\include
set LLVM32INC=$MUSL32PATH\include
set GNUROOT=C:\Apps\Linaro
set GNULIBC=%GNUROOT%\aarch64-linux-gnu\libc
set GNUTOOL=%GNUROOT%\aarch64-linux-gnu
set GNUARM7=C:\Apps\gcc-linaro-arm-linux-gnueabihf-4.9-2014.05_win32


set path=%LLVMBIN%;%PERLPATH%;%CRMPERL%;%PYTHON_PATH%;%GNUPATH%;%ARMCC5BIN%;%UTILROOT%;%path%
set


    