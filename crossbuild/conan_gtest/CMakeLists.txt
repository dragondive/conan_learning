cmake_minimum_required(VERSION 3.18.1)
project(conan_gtest)

add_definitions("-std=c++14")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include_directories(src)
add_subdirectory(src)

