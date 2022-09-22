/*
*   此项目主要用来训练 cmake 的各种指令操作
*
*/
#include <iostream>
#include <signal.h>
#include <unistd.h>
#include "mymath.h"
using namespace std;
void handlsignal(int signal){
    std::cout<<"我被结束了"<<std::endl;
    // 清理并关闭
    // 终止程序
    exit(signal);
}

int main(){

    signal(SIGINT,handlsignal);

    double a = add(1.1, 1.1);
    int b = add(1, 1);
    cout << "1.1加1.1等于" << a <<endl;
    cout << "1加1等于" << b <<endl;
    return 0;

    while (true)
    {
        sleep(10);
    }
    
    return 0;
}