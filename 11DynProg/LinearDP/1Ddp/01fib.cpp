#include<iostream>
using namespace std;

#ifdef DEBUG
int cnt = 0;
int fib(int n) {
	if (n <= 0) {
		return INT_MIN;
	}
	cnt++;
	if (n == 1 || n == 2) {
		return 1;
	}
	return fib(n - 1) + fib(n - 2);
}

int main() {
	cout << fib(10) << endl;
	cout << cnt;  // 109
	return 0;
}
#endif // DEBUG

#ifdef DEBUG
// MemoTable
#include<vector>
int cnt = 0;
int fib(int n, vector<int>& memo) {
	if (n <= 0) {
		return INT_MIN;
	}
	if (memo[n] != 0) {
		return memo[n];
	}
	cnt++;
	if (n == 1 || n == 2) {
		memo[n] = 1;
		return memo[n];
	}
	return fib(n - 1, memo) + fib(n - 2, memo);
}
const int N = 20;
int main() {
	vector<int>memo(N + 1, 0);
	cout << fib(N, memo) << endl;
	cout << cnt;  // 6766
	return 0;
}
#endif // DEBUG

// Iterator
#include<vector>
const int N = 20;
int main() {
	vector<int>fib(N + 1, 0);  // 这里我明知N合法，如果是封装函数需要查一下啊
	fib[1] = fib[2] = 1;
	for (int i = 3; i < N; i++) {
		fib[i] = fib[i - 1] + fib[i - 2];
	}
	cout << fib[N];
	return 0;
}