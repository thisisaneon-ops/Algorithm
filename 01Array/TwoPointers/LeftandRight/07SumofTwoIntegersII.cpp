// ##### [167] 两数之和 II
// 给你一个下标从 **1 开始** 的整数数组 `numbers`，该数组已按 **非递减顺序排列**。请你从数组中找出满足相加之和等于目标数 `target` 的两个数。
// 以长度为 2 的整数数组 `[index1, index2]` 的形式返回这两个整数的下标（从 1 开始）。
// 你可以假设每个输入只对应唯一的答案**，而且你不可以重复使用相同的元素。**
// 你所设计的解决方案必须只使用常量级的额外空间。

// 注意观察，题目虽然和LeetcodeI 一样要求返回下标，但是这里已经排序，第一题未排序，非要用双指针必须用pair记录和维护原本的数组下标！

vector<int>FindTwoNumberSum(vector<int>& nums, int target)
{
    int left = 0;
    int right = nums.size() - 1;
    while(left < right)
    {
        int curSum = nums[left] + nums[right];
        if(curSum > target)
        {
            right--;
        }
        else if(curSum < target)
        {
            left++;
        }
        else
        {
            break;  // 找到
        }
    }
    return { left, right };
}
