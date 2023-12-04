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
void resize(){  
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

/**
 * @brief 改变容器占用内存大小 
 * capacity:获取容量大小 
 * 以下操作与实际操作系统有关联
 * reserve：修改容量大小（只增不减） shrink_to_fit 容量大小裁剪至和元素数量大小一致（不一定真的退还）
 */
void resizecapacity(){
    vector<int> vec;
    cout<<vec.capacity()<<endl;//显示当前vec的容量大小
    vec.shrink_to_fit();//容量大小裁剪至和元素数量大小一致
    cout<<vec.capacity()<<endl;
    vec.reserve(100);//修改容量大小（只增不减）
    cout<<vec.capacity()<<endl;
}

/**
 * @brief 一些string 其他的构造方法 
 * string s(cp,n):cp 为数组。n为拷贝数量，默认为前n个。数组需要以/n结尾
 * string s(s2,pos2)：从s2 pos2位置开始拷贝 pos2 不能大于s2的总长度 size()
 * string s(s2,pos2，n)：从s2 pos2位置开始拷贝 n 个字符 pos2 不能大于s2的总长度 size()
 * * substr(pos,n):字符串截取 从pos开始的n个字符
 * * string 的 insert 和 erase 还额外支持 下标相关的操作 
 * * 例如：insert(pos,n,s) 从pos位置添加n个s元素 erase(pos,n) 从pos位置开始删除n个元素 注：POS 可以是 c 风格字符串数组
 * * append(str) 末尾追加 和 replace(range,args) 删除s中range范围内的字符，替换为args指定的长度，range可以是下标和长度的组合，或者一对迭代器
 */
void special_str_operator(){
    char ch[10]{'h','e','l','o','w','o','r','l','d'};
    string str1{"111 222"};

    string str2(ch,5);
    string str3(str1,0,3);
    string str4(str1,2);

    string str5 = str1.substr(1);
    cout<<str2<<" "<<str3<<" "<<str4<<" "<<str5<<endl;

    string str6{"AAAA"};
    str6.insert(4,"1");
    cout<<str6<<endl;
    str6.erase(0,1);
    cout<<str6<<endl;
    str6.insert(str6.size()-1,ch); //在size()-1 之前位置加入元素
    cout<<str6<<endl;
    str6.insert(str6.size(),ch+4);
    cout<<str6<<endl;
    //* 替换str6 内容为 ch+4位置开始 连续5个元素的内容 ，或者只写开始位置，默认以字符串末尾为结束位置
    str6.assign(ch+4,5);
    cout<<str6<<endl;
    str6 = {"ABCDE"};
    str6.replace(1,3,"s"); //从str6 第一个位置开始删除3个元素 然后插入 "s"
    cout<<str6<<endl;
}

/**
 * @brief 习题 9.5.2-9.43
 * 
 */
void exec_9_43(string &s , string oldVal , string newVal){
    //* 1、使用 insert + replace
    for (auto i = 0; i < s.size();)
    {
        if (s.substr(i,oldVal.size()) == oldVal)
        {
            s.erase(i,oldVal.size());
            s.insert(i,newVal);
            i+=oldVal.size();
        }
        ++i;
    }
}

void exec_9_44(string &s , string oldVal , string newVal){
    //* 2、使用replace
    for (auto i = 0; i < s.size();)
    {
        if (s.substr(i,oldVal.size()) == oldVal)
        {
            s.replace(i,oldVal.size(),newVal);
            i+=oldVal.size();
        }
        ++i;
    }
}

void test_9_43(){
    std::string s1 = "hello world";  
    std::string oldVal1 = "world";  
    std::string newVal1 = "Python";  
    exec_9_44(s1, oldVal1, newVal1);  
    std::cout << s1 << std::endl; // Output: hello Python  
  
    std::string s2 = "abcd";  
    std::string oldVal2 = "cd";  
    std::string newVal2 = "efg";  
    exec_9_44(s2, oldVal2, newVal2);  
    std::cout << s2 << std::endl; // Output: abefgefg  
  
    std::string s3 = "1234567890";  
    std::string oldVal3 = "345";  
    std::string newVal3 = "ABC";  
    exec_9_44(s3, oldVal3, newVal3);  
    std::cout << s3 << std::endl; // Output: 12ABC67890  
}

/**
 * @brief string 搜索操作
 * *查找第一次/最后一次出现的位置
 * find rfind find_first_of  find_last_of  
 * *查找第一个/最后一个 不在args 中的字符
 * find_first_not_of   find_last_not_of  
 * *参数都为args ：可以为 c pos(位置) , s2 pos , cp(字符数组指针) pos , cp(字符数组指针) ,pos(位置),n(前n个字符)
 * *可以通过修改位置参数 在字符串中循环的搜索子字符串出现的所有位置
 */
void stringSerch(){
    string src1{"aaabcdefgha123456"};
    string src3{"1234p56789"};
    char src2[]={'a','b','c'};
    char src4[]={'1','2','3','4','5','6','7','8','9','0'};

    std::cout<<src1.find('a')<<std::endl;//查找第一次出现的位置
    std::cout<<src1.rfind("gha")<<std::endl;//查找最后一次出现的位置
    std::cout<<src1.find('a',2)<<std::endl;//从第二个位置开始，查找第一次出现的位置
    std::cout<<src1.find('a',1)<<std::endl;//从第1个位置开始，查找第一次出现的位置
    std::cout<<src1.rfind(src2,src1.size(),3)<<std::endl;//从最后一个字符开始,查找最后一次出现的位置

    std::cout<<src1.find_first_of("kle")<<std::endl;//在src1中查找arg中任何一个字符第一次出现的位置。
    std::cout<<src1.find_first_not_of("kle")<<std::endl;//在src1中查找第一个不在args中的字符。

    std::cout<<src3.find_last_of(src2)<<std::endl;//在src1中查找arg中任何一个字符最后一次出现的位置。
    std::cout<<src3.find_last_not_of(src4)<<std::endl;//在src1中查找最后一个不在args中的字符。
}

int main(){
    stringSerch();
    return 0;
}