vector<int>sort(vector<int>& nums)
{
    mergesort(nums, 0, nums.size() - 1);
    return nums;
}
void merge(vector<int>& nums, int i, int mid, int j)
{
    vector<int>tmp;
    int l1 = i;
    int l2 = mid + 1;
    while(l1 <= mid && l2 <= j)
    {
        if(nums[l1] < nums[l2])
        {
            tmp.push_back(nums[l1++]);
        }
        else
        {
            tmp.push_back(nums[l2++]);
        }
    }
    while(l1 <= mid)
    {
        tmp.push_back(nums[l1++]);
    }
    while(l2 <= j)
    {
        tmp.push_back(nums[l2++]);
    }
    for(int k = 0; k < tmp.size(); k++)
    {
        nums[i + k] = tmp[k];
    }
}
void mergesort(vector<int>& nums, int i, int j)
{
    if(i >= j)
    {
        return;
    }
    int mid = i + (j - i) / 2;
    mergesort(nums, i, mid);
    mergesort(nums, mid + 1, j);
    merge(nums, i, mid, j);
}
