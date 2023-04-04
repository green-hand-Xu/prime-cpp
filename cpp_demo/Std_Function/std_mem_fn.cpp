#include <iostream>
#include <functional>
#include <memory>

//* 成员指针包装器。 std:：mem_fn为 指向成员的指针（函数 变量等） 生成包装对象

class Foo
{
private:
    /* data */
public:
    Foo(/* args */){}
    ~Foo(){}
    
    void display_greeting() {
        std::cout <<data<< " Hello, world.\n";
    }
    void display_number(int i) {
        std::cout << "number: " << i << '\n';
    }
    int add_xy(int x, int y) {
        return x + y;
    }
    template <typename... Args> int add_many(Args... args) {
        return (args + ...);
    }
    auto add_them(auto... args) {
        return (args + ...);
    }
 
    int data = 7;
};



int main(){
    
    Foo f = Foo{};
    Foo f2 = Foo{};
    f2.data = 10;

    auto greet = std::mem_fn(&Foo::display_greeting);//包装成员方法
    std::_Mem_fn<void(Foo::*)()> greet1 = std::mem_fn(&Foo::display_greeting);//等价于 auto 声明
    //调用时 传入的第一个参数为实例对象，之后的为函数参数
    greet(f);
    greet(f2);

    auto print_num = std::mem_fn(&Foo::display_number);//包装带参数的成员方法
    std::_Mem_fn<void(Foo::*)(int)> print_num = std::mem_fn(&Foo::display_number);//等价于 auto 声明
    print_num(f,5);//第一个参数为具体实例对象，第二个参数为函数参数

    auto access_data = std::mem_fn(&Foo::data);
    //mem_fn绑定成员变量时，输出变量 也要传入实例参数 类似bind
    std::cout<<"data:"<<access_data(f)<<std::endl;

    auto add_xy = std::mem_fn(&Foo::add_xy);
    std::cout<<add_xy(f,2,3)<<std::endl;

    //*和智能指针结合使用 除了传入实例对象，也可以传入指向对象的智能指针
    auto u = std::make_unique<Foo>();
    std::cout<<"access_date(u): "<<access_data(u)<<std::endl;
    std::cout<<"add_xy(u,1,2): "<<add_xy(u,1,2)<<std::endl;

    //*用于包装 成员 模板 函数
    auto add_many = std::mem_fn(&Foo::add_many<short,int,long>);
    std::cout<<"add_many(u, 1,2,3) : "<<add_many(u,1,2,3)<<'\n';
    auto add_them = std::mem_fn(&Foo::add_them<short,int,float,double>);
    std::cout << "add_them(u, ...): " << add_them(u, 5, 7, 10.2f, 13.0) << '\n';

}