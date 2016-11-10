@echo off
cd /d %~dp0

if not exist build md build
cd build
if not exist x86 md x86
cd x86
if not exist windows md windows
cd windows

set HOST_PLATFORM=PLATFORM_X86
set HOST_OS=OS_WINDOWS

cmake -G "Visual Studio 12" ../../../src
@pause
