//
// Created by 75742 on 2023/10/1.
//

#ifndef LEARNALGORITHM_MAIN_MATRIX_IN_ARRAY_HPP
#define LEARNALGORITHM_MAIN_MATRIX_IN_ARRAY_HPP
#include <iostream>
#include <cstdint>
#include <array>
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
        using matrix_t = std::array<std::array<std::unique_ptr<Type>, X>, X>;
        using vector_t = std::array<std::unique_ptr<Type>, X>;
        std::array<std::array<std::unique_ptr<Type>, X>, X> M;
        int len = X * X;
        template<typename _Tp, int Length>

        matrix_t& multi(const matrix<Type, X, X>& m1, const matrix<Type, X, X>& m2) const noexcept;
        matrix_t power(uint32_t x) const noexcept;
        matrix_t& inverse(uint32_t x) const;
    public:
#if defined(_DEBUG) || defined(DEBUG)
        static_assert((X == 0) , "Neither X nor Y is zero!");
#endif

        template<typename Container>
        matrix(Container vec) { }
        matrix(const matrix<Type, X, X>& m) = delete;
        matrix(const matrix<Type, X, X>&& m){ }
        matrix& operator= (const matrix<Type, X, X>& m) = delete;
        matrix&& operator= (const matrix<Type, X, X>&& m){ }
        ~matrix();

        std::array<std::unique_ptr<Type>, X*X> flat() noexcept{ return this->M; }
        void print() const;
        Type& at(const uint32_t x, const uint32_t y) {}
        vector_t& get_row_vector(const uint32_t x){}
        vector_t& get_col_vector(const uint32_t y){}

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
        HAVEZERO_ASSERT((X),(Y));
        using row_vec_t = std::array<std::unique_ptr<Type>, X>;
        using col_vec_t = std::array<std::unique_ptr<Type>, Y>;
        std::array<std::array<std::unique_ptr<Type>, X>, Y> vec;

    public:
        template<typename Container>
        matrix(Container vec) ;
        matrix(const matrix<Type, X, Y>& m);
        matrix(const matrix<Type, X, Y>&& m);
        matrix& operator= (const matrix<Type, X, Y>& m);
        matrix&& operator= (const matrix<Type, X, Y>&& m);
        ~matrix();


        Type& at(const uint32_t x, const uint32_t y) {}
        row_vec_t& get_row_vector(const uint32_t x){}
        col_vec_t& get_col_vector(const uint32_t y){}

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

#endif //LEARNALGORITHM_MAIN_MATRIX_IN_ARRAY_HPP
