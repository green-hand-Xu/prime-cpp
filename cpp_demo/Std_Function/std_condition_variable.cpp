#include <mutex>
#include <iostream>
#include <thread>
#include <condition_variable>
#include <atomic>

std::mutex m;
std::condition_variable cv;
std::string data;
bool ready = false;
bool processed = false;
 
void worker_thread()
{
    while (1)
    {
        // Wait until main() sends data
        std::unique_lock<std::mutex> lk(m);
        //子进程的中wait函数对互斥量进行解锁，同时线程进入阻塞或者等待状态。
        cv.wait(lk, []{
            return ready;
        });
    
        // after the wait, we own the lock.
        std::cout << "Worker thread is processing data\n";
        data += " after processing";
    
        // Send data back to main()
        processed = true;
        std::cout << "Worker thread signals data processing completed\n";
    
        // Manual unlocking is done before notifying, to avoid waking up
        // the waiting thread only to block again (see notify_one for details)
        lk.unlock();
        cv.notify_one();
    }
}

void modify_ready(bool St){
    // send data to the worker thread
    std::lock_guard<std::mutex> lk(m);
    ready = St;
    std::cout << "ready 状态被修改为: "<<ready<<std::endl;
}

int main(){
    std::thread worker(worker_thread);

    while (1)
    {
        std::cout<<"请输入ready状态:"<<std::endl;
        int a{0};
        std::cin>>a;
        modify_ready(a);
        cv.notify_one();
    }
    worker.join();
    return 0;
}