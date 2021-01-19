# Set minimum cmake version
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
cmake_policy(SET CMP0048 NEW)

# Project settings.
project(GraphCPP-Library VERSION 1.0.0)

# Set C++ standard to C++11.
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/prerequisites)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

option(GraphCPP_BUILD_EXAMPLES "Build the example of GraphCPP." OFF)
if (GraphCPP_BUILD_EXAMPLES)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/examples)
endif ()

option(GraphCPP_BUILD_TESTS "Build the tests of GraphCPP." OFF)
if (GraphCPP_BUILD_TESTS)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests)
    include(CTest)
    add_test(NAME System-Tests
            COMMAND system-tests
            )
endif ()