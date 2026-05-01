// [6. Z 字形变换](https://leetcode.cn/problems/zigzag-conversion/)

/*
将一个给定字符串 `s` 根据给定的行数 `numRows` ，以从上往下、从左到右进行 Z 字形排列。
比如输入字符串为 `"PAYPALISHIRING"` 行数为 `3` 时，排列如下：
P   A   H   N
A P L S I I G
Y   I   R
之后，你的输出需要从左往右逐行读取，产生出一个新的字符串，比如：`"PAHNAPLSIIGYIR"`。
请你实现这个将字符串进行指定行数变换的函数：
*/

class Solution {
public:
    string convert(string s, int numRows) {
        if (numRows == 1) {
            return s;
        }
        vector<string>v(numRows);
        int row = 0;
        bool flag = true;
        for (int i = 0; i < s.size(); i++) {
            char c = s[i];
            v[row].push_back(c);
            if(row == 0){
                flag = true;
            }
            if(row == numRows - 1){
                flag = false;
            }
            if(flag){
                row++;
            }
            else{
                row--;
            }
        }
        string ret;
        for(auto u : v){
            ret += u;
        }
        return ret;
    }
};