#!/bin/bash

TOOLCHAIN_DIR=$PWD/cmake/toolchain
TOOLCHAIN=$1
BUILD_TYPE=$2

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
$CMAKE -LAH\
	-DCMAKE_TOOLCHAIN_FILE=$TOOLCHAIN_DIR/$TOOLCHAIN \
	-DCMAKE_BUILD_TYPE=$BUILD_TYPE \
	..
make all && make install

exit 0
