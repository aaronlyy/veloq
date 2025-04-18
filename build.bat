@echo off
setlocal

set BUILD_DIR=build

if not exist %BUILD_DIR% (
    mkdir %BUILD_DIR%
)

cmake -S . -B %BUILD_DIR% -G "Ninja" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ^
    -DCMAKE_CXX_COMPILER="C:/Users/aaron/scoop/apps/mingw/current/bin/g++.exe"

cmake --build %BUILD_DIR%