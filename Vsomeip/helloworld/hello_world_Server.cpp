#include <vsomeip/vsomeip.hpp>

//声明一个runtime 对象
std::shared_ptr<vsomeip::runtime> ServerApp_run;
//声明一个application 对象
std::shared_ptr<vsomeip::application> ServerApp_app;

#define Service_ID 0x0001
#define Service_Instance_ID 0x0001 

int main(){

    ServerApp_run = vsomeip::runtime::get(); //实例化 runtime对象
    ServerApp_app = ServerApp_run->create_application("ClockSrv"); //实例化 application 对象

    ServerApp_app->init();
    ServerApp_app->offer_service(Service_ID,Service_Instance_ID);//提供服务 服务id instance id
    ServerApp_app->start();

}

