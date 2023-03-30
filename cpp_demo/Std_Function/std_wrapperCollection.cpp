/**
 * @file std_wrapperCollection.cpp
 * @author your name (you@domain.com)
 * @brief 各类包装器的练习合集 
 * *包含 std::reference_wrapper std::ref std::cref std::mem_fn std::bind  std::make_pair std::make_tuple
 * *std::function 见function的专门的练习例子
 * @version 0.1
 * @date 2023-03-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <random> //std::iota
#include <functional>
#include <iostream>
#include <list>
#include <vector>

void print(std::string const rem, std::list<int> const& v)
{
    std::cout << rem;
    for (auto i = v.begin() ; i != v.end() ; i++ ){
        std::cout << *i << ' ';
    }
    std::cout << '\n';
}

void func(int a){
    std::cout<<"a = "<<a<<std::endl;
}

void func1(int &a,int &b,int &c){
    std::cout<<"a = "<<a<<" b = "<<b<<" c = "<<c<<std::endl;
    std::cout<<"&a = "<<&a<<" &b = "<<&b<<" &c = "<<&c<<std::endl;
    a += 1;
    b += 10;
    c += 100;
}

int main(){

    std::list<int> l(10);
    //往 l list 中 填充数据
    std::iota(l.begin(), l.end(), -4);

    //* std::reference_wrapper
    std::reference_wrapper<void(int)> R_FUN=func;//声明一个 引用包装器对象
    R_FUN(10);
    //使用get（）方法可以获取保存的对象的内容，这里返回的是一个函数指针
    auto fun_p = R_FUN.get();  
    
    std::vector<std::reference_wrapper<std::list<int>>> v;//声明一个存储 list 引用包装器对象 的vector 容器
    v.push_back(l);
    //vector中保存的list 引用包装器对象 可以当正常的引用使用
    print("list: ",v.at(0));

    int n1 = 1, n2 = 10, n3 = 100;
    int& r1 = n1;
    int& r2 = n2;
    //创建一个函数 bind 对象，参数使用固定传入的方式
    std::function<void()> f1 = std::bind(func1,r1,r2,std::ref(n3));
    std::cout<<"==========首次调用f1==========="<<std::endl;
    f1();//初次调用，传入 r1 r2 std::ref(n3)

    std::cout<<"调用完后 只改变了 本地变量n3 的值,虽然r1 r2传的是引用,但是bind是对参数直接拷贝,无法传入引用"<<std::endl;
    std::cout<<"r1 = "<<r1<<" r2 = "<<r2<<" n3 = "<<n3<<std::endl;
    std::cout<<"&r1 = "<<&r1<<" &r2 = "<<&r2<<" &c = "<<&n3<<std::endl;

    std::cout<<"===========第二次调用f1================="<<std::endl;
    f1();//再次调用，此时上一步传入的值 已经有了变化
    std::cout<<"多次调用,仍然无法改变r1 r2 的引用的对象的值"<<std::endl;
    std::cout<<"r1 = "<<r1<<" r2 = "<<r2<<" n3 = "<<n3<<std::endl;
    std::cout<<"&r1 = "<<&r1<<" &r2 = "<<&r2<<" &c = "<<&n3<<std::endl;

    return 0;
}