#include <iostream>  
#include <queue>  
#include <thread>  
#include <mutex>  
#include <condition_variable>  
  
enum class TaskStatus {  
    READY,  
    RUNNING,  
    INTERRUPTED,  
    DONE  
};  
  
class Task {  
public:  
    Task(int priority) : priority_(priority), status_(TaskStatus::READY) {}  
  
    int getPriority() const { return priority_; }  
    TaskStatus getStatus() const { return status_; }  
  
    void setStatus(TaskStatus status) {  
        // std::unique_lock<std::mutex> lock(mutex_);  
        status_ = status;  
        // if (status == TaskStatus::DONE) {  
        //     cv_.notify_all(); // 通知等待的任务调度器  
        // }  
    }  
  
    void interrupt() {
        setStatus(TaskStatus::INTERRUPTED);
    }

    virtual void run(){}  



private:  
    int priority_;  
    TaskStatus status_;  
    std::mutex mutex_;  
    std::condition_variable cv_;  
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
        // std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout<<"addTask "<<task->getPriority()<<std::endl;
        if (currentTask)
        {
            if (currentTask->getPriority() > task->getPriority())
            {
                currentTask->interrupt();
                std::cout<<"打断当前任务 "<<std::endl;
            }
            // //todo: 优先级相等时候 后来的先触发
            // if (currentTask->getPriority() == task->getPriority())
            // {
            //     currentTask->interrupt();
            // }
        }
        tasks_.push(task);  
        lock.unlock();  
        cv_.notify_one(); // 通知等待的任务调度器  
    }  
  
    void run() {  
        int n = 0;
        while (true) {  
            std::unique_lock<std::mutex> lock(mutex_);  
            cv_.wait(lock, [this]{  return !tasks_.empty() || done_; });  
            // std::cout<<"cv 拿到锁"<<std::endl;
            if (done_) {  
                break;  
            }  

            Task* task = tasks_.top();  
            currentTask = task;  
            tasks_.pop();
            lock.unlock(); 
  
            if (task->getStatus() == TaskStatus::READY) {  
                task->setStatus(TaskStatus::RUNNING);  
                task->run();   
            } 
            if (task->getStatus() == TaskStatus::INTERRUPTED) {
                //todo:judge the precondition
                task->setStatus(TaskStatus::READY); 
                // std::cout<<"栈顶元素为"<<tasks_.top()->getPriority()<<std::endl; 
                addTask(task);
                std::cout<<"将当前被中断的任务重新加入队列 当前任务优先级 = "<<task->getPriority()<<std::endl;
                continue;  
            }
            task->setStatus(TaskStatus::DONE); 
            delete(currentTask);
        }  
    }  

    void shutdown() {  
        std::unique_lock<std::mutex> lock(mutex_);  
        done_ = true;  
        lock.unlock();  
        cv_.notify_all(); // 通知等待的任务调度器  
    }  

    void taskstatus(Task* task){
        if (task->getPriority()==1)
        {
            std::cout<<"高优先级任务"<<std::endl;
        }else{
            std::cout<<"低优先级任务"<<std::endl;
        }
        
    }

    bool comp(Task* a, Task* b){
        return (a->getPriority()) < (b->getPriority());
    }
  
private:  
    std::priority_queue<Task*, std::vector<Task*>,cmpClass> tasks_; // 优先级队列，高优先级任务在前  
    std::mutex mutex_;  
    std::condition_variable cv_;  
    bool done_ = false;  
    Task* currentTask{nullptr};
};  
  
class HighPriorityTask : public Task {  
public:  
    HighPriorityTask() : Task(1) {} // 假设高优先级任务的优先级为1  
  
    void run() {  
        std::cout<<"第 "<<highFlag<<" 次 执行 优先级 = 1 任务."<<std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1)); // 模拟任务执行  
        if (getStatus() == TaskStatus::INTERRUPTED)
        {
            std::cout <<"第 "<< highFlag << " 次 优先级 = 1 任务被打断..." << std::endl;  
            highFlag++;
            return;
        }
        std::cout<<"第 "<<highFlag<<" 次 优先级 = 1 任务 执行完毕"<<std::endl;
        highFlag++;
    }  

    int highFlag{1};
};  
  
class LowPriorityTask : public Task {  
public:  
    LowPriorityTask() : Task(2) {} // 假设低优先级任务的优先级为2  
  
    void run() {  
        std::cout<<"第 "<<lowFlag<<" 次 执行 优先级 = 2 任务."<<"开始计时"<<std::endl;
        int x = 1;
        for (size_t i = 0; i < 3; i++)
        {
            std::cout<<"优先级 = 2 计时时间 = "<<x++<<"\n";
            std::this_thread::sleep_for(std::chrono::seconds(1)); // 模拟任务执行
            if (getStatus() == TaskStatus::INTERRUPTED)
            {
                std::cout<<std::endl;
                std::cout<<"第 "<<lowFlag << " 次 优先级 = 2 任务被打断..." << std::endl;
                lowFlag++;
                return;  
            }
        }
        std::cout<<"第 "<<lowFlag<<" 次 优先级 = 2 任务 执行完毕"<<std::endl; 
        lowFlag++;
    }  

    int lowFlag{1};
};  
  
class LowPriorityTask3 : public Task {  
public:  
    LowPriorityTask3() : Task(3) {} // 假设低优先级任务的优先级为3  
  
    void run() {  
        std::cout<<"第 "<<lowFlag<<" 次 执行 优先级 = 3 任务."<<"开始计时"<<std::endl;
        int x = 1;
        for (size_t i = 0; i < 5; i++)
        {
            std::cout<<"优先级 = 3 计时时间 = "<<x++<<"\n";
            if (getStatus() == TaskStatus::INTERRUPTED)
            {
                std::cout<<std::endl;
                std::cout<<"第 "<<lowFlag << " 次 优先级 = 3 任务被打断..." << std::endl;
                lowFlag++;
                return;  
            }
            std::this_thread::sleep_for(std::chrono::seconds(1)); // 模拟任务执行
        }
        std::cout<<"第 "<<lowFlag<<" 次 优先级 = 3 任务 执行完毕"<<std::endl; 
        lowFlag++;
    }  

    int lowFlag{1};
}; 

class LowPriorityTask333 : public Task {  
public:  
    LowPriorityTask333() : Task(3) {} // 假设低优先级任务的优先级为3  
  
    void run() {  
        std::cout<<"第 "<<lowFlag<<" 次 执行 优先级 = 333 任务."<<"开始计时"<<std::endl;
        int x = 1;
        for (size_t i = 0; i < 5; i++)
        {
            std::cout<<"优先级 = 333 计时时间 = "<<x++<<"\n";
            if (getStatus() == TaskStatus::INTERRUPTED)
            {
                std::cout<<std::endl;
                std::cout<<"第 "<<lowFlag << " 次 优先级 = 333 任务被打断..." << std::endl;
                lowFlag++;
                return;  
            }
            std::this_thread::sleep_for(std::chrono::seconds(1)); // 模拟任务执行
        }
        std::cout<<"第 "<<lowFlag<<" 次 优先级 = 333 任务 执行完毕"<<std::endl; 
        lowFlag++;
    }  

    int lowFlag{1};
}; 
int main() {  
    TaskScheduler scheduler;  
  
    // 添加任务到调度器  
    HighPriorityTask* highPriorityTask = new HighPriorityTask();  // 1
    LowPriorityTask* lowPriorityTask = new LowPriorityTask();   // 2
    LowPriorityTask3* lowPriorityTask3 = new LowPriorityTask3(); // 3
    LowPriorityTask333* lowPriorityTask333  = new LowPriorityTask333(); // 3
    // 启动任务调度器线程  
    std::thread schedulerThread([&scheduler]() {  
        scheduler.run();  
    });  
  
    std::cout << "触发 低优先级任务" << std::endl;  
    scheduler.addTask(lowPriorityTask);  
    scheduler.addTask(lowPriorityTask3); 
    scheduler.addTask(lowPriorityTask333);
    std::this_thread::sleep_for(std::chrono::seconds(1)); // 模拟主线程进行其他任务
    // 模拟高优先级任务需要被触发  
    std::cout << "触发 高优先级任务" << std::endl;  
    scheduler.addTask(highPriorityTask);   // 中断低优先级任务  
    
    // 等待任务调度器线程完成  
    schedulerThread.join();  
  
    // 清理任务对象  
    delete lowPriorityTask;  
    delete highPriorityTask;  
  
    std::cout << "All tasks have been processed." << std::endl;  
  
    return 0;  
}