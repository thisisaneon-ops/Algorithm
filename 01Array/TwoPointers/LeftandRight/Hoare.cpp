void Hoare(vector<int>& nums, int i, int j)
{
    if(i >= j)
    {
        return;
    }
    int pivot = nums[i];
    int left = i;
    int right = j;
    while(true)
    {
        while(nums[left] < pivot)
        {
            left++;
        }
        while(nums[right] > pivot)
        {
            right--;
        }
        if(left >= right)  // 其实出循环只会有两种可能： left == right || left == right+1
        {
            break;
        }
        swap(nums[left], nums[right]);
        // 为什么left right需要移动？
        // 交换前left指向 >= pivot元素；right指向 <= pivot元素，那么交换后如果不移left 和right，那么left和right当前分别指向 <= pivot和 >= pivot元素；一旦是 == pivot的元素可能陷入死循环
        left++;
        right--;
    }
    // right能够保证左侧的元素都 <= pivot，但是left不行，当left == right + 1时，由于right指向的元素是 >= pivot的，不满足分区标准，因此只能选择right作为下一轮分区标准
    Hoare(nums, i, right);
    Hoare(nums, right + 1, j);
}
