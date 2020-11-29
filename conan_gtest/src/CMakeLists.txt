set(BINARY ${CMAKE_PROJECT_NAME})

set(SOURCES
    main.cpp
    sample.h
    sample.cpp
)

add_executable(${BINARY}_run ${SOURCES})
add_library(${BINARY} STATIC ${SOURCES})
