/**
 * @file main.cpp
 * @author XuYingBo (you@domain.com)
 * @brief 第十章 泛型算法相关练习
 * @version 0.1
 * @date 2023-12-12
 ** 只读算法
 ** 写容器元素算法
 ** 重排容器元素的算法 
 * @copyright Copyright (c) 2023
 * 
 */

#include <iostream>
#include <algorithm>  //大部分泛型算法的头文件
#include <numeric>
#include <utils.hpp>
using namespace std;

/**
 * * 只读算法
 * @brief count(range,value) 返回给定值在序列中出现的次数。
 * 
 */
void gf_count(){
    vector<int> vec{1,2,3,4,5,4,5,5,5,6,7,4,0};
    string str{"hello"};
    cout<<"4 出现的次数为："<<count(vec.begin(),vec.end(),4)<<endl;
    cout<<"5 出现的次数为："<<count(vec.begin(),vec.end(),5)<<endl;
    cout<<"l 出现的次数为："<<count(str.begin(),str.end(),'l')<<endl;
}

/**
 * * 只读算法
 * @brief accumulate(range,sum) 计算范围内元素的和，sum 参数为初始值，其类型决定了计算时的算术运算符
 * 头文件 numeric
 */
void gf_accumulate(){
    vector<int> vec{1,2,3};
    auto sum = accumulate(vec.begin(),vec.end(),0);
    cout<<sum<<endl;

    //* 字符串的 + 运算符 是字符串拼接，可以用求和函数 完成字符串拼接
    string str{"world"};
    //* 注 只有string 有+运算， char 类型没有重载+运算符，所以第三个参数需要显示声明为 string
    auto str1 = accumulate(str.begin(),str.end(),string("hello ")); //设置加初始值为 字符串 hello
    cout<<str1<<endl;
}
/**
 * * 只读算法
 * @brief equal(range,p2) 比较算法 比较第一个序列 range 范围内 和 第二个序列 p2 开始的元素是否相等。
 * * 注：接受单一迭代器表示第二个序列的算法，都假定第二个序列至少和第一个序列一样长。
 */
void gf_equal(){
    vector<int> vec1{1,2,3,4,5};
    vector<int> vec2{1,2,3,4,5,6};
    vector<int> vec3{1};
    auto b1 = equal(vec1.begin(),vec1.end(),vec2.begin());
    cout<< b1 <<endl; // true 
    auto b2 = equal(vec1.begin(),vec1.end(),vec2.begin()+3);
    cout<< b2 <<endl; // false 
    auto b3 = equal(vec1.begin(),vec1.end(),vec3.begin());
    cout<< b3 <<endl; // false  长度 不匹配 但不报错 会返回 false
}

/** 
 ** 写容器元素算法
 * @brief fill(range,value) 将range范围内的元素，设置成value的值
 * 
 */
void gf_fill(){
    vector<int> vec{1,2,3,4,5,6};
    fill(vec.begin(),vec.begin()+vec.size()/2,0);
    my_print(vec);
}

int main(){
    gf_fill();


    return 0;
}