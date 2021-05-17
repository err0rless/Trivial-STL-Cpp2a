file(GLOB_RECURSE TEST_SRC LIST_DIRECTORIES false *.h *.cpp)

set(TEST_BINARY triv_stl_test_bin)

add_executable(${TEST_BINARY} ${TEST_SRC})
add_test(NAME ${TEST_BINARY} COMMAND ${TEST_BINARY})
target_link_libraries(${TEST_BINARY} PUBLIC gtest)
