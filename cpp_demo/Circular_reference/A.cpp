#include "A.h"
#include <iostream>

A::A(){
    std::cout<<"this is "<<__func__<<std::endl;
}

A::~A(){
    std::cout<<"this is "<<__func__<<std::endl;
}
/*Skeleton 的Method 需要调 GS2S 对象的 Method*/
void A::SkeletonMethod(){
    std::cout<<"this is "<<__func__<<std::endl;
}
/*Skeleton 对象提供的 Update*/
void A::Field_Update(){
    std::cout<<"this is "<<__func__<<std::endl;
}