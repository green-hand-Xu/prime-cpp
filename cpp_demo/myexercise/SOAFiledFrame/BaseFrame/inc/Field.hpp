#ifndef __FIELD__
#define __FIELD__

#include <functional>
/**
 * @brief Field 字段的处理类
 * 将Field 声明为一个此类对象，封装一些针对于该field常用的操作
 * 某些子类可以重载的函数 设置为虚函数，尽量所有函数设置为 不抛出异常
 * 
 * @tparam T Field 字段的类型 
 */
template <typename T>
class FieldOperateObj{
public:

    // 接收到Field后 执行的函数
    using FieldChange_Before = std::function<bool(T value)>;
    // 接收到Filed后 若Field 发生了值的变化 执行的函数
    using FieldChange_After = std::function<bool(T old value , T newvalue)>;
    // 接收到Field后 值变化后执行的函数
    using FieldValue_Handler = FieldChange_After;

    FieldChange_Before onChangeBefore{nullptr};//Field 触发后 立即执行的函数
    FieldChange_After onChangeAfter{nullptr};//Field 触发并保存到本地后 立即执行的函数
    FieldValue_Handler onChangeValue{nullptr};//Field 触发后 在保存之前 对Field 数据进行处理特定触发的函数

    protected:
    bool _isInitialValue{true};//标识 是否为初始值
    T _lastValue, _value;//当前值 上一次的值

    protected:
    inline void invokeOnChanged(T lastvalue,T value){
        //判断回调函数是否以及设置有内容
        if (onChangeAfter)
        {
            std::invoke(onChangeAfter,lastvalue,value);//如果设置的有值，则执行对应回调函数
        }
        
    }

    public:
    //*Construct
    //无参构造函数
    FieldOperateObj() : FieldOperateObj(T{},true){

    }
    //带Field 值的构造函数
    explicit FieldOperateObj(T value) : FieldOperateObj(value , true){

    }
    //带Field 值 和 标识符的构造函数
    explicit FieldOperateObj(T value , bool isInitial){
        _value = value;
        _isInitialValue = isInitial;
    }

    //*Basic Fun

    //初始化标志位
    virtual void init() noexcept{
        _isInitialValue = true;
    }

    //获取标志位的值 只是获取值 这类行数少的 可以声明为内联函数 直接编译到调用处
    inline bool isInitial() noexcept {
        return _isInitialValue;
    }

    //获取_value的值  const 加载参数列表后面 表面该函数为只读函数，不能修改类的成员的值 （相当于成员函数的隐藏参数 *this 为const类型的）
    T value() const noexcept{
        return _value;
    }
    //获取_lastvalue的值
    T lastvalue() const noexcept{
        return _value;
    }

    void update(T value) noexcept{
        if(onChangeBefore){
            if(!onChangeBefore(value)){
                return;//如果触发后立即执行的函数 判断提前失败 则提前退出
            }
        }

        //若当前值为初始值状态，则修改值的同时，修改初始值状态标志位
        if(_isInitialValue){
            _isInitialValue = false;
            _value = value;//更新内部存储的field 值
            //因为为初始值，所以_lastvalue 还没有进行过更新，因此两个入参全部 传入_value
            std::invoke(invokeOnChanged,_value,_value);
        }

        _lastValue = _value;
        _value = value;
        std::invoke(invokeOnChanged,_lastValue,_value);
    }

};

#endif // __FIELD__