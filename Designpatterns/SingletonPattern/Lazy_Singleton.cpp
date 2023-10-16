/**
 * @file Lazy_Singleton.cpp
 * @author your name (you@domain.com)
 * @brief 单例模式(Singleton Pattern，也称为单件模式)，使用最广泛的设计模式之一。其意图是保证一个类仅有一个实例，并提供一个访问它的全局访问点，该实例被所有程序模块共享。
 * @version 0.1
 * @date 2023-10-13
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <iostream>
#include <memory>

/*
    单例模式，使用返回局部静态变量的引用方式创建实例。
        局部静态变量生命周期与类相同，
*/
class Lazy_Singleton
{
private:
    Lazy_Singleton() = default;
    ~Lazy_Singleton() = default;
    Lazy_Singleton(const Lazy_Singleton&) = delete;
    Lazy_Singleton& operator=(const Lazy_Singleton&) = delete;

public:

    static Lazy_Singleton& getInstance(){
        static Lazy_Singleton instance;
        return instance;
    }

};


int main(){

    Lazy_Singleton::getInstance();
    Lazy_Singleton::getInstance();


}