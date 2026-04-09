// ##### [209] 长度最小的子数组

// 给定一个含有 `n` 个正整数的数组和一个正整数 `target`。

// 找出该数组中满足其和 `≥ target` 的**长度最小的连续子数组** `[numsl, numsl+1, ..., numsr-1, numsr]`，并返回其长度。如果不存在符合条件的子数组，返回 `0`。

// 双指针 + 单调性

// 几个需要注意的：

// 1. bestlen要初始化INT_MAX
// 2. 出循环必须检查！防止有更优解被漏掉
// 3. 本质思想其实是 j 指针对数组的穷举，i 在每个情况下给出最优解！

int FindSubArray(vector<int>& nums, int target)
{
    int i = 0;
    int j = 1;
    int bestlen = INT_MAX;
    int sum = nums[i];
    while(j < nums.size())
    {
        if(sum >= target)
        {
            int len = j - i;
            bestlen = min(len, bestlen);
            if(bestlen == 1)
            {
                return 1;
            }
            while(sum >= target)
            {
                sum -= nums[i];
                i++;
            }
        }
        sum += nums[j];
        j++;
    }
    // 出循环还要检查一下
    if(sum >= target)
    	bestlen = min(j - i, bestlen);
    return bestlen == INT_MAX ? 0 : bestlen;
}

// DP

// 状态：定义状态数组 dp[i] 为以 nums[i]结尾的最短满足条件的子数组长度
// 状态转移方程：
// 假设数组长度为n
// dp[0] = nums[0] >= target ? 1 : 0;
// dp[1] = nums[1] >= target ? 1 : nums[1] + nums[0] >= target ? 2 : 0;
// 能看出这道题并不适合用DP的算法解，我们需要考虑原因
// 这道题的dp数组的每一项并不能告诉我们每一种状态到底选择了什么数字，现在的和是多少，因此不适合用dp，数组提供的信息不够；

// 对比一下可以使用动态规划的题和滑动窗口的题，就会发现明显的区别！

// | 特性               | LIS      | 最短子数组 |
// | ------------------ | -------- | ---------- |
// | 区间是否连续       | ❌ 不要求 | ✅ 必须连续 |
// | 状态是否可继承     | ✅ 可以   | ❌ 不行     |
// | 是否只依赖最后元素 | ✅ 是     | ❌ 不是     |
// | 状态信息是否完整   | ✅ 完整   | ❌ 不完整   |
// | 适合算法           | DP       | 滑动窗口   |