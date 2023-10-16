#ifndef __utils_deviceDef_AADevice_HPP__
#define __utils_deviceDef_AADevice_HPP__

#include <memory>
#include "BasicDevice.h"
#include "DeviceControlUnit.hpp"

template<typename ServiceT, typename ArgT>
class AADevice : public BasicDevice
{
protected:
    /**
     * @brief 执行指令的DeviceController，使用它进行命令执行。
     */
    std::shared_ptr<DeviceControlUnit<ArgT>> _deviceController{nullptr};

    /**
     * @brief 负责执行代码的
     * 
     */
    std::shared_ptr<ServiceT> _service{nullptr};

public:
    AADevice(std::shared_ptr<ServiceT> srv)
        : _service(srv){
    };

    void bindEventBus(std::shared_ptr<VehicleDomainEventBus> eventBus) override{
        _deviceController->bindEventBus(eventBus);
    }

    void start() override {
        _deviceController->start();
    }

    void stop() override {
        _deviceController->stop();
    }

    bool available() override {
        return _service->available();
    }
};



#endif