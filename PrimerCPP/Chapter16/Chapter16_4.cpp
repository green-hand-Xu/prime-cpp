/**
 * @file Chapter16_4.cpp
 * @author 许营博
 * @brief 可变参数模板练习
 * @version 0.1
 * @date 2023-08-14
 * * 可变数目的参数被称为参数包   参数包分为 1、模板参数包：表示 0 或者 多个模板参数 2、函数参数包：表示 0 或者 多个 函数参数 *
 * * 在template<> 中 class... 或者 typename... 指示出接下来的参数表示 0 或 多个类型的列表 *
 * * 一个类型名 后面跟 一个省略号(...)  表示 0 个 或 多个 给定类型的 非类型参数的列表 *
 * * sizeof...(Args) sizeof...(args) 可以计算 模板参数包 或者 函数参数包内包含的元素数量*
 * * 包拓展：拓展一个包就是将他分解为构成的元素，对每个元素应用模式，获得拓展后的列表。 通过在模式右边放一个省略号（...）来触发拓展操作 *
 * @copyright Copyright (c) 2023
 * 
 */
#include <iostream>

template <typename T , typename... Args>//*Args是一个模板参数包 表示 0 或 多个模板类型参数
void foo(const T &t,const Args& ... rest)//*rest 是一个函数参数包 表示 0 或 多个 函数参数
{
    std::cout<<" 模板参数包 数量 = "<<sizeof...(Args)<<'\n'<<"函数参数包 数量 = "<<sizeof...(rest)<<std::endl;
}

//* 终止参数包的递归展开
template<typename T> //用来终止递归并打印最后一个元素的值 
std::ostream &print(std::ostream &os , const T &t){

    return os<<t<< '\n'; //包中最后一个元素不打印分隔符

}
//* 可变参数函数的使用 （一般结合递归 对 可变参数包进行展开）
template<typename T ,typename... Args>
std::ostream &print(std::ostream &os , const T &t , Args... args){ //*包拓展： 拓展 Args 为print 生成函数参数列表

    os << t <<" , ";
    return print(os,args...); //*包拓展： 拓展 args  生成实参列表
}

//* 包拓展
template <typename... Args>
std::ostream &errorMsg(std::ostream &os, const Args... rest){
    //*等价于 第二个参数为 print（a1）, print（a2）...一次展开 单独的调用
    //*若 入参为 print(rest...) 则在参数列表内进行包拓展  相当于 print(a1,a2,a3...)
    return print(os,print(rest)...); 
}

//* 转发参数包 结合 完美转发 来实现 统一接口的调用
//* 为一个函数实现两种调用方式，分为单参数和两个参数
template<typename T>
void _FieldHandler(T value){
    std::cout<<"单参数函数 "<<value<<std::endl;
}

template<typename T>
void _FieldHandler(T value,T olevalue){
    std::cout<<"双参数函数 "<<value<<' '<<olevalue<<std::endl;
}

template<typename... Args>
void FieldHandler(Args... rest){
    return _FieldHandler(std::forward<Args>(rest)...);
}


// 可变参数模板函数普通调用
void test_one(){
    foo("1",1,1,1,1);
    foo("3",2,2);
}

//可变参数模板 打印入参数据
void test_two(){
    print(std::cout,"a",1,"c",2.2);
}

int main(){

    FieldHandler("a","b");
    FieldHandler("a");
    return 0;
}