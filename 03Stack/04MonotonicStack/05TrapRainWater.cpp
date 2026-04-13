// ##### [42]接雨水

// 给定 `n` 个非负整数表示每个宽度为 `1` 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。

// 几个难点：

// 1. 是否理解栈在本题中到底是干什么的？单调栈是否有更深刻理解？如果能说出处理每个栈顶元素都能保证两侧元素（当前遍历元素和新的栈顶元素）都比弹出元素大恒成立，呈现凹槽结构，单调栈理解深度还不错
// 2. 接雨水的面积表示公式推导：如何计算才能避免柱子本身的面积被计入？一层一层算！弹一个算一个！将问题由区间面积转化为本层面积！
// 3. 弹出需要判空，如果栈空，说明左边没有比他高的元素，或者左边已经处理完毕！因此当前区间无可接雨水！
// 4. 设置一个bottom变量记录被弹出去的元素作为本层雨水面积的底！
// 5. 计算本层面积： S = height * width;   height = min(left, right) - bottom；   width = right - left - 1;

// ==**不要忘记新元素压栈！！**==

int trap(vector<int>& height)
{
    int TotalWater = 0;
    stack<int>s;
    for(int i = 0; i < height.size(); i++)
    {
        int curS = 0;
        while(!s.empty() && height[s.top()] < height[i])
        {
            int bottom = s.top();  // 底
            s.pop();  // 弹出
            if(s.empty())
            {
                break;
            }
            int left = s.top();  // 当前层左边界下标
            int right = i;  // 当前层右边界下标
            int h = min(height[left], height[right]) - height[bottom];
            int S = h * (right - left - 1);
            curS += S;
        }
        s.push(i);
        TotalWater += curS;
    }
    return TotalWater;
}