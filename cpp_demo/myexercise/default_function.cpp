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
    Date(int n)
    {
        _ptr = (int*)malloc(n*sizeof(int));//申请一个n个int长度的int指针
    }

    //析构函数
    ~Date()
    {
        cout<<"析构函数"<<endl;
        if(_ptr){
            cout<<"清理申请的指针,或任何形式申请出来的占用空间"<<endl;
            free(_ptr);//清理工作，也就是释放动态开辟的空间。
            _ptr = NULL ;
        }
    }

    //拷贝构造函数
    Date(const Date& d)
    {
        cout<<"拷贝构造函数"<<endl;
        _year = d._year;
        _month = d._month;
        _day = d._day;
    }

    //赋值运算符重载函数
    Date& operator= (const Date& d)//&是引用传参
    {
        if(this != &d) //&是取地址，这里是防止自己给自己赋值的情况
        {
            this->_year = d._year;
            this->_month = d._month;
            this->_day = d._day;
        }
        return *this;//返回了默认参数*this指针指向的对象的引用
    }

    //普通取地址操作符重载
    Date* operator& (){
        cout<<"普通取地址符重载"<<endl;
        return this;
    }

    //const 取地址操作符重载
    const Date* operator& () const {
        cout<<"const 取地址符重载"<<endl;
        return this;
    }


public:
    int _year;
    int _month;
    int _day;
    int *_ptr = NULL;
};
int main()
{
    Date d1(1,2,3);
    const Date d2(4,5,6);

    Date* pd1 = &d1;
    const Date* pd2 = &d2;
    &d1;
    &d2;
    getchar();

}