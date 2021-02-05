
#include "expr.h"

#include <algorithm>



int main(void){

    double tmp;
    cin >> tmp;
    double& sigma = tmp;

    using E1 = BinaryExpr<Variable, Literal, std::plus<double>>;
    using E2 = BinaryExpr<Literal, E1, std::multiplies<double>>;

    E1 e1(sigma, 3);
    E2 e2(-3.3, e1);

    cout << e1.eval() << '\n';
    cout << e2.eval() << '\n';

    return 0;
}
