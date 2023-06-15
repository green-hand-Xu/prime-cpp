#include <vsomeip/vsomeip.hpp>
#include <iostream>
#include <iomanip>
#define Client_ID 0x0002  //客户端ID
#define Client_Instance_ID 0x0001 //客户端 instance ID

#define Rport_ClockSrv_ID 0x0001 //依赖客户端 ID
#define Rport_ClockSrv_InsID 0x0001 //依赖客户端 instance ID
#define Rport_ClockSrv_CurrentTime_Method_ID  0x0001 //依赖客户端的method ID


std::shared_ptr<vsomeip::runtime> C_runtime;  //runtime 对象
std::shared_ptr<vsomeip::application> C_application; //application 对象

void callback(vsomeip::service_t _service, vsomeip::instance_t _instance, bool _is_available){
    std::cout << "Service ["
            << std::setw(4) << std::setfill('0') << std::hex << _service << "." << _instance
            << "] is " << (_is_available ? "available." : "NOT available.")  << std::endl;
}

int main(){

    C_runtime = vsomeip::runtime::get();
    C_application = C_runtime->create_application("RemoteChargingSrv");
    C_application->init();
    C_application->offer_service(Client_ID,Client_Instance_ID);//提供服务 服务id instance id
    //注册服务可用性更改时执行的回调
    C_application->register_availability_handler(0x0001,0x0001,callback);
    //将应用程序注册为服务实例的客户端
    C_application->request_service(0x0001,0x0001);

    C_application->start();

    return 0;
}