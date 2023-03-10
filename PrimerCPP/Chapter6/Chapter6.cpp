// #define NDEBUG 1

#include <iostream>
#include <initializer_list>
#include <cstdlib>
//assert 预处理宏头文件
#include <cassert>


using namespace std;

/**
 * @brief 6.22 交换两个 int 指针
 *          指向指针对象的引用
 * @param A 
 * @param B 
 */
void swap(int* &A,int* &B){
    int *C;
    C = A;
    A = B;
    B = C;
}

/**
 * @brief 6.23 输出整数
 * 
 * @param i 
 */
void print(int i){
    cout<<"i = "<<i<<endl;
}

/**
 * @brief 6.23 输出数组
 *          形参为数组首地址指针
 *          可以显式传数组大小，或者使用标准库函数传首尾地址，或者C风格字符串判断 空字符
 * @param i 
 */
void print(const int *beg ,const  int *end){
    int num = 0;
    for(const int *i = beg ; i != end ; i++){
        cout<<"int["<<num<<"] = "<<*i<<endl;
        ++num;
    }
}
/**
 * @brief 6.24 传数组 和 传数组首地址 是两个概念
 *        可以用引用的方式 传整个数组 因为数组大小是构成数组类型的一部分，所以使用引用时，实参必须和形参大小类型一致
 * 
 * @param ia 
 */
void print(const int (&ia)[10])
{
	for (size_t i = 0; i != 10; ++i)
		cout << ia[i] << endl;
}

/**
 * @brief 参数是initializer_list类型的对象
 *          功能是计算列表中所有元素的和
 * @param li 
 */
int demo(initializer_list<int> li){
    int sum = 0;
    for(auto e :li){
        sum += e;
    }
    return sum;
}
/**
 * @brief 声明一个返回数组指针的函数
 *        数组的维度必须跟在函数名字之后
 * @return int 
 */
int (*shuzu(int i))[10];

//声明 尾置返回类型函数
auto func(int i) -> int (*)[10];

//使用别名 声明 返回数组指针的函数
using arr = int[10];
arr* func2(int i);

//声明带有默认实参的函数  *一旦某个形参被赋予了默认值，它后面所有的形参都必须有默认值
using sz = string::size_type;
string screen(sz ht = 24, sz wid = 80 , char backgrnd = ' ' );
//默认实参初始值 也可以为表达式，只要类型能转换成形参所需类型即可(不能是局部变量)
sz ht(){
    cout<<"1"<<endl;
    return 0;
}

sz ht2();
string screen2(sz ht = ht2(), sz wid = 80 , char backgrnd = ' ' );

string make_plural(size_t ctr, const string &word, const string &ending = "s")
{
	return (ctr > 1) ? word + ending : word;
}

void fun1(){
    
}

int main(){
//------------------ 6.22---------------------
    int O = 1;
    int P = 2;
    int *A = &O; // 1
    int *B = &P; // 2
    swap(A,B); // A=2 B=1
    cout<<"A= "<<*A<<" B= "<<*B<<endl;
//------------------6.5.3节---------------------
    assert(0);
//------------------6.23----------------------
    int i = 0;
    int j[2]={0,1};
    print(i);
    print(begin(j),end(j));
//------------------6.24----------------------
    int p[10] = {1,2,3,4};
    print(p);
//------------------6.27----------------------
    cout<<"demo() = "<<demo({1,2,3,4,5})<<endl;
//return EXIT_SUCCESS或EXIT_FAILURE 是定义在cstdlib头文件里的预处理变量 表示成功或者失败
// 预处理变量 不能加 std:: 也不能在 using声明中出现。
    // return EXIT_SUCCESS;
//------------------6.42---------------------------
    std::cout << make_plural(2, "success", "es") << std::endl;
	std::cout << make_plural(2, "failure") << std::endl;
    return 0;
}

/**
 * @brief 带参数的main函数
 *          argv[0] 保存程序的名字，非用户输入。
 *          接下来 依次传递命令行提供的实参进数组，最后一个指针之后的元素值保证为0.
 * @param argc 
 * @param argv 
 * @return int 
 */
// int main(int argc,char *argv[]){

//     cout<<argv[0]<<endl; 
//     cout<<argv[1]<<endl;
//     // cout<<sizeof(argv)<<endl; 
//     cout<<argv[7]<<endl;
// }