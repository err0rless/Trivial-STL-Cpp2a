cmake_minimum_required(VERSION 3.17)
project(extstl)

# C++ Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# include dir
include_directories(extstl)

# executaable 
add_executable(main main.cpp)