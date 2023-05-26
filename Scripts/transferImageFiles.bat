@echo off
setlocal

set "source_folder=C:\Users\anujyadav\OneDrive - Microsoft\Personal\Wedding-Iphone Pictures\Wedding - iphone11-18-Nov-2021\103APPLE(1)"
set "destination_folder=D:\Picstransfer"

if not exist "%destination_folder%" (
    mkdir "%destination_folder%"
)

for %%F in ("%source_folder%\*.jpg", "%source_folder%\*.heic") do (
    move "%%F" "%destination_folder%\"
    echo Transferred: %%~nxF
)

echo Transfer complete!
