
export BUILDSPEC=KLOCWORK
#===============================================================================
#Set up  Environment
#===============================================================================
unamestr=`uname`
# Set up compiler path
   PYTHON_PATH=/pkg/qct/software/python/2.7/bin
   MAKE_PATH=/pkg/gnu/make/3.81/bin
export ARMTOOLS=ARMCT6 #FIXME
export LLVMTOOLS=LLVM
export LLVMROOT=/pkg/qct/software/llvm/release/arm/3.5.2.4
export LLVMBIN=$LLVMROOT/bin
export LLVMLIB=$LLVMROOT/lib/clang/3.5.2/lib/linux
export MUSLPATH=$LLVMROOT/tools/lib64
export MUSL32PATH=$LLVMROOT/tools/lib32
export LLVMINC=$MUSLPATH/include
export LLVM32INC=$MUSL32PATH/include
export LLVMTOOLPATH=$LLVMROOT/tools/bin
export GNUROOT=/pkg/qct/software/arm/linaro-toolchain/aarch64-none-elf/4.9-2014.07
export GNUARM7=/prj/llvm-arm/home/common/build_tools/gcc-linaro-arm-linux-gnueabihf-4.8-2014.02_linux
export PATH=$GNUTOOL:$PATH

   # PYTHONBIN specifies version that will be added to PATH
   if [ -z ${PYTHONBIN} ]; then
      # Set default version for legacy builds
      PYTHONBIN=${PYTHON_PATH}
   fi

   export PATH=$MAKE_PATH:$PYTHONBIN:$ARM_COMPILER_PATH:$PATH
   export ARMHOME=$ARMROOT
#   export_armlmd_license

#==============================================================================
# Dump environment to stdout so that calling scripts can read it.
#==============================================================================
env
