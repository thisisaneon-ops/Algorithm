// [387. 字符串中的第一个唯一字符](https://leetcode.cn/problems/first-unique-character-in-a-string/)

class Solution {
public:
    int firstUniqChar(string s) {
        // 桶可能会快一些
        int* bucket = new int[26](0);
        for(int i = 0; i < s.size(); i++){
            bucket[s[i] - 'a']++;
        }
        for(int i = 0; i < s.size(); i++){
            if(bucket[s[i] - 'a'] == 1)
                return i;
        }
        return -1;
    }
};