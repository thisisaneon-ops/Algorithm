// ##### [1047]删除相邻重复项

// 给出由小写字母组成的字符串 `s`，**重复项删除操作**会选择两个相邻且相同的字母，并删除它们。

// 在 `s` 上反复执行重复项删除操作，直到无法继续删除。

// 在完成所有重复项删除操作后返回最终的字符串。答案保证唯一

// 显示表示比较笨，但也可以
// 显式栈

string removeDuplicates(string s) {
    stack<char>t;
    for(int i = 0; i < s.size(); i++)
    {
        if(t.empty())
        {
            t.push(s[i]);
            continue;
        }
        char top = t.top();
        if(top == s[i])
        {
            t.pop();
            continue;
        }
        t.push(s[i]);
    }
    string ret;
    while(!t.empty())
    {
        char top = t.top();
        ret += top;
        t.pop();
    }
    reverse(ret.begin(), ret.end());
    return ret;
}

// 隐式栈
string removeDuplicates(string s) {
    string ret;
    for(int i = 0; i < s.size(); i++)
    {
        if(ret == "")
        {
            ret += s[i];
        }
        else
        {
            char top = ret[ret.size() - 1];  // 取最后一个元素
            if(top == s[i])
            {
                ret.pop_back();
            }
            else
            {
                ret += s[i];
            }
        }
    }
    return ret;
}