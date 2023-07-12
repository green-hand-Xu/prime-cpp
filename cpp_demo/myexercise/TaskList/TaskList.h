#ifndef __TASKLIST__
#define __TASKLIST__
#include <atomic>
//任务接口
class WorkItem
{
public:
	//接口方法必须在子类实现
	virtual void run() = 0;
 
public:
	//任务清理接口
	virtual void clean()
	{
	}
	//判断任务是否可执行(返回真时任务才会执行)
	virtual bool runnable()
	{
		return true;
	}
};

//自旋锁类
class SpinMutex
{
private:
	std::atomic_flag flag = ATOMIC_FLAG_INIT;
 
public:
	void lock()
	{
		while (flag.test_and_set(std::memory_order_acquire));
	}
	void unlock()
	{
		flag.clear(std::memory_order_release);
	}
};



/**
 * @brief 任务队列的使用，将要执行的任务放进队列，让任务按照顺序一个接一个的触发
 * 
 */
class TaskList
{
public:
    TaskList(){

    };
    ~TaskList(){

    };

    //Push: 往任务队列里放任务（互斥方法）同时只能只能有一个线程放任务，其余的等待锁释放后在放任务,任务执行后要清理任务

    //Start: 启动线程 

    //ProcessData: 循环去队列里拿任务 然后执行

    //TryLock: 尝试获取锁,锁被占用则等待锁

    //UnLock: 释放锁
    
    //TaskList: 任务队列


};


int main(){



    return 0;
}



#endif // __TASKLIST__