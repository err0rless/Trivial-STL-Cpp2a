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
include(CheckCXXCompilerFlag)
check_cxx_compiler_flag(-std=c++2a cxx_latest)
check_cxx_source_compiles("
#include <type_traits>

template <typename T>
concept __int_type = std::is_same_v<T, int>;

template <typename T>
int __f(T arg) { return 1; }

template <typename T>
requires __int_type<T>
int __f(T arg) { return 0; }

int main(void) {
  __f(10);
  __f(\"Hello\");
}" SUPPORT_REQUIRED_FEATURES)

if (NOT SUPPORT_REQUIRED_FEATURES)
  message(FATAL_ERROR "Does not support requires features")
endif()

# executable
include_directories(include)
add_subdirectory(src)

