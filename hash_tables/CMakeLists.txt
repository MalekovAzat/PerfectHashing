project(hash_tables)

set(SOURCE_LIB DirectHashTable.cpp PerfectHashTable.cpp)

add_library(hash_tables STATIC ${SOURCE_LIB})