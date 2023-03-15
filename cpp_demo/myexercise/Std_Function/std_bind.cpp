#include <random>
#include <iostream>
#include <memory>
#include <functional> //header std::bing
/**
 * @brief std::bind 的使用练习
 * 
 *        template< class F, class... Args >
 * 语法： std::function<> func = std::bind(F&& f, Args&&... args) 
 *        template< class R, class F, class... Args >  
 *       std::function<> func = std::bind(F&& f, Args&&... args)
 * 参数：
 *     f：将绑定到某些参数的可调用对象（函数对象、函数指针、函数引用、成员函数指针或数据成员指针）
 *     atgs:要绑定的参数列表，未绑定的参数由命名空间std:：placeholders的占位符_1、_2、_3…替换
 * 
 * 功能：函数模板bind为f生成一个转发调用包装器。调用此包装器相当于调用f，并将其某些参数绑定到args。      
 * 
 */
using namespace std;

void f(int n1, int n2, int n3, const int& n4, int n5)
{
    std::cout << n1 << ' ' << n2 << ' ' << n3 << ' ' << n4 << ' ' << n5 << '\n';
}
 
int g(int n1)
{
    return n1;
}
 
struct Foo {
    void print_sum(int n1, int n2)
    {
        std::cout << n1+n2 << '\n';
    }
    int data = 10;
};

int main(){

    cout<<"1、bind 用于普通函数"<<endl;
    int n = 7;
    auto f1 = std::bind(f,placeholders::_2,42,placeholders::_1,std::cref(n),n);
    n = 10;
    f1(1,2,1001);//若占位符只有两个，则当出现第三个参数时，会被抛弃。

    cout<<"2、lambda表达式 类似用法 ,区别就是 需要多写一个函数体"<<endl;
    n = 7;
    auto lambda = [&ncref=n,n](auto a,auto b,auto){
        f(b,42,a,ncref,n);
    };
    n = 10;
    lambda(1,2,1001);

    cout<<"3、bind 的参数列表里 继续套用 bind 对象,此时 占位符 是共享的"<<endl;
    auto f2 = std::bind(f,placeholders::_3,std::bind(g,std::bind(g,std::bind(g,placeholders::_3))),placeholders::_3,4,5); //实际参数 相当于前面三个都是_3
    f2(10,11,12);//占位符重复时，使用最后一个最新的占位符赋值
    f2(12,11,10);

    cout<<"4、使用随机数方法"<<endl;
    std::default_random_engine e;//声明一个默认随机数种子
    std::uniform_int_distribution<> d(0,20);//声明一个随机数生成方法，范围0-20
    auto rnd = std::bind(d,e);
    for(int n=0;n<10;n++){
        cout<<rnd()<<" ";
    }
    cout<<endl;

    cout<<"5、 bind 用于对象内的函数指针"<<endl;
    Foo foo;
    auto f3 = std::bind(&Foo::print_sum,&foo,95,placeholders::_1);
    f3(5);

    return 0;
}