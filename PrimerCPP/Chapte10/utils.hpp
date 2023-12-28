/**
 * @file utils.hpp
 * @author XuYingBo (you@domain.com)
 * @brief 工具类
 * @version 0.1
 * @date 2023-12-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef __UTILS__
#define __UTILS__

#include <iostream>

#ifdef _WIN64
#define __FUNC__ __FUNCSIG__
#else
#define __FUNC__  __PRETTY_FUNCTION__
#endif

template<typename T>
std::string_view TypeInfo()
{
    std::string type = __FUNC__;
    auto begin = type.find("T = ") + 4;
    auto end = type.find_last_of(';');
    return std::string_view{ type.data() + begin, end - begin };
}

template < typename T>
void my_print(T data){
    auto sv = TypeInfo<T>();
    std::cout<<sv<<" [ ";
    for (auto v : data)
    {
        std::cout<<v<<" ";
    }
    std::cout<<" ]"<<std::endl;
}

#endif // __UTILS__
