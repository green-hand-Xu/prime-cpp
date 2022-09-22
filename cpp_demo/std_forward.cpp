/*
* std::forward 用于完美转发 
* && 表示折叠引用
*/

#include <iostream>
using namespace std;

//接受左值的函数 f()
template<typename T>
void f(T &){
    cout<<"f(T &)"<<endl;
}

//接受右值的函数 f()
template<typename T>
void f(T &&){
    cout<<"f(T &&)"<<endl;
}

//万能引用，转发接收到的参数
template <typename T>
void PrintType(T&& param){
//虽然接收到的值既可以被初始化为左值引用，也可以被初始化为右值引用
//但是，当我们在函数 PrintType 内部，将param传递给另一个函数的时候，此时，param是被当作左值进行传递的。
//任何的函数内部，对形参的直接使用，都是按照左值进行的。
    cout<<"对形参直接使用，传递的是左值"<<endl;
    f(param);
    cout<<"对形参采用 std::forward 进行使用，则传进来什么形式，就是用的什么形式"<<endl;
    f(std::forward<T>(param));

}


int main(){
    int a = 0;
   // PrintType(a);//传入左值
    PrintType(int(0));//传入右值
}