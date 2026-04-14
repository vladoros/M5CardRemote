@echo off
cd /d "%~dp0"

if "%1"=="" goto build
if "%1"=="build" goto build
if "%1"=="upload" goto upload
if "%1"=="monitor" goto monitor
if "%1"=="clean" goto clean
if "%1"=="discover" goto discover
goto usage

:build
    rmdir /s /q build 2>nul
    mkdir build
    pio run
    move .pio\build\m5stack-cardputer\firmware.bin build\M5CardRemote.bin
    goto :eof

:upload
    pio run --target upload
    goto :eof

:monitor
    pio device monitor
    goto :eof

:clean
    pio run --target clean
    rmdir /s /q build 2>nul
    goto :eof

:discover
    pio device list
    goto :eof

:usage
    echo Usage: build.bat [build^|upload^|monitor^|clean^|discover]
    echo   build   - Build the project (default)
    echo   upload  - Build and upload
    echo   monitor - Open serial monitor
    echo   clean   - Clean build artifacts
    echo   discover - List connected devices
    goto :eof
