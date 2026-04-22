// [58. 最后一个单词的长度](https://leetcode.cn/problems/length-of-last-word/)

// 从后向前找

class Solution {
public:
    int lengthOfLastWord(string s) {
        // 倒这来
        int cnt = 0; 
        int i = s.size() - 1;
        for(; i >= 0; i--){
            if(s[i] == ' ') continue;
            else break;
        }  
        for(; i >= 0; i--){
            if(s[i] == ' '){
                return cnt;
            }
            cnt++;
        }
        return cnt;
    }
};