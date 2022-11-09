#include <iostream>
#include <vector>
#include <list>
/*
*数组
*定义数组，数组的长度 必须是一个常量表达式 如字面值 或者 constexpr 修饰的
*标准函数库 begin() end() 获取首元素指针 和尾后元素的指针
*多维数组（数组的元素也是数组）
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

    //创建多维数组  
    int ia[3][4];//大小为3的数组，每个元素是含有4个整数的数组
    int arr[10][20][30] = {0};// 大小为10的数组，他的每个元素都是大小为20的数组，这些数组元素是含有30个整数的数组。

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

//二维数组，元素的位置索引作为他的值
void erweishuzu() {
    constexpr size_t rowCnt = 3, colCnt = 4;
    int ia[rowCnt][colCnt]; //12个未初始化的元素
    for (size_t i = 0; i != rowCnt; i++){
        for (size_t j = 0;j != colCnt; j++){
            ia[i][j] = i * colCnt +j;
        }
    }

    cout<<"输出的是数组中存的数组的首地址："<<std::endl;

    for(auto a:ia){
        cout<<a<<" ";
    }
    cout<<'\n';
    cout<<"输出的是数组中存的数"<<std::endl;
    for(auto &a:ia){
        for(auto b:a){
            cout<<b<<" ";
        }
    }
    cout<<std::endl;
}

void zhizhenandshuzu(){
    constexpr size_t rowCnt = 3, colCnt = 4;
    int ia[rowCnt][colCnt];
    for (size_t i = 0; i != rowCnt; i++){
        for (size_t j = 0;j != colCnt; j++){
            ia[i][j] = i * colCnt +j;
        }
    }

    int (*p)[4] = ia; //p指向ia的内层元素 是个包含4个整数的数组
    p = &ia[2];
    
    for(auto p = ia ; p != ia+3 ;++p){
        for(auto q = *p ; q != *p+4 ; ++q){
            cout<< *q << ' ';
        }
        cout<<'\n';
    }

}

//不使用 auto 或 decltype 关键字 对数组输出  （理解具体类型）
void shuzu()
{
    constexpr size_t rowCnt = 3, colCnt = 4;
    int ia[rowCnt][colCnt];
    for (size_t i = 0; i != rowCnt; i++){
        for (size_t j = 0;j != colCnt; j++){
            ia[i][j] = i * colCnt +j;
        }
    }

    // 1、 使用普通for 指针形式  //TODO:仔细理解！
    for(int (*i)[4] = ia ; i!=ia+3 ; i++){
        for(int *n=*i ; n != *i+4 ; n++){
            cout<<*n<<' ';
        }
        cout<<'\n';
    }

    //2、使用范围for循环    //TODO:仔细理解 和普通for循环的不同 范围for 循环元素 要有迭代器操作才行
    for(int (&i)[4]:ia){
        for(int j:i){
            cout<<j<<' ';
        }
        cout<<'\n';
    }

    //3、使用普通for 下标形式
    for(int i=0; i !=3 ; i++){
        for(int j = 0 ; j !=4 ; j++){
            cout<<ia[i][j]<<' ';
        }
        cout<<'\n';
    }

}


int main(){
    shuzu();
}