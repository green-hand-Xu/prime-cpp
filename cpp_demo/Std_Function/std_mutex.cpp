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

void safe_increment(int iterations)
{
    const std::lock_guard<std::mutex> lock(mtx);
    while (iterations-- > 0){
        counts = counts + 1;
    }
    // g_i_mutex 当锁离开作用域后 会自动释放
}

//*****************std::unique_lock 练习
struct uniquelock
{
    explicit uniquelock(int num) : num_things{num}{
    }

    int num_things;
    std::mutex m;
};

void transfer(uniquelock &from , uniquelock &to ,int num){
    // 先构造锁但是不获取锁
    std::unique_lock lock1{from.m, std::defer_lock};
    std::unique_lock lock2{to.m, std::defer_lock};
    //在不会死锁的情况下 一次获取两个锁 
    std::lock(lock1,lock2);

    if (lock1 && lock2)
    {
        std::cout<<"成功获得锁"<<std::endl;
    }

    from.num_things -= num;
    to.num_things += num;

    lock1.unlock();//释放锁1
    lock2.unlock();//释放锁2

    if (!lock1 && !lock2)
    {
        std::cout<<"手动释放锁"<<std::endl;
    }
    
    //超出作用域后 uniquelock 会自动释放
}

void T_uniquelock(){
    uniquelock uni1{100};
    uniquelock uni2{50};
    //因为调用方法入参为引用，所以启用线程时使用 std::ref 进行转换参数类型
    std::thread t1{transfer,std::ref(uni1),std::ref(uni2),10};

    std::thread t2{transfer,std::ref(uni2),std::ref(uni1),5};

    t1.join();
    t2.join();

    std::cout << "acc1: " << uni1.num_things << "\n"
                 "acc2: " << uni2.num_things << '\n';
}

void T2_uniquelock(){
    uniquelock uni1{100};
    uniquelock uni2{50};
    //创建就获取锁
    std::unique_lock unl1{uni1.m};
    //创建不获取锁
    std::unique_lock unl2{uni2.m,std::defer_lock};
    std::cout<<" 交换前状态 unl1 st = "<< unl1.owns_lock() <<" unl2 st= "<<unl2.owns_lock()<<std::endl;

    //swap() : 与另一个 std::unique_lock 交换状态。
    unl1.swap(unl2); //u1 unlock  u2 lock
    std::cout<<" 交换后状态 unl1 st = "<< unl1.owns_lock() <<" unl2 st= "<<unl2.owns_lock()<<std::endl;

    unl1.try_lock();
    //unl1.try_lock(); 同一线程对已获得所有权的锁 重复获取锁会抛出死锁异常
}

void T3_uniquelock(){

    uniquelock uni1{100};
    uniquelock uni2{50};
    //创建就获取锁
    std::unique_lock unl1{uni1.m}; //u1 lock
    //创建不获取锁
    std::unique_lock unl2{uni2.m,std::defer_lock};// u2 unlock

    //mutex() : 返回指向关联互斥体的指针。
    std::cout<<" 交换前 unl1的指针地址为 "<<unl1.mutex()<<std::endl;
    std::cout<<" 交换前 unl2的指针地址为 "<<unl2.mutex()<<std::endl;

    //swap() : 与另一个 std::unique_lock 交换状态。
    unl1.swap(unl2); //u1 unlock  u2 lock

    //mutex() : 返回指向关联互斥体的指针。
    std::cout<<" 交换后 unl1的指针地址为 "<<unl1.mutex()<<std::endl;
    std::cout<<" 交换后 unl2的指针地址为 "<<unl2.mutex()<<std::endl;

    //交换后查看 unique_lock 对象状态
    if (unl1.owns_lock())
    {
        std::cout<<" 交换后状态 unl1 上锁"<<std::endl;
    }else{
        std::cout<<" 交换后状态 unl1 未上锁"<<std::endl;
    }
    if (unl2.owns_lock())
    {
        std::cout<<" 交换后状态 unl2 上锁"<<std::endl;
    }else{
        std::cout<<" 交换后状态 unl2 未上锁"<<std::endl;
    }
    
    //交换后尝试直接获取mutex锁 发现 uni1.m 仍是上锁状态，因此交换对绑定的mutex对象状态无影响
    if (uni1.m.try_lock())
    {
        std::cout<<" 交换后 查看 绑定的 mutex 变量状态 uni1.m 未上锁"<<std::endl;
        uni1.m.unlock();
    }else{
        std::cout<<" 交换后 查看 绑定的 mutex 变量状态 uni1.m 上锁"<<std::endl;
    }

    if (uni2.m.try_lock())
    {
        std::cout<<" 交换后 查看 绑定的 mutex 变量状态 uni2.m 未上锁"<<std::endl;
        uni2.m.unlock();
    }else{
        std::cout<<" 交换后 查看 绑定的 mutex 变量状态 uni2.m 上锁"<<std::endl;
    }   

    //release() : 解除关联的互斥体而不解锁（即释放其所有权）。如果在调用之前拥有关联互斥体的所有权，则调用者现在负责解锁互斥体。
    auto unl2bindmutex = unl2.release();//解除锁的关联，但是不会改变关联mutex锁的状态。返回与之绑定的mutex指针
    std::cout<<" unl2 绑定的 mutex 对象为 "<<unl2bindmutex<<std::endl;

    if (uni1.m.try_lock())
    {
        std::cout<<" 交换后 查看 绑定的 mutex 变量状态 uni1.m 未上锁"<<std::endl;
        uni1.m.unlock();
    }else{
        std::cout<<"unique_lock 2 解除锁关联后 直接尝试获取 uni1.m 的mutex锁 ，发现仍是上锁状态，并没有释放 "<<std::endl;
    }
}



int main (int argc, const char* argv[]) {
    T3_uniquelock();
}