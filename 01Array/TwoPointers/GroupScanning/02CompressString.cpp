// ##### **[443] 字符串压缩**

// 同样的思路；只是要求把字符串中重复的元素，用字符串 + 次数的形式表现出来 
#include<vector>
#include<iostream>
using namespace std;
int compressString(vector<char> &chars)
{
    int i = 0;
    int idx = 0;
    while(i < chars.size())
    {
        int j = i;
        while(j < chars.size() && chars[j] == chars[i])
        {
            j++;
        }
        if(j - i == 1)
        {
            chars[idx++] = chars[i];
        }
        else
        {
            int count = j - i;
            string tmp = to_string(count);
            chars[idx++] = chars[i];
            for(int k = 0; k < tmp.size(); k++)
            {
                chars[idx++] = tmp[k];
            }
        }
        i = j;
    }
    return idx;
}