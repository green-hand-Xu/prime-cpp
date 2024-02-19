/**
 * @file hello_world_Server.cpp
 * @author XuYingBo (you@domain.com)
 * @brief Vsomeip 服务端示例代码
 * TODO 当入参为多个值时，应如何进行入参类型转回？
 * @version 0.1
 * @date 2024-02-19
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iomanip>
#include <iostream>
#include <sstream>
#include <algorithm>

#include <vsomeip/vsomeip.hpp>
#include <vsomeip/internal/logger.hpp>
#define SAMPLE_SERVICE_ID 0x1234
#define SAMPLE_INSTANCE_ID 0x5678
#define SAMPLE_METHOD_ID 0x0421

std::shared_ptr< vsomeip::application > app;

/**
 * @brief 该函数被server端注册为 method 类型的接口
 * 
 * @param _request 
 */
void get_message(const std::shared_ptr<vsomeip::message> &_request) {
    //* 1、获取请求消息中的 payload 字段
    std::shared_ptr<vsomeip::payload> its_payload = _request->get_payload();
    vsomeip::length_t l = its_payload->get_length();

    //* 2、解析 payload 内容
    std::stringstream ss;
    ss << its_payload->get_data(); // 该请求内容的格式应是提前定义好的接口入参。

    std::cout << "SERVICE: 收到来自 Client/Session ["<< _request->get_client() << "/"<< _request->get_session() 
        << "] 的调用,内容为: [" << ss.str() <<" ]"<< std::endl;

    //* 3、基于请求消息字段相关属性，创建一条用于回复的消息对象。
    std::shared_ptr<vsomeip::message> its_response = vsomeip::runtime::get()->create_response(_request);

    //* 4、创建 空的 payload 对象 
    its_payload = vsomeip::runtime::get()->create_payload();

    //* 5、设置回复消息内容
    std::vector<vsomeip::byte_t> its_payload_data;
    std::string str = "hello world";
    auto start = str.data();
    auto end = str.size();
    for (auto i = 0; i < end; i++)
    {
        its_payload_data.push_back(*(start+i));
    }

    //* 6、设置 payload 内容
    its_payload->set_data(its_payload_data); // "hello world"

    //* 7、将设置好内容的 payload 放入用于回复的消息对象中
    its_response->set_payload(its_payload);

    //* 8、发送回复消息报文
    app->send(its_response);
}

int main() {
    app = vsomeip::runtime::get()->create_application("World");
    app->init();
    app->register_message_handler(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, SAMPLE_METHOD_ID, get_message);
    //提供服务前 初始化完毕，并注册好所有提供出去的接口信息
    app->offer_service(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID);
    app->start();
}