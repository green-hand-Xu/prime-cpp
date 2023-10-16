/**
 * @file main.cpp
 * @author your name (you@domain.com)
 * @brief 重载、重写、覆盖与隐藏的区别
 * @version 0.1
 * @date 2023-10-16
 * 1、Overload（重载）：C++规定在同一作用域中，例如一个类的成员函数之间，多个函数的名称相同，但是各个函数的形式参数（指参数的个数、类型或者顺序）不同时，构成函数重载。
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

    int operator =(A& a){
        return 1;
    }

    void hidefun(){
        std::cout<<"class A hidefun() "<<std::endl;
    }

    virtual void showA(){
        std::cout<<"class A showA() "<<std::endl;
    }

    //*Overload（重载）：在同一个类中，函数名相同，参数列表不同
    void showA(int a){
        std::cout<<"class A showA(int a) "<<std::endl;
    }

    virtual void showAA(A& a){
        std::cout<<"class A showAA "<<std::endl;
    }

};

class B : public A
{
public:
    //使用 using 将基类中需要继承过来的重载方法 进行声明，可以直接加载父类重载方法过来，进行调用时不会被隐藏
    using A::hidefun;
    using A::operator=;
    //* 派生类的函数与基类的函数同名，但是参数不同。基类同名函数被隐藏，调用时找不到基类的单参和无参的同名方法
    void hidefun(int a,int b){
        std::cout<<"class B hidefun() "<<std::endl;
    }

    
    void showA(int a,int b){
        std::cout<<"class B showA(int a,int b) "<<std::endl;
    }

    virtual void showA() override{
        std::cout<<"class B showA() override"<<std::endl;
    }

    //* 重写
    void showAA(){
        std::cout<<"class B showA() "<<std::endl;
    }

    //* 覆盖：子类覆盖父类方法  加override 与不加 的区别是 编译器会不会去按照覆盖的规则去进行代码检查
    void showAA(A& a) override{
        std::cout<<"class B showAA() "<<std::endl;
    }

};

class C : public A
{
public:
    //* 函数重写 具有多态性
    void showAA(A& a) override{
        std::cout<<"class C showAA "<<std::endl;
    }
   
};

//* 实现多态 必须满足的条件
//1 必须通过基类的指针或者引用调用虚函数
//2 被调用的函数是虚函数，且必须完成对基类虚函数的重写
void DynamicShow(A& a){
    a.showAA(a);
}

A a;
B b;
C c;
B d;

void test1(){
    // 若子类没有 使用 using声明将名字加入作用域  则编译报错。找不到基类不带参数的方法（被隐藏）
    b.hidefun(); 
    std::cout<<(b=a)<<std::endl;
    b.hidefun(1,2); //这里使用的是子类自己的重载版本
}

void test2(){
    //根据传入类型决定调哪个类的重写方法
    DynamicShow(c);
}

int main(){
    
    return 0;
}