cmake_minimum_required(VERSION 3.18.1)
project(conan_gtest)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include_directories(src)
add_subdirectory(src)

