// ##### [15] 三数之和
// 给你一个整数数组 `nums`，判断是否存在三元组 `[nums[i], nums[j], nums[k]]` 满足 `i != j`、`i != k` 且 `j != k`，同时还满足 `nums[i] + nums[j] + nums[k] == 0`。请你返回所有和为 `0` 且**不重复**的三元组(返回值，不是下标)。
// **注意**：答案中不可以包含重复的三元组。
// 先拿一个指针遍历数组，定下一个元素后转化为167或1这类题
// 去重逻辑：
// 1. 外层循环遇到连续的元素直接跳过
// 2. 内层循环找到一组解后，驱动left和right跳过连续的重复元素即可
// 别忘了先对数组排序，本题数组没说有序！

// 可以不定期手写，巩固去重逻辑和循环把控能力

#include<iostream>
using namespace std;

vector<vector<int>> SumOfThreeIntegers(vector<int>& nums)
{
    vector<vector<int>>v;
    const int n = nums.size();
    sort(nums.begin(), nums.end());
    // 为什么要从0开始？从2开始往回看行不行？请手动实现？
    for(int i = 0; i < n - 2; i++)
    {
        if(i != 0 && nums[i] == nums[i - 1])
        {
            continue;
        }
        int target = -nums[i];
        // 利用双指针
        int left = i + 1;
        int right = n - 1;
        while(left < right)
        {
            int sum = nums[left] + nums[right];
            if(sum == target)
            {
                v.push_back({nums[i], nums[left], nums[right]});
                // 思考：为什么要先left++ right-- 使用do-while结构？while可以么？
                do {left++; } while(left < right && nums[left] == nums[left - 1]);
                do {right--;} while(left < right && nums[right] == nums[right + 1]);
            }
            else if(sum < target)
            {
                left++;
            }
            else
            {
                right--;
            }
        }
    }
    return v;
}
