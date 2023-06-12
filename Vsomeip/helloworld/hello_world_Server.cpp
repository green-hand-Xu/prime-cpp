#include <vsomeip/vsomeip.hpp>

//声明一个runtime 对象
std::shared_ptr<vsomeip::runtime> ServerApp_run;
//声明一个application 对象
std::shared_ptr<vsomeip::application> ServerApp_app;

int main(){

    ServerApp_run = vsomeip::runtime::get(); //实例化 runtime对象
    ServerApp_app = ServerApp_run->create_application("ClockSrv"); //实例化 application 对象

    ServerApp_app->init();
    ServerApp_app->offer_service(1,1);
    ServerApp_app->start();

}

