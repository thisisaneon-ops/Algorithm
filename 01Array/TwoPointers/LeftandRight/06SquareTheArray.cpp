vector<int> squareNums(vector<int>& nums)
{
    int left = 0;
    int right = nums.size() - 1;
    vector<int>ret;
    ret.resize(nums.size());
    int idx = nums.size() - 1;
    while(left <= right)
    {
        if(nums[left] * nums[left] > nums[right] * nums[right])
        {
            ret[idx--] = nums[left] * nums[left];
            left++;
        }
        else
        {
            ret[idx--] = nums[right] * nums[right];
            right--;
        }
    }
    return ret;
}
