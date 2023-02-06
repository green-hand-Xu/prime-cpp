#include <iostream>
#include <chrono>
#include <thread>
using namespace std;
 
class Base
{
private:
    /* data */
public:
    Base(/* args */);
    // ~Base();
};

Base::Base(/* args */)
{
    cout<<"父类构造函数"<<endl;
}

// Base::~Base()
// {
//     cout<<"父类析构函数"<<endl;
// }

class Son:public Base
{
private:
    /* data */
public:
    Son(/* args */);
    // ~Son();
};

Son::Son(/* args */)
{
    cout<<"子类构造函数"<<endl;
}

// Son::~Son()
// {
//     cout<<"子类析构函数"<<endl;
// }


int main()
{

    Son son1;

    return 0;
}