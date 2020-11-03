cmake_minimum_required(VERSION 2.8)

project(hash_tables_research)

set(SOURCE_EXE main.cpp)

set(SOURCE_LIB ./tools/UniversalHash.h)

include_directories(tools hash_tables)

add_executable(main main.cpp)

add_subdirectory(tools)
add_subdirectory(hash_tables)

target_link_libraries(main tools hash_tables)	
