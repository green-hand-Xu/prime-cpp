/**
 * @file main.cpp
 * @author your name (you@domain.com)
 * @brief 重载、重写、覆盖与隐藏的区别
 * @version 0.1
 * @date 2023-10-16
 * 1、Overload（重载）：重载是指不同的函数使用相同的函数名，但是函数的参数个数或类型（参数列表不同）。调用的时候根据函数的参数来区别不同的函数。
 * 2、Override（覆盖）：是指派生类函数覆盖基类函数，有以下特征：（1）不同的范围（分别位于派生类与基类）；（2）函数名字相同；（3）参数相同；（4）基类函数必须有virtual关键字
 * 3、Overwrite（重写）：是指在派生类中重新对基类中的虚函数重新实现。即函数名和参数都一样，只是函数的实现体不一样。
 * * 函数的覆盖和重写是一个意思的两个叫法
 * 4、隐藏：
 *      1、如果派生类的函数与基类的函数同名，但是参数不同。此时，不论有无virtual关键字，基类的函数将被隐藏（注意别与重载混淆）。
 *      2、如果派生类的函数与基类的函数同名，并且参数也相同，但是基类函数没有virtual关键字。此时，基类的函数被隐藏（注意别与覆盖混淆）。
 *      隐藏的原因：C++中,遇到一个函数调用,需要根据名字来确定调用的是哪一个函数,这时候如果派生类定义了该函数,就不会在基类的名字空间中去找。
 *      可以这么看，函数覆盖和函数隐藏共同构建了在具有集成关系的纵向作用域里面的同名函数的不同衍变，只不过函数覆盖的条件更加严格些。
 * 
 * 5、覆盖与隐藏的区别：覆盖指的是子类覆盖父类函数（被覆盖）。 隐藏指的是子类隐藏了父类的函数（还存在）。
 * @copyright Copyright (c) 2023
 * 
 */
#include <iostream>

class A
{
public:
    A(){
        std::cout<<" A Construct "<<std::endl;
    }

    void showA(){
        std::cout<<"class A showA() "<<std::endl;
    }

    //*Overload（重载）：在同一个类中
    void showA(int a){
        std::cout<<"class A showA(int a) "<<std::endl;
    }

    virtual void showAA(){
        std::cout<<"class A showAA() "<<std::endl;
    }

};

class B : public A
{

public:
    //*派生类的函数与基类的函数同名，但是参数不同。基类同名函数被隐藏，调用时找不到基类的单参和无参的同名方法
    void showA(int a,int b){
        std::cout<<"class B showA(int a,int b) "<<std::endl;
    }

    //*重写
    void showAA(){
        std::cout<<"class B showA() "<<std::endl;
    }

    //*覆盖：子类覆盖父类方法  加override 与不加 的区别是 编译器会不会去按照覆盖的规则去进行代码检查
    void showAA() override{
        std::cout<<"class B showAA() "<<std::endl;
    }

};

class C : public A
{
public:
   
};



A a;
B b;
C c;

int main(){
    //b.showA() 编译报错。找不到基类同名方法（被隐藏）
    b.showA(1,2);// 编译通过，因为两个参数类型的方法是在 b 内声明的
    b.showAA();// 子类覆盖父类方法，这里执行的的子类的实现
    b.showA();

    return 0;
}