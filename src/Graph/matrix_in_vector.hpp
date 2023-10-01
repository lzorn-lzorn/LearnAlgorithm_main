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
    namespace detail{

#if defined(_DEBUG) || defined(DEBUG)
#define HAVEZERO_ASSERT((X),(Y)) \
            static_assert(((X) == 0) || ((Y) == 0), "Neither X nor Y is zero!");
#else
#define HAVEZERO_ASSERT(X,Y)
#endif
        template <int X, int Y>
        struct is_square{
            static constexpr bool value = false;
        };
        template <int X>
        struct is_square<X, X>{
            static constexpr bool value = true;
        };

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
    }

    template <typename Type, int X, int Y,
            detail::vec_type VectorType = ltd::detail::vec_info<X, Y>::value,
            bool IsSquare = ltd::detail::is_square<X, Y>::value>
    struct matrix;

    template <typename Type, int X>
    struct matrix<Type, X, X, ltd::detail::vec_type::None, true>{
    private:
        HAVEZERO_ASSERT((X),(X));
        std::vector<std::unique_ptr<Type>> vec;
        int len = X * X;
        template<typename _Tp, int Length>
        struct get_proxy{
            std::vector<std::unique_ptr<Type>> row;
            int x;
            get_proxy(std::vector<std::unique_ptr<Type>>& row, int x) : row(row), x(x){}
            Type& operator[](uint32_t col){
                return *row.at(x * Length + col);
            }
        };
        uint64_t pair_to_one (const uint32_t x, const uint32_t y) const{
            // 将坐标变成线性
            return this->vec.at((x-1)*X+y);
        }
        bool is_sparse(){
            // 是否是稀疏矩阵 非零元 : 零元 = 1 : 99
            uint64_t is_zero = 0;
            for(uint64_t i=0; i<len; i++){
                if(*(this->vec.at(i)) == 0){
                    is_zero++;
                }
            }
            return ( is_zero / len ) > 0.9;
        }


        matrix<Type, X, X>& multi(const matrix<Type, X, X>& m1, const matrix<Type, X, X>& m2) const noexcept;
        matrix<Type, X, X>& power(uint32_t x) const noexcept;
        matrix<Type, X, X>& inverse(uint32_t x) const;
    public:
#if defined(_DEBUG) || defined(DEBUG)
        static_assert((X == 0) , "Neither X nor Y is zero!");
#endif
        matrix(std::vector<Type> vec) {

            for(auto it=vec.begin(); it!=vec.end(); it++){
                this->vec.emplace_back(std::make_unique<Type>(*it));
            }
            int size = vec.size();
            while(len > size){
                this->vec.emplace_back(std::make_unique<Type>(Type()));
                size++;
            }
        }
        matrix(const matrix<Type, X, X>& m) = delete;
        matrix(const matrix<Type, X, X>&& m){
            this->vec = std::vector<Type>(std::move(m.flat()));
        }
        matrix& operator= (const matrix<Type, X, X>& m) = delete;
        matrix&& operator= (const matrix<Type, X, X>&& m){
            return ltd::matrix<Type, X, X>(std::move(m.flat()));
        }
        ~matrix();

        std::vector<std::unique_ptr<Type>> flat() noexcept{ return this->vec; }
        void print() const;
        Type& get(const uint32_t x, const uint32_t y) const {}
        void set(const uint32_t x, const uint32_t y) {}
        std::vector<std::unique_ptr<Type>>& get_X_vector(const uint32_t x){}
        std::vector<std::unique_ptr<Type>>& get_Y_vector(const uint32_t y){}
        get_proxy<Type, X>& operator[](const uint32_t x){
            return get_proxy<Type, X>(get_X_vector(), x);
        }
        matrix<Type, X, X>& operator+=(const matrix<Type, X, X>& m) noexcept;
        matrix<Type, X, X>& operator-=(const matrix<Type, X, X>& m) noexcept;

        template<int Z>
        matrix<Type, X, Z>& operator*=(const matrix<Type, X, Z>& m) noexcept;
        template<int Z>
        friend matrix<Type, X, Z>& operator*(const matrix<Type, X, X>& m1, const matrix<Type, X, Z>& m2) noexcept;
        friend matrix<Type, X, X>& operator+(const matrix<Type, X, X>& m1, const matrix<Type, X, X>& m2) noexcept;
        friend matrix<Type, X, X>& operator-(const matrix<Type, X, X>& m1, const matrix<Type, X, X>& m2) noexcept;

    };

    template <typename Type, int X, int Y>
    struct matrix<Type, X, Y, ltd::detail::vec_type::None, false>{
    private:
        std::vector<std::unique_ptr<Type>> vec;
        HAVEZERO_ASSERT((X),(Y));
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

    public:
#if defined(_DEBUG) || defined(DEBUG)
        static_assert((X == 0) || (Y == 0), "Neither X nor Y is zero!");
#endif
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

        template<int Z>
        matrix& operator*=(const matrix<Type, Y, Z>& m) noexcept;
        template<int Z>
        friend matrix& operator*(const matrix<Type, X, Y>& m1, const matrix<Type, X, Z>& m2) noexcept;
        friend matrix& operator+(const matrix<Type, X, Y>& m1, const matrix<Type, X, Y>& m2) noexcept;
        friend matrix& operator-(const matrix<Type, X, Y>& m1, const matrix<Type, X, Y>& m2) noexcept;
    };

    template <typename Type, int X, int Y>
    struct matrix<Type, X, Y, ltd::detail::vec_type::XIsOne, false>{
        HAVEZERO_ASSERT((X),(Y));
    };
    template <typename Type, int X, int Y>
    struct matrix<Type, X, Y, ltd::detail::vec_type::YIsOne, false>{
        HAVEZERO_ASSERT((X),(Y));
    };
    template <typename Type, int X, int Y>
    struct matrix<Type, X, Y, ltd::detail::vec_type::BothOne, false>{
    private:
        HAVEZERO_ASSERT((X),(Y));
    public:
        Type& data;
    };

}

#endif //LEARNALGORITHM_MAIN_GRAPH_STRUCTURE_H
