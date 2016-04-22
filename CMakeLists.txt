cmake_minimum_required(VERSION 3.0)
project(chip8curses CXX)
set(PROJECT_VERSION "0.1")

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

add_subdirectory(lib/CHIP-8-Virtual-Machine-Core)

set(CMAKE_CXX_FLAGS "${MAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Weffc++ -std=c++11")

file(GLOB_RECURSE LOCAL_SOURCE_FILES "${CMAKE_SOURCE_DIR}/src/*.cc")
include_directories("${CMAKE_SOURCE_DIR}/include")

add_executable(${PROJECT_NAME} ${LOCAL_SOURCE_FILES})
