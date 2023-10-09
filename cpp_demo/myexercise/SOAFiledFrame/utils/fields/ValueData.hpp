#ifndef __utils_ValueData_HPP__
#define __utils_ValueData_HPP__

#include "GA/include/data/BasicData.hpp"

/**
 * @brief 此处定义了业务系统中（也就是AA程序中）使用的所有值类型数据。
 * 
 * AA服务中所有的Event、Field、内部变量的值类型以此为基础进行扩展。
 * 
 * 因为BasicData基类不基于类型，所以实现为具体类型的时候将通过可复用的ValueData进行实现。
 * ValueData不依赖于任何业务系统，不根据AA代码进行特殊化。
 */


/**
 * @brief 值类型数据对象，处理值类型数据及相关能力，
 *        支持最小值、最大值设定；更新前校验最小值、最大值。
 */
template <typename T>
class ValueData : public BasicData<T>{
protected:
    ValueData(const ValueData &) = delete;
    ValueData(ValueData &&) = delete;
    ValueData & operator =(const ValueData &) = delete;
    ValueData & operator =(ValueData &&) = delete;

public:
    using BasicData<T>::BasicData;

    explicit ValueData(std::string name, T min, T max)
      : ValueData(name, min, max, T()) {
    }

    explicit ValueData(std::string name, T min, T max, T value)
      : BasicData<T>(name, value) {
        setMinValue(min);
        setMaxValue(max);
    }

    void operator=(const T &v) {
      this->update(v);
    }

    void setMinValue(const T& min){
        _min = min;
        _isMinSet = true;
    }

    void setMaxValue(const T& max){
        _max = max;
        _isMaxSet = true;
    }

    void setRange(const T& min, const T& max){
        _min = min;
        _max = max;

        _isMinSet = true;
        _isMaxSet = true;
    }

protected:
    bool _isMinSet{false};
    bool _isMaxSet{false};
    T _min, _max;

    bool onUpdating(DataValueArgs<T>& arg) override{
        if(this->_isInitialValue){
            return true;
        }

        if(_isMinSet && arg < _min){
            this->invokeOnChangeFail(UpdateFailReason::OutofLeft, arg);
            return false;
        }
        if(_isMaxSet && arg > _max){
            this->invokeOnChangeFail(UpdateFailReason::OutofRight, arg);
            return false;
        }

        return true;
    }
};

#endif
