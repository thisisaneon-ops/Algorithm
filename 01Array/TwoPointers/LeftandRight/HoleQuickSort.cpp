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
