#ifndef __GALogicExpressFeatureTest_HPP__
#define __GALogicExpressFeatureTest_HPP__

#include <iostream>
#include "GA/include/expression/FuncionExpression.hpp"

#define LOG(v) std::cout << v << "\r\n"

void GALogicExpressFeatureTest(){
    auto testField1 = 1;
    auto testField2 = 2;
    auto testField3 = 3;

    //Feature: empty expression
    FuncionExpression expr;

    //Feature: default result shoule be false
    if(expr){
        LOG("Feature: default result shoule be false(convert bool), failed");
        return;
    }
    if(expr.result()){
        LOG("Feature: default result shoule be false(method result()), failed");
        return;
    }
    if(expr == true){
        LOG("Feature: default result shoule be false(operator ==), failed");
        return;
    }
    if(expr != false){
        LOG("Feature: default result shoule be false(operator !=), failed");
        return;
    }

    FuncionExpression expr20([&testField1]()->bool{ return testField1 == 2;});
    auto expr21 = expr20 && ([&testField1]()->bool{ return testField1 == 3;});
    auto expr22 = expr20 || ([&testField1]()->bool{ return testField1 == 3;});
    auto expr23 = expr21 && expr22;
    auto expr24 = expr21 || expr22;

    //Feature: && make a new copy.
    auto ptr20 = &expr20;
    auto ptr21 = &expr21;
    if(ptr20 == ptr21){
        LOG("Feature: && make a new copy, failed");
        return;
    }
    auto ptr21 = &expr21;
    auto ptr22 = &expr22;
    auto ptr23 = &expr23;
    if(ptr23 == ptr21 || ptr23 == ptr22){
        LOG("Feature: && make a new copy, failed");
        return;
    }
    //Feature: || make a new copy.
    auto ptr20 = &expr20;
    auto ptr22 = &expr22;
    if(ptr20 == ptr22){
        LOG("Feature: || make a new copy, failed");
        return;
    }
    auto ptr21 = &expr21;
    auto ptr22 = &expr22;
    auto ptr24 = &expr24;
    if(ptr24 == ptr21 || ptr24 == ptr22){
        LOG("Feature: || make a new copy, failed");
        return;
    }
}

#endif