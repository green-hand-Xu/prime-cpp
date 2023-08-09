/*
*   std::enable_if_t 是C++14 才支持的写法， C++11 为std::enable_if
*   enable_if 是可用用来帮助编译器在编译期间进行模板选择的struct。利用了c++的traits编程技法。
*
*/

#include <iostream>
// enable_if 的头文件
#include <type_traits>


using namespace std;

//定义一个person类
class person{};

//定义一个dog类
class dog{};

//用来判断是否是person类
template<typename T>
struct is_person{
   static const bool value = false;
} ;

template<>
struct is_person<person>{
   static const bool value = true;
};

//当T为person时，被调用
template<typename T, typename std::enable_if<is_person<T>::value, T> :: type* = nullptr>
void func(T t){
    // do something;
    cout << "person stuff"<<endl;
}

void func(int a){
    cout << "int type" <<endl;
}

//当T不是person时，被调用
template<typename T, typename std::enable_if<!is_person<T>::value, T> :: type* = nullptr>
void func(T t){
    // do something;
    cout << "not person stuff"<<endl;
}

int main(){
    func(5);  		// int type
    func(person());     // person stuff
    func(dog());	// not person stuff
}