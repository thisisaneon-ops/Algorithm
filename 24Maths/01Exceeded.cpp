#include<iostream>
using namespace std;

// * 力扣 50 Pow(x, n)
#ifdef DEBUG

/*
* 力扣 50 Pow(x, n)
* 实现 pow(x, n) ，即计算 x 的整数 n 次幂函数（即，xn ）。
*/
class Solution {
public:
    double helper(double x, uint32_t n) {
        if (n == 1 || n == 0) {
            return x;
        }
        if (n % 2 == 0) {
            double ans = helper(x, n / 2);
            return ans * ans;
        }
        else {
            double ans = helper(x, n / 2);
            return ans * ans * x;
        }
    }
    double myPow(double x, int n) {
        if (x == 1 || n == 0) {
            return 1;
        }
        long long N = n;
        if (n < 0) {
            return 1 / helper(x, abs(N));
        }
        else {
            return helper(x, N);
        }
    }
}; 
#endif // DEBUG

// * 力扣 8 字符串转整数

/*
* 力扣 8 字符串转整数
* 请你来实现一个 myAtoi(string s) 函数，使其能将字符串转换成一个 32 位有符号整数。
函数 myAtoi(string s) 的算法如下：

空格：读入字符串并丢弃无用的前导空格（" "）
符号：检查下一个字符（假设还未到字符末尾）为 '-' 还是 '+'。如果两者都不存在，则假定结果为正。
转换：通过跳过前置零来读取该整数，直到遇到非数字字符或到达字符串的结尾。如果没有读取数字，则结果为0。
舍入：如果整数数超过 32 位有符号整数范围 [−231,  231 − 1] ，需要截断这个整数，使其保持在这个范围内。具体来说，小于 −231 的整数应该被舍入为 −231 ，大于 231 − 1 的整数应该被舍入为 231 − 1 。
返回整数作为最终结果。
*/
uint32_t myAtoi(string s) {
    
}


// * 43 字符串相乘
/*
* 43 字符串相乘
* 给定两个以字符串形式表示的非负整数 num1 和 num2，返回 num1 和 num2 的乘积，它们的乘积也表示为字符串形式。
注意：不能使用任何内置的 BigInteger 库或直接将输入转换为整数。
*/
string myMultiply(string num1, string num2) {

}


// * 力扣 7 整数反转
/*
* 力扣 7 整数反转
* 给你一个 32 位的有符号整数 x ，返回将 x 中的数字部分反转后的结果。
如果反转后整数超过 32 位的有符号整数的范围 [−231,  231 − 1] ，就返回 0。
假设环境不允许存储 64 位整数（有符号或无符号）。
*/
uint32_t reverseInt(uint32_t x) {

}