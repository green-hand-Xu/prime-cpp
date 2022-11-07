#include <iostream>
#include <vector>
/*
*数组
*定义数组，数组的长度 必须是一个常量表达式 如字面值 或者 constexpr 修饰的
*标准函数库 begin() end() 获取首元素指针 和尾后元素的指针
*/
using namespace std;

//显示初始化
void Explicit_initialization(){
    const unsigned sz = 3;
    int ial[sz] = {0,1,2};
    int a2[] = {2,3,4};
    int a3[5] = {3,4,5};
    string a4[3] = {"hi","bye"};
    int a5[2] = {0,1};

    //创建数组的指针
    int (*ptra2)[3] = &a2;
    //创建数组的引用
    int (&refa3)[5] = a3;

    //存放指针的数组
    int *ptrs[10];

    for(int i=0;i != 10;i++){
        cout<<a2[i]<<" ";
    }
    cout<<endl;
}

//注意值初始化和默认初始化的区别
string sa[10];
int ia[10];

//3.41 用整型数组初始化一个Vector对象
void initVector(){
    int IntArray[10]={1,2,3,4,5,6,7,8,9,0};
    vector<int> VecInt(begin(IntArray),end(IntArray));

    for(auto i:VecInt){
        cout<<i<<endl;
    }
}

//begin() And end()
void headandtail(){
string sa2[10];
    int ia2[10] = {0};
    //获取 首元素指针和尾后元素指针
    int *beg = begin(ia2);
    int *last = end(ia2);

    for(auto i=beg;i!=last;i++){
        cout<<*i<<" ";
    }

    cout<<endl;
}

//3.42 将含有整数元素的vector对象拷贝给一个整型数组
void copyv2a(){

    int a[10]{0};
    //创建一个含有10个1的vector对象
    vector<int> vec(10,1);

    auto beg=begin(a);
    auto endl=end(a);

    int b = 0;
    for(auto i=beg;i!=endl;i++){
        *i=vec[b];
        b++;
    }
    cout<<std::endl;
    cout<<std::endl<<"vec内容"<<std::endl;
    for(auto v:vec){
        cout<<v<<" ";
    }
    cout<<std::endl;
    cout<<"a[]内容"<<std::endl;
    for(auto c:a){
        cout<<c<<" ";
    }
    cout<<std::endl;
}

int main(){
    copyv2a();
}