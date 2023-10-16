 
#ifndef __utils_AAFieldsDefine_HPP__
#define __utils_AAFieldsDefine_HPP__

#include "fields/AAEvent.hpp"
#include "fields/AAField.hpp"
#include "fields/AAStructField.hpp"

/**
 * @brief 这里是所有数据定义的入口，引用了所有需要的数据类型定义。
 * 
 * 如果你需要使用AAEvent、AAField，那么你需要引用的仅是这个头文件。
 * 
 * 这里定义了一些精简的名字，如果你喜欢可以尝试自己添加一些不影响代码的精简定义。
 * 比如你可以将String定义为你需要的类型，这样在以后系统变更的过程中，将避免影响业务代码。
 */

using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;

using i8 = std::int8_t;
using i16 = std::int16_t;
using i32 = std::int32_t;
using i64 = std::int64_t;


#endif