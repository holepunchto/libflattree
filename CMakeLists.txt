cmake_minimum_required(VERSION 3.25)

project(flattree C)

add_library(flattree_obj OBJECT)

set_target_properties(
  flattree_obj
  PROPERTIES
  C_STANDARD 99
  POSITION_INDEPENDENT_CODE ON
)

target_sources(
  flattree_obj
  PRIVATE
    src/flattree.c
  PUBLIC
    FILE_SET HEADERS
    BASE_DIRS include
    FILES
      include/flattree.h
)

add_library(flattree_shared SHARED)
set_target_properties(flattree_shared PROPERTIES OUTPUT_NAME flattree)
target_link_libraries(flattree_shared PUBLIC flattree_obj)

add_library(flattree_static STATIC)
set_target_properties(flattree_static PROPERTIES OUTPUT_NAME flattree)
target_link_libraries(flattree_static PUBLIC flattree_obj)

install(TARGETS flattree_shared flattree_static)

install(
  FILES
    include/flattree.h
  DESTINATION
    include
)

if(PROJECT_IS_TOP_LEVEL)
  enable_testing()
  add_subdirectory(test)
endif()
