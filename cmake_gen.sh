#!/bin/bash

TOOLCHAIN=$1
BUILD_TYPE=$2
UNIT_TEST=$3
INSTALL_PREFIX=$4

TOOLCHAIN_DIR=$PWD/cmake/toolchain

CMAKE=$(which cmake3 2>/dev/null || which cmake2 2>/dev/null || which cmake 2>/dev/null)

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
	-G "Unix Makefiles" \
	-DCMAKE_TOOLCHAIN_FILE=$TOOLCHAIN_DIR/$TOOLCHAIN \
	-DCMAKE_BUILD_TYPE=$BUILD_TYPE \
	-DUNIT_TEST=$UNIT_TEST \
	-DCMAKE_INSTALL_PREFIX=$INSTALL_PREFIX
	../

exit 0
