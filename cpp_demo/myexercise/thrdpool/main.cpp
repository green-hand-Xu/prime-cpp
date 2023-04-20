#include <iostream>
#include "thrdpool.h"
#include "computColor.h"
#include <thread>

bool flag = true;

//动态模式颜色切换
void my_routine(/*void *context*/)                                                   
{   
    std::cout<< " 动态模式颜色切换启动 "<<std::endl;
    uint8_t i = 0;
    while (flag == true)
    {
        auto test_color = return_rgbcolor(static_cast<AtmLi_ColorSet_64_Enum>(i),colormap);
        std::cout<< static_cast<int>(i) << " ";
        print_ColorCtrl_Struct(test_color);
        ++i;
        if(i > 63){
            i = static_cast<uint8_t>(0);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(2100));
    }
    i = static_cast<uint8_t>(0);
    std::cout<<"flag == false i = "<< static_cast<int>(i) <<std::endl;               
}

//释放线程回收资源
void stopthread(std::thread& th ){
    th.join();
}

int main()                                                                         
{
    std::thread th1(my_routine);
    std::cout<<colormap.size()<<std::endl;
    getchar(); // 卡住主线程，按回车继续
    flag = false;
    stopthread(th1);
    getchar(); // 卡住主线程，按回车继续
    uint8_t a{static_cast<uint8_t>(0)};
    std::cout<<"a = "<<static_cast<int>(a);


    return 0;                                                                   
} 