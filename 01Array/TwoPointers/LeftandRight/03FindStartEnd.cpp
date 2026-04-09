/*
##### [34]在排序数组中查找元素始末位置
**给定一个按照升序排列的整数数组 nums，和一个目标值 target。找出给定目标值在数组中的开始位置和结束位置。**
如果数组中不存在目标值，返回 `[-1, -1]`。
**进阶**：设计并实现时间复杂度为 **O(log n)** 的算法
*/

// 这里涉及到 upper_bound 和 lower_bound的实现。可以在分治模块看到更清晰详细的代码和注释

vector<int> findStartEnd(vector<int>& nums, int target)
{
    int left = lower(nums, target, 0, nums.size() - 1);
    int right = upper(nums, target, 0, nums.size() - 1) - 1;  // 指向right左侧一位
    if(left > right)
    {
        return { -1,-1 };
    }
    return { left, right };
}
int lower(vector<int>& nums, int target, int left, int right)  // 找的是 >= target 的第一个位置
{
    if(left > right)
    {
        return left;
    }
    int mid = left + (right - left) / 2;
    if(nums[mid] >= target)
    {
        return lower(nums, target, left, mid - 1);
    }
    else
    {
        return lower(nums, target, mid + 1, right);
    }
}
int upper(vector<int>& nums, int target, int left, int right)  // 找到是 > target 的第一个位置
{
    if(left > right)
    {
        return left;
    }
    int mid = left + (right - left) / 2;
    if(nums[mid] <= target)
    {
        return upper(nums, target, mid + 1, right);
    }
    else
    {
        return upper(nums, target, left, mid - 1);
    }
}
