/*
##### [496]找下一个更大元素

###### 栈 + 哈希表

`nums1` 中数字 `x` 的 **下一个更大元素** 是指 `x` 在 `nums2` 中对应位置 **右侧** 的 **第一个** 比 `x` 大的元素。

给你两个 **没有重复元素** 的数组 `nums1` 和 `nums2` ，下标从 **0** 开始计数，其中`nums1` 是 `nums2` 的子集。

对于每个 `0 <= i < nums1.length` ，找出满足 `nums1[i] == nums2[j]` 的下标 `j` ，并且在 `nums2` 确定 `nums2[j]` 的 **下一个更大元素** 。如果不存在下一个更大元素，那么本次查询的答案是 `-1` 。

返回一个长度为 `nums1.length` 的数组 `ans` 作为答案，满足 `ans[i]` 是如上所述的 **下一个更大元素** 。

nums1 && nums2内部元素互不相同；

num1中的元素都在nums2中；

核心思想：

1. 这道题是两个数组的查找，我们只需要对nums2做单调栈处理即可
2. 由于题目告诉我们互不相同，栈内可以直接存对应数据，而非普通的下标
3. 由于题目要找下一个更大元素，我们选用递减单调栈

注意事项：

1. 可以考虑哈希表，省去nums1遍历nums2的时间
2. ==**注意找不到需要返回-1！**==
*/

vector<int> FindNextBiggerEle(vector<int>& nums1, vector<int>& nums2)
{
    vector<int>ans;
    unordered_map<int, int>map;
    stack<int>Des;   // decreasing stack
    for(int i = 0 ; i < nums2.size(); i++)
    {
        while(!Des.empty() && Des.top() < nums2[i])
        {
            map[Des.top()] = nums2[i];
            Des.pop();
        }
        Des.push(nums2[i]);
    }
    // 注意，出循环时，栈可能残留元素，哈希表内并非都能映射到！！
	for(int i = 0; i < nums1.size(); i++)
    {
        ans.push_back(map.count(nums1[i]) ? map[nums1[i]] : -1);
    }
    return ans;
}