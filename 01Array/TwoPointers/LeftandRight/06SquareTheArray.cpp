/*
##### **[977] 对有序数组平方顺序输出**
有序数组考虑负数的情况下，我们只需要盯着两侧的元素即可，因两侧的数据一定是正的和负的的最大值。
左右指针向中间靠拢即可。
*/

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
