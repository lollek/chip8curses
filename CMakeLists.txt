cmake_minimum_required(VERSION 3.0)
project(chip8curses
  VERSION 1.1.0.0
  LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

find_library(Curses REQUIRE)

# Include chip8core
add_subdirectory(lib/CHIP-8-Virtual-Machine-Core)
include_directories("${chip8core_SOURCE_DIR}/include")

configure_file(
  "${PROJECT_SOURCE_DIR}/src/chip8curses.h.in"
  "${PROJECT_BINARY_DIR}/src/chip8curses.h"
)

include_directories(
  "${CMAKE_BINARY_DIR}/src"
)

set(CMAKE_CXX_FLAGS "${MAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Weffc++ -std=c++11")

file(GLOB_RECURSE LOCAL_SOURCE_FILES "${CMAKE_SOURCE_DIR}/src/*.cc")

add_executable(${PROJECT_NAME} ${LOCAL_SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} chip8core curses)
