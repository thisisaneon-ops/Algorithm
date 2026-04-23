// 46. 全排列
// 给定一个不含重复数字的数组 nums ，返回其 所有可能的全排列 。你可以 按任意顺序 返回答案。

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<int>x;
        vector<vector<int>>ret;
        vector<bool>state(nums.size(), false);
        func(0, x, state, ret, nums);
        return ret;
    }
    void func(int i, vector<int>&x, vector<bool>& state, vector<vector<int>>& ret, vector<int>& nums){
        if(i == nums.size()){
            ret.push_back(x);
        }
        else{
            for(int k = 0; k < nums.size(); k++){
                if(state[k] == true){
                    continue;
                }
                x.push_back(nums[k]);
                state[k] = true;
                func(i + 1, x, state, ret, nums);
                x.pop_back();
                state[k] = false;
            }
        }
    }
};

vector<vector<int>> AllArrangements(vector<int>& nums)
{
    vector<vector<int>> ret;
    helper(ret, nums, 0);
    return ret;
}
void helper(vector<vector<int>>& ret, vector<int>& nums, int i)
{
    if(i == nums.size())
    {
        ret.push_back(nums);
    }
    else
    {
        for(int j = i; j < nums.size(); j++)
        {
            swap(nums[i], nums[j]);
            helper(ret, nums, i + 1);
            swap(nums[i], nums[j]);
        }
    }
}