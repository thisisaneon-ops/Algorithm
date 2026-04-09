// ##### [169]多数元素

// 给定一个大小为 `n` 的数组 `nums` ，返回其中的多数元素。多数元素是指在数组中出现次数 **大于** `⌊ n/2 ⌋` 的元素。

// 如不存在，返回-1；

// 摩尔投票，用两个变量代替笨重的哈希表；但是需要注意的是：摩尔投票法不保证一定存在major，一次循环结束后必须检查'众数'的出现次数是否超过半数！

// 另外更新major的分支不要忘记votes++

int FindMajorNumber(vector<int>& nums)
{
    int major = 0;
    int votes = 0;
    for(auto& u : nums)
    {
        if(votes == 0)
        {
            major = u;
            votes++;
        }
        else
        {
            if(u == major)
            {
                votes++;
            }
            else
            {
                votes--;
            }
        }
    }
    int cnt = 0;
    for(auto& u : nums)
    {
        if(u == major)
        {
            cnt++;
        }
    }
    return cnt <= nums.size() / 2 ? -1 : major;
}