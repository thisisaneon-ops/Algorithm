// [796. 旋转字符串](https://leetcode.cn/problems/rotate-string/)

// 给定两个字符串, `s` 和 `goal`。如果在若干次旋转操作之后，`s` 能变成 `goal` ，那么返回 `true` 。

// `s` 的 **旋转操作** 就是将 `s` 最左边的字符移动到最右边。 

// - 例如, 若 `s = 'abcde'`，在旋转一次之后结果就是`'bcdea'` 

// 注意要先排除长度不等的情况

// 除了暴力计算，也可以使用和459相同的思想，利用s+s枚举出所有可能的情况

class Solution {
public:
    bool rotateString(string s, string goal) {
        if(s.size() != goal.size()){
            return false;
        }
        string d = s + s;
        return d.find(goal, 0) != string::npos;   
    }
};