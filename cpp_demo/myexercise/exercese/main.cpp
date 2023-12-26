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
  cout<<ret->LightVal<<" "<<(int)ret->pos<<endl;
  return 0;
}