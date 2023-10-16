#ifndef __utils_deviceDef_VehicleEventBus_HPP__
#define __utils_deviceDef_VehicleEventBus_HPP__

#include <list>
#include "folly/FunctionScheduler.hpp"
#include "AsyncTimer.hpp"
#include "CTPL/ctpl_stl.h"

using EventHandler = std::function<void()>;

/**
 * @brief Basic concept of a event bus.
 */
class VehicleEventBus
{
public:
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void push(EventHandler func) = 0;
};

/**
 * @brief Event bus for a vehicle domain,
 *        which include an event bus and a thred pool.
 */
struct VehicleDomainEventBus{
    std::shared_ptr<VehicleEventBus> eventBus{nullptr};
    std::shared_ptr<VehicleEventBus> handlerPool{nullptr};
};

/**
 * @brief Event bus instances.
 */

class VehicleEventHandlerPool : public VehicleEventBus
{
    ctpl::thread_pool _pool{15};

public:
    void start() override{

    }

    void stop() override{

    }

    void push(EventHandler func) override{
        _pool.push([func](auto){func();});
    }
};

class VehicleEventBusFS : public VehicleEventBus
{
private:
    folly::FunctionScheduler _events;

public:
    void start() override{
        _events.start();
    }

    void stop() override{
        _events.shutdown();
    }

    void push(EventHandler func) override{
        _events.addFunctionOnce(std::move(func), std::string(), 50ms);
    }
};

class VehicleEventBusAT :public VehicleEventBus
{
private:
    std::list<EventHandler> _events;
    std::shared_ptr<AsyncTimer> _timer{nullptr};

public:
    void start() override{
        if(_timer){
            return;
        }

        _timer = std::make_shared<AsyncTimer>(50ms, [this](auto arg){busWork(arg);});
    }

    void stop() override{
        if(!_timer){
            return;
        }
        _timer = nullptr;
    }

    void push(EventHandler func) override {
        _events.emplace_back(func);
    }

    void busWork(AsyncTimer::TaskArg& arg){
        while (_events.size() > 0)
        {
            auto func = std::move(_events.front());
            _events.pop_back();
            func();
        }
    }
};


#endif