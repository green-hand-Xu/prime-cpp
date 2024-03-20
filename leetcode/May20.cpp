/**
57. 插入区间
给你一个 无重叠的 ，按照区间起始端点排序的区间列表 intervals，
其中 intervals[i] = [starti, endi] 表示第 i 个区间的开始和结束，
并且 intervals 按照 starti 升序排列。同样给定一个区间 newInterval = [start, end] 表示另一个区间的开始和结束。

在 intervals 中插入区间 newInterval，使得 intervals 依然按照 starti 升序排列，
且区间之间不重叠（如果有必要的话，可以合并区间）。

返回插入之后的 intervals。

注意 你不需要原地修改 intervals。你可以创建一个新数组然后返回它。

示例 1：
输入：intervals = [[1,3],[6,9]], newInterval = [2,5]
输出：[[1,5],[6,9]]

示例 2：
输入：intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
输出：[[1,2],[3,10],[12,16]]
解释：这是因为新的区间 [4,8] 与 [3,5],[6,7],[8,10] 重叠。

**题目背景
    数组相关练习
**解题思路
    1、在原数组中找到新插入区间下限和上限所在索引位置记为 begIndex endIndex
    2、判断begIndex、endIndex是否为同一索引位置。
        a.是同一索引位置，将原索引间隔上下标与插入索引上下标进行对比，取最小值做下标，最大值做上标 [min,max] ,然后赋值给原数组该索引内容上
        b.不是同一索引位置,下标取最小值，上标取最大值,记录内容为[min,max] 放在索引为下标所在位置上，同时删除上限所在索引至下限索引之间的所有内容。
    3、特殊情况 上下标完全包括原数组，那么结果就是 newInterval 本身。
*/


#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
    auto fun1 = [intervals,newInterval](){
        auto ret = std::find_if(intervals.begin(),intervals.end(),[](vector<int> src){
            auto a = src.front()<=src.front()&&src.back()>=src.front();
            return a;
        });
        return ret;
    };

    if (fun1()!=intervals.end())
    {
        /* code */
    }
    
}

int main(){
    vector<vector<int>> intervals = {{1,3},{6,9}};
    vector<int> newInterval = {4,8};
    insert(intervals,newInterval);
}