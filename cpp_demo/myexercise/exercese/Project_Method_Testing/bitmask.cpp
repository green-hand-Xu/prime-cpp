/**
 * @file bitmask.cpp
 * @author XuYingBo (you@domain.com)
 * @brief 矩阵通信时，位掩码规则的计算方式
 * @version 0.1
 * @date 2024-01-02
 * 矩阵表中缩写定义  MSB>LSB 读取顺序为从高位向地位读取
 * DLC:  帧总长度，单位：字节（8bit）
 * MSB: （Most Significant Bit）：最高有效位，二进制中代表最高值的比特位，这一位对数值的影响最大。
 * LSB: （Least Significant Bit）：最低有效位，二进制中代表最低值的比特位。
 **ByteOrder(字节序): Motorola
 * 
 ** 注： ByteOrder 别名: Motorola 表示大端 用 Inter 表示小端

 ** 计算公式：array[index]: 声明的数组名字  MSB、size:矩阵表头名字
 **  ---------------------------- 位序递增算法 ------------------------------------------------------
 ** 1、startIndex : 起始位所在字节数组下标：array[MSB/8]（利用了整数除法向下取整特性）
 ** 2、endIndex : 结束位所在字节数组下标：array[(MSB+size-1)/8]
 ** 3、isSingleByte : 是否跨字节：startIndex != endIndex
 ** 4、不夸字节时对齐方式：
 **     1、leftShift:左移位移量：7 - (MSB % 8)
 ** 5、跨字节时对齐方式：先右移，再左移
 **     1、rightShift:右移位移量：MSB % 8
 **     2、leftShift:左移位移量：7 - ((MSB+size-1) % 8)
 ** 6、掩码计算方式：
 **   不跨字节：
 **     1、leftMask : 左移时掩码计算方式：{ {2 ^ (leftShift + 1) } - 1 } - { {2 ^ (8 - leftShift) } -1 }
 **   跨字节：
 **     1、leftMask : 左移时掩码计算方式：2 ^ (leftShift + 1) - 1
 **     2、rightMask : 右移时掩码计算方式：{ 2 ^ (rightShift + 1) } - 1


 **  ---------------------------- 位序递减算法 -------------------------------------------------------
 ** 1、startIndex : 起始位所在字节数组下标：array[MSB/8]（利用了整数除法向下取整特性）
 ** 2、endIndex : 结束位所在字节数组下标：array[(MSB+size-1)/8]
 ** 3、isSingleByte : 是否跨字节：startIndex != endIndex
 ** 4、不夸字节时对齐方式：
 **     1、leftShift:左移位移量：MSB % 8
 ** 5、跨字节时对齐方式：先右移，再左移
 **     1、rightShift:右移位移量：MSB % 8
 **     2、leftShift:左移位移量：7 - ((MSB+size-1) % 8)
 */

#include <iostream>
#include <algorithm>
#include <bitset>
#include <array>
#include <cmath>
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
    cout <<(void *)*p;
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
 * 该数据是A核传入的
 */
struct Data{
    uint8_t SteerWheelAng{5}; // MSB 15  LSB 17
    uint8_t SteerWheelAngSign{0};// MSB  16  LSB 16
    uint8_t SteerWheelSpd{2};// MSB 31 LSB 33
    uint8_t SteerWheelSpdSign{0};// MSB 32 LSB 32
};

//* 位序递增算法
struct Inc
{
    Inc(uint Msb , uint sizeBit){
        startBit = Msb;
        endBit = Msb + sizeBit -1;
        startIndex = Msb / 8;
        endIndex = endBit / 8;
        isSingleByte = startIndex != endIndex ? false : true;

        getLeftShift();
        getRightShift();
        getLeftMask();
        getRightMask();
    };

    uint getLeftShift(){
        if (isSingleByte)
        {
            leftShift = 7 - (startBit % 8);
        }else{
            leftShift = 7 - (endBit % 8);
        }
        return leftShift;
    }

    //* 不夸字节时 是不需要右移的 默认0xff
    uint getRightShift(){
        if (!isSingleByte)
        {
            rightShift = startBit % 8;
            return rightShift;
        }
        return 0xff;
    }

    uint getLeftMask(){
        if (isSingleByte)
        {
            leftMask = ( ( pow(2,leftShift+1) -1 ) - ( pow(2,8 - leftShift) - 1 ));
        }{//todo:
            leftMask = 0xff - (pow(2,leftShift) - 1);
        }
        return leftMask;
    }

    uint getRightMask(){
        if(!isSingleByte){
            rightMask = pow(2,rightShift + 1) -1 ;
        }
        return rightMask;
    }

    void printInDate(){
        cout <<" startBit = "<<startBit << " endBit = "<<endBit<<endl;
        cout <<" startIndex = "<<startIndex << " endIndex = "<<endIndex<<endl;
        cout <<" isSingleByte = "<<isSingleByte<<endl;
        cout <<" leftShift = "<<leftShift << " rightShift = "<<rightShift<<endl;
        cout <<" leftMask = "<<leftMask << " rightMask = "<<rightMask<<endl;
    }

    // 起始，结束位下标
    uint startBit{0};
    uint endBit{0};
    // 数组索引
    uint startIndex{0};
    uint endIndex{0};
    // 是否为单字节
    bool isSingleByte{0};
    // 移位
    uint leftShift{0};
    uint rightShift{0xff};
    // 掩码
    uint leftMask{0xffff};
    uint rightMask{0xffff};
};

struct Ind
{
    Ind(uint Msb , uint sizeBit){
        startBit = Msb;
        endBit = Msb + sizeBit -1;
        startIndex = Msb / 8;
        endIndex = endBit / 8;
        isSingleByte = startIndex != endIndex ? false : true;

        getLeftShift();
        getRightShift();
        getLeftMask();
        getRightMask();
    };

    uint getLeftShift(){
        if (isSingleByte)
        {
            leftShift = startBit % 8;
        }else{
            leftShift = endBit % 8;
        }
        return leftShift;
    }

    //* 不夸字节时 是不需要右移的 默认0xff
    uint getRightShift(){
        
        return 0xff;
    }

    uint getLeftMask(){
        
        return leftMask;
    }

    uint getRightMask(){
        
        return rightMask;
    }

    void printInDate(){
        cout <<" startBit = "<<startBit << " endBit = "<<endBit<<endl;
        cout <<" startIndex = "<<startIndex << " endIndex = "<<endIndex<<endl;
        cout <<" isSingleByte = "<<isSingleByte<<endl;
        cout <<" leftShift = "<<(int)leftShift << " rightShift = "<<rightShift<<endl;
        cout <<" leftMask = "<<leftMask << " rightMask = "<<rightMask<<endl;
    }

    // 起始，结束位下标
    uint startBit{0};
    uint endBit{0};
    // 数组索引
    uint startIndex{0};
    uint endIndex{0};
    // 是否为单字节
    bool isSingleByte{0};
    // 移位
    uint leftShift{0};
    uint rightShift{0xff};
    // 掩码
    uint leftMask{0};
    uint rightMask{0xff};
};


int main(){
    Inc SteerWheelAng(31,15);
    SteerWheelAng.printInDate();
}