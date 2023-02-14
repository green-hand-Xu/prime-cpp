#ifndef MYLOGGER
#define MYLOGGER
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

using std::cout;
using std::string;
using std::endl;
using std::to_string;
using std::ios;

//** 声明一个指针对象 并不是直接声明了 这个指针类型的一个对象，此时这个指针为空

/**
 *  @brief 简单的日志类实现
 *  日志级别设置为 debug info warning error
 *  通过枚举雷的方式设置日志级别  和 日志输出目标格式
 */

enum log_level{debug, info, warning, error};// 日志等级
enum log_target{file, terminal, file_and_terminal};// 日志输出目标

/**
 * @brief 获取当前时间
 * 使用 time 库的 time_t time (time_t *__timer) 方法 返回类型为 time_t 对象 并赋值给传入的对象。
 * 
 * @return string 
 */
string currTime(){
    // 创建 time_t 类型 变量 实际类型为 long int
    time_t nowtime;
    //创建编译器内置时间结构体
    struct tm* p;
    string t ;
    time(&nowtime); //*获取当前时间，并保存到 nowtime 中
    auto a = time(NULL);

    //* localtime( time_t 对象指针 )返回“struct tm”表示 *TIMER的本地时区
    //* 该结构体可用于输出关于日期时间的相关属性值，但是为int类型 不适合当作字符串输出
    p = localtime(&nowtime); 

    char tmp[256];
    //* strftime(目标字符串，最多传出字符数量 ，格式化方式 ，tm 结构体指针 ) 
    //* 可以将格式化后的时间格式字符串 写到目标char数组中
    //* 第四个参数为 tm 结构体指针对象， 可用 localtime（）方法 返回此对象
    //* 适合返回字符串进行打印。
    //* 常用格式化方式 ：%a 星期几的简写 %A 星期几的全称 %b 月份的简写 %B 月份的全称
    //* %F 年-月-日 %T 时-分-秒    %Y 年   % m 月 %d 日  %H 时 %M 分 %S 妙
    strftime(tmp,sizeof(tmp),"%F %T",localtime(&nowtime));

    cout<<"a"<<a<<endl;

    return tmp;
}


#endif
