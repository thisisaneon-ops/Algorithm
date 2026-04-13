// ##### [739]每日温度

// 给定一个整数数组 `temperatures` ，表示每天的温度，返回一个数组 `answer` ，其中 `answer[i]` 是指对于第 `i` 天，下一个更高温度出现在几天后。如果气温在这之后都不会升高，请在该位置用 `0` 来代替。

vector<int> dailyTemperatures(vector<int>& temp) 
{
    vector<int>ans(temp.size(), 0);
    stack<int>s;
    for(int i = 0; i < temp.size(); i++)
    {
        // 找下一个更大，应该保证栈内单调递减！！
        while(!s.empty() && temp[s.top()] < temp[i])
        {
            ans[s.top()] = i - s.top();
            s.pop();
        }
        s.push(i);
    }
    return ans;
}