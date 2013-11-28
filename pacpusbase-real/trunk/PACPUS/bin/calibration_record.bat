call mkdir_dbite.bat
set PACPUSDIR=%CD%
set PATH=%PATH%;%CD%
@echo on
start /D %DBITEDIR% debug\sensor_d.exe %PACPUSDIR%\calibration_record.xml
start debug\pedestriandetection_d.exe viewer.xml
