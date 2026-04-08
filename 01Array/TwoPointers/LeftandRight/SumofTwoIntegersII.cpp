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
