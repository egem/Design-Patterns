# Minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Project name and language
project(Example LANGUAGES CXX)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(Creational)
add_subdirectory(Structural)
add_subdirectory(Behavioral)

# Export compile commands for IntelliSense
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

