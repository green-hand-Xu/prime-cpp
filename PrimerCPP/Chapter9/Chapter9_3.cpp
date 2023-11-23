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

//*辅助*
template<typename T >
void print(T t){
    for(auto s : t){
        cout<< s <<" ";
    }
    cout<<endl;
}

void printAll(){
    cout<<"ilist ";
    print(ilist);
    cout<<"ideque ";
    print(ideque);
    cout<<"ivector ";
    print(ivector);
    cout<<"i_flist ";
    print(i_flist);
    cout<<"str ";
    print(str);
    cout<<"iarray ";
    print(iarray);
}

//******************

/**
 * @brief 向顺序容器添加元素 push emplace insert。  array 不支持这些操作
 * * 插入元素会导致 vector string deque 迭代器失效
 */
void addElement(){
    // push_back push_front  末尾追加元素 拷贝方式 返回 void
    ivector.push_back(1); 
    ideque.push_front(1);

    // emplace_back emplace_front emplace 头/尾 指定迭代器之前追加元素 直接在容器中构造对象 传入元素需要匹配构造函数 
    ilist.emplace_back(1);
    ilist.emplace_front(1);
    ilist.emplace(ilist.begin(),2); 

    // insert  返回指向新添加的第一个元素的迭代器 插入元素类型必须与容器保存类型相同，否则不会插入元素。
    string str1{" hhh "};
    str.insert(str.begin(),'1'); //在指定位置迭代器之前添加元素
    str.insert(str.end(),1,'2'); // 在指定位置迭代器之前 添加 1 个 2
    str.insert(str.end(),str1.begin(),str1.end()); // 在指定位置迭代器之前 插入迭代器范围内的元素
    str.insert(str.begin(),{'h','e','l','l','o'}); //  在指定位置迭代器之前 插入一个元素值列表

    printAll();
}

/**
 * @brief 访问容器中的元素
 * 访问方式有 下标访问 迭代器访问 at back front
 * *注：访问不存在的位置和空容器的行为是未定义的，需要自行处理这类情况
 * * at 仅适用于 string vector deque array
 */
void accessElement(){
    if(str.empty()){
        cout<<"容器内容为空"<<endl;
    }else{
        cout<<"str[1] = "<<str[1]<<endl; //下标访问
        cout<<"str.front() = "<<str.front()<<endl; // 访问首元素
        cout<<"str.back() = "<<str.back()<<endl; // 访问尾元素
        cout<<"str.at(0) = "<<str.at(0)<<endl; // 访问 下标 0 的元素
    }
    //* ilist[0]; list 不支持随机访问 所以也不支持 at() 访问
}

/**
 * @brief 删除容器中的元素
 * 删除方式有 pop_back pop_front erase(p) erase(b,e) clear()
 ** 注：删除操作会改变容器大小，所以array 不适用
 ** 删除元素 会导致 迭代器失效
 ** 同访问一样 删除不存在的位置和空容器的行为是未定义的，需要自行处理这类情况
 */
void erraseElement(){

}

int main(){
    accessElement();
    
    return 0;
}