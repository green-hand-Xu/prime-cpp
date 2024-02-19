#include <iomanip>
#include <iostream>
#include <condition_variable>
#include <vsomeip/vsomeip.hpp>
#include <thread>
#include <vsomeip/internal/logger.hpp>

#define SAMPLE_SERVICE_ID 0x1234
#define SAMPLE_INSTANCE_ID 0x5678
#define SAMPLE_METHOD_ID 0x0421


std::shared_ptr< vsomeip::application > app;

std::mutex mutex;
std::condition_variable condition;

/**
 * @brief 服务请求
 * 创建请求报文 放入请求消息字段后发送
 */
void run_request() {
  if (!app->is_available(SAMPLE_SERVICE_ID,SAMPLE_INSTANCE_ID))
  {
    VSOMEIP_INFO<<"[SAMPLE_SERVICE_ID,SAMPLE_INSTANCE_ID] 服务状态不可用";
  }
  
  std::unique_lock<std::mutex> its_lock(mutex);
  condition.wait(its_lock);

  std::shared_ptr< vsomeip::message > request;
  request = vsomeip::runtime::get()->create_request();
  request->set_service(SAMPLE_SERVICE_ID);
  request->set_instance(SAMPLE_INSTANCE_ID);
  request->set_method(SAMPLE_METHOD_ID);

  std::shared_ptr< vsomeip::payload > its_payload = vsomeip::runtime::get()->create_payload();

  //* 设置请求消息内容（入参内容）
  std::vector<vsomeip::byte_t> its_payload_data;
  std::string str = "Hello World";

  auto start = (uint8_t *)str.data();
  auto end = str.size();
  for (auto i = 0; i < end; i++)
  {
      its_payload_data.push_back(*(start+i));
  }

  its_payload->set_data(its_payload_data);
  request->set_payload(its_payload);
  app->send(request);
}

/**
 * @brief 设置处理请求回复报文的回调函数
 * @param _response 
 */
void request_ret_handler(const std::shared_ptr<vsomeip::message> &_response) {

  std::shared_ptr<vsomeip::payload> its_payload = _response->get_payload();
  vsomeip::length_t l = its_payload->get_length();

  //* 2、解析 payload 内容
  std::stringstream ss;
  ss <<its_payload->get_data();
  std::cout << "CLIENT: 收到来自 Client/Session ["
      << _response->get_client() << "/"
      << _response->get_session() << "] 的回复，内容为 ["
      << ss.str() <<" ]"<< std::endl;
}

//*服务可用性变化时的回调
void on_availability(vsomeip::service_t _service, vsomeip::instance_t _instance, bool _is_available) {
    std::cout<<"Service [ "<< _service <<" ]"<<" Instance [ "<<_instance<<" ]"<<" _is_available [ "<<(_is_available ? "true" : "false")<<" ]"<<std::endl;
    condition.notify_one();//检测到服务后 激活请求操作
}

int main() {

    app = vsomeip::runtime::get()->create_application("Hello");
    app->init();
    //* 设置服务可用性回调函数
    app->register_availability_handler(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, on_availability);
    //* 添加依赖服务
    app->request_service(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID);
    //* 创建接收请求回复的回调函数
    app->register_message_handler(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, SAMPLE_METHOD_ID, request_ret_handler);
    //* 启动线程 进行请求操作（应为start后不会返回任何结果，阻塞住主线程，因此需要异步请求）
    std::thread sender(run_request);
    app->start();
}