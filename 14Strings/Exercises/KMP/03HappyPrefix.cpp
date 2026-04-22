// [1392. 最长快乐前缀](https://leetcode.cn/problems/longest-happy-prefix/)

// KMP的直接应用，和KMP算法中用的next数组略有不同，注意一下

int * getNext(string& t){
    int j = 0;
    int k = -1;
    int* next = new int [t.size()];
    next[j] = k;
    while(j < t.size() - 1){
        if(t[j] == t[k]){
            j++; k++:
            next[j] = k;
        }
        else k = next[k];
    }
    return next;
}
// 每一位next[i]表示不包含索引i的前面的子串里, 最长公共前后缀的长度(由于不包含size位，所以当前数组并无记录完整字符串最长公共前后缀长度的值)

// KMP算法中，我们不需要整串的Next数组，因为失配位置只会出现在[0 : N-1]的位置，因此最多只考虑到末位之前的字符串的最长公共子串；

// 本题和上略有不同，关心的是整串的性质，所以必须研究所有

class Solution {
public:
    string longestPrefix(string s) {
        int len = 0;
        int suflen = getNext(s);
        return s.substr(0, suflen);
    }
    int getNext(string s){
        int j = 0;
        int k = -1;
        int* next = new int[s.size() + 1];
        next[j] = k;
        while(j < s.size()){
            if(k == -1 || s[j] == s[k]){
                j++; k++;
                next[j] = k;
            }
            else
            { k = next[k]; }
        }
        return next[s.size()];
    }
};