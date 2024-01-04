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

 ** 压包 计算公式：array[index]: 声明的数组名字  MSB、LSB、size:矩阵表头名字
 ** 1、startIndex : 起始位所在字节数组下标：array[MSB/8]（利用了整数除法向下取整特性）
 ** 2、endIndex : 结束位所在字节数组下标：array[LSB/8]
 ** 3、是否跨字节：
 **    1、isSingleByte(是否为单字节) : startIndex != endIndex
 **    2、isDoubleByte(是否为双字节) : endIndex - startIndex == 1
 **    3、isMultibyte(是否为多字节)  : endIndex - startIndex > 1
 ** 4、不夸字节时对齐方式：
 **     1、leftShift:左移位移量：(Msb % 8) + 1 - size
 ** 5、跨字节时对齐方式：先右移，再左移
 **     1、rightShift:右移位移量：size - ( (Msb % 8) + 1 ) 
 **     2、leftShift:左移位移量：(Lsb % 8)
 **     3、跨多个字节时，首位部分移位值同上 ，中间部分位移值如下
 **         map<uint,uint> midRightShift：中间部分数据对应的位移值 <索引,右移位移数>
 **         索引 = (startIndex,endIndex) 内所有整数
 **         右移位移数 = rightShift - { (索引 - startIndex) * 8 }
 ** 6、掩码计算方式：
 **   不跨字节：
 **     1、leftMask : 左移时掩码计算方式：{ {2 ^ ( (Msb % 8) + 1 ) } - 1 } - { {2 ^ (leftShift) } -1 }
 **   跨字节：
 **     1、leftMask : 左移时掩码计算方式：0xff - { { 2 ^ leftShift } - 1 }
 **     2、rightMask : 右移时掩码计算方式：{ 2 ^ ((Msb % 8) + 1) } - 1
 **     3、跨多个字节时，首位部分掩码同上 ，中间部分掩码一律为 0xff 
 */

#include <iostream>
#include <algorithm>
#include <bitset>
#include <array>
#include <cmath>
#include <map>
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

struct In
{
    // 起始，结束位下标 已经长度
    uint Msb{0};
    uint Lsb{0};
    uint size{0};
    // 数组索引
    uint startIndex{0};
    uint endIndex{0};
    // 跨字节标志位
    bool isSingleByte{0};
    bool isDoubleByte{0};
    bool isMultibyte{0};
    // 移位
    uint leftShift{0};
    uint rightShift{0xff};
    // 多字节时，中间部分数据 对应的 <索引,右移位移数>
    map<uint,uint> midRightShift;
    // 掩码
    uint leftMask{0};
    uint rightMask{0xff};

    In(uint _Msb , uint _Lsb , uint _size){
        Msb = _Msb;
        Lsb = _Lsb;
        size = _size;

        startIndex = Msb / 8;
        endIndex = Lsb / 8;
        isSingleByte = startIndex != endIndex ? false : true;
        isDoubleByte = (endIndex - startIndex) == 1 ? true : false;
        isMultibyte  = (endIndex - startIndex > 1) ? true : false;

        computeLeftShift();
        computeLeRightShift();
        computeLeftMask();
        computeRightMask();
        computeMidData();
    };

    void computeLeftShift(){
        if (isSingleByte)
        {
            leftShift = ( Msb % 8 ) + 1 - size;
        }else{
            leftShift = Lsb % 8;
        }
    }

    
    void computeLeRightShift(){
        if (isSingleByte)
        {
            //* 不夸字节时 是不需要右移的 默认0xff
        }else{
            rightShift = size - ( (Msb % 8 ) + 1 );
        }       
    }

    void computeLeftMask(){
        if (isSingleByte)
        {
            leftMask = ( pow(2,(Msb % 8) + 1) - 1 )- ( pow(2,leftShift) - 1 );
        }else{
            leftMask = 0xff - (pow(2,leftShift) - 1);
        }        
    }

    void computeRightMask(){
        if(isSingleByte){
            //* 不夸字节时 是不需要右移的 默认0xff
        }else{
            rightMask = pow(2,(Msb % 8) + 1) - 1;
        }
    }

    void computeMidData(){
        if (isMultibyte)
        {
            for (auto i = startIndex + 1 ; i < endIndex; i++){
                midRightShift[i] = rightShift - ((i - startIndex) * 8);
            }
        }
    }
    
    void printByteWidth(){
        if (isSingleByte)
        {
            cout <<" isSingleByte = "<<isSingleByte<<endl;
        }
        if (isDoubleByte)
        {
            cout <<" isDoubleByte = "<<isDoubleByte<<endl;
        }        
        if (isMultibyte)
        {
            cout <<" isMultibyte = "<<isMultibyte<<endl;
        }   
    }

    void printMap(){
        if (isMultibyte)
        {
            int n = 1;
            for (auto i : midRightShift)
            {
                cout<<" 除首尾外，中间第 "<<n<<" 个,右移位数 = "<<i.second<<endl;
                ++n;
            }
        }
    }

    void printShift(){
        cout <<" leftShift = "<<leftShift;
        if (!isSingleByte)
        {
            cout<<" rightShift = "<<rightShift;
        }
        cout<<endl;
    }

    void printMask(){
        cout <<" leftMask = "<<leftMask;
        if (!isSingleByte)
        {
            cout << " rightMask = "<<rightMask;
        }
        cout<<endl;
    }

    void printInDate(){
        cout <<" Msb = "<<Msb << " Lsb = "<<Lsb<<" size = " <<size<<endl;
        cout <<" startIndex = "<<startIndex << " endIndex = "<<endIndex<<endl;
        printByteWidth();
        printShift();
        printMask();
        printMap();
    }
};


int main(){
    In SteerWheelAng(7,56,64);
    SteerWheelAng.printInDate();
}