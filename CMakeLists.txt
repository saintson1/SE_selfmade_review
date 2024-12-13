cmake_minimum_required(VERSION 3.20)

project(
  labwork5
  VERSION 1.0
  DESCRIPTION "battleship"
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)

set(ENV{INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(lib)
add_subdirectory(bin)

set(ENV{INCLUDE_DIRS} "")