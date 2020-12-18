project(hash_tables)

set(SOURCE_LIB OpenHashTable.cpp PerfectHashTable.cpp SquareSizeTable.cpp)

add_library(hash_tables STATIC ${SOURCE_LIB})