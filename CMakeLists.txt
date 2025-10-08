cmake_minimum_required(VERSION 3.10)

project(White_Noise LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SDL2 REQUIRED CONFIG)

include_directories(${SDL2_INCLUDE_DIRS})

add_executable(noise src/main.cpp)

target_link_libraries(noise ${SDL2_LIBRARIES})

add_custom_target(clear
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/CMakeFiles
    COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/CMakeCache.txt
    COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/*.cmake
    COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/Makefile
    DEPENDS noise
)
