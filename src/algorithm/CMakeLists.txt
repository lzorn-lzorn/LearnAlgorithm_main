add_library(algorithm "")

target_sources(algorithm
    PRIVATE
        algorithm-test.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/algorithm-test.h
)

target_include_directories(algorithm
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)