#include <iostream>
#include <algorithm>
#include <sstream>

using namespace std;

/**
 * @brief 第一章：基础
 * 1.2.5节 课后习题 字符串的回环变位
 * 如果字符串s中的字符循环移动任意位置之后能够得到另一个字符串t,那么s就被称为t的回环变位(circular rotation ) 
 */

//* 从s的首位置开始，依次逐个将字符循环左移（即分为左右两字串，然后将左子串接在右字串子串后面），将拼接后的字串与t作比较
//* 主动构造s的回环字串
bool circularRotationOne(string s,string t){
    for (int i = 0; i < s.size(); i++)
    {
        auto str = s.substr(i,s.size()-i)+s.substr(0,i);
        if (str == t)
        {
            return true;
        }
    }
    return false;
}

//*  若两个字符串为回环变位，则 两个其中任意一个字符串的拼接，必然 包含另一个字符串在内。利用Find 函数直接进行查找。
//*  思路：不要陷入对回环变位的描述中，把问题复杂化。
//*         循环 移动 -> 也可以延伸为 向后追加。例如 abc -> abcabc 这样的字符串可以包含所有的回环变位的组合。
//*         只需要查询 字符串t 是否在 包含所有的a 的回环变位的组合的 字符串内即可。
bool circularRotationTwo(string s,string t){
    return (s.length()==t.length()) && ((s+s).find(t)!=string::npos);
}

void Test_circularRotation(){
    string s {"ABCD"}; 
    string t {"BCDA"};
    cout<<" circularRotationOne "<< circularRotationOne(s,t)<<endl;
    cout<<" circularRotationTwo " <<circularRotationTwo(s,t)<<endl;
}


int main(){
    Test_circularRotation();

    return 0;
}