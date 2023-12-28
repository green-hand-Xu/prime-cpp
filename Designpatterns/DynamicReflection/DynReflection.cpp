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

enum class DataType{USB,PCI,HD,NOT};
enum  DType{USB,PCI,HD,NOT};
template<auto T>
std::string_view TypeInfo()
{
    std::string type = __FUNC__;
    auto begin = type.find("T = ") + 4;
    auto end = type.find_last_of(';');
    return std::string_view{ type.data() + begin, end - begin };
}

template <int s, int e>
struct static_for
{
    template<typename F>
    void operator()(const F& func) const
    {
        if (s < e)
        {
            //注意：一定要转成常量
            func(std::integral_constant<int,s>());
            static_for<s + 1, e>()(func);
        }
    }
};

template <int n>
struct static_for<n, n>
{
    template<typename F>
    void operator()( const F & func) const
    {
       std::cout << "noting" << std::endl;
    }
};
constexpr int s = static_cast<int>(DataType::USB);
constexpr int e = static_cast<int>(DataType::NOT);

template<typename T>
std::string_view Typeof(T t)
{
    int t1 = static_cast<int>(t);
    std::string_view sv;

    auto fun = [&](auto num) {
        if (t1 == num) {
            //* 重点要理解const和num.value [模板入参必须为常量，因为是编译期展开的]
            const DataType d = DataType{num.value};
            sv = TypeInfo<d>();
            }
        };
    //* 模板展开 编译期生成所有需要的函数 
    static_for<s, e>()(fun);

    return sv;
}

void getTypeTest()
{
    std::cout << Typeof(DataType::HD) << std::endl;
    std::cout << Typeof<DType>(DType::PCI) << std::endl;
}

int main()
{
    std::cout<<TypeInfo<DataType::HD>()<< std::endl;
    getTypeTest();

    return 0;
}