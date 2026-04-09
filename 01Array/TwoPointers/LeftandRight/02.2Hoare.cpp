/*
如果你能回答以下几个，就说明你完全理解Hoare算法的本质了！

1. 为什么 i= j 也要return 不能是i > j  --return么
2. 在do-while里，为什么不需要单独手动移动 left 和 right？while里却需要？
3. 为什么while循环的条件是 <  > pivot？不可以是 <= pivot  >= pivot么？
4. 出循环时 left 和 right可能是什么关系？可能不相邻间隔很多个位置么？
5. 整个循环的过程中有什么不变的性质？
6. 为什么最后划分区间的时候需要我们以 right // right + 1做划分？

双指针交换法，理解难度大

关心的就是中间的间隙大小

left只有可能在出循环时在right右边一个或者就是和right重合

while风格

**注意需要单独手动移动一下left和right指针**
*/

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




// 下面是do-while风格，可以灵活选择，不要拘泥于一种手段，排斥另一种，理解两种写法的差异本身也可以巩固对算法模型的理解！

void Hoare(vector<int>& nums, int i, int j)
{
    if(i >= j)
    {
        return;
    }
    int pivot = nums[i];
    int left = i - 1;
    int right = j + 1;
    while(true)
    {
        do
        {
            left++;
        } while (nums[left] < pivot);
        do
        {
            right--;
        } while (nums[right] > pivot);
        if(left >= right)  // 其实出循环只会有两种可能： left == right || left == right+1
        {
            break;
        }
        swap(nums[left], nums[right]);
    }
    // right能够保证左侧的元素都 <= pivot，但是left不行，当left == right + 1时，由于right指向的元素是 >= pivot的，不满足分区标准，因此只能选择right作为下一轮分区标准
    Hoare(nums, i, right);
    Hoare(nums, right + 1, j);
}