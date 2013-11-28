call mkdir_dbite.bat
set PACPUSDIR=%CD%
set PATH=%PATH%;%CD%
@echo on
start /D %DBITEDIR% debug\sensor_d.exe %PACPUSDIR%\radar_tx.xml


