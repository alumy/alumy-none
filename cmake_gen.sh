#!/bin/bash

TOOLCHAIN=es32f0654lt.cmake
LINKER_SCRIPT=es32f0654lt.ld

TOOLCHAIN_DIR=$PWD/cmake/toolchain
LINKER_SCRIPT_DIR=$PWD

BUILD_TYPE=$1

CMAKE=$(which cmake 2>/dev/null || which cmake3 2>/dev/null || which cmake2 2>/dev/null)

if [ -x "$CMAKE" ]; then
	echo "Using cmake: $CMAKE"
else
	echo "cmake not found, please install cmake firstly"
	exit 1
fi

# enable exit on error
set -e

# Delete build directory
if [ -d build ]; then
	rm -r build
fi

# Make build directory
mkdir build && cd build

# add options '-LAH' if you want see all variables
$CMAKE \
	-DCMAKE_TOOLCHAIN_FILE=$TOOLCHAIN_DIR/$TOOLCHAIN \
	-DLINKER_SCRIPT=$LINKER_SCRIPT_DIR/$LINKER_SCRIPT \
	-DCMAKE_BUILD_TYPE=$BUILD_TYPE \
	../

exit 0
