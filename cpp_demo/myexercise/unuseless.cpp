#include <iostream>

using namespace std;


enum class S2S_Response_Enum : std::uint32_t {
    E_OK = 0,
    E_MEMORY_ERROR = 1,
    E_STORAGE_ERROR = 2,
    E_SYSTEM_RESOURCE_ERROR = 3,
    E_MIDDLEWARE_ERROR = 4,
    E_IPC_READ_ERROR = 5,
    SOMEIP_E_UNKNOWN_SERVICE = 16777218,
    SOMEIP_E_UNKNOWN_METHOD = 16777219,
    SOMEIP_E_NOT_READY = 16777220,
    SOMEIP_E_NOT_REACHABLE = 16777221
};


// someip 时候 1--0 也是表示调用成功
enum class SOA_Protocol_Type_Enum : std::uint8_t {
    Protocol_General = 0,
    Protocol_SOMEIP = 1,
    Protocol_DDS = 2,
    Protocol_Custom = 128
};

struct SOA_Response_Struct {
    using _ProtocolType_type = SOA_Protocol_Type_Enum;
    _ProtocolType_type ProtocolType;

    using _Reserved0_type = std::uint8_t;
    _Reserved0_type Reserved0;

    using _Reserved1_type = std::uint8_t;
    _Reserved1_type Reserved1;

    using _ReturnCode_type = std::uint8_t;
    _ReturnCode_type ReturnCode;

};

 template<typename R ,typename GS2S>
bool rethandler_c(R &ret,const GS2S &response){
    auto res = static_cast<uint32_t>(response);

    auto protocolType_value = static_cast<uint8_t>(res>>24);
    auto reserved0_value = static_cast<uint8_t>(res>>16);
    auto reserved1_value = static_cast<uint8_t>(res>>8);
    auto code_value = static_cast<uint8_t>(res);

    //调用成功 返回 0,0,0,0
    if(code_value == 0){
        ret.ProtocolType = typename R::_ProtocolType_type(static_cast<uint8_t>(0));
        ret.Reserved0 = reserved0_value;
        ret.Reserved1 = reserved1_value;
        ret.ReturnCode = code_value;
        return true;
    }

    //调用失败 
    ret.ProtocolType = typename R::_ProtocolType_type(protocolType_value);
    ret.Reserved0 = reserved0_value;
    ret.Reserved1 = reserved1_value;
    ret.ReturnCode = code_value;
    return false;
}

                template<typename R>
                std::string responseToString(const R &ret){
                    return "ProtocolType = " + std::to_string(static_cast<int>(ret.ProtocolType)) + " Reserved0 = " + std::to_string(static_cast<int>(ret.Reserved0))
                    + " Reserved1 = " + std::to_string(static_cast<int>(ret.Reserved1)) + " ReturnCode = " + std::to_string(static_cast<int>(ret.ReturnCode));
                }

int main()
{
    S2S_Response_Enum GS2S_Ret{S2S_Response_Enum(65793)};
    SOA_Response_Struct Method_Ret{SOA_Protocol_Type_Enum(0),0,0,0};
    rethandler_c(Method_Ret,GS2S_Ret);
    cout<<static_cast<int>(Method_Ret.ProtocolType)<<endl;
    cout<<static_cast<int>(Method_Ret.Reserved0)<<endl;
    cout<<static_cast<int>(Method_Ret.Reserved1)<<endl;
    cout<<static_cast<int>(Method_Ret.ReturnCode)<<endl;
    cout<<responseToString(Method_Ret);
}

