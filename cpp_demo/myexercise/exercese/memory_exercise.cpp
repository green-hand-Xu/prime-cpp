#include <iostream>
#include <string.h>
using namespace std;

//全局区 分为 全局初始化区和 全局为初始化区
//全局初始化区
int a = 0;
//全局未初始化区
char *p1;

int main(){

    int b;//栈
    char s[] = "abc";//栈
    char *p2;//栈
    char *p3 = "123456";//值 内容在常量区  P3在栈上

    static int c = 0;// 全局 初始化区

    //分配得来的 10和20字节的区域在堆区，
    //既 指针指向的地址是堆区的地址，指针本身存在栈区。
    char *p4 = (char *)malloc(20);

    cout<<"全局区初始化区 a 地址为："<<&a<<endl;
    cout<<"全局未初始化区 p1 地址为："<<&p1<<endl;
    cout<<"堆区 p4 指向的地址为："<<static_cast<void *>(p4)<<endl;
    cout<<"栈区 p4 地址为："<<&p4<<endl;
    cout<<"栈区 b 地址为："<<&b<<endl;
    
    return 0;

}