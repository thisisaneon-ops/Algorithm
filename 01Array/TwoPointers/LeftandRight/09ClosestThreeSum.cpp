/*
##### [16]最接近的三数之和

给你一个长度为 `n` 的整数数组 `nums` 和 一个目标值 `target`。请你从 `nums` 中选出三个在 **不同下标位置** 的整数，使它们的和与 `target` 最接近。

返回这三个数的和。

假定每组输入只存在恰好一个解。

思路和力扣15完全一样
*/

class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int closest = nums[0] + nums[1] + nums[2];
        for (int i = 0; i < nums.size() - 2; i++) {
            int cur = nums[i];
            int remain = target - cur;
            // 下面利用双指针找最接近remain的
            int left = i + 1;
            int right = nums.size() - 1;
            while (left < right) {
                int sum = nums[left] + nums[right];
                if(abs(sum + nums[i] - target) < abs(closest - target)){
                    closest = sum + nums[i];
                }
                if (sum > remain) { right--; } 
                else if (sum < remain){ left++; }
                else { return target; }
            }
        }
        return closest;
    }
};