/**
 * @file Lazy_Singleton.cpp
 * @author your name (you@domain.com)
 * @brief 单例模式(Singleton Pattern，也称为单件模式)，使用最广泛的设计模式之一。其意图是保证一个类仅有一个实例，并提供一个访问它的全局访问点，该实例被所有程序模块共享。
 * *懒汉单例模式存在的问题 ：new出来的对象 不进行手动删除的话 会有内存泄漏的风险。解决方法：1、使用智能指针 2、使用静态的嵌套类对象
 * @version 0.1
 * @date 2023-10-13
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <iostream>
#include <memory>

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