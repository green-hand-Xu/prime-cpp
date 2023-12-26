#include <vector>
#include <iostream>
#include <memory>
#include <algorithm>
#include <cstring>
using namespace std;

enum class Position : std::uint8_t{
    Front = 0,
    Behind = 1,
    Left = 2,
    Right = 3
};

//* 结构体成员默认按照最大的字节位数对齐
struct LightSet
{
  Position pos;
  uint16_t LightVal;
};


void NvmSet(std::vector<uint8_t> vec){
  for (int i = 0 ; auto v : vec)
  {
    cout<<" v["<<i<<"] = "<<(int)v<<" ";
    ++i;
  }
  cout<<endl;
}

int main(){
  LightSet lightset{Position::Right,10};
  uint8_t* begin = (uint8_t*)&lightset;
  uint8_t* end = begin + sizeof(lightset);
  //*1、容器初始化时传入迭代器（指针）范围
  vector<uint8_t> vec(begin,end);
  NvmSet(vec);

  //*2、memcpy
  lightset.LightVal = 20;
  memcpy(vec.data(),&lightset,sizeof(lightset));
  NvmSet(vec);
  auto ret = (LightSet*)vec.data();
  cout<<(int)ret->LightVal<<" "<<(int)ret->pos<<endl;
  
  //*3、直接手动存成员，然后进行类型转回
  vector<uint8_t> vec1;
  //*存的时候按照成员顺序手动存
  vec1.push_back((uint8_t)lightset.pos);
  vec1.push_back(lightset.LightVal);//!默认小端存储 这里unit16 转成了 uint8 高位丢失
  //! 取的时候按照内存强转回来 会出现字节对齐错误
  auto ret1 = (LightSet*)vec1.data();
  cout<<(int)ret1->LightVal<<" "<<(int)ret1->pos<<endl; 
  cout<<(int)lightset.LightVal<<" "<<(int)lightset.pos<<endl;
  NvmSet(vec1);
  return 0;
}