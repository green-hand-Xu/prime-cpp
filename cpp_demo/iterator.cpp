#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
*迭代器的使用
*可以用 a.begin()!=a.end() 语句判断 a 是不是空内容
*为空则返回的都是尾后迭代器
*   *iter 表示迭代器所指的元素的引用
*声明迭代器类型变量 
*vector<int>::iterator it;  可用 it 对元素进行读写
*string::iterator it;       可用 it 读写单个字符
*string::const_iterator     加了const_iterator后 就变成常量的了 类似于常量指针，只能读 不能写元素

*begin 和 end 运算符的返回的具体类型由对象是否为常量决定， 为常量 返回 const_iterator ,否则返回 iterator

* v.cbegin() v.cend() 固定返回 const_iterator

*不能在范围for循环中向 vector 对象添加元素;
*任何一种可能改变vector对象容量的操作，都会使该vector对象的迭代器失效。
*但凡是使用了迭代器的循环体，都不要向迭代器所属的容器添加元素。

*/

void shouzimudaxie(){
    string s("some string");
    //首字母变大写
    if (s.begin()!=s.end()){
        auto it = s.begin();
        *it = toupper(*it);
        cout<<s<<endl;
    }
    //全部变大写
    for(auto it=s.begin();it!=s.end();++it){
        //判断遇到空格则跳过
        if(isspace(*it)){
            continue;
        }
        *it = toupper(*it);
    }
    cout<<s<<endl;
}

// 翻倍 容器内元素值
void fanbei(){
    struct str
    {
        std::string str;
    };
    
    vector<str> vec;
    std::string a;
    cout<<"输入string值存入 容器中 , 输入 z 字符结束。"<<endl;
    while (cin>>a && a != "z")
    {
        str b ;
        b.str = a;
        vec.push_back(b);
    }
    // 容器内首字母大写
    for(auto v = vec.begin() ; v != vec.end(); ++v){
        v->str =toupper((v->str)[0]) ;
    }
    for (auto v = vec.begin() ; v != vec.end(); ++v)
    {
        std::cout<<v->str<<" "<<std::endl;
    }
}

//使用迭代器完成二分查找
void erfenchazhao(){
    string text = "abcdefghigklmn";
    auto beg = text.begin();
    auto end = text.end();
    auto mid = text.begin()+(end-beg)/2;
    while (mid != end && *mid != 'n')
    {
        if('n'<*mid){
            end = mid;
        }else{
            beg=mid;
        }
        mid = beg+(end-beg)/2;
    }

    cout<<*mid<<endl;
}

int main(){

    fanbei();


    return 0;
}