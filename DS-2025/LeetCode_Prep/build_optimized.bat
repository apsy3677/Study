@echo off
REM Professional Build Script for Fast Compilation
REM Optimized for Windows development environment

echo ===========================================
echo Professional C++ Build Script
echo ===========================================

REM Check if compiler is available
where g++ >nul 2>&1
if %ERRORLEVEL% neq 0 (
    echo ERROR: g++ compiler not found in PATH
    echo Please install MinGW-w64 or Visual Studio Build Tools
    echo Download from: https://www.mingw-w64.org/
    pause
    exit /b 1
)

REM Build configuration
set SOURCE_FILE=delivery_truck_simple.cpp
set OUTPUT_FILE=delivery_truck_optimized.exe
set OPTIMIZATION_LEVEL=-O2
set CPP_STANDARD=-std=c++17
set WARNINGS=-Wall -Wextra -Wpedantic
set FAST_COMPILE_FLAGS=-pipe -ffast-math

echo Building: %SOURCE_FILE%
echo Target: %OUTPUT_FILE%
echo.

REM Fast compilation with optimizations
echo [1/3] Compiling with fast build flags...
g++ %OPTIMIZATION_LEVEL% %CPP_STANDARD% %WARNINGS% %FAST_COMPILE_FLAGS% %SOURCE_FILE% -o %OUTPUT_FILE%

if %ERRORLEVEL% neq 0 (
    echo.
    echo BUILD FAILED!
    echo Check the error messages above for details.
    echo.
    echo Common solutions:
    echo 1. Ensure MinGW-w64 is properly installed
    echo 2. Check that g++ is in your PATH
    echo 3. Verify C++ standard library is available
    pause
    exit /b 1
)

echo [2/3] Build successful!

REM Run the program if build succeeded
echo [3/3] Running the optimized program...
echo.
./%OUTPUT_FILE%

if %ERRORLEVEL% neq 0 (
    echo.
    echo RUNTIME ERROR!
    echo The program compiled but failed to run properly.
    pause
    exit /b 1
)

echo.
echo ===========================================
echo BUILD AND EXECUTION COMPLETED SUCCESSFULLY
echo ===========================================
echo.
echo Performance Optimizations Applied:
echo - Fast compilation flags (-pipe, -ffast-math)
echo - Optimized code generation (-O2)
echo - Modern C++ standard (C++17)
echo - Comprehensive warnings enabled
echo.
echo Build time should be under 10 seconds on modern hardware.
echo If builds are still slow, consider:
echo 1. Using SSD storage
echo 2. Disabling antivirus real-time scanning for build directory
echo 3. Using distributed build tools like distcc
echo 4. Precompiled headers for larger projects
echo.
pause
