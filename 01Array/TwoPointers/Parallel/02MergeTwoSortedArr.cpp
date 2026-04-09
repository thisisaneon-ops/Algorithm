/*
[88] 合并两个有序数组
不同于普通的归并排序，可以自己手写一下！
逆序思想，不要开辟新的空间！
*/

void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    int i = m - 1;
    int j = n - 1;
    int k = nums1.size() - 1;
    while(i >= 0 && j >= 0)
    {
        if(nums1[i] > nums2[j])
        {
            nums1[k--] = nums1[i--];
        }
        else
        {
            nums1[k--] = nums2[j--];
        }
    }
    while(i >= 0)
    {
        nums1[k--] = nums1[i--];
    }
    while(j >= 0)
    {
        nums1[k--] = nums2[j--];
    }
}