#include <iostream>
#include <string>
// int 与 str 互转的流头文件
#include <sstream>
using namespace std;

int main(){

    int a = 1;
    int b = 2;
    int c = 3;

    string str;

    str = to_string(a)+to_string(b)+to_string(c);
    
    stringstream stream;
    stream << 123;
    cout<<stream.str()<<endl;

    stream.str(" ");//给流设置内容为 空 则清空流内容
    stream.clear(); //清楚标志位 让流重头开始读
    
    stream << 456;
    cout << stream.str()<<endl;
    stream >>a;
    cout<<a<<endl;

}