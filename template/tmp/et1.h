
#pragma once

#include <algorithm>
#include <type_traits>

using std::plus;
using std::multiplies;
using std::divides;

////////////////////////////////
//  Literal 
///////////////////////////////
template<class T = double>
struct Literal{
    private:
        T val;
    public:
        using value_type = typename T::value_type;
        Literal(T v) : val(v){}
        T eval(...){return val;}
};

template<>
struct Literal<double>{
    private:
        using T = double;
        T val;
    public:
        using value_type = T;
        Literal(T v) : val(v){}
        T eval(...){return val;}
};

template<>
struct Literal<float>{
    private:
        using T = float;
        T val;
    public:
        using value_type = T;
        Literal(T v) : val(v){}
        T eval(...){return val;}
};




////////////////////////////////
//  Variable
///////////////////////////////
template<class T>
struct Variable{
    using value_type = typename T::value_type;
    T eval(T v){return v;}
};

template<>
struct Variable<double>{
    private:
        using T = double;
    public:
        using value_type = T;
        T eval(T v){return v;}
};

template<>
struct Variable<float>{
    private:
        using T = float;
    public:
        using value_type = T;
        T eval(T v){return v;}
};



////////////////////////////////
//  Tratis
///////////////////////////////
template<typename Expr>
struct ExprTypeTrait{
    typedef Expr expr_type; 
};

template<>
struct ExprTypeTrait<double>{
    typedef Literal<double> expr_type; 
};

template<>
struct ExprTypeTrait<float>{
    typedef Literal<float> expr_type; 
};

template<>
struct ExprTypeTrait<int>{
    typedef Literal<int> expr_type; 
};



////////////////////////////////
//  Expr
///////////////////////////////
template<class Expr1, class Expr2, typename Op>
struct BinaryExpr{
    private:
        typename ExprTypeTrait<Expr1>::expr_type e1;
        typename ExprTypeTrait<Expr2>::expr_type e2;
        Op op;
    public:
        using value_type = typename Expr1::value_type;
        BinaryExpr(Expr1 ee1, Expr2 ee2, Op opp = Op()) :
            e1(ee1), e2(ee2), op(opp) {};
        value_type eval(value_type v){
            return op(e1.eval(v), e2.eval(v));
        }
};

////////////////////////////////
//  Overload + 
///////////////////////////////
template<typename Expr1, typename Expr2>
auto operator+(Expr1 e1, Expr2 e2){
    return BinaryExpr<Expr1, Expr2, plus<typename Expr1::value_type>>(e1, e2);
};

// double
template<typename Expr1>
auto operator+(double e1, Expr1 e2){
    return BinaryExpr<Literal<double>, Expr1, plus<typename Expr1::value_type>>(e1, e2);
};

template<typename Expr1>
auto operator+(Expr1 e1, double e2){
    return BinaryExpr<Expr1, Literal<double>, plus<typename Expr1::value_type>>(e1, e2);
};

// float
template<typename Expr1>
auto operator+(Expr1 e1, float e2){
    return BinaryExpr<Expr1, Literal<float>, plus<typename Expr1::value_type>>(e1, e2);
};

template<typename Expr1>
auto operator+(float e1, Expr1 e2){
    return BinaryExpr<Literal<float>, Expr1, plus<typename Expr1::value_type>>(e1, e2);
};



////////////////////////////////
//  Overload -
///////////////////////////////
template<typename Expr1, typename Expr2>
auto operator-(Expr1 e1, Expr2 e2){
    return BinaryExpr<Expr1, Expr2, plus<typename Expr1::value_type>>(e1, e2);
};

// double
template<typename Expr1>
auto operator-(double e1, Expr1 e2){
    return BinaryExpr<Literal<double>, Expr1, std::minus<typename Expr1::value_type>>(e1, e2);
};

template<typename Expr1>
auto operator-(Expr1 e1, double e2){
    return BinaryExpr<Expr1, Literal<double>, std::minus<typename Expr1::value_type>>(e1, e2);
};

// float
template<typename Expr1>
auto operator-(Expr1 e1, float e2){
    return BinaryExpr<Expr1, Literal<float>, std::minus<typename Expr1::value_type>>(e1, e2);
};

template<typename Expr1>
auto operator-(float e1, Expr1 e2){
    return BinaryExpr<Literal<float>, Expr1, std::minus<typename Expr1::value_type>>(e1, e2);
};



////////////////////////////////
//  Overload *
///////////////////////////////
template<typename Expr1, typename Expr2>
auto operator*(Expr1 e1, Expr2 e2){
    return BinaryExpr<Expr1, Expr2, multiplies<typename Expr1::value_type>>(e1, e2);
};

// double
template<typename Expr1>
auto operator*(double e1, Expr1 e2){
    return BinaryExpr<Literal<double>, Expr1, multiplies<typename Expr1::value_type>>(e1, e2);
};

// double
template<typename Expr1>
auto operator*(Expr1 e1, double e2){
    return BinaryExpr<Expr1, Literal<double>, multiplies<typename Expr1::value_type>>(e1, e2);
};

// float
template<typename Expr1>
auto operator*(Expr1 e1, float e2){
    return BinaryExpr<Expr1, Literal<float>, std::multiplies<typename Expr1::value_type>>(e1, e2);
};

template<typename Expr1>
auto operator*(float e1, Expr1 e2){
    return BinaryExpr<Literal<float>, Expr1, std::multiplies<typename Expr1::value_type>>(e1, e2);
};



////////////////////////////////
//  Overload /
///////////////////////////////
template<typename Expr1, typename Expr2>
auto operator/(Expr1 e1, Expr2 e2){
    return BinaryExpr<Expr1, Expr2, divides<typename Expr1::value_type>>(e1, e2);
};

// double
template<typename Expr1>
auto operator/(double e1, Expr1 e2){
    return BinaryExpr<Literal<double>, Expr1, divides<typename Expr1::value_type>>(e1, e2);
};

// double
template<typename Expr1>
auto operator/(Expr1 e1, double e2){
    return BinaryExpr<Expr1, Literal<double>, divides<typename Expr1::value_type>>(e1, e2);
};

// float
template<typename Expr1>
auto operator/(Expr1 e1, float e2){
    return BinaryExpr<Expr1, Literal<float>, std::divides<typename Expr1::value_type>>(e1, e2);
};

template<typename Expr1>
auto operator/(float e1, Expr1 e2){
    return BinaryExpr<Literal<float>, Expr1, std::divides<typename Expr1::value_type>>(e1, e2);
};
