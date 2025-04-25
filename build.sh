#!/bin/bash
set -e

BUILD_DIR="build"
CMAKE_FLAGS="-G Ninja -DCMAKE_EXPORT_COMPILE_COMMANDS=ON"

for arg in "$@"; do
  case "$arg" in
    --clean)
        echo "🧹 Cleaning build directory..."
        rm -rf "$BUILD_DIR"
        ;;
    --release)
        CMAKE_FLAGS+=" -DCMAKE_BUILD_TYPE=Release"
        ;;
    *)
        echo "❌ Unknown option: $arg"
        echo "Usage: $0 [--clean] [--release]"
        exit 1
        ;;
  esac
done

if [ ! -d "$BUILD_DIR" ]; then
    mkdir "$BUILD_DIR"
fi

echo "🔧 Configuring project..."
cmake -S . -B "$BUILD_DIR" $CMAKE_FLAGS

echo "🚀 Building project..."
cmake --build "$BUILD_DIR"
