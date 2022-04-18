REM This batch script runs the Fast Playback!

@echo off

if [%1]==[] ( 
  echo Error!  Need to specify the playback executable as input!
  goto :eof
)

if exist "%1" (
  goto ok
) else (
  echo Error!  Need to specify a valid playback executable as input!
  goto :eof
)

:ok

echo Running:  fast_playback.cmd %1
echo
echo Temporarily adding Hexagon Tools v7.4.02 to your current environment.
echo This will ensure that Fast Playback will use Hexagon Simulator v7.4.02
echo PATH += C:\Qualcomm\HEXAGON_Tools\7.4.02\Tools\bin; 
echo PATH += C:\Qualcomm\HEXAGON_Tools\7.4.02\Tools\lib;
echo PATH += C:\Qualcomm\HEXAGON_Tools\7.4.02\Tools\lib\iss;
setlocal
SET PATH=C:\Qualcomm\HEXAGON_Tools\7.4.02\Tools\bin;C:\Qualcomm\HEXAGON_Tools\7.4.02\Tools\lib;C:\Qualcomm\HEXAGON_Tools\7.4.02\Tools\lib\iss;%PATH%
echo

echo Change current working directory to %~dp0
cd %~dp0

C:\Windows\system32\attrib.exe -R sns.reg

echo
echo Running:  hexagon-sim -mv5 %1
hexagon-sim -mv5 %1

if exist "fast_playback_output.dlf" (
  echo Done!
) else (
  echo Error!  Playback failed!
)

:eof