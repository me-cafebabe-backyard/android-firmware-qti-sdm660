@echo off

echo This batch script MUST be run prior to running any Fast Playback tests!
echo However, it only needs to be run ONCE per lifetime of the command prompt.

echo Temporarily adding Hexagon Tools v7.2.01 to your current environment.
echo This will ensure that Fast Playback will use Hexagon Simulator v7.2.01
echo Note: This is temporary and lasts only as long as your current
SET PATH=C:\Qualcomm\HEXAGON_Tools\7.2.01\Tools\bin;C:\Qualcomm\HEXAGON_Tools\7.2.01\Tools\lib;C:\Qualcomm\HEXAGON_Tools\7.2.01\Tools\lib\iss;%PATH%