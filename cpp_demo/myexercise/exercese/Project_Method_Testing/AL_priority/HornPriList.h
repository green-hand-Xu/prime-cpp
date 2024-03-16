/**
 * @file HornPriList.h
 * @author XuYingBo (you@domain.com)
 * @brief 喇叭优先级类，涉及到喇叭控制的操作均需要将任务扔到这里面，执行任务请自己做好中断位置。
 * @version 0.1
 * @date 2024-03-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef __HORNPRILIST__
#define __HORNPRILIST__

#include "priorityList.h"

class HornPriList
{
private:
    HornPriList(){
        std::thread schedulerThread([this](){
            scheduler.run();
        });
        schedulerThread.detach();
    };
public:
    static HornPriList& getInstance(){
        static HornPriList horn;
        return horn;
    }
    TaskScheduler scheduler;
};


#endif // __HORNPRILIST__