// ##### 283 移动0
// 给定一个数组 `nums`，编写一个函数将所有 `0` 移动到数组的末尾，同时保持非零元素的**相对顺序**。
// **请注意** ，必须在不复制数组的情况下**原地**对数组进行操作

vector<int> MoveZeros(vector<int> &nums)
{
    int slow = 0;
    int fast = 0;
    while (fast < nums.size())
    {
        if (nums[fast] != 0)
        {
            nums[slow++] = nums[fast];
        }
        fast++;
    }
    while (slow < nums.size())
    {
        nums[slow] = 0;
        slow++;
    }
    return nums;
}
