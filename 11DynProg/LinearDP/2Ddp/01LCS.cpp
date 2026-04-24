#include<iostream>
#include<vector>
using namespace std;
/*
LCS：求两个序列最长的公共子序列  子串(连续的)
s: helloworld
t: hlweord
分治思想：
if s[m] == s[n] :
LCS(s, m, t, n) = LCS(s, m - 1, t, n - 1) + 1;
else
LCS(s, m, t, n) = max{ LCS(s, m - 1, t, n), LCS(s, m, t, n - 1) };
*/

// 分治
#ifdef DEBUG
int cnt = 0;
int LCS(string& s, int m, string& t, int n) {
	if (m < 0 || n < 0) {
		return 0;
	}
	cnt++;
	if (s[m] == t[n]) {
		return LCS(s, m - 1, t, n - 1) + 1;
	}
	else {
		int len1 = LCS(s, m - 1, t, n);
		int len2 = LCS(s, m, t, n - 1);
		return max(len1, len2);
	}
}

int main() {
	string s = "helloworld";
	int m = s.size() - 1;
	string t = "hlweord";
	int n = t.size() - 1;
	int LCSsize = LCS(s, m, t, n);
	cout << LCSsize << endl;
	cout << "cnt : " << cnt << endl;  // 628
	return 0;
}
#endif // DEBUG

// 记忆化搜索优化
#ifdef DEBUG
int cnt = 0;
int LCS(string& s, int m, string& t, int n, vector<vector<int>>& memo) {
	if (m < 0 || n < 0) {
		return 0;
	}
	if (memo[m][n] > 0) {
		return memo[m][n];
	}
	cnt++;
	if (s[m] == t[n]) {
		memo[m][n] = LCS(s, m - 1, t, n - 1, memo) + 1;
		return memo[m][n];
	}
	else {
		int len1 = LCS(s, m - 1, t, n, memo);
		int len2 = LCS(s, m, t, n - 1, memo);
		memo[m][n] = max(len1, len2);
		return memo[m][n];
	}
}

int main() {
	string s = "helloworld";
	int m = s.size() - 1;
	string t = "hlweord";
	int n = t.size() - 1;
	int e = max(m, n) + 1;
	vector<vector<int>>memo(e, vector<int>(e, 0));
	int LCSsize = LCS(s, m, t, n, memo);
	cout << LCSsize << endl;
	cout << "cnt : " << cnt << endl; // 40
	return 0;
}
#endif // DEBUG

#ifdef DEBUG
// DP数组优化
// 二维数组 
// dp[n][m]表示

int main() {
	int cnt = 0;
	string s = "helloworld";
	int m = s.size() - 1;
	string t = "hlweord";
	int n = t.size() - 1;
	vector<vector<int>>dp(m + 1, vector<int>(n + 1, -1));
	for (int i = 0; i < m; i++) {
		if (s[i] == t[0]) {
			dp[i][0] = 1;
		}
		else {
			dp[i][0] = 0;
		}
	}
	for (int j = 0; j < n; j++) {
		if (s[0] == t[j]) {
			dp[0][j] = 1;
		}
		else {
			dp[0][j] = 0;
		}
	}
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			cnt++;
			if (s[i] == t[j]) {
				dp[i + 1][j + 1] = dp[i][j] + 1;
			}
			else {
				int len1 = dp[i + 1][j];
				int len2 = dp[i][j + 1];
				dp[i + 1][j + 1] = max(len1, len2);
			}
		}
	}
	cout << dp[m][n] << endl;
	cout << "cnt : " << cnt << endl;
	return 0;
}
#endif // DEBUG


#ifdef DEBUG
/*
力扣1143
1143. 最长公共子序列

给定两个字符串 text1 和 text2，返回这两个字符串的最长 公共子序列 的长度。如果不存在 公共子序列 ，返回 0 。

一个字符串的 子序列 是指这样一个新的字符串：它是由原字符串在不改变字符的相对顺序的情况下删除某些字符（也可以不删除任何字符）后组成的新字符串。

例如，"ace" 是 "abcde" 的子序列，但 "aec" 不是 "abcde" 的子序列。
两个字符串的 公共子序列 是这两个字符串所共同拥有的子序列。
*/

// 记忆化搜索，稍微有点慢
class Solution {
public:
	int longestCommonSubsequence(string s, string t) {
		int m = s.size() - 1;
		int n = t.size() - 1;
		vector<vector<int>>memo(m + 1, vector<int>(n + 1, -1));
		return func(s, m, t, n, memo);
	}
	int func(const string& s, int m, const string& t, int n, vector<vector<int>>& memo) {
		if (m < 0 || n < 0) {
			return 0;
		}
		if (memo[m][n] != -1) {
			return memo[m][n];
		}
		if (s[m] == t[n]) {
			memo[m][n] = func(s, m - 1, t, n - 1, memo) + 1;
			return memo[m][n];
		}
		else {
			int len1 = func(s, m - 1, t, n, memo);
			int len2 = func(s, m, t, n - 1, memo);
			if (len1 > len2) {
				memo[m][n] = len1;
			}
			else {
				memo[m][n] = len2;
			}
			return memo[m][n];
		}
	}
};

// 迭代法
// 迭代法
class Solution {
public:
	int longestCommonSubsequence(string s, string t) {
		int m = s.size();
		int n = t.size();
		vector<vector<int>>dp(m + 1, vector<int>(n + 1, 0));
		for (int i = 1; i <= m; i++) {
			for (int j = 1; j <= n; j++) {
				if (s[i - 1] == t[j - 1]) {
					dp[i][j] = dp[i - 1][j - 1] + 1;
				}
				else {
					int len1 = dp[i - 1][j];
					int len2 = dp[i][j - 1];
					if (len1 > len2)
						dp[i][j] = len1;
					else
						dp[i][j] = len2;
				}
			}
		}
		return dp[m][n];
	}
};
#endif // DEBUG

using namespace std;

int cnt = 0;
int LCS(string& s, int m, string& t, int n, vector<vector<int>>& memo, vector<vector<int>>& path) {
	if (m < 0 || n < 0) {
		return 0;
	}
	if (memo[m][n] > 0) {
		return memo[m][n];
	}
	cnt++;
	if (s[m] == t[n]) {
		// 往斜对角走
		memo[m][n] = LCS(s, m - 1, t, n - 1, memo, path) + 1;
		path[m][n] = 3;
		return memo[m][n];
	}
	else {
		int len1 = LCS(s, m - 1, t, n, memo, path);
		int len2 = LCS(s, m, t, n - 1, memo, path);
		if (len1 > len2) { 
			// 调用len1对应的函数，向上一行走
			memo[m][n] = len1;
			path[m][n] = 1;  // 向上
		}
		else {
			memo[m][n] = len2;
			path[m][n] = 2;  // 向左
		}
		return memo[m][n];
	}
}

// instruction: 3->dig 2->left 1->up
void print(const string& s,  vector<vector<int>>& path, int m, int n) {
	// 回溯时打印
	if (m < 0 || n < 0){
		cout << "我结束了" << endl;
		return;
	}
	if (path[m][n] == 1) {
		cout << "我往上走了" << endl;
		print(s, path, m - 1, n);
	}
	else if (path[m][n] == 2) {
		cout << "我往左走了" << endl;
		print(s, path, m, n - 1);
	}
	else if(path[m][n] == 3) {
		cout << "我往左上走了" << endl;
		print(s, path, m - 1, n - 1);
		cout << "我要回溯了" << endl;
		cout << s[m] << endl;
	}
	cout << "我往回走了" << endl;
}

void pureprint(const string& s,  vector<vector<int>>& path, int m, int n) {
	// 回溯时打印
	if (m < 0 || n < 0){
		return;
	}
	if (path[m][n] == 1) {
		pureprint(s, path, m - 1, n);
	}
	else if (path[m][n] == 2) {
		pureprint(s, path, m, n - 1);
	}
	else if(path[m][n] == 3) {
		pureprint(s, path, m - 1, n - 1);
		cout << s[m];
	}
}

int main() {
	string s = "helloworld";
	int m = s.size();
	string t = "hlweord";
	int n = t.size();
	vector<vector<int>>memo(m + 1, vector<int>(n + 1, 0));
	vector<vector<int>>path(m + 1, vector<int>(n + 1, 0));
	int LCSsize = LCS(s, m - 1, t, n - 1, memo, path);
	cout << LCSsize << endl;
	cout << "cnt : " << cnt << endl; // 40
	// 打印memo数组和path数组
	cout << "--memo数组--" << endl;
	cout << "   ";
	for (int i = 0; i < n; i++) {
		cout << t[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < m; i++) {
		cout << s[i] << ": ";
		for (int j = 0; j < n; j++) {
			if (memo[i][j] == 0) {
				cout << "*" << " ";
			}
			else
				cout << memo[i][j] << " ";
		}
		cout << endl;
	}
	cout << "--path数组" << endl;
	cout << "instruction: 3->dig 2->left 1->up" << endl;
	cout << "   ";
	for (int i = 0; i < n; i++) {
		cout << t[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < m; i++) {
		cout << s[i] << ": ";
		for (int j = 0; j < n; j++) {
				cout << path[i][j] << " ";
		}
		cout << endl;
	}
	// 利用Path把目标串打印出来
	cout << "LCS: " << endl;
	print(s, path, m-1, n-1);
	cout << "\nLCS: " << endl;
	pureprint(s, path, m-1, n-1);
	return 0;
}