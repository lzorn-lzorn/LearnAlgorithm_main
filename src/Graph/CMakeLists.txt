add_library(Graph "")

target_sources(Graph # ##
        PRIVATE
        graph_structure.hpp
        # ##
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/matrix.hpp # ##
)

target_include_directories(Graph # ##
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)