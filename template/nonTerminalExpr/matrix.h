
#ifndef ACT_MATRIX_HPP
#define ACT_MATRIX_HPP

#include <iostream>
#include <ostream>
#include <array>

#include "matrix_traits.h"


using std::cout;


////////////////////////////////
//  Matrix
///////////////////////////////
template<typename T, size_t RowN = 1, size_t ColumnN = RowN>
struct Matrix{
    private:
        //std::array<T, RowN*ColumnN>  data;
        const size_t M = Row;
        const size_t N = Column;

    public:
        std::array<T, RowN*ColumnN>  data;
        static const size_t Row = RowN;
        static const size_t Column = ColumnN;
        using value_type = T;

    public:

        void set(T val){ *data = val;}
        void get(void){return *data;}

        void set(size_t i, size_t j, T val) noexcept {
           data[i*N+j] = val;
        }

        T get(size_t i, size_t j){
            if(i>=M || j>=N){
            }
            return data[i*N+j];
        }

        friend std::ostream& operator<<(std::ostream& os, const Matrix& m){
            for(auto i = 0; i < Row; ++i){
                os << "[ ";
                for(auto j = 0; j < Column; ++j){
                    os << m.data[i*Column+j] << ", ";
                }
                os << "\b\b ]\n";
            }
            return os;
        }

};




////////////////////////////////
//  Plus
///////////////////////////////
template<class M1, class M2>
struct plusM{
    using value_type = typename MatrixTypeTraitsAdd<typename M1::value_type, typename M2::value_type>::value_type;
    value_type operator()(const value_type& m1, const value_type& m2){
        value_type rst;
        const size_t Row = value_type::Row;
        const size_t Column = value_type::Column;
        for(auto i = 0; i<Row; ++i){
            for(auto j = 0; j<Column; ++j){
                //rst.set(i, j, m1.get(i,j)+m2.get(i,j));
                rst.data[i*Column+j] = m1.data[i*Column+j] + m2.data[i*Column+j];
            }
        }
        return rst;
    }

};

template<class M1>
struct plusM<M1, float>{
    private:
        using T = float;
    public:
    using value_type = typename MatrixTypeTraitsAdd<typename M1::value_type, T>::value_type;
    value_type operator()(const value_type& m1, T m2){
        value_type rst;
        const size_t Row = value_type::Row;
        const size_t Column = value_type::Column;
        for(auto i = 0; i<Row; ++i){
            for(auto j = 0; j<Column; ++j){
                //rst.set(i, j, m1.get(i,j)+m2);
                rst.data[i*Column+j] = m1.data[i*Column+j] + m2;
            }
        }
        return rst;
    }
};

template<class M1>
struct plusM<float, M1>{
    private:
        using T = float;
    public:
    using value_type = typename MatrixTypeTraitsAdd<typename M1::value_type, T>::value_type;
    value_type operator()(T m1, const value_type& m2){
        value_type rst;
        const size_t Row = value_type::Row;
        const size_t Column = value_type::Column;
        for(auto i = 0; i<Row; ++i){
            for(auto j = 0; j<Column; ++j){
                //rst.set(i, j, m2.get(i,j)+m1);
                rst.data[i*Column+j] = m2.data[i*Column+j] + m1;
            }
        }
        return rst;
    }

};


template<class M1>
struct plusM<M1, double>{
    private:
        using T = double;
    public:
    using value_type = typename MatrixTypeTraitsAdd<typename M1::value_type, T>::value_type;
    value_type operator()(const value_type& m1, T m2){
        value_type rst;
        const size_t Row = value_type::Row;
        const size_t Column = value_type::Column;
        for(auto i = 0; i<Row; ++i){
            for(auto j = 0; j<Column; ++j){
                //rst.set(i, j, m1.get(i,j)+m2);
                rst.data[i*Column+j] = m1.data[i*Column+j] + m2;
            }
        }
        return rst;
    }
};

template<class M1>
struct plusM<double, M1>{
    private:
        using T = double;
    public:
    using value_type = typename MatrixTypeTraitsAdd<typename M1::value_type, T>::value_type;
    value_type operator()(T m1, const value_type& m2){
        value_type rst;
        const size_t Row = value_type::Row;
        const size_t Column = value_type::Column;
        for(auto i = 0; i<Row; ++i){
            for(auto j = 0; j<Column; ++j){
                //rst.set(i, j, m2.get(i,j)+m1);
                rst.data[i*Column+j] = m2.data[i*Column+j] + m1;
            }
        }
        return rst;
    }

};



////////////////////////////////
//  Minus
///////////////////////////////
template<class M1, class M2>
struct minusM{
    using value_type = typename MatrixTypeTraitsAdd<typename M1::value_type, typename M2::value_type>::value_type;
    value_type operator()(const value_type& m1, const value_type& m2){
        value_type rst;
        const size_t Row = value_type::Row;
        const size_t Column = value_type::Column;
        for(auto i = 0; i<Row; ++i){
            for(auto j = 0; j<Column; ++j){
                //rst.set(i, j, m1.get(i,j)+m2.get(i,j));
                rst.data[i*Column+j] = m1.data[i*Column+j] - m2.data[i*Column+j];
            }
        }
        return rst;
    }
};

template<class M1>
struct minusM<M1, float>{
    private:
        using T = float;
    public:
    using value_type = typename MatrixTypeTraitsAdd<typename M1::value_type, T>::value_type;
    value_type operator()(const value_type& m1, T m2){
        value_type rst;
        const size_t Row = value_type::Row;
        const size_t Column = value_type::Column;
        for(auto i = 0; i<Row; ++i){
            for(auto j = 0; j<Column; ++j){
                //rst.set(i, j, m1.get(i,j)+m2);
                rst.data[i*Column+j] = m1.data[i*Column+j] - m2;
            }
        }
        return rst;
    }
};

template<class M1>
struct minusM<float, M1>{
    private:
        using T = float;
    public:
    using value_type = typename MatrixTypeTraitsAdd<typename M1::value_type, T>::value_type;
    value_type operator()(T m1, const value_type& m2){
        value_type rst;
        const size_t Row = value_type::Row;
        const size_t Column = value_type::Column;
        for(auto i = 0; i<Row; ++i){
            for(auto j = 0; j<Column; ++j){
                //rst.set(i, j, m2.get(i,j)+m1);
                rst.data[i*Column+j] = m1 - m2.data[i*Column+j];
            }
        }
        return rst;
    }

};


template<class M1>
struct minusM<M1, double>{
    private:
        using T = double;
    public:
    using value_type = typename MatrixTypeTraitsAdd<typename M1::value_type, T>::value_type;
    value_type operator()(const value_type& m1, T m2){
        value_type rst;
        const size_t Row = value_type::Row;
        const size_t Column = value_type::Column;
        for(auto i = 0; i<Row; ++i){
            for(auto j = 0; j<Column; ++j){
                //rst.set(i, j, m1.get(i,j)+m2);
                rst.data[i*Column+j] = m1.data[i*Column+j] - m2;
            }
        }
        return rst;
    }
};


template<class M1>
struct minusM<double, M1>{
    private:
        using T = double;
    public:
    using value_type = typename MatrixTypeTraitsAdd<typename M1::value_type, T>::value_type;
    value_type operator()(T m1, const value_type& m2){
        value_type rst;
        const size_t Row = value_type::Row;
        const size_t Column = value_type::Column;
        for(auto i = 0; i<Row; ++i){
            for(auto j = 0; j<Column; ++j){
                //rst.set(i, j, m2.get(i,j)+m1);
                rst.data[i*Column+j] = m1 - m2.data[i*Column+j];
            }
        }
        return rst;
    }

};




////////////////////////////////
//  Multiply
///////////////////////////////
template<class M1, class M2>
struct multiplyM{
    using value_type = typename MatrixTypeTraitsMultiply<typename M1::value_type, typename M2::value_type>::value_type;
    value_type operator()(const typename M1::value_type& m1, const typename M2::value_type& m2){
        value_type rst;
        const size_t Row = value_type::Row;
        const size_t Column = value_type::Column;
        const size_t c1 = M1::value_type::Column;
        for(auto i = 0; i<Row; ++i){
            for(auto j = 0; j<Column; ++j){
                auto tmp = 0.0;
                for(auto k = 0; k<c1; ++k){
                    //TODO can not use +=
                    tmp += m1.data[i*c1+k] * m2.data[k*Column+j];
                    //rst.data[i*Column+j] += m1.data[i*c1+k] * m2.data[k*Column+j]; 
                }
                rst.data[i*Column+j] = tmp;
            }
        }
        return rst;
    }
};

template<class M1>
struct multiplyM<float, M1>{
    private:
        using T = float;
    public:
    using value_type = typename MatrixTypeTraitsMultiply<typename M1::value_type, T>::value_type;
    value_type operator()(const T m1, const typename M1::value_type& m2){
        value_type rst;
        const size_t Row = value_type::Row;
        const size_t Column = value_type::Column;
        for(auto i = 0; i<Row; ++i){
            for(auto j = 0; j<Column; ++j){
                rst.data[i*Column+j] = m2.data[i*Column+j] * m1;
            }
        }
        return rst;
    }
};

template<class M1>
struct multiplyM<M1, float>{
    private:
        using T = float;
    public:
    using value_type = typename MatrixTypeTraitsMultiply<typename M1::value_type, T>::value_type;
    value_type operator()(const typename M1::value_type& m1, const T m2){
        value_type rst;
        const size_t Row = value_type::Row;
        const size_t Column = value_type::Column;
        for(auto i = 0; i<Row; ++i){
            for(auto j = 0; j<Column; ++j){
                rst.data[i*Column+j] = m1.data[i*Column+j] * m2;
            }
        }
        return rst;
    }
};

template<class M1>
struct multiplyM<double, M1>{
    private:
        using T = double;
    public:
    using value_type = typename MatrixTypeTraitsMultiply<typename M1::value_type, T>::value_type;
    value_type operator()(T m1, const typename M1::value_type& m2){
        value_type rst;
        const size_t Row = value_type::Row;
        const size_t Column = value_type::Column;
        for(auto i = 0; i<Row; ++i){
            for(auto j = 0; j<Column; ++j){
                rst.data[i*Column+j] = m2.data[i*Column+j] * m1;
            }
        }
        return rst;
    }
};

template<class M1>
struct multiplyM<M1, double>{
    private:
        using T = double;
    public:
    using value_type = typename MatrixTypeTraitsMultiply<typename M1::value_type, T>::value_type;
    value_type operator()(const typename M1::value_type& m1, T m2){
        value_type rst;
        const size_t Row = value_type::Row;
        const size_t Column = value_type::Column;
        for(auto i = 0; i<Row; ++i){
            for(auto j = 0; j<Column; ++j){
                rst.data[i*Column+j] = m1.data[i*Column+j] * m2;
            }
        }
        return rst;
    }
};




////////////////////////////////
//  Transpose
///////////////////////////////
template<typename T>
struct transposeM{
    using value_type = typename MatrixTypeTraitsTranspose<typename T::value_type>::value_type;
    static const size_t Row = T::value_type::Row;
    static const size_t Column = T::value_type::Column;
    value_type operator()(const typename T::value_type& m){
        value_type rst;
        for(auto i = 0; i<Row; ++i){
            for(auto j = 0; j<Column; ++j){
                rst.data[j*Row+i] = m.data[i*Column+j];
            }
        }
        return rst;
    };
};





////////////////////////////////
//  Literal 
///////////////////////////////
template<class T>
struct Literal{
    private:
        T val;
    public:
        using value_type = T;
        Literal(T& v) : val(v){}
        T eval(...){return val;}
};


template<>
struct Literal<double>{
    private:
        using T = double;
        T val;
    public:
        using value_type = T;
        Literal(T& v) : val(v){}
        T eval(...){return val;}
};

template<>
struct Literal<float>{
    private:
        using T = float;
        T val;
    public:
        using value_type = T;
        Literal(T& v) : val(v){}
        T eval(...) noexcept {return val;}
};




////////////////////////////////
//  Variable
///////////////////////////////
template<class T>
struct Variable{
    using value_type = T;
    T eval(T& v) noexcept {return v;}
};

template<>
struct Variable<double>{
    private:
        using T = double;
    public:
        using value_type = T;
        T eval(T& v){return v;}
};

template<>
struct Variable<float>{
    private:
        using T = float;
    public:
        using value_type = T;
        T eval(T& v){return v;}
};



////////////////////////////////
//  Tratis
///////////////////////////////
template<class Expr>
struct ExprTypeTraits{
    using expr_type = Expr;
};

template<>
struct ExprTypeTraits<int>{
    using expr_type = Literal<int>;
};

template<>
struct ExprTypeTraits<float>{
    using expr_type = Literal<float>;
};

template<>
struct ExprTypeTraits<double>{
    using expr_type = Literal<double>;
};




////////////////////////////////
//  BinaryExpr
///////////////////////////////
template<typename Expr1, typename Expr2, typename Op>
struct BinaryExpr{
    private:
        typename ExprTypeTraits<Expr1>::expr_type e1;
        typename ExprTypeTraits<Expr2>::expr_type e2;
        Op op;

    public:
        using value_type = typename Op::value_type;

        BinaryExpr(Expr1& ee1, Expr2& ee2, Op opp=Op()):
            e1(ee1), e2(ee2), op(opp) {}

        value_type eval(value_type& v){
            return op(e1.eval(v), e2.eval(v));
        }
};


////////////////////////////////
//  UnaryExpr
///////////////////////////////
template<typename Expr, typename Op>
struct UnaryExpr{
    private:
        typename ExprTypeTraits<Expr>::expr_type e1;
        Op op;

    public:
        using value_type = typename Op::value_type;

        UnaryExpr(Expr& ee1, Op opp=Op()):
            e1(ee1), op(opp) {}

        value_type eval(typename Expr::value_type& v){
            return op(e1.eval(v));
        }
};




////////////////////////////////
//  Overload operators
///////////////////////////////
template<typename M1, typename M2>
auto operator+(M1 m1, M2 m2){
    return BinaryExpr<M1, M2, plusM<M1, M2>>(m1, m2);
};


template<typename M1, typename M2>
auto operator-(M1 m1, M2 m2){
    return BinaryExpr<M1, M2, minusM<M1, M2>>(m1, m2);
};


template<typename M1, typename M2>
auto operator*(M1 m1, M2 m2){
    return BinaryExpr<M1, M2, multiplyM<M1, M2>>(m1, m2);
};


// transpose
template<typename M>
auto operator~(M m){
    return UnaryExpr<M, transposeM<M>>(m);
};






#endif
