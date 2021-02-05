

#include <iostream>

using namespace std;


class Literal{
    public:
        Literal(const double v) : val_(v){}

        double eval() const{
            return val_;
        }
    private:
        const double val_;
};

class Variable{
    public:
        Variable(double& v) : val_(v){}
        double eval() const{
            return val_;
        }
    private:
        double& val_;
};


template<typename ExprT1, typename ExprT2, typename BinOp>
class BinaryExpr{
    public:
        BinaryExpr(ExprT1 e1, ExprT2 e2, BinOp op = BinOp()) :
            expr1_(e1), expr2_(e2), op_(op){}

        double eval() const{
            return op_(expr1_.eval(), expr2_.eval());
        }
    private:
        ExprT1 expr1_;
        ExprT2 expr2_;
        BinOp op_;
};



using E1 = BinaryExpr<Variable, Literal, std::plus<double>>;
using E2 = BinaryExpr<Literal, E1, std::multiplies<double>>;


template<typename ExprT1, typename ExprT2, typename BinOp>
BinaryExpr<ExprT1, ExprT2, std::plus<double>> makeSum(ExprT1 e1, ExprT2 e2){ 
    return BinaryExpr<ExprT1, ExprT2, std::plus<double>>(e1, e2);
};

