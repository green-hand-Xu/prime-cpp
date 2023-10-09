#ifndef __GA_Core_HPP__
#define __GA_Core_HPP__

#include <string>
#include <functional>

/**
 * @brief 这里定义了一些基础的工具对象，
 * 比如：属性、只读属性的声明；
 * 属性、事件和对象关联的实现，方便地把属性和事件关联到特定对象和方法上。
 * 
 * 属性的关联目前没有任何有实际意义的作用，仅仅是封装了读写，
 * 如果属性变更将来作为事件的话，那么这里的属性声明将更加方便，目前仅仅是对于直接声明的一个替换。
 * 
 * 事件的关联目前主要是实现了+=的运算符重载。
 */

/**
 * @brief All basic value type, basic structs.
 */

/**
 * @brief string type used by GA.
 * 
 */
using GAString = std::string;

/**
 * @brief A property.
 * 
 * @tparam T 
 */
template <typename T>
class GAProperty{
protected:
    GAProperty(const GAProperty &) = delete;
    GAProperty(GAProperty &&) = delete;
    GAProperty & operator =(const GAProperty &) = delete;
    GAProperty & operator =(GAProperty &&) = delete;

public:
    GAProperty():GAProperty(T()){

    }

    explicit GAProperty(const T& value)
      : _value(value){

    }

    operator T() const{
        return _value;
    }
    void operator=(const T& value) {
        set(value);
    }

    const T& get(){
        return _value;
    }
    void set(const T& value){
        _value = value;
    }

protected:
    T _value;
};

template <typename T>
class GAReadonlyPropertyWrapper
{
public:
    GAReadonlyPropertyWrapper(T& value){
        _value = value;
    }

    operator T() const{
        return _value;
    }

    const T& get(){
      return _value;
    }

protected:
    T& _value;
};

template <typename T>
class GAPropertyWrapper : public GAReadonlyPropertyWrapper<T>
{
public:
    using GAReadonlyPropertyWrapper<T>::GAReadonlyPropertyWrapper;

    void operator=(const T& value) {
        set(value);
    }

    void set(const T& value){
        this->_value = value;
    }
};


/**
 * @brief A readonly property adapter to get method, 
 *        uset get() to get value.
 * 
 * @tparam T type of the property.
 */
template <typename T>
class GAReadonlyPropertyAdapter{
    using ValueReadHandler = std::function<const T&()>;
  
public:
    explicit GAReadonlyPropertyAdapter(ValueReadHandler getter)
        : _getter(getter){
    }

    const T& get(){
        return _getter ? _getter() : T();
    }

    operator T() const {
        return get();
    }

protected:
    ValueReadHandler _getter;
};

/**
 * @brief A property adapter to get/set method, 
 *        use operator '=' to update it,
 *        uset get() to get value, use set() update value.
 * 
 * @tparam T type of the property.
 */
template <typename T>
class GAPropertyAdapter{
public:
    using ValueSetHandler = std::function<void(const T&)>;
    using ValueReadHandler = std::function<const T&()>;
  
public:
    explicit GAPropertyAdapter(ValueSetHandler setter, ValueReadHandler getter)
      : _setter(setter),
        _getter(getter){
    }

    void operator=(const T& value) {
        set(value);
    }

    const T& get(){
        return _getter ? _getter() : T();
    }

    operator T() const {
        return get();
    }

    void set(const T& value){
        if(_setter){
            _setter(value);
        }
    }

protected:
    ValueSetHandler _setter{nullptr};
    ValueReadHandler _getter{nullptr};
};

/**
 * @brief A single event, use operator '=' to set handler.
 * 
 * @tparam HandlerType 
 */
template <typename HandlerType>
class GAEventAdapterSingle{
public:
    explicit GAEventAdapterSingle(HandlerType& handler)
    : _handler(handler){
      
    }

    void operator=(const HandlerType& handler) {
        _handler = handler;
    }

private:
    HandlerType& _handler;
};

/**
 * @brief An event, use operator '+=' to append handler,
 *        use operator '-=' to remove handler. 
 * 
 * @tparam HandlerType Handler type of this event.
 */
template <typename TargetType, typename HandlerType>
class GAEventAdapter {
public:
    explicit GAEventAdapter(TargetType& target) 
        : _target(target) {
    }

    void operator+=(const HandlerType& handler) {
        _target += handler;
    }
    
    void operator-=(const HandlerType& handler) {
        _target -= handler;
    }

private:
    TargetType& _target;
};

/**
 * 实现Event和+=运算符关联方法的实现，用于私有成员构造的Event对外暴露的场景。
 * 比如+=对内部list的push。
 */
template<typename HandlerType>
class GAEventWrapper{
public:
    explicit GAEventWrapper(std::function<void(HandlerType)> bindFunc) 
        : GAEventWrapper(bindFunc, nullptr) {
    }
    explicit GAEventWrapper(std::function<void(HandlerType)> bindFunc, std::function<void(HandlerType)> unbindFunc) 
        : _bindFunc(bindFunc),
          _unbindFunc(unbindFunc) {
    }

    void operator+=(const HandlerType& handler) {
        if(_unbindFunc){
            _unbindFunc(handler);
        }
    }
    
    void operator-=(const HandlerType& handler) {
        if(_unbindFunc){
            _unbindFunc(handler);
        }
    }

private:
    std::function<void(HandlerType)> _bindFunc{nullptr};
    std::function<void(HandlerType)> _unbindFunc{nullptr};
};

#endif