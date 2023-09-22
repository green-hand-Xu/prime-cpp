#include <mutex>
#include <iostream>
#include <thread>
#include <condition_variable>
#include <atomic>

std::mutex m;
std::condition_variable cv;
std::string data;
bool ready = false;
bool processed = false;
int VCU_ST;
int VCU_ST_TMP{-1};
int PowerMode;

//两侧转向灯均未点亮时动力运行点亮日间灯激活状态
bool DayRunngLmpSts_0{false};
//两侧转向灯均未点亮时远程泊车点亮日间灯激活状态
bool DayRunngLmpSts_1{false};
//左侧转向灯点亮右侧未点亮动力运行点亮日间灯激活状态
bool DayRunngLmpSts_2{false};

//左侧转向灯点亮右侧未点亮远程泊车点亮日间灯激活状态
bool DayRunngLmpSts_3{false};
//左侧转向灯未点亮右侧点亮动力运行点亮日间灯激活状态
bool DayRunngLmpSts_4{false};
//左侧转向灯未点亮右侧点亮远程泊车点亮日间灯激活状态
bool DayRunngLmpSts_5{false};

int DayRunngLmpNo{-1};

std::pair<bool,bool> DayRunLight{false,false};

//执行打开日行灯操作
void action(bool left, bool right){
    std::cout<<" 打开日行灯 left = "<<left <<" right = "<<right<<std::endl;
}

void Update_DayRunngLmpNo(){
    if (DayRunngLmpSts_0)
    {
        DayRunngLmpNo = 0;
    }

    if (DayRunngLmpSts_1)
    {
        DayRunngLmpNo = 1;
    }

    if (DayRunngLmpSts_2)
    {
        DayRunngLmpNo = 2;
    }

    if (DayRunngLmpSts_3)
    {
        DayRunngLmpNo = 3;
    }

    if (DayRunngLmpSts_4)
    {
        DayRunngLmpNo = 4;
    }

    if (DayRunngLmpSts_5)
    {
        DayRunngLmpNo = 5;
    }
    
}

//* 工作线程
void worker_thread()
{
    while (1)
    {
        std::unique_lock<std::mutex> lk(m);
        //子进程的中wait函数对互斥量进行解锁，同时线程进入阻塞或者等待状态。
        cv.wait(lk, []{
            return ready;
        }); 

        auto [lastL,lastR] = DayRunLight;


        switch (DayRunngLmpNo)
        {
        case 0:
            if (lastL && lastR)
            {
                break;
            }
            DayRunLight = {true,true};
            action(true,true);
            break;
        
        case 1:
            if (lastL && lastR)
            {
                break;
            }
            DayRunLight = {true,true};
            action(true,true);
            break;

        case 2:
            if (!lastL && lastR)
            {
                break;
            }
            DayRunLight = {false,true};
            action(false,true);
            break;

        case 3:
            if (!lastL && lastR)
            {
                break;
            }
            DayRunLight = {false,true};
            action(false,true);
            break;

        case 4:
            if (lastL && !lastR)
            {
                break;
            }
            DayRunLight = {true,false};;
            action(true,false);
            break;

        case 5:
            if (lastL && !lastR)
            {
                break;
            }
            DayRunLight = {true,false};
            action(true,false);
            break;
        default:
            break;
        }

        ready = false;
        lk.unlock();
        cv.notify_one();
    }
}

//* 监听VCU_St 状态并进行触发 (动力运行点亮)
void On_VCU_ST(){
    while (1)
    {
        if (VCU_ST != 6 && VCU_ST!=12 && (PowerMode == 2 || PowerMode == 3 || PowerMode == 5)) //触发源关系是 & 因此VCU_ST和电源都要检查
        {
            if(VCU_ST_TMP != VCU_ST){
                auto temp = VCU_ST;
                std::this_thread::sleep_for(std::chrono::seconds(2));
                if (temp == VCU_ST)
                {
                    VCU_ST_TMP = VCU_ST;
                    if (std::unique_lock<std::mutex> unilock(m);true /* 判断前提条件是否成立 */)
                    {
                        //*设定好日行灯状态
                        Update_DayRunngLmpNo();
                        ready = true;
                        unilock.unlock();
                        cv.notify_one();
                    }
                }else{
                    continue;
                }   
            }else{
                    if (std::unique_lock<std::mutex> unilock(m);true /* 判断前提条件是否成立 */)
                    {
                        //*设定好日行灯状态
                        Update_DayRunngLmpNo();
                        ready = true;
                        unilock.unlock();
                        cv.notify_one();
                    }
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    
}

//* 监听电源状态并进行触发 (动力运行点亮)
void On_SysPwr(int PowerSt){
    //触发源关系是 & 因此VCU_ST和电源都要检查
    if (std::unique_lock<std::mutex> unilock(m);PowerSt == 2 ||PowerSt == 3 || PowerSt == 5 || true/*前提条件满足*/ &&(VCU_ST != 6 && VCU_ST!=12))
    {
        PowerMode = PowerSt;
        //*设定好日行灯状态
        Update_DayRunngLmpNo();
        ready = true;
        std::cout<<" 电源触发打开日行灯 "<<std::endl;
        unilock.unlock();
        cv.notify_one();
    }
}

void Set_VCU_ST(int St){
    // send data to the worker thread
    std::lock_guard<std::mutex> lk(m);
    VCU_ST_TMP = VCU_ST;
    VCU_ST = St;
    std::cout << "VCU_ST 状态被修改为: "<<St<< " VCU_ST_TMP 状态被修改为: "<<VCU_ST_TMP<<std::endl;
}

void setDayRunngLmpSt(int No,bool St){
    switch (No)
    {
    case 0:
        DayRunngLmpSts_0 = St;
        DayRunngLmpSts_1 = false;
        DayRunngLmpSts_2 = false;
        DayRunngLmpSts_3 = false;
        DayRunngLmpSts_4 = false;
        DayRunngLmpSts_5 = false;
        break;

    case 1:
        DayRunngLmpSts_0 = false;
        DayRunngLmpSts_1 = St;
        DayRunngLmpSts_2 = false;
        DayRunngLmpSts_3 = false;
        DayRunngLmpSts_4 = false;
        DayRunngLmpSts_5 = false;
        break;

    case 2:
        DayRunngLmpSts_0 = false;
        DayRunngLmpSts_1 = false;
        DayRunngLmpSts_2 = St;
        DayRunngLmpSts_3 = false;
        DayRunngLmpSts_4 = false;
        DayRunngLmpSts_5 = false;
        break;

    case 3:
        DayRunngLmpSts_0 = false;
        DayRunngLmpSts_1 = false;
        DayRunngLmpSts_2 = false;
        DayRunngLmpSts_3 = St;
        DayRunngLmpSts_4 = false;
        DayRunngLmpSts_5 = false;
        break;

    case 4:
        DayRunngLmpSts_0 = false;
        DayRunngLmpSts_1 = false;
        DayRunngLmpSts_2 = false;
        DayRunngLmpSts_3 = false;
        DayRunngLmpSts_4 = St;
        DayRunngLmpSts_5 = false;
        break;

    case 5:
        DayRunngLmpSts_0 = false;
        DayRunngLmpSts_1 = false;
        DayRunngLmpSts_2 = false;
        DayRunngLmpSts_3 = false;
        DayRunngLmpSts_4 = false;
        DayRunngLmpSts_5 = St;
        break;
    default:
        break;
    }

}

void Test_1(){
    while (1)
    {
        int No;
        std::cout<<" 1.设置 VCU_ST 2.设置 电源模式 3.设置左右转向灯状态"<<std::endl;
        std::cin >> No;
        switch (No)
        {
        case 1:
        {
            int St;
            std::cout<<" 输入要设置的 VCU_ST 状态"<<std::endl;
            std::cin>>St;
            Set_VCU_ST(St);
        }
            break;

        case 2:
        {
            int St;
            std::cout<<" 输入要设置的 电源 状态"<<std::endl;
            std::cin>>St;
            On_SysPwr(St);
        }
            break;

        case 3:
        {
            bool St;
            int No;
            std::cout<<" 输入要设置的 左右转向灯内部量编号"<<std::endl;
            std::cin>>No;
            std::cout<<" 输入要设置的 左右转向灯内部量状态"<<std::endl;
            std::cin>>St;
            setDayRunngLmpSt(No,St);
        }
            break;
        default:
            break;
        }
    }
    

}

int main(){
    std::thread worker(worker_thread);
    std::thread worker1(On_VCU_ST);
    std::tuple<bool,bool> tupl{true,true};

    Test_1();

    return 0;
}