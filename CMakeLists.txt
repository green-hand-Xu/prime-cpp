cmake_minimum_required(VERSION 3.16.0)

project(demo)

set(CMAKE_CXX_STANDARD 14)   
#设置可执行文件输出位置
#set(EXECUTABLE_OUTPUT_PATH ./bin)

find_package (Threads REQUIRED)

# set(${PROJECT_NAME}_COMMON_INCLUDE
#     Object_one/inc
#     Object_two/inc
# 

add_executable(demo Vector.cpp)

target_link_libraries(demo pthread)

