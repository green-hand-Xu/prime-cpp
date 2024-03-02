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
        if (getPriority() == 2)
        {
            std::cout << "对 低优先级任务 进行打断设置" << std::endl;
            setStatus(TaskStatus::INTERRUPTED);   
            return;
        }
    }

    virtual void run(){}  

    bool operator<(Task a){
       return this->getPriority() < a.getPriority() ? true : false;
    }
  
private:  
    int priority_;  
    TaskStatus status_;  
    std::mutex mutex_;  
    std::condition_variable cv_;  
};  
  
class TaskScheduler {  
public:  
    void addTask(Task* task) {  
        std::unique_lock<std::mutex> lock(mutex_);  
        if (!tasks_.empty())
        {
            auto curtask = tasks_.top();
            std::cout<<"当前任务优先级 = "<<curtask->getPriority()<<" 新加入的任务优先级 = "<<task->getPriority()<<std::endl;
            if (curtask->getPriority() > task->getPriority())
            {
                curtask->interrupt();
                std::cout<<"打断当前任务 "<<std::endl;
            }
        }
        tasks_.push(task);  
        lock.unlock();  
        cv_.notify_one(); // 通知等待的任务调度器  
    }  
  
    void run() {  
        while (true) {  
            std::unique_lock<std::mutex> lock(mutex_);  
            cv_.wait(lock, [this]{ return !tasks_.empty() || done_; });  
  
            if (done_) {  
                break;  
            }  

            Task* task = tasks_.top();    
            
            lock.unlock(); 
  
            if (task->getStatus() == TaskStatus::READY) {  
                task->setStatus(TaskStatus::RUNNING);  
                task->run();   
            } 
            if (task->getStatus() == TaskStatus::INTERRUPTED) {
                //todo:judge the precondition
                task->setStatus(TaskStatus::READY);  
                tasks_.pop();
                addTask(task);
                std::cout<<"将当前被中断的任务重新加入队列 当前任务为"<<(task->getPriority() == 1 ? "高优先级任务" : "低优先级任务")<<std::endl;
                continue;  
            } 
            task->setStatus(TaskStatus::READY);
            tasks_.pop();
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
  
private:  
    std::priority_queue<Task*, std::vector<Task*>> tasks_; // 优先级队列，高优先级任务在前  
    std::mutex mutex_;  
    std::condition_variable cv_;  
    bool done_ = false;  
};  
  
class HighPriorityTask : public Task {  
public:  
    HighPriorityTask() : Task(1) {} // 假设高优先级任务的优先级为1  
  
    void run() {  
        std::cout<<"第 "<<highFlag<<" 次 执行高优先级任务."<<std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1)); // 模拟任务执行  
        if (getStatus() == TaskStatus::INTERRUPTED)
        {
            std::cout <<"第 "<< highFlag << " 次高优先级任务被打断..." << std::endl;  
            highFlag++;
            return;
        }
        std::cout<<"第 "<<highFlag<<" 次 高优先级任务 执行完毕"<<std::endl;
        highFlag++;
    }  

    int highFlag{1};
};  
  
class LowPriorityTask : public Task {  
public:  
    LowPriorityTask() : Task(2) {} // 假设低优先级任务的优先级为2  
  
    void run() {  
        std::cout<<"第 "<<lowFlag<<" 次 执行低优先级任务."<<std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(4)); // 模拟任务执行  
        if (getStatus() == TaskStatus::INTERRUPTED)
        {
            std::cout<<"第 "<<lowFlag << " 次低优先级任务被打断..." << std::endl;
            lowFlag++;
            return;  
        }
        std::cout<<"第 "<<lowFlag<<" 次 低优先级任务 执行完毕"<<std::endl; 
        lowFlag++;
    }  

    int lowFlag{1};
};  
  
int main() {  
    TaskScheduler scheduler;  
  
    // 添加任务到调度器  
    LowPriorityTask* lowPriorityTask = new LowPriorityTask();  
    HighPriorityTask* highPriorityTask = new HighPriorityTask();  
    std::cout << "触发 低优先级任务" << std::endl;  
    scheduler.addTask(lowPriorityTask);  
  
    // 启动任务调度器线程  
    std::thread schedulerThread([&scheduler]() {  
        scheduler.run();  
    });  
  
    // 模拟主线程继续执行其他任务  
    // std::cout << "Main thread continuing with other work..." << std::endl;  
    std::this_thread::sleep_for(std::chrono::seconds(1)); // 等待一段时间  
  
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