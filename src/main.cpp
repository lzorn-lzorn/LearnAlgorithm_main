//
// Created by 75742 on 2023/9/22.
//
#include "HeapSort/HeapSort.h"

int main(){
    std::vector<int> vec{ 0, 2, 9, 7, 4, 1, 8, 3, 6, 5};
    ltd::priority_queue<int> heap(vec.begin(),vec.end());
    heap.print();
    heap.heap_sort();
    heap.print();
    heap.pop();
    heap.print();
    heap.push(11);
    heap.print();
    return 0;
}