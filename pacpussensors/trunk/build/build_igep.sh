#!/bin/sh

set -e

BUILD_DIR=./build_arm
if [ -z $1 ]; then J="1"; else J="$1"; fi

if [ "$TARGET_PREFIX" != "arm-poky-linux-gnueabi-" ]; then
    echo You must setup your environment first.
    echo     source /opt/poky/environment-setup
    exit 1
fi

if [ -d "$BUILD_DIR" ]; then
    rm -rf $BUILD_DIR
fi

mkdir $BUILD_DIR
cd $BUILD_DIR

cmake -DCMAKE_TOOLCHAIN_FILE=../igep_toolchain.cmake \
      -DPACPUS_INSTALL_DIR=/opt/poky/1.3/sysroots/armv7a-vfp-neon-poky-linux-gnueabi/ \
      ../..

make -j$J
sudo make install


