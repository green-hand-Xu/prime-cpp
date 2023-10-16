#include <iostream>

    //设置节点开关
    AtlmiCNTLR->contourLightSt.setNodeSwtCmd(1u);
    //设置氛围灯模式
    AtlmiCNTLR->contourLightSt.setModeSelectionCtrl(0u);
    //获取颜色色号 根据色号获取颜色色值结构体 设置颜色
    auto colorNo = static_cast<uint8_t>(_PreconditionContext->context_AtmLi_ColorSet_64);
    auto colortype = _computColor->return_rgbcolor(static_cast<AtmLi_ColorSet_64_Enum>(colorNo),_computColor->_64colormap); 
    AtlmiCNTLR->contourLightSt.setRGBValue(colortype.RedRatCtrl,colortype.GreenRatCtrl,colortype.BlueRatCtrl);
    //获取设置的亮度信息 设置氛围灯亮度
    auto light_value = static_cast<int>(_PreconditionContext->context_LightLvlSet);
    AtlmiCNTLR->contourLightSt.setLightLvlCmd(light_value);
    //设置模式变化控制命令
    AtlmiCNTLR->contourLightSt.setModeChangeCtrlCmd(0u);
    //设置渐变时间
    AtlmiCNTLR->contourLightSt.setFadeTimeCtrlCmd(0u);
    //设置律动闪烁时间
    AtlmiCNTLR->contourLightSt.setSyllablePrmCmd(0u);
    //同步分区开关状态 并 设置使能节点
    AtlmiCNTLR->atmLiS2SInterface->SyncZoneNode();
    _PreconditionContext->LIN_ZoneNode_Rec(_PreconditionContext->context_ActvNodeCtrl);
    AtlmiCNTLR->contourLightSt.setActvNode(_PreconditionContext->context_ActvNodeCtrl);
    //将设置信号下发至S2S服务
    AtlmiCNTLR->openContourAtlmi(AtlmiCNTLR->contourLightSt);
    //存储氛围灯模式、颜色、亮度等开关的状态
    AtlmiCNTLR->atmLiS2SInterface->EEPROM_SaveSwitchContext();

    //使能节点设置 全开
    uint8_t actvnode[ActvNodeSize];
    memcpy(actvnode,_PreconditionContext->getContext_ActvNodeCtrl(),sizeof(actvnode));
    _PreconditionContext->SetNodeToAllOpen(actvnode);
    AtlmiCNTLR->contourLightSt.setActvNode(actvnode);
    
    AtlmiCNTLR->crystalPanelLightSt.setNodeSwtCtrl(1u);
    AtlmiCNTLR->crystalPanelLightSt.setModeChangeCtrl(1u);
    AtlmiCNTLR->crystalPanelLightSt.setModeSelectionCtrl(4u);
    AtlmiCNTLR->crystalPanelLightSt.setFadeTimeCtrl(13u);
    AtlmiCNTLR->crystalPanelLightSt.setWPCGangSwt(0u);
    AtlmiCNTLR->crystalPanelLightSt.setSyllablePrmCtrl(0u);
    AtlmiCNTLR->crystalPanelLightSt.setLightLvlCtrl(light);
    //设置颜色
    AtlmiCNTLR->crystalPanelLightSt.setOLERGBValue(retcolor.RedRatCtrl,retcolor.GreenRatCtrl,retcolor.BlueRatCtrl);
    AtlmiCNTLR->openCrystalPanelAtlmi(AtlmiCNTLR->crystalPanelLightSt);

    
    AtlmiCNTLR->crystalPanelLightSt.setNodeSwtCtrl(1u);
    AtlmiCNTLR->crystalPanelLightSt.setWPCGangSwt(static_cast<uint8_t>(_PreconditionContext->context_WPCGangSwt));
    AtlmiCNTLR->crystalPanelLightSt.setCPModeSet(0u);
    AtlmiCNTLR->crystalPanelLightSt.setFadeTimeCtrl(3u);
    AtlmiCNTLR->crystalPanelLightSt.setModeChangeCtrl(1u);
    //获取亮度设置
    auto light = static_cast<uint8_t>(_PreconditionContext->context_LightLvlSet);
    AtlmiCNTLR->crystalPanelLightSt.setLightLvlCtrl(light);
    AtlmiCNTLR->openCrystalPanelAtlmi(AtlmiCNTLR->crystalPanelLightSt);





/**
 * @brief 5.1.1.5.1 ALCM(LIN)分区控制 : 关闭主驾区氛围灯
 * 触发函数
 */
void PreconditionJudge::LIN_CloseMainALCM_Tri(){
    if(!AtlmiCNTLR->serverSt()){
        log_.LogError()<<__func__<<"ALCMCtrlSrv was not found";
        return;
    }
    
    auto retcode = this->LIN_CloseMainALCMPre();
    log_.LogInfo()<<"execute : "<<__func__<<" Precondition return code = "<< retcode;
    if(retcode == 255){
        log_.LogInfo()<<__func__<<" 不满足前提条件";
        return ;
    }

    if(retcode == 1){
        //设置节点开关
        AtlmiCNTLR->contourLightSt.setNodeSwtCmd(1u);
        //获取存储的节点信息
        uint8_t actvnode[ActvNodeSize];
        memcpy(actvnode,_PreconditionContext->getContext_ActvNodeCtrl(),sizeof(actvnode));
        //关闭主驾节点使能
        _PreconditionContext->MainZoneClose(actvnode);
        if(LIN_CloseFrontAreaPre() == 1){
            _PreconditionContext->SpecialNodesClose(actvnode);
        }
        //存储分区设置结果
        _PreconditionContext->setContext_ActvNodeCtrl(actvnode);
        //打开主驾区节点使能
        _PreconditionContext->MainZoneOpen(actvnode);
        if(LIN_CloseFrontAreaPre() == 1){
            _PreconditionContext->SpecialNodesOpen(actvnode);
        }else if(LIN_CloseFrontAreaPre() == 2){
            _PreconditionContext->SpecialNodesClose(actvnode);
        }
        //关闭副驾、后排、正在联动的 节点使能
        _PreconditionContext->RearZoneClose(actvnode);
        _PreconditionContext->FrontPassengerZoneClose(actvnode);
        //去除掉联动节点
        _PreconditionContext->LIN_ZoneNode_Rec(actvnode);
        //设置节点使能
        AtlmiCNTLR->contourLightSt.setActvNode(actvnode);
        //设置氛围灯亮度为 0 
        AtlmiCNTLR->contourLightSt.setLightLvlCmd(0);
        AtlmiCNTLR->openContourAtlmi(AtlmiCNTLR->contourLightSt);
        std::this_thread::sleep_for(std::chrono::milliseconds(75));
        //2、恢复其他分区灯亮度
        auto light_value = static_cast<int>(_PreconditionContext->context_LightLvlSet);
        AtlmiCNTLR->contourLightSt.setLightLvlCmd(light_value);
        //设置节点使能 使用存储的分区状态信息 需要去掉联动中的节点
        memcpy(actvnode,_PreconditionContext->getContext_ActvNodeCtrl(),sizeof(actvnode));
        _PreconditionContext->LIN_ZoneNode_Rec(actvnode);
        AtlmiCNTLR->contourLightSt.setActvNode(actvnode);
        AtlmiCNTLR->openContourAtlmi(AtlmiCNTLR->contourLightSt);
        //存储分区开关信息
        AtlmiCNTLR->atmLiS2SInterface->EEPROM_SaveZoneContext();
    }
}

/**
 * @brief 5.1.1.5.1 ALCM(LIN)分区控制 : 打开主驾区氛围灯
 * 触发函数
 */
void PreconditionJudge::LIN_OpenMainALCM_Tri(){
    log_.LogInfo()<<"execute : "<<__func__;
    if(!AtlmiCNTLR->serverSt()){
        log_.LogError()<<__func__<<"ALCMCtrlSrv was not found";
        return;
    }
    
    auto retcode = this->LIN_CloseMainALCMPre();
    log_.LogInfo()<<"execute : "<<__func__<<" Precondition return code = "<< retcode;
    if(retcode == 255){
        log_.LogInfo()<<__func__<<" 不满足前提条件";
        return ;
    }

    if(retcode == 2){
        //设置节点开关
        AtlmiCNTLR->contourLightSt.setNodeSwtCmd(1u);
        //获取存储的节点信息
        uint8_t actvnode[ActvNodeSize];
        memcpy(actvnode,_PreconditionContext->getContext_ActvNodeCtrl(),sizeof(actvnode));
        //打开主驾区节点使能
        _PreconditionContext->MainZoneOpen(actvnode);
        _PreconditionContext->SpecialNodesOpen(actvnode);
        //存储当前节点状态
        _PreconditionContext->setContext_ActvNodeCtrl(actvnode);
        //去除掉正在联动的节点
        _PreconditionContext->LIN_ZoneNode_Rec(actvnode);
        //设置节点使能
        AtlmiCNTLR->contourLightSt.setActvNode(actvnode);
        //恢复氛围灯亮度为存储值
        auto light_value = static_cast<int>(_PreconditionContext->context_LightLvlSet);
        AtlmiCNTLR->contourLightSt.setLightLvlCmd(light_value);
        AtlmiCNTLR->openContourAtlmi(AtlmiCNTLR->contourLightSt);
        //存储分区开关信息
        AtlmiCNTLR->atmLiS2SInterface->EEPROM_SaveZoneContext();
    }
}

int main(){
    return 0;
}