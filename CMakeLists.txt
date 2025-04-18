cmake_minimum_required(VERSION 4.0.1)

project(veloq LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(veloq
    src/main.cpp
    src/cli.cpp
    src/runner.cpp
    src/utils.cpp
)

target_include_directories(veloq PRIVATE src)
target_include_directories(veloq PRIVATE external/CLI11)