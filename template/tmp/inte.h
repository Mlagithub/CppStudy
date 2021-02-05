
#pragma once

#include "et1.h"

template<class Expr>
auto Inte(Expr expr, double from, double to, size_t N){
    using T = typename Expr::value_type;
    T rst = 0.0;
    T step = (to-from)/N;
    for(size_t v = 0; v < N; ++v){
        rst += expr.eval(from+step*0.5 + v*step);
    };
    return rst*step;
};

