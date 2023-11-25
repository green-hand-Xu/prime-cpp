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
 * * vector string 不支持push_front
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
 ** vector string 不支持pop_front
 */
void erraseElement(){
    ivector.pop_back();//删除尾元素
    ilist.pop_front();//删除首元素
    ivector.erase(ivector.begin());//删除迭代器指向的元素 返回被删除元素之后的迭代器
    ilist.erase(ilist.end(),ilist.end()); //删除迭代器指向范围内的元素
    str.clear();// 删除容器中 所有元素


    printAll();
}

/**
 * @brief forward_list (单向链表) 特殊的操作
 * (c)before_begin  insert_after emplace_after erase_after
 ** 由于单向链表的特性， 这些插入删除方法 操作的是 迭代器指向位置之后的位置
 */
void specialOperator(){
    forward_list<int> flist;
    flist.insert_after(flist.before_begin(),1);//在首前迭代器之后添加一个元素
    flist.emplace_front(2);//在首位置添加，直接构造方式
    flist.emplace_after(flist.begin()++,3);//在指定位置之后添加一个元素，直接构造方式
    flist.erase_after(flist.begin()++);//删除指定位置之后的元素
    print(flist);
}

/**
 * @brief 移除 单向列表的奇数元素， 添加至 vector中
 * 
 */
void eraseSpecificElement(){
    forward_list<int> ilist{0,1,2,3,4,5,6,7,8,9,10,11};
    vector<int> dst;
    auto curr = ilist.begin(); //指向首元素
    auto prev = ilist.before_begin(); //指向首前元素
    while (curr != ilist.end())
    {
        if (*curr % 2 != 0)
        {
            dst.push_back(*curr);
            curr = ilist.erase_after(prev);//删除奇数元素，并把curr位置挪到删除元素之后的位置
        }else{
            //不是基数 将前一个元素指针指向当前位置 并 将当前位置指针后移 
            prev = curr;
            curr++;
        }
    }
    print(ilist);
    print(dst);
}

/**
 * @brief 9.3.4   9.28 习题练习
 * 
 * @param flist 
 * @param str1 
 * @param str2 
 */
void exe9_3_4(forward_list<string> flist, string str1 , string str2){
    if (flist.empty())
    {
        return;
    }
    print(flist);

    auto index = flist.begin();
    while (index != flist.end())
    {
        if (*index == str1)
        {
            index = flist.insert_after(index,str2);
        }else{
            index++;
        }
    }
    print(flist);
}

void exe9_3_4test(){
    forward_list<string> flist{"hello","hello"};
    string str1{"hello"};
    string str2{"world"};
    string str3{"a"};
    exe9_3_4(flist,str1,str2);
    exe9_3_4(flist,str3,str2);
}

/**
 * @brief 改变容器的大小
 *  resize
 *  改变大小后 容器的 迭代器 以及相关的引用、指针可能会失效
 *  扩容后自动使用元素默认初始化，或者主动填入构造初始化进行元素追加
 *  缩小容器  会将多余的元素删除
 *  array不支持改变大小 需要动态重新手动分配
 */
void resizecapacity(){  
    ilist.resize(15);// 扩容到15 使用int类型的值初始化为0
    ilist.resize(20,1);// 扩容到20 初始化成 1
    print(ilist);
}

/**
 * @brief 单向链表 循环改变容器内容
 * 
 */
void exe9_3_1(){
    forward_list<int> vi = {0,1,2,3,4,5,6,7,8,9,0};
    auto iter = vi.begin();
    auto before_iter = vi.before_begin();
    while (iter != vi.end())
    {
        if(*iter%2){
            iter = vi.insert_after(iter,*iter); // 返回指向新插入元素的指针，与insert的区别是 insert在给定迭代器之前插入，insert_after 是在之后
            before_iter = iter;
            iter++;//移动指针到下一个未处理的元素
        }else{
            iter = vi.erase_after(before_iter); // 返回删除元素之后的位置
        }
    }
    
    print(vi);

}

int main(){
    
    exe9_3_1();
    return 0;
}