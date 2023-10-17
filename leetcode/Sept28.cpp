#include <iostream>
#include <vector>
/**
 * @brief SolutionOne 
 * 给你两个字符串 word1 和 word2 。请你从 word1 开始，通过交替添加字母来合并字符串。
 * 如果一个字符串比另一个字符串长，就将多出来的字母追加到合并后字符串的末尾。
 * 返回合并后的字符串 。
 * 
 */
using namespace std;
class SolutionOne {
public:
    string mergeAlternately(string word1, string word2) {
        string MergeString{""};
        int WordIndex{0};
        bool IsLongerThanB{false};
        IsLongerThanB = word1.size() >= word2.size(); 
        if (IsLongerThanB)
        {
            for (auto i = word1.begin(); i < word1.end(); i++)
            {
                MergeString = MergeString+*i;
                if (WordIndex < word2.size())
                {
                    MergeString = MergeString+word2[WordIndex];
                }
                WordIndex++;
            }
        }else{
            for (auto i = word2.begin(); i < word2.end(); i++)
            {
                if (WordIndex < word1.size())
                {
                    MergeString = MergeString+word1[WordIndex];
                }
                MergeString = MergeString+*i;
                WordIndex++;
            }
        }
        return MergeString;
    }

};

/**
 * @brief SolutionTwo 字符串的最大公因子
 * 对于字符串 s 和 t，只有在 s = t + ... + t（t 自身连接 1 次或多次）时，我们才认定 “t 能除尽 s”。
 * 给定两个字符串 str1 和 str2 。返回 最长字符串 x，要求满足 x 能除尽 str1 且 x 能除尽 str2 。
 * 
 */
class SolutionTwo {
public:
    string gcdOfStrings(string str1, string str2) {
        //先计算两个字符串长度
        int len1 = (int)str1.length();
        int len2 = (int)str2.length();
        //用长度短的字符串 开始进行枚举, 从长到短开始找
        for(int i = min(len1,len2);i>=1;i--){
            //若有一个长度 使两个字符串 都能除尽，那么就有可能是一个公因子，然后在保存这个字符串，并进行检查，是否为真的公因子
            if (len1 % i == 0 && len2 % i ==0)
            {
                string X = str1.substr(0,i);
                if (check(X,str1)&&check(X,str2)) return X;
            } 
        }
        //找不到就返回空字符串
        return "";
    }

    /**
     * 判断 t 能否 除尽 s ,t 为公因子
    */
    bool check(string t, string s){
        // s 的长度是 最大公因子 t 的 lenx 倍
        int lenx = (int)s.length()/(int)t.length();
        string ans = "";
        //最大公因子 经过 lenx 倍拼接后，应该等于 原字符串 s
        for (int i = 0; i < lenx; i++)
        {
            ans = ans + t;
        }
        return ans == s;//判断 是否等于原字符串
    }
};

void TestSolutionOne(){
    SolutionOne one;
    string WordOne{"0246"};
    string WordTwo{"13579"};
    auto ret = one.mergeAlternately(WordOne,WordTwo);
    cout<<ret<<endl;
}


int main(){
    
    TestSolutionOne();

    return 0;
}