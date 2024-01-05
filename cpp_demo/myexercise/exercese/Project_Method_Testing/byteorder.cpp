/**
 * @file byteorder.cpp
 * @author XuYingBo (you@domain.com)
 * @brief 用于探究大小端 内存位置之谜
 * @version 0.1
 * @date 2024-01-04
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <iostream>
#include <bitset>


using namespace std;

void Memorydirection(){
    uint16_t u16t = 769;// 0000 0011  0000 0001
    cout<<"769 2 进制形式"<<bitset<8>(u16t>>8)<<" "<<bitset<8>(u16t)<<endl;
    uint8_t* begin = (uint8_t*)&u16t;
    cout<<"取成员指针地址后 按照 uint8_t 读取 首位置 = "<<bitset<8>(*begin)<<" 第二个字节位置 值 = "<<bitset<8>(*(begin+1))<<endl;
}


int main(){
    Memorydirection();
}