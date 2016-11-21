@echo off
cd /d %~dp0

if not exist build md build
cd build
if not exist x64 md x64
cd x64
if not exist windows md windows
cd windows

set HOST_PLATFORM=PLATFORM_X64
set HOST_OS=OS_WINDOWS

cmake -G "Visual Studio 14 2015 Win64" ../../../src
@pause