


#include "matrixTraits.h"

#include <array>
#include <vector>
#include <iostream>
using std::array;
using std::vector;

#ifndef ACT_MATRIX_HPP
#define ACT_MATRIX_HPP


////////////////////////////////
//  Expr
///////////////////////////////
template<typename T>
struct Expr{
    inline const T& self(void) const {
        return *static_cast<const T*>(this);
    }
};


////////////////////////////////
//  Literal
///////////////////////////////
template<typename T>
struct Literal : public Expr<Literal<T>>{
    const T& val;
    using value_type = T;
    Literal(const T& v) : val(v) {}
    inline T eval(int, int) const {return val;}
};

template<>
struct Literal<double> : public Expr<Literal<double>>{
    using value_type = double;
    const value_type val;
    Literal(const value_type v) : val(v) {}
    inline value_type eval(int, int) const {return val;}
};

template<>
struct Literal<float> : public Expr<Literal<float>>{
    using value_type = float;
    const value_type val;
    Literal(const value_type v) : val(v) {}
    inline value_type eval(int, int) const {return val;}
};

template<>
struct Literal<int> : public Expr<Literal<int>>{
    using value_type = int;
    const value_type val;
    Literal(const value_type v) : val(v) {}
    inline value_type eval(int, int) const {return val;}
};



////////////////////////////////
//  Matrix
///////////////////////////////
template<typename T, size_t Row, size_t Column>
struct Matrix : public Expr<Matrix<T, Row, Column>>{
    using value_type = T;
    static const size_t ROW = Row;
    static const size_t COLUMN = Column;

    std::array<T, ROW*COLUMN> ptr;

    T& operator()(int i, int j){
        return ptr[i*Column+j];
    };

    template<typename E>
    inline Matrix& operator=(const Expr<E>& src){
        const E& val = src.self();
        for(int i = 0; i<Row*Column; ++i){
            ptr[i] = val.eval(i);
        }
        return *this;
    };

    inline value_type eval(int i, int j) const { return ptr[i*Column + j]; }
    inline value_type eval(int n) const {return ptr[n];}

    auto begin() {return ptr.begin();}
    auto end() {return ptr.end();}

    friend std::ostream& operator<<(std::ostream& os, const Matrix& m){
        for(auto i = 0; i < Row; ++i){
            os << "[ ";
            for(auto j = 0; j < Column; ++j){
                os << m.ptr[i*Column+j] << ", ";
            }
            os << "\b\b ]\n";
        }
        return os;
    }
};



////////////////////////////////
//  Expr traits
///////////////////////////////
template<typename T>
struct ExprTypeTraits;

template<>
struct ExprTypeTraits<int>{
    using type = Literal<int>;
};

template<>
struct ExprTypeTraits<float>{
    using type = Literal<float>;
};

template<>
struct ExprTypeTraits<double>{
    using type = Literal<double>;
};


////////////////////////////////
//  Transpose
///////////////////////////////
template<typename E>
struct UnaryTransposeExpr : public Expr<UnaryTransposeExpr<E>>{
    const E& rhs;
    static const size_t ROW = E::ROW;
    static const size_t COLUMN = E::COLUMN;
    using value_type = typename E::value_type;

    UnaryTransposeExpr(const E& val) : rhs(val) {}

    inline value_type eval(int i, int j) const {
        return rhs.eval(i+j*COLUMN);
    }
    friend std::ostream& operator<<(std::ostream& os, const UnaryTransposeExpr& m) {
        for (auto i = 0; i < COLUMN; ++i) {
            os << "[ ";
            for (auto j = 0; j < ROW; ++j) {
                os << m.eval(i, j) << ", ";
            }
            os << "\b\b ]\n";
        }
        return os;
    }
};


////////////////////////////////
//  Expr + Expr
///////////////////////////////
template<typename LHS, typename RHS>
struct BinaryAddExpr : public Expr<BinaryAddExpr<LHS, RHS>>{
    private:
        const RHS& rhs;
        const LHS& lhs;

    public:
        static const size_t ROW = LHS::ROW;
        static const size_t COLUMN = LHS::COLUMN;
        using value_type = typename MatrixValueTypeTraits<
            typename LHS::value_type, 
            typename RHS::value_type>::type;

        BinaryAddExpr(const LHS& l, const RHS& r) :
            rhs(r), lhs(l) {}

        inline value_type eval(int i, int j) const {
            return lhs.eval(i, j) + rhs.eval(i, j);
        }
        friend std::ostream& operator<<(std::ostream& os, const BinaryAddExpr& m){
            for(auto i = 0; i < ROW; ++i){
                os << "[ ";
                for(auto j = 0; j < COLUMN; ++j){
                    os << m.eval(i, j) << ", ";
                }
                os << "\b\b ]\n";
            }
            return os;
        }
};


////////////////////////////////
//  Expr + int/float/double
///////////////////////////////
#define EXPR_ADD_VALUE(OP) template<typename EXPR>                                         \
struct BinaryAddExpr<EXPR, Literal<OP>> : public Expr<BinaryAddExpr<EXPR, Literal<OP>>>{   \
    private:                                                                               \
        using T = OP;                                                                      \
        const Literal<T>& rhs;                                                             \
        const EXPR& lhs;                                                                   \
                                                                                           \
    public:                                                                                \
        static const size_t ROW = EXPR::ROW;                                               \
        static const size_t COLUMN = EXPR::COLUMN;                                         \
        using value_type =                                                                 \
            typename MatrixValueTypeTraits<typename EXPR::value_type, T>::type;            \
        BinaryAddExpr(const EXPR& l, const Literal<T>& r) :                                \
            rhs(r), lhs(l) {}                                                              \
                                                                                           \
        inline value_type eval(int i, int j) const {                                       \
            return lhs.eval(i, j) + rhs.eval(i, j);                                        \
        }                                                                                  \
        friend std::ostream& operator<<(std::ostream& os, const BinaryAddExpr& m){         \
            for(auto i = 0; i < ROW; ++i){                                                 \
                os << "[ ";                                                                \
                for(auto j = 0; j < COLUMN; ++j){                                          \
                    os << m.eval(i, j) << ", ";                                            \
                }                                                                          \
                os << "\b\b ]\n";                                                          \
            }                                                                              \
            return os;                                                                     \
        }                                                                                  \
};                                                                                         

EXPR_ADD_VALUE(double);
EXPR_ADD_VALUE(float);
EXPR_ADD_VALUE(int);




////////////////////////////////
//  Expr - Expr
///////////////////////////////
template<typename LHS, typename RHS>
struct BinaryMinusExpr : public Expr<BinaryMinusExpr<LHS, RHS>>{
    private:
        const RHS& rhs;
        const LHS& lhs;

    public:
        static const size_t ROW = LHS::ROW;
        static const size_t COLUMN = LHS::COLUMN;
        using value_type = 
            typename MatrixValueTypeTraits<
            typename LHS::value_type, 
                     typename RHS::value_type>::type;

        BinaryMinusExpr(const LHS& l, const RHS& r) :
            rhs(r), lhs(l) {}

        inline value_type eval(int i, int j) const {
            return lhs.eval(i, j) - rhs.eval(i, j);
        }
        friend std::ostream& operator<<(std::ostream& os, const BinaryMinusExpr& m){
            for(auto i = 0; i < ROW; ++i){
                os << "[ ";
                for(auto j = 0; j < COLUMN; ++j){
                    os << m.eval(i, j) << ", ";
                }
                os << "\b\b ]\n";
            }
            return os;
        }
};


////////////////////////////////
//  Expr - int/float/double
///////////////////////////////
#define EXPR_MINUS_VALUE(OP) template<typename EXPR>                                           \
struct BinaryMinusExpr<EXPR, Literal<OP>> : public Expr<BinaryMinusExpr<EXPR, Literal<OP>>>{\
    private:                                                                               \
        using T = OP;                                                                      \
        const Literal<T>& rhs;                                                             \
        const EXPR& lhs;                                                                   \
                                                                                           \
    public:                                                                                \
        static const size_t ROW = EXPR::ROW;                                               \
        static const size_t COLUMN = EXPR::COLUMN;                                         \
        using value_type =                                                                 \
            typename MatrixValueTypeTraits<typename EXPR::value_type, T>::type;            \
        BinaryMinusExpr(const EXPR& l, const Literal<T>& r) :                              \
            rhs(r), lhs(l) {}                                                              \
                                                                                           \
        inline value_type eval(int i, int j) const {                                       \
            return lhs.eval(i, j) - rhs.eval(i, j);                                        \
        }                                                                                  \
        friend std::ostream& operator<<(std::ostream& os, const BinaryMinusExpr& m){       \
            for(auto i = 0; i < ROW; ++i){                                                 \
                os << "[ ";                                                                \
                for(auto j = 0; j < COLUMN; ++j){                                          \
                    os << m.eval(i, j) << ", ";                                            \
                }                                                                          \
                os << "\b\b ]\n";                                                          \
            }                                                                              \
            return os;                                                                     \
        }                                                                                  \
};                                                                                         

EXPR_MINUS_VALUE(double);
EXPR_MINUS_VALUE(float);
EXPR_MINUS_VALUE(int);



////////////////////////////////
//  Expr * Expr
///////////////////////////////
template<typename LHS, typename RHS>
struct BinaryMultExpr : public Expr<BinaryMultExpr<LHS, RHS>>{
    private:
        const RHS& rhs;
        const LHS& lhs;
        const size_t rank;

    public:
        using value_type = typename RHS::value_type;
        static const size_t ROW = LHS::ROW;
        static const size_t COLUMN = RHS::COLUMN;

    public:
        BinaryMultExpr(const LHS& l, const RHS& r, size_t lc) :
            rhs(r), lhs(l), rank(lc) {}
        //BinaryMultExpr(const RHS& r, const LHS& l, size_t lc) :
        //    rhs(r), lhs(l), rank(lc) {}

        inline value_type eval(int i, int j) const {
            value_type rst = 0.0;
            for(size_t k = 0; k<rank; ++k){
                rst += lhs.eval(i, k) * rhs.eval(k, j);
            }
            return rst;
        }
        friend std::ostream& operator<<(std::ostream& os, const BinaryMultExpr& m){
            for(auto i = 0; i < ROW; ++i){
                os << "[ ";
                for(auto j = 0; j < COLUMN; ++j){
                    os << m.eval(i, j) << ", ";
                }
                os << "\b\b ]\n";
            }
            return os;
        }
        size_t row_size(void) {return ROW;}
        size_t col_size(void) {return COLUMN;}
};

////////////////////////////////
//  Expr * int/float/double
///////////////////////////////
#define EXPR_MULTIPLY_VALUE(OP) template<typename EXPR>                                    \
struct BinaryMultExpr<EXPR, Literal<OP>> : public Expr<BinaryMultExpr<EXPR, Literal<OP>>>{ \
    private:                                                                               \
        using T = OP;                                                                      \
        const Literal<T>& val;                                                             \
        const EXPR& expr;                                                                  \
        const size_t rank;                                                                 \
                                                                                           \
    public:                                                                                \
        static const size_t ROW = EXPR::ROW;                                               \
        static const size_t COLUMN = EXPR::COLUMN;                                         \
        using value_type =                                                                 \
            typename MatrixValueTypeTraits<typename EXPR::value_type, T>::type;            \
                                                                                           \
    public:                                                                                \
        BinaryMultExpr(const EXPR& e, const Literal<T>& v, size_t col) :                   \
            val(v), expr(e), rank(col) {}                                                  \
                                                                                           \
        BinaryMultExpr(const Literal<T>& v, const EXPR& e, size_t col) :                   \
            val(v), expr(e), rank(col) {}                                                  \
        inline value_type eval(int i, int j) const {                                       \
            value_type rst = expr.eval(i, j) * val.eval(i, j);                             \
            return rst;                                                                    \
        }                                                                                  \
        friend std::ostream& operator<<(std::ostream& os, const BinaryMultExpr& m){        \
            for(auto i = 0; i < ROW; ++i){                                                 \
                os << "[ ";                                                                \
                for(auto j = 0; j < COLUMN; ++j){                                          \
                    os << m.eval(i, j) << ", ";                                            \
                }                                                                          \
                os << "\b\b ]\n";                                                          \
            }                                                                              \
            return os;                                                                     \
        }                                                                                  \
};                                                                                         

EXPR_MULTIPLY_VALUE(double);
EXPR_MULTIPLY_VALUE(float);
EXPR_MULTIPLY_VALUE(int);



////////////////////////////////
//  Expr / Expr
///////////////////////////////
template<typename LHS, typename RHS>
struct BinaryDivideExpr : public Expr<BinaryDivideExpr<LHS, RHS>> {
private:
    const RHS& rhs;
    const LHS& lhs;
    const size_t rank;

public:
    using value_type = typename RHS::value_type;
    static const size_t ROW = LHS::ROW;
    static const size_t COLUMN = RHS::COLUMN;

public:
    BinaryDivideExpr(const LHS& l, const RHS& r, size_t lc) :
        rhs(r), lhs(l), rank(lc) {}

    inline value_type eval(int i, int j) const {
        value_type rst = lhs.eval(i, j) / rhs.eval(i, j);
        return rst;
    }
    friend std::ostream& operator<<(std::ostream& os, const BinaryDivideExpr& m) {
        for (auto i = 0; i < ROW; ++i) {
            os << "[ ";
            for (auto j = 0; j < COLUMN; ++j) {
                os << m.eval(i, j) << ", ";
            }
            os << "\b\b ]\n";
        }
        return os;
    }
};

////////////////////////////////
//  Expr / int/float/double
///////////////////////////////
#define EXPR_DIVIDE_VALUE(OP) template<typename EXPR>                                      \
struct BinaryDivideExpr<EXPR, Literal<OP>> : public Expr<BinaryDivideExpr<EXPR, Literal<OP>>>{\
    private:                                                                               \
        using T = OP;                                                                      \
        const Literal<T>& rhs;                                                             \
        const EXPR& lhs;                                                                   \
                                                                                           \
    public:                                                                                \
        static const size_t ROW = EXPR::ROW;                                               \
        static const size_t COLUMN = EXPR::COLUMN;                                         \
        using value_type =                                                                 \
            typename MatrixValueTypeTraits<typename EXPR::value_type, T>::type;            \
        BinaryDivideExpr(const EXPR& l, const Literal<T>& r) :                             \
            rhs(r), lhs(l) {}                                                              \
                                                                                           \
        inline value_type eval(int i, int j) const {                                       \
            return lhs.eval(i, j) / rhs.eval(i, j);                                        \
        }                                                                                  \
        friend std::ostream& operator<<(std::ostream& os, const BinaryDivideExpr& m){      \
            for(auto i = 0; i < ROW; ++i){                                                 \
                os << "[ ";                                                                \
                for(auto j = 0; j < COLUMN; ++j){                                          \
                    os << m.eval(i, j) << ", ";                                            \
                }                                                                          \
                os << "\b\b ]\n";                                                          \
            }                                                                              \
            return os;                                                                     \
        }                                                                                  \
};                                                                                         

EXPR_DIVIDE_VALUE(double);
EXPR_DIVIDE_VALUE(float);
EXPR_DIVIDE_VALUE(int);





/////////////////////////////////////
//  Expr + Expr
////////////////////////////////////
template<typename LHS, typename RHS>
inline BinaryAddExpr<LHS, RHS>
operator + (const Expr<LHS>& lhs, const Expr<RHS>& rhs){
    using value_type = 
        typename MatrixValueTypeTraits<
            typename LHS::value_type, 
            typename RHS::value_type>::type;
    return BinaryAddExpr<LHS, RHS>(lhs.self(), rhs.self());
}
/////////////////////////////////////
//  Expr + float/double/int
////////////////////////////////////
template<typename EXPR, typename T>
inline BinaryAddExpr<
    EXPR, 
    typename ExprTypeTraits<T>::type>
operator + (const Expr<EXPR>& lhs, const T rhs){
    const static typename ExprTypeTraits<T>::type val(rhs);
    return 
        BinaryAddExpr<
            EXPR,
            typename ExprTypeTraits<T>::type>
        (lhs.self(), val.self());
}
/////////////////////////////////////
//  float/double/int + Expr
////////////////////////////////////
template<typename EXPR, typename T>
inline BinaryAddExpr<
    EXPR, 
    typename ExprTypeTraits<T>::type>
operator + (const T rhs, const Expr<EXPR>& lhs){
    const static typename ExprTypeTraits<T>::type val(rhs);
    return 
        BinaryAddExpr<
            EXPR,
            typename ExprTypeTraits<T>::type>
        (lhs.self(), val.self());
}

/////////////////////////////////////
//  Expr - Expr
////////////////////////////////////
template<typename LHS, typename RHS>
inline BinaryMinusExpr<LHS, RHS>
operator - (const Expr<LHS>& lhs, const Expr<RHS>& rhs){
    using value_type = 
        typename MatrixValueTypeTraits<
            typename LHS::value_type, 
            typename RHS::value_type>::type;
    return BinaryMinusExpr<LHS, RHS>(lhs.self(), rhs.self());
}
/////////////////////////////////////
//  Expr - float/double/int
////////////////////////////////////
template<typename EXPR, typename T>
inline BinaryMinusExpr<
    EXPR, 
    typename ExprTypeTraits<T>::type>
operator - (const Expr<EXPR>& lhs, const T rhs){
    const static typename ExprTypeTraits<T>::type val(rhs);
    return 
        BinaryMinusExpr<
            EXPR,
            typename ExprTypeTraits<T>::type>
        (lhs.self(), val.self());
}
/////////////////////////////////////
//  float/double/int - Expr
////////////////////////////////////
template<typename EXPR, typename T>
inline BinaryMinusExpr<
    EXPR, 
    typename ExprTypeTraits<T>::type>
operator - (const T rhs, const Expr<EXPR>& lhs){
    const static typename ExprTypeTraits<T>::type val(rhs);
    return 
        BinaryMinusExpr<
            EXPR,
            typename ExprTypeTraits<T>::type>
        (lhs.self(), val.self());
}



/////////////////////////////////////
//  Expr * Expr
////////////////////////////////////
template<typename LHS, typename RHS>
inline BinaryMultExpr<LHS, RHS>
operator * (const Expr<LHS>& lhs, const Expr<RHS>& rhs){
    return BinaryMultExpr<LHS, RHS>(lhs.self(), rhs.self(), LHS::COLUMN);
}
/////////////////////////////////////
//  Expr * float/double/int
////////////////////////////////////
template<typename EXPR, typename T>
inline BinaryMultExpr<
    EXPR, 
    typename ExprTypeTraits<T>::type>
operator * (const Expr<EXPR>& lhs, const T rhs){
    const static typename ExprTypeTraits<T>::type val(rhs);
    return 
        BinaryMultExpr<
            EXPR,
            typename ExprTypeTraits<T>::type>
        (lhs.self(), val.self(), EXPR::COLUMN);
}
/////////////////////////////////////
//  float/double/int * Expr
////////////////////////////////////
template<typename EXPR, typename T>
inline BinaryMultExpr<
    EXPR, 
    typename ExprTypeTraits<T>::type>
operator * (const T rhs, const Expr<EXPR>& lhs){
    const static typename ExprTypeTraits<T>::type val(rhs);
    return 
        BinaryMultExpr<
            EXPR,
            typename ExprTypeTraits<T>::type>
        (lhs.self(), val.self(), EXPR::COLUMN);
}



/////////////////////////////////////
//  Expr / Expr
////////////////////////////////////
template<typename LHS, typename RHS>
inline BinaryDivideExpr<LHS, RHS>
operator / (const Expr<LHS>& lhs, const Expr<RHS>& rhs) {
    using value_type =
        typename MatrixValueTypeTraits<
        typename LHS::value_type,
        typename RHS::value_type>::type;
    return BinaryDivideExpr<LHS, RHS>(lhs.self(), rhs.self());
}
/////////////////////////////////////
//  Expr / float/double/int
////////////////////////////////////
template<typename EXPR, typename T>
inline BinaryDivideExpr<
    EXPR,
    typename ExprTypeTraits<T>::type>
    operator / (const Expr<EXPR>& lhs, const T rhs) {
    const static typename ExprTypeTraits<T>::type val(rhs);
    return
        BinaryDivideExpr<
        EXPR,
        typename ExprTypeTraits<T>::type>
        (lhs.self(), val.self());
}


/////////////////////////////////////
//  Matrix Transpose
////////////////////////////////////
template<typename E>
inline UnaryTransposeExpr<E>
operator ~ (const Expr<E>& rhs){
    return UnaryTransposeExpr<E>(rhs.self());
}





#endif
