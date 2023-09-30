//
// Created by 75742 on 2023/9/30.
//

#ifndef LEARNALGORITHM_MAIN_GRAPH_STRUCTURE_H
#define LEARNALGORITHM_MAIN_GRAPH_STRUCTURE_H
#include <iostream>
#include <cstdint>
#include <vector>
#include <memory>
namespace ltd{
    enum class vec_type { None, XIsOne, YIsOne, BothOne};
    template<int X, int Y>
    struct vec_info{
        template <int DummyX = X, int DummyY = Y>
        static auto get_type(){
            if constexpr ( DummyX==1 && DummyY==1 ){
                return std::integral_constant<vec_type, vec_type::BothOne>{};
            }
            else if constexpr ( DummyX==1 && DummyY==0 ){
                return std::integral_constant<vec_type, vec_type::XIsOne>{};
            }else if constexpr ( DummyX==0 && DummyY==1 ){
                return std::integral_constant<vec_type, vec_type::YIsOne>{};
            }else {
                return std::integral_constant<vec_type, vec_type::None>{};
            }
        }

        using value = typename decltype(get_type())::value;
    };
    template <typename Type, int X, int Y, vec_type VectorType = ltd::vec_info<X, Y>::value>
    struct matrix;

    template <typename Type, int X, int Y>
    struct matrix<Type, X, Y, ltd::vec_type::None>{
    private:
        std::vector<std::unique_ptr<Type>> vec;

        template<typename _Tp, int Length>
        struct get_proxy{
            std::vector<std::unique_ptr<Type>> row;
            int x;
            get_proxy(std::vector<std::unique_ptr<Type>>& row, int x) : row(row), x(x){}
            Type& operator[](uint32_t col){
                return *row.at(x * Length + col);
            }
        };
        uint64_t pair_to_one(const uint32_t x, const uint32_t y) const{
            // 将坐标变成线性
        }
        bool is_sparse(){
            // 是否是稀疏矩阵 非零元 : 零元 = 1 : 99
        }


        matrix& multi(const matrix<Type, X, Y>& m1, const matrix<Type, X, Y>& m2) const noexcept;
        matrix& power(uint32_t x) const noexcept;
        matrix& inverse(uint32_t x) const;
    public:
        matrix(std::vector<Type> vec) ;
        matrix(const matrix<Type, X, Y>& m);
        matrix(const matrix<Type, X, Y>&& m);
        matrix& operator= (const matrix<Type, X, Y>& m);
        matrix&& operator= (const matrix<Type, X, Y>&& m);
        ~matrix();


        Type& get(const uint32_t x, const uint32_t y) const {}
        void set(const uint32_t x, const uint32_t y) {}
        std::vector<std::unique_ptr<Type>>& get_X_vector(const uint32_t x){}
        std::vector<std::unique_ptr<Type>>& get_Y_vector(const uint32_t y){}
        get_proxy<Type, Y>& operator[](const uint32_t x){
            return get_proxy<Type, Y>(get_X_vector(), x);
        }
        matrix& operator+=(const matrix<Type, X, Y>& m) noexcept;
        matrix& operator-=(const matrix<Type, X, Y>& m) noexcept;
        matrix& operator*=(const matrix<Type, X, Y>& m) noexcept;
        friend matrix& operator*(const matrix<Type, X, Y>& m1, const matrix<Type, X, Y>& m2) noexcept;
        friend matrix& operator+(const matrix<Type, X, Y>& m1, const matrix<Type, X, Y>& m2) noexcept;
        friend matrix& operator-(const matrix<Type, X, Y>& m1, const matrix<Type, X, Y>& m2) noexcept;
    };
    template <typename Type, int X, int Y>
    struct matrix<Type, X, Y, ltd::vec_type::XIsOne>{

    };
    template <typename Type, int X, int Y>
    struct matrix<Type, X, Y, ltd::vec_type::YIsOne>{};
    template <typename Type, int X, int Y>
    struct matrix<Type, X, Y, ltd::vec_type::BothOne>{};
}

#endif //LEARNALGORITHM_MAIN_GRAPH_STRUCTURE_H
