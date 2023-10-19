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

int main(){
    TestSolutionTwo();
    return 0;
}