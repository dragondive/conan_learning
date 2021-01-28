cmake_minimum_required(VERSION 3.18)
project(random_use)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(random_use src/main.cpp)
target_link_libraries(random_use ${CONAN_LIBS})
