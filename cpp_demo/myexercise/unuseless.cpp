#include <iostream>

using namespace std;

class Date
{
public:
    //构造函数
    Date(int year,int month,int day)
    {
        _year = year;
        _month = month;
        _day = day;
    }
    //拷贝构造函数
    Date(const Date& d)
    {
        cout<<"拷贝构造函数"<<endl;
        _year = d._year;
        _month = d._month;
        _day = d._day;
    }
private:
    int _year;
    int _month;
    int _day;
};

void demo9(){
    //* volatile：系统总是重新从它所在的内存读取数据
    //整型常量 加const 后 一些基本常量 会被编译器进行优化 存到寄存器里，后续直接使用寄存器里存的值
    const volatile int a = 100;
    const int c = 200;//整型常量

    int *p = const_cast<int *>(&a); //常量引用被转为 非常量指针，仍指向原来的对象
    int pp = const_cast<int&>(c); //去const的引用，进行了赋值操作，构造了新对象
    int &ppp = const_cast<int &>(a);//去const 转换成引用，仍指向原来的对象


    *p = 150;
    pp = 250;
    ppp = 300;
    // 有 volatile 声明 a = 150； 无 volatile 声明 a = 100；
    // 因为编译器优化 const a 的值存到了寄存器里，再输出时，默认取的寄存器的值 不是内存的值
    cout<<"a = "<<a<<endl;
    //下面输出的是指针内容，所以值是改变后的值，不是从寄存器拿的值
    cout<<"*p = "<<*p<<endl;
    cout<<"pp = "<<pp<<endl;
    cout<<"ppp = "<<ppp<<endl;

}

int main()
{
    demo9();
}

