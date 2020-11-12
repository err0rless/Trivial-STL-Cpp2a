cmake_minimum_required(VERSION 3.17)
project(trivstl LANGUAGES CXX VERSION 0.0.0)

# C++ Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

message(STATUS "Compiler Information")
message(STATUS "  NAME   : ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "  Version: ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "  Path   : ${CMAKE_CXX_COMPILER}")

# Check compiler features
include(cmake/check-compiler-spec.cmake)

# executable
include_directories(include)
add_subdirectory(src)

