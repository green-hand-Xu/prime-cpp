/**
 * @file DynReflection.cpp
 * @author XuYingBo (you@domain.com)
 * @brief 
 ** 动态反射的核心在动态类型的获取，那么可以在前面使用PRETTY_FUNCTION的基础上对其进行处理，从而使其可以在运行获取对象的类型
 ** __FUNCSIG__（WIN64）__PRETTY_FUNCTION__（GCC）会把函数名称（包括成员函数）和类名及参数列表都打出来。对模板的支持也非常到位。
 * @date 2023-12-22
 */
#include <iostream>
#include <string>
#include <type_traits>

#ifdef _WIN64
#define __FUNC__ __FUNCSIG__
#else
#define __FUNC__  __PRETTY_FUNCTION__
#endif

enum class DataType : int
{
  USB, 
  PCI, 
  HD, 
  NOT
};


enum DType
{
  USB, 
  PCI, 
  HD, 
  NOT
};


template<auto T>
std::basic_string_view<char, std::char_traits<char> > TypeInfo()
{
  std::basic_string<char> type = __PRETTY_FUNCTION__;
  unsigned long begin = type.find("T = ", 0) + 4;
  unsigned long end = type.find_last_of(';', std::basic_string<char>::npos);
  return std::basic_string_view<char, std::char_traits<char> >{type.data() + begin, end - begin};
}


/* First instantiated from: insights.cpp:81 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
std::basic_string_view<char, std::char_traits<char> > TypeInfo<2>()
{
  std::basic_string<char> type = std::basic_string<char>("std::string_view TypeInfo() [T = DataType::HD]", std::allocator<char>());
  unsigned long begin = type.find("T = ", 0) + 4;
  unsigned long end = type.find_last_of(';', std::basic_string<char>::npos);
  return std::basic_string_view<char, std::char_traits<char> >(type.data() + begin, end - begin);
}
#endif


/* First instantiated from: insights.cpp:66 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
std::basic_string_view<char, std::char_traits<char> > TypeInfo<0>()
{
  std::basic_string<char> type = std::basic_string<char>("std::string_view TypeInfo() [T = DataType::USB]", std::allocator<char>());
  unsigned long begin = type.find("T = ", 0) + 4;
  unsigned long end = type.find_last_of(';', std::basic_string<char>::npos);
  return std::basic_string_view<char, std::char_traits<char> >(type.data() + begin, end - begin);
}
#endif


/* First instantiated from: insights.cpp:66 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
std::basic_string_view<char, std::char_traits<char> > TypeInfo<1>()
{
  std::basic_string<char> type = std::basic_string<char>("std::string_view TypeInfo() [T = DataType::PCI]", std::allocator<char>());
  unsigned long begin = type.find("T = ", 0) + 4;
  unsigned long end = type.find_last_of(';', std::basic_string<char>::npos);
  return std::basic_string_view<char, std::char_traits<char> >(type.data() + begin, end - begin);
}
#endif


template<int s, int e>
struct static_for
{
  template<typename F>
  inline void operator()(const F & func) const
  {
    if(s < e) {
      func(std::integral_constant<int, s>());
      static_for<s + 1, e>()(func);
    } 
    
  }
};

/* First instantiated from: insights.cpp:40 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
struct static_for<1, 3>
{
  template<typename F>
  inline void operator()(const F & func) const;
  
  /* First instantiated from: insights.cpp:40 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<__lambda_62_27>(const __lambda_62_27 & func) const
  {
    if(1 < 3) {
      func.operator()(std::integral_constant<int, 1>());
      static_for<2, 3>().operator()(func);
    } 
    
  }
  #endif
  
  
  /* First instantiated from: insights.cpp:40 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<__lambda_62_27>(const __lambda_62_27 & func) const
  {
    if(1 < 3) {
      func.operator()(std::integral_constant<int, 1>());
      static_for<2, 3>().operator()(func);
    } 
    
  }
  #endif
  
};

#endif
/* First instantiated from: insights.cpp:40 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
struct static_for<2, 3>
{
  template<typename F>
  inline void operator()(const F & func) const;
  
  /* First instantiated from: insights.cpp:40 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<__lambda_62_27>(const __lambda_62_27 & func) const
  {
    if(2 < 3) {
      func.operator()(std::integral_constant<int, 2>());
      static_for<3, 3>().operator()(func);
    } 
    
  }
  #endif
  
  
  /* First instantiated from: insights.cpp:40 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<__lambda_62_27>(const __lambda_62_27 & func) const
  {
    if(2 < 3) {
      func.operator()(std::integral_constant<int, 2>());
      static_for<3, 3>().operator()(func);
    } 
    
  }
  #endif
  
};

#endif
/* First instantiated from: insights.cpp:40 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
struct static_for<3, 3>
{
  template<typename F>
  inline void operator()(const F & func) const;
  
  /* First instantiated from: insights.cpp:40 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<__lambda_62_27>(const __lambda_62_27 & func) const
  {
    std::operator<<(std::cout, "noting").operator<<(std::endl);
  }
  #endif
  
  
  /* First instantiated from: insights.cpp:40 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<__lambda_62_27>(const __lambda_62_27 & func) const
  {
    std::operator<<(std::cout, "noting").operator<<(std::endl);
  }
  #endif
  
};

#endif
/* First instantiated from: insights.cpp:62 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
struct static_for<0, 3>
{
  template<typename F>
  inline void operator()(const F & func) const;
  
  /* First instantiated from: insights.cpp:62 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<__lambda_62_27>(const __lambda_62_27 & func) const
  {
    if(0 < 3) {
      func.operator()(std::integral_constant<int, 0>());
      static_for<1, 3>().operator()(func);
    } 
    
  }
  #endif
  
  
  /* First instantiated from: insights.cpp:62 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<__lambda_62_27>(const __lambda_62_27 & func) const
  {
    if(0 < 3) {
      func.operator()(std::integral_constant<int, 0>());
      static_for<1, 3>().operator()(func);
    } 
    
  }
  #endif
  
};

#endif


template<int n>
struct static_for<n, n>
{
  template<typename F>
  inline void operator()(const F & func) const
  {
    std::operator<<(std::cout, "noting").operator<<(std::endl);
  }
};


constexpr const int s = static_cast<int>(DataType::USB);

constexpr const int e = static_cast<int>(DataType::NOT);


template<typename T>
std::basic_string_view<char, std::char_traits<char> > Typeof(T t)
{
  int t1 = static_cast<int>(t);
  std::basic_string_view<char, std::char_traits<char> > sv = std::basic_string_view<char, std::char_traits<char> >() /* NRVO variable */;
    
  class __lambda_62_27
  {
    public: 
    template<class type_parameter_1_0>
    inline auto operator()(type_parameter_1_0 num) const
    {
      if(t1 == num) {
        const DataType d = DataType{{num.value}};
        sv = TypeInfo<d>();
      } 
      
    }
    
  };
  
  static_for<0, 3>()(__lambda_62_27{});
  return std::basic_string_view<char, std::char_traits<char> >(static_cast<const std::basic_string_view<char, std::char_traits<char> > &&>(sv));
}


/* First instantiated from: insights.cpp:75 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
std::basic_string_view<char, std::char_traits<char> > Typeof<DataType>(DataType t)
{
  int t1 = static_cast<int>(t);
  std::basic_string_view<char, std::char_traits<char> > sv = std::basic_string_view<char, std::char_traits<char> >() /* NRVO variable */;
    
  class __lambda_62_27
  {
    public: 
    template<class type_parameter_0_0>
    inline /*constexpr */ auto operator()(type_parameter_0_0 num) const
    {
      if(t1 == num) {
        const DataType d = DataType{{num.value}};
        sv = TypeInfo<d>();
      } 
      
    }
    
    #ifdef INSIGHTS_USE_TEMPLATE
    template<>
    inline /*constexpr */ void operator()<std::integral_constant<int, 0> >(std::integral_constant<int, 0> num) const
    {
      if(t1 == num.operator std::integral_constant<int, 0>::value_type()) {
        const DataType d = DataType{static_cast<DataType>(num.value)};
        sv.operator=(TypeInfo<d>());
      } 
      
    }
    #endif
    
    
    #ifdef INSIGHTS_USE_TEMPLATE
    template<>
    inline /*constexpr */ void operator()<std::integral_constant<int, 1> >(std::integral_constant<int, 1> num) const
    {
      if(t1 == num.operator std::integral_constant<int, 1>::value_type()) {
        const DataType d = DataType{static_cast<DataType>(num.value)};
        sv.operator=(TypeInfo<d>());
      } 
      
    }
    #endif
    
    
    #ifdef INSIGHTS_USE_TEMPLATE
    template<>
    inline /*constexpr */ void operator()<std::integral_constant<int, 2> >(std::integral_constant<int, 2> num) const
    {
      if(t1 == num.operator std::integral_constant<int, 2>::value_type()) {
        const DataType d = DataType{static_cast<DataType>(num.value)};
        sv.operator=(TypeInfo<d>());
      } 
      
    }
    #endif
    
    private: 
    int & t1;
    std::basic_string_view<char, std::char_traits<char> > & sv;
    
    public:
    __lambda_62_27(int & _t1, std::basic_string_view<char, std::char_traits<char> > & _sv)
    : t1{_t1}
    , sv{_sv}
    {}
    
  } __lambda_62_27{t1, sv};
  
  static_for<0, 3>().operator()(__lambda_62_27);
  return std::basic_string_view<char, std::char_traits<char> >(static_cast<const std::basic_string_view<char, std::char_traits<char> > &&>(sv));
}
#endif


/* First instantiated from: insights.cpp:76 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
std::basic_string_view<char, std::char_traits<char> > Typeof<DType>(DType t)
{
  int t1 = static_cast<int>(t);
  std::basic_string_view<char, std::char_traits<char> > sv = std::basic_string_view<char, std::char_traits<char> >() /* NRVO variable */;
    
  class __lambda_62_27
  {
    public: 
    template<class type_parameter_0_0>
    inline /*constexpr */ auto operator()(type_parameter_0_0 num) const
    {
      if(t1 == num) {
        const DataType d = DataType{{num.value}};
        sv = TypeInfo<d>();
      } 
      
    }
    
    #ifdef INSIGHTS_USE_TEMPLATE
    template<>
    inline /*constexpr */ void operator()<std::integral_constant<int, 0> >(std::integral_constant<int, 0> num) const
    {
      if(t1 == num.operator std::integral_constant<int, 0>::value_type()) {
        const DataType d = DataType{static_cast<DataType>(num.value)};
        sv.operator=(TypeInfo<d>());
      } 
      
    }
    #endif
    
    
    #ifdef INSIGHTS_USE_TEMPLATE
    template<>
    inline /*constexpr */ void operator()<std::integral_constant<int, 1> >(std::integral_constant<int, 1> num) const
    {
      if(t1 == num.operator std::integral_constant<int, 1>::value_type()) {
        const DataType d = DataType{static_cast<DataType>(num.value)};
        sv.operator=(TypeInfo<d>());
      } 
      
    }
    #endif
    
    
    #ifdef INSIGHTS_USE_TEMPLATE
    template<>
    inline /*constexpr */ void operator()<std::integral_constant<int, 2> >(std::integral_constant<int, 2> num) const
    {
      if(t1 == num.operator std::integral_constant<int, 2>::value_type()) {
        const DataType d = DataType{static_cast<DataType>(num.value)};
        sv.operator=(TypeInfo<d>());
      } 
      
    }
    #endif
    
    private: 
    int & t1;
    std::basic_string_view<char, std::char_traits<char> > & sv;
    
    public:
    __lambda_62_27(int & _t1, std::basic_string_view<char, std::char_traits<char> > & _sv)
    : t1{_t1}
    , sv{_sv}
    {}
    
  } __lambda_62_27{t1, sv};
  
  static_for<0, 3>().operator()(__lambda_62_27);
  return std::basic_string_view<char, std::char_traits<char> >(static_cast<const std::basic_string_view<char, std::char_traits<char> > &&>(sv));
}
#endif


void getTypeTest()
{
  std::operator<<(std::cout, Typeof(DataType::HD)).operator<<(std::endl);
  std::operator<<(std::cout, Typeof<DType>(PCI)).operator<<(std::endl);
}


int main()
{
  std::operator<<(std::cout, TypeInfo<DataType::HD>()).operator<<(std::endl);
  getTypeTest();
  return 0;
}
