cmake_minimum_required(VERSION 3.17)
include(CheckCXXCompilerFlag)

# flag checks
check_cxx_compiler_flag(-std=c++2a cxx_latest)

# compile tests
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
  message(FATAL_ERROR "Does not support required features")
endif()

