#include <iostream>

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


int main(){
//------------------ 6.22---------------------
    int O = 1;
    int P = 2;
    int *A = &O; // 1
    int *B = &P; // 2
    swap(A,B); // A=2 B=1
    cout<<"A= "<<*A<<" B= "<<*B<<endl;
//------------------6.23----------------------
    int i = 0;
    int j[2]={0,1};
    print(i);
    print(begin(j),end(j));
//------------------6.24----------------------
    int p[10] = {1,2,3,4};
    print(p);
    return 0;
}