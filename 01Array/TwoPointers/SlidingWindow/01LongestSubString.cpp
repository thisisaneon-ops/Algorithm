// ##### [3] 无重复字符的最长子串

// 给定一个字符串 `s` ，请你找出其中**不含有重复字符**的**最长子串**的长度

// 注意区分概念：子串(substring/ subarray) 必须是原数组/串的连续段；和后面的LIS问题的子序列(subSequence不是一个概念)

int LongestSubStringWithoutDuplicates(string s)
{
    if(s.empty())
    {
        return 0;
    }
    int i = 0;
    int j = 1;
    int bestlen = 1;
    // 注意一下，串内重复字符可能不一定会相邻，因此我们必须要一个桶来记录出现了什么元素！
    vector<int>Bucket(128, 0);
    // 先依据 i j 指向位置初始化哈希桶
    Bucket[s[i]]++;
    while(j < s.size())
    {
        // 先检查j
        if(Bucket[s[j]] != 0) // 说明已经出现过了
        {
            int len = j - i;
            if(len > bestlen)
            {
                bestlen = len;
            }
            // 下面我们需要将i移动到重复位置；（不是直接跳到j！！这样会漏掉非重复元素，导致计算长度出错！！）
           while(Bucket[s[j]] != 0)
           {
               Bucket[s[i++]]--;
           }
        }
        Bucket[s[j++]]++;
    }
    // 最后出循环的时候再比一次！！
    if(j - i > bestlen)
    {
        bestlen = j - i;
    }
    return bestlen;
}