# Cmake 版本要求
cmake_minimum_required(VERSION 3.10)

# 工程名字
project(MARS)

# 定义一些变量用于表示带版本号的工具名字和兼容性的名字（不带版本号）
set (MARS_NAME mars1)
set (MARS_COMPAT_NAME mars)

# 定义短版本号变量
set (MARS_MAJOR_VERSION 1)
set (MARS_MINOR_VERSION 1)
set (MARS_PATCH_VERSION 0)
set (MARS_HOTFIX_VERSION 0)

# 定义长版本号变量
set (MARS_VERSION ${MARS_MAJOR_VERSION}.${MARS_MINOR_VERSION}.${MARS_PATCH_VERSION})
# message(STATUS "MARS_VERSION = ${MARS_MAJOR_VERSION}.${MARS_MINOR_VERSION}.${MARS_PATCH_VERSION}")

# cmake 与 doxygen的关系 有待查阅
set (PACKAGE_VERSION ${MARS_VERSION}) # Used in documentation/doxygen.in

# 不启用 Makefile 生成的详细输出  此变量是由 project（） 命令初始化（为 FALSE）的缓存条目。
set (CMAKE_VERBOSE_MAKEFILE off)

# 为用户提供覆盖安装目录的选择 所以需要设置为缓存变量
set (INSTALL_LIB_DIR lib CACHE PATH "Installation directory for libraries")
set (INSTALL_BIN_DIR bin CACHE PATH "Installation directory for executables")
set (INSTALL_INCLUDE_DIR include CACHE PATH "Installation directory for header files")
# message(STATUS "INSTALL_LIB_DIR = ${INSTALL_LIB_DIR}")
# message(STATUS "INSTALL_BIN_DIR = ${INSTALL_BIN_DIR}")
# message(STATUS "INSTALL_INCLUDE_DIR = ${INSTALL_INCLUDE_DIR}")

# 预定义cmake安装路径变量。 提供 windows 和 linux 两种风格的cmake文件安装路径
if (WIN32 AND NOT CYGWIN)
    set (DEF_INSTALL_CMAKE_DIR CMake)
else ()
    set (DEF_INSTALL_CMAKE_DIR lib/cmake/${MARS_NAME})
endif ()

# 定义cmake安装路径变量。 使用上一步判断出来的结果进行设置
set (INSTALL_CMAKE_DIR ${DEF_INSTALL_CMAKE_DIR} CACHE PATH "Installation directory for CMake files")
# message(STATUS "INSTALL_CMAKE_DIR = ${INSTALL_CMAKE_DIR}")

# 定义绝对路径变量并赋值。利用相对路径和循环+字符拼接的形式完成了该功能 CMAKE_INSTALL_PREFIX : 此变量在 UNIX 上默认为 /usr/local
foreach (p LIB BIN INCLUDE CMAKE)
    set (var INSTALL_${p}_DIR) # 定义 路径的变量名
    if (NOT IS_ABSOLUTE "${${var}}")
        # 定义绝对路径的变量名 并赋值  ${${var}} 对var进行了两次展开，最终结果是对应的 INSTALL_${p}_DIR 变量的值
        set (ABSOLUTE_${var} "${CMAKE_INSTALL_PREFIX}/${${var}}") # Add all targets to the build-tree export set
    endif ()
endforeach ()

# message(STATUS "ABSOLUTE_INSTALL_LIB_DIR = ${ABSOLUTE_INSTALL_LIB_DIR}")
# message(STATUS "ABSOLUTE_INSTALL_LIB_DIR = ${ABSOLUTE_INSTALL_BIN_DIR}")
# message(STATUS "ABSOLUTE_INSTALL_LIB_DIR = ${ABSOLUTE_INSTALL_INCLUDE_DIR}")

