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
//使用typedef 声明 函数指针 比传统方式声明 更简洁好用，可以当作参数 传进去，因为类型支持识别。
typedef void (*PrintFinCallback)();
void print(const char *text, PrintFinCallback callback) {
    printf("%s\n", text);
    callback();
}

void printFinCallback() {
    cout << "hhh" << endl;
}


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

    // 用于成员函数时，要传入对象实例，因为成员函数默认第一个为 this 指针参数，类型为自己的对象类型。
    // 此时就需要补全参数。用于全局函数或者静态函数时则不用补全。
    cout<<"5、 bind 用于对象内的函数指针"<<endl;
    Foo foo;
    Foo foo2;
    foo.data = 100;
    auto f3 = std::bind(&Foo::print_sum,&foo,1,placeholders::_1);
    f3(1);

    cout<<"6、函数指针的使用。"<<endl;
    print("test", printFinCallback);


    cout<<"7、bind 用于 std::mem_fn 对象 指向成员函数"<<endl;
    auto ptr_to_print_sum = std::mem_fn(&Foo::print_sum);
    auto f4 = std::bind(ptr_to_print_sum,&foo,95,placeholders::_1);
    f4(5);

    cout<<"8、bind 用于 一个指向成员数据的指针,可以输出成员值，此时占位符的入参为想要输出值的对象实例"<<endl;
    auto f5 = std::bind(&Foo::data,placeholders::_1);
    std::cout << f5(foo2)<<endl;

    cout<<"9、bind 用于std::mem_fn 对象 指向成员内成员变量"<<endl;
    auto ptr_to_data = std::mem_fn(&Foo::data);
    auto f6 = std::bind(ptr_to_data,placeholders::_1);
    cout<<f6(foo)<<endl;

    cout<<"10、使用智能指针去调用对象成员的引用"<<endl;
    cout<<f6(std::make_shared<Foo>(foo))<<endl;
    cout<<f6(std::make_unique<Foo>(foo2))<<endl;

    return 0;
}