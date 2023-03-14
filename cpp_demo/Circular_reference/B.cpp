#include "B.h"
#include <iostream>

B::B(){
    std::cout<<"this is "<<__func__<<std::endl;
}

B::~B(){
    std::cout<<"this is "<<__func__<<std::endl;
}

void B::funB(){
    std::cout<<"this is"<<__func__<<std::endl;
}