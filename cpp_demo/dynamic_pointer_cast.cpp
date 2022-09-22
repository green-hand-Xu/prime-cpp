#include <iostream>
#include <memory>
struct A {
   static const char* static_type;
   const char* dynamic_type; //基类中声明变量用于区别转换后的类型
   A() { dynamic_type = "是基类成员"; }
};
struct B: A {
   static const char* static_type;
   B() { dynamic_type = static_type; }
};
const char* A::static_type = "sample text A";
const char* B::static_type = "sample text B";
int main () {
   //声明共享指针 foo bar 指向A类和B类
   std::shared_ptr<A> foo; 
   std::shared_ptr<B> bar;  

   // 创建bar 指针 同时 dynamic_type 在构造函数中 被赋值成了 sample text B
   bar = std::make_shared<B>();

   //给 foo 指针赋值 为将 bar指针 转换为基类类型的指针 此时foo 是一个基类指针 但是指向的是子类内容
   foo = std::dynamic_pointer_cast<A>(bar);
  // foo = std::make_shared<A>();

   std::cout << "foo's static type: " << foo->static_type << '\n';
   std::cout << "foo's dynamic type: " << foo->dynamic_type << '\n';
   std::cout << "bar's static type: " << bar->static_type << '\n';
   std::cout << "bar's dynamic type: " << bar->dynamic_type << '\n';
   return 0;
}