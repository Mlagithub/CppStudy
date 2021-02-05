

#include <cstdio>

// this is expression, all expressions must inheritate it,
//  and put their type in subtype
template <typename SubType>
struct Exp {
    // returns const reference of the actual type of this expression
    inline const SubType &self(void) const {
        return *static_cast<const SubType *>(this);
    }
};

// binary add expression
// note how it is inheritates from Exp
// and put its own type into the template argument
template <typename TLhs, typename TRhs>
struct BinaryAddExp : public Exp<BinaryAddExp<TLhs, TRhs>> {
    const TLhs &lhs;
    const TRhs &rhs;
    BinaryAddExp(const TLhs &lhs, const TRhs &rhs) : lhs(lhs), rhs(rhs) {}
    // evaluation function, evaluate this expression at position i
    inline float Eval(int i) const { return lhs.Eval(i) + rhs.Eval(i); }
};

// binary minus expression
// note how it is inheritates from Exp
// and put its own type into the template argument
template <typename TLhs, typename TRhs>
struct BinaryMinusExp : public Exp<BinaryMinusExp<TLhs, TRhs>> {
    const TLhs &lhs;
    const TRhs &rhs;
    BinaryMinusExp(const TLhs &lhs, const TRhs &rhs) : lhs(lhs), rhs(rhs) {}
    // evaluation function, evaluate this expression at position i
    inline float Eval(int i) const { return lhs.Eval(i) - rhs.Eval(i); }
};

// binary multiply expression
// note how it is inheritates from Exp
// and put its own type into the template argument
template <typename TLhs, typename TRhs>
struct BinaryMulExp : public Exp<BinaryMulExp<TLhs, TRhs>> {
    const TLhs &lhs;
    const TRhs &rhs;
    BinaryMulExp(const TLhs &lhs, const TRhs &rhs) : lhs(lhs), rhs(rhs) {}
    // evaluation function, evaluate this expression at position i
    inline float Eval(int i) const { return lhs.Eval(i) * rhs.Eval(i); }
};

// binary div expression
// note how it is inheritates from Exp
// and put its own type into the template argument
template <typename TLhs, typename TRhs>
struct BinaryDivExp : public Exp<BinaryDivExp<TLhs, TRhs>> {
    const TLhs &lhs;
    const TRhs &rhs;
    BinaryDivExp(const TLhs &lhs, const TRhs &rhs) : lhs(lhs), rhs(rhs) {}
    // evaluation function, evaluate this expression at position i
    inline float Eval(int i) const { return lhs.Eval(i) / rhs.Eval(i); }
};
// no constructor and destructor to allocate
// and de-allocate memory, allocation done by user
struct Vec : public Exp<Vec> {
    int len;
    float *dptr;
    Vec(void) {}
    Vec(float *dptr, int len) : len(len), dptr(dptr) {}
    // here is where evaluation happens
    template <typename EType>
    inline Vec &operator=(const Exp<EType> &src_) {
        const EType &src = src_.self();
        for (int i = 0; i < len; ++i) {
            dptr[i] = src.Eval(i);
        }
        return *this;
    }
    // evaluation function, evaluate this expression at position i
    inline float Eval(int i) const { return dptr[i]; }
};
// template add, works for any expressions
template <typename TLhs, typename TRhs>
inline BinaryAddExp<TLhs, TRhs> operator+(const Exp<TLhs> &lhs,
                                          const Exp<TRhs> &rhs) {
    return BinaryAddExp<TLhs, TRhs>(lhs.self(), rhs.self());
}
// template minus, works for any expressions
template <typename TLhs, typename TRhs>
inline BinaryMinusExp<TLhs, TRhs> operator-(const Exp<TLhs> &lhs,
                                            const Exp<TRhs> &rhs) {
    return BinaryMinusExp<TLhs, TRhs>(lhs.self(), rhs.self());
}
// template mul, works for any expressions
template <typename TLhs, typename TRhs>
inline BinaryMulExp<TLhs, TRhs> operator*(const Exp<TLhs> &lhs,
                                          const Exp<TRhs> &rhs) {
    return BinaryMulExp<TLhs, TRhs>(lhs.self(), rhs.self());
}
// template div, works for any expressions
template <typename TLhs, typename TRhs>
inline BinaryDivExp<TLhs, TRhs> operator/(const Exp<TLhs> &lhs,
                                          const Exp<TRhs> &rhs) {
    return BinaryDivExp<TLhs, TRhs>(lhs.self(), rhs.self());
}

const int N = 3;
int main(void) {
    float sa[N] = {1, 2, 3};
    float sb[N] = {2, 3, 4};
    float sc[N] = {3, 4, 5};
    float sd[N] = {4, 5, 6};
    float se[N] = {5, 6, 7};
    Vec A(sa, N), B(sb, N), C(sc, N), D(sd, N), E(se, N);
    // run expression, this expression is longer:)
    A = B + C + C * D - D / E;
    for (int i = 0; i < N; ++i) {
        printf("%d:%f == %f + %f + %f*%f - %f/%f\n", i, A.dptr[i], B.dptr[i],
               C.dptr[i], C.dptr[i], D.dptr[i], D.dptr[i], E.dptr[i]);
    }
    return 0;
}