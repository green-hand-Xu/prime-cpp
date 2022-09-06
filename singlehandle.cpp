
#include <iostream>
#include <csignal>
#include <unistd.h>

/*
*   处理信号的练习 SIGINT 为程序终止信号 如 ctrl +c
    信号处理头文件 csignal
    sleep 头文件 unistd.h
*/

using namespace std;

void signalHandler( int signal ){    
    cout<<"捕获信号"<<endl;
    // 清理并关闭
    // 终止程序
    exit(signal);
}
 
int main( )
{ 
    //signal():注册信号SIGINT 和 信号处理程序
    signal(SIGINT , signalHandler);

    int i = 0;
    while (++i)
    {
        cout<<"sleeping"<<endl;
        if(i==3){
        //raise():生成信号 , 并给自己发送这个信号
        raise(SIGINT);
        }
        sleep(1);
    }
    

}