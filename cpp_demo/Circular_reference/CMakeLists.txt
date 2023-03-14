cmake_minimum_required(VERSION 3.16.0)

project(demo)

set(CMAKE_CXX_STANDARD 17)

find_package (Threads REQUIRED)

add_executable(demo main.cpp A.cpp B.cpp IController.cpp manager.cpp)

target_link_libraries(demo pthread)