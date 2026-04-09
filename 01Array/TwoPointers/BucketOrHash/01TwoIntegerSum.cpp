#include<vector>
#include<iostream>
#include<unordered_map>
using namespace std;
// 哈希思想
vector<int> SumOfTwoIntegers(vector<int>& nums, int target)
{
    vector<int>ret;
    unordered_map<int, int>m;
    for(int i = 0; i < nums.size(); i++)
    {
        int curNeed = target - nums[i];
        if(m.find(curNeed) != m.end())
        {
            return {m[curNeed] , i};
        }
        m[nums[i]] = i;
    }
    return {};
}

int main()
{

    return 0;
}
