vector<int>MoveZeros(vector<int>&nums)
{
	int slow = 0;
    int fast = 0;
    while(fast < nums.size())
    {
        if(nums[fast] != 0)
        {
            nums[slow++] = nums[fast];
        }
        fast++;
    }
    while(slow < nums.size())
    {
        nums[slow] = 0;
        slow++;
    }
    return nums;
}
