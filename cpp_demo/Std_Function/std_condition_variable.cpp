#include <iostream>
#include <mutex>
#include <condition_variable>

#include <mutex>
#include <deque>
#include <iostream>
#include <thread>
#include <condition_variable>
 
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
                std::cout<<"启动氛围灯 动态模式 启动。 模式 = "<< ModeNo <<std::endl;
                if(DynStopflag == false){
                    break;
                }
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


    std::mutex DynMutex;//动态模式互斥变量
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

            while (DynModeSwt) //判断动态模式开关状态
            {
                std::cout<<"启动氛围灯 动态模式 启动。"<<"线程id = "<<std::this_thread::get_id()<<" 模式 = "<< modeid <<std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(5));
            }
            std::cout<<"氛围灯 动态模式 结束。 模式 = "<< modeid <<std::endl;
        }).detach();
    }

    //结束动态模式
    void stop(){
        DynModeSwt = false;
    }


    std::mutex DynMutex;//动态模式互斥变量
    std::condition_variable Dyncv;//动态模式条件变量

    bool Dynflag = true; //动态模式线程循环 互斥标志位
    bool DynStopflag = true;//动态模式运行标志位 true 表示 无动态模式运行
    bool DynModeSwt = false;//氛围灯动态模式开关状态
    int modeid = 1;
};

DynMode1 Dmode1;
int modeNo;


void simulate_Dyn1Start(){
    Dmode1.DynModeSwt = true;
    Dmode1.start();
}

int main(){
    
    while (1)
    {
        std::cout<<"请输入动态模式色条编号'\n'1表示开启动态模式'\n'0表示关闭动态模式"<<std::endl;
        std::cin>>modeNo;
        if(modeNo == 1){
            simulate_Dyn1Start();
        }
        
        if(modeNo == 0){
            Dmode1.stop();
            std::cout<<"动态模式结束"<<std::endl;
        }
        Dmode1.modeid = modeNo;

    }
    
    return 0;
}