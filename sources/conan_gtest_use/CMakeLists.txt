cmake_minimum_required(VERSION 3.18.1)
project(conan_gtest_use)

add_definitions("-std=c++11")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(conan_gtest_use conan_gtest_use.cpp)
target_link_libraries(conan_gtest_use ${CONAN_LIBS})
