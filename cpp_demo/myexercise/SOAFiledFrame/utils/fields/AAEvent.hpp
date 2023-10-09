#ifndef __utils_AAEvent_HPP__
#define __utils_AAEvent_HPP__

#include "ValueData.hpp"

/**
 * @brief 此处定义了Event对象，AA程序所有的Event都以此处的类型声明，在服务中
 * 最常用的是AAEventUint8、AAEventUint32、AAEventUint64、AAEventFloat等。
 * 
 * Event是稳定触发的一种数据，
 * 只要底层调用update()更新数据，无论值是否变化，都会触发后续回调。
 * 
 * 因为设计原因，数据需要一个只命名的构造，所以存储的数据类型为string不被支持，AAEvent对象无法容纳string类型的数据。
 * 
 * 此处根据平特特性特殊处理了日志模块支持的类型，可以直接把数据写入日志，而不需要进行value()函数取值。
 * 比如_log.LogInfo() << _fields->CampingModeSrv.CampingModeSts
 * 
 * 实现方法是通过一个中介类（AALogableEvent），将T和日志取值的类型进行了默认转换。
 */

/**
 * @brief Event类型的数据类，存储数值类型数据。
 * 承载数据存储，可跟踪数据更新、可跟踪数据变化。
 * @note Event类型支持相同值重复触发数据变更通知。
 * @tparam T 数值类型数据，支持对比运算符（>, <, ==, !=）。
 */
template <typename T>
class AAEvent : public ValueData<T> {
public:
    using ValueData<T>::ValueData;

    void operator=(const T &v) {
        this->update(v);
    }
};


/**
 * @brief 可记录日志的Event对象，Event对象可针对重复值多次更新。
 */
template <typename T, typename LogValueType>
class AALogableEvent : public AAEvent<T> {
public:
    AALogableEvent() : AAEvent<T>() {
        initEvents();
    }

    AALogableEvent(T value) : AAEvent<T>(value) {
        initEvents();
    }

    AALogableEvent(std::string name) : AAEvent<T>(name) {
        initEvents();
    }

    AALogableEvent(std::string name, T value) : AAEvent<T>(name, value) {
        initEvents();
    }

    AALogableEvent(std::string name, T min, T max)
        : AAEvent<T>(name, min, max){
        initEvents();
    }

    AALogableEvent(std::string name, T min, T max, T value)
        : AAEvent<T>(name, min, max, value){
        initEvents();
    }

    void operator=(const T &v) {
        this->update(v);
    }

    operator LogValueType() const {
        return static_cast<LogValueType>(this->_value);
    }

private:
    void initEvents() {
        this->onChangeFail = [this](auto reason, auto arg) {
            // if(reason == UpdateFailReason::OutofLeft) {
            //     _log.LogWarn() << "Field (name = " << this->name
            //                    << ") updata failed, value is too little, value = " << static_cast<LogValueType>(arg.value())
            //                    << ", min value = " << static_cast<LogValueType>(this->_min) << ".";
            // } else if(reason == UpdateFailReason::OutofRight) {
            //     _log.LogWarn() << "Field (name = " << this->name
            //                    << ") updata failed, value is too large, value = " << static_cast<LogValueType>(arg.value())
            //                    << ", max value = " << static_cast<LogValueType>(this->_max) << ".";
            // } else if(reason != UpdateFailReason::DuplicateValue) {
            //     _log.LogWarn() << "Field (name = " << this->name << ") updata failed, error code = " << reason;
            // }
        };
    }

private:
    // GWM::Platform::Log::LogMessage _log;
};

/**
 * @brief 可自动进行数值范围检查，
 * 拒绝超范围更新，并记录更新失败日志的数据类，数据类型char
 */
template <typename T>
class AAEventChar : public AALogableEvent<T, char> {
public:
    using AALogableEvent<T, char>::AALogableEvent;

    void operator=(const T &v) {
        this->update(v);
    }
};

/**
 * @brief 可自动进行数值范围检查，
 * 拒绝超范围更新，并记录更新失败日志的数据类，数据类型int8_t
 */
template <typename T>
class AAEventInt8 : public AALogableEvent<T, std::int8_t> {
public:
    using AALogableEvent<T, std::int8_t>::AALogableEvent;

    void operator=(const T &v) {
        this->update(v);
    }
};

/**
 * @brief 可自动进行数值范围检查，
 * 拒绝超范围更新，并记录更新失败日志的数据类，数据类型int16_t
 */
template <typename T>
class AAEventInt16 : public AALogableEvent<T, std::int16_t> {
public:
    using AALogableEvent<T, std::int16_t>::AALogableEvent;

    void operator=(const T &v) {
        this->update(v);
    }
};

/**
 * @brief 可自动进行数值范围检查，
 * 拒绝超范围更新，并记录更新失败日志的数据类，数据类型int32_t
 */
template <typename T>
class AAEventInt32 : public AALogableEvent<T, std::int32_t> {
public:
    using AALogableEvent<T, std::int32_t>::AALogableEvent;

    void operator=(const T &v) {
        this->update(v);
    }
};

/**
 * @brief 可自动进行数值范围检查，
 * 拒绝超范围更新，并记录更新失败日志的数据类，数据类型int64_t
 */
template <typename T>
class AAEventInt64 : public AALogableEvent<T, std::int64_t> {
public:
    using AALogableEvent<T, std::int64_t>::AALogableEvent;

    void operator=(const T &v) {
        this->update(v);
    }
};

/**
 * @brief 可自动进行数值范围检查，
 * 拒绝超范围更新，并记录更新失败日志的数据类，数据类型uint8_t
 */
template <typename T>
class AAEventUint8 : public AALogableEvent<T, std::uint8_t> {
public:
    using AALogableEvent<T, std::uint8_t>::AALogableEvent;

    void operator=(const T &v) {
        this->update(v);
    }
};

/**
 * @brief 可自动进行数值范围检查，
 * 拒绝超范围更新，并记录更新失败日志的数据类，数据类型uint16_t
 */
template <typename T>
class AAEventUint16 : public AALogableEvent<T, std::uint16_t> {
public:
    using AALogableEvent<T, std::uint16_t>::AALogableEvent;

    void operator=(const T &v) {
        this->update(v);
    }
};

/**
 * @brief 可自动进行数值范围检查，
 * 拒绝超范围更新，并记录更新失败日志的数据类，数据类型uint32_t
 */
template <typename T>
class AAEventUint32 : public AALogableEvent<T, std::uint32_t> {
public:
    using AALogableEvent<T, std::uint32_t>::AALogableEvent;

    void operator=(const T &v) {
        this->update(v);
    }
};

/**
 * @brief 可自动进行数值范围检查，
 * 拒绝超范围更新，并记录更新失败日志的数据类，数据类型uint64_t
 */
template <typename T>
class AAEventUint64 : public AALogableEvent<T, std::uint64_t> {
public:
    using AALogableEvent<T, std::uint64_t>::AALogableEvent;

    void operator=(const T &v) {
        this->update(v);
    }
};

/**
 * @brief 可自动进行数值范围检查，
 * 拒绝超范围更新，并记录更新失败日志的数据类，数据类型float
 */
template <typename T>
class AAEventFloat : public AALogableEvent<T, float> {
public:
    using AALogableEvent<T, float>::AALogableEvent;

    void operator=(const T &v) {
        this->update(v);
    }
};

/**
 * @brief 可自动进行数值范围检查，
 * 拒绝超范围更新，并记录更新失败日志的数据类，数据类型double
 */
template <typename T>
class AAEventDouble : public AALogableEvent<T, double> {
public:
    using AALogableEvent<T, double>::AALogableEvent;

    void operator=(const T &v) {
        this->update(v);
    }
};

#endif