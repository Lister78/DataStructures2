cmake_minimum_required(VERSION 3.0)
project(main)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

file (GLOB SOURCES "src/*.cc")

set (LINKED_LIST "src/LinkedList.cc")

list(APPEND SOURCES ${LINKED_LIST})

add_executable(main ${SOURCES})


