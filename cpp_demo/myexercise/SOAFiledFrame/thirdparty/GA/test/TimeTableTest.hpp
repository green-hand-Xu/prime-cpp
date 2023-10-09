#ifndef __TimeTableTest_HPP__
#define __TimeTableTest_HPP__

#include <iostream>
#include <thread>
#include "TimeLine.h"

void test(){
    auto isOutput = false;
    TimeLine tt([&isOutput](auto line){
        std::cout << line;
        isOutput = true;
    });

    tt.mark("action1", "step 1");

    tt.mark("action1", "step 2");

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    tt.mark("action1", "step after sleep(100ms)");

    tt.show();

    if(isOutput){
        std::cout << "Test Passed, log is being outputed";
    }else{
        std::cout << "Text Failed: log has not been outputed";
    }
}

#endif