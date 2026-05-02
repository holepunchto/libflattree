cmake_minimum_required(VERSION 3.25)

find_package(cmake-fetch REQUIRED PATHS node_modules/cmake-fetch)

project(flattree C)

add_library(flattree OBJECT)

set_target_properties(
  flattree
  PROPERTIES
  C_STANDARD 99
  POSITION_INDEPENDENT_CODE ON
)

target_sources(
  flattree
  INTERFACE
    include/flattree.h
  PRIVATE
    src/flattree.c
)

target_include_directories(
  flattree
  PUBLIC
    include
)

add_library(flattree_shared SHARED $<TARGET_OBJECTS:flattree>)

set_target_properties(
  flattree_shared
  PROPERTIES
  OUTPUT_NAME flattree
  WINDOWS_EXPORT_ALL_SYMBOLS ON
)

target_link_libraries(
  flattree_shared
  PUBLIC
  flattree
)

add_library(flattree_static STATIC)

set_target_properties(
  flattree_static
  PROPERTIES
  OUTPUT_NAME flattree
  PREFIX lib
)

target_link_libraries(
  flattree_static
  PUBLIC
  flattree
)

install(TARGETS flattree_shared flattree_static)

install(FILES include/flattree.h DESTINATION include)

if(PROJECT_IS_TOP_LEVEL)
  enable_testing()
  add_subdirectory(test)
endif()
