@echo off
rem ==========================================================================
rem
rem  Set Environment Script for Windows
rem
rem  General Description
rem     Setup Qualcomm-specific environment variables for the build system.
rem
rem Copyright (c) 2009-2012 by QUALCOMM, Incorporated.
rem All Rights Reserved.
rem QUALCOMM Proprietary/GTDR
rem
rem --------------------------------------------------------------------------
rem
rem $Header: //components/rel/scons.tz/1.0.7.1/build/scons/build/setenv.cmd#1 $
rem $DateTime: 2020/01/14 12:34:44 $
rem $Change: 22186827 $
rem
rem ==========================================================================

call %1.cmd
set  BUILDSPEC=KLOCWORK
rem Dump environment to stdout so that calling scripts can read it.
set
