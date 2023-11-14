/**
练习 std::make_heap std::pop_heap std::push_heap
** 通过 先make_heap 再 pop_heap 的操作 可以将容器中 最大/小 值 移至堆尾  默认为最大值，可加入自定义的比较函数
** 简介：用途待补充
** std::make_heap(item.begin(),item.end(),[可选比较参数（默认执行<）]cmp)： 在迭代器所给范围内建立一个最大（最小）堆（取决于比较函数默认为最大堆）
**      ，堆的范围是 [item.begin(),item.end()) 半开半闭

** std::pop_heap(item.begin(),item.end(),[可选比较参数（默认执行<）]cmp)：在迭代器所给范围内交换 item.begin() 和 item.end()-1（尾元素） 的值，
**      然后在[item.begin(),item.end()-1) 范围内重新进行堆排序，相当于移除堆顶元素后，重新排序。 

** std::push_heap(item.begin(),item.end(),[可选比较参数（默认执行<）]cmp)：

** 注：排序后也影响原 迭代器所属容器 内元素的顺序，但是pop_heap() push_heap() 并不会真的对 传入原容器的内容进行 弹出 和 插入！！！！ 仅仅是对生成的堆内元素的影响
*/
#include <iostream>
#include <vector>
#include <algorithm>

template<typename T>
void printvector(std::vector<T> a){
    std::cout<<"vector contain : ";
    for(auto i:a){
        std::cout<<" "<<i;
    }
    std::cout<<std::endl;
}
//* a>b  把小的放前面  a<b 把大的放前面
auto cmp = [](int a, int b){
    return a > b;
};

int main(){
    std::vector<int> vec1{10,8,6,4,2};
    std::cout<<"initially ";
    printvector(vec1);

    //* 按照最小堆排序
    std::make_heap(vec1.begin(),vec1.end(),cmp);
    std::cout<<"按照最小堆排序 ";
    printvector(vec1);

    //* 将堆顶移至容器堆尾，后对其他元素 进行最小堆排序
    std::pop_heap(vec1.begin(),vec1.end(),cmp);
    std::cout<<"将堆顶移至容器堆尾，后对其他元素 进行最小堆排序 ";
    printvector(vec1);

    vec1.push_back(12);//容器尾部追加元素
    std::cout<<"容器尾部追加元素 1  ";
    printvector(vec1);

    //* push_heap 后无法保证堆的特性了？
    std::push_heap(vec1.begin(),vec1.end(),cmp);
    std::cout<<"  ";
    printvector(vec1);

    // std::pop_heap(vec1.begin(),vec1.end(),cmp);
    // std::cout<<"after 第二次 pop_heap before push_heap()";
    // printvector(vec1);

    // std::push_heap(vec1.begin(),vec1.end(),cmp);
    // std::cout<<"after push_heap ";
    // printvector(vec1);

    // vec1.push_back(1);
    // std::push_heap(vec1.begin(),vec1.end(),cmp);
    // std::cout<<"after push_heap2 ";
    // printvector(vec1);
    return 0;
}