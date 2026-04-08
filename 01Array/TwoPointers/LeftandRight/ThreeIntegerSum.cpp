#include<iostream>
using namespace std;

vector<vector<int>> SumOfThreeIntegers(vector<int>& nums)
{
    vector<vector<int>>v;
    const int n = nums.size();
    sort(nums.begin(), nums.end());
    for(int i = 0; i < n - 2; i++)
    {
        if(i != 0 && nums[i] == nums[i - 1])
        {
            continue;
        }
        int target = -nums[i];
        // 利用双指针
        int left = i + 1;
        int right = n - 1;
        while(left < right)
        {
            int sum = nums[left] + nums[right];
            if(sum == target)
            {
                v.push_back({nums[i], nums[left], nums[right]});
                do {left++; } while(left < right && nums[left] == nums[left - 1]);
                do {right--;} while(left < right && nums[right] == nums[right + 1]);
            }
            else if(sum < target)
            {
                left++;
            }
            else
            {
                right--;
            }
        }
    }
    return v;
}
