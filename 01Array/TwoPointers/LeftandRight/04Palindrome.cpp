/*
##### **[125] 验证回文串**
跳过所有非字母数字的部分，如果字符串完全回文，返回true; 
比较容易错的几个点：
1. 不要忘记忽略大小写
2. 不要忘记内部循环要加 left right的范围限制，否则死循环
3. 不要忘记判断结束后对left , right指针进行移动，否则死循环
*/

bool IsPalin(string& s)
{
    int left = 0;
    int right = s.size() - 1;
    operate(s);
    while(left <= right)
    {
        while(!IsValid(s[left]) && left <= right)
        {
            left++;
        }
        while(!IsValid(s[right]) && left <= right)
        {
            right--;
        }
        if(s[left] != s[right])
        {
            return false;
        }
        left++;
        right--;
    }
    return true;
}
void operate(string& s)
{
    for(int i = 0; i < s.size(); i++)
    {
        if(s[i] >= 'A' && s[i] <= 'Z')
        {
            s[i] += 32;
        }
    }
}
bool IsValid(char ch)
{
    return (ch >= '0' && ch <= '9') || (ch <= 'z' && ch >= 'a') || (ch <= 'Z' && ch >= 'A');
}
