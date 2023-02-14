#include <iostream>
#include <future>
//c++ std::promise std::future
#include <thread>


struct Stu{

    int No;

}Stu1;



//模拟Pport中的method
std::future<Stu> future(){
    std::promise<Stu> ret;

    ret.set_value({1});
    return ret.get_future();
}

//模拟调用Rport的method
void ret(){
    auto ret = future();
    auto Ret = static_cast<int>(ret.get().No);
     std::cout<<Ret<<std::endl;
}

int main()
{
    std::thread t1(future);
    std::thread t2(ret);
    t1.join();
    t2.join();
	return 0;
}