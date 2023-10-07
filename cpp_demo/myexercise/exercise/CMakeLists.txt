cmake_minimum_required(VERSION 3.16.0)

project(demo)

option(USEMacro1 "Macro1 宏开关" OFF)

#判断宏开关是否打开 打开则添加宏定义进来
if(USEMacro1)
    add_definitions("-DMacro1") #可以将这一行理解为加入编译命令行的语句 需要-D开头 加 自定义的宏名字
endif(USEMacro1)

message(STATUS "USEMacro1 = " ${USEMacro1})

set(CMAKE_CXX_STANDARD 17)   
#设置可执行文件输出位置
#set(EXECUTABLE_OUTPUT_PATH ./bin)

find_package (Threads REQUIRED)



add_executable(demo default_function.cpp)

target_link_libraries(demo pthread)

