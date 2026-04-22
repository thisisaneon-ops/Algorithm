// [459. 重复的子字符串](https://leetcode.cn/problems/repeated-substring-pattern/)

// 暴力法

class Solution {
public:
    bool repeatedSubstringPattern(string s) {
        if(s.size() == 1 || s.size() == 0){
            return false;
        }
        int len = s.size();
        bool flag = true;
        for(int i = 0; i < len / 2; i++){
            // 当前循环比对对象就是 0~i
            int sublen = i + 1;
            if((len - sublen) % sublen != 0)
            {
                continue;
            }
            flag = true;
            for(int j = i + 1; j <= len - sublen; j += sublen)
            {
                for(int k = 0; k < sublen; k++)
                {
                    if(s[k] != s[k + j])
                    {
                        flag = false;
                        break;
                    }
                }
                if(flag == false)
                {
                    break;
                }
            }
            if(flag == true){
                return true;
            }
        }
        return flag;
    }
};

// 字符串拼接

// 理论原型：KMP周期定理

class Solution {
public:
    bool repeatedSubstringPattern(string s) {
        string d = s + s;
        return d.find(s, 1) < s.size();
    }
};