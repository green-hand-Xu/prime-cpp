#ifndef __utils_deviceDef_VehicleDeviceDomain_HPP__
#define __utils_deviceDef_VehicleDeviceDomain_HPP__

#include <list>
#include "BasicDevice.h"
#include "VehicleEventBus.hpp"


/**
 * @brief 负载划分，将设备划分到不同的区域，一个区域共用一个EventBus、一个线程池
 */
class VehicleDeviceDomain
{
public:
    std::list<BasicDevice> devices;
    std::shared_ptr<VehicleDomainEventBus> events{
        std::make_shared<VehicleDomainEventBus>(
        std::make_shared<VehicleEventBusAT>(),
        std::make_shared<VehicleEventHandlerPool>())
    };

    void add(BasicDevice& device){
        device.bindEventBus(events);
        devices.emplace_back(device);
    }

    void start(){
        for(auto it = devices.begin(); it != devices.cend(); ++it){
            it->start();
        }
    }

    void stop(){
        for(auto it = devices.begin(); it != devices.cend(); ++it){
            it->stop();
        }
    }
};

#endif