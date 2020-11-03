cmake_minimum_required(VERSION 2.8)

project(tools)

set(SOURCE_LIB UniversalHash.cpp)

add_library(tools STATIC ${SOURCE_LIB})