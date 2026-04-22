// [28. 找出字符串中第一个匹配项的下标](https://leetcode.cn/problems/find-the-index-of-the-first-occurrence-in-a-string/)

给你两个字符串 `haystack` 和 `needle` ，请你在 `haystack` 字符串中找出 `needle` 字符串的第一个匹配项的下标（下标从 0 开始）。如果 `needle` 不是 `haystack` 的一部分，则返回  `-1` 。

class Solution {
public:
    int strStr(string haystack, string needle) {
        return kmp(haystack, needle);
    }
    int kmp(string s, string t){
        int i = 0;
        int j = 0;
        int * next = getNext(t);
        while(i < s.size()){
            if(j == -1 || s[i] == t[j]){
                i++;
                j++;
                if(j == t.size()){
                    return i - j;
                }
            }
            else
            {
                j = next[j];
            }
        }
        return -1;
    }
    int* getNext(const string& t){
        int j = 0;
        int k = -1;
        int * next = new int[t.size()];
        next[j] = k;
        while(j < t.size() - 1){
            if(k == -1 || t[j] == t[k]){
                j++;
                k++;
                next[j] = k;
            }
            else{
                k = next[k];
            }
        }
        return next;
    }
};