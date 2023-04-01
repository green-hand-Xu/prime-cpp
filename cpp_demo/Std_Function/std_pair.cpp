/**
 * @file std_pair-tuple.cpp
 * @author your name (you@domain.com)
 * @brief tuple 与 pair 的练习文件
 * *可用于一个函数返回多个值的场景
 * @version 0.1
 * @date 2023-04-01
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <iostream>
#include <utility>
#include <functional>

class OBJ
{
public:
    OBJ(){

    }
    ~OBJ(){

    }

    void print(int i){
        std::cout<<" i = "<<i<<std::endl;
    }

};
//pair 对象作为参数使用
void fun(std::pair<OBJ,int> pair){
    pair.first.print(pair.second);
}


int main(){

    std::pair<std::string,double> pair1("pair1",3.14);//1.使用构造函数赋值
    std::pair<int,float> pair2;
    std::pair<int,float> pair3;

    //2.调用直接赋值
    pair2.first = 2;
    pair2.second = 2.2;

    //3.使用make_pair创建pair对象。
    pair3 = std::make_pair<int,float> (3,3.3);

    //4.泛型不写时，可以自动推断类型，会发生隐式转换
    pair3 = std::make_pair(3,3.3);

    //5.这里将4.4自动推断成double类型
    auto pair4 = std::make_pair(4,4.4);

    //6.用来保存对象
    std::pair<OBJ,int> pair5;
    fun(pair5);//pair作为参数
    //7.保存引用
    auto pair6 = std::make_pair(std::ref(pair1),pair2);

    //8.直接调用成员输出
    std::cout<<pair1.first<<pair1.second<<std::endl;
    //9.使用std::get 方法获取指定索引对象输出，或者对应泛型输出。
    std::cout<<std::get<0>(pair1)<<std::endl;
    std::cout<<std::get<double>(pair1)<<std::endl;

    //10.使用std::tuple_size<std::pair> 查看 pair 对象的长度
        //用于 pair对象时 该数值永远为2
    std::cout<<std::tuple_size<std::pair<std::string,double>>::value<<std::endl;

    return 0;
}