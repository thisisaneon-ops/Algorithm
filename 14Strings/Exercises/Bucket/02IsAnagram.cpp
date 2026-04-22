// [242. 有效的字母异位词](https://leetcode.cn/problems/valid-anagram/)

class Solution {
public:
    bool isAnagram(string s, string t) {
        int* buckets = new int[26](0);
        for(int i = 0; i < s.size(); i++){
            buckets[s[i] - 'a']++;
        }
        int* buckett = new int[26](0);
        for(int i = 0 ; i < t.size(); i++){
            buckett[t[i] - 'a']++;
        }
        for(int i = 0; i < 26; i++){
            if(buckets[i] != buckett[i]){
                return false;
            }
        }
        return true;
    }
};