cmake_minimum_required(VERSION 3.17)
project(TrivSTL LANGUAGES CXX VERSION 0.0.0)

# C++ Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -stdlib=libc++")

message(STATUS "Compiler Information")
message(STATUS "  NAME   : ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "  Version: ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "  Path   : ${CMAKE_CXX_COMPILER}")

# Check compiler features
include(cmake/check-compiler-spec.cmake)

# Subdirectories
add_subdirectory(extern/googletest)
add_subdirectory(tests)
