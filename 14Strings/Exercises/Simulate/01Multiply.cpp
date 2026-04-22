// 43. 字符串相乘

// 给定两个以字符串形式表示的非负整数 `num1` 和 `num2`，返回 `num1` 和 `num2` 的乘积，它们的乘积也表示为字符串形式。

// 注意：不能使用任何内置的 BigInteger 库或直接将输入转换为整数。

class Solution {
public:
	string multiply(string s1, string s2) {
		if (s1 == "0" || s2 == "0") { return "0"; }
		int m = s1.size();
		int n = s2.size();
		vector<int>ans(m + n, 0);
		for (int i = m - 1; i >= 0; i--) {
			int digit1 = s1[i] - '0';
			for (int j = n - 1; j >= 0; j--) {
				int digit2 = s2[j] - '0';
				int mul = digit1 * digit2 + ans[i + j + 1];  // 乘积+这位本身可能有的值
				ans[i + j + 1] = mul % 10;
				ans[i + j] += mul / 10;
			}
		}
        int i = 0;
        while(i < ans.size()){
            if(ans[i] == 0){
                i++;
            }
            else break;
        }
		string ret;
		for (; i < ans.size(); i++) {
			ret += ans[i] + '0';
		}
		return ret;
	}
};