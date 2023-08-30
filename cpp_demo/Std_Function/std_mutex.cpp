#include <iostream>
#include <string>
#include <mutex>
#include <thread>
#include <cstdio>
#include <functional>
#include <map>
#include <list>
#include <atomic>
#include <algorithm>
using namespace std;

/*
*std::mutex 是C++11 中最基本的互斥量，std::mutex 对象提供了独占所有权的特性
*即不支持递归地对 std::mutex 对象上锁，而 std::recursive_lock 则可以递归地对互斥量对象上锁。
*最初产生的 mutex 对象是处于 unlocked 状态
*/

std::mutex mtx;           // locks access to counter
std::timed_mutex tmtx;   // 带时间的锁

volatile int counts{0};

void sync_fun1() {
    //使用 print 输出是为了防止多线程下 cout（非线程安全） 的输出混乱问题。
    if (mtx.try_lock())
    {
        printf("线程id = %-ld  持有锁 \n",std::this_thread::get_id());
        counts++;
        mtx.unlock();//解锁
        printf("线程id = %-ld  释放锁 \n",std::this_thread::get_id());
    }else{
        printf("线程id = %-ld  未持有锁 \n",std::this_thread::get_id());
    }
    
}

void sync_fun2() {
    if (tmtx.try_lock_for(std::chrono::seconds(2))) // 两秒内没有获得锁 则阻塞 获得锁则继续执行
    {
        printf("线程id = %-ld  持有锁 \n",std::this_thread::get_id());
        counts++;
        tmtx.unlock();//解锁
        printf("线程id = %-ld  释放锁 \n",std::this_thread::get_id());
    }else{
        printf("线程id = %-ld  未持有锁 \n",std::this_thread::get_id());
    }
    
}

void sync_fun3(int i) {

    mtx.lock();
    printf("线程id = %-d  持有锁 \n ",i);
    counts++;
    mtx.unlock();//解锁
    printf("线程id = %-d  释放锁 \n",i); 
}

std::mutex Linkmtx;
std::mutex LinkExemtx;
int mapcounts;
struct FreqFields{
    int No;
    int Freq0;
    int Freq1;
    int Freq2;
    int Freq3;
};

std::map<int,FreqFields> LinkTasks;
std::list<FreqFields> List_Tasks;
std::atomic<bool> LinkSwt{false};

//要执行的处理任务
void FunTask(FreqFields task){
    auto [No,Freq0,Freq1,Freq2,Freq3] = task;
    printf("Tasks,No = %d \n",No);
    printf("Tasks,Freq0 = %d \n",Freq0);
    printf("Tasks,Freq1 = %d \n",Freq1);
    printf("Tasks,Freq2 = %d \n",Freq2);
    printf("Tasks,Freq3 = %d \n",Freq3);    
}

//排序队列 并取出队列中第一个元素
FreqFields GetFirstNode(){
    LinkExemtx.lock();
    List_Tasks.sort([](FreqFields a ,FreqFields b){return a.No<b.No;});
    auto task = List_Tasks.front();
    List_Tasks.pop_front();
    LinkExemtx.unlock();
    return task;
}

//执行函数
void execute_Tri(){
    if (LinkSwt.load())
    {
        std::cout<<"已有线程启动"<<std::endl;
        return;
    }
    
    std::thread([](){
        LinkSwt.store(true);
        //队列不等于0时 升序排序 然后取出第一个元素 并执行 读数据操作为异步
        while (List_Tasks.size() != 0)
        {
            auto task = GetFirstNode();
            FunTask(task);
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
        LinkSwt.store(false);
    }).detach();
}

void mappush_task(int No , FreqFields FrqStruct){
    Linkmtx.lock();
    LinkTasks.insert({No,FrqStruct});
    Linkmtx.unlock();
}

void listpush_task(FreqFields FrqStruct){
    LinkExemtx.lock();
    List_Tasks.push_back(FrqStruct);
    LinkExemtx.unlock();
    execute_Tri();
}

void print_map(std::map<int,FreqFields> LinkTasks){
    for (auto [key,value] : LinkTasks)
    {
        std::cout<<"Map.Size = "<<LinkTasks.size()<<std::endl;
        std::cout<<"Id = "<<key<<std::endl;
        std::cout<<"Tasks,Freq0 = "<< value.Freq0<<std::endl;
        std::cout<<"Tasks,Freq1 = "<< value.Freq1<<std::endl;
        std::cout<<"Tasks,Freq2 = "<< value.Freq2<<std::endl;
        std::cout<<"Tasks,Freq3 = "<< value.Freq3<<std::endl;
    }
    
}

void retNew_Task(){

}



int main (int argc, const char* argv[]) {
    std::thread threads[10];

    for (int i=0; i<10; ++i){
        threads[i] = std::thread(listpush_task,FreqFields{i,i,i,i,i});
    }

    for (auto& th : threads) {
        th.join();
    }

    std::this_thread::sleep_for(100s);
    return 0;
}