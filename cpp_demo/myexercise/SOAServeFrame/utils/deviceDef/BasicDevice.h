#ifndef __utils_deviceDef_BasicDevice_HPP__
#define __utils_deviceDef_BasicDevice_HPP__

#include <memory>
#include "VehicleEventBus.hpp"

/**
 * @brief 定义设备的基本行为和能力。
 */
class BasicDevice
{
public:
    /**
     * @brief 将设备绑定到指定EventBus的处理流程中。
     * 设备将使用EventBus中的事件线程和线程池队列进行任务执行。
     */
    virtual void bindEventBus(std::shared_ptr<VehicleDomainEventBus> eventBus) = 0;

    /**
     * @brief 启动设备，设备启动之后便进入可用状态。
     * 可用前对设备的控制将被缓存，待设备启动之后立即执行。
     */
    virtual void start() = 0;

    /**
     * @brief 停止设备运行。
     * 停止设备运行后，仍可通过接口控制设备，但具体受控设备不会按要求响应。
     */
    virtual void stop() = 0;

    /**
     * @brief 返回设备的可用状态。
     */
    virtual bool available() = 0;
};


#endif