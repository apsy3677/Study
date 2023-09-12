@echo off
setlocal

set "source_folder=This PC\Apple iPhone\Internal Storage\DCIM"
set "destination_folder=D:\Personal\Lala\PicsTransfer"

if not exist "%destination_folder%" (
    mkdir "%destination_folder%"
)

for %%F in ("%source_folder%\*.jpg", "%source_folder%\*.png", "%source_folder%\*.heic") do (
    move "%%F" "%destination_folder%\"
    echo Transferred: %%~nxF
)

echo Transfer complete!
