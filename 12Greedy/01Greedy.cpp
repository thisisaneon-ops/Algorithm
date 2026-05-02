#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

// * 力扣 56 合并区间
/*
* 以数组 intervals 表示若干个区间的集合，其中单个区间为 intervals[i] = [starti, endi] 。
* 请你合并所有重叠的区间，并返回 一个不重叠的区间数组，该数组需恰好覆盖输入中的所有区间 。
*/
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<vector<int>> mergeIntervals;
        sort(intervals.begin(), intervals.end()); // 默认字典序
        const int n = intervals.size();
        for (int i = 0; i < n; i++) {
            // 只需要比较当前元素和上一个元素的区间包含情况即可
            int startA = intervals[i][0];
            int endA = intervals[i][1];
            if (mergeIntervals.size() == 0) {
                mergeIntervals.push_back({ startA, endA });
                continue;
            }
            int startP = mergeIntervals[mergeIntervals.size() - 1][0];
            int endP = mergeIntervals[mergeIntervals.size() - 1][1];
            // 因为我们已经排好序, startP >= startA
            // 第一种：直接错开
            if (startA > endP) {
                mergeIntervals.push_back({ startA, endA });
            }
            // 第二种，有重叠：但是因为排序，我们的endA不可能小于endP;
            mergeIntervals[mergeIntervals.size() - 1][1] = max(endA, endP);
        }
        return mergeIntervals;
    }
};