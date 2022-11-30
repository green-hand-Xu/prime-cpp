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



//类 Student
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


//* const_cast<>() 使用方法
//* 1、 对 指针对象 使用const_cast 常量指针 被强转为 非常量指针，且仍然指向原来的对象
//* 指向常对象的指针，并不是该对象无法被修改，而是该指针没有修改对象的权限，
//* 就算该指针被重新赋值，其仍为指向常对象的指针，无法对新对象进行修改。
void demo7(){
    Student *Stu1 = new Student(1); // 普通 对象指针
    const Student *Stu2 = new Student(2); // 指针指的对象为常量
    const Student *const Stu3 = new Student(3); // 指针和指针指的对象都为常量
        //* 去 const 
    Student *Stu4 = const_cast<Student *>(Stu2); // 去掉Stu2的 指向对象的const NO=2
    const Student *Stu5 = const_cast<Student*>(Stu3); // 只去掉Stu3的 指针本身的const ，去掉后可对指针本身进行修改 NO=3
    Student *const Stu6 = const_cast<Student*>(Stu3); // 只去掉Stu3的 指针指向对象的const ，去掉后可对 对象的值进行修改 NO=3
    Student *Stu7 = const_cast<Student *>(Stu3); // 将Stu3的 两种const 都去掉 NO=3

    cout<<"常量指针 被强转为 非常量指针，且仍然指向原来的对象,地址不变"<<endl;
    cout<<"Stu4地址="<<Stu4<<" Stu4数据="<<Stu4->No1<<endl;
    cout<<"Stu5地址="<<Stu5<<" Stu5数据="<<Stu5->No1<<endl;
    cout<<"Stu6地址="<<Stu6<<" Stu6数据="<<Stu6->No1<<endl;
    cout<<"Stu7地址="<<Stu7<<" Stu7数据="<<Stu7->No1<<endl;

    cout<<""<<endl;
    cout<<"去掉const后,部分属性可进行修改,由于修改的都是同一地址数据,所以相互之间会有影响"<<endl;
    Stu4->No1 = 4;//Stu4 去掉了 const 然后可以修改No1数据,此时Stu2.No1 = 4
    cout<<"Stu4地址="<<Stu4<<" Stu4数据="<<Stu4->No1<<endl;

    Stu5 = Stu1;//Stu5 去掉了 指针的 const ，指针本身可以改，指向的数据仍未 const 不可改。
    cout<<"Stu5地址="<<Stu5<<" Stu5数据="<<Stu5->No1<<endl;

    Stu6->No1 = 6; //Stu6 去掉了指针指向对象的const ， 可以修改对象数据，但指针本身不可改,此时Stu2.No1 = 6
    cout<<"Stu6地址="<<Stu6<<" Stu6数据="<<Stu6->No1<<endl;

    Stu7->No1 = 7; //Stu7 去掉了两个const 指针本身和指向对象数据皆可修改,此时Stu2.No1 = 7
    cout<<"Stu7地址="<<Stu7<<" Stu7数据="<<Stu7->No1<<endl;

    //由于指针强转为非常量指针后，指向原对象，所以Stu2，Stu3的数据都被修改了
    cout<<"Stu2地址="<<Stu2<<" Stu2数据="<<Stu2->No1<<endl;
    cout<<"Stu3地址="<<Stu3<<" Stu3数据="<<Stu3->No1<<endl;
    
}

//* const_cast<>() 使用方法
//* 2、 对类对象 使用 const_cast 
//* 常量对象 被强转为 非常量对象，此过程赋值运算符 构造了新的对象 ，新的对象去掉了源对象的部分const属性
void demo8(){
    const Student Stu1(1); // const 修饰的 对象,Stu1 内容无法直接修改

    Student Stu2 = const_cast<Student&>(Stu1); // 赋值操作构造了新的对象，新对象去掉了元对象的const属性
    Student& Stu3 = const_cast<Student&>(Stu1);// 引用对象去掉了原对象的const属性
    Student* Stu4 = const_cast<Student*>(&Stu1);// 对象地址(相当于常指针) 去const属性后赋给指针

    // 修改去const后的对象的成员属性
    Stu2.No1 = 2; 
    Stu3.No1 = 3;
    Stu4->No1 = 4;

    cout<<"Stu1.No1="<<Stu1.No1<<" Stu1 地址为："<<&Stu1<<endl;
    cout<<"Stu2.No1="<<Stu2.No1<<" Stu2 地址为:"<<&Stu2<<endl;
    cout<<"Stu3.No1="<<Stu3.No1<<" Stu3 地址为:"<<&Stu3<<endl; //因为是引用所以和元地址相同
    cout<<"Stu4.No1="<<Stu4->No1<<" Stu4 地址为:"<<&Stu4<<endl;

}

//* const_cast<>() 使用方法
//* 3、 对 局部变量 使用 const_cast
void demo9(){
    //* volatile：系统总是重新从它所在的内存读取数据
    const volatile int a = 100;//整型常量 
    const int c = 200;//整型常量

    int *p = const_cast<int *>(&a); //常量引用被转为 非常量指针，仍指向原来的对象
    int pp = const_cast<int&>(c); //去const的引用，进行了赋值操作，构造了新对象
    int &ppp = const_cast<int &>(a);//去const 转换成引用，仍指向原来的对象


    *p = 150;
    pp = 250;
    ppp = 300;

    cout<<"a="<<a<<" a的地址为:"<<&a<<endl; // 150  
    cout<<"p="<<*p<<" p的地址为:"<<p<<endl; // 150  p的地址与a相同
    cout<<"pp="<<pp<<" pp的地址为:"<<&pp<<endl;//300
    cout<<"ppp="<<ppp<<" ppp的地址为:"<<&ppp<<endl;// 300 ppp的地址与a相同

}

//* reinterpret_cast<>() 使用方法
void demo10(){
	int num = 0x00636261;//用16进制表示32位int，0x61是字符'a'的ASCII码
	int * pnum = &num;
	char * pstr = (char *)(pnum);
	cout<<"pnum指针的值: "<<pnum<<endl;
    //直接输出pstr会输出其指向的字符串(ostream对char的输出进行了重载)，这里的类型转换是为了保证输出pstr的值
	cout<<"pstr指针的值: "<<static_cast<void *>(pstr)<<endl;
	cout<<"pnum指向的内容: "<<hex<<*pnum<<endl;
	cout<<"pstr指向的内容: "<<pstr<<endl;

}



int main(){

   demo10();

    return 0;
}