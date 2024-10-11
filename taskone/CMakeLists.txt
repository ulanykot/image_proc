cmake_minimum_required(VERSION 3.29)
project(taskone)

set(CMAKE_CXX_STANDARD 20)
set(SOURCE_FILES
    CImg.h
        cmake-build-debug/img/lenac.bmp
)
add_executable(taskone main.cpp)
include_directories(cmake-build-debug/img/)