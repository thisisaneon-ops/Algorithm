#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#include<iomanip>
using namespace std;

/*
	DP 0-1背包问题：
	有一组物品，其重量为w0, w1...wn-1 价值为v0, v1...vn-1;
	现在有一个背包，容量为c, 求怎么装物品让价值最大化？
	显然，在这个问题中，一维数组提供的信息太少，我们需要的条件(模式是从后向前)：
	1. 当前允许选择的物品范围 [i: n-1]
	2. 当前的背包剩余容量j
	那么定义问题的状态 dp[i][j] 表示，在允许选择的范围在[i: n-1], 剩余背包容量为j时，所选择物品的最大价值v
	下面推导状态转移方程：
	从最小子问题入手：
	当 i == n-1时(即只有最后一个元素为可选元素时) dp[n-1][j]的情况：
	当 dp[n-1] > j(此时是c)：dp[n-1][j] = 0;
	否则：dp[n-1][j] = v[n-1]
	下面推广到一般问题：
	对于物品i, i+1,...., n  背包容量为j的问题：
	if w[i] > j :  dp[i][j] = dp[i+1][j];
	else :  dp[i][j] = max(dp[i+1][j-w[i]] + v[i], dp[i+1][j])  选或者不选
	其实整个过程就可以由两个步骤概括
	1. 根据背包容量和w[i]判断'能不能选'
	2. 根据两种选择价值的大小判断'要不要选'
*/

#ifdef DEBUG
void BackTrace(vector<int>& w, vector<int>& v, int c, vector<vector<int>>& dp) {
	int bestv = 0;
	for (int i = 0; i < v.size() - 1; i++) {
		if (dp[i][c] != dp[i + 1][c]) {
			// 第i个物品被选中
			cout << w[i] << " ";
			bestv += v[i];
			c -= w[i];
		}
	}
	// 单独处理最后一行
	if (dp[w.size()][c] > 0) {
		bestv += v[w.size() - 1];
		cout << w[w.size() - 1] << " ";
	}
}

int main()
{
	vector<int>w = { 8,6,4,2,5 };
	vector<int>v = { 6,4,7,8,6 };
	const int N = w.size();
	const int c = 12;
	vector<vector<int>>dp(N, vector<int>(c + 1, 0));  // 为了取到容量c，我们直接多开辟一位
	// 需要先初始化状态：
	// 先初始化最后一行
	for (int j = 1; j < c + 1; j++) {
		if (w[N - 1] > j) {
			dp[N - 1][j] = 0;
		}
		else {
			dp[N - 1][j] = v[N - 1];
		}
	}
	for (int i = N - 2; i >= 0; i--) {
		for (int j = 1; j <= c; j++) {
			if (w[i] > j) {
				dp[i][j] = dp[i + 1][j];
			}
			else {
				dp[i][j] = max(dp[i + 1][j], dp[i + 1][j - w[i]] + v[i]);
			}
		}
	}
	cout << dp[0][c] << endl;
	cout << "Table" << endl;
	for (int i = 1; i <= 12; i++) {
		cout << setw(4) << i;
	}
	cout << "\n===================================================";
	cout << endl;
	for (int i = 0; i < dp.size(); i++) {
		for (int j = 1; j < dp[i].size(); j++) {
			cout << setw(4) << dp[i][j];
		}
		cout << endl;
		BackTrace(w, v, c, dp);
	}
	return 0;
}
#endif // DEBUG

#ifdef DEBUG

// 当然你也可以正着推导！
/*
	有一组物品，其重量为w0, w1...wn-1 价值为v0, v1...vn-1;
	现在有一个背包，容量为c, 求怎么装物品让价值最大化？
	假设dp[i][j]表示可选择物品范围[0:i]且背包剩余容量为j时可选物品的最大总价值
	那么先初始化：
	对第一行有：
	dp[0][j] = 0(j < w[0])  v[0](j >= w[0])
	类似地也可以得到
	if w[i] > j :
	dp[i][j] = dp[i-1][j]
	else
	dp[i][j] = max(dp[i-1][j], dp[i-1][j-w[i]]+v[i]);
*/

int main()
{
	vector<int>w = { 8,6,4,2,5 };
	vector<int>v = { 6,4,7,8,6 };
	const int N = w.size();
	const int c = 12;
	vector<vector<int>>dp(N, vector<int>(c + 1, 0));  // 为了取到容量c，我们直接多开辟一位
	// 先初始化第一行
	for (int j = 1; j <= c; j++) {
		if (j < w[0]) {
			dp[0][j] = 0;
		}
		else {
			dp[0][j] = v[0];
		}
	}
	// 双重for循环
	for (int i = 1; i < N; i++) {
		for (int j = 1; j <= c; j++) {
			if (j < w[i]) {
				dp[i][j] = dp[i - 1][j];
			}
			else {
				dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - w[i]] + v[i]);
			}
		}
	}
	cout << dp[N - 1][c] << endl;
	cout << "Table" << endl;
	for (int i = 1; i <= 12; i++) {
		cout << setw(4) << i;
	}
	cout << "\n===================================================";
	cout << endl;
	for (int i = 0; i < dp.size(); i++) {
		for (int j = 1; j < dp[i].size(); j++) {
			cout << setw(4) << dp[i][j];
		}
		cout << endl;
	}
	/*
	Table
   1   2   3   4   5   6   7   8   9  10  11  12
===================================================
   0   0   0   0   0   0   0   6   6   6   6   6
   0   0   0   0   0   4   4   6   6   6   6   6
   0   0   0   7   7   7   7   7   7  11  11  13
   0   8   8   8   8  15  15  15  15  15  15  19
   0   8   8   8   8  15  15  15  15  15  21  21
	*/
	return 0;
}
#endif // DEBUG

#ifdef DEBUG
int main()
{
	vector<int>w = { 8,6,4,2,5 };
	vector<int>v = { 6,4,7,8,6 };
	const int N = w.size();
	const int c = 12;
	vector<vector<int>>dp(N, vector<int>(c + 1, 0));  // 为了取到容量c，我们直接多开辟一位
	// 需要先初始化状态：
	// 先初始化最后一行
	for (int j = 1; j < c + 1; j++) {
		if (w[N - 1] > j) {
			dp[N - 1][j] = 0;
		}
		else {
			dp[N - 1][j] = v[N - 1];
		}
	}
	for (int i = N - 2; i >= 0; i--) {
		for (int j = 1; j <= c; j++) {
			if (w[i] > j) {
				dp[i][j] = dp[i + 1][j];
			}
			else {
				dp[i][j] = max(dp[i + 1][j], dp[i + 1][j - w[i]] + v[i]);
			}
		}
	}
	cout << dp[0][c] << endl;
	cout << "Table" << endl;
	for (int i = 1; i <= 12; i++) {
		cout << setw(4) << i;
	}
	cout << "\n===================================================";
	cout << endl;
	for (int i = 0; i < dp.size(); i++) {
		for (int j = 1; j < dp[i].size(); j++) {
			cout << setw(4) << dp[i][j];
		}
		cout << endl;
	}
	/*
	Table
   1   2   3   4   5   6   7   8   9  10  11  12
===================================================
   0   8   8   8   8  15  15  15  15  15  21  21
   0   8   8   8   8  15  15  15  15  15  21  21
   0   8   8   8   8  15  15  15  15  15  21  21
   0   8   8   8   8   8  14  14  14  14  14  14
   0   0   0   0   6   6   6   6   6   6   6   6
	*/
	// 打印物品栏
	for (int i = 0; i < N; i++) {
		cout << "物品" << i << " w: " << w[i] << "  v: " << v[i] << endl;
	}
	cout << endl;
	int current_c = c;
	// 打印选择的物品
	// 思路来自于我们对上表以及dp数组赋值逻辑的分析：
	// 只有一种可能会使得dp[i][j]和dp[i+1][j]不相等：w[i]和j间满足容量恰当关系的情况下，max比较中决定选择当前物品的情况才可能出现上下两行对应值不相等！
	// 因此：
	// 从第0行第c列起看(最优解)，向下看：
	// 如果当前行当前列与下一行当前列值相等：那么该元素未被选中，继续向下看，知道出现上下行不一致
	// 如果不相等，当前行所代表物品被选中，打印物品信息
	// 单独处理最后一行，利用current_c记录剩余容量，如果最终current_c > w[N-1]，则选；否则不选
	for (int i = 0; i < N - 1; i++) {
		if (dp[i][current_c] != dp[i + 1][current_c]) {
			cout << "选中物品" << i << " w: " << w[i] << "  v: " << v[i] << endl;
			current_c -= w[i];
		}
	}
	// 单独判断最后一行
	if (dp[N - 1][current_c] > 0) {
		cout << "选中物品" << N - 1 << " w: " << w[N - 1] << "  v: " << v[N - 1] << endl;
		current_c -= w[N - 1];
	}
	return 0;
}

#endif // DEBUG

// 正着也是类似的
int main()
{
	vector<int>w = { 8,6,4,2,5 };
	vector<int>v = { 6,4,7,8,6 };
	const int N = w.size();
	const int c = 12;
	vector<vector<int>>dp(N, vector<int>(c + 1, 0));  // 为了取到容量c，我们直接多开辟一位
	// 先初始化第一行
	for (int j = 1; j <= c; j++) {
		if (j < w[0]) {
			dp[0][j] = 0;
		}
		else {
			dp[0][j] = v[0];
		}
	}
	// 双重for循环
	for (int i = 1; i < N; i++) {
		for (int j = 1; j <= c; j++) {
			if (j < w[i]) {
				dp[i][j] = dp[i - 1][j];
			}
			else {
				dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - w[i]] + v[i]);
			}
		}
	}
	cout << dp[N - 1][c] << endl;
	cout << "Table" << endl;
	for (int i = 1; i <= 12; i++) {
		cout << setw(4) << i;
	}
	cout << "\n===================================================";
	cout << endl;
	for (int i = 0; i < dp.size(); i++) {
		for (int j = 1; j < dp[i].size(); j++) {
			cout << setw(4) << dp[i][j];
		}
		cout << endl;
	}
	/*
	Table
   1   2   3   4   5   6   7   8   9  10  11  12
===================================================
   0   0   0   0   0   0   0   6   6   6   6   6
   0   0   0   0   0   4   4   6   6   6   6   6
   0   0   0   7   7   7   7   7   7  11  11  13
   0   8   8   8   8  15  15  15  15  15  15  19
   0   8   8   8   8  15  15  15  15  15  21  21
	*/
	// 和刚才反过来，最优解在表格的右下角
	// 我们从最后一行开始，单独处理第一行
	int current_c = c;
	for (int i = N - 1; i > 0; i--) {
		if (dp[i][current_c] != dp[i - 1][current_c]) {
			cout << "选中物品" << i << " w: " << w[i] << "  v: " << v[i] << endl;
			current_c -= w[i];
		}
	}
	// 单独处理第一行
	if (dp[0][current_c] > 0) {
		cout << "选中物品" << 0 << " w: " << w[0] << "  v: " << v[0] << endl;
		current_c -= w[0];
	}
	return 0;
}
