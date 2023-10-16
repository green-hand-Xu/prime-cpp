#ifndef __GALogicExpressUserTest_HPP__
#define __GALogicExpressUserTest_HPP__

#include <iostream>
#include "GA/include/expression/FuncionExpression.hpp"

#define LOG(v) std::cout << v << "\r\n"

void GALogicExpressUserTest(){
    auto testField1 = 1;
    auto testField2 = 2;
    auto testField3 = 3;

    //Feature: empty expression
    FuncionExpression expr;

    //Feature: expression has a result.
    auto result = expr.result();

    //Feature: created via lambda
    FuncionExpression expr12{[&testField1]()->bool{ return testField1 == 2;}};
    FuncionExpression expr13{[&testField1]()->bool{ return testField1 == 3;}};
    FuncionExpression expr14{[&testField1]()->bool{ return testField1 == 4;}};
    FuncionExpression expr15{[&testField1]()->bool{ return testField1 == 5;}};


    FuncionExpression expr22{[&testField2]()->bool{ return testField2 == 2;}};
    FuncionExpression expr23{[&testField2]()->bool{ return testField2 == 3;}};
    FuncionExpression expr24{[&testField2]()->bool{ return testField2 == 4;}};
    FuncionExpression expr25{[&testField2]()->bool{ return testField2 == 5;}};

    //Feature: created via expression and lambda.
    auto expr31 = expr12 && [&testField3]()->bool{return testField3 == 1;};

    //todo: Feature: created via expressions
    //FuncionExpression expr32{expr12, LogicOperator::And, expr22};

    //Feature: created via lambdas
    FuncionExpression expr33_1 = {[&testField2]()->bool{return testField2 == 3;}, And, [&testField3]()->bool{return testField3 == 3;}};
    FuncionExpression expr33_2 = {[&testField2]()->bool{return testField2 == 3;}, Or, [&testField3]()->bool{return testField3 == 3;}};

    //Feature: convert to bool
    if(expr){
        LOG("Empty expression is true");
    }else{
        LOG("Empty expression is false");
    }

    //Feature: operator &&
    if(expr12 && expr24){
        LOG("expr12 && expr24 is meet.");
    }

    //Feature: operator ||
    if(expr12 || expr13){
        LOG("(expr12 || expr13) is meet.");
    }

    //Feature: complex logic
    if((expr12 || expr13) && (expr23 || expr24)){
        LOG("(expr12 || expr13) && (expr23 || expr24) is meet.");
    }
}

#endif