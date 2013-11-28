#!/bin/sh

set -e

BUILD_DIR=./build
if [ -z $1 ]; then J="1"; else J="$1"; fi

if [ "$TARGET_PREFIX" == "arm-poky-linux-gnueabi-" ]; then
    echo The environment is configured for poky_arm
    exit 1
fi

if [ -d "$BUILD_DIR" ]; then
    rm -rf $BUILD_DIR
fi

mkdir $BUILD_DIR
cd $BUILD_DIR

cmake ../..

make -j$J
sudo make install


