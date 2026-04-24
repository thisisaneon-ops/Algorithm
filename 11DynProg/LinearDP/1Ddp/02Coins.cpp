/*
你有三种面值的硬币：1元、3元、5元。每种硬币数量无限。
现在给你一个目标金额 amount，请计算出凑出这个金额所需的最少硬币数量。
如果无法凑出该金额，返回 -1。
*/

/*
定义问题状态：dp[i]表示金额为i时，需要凑出的最少硬币数量
1 3 5
dp[0] = 0;
dp[1] = 1; dp[2] = 2;
dp[3] = 1; dp[4] = 2;
dp[5] = 1; 
dp[i] = min{ dp[i-1] + 1, dp[i-3] + 1, dp[i-5] + 1 };
*/

#ifdef DEBUG
#include<iostream>
#include<vector>
using namespace std;

int main() {
	vector<int>coins = { 1,3,5 };
	int amount = 15;
	vector<int>dp(amount + 1, amount + 1);
	// 手动操作
	/*dp[1] = 1; dp[2] = 2;
	dp[3] = 1; dp[4] = 2;
	dp[5] = 1;
	for (int i = 6; i <= amount; i++) {
		dp[i] = min({ dp[i - 1] + 1, dp[i - 3] + 1, dp[i - 5] + 1 });
	}
	cout << dp[amount] << endl;*/
	dp[0] = 0;
	for (int i = 1; i <= amount; i++) {
		for (auto coin : coins) {
			if (i >= coin) {
				dp[i] = min(dp[i], dp[i - coin] + 1);
			}
		}
	}
	cout << (dp[amount] == amount + 1 ? -1 : dp[amount]) << endl;
	return 0;
}
#endif // DEBUG