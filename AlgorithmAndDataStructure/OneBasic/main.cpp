#include <iostream>

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




int main(){
  Date a;
  Date b;
  std::cout<<a.equals(&b)<<std::endl;

  return 0;
}