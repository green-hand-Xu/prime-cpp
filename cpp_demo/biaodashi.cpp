/**
 * @file biaodashi.cpp
 * @author your name (you@domain.com)
 * @brief prime c++ 第四章 表达式相关练习
 * @version 0.1
 * @date 2022-11-25
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include <iostream>
#include <vector>
#include <typeinfo>
using namespace std;



// 括号的结合
void demo1(){
    std::vector<int> vec{1,2,3,4,5,6,7,8,9,10};

    std::cout<<*vec.begin()<<'\n';
    std::cout<<*vec.begin()+1<<'\n';

    //上面两个等价于
    std::cout<<(*vec.begin())<<'\n';
    std::cout<<(*vec.begin())+1<<'\n';
}

// 为表达式添加括号 说明求值过程及结果。
void demo2(){
    int a,b;
    //不加括号
    a=12/3*4+5*15+24%4/2;
    //加括号
    b=12/(3*4)+(5*15)+(24%4/2); 

    std::cout<<"a:"<<a<<'\n'<<"b:"<<b<<'\n';

}

// 算术转换练习
void demo3(){
    cout<<"int:"<<sizeof(int)<<endl;  //4
    cout<<"bool:"<<sizeof(bool)<<endl; //1
    cout<<"char:"<<sizeof(char)<<endl; //1
    cout<<"unsigned int:"<<sizeof(unsigned int)<<endl; //4
    cout<<"long:"<<sizeof(long)<<endl; //8
    cout<<"unsignde long:"<<sizeof(unsigned long)<<endl;//8

    unsigned long ulong = 1; // 8
    int i = -2; //4

    auto sum = ulong + i; // 无符号类型大小比带符号类型大小大，转换成无符号类型。
    const type_info &kind = typeid(sum);
    cout<<"sum 类型为："<<typeid(sum).name()<<"  value="<<sum<<endl; // unsigned long  

    long l = -3; //8
    uint u_int = 1; //4

    auto sum2 = l + u_int; // 无符号类型大小比带符号类型小，转换成带符号类型
    const type_info &kind2 = typeid(sum2);
    cout<<"sum 类型为："<<typeid(sum2).name()<<"  value="<<sum2<<endl;// long
}

// 类类型定义的转换
void demo4(){
    string s,t = "a value";
    while (cin >> s){
        cout <<s <<'\n';
    }
}

//static_cast
void demo5(){

    int j=5,i=3;
    //将int型转换成double型
    double slope = static_cast<double>(j)/i;
    cout<<"j/i="<<slope<<endl;

    double d = 3.14;
    void* p = &d;//正确：任何非常量对象的地址都能存入void*

    // 将void* 转换回初始的指针类型
    double *dp = static_cast<double*>(p); 
    cout<<*dp<<endl;
}

//const_cast
void demo6(){

    const char *cp;
    //! 对象是一个常量，使用const_cast执行写操作会产生未定义的后果。
    char *q = const_cast<char *>(cp);
    static_cast<string>(cp); // static_cast 可以改变表达式类型。
    //! 不能用const_cast改变表达式的类型。
    //! const_cast<string>(cp);

    //使用const_cast 增加const修饰
    int i = 100;
    int *j = &i;
    const int *k = const_cast<const int*>(j);
    //const int *m = j;   和这样写差不多

    //指的地址都一样
    cout <<i<<","<<&i<<endl; //100
    cout <<*j<<","<<j<<endl; //100
    cout <<*k<<","<<k<<endl; //100

    *j = 200;
    //*k = 200;   //error
}



const int a = 50;
//类 A
class Student
{
public:
	int No1;

public:
	Student(int value = 100);
};

Student::Student(int value) : No1(value)
{
}


//const_cast<>() 使用方法
void demo7(){
//* 指向常对象的指针，并不是该对象无法被修改，而是该指针没有修改对象的权限，
//* 就算该指针被重新赋值，其仍为指向常对象的指针，无法对新对象进行修改。

    //1. 对 指针对象 使用const_cast //*常量指针 被强转为 非常量指针，且仍然指向原来的对象
    Student *Stu1 = new Student(); // 普通 对象指针
    const Student *Stu2 = new Student(2); //指针指的对象为常量
    const Student *const Stu3 = new Student(3); // 指针和指针指的对象都为常量

    Student *Stu4 = const_cast<Student *>(Stu2); //去掉Stu2的 指向对象的const 
    const Student *Stu5 = const_cast<Student*>(Stu3); //只去掉Stu3的 指针本身的const ，去掉后可对指针本身进行修改
    Student *const Stu6 = const_cast<Student*>(Stu3); //只去掉Stu3的 指针指向对象的const ，去掉后可对 对象的值进行修改
    Student *Stu7 = const_cast<Student *>(Stu3); // 将Stu3的 两种const 都去掉

    cout<<"常量指针 被强转为 非常量指针，且仍然指向原来的对象,地址不变"<<endl;
    cout<<"Stu4地址="<<Stu4<<endl;
    cout<<"Stu5地址="<<Stu5<<endl;
    cout<<"Stu6地址="<<Stu6<<endl;
    cout<<"Stu7地址="<<Stu7<<endl;



}

void demo8(){
    volatile const int a = 10;
	int *p = const_cast<int*>(&a);
	*p = 20;
	cout << "a: "<<&a<<"-" << a << endl;
	cout << "*p: "<<p<<"-" << *p << endl;
}

int main(){

   demo7();

    return 0;
}