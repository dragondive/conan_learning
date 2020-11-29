set(BINARY ${CMAKE_PROJECT_NAME}_test)

set(TEST_SOURCES
    gtest_main.cpp
    sample_test.cpp
)

add_executable(${BINARY} ${TEST_SOURCES})
add_test(NAME ${BINARY} COMMAND ${BINARY})

target_link_libraries(${BINARY} PUBLIC conan_gtest ${CONAN_LIBS})
