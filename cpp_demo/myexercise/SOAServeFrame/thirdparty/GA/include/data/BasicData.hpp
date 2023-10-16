#ifndef __Fields_BasicData_HPP__
#define __Fields_BasicData_HPP__

#include <atomic>
#include <chrono>
#include <list>

#include "GA/include/Notifier.hpp"
#include "GA/include/Core.hpp"
#include "DataValueArgs.hpp"
#include "AsyncTimer.hpp"

using namespace std::chrono;
using namespace std::chrono_literals;

/**
 * @brief Reason of onChangeFail is invoked, such as value ot of range.
 */
enum UpdateFailReason {
    Unknown = 0x00u,

    OutofLeft,
    OutofRight,
    InvalidValue,
    DuplicateValue,
};

/**
 * @brief A single field which caches value, provides updatings triggers and watches value changing, etc.
 * 
 * @tparam T Data type stored in field.
 */
template <typename T>
class BasicData {
public:
    using FieldValueChangingHandler = std::function<bool(DataValueArgs<T>& arg)>;
    using FieldValueUpdateFailHandler = std::function<void(UpdateFailReason reason, DataValueArgs<T> arg)>;
    using FieldValueValidator = std::function<bool(const DataValueArgs<T>& arg)>;
    using FieldValueHandler = std::function<void(DataValueArgs<T> arg)>;

    BasicData(const BasicData &) = delete;
    BasicData(BasicData &&) = delete;
    BasicData & operator =(const BasicData &) = delete;
    BasicData & operator =(BasicData &&) = delete;

    void operator=(const T &v) {
        update(v);
    }

    operator T() const{
        return _value;
    }

    bool operator == (const std::list<T>& values){
        auto v = this->_value;
        return std::find(values.cbegin(), values.cend(), v) != values.cend();
    }

    bool operator != (const std::list<T>& values){
        auto v = this->_value;
        return std::find(values.cbegin(), values.cend(), v) == values.cend();
    }

    BasicData() : BasicData("", T()) {
    }

    explicit BasicData(T value) : BasicData("", value){
    }

    explicit BasicData(std::string name) : BasicData(name, T()){
    }

    explicit BasicData(std::string name, T value)
      : name(name), 
        _value(value) {
    }

    /**
     * @brief name for this data, may be used in onChangeFail.
     */
    GAProperty<GAString> name{""};

    /**
     * @brief Duration since last update.
     */
    duration<double, std::milli> updateDuration(){
        return duration<double, std::milli>{steady_clock::now() - _updateTime};
    }

    /**
     * @brief 设置为true以异步执行事件通知(onChanged, onChangeFail) ，事件将使用GAThreadPool进行排队执行；
     * 设置为false，以直接在当前线程触发事件通知
     * @note 默认值是Notifier的默认值。
     */
    GAPropertyAdapter<bool> isAsyncInvoke {
        [this](auto v){this->_notifier.isAsync = v;},
        [this]()->bool{return this->_notifier.isAsync;}
    };

    /**
     * @brief 数据变更之前触发的事件，在此事件中可以进行更新前的数据检查、过滤、修改等。
     * 如果拒绝本次更新，return false即可；
     * 如果进行数据修改，那onChanged中以此处修改的值进行通知。
     */
    GAEventAdapterSingle<FieldValueChangingHandler> onChanging{_onChanging};

    /**
     * @brief update() 调用之后，数据不会触发onChanged的话则被认为是ChangeFail。
     * 无法触发onChanged的情况下会触发该事件，事件参数说明了失败原因。
     */
    GAEventAdapterSingle<FieldValueUpdateFailHandler> onChangeFail{_onChangeFail};
    /**
     * @brief 数据产生变更的事件通知。
     */
    GAEventAdapter<Notifier<DataValueArgs<T>>, FieldValueHandler> onChanged{_notifier};

    /**
     * @brief 取值函数，取当前保存的值。
     */
    T value() {
        return _value;
    }

    /**
     * @brief 取值函数，取当前值变化之前的值。
     */
    T lastValue() {
        return _lastValue;
    }

    /**
     * @brief 判定数据仍为初始值，未有变更。
     */
    bool isInitial() {
        return _isInitialValue;
    }

    /**
     * 进行数据更新。
     * @note 如果有变更前数据检查规则，则会首先进行规则检查。
     */
    void update(T value) {
        auto now = steady_clock::now();
        
        DataValueArgs<T> args{_value ,value, _isInitialValue};
        if(_isInitialValue){
            // 如果是第一次更新，我们不提供lastValue
            args.setLastValue(value);
        }

        if(!onUpdating(args)){
            return;
        }

        if(_onChanging && !_onChanging(args)){
            return;
        }
        
        _updateTime = now;

        if(_isInitialValue){
            _isInitialValue = false;
        }else{
            _lastValue = _value;
        }
  
        _value = value;
        _notifier.invoke(args);
    }

    /**
     * 监控值变化，满足validator的时候将执行给定的handler。
     */
    inline void watch(FieldValueValidator validator, FieldValueHandler handler){
        _notifier.watch(validator, handler);
    }

    /**
     * 监控值变化，当满足validator，并且保持一定时间之后触发给定的handler；
     * @note 会持续监控值变更，在计时时间内，有其他不满足的值更新将打断计时。
     */
    template<typename _Rep, typename _Period>
    void stay(FieldValueValidator validator, const duration<_Rep, _Period>& duration, FieldValueHandler handler){
        if(!validator || !handler){
            return;
        }

        this->onChanged += [this, validator, duration, handler](auto arg){
            // try lock, will this work well?
            auto id = _stayHandlerIndex.load();

            //remove timers with invalid validator.
            _stayHandlers.remove_if([this, arg](const StayHandler& h)->bool{
                return !h.validator || !h.validator(arg);
            });

            // Add timer for this validator
            if(!validator(arg)){
                return;
            }
            
            ++_stayHandlerIndex;
            id = _stayHandlerIndex.load();
            auto timer = std::make_shared<AsyncTimer>();

            StayHandler h{id, validator, handler, timer};
            _stayHandlers.emplace_back(h);

            timer->run(duration, [this, id, validator, handler, arg](){
                // dboule check...
                if(!validator(arg)){
                    return;
                }
                handler(arg);
                auto lock = this->_stayHandlerIndex.load();
                // clear timer.
                _stayHandlers.remove_if([lock, id](const StayHandler& h)->bool{                
                    // Hi, compiler, please keep this line.
                    if(lock == id){
                        return h.id == lock;
                    }
                    return h.id == id;
                });
            });
        };
    }

    /**
     * 监控值变化，如果存储的是值类型，
     * 且值等于给定value的时候将执行给定的handler。
     * @note 仅值类型存储可用，结构体无法进行直接比较。
     */
    void equals(const T& value, FieldValueHandler handler) noexcept {
        this->_notifier.watch([value](auto arg){
            return arg == value;
        }, handler);
    }

    /**
     * 监控值变化，如果存储的是值类型，
     * 且值等于给定value，且保持给定时间之后，将执行给定的handler。
     * @note 仅值类型存储可用，结构体无法进行直接比较。
     */
    template<typename _Rep, typename _Period>
    void equals(const T& value, const duration<_Rep, _Period>& duration, FieldValueHandler handler) noexcept {
        this->stay([value](auto arg){
            return arg == value;
        }, duration, handler);
    }

    /**
     * 监控值变化，如果存储的是值类型，
     * 且值从lastValue变为value的时候将执行给定的handler。
     * @note 仅值类型存储可用，结构体无法进行直接比较。
     */
    void equals(const T& lastValue, const T& value, FieldValueHandler handler) noexcept {
        this->_notifier.watch([lastValue, value](auto arg){
            return arg.lastValue() == lastValue && arg == value;
        }, handler);
    }

    /**
     * 监控值变化，如果存储的是值类型，
     * 且值从lastValue变为value，且保持给定时间之后，将执行给定的handler。
     * @note 仅值类型存储可用，结构体无法进行直接比较。
     */
    template<typename _Rep, typename _Period>
    void equals(const T& lastValue, const T& value, const duration<_Rep, _Period>& duration, FieldValueHandler handler) noexcept {
        this->stay([lastValue, value](auto arg){
            return arg.lastValue() == lastValue && arg == value;
        }, duration, handler);
    }

    /**
     * 监控值变化，如果存储的是值类型，
     * 且值等于给定values其中之一的时候将执行给定的handler。
     * @note 仅值类型存储可用，结构体无法进行直接比较。
     */
    void equals(std::list<T> values, FieldValueHandler handler) noexcept {
        this->_notifier.watch([values](auto arg){
            return std::find(values.cbegin(), values.cend(), arg.value()) != values.cend();
        }, handler);
    }

    /**
     * 监控值变化，如果存储的是值类型，
     * 且值等于给定values之一时，且保持给定时间之后，将执行给定的handler。
     * @note 仅值类型存储可用，结构体无法进行直接比较。
     */
    template<typename _Rep, typename _Period>
    void equals(std::list<T> values, const duration<_Rep, _Period>& duration, FieldValueHandler handler) noexcept {
        this->stay([values](auto arg){
            return std::find(values.cbegin(), values.cend(), arg.value()) != values.cend();
        }, duration, handler);
    }

    /**
     * 监控值变化，如果存储的是值类型，
     * 且值从lastValues之一变为value之一的时候，将执行给定的handler。
     * @note 仅值类型存储可用，结构体无法进行直接比较。
     */
    void equals(std::list<T> lastValues, std::list<T> values, FieldValueHandler handler) noexcept {
        this->_notifier.watch([lastValues, values](auto arg){
            return std::find(lastValues.cbegin(), lastValues.cend(), arg.lastValue()) != lastValues.cend()
                && std::find(values.cbegin(), values.cend(), arg.value()) != values.cend();
        }, handler);
    }

    /**
     * 监控值变化，如果存储的是值类型，
     * 且值从lastValues之一变为value之一，且保持给定时间之后，将执行给定的handler。
     * @note 仅值类型存储可用，结构体无法进行直接比较。
     */
    template<typename _Rep, typename _Period>
    void equals(std::list<T> lastValues, std::list<T> values, const duration<_Rep, _Period>& duration, FieldValueHandler handler) noexcept {
        this->stay([lastValues, values](auto arg){
            return std::find(lastValues.cbegin(), lastValues.cend(), arg.lastValue()) != lastValues.cend()
                && std::find(values.cbegin(), values.cend(), arg.value()) != values.cend();
        }, duration, handler);
    }

    /**
     * 监控值变化，如果存储的是值类型，
     * 且值不等于给定value的时候将执行给定的handler。
     * @note 仅值类型存储可用，结构体无法进行直接比较。
     * @note 不等于相对于等于来说可能是一个更大的范围，所以可能会经常被触发。
     */
    void notEquals(const T& value, FieldValueHandler handler) noexcept {
        this->_notifier.watch([value](auto arg){
            return arg != value;
        }, handler);
    }

    /**
     * 监控值变化，如果存储的是值类型，
     * 且值不等于给定value，且保持给定时间之后，将执行给定的handler。
     * @note 仅值类型存储可用，结构体无法进行直接比较。
     * @note 不等于相对于等于来说可能是一个更大的范围，所以可能会经常被触发。
     */
    template<typename _Rep, typename _Period>
    void notEquals(const T& value, const duration<_Rep, _Period>& duration, FieldValueHandler handler) noexcept {
        this->_notifier.watch([value](auto arg){return arg != value; }, duration, handler);
    }

    /**
     * 监控值变化，如果存储的是值类型，
     * 且值不等于给定values的其中任何一项的时候将执行给定的handler。
     * @note 仅值类型存储可用，结构体无法进行直接比较。
     * @note 不等于相对于等于来说可能是一个更大的范围，所以可能会经常被触发。
     */
    void notEquals(std::list<T> values, FieldValueHandler handler) noexcept {
        this->_notifier.watch([values](auto arg){
            return std::find(values.cbegin(), values.cend(), arg.value()) == values.cend();
        }, handler);
    }

    /**
     * 监控值变化，如果存储的是值类型，
     * 且值不等于给定values的其中任何一项，且保持给定时间之后，将执行给定的handler。
     * @note 仅值类型存储可用，结构体无法进行直接比较。
     * @note 不等于相对于等于来说可能是一个更大的范围，所以可能会经常被触发。
     */
    template<typename _Rep, typename _Period>
    void notEquals(std::list<T> values, const duration<_Rep, _Period>& duration, FieldValueHandler handler) noexcept {
        this->stay([values](auto arg){
            return std::find(values.cbegin(), values.cend(), arg.value()) == values.cend();
        }, duration, handler);
    }

    /**
     * 监控值变化，如果存储的是值类型，
     * 且值大于给定value的时候将执行给定的handler。
     * @note 仅值类型存储可用，结构体无法进行直接比较。
     * @note 大于相对于等于来说可能是一个更大的范围，所以可能会经常被触发。
     */
    void greaterThan(const T& value, FieldValueHandler handler) noexcept {
        this->_notifier.watch([value](auto arg){return arg > value;}, handler);
    }

    /**
     * 监控值变化，如果存储的是值类型，
     * 且值大于给定value，且保持给定时间之后，将执行给定的handler。
     * @note 仅值类型存储可用，结构体无法进行直接比较。
     * @note 大于相对于等于来说可能是一个更大的范围，所以可能会经常被触发。
     */
    template<typename _Rep, typename _Period>
    void greaterThan(const T& value, const duration<_Rep, _Period>& duration, FieldValueHandler handler) noexcept {
        this->stay([value](auto arg){return arg > value;}, duration, handler);
    }

    /**
     * 监控值变化，如果存储的是值类型，
     * 且值小于给定value的时候将执行给定的handler。
     * @note 仅值类型存储可用，结构体无法进行直接比较。
     * @note 小于相对于等于来说可能是一个更大的范围，所以可能会经常被触发。
     */
    void lessThan(const T& value, FieldValueHandler handler) noexcept {
        this->_notifier.watch([value](auto arg){return arg < value;}, handler);
    }

    /**
     * 监控值变化，如果存储的是值类型，
     * 且值小于给定value，且保持给定时间之后，将执行给定的handler。
     * @note 仅值类型存储可用，结构体无法进行直接比较。
     * @note 小于相对于等于来说可能是一个更大的范围，所以可能会经常被触发。
     */
    template<typename _Rep, typename _Period>
    void lessThan(const T& value, const duration<_Rep, _Period>& duration, FieldValueHandler handler) noexcept {
        this->stay([value](auto arg){return arg < value;}, duration, handler);
    }

    /**
     * 监控值变化，如果存储的是值类型，
     * 且值大于value1，并且小于value1的时候将执行给定的handler。
     * @note 仅值类型存储可用，结构体无法进行直接比较。
     * @note 范围值判断相对于等于来说可能是一个更大的范围，所以可能会经常被触发。
     */
    void between(const T& value1, const T& value2, FieldValueHandler handler) noexcept {
        T min = value1, max = value2;
        if (value2 < value1) {
            min = value2;
            max = value1;
        }
        this->_notifier.watch([min, max](auto arg) {return min < arg && arg < max;}, handler);
    }
    /**
     * 监控值变化，如果存储的是值类型，
     * 且值大于value1，并且小于value1，且保持给定时间之后，将执行给定的handler。
     * @note 仅值类型存储可用，结构体无法进行直接比较。
     * @note 范围值判断相对于等于来说可能是一个更大的范围，所以可能会经常被触发。
     */
    template<typename _Rep, typename _Period>
    void between(const T& value1, const T& value2, const duration<_Rep, _Period>& duration, FieldValueHandler handler) noexcept {
        T min = value1, max = value2;
        if (value2 < value1) {
            min = value2;
            max = value1;
        }
        this->stay([min, max](auto arg) {return min < arg && arg < max;}, duration, handler);
    }

protected:
    FieldValueChangingHandler _onChanging{nullptr};
    FieldValueUpdateFailHandler _onChangeFail{nullptr};

    inline void invokeOnChangeFail(UpdateFailReason reason, DataValueArgs<T> arg){
        if(!_onChangeFail){
            return;
        }
        if(this->_notifier.isAsync){
            async([this, reason, arg](){_onChangeFail(reason, arg);});
        }else{
            _onChangeFail(reason, arg);
        }
    }

    /**
     * @brief Internal logic, will be invoked before updating.
     * 
     * @param arg 
     * @return true : New value will be accepted.
     * @return false : New value will be rejected, no future onChanged event.
     */
    virtual bool onUpdating(DataValueArgs<T>& arg){
        return true;
    }

protected:
    bool _isInitialValue{true};
    T _lastValue, _value;
    steady_clock::time_point _updateTime{steady_clock::time_point::min()};

    Notifier<DataValueArgs<T>> _notifier;

    // Unique id for stay() handlers, 
    // and also unique lock for all handlers.
    std::atomic_ulong _stayHandlerIndex{0};

    // Container that keep all actived handlers.
    struct StayHandler
    {
        unsigned long id;
        FieldValueValidator validator;
        FieldValueHandler handler;
        std::shared_ptr<AsyncTimer> timer{nullptr};

        StayHandler(unsigned long id, FieldValueValidator validator, 
                    FieldValueHandler handler, std::shared_ptr<AsyncTimer> timer)
            : id(id),
              validator(validator),
              handler(handler),
              timer(timer) {
        }
    };

    std::list<StayHandler> _stayHandlers;
};

#endif