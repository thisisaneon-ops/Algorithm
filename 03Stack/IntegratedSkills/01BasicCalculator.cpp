/*
##### [224]基本计算器

设计一个计算器，处理string类型的数据；

字符串内包括 '+'  '-'  '('  ')'  '数字'  ' '

**核心思想：**

1. 利用栈保存遇到括号后前面记录的一计算结果和即将操作的数字的正负号
2. 利用num 和 cal两个变量记录当前数字和计算总结果
3. 利用sign记录下面一个数字的符号
*/

class Solution {
public:
    int calculate(string s) {
        long long num = 0;
        long long cal = 0;
        int sign = 1;
        stack<int>stk;
        for(int i = 0; i < s.size(); i++)
        {
            if(s[i] == ' ')
            {
                continue;
            }
            else if(s[i] == '+')
            {
                cal = cal + num * sign;
                sign = 1;  // 为下一个数字做准备
                num = 0;  // 当前数字记录完毕
            }
            else if(s[i] == '-')
            {
                cal = cal + num * sign;
                sign = -1;
                num = 0;
            }
            else if(s[i] == '(')  // 遇到左括号，保存当前的cal 和sign
            {
                stk.push(cal);
                stk.push(sign);
                cal = 0;
                num = 0;
                sign = 1;
            }
            else if(s[i] == ')')
            {
                int l_sign = stk.top();
                stk.pop();
                long long l_cal = stk.top();
                stk.pop();
                cal = cal + sign * num;
                num = 0;
                sign = 1;
                cal = l_cal + l_sign * cal;
            }
            else
            {
                num = num * 10 + (s[i] - '0');
            }
        }
        return cal + sign * num;
    }
};