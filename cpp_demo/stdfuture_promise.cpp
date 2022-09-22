#include <iostream>
#include <future>
//c++ std::promise std::future
#include <thread>

//模拟Pport中的method
std::future<char*> future(){
    std::promise<char*> ret;
    //
    //
    
    ret.set_value("OK");
    return ret.get_future();
}

//模拟调用Rport的method
void ret(){
    auto ret = future();
    std::cout<<ret.get()<<std::endl;
}

int main()
{
    std::thread t1(future);
    std::thread t2(ret);
    t1.join();
    t2.join();
	return 0;
}