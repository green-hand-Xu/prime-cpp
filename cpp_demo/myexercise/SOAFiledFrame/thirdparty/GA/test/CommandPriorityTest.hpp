#ifndef __CommandPriorityTest_HPP__
#define __CommandPriorityTest_HPP__

#include <iostream>
#include <thread>

#include "GA/include/CommandPriority.hpp"

#define LOG(v) std::cout << v << "\r\n"

#define PriorityHigh 1
#define PriorityLow 2

void showIsBusy(CommandPriority& p){
    if(p.isBusy()){
        LOG("MESSAGE: current state is busy.");
    }else{
        LOG("MESSAGE: current state is not busy.");
    }
}

void showCurrentToken(CommandPriority& p){
    auto token = p.currentToken();
    LOG("MESSAGE: current token is: " + std::to_string(token));
}

void showTestDone(std::string action, bool isPass){
    if(isPass){
        LOG("Test PASS: " + action + " done, test passed.\r\n");
    }else{
        LOG("Test FAIL: " + action + " done, test failed.\r\n");
    }
}

/**
 * @brief Basic test for tryAccess() and access().
 * 
 * @param p 
 * @param priority 
 * @param command 
 * @return true 
 * @return false 
 */
bool testAccess(CommandPriority& p, int priority, int command){
    auto result = true;
    LOG("\r\nTest START access:");

    showIsBusy(p);
    showCurrentToken(p);

    auto ta = p.tryAccess(priority, command);
    if(!ta){
        result = false;
        LOG("MESSAGE: failed to tryAccess(...).");
    }
    
    CommandTokenValueType token;
    ta = p.access(priority, command, token);
    if(!ta){
        result = false;
        LOG("MESSAGE: failed to access.");
    }
    if(p.isBusy()){
        result = false;
        LOG("Failed: controller is busy after access.");
    }

    if(token == CommandTokenInvalid){
        result = false;
        LOG("Failed: token is invalid after access, token = " + std::to_string(token));
    }
    if(token < CommandTokenInvalid){
        result = false;
        LOG("Warning: token may not in correct range after access, token = " + std::to_string(token));
    }

    auto ctoken = p.currentToken();
    if(ctoken != token){
        result = false;
        LOG("Failed: current token is not the one got via access().");
    };
    showIsBusy(p);
    showCurrentToken(p);

    showTestDone("access test", result);

    return result;
}

/**
 * @brief Basic test for tryAccess() and accessAndOccupy().
 * 
 * @param p 
 * @param priority 
 * @param command 
 * @return true 
 * @return false 
 */
bool testAccessAndOccupy(CommandPriority& p, int priority, int command, bool expectResult = true){
    auto result = true;
    if(expectResult){
        LOG("\r\nTest START accessAndOccupy(...):");
    }else{
        LOG("\r\nTest START accessAndOccupy(...), expectResult = false:");
    }
    
    showIsBusy(p);
    showCurrentToken(p);

    auto ta = p.tryAccess(priority, command);
    if(!ta){
        result = false;
        LOG("MESSAGE: failed to try access.");
    }
    
    CommandTokenValueType token;
    ta = p.accessAndOccupy(priority, command, token);
    if(!ta){
        result = false;
        LOG("MESSAGE: failed to accessAndOccupy.");
    }
    if(!p.isBusy()){
        result = false;
        if(result != expectResult){
            LOG("Failed: controller is not busy after accessAndOccupy, it seems occupy failed.");
        }
    }

    if(token == CommandTokenInvalid){
        result = false;
        if(result != expectResult){
            LOG("Failed: token is invalid after accessAndOccupy, token = " + std::to_string(token));
        }
    }
    if(token < CommandTokenInvalid){
        result = false;
        if(result != expectResult){
            LOG("Warning: token may not in correct range after accessAndOccupy, token = " + std::to_string(token));
        }
    }

    auto ctoken = p.currentToken();
    if(ctoken != token){
        result = false;
        if(result != expectResult){
            LOG("Failed: current token is not the one got via accessAndOccupy().");
        }
    };
    
    showIsBusy(p);
    showCurrentToken(p);

    showTestDone("accessAndOccupy test", result == expectResult);

    return result == expectResult;
}

bool testLeave(CommandPriority& p, bool isRequireBusy, CommandTokenValueType token, bool expectResult = true){
    auto result = true;
    if(expectResult){
        LOG("\r\nTest START leave(...):");
    }else{
        LOG("\r\nTest START leave(...), expectResult = false:");
    }

    if(isRequireBusy && !p.isBusy()){
        result = false;
        if(result != expectResult){
            LOG("Failed: controller is not busy, does not need leave(...)");
        }
    }

    if(token <= CommandTokenInvalid){
        result = false;
        if(result != expectResult){
            LOG("Failed: invalid token, will not call leave for all");
        }
    }

    result = p.leave(token);
    if(result != expectResult){
        LOG("Failed: leave returns false, failed to leave.");
    }

    return result == expectResult;
}

bool testLeave(CommandPriority& p, bool isRequireBusy){
    auto result = true;
    LOG("\r\nTest START leave:");

    if(isRequireBusy && !p.isBusy()){
        result = false;
        LOG("Failed: controller is not busy, does not need leave(...)");
    }

    result = p.leave();
    if(!result){
        LOG("Failed: leave returns false, failed to leave.");
    }

    return result;
} 

/**
 * @brief Test initial state, tryAccess.
 * 
 */
bool testInitialState(){
    LOG(std::string("\r\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\r\nStart test for: ") + __func__);

    CommandPriority p;

    auto result = true;
    if(p.isBusy()){
        result = false;
        LOG("Failed: default state is busy.");
    }

    auto token = p.currentToken();
    if(token != CommandTokenInvalid){
        result = false;
        LOG("Failed: initial token is a valid one.");
    }
    if(token < CommandTokenInvalid){
        result = false;
        LOG("Warning: default token may not in correct range, token = " + std::to_string(token));
    }

    auto ta = p.tryAccess(1, 1);
    if(!ta){
        result = false;
        LOG("Failed: failed to tryAccess by priority 1 and command 1.");
    }

    showTestDone(__func__, result);

    return result;
}

/**
 * @brief Priority from low to high,
 * all should pass.
 */
void testAccessHigh(){
    LOG(std::string("\r\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\r\nStart test for: ") + __func__);

    CommandPriority p;
    
    auto r = testAccess(p, PriorityLow, 1);
    auto token1 = p.currentToken();
    showTestDone("Test initial access", r);

    r = testAccess(p, PriorityHigh, 1);
    auto token2 = p.currentToken();
    showTestDone("Test access(high)", r);

    auto r2 = token1 != token2;
    if(r && !r2){
        LOG("Failed: token not changed after access.");
    }

    showTestDone(__func__, r && r2);
}

/**
 * @brief Priority from high to low,
 * all should pass.
 */
void CommandPriorityTestAccessLow(){
    LOG(std::string("\r\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\r\nStart test for: ") + __func__);

    CommandPriority p;
    
    auto r = testAccess(p, PriorityHigh, 1);
    auto token1 = p.currentToken();
    showTestDone("Test initial access", r);
 
    r = testAccess(p, PriorityLow, 1);
    auto token2 = p.currentToken();
    showTestDone("Test access(low)", r);
    
    auto r2 = token1 != token2;
    if(r && !r2){
        LOG("Failed: token not changed after access.");
    }
    showTestDone(__func__, r && r2);
}

/**
 * @brief Same priority, different command,
 * all should pass.
 */
void CommandPriorityTestAccessSame1(){
    LOG(std::string("\r\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\r\nStart test for: ") + __func__);

    CommandPriority p;
    
    auto r = testAccess(p, PriorityHigh, 1);
    auto token1 = p.currentToken();
    showTestDone("Test initial access", r);

    r = testAccess(p, PriorityHigh, 2);
    auto token2 = p.currentToken();
    showTestDone("Test access(same priority, different command)", r);
    
    auto r2 = token1 != token2;
    if(r && !r2){
        LOG("Failed: token not changed after access.");
    }
    showTestDone(__func__, r && r2);
}

/**
 * @brief Same priority and same command, 
 * all should pass.
 */
void CommandPriorityTestAccessSame2(){
    LOG(std::string("\r\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\r\nStart test for: ") + __func__);

    CommandPriority p;
    
    auto r = testAccess(p, PriorityHigh, 1);
    auto token1 = p.currentToken();
    showTestDone("Test initial access", r);

    r = testAccess(p, PriorityHigh, 1);
    auto token2 = p.currentToken();
    showTestDone("Test access(same priority, same command)", r);
    
    auto r2 = token1 != token2;
    if(r && !r2){
        LOG("Failed: token not changed after access.");
    }
    showTestDone(__func__, r && r2);
}

/**
 * @brief Occupy, priority from low to high,
 * all should pass.
 */
void CommandPriorityTestAccessAndOccupyHigh(){
    LOG(std::string("\r\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\r\nStart test for: ") + __func__);

    CommandPriority p;
    
    auto r = testAccessAndOccupy(p, PriorityLow, 1);
    auto token1 = p.currentToken();
    showTestDone("Test initial accessAndOccupy", r);

    r = testAccessAndOccupy(p, PriorityHigh, 1);
    auto token2 = p.currentToken();
    showTestDone("Test accessAndOccupy(high)", r);

    if(token1 == token2){
        LOG("Failed: Test accessAndOccupy(high) failed, as token is not changed after accessAndOccupy.");
    }

    r = testLeave(p, true, token2);
    showTestDone("Test leave(token2)", r);
}

/**
 * @brief Occupy, priority from high to low,
 * second one should fail.
 * 
 */
void CommandPriorityTestAccessAndOccupyLow(){
    LOG(std::string("\r\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\r\nStart test for: ") + __func__);

    CommandPriority p;
    
    auto r = testAccessAndOccupy(p, PriorityHigh, 1);
    auto token1 = p.currentToken();
    showTestDone("Test initial accessAndOccupy", r);

    r = testAccessAndOccupy(p, PriorityLow, 1, false);
    auto token2 = p.currentToken();
    showTestDone("Test accessAndOccupy(low)", r);

    if(token1 != token2){
        LOG("Failed: Test accessAndOccupy(low) failed, as token is changed when accessAndOccupy failed.");
    }

    r = testLeave(p, true, token1);
    showTestDone("Test leave(token1)", r);
}

/**
 * @brief Low priority can access after leave(current token).
 * 
 */
void CommandPriorityTestAccessAndOccupyLowLeaveCurrentToken(){
    LOG(std::string("\r\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\r\nStart test for: ") + __func__);

    CommandPriority p;
    
    auto r = testAccessAndOccupy(p, PriorityHigh, 1);
    auto token1 = p.currentToken();
    showTestDone("Test initial accessAndOccupy", r);

    r = testAccessAndOccupy(p, PriorityLow, 1, false);
    auto token2 = p.currentToken();
    showTestDone("Test accessAndOccupy(low)", r);
    
    if(token1 != token2){
        LOG("Failed: Test accessAndOccupy(low) failed, as token is changed when accessAndOccupy failed.");
    }

    r = testLeave(p, true, token1);
    showTestDone("Test leave(token1)", r);

    r = testAccessAndOccupy(p, PriorityLow, 1);
    showTestDone("Test accessAndOccupy(low) after leave", r);

    token2 = p.currentToken();
    if(token1 == token2){
        LOG("Failed: Test accessAndOccupy(low) failed, as token is not changed after accessAndOccupy.");
    }
}

/**
 * @brief Low priority can access after leave().
 * 
 */
void CommandPriorityTestAccessAndOccupyLowLeaveNoToken(){
    LOG(std::string("\r\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\r\nStart test for: ") + __func__);

    CommandPriority p;
    
    auto r = testAccessAndOccupy(p, PriorityHigh, 1);
    auto token1 = p.currentToken();
    showTestDone("Test initial accessAndOccupy", r);

    r = testAccessAndOccupy(p, PriorityLow, 1, false);
    auto token2 = p.currentToken();
    showTestDone("Test accessAndOccupy(low)", r);
    
    if(token1 != token2){
        LOG("Failed: Test accessAndOccupy(low) failed, as token is changed when accessAndOccupy failed.");
    }

    r = testLeave(p, true);
    showTestDone("Test leave(other token)", r);

    r = testAccessAndOccupy(p, PriorityLow, 1);
    showTestDone("Test accessAndOccupy(low) after leave via other token", r);

    token2 = p.currentToken();
    if(token1 == token2){
        LOG("Failed: Test accessAndOccupy(low) failed, as token is not changed after accessAndOccupy.");
    }
}

/**
 * @brief Low priority can NOT access after leave(other token).
 * 
 */
void CommandPriorityTestAccessAndOccupyLowLeaveOtherToken(){
    LOG(std::string("\r\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\r\nStart test for: ") + __func__);

    CommandPriority p;
    
    auto r = testAccessAndOccupy(p, PriorityHigh, 1);
    auto token1 = p.currentToken();
    showTestDone("Test initial accessAndOccupy", r);

    r = testAccessAndOccupy(p, PriorityLow, 1, false);
    auto token2 = p.currentToken();
    showTestDone("Test accessAndOccupy(low)", r);
    
    if(token1 != token2){
        LOG("Failed: Test accessAndOccupy(low) failed, as token is changed when accessAndOccupy failed.");
    }

    r = testLeave(p, true, token1 + 1, false);
    showTestDone("Test leave(other token)", r);

    r = testAccessAndOccupy(p, PriorityLow, 1, false);
    showTestDone("Test accessAndOccupy(low) after leave via other token", r);
}

void CommandPriorityTestLeaveViaToken(){
    LOG(std::string("\r\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\r\nStart test for: ") + __func__);

    CommandPriority p; 
    auto r = testAccessAndOccupy(p, PriorityHigh, 1);
    showTestDone("Test initial accessAndOccupy", r);
    auto token = p.currentToken();
    auto otherToken = token + 1;

    r = testLeave(p, true, otherToken, false);
    showTestDone("Test Leave via other token.", r);

    r = testLeave(p, true, token);
    showTestDone("Test Leave via current token", r);

    //leave for not-busy controller is always ok.
    r = testLeave(p, false, otherToken);
    showTestDone("Test Leave after leave via other token", r);

    r = testLeave(p, false, token);
    showTestDone("Test Leave after leave via current token", r);

    r = testLeave(p, false);
    showTestDone("Test Leave after leave", r);
}

void CommandPriorityTestLeaveAll(){
    LOG(std::string("\r\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\r\nStart test for: ") + __func__);

    CommandPriority p; 
    auto r = testAccessAndOccupy(p, PriorityHigh, 1);
    showTestDone("Test initial accessAndOccupy", r);
    auto token = p.currentToken();
    auto otherToken = token + 1;

    r = testLeave(p, true);
    showTestDone("Test Leave", r);

    //leave for not-busy controller is always ok.
    r = testLeave(p, false);
    showTestDone("Test Leave after leave", r);

    r = testLeave(p, false, otherToken);
    showTestDone("Test Leave after leave via other token", r);

    r = testLeave(p, false, token);
    showTestDone("Test Leave after leave via current token", r);
}

/**
 * @brief accessAndOccupy(1, 1) and then accessAndOccupy(1, 2),
 * all should pass.
 * 
 */
void CommandPriorityTestAccessAndOccupySame1(){
    LOG(std::string("\r\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\r\nStart test for: ") + __func__);

    CommandPriority p;
    
    auto r = testAccessAndOccupy(p, PriorityHigh, 1);
    auto token1 = p.currentToken();
    showTestDone("Test initial accessAndOccupy", r);

    r = testAccessAndOccupy(p, PriorityHigh, 2);
    auto token2 = p.currentToken();
    showTestDone("Test accessAndOccupy(same priority, different command)", r);

    if(token1 == token2){
        LOG("Failed: Test accessAndOccupy(same priority, different command) failed, as token is not changed after accessAndOccupy.");
    }
}

/**
 * @brief accessAndOccupy(1, 1) and then accessAndOccupy(1, 1), 
 * second one should fail.
 * 
 */
void CommandPriorityTestAccessAndOccupySame2(){
    LOG(std::string("\r\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\r\nStart test for: ") + __func__);

    CommandPriority p;
    
    auto r = testAccessAndOccupy(p, PriorityHigh, 1);
    auto token1 = p.currentToken();
    showTestDone("Test initial accessAndOccupy", r);

    r = testAccessAndOccupy(p, PriorityHigh, 1, false);
    auto token2 = p.currentToken();
    showTestDone("Test accessAndOccupy(same priority, same command)", r);

    if(token1 != token2){
        LOG("Failed: Test accessAndOccupy(same priority, same command) failed, as token is changed when accessAndOccupy failed.");
    }
}

/**
 * @brief Main test.
 * 
 */
void CommandPriorityTest(){
    testInitialState();

    testAccessHigh();
    CommandPriorityTestAccessLow();
    CommandPriorityTestAccessSame1();
    CommandPriorityTestAccessSame2();

    CommandPriorityTestLeaveViaToken();
    CommandPriorityTestLeaveAll();

    CommandPriorityTestAccessAndOccupyHigh();
    CommandPriorityTestAccessAndOccupyLow();
    CommandPriorityTestAccessAndOccupyLowLeaveCurrentToken();
    CommandPriorityTestAccessAndOccupyLowLeaveNoToken();
    CommandPriorityTestAccessAndOccupyLowLeaveOtherToken();
    CommandPriorityTestAccessAndOccupySame1();
    CommandPriorityTestAccessAndOccupySame2();
}

#endif