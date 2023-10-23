#include <iostream>
#include <unistd.h>
#include <thread>
#include "FunctionScheduler.hpp"
#include <memory>

std::shared_ptr<folly::FunctionScheduler> fs = std::make_shared<folly::FunctionScheduler>();
//添加延时任务
void start(){
    fs->cancelFunction("ticker");
    fs->addFunctionOnce([] { std::cout << "start"<<std::endl; }, "ticker", std::chrono::milliseconds(2000));
    std::cout << "addFunctionOnce "<<std::endl;
}

//取消延时任务
void cancel(){
    fs->cancelFunction("ticker");
    std::cout << "cancel"<<std::endl;
}

int main(){
    fs->start();
    std::thread th1([](){start();});
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::thread th2([](){cancel();});
    
    th1.detach();
    th2.detach();
    std::this_thread::sleep_for(std::chrono::seconds(6));
    
    return 0;
}