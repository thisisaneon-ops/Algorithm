/*
##### [844]退格字符串

给定 `s` 和 `t` 两个字符串，当它们分别被输入到空白的文本编辑器后，如果两者相等，返回 `true` 。`#` 代表退格字符。

**注意：**如果对空文本输入退格字符，文本继续为空。

依然是简单的栈应用，**注意需要防止对空栈做弹出！**
*/

class Solution {
public:
    bool backspaceCompare(string s, string t) {
        stack<char>s1;
        stack<char>s2;
        for(int i = 0; i < s.size(); i++)
        {
            if(s[i] == '#')
            {
                if(!s1.empty())
                {
                    s1.pop();
                }
            }
            else
            {
                s1.push(s[i]);
            }
        }
        for(int i = 0; i < t.size(); i++)
        {
            if(t[i] == '#')
            {
                if(!s2.empty())
                {
                    s2.pop();
                }
            }
            else
            {
                s2.push(t[i]);
            }
        }
        if(s1.size() != s2.size())
        {
            return false;
        }
        while(!s1.empty() && !s2.empty())
        {
            char top1 = s1.top();
            char top2 = s2.top();
            if(top1 != top2)
            {
                return false;
            }
            s1.pop();
            s2.pop();
        }
        return s1.empty() && s2.empty();
    }
};