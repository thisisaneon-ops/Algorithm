/*
##### [503]找下一个更大元素II  循环数组

496的变形，如果数组是循环的，怎么办？

第一个想法：把数组写两遍，开一个state数组标志当前数字是否已经被找过，如找过，不覆盖！
*/

vector<int> nextGreaterElements(vector<int>& nums) {
    int n = nums.size();
    vector<int>ans(nums.size(), -1);  // 存储答案
    int recorded = 0;
    vector<bool>state(nums.size(), false);  // 记录是否已经存储过
    nums.insert(nums.end(), nums.begin(), nums.end());   // 先将数组写两遍
    stack<int>s;
    for(int i = 0; i < nums.size(); i++)
    {
        while(!s.empty() && nums[s.top()] < nums[i])
        {
            if(!state[s.top() % n])
            {
                ans[s.top() % n] = nums[i];
                recorded++;
                state[s.top() % n] = 1;
            }
            s.pop();
        }
        s.push(i);
        if(recorded == nums.size() / 2)
        {
            break;
        }
    }
    return ans;
}

/*
缺点：需要的额外空间太大！且最坏情况跑的时间是 O(2 * N) 虽然也是 O(N)

下面我们使用第二种方法：

取模法，内存开销小，时间复杂度没有变化

注意：

1. 遍历长度必须是 2 * n
2. 第一轮允许新元素进栈；第二轮元素和第一轮完全重复，因此第二轮不再允许元素入栈，防止修改已经保存的正确答案！
3. 注意取模时机和目的
*/

vector<int> nextGreaterElements(vector<int>& nums) {
    vector<int>ans(nums.size(), -1);
    stack<int>s;
    int n = nums.size();
    // 要找的是下一个更大，维护栈内单调！栈内单调递减！
    for(int i = 0; i < 2 * n; i++)
    {
        int idx = i % n;
        while(!s.empty() && nums[s.top()] < nums[idx])
        {
            ans[s.top()] = nums[idx];
            s.pop();
        }
        if(i < n)
        {
            s.push(idx);
        }
    }
    return ans;
}