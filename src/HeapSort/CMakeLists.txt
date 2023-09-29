add_library(HeapSort "")

target_sources(HeapSort # ##
        PRIVATE
        HeapSort.cpp # ##
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/HeapSort.h # ##
)

target_include_directories(HeapSort # ##
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)