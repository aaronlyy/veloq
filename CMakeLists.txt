cmake_minimum_required(VERSION 4.0.1)

project(veloq LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(veloq
    src/main.cpp
    src/cli.cpp
    src/config.cpp
    src/controller.cpp
    src/executor.cpp
    src/format/color.cpp
)

add_subdirectory(external/yaml-cpp)
target_link_libraries(veloq PRIVATE yaml-cpp)

add_subdirectory(external/CLI11)
target_link_libraries(veloq PRIVATE CLI11::CLI11)

target_include_directories(veloq PRIVATE src)