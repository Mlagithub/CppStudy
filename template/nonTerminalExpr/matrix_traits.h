
#ifndef ACT_MATRIX_TYPE_TRAITS_HPP
#define ACT_MATRIX_TYPE_TRAITS_HPP

#include <iostream>
#include <type_traits>

template<typename T, size_t M, size_t N> 
struct Matrix;



template<typename T1, typename T2>
struct MatrixValueTypeTraits{
    using value_type = typename T1::value_type;
};

template<>
struct MatrixValueTypeTraits<float, double>{
    using value_type = float;
};

template<>
struct MatrixValueTypeTraits<float, float>{
    using value_type = float;
};

template<>
struct MatrixValueTypeTraits<double, float>{
    using value_type = float;
};

template<>
struct MatrixValueTypeTraits<double, double>{
    using value_type = double;
};

template<>
struct MatrixValueTypeTraits<double, int>{
    using value_type = double;
};

template<>
struct MatrixValueTypeTraits<int, double>{
    using value_type = double;
};



// ================== Add ================ //
template<class M1, class M2>
struct MatrixTypeTraitsAdd{
    private:
        static const bool sameShape = 
            M1::Row == M2::Row && M1::Column==M2::Column ? true : false;
        static const size_t Row = (sameShape) ? (M1::Row) : 0;
        static const size_t Column = (sameShape) ? (M1::Column) : 0;

    public:
        using value_type = Matrix<typename M1::value_type , Row, Column>;

};

template<class M1>
struct MatrixTypeTraitsAdd<M1, float>{
    static const size_t Row = M1::Row;
    static const size_t Column = M1::Column;
    using value_type = Matrix<typename MatrixValueTypeTraits<M1, float>::value_type, Row, Column>;
};

template<class M1>
struct MatrixTypeTraitsAdd<M1, double>{
    static const size_t Row = M1::Row;
    static const size_t Column = M1::Column;
    using value_type = Matrix<typename MatrixValueTypeTraits<M1, double>::value_type, Row, Column>;
};



// ================== Multipies ================ //
template<class M1, class M2>
struct MatrixTypeTraitsMultiply{
    private:
        static const bool sameShape = 
            M1::Row == M2::Row && M1::Column==M2::Column ? true : false;
        static const size_t Row = (!sameShape) ? (M1::Row) : 0;
        static const size_t Column = (!sameShape) ? (M2::Column) : 0;

    public:
        using value_type = Matrix<typename M1::value_type , Row, Column>;
};

template<class M1>
struct MatrixTypeTraitsMultiply<M1, float>{
    static const size_t Row = M1::Row;
    static const size_t Column = M1::Column;
    using value_type = Matrix<typename MatrixValueTypeTraits<M1, float>::value_type, Row, Column>;
};

template<class M1>
struct MatrixTypeTraitsMultiply<M1, double>{
    static const size_t Row = M1::Row;
    static const size_t Column = M1::Column;
    using value_type = Matrix<typename MatrixValueTypeTraits<M1, double>::value_type, Row, Column>;
};



// ================== Transpose ================ //
template<class M>
struct MatrixTypeTraitsTranspose{
    static const size_t Row = M::Column;
    static const size_t Column = M::Row;
    using value_type = Matrix<typename M::value_type, Row, Column>;
};


#endif
