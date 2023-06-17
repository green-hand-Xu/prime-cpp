#include <iostream>
#include "thrdpool.h"
#include "computColor.h"
#include <thread>

#include <functional>
#include <limits.h>
#include "error.h"

bool flag = true;

typedef void (*TaskType)(void *); //定义context 类型的函数指针

    /**
     * @brief 
     * 
     * @param task 
     */
    void my_pending(const struct thrdpool_task *task){
        // 线程池销毁后，没执行的任务会到这里
        //todo:暂不处理未执行的任务
        printf("pending task-%llu.\n", reinterpret_cast<unsigned long long>(task->context)); 
    }

class Threadpool
{
public:
    //默认创建线程池：线程数 5  堆栈大小 4k (ubutun 最小大小为4k)
    Threadpool(){
        thrdpool = thrdpool_create((size_t)(5),(size_t)(16384));
        std::cout<<"initialization finish"<<std::endl;
    }
    ~Threadpool() = default;

    /**
     * @brief Construct a new Threadpool object
     * 
     * @param pools 线程池大小
     * @param stacks_size 线程堆栈大小
     */
    Threadpool(size_t pools , size_t stacks_size){
        thrdpool = thrdpool_create(pools,stacks_size);
    }

    /**
     * @brief 开启线程任务
     * 
     * @param task 要执行的线程任务
     * @return int 
     */
    int thrdstart(TaskType task){
        _task.context = reinterpret_cast<void *>(0);
        _task.routine = task; 
        auto ret = thrdpool_schedule(&_task,thrdpool);//将线程任务放入线程池启动
        return ret;
    }

    void destory_thrdpool(){
        thrdpool_destroy(&my_pending, thrdpool); // 摧毁线程池并取出未执行的任务
    }

    thrdpool_t* thrdpool; //申请的线程池对象
    thrdpool_task _task; //执行的任务对象
};


//动态模式颜色切换
void my_routine(void *context)                                                   
{   
    std::cout<< " 动态模式颜色切换启动 "<<std::endl;
    uint8_t i = 0;
    while (flag == true)
    {
        auto test_color = return_rgbcolor(static_cast<AtmLi_ColorSet_64_Enum>(i),colormap);
        std::cout<< static_cast<int>(i) << " ";
        print_ColorCtrl_Struct(test_color);
        ++i;
        if(i > 63){
            i = static_cast<uint8_t>(0);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    i = static_cast<uint8_t>(0);
    std::cout<<"flag == false i = "<< static_cast<int>(i) <<std::endl;
}


int print_STACK_size(){

   pthread_t thread;

   size_t stacksize;

   pthread_attr_t thread_attr;

   int ret;

   pthread_attr_init(&thread_attr);

   int new_size = 20480;

   ret =  pthread_attr_getstacksize(&thread_attr,&stacksize);

   if(ret != 0){

       std::cout << "emError" << std::endl;

       return -1;

   }

 

   std::cout << "stacksize=" << stacksize << std::endl;

 

  std::cout << PTHREAD_STACK_MIN << std::endl;

   ret = pthread_attr_setstacksize(&thread_attr,new_size);

   if(ret != 0)

       return -1;

   ret =  pthread_attr_getstacksize(&thread_attr,&stacksize);

   if(ret != 0){

       std::cout << "emError" << std::endl;

       return -1;

   }

   std::cout << "after set stacksize=" << stacksize << std::endl;

   ret = pthread_attr_destroy(&thread_attr);

   if(ret != 0)

      return -1;

   return 0;    
}

thrdpool_task task ;
void thrdpool_start(){
    thrdpool_t *thrd_pool = thrdpool_create(3, 16384); // 创建 线程池  堆栈大小采取最小值       
    
    unsigned long long i;
                               
    // for (i = 0; i < 5; i++)

    // {
        auto tri = [](void *){my_routine(task.context);}; 
        task.routine = tri;                                           
        // task.context = reinterpret_cast<void *>(i);                             
        thrdpool_schedule(&task, thrd_pool); // 调用
    // }
    // getchar(); // 卡住主线程，按回车继续
    // thrdpool_destroy(&my_pending, thrd_pool); // 结束
}

void std_threadstart(){
    int i =0;
    std::thread(
        [&i](){
            while (flag)
            {
                std::cout<<++i<<std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        }
    ).detach();
}



int main()                                                                         
{
    Threadpool threadpool;
    threadpool.thrdstart([](void *){my_routine(task.context);});
    print_STACK_size();
    getchar(); // 卡住主线程，按回车继续
    flag = false;
    getchar();
    return 0;                                                                   
} 