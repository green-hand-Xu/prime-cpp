#include <iostream>
#include <memory>
#include <thread>

static int a = 1;
std::shared_ptr<int> aptr(std::make_shared<int>(a));


std::shared_ptr<int> getinstance(){
    return aptr;
}

auto test(){
    auto ptr1 = getinstance();
    std::cout<<"ptr1 = "<<&ptr1<<std::endl;
    return [&ptr1](){
        std::cout<<"ptr1 = "<<&ptr1<<std::endl;
    };
}

auto fun2 = test();

int main(){
    auto ptr1 = getinstance();
    std::cout<<"ptr1 = "<<&ptr1<<std::endl;
    auto fun = [&ptr1](){
        std::cout<<"ptr1 = "<<&ptr1<<std::endl;
    };
    fun();
    std::thread();
    return 0;
}