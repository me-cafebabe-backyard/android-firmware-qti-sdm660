echo fast_playback run start!!
C:\Windows\system32\attrib.exe -R sns.reg
echo %time%
hexagon-sim -mv60 LLVM_Debug/fast_playback_v60_LLVM -- ./ fast_playback_input.csv fast_playback_output.dlf algoqmiinput.csv sns.reg.rw fast_playback_diag_input.txt
echo %time%
echo fast_plyaback simulation finished!! Please check fast_plyaback_output.dlf for verification!