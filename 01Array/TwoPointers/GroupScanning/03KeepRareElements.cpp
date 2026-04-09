/*
##### 数组内保留稀有元素

保留数组只出现一次的元素，返回有效长度，不允许申请额外空间

两种常见方法：

###### 前后检查法
*/

int RareElements(vector<int>& nums)
{
    int i = 0;
    for(int j = 0; j < nums.size(); j++)
    {
        if((j == 0 || nums[j] != nums[j - 1]) && (j == nums.size() - 1 || nums[j] != nums[j + 1]))
        {
            nums[i++] = nums[j];
        }
    }
    return i;
}

// ###### 分区扫描

// 将数组内部相等的元素看成一个自然组，在遍历完每个组后计算自然组长度，判断是否==1，依据判断执行/不执行写入操作；然后再让指针指向下一个区域

int RareElements(vector<int>& nums)
{
    int i = 0;
    int idx = 0;
    while(i < nums.size())
    {
        int j = i;
        while(j < nums.size() && nums[j] == nums[i])
        {
            j++;
        }
        if(j - i == 1)
        {
            nums[idx++] = nums[i];
        }
        i = j;
    }
    return idx;
}