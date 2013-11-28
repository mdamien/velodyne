@echo off

echo #################################################
echo #   ___________    ____ ______  __ __  _____    #
echo #   \____ \__  \ _/ ___\\____ \^|  ^|  \/  ___/   #
echo #   ^|  ^|_^> ^> __ \\  \___^|  ^|_^> ^>  ^|  /\___ \    #
echo #   ^|   __(____  /\___  ^>   __/^|____//____  ^>   #
echo #   ^|__^|       \/     \/^|__^|              \/    #
echo #                                               #
echo #################################################
echo:

echo ========================================
echo           PACPUS BUILD MSVC             
echo ========================================
echo:

:preamble
:: Check if the user is in the build directory
if not exist "%CD%\..\README.txt" goto usage
:: Args ok, go to build
goto build

:usage
echo Usage:
echo     build-msvc.bat [install_dir]
echo     [install-dir] is optional
echo The script must be run in the build directory, which is 'trunk\build'
echo:
echo Where:
echo     install_dir   is the installation directory of the library
echo:
echo For instance, here is how to build Pacpus:
echo     ..\scripts\build-msvc.bat "D:\Libraries\Pacpus"
echo:
goto exit

:build
:: Initialize the build
cmake .. -DPACPUS_INSTALL_3RD=TRUE -DPACPUS_USE_LOG=TRUE -DPACPUS_INSTALL_WITH_VERSION_NUMBER=TRUE
:: Build in debug and release
msbuild Pacpus.sln /p:Configuration=Debug
msbuild Pacpus.sln /p:Configuration=Release
:: Install
msbuild INSTALL.vcxproj /p:Configuration=Debug
msbuild INSTALL.vcxproj /p:Configuration=Release
echo Build finished, do not forget to check the MSVC's output

:exit
pause