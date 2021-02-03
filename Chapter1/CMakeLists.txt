cmake_minimum_required(VERSION 3.17)
project(Chapter1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include_directories()

add_executable(Chapter1 main.cpp Game.cpp Game.h)

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

target_link_libraries(Chapter1 ${SDL2_LIBRARIES})