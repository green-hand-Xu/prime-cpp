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
    fs.addFunction([] { std::cout << "tick111111111"; }, std::chrono::microseconds(1000), "ticker",std::chrono::microseconds(1000));
    fs.start();
    fs.cancelFunction("ticker");

    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(100));
    }
    

    return 0;
}