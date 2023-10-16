#include <vector>
#include <iostream>
#include <string>

using namespace std;

/*
*   vector and map exercise
*/

using namespace std;

//成绩统计
void chengjitongji(){
     // 以10分为一个分数段统计成绩的数量：0~9，10~19.。。。100
    vector<uint> socres(11,0); 
    uint grade;
    cout<<"请输入成绩分数"<<endl;
    while (cin>>grade)
    {
        if (grade <= 100)
        {
            ++socres[grade/10];
        }     
    }

    for(auto a : socres){
        cout<<a<<" ";
    }
}

// 改变单词大小写
void Upper(){
    string str;
    vector<string> vstr;
    cout<<"请输入要转换成大写的字符,输入0结束"<<endl;

    while (cin>>str)
    {
        if (str == "0")
        {
            break;
        }
        vstr.push_back(str);        
    }

//todo:没有判断 字符中间有空格的情况 ，解决方法加上 isspace(str) 判断是不是空格
    for(string &s:vstr){
        for(int i=0;i<=s.size()-1;i++){
            //将字符串内每个字符改成大写并保存回来
            s[i]=toupper(s[i]);
        }   
        cout<<s<<endl;   
    }
}

//读入一组整数并把他们存入一个vector对象，将每对相邻整数的和输出出来
void xianglin(){
    int a;
    vector<int> vsum;
    cout<<"请输入数字,输入非数字字符则结束输入"<<endl;
    while(cin >> a){
        vsum.push_back(a);
    }
    for(int i=0;i<vsum.size()-1;i++){
        a = vsum[i]+vsum[i+1];
        cout << a << "  ";
    }
}


//读入一组整数并把他们存入一个vector对象，要求先输出第一个和最后一个的和，接着输出第二个和倒数第二个的和，以此类推。
void shouwei(){
    int a;
    vector<int> vsum;
    cout<<"请输入数字,输入非数字字符则结束输入"<<endl;
    while(cin >> a){
        vsum.push_back(a);
    }
    //双下标前后遍历
    int j = vsum.size()-1;
    for(int i=0;i<vsum.size()/2;i++){
        a = vsum[i]+vsum[j];
        cout << a << "  "<<i<<"+"<<j<<endl;
        j--;
    }
}
/**
 * @brief 验证 插入 中间删除后 是否还会自动排序
 * 
 */
void fun1(){

    vector<int> vints{1,2,3,4,5,6,7};
    cout<<"数组长度 = "<<vints.size()<<endl;
    vints.erase(vints.cbegin());
    cout<<"释放首位元素后 数组长度 = "<<vints.size()<<endl;
    cout<<"第一个元素为 = "<<vints[0]<<endl;


}

int main( )
{
    fun1();

    return 0;
}