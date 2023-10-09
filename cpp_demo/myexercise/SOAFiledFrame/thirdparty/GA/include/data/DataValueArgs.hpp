#ifndef __Fields_DataValueArgs_HPP__
#define __Fields_DataValueArgs_HPP__

#include <chrono>

using namespace std::chrono;
using namespace std::chrono_literals;

/**
 * @brief 数据变更参数，记录了数据变更相关的数据（包括之前值、当前值、变化触发时间等）。
 * 并提供方法方便地进行时间计算。
 */
template<typename T>
class DataValueArgs
{
public:
    DataValueArgs() {
    }
    
    explicit DataValueArgs(T value) 
        : _value(value)  {
    }

    explicit DataValueArgs(T lastValue, T value) 
        : _lastValue(lastValue),
          _value(value)  {
    }

    explicit DataValueArgs(T lastValue, T value, bool isInitial) 
        : _lastValue(lastValue),
          _value(value),
          _isInitial(isInitial) {
    }

    operator T() const {
        return _value;
    }
    T value() {
        return _value;
    }
    void setValue(const T& value){
        _value = value;
    }

    T lastValue(){
        return _lastValue;
    }
    void setLastValue(const T& lastValue){
        _lastValue = lastValue;
    }

    bool isInitial(){
        return _isInitial;
    }
    void setIsInitial(bool isInitial){
        _isInitial = isInitial;
    }

    operator steady_clock::time_point() const {
        return _receiveTime;
    }
    steady_clock::time_point receiveTime() {
        return _receiveTime;
    }

    duration<double, std::milli> receiveDuration(){
        return duration<double, std::milli>{steady_clock::now() - _receiveTime};
    }

private:
    T _lastValue{};
    T _value{};
    bool _isInitial{false};

    steady_clock::time_point _receiveTime{steady_clock::now()};
};


#endif