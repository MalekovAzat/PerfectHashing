project(tools)

set(SOURCE_LIB UniversalHash.cpp Node.cpp UniformDistributionGenerator.cpp)

add_library(tools STATIC ${SOURCE_LIB})