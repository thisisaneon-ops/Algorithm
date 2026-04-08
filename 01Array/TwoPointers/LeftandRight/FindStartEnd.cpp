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
