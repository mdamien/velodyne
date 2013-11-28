@echo off

:parameters
set SCRIPTS_DIR=%CD%
set DIRECTORIES=..\include ..\src
set FILES_TO_UPDATE=*.h *.c *.hpp *.cpp *.hxx *.cxx *.cc *.tcc

:scan
:: for all directories
for %%D in (%DIRECTORIES%) do (
    ::echo %%D
    cd %SCRIPTS_DIR%
    cd %%D
    :: find source files
    :: update each file
    for /R %%E in (%FILES_TO_UPDATE%) do (
        "%SCRIPTS_DIR%\update-license.bat" "%%E" "%SCRIPTS_DIR%"
    )
)

:exit
cd %SCRIPTS_DIR%
pause
