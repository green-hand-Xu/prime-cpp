/**
 * @file func_point.cpp
 * @author your name (you@domain.com)
 * @brief 函数指针。常用场景，线程、回调函数（std::bind  lambda std::function 结合使用）
 * @version 0.1
 * @date 2023-03-29
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <iostream>

using namespace std;
//    返回值类型 ( * 指针变量名) (形参列表);
int func(int x); /* 声明一个函数 */
int (*f) (int x); /* 声明一个函数指针 */

int func(int x){
    cout <<__func__<<x<<endl;
    return x;
}

//使用typedef 定义 普通函数 
typedef int (Func0)(int);
//使用typedef 定义 函数指针
typedef int (*Func1)(int);
//普通方式定义函数指针
int (*padd)(int);

/*
当用普通方式声明的函数指针作为返回值时，编译器无法正确识别 函数名 参数列表
int (*f) (int x) popo(int (*f) (int x)){
    cout<<f(10)<<endl;
    return f;
}
*/
//下面这种语法编译器已经无法识别了
//(void (*PtrFunA)()) getPtrFunA2() {
//    return FunA;
//}

int main(){

    f=func; /* 将func函数的首地址赋给指针f */
    f=&func;/* 将func函数的首地址赋给指针f */
    f(1);//调用函数指针 

    // popo(f);

    //创建 使用 typedef 声明的 函数指针 对象，并赋值。
    Func0 *fun0 = func;
    Func1 fun1 = func;

    fun0(2);
    fun1(3);

    return 0;
}