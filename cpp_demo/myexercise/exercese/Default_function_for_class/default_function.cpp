/**
 * 类的默认函数练习
*/
#include <iostream>

using namespace std;

template<typename T>
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
    
    //重载()运算符
    Date operator() (){
        cout<<"operator() "<<endl;
        return _month;
    }

    //重载类型转换运算符 注意与函数调用运算符的区别
    operator T() const{
        cout<<"重载 成员类型转换 运算符"<<endl;
        return _month;
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
    T _year;
    T _month;
    T _day;
    T *_ptr = NULL;
};
int main()
{
    Date<int> d1(1,2,3);
    const Date<int> d2(4,5,6);

    Date<int>* pd1 = &d1;
    const Date<int>* pd2 = &d2;

    //重载类型转换运算符后，当直接使用这个类型时，会自动调用方法
    cout<<d1<<endl;
    //等价于
    cout<<d1.operator int()<<endl; 
    
    d1();

    &d1;
    &d2;
    getchar();

}