#ifndef __utils_AAField_HPP__
#define __utils_AAField_HPP__
#include "ValueData.hpp"

/**
 * @brief 此处定义了Field对象，AA程序所有的Field都以此处的类型声明，在服务中
 * 最常用的是AAFieldUint8、AAFieldUint32、AAFieldUint64、AAFieldFloat等。
 * 
 * 因为设计原因，数据需要一个只命名的构造，所以存储的数据类型为string不被支持，AAField对象无法容纳string类型的数据。
 * 
 * Field是变更触发的一种数据。
 * 底层调用update()之后，只有值变更的时候触发后续回调事件。
 * 
 * 此处根据平特特性特殊处理了日志模块支持的类型，可以直接把数据写入日志，而不需要进行value()函数取值。
 * 比如_log.LogInfo() << _fields->CampingModeSrv.CampingModeSts
 * 
 * 实现方法是通过一个中介类（AALogableField），将T和日志取值的类型进行了默认转换。
 */


/**
 * @brief Field类型的数据类，存储数值类型数据。
 * 承载数据存储，可跟踪数据更新、可跟踪数据变化。
 * @note Field类型不会对相同值重复触发数据变更通知。
 * @tparam T 数值类型数据，支持对比运算符（>, <, ==, !=）。
 */
template <typename T>
class AAField : public ValueData<T> {
public:
    using ValueData<T>::ValueData;

    void operator=(const T &v) {
        this->update(v);
    }

protected:
    bool onUpdating(DataValueArgs<T>& arg) override {
        if(!ValueData<T>::onUpdating(arg)) {
            return false;
        }

        if(arg == this->_value) {
            this->invokeOnChangeFail(UpdateFailReason::DuplicateValue, arg);
            return false;
        }

        return true;
    }
};

/**
 * @brief An enum value field for AA apps, will print GWM log when update failed.
 *
 * @tparam T Field value type that support compare operators(>, <, ==) such as int, uint, string etc.
 * @tparam LogType Type for log module, value will be converted to this type before loging.
 * Supported types are: int(8/16/32/64), uint(8/16/32/64), bool, float, double, char, char*, std::string.
 */
template <typename T, typename LogValueType>
class AALogableField : public AAField<T> {
public:
    AALogableField() : AAField<T>() {
        initEvents();
    }

    AALogableField(T value) : AAField<T>(value) {
        initEvents();
    }

    AALogableField(std::string name) : AAField<T>(name){
        initEvents();
    }

    AALogableField(std::string name, T value) : AAField<T>(name, value){
        initEvents();
    }

    AALogableField(std::string name, T min, T max)
        : AAField<T>(name, min, max) {
        initEvents();
    }

    AALogableField(std::string name, T min, T max, T value)
        : AAField<T>(name, min, max, value) {
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
        this->onChangeFail = [this](auto reason, DataValueArgs<T> arg) {
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
class AAFieldChar : public AALogableField<T, char> {
public:
    using AALogableField<T, char>::AALogableField;

    void operator=(const T &v) {
        this->update(v);
    }
};

/**
 * @brief 可自动进行数值范围检查，
 * 拒绝超范围更新，并记录更新失败日志的数据类，数据类型int8_t
 */
template <typename T>
class AAFieldInt8 : public AALogableField<T, std::int8_t> {
public:
    using AALogableField<T, std::int8_t>::AALogableField;

    void operator=(const T &v) {
        this->update(v);
    }
};

/**
 * @brief 可自动进行数值范围检查，
 * 拒绝超范围更新，并记录更新失败日志的数据类，数据类型int16_t
 */
template <typename T>
class AAFieldInt16 : public AALogableField<T, std::int16_t> {
public:
    using AALogableField<T, std::int16_t>::AALogableField;

    void operator=(const T &v) {
        this->update(v);
    }
};

/**
 * @brief 可自动进行数值范围检查，
 * 拒绝超范围更新，并记录更新失败日志的数据类，数据类型int32_t
 */
template <typename T>
class AAFieldInt32 : public AALogableField<T, std::int32_t> {
public:
    using AALogableField<T, std::int32_t>::AALogableField;

    void operator=(const T &v) {
        this->update(v);
    }
};

/**
 * @brief 可自动进行数值范围检查，
 * 拒绝超范围更新，并记录更新失败日志的数据类，数据类型int64_t
 */
template <typename T>
class AAFieldInt64 : public AALogableField<T, std::int64_t> {
public:
    using AALogableField<T, std::int64_t>::AALogableField;

    void operator=(const T &v) {
        this->update(v);
    }
};

/**
 * @brief 可自动进行数值范围检查，
 * 拒绝超范围更新，并记录更新失败日志的数据类，数据类型uint8_t
 */
template <typename T>
class AAFieldUint8 : public AALogableField<T, std::uint8_t> {
public:
    using AALogableField<T, std::uint8_t>::AALogableField;

    void operator=(const T &v) {
        this->update(v);
    }
};

/**
 * @brief 可自动进行数值范围检查，
 * 拒绝超范围更新，并记录更新失败日志的数据类，数据类型uint16_t
 */
template <typename T>
class AAFieldUint16 : public AALogableField<T, std::uint16_t> {
public:
    using AALogableField<T, std::uint16_t>::AALogableField;

    void operator=(const T &v) {
        this->update(v);
    }
};

/**
 * @brief 可自动进行数值范围检查，
 * 拒绝超范围更新，并记录更新失败日志的数据类，数据类型uint32_t
 */
template <typename T>
class AAFieldUint32 : public AALogableField<T, std::uint32_t> {
public:
    using AALogableField<T, std::uint32_t>::AALogableField;

    void operator=(const T &v) {
        this->update(v);
    }
};

/**
 * @brief 可自动进行数值范围检查，
 * 拒绝超范围更新，并记录更新失败日志的数据类，数据类型uint64_t
 */
template <typename T>
class AAFieldUint64 : public AALogableField<T, std::uint64_t> {
public:
    using AALogableField<T, std::uint64_t>::AALogableField;

    void operator=(const T &v) {
        this->update(v);
    }
};

/**
 * @brief 可自动进行数值范围检查，
 * 拒绝超范围更新，并记录更新失败日志的数据类，数据类型float
 */
template <typename T>
class AAFieldFloat : public AALogableField<T, float> {
public:
    using AALogableField<T, float>::AALogableField;

    void operator=(const T &v) {
        this->update(v);
    }
};

/**
 * @brief 可自动进行数值范围检查，
 * 拒绝超范围更新，并记录更新失败日志的数据类，数据类型double
 */
template <typename T>
class AAFieldDouble : public AALogableField<T, double> {
public:
    using AALogableField<T, double>::AALogableField;

    void operator=(const T &v) {
        this->update(v);
    }
};

#endif