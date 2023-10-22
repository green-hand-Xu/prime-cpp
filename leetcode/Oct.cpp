/**
 * SolutionOne 拥有最多糖果的孩子
 * 给你一个数组 candies 和一个整数 extraCandies ，其中 candies[i] 代表第 i 个孩子拥有的糖果数目。
 * 对每一个孩子，检查是否存在一种方案，将额外的 extraCandies 个糖果分配给孩子们之后，此孩子有 最多 的糖果。注意，允许有多个孩子同时拥有 最多 的糖果数目。
*/
#include <iostream>
#include <vector>
#include <algorithm> //使用sort()函数排序

using namespace std;

class SolutionOne {
public:
    vector<bool> kidsWithCandies(vector<int>& candies, int extraCandies) {
        vector<bool> result;
        int max = 0;
        //获取最大值
        for (auto num : candies)
        {
            max = max > num ? max : num;
        }
        for (auto num : candies)
        {
            if (num + extraCandies >= max)
            {
                result.push_back(true);
            }else{
                result.push_back(false);
            }
        }
        return result;
    }
}SolutionOne;

void TestSolutionOne(){
    vector<int> input{1,2,3,4,5};
    auto output = SolutionOne.kidsWithCandies(input,2);
    for (auto res : output)
    {
        cout<<res<<" "<<endl;
    }
}

/**种花问题
 * 假设有一个很长的花坛，一部分地块种植了花，另一部分却没有。可是，花不能种植在相邻的地块上，它们会争夺水源，两者都会死去。
 * 给你一个整数数组 flowerbed 表示花坛，由若干 0 和 1 组成，其中 0 表示没种植花，1 表示种植了花。另有一个数 n ，
 * 能否在不打破种植规则的情况下种入 n 朵花？能则返回 true ，不能则返回 false 。
*/

    bool canPlaceFlowers(vector<int> &flowerbed, int n) {
        int m = flowerbed.size();
        for (int i = 0; i < m; i++) {
            if ((i == 0 || flowerbed[i - 1] == 0) && flowerbed[i] == 0 && (i == m - 1 || flowerbed[i + 1] == 0)) {
                n--;
                i++; // 下一个位置肯定不能种花，直接跳过
            }
        }
        return n <= 0;
    }


class SolutionTwo {
public:
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        //获取花坛长度
        int length = flowerbed.size();
        for (int i = 0; i < length; i++)
        {
            if ((i == 0 || flowerbed[i-1] == 0) && flowerbed[i] == 0 && ( i == length-1 || flowerbed[i+1] == 0))
            {
                // flowerbed[i] = 1;//不进行插入数据的话，可以对 便利的位序 i 进行 +1 ，让其跳过下一个位置，因为种花后，相邻位置必然无法继续种花
                n--;
                i++;
                if (n<=0)
                {
                    return true;
                }
            }   
        }
        return n<=0;
    }
    //还可以用贪心算法 直接计算出一共可以种多少只花
}SolutionTwo;

void TestSolutionTwo(){
    vector<int> flower{1,0,0,0,0,1};
    auto n = 2;
    cout<<SolutionTwo.canPlaceFlowers(flower,n)<<endl;
}

/** 反转字符串中的元音字母
        给你一个字符串 s ，仅反转字符串中的所有元音字母，并返回结果字符串。元音字母包括 'a'、'e'、'i'、'o'、'u'，且可能以大小写两种形式出现不止一次。
*/
class SolutionThree {
public:
    string YY{"aeiouAEIOU"};
    string reverseVowels(string s) {
        
        std::vector<int> YYIndex;
        //* 用一个数组 记录字符中所有的元音字符的位置
        for (int i = 0; i < s.size(); i++)
        {
            if (copare(s[i]))
            {
                YYIndex.push_back(i);
            }
        }
        if(YYIndex.empty()) return s;

        int head = 0;
        int tail = YYIndex.size();
        int mid = tail/2;
        
        for (auto i = head; i < mid; i++)
        {
            if (head<=tail)
            {   
                auto temp = s[YYIndex[i]];
                s[YYIndex[i]] = s[YYIndex[tail-1]];
                s[YYIndex[tail-1]] =temp;
            } 
            tail--;
        }
        return s;
    }

    bool copare(char s){
        if(YY.find(s)!=string::npos) return true;
        return false;
    }
}SolutionThree;

void TestThree(){
    string str{"aeiou"};
    cout<<SolutionThree.reverseVowels(str)<<endl;
}

/** 反转字符串中的单词
        给你一个字符串 s ，请你反转字符串中 单词 的顺序。
        单词 是由非空格字符组成的字符串。s 中使用至少一个空格将字符串中的 单词 分隔开。
        返回 单词 顺序颠倒且 单词 之间用单个空格连接的结果字符串。
        注意：输入字符串 s中可能会存在前导空格、尾随空格或者单词间的多个空格。返回的结果字符串中，单词间应当仅用单个空格分隔，且不包含任何额外的空格。
*/
class SolutionFour {
public:
    vector<string> words;//把读出来的单词进行存储 然后在倒置顺序
    string reverseWords(string s) {
        s = ' '+s+' ';
        sortWords(s);
        string str{""};
        int index = words.size()-1;
        while (index > 0)
        {
            str = str + words[index]+ ' ';
            index--;
        }
        str = str+words[0];
        return str;
    }

    string sortWords(string s){
        int re = 0;//左下标
        int ri = 0;//右下标
        for(int i = 0; i<s.size();i++){
            if (s[i] == ' ' || i == s.size()-1)
            {
                if (re < ri)
                {
                    words.push_back(s.substr(re+1,ri-re));
                }
                re = i;
                continue;
            }
            ri = i;
        }
        return s;
    }
//* 力扣官方题解
    string reverseWords_leetcode(string s) {
        // 反转整个字符串
        reverse(s.begin(), s.end());

        int n = s.size();
        int idx = 0;
        for (int start = 0; start < n; ++start) {
            if (s[start] != ' ') {
                // 填一个空白字符然后将idx移动到下一个单词的开头位置
                if (idx != 0) s[idx++] = ' ';

                // 循环遍历至单词的末尾
                int end = start;
                while (end < n && s[end] != ' ') s[idx++] = s[end++];

                // 反转整个单词
                reverse(s.begin() + idx - (end - start), s.begin() + idx);

                // 更新start，去找下一个单词
                start = end;
            }
        }
        s.erase(s.begin() + idx, s.end());
        return s;
    }

}SolutionFour;

void TestFour(){
    string s = "the sky is blue";
    auto str = SolutionFour.reverseWords(s);
    for (auto word : SolutionFour.words)
    {
        cout<<word;
    }
    cout<<endl;
    cout << str<<endl;
    
}

int main(){
    TestFour();
    return 0;
}