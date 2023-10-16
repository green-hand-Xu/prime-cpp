/**
 * @file TestAdd.h
 * @author your name (you@domain.com)
 * @brief 将模板函数（类）的声明与定义写到不同文件中
 *        1、利用 include 宏 实现写在不同文件的方法。注意 被引用的文件 加头文件保护，防止多次引入。
 * @version 0.1
 * @date 2023-10-16
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef __MAIN__
#define __MAIN__

#include <iostream>

template<typename T>
class MATH
{
public:
    MATH(/* args */);
    ~MATH();

    T add(T a, T b);
};

#include "TemplateSeparationDeclaration.hpp"

#endif // __MAIN__