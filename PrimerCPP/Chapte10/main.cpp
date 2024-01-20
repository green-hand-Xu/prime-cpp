/**
 * @file main.cpp
 * @author XuYingBo (you@domain.com)
 * @brief 第十章 泛型算法相关练习
 * @version 0.1
 * @date 2023-12-12
 ** 只读算法
 ** 写容器元素算法
 ** 重排容器元素的算法 
 * @copyright Copyright (c) 2023
 * 
 */

#include <iostream>
#include <algorithm>  //大部分泛型算法的头文件
#include <numeric>
#include <utils.hpp>
using namespace std;

/**
 * * 只读算法
 * @brief count(range,value) 返回给定值在序列中出现的次数。
 * 
 */
void gf_count(){
    vector<int> vec{1,2,3,4,5,4,5,5,5,6,7,4,0};
    string str{"hello"};
    cout<<"4 出现的次数为："<<count(vec.begin(),vec.end(),4)<<endl;
    cout<<"5 出现的次数为："<<count(vec.begin(),vec.end(),5)<<endl;
    cout<<"l 出现的次数为："<<count(str.begin(),str.end(),'l')<<endl;
}

/**
 * * 只读算法
 * @brief accumulate(range,sum) 计算范围内元素的和，sum 参数为初始值，其类型决定了计算时的算术运算符
 * 头文件 numeric
 */
void gf_accumulate(){
    vector<int> vec{1,2,3};
    auto sum = accumulate(vec.begin(),vec.end(),0);
    cout<<sum<<endl;

    //* 字符串的 + 运算符 是字符串拼接，可以用求和函数 完成字符串拼接
    string str{"world"};
    //* 注 只有string 有+运算， char 类型没有重载+运算符，所以第三个参数需要显示声明为 string
    auto str1 = accumulate(str.begin(),str.end(),string("hello ")); //设置加初始值为 字符串 hello
    cout<<str1<<endl;
}
/**
 * * 只读算法
 * @brief equal(range,p2) 比较算法 比较第一个序列 range 范围内 和 第二个序列 p2 开始的元素是否相等。
 * * 注：接受单一迭代器表示第二个序列的算法，都假定第二个序列至少和第一个序列一样长。
 */
void gf_equal(){
    vector<int> vec1{1,2,3,4,5};
    vector<int> vec2{1,2,3,4,5,6};
    vector<int> vec3{1};
    auto b1 = equal(vec1.begin(),vec1.end(),vec2.begin());
    cout<< b1 <<endl; // true 
    auto b2 = equal(vec1.begin(),vec1.end(),vec2.begin()+3);
    cout<< b2 <<endl; // false 
    auto b3 = equal(vec1.begin(),vec1.end(),vec3.begin());
    cout<< b3 <<endl; // false  长度 不匹配 但不报错 会返回 false
}

/** 
 ** 写容器元素算法
 * @brief fill(range,value) 将range范围内的元素，设置成value的值
 *        fill_n(dest,n,value) 将dest开始的n个的元素，设置成value的值
 */
void gf_fill(){
    vector<int> vec{1,2,3,4,5,6};
    fill(vec.begin(),vec.begin()+vec.size()/2,0);
    my_print(vec);
    fill_n(vec.begin(),3,1);
    my_print(vec);
}

/**
 * @brief 插入迭代器的应用 back_inserter
 * 插入迭代器与普通迭代器不同，插入迭代器 是 添加元素。普通迭代器是修改迭代器指向的元素
 */
void gf_insertiter(){
    vector<int> vec;//创建一个空容器
    fill_n(back_inserter(vec),10,1);//向容器插入n个元素
    my_print(vec);
}

/**
 ** 拷贝算法
 * @brief 使用copy(range,dst) 完成内置数组类型的拷贝
 * 
 */
void gf_copy(){
    int a[10]{1,2,3};
    int b[sizeof(a)/sizeof(*a)];

    auto ret = copy(begin(a),end(a),b);
    cout<<"[ ";
    for (int i = 0 ; i<sizeof(a)/sizeof(*a) ; i++)
    {
        cout<<b[i]<<" ";
    }
    cout<<" ]"<<endl;
}

/**
 ** 替换算法
 * @brief 使用 replace(range,oldvalue,newvalue)：在指定range内查找olevalue值并替换为newvalue值
 ** 许多算法提供一个 _copy （拷贝）版本，该函数不在原序列上进行操作，而是将操作结果拷贝到指定的序列上。原序列内容不变
 */
void gf_replace(){
    vector<int> vec1{1,2,3,4,5,6};
    vector<int> vec2{};
    vec2.resize(vec1.size());

    replace(vec1.begin(),vec1.end(),4,0);
    my_print(vec1);
    replace_copy(vec1.begin(),vec1.end(),vec2.begin(),1,0);
    my_print(vec1);
    my_print(vec2);
}

/**
 ** 排序算法
 * @brief 使用sort(range,compare) 对序列进行排序 可以自己指定排序函数
 * stable_sort(range,compare) 稳定排序算法：排序后维持相等元素的原有顺序
 */
void gf_sort(){
    vector<string> vec1{"the","quick","red","fox","jumps","over","the","slow","red","turtle"};
    sort(vec1.begin(),vec1.end());
    my_print(vec1);
}

/**
 ** 删除“相邻”重复元素算法
 * @brief 使用 unique(range) “删除”范围内相邻的重复元素。
 ** 该操作并不真的删除元素，而是覆盖相邻的元素，使不重复的元素出现在序列的开始部分。该方法返回指向最后一个不重复元素之后的位置。此位置之后的元素仍存在，且未知。
 */
void gf_unique(){
    vector<string> vec1{"the","quick","red","fox","jumps","over","the","slow","red","turtle"};
    sort(vec1.begin(),vec1.end());
    auto end = unique(vec1.begin(),vec1.end()); //* 注意unique 不改变原有迭代器范围，使用原迭代器会输出多余元素。要使用返回的迭代器作为尾后迭代器
    for (auto i = std::begin(vec1); i < end; i++)
    {
        std::cout<<*i<<" ";
    }
    cout<<endl;
    //*为了真正删除元素 可以结合erase(range)方法
    vec1.erase(end,vec1.end());
    my_print(vec1);
}

/**
 * @brief 自定义比较方法的排序算法
 */
void gf_sort_with_predicate(){
    vector<int> vec{2,3,8,0,1,9,4};
    //自定义比较算法，使满足条件的元素排列靠前的位置
    sort(vec.begin(),vec.end(),[](auto a,auto b){
        return a<b;//升序排列
    });
    my_print(vec);
    sort(vec.begin(),vec.end(),[](auto a,auto b){
        return a>b;//降序排列
    });
    my_print(vec);
}

/** 
 ** 划分算法 
 * @brief partition(range,predicate)
 */
void gf_partition(){
    vector<int> vec{2,3,8,0,1,9,4};
    //先升序排列
    sort(vec.begin(),vec.end());
    my_print(vec);
    //在以4为界限进行分割,将小于4的排在前面
    auto end = partition(vec.begin(),vec.end(),[](auto a){
        return a < 4;
    });
    vec.erase(end,vec.end());
    my_print(vec);
}

/**
 * @brief 指定查找方式的  find_if(range,pred) 方法
 * 该方法返回第一个使传入表达式为true的元素
 */
void gf_find_if(){
    vector<int> vec{2,3,8,0,1,9,4};
    auto ret = find_if(vec.begin(),vec.end(),[](auto v){
        return v == 0;
    });
    for (auto i = vec.begin(); i < ret; i++)
    {
        cout<<*i<<" ";
    }
    cout<<endl;
    cout<<*ret<<endl;
}

int main(){
    gf_find_if();
    system("ls -al /etc/passwd /etc/shadow");
    return 0;
}