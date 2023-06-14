#include <vsomeip/vsomeip.hpp>
#include <sstream>
#include <iomanip>
#include <iostream>

//声明一个runtime 对象
std::shared_ptr<vsomeip::runtime> ServerApp_run;
//声明一个application 对象
std::shared_ptr<vsomeip::application> ServerApp_app;

#define Service_ID 0x0001 // 服务ID
#define Service_Instance_ID 0x0001 //服务 instance ID
#define CurrentTime_Method_ID 0x0001 // CurrentTime method id

void CurrentTime(const std::shared_ptr<vsomeip_v3::message> &message){
    std::shared_ptr<vsomeip::payload> CurrentTime_payload = message->get_payload();//返回指向消息负载的指针
    vsomeip::length_t _length = CurrentTime_payload->get_length();//返回有效负载内容的长度

    //取出 payload 的内容
    std::stringstream ss;
    for (vsomeip::length_t i=0; i<_length; i++) {
       ss << std::setw(2) << std::setfill('0') << std::hex
          << (int)*(CurrentTime_payload->get_data()+i) << " ";
    }

    std::cout << "SERVICE: Received message with Client/Session ["
        << std::setw(4) << std::setfill('0') << std::hex << message->get_client() << "/"
        << std::setw(4) << std::setfill('0') << std::hex << message->get_session() << "] "
        << ss.str() << std::endl;

    //为指定的请求消息 创建响应消息
    std::shared_ptr<vsomeip::message> CurrentTime_retponse = vsomeip::runtime::get()->create_response(message);
    //创建一个空的有效负载对象。
    CurrentTime_payload = vsomeip::runtime::get()->create_payload();
    //声明一个vsomeip::byte_t 类型的vector 容器 用于放 消息内容
    std::vector<vsomeip::byte_t> CurrentTime_payload_data;
    //向容器中存放数据
    for (int i=9; i>=0; i--) {
        CurrentTime_payload_data.push_back(i);
    }
    //向payload中设置内容
    CurrentTime_payload->set_data(CurrentTime_payload_data);
    //将设置完内容的payload 放入响应消息中
    CurrentTime_retponse->set_payload(CurrentTime_payload);
    ServerApp_app->send(CurrentTime_retponse);


}

int main(){

    ServerApp_run = vsomeip::runtime::get(); //实例化 runtime对象
    ServerApp_app = ServerApp_run->create_application("ClockSrv"); //实例化 application 对象
    ServerApp_app->init();
    //注册method/event回调程序  同时设置好该method 所属的 service 以及 instance
    ServerApp_app->register_message_handler(Service_ID,Service_Instance_ID,CurrentTime_Method_ID,CurrentTime);
    ServerApp_app->offer_service(Service_ID,Service_Instance_ID);//提供服务 服务id instance id
    ServerApp_app->start();

}

