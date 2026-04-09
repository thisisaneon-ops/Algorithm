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
