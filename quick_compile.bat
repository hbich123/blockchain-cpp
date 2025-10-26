@echo off
REM ============================================
REM Build script for Blockchain C++ on Windows
REM ============================================

echo.
echo ================================================
echo   Building Blockchain C++ Project
echo ================================================
echo.

REM Check if build directory exists
if not exist build (
    echo Creating build directory...
    mkdir build
)

cd build

REM Configure with CMake
echo Configuring project with CMake...
cmake .. -G "MinGW Makefiles"

if %ERRORLEVEL% NEQ 0 (
    echo.
    echo ERROR: CMake configuration failed!
    echo Make sure CMake and MinGW are installed.
    pause
    exit /b 1
)

REM Build the project
echo.
echo Building project...
cmake --build .

if %ERRORLEVEL% NEQ 0 (
    echo.
    echo ERROR: Build failed!
    pause
    exit /b 1
)

echo.
echo ================================================
echo   Build completed successfully!
echo ================================================
echo.
echo Available executables:
echo   - example1_merkle_tree.exe
echo   - example2_proof_of_work.exe
echo   - example3_proof_of_stake.exe
echo   - example4_complete_blockchain.exe
echo   - test_blockchain.exe
echo.
echo To run the complete demo:
echo   cd build
echo   example4_complete_blockchain.exe
echo.

cd ..
pause