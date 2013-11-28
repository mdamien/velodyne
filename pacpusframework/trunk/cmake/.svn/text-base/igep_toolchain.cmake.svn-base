cmake_minimum_required(VERSION 2.8)

# CMake system name must be something like "Linux".
# This is important for cross-compiling.
set( CMAKE_SYSTEM_NAME Linux )
set( CMAKE_SYSTEM_PROCESSOR arm )

if(EXISTS "/opt/poky/1.3/sysroots/x86_64-pokysdk-linux")#64 bits
	SET(CMAKE_C_COMPILER   /opt/poky/1.3/sysroots/x86_64-pokysdk-linux/usr/bin/armv7a-vfp-neon-poky-linux-gnueabi/arm-poky-linux-gnueabi-gcc)
	SET(CMAKE_CXX_COMPILER /opt/poky/1.3/sysroots/x86_64-pokysdk-linux/usr/bin/armv7a-vfp-neon-poky-linux-gnueabi/arm-poky-linux-gnueabi-g++)
        SET(CMAKE_LINKER       /opt/poky/1.3/sysroots/x86_64-pokysdk-linux/usr/bin/armv7a-vfp-neon-poky-linux-gnueabi/arm-poky-linux-gnueabi-ld)
        SET(CMAKE_AR           /opt/poky/1.3/sysroots/x86_64-pokysdk-linux/usr/bin/armv7a-vfp-neon-poky-linux-gnueabi/arm-poky-linux-gnueabi-ar)
        SET(QT_QMAKE_EXECUTABLE /opt/poky/1.3/sysroots/x86_64-pokysdk-linux/usr/bin/qmake2)
elseif(EXISTS "/opt/poky/1.3/sysroots/i686-pokysdk-linux")#32 bits
	SET(CMAKE_C_COMPILER   /opt/poky/1.3/sysroots/i686-pokysdk-linux/usr/bin/armv7a-vfp-neon-poky-linux-gnueabi/arm-poky-linux-gnueabi-gcc)
	SET(CMAKE_CXX_COMPILER /opt/poky/1.3/sysroots/i686-pokysdk-linux/usr/bin/armv7a-vfp-neon-poky-linux-gnueabi/arm-poky-linux-gnueabi-g++)
        SET(CMAKE_LINKER       /opt/poky/1.3/sysroots/i686-pokysdk-linux/usr/bin/armv7a-vfp-neon-poky-linux-gnueabi/arm-poky-linux-gnueabi-ld)
        SET(CMAKE_AR           /opt/poky/1.3/sysroots/i686-pokysdk-linux/usr/bin/armv7a-vfp-neon-poky-linux-gnueabi/arm-poky-linux-gnueabi-ar)
        SET(QT_QMAKE_EXECUTABLE /opt/poky/1.3/sysroots/i686-pokysdk-linux/usr/bin/qmake2)
else()
        message(FATAL_ERROR "Cross-compilator is not installed, please read https://devel.hds.utc.fr/projects/igep" )
endif()

SET(CMAKE_C_ARCHIVE_CREATE "${CMAKE_AR} cr <TARGET> <LINK_FLAGS> <OBJECTS>")
SET(CMAKE_CXX_ARCHIVE_CREATE ${CMAKE_C_ARCHIVE_CREATE})

SET(CMAKE_SYSTEM_PREFIX_PATH /opt/poky/1.3/sysroots/armv7a-vfp-neon-poky-linux-gnueabi/)

set( CMAKE_C_FLAGS " -march=armv7-a -fno-tree-vectorize     -mthumb-interwork -mfloat-abi=softfp -mfpu=neon -mtune=cortex-a8  --sysroot=/opt/poky/1.3/sysroots/armv7a-vfp-neon-poky-linux-gnueabi " CACHE STRING "CFLAGS" )
set( CMAKE_CXX_FLAGS " -march=armv7-a -fno-tree-vectorize     -mthumb-interwork -mfloat-abi=softfp -mfpu=neon -mtune=cortex-a8  --sysroot=/opt/poky/1.3/sysroots/armv7a-vfp-neon-poky-linux-gnueabi -O2 -pipe -g -feliminate-unused-debug-types -fpermissive -fvisibility-inlines-hidden -fpermissive" CACHE STRING "CXXFLAGS" )
set( CMAKE_C_FLAGS_RELEASE "-O2 -pipe -g -feliminate-unused-debug-types  -DNDEBUG" CACHE STRING "CFLAGS for release" )
set( CMAKE_CXX_FLAGS_RELEASE "-O2 -pipe -g -feliminate-unused-debug-types  -O2 -pipe -g -feliminate-unused-debug-types -fpermissive -fvisibility-inlines-hidden -DNDEBUG" CACHE STRING "CXXFLAGS for release" )

# only search in the paths provided so cmake doesnt pick
# up libraries and tools from the native build machine
set( CMAKE_FIND_ROOT_PATH /opt/poky/1.3/sysroots/armv7a-vfp-neon-poky-linux-gnueabi/ )
set( CMAKE_FIND_ROOT_PATH_MODE_PROGRAM ONLY )
set( CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY )
set( CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY )

# Use qt.conf settings
#set( ENV{QT_CONF_PATH} $ENV{IGEP_ROOT}/uav_dev/include/qt.conf )

# Use native cmake modules
set( CMAKE_MODULE_PATH /opt/poky/1.3/sysroots/armv7a-vfp-neon-poky-linux-gnueabi/usr/share/cmake-2.8/Modules/ )
list (APPEND CMAKE_MODULE_PATH " /home/romain/TX1/tmpTarget/cmake/")

# add for non /usr/lib libdir, e.g. /usr/lib64
set( CMAKE_LIBRARY_PATH /home/romain/TX1/tmpTarget/lib)

set (CMAKE_CXX_FLAGS "-fPIC")

