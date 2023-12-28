cmake_minimum_required(VERSION 3.16.0)

project(demo)

set(CMAKE_CXX_STANDARD 20)

find_package (Threads REQUIRED)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
)
message(${CMAKE_CURRENT_SOURCE_DIR})
add_executable(demo main.cpp)


target_link_libraries(demo pthread)