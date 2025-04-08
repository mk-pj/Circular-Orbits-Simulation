cmake_minimum_required(VERSION 3.30)
project(5)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include_directories(include)

add_executable(5 src/main.cpp
        src/Vector2D.cpp
        src/func.cpp)
