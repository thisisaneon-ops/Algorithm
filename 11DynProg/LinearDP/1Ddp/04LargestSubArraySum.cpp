/*
给定一个整数数组 nums，请找出一个具有最大和的连续子数组（子数组最少包含一个元素），并返回其最大和。
定义状态：dp[i]表示到下标为i的元素时，最大和是多少
状态转移方程：
dp[0] = nums[0];
dp[1] = max(dp[0] + nums[1], nums[1]);
dp[2] = max(dp[1] + nums[2], nums[2]);
...
dp[i] = max(dp[i - 1] + nums[i], nums[i]);
*/

/*
为什么不能用 dp[i] = max(dp[i - 1], dp[i - 1] + nums[i])？
这样定义状态会导致状态断裂，此时dp[i]无法确定当前元素是否背真正选中；
进而导致下一个需要dp[i]的元素不能正确判定前一个元素的状态，无法保证'连续性'！
*/
#include<iostream>
#include<vector>
using namespace std;


int main() {
	vector<int>nums = { 1,2,-4,1,6,-8, 9,12,-7,-3,-5,10 };
	vector<int>dp(nums.size(), 0);
	dp[0] = nums[0];
	int maxSum = dp[0];
	for (int i = 1; i < nums.size(); i++) {
		dp[i] = max(dp[i - 1] + nums[i], nums[i]);
		maxSum = max(dp[i], maxSum);
	}
	cout << maxSum << endl;
	return 0;
}