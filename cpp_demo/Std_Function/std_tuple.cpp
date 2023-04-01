/**
 * @file std_tuple.cpp
 * @author your name (you@domain.com)
 * @brief std::tuple 练习
 * @version 0.1
 * @date 2023-04-01
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <tuple>
#include <iostream>
#include <string>
#include <stdexcept>
#include <functional>
//返回类型为tuple的函数，可以使用列表初始化进行赋值。 
std::tuple<double, char, std::string> get_student(int id)
{
    switch (id)
    {
        case 0: return {3.8, 'A', "Lisa Simpson"};
        case 1: return {2.9, 'C', "Milhouse Van Houten"};
        case 2: return {1.7, 'D', "Ralph Wiggum"};
        case 3: return {0.6, 'F', "Bart Simpson"};
    }
 
    throw std::invalid_argument("id");
}


 
int main()
{   
    // 创建并初始化tuple对象
    std::tuple<std::string,std::string,int> tuple1{"a","a",1};//构造函数 列表初始化
    std::tuple<std::string,std::string,int> tuple2;
    tuple2 = std::make_tuple("b","b",2);//使用 make_tuple

    int i_third = 3;
    std::tuple<int&> third(std::ref(i_third));//创建元素是引用的元组

    std::tuple<int,int> tuple3{0,1};
    //std::get 模板方法返回的是数据的引用，因此可以用来修改元组中保存的数据
    std::get<0>(tuple3) = 2;

    std::cout <<std::get<0>(tuple3)<<std::endl;

    //1.std::get<索引>形式
    const auto student0 = get_student(0);
    std::cout << "ID: 0, "
              << "GPA: " << std::get<0>(student0) << ", "
              << "grade: " << std::get<1>(student0) << ", "
              << "name: " << std::get<2>(student0) << '\n';
    //2.std::get<泛型>形式
    const auto student1 = get_student(1);
    std::cout << "ID: 1, "
              << "GPA: " << std::get<double>(student1) << ", "
              << "grade: " << std::get<char>(student1) << ", "
              << "name: " << std::get<std::string>(student1) << '\n';
 
    double gpa2;
    char grade2;
    std::string name2;

    //3.std::tie() 创建一个左值引用的元组，或将元组拆包到各个对象中
    std::tie(gpa2, grade2, name2) = get_student(2);
    std::cout << "ID: 2, "
              << "GPA: " << gpa2 << ", "
              << "grade: " << grade2 << ", "
              << "name: " << name2 << '\n';
 
    //4.C++17 结构化绑定,接收到的tuple对象内容，自动绑定到对应变量上（按顺序）:
    const auto [ gpa3, grade3, name3 ] = get_student(3);
    std::cout << "ID: 3, "
              << "GPA: " << gpa3 << ", "
              << "grade: " << grade3 << ", "
              << "name: " << name3 << '\n';

}