// LIS问题
// 1 2 3 3 1 7 8
// 子序列可以不连续
// 定义状态: dp[i]表示到第i位止最长LIS序列长度
/*
状态转移方程: 
dp[0] = 1;
dp[1] = max(1, dp[0]+1) if nums[0] < nums[1]
...
dp[i] = max(1, dp[j] + 1) if nums[j] < nums[i]
*/
#include<vector>
#include<iostream>
using namespace std;
int main() {
	vector<int>nums = { 1,3,2,5,7,4,9,10 };
	vector<int>dp(nums.size(), 0);
	int longestlis = 0;
	dp[0] = 1;
	for (int i = 1; i < nums.size(); i++) {
		dp[i] = 1;
		for (int j = 0; j < i; j++) {
			if (nums[i] >= nums[j]) {
				dp[i] = max(dp[j] + 1, dp[i]);
			}
		}
		longestlis = max(longestlis, dp[i]);
	}
	cout << longestlis << endl;
	return 0;
}