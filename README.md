# LearnAlgorithm
这是一个仅仅用于算法学习的仓库，您可以通过约定好的格式对您的算法和数据结构进行测试，以便于您进行算法的学习
## 使用语言
本仓库使用C/C++语言来进行算法的测试，并使用cmake来构建项目。但您无需关注cmake的具体细节，只需要按照我们约定好的格式来书写和提交代码. C++的版本请使用C++17及以上版本
## 目录结构
该项目将所有的算法统一视为第三方库，所以在进行编写的时候，创建一个文件夹名，在这个文件下按照给出的例子，写好CMakeLists.txt 并在外部的 CMakeLists.txt 中添加 你自己的库，这样就可以在main中进行测试。
后续会考虑加入专门的test文件，到时候的具体方法会在之后更新。

如果你已经掌握Cmake，请忽略一下例子

例如: 当你创建了 AAA 文件，里面是 你写的任何东西，请在文件夹下创建CMakeList.txt，并写
```cmake
add_library(AAA "")

target_sources(AAA # 
        PRIVATE
        AAA.cpp # 
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/AAA.h #
)

target_include_directories(AAA # 
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)
```

并且在src/CMakeList.txt中添加你的内容
```cmake
add_subdirectory(AAA)

target_link_libraries(LearnAlgorithm_main
    PRIVATE
        AAA
)
```
### 关于头文件和源文件
在头文件也就是.h文件中，以注释的形式注明函数签名，即参数的含义已经返回值的含义
对于.cpp文件 请将您想练习的算法写入对应的文件夹中，对于每一个算法或者数据结构都要以md为格式给出详细的文档，也即您对这个算法和数据结构的理解以及您的参考资料。作为学习资料请尽可能全面和准确

您可以写任意的算法和数据结构，包括各种刷题网站上的题目您都可以拿来操作并添加到这个仓库中，只是需要您补足文档。
文档内容包括但不仅限于（并不需要全都包括，只要可以表达清楚）：
* 问题的出处
* 问题的解决思路
* 算法的实现细节
* 算法的分析
* 参考资料

### 关于测试文件
测试文件为.cpp文件不需要在include中添加头文件，同时测试用例要尽可能全面并给出注释

