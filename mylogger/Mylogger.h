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
 * @brief 简单的日志类实现
 *  日志级别设置为 debug info warning error
 *  通过枚举雷的方式设置日志级别  和 日志输出目标格式
 */

enum log_level{debug, info, warning, error};// 日志等级
enum log_target{file, terminal, file_and_terminal};// 日志输出目标

/**
 * @brief 获取当前时间
 * 使用 time 库的 time_t time (time_t *__timer) 方法 返回类型为 time_t 对象
 * 
 * @return string 
 */
string currTime(){
    // 创建 time_t 类型 变量
    time_t nowtime;
    //创建编译器内置时间结构体
    struct tm* p;
    time(&nowtime);
    p = localtime(&nowtime);
    printf("%02d:%02d:%02d\n",p->tm_hour,p->tm_min,p->tm_sec);

    return "a";
}


#endif