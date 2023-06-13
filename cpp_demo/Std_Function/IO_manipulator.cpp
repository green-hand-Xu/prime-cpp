/**
 * @file IO_manipulator.cpp
 * @author your name (you@domain.com)
 * @brief 练习使用 std::hex std::oct std::dec std::setw std::setfill std::ostream::fill 用于输入和输出流中的使用方法
 * @version 0.1
 * @date 2023-06-13
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <iostream>
#include <sstream>
#include <bitset>
#include <iomanip>


void hex_oct_dec(){
    std::cout << "The number 42 in octal:   " << std::oct << 42 << '\n'
              << "The number 42 in decimal: " << std::dec << 42 << '\n'
              << "The number 42 in hex:     " << std::hex << 42 << '\n';
    //* 使用一次后 后面的所有 默认数字基数 都会改变，直到下次进行设置（一次设置只在当前输入输出语句中生效一次，新的语句不受限）
    std::cout << "The number 42 in octal:   " << std::oct << 42 <<" "<< 56 << '\n';      

    int n;
    std::istringstream("2A") >> std::hex >> n; //*在输入流中使用 std::hex
    std::cout << std::dec << "Parsing \"2A\" as hex gives " << n << '\n';
    //输出流在新的设置到来之前，一直保持格式不变
    std::cout << std::hex << "42 as hex gives " << 42 << " and 21 as hex gives " << 21 << '\n';
    //输出二进制
    std::cout << "The number 42 in binary:  " << std::bitset<8>{42} << '\n';
}

void m_setw(){
    std::cout << "no setw: [" << 42 << "]\n"
              << "setw(6): [" << std::setw(6) << 42 << "]\n"
              << "no setw, several elements: [" << 89 << 12 << 34 << "]\n"
              << "setw(6), several elements: [" << 89 << std::setw(6) << 12 << 34 << "]\n";
    //std::setw(n) 使用后若中间进行了 string 或 char 类型的 输出 则会 重置n为0 即不受限制
    std::cout << "setw(6): [" << std::setw(6) << 42 << "]\n"<< " ["<< 42 << "]\n";

    std::istringstream is("hello, world");
    char arr[10];
 
    is >> std::setw(6) >> arr;
    std::cout << "Input from \"" << is.str() << "\" with setw(6) gave \""
              << arr << "\"\n";
}

void m_setfill(){
    std::cout << "default fill: [" << std::setw(10) << 42 << "]\n"
              << "setfill('*'): [" << std::setw(10)
                                   << std::setfill('*') << 42 << "]\n"
                                   << " [ " << 42 <<" ]" << '\n'
                                   << "当前填充字符为：" << std::cout.fill()<<'\n' ;  
}

int main(){
    m_setfill();

    return 0;
}