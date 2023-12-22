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

// 定义宏__FUNC__ 表示
#ifdef _WIN64
#define __FUNC__ __FUNCSIG__
#else
#define __FUNC__  __PRETTY_FUNCTION__
#endif

using namespace std;

namespace DynReflection_Space {
void globalfunc(int a,int b){
    cout<<__FUNC__<<endl;
}
} // DynReflection_Space






int main(){
    DynReflection_Space::globalfunc(1,2);

    return 0;
}