// ##### [80] 去重II-可保留两个
// 核心：比刚才的[26]多一个变量记录当前遍历元素的出现个数
// 根据 cnt 变量的值确定是否需要书写当前值
// 核心的判断变成了 cnt 的值是几

// 非常建议手写练习，验证自己是否完全理解

#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int removeDuplicates(vector<int>& nums) {
    if(nums.size() <= 2)
    {
        return nums.size();
    }
    int slow = 0;
    int fast = 1;
    int dup = 1;
    while(fast < nums.size())
    {
        if(nums[fast] == nums[slow])
        {
            dup++;
        }
        else
        {
            dup = 1;
        }
        if(dup > 2)
        {
            fast++;
        }
        else
        {
            slow++;
            nums[slow] = nums[fast];
            fast++;
        }
    }
    return slow+1;
}

int main()
{
    vector<int>n = {1,1,1,2};
    int N = removeDuplicates(n);
    cout << N << endl;
    for(int i = 0; i < N; i++)
    {
        cout << n[N] << " ";
    }
    return 0;
}
