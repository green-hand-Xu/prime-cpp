/**
 * @file EBOdemo.cpp
 * @author XuYingBo (you@domain.com)
 * @brief 用于帮助理解空基类优化的练习demo
 * @version 0.1
 * @date 2023-11-13
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <iostream>
#include <type_traits>
#include <memory>


using namespace std;
static int id = 0;


template <typename... Types>
class SelfTuple;

/*
    SelfTuple<Test1,Test2,Test3> : private SelfTuple <Test2,Test3>  : private SelfTuple <Test3>
*/

template <typename FirstT, typename ...Rest>
class SelfTuple<FirstT, Rest...>
{
    FirstT val;
public:
    SelfTuple(): val(){
        std::cout<<"SelfTuple<FirstT...> sizeof = "<<sizeof...(Rest)<<std::endl;
    }
};

template <>
class SelfTuple<> {
    public:
    SelfTuple<>(){
        std::cout<<"SelfTuple< "<< id <<" >"<<std::endl;
        id++;
    }
};


struct Test1{
    Test1(){
        std::cout<< "Test1\n";
    }
};

struct Test2{
    Test2(){
        std::cout<< "Test2\n";
    }
};

struct Test3{
    Test3(){
        std::cout<< "Test3\n";
    }
};



template<typename T >
void add(T a1, T a2){
    a1 = a1 + a2;
}

template<typename T>
typename std::enable_if<std::is_reference<T>::value,void>::type add(T& a1, T& a2){
    a1 = a1 + a2;
}

//判断类型
template <typename _Tp>
struct Smart_pointer : public false_type {};

template <typename _Tp>
struct Smart_pointer<std::weak_ptr<_Tp>> : public true_type {};

template <typename _Tp>
struct Smart_pointer<std::shared_ptr<_Tp>> : public true_type {};

template <typename _Tp>
struct is_smart_pointer : public Smart_pointer<typename std::remove_cv<_Tp>::type>{};

//若 模板参数为 智能指针则选用此函数
template <typename _Tp>
typename enable_if<is_smart_pointer<_Tp>::value,void>::type check(_Tp p){
    std::cout << "is smart pointer" << std::endl;
}
//若 模板参数不为智能指针则选用此函数
template <typename _Tp>
typename enable_if<!is_smart_pointer<_Tp>::value,void>::type check(_Tp p){
    std::cout << "not smart pointer" << std::endl;
}
void test_enable_if(){
    int *p = new int(3);
    std::shared_ptr<int> sp = std::make_shared<int>(3);
    check(sp);
    check(p);
    delete p;
}

int main(){
    int a1 = 1;
    int a2 = 2;
    int& a3 = a1;
    int& a4 = a2;
    add(a3,a4);
    add(1,2);
    test_enable_if();
    std::cout<<a1<<std::endl;
}