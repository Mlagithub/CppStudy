
#ifndef ACT_MATRIX_TYPE_TRAITS_HPP
#define ACT_MATRIX_TYPE_TRAITS_HPP

//#include <type_traits>

template<typename T1, typename T2>
struct MatrixValueTypeTraits;

template<typename T1>
struct MatrixValueTypeTraits<T1, T1>{
    using type = T1;
};

template<>
struct MatrixValueTypeTraits<float, double>{
    using type = double;
};


template<>
struct MatrixValueTypeTraits<double, float>{
    using type = double;
};


template<>
struct MatrixValueTypeTraits<double, int>{
    using type = double;
};

template<>
struct MatrixValueTypeTraits<int, double>{
    using type = double;
};


template<>
struct MatrixValueTypeTraits<float, int>{
    using type = float;
};

template<>
struct MatrixValueTypeTraits<int, float>{
    using type = float;
};

template<typename T, typename U>
using TURetType = typename MatrixValueTypeTraits<T, U>::type;

#endif
