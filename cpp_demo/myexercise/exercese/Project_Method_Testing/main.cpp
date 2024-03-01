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
        std::unique_lock<std::mutex> lock(mutex_);  
        status_ = status;  
        if (status == TaskStatus::DONE) {  
            cv_.notify_all(); // 通知等待的任务调度器  
        }  
    }  
  
    void interrupt() {  
        setStatus(TaskStatus::INTERRUPTED);  
    }  

    virtual void run() = 0;
  
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
            if (curtask->getPriority() > task->getPriority())
            {
                curtask->setStatus(TaskStatus::INTERRUPTED);
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
            tasks_.pop();  
            lock.unlock();  
  
            if (task->getStatus() == TaskStatus::READY) {  
                task->setStatus(TaskStatus::RUNNING);  
                task->run();  
                task->setStatus(TaskStatus::DONE);  
            } else if (task->getStatus() == TaskStatus::INTERRUPTED) {  
                task->setStatus(TaskStatus::READY); // 重新放入队列  
                addTask(task);  
            }  
        }  
    }  
  
    void shutdown() {  
        std::unique_lock<std::mutex> lock(mutex_);  
        done_ = true;  
        lock.unlock();  
        cv_.notify_all(); // 通知等待的任务调度器  
    }  
  
private:  
    std::priority_queue<Task*, std::vector<Task*>, std::greater<Task*>> tasks_; // 优先级队列，高优先级任务在前  
    std::mutex mutex_;  
    std::condition_variable cv_;  
    bool done_ = false;  
};  
  
class HighPriorityTask : public Task {  
public:  
    HighPriorityTask() : Task(1) {} // 假设高优先级任务的优先级为1  
  
    void run() {  
        std::cout << "Executing high priority task..." << std::endl;  
        std::this_thread::sleep_for(std::chrono::seconds(1)); // 模拟任务执行  
        if (getStatus() == TaskStatus::INTERRUPTED)
        {
            std::cout << "高优先级任务被打断..." << std::endl;  
        }
        std::cout << "High priority task done." << std::endl;  
    }  
};  
  
class LowPriorityTask : public Task {  
public:  
    LowPriorityTask() : Task(2) {} // 假设低优先级任务的优先级为2  
  
    void run() {  
        std::cout << "Executing low priority task..." << std::endl;  
        std::this_thread::sleep_for(std::chrono::seconds(10)); // 模拟任务执行  
        if (getStatus() == TaskStatus::INTERRUPTED)
        {
            std::cout << "低优先级任务被打断..." << std::endl;  
        }
        std::cout << "Low priority task done." << std::endl;  
    }  
};  
  
int main() {  
    TaskScheduler scheduler;  
  
    // 添加任务到调度器  
    LowPriorityTask* lowPriorityTask = new LowPriorityTask();  
    HighPriorityTask* highPriorityTask = new HighPriorityTask();  
  
    scheduler.addTask(lowPriorityTask);  
    scheduler.addTask(highPriorityTask);  
  
    // 启动任务调度器线程  
    std::thread schedulerThread([&scheduler]() {  
        scheduler.run();  
    });  
  
    // 模拟主线程继续执行其他任务  
    std::cout << "Main thread continuing with other work..." << std::endl;  
    std::this_thread::sleep_for(std::chrono::seconds(1)); // 等待一段时间  
  
    // 模拟高优先级任务需要被触发  
    std::cout << "High priority task triggered!" << std::endl;  
    highPriorityTask->interrupt(); // 中断低优先级任务  
  
    // 等待任务调度器线程完成  
    schedulerThread.join();  
  
    // 清理任务对象  
    delete lowPriorityTask;  
    delete highPriorityTask;  
  
    std::cout << "All tasks have been processed." << std::endl;  
  
    return 0;  
}