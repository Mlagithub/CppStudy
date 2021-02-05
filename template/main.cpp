
// #include "factorial.h"
#include "root.h"
// #include "dot.h"
// #include "apply_fun_to_container.h"
// #include "sfinaf.h"
#include "nesting.h"


#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cmath>

using namespace std;

// void someFun(double x) {
//     BinaryExpr<BinaryExpr<Variable, Literal, plus<double>>, Literal,
//                multiplies<double>> expr =
//         makeProd(makeSum(Variable(x), Literal(2)), Literal(3));
//     // cout << expr.eval() << '\n';
//     // cout << makeProd(makeSum(Variable(x), Literal(2)), Literal(3)).eval() <<
//     // '\n';
//     Variable v(x);
//     cout << ((v + 2) * 3).eval() << '\n';
//     cout << eval((v + 2) * 3) << '\n';
// }
// struct Point {
//     double x;
//     double y;
// };

// double normal(Point const &point) {
//     return sqrt(point.x * point.x + point.y * point.y);
// }

// template <typename T>
// void prt(std::vector<T> content) {
//     std::copy(content.begin(), content.end(),
//               std::ostream_iterator<double>(std::cout, "\n"));
// }

// template <unsigned N>
// struct Factorial
//     : public std::integral_constant<int, N * Factorial<N - 1>::value> {};

// template <>
// struct Factorial<0> : public std::integral_constant<int, 1> {};

int main(void) {
    // cout << "Factorial of 3 : " << factorial<3>() << '\n';
    // cout << "Factorial of 5 : " << factorial<5>() << '\n';
    // cout << "Factorial of 9 : " << factorial<9>() << '\n';
    cout << "Root of 29 : " << Root<29>::value << '\n';

    // int a[3] = {1, 2, 3};
    // int b[3] = {2, 3, 4};

    // cout << "Dot of A B : " << dot<3, int>(a, b) << '\n';

    // someFun(3.0);
    // someFun(4.0);
    // someFun(5.0);

    // auto norms = Project(normal);
    // auto const myPoints = std::vector<Point>{{3, 4}, {6, 8}, {9, 12}};
    // auto const nrm = norms(myPoints);

    // std::copy(nrm.begin(), nrm.end(),
    //           std::ostream_iterator<double>(std::cout, "\n"));

    // auto const test = std::vector<double>{1, 3, 5};
    // prt(test);

    // cout << Factorial<3>() << '\n';
    // cout << Factorial<4>::value << '\n';
    // cout << Factorial<5>::value << '\n';

    // cout << "Int " << f<int>(3) << '\n';
    // cout << "float " << f<string>("34.0") << '\n';

    // //cout << "Int " << sfinaf<int>(3) << '\n';
    // sfinaf(3);
    // sfinaf(56);
    // sfinaf(3.0);

    // std::cout << "Hello world ni hao \n";

    // test_nesting();

    return 0;
}
