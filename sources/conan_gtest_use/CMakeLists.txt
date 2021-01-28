cmake_minimum_required(VERSION 3.18.1)
project(conan_gtest_use)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(conan_gtest_use
    main.cpp
    use.cpp)

target_link_libraries(conan_gtest_use ${CONAN_LIBS})
