#include "TimeLine.h"
#include <iostream>

TimeLine::TimeLine()
    : TimeLine(std::bind(&TimeLine::defaultOutput, this, std::placeholders::_1))
{
    
}

TimeLine::TimeLine(TimeLineOutputHandler output)
    : _output(output)
{
}

TimeLineOutputHandler TimeLine::getOutput()
{
    return _output;
}

void TimeLine::setOutput(TimeLineOutputHandler output)
{
    _output = output;
}

void TimeLine::mark(std::string action, const std::string& step)
{
    _marks.emplace_back((TimeLineMark){
        action, 
        step, 
        steady_clock::now()
    });
}

void TimeLine::clear()
{
    _marks.clear();
}

void TimeLine::clear(const std::string& action)
{   
    _marks.remove_if([&action](const TimeLineMark& mark)->bool{
        return mark.action == action;
    });
}

void TimeLine::clear(const std::string& action, const std::string& step)
{
    _marks.remove_if([&action, &step](const TimeLineMark& mark)->bool{
        return mark.action == action && mark.step == step;
    });
}

void TimeLine::show(const std::string &action)
{
    showItems([action](const TimeLineMark& mark)->bool{
        return mark.action == action;
    });
}

void TimeLine::show()
{
    showItems(nullptr);
}

void TimeLine::defaultOutput(const std::string &line)
{
    std::cout << line << "\r\n";
}

inline void TimeLine::showItems(TimeLineItemFilter filter)
{
    if(!_output){
        return;
    }
    
    if(_marks.size() <= 0){
        _output("No marked times found.");
        return;
    }

    auto size = 0; 
    steady_clock::time_point last;
    steady_clock::time_point begin;
    for (auto it : _marks) {
        if(filter && !filter(it)){
            continue;
        }

        if(size == 0){
            begin = it.time;
            last = it.time;
            _output("|Action |Step |BeginAt |Cost");
        }
        duration<double, std::milli> current{it.time - begin};
        duration<double, std::milli> cost{it.time - last};
        _output("|" + it.action + " |" + it.step + " |" + std::to_string(current.count()) + "ms |" + std::to_string(cost.count()) + "ms");

        last = it.time;
        ++size;
    }
}
