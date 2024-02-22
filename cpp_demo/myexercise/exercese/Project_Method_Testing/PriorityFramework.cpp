/**
 * @file PriorityFramework.cpp
 * @author XuYingBo (you@domain.com)
 * @brief 模拟喇叭、转向灯类涉及到优先级仲裁功能的执行流程
 * @version 0.1
 * @date 2024-02-22
    **设计思路
    map+vector 对队列进行管理。
    例如：std::map<优先级,vector<任务队列>>

    任务队列使用 std::list<std::function(void())>

    可进行循环遍历执行（单线程任务处理，考虑好执行一个任务时候的阻塞情况），从优先级最高的开始，哪个队列不为空，则先进行任务的执行。
    1、同优先级多个任务后来的先执行（栈）。
    2、做好任务队列的任务管理：添加、删除、查询。
    3、map表的快速遍历方法：查找出优先级最高的任务进行执行。
    4、任务执行方式也可以使用锁的方式，不用循环遍历。
    5、需要一个任务中断功能，也可以使用map进行管理中断方法。

        ** 优先级模块需求
        1、优先级高的先执行
        2、同优先级，后触发先执行
        3、中断后进行被中断任务的前提条件判断，若仍满足触发和前提条件，则保留任务用于恢复执行（恢复执行时，仍需要进行前提/触发的判断）,若不满足触发条件活前提条件，则删除该任务。
*TODO： 4、高优先级触发时，收到低优先级命令，是丢弃还是加入任务队列等待触发。

    **测试用例
    1、高优先级打断低优先级
    2、高优先级运行，低优先级触发，高优先级结束，处理低优先级触发任务
    3、按照优先级  3 2 1 2 3 进行任务的触发
    4、按照优先级 1 2 1 2 1 2 1 2 进行任务的触发
 */

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <condition_variable>
#include <functional>
#include <list>
//使用vsomeip的日志库
#include <vsomeip/internal/logger.hpp>

//* 最底层的开关操作，该操作不能并发控制，同时操作时应遵循优先级规则。
void Open(){
    VSOMEIP_INFO<<" 打开 ";
}

void Close(){
    VSOMEIP_INFO<<" 关闭 ";
}

//* 待执行的任务
struct Task
{
    //优先级
    uint8_t priority{0xff};
    //任务
    std::function<void()> task{nullptr};
    //中断标志
    bool interrupt{false};
    //中断函数
    std::function<void()> interruptTask{nullptr};
};



//待执行任务队列
std::list<Task> tasks;



int main(){

}