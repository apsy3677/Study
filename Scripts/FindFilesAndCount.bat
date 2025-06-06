@echo off
setlocal enabledelayedexpansion

set "folder=C:\Users\anujyadav\OneDrive - Microsoft\Personal\Wedding-Iphone Pictures\Wedding - iphone11-18-Nov-2021\103APPLE(1)"

set "total_files=0"
for /r "%folder%" %%F in (*) do (
    set /a "total_files+=1"
)

set "processed_files=0"

for /r "%folder%" %%F in (*) do (
    set "ext=%%~xF"
    set "ext=!ext:.=!"
    set /a "ext_count[!ext!]+=1"
    for /f %%A in ('dir /a-d "%%F" ^| findstr "File(s)"') do (
        for /f "tokens=3" %%B in ("%%A") do (
            set "file_size=%%B"
            set "file_size=!file_size:,=!"
            set /a "ext_size[!ext!]+=file_size"
        )
    )

    set /a "processed_files+=1"
    set /a "progress=(processed_files * 100) / total_files"
    set "progress_bar="
    for /f %%P in ("!progress!") do (
        set /a "bar_length=(%%P * 50) / 100"
        for /l %%i in (1, 1, 50) do (
            if %%i LEQ !bar_length! (
                set "progress_bar=!progress_bar!=="
            ) else (
                set "progress_bar=!progress_bar! "
            )
        )
    )
    echo -ne Processing: !progress!%% [!progress_bar!]\r"
)

echo.
echo File Type   Count   Size (GB)   Size (MB)
echo ----------------------------------------
for /f "tokens=2,3,4 delims=[]=" %%A in ('set ext_count[') do (
    set /a "size_gb=ext_size[%%A] / 1073741824"
    set /a "size_mb=(ext_size[%%A] %% 1073741824) / 1048576"
    echo %%A         %%B        !size_gb!         !size_mb!
)

echo Done.
