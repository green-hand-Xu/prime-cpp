#include <iostream>


int main(){
    auto fun1 = []<typename T>(T a) {
    std::cout<<"a = "<<a<<std::endl;
  };

    fun1(1);

    return 0;
}