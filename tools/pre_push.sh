#!/bin/bash

set -e

ROOTDIR=$PWD/../

echo "checking for gcc"
cd $ROOTDIR
./cmake_gen.sh gcc.cmake MinSizeRel 1 $ROOTDIR/build/release
cd $ROOTDIR/build
make -j32 && make test && make install

echo "checking for hc32f460petb"
cd $ROOTDIR
./cmake_gen.sh hc32f460petb.cmake MinSizeRel 1 $ROOTDIR/build/release
cd $ROOTDIR/build
make  && make -j32 test && make install

echo "checking for stm32f411ce"
cd $ROOTDIR
./cmake_gen.sh stm32f411ce.cmake MinSizeRel 1 $ROOTDIR/build/release
cd $ROOTDIR/build
make  && make -j32 test && make install

