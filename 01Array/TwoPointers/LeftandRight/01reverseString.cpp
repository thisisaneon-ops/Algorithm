// ##### **[344] 逆序字符串**
// 最基础的左右指针模型

string ReverseString(string& s)
{
    int left = 0;
    int right = s.size() - 1;
    while(left < right)
    {
        swap(s[left], s[right]);
        left++;
        right--;
    }
    return s;
}
