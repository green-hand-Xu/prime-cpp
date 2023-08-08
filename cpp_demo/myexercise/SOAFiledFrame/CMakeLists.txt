cmake_minimum_required(VERSION 3.16.0)

project(demo)

set(CMAKE_CXX_STANDARD 17)   
#设置可执行文件输出位置
#set(EXECUTABLE_OUTPUT_PATH ./bin)

find_package (Threads REQUIRED)

file(GLOB_RECURSE SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/BaseFrame/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ConsumerObj/*.cpp
)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/BaseFrame/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/ConsumerObj/inc
)

add_executable(demo main.cpp ${SRCS})

target_link_libraries(demo pthread)

