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
 ** 1、startIndex : MSB所在字节数组下标：array[MSB/8]（利用了整数除法向下取整特性）
 ** 2、endIndex : LSB所在字节数组下标：array[LSB/8]
 ** 3、是否跨字节：
 **    1、isSingleByte(是否为单字节) : startIndex != endIndex
 **    2、isDoubleByte(是否为双字节) : endIndex - startIndex == 1
 **    3、isMultibyte(是否为多字节)  : endIndex - startIndex > 1
 ** 4、不夸字节时对齐方式：
 **     1、leftShift:左移位移量：(Msb % 8) + 1 - size
 ** 5、跨字节时对齐方式：先右移，再左移（从  [startIndex,endIndex) 右移， endIndex 左移 ）
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

 ** 解包 计算公式：array[index]: 声明的数组名字  MSB、LSB、size:矩阵表头名字
 ** 注意：解包时是从源数据处一个字节一个字节读的，因此需要先掩码计算，屏蔽掉字节内的无用位，只保留有效位，然后在位移至目标数据的对应位上
 ** 1、startIndex : MSB所在字节数组下标：array[MSB/8]（利用了整数除法向下取整特性）
 ** 2、endIndex : LSB所在字节数组下标：array[LSB/8]
 ** 3、是否跨字节：
 **    1、isSingleByte(是否为单字节) : startIndex != endIndex
 **    2、isDoubleByte(是否为双字节) : endIndex - startIndex == 1
 **    3、isMultibyte(是否为多字节)  : endIndex - startIndex > 1
 ** 4、不夸字节时对齐方式：
 **     1、rightShift:右移位移量：(Msb % 8) + 1 - size
 ** 5、跨字节时对齐方式：先左移，再右移 （从  [startIndex,endIndex) 左移， endIndex 右移 ）
 **     1、leftShift:左移位移量：size - ( (Msb % 8) + 1 )
 **     2、rightShift:右移位移量：(Lsb % 8)
 **     3、跨多个字节时，首位部分移位值同上 ，中间部分位移值如下
 **         map<uint,uint> midRightShift：中间部分数据对应的位移值 <索引,左移位移数>
 **         索引 = (startIndex,endIndex) 内所有整数
 **         左移位移数 = leftShift - { (索引 - startIndex) * 8 }
 ** 6、掩码计算方式：
 **   不跨字节：
 **     1、rightMask : 右移时掩码计算方式：{ {2 ^ ( (Msb % 8) + 1 ) } - 1 } - { {2 ^ (rightShift) } -1 }
 **   跨字节：
 **     1、leftMask : 左移时掩码计算方式：{ 2 ^ ((Msb % 8) + 1) } - 1
 **     2、rightMask : 右移时掩码计算方式：0xff - { { 2 ^ leftShift } - 1 }
 **     3、跨多个字节时，首位部分掩码同上 ，中间部分掩码一律为 0xff 
 */

#include <iostream>
#include <algorithm>
#include <bitset>
#include <array>
#include <cmath>
#include <map>
#include <typeinfo>
#include "shift.cpp"
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
 *  CAN数据格式。是一个字节数组 长度为矩阵中对应帧的 DLC 长度
 *  PT_CAN CSA2	id = 0x0A1 
 *  DLC = 8
*/ 
struct CSA2
{
    //* payload[DLC]
    uint8_t payload[8]{0,0,0,0,0,0,0,0};
};

/*
 * A2R数据源
 * 该数据是A核传入的
 */
struct Data{
    uint16_t SteerWheelAng{255}; // MSB 15  LSB 17  size 15    1110
    uint8_t SteerWheelAngSign{0};// MSB  16  LSB 16  size 1
    uint16_t SteerWheelSpd{2};// MSB 31 LSB 33 size 15
    uint8_t SteerWheelSpdSign{0};// MSB 32 LSB 32 size 1
};

//* 压包算法
struct In
{
    // 起始，结束位下标 已经长度
    uint Msb{0};
    uint Lsb{0};
    uint size{0};
    // 数组索引
    uint startIndex{0};
    uint endIndex{0};
    //* 跨字节标志位  依据此标志位判断 压包时，如何调用 left/right_shift 函数
    bool isSingleByte{0};
    bool isDoubleByte{0};
    bool isMultibyte{0};
    // 移位
    uint leftShift{0}; // 左移位
    uint rightShift{0xff}; // 右移位
    // 多字节时，中间部分数据 对应的 <索引,右移位移数>
    map<uint,uint> midRightShift;
    // 掩码
    uint leftMask{0}; // 左移位时的掩码
    uint rightMask{0xff};// 右移位时的掩码

    /**
     * @brief Construct a new In object
     * 
     * @param _Msb 矩阵中对应信号的 MSB 
     * @param _Lsb 矩阵中对应信号的 LSB
     * @param _size 矩阵中对应信号的 size
     */
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
            for (auto i : midRightShift)
            {
                cout<<" 第 "<<i.first<<" 个数组位置 , 右移位数 = "<<i.second<<" 掩码 = 255"<<endl;
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
        cout<<"以下为压包数据"<<endl;
        cout <<" Msb = "<<Msb << " Lsb = "<<Lsb<<" size = " <<size<<endl;
        cout <<" startIndex = "<<startIndex << " endIndex = "<<endIndex<<endl;
        printByteWidth();
        printShift();
        printMask();
        printMap();
    }
};

//* 解包算法 
struct Out
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

    /**
     * @brief Construct a new In object
     * 
     * @param _Msb 矩阵中对应信号的 MSB 
     * @param _Lsb 矩阵中对应信号的 LSB
     * @param _size 矩阵中对应信号的 size
     */
    Out(uint _Msb , uint _Lsb , uint _size){
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
            //* 不夸字节时 是不需要左移的 默认0xff
        }else{
            leftShift = size - ( (Msb % 8 ) + 1 );
        }   
    }
    
    void computeLeRightShift(){
        if (isSingleByte)
        {
            rightShift = ( Msb % 8 ) + 1 - size;
        }else{
            rightShift = Lsb % 8;
        }
    }

    void computeLeftMask(){
        if(isSingleByte){
            //* 不夸字节时 是不需要左移的 默认0xff
        }else{
            leftMask = pow(2,(Msb % 8) + 1) - 1;
        }    
    }

    void computeRightMask(){
        if (isSingleByte)
        {
            rightMask = ( pow(2,(Msb % 8) + 1) - 1 )- ( pow(2,rightShift) - 1 );
        }else{
            rightMask = 0xff - (pow(2,rightShift) - 1);
        }   
    }

    void computeMidData(){
        if (isMultibyte)
        {
            for (auto i = startIndex + 1 ; i < endIndex; i++){
                midRightShift[i] = leftShift - ((i - startIndex) * 8);
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
            for (auto i : midRightShift)
            {
                cout<<" 第 "<<i.first<<" 个数组位置 , 左移位数 = "<<i.second<<" 掩码 = 255"<<endl;
            }
        }
    }

    void printShift(){
        cout<<" rightShift = "<<rightShift;
        if (!isSingleByte)
        {
            cout <<" leftShift = "<<leftShift;
        }
        cout<<endl;
    }

    void printMask(){
        cout << " rightMask = "<<rightMask;
        if (!isSingleByte)
        {
            cout <<" leftMask = "<<leftMask;
        }
        cout<<endl;
    }

    void printInDate(){
        cout<<"以下为解包数据"<<endl;
        cout <<" Msb = "<<Msb << " Lsb = "<<Lsb<<" size = " <<size<<endl;
        cout <<" startIndex = "<<startIndex << " endIndex = "<<endIndex<<endl;
        printByteWidth();
        printShift();
        printMask();
        printMap();
    }
};


void TESTPack(){
    In SteerWheelAng(15,17,15);
    In SteerWheelAngSign(16,16,1);
    In SteerWheelSpd(31,33,15);
    In SteerWheelSpdSign(32,32,1);
    In MAC_Check_ABM1{87,120,48};
    MAC_Check_ABM1.printInDate();
    // A 核数据
    Data src;
    // 压包后数据
    CSA2 csa2;
    csa2.payload[SteerWheelAng.startIndex] = csa2.payload[SteerWheelAng.startIndex] | static_cast<uint8_t>(pack_right_shift_u16(src.SteerWheelAng,(uint8_t)SteerWheelAng.rightShift,(uint8_t)SteerWheelAng.rightMask));
    csa2.payload[SteerWheelAng.endIndex]   = csa2.payload[SteerWheelAng.endIndex]   | static_cast<uint8_t>(pack_left_shift_u16(src.SteerWheelAng,(uint8_t)SteerWheelAng.leftShift,(uint8_t)SteerWheelAng.leftMask));
}

void TESTUnpack(){
    Out SteerWheelAng(15,17,15);
    Out SteerWheelAngSign(16,16,1);
    Out SteerWheelSpd(31,33,15);
    Out SteerWheelSpdSign(32,32,1);
    Out MAC_Check_ABM1{87,120,48}; //MAC_Check_ABM1{MSB,LSB,SIZE}
    MAC_Check_ABM1.printInDate();

}
int main(){
    TESTPack();
    TESTUnpack();
    return 0;
}