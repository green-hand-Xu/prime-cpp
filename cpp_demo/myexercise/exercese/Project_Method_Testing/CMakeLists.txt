cmake_minimum_required (VERSION 3.16.0)

# set (CMAKE_CXX_FLAGS "-g -std=c++0x")
project(FirstProject)
# vsomeip 库
find_package (vsomeip3 3.3.5 REQUIRED)
# boost 库
find_package( Boost 1.71 COMPONENTS system thread log REQUIRED )
# vsomeip  boost 的头文件目录
include_directories (
    ${Boost_INCLUDE_DIR}
    ${VSOMEIP_INCLUDE_DIRS}
)

add_executable(demo PriorityFramework.cpp)

target_link_libraries(demo vsomeip3 ${Boost_LIBRARIES})
