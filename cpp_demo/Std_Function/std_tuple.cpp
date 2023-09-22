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

//* 递归展开 输出tuple 元素
template<typename Tuple , size_t N>
struct tuple_show
{
    static void show(const Tuple &t)
    {
        //输出最后一位元素的内容，然后递归调用函数获取下一位的内容
        std::cout<< ", " << std::get<N - 1>(t);//模板类型是编译阶段定义的，因此这里的N-1不算做变量，可以用在std::get 里
        tuple_show<Tuple, N - 1>::show(t);       
    }
};

//* 偏特性，可以理解为递归的终止
template<typename Tuple>
struct tuple_show <Tuple,1>
{
    static void show(const Tuple &t)
    {
        //输出最后一位元素的内容，然后递归调用函数获取下一位的内容
        std::cout<< ", " << std::get<0>(t);     
    }
};

//调用函数
template<typename... Args>
void show_tuple(const std::tuple<Args...>& t){
    std::cout<<"[";
    //sizeof...(Args) : tuple 的类型数量
    tuple_show<decltype(t), sizeof...(Args)>::show(t);
    std::cout<<"]"<<std::endl;
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
    //5.获取元组元素个数
    std::tuple<char,int,long,std::string> tuple4('A',4,4.0,"F");
    //tuple类型 写着比较长，用decltype 进行推断是一种不错的选择
    int t4_count = std::tuple_size<decltype(tuple4)>::value;
    std::cout<<"元组个数为 "<<t4_count<<std::endl;
    //6、访问元组钟的元素
    std::tuple<char,int,long,std::string> tuple5('A',4,4.0,"F");
    std::cout<<"元组 第一个 元素 为 "<<std::get<0>(tuple5)<<std::endl;
    std::cout<<"元组 int 元素 为 "<<std::get<int>(tuple5)<<std::endl;
    //7、获取元组中元素的类型
    std::tuple<char,int,long,std::string> tuple6('A',4,4.0,"F");
    //获取指定位置类型 并声明变量
    std::tuple_element<3,decltype(tuple6)>::type val_6;
    //获取指定位置数据元素 并给声明的变量赋值
    val_6 = std::get<3>(tuple6);
    std::cout<<"val_6 为 "<<val_6<<std::endl;

    //使用std::tie 解包
    std::tuple<char,int,long,std::string> tuple7('A',4,4.0,"F");
    // 定义变量，保存解包结果
    auto tuple_0    = '0';
    int tuple_1        = 0;
    long tuple_2    = 0;
    std::string tuple_3("");
    std::tie(tuple_0,std::ignore,tuple_2,tuple_3) = tuple7;
    //C++17 结构化绑定,接收到的tuple对象内容，自动绑定到对应变量上（按顺序）
    auto [t1,t2,t3,t4] = tuple7;
    std::cout<<"tuple_0 = "<<tuple_0<<" t1 = "<<t1<<std::endl;
    //元组拼接
    std::tuple<char, int, double> first('A', 1, 2.2f);
    // 组合到一起, 使用auto, 自动推导
    auto second = std::tuple_cat(first, std::make_tuple('B', std::string("-=+")));
    // 组合到一起，可以知道每一个元素的数据类型时什么 与 auto推导效果一样
    std::tuple<char, int, double, char, std::string> tuple8 = std::tuple_cat(first, std::make_tuple('B', std::string("-=+")));
    show_tuple(tuple8);

    


}