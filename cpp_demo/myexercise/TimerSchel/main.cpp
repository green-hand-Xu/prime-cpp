#include <iostream>
#include <unistd.h>
// #include <thread>
#include "FunctionScheduler.hpp"


void Fun1(){
    folly::FunctionScheduler fs;
    fs.addFunction([] { std::cout << "tick111111111"; }, std::chrono::microseconds(1), "ticker");
    fs.start();
}


int main(){
    // std::thread t1(Fun1);
    // t1.join();
    folly::FunctionScheduler fs;
    int a = 101;

    fs.addFunction([&fs,&a] { 
    std::cout << "tick111111111"<<std::endl;
    if( a <= 100){
        std::cout << "a = "<<a <<std::endl;
        fs.cancelFunction("ticker");
    }
    }, std::chrono::milliseconds(50), "ticker");

    fs.addFunction([&fs,&a] { 
    std::cout << "tick2222222222222"<<std::endl;
    if( a <= 100){
        std::cout << "a = "<<a <<std::endl;
        fs.cancelFunction("ticker");
    }
    }, std::chrono::milliseconds(50), "ticker");

    fs.start();

    while (std::cin>>a)
    {

        std::this_thread::sleep_for(std::chrono::seconds(100));

    }
    

    return 0;
}