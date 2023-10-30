/**
 * @file FileIO.cpp
 * @author XuYingBo (you@domain.com)
 * @brief 文件读写练习
 * @version 0.1
 * @date 2023-10-30
 * a
 * @copyright Copyright (c) 2023
 * 
 */
#include <iostream>
#include <fstream>
#include <thread>

/**
 * @brief 参数和返回类型 是一个输入流的引用
 * 
 * @param is 
 * @return std::istream& 
 */
std::istream& input(std::istream& is){
    int a;
    while (is>>a)
    {
        std::cout<<a<<std::endl;
        if (a == 0)
        {
            is.setstate(std::cin.eofbit);
        }
    }
    
    is.clear();//重置流标志位
    return is;
}

void input_Test(){
    auto& in = input(std::cin);

	std::string s1;
	while(in >> s1)
		std::cout << s1 << std::endl;
}

void exchangestream(){
    //查看 cin 绑定的输出流
    std::cout<<std::cin.tie()<<std::endl;
    //解绑 cin 绑定的输出流
    std::cin.tie(nullptr);
    //查看 cin 绑定的输出流
    std::cout<<std::cin.tie()<<std::endl;
    //重新绑定
    std::cin.tie(&std::cout);
}


int main(){
    exchangestream();
    return 0;
}