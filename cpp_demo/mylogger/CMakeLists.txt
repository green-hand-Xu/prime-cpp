cmake_minimum_required(VERSION 3.16.0)
project(mylogger)
set(CMAKE_CXX_STANDARD 17) 
 
#设置可执行文件输出位置
#set(EXECUTABLE_OUTPUT_PATH ./bin)

find_package (Threads REQUIRED)


add_executable(mylogger main.cpp)

target_link_libraries(mylogger pthread)

