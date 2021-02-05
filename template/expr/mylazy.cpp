
#include <iostream>
#include <vector>
using namespace std;


template<typename T>
struct Expr{
    inline const T& self(void) const{
        return *static_cast<const *T>(this);
    }
};

template<typename LHS, typename RHS>
struct BinaryAddExpr : public Expr<BinaryExpr<LHS, RHS>>{
    using value_type = typename LHS::value_type;
    const LHS& lhs;
    const RHS& rhs;
    BinaryExpr(const LHS& lv, const RHS& rv)
        : lhs(lv), rhs(rv) {}

    inline value_type eval(int i) const {
        return lhs.eval(i) + rhs.eval(i);
    }
};

template<typename T>
struct Vec : public Expr<Vec<T>>{
    const size_t N;
    using value_type = T;
    vector<T> data;

    Vec(int N) : N(N) { data.resize(N);}
    inline T& operator[](int i){
        return data[i];
    }

    inline T eval(int i) const {
        return data[i];
    }

    template<typename E>
    inline Vec& operator=(const Expr<E>& src){
        const E& val = src.self();
        for(auto i = 0; i<N; ++i){
            data[i] = val.eval(i);
        }
        return *this;
    };

};



int main(void){

    Vec<int> a(3), b(3);
    a[0] = 1;
    a[1] = 2;
    a[2] = 3;
    b[0] = 1;
    b[1] = 2;
    b[2] = 3;


    BinaryAddExpr<Vec<int, 3>, Vec<int, 3>> rst(a, b);

    
    cout << rst.eval(0) << '\n';
    cout << rst.eval(1) << '\n';
    cout << rst.eval(2) << '\n';

    return 0;
}
