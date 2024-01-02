/**
 * @file bitmask.cpp
 * @author XuYingBo (you@domain.com)
 * @brief 矩阵通信时，位掩码规则的计算方式
 * @version 0.1
 * @date 2024-01-02
 * 矩阵表中缩写定义  MSB>LSB 读取顺序为从高位向地位读取
 * DLC: 帧总长度，单位：字节（8bit）
 * MSB: （Most Significant Bit）：最高有效位，二进制中代表最高值的比特位，这一位对数值的影响最大。
 * LSB: （Least Significant Bit）：最低有效位，二进制中代表最低值的比特位。
 **ByteOrder: Motorola
 * 在内存中默认 数据读取方向为 从低位向高位读取
 * 
 ** 注： ByteOrder 用 Motorola 表示大端 用 Inter 表示小端
 * @copyright Copyright (c) 2024
 */

#include <iostream>
#include <algorithm>
#include <bitset>
#include <array>
using namespace std;

/**
 * @brief 打印数据成二进制格式
 * @param p 数据
 * @param length 数据长度 
 */
void printdata(uint8_t *p,int length){

    for (auto i = p; i < p+length; i++)
    {
        //按照二进制位打印出来
        cout<<bitset<8>(*i)<<" ";
    }
    cout<<endl;
}

/**
 * 打印地址
*/
void printaddr(uint8_t *p,int length){

    for (auto i = p; i < p+length; i++)
    {
        //按照二进制位打印出来
        cout<<(void *)i<<" ";
    }
    cout<<endl;
}

/**
 * 打印16进制
*/
void printdatax(uint32_t *p,int length){

    cout<<hex<<*p<<" ";
    cout<<endl;
}

/*
 *  PT_CAN CSA2	id = 0x0A1 
 *  DLC = 8
*/ 
struct CSA2
{
    uint8_t payload[8]{0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
};

/**
 * @brief A2R数据源
 */
struct Data{
    uint8_t SteerWheelAng{5}; // MSB 15  LSB 17
    uint8_t SteerWheelAngSign{0};// MSB  16  LSB 16
    uint8_t SteerWheelSpd{2};// MSB 31 LSB 33
    uint8_t SteerWheelSpdSign{0};// MSB 32 LSB 32
};

int main(){
    CSA2 csa;
    Data data;
    printdata((uint8_t *)&csa,sizeof(csa));
    printdata((uint8_t *)&data,sizeof(data));
}