#ifndef __THRDPOOL__
#define __THRDPOOL__

#include <functional>

typedef struct __thrdpool thrdpool_t;

struct thrdpool_task
{
  std::function<void(void *)> routine;
	// void (*routine)(void *); //要执行的函数指针
	void *context;//对本次任务的描述 保存时要转成void * 取出时 转回原类型
};


/**
 * @brief 创建线程池
 * 
 * @param nthreads 
 * @param stacksize 
 * @return thrdpool_t* 
 */
thrdpool_t *thrdpool_create(size_t nthreads, size_t stacksize);
/**
 * @brief 把任务交给线程池的入口
 * 
 * @param task 
 * @param pool 
 * @return int 
 */
int thrdpool_schedule(const struct thrdpool_task *task, thrdpool_t *pool);
int thrdpool_increase(thrdpool_t *pool);
int thrdpool_in_pool(thrdpool_t *pool);

/**
 * @brief 销毁线程池
 * 
 * @param pending 
 * @param pool 
 */
void thrdpool_destroy(void (*pending)(const struct thrdpool_task *),
					  thrdpool_t *pool);


#endif // __THRDPOOL__