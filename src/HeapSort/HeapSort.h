//
// Created by 75742 on 2023/9/25.
//

#ifndef LEARNALGORITHM_MAIN_HEAPSORT_H
#define LEARNALGORITHM_MAIN_HEAPSORT_H
#include <iostream>
#include <vector>
#include <memory>
namespace ltd {
    template<typename Type>
    struct less_compare_unique_ptr{
        bool operator()(const std::unique_ptr<Type>& a, const std::unique_ptr<Type>& b){
            if (!a && !b) return false;
            if (!a) return true;
            if (!b) return false;
            return (*a) < (*b);
        }
    };
    template<typename Type>
    struct greater_compare_unique_ptr{
        bool operator()(const std::unique_ptr<Type>& a, const std::unique_ptr<Type>& b){
            if (!a && !b) return false;
            if (!a) return true;
            if (!b) return false;
            return (*a) > (*b);
        }
    };
    template <typename Type,
            typename Container = std::vector<std::unique_ptr<Type>>,
            typename Cmp = ltd::less_compare_unique_ptr<Type>
             >
    class priority_queue{
    private:
        [[nodiscard]] int parent(const int i) const noexcept { return (i - 1) / 2; }
        [[nodiscard]] int left(const int i) const noexcept { return 2 * i + 1; }
        [[nodiscard]] int right(const int i) const noexcept { return 2 * i + 2; }
        // [[nodiscard]] int brother(const int i) const noexcept { return i % 2 == 0 ? i + 1 : i - 1; }
        void up(int begin, int end) {
            int i = end;
            int parent_idx = parent(i);
            while(parent_idx >= begin){
                if(cmp(heap.at(parent_idx), heap.at(i))){
                    std::swap(heap.at(i), heap.at(parent_idx));
                    i = parent_idx;
                    parent_idx = parent(i); // 迭代的和双亲比较
                }else{
                    break;
                }
            }
        }
        void down(int begin, int end){
            int i = begin;
            int left_idx = left(i);
            int right_idx = right(i);
            int max_or_min = 0;
            while(left_idx <= end){
                if(right_idx <= end && cmp(heap.at(right_idx), heap.at(left_idx))){
                    max_or_min = right_idx;
                    // std::cout << "max_or_min=" << max_or_min << std::endl;
                    // std::cout << "cmp=right_idx" << std::endl;
                }else{
                    max_or_min = left_idx;
                    // std::cout << "max_or_min=" << max_or_min << std::endl;
                    // std::cout << "cmp=left_idx" << std::endl;
                }
                if(cmp(heap.at(max_or_min),heap.at(i))){
                    std::swap(heap.at(max_or_min), (heap.at(i)));
                    i = max_or_min;
                    left_idx = left(i);
                    right_idx = right(i);
                }else{
                    break;
                }
            }
        }
        void recursion_down(int x) {
            int i = x;
            int left_idx = left(i);
            int right_idx = right(i);
            int max_or_min = (left_idx <= size && cmp(heap.at(left_idx), heap.at(i))) ? left_idx : i;
            if(right_idx <= size && cmp(heap.at(right_idx), heap.at(max_or_min))){
                max_or_min = right_idx;
            }
            if(max_or_min != i){
                std::swap(heap.at(max_or_min), heap.at(i));
                recursion_down(max_or_min);
            }
        }
        void heapify(){
            for(int i=parent(size); i >= 0; i--){
                down(i, size);
            }
        }

        Cmp cmp;
        Container heap;
        int size { 0 };
    public:
        priority_queue() = default;
        template<typename Iterator>
        explicit priority_queue(Iterator begin, Iterator end){
            for (auto it = begin; it != end; ++it) {
                heap.emplace_back(std::make_unique<Type>(*it));
            }
            size = heap.size() - 1;
            heapify();
        }
        explicit priority_queue(Container& container) {
            for (auto& elem : container) {
                heap.emplace_back(std::make_unique<Type>(elem));
            }
            size = heap.size() - 1;

            heapify();
        }
        ~priority_queue() = default;
        priority_queue(const priority_queue& heap) = delete;
        priority_queue(const priority_queue&& heap) = delete;
        priority_queue<Type> operator=(const priority_queue& heap) = delete;
        priority_queue<Type> operator=(const priority_queue&& heap) = delete;

        void pop(){
            heap.at(0) = std::move(heap.at(size));
            heap.pop_back();
            size--;
            heapify();
            heap_sort();
        }
        void push(const Type& elem){
            heap.emplace_back(std::make_unique<Type>(elem));
            size++;
            heapify();
            heap_sort();
        }
        Type& top() const noexcept{ return *(heap.at(0)); }

        void heap_sort(){
            for(int i=size; i>0; i--){
                std::swap(heap.at(i), heap.at(0));
                down(0, i-1);
            }
            std::cout << std::endl;
        }

        void print() const noexcept{
            for( int i=0; i<=size; i++ ){
                std::cout << *(heap.at(i)) << " ";
            }
            std::cout << std::endl;
        }
    };
}
#endif //LEARNALGORITHM_MAIN_HEAPSORT_H
