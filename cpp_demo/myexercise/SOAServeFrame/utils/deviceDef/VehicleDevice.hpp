#ifndef __utils_deviceDef_VehicleDevice_HPP__
#define __utils_deviceDef_VehicleDevice_HPP__

#include <list>
#include "VehicleEventBus.hpp"
#include "BasicDevice.h"

#include "VehicleServiceDomain.hpp"

/**
 * @brief 整车接口定义
 */
class VehicleDevice
{
private:
    VehicleServiceDomain _veh;
    VehicleServiceDomain _BD;
    VehicleServiceDomain _PT;

public:
    void start(){
        _veh.start();
        _BD.start();
        _PT.start();
    }

    void stop(){
        _veh.stop();
        _BD.stop();
        _PT.stop();
    }
};

#endif