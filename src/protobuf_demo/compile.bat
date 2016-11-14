@echo off
cd %~dp0

protoc --cpp_out=./ ./data.proto2

@pause