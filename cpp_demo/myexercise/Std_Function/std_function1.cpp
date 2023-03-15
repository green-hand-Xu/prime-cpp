//c++ std::function
#include <iostream>
#include <functional>

class TimerBasicController
{
public:
    //定义一个枚举类型
    enum class TimerState { TimerDefault = 0, TimerTrigger = 1};
    
    //将定义TimerState类型的function对象 声明语句起别名
    using NotifierFn = std::function<void(TimerState)>;

    //定义一个NotifierFn（std::function<void(TimerState)>）对象实例
    //此处别名 相当于std::function<void(TimerState)> 在项目组这种用法大量用到
     NotifierFn _notifier;

    //写一个方法专门用来给_notifier对象赋值
     void setTimerNotifier(NotifierFn notifier) {
    _notifier = notifier;
}

};

//模拟一个可调用函数 用于判断枚举类型
//在项目中 一般用一个lambda表达式代替
void callback (TimerBasicController::TimerState data){
    if(data == TimerBasicController::TimerState::TimerTrigger) 
    {
        std::cout<<"is TimerTrigger"<<std::endl;      
        //this->TimerSt.Update(_timerState);
    } else 
    {
        std::cout<<"not TimerTrigger"<<std::endl;  
    }
    //this->TimerSt.Update(_timerState);
};



int main()
{
    TimerBasicController timerBasicController;
    //给声明的_notifier对象赋值一个可调用对象
    //项目中采取的lambda表达式形式
    timerBasicController.setTimerNotifier(callback);
    timerBasicController._notifier(TimerBasicController::TimerState::TimerTrigger);
    return 0;
}
