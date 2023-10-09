#ifndef __utils_AAStructData_HPP__
#define __utils_AAStructData_HPP__

#include "GA/include/data/BasicData.hpp"

/**
 * @brief
 * 
 * 此处定义了AA服务程序中使用的结构体对象数据存储类。
 * 
 * AA服务中所有结构体数据均以此对象存储。
 */

/**
 * @brief 普通的数据类，存储结构体类型数据。
 * 承载数据存储；可跟踪数据更新、无法跟踪数据变化。
 *
 * @tparam T 数值类型数据，不支持比较运算符的数据类型。
 */
template <typename T>
class AAStructData : public BasicData<T> {
public:
    using BasicData<T>::BasicData;

    void operator=(const T &v) {
        this->update(v);
    }
};


#endif