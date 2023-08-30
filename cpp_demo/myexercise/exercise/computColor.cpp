/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  Copyright (c) 2022 by Gwm. All rights reserved.
 *********************************************************************************************************************/

#ifndef _ALCMCLRSETHMISRV_GS2S_DATATYPES_HPP_
#define _ALCMCLRSETHMISRV_GS2S_DATATYPES_HPP_

#include <cstdint>
#include <thread>
#include <bitset>
namespace GWM{
namespace Vehicle{
namespace Body{
namespace ALCM{
namespace GS2S{
namespace ALCMClrSetHMISrv_GS2S{
namespace ALCMClrSetHMISrv_GS2S_Gen{


enum class ClrSet_Enum : std::uint8_t {
    Colour_0 = 0,
    Colour_1 = 1,
    Colour_2 = 2,
    Colour_3 = 3,
    Colour_4 = 4,
    Colour_5 = 5,
    Colour_6 = 6,
    Colour_7 = 7,
    Colour_8 = 8,
    Colour_9 = 9,
    Colour_10 = 10,
    Colour_11 = 11,
    Colour_12 = 12,
    Colour_13 = 13,
    Colour_14 = 14,
    Colour_15 = 15,
    Colour_16 = 16,
    Colour_17 = 17,
    Colour_18 = 18,
    Colour_19 = 19,
    Colour_20 = 20,
    Colour_21 = 21,
    Colour_22 = 22,
    Colour_23 = 23,
    Colour_24 = 24,
    Colour_25 = 25,
    Colour_26 = 26,
    Colour_27 = 27,
    Colour_28 = 28,
    Colour_29 = 29,
    Colour_30 = 30,
    Colour_31 = 31,
    Colour_32 = 32,
    Colour_33 = 33,
    Colour_34 = 34,
    Colour_35 = 35,
    Colour_36 = 36,
    Colour_37 = 37,
    Colour_38 = 38,
    Colour_39 = 39,
    Colour_40 = 40,
    Colour_41 = 41,
    Colour_42 = 42,
    Colour_43 = 43,
    Colour_44 = 44,
    Colour_45 = 45,
    Colour_46 = 46,
    Colour_47 = 47,
    Colour_48 = 48,
    Colour_49 = 49,
    Colour_50 = 50,
    Colour_51 = 51,
    Colour_52 = 52,
    Colour_53 = 53,
    Colour_54 = 54,
    Colour_55 = 55,
    Colour_56 = 56,
    Colour_57 = 57,
    Colour_58 = 58,
    Colour_59 = 59,
    Colour_60 = 60,
    Colour_61 = 61,
    Colour_62 = 62,
    Colour_63 = 63,
    NoAction = 64,
    Reserved1 = 65,
    Reserved2 = 66,
    Reserved3 = 67,
    Reserved4 = 68,
    Reserved5 = 69,
    Reserved6 = 70,
    Reserved7 = 71,
    Reserved8 = 72,
    Reserved9 = 73,
    Reserved10 = 74,
    Reserved11 = 75,
    Reserved12 = 76,
    Reserved13 = 77,
    Reserved14 = 78,
    Reserved15 = 79,
    Reserved16 = 80,
    Reserved17 = 81,
    Reserved18 = 82,
    Reserved19 = 83,
    Reserved20 = 84,
    Reserved21 = 85,
    Reserved22 = 86,
    Reserved23 = 87,
    Reserved24 = 88,
    Reserved25 = 89,
    Reserved26 = 90,
    Reserved27 = 91,
    Reserved28 = 92,
    Reserved29 = 93,
    Reserved30 = 94,
    Reserved31 = 95,
    Reserved32 = 96,
    Reserved33 = 97,
    Reserved34 = 98,
    Reserved35 = 99,
    Reserved36 = 100,
    Reserved37 = 101,
    Reserved38 = 102,
    Reserved39 = 103,
    Reserved40 = 104,
    Reserved41 = 105,
    Reserved42 = 106,
    Reserved43 = 107,
    Reserved44 = 108,
    Reserved45 = 109,
    Reserved46 = 110,
    Reserved47 = 111,
    Reserved48 = 112,
    Reserved49 = 113,
    Reserved50 = 114,
    Reserved51 = 115,
    Reserved52 = 116,
    Reserved53 = 117,
    Reserved54 = 118,
    Reserved55 = 119,
    Reserved56 = 120,
    Reserved57 = 121,
    Reserved58 = 122,
    Reserved59 = 123,
    Reserved60 = 124,
    Reserved61 = 125,
    Reserved62 = 126,
    Reserved63 = 127
};

enum class AtmLi_ColorSet_64_Enum : std::uint8_t {
    Colour_0 = 0,
    Colour_1 = 1,
    Colour_2 = 2,
    Colour_3 = 3,
    Colour_4 = 4,
    Colour_5 = 5,
    Colour_6 = 6,
    Colour_7 = 7,
    Colour_8 = 8,
    Colour_9 = 9,
    Colour_10 = 10,
    Colour_11 = 11,
    Colour_12 = 12,
    Colour_13 = 13,
    Colour_14 = 14,
    Colour_15 = 15,
    Colour_16 = 16,
    Colour_17 = 17,
    Colour_18 = 18,
    Colour_19 = 19,
    Colour_20 = 20,
    Colour_21 = 21,
    Colour_22 = 22,
    Colour_23 = 23,
    Colour_24 = 24,
    Colour_25 = 25,
    Colour_26 = 26,
    Colour_27 = 27,
    Colour_28 = 28,
    Colour_29 = 29,
    Colour_30 = 30,
    Colour_31 = 31,
    Colour_32 = 32,
    Colour_33 = 33,
    Colour_34 = 34,
    Colour_35 = 35,
    Colour_36 = 36,
    Colour_37 = 37,
    Colour_38 = 38,
    Colour_39 = 39,
    Colour_40 = 40,
    Colour_41 = 41,
    Colour_42 = 42,
    Colour_43 = 43,
    Colour_44 = 44,
    Colour_45 = 45,
    Colour_46 = 46,
    Colour_47 = 47,
    Colour_48 = 48,
    Colour_49 = 49,
    Colour_50 = 50,
    Colour_51 = 51,
    Colour_52 = 52,
    Colour_53 = 53,
    Colour_54 = 54,
    Colour_55 = 55,
    Colour_56 = 56,
    Colour_57 = 57,
    Colour_58 = 58,
    Colour_59 = 59,
    Colour_60 = 60,
    Colour_61 = 61,
    Colour_62 = 62,
    Colour_63 = 63
};


}//ALCMClrSetHMISrv_GS2S_Gen
}//ALCMClrSetHMISrv_GS2S
}//GS2S
}//ALCM
}//Body
}//Vehicle
}//GWM


#endif 

#ifndef _ALCMCTRLSRV_DATATYPES_HPP_
#define _ALCMCTRLSRV_DATATYPES_HPP_
#include <iostream>
#include <cstdint>

namespace GWM{
namespace Vehicle{
namespace Body{
namespace ALCM{
namespace ALCMCtrlSrv_Gen{

enum class ActvNodeCtrl_Command_Enum : std::uint8_t {
    Disable = 0,
    Enable = 1
};
struct ActvNodeCtrl_Struct {
    using _Active_Node_1_type = ActvNodeCtrl_Command_Enum;
    _Active_Node_1_type Active_Node_1;

    using _Active_Node_2_type = ActvNodeCtrl_Command_Enum;
    _Active_Node_2_type Active_Node_2;

    using _Active_Node_3_type = ActvNodeCtrl_Command_Enum;
    _Active_Node_3_type Active_Node_3;

    using _Active_Node_4_type = ActvNodeCtrl_Command_Enum;
    _Active_Node_4_type Active_Node_4;

    using _Active_Node_5_type = ActvNodeCtrl_Command_Enum;
    _Active_Node_5_type Active_Node_5;

    using _Active_Node_6_type = ActvNodeCtrl_Command_Enum;
    _Active_Node_6_type Active_Node_6;

    using _Active_Node_7_type = ActvNodeCtrl_Command_Enum;
    _Active_Node_7_type Active_Node_7;

    using _Active_Node_8_type = ActvNodeCtrl_Command_Enum;
    _Active_Node_8_type Active_Node_8;

    using _Active_Node_9_type = ActvNodeCtrl_Command_Enum;
    _Active_Node_9_type Active_Node_9;

    using _Active_Node_10_type = ActvNodeCtrl_Command_Enum;
    _Active_Node_10_type Active_Node_10;

    using _Active_Node_11_type = ActvNodeCtrl_Command_Enum;
    _Active_Node_11_type Active_Node_11;

    using _Active_Node_12_type = ActvNodeCtrl_Command_Enum;
    _Active_Node_12_type Active_Node_12;

    using _Active_Node_13_type = ActvNodeCtrl_Command_Enum;
    _Active_Node_13_type Active_Node_13;

    using _Active_Node_14_type = ActvNodeCtrl_Command_Enum;
    _Active_Node_14_type Active_Node_14;

    using _Active_Node_15_type = ActvNodeCtrl_Command_Enum;
    _Active_Node_15_type Active_Node_15;

    using _Active_Node_16_type = ActvNodeCtrl_Command_Enum;
    _Active_Node_16_type Active_Node_16;

    using _Active_Node_17_type = ActvNodeCtrl_Command_Enum;
    _Active_Node_17_type Active_Node_17;

    using _Active_Node_18_type = ActvNodeCtrl_Command_Enum;
    _Active_Node_18_type Active_Node_18;

    using _Active_Node_19_type = ActvNodeCtrl_Command_Enum;
    _Active_Node_19_type Active_Node_19;

    using _Active_Node_20_type = ActvNodeCtrl_Command_Enum;
    _Active_Node_20_type Active_Node_20;

    using _Active_Node_21_type = ActvNodeCtrl_Command_Enum;
    _Active_Node_21_type Active_Node_21;

    using _Active_Node_22_type = ActvNodeCtrl_Command_Enum;
    _Active_Node_22_type Active_Node_22;

    using _Active_Node_23_type = ActvNodeCtrl_Command_Enum;
    _Active_Node_23_type Active_Node_23;

    using _Active_Node_24_type = ActvNodeCtrl_Command_Enum;
    _Active_Node_24_type Active_Node_24;

    using _Active_Node_1_NF_type = ActvNodeCtrl_Command_Enum;
    _Active_Node_1_NF_type Active_Node_1_NF;

    using _Active_Node_2_NF_type = ActvNodeCtrl_Command_Enum;
    _Active_Node_2_NF_type Active_Node_2_NF;

    using _Active_Node_3_NF_type = ActvNodeCtrl_Command_Enum;
    _Active_Node_3_NF_type Active_Node_3_NF;

    using _Active_Node_4_NF_type = ActvNodeCtrl_Command_Enum;
    _Active_Node_4_NF_type Active_Node_4_NF;

    using _Active_Node_5_NF_type = ActvNodeCtrl_Command_Enum;
    _Active_Node_5_NF_type Active_Node_5_NF;

    using _Active_Node_6_NF_type = ActvNodeCtrl_Command_Enum;
    _Active_Node_6_NF_type Active_Node_6_NF;

    using _Active_Node_7_NF_type = ActvNodeCtrl_Command_Enum;
    _Active_Node_7_NF_type Active_Node_7_NF;

    using _Active_Node_8_NF_type = ActvNodeCtrl_Command_Enum;
    _Active_Node_8_NF_type Active_Node_8_NF;

    using _Active_Node_9_NF_type = ActvNodeCtrl_Command_Enum;
    _Active_Node_9_NF_type Active_Node_9_NF;

    using _Active_Node_10_NF_type = ActvNodeCtrl_Command_Enum;
    _Active_Node_10_NF_type Active_Node_10_NF;

    using _Active_Node_11_NF_type = ActvNodeCtrl_Command_Enum;
    _Active_Node_11_NF_type Active_Node_11_NF;

    using _Active_Node_12_NF_type = ActvNodeCtrl_Command_Enum;
    _Active_Node_12_NF_type Active_Node_12_NF;

    using _Active_Node_13_NF_type = ActvNodeCtrl_Command_Enum;
    _Active_Node_13_NF_type Active_Node_13_NF;

    using _Active_Node_14_NF_type = ActvNodeCtrl_Command_Enum;
    _Active_Node_14_NF_type Active_Node_14_NF;

    using _Active_Node_15_NF_type = ActvNodeCtrl_Command_Enum;
    _Active_Node_15_NF_type Active_Node_15_NF;

    using _Active_Node_16_NF_type = ActvNodeCtrl_Command_Enum;
    _Active_Node_16_NF_type Active_Node_16_NF;

    using _Active_Node_17_NF_type = ActvNodeCtrl_Command_Enum;
    _Active_Node_17_NF_type Active_Node_17_NF;

    using _Active_Node_18_NF_type = ActvNodeCtrl_Command_Enum;
    _Active_Node_18_NF_type Active_Node_18_NF;

    using _Active_Node_19_NF_type = ActvNodeCtrl_Command_Enum;
    _Active_Node_19_NF_type Active_Node_19_NF;

    using _Active_Node_20_NF_type = ActvNodeCtrl_Command_Enum;
    _Active_Node_20_NF_type Active_Node_20_NF;

    using _Active_Node_21_NF_type = ActvNodeCtrl_Command_Enum;
    _Active_Node_21_NF_type Active_Node_21_NF;

    using _Active_Node_22_NF_type = ActvNodeCtrl_Command_Enum;
    _Active_Node_22_NF_type Active_Node_22_NF;

    using _Active_Node_23_NF_type = ActvNodeCtrl_Command_Enum;
    _Active_Node_23_NF_type Active_Node_23_NF;

    using _Active_Node_24_NF_type = ActvNodeCtrl_Command_Enum;
    _Active_Node_24_NF_type Active_Node_24_NF;

};

}//ALCMCtrlSrv_Gen
}//ALCM
}//Body
}//Vehicle
}//GWM


#endif /* _ALCMCTRLSRV_DATATYPES_HPP_ */



using Context_ActvNodeCtrl_Command_Enum = GWM::Vehicle::Body::ALCM::ALCMCtrlSrv_Gen::ActvNodeCtrl_Command_Enum;
using Context_ActvNodeCtrl_Struct = GWM::Vehicle::Body::ALCM::ALCMCtrlSrv_Gen::ActvNodeCtrl_Struct;

//打印节点详细信息
void printNodeStatus(GWM::Vehicle::Body::ALCM::ALCMCtrlSrv_Gen::ActvNodeCtrl_Struct& data){
    Context_ActvNodeCtrl_Command_Enum *item = (Context_ActvNodeCtrl_Command_Enum*)&data;//获取结构体存储首地址
    auto num = 1;
    auto tail = item+sizeof(data)/sizeof(Context_ActvNodeCtrl_Command_Enum);//获取结构体存储尾地址
    for(auto i = item ; i<tail;i++){
        std::cout<<"num = "<<num <<" data = "<<static_cast<int>(*i)<<std::endl;
        num++;
    }    
}
//设置单个位置的节点
Context_ActvNodeCtrl_Struct setSignalNode(int No , int status ,Context_ActvNodeCtrl_Struct& ActvNodeStruct){
    Context_ActvNodeCtrl_Command_Enum *head = (Context_ActvNodeCtrl_Command_Enum*)&ActvNodeStruct;//获取结构体存储首地址
    auto index = head+No-1;//对应的 结构体中 元素位置
    *index = (Context_ActvNodeCtrl_Command_Enum)status; //改变对应位置的节点值
    return ActvNodeStruct;
}
//设置范围区域的节点
void SetNodesRanges(int start, int end ,int status , Context_ActvNodeCtrl_Struct& ActvNodeStruct){
    Context_ActvNodeCtrl_Command_Enum *head = (Context_ActvNodeCtrl_Command_Enum*)&ActvNodeStruct;//获取结构体存储首地址
    auto startindex = head + start -1;
    auto endindex = head + end -1;
    for (auto i = startindex; i <=endindex ; i++)
    {
        *i = (Context_ActvNodeCtrl_Command_Enum)status;
    }
}
//全部置0
void ResetNodeToAllZero(Context_ActvNodeCtrl_Struct& ActvNodeStruct){
    Context_ActvNodeCtrl_Command_Enum *head = (Context_ActvNodeCtrl_Command_Enum*)&ActvNodeStruct;//获取结构体存储首地址
    auto tail = head+sizeof(ActvNodeStruct)/sizeof(Context_ActvNodeCtrl_Command_Enum);//获取结构体存储尾地址

    for(auto i = head ; i<tail;i++){
        *i =(Context_ActvNodeCtrl_Command_Enum)0;
    }
}
//全部置1
void SetNodeToAllOpen(Context_ActvNodeCtrl_Struct& ActvNodeStruct){
    Context_ActvNodeCtrl_Command_Enum *head = (Context_ActvNodeCtrl_Command_Enum*)&ActvNodeStruct;//获取结构体存储首地址
    auto tail = head+sizeof(ActvNodeStruct)/sizeof(Context_ActvNodeCtrl_Command_Enum);//获取结构体存储尾地址

    for(auto i = head ; i<tail;i++){
        *i =(Context_ActvNodeCtrl_Command_Enum)1;
    }
}


/*
//--------------------------------------律动模式算法---------------------------------------------------------------------
enum class SyllablePrmCtrl_Command_Enum : std::uint8_t {
    No_Action = 0,
    Valid1 = 1,
    Valid2 = 2,
    Valid3 = 3,
    Valid4 = 4,
    Valid5 = 5,
    Valid6 = 6,
    Valid7 = 7
};

struct SyllablePrmCtrl_Struct {
    using _SyllablePrmCtrl_type = SyllablePrmCtrl_Command_Enum;
    _SyllablePrmCtrl_type SyllablePrmCtrl;

    using _SyllablePrmCtrl_NF_type = SyllablePrmCtrl_Command_Enum;
    _SyllablePrmCtrl_NF_type SyllablePrmCtrl_NF;

};

//0-100有效 101 无响应
enum class MusicFrqSet_Enum : std::uint8_t {
    amplitude_0 = 0,
    amplitude_1 = 1,
    amplitude_2 = 2,
    amplitude_3 = 3,
    amplitude_4 = 4,
    amplitude_5 = 5,
    amplitude_6 = 6,
    amplitude_7 = 7,
    amplitude_8 = 8,
    amplitude_9 = 9,
    amplitude_10 = 10,
    amplitude_11 = 11,
    amplitude_12 = 12,
    amplitude_13 = 13,
    amplitude_14 = 14,
    amplitude_15 = 15,
    amplitude_16 = 16,
    amplitude_17 = 17,
    amplitude_18 = 18,
    amplitude_19 = 19,
    amplitude_20 = 20,
    amplitude_21 = 21,
    amplitude_22 = 22,
    amplitude_23 = 23,
    amplitude_24 = 24,
    amplitude_25 = 25,
    amplitude_26 = 26,
    amplitude_27 = 27,
    amplitude_28 = 28,
    amplitude_29 = 29,
    amplitude_30 = 30,
    amplitude_31 = 31,
    amplitude_32 = 32,
    amplitude_33 = 33,
    amplitude_34 = 34,
    amplitude_35 = 35,
    amplitude_36 = 36,
    amplitude_37 = 37,
    amplitude_38 = 38,
    amplitude_39 = 39,
    amplitude_40 = 40,
    amplitude_41 = 41,
    amplitude_42 = 42,
    amplitude_43 = 43,
    amplitude_44 = 44,
    amplitude_45 = 45,
    amplitude_46 = 46,
    amplitude_47 = 47,
    amplitude_48 = 48,
    amplitude_49 = 49,
    amplitude_50 = 50,
    amplitude_51 = 51,
    amplitude_52 = 52,
    amplitude_53 = 53,
    amplitude_54 = 54,
    amplitude_55 = 55,
    amplitude_56 = 56,
    amplitude_57 = 57,
    amplitude_58 = 58,
    amplitude_59 = 59,
    amplitude_60 = 60,
    amplitude_61 = 61,
    amplitude_62 = 62,
    amplitude_63 = 63,
    amplitude_64 = 64,
    amplitude_65 = 65,
    amplitude_66 = 66,
    amplitude_67 = 67,
    amplitude_68 = 68,
    amplitude_69 = 69,
    amplitude_70 = 70,
    amplitude_71 = 71,
    amplitude_72 = 72,
    amplitude_73 = 73,
    amplitude_74 = 74,
    amplitude_75 = 75,
    amplitude_76 = 76,
    amplitude_77 = 77,
    amplitude_78 = 78,
    amplitude_79 = 79,
    amplitude_80 = 80,
    amplitude_81 = 81,
    amplitude_82 = 82,
    amplitude_83 = 83,
    amplitude_84 = 84,
    amplitude_85 = 85,
    amplitude_86 = 86,
    amplitude_87 = 87,
    amplitude_88 = 88,
    amplitude_89 = 89,
    amplitude_90 = 90,
    amplitude_91 = 91,
    amplitude_92 = 92,
    amplitude_93 = 93,
    amplitude_94 = 94,
    amplitude_95 = 95,
    amplitude_96 = 96,
    amplitude_97 = 97,
    amplitude_98 = 98,
    amplitude_99 = 99,
    amplitude_100 = 100,
    No_action = 101,
    Reserved1 = 102,
    Reserved2 = 103,
    Reserved3 = 104,
    Reserved4 = 105,
    Reserved5 = 106,
    Reserved6 = 107,
    Reserved7 = 108,
    Reserved8 = 109,
    Reserved9 = 110,
    Reserved10 = 111,
    Reserved11 = 112,
    Reserved12 = 113,
    Reserved13 = 114,
    Reserved14 = 115,
    Reserved15 = 116,
    Reserved16 = 117,
    Reserved17 = 118,
    Reserved18 = 119,
    Reserved19 = 120,
    Reserved20 = 121,
    Reserved21 = 122,
    Reserved22 = 123,
    Reserved23 = 124,
    Reserved24 = 125,
    Reserved25 = 126,
    Reserved26 = 127
};

struct MusicFrqSet_Struct {
    using _MusicFrq0_type = MusicFrqSet_Enum;
    _MusicFrq0_type MusicFrq0;

    using _MusicFrq1_type = MusicFrqSet_Enum;
    _MusicFrq1_type MusicFrq1;

    using _MusicFrq2_type = MusicFrqSet_Enum;
    _MusicFrq2_type MusicFrq2;

    using _MusicFrq3_type = MusicFrqSet_Enum;
    _MusicFrq3_type MusicFrq3;

    using _MusicFrq4_type = MusicFrqSet_Enum;
    _MusicFrq4_type MusicFrq4;

    using _MusicFrq5_type = MusicFrqSet_Enum;
    _MusicFrq5_type MusicFrq5;

    using _MusicFrq6_type = MusicFrqSet_Enum;
    _MusicFrq6_type MusicFrq6;

};

int getMaxMusicNo(MusicFrqSet_Struct& musicstruct){
    int MaxNo = 0;
    int No = 0;
    int max = 0;
    int min = 0;
    //获取结构体首地址
    MusicFrqSet_Enum* MusicFrqSet_Start = (MusicFrqSet_Enum*)&musicstruct;
    //获取结构体尾地址
    MusicFrqSet_Enum* MusicFrqSet_End = MusicFrqSet_Start + sizeof(musicstruct)/sizeof(MusicFrqSet_Enum);

    for (auto i = MusicFrqSet_Start ; i < MusicFrqSet_End ; i++)
    {
        min = static_cast<uint8_t>(*i);
        if(max < min){
            max = min;
            MaxNo = No;
        }
        No++;
    }
    return MaxNo;
}

void setMusicFrq_Struct(MusicFrqSet_Struct& musicstruct){
    int value = 18;
    //获取结构体首地址
    MusicFrqSet_Enum* MusicFrqSet_Start = (MusicFrqSet_Enum*)&musicstruct;
    //获取结构体尾地址
    MusicFrqSet_Enum* MusicFrqSet_End = MusicFrqSet_Start + sizeof(musicstruct)/sizeof(MusicFrqSet_Enum);
    for (auto i = MusicFrqSet_Start ; i < MusicFrqSet_End ; i++)
    {
        *i = (MusicFrqSet_Enum)value;
        value += (-3);
    }
        
}

void printMusicFrq_Struct(MusicFrqSet_Struct& musicstruct){
    int musicno = 0;
    //获取结构体首地址
    MusicFrqSet_Enum* MusicFrqSet_Start = (MusicFrqSet_Enum*)&musicstruct;
    //获取结构体尾地址
    MusicFrqSet_Enum* MusicFrqSet_End = MusicFrqSet_Start + sizeof(musicstruct)/sizeof(MusicFrqSet_Enum);
    for (auto i = MusicFrqSet_Start ; i < MusicFrqSet_End ; i++)
    {
        std::cout<<"musicno "<<musicno<<" : "<<static_cast<int>(*i)<<std::endl;
        musicno++;
    }    
}
*/
//*********************************** 驾驶区域 节点开关 辅助函数*************************************//
//主驾区节点全开/全关
Context_ActvNodeCtrl_Struct MainZoneOpen(Context_ActvNodeCtrl_Struct ActvNodeStruct){
    Context_ActvNodeCtrl_Struct OpenNode = ActvNodeStruct;
    //LIN 7
    OpenNode = setSignalNode(2,1,OpenNode);
    OpenNode = setSignalNode(5,1,OpenNode);
    OpenNode = setSignalNode(20,1,OpenNode);
    OpenNode = setSignalNode(18,1,OpenNode);
    OpenNode = setSignalNode(6,1,OpenNode);
    OpenNode = setSignalNode(7,1,OpenNode);
    OpenNode = setSignalNode(8,1,OpenNode);
    //LIN 9
    OpenNode = setSignalNode(42,1,OpenNode);
    OpenNode = setSignalNode(43,1,OpenNode);
    OpenNode = setSignalNode(44,1,OpenNode);
    OpenNode = setSignalNode(45,1,OpenNode);
    OpenNode = setSignalNode(25,1,OpenNode);
    OpenNode = setSignalNode(26,1,OpenNode);
    OpenNode = setSignalNode(27,1,OpenNode);
    OpenNode = setSignalNode(28,1,OpenNode);
    OpenNode = setSignalNode(29,1,OpenNode);
    OpenNode = setSignalNode(30,1,OpenNode);
    OpenNode = setSignalNode(31,1,OpenNode);

    return OpenNode;
}
Context_ActvNodeCtrl_Struct MainZoneClose(Context_ActvNodeCtrl_Struct ActvNodeStruct){
    Context_ActvNodeCtrl_Struct CloseNode = ActvNodeStruct;
    CloseNode = setSignalNode(2,0,CloseNode);
    CloseNode = setSignalNode(5,0,CloseNode);
    CloseNode = setSignalNode(20,0,CloseNode);
    CloseNode = setSignalNode(18,0,CloseNode);
    CloseNode = setSignalNode(6,0,CloseNode);
    CloseNode = setSignalNode(7,0,CloseNode);
    CloseNode = setSignalNode(8,0,CloseNode);
    CloseNode = setSignalNode(42,0,CloseNode);
    CloseNode = setSignalNode(43,0,CloseNode);
    CloseNode = setSignalNode(44,0,CloseNode);
    CloseNode = setSignalNode(45,0,CloseNode);
    CloseNode = setSignalNode(25,0,CloseNode);
    CloseNode = setSignalNode(26,0,CloseNode);
    CloseNode = setSignalNode(27,0,CloseNode);
    CloseNode = setSignalNode(28,0,CloseNode);
    CloseNode = setSignalNode(29,0,CloseNode);
    CloseNode = setSignalNode(30,0,CloseNode);
    CloseNode = setSignalNode(31,0,CloseNode);
    return CloseNode;
}

//副驾区节点全开/全关
Context_ActvNodeCtrl_Struct FrontPassengerZoneOpen(Context_ActvNodeCtrl_Struct ActvNodeStruct){
    Context_ActvNodeCtrl_Struct OpenNode = ActvNodeStruct;
    OpenNode = setSignalNode(3,1,OpenNode);
    OpenNode = setSignalNode(4,1,OpenNode);
    OpenNode = setSignalNode(22,1,OpenNode);
    OpenNode = setSignalNode(19,1,OpenNode);
    OpenNode = setSignalNode(12,1,OpenNode);
    OpenNode = setSignalNode(13,1,OpenNode);
    OpenNode = setSignalNode(14,1,OpenNode);
    OpenNode = setSignalNode(35,1,OpenNode);
    OpenNode = setSignalNode(36,1,OpenNode);
    OpenNode = setSignalNode(37,1,OpenNode);

    return OpenNode;
}
Context_ActvNodeCtrl_Struct FrontPassengerZoneClose(Context_ActvNodeCtrl_Struct ActvNodeStruct){
    Context_ActvNodeCtrl_Struct CloseNode = ActvNodeStruct;
    CloseNode = setSignalNode(3,0,CloseNode);
    CloseNode = setSignalNode(4,0,CloseNode);
    CloseNode = setSignalNode(22,0,CloseNode);
    CloseNode = setSignalNode(19,0,CloseNode);
    CloseNode = setSignalNode(12,0,CloseNode);
    CloseNode = setSignalNode(13,0,CloseNode);
    CloseNode = setSignalNode(14,0,CloseNode);
    CloseNode = setSignalNode(35,0,CloseNode);
    CloseNode = setSignalNode(36,0,CloseNode);
    CloseNode = setSignalNode(37,0,CloseNode);

    return CloseNode;
}

//后部区节点全开/全关
Context_ActvNodeCtrl_Struct RearZoneOpen(Context_ActvNodeCtrl_Struct ActvNodeStruct){
    Context_ActvNodeCtrl_Struct OpenNode = ActvNodeStruct;
    OpenNode = setSignalNode(9,1,OpenNode);
    OpenNode = setSignalNode(10,1,OpenNode);
    OpenNode = setSignalNode(11,1,OpenNode);
    OpenNode = setSignalNode(15,1,OpenNode);
    OpenNode = setSignalNode(16,1,OpenNode);
    OpenNode = setSignalNode(17,1,OpenNode);
    OpenNode = setSignalNode(32,1,OpenNode);
    OpenNode = setSignalNode(33,1,OpenNode);
    OpenNode = setSignalNode(34,1,OpenNode);
    OpenNode = setSignalNode(38,1,OpenNode);
    OpenNode = setSignalNode(39,1,OpenNode);
    OpenNode = setSignalNode(40,1,OpenNode);
    OpenNode = setSignalNode(47,1,OpenNode);
    OpenNode = setSignalNode(48,1,OpenNode);

    return OpenNode;
}
//关闭后排节点使能
Context_ActvNodeCtrl_Struct RearZoneClose(Context_ActvNodeCtrl_Struct ActvNodeStruct){
    Context_ActvNodeCtrl_Struct CloseNode = ActvNodeStruct;
    CloseNode = setSignalNode(9,0,CloseNode);
    CloseNode = setSignalNode(10,0,CloseNode);
    CloseNode = setSignalNode(11,0,CloseNode);
    CloseNode = setSignalNode(15,0,CloseNode);
    CloseNode = setSignalNode(16,0,CloseNode);
    CloseNode = setSignalNode(17,0,CloseNode);
    CloseNode = setSignalNode(32,0,CloseNode);
    CloseNode = setSignalNode(33,0,CloseNode);
    CloseNode = setSignalNode(34,0,CloseNode);
    CloseNode = setSignalNode(38,0,CloseNode);
    CloseNode = setSignalNode(39,0,CloseNode);
    CloseNode = setSignalNode(40,0,CloseNode);
    CloseNode = setSignalNode(47,0,CloseNode);
    CloseNode = setSignalNode(48,0,CloseNode);

    return CloseNode;
}

/**
 * @brief 关闭特殊区域节点
 */
Context_ActvNodeCtrl_Struct SpecialNodesClose(Context_ActvNodeCtrl_Struct ActvNodeStruct){
    Context_ActvNodeCtrl_Struct CloseNode = ActvNodeStruct;

    CloseNode = setSignalNode(1,0,CloseNode);
    CloseNode = setSignalNode(21,0,CloseNode);
    CloseNode = setSignalNode(23,0,CloseNode);
    CloseNode = setSignalNode(41,0,CloseNode);
    CloseNode = setSignalNode(46,0,CloseNode);

    return CloseNode;
}
/**
 * @brief 打开特殊区域节点
 */
Context_ActvNodeCtrl_Struct SpecialNodesOpen(Context_ActvNodeCtrl_Struct ActvNodeStruct){
    Context_ActvNodeCtrl_Struct CloseNode = ActvNodeStruct;

    CloseNode = setSignalNode(1,1,CloseNode);
    CloseNode = setSignalNode(21,1,CloseNode);
    CloseNode = setSignalNode(23,1,CloseNode);
    CloseNode = setSignalNode(41,1,CloseNode);
    CloseNode = setSignalNode(46,1,CloseNode);

    return CloseNode;
}
/**
 * @brief 与或非的计算
 * 
 */
void computenum(){
    uint16_t gradual_bright = 0x1<<12;//渐亮
    uint16_t gradual_extinction = 0x2<<12;//渐灭


    uint8_t save_light = 255u;

    uint16_t light1 = gradual_bright | save_light;
    uint16_t light2 = gradual_extinction | save_light;
    uint16_t flash_fulllight = (0x4<<12) | 0xff;

    std::cout<<std::bitset<16>(light1)<<std::endl;
    std::cout<<std::bitset<16>(light2)<<std::endl;
    std::cout<<std::bitset<16>(flash_fulllight)<<std::endl;
    std::cout<<"0&0: "<< (0&0) << " 0&1:" <<(0&1)<<" 0&2: "<<(0&2)<<std::endl;
    std::cout<<"1&0: "<< (1&0) << " 1&1:" <<(1&1)<<" 1&2: "<<(1&2)<<std::endl;
    std::cout<<"2|0: "<< (2|0) << " 1|1:" <<(1|1)<<" 1|2: "<<(1|2)<<std::endl;
}

/**
 * @brief 打印功能菜单
 * 1：打印详细节点信息
 * 2：关闭分区 （主驾、副驾、后排、特殊）
 * 3：打开分区 （主驾、副驾、后排、特殊）
 */
void PrintMenu(){

}



int main(){

    Context_ActvNodeCtrl_Struct actvnode;


    return 0;
}


