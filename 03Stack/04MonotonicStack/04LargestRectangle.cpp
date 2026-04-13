// ##### [84]柱状图中最大矩形

// 给定 *n* 个非负整数，用来表示柱状图中各个柱子的高度。每个柱子彼此相邻，且宽度为 1 。

// 求在该柱状图中，能够勾勒出来的矩形的最大面积。

/*
问题转化，我们选取一个固定的矩形条作为研究对象，那么高度固定，下面问题就是求这个高度能维持的最大宽度！如果求解最大宽度？？

很简单，打个比方，你有一把尺子，横在h = hi的位置，看哪里的柱子掉下去够不到这把尺子，哪里就是断点！！

那么放到数组里，断点位置就是该柱子两侧第一个比其本身小的元素！

本题存在的几个难点：

1. 抽象出数学模型，发现可以一次遍历利用栈解决；  
2. 不需要数组，直接在弹出时计算面积 ; 
3. 不需要两个栈分别做，一个栈已经可以处理左右边界的两个信息 
4. 左边界右边界都有找不到的嫌疑，应单独处理  
5. 面积公式的推导和变量的选取  
6. 可能残留在栈内元素的处理  
7. 尾插0的优化  

==**不要忘记尾插0把栈内剩余元素处理干净！！！**==
*/

int largestRectangleArea(vector<int>& nums)
{
    int maxS = 0;
    nums.push_back(0);  // 尾插元素处理不加0可能遗留在栈内的待处理元素
    stack<int>s;
    for(int i = 0 ; i < nums.size(); i++)
    {
        // 找的是第一个小于当前元素的！！维护栈单调递增！！
        while(!s.empty() && nums[s.top()] > nums[i])
        {
            int right = i;  // 右边的极限
            int height = nums[s.top()];
            s.pop();
            int left = -1;   // 左边的极限
            if(!s.empty())
            {
                left = s.top();
            }
            int width = s.empty() ? right : right - left - 1;
            maxS = max(maxS, width * height);
        }
        s.push(i);
    }
    return maxS;
}

// or

// 最大矩形
int LargestrectangleCoverage(vector<int>& nums)
{
	nums.push_back(-1);
	int maxS = 0;
	stack<int>s;
	for (int i = 0; i < nums.size(); i++)
	{
		while (!s.empty() && nums[s.top()] > nums[i])
		{
			int height = nums[s.top()];
			s.pop();
			int leftidx = s.empty() ? -1 : s.top();
			int rightidx = i;
			int width = rightidx - leftidx - 1;
			int S = width * height;
			maxS = max(maxS, S);
		}
		s.push(i);
	}
	return maxS;
}