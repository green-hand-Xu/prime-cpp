#ifndef __PRIORITYLIST__
#define __PRIORITYLIST__

#include <iostream>  
#include <queue>  
#include <thread>  
#include <mutex>  
#include <condition_variable>  
#include <functional>

/**
 * @brief 任务的运行状态
 * 
 */
enum class TaskStatus {  
    READY,  // 就绪状态，还未运行
    RUNNING,  // 正在运行
    INTERRUPTED,  // 正处于打断流程中
    DONE  // 任务已运行结束
};  

/**
 * @brief 任务的属性
 * 
 */
enum class TaskAttribute {  
    Rerun,//打断后需要重新运行
    Abandoned //打断后直接丢弃当前任务
};  
  
class Task {  
public:  
    Task(int priority) : priority_(priority), status_(TaskStatus::READY) {}  
  
    int getPriority() const { return priority_; }  
    TaskStatus getStatus() const { return status_; }  
    TaskAttribute getAttribute() const {return attribute_;};

    void setStatus(TaskStatus status) {  
        status_ = status;  
    }  

    void setAttribute(TaskAttribute attr){
        attribute_ = attr;
    }
  
    void interrupt() {
        setStatus(TaskStatus::INTERRUPTED);
    }

    void setTask(std::function<void()> FUN){
        fun = FUN;
    }

    void run(){
        if (fun)
        {
            fun();
        }
    }  
public: 
    //时间
    //运行次数 
    //触发源
    std::string name_{""};
    int priority_;  
    //执行任务
    std::function<void()> fun{nullptr};
    //任务状态
    TaskStatus status_;  
    //任务属性
    TaskAttribute attribute_{TaskAttribute::Abandoned};
};  

struct cmpClass
{
    // 操作符重载函数，必须是写()
    bool operator()(Task* a,Task* b)
    {
        // less,大顶堆
        return a->getPriority() > b->getPriority() ? true : false;
    }
};

class TaskScheduler {  
public:  
    void addTask(Task* task) {  
        std::unique_lock<std::mutex> lock(mutex_);  
        if (currentTask)
        {
            if (currentTask->getPriority() >= task->getPriority())
            {
                currentTask->interrupt();
            }
        }
        tasks_.push(task);  
        lock.unlock();  
        cv_.notify_one(); 
    } 

    void push_task(Task* task){
        std::unique_lock<std::mutex> lock(mutex_);
        tasks_.push(task);
        lock.unlock();  
        cv_.notify_one(); 
    } 
  
    void run() {  
        int n = 0;
        while (true) {  
            std::unique_lock<std::mutex> lock(mutex_);  
            cv_.wait(lock, [this]{  return !tasks_.empty() || done_; });  
            if (done_) {  
                break;  
            }  

            Task* task = tasks_.top();  
            currentTask = task;  
            tasks_.pop();
            lock.unlock(); 

            if (task->getStatus() == TaskStatus::READY) {  
                task->setStatus(TaskStatus::RUNNING);  
                std::cout<<"当前运行任务为"<<(task->name_)<<std::endl;
                task->run();   
            } 
            if (task->getStatus() == TaskStatus::INTERRUPTED) {
                task->setStatus(TaskStatus::READY); 
                if (task->getAttribute()==TaskAttribute::Rerun)
                {
                    push_task(task);
                    std::cout<<"将当前被中断的任务重新加入队列 "<<std::endl;
                }
                continue;  
            }
            task->setStatus(TaskStatus::DONE); 
            delete(currentTask);
            currentTask = nullptr;
        }  
    }  

    void shutdown() {  
        std::unique_lock<std::mutex> lock(mutex_);  
        done_ = true;  
        lock.unlock();  
        cv_.notify_all(); // 通知等待的任务调度器  
    }  

public:  
    std::priority_queue<Task*, std::vector<Task*>,cmpClass> tasks_; // 优先级队列，高优先级任务在前  
    std::mutex mutex_;  
    std::condition_variable cv_;  
    bool done_ = false;  
    Task* currentTask{nullptr};
};  

#endif // __PRIORITYLIST__