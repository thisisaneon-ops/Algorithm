// ##### [682]棒球比赛

// 比赛开始时，记录是空白的。你会得到一个记录操作的字符串列表 `ops`，其中 `ops[i]` 是你需要记录的第 `i` 项操作，`ops` 遵循下述规则：

// 1. 整数 `x` - 表示本回合新获得分数 `x`
// 2. `"+"` - 表示本回合新获得的得分是前两次得分的总和。题目数据保证记录此操作时前面总是存在两个有效的分数。
// 3. `"D"` - 表示本回合新获得的得分是前一次得分的两倍。题目数据保证记录此操作时前面总是存在一个有效的分数。
// 4. `"C"` - 表示前一次得分无效，将其从记录中移除。题目数据保证记录此操作时前面总是存在一个有效的分数。

// 请你返回记录中所有得分的总和。

// 基础的栈模型应用

// - ==**如果没有‘C’这个功能，完全可以只用一个变量，这恰恰体现了栈的存储特性**==

int calPoints(vector<string>& ops) {
    stack<int>s;
    for(int i = 0; i < ops.size(); i++)
    {
        if(ops[i] == "C")
        {
            s.pop();
        }
        else if(ops[i] == "D")
        {
            int top = s.top();
            top *= 2;
            s.push(top);
        }
        else if(ops[i] == "+")
        {
            int top = s.top();
            s.pop();
            int top2 = s.top();
            top2 = top + top2;
            s.push(top);
            s.push(top2);
        }
        else
        {
            int cur = stoi(ops[i]);
            s.push(cur);
        }
    }
    int ret = 0;
    while(!s.empty())
    {
        int top = s.top();
        ret += top;
        s.pop();
    }
    return ret;
}