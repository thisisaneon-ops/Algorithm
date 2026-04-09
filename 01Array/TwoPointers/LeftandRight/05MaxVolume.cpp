/*
##### [11] 盛最多水的容器
给定一个长度为 `n` 的整数数组 `height`。有 `n` 条垂线，第 `i` 条线的两个端点是 `(i, 0)` 和 `(i, height[i])`。
找出其中的两条线，使得它们与 `x` 轴共同构成的容器可以容纳**最多的水**。
核心思路：左右双指针，时刻比较，记录最大值；移动较矮一侧的指针
*/

int MaxVolume(vector<int>& height)
{
    int left = 0;
    int right = height.size() - 1;
    int maxVol = 0;
    while(left < right)
    {
        int vol = (right - left) * min(height[left], height[right]);
        maxVol = max(maxVol, vol);
        if(height[left] > height[right])
        {
            right--;
        }
        else
        {
            left++;
        }
    }
    return maxVol;
}
