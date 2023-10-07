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
        vector<string> Str1Vec;
        vector<string> Str2Vec;

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