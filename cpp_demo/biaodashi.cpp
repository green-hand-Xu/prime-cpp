/**
 * @file biaodashi.cpp
 * @author your name (you@domain.com)
 * @brief prime c++ 第四章 表达式相关练习
 * @version 0.1
 * @date 2022-11-25
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include <iostream>
#include <vector>
#include <typeinfo>
using namespace std;



// 括号的结合
void demo1(){
    std::vector<int> vec{1,2,3,4,5,6,7,8,9,10};

    std::cout<<*vec.begin()<<'\n';
    std::cout<<*vec.begin()+1<<'\n';

    //上面两个等价于
    std::cout<<(*vec.begin())<<'\n';
    std::cout<<(*vec.begin())+1<<'\n';
}

// 为表达式添加括号 说明求值过程及结果。
void demo2(){
    int a,b;
    //不加括号
    a=12/3*4+5*15+24%4/2;
    //加括号
    b=12/(3*4)+(5*15)+(24%4/2); 

    std::cout<<"a:"<<a<<'\n'<<"b:"<<b<<'\n';

}

// 算术转换练习
void demo3(){
    cout<<"int:"<<sizeof(int)<<endl;  //4
    cout<<"bool:"<<sizeof(bool)<<endl; //1
    cout<<"char:"<<sizeof(char)<<endl; //1
    cout<<"unsigned int:"<<sizeof(unsigned int)<<endl; //4
    cout<<"long:"<<sizeof(long)<<endl; //8
    cout<<"unsignde long:"<<sizeof(unsigned long)<<endl;//8

    unsigned long ulong = 1; // 8
    int i = -2; //4

    auto sum = ulong + i; // 无符号类型大小比带符号类型大小大，转换成无符号类型。
    const type_info &kind = typeid(sum);
    cout<<"sum 类型为："<<typeid(sum).name()<<"  value="<<sum<<endl; // unsigned long  

    long l = -3; //8
    uint u_int = 1; //4

    auto sum2 = l + u_int; // 无符号类型大小比带符号类型小，转换成带符号类型
    const type_info &kind2 = typeid(sum2);
    cout<<"sum 类型为："<<typeid(sum2).name()<<"  value="<<sum2<<endl;// long
}

// 类类型定义的转换
void demo4(){
    string s,t = "a value";
    while (cin >> s){
        cout <<s <<'\n';
    }
}

int main(){

   demo4();

    return 0;
}