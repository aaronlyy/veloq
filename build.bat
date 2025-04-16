@echo off
setlocal

set BUILD_DIR=build

:: 1. Build-Verzeichnis anlegen
if not exist %BUILD_DIR% (
    mkdir %BUILD_DIR%
)

:: 2. CMake konfigurieren mit Ninja
cmake -S . -B %BUILD_DIR% -G "Ninja" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ^
    -DCMAKE_CXX_COMPILER="C:/Users/aaron/scoop/apps/mingw/current/bin/g++.exe"

:: 3. Build ausführen
cmake --build %BUILD_DIR%

:: 4. Ausführen
:: %BUILD_DIR%\veloq.exe
