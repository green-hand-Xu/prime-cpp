#include "manager.h"
#include <iostream>

manager::manager(){
    std::cout<<"this is "<<__func__<<std::endl;
}

manager::~manager(){
    std::cout<<"this is "<<__func__<<std::endl;
}

void manager::start(){

    obja = std::make_shared<A>();
    objb = std::make_shared<B>();
}