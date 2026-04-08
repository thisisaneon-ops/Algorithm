int Removetarget(vector<int>& nums, const int target)
{
    int slow = 0;
    int fast = 0;
    while(fast < nums.size())
    {
        if(nums[fast] != target)
        {
            nums[slow] = nums[fast];
            slow++;
        }
        fast++;
    }
    return slow;
}
