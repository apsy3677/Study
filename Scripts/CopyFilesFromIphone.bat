@echo off
setlocal

REM Set your source and destination paths
set "sourcePath=This PC\Apple iPhone\Internal Storage\DCIM"
set "destinationPath=D:\Personal\Lala\PicsTransfer"

REM Check if the source folder exists
if not exist "%sourcePath%" (
    echo Source folder does not exist.
    pause
    exit /b
)

REM Check if the destination folder exists
if not exist "%destinationPath%" (
    echo Destination folder does not exist.
    pause
    exit /b
)

REM Copy files from source to destination
echo Copying files...
xcopy "%sourcePath%\*.jpg" "%destinationPath%" /Y
xcopy "%sourcePath%\*.png" "%destinationPath%" /Y
echo Files copied successfully.

pause
