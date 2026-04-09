// ##### [438] 找到字符串中所有字母异位词

// 给定两个字符串 `s` 和 `p`，找到 `s` 中所有 `p` 的 **异位词** 的子串，返回这些子串的起始索引。不考虑答案输出的顺序。

// **异位词** 指由相同字母重排列形成的字符串（包括相同的字符串）。

// - 字符串只包含 **小写英文字母**
// - 对比第三题，第三题桶的初始化长度是128，因为可能含其他元素，ASCII码有128个元素

vector<int> findAnagrams(string s, string p)  // 注意一下 p 是子串 s是大串
{
    vector<int>ans;
    if(p.size() > s.size())
    {
        return ans;
    }
    int i = 0;
    int j = 0;
    // 我们可以先初始化一个桶专门存p
    vector<int>Bucket(26, 0); // 初始元素个数都是0
    for(int k = 0; k < p.size(); k++)
    {
        Bucket[p[k] - 'a']++;
    }
    vector<int>Bucket_win(26, 0);
    // 先初始化第一个窗口
    while(j < i + p.size())
    {
        Bucket_win[s[j++] - 'a']++;
    }
    // 为了避免等会循环内没轮对内容从头到尾检查，先查哪些不一样
    int dif = 0;
    for(int k = 0; k < 26; k++)
    {
        if(Bucket[k] != Bucket_win[k])
        {
            dif++;
        }
    }
    if(dif == 0)
    {
        ans.push_back(0);
    }
    // 出来以后dif统计了第一个窗口的错位数
    // 注意 j 现在已经指向窗口右侧第一个点，每次要做的是：
    // 因为咱们的窗口大小是固定的，为了保证检查下一个元素，窗口的第一个元素必须退出窗口
    while(j < s.size())
    {
        // 注意操作顺序
        // 注意一下： j++ 和 i++必须分开做，做一步 检查一步！！否则可能出现互相干扰，记录数dif被污染！
        // 先让 j 进窗口：
        Bucket_win[s[j] - 'a']++;
        // 由于j元素的进入，只对桶内该元素状态产生了改变；因此，我们只需要查这个元素即可
        // j进来可能导致什么？
        // 1. 恰好窗口匹配
        // 2. 进来导致窗口不在匹配
        if(Bucket[s[j] - 'a'] == Bucket_win[s[j] - 'a'])  // 现在才相等，说明原来肯定不相等，那么--
        {
            dif--;
        }
        else if(Bucket[s[j] - 'a'] + 1 == Bucket_win[s[j] - 'a'])
        {
            dif++;
        }
        j++;
        // 再让i退出窗口
        Bucket_win[s[i] - 'a']--;
        // i退出窗口可能导致什么？
        // 1. 可能导致当前窗口不在匹配！
        // 2. 可能导致当前窗口恰好匹配了！
        if(Bucket_win[s[i] - 'a'] == Bucket[s[i] - 'a'])
        {
            dif--;
        }
        else if(Bucket_win[s[i] - 'a'] == Bucket[s[i] - 'a'] - 1)  // 注意这里有个坑！如果原本这个位置就不相等，那么我们不需要dif++
        {
            dif++;
        }
        i++;
        // 在对当前窗口进行检查
        if(dif == 0)
        {
            ans.push_back(i);
        }
    }
    return ans;
}