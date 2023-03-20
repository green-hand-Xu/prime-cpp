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
int main()
{
    Date d1(2018,1,1);
    //以下两种方法等价
    Date d2(d1);
    Date d3=d1;
}