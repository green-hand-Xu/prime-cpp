#include <iostream>
#include <vector>




// 括号的结合
void demo1(){
    std::vector<int> vec{1,2,3,4,5,6,7,8,9,10};

    std::cout<<*vec.begin()<<'\n';
    std::cout<<*vec.begin()+1<<'\n';

    //上面两个等价于
    std::cout<<(*vec.begin())<<'\n';
    std::cout<<(*vec.begin())+1<<'\n';
}

// 为表达式添加括号 说明求值过程及结果。
void demo2(){
    int a,b;
    //不加括号
    a=12/3*4+5*15+24%4/2;
    //加括号
    b=12/(3*4)+(5*15)+(24%4/2); 

    std::cout<<"a:"<<a<<'\n'<<"b:"<<b<<'\n';

}

int main(){

   demo2();

    return 0;
}