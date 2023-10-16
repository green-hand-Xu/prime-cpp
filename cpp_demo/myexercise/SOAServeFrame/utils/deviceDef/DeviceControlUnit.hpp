#ifndef __utils_deviceDef_DeviceControlUnit_HPP__
#define __utils_deviceDef_DeviceControlUnit_HPP__

#include <functional>
#include <memory>
#include <atomic>
#include <list>
#include "GA/include/data/DataValueArgs.hpp"
#include "VehicleEventBus.hpp"

/**
 * @brief 抽象设备控制单元，提供指令缓存、仲裁策略。
 */
template <typename T>
class DeviceControlUnit
{
private:
    using WorkFunction = std::function<void(const T&)>;

    WorkFunction _func{nullptr};

    std::atomic_bool _hasNewCommand{false};
    std::list<DataValueArgs<T>> _commands;

    std::shared_ptr<VehicleDomainEventBus> _events{nullptr};
    bool _isStarted{false};

public:
    DeviceControlUnit(WorkFunction func)
        : _func(func){
    }

    void bindEventBus(std::shared_ptr<VehicleDomainEventBus> eventBus){
        _events = eventBus;
        _events->eventBus->push([this](){
            threadWork();
        });
    }

    void start() {
        _isStarted = true;
    }

    void stop() {
        _isStarted = false;
    }

    void execute(DataValueArgs<T>& args){
        _hasNewCommand = true;
        _commands.emplace_back(args);
    }

    bool getCommand(DataValueArgs<T>& arg){
        if(!_hasNewCommand){
            return false;
        }

        if(_commands.size() <= 0){
            return false;
        }

        auto cmd = std::move(_commands.front());
        _commands.pop_front();

        while (_commands.size() > 0){
            auto cmd2 = std::move(_commands.front());
            _commands.pop_front();

            if(cmd2.receiveTime() < cmd.receiveTime()){
                cmd = std::move(cmd2);
            }            
        }

        arg = cmd;
        return true;
    }

private:
    void threadWork(){
        if(!_isStarted){
            return;
        }

        DataValueArgs<T> arg;
        if(!getCommand(arg)){
            return;
        }

        _events->handlerPool->push([this, arg](){
            _func(arg);
        });
    }
};



#endif