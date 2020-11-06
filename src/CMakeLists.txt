set(BINARY ${CMAKE_PROJECT_NAME})

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)

set(SOURCES ${SOURCES})

include_directories(../tools ../hash_tables)

add_executable(${BINARY}_run ${SOURCES})

#add_library(${BINARY}_lib STATIC ${SOURCES})