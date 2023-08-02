#include <iostream>
#include <string>
#include <mutex>
#include <thread>
#include <cstdio>

using namespace std;

/*
*std::mutex 是C++11 中最基本的互斥量，std::mutex 对象提供了独占所有权的特性
*即不支持递归地对 std::mutex 对象上锁，而 std::recursive_lock 则可以递归地对互斥量对象上锁。
*最初产生的 mutex 对象是处于 unlocked 状态
*/

std::mutex mtx;           // locks access to counter
 
void sync_fun1() {
    //使用 print 输出是为了防止多线程下 cout（非线程安全） 的输出混乱问题。
    if (mtx.try_lock())
    {
        printf("线程id = %-ld  持有锁 \n",std::this_thread::get_id());
        mtx.unlock();//解锁
        printf("线程id = %-ld  释放锁 \n",std::this_thread::get_id());
    }else{
        printf("线程id = %-ld  未持有锁 \n",std::this_thread::get_id());
    }
    
}
 
int main (int argc, const char* argv[]) {
    std::thread threads[10];
    for (int i=0; i<10; ++i){
        threads[i] = std::thread(sync_fun1);
    }
    for (auto& th : threads) {
        th.join();
    }
    return 0;
}