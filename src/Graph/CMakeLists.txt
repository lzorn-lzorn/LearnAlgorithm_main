add_library(Graph "")

target_sources(Graph # ##
        PRIVATE
        HeapSort.cpp # ##
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/matrix.h # ##
)

target_include_directories(Graph # ##
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)