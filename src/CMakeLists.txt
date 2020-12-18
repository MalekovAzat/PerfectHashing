set(BINARY ${CMAKE_PROJECT_NAME})
file(GLOB_RECURSE SOURCES_MAIN LIST_DIRECTORIES true *.h *.cpp)

set(SOURCES ${SOURCES_MAIN})

add_executable(${BINARY}_run ${SOURCES})

add_library(${BINARY}_lib STATIC ${SOURCES})

target_link_libraries(${BINARY}_run tools gtest hash_tables)