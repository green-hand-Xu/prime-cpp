#include <iostream>
#include <cstdint>
#include <cstring>

using HardwireOutput_Command_Integer = std::uint16_t;

enum class CPModeSet_Command_Enum : std::uint8_t {
    NoAction = 0,
    ClockwiseMode = 1,
    CounterclockwiseMode = 2,
    AlternationOfClockwiseAndCounterclockwise = 3,
    BreathingRhythmMode = 4,
    Reserved1 = 5,
    Reserved2 = 6,
    Reserved3 = 7
};

enum class WPCGangSwt_Command_Enum : std::uint8_t {
    OFF = 0,
    RainbowRhythm = 1,
    SpacetimeFlow = 2,
    InspirationalBreathing = 3,
    RedAndBlueCP = 4,
    CustomMode = 5,
    Reserved1 = 6,
    Reserved2 = 7
};

enum class S2S_Response_Enum : std::uint32_t {
    E_OK = 0,
    E_MEMORY_ERROR = 29,
    E_STORAGE_ERROR = 30,
    E_SYSTEM_RESOURCE_ERROR = 31,
    E_MIDDLEWARE_ERROR = 47,
    E_IPC_READ_ERROR = 62,
    E_IPC_WRITE_ERROR = 63,
    E_FILE_CREATE_ERROR = 72,
    E_FILE_NOT_EXIST = 73,
    E_FILE_WRITE_ERROR = 74,
    E_FILE_READ_ERROR = 75,
    E_PERSISTENCY_CREATE_ERROR = 76,
    E_PERSISTENCY_NOT_EXIST = 77,
    E_PERSISTENCY_WRITE_ERROR = 78,
    E_PERSISTENCY_READ_ERROR = 79,
    E_AUTH_ERROR = 95,
    E_EVENT_NOT_SUBSCRIBE = 96,
    E_INVALID_FIELD = 97,
    E_INVALID_ARGUMENT = 98,
    E_WORKING_CONDITION_UNFULFILLED = 99,
    E_HIGHER_PRIORITY_TASK_ONGOING = 100,
    E_FUNCTION_UNAVAILABLE = 101,
    E_INVALID_SOURCE_ID = 102,
    E_DEVICE_ABNORMAL = 103,
    E_SEQUENCE_ERROR = 104,
    E_NOTLEARNED = 105,
    E_FREQ_LIMIT = 106,
    E_CAN_BUSON = 224,
    E_CAN_BUSOFF = 225,
    E_CAN_NOT_TIMEOUT = 226,
    E_CAN_TIMEOUT = 227,
    E_CAN_E2E_OK = 228,
    E_CAN_E2E_NOT_OK = 229,
    E_UNKNOWN_ERROR = 255,
    SOMEIP_E_OK = 16777216,
    SOMEIP_E_NOT_OK = 16777217,
    SOMEIP_E_UNKNOWN_SERVICE = 16777218,
    SOMEIP_E_UNKNOWN_METHOD = 16777219,
    SOMEIP_E_NOT_READY = 16777220,
    SOMEIP_E_NOT_REACHABLE = 16777221,
    SOMEIP_E_TIMEOUT = 16777222,
    SOMEIP_E_WRONG_PROTOCAL_VERSION = 16777223,
    SOMEIP_E_WRONG_INTERFACE_VERSION = 16777224,
    SOMEIP_E_MALFORMED_MESSAGE = 16777225,
    SOMEIP_E_WRONG_MESSAGE_TYPE = 16777226,
    SOMEIP_E_E2E_REPEATED = 16777227,
    SOMEIP_E_E2E_WRONG_SEQUENCE = 16777228,
    SOMEIP_E_E2E = 16777229,
    SOMEIP_E_E2E_NOT_AVAILABLE = 16777230,
    SOMEIP_E_E2E_NO_NEW_DATA = 16777231
};

using ColorCtrl_Command_Integer = std::uint8_t;

enum class ModeSelectionCtrl_Command_Enum : std::uint8_t {
    StaticMode = 0,
    BreathingMode = 1,
    FlowingMode = 2,
    MusicMode = 3,
    DynamicMode = 4,
    RandomMode = 5,
    WelcomeMode = 6,
    FlashFrequencyMode = 7
};

enum class LightLvlCtrl_Command_Enum : std::uint8_t {
    OFF = 0,
    Lvl10 = 1,
    Lvl20 = 2,
    Lvl30 = 3,
    Lvl40 = 4,
    Lvl50 = 5,
    Lvl60 = 6,
    Lvl70 = 7,
    Lvl80 = 8,
    Lvl90 = 9,
    Lvl100 = 10,
    Reserved1 = 11,
    Reserved2 = 12,
    Reserved3 = 13,
    Reserved4 = 14,
    Reserved5 = 15
};

enum class ModeChangeCtrl_Command_Enum : std::uint8_t {
    Immediately = 0,
    NONImmediately = 1
};

using FadeTimeCtrl_Command_Integer = std::uint8_t;

enum class SyllablePrmCtrl_Command_Enum : std::uint8_t {
    NoAction = 0,
    Valid1 = 1,
    Valid2 = 2,
    Valid3 = 3,
    Valid4 = 4,
    Valid5 = 5,
    Valid6 = 6,
    Valid7 = 7
};

enum class NodeSwtCtrl_Command_Enum : std::uint8_t {
    OFF = 0,
    ON = 1
};

enum class ActvNodeCtrl_Command_Enum : std::uint8_t {
    Disable = 0,
    Enable = 1
};

struct ContourAtmLiCtrl_Struct {
    using _ActvNode1_type = ActvNodeCtrl_Command_Enum;
    _ActvNode1_type ActvNode1;

    using _ActvNode2_type = ActvNodeCtrl_Command_Enum;
    _ActvNode2_type ActvNode2;

    using _ActvNode3_type = ActvNodeCtrl_Command_Enum;
    _ActvNode3_type ActvNode3;

    using _ActvNode4_type = ActvNodeCtrl_Command_Enum;
    _ActvNode4_type ActvNode4;

    using _ActvNode5_type = ActvNodeCtrl_Command_Enum;
    _ActvNode5_type ActvNode5;

    using _ActvNode6_type = ActvNodeCtrl_Command_Enum;
    _ActvNode6_type ActvNode6;

    using _ActvNode7_type = ActvNodeCtrl_Command_Enum;
    _ActvNode7_type ActvNode7;

    using _ActvNode8_type = ActvNodeCtrl_Command_Enum;
    _ActvNode8_type ActvNode8;

    using _ActvNode9_type = ActvNodeCtrl_Command_Enum;
    _ActvNode9_type ActvNode9;

    using _ActvNode10_type = ActvNodeCtrl_Command_Enum;
    _ActvNode10_type ActvNode10;

    using _ActvNode11_type = ActvNodeCtrl_Command_Enum;
    _ActvNode11_type ActvNode11;

    using _ActvNode12_type = ActvNodeCtrl_Command_Enum;
    _ActvNode12_type ActvNode12;

    using _ActvNode13_type = ActvNodeCtrl_Command_Enum;
    _ActvNode13_type ActvNode13;

    using _ActvNode14_type = ActvNodeCtrl_Command_Enum;
    _ActvNode14_type ActvNode14;

    using _ActvNode15_type = ActvNodeCtrl_Command_Enum;
    _ActvNode15_type ActvNode15;

    using _ActvNode16_type = ActvNodeCtrl_Command_Enum;
    _ActvNode16_type ActvNode16;

    using _ActvNode17_type = ActvNodeCtrl_Command_Enum;
    _ActvNode17_type ActvNode17;

    using _ActvNode18_type = ActvNodeCtrl_Command_Enum;
    _ActvNode18_type ActvNode18;

    using _ActvNode19_type = ActvNodeCtrl_Command_Enum;
    _ActvNode19_type ActvNode19;

    using _ActvNode20_type = ActvNodeCtrl_Command_Enum;
    _ActvNode20_type ActvNode20;

    using _ActvNode21_type = ActvNodeCtrl_Command_Enum;
    _ActvNode21_type ActvNode21;

    using _ActvNode22_type = ActvNodeCtrl_Command_Enum;
    _ActvNode22_type ActvNode22;

    using _ActvNode23_type = ActvNodeCtrl_Command_Enum;
    _ActvNode23_type ActvNode23;

    using _ActvNode24_type = ActvNodeCtrl_Command_Enum;
    _ActvNode24_type ActvNode24;

    using _ActvNode1_NF_type = ActvNodeCtrl_Command_Enum;
    _ActvNode1_NF_type ActvNode1_NF;

    using _ActvNode2_NF_type = ActvNodeCtrl_Command_Enum;
    _ActvNode2_NF_type ActvNode2_NF;

    using _ActvNode3_NF_type = ActvNodeCtrl_Command_Enum;
    _ActvNode3_NF_type ActvNode3_NF;

    using _ActvNode4_NF_type = ActvNodeCtrl_Command_Enum;
    _ActvNode4_NF_type ActvNode4_NF;

    using _ActvNode5_NF_type = ActvNodeCtrl_Command_Enum;
    _ActvNode5_NF_type ActvNode5_NF;

    using _ActvNode6_NF_type = ActvNodeCtrl_Command_Enum;
    _ActvNode6_NF_type ActvNode6_NF;

    using _ActvNode7_NF_type = ActvNodeCtrl_Command_Enum;
    _ActvNode7_NF_type ActvNode7_NF;

    using _ActvNode8_NF_type = ActvNodeCtrl_Command_Enum;
    _ActvNode8_NF_type ActvNode8_NF;

    using _ActvNode9_NF_type = ActvNodeCtrl_Command_Enum;
    _ActvNode9_NF_type ActvNode9_NF;

    using _ActvNode10_NF_type = ActvNodeCtrl_Command_Enum;
    _ActvNode10_NF_type ActvNode10_NF;

    using _ActvNode11_NF_type = ActvNodeCtrl_Command_Enum;
    _ActvNode11_NF_type ActvNode11_NF;

    using _ActvNode12_NF_type = ActvNodeCtrl_Command_Enum;
    _ActvNode12_NF_type ActvNode12_NF;

    using _ActvNode13_NF_type = ActvNodeCtrl_Command_Enum;
    _ActvNode13_NF_type ActvNode13_NF;

    using _ActvNode14_NF_type = ActvNodeCtrl_Command_Enum;
    _ActvNode14_NF_type ActvNode14_NF;

    using _ActvNode15_NF_type = ActvNodeCtrl_Command_Enum;
    _ActvNode15_NF_type ActvNode15_NF;

    using _ActvNode16_NF_type = ActvNodeCtrl_Command_Enum;
    _ActvNode16_NF_type ActvNode16_NF;

    using _ActvNode17_NF_type = ActvNodeCtrl_Command_Enum;
    _ActvNode17_NF_type ActvNode17_NF;

    using _ActvNode18_NF_type = ActvNodeCtrl_Command_Enum;
    _ActvNode18_NF_type ActvNode18_NF;

    using _ActvNode19_NF_type = ActvNodeCtrl_Command_Enum;
    _ActvNode19_NF_type ActvNode19_NF;

    using _ActvNode20_NF_type = ActvNodeCtrl_Command_Enum;
    _ActvNode20_NF_type ActvNode20_NF;

    using _ActvNode21_NF_type = ActvNodeCtrl_Command_Enum;
    _ActvNode21_NF_type ActvNode21_NF;

    using _ActvNode22_NF_type = ActvNodeCtrl_Command_Enum;
    _ActvNode22_NF_type ActvNode22_NF;

    using _ActvNode23_NF_type = ActvNodeCtrl_Command_Enum;
    _ActvNode23_NF_type ActvNode23_NF;

    using _ActvNode24_NF_type = ActvNodeCtrl_Command_Enum;
    _ActvNode24_NF_type ActvNode24_NF;

    using _NodeSwtCtrl_type = NodeSwtCtrl_Command_Enum;
    _NodeSwtCtrl_type NodeSwtCtrl;

    using _NodeSwtCtrl_NF_type = NodeSwtCtrl_Command_Enum;
    _NodeSwtCtrl_NF_type NodeSwtCtrl_NF;

    using _SyllablePrmCtrl_type = SyllablePrmCtrl_Command_Enum;
    _SyllablePrmCtrl_type SyllablePrmCtrl;

    using _SyllablePrmCtrl_NF_type = SyllablePrmCtrl_Command_Enum;
    _SyllablePrmCtrl_NF_type SyllablePrmCtrl_NF;

    using _FadeTimeCtrl_type = FadeTimeCtrl_Command_Integer;
    _FadeTimeCtrl_type FadeTimeCtrl;

    using _FadeTimeCtrl_NF_type = FadeTimeCtrl_Command_Integer;
    _FadeTimeCtrl_NF_type FadeTimeCtrl_NF;

    using _ModeChangeCtrl_type = ModeChangeCtrl_Command_Enum;
    _ModeChangeCtrl_type ModeChangeCtrl;

    using _ModeChangeCtrl_NF_type = ModeChangeCtrl_Command_Enum;
    _ModeChangeCtrl_NF_type ModeChangeCtrl_NF;

    using _LightLvlCtrl_type = LightLvlCtrl_Command_Enum;
    _LightLvlCtrl_type LightLvlCtrl;

    using _LightLvlCtrl_NF_type = LightLvlCtrl_Command_Enum;
    _LightLvlCtrl_NF_type LightLvlCtrl_NF;

    using _ModeSelectionCtrl_type = ModeSelectionCtrl_Command_Enum;
    _ModeSelectionCtrl_type ModeSelectionCtrl;

    using _ModeSelectionCtrl_NF_type = ModeSelectionCtrl_Command_Enum;
    _ModeSelectionCtrl_NF_type ModeSelectionCtrl_NF;

    using _RedRatCtrl_type = ColorCtrl_Command_Integer;
    _RedRatCtrl_type RedRatCtrl;

    using _RedRatCtrl_NF_type = ColorCtrl_Command_Integer;
    _RedRatCtrl_NF_type RedRatCtrl_NF;

    using _GreenRatCtrl_type = ColorCtrl_Command_Integer;
    _GreenRatCtrl_type GreenRatCtrl;

    using _GreenRatCtrl_NF_type = ColorCtrl_Command_Integer;
    _GreenRatCtrl_NF_type GreenRatCtrl_NF;

    using _BlueRatCtrl_type = ColorCtrl_Command_Integer;
    _BlueRatCtrl_type BlueRatCtrl;

    using _BlueRatCtrl_NF_type = ColorCtrl_Command_Integer;
    _BlueRatCtrl_NF_type BlueRatCtrl_NF;

};

//*********  以上是数据类型  **************************//

const int ActvNodeSize = 48;

class Context
{    
public:
    //*内部存储的节点使能信息
    uint8_t context_ActvNodeCtrl[ActvNodeSize];
    ContourAtmLiCtrl_Struct contourLightSt;

    void setContext_ActvNodeCtrl(uint8_t* actv){
        uint8_t* head = actv;//获取结构体存储首地址
        auto tail = head+ActvNodeSize*sizeof(uint8_t);//获取结构体存储尾地址
        auto rtail = context_ActvNodeCtrl+ActvNodeSize*sizeof(uint8_t);
        int idx = 0;
        for(auto i = head,r = context_ActvNodeCtrl; i<tail && r<rtail;i++,r++){
            *r = *i;
        }
    }

    //* 注意返回的是数组首地址指针， 不能直接赋值给其他数组
    auto getContext_ActvNodeCtrl(){
        return context_ActvNodeCtrl;
    }

    uint8_t* ResetNodeToAllZero(uint8_t* actv){
        uint8_t* head = actv;//获取结构体存储首地址
        auto tail = head+ActvNodeSize*sizeof(uint8_t);//获取结构体存储尾地址

        for(auto i = head ; i<tail;i++){
            *i =0u;
        }
        return head;
    }

    uint8_t* SetNodeToAllOpen(uint8_t* actv){
        uint8_t* head = actv;//获取结构体存储首地址
        auto tail = head+ActvNodeSize*sizeof(uint8_t);//获取结构体存储尾地址

        for(auto i = head ; i<tail;i++){
            *i =1u;
        }
        return head;
    }

    uint8_t* SetSignalNode(int No , int status ,uint8_t* ActvNodeStruct){
        uint8_t* head = ActvNodeStruct;//获取结构体存储首地址
        auto index = head+No-1;//对应的 结构体中 元素位置
        *index = (uint8_t)(status);
        return ActvNodeStruct;
    }

    void printActvNode(uint8_t* actv){
        uint8_t* head = actv;//获取结构体存储首地址
        int idx = 1;
        for (auto i = head; i < head+(ActvNodeSize)*sizeof(uint8_t); i++)
        {
            std::cout<<idx<<" 号使能节点值 =  "<<static_cast<int>(*i)<<std::endl;
            idx ++;
        }
    }

    void setActvNode(uint8_t actvNode[ActvNodeSize]){
        auto ActvNodeIndex = (ActvNodeCtrl_Command_Enum *)(&contourLightSt);    
        memcpy(ActvNodeIndex,actvNode,ActvNodeSize*sizeof(ActvNodeCtrl_Command_Enum));

        uint8_t* head = (uint8_t *)&contourLightSt;//获取结构体存储首地址
        int idx = 1;
        for (auto i = head; i < head+sizeof(contourLightSt)/sizeof(uint8_t); i++)
        {
            std::cout<<idx<<" 号使能节点值 =  "<<static_cast<int>(*i)<<std::endl;
            idx ++;
        }
    }
};

int main(){
    uint8_t context_ActvNodeCtrl_NF[ActvNodeSize];
    Context con;

    //拿出存储的节点信息
    memcpy(context_ActvNodeCtrl_NF,con.getContext_ActvNodeCtrl(),sizeof(context_ActvNodeCtrl_NF));
    //临时节点信息全关
    con.ResetNodeToAllZero(context_ActvNodeCtrl_NF);
    con.printActvNode(context_ActvNodeCtrl_NF);
    std::cout<<std::endl;

    //临时节点信息全开
    con.SetNodeToAllOpen(context_ActvNodeCtrl_NF);
    con.printActvNode(context_ActvNodeCtrl_NF);
    std::cout<<std::endl;

    //存储临时信息回本地
    con.setContext_ActvNodeCtrl(context_ActvNodeCtrl_NF);
    con.printActvNode(con.getContext_ActvNodeCtrl());
    std::cout<<std::endl;

    //单个设置值
    con.SetSignalNode(2,0,context_ActvNodeCtrl_NF);
    con.printActvNode(context_ActvNodeCtrl_NF);
    // con.setActvNode(context_ActvNodeCtrl_NF);
    std::cout<<std::endl;

    return 0;
}


