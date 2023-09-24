add_executable(LearnAlgorithm_main
        main.cpp)

add_subdirectory(algorithm)
add_subdirectory(test)

target_link_libraries(LearnAlgorithm_main
    PRIVATE
        algorithm
        test
)