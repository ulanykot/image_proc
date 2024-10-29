cmake_minimum_required(VERSION 3.29)
project(taskone)

set(CMAKE_CXX_STANDARD 20)
set(SOURCE_FILES
    CImg.h
)
add_executable(taskone main.cpp
        BasicOperations.cpp
        BasicOperations.h
        FilterOperations.cpp
        FilterOperations.h
        CommandLineInterface.cpp
        CommandLineInterface.h)
include_directories(cmake-build-debug/img/)