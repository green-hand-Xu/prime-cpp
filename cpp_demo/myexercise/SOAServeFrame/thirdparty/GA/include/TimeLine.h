#ifndef __TimeLine_H__
#define __TimeLine_H__

#include <string>
#include <map>
#include <list>
#include <functional>
#include <chrono>
#include <memory>

using namespace std::chrono;
using namespace std::chrono_literals;

/**
 * @brief 一个时间线标记类，提供时间线标记和输出。
 * 可以通过构造函数或setOutput提供自定义输出，以支持输出到任何你想要的地方。
 * 
 * 我们的设计目标是为全局提供一个时间线标记类，
 * 为每一个动作、每一步进行时间标记，所以我们标记时间是有两个参数的（动作和步骤）。
 * 
 * 所以输出时间有多个参数，
 * show 输出所有数据。
 * show(action) 只输出某个动作的时间线。
 * 
 * 如果你想全局复用一个对象，我们还提供清理时间标记的方法clear，
 * 如果你只是想在临时场景中进行时间标记，那么clear应该用不到。
 * 
 * 
 * 
 * 最基础的用法便是声明一个类，然后调用mark。
 * TimeLine tl;
 * 
 * tl.mark("FieldCacheHelper", "Start");
 * ... ...
 * tl.mark("FieldCacheHelper", "Created");
 * ... ...
 * tl.mark("FieldCacheHelper", "Load");
 * ... ...
 * tl.mark("FieldCacheHelper", "Save");
 * 
 * 最后调用show输出结果，
 * 输出默认为std::cout，
 * 并且自动以“|”分割，
 * 并且根据需要输出的时间点计算每一步时间间隔。
 * 下面是我们自己统计一个代码性能的输出数据：
    |Action             |Step               |BeginAt        |Cost
    |FieldCacheHelper   |Start              |0.000000ms     |0.000000ms
    |FieldCacheHelper   |Created            |76.355400ms    |76.355400ms
    |FieldCacheHelper   |Load               |94.575400ms    |18.220000ms
    |FieldCacheHelper   |load again         |105.375600ms   |10.800200ms
    |FieldCacheHelper   |Save               |272.146200ms   |166.770600ms
    |FieldCacheHelper   |Save after save    |272.458400ms   |0.312200ms
    |FieldCacheHelper   |load after updated |318.636400ms   |46.178000ms
 * 
 */

struct TimeLineMark
{
    std::string action;
    std::string step;
    steady_clock::time_point time;
};

/**
 * @brief Handler to handle a single line of text outputing.
 */
using TimeLineOutputHandler = std::function<void(const std::string&)>;
using TimeLineItemFilter = std::function<bool(const TimeLineMark&)>;

class TimeLine
{
public:
    /**
     * @brief Construct a new Time Table object, use std::cout.to show time table.
     * 
     */
    TimeLine();

    /**
     * @brief Construct a new Time Table object, use given output handler to show time table.
     * 
     * @param output 
     */
    explicit TimeLine(TimeLineOutputHandler output);

    TimeLineOutputHandler getOutput();
    void setOutput(TimeLineOutputHandler output);

    /**
     * @brief Mark a time point for the step of the given action.
     * 
     * @param action Name of the action.
     * @param step Step or details of action.
     */
    void mark(std::string action, const std::string& step);

    /**
     * @brief Clear marked time points for ALL actions.
     * 
     */
    void clear();

    /**
     * @brief Clear ALL time points for the given action.
     * 
     * @param action 
     */
    void clear(const std::string& action);

    /**
     * @brief Clear time point for the step of the action.
     * 
     * @param action 
     * @param step 
     */
    void clear(const std::string& action, const std::string& step);

    /**
     * @brief Show all marked time points of the given action.
     * 
     * @param action 
     */
    void show(const std::string& action);

    /**
     * @brief Show all marked time points.
     * 
     */
    void show();

protected:
    inline void defaultOutput(const std::string& line);

    /**
     * @brief Show filtered items.
     * 
     * @note Will show all when filter is nullptr.
     * 
     */
    inline void showItems(TimeLineItemFilter filter);

private:
    TimeLineOutputHandler _output{nullptr};
    std::list<TimeLineMark> _marks;
};


#endif