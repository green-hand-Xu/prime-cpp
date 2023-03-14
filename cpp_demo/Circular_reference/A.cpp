#include "A.h"
#include <iostream>

A::A(){
    std::cout<<"this is "<<__func__<<std::endl;
}

A::~A(){
    std::cout<<"this is "<<__func__<<std::endl;
}

void A::funA(){
    std::cout<<"this is "<<__func__<<std::endl;
}