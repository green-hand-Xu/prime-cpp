#include <iostream>
#include <functional>
class Date{
  public:
    Date(){}
    ~Date(){}

  bool equals(Date *x){
      if (this == x) return true;
      
      
    return false;
  }

  private:
    int month{0};
    int day{0};
    int year{0};
};

int FUN1(int a){
  if (a == 0)
  {
    return 0;
  }
  if (a == 1)
  {
    return 1;
  }
  return FUN1(a-1)+FUN1(a-2);
}

int FUN(int a){
  return FUN1(a);
}



void Test(){
  for (int i = 0; i < 100; i++)
  {
    std::cout<<FUN(i)<<std::endl;
  }
  
}

struct lambda{
  int operator ()(){
    return ++x;
  }

  private:
  int x=0;
};

std::function<int()>  meta_add(){
  lambda add;
  return add;
}

void TestTwo(){
  auto fun = meta_add();

  std::cout<<fun()<<std::endl;
  std::cout<<fun()<<std::endl;
  std::cout<<fun()<<std::endl;
}

int main(){
  Test();
  return 0;
}