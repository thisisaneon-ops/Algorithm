// 填坑法
// 1. 不要忘记递归终止条件
// 2. 每个条件都要加 left < right的严格限制，否则无法保证 出循环时 left == right;
// 3. 两个if语句的 left ++ right--不一定要写
// 4. 第一个区间返回 i -- right-1也可以

void HoleQuickSort(vector<int>& nums, int i, int j)
{
    if(i >= j)
    {
        return;
    }
    int pivot = nums[i];
    int left = i;
    int right = j;
    while(left < right)
    {
        while(left < right && nums[right] >= pivot)
        {
            right--;
        }
        if(left < right)
        {
            nums[left] = nums[right];
            left++;
        }
        while(left < right && nums[left] <= pivot)
        {
            left++;
        }
        if(left < right)
        {
            nums[right] = nums[left];
            right--;
        }
    }
    nums[right] = pivot;
    HoleQuickSort(nums, i, right);
    HoleQuickSort(nums, right + 1, j);
}
