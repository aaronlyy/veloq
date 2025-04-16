# build.ps1

$buildDir = "build"

# 1. Build-Verzeichnis anlegen, falls es nicht existiert
if (-not (Test-Path $buildDir)) {
    New-Item -ItemType Directory -Path $buildDir | Out-Null
}

# 2. cmake-Konfiguration mit Ninja + compile_commands
cmake -S . -B $buildDir -G "Ninja" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON `
    -DCMAKE_CXX_COMPILER="C:/Users/aaron/scoop/apps/mingw/current/bin/g++.exe"

# 3. Projekt bauen
cmake --build $buildDir

# 4. Programm ausführen
& "$buildDir/veloq.exe"
