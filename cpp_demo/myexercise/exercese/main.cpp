#include <iostream>
#include <string>
class A
{
    public:
    void fun1(){
        std::cout<<"asoidhoa"<<std::endl;
    };
    void fun2();
};


int main(){

    std::cout<<sizeof(A)<<std::endl;
    return 0;
}