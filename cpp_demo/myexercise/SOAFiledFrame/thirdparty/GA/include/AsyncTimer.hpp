#ifndef __AsyncTimer_HPP__
#define __AsyncTimer_HPP__

#include <functional>
#include <thread>
#include <chrono>

using namespace std::chrono_literals;
using namespace std::chrono;
using namespace std::this_thread;

inline steady_clock::time_point now(){
    return steady_clock::now();
}

/**
 * @brief 异步计时器，通过创建线程来进行异步执行。
 * 可以通过销毁计时器对象来停止计时器。
 * 
 * @note 基于Sleep实现，可
 */
class AsyncTimer
{
    AsyncTimer(const AsyncTimer &) = delete;
    AsyncTimer(AsyncTimer &&) = delete;
    AsyncTimer & operator =(const AsyncTimer &) = delete;
    AsyncTimer & operator =(AsyncTimer &&) = delete;

public:
    using T_Interval = duration<double, std::milli>;

    const T_Interval DefaultWaitingTaskCheckInterval = 100ms;

    struct TaskArg {
        /**
         * @brief 重复任务继续执行标志。
         * true: 继续执行
         * false: 停止执行
         */
        bool isContinue{true};
        
        /**
         * @brief 重复任务执行间隔。
         * 有效值为大于0ms；默认值为1ms。
         * 通过sleep以保证任务执行间隔是此处设定的毫秒值。
         */
        T_Interval interval{1};
    };
    using RepeatableTaskHandler = std::function<void(TaskArg&)>;

private:
    struct TaskArgInternal : TaskArg
    {
        /**
         * @brief interval生效标志。
         * 内部调度时可把内置的sleep等待机制停止，而使用自己的等待机制，此时repeat是一个没有停止的循环。
         */
        bool isIntervalOn{true};

        //如果interval有效，则根据此处设定值约定其最小值。
        T_Interval intervalMin{1};
    };
    using RepeatableTaskHandlerInternal = std::function<void(TaskArgInternal& args)>;

public:
    AsyncTimer() : AsyncTimer(nullptr) {

    }

    // 构造一个不间断重复执行的任务，默认间隔sleep 1毫秒。
    explicit AsyncTimer(RepeatableTaskHandler task)
        : _isWorking(std::make_shared<bool>(true)) {
        
        if(task){
            repeat(task);
        }
    }

    // 构造一个不间断执行的任务，并指定间隔执行的时间。
    template<typename _Rep, typename _Period>
    explicit AsyncTimer(const duration<_Rep, _Period>& interval, RepeatableTaskHandler task)
        : _isWorking(std::make_shared<bool>(true)) {
        
        if(task){
            repeat(interval, task);
        }
    }

    // 计时器销毁时的通知，销毁时会调用该通知。
    std::function<void()> onDestroy{nullptr};

    // 在指定时间以后执行指定函数。
    template<typename _Rep, typename _Period>
    void run(const duration<_Rep, _Period>& waitingTime, std::function<void()> func){
        if(!func){
            return;
        }

        TaskArgInternal args;
        args.interval = DefaultWaitingTaskCheckInterval;
        if(waitingTime < args.interval){
            args.interval = waitingTime;
        }

        auto startTime = now();
        auto finalLine = startTime + waitingTime - args.interval;
        auto runTime = startTime + waitingTime;

        repeatTask([this, func, startTime, finalLine, runTime](TaskArgInternal& arg){
            auto current = now();

            if(current < finalLine) {
                return;
            }

            if(current < runTime) {
                sleep_for(runTime - current);
            }

            arg.isContinue = false;
            func();

        }, args);
    }

    /**
     * @brief 重复执行指定函数，每次执行线程默认sleep 1毫秒。
     */
    void repeat(RepeatableTaskHandler task){
        repeatTask(task, TaskArgInternal());
    }

    // 按照指定时间重复执行指定函数。
    template<typename _Rep, typename _Period>
    void repeat(const duration<_Rep, _Period>& interval, RepeatableTaskHandler task){
        TaskArgInternal args{};
        args.interval = duration_cast<T_Interval>(interval);

        repeatTask(task, args);
    }

    ~AsyncTimer(){
        _isWorking = nullptr;
        if(onDestroy){
            onDestroy();
        }
    }

private:
    // 所有任务共享的有效性标志，标志清除时，各个并发的异步任务都会在sleep完成之后取消。
    std::shared_ptr<bool> _isWorking{nullptr};

    void repeatTask(RepeatableTaskHandlerInternal func, TaskArgInternal funcArgs){
        if(!func){
            return;
        }

        std::weak_ptr<void> workFlag(_isWorking);

        std::thread([func, funcArgs, workFlag](){
            auto args = funcArgs;

            while (!workFlag.expired()) {
                auto started = now();
                func(args);

                if(!args.isContinue) {
                    break;
                }

                if(!args.isIntervalOn) {
                    continue;
                }

                if(args.interval < args.intervalMin) {
                    args.interval = args.intervalMin;
                }

                T_Interval left{args.interval - (now() - started)};
                if(left <= T_Interval::zero()) {
                    continue;
                }

                if(left < args.interval) {
                    sleep_for(left);
                }else{
                    sleep_for(args.interval);
                }
            }

        }).detach();
    }


};

#endif