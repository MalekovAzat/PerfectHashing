cmake_minimum_required(VERSION 2.8)
project(hash_test_project)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(tools)
add_subdirectory(lib/googletest)
add_subdirectory(hash_tables)
add_subdirectory(src)
add_subdirectory(tst)