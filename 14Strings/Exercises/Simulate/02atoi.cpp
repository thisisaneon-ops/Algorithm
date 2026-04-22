// [8. 字符串转换整数 (atoi)](https://leetcode.cn/problems/string-to-integer-atoi/)

// 比较麻烦，容易出错，这里列举几个常见的需要注意的问题：

// 1. 遇到+-号后又遇到了一次+-号，判定为非法串，直接返回0
// 2. 记得实时检查当前值有没有溢出，否则非法检查不及时，会有整除溢出循环问题！

class Solution {
public:
    int myAtoi(string s) {
        long long a = 0;
        int i = 0;
        int n = s.size();
        int sign = 1;
        for(; i < n; i++){
            if(s[i] == ' ') continue;
            else break;
        }
        if(s[i] == '+') i++;
        else if(s[i] == '-') 
        {sign = -1; i++;}
        if(i < n && s[i] == '+') return 0;
        if(i < n && s[i] == '-') return 0;
        for(; i < n; i++){
            if(s[i] == '0') continue;
            else break;
        }
        for(; i < n; i++){
            if(s[i] > '9' || s[i] < '0'){
                break;
            }
            if(a * sign >= INT_MAX) return INT_MAX;
            if(a * sign <= INT_MIN) return INT_MIN;
            // 乘之前检查
            a *= 10;
            if(a * sign >= INT_MAX) return INT_MAX;
            if(a * sign <= INT_MIN) return INT_MIN;
            // 乘之后检查
            a += s[i] - '0';
            if(a * sign >= INT_MAX) return INT_MAX;
            if(a * sign <= INT_MIN) return INT_MIN;
            // 加以后检查
        }
        return sign * a;
    }
};