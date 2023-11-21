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

//*辅助函数*


//******************

//*容器 声明与初始化
//双向链表
list<int> ilist(10,0);// 构造一个 包含10个0的list 
//双向队列
deque<int> ideque(10); // 构造包含10个int的deque 使用默认初始化 int 0
//单向向量
vector<int> ivector(ilist.begin(),ilist.end()); // 构造一个vector 容器，初始化为迭代器指定范围中的元素拷贝
//前向链表
forward_list<int> i_flist{0,0,0}; //构造一个forward_list 使用列表初始化
// 字符容器
string str("hello world");// 构造初始化
// 数组
array<int,5> iarray{0}; //列表初始化，只写一个元素 后面默认初始化，或者全写

/**
 * @brief 向顺序容器添加元素 push emplace insert。  array 不支持这些操作
 * * 插入元素会导致 vector string deque 迭代器失效
 */
void addElement(){
    // push_back push_front  末尾追加元素 拷贝方式 返回 void
    ivector.push_back(1); 
    ideque.push_front(1);

    // emplace_back emplace_front 头/尾追加元素 直接原地构造方式 
    ilist.emplace_back(1);
    ilist.emplace_front(1);

    // insert  返回指向新添加的第一个元素的迭代器
    str.insert(str.begin(),1); //在指定位置迭代器之前添加元素
    str.insert(str.end(),1,1); // 在指定位置迭代器之前 添加 1 个 1
    str.insert(str.end(),ilist.begin(),ilist.end()); // 在指定位置迭代器之前 插入迭代器范围内的元素
    str.insert(str.begin(),{'h','e','l','l','o'}); //  在指定位置迭代器之前 插入一个元素值列表
}

int main(){
    
    
    return 0;
}