add_executable(LearnAlgorithm_main
        main.cpp)


add_subdirectory(example)
# 当你添加一个新的目录时，使用add_subdirectory( 文件名 )  让cmake知道添加了这个新的目标
add_subdirectory(HeapSort)
target_link_libraries(LearnAlgorithm_main
    PRIVATE
        example # 并同时在这里添加 文件名，让cmake链接你的库
        HeapSort
)