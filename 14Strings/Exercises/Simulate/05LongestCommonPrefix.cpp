// [14. 最长公共前缀](https://leetcode.cn/problems/longest-common-prefix/)

// 编写一个函数来查找字符串数组中的最长公共前缀。

// 如果不存在公共前缀，返回空字符串 `""`。

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        string s;
        for(int j = 0; j < strs[0].size(); j++){
            char c;
            for(int i = 0 ; i < strs.size(); i++){
                if(j == strs[i].size()){
                    return s;
                }
                if(i == 0){
                    c = strs[i][j];
                }   
                else{
                    if(c == strs[i][j]){
                        continue;
                    }
                    else{
                        return s;
                    }
                }
            }
            s += c;
        }
        return s;
    }
};