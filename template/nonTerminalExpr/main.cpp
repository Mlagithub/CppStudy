

//#include "et1.h"
//#include "inte.h"
#include "matrix.h"

#include <iostream>
#include <algorithm>
#include <functional>
#include <typeinfo>

using namespace std;

template<typename T>
struct A{
    using value_type = double;
    static double eval(const double val){
        return 2.45- val;
    }
    T id;
    array<T, 3> data;
};



void call(int v1, char c1, int v2, char c2){
    cout << "calling :" 
        << v1 << '\t'
        << c1 << '\t'
        << v2 << '\t'
        << c2 << '\n';
}

template<size_t ... holders>
void test(int val){
    auto callable = std::bind(&call, val, std::_Placeholder<holders>()...);
    callable('a', 42, 'c');
}


int main(void){

    //Variable<double> v;
    //A y;
    //auto e1 = 2.0 * v;
    //auto e2 = v + y;
    //auto e3 = e1.eval(3.0)* e2;

    //cout << e1.eval(3.0) << '\n';
    //cout << e2.eval(1.0) << '\n';
    //cout << e3.eval(1.0) << '\n';
    //cout << e3.eval(2.0) << '\n';

    //cout << (1.0 + v).eval(3.0) << '\n';
    //cout << Inte(v/(v+1.0), 1.0, 5.0, 200) << '\n';
    //cout << Inte(v, 1.0, 2.0, 200) << '\n';
    //auto expr = x + v*v*1.34;
    //cout << expr.eval(3.0) << '\n';
    //cout << expr.eval(-3.0) << '\n';

    using MT = Matrix<float, 2>;

    Matrix<float, 2> m1;
    m1.set(0, 0, 1.0);
    m1.set(0, 1, 2.0);
    m1.set(1, 0, 3.0);
    m1.set(1, 1, 4.0);

    Matrix<float, 2> m2;
    m2.set(0, 0, 1.0);
    m2.set(0, 1, 2.0);
    m2.set(1, 0, 3.0);
    m2.set(1, 1, 4.0);

    Matrix<float, 2> m3;
    m3.set(0, 0, -1.0);
    m3.set(0, 1, -2.0);
    m3.set(1, 0, -3.0);
    m3.set(1, 1, -4.0);

    cout << "\nLiteral matrix + literal materix \n";
    Literal<MT> m4(m1);
    auto e1 = m4 + m4;
    cout << "Change before : \n";
    cout << e1.eval(m2);
    cout << "Change after : \n";
    m2.set(0, 0, 2.0);
    cout << e1.eval(m2);


    cout << "\nliteral matrix + variable materix \n";
    Variable<MT> m5;
    auto e2 = m4 + m5 - 2.0;
    cout << "Change before : \n";
    cout << e2.eval(m2);
    cout << "Change after : \n";
    m2.set(0, 0, 1.0);
    cout << e2.eval(m2);


    cout << "\nliteral matrix + number \n";
    auto e3 = m4 + 2.0;
    cout << "Change before : \n";
    cout << e3.eval(m2);
    cout << "Change after : \n";
    m2.set(0, 0, 11.0);
    cout << e3.eval(m2);


    cout << "\nvariable matrix + number \n";
    auto e4 = m5 + 3.0;
    cout << "Change before : \n";
    cout << e4.eval(m2);
    cout << "Change after : \n";
    m2.set(0, 0, -1.0);
    cout << e4.eval(m2);


    cout << "\nLiteral matrix - literal materix \n";
    Literal<MT> m7(m3);
    auto e8 = m4 - m7;
    cout << "Change before : \n";
    cout << e8.eval(m2);
    cout << "Change after : \n";
    m2.set(0, 0, 2.0);
    cout << e8.eval(m2);


    cout << "\nliteral matrix - variable materix \n";
    auto e9 = m4 - m5;
    cout << "Change before : \n";
    cout << e9.eval(m2);
    cout << "Change after : \n";
    m2.set(0, 0, 1.0);
    cout << e9.eval(m2);


    cout << "\nliteral matrix - number \n";
    auto e10 = 2.0 - m4;
    cout << "Change before : \n";
    cout << e10.eval(m2);
    cout << "Change after : \n";
    m2.set(0, 0, 11.0);
    cout << e10.eval(m2);

    cout << "\nvariable matrix - number \n";
    auto e6 = 1.0 - m5 + 3.0;
    cout << "Change before : \n";
    cout << e6.eval(m2);
    cout << "Change after : \n";
    m2.set(0, 0, -11.0);
    m2.set(1, 0, -11.0);
    cout << e6.eval(m2);

    cout << "\nliteral matrix * literal matrix \n";
    Matrix<float, 2, 4> t11;
    t11.set(0, 0, 1.0);
    t11.set(0, 1, 2.0);
    t11.set(0, 2, 3.0);
    t11.set(0, 3, 4.0);
    t11.set(1, 0, 5.0);
    t11.set(1, 1, 6.0);
    t11.set(1, 2, 7.0);
    t11.set(1, 3, 8.0);
    Literal<Matrix<float, 2, 4>> t1(t11);
    Matrix<float, 4, 3> t12;
    t12.set(0, 0, 1.0);
    t12.set(0, 1, 1.0);
    t12.set(0, 2, 1.0);
    t12.set(1, 0, 2.0);
    t12.set(1, 1, 2.0);
    t12.set(1, 2, 2.0);
    t12.set(2, 0, 3.0);
    t12.set(2, 1, 3.0);
    t12.set(2, 2, 3.0);
    t12.set(3, 0, 4.0);
    t12.set(3, 1, 4.0);
    t12.set(3, 2, 4.0);
    Literal<Matrix<float, 4, 3>> t2(t12);
    auto e11 = t1 * t2;
    Matrix<float, 2, 3> tmp;
    tmp.set(0, 0, 1.0);
    tmp.set(0, 1, 1.0);
    tmp.set(0, 2, 1.0);
    tmp.set(1, 0, 1.0);
    tmp.set(1, 1, 1.0);
    tmp.set(1, 2, 1.0);
    cout << "Change before : \n";
    cout << e11.eval(tmp) << '\n';
    cout << "Change after : \n";
    tmp.set(0, 0, 1.0);
    cout << e11.eval(tmp) << '\n';


    cout << "\nliteral matrix * number \n";
    auto e12 = e11 * 2.0;
    cout << "Change before : \n";
    cout << e12.eval(tmp) << '\n';
    cout << "Change after : \n";
    tmp.set(0, 0, 2.0);
    cout << e12.eval(tmp) << '\n';


    cout << "\nvariable matrix * number \n";
    Variable<Matrix<float, 2, 3>> t3;
    auto e13 = 1.0 * t3 * 2.0;
    cout << "Change before : \n";
    cout << e13.eval(tmp) << '\n';
    cout << "Change after : \n";
    tmp.set(1, 1, 2.0);
    cout << e13.eval(tmp) << '\n';


    cout << "\nmatrix transpose \n";
    Literal<Matrix<float, 2, 4>> x(t11);
    auto z = ~x;
    cout << z.eval(t11) << '\n';
    //cout << ~t11 << '\n';


    Matrix<float, 1, 3> vx;
    vx.set(0, 1, 1.0);
    vx.set(0, 2, 2.0);
    vx.set(0, 3, 3.0);

    Matrix<float, 3, 1> vy;
    vy.set(0, 1, 3.0);
    vy.set(0, 2, 4.0);
    vy.set(0, 3, 5.0);


    Literal<Matrix<float, 1, 3>> v1(vx);
    Literal<Matrix<float, 3, 1>> v2(vy);
    //auto v3 = v1 * v2;
    //cout << v3.eval(vy) << '\n';

    //cout << v3.eval(vx) << '\n';

    return 0;
}
