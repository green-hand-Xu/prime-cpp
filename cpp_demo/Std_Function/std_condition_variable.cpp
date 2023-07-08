#include <iostream>
#include <mutex>
#include <condition_variable>

#include <mutex>
#include <deque>
#include <iostream>
#include <thread>
#include <condition_variable>
#include <map>
#include <atomic>
/**
 * @brief 生产者消费者案例
 * 
 */
class PCModle {
 public:
  PCModle() : work_(true), max_num(30), next_index(0) {
  }
 
  void producer_thread() {
    while (work_) {
      std::this_thread::sleep_for(std::chrono::milliseconds(500));
 
      //加锁
      std::unique_lock<std::mutex> lk(cvMutex);
      //当队列未满时，继续添加数据
      cv.wait(lk, [this]() { return this->data_deque.size() <= this->max_num; });
 
      next_index++;
      data_deque.push_back(next_index);
      std::cout << "producer " << next_index << ", queue size: " << data_deque.size() << std::endl;
      //唤醒其他线程
      cv.notify_all();
      //自动释放锁
    }
  }
 
  void consumer_thread() {
    while (work_) {
      //加锁
      std::unique_lock<std::mutex> lk(cvMutex);
      //检测条件是否达成
      cv.wait(lk, [this] { return !this->data_deque.empty(); });
 
      //互斥操作，消息数据
      int data = data_deque.front();
      data_deque.pop_front();
      std::cout << "consumer " << data << ", deque size: " << data_deque.size() << std::endl;
      //唤醒其他线程
      cv.notify_all();
      //自动释放锁
    }
  }
  
 private:
  bool work_;
 
  std::mutex cvMutex;
  std::condition_variable cv;
 
  //缓存区
  std::deque<int> data_deque;
  //缓存区最大数目
  size_t max_num;
  //数据
  int next_index;
};

/**
 * @brief 生产者消费者 案例执行
 * 
 */
void consumer_producer(){
  PCModle obj;
 
  std::thread ProducerThread = std::thread(&PCModle::producer_thread, &obj);
  std::thread ConsumerThread = std::thread(&PCModle::consumer_thread, &obj);
 
  ProducerThread.join();

}

//====================模拟氛围灯动态模式线程 挨个执行  互斥线程方法 但是无法保证 排队中的线程会先执行谁=======================//
class DynMode{
public:
    DynMode(){

    }

    ~DynMode(){

    }

    void start(int ModeNo){
        stop();//结束上一次动态模式 如果有的话
        std::thread([this,ModeNo](){
            //加锁
            std::unique_lock<std::mutex> lk(DynMutex);
            //等待 动态模式标志位为 true 时，再进行启动
            Dyncv.wait(lk, [this]() { return Dynflag; });
            Dynflag == false;
            while (1)
            {
                if(DynStopflag == false){
                    break;
                }
                std::cout<<"启动氛围灯 动态模式 启动。 模式 = "<< ModeNo <<std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
            Dynflag == true;
            std::cout<<"氛围灯 动态模式 结束。 模式 = "<< ModeNo <<std::endl;
            //唤醒其他线程
            Dyncv.notify_one(); //有多个线程执行时候 无法保证 要notify 的对象是哪一个 ，排队中的线程 争抢运行是随机的
        }).detach();
    }

    //结束动态模式
    void stop(){
        DynStopflag = false;
    }


    std::mutex DynMutex;//动态模式互斥变量 最初的 mutex 对象是未加锁的
    std::condition_variable Dyncv;//动态模式条件变量

    bool Dynflag = true; //动态模式线程循环 互斥标志位
    bool DynStopflag = true;//动态模式运行标志位 true 表示 无动态模式运行
};


void simulate_DynStart(){
    std::thread([](){
        DynMode Dmode1;
        Dmode1.start(1);
        Dmode1.start(2);
        Dmode1.start(3);
    }).detach();
}

//====================模拟氛围灯动态模式线程 使用一个线程运行，改变模式后 动态改变传入参数 但是当短时间内多次进行 开关操作时 会导致启动多个线程 =======================//
class DynMode1{
public:
    DynMode1(){

    }

    ~DynMode1(){

    }

    void start(){
                std::thread([this](){
                    DynStopflag = false;//线程运行时 停止标志位为 false
                    int i = 1;
                    while (DynModeSwt) //判断动态模式开关状态
                    {
                        std::cout<<"启动氛围灯 动态模式 启动。"<<"线程id = "<<std::this_thread::get_id()<<" 模式 = "<< colormap_runtime[i]<<std::endl;
                        std::this_thread::sleep_for(std::chrono::seconds(2));
                        ++i;
                        if(i>colormap_runtime.size()){
                            i = 1;
                        }
                    }
                    DynStopflag = true; //结束循环时 将表示动态模式循环运行状态的标志位 置为 true
                    std::cout<<"氛围灯 动态模式 结束。 模式 = "<<"线程id = "<<std::this_thread::get_id()<<" 模式 = "<< colormap_runtime[i]<<std::endl;
                }).detach();
        }


    //结束动态模式
    void stop(){
        DynModeSwt = false;
    }

    bool DynStopflag = true;//动态模式运行标志位 true 表示 无动态模式运行
    bool DynModeSwt = false;//氛围灯动态模式开关状态
    std::map<int,std::string> colormap_runtime = colormap1; //运行时动态读取的 颜色色条

    //预定义的颜色色条
    std::map<int,std::string> colormap1{{1,"colormap1颜色1"},{2,"colormap1颜色2"},{3,"colormap1颜色3"},{4,"colormap1颜色4"},{5,"colormap1颜色5"},{6,"colormap1颜色6"},{7,"colormap1颜色7"}};
    std::map<int,std::string> colormap2{{1,"colormap2颜色1"},{2,"colormap2颜色2"},{3,"colormap2颜色3"},{4,"colormap2颜色4"},{5,"colormap2颜色5"},{6,"colormap2颜色6"},{7,"colormap2颜色7"}};
    std::map<int,std::string> colormap3{{1,"colormap3颜色1"},{2,"colormap3颜色2"},{3,"colormap3颜色3"},{4,"colormap3颜色4"},{5,"colormap3颜色5"},{6,"colormap3颜色6"},{7,"colormap3颜色7"}};
};

DynMode1 Dmode1;
int modeNo;


void simulate_Dyn1Start( std::map<int,std::string> colormap){
    Dmode1.DynModeSwt = true; //触发条件为动态模式ON
    Dmode1.colormap_runtime = colormap;//改变动态模式运行时读取的色条
    //判断当前动态模式线程是否在运行，运行则不再进行线程的启动
    if(!Dmode1.DynStopflag){
        return;
    }
    Dmode1.start();//启动动态模式
}

int main(){
    
    while (1)
    {
        std::cout<<"请输入动态模式色条编号'\n'1-3表示开启对应动态模式'\n'0表示关闭动态模式"<<std::endl;
        std::cin>>modeNo;
        switch (modeNo)
        {
        case 1:
            simulate_Dyn1Start(Dmode1.colormap1);
            break;
        case 2:
            simulate_Dyn1Start(Dmode1.colormap2);
            break;
        case 3:
            simulate_Dyn1Start(Dmode1.colormap3);
            break;        
        default:
            break;
        }
       
        if(modeNo == 0){
            Dmode1.stop();
            std::cout<<"动态模式结束"<<std::endl;
        }
    }
    
    return 0;
}