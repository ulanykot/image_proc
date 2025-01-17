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
        CommandLineInterface.h
        SimilarityMeasures.cpp
        SimilarityMeasures.h
        HistogramComputations.cpp
        HistogramComputations.h
        ImageCharacteristics.cpp
        ImageCharacteristics.h
        SpatialOperations.cpp
        SpatialOperations.h
        MorphologicalBasic.cpp
        MorphologicalBasic.h
        ImageSegmentation.cpp
        ImageSegmentation.h
        HelperFunctions.cpp
        HelperFunctions.h
        FourierTransform.cpp
        FourierTransform.h)
include_directories(cmake-build-debug/img/)