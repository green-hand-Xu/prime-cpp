#include "HornPriList.h"

using namespace std;
//***************** 模拟触发信号  ********************//
bool VMDRAlarmReq{false};
bool RKESerReq{false};

/**
 * @brief 喇叭打开
 */
void HornOn(){
    Task* Hornon = new Task(1);
    Hornon->name_ = "Hornon";
    Hornon->setAttribute(TaskAttribute::Rerun);
    Hornon->setTask([Hornon](){
        std::this_thread::sleep_for(std::chrono::milliseconds(1500));
        cout<<"喇叭打开"<<endl;
    });
    HornPriList::getInstance().scheduler.addTask(Hornon);
}

/**
 * @brief 喇叭关闭
 */
void HornOff(){
    Task* Hornoff = new Task(1);
    Hornoff->name_ = "HornOff";
    Hornoff->setAttribute(TaskAttribute::Rerun);
    Hornoff->setTask([](){
        cout<<"喇叭关闭"<<endl;
    });
    HornPriList::getInstance().scheduler.addTask(Hornoff);
}

/**
 * @brief 活体检测激活喇叭
 */
void liveHorn(){
    Task* liveHorn = new Task(3);
    liveHorn->name_ = "liveHorn";
    liveHorn->setAttribute(TaskAttribute::Abandoned);
    VMDRAlarmReq = true;
    liveHorn->setTask([liveHorn](){
        while (VMDRAlarmReq)
        {
            if (liveHorn->getStatus() == TaskStatus::INTERRUPTED)
            {
                cout<<"活体检测喇叭功能被打断"<<endl;
                return;
            }
            cout<<"live Horn Open Horn 350ms"<<endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(350));
            if (liveHorn->getStatus() == TaskStatus::INTERRUPTED)
            {
                cout<<"活体检测喇叭功能被打断"<<endl;
                return;
            }
            cout<<"live Horn Close Horn 350ms"<<endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(350));
        }
        cout<<"关闭喇叭 退出活体检测"<<endl;
    });
    HornPriList::getInstance().scheduler.addTask(liveHorn);   
}

/**
 * @brief 活体检测关闭喇叭
 */
void liveHornExit(){
    VMDRAlarmReq = false;
}

/**
 * @brief RKE寻车激活喇叭 双闪切鸣笛
 */
void RKE_Ser(){
    Task* RKEHorn = new Task(7);
    RKEHorn->name_ = "RKE_Ser";
    RKEHorn->setAttribute(TaskAttribute::Abandoned);
    RKEHorn->setTask([RKEHorn](){
        cout<<"RKE 寻车双闪鸣笛 等待中"<<endl;
        for (int i = 0; i < 102; i++)
        {
            if (RKEHorn->getStatus() == TaskStatus::INTERRUPTED)
            {
                cout<<"关闭喇叭  打断 RKE 寻车双闪鸣笛"<<endl;
                return;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
        cout<<"RKE 寻车双闪鸣笛 开始鸣笛"<<endl;
        for (int i = 0; i < 3; i++)
        {
            if (RKEHorn->getStatus() == TaskStatus::INTERRUPTED)
            {
                cout<<"关闭喇叭  打断 RKE 寻车双闪鸣笛"<<endl;
                return;
            }
            cout<<"RKE 寻车双闪鸣笛 打开喇叭"<<endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(350));
            if (RKEHorn->getStatus() == TaskStatus::INTERRUPTED)
            {
                cout<<"关闭喇叭  打断 RKE 寻车双闪鸣笛"<<endl;
                return;
            }
            cout<<"RKE 寻车双闪鸣笛 关闭喇叭"<<endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(350));
        }
    });
    HornPriList::getInstance().scheduler.addTask(RKEHorn);
}

/**
 * @brief RKE寻车终止
 */
void RKE_Stop(){
    Task* RKEStop = new Task(7);
    RKEStop->name_ = "RKE_Stop";
    RKEStop->setAttribute(TaskAttribute::Abandoned);
    RKEStop->setTask([RKEStop](){
        cout<<"RKE 寻车鸣笛关闭"<<endl;
    });
    HornPriList::getInstance().scheduler.addTask(RKEStop);
}

int main(){
    RKE_Ser(); // 7
    std::this_thread::sleep_for(std::chrono::seconds(1));
    liveHorn(); // 3
    std::this_thread::sleep_for(std::chrono::seconds(1));
    HornOn(); // 1
    std::this_thread::sleep_for(std::chrono::seconds(1));
    HornOff();// 1


    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
}