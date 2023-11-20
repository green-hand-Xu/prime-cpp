/**
 * @file Chapter9_3.cpp
 * @author XuYingBo (you@domain.com)
 * @brief 顺序容器操作练习
 * @version 0.1
 * @date 2023-11-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <iostream>

#include <list>
#include <deque>
#include <vector>
#include <forward_list>
#include <string>
#include <array>

using namespace std;
//双向链表
list<int> ilist(10,0);// 构造一个 包含10个0的list 
//双向队列
deque<int> ideque(10); // 构造包含10个int的deque 使用默认初始化 int 0
//单向向量
vector<int> ivector(ilist.begin(),ilist.end()); // 构造一个vector 容器，初始化为迭代器指定范围中的元素拷贝
//前向链表
forward_list<int> i_flist{1,2,3}; //构造一个forward_list 使用列表初始化
// 字符容器
string str;
// 数组
array<int,20> iarray; 

int main(){
    
    
    return 0;
}