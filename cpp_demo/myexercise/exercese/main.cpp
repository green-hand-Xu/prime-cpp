/**
 * @file EBOdemo.cpp
 * @author XuYingBo (you@domain.com)
 * @brief 用于帮助理解空基类优化的练习demo
 * @version 0.1
 * @date 2023-11-13
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <iostream>
#include <type_traits>

static int id = 0;



template<typename ... Types>
class SelfTuple;
/* First instantiated from: insights.cpp:25 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
class SelfTuple<Test2, Test3> : private SelfTuple<Test3>
{
  Test2 val;
  
  public: 
  inline SelfTuple()
  : SelfTuple<Test3>()
  , val{Test2()}
  {
    std::operator<<(std::cout, "SelfTuple<FirstT...> sizeof = ").operator<<(1).operator<<(std::endl);
  }
  
};

#endif
/* First instantiated from: insights.cpp:25 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
class SelfTuple<Test3> : private SelfTuple<>
{
  Test3 val;
  
  public: 
  inline SelfTuple()
  : SelfTuple<>()
  , val{Test3()}
  {
    std::operator<<(std::cout, "SelfTuple<FirstT...> sizeof = ").operator<<(0).operator<<(std::endl);
  }
  
};

#endif
/* First instantiated from: insights.cpp:63 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
class SelfTuple<Test1, Test2, Test3> : private SelfTuple<Test2, Test3>
{
  Test1 val;
  
  public: 
  inline SelfTuple()
  : SelfTuple<Test2, Test3>()
  , val{Test1()}
  {
    std::operator<<(std::cout, "SelfTuple<FirstT...> sizeof = ").operator<<(2).operator<<(std::endl);
  }
  
};

#endif


/*
    SelfTuple<Test1,Test2,Test3> : private SelfTuple <Test2,Test3>  : private SelfTuple <Test3>
*/

template<typename FirstT, typename ... Rest>
class SelfTuple<FirstT, Rest...> : private SelfTuple<Rest...>
{
  FirstT val;
  
  public: 
  inline SelfTuple()
  : val{}
  {
    std::operator<<(std::cout, "SelfTuple<FirstT...> sizeof = ").operator<<(sizeof...(Rest)).operator<<(std::endl);
  }
  
};



template<>
class SelfTuple<>
{
  
  public: 
  inline SelfTuple()
  {
    std::operator<<(std::operator<<(std::cout, "SelfTuple< ").operator<<(id), " >").operator<<(std::endl);
    id++;
  }
  
};



struct Test1
{
  inline Test1()
  {
    std::operator<<(std::cout, "Test1\n");
  }
  
};



struct Test2
{
  inline Test2()
  {
    std::operator<<(std::cout, "Test2\n");
  }
  
};



struct Test3
{
  inline Test3()
  {
    std::operator<<(std::cout, "Test3\n");
  }
  
};




int main()
{
  SelfTuple<Test1, Test2, Test3> t = SelfTuple<Test1, Test2, Test3>();
  std::cout.operator<<(sizeof(t)).operator<<(std::endl);
  return 0;
}
