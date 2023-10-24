cmake_minimum_required(VERSION 3.16.0)

project(demo)

set(CMAKE_CXX_STANDARD 17)   
#设置可执行文件输出位置
#set(EXECUTABLE_OUTPUT_PATH ./bin)

file(GLOB SRCS
  ${CMAKE_CURRENT_SOURCE_DIR}/*.c
  ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)
message(STATUS ${SRCS})

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
)


find_package (Threads REQUIRED)

add_executable(demo main.cpp )
# target_link_directories(
#     ${PROJECT_NAME}
#     PUBLIC ${include_directories}
# )
target_link_libraries(
    ${PROJECT_NAME}
    pthread
    libpthread.a
)

