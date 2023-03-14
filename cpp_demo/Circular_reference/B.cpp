#include "B.h"
#include <iostream>

B::B(){
    std::cout<<"this is "<<__func__<<std::endl;
}

B::~B(){
    std::cout<<"this is "<<__func__<<std::endl;
}

/*Proxy 对象的 Field 回调 需要掉 Skeleton 的 Update*/
void B::RegistGetHandler(){
    std::cout<<"this is"<<__func__<<std::endl;
}
/*Proxy 对象提供的 Method*/
void B::GS2SMethod(){
    std::cout<<"this is"<<__func__<<std::endl;
}