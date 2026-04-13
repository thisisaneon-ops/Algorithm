// ##### [20]有效括号匹配

// 给定一个只包括 `'('`，`')'`，`'{'`，`'}'`，`'['`，`']'` 的字符串 `s`，判断字符串是否有效。

// **有效字符串需满足：**

// 1. 左括号必须用相同类型的右括号闭合
// 2. 左括号必须以正确的顺序闭合
// 3. 每个右括号都有一个对应的相同类型的左括号
// 4. ==**注意有三类括号**==

bool IsValidQuotations(string& s)
{
    if(s.size() % 2 == 1)
    {
        return false;
    }
    stack<char>quos;
    for(int i = 0; i < s.size(); i++)
    {
        if(s[i] == '(' || s[i] == '[' || s[i] == '{')
        {
            quos.push(s[i]);
        }
        else  // 右括号, 找子集对应的左括号
        {
            if(quos.empty())
            {
                return false;
            }
            char top = quos.top();
            if((top == '(' && s[i] == ')') ||
               (top == '[' && s[i] == ']') ||
               (top == '{' && s[i] == '}'))
            {
                quos.pop();
                continue;
            }
            else
            {
                return false;
            }
        }
    }
    return quos.empty();
}