#include <iostream>
#include <string>
#include <mutex>
#include <thread>

using namespace std;

/*
*std::mutex 是C++11 中最基本的互斥量，std::mutex 对象提供了独占所有权的特性
*即不支持递归地对 std::mutex 对象上锁，而 std::recursive_lock 则可以递归地对互斥量对象上锁。
*最初产生的 mutex 对象是处于 unlocked 状态
*/

volatile int counter(0); // non-atomic counter
std::mutex mtx;           // locks access to counter
 
void attempt_10k_increases() {
    for (int i=0; i<10000; ++i) {
        if (mtx.try_lock()) {   // only increase if currently not locked:
            //mtx.lock();
            ++counter;
            mtx.unlock();
        }
    }
}
 
int main (int argc, const char* argv[]) {
    std::thread threads[10];
    for (int i=0; i<10; ++i)
        threads[i] = std::thread(attempt_10k_increases);
 
    for (auto& th : threads) th.join();
    std::cout << counter << " successful increases of the counter.\n";
 
    return 0;
}