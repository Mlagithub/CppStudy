
#pragma once
#include <iostream>
#include <algorithm>

using namespace std;

template<size_t N, typename T>
struct DotProduct{
    static T eval(T * a, T * b){
        return DotProduct<1, T>::eval(a,b) + DotProduct<N-1, T>::eval(a+1, b+1);
    }
};

template<typename T>
struct DotProduct<1, T>{
    static T eval(T * a, T * b){
        return (*a)*(*b);
    }
};

template<size_t N, typename T>
inline T dot(T* a, T* b){
    return DotProduct<N,T>::eval(a,b);
};


//=============================================


struct Literal{
    Literal(const double v) : val_t(v){}
    double eval() const{return val_t;}
    private:
        const double val_t;
};

struct Variable{
    Variable(double& v) : val_t(v){}
    double eval() const {return val_t;}
    private:
        double& val_t;
};

template<typename ExprT>
struct exprTrait{
    typedef ExprT expr_type;
};

template<>
struct exprTrait<double>{
    typedef Literal expr_type;
};

template<>
struct exprTrait<int>{
    typedef Literal expr_type;
};

template<typename ExprT1, typename ExprT2, typename BinOp>
struct BinaryExpr{
    BinaryExpr(ExprT1 e1, ExprT2 e2, BinOp bop=BinOp()) : 
        expr1(e1), expr2(e2), op(bop){}
    double eval() const {return op(expr1.eval(), expr2.eval());}

    private:
        typename exprTrait<ExprT1>::expr_type expr1;
        typename exprTrait<ExprT2>::expr_type expr2;
        BinOp op;
};


template<typename ExprT1, typename ExprT2>
BinaryExpr<ExprT1, ExprT2, plus<double>> makeSum(ExprT1 e1, ExprT2 e2){
    return BinaryExpr<ExprT1, ExprT2, plus<double>>(e1, e2);
}

template<typename ExprT1, typename ExprT2>
BinaryExpr<ExprT1, ExprT2, plus<double>> operator+(ExprT1 e1, ExprT2 e2){
    return BinaryExpr<ExprT1, ExprT2, plus<double>>(e1, e2);
}

template<typename ExprT1, typename ExprT2>
BinaryExpr<ExprT1, ExprT2, multiplies<double>> makeProd(ExprT1 e1, ExprT2 e2){
    return BinaryExpr<ExprT1, ExprT2, multiplies<double>>(e1, e2);
}

template<typename ExprT1, typename ExprT2>
BinaryExpr<ExprT1, ExprT2, multiplies<double>> operator*(ExprT1 e1, ExprT2 e2){
    return BinaryExpr<ExprT1, ExprT2, multiplies<double>>(e1, e2);
}

template<class ExprT>
double eval(ExprT e){
    return e.eval();
};

