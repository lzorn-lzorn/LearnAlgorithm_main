add_library(Graph "")

target_sources(Graph # ##
        PRIVATE
        graph_structure.hpp
        matrix_in_array.hpp
        matrix_in_vector.hpp
        # ##
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/matrix_in_vector.hpp
        ${CMAKE_CURRENT_LIST_DIR}/matrix_in_array.hpp
        ${CMAKE_CURRENT_LIST_DIR}/graph_structure.hpp
)

target_include_directories(Graph # ##
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)