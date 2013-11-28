@echo off

:: You have to install `sed` first!

:init
:: get full path of the file
set FILE=%~df1
set SCRIPTS_DIR=%2
set MV=move

::echo %FILE%
::echo %LICENSE_HEADER_FILE%

:find
:: remove license
:: sed '/^%pacpus:license{/,/^%pacpuse:license}/d' %FILE%

sed -nf %SCRIPTS_DIR%\update-license.sed "%FILE%" > update-license.tmp
%MV% update-license.tmp "%FILE%"

:: print lines from begin of file till begin of license
::sed -n '0,/^%pacpus:license{/   p' %FILE%
:: print new license

:: print lines from end of license till end of file
::sed -n '/^%pacpus:license}/,$   p' %FILE%
