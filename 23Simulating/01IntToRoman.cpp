#include<iostream>
#include<vector>
#include<stack>
using namespace std;

// * 力扣 12 整数转罗马数字
#ifdef DEBUG
/*
* 力扣 12 整数转罗马数字
* 罗马数字是通过添加从最高到最低的小数位值的转换而形成的。将小数位值转换为罗马数字有以下规则：
如果该值不是以 4 或 9 开头，请选择可以从输入中减去的最大值的符号，将该符号附加到结果，减去其值，然后将其余部分转换为罗马数字。
如果该值以 4 或 9 开头，使用 减法形式，表示从以下符号中减去一个符号，例如 4 是 5 (V) 减 1 (I): IV ，9 是 10 (X) 减 1 (I)：IX。仅使用以下减法形式：4 (IV)，9 (IX)，40 (XL)，90 (XC)，400 (CD) 和 900 (CM)。
只有 10 的次方（I, X, C, M）最多可以连续附加 3 次以代表 10 的倍数。你不能多次附加 5 (V)，50 (L) 或 500 (D)。如果需要将符号附加4次，请使用 减法形式。
给定一个整数，将其转换为罗马数字。
*/

// 一种很麻烦的方式：
class Solution {
public:
    int exp(int i) {
        int l = 1;
        for (int k = 1; k < i; k++) {
            l *= 10;
        }
        return l;
    }
    string intToRoman(int num) {
        vector<int> v;
        while (num != 0) {
            int remainder = num % 10;
            num /= 10;
            v.push_back(remainder);
        }
        // 我们可以就用3749来模拟，否则空泛有点难想
        // 如果是3749，那么v里现在存储的就是9 4 7 3
        const int n = v.size(); // 标记位数
        int multi = exp(n);     // 乘积因子
        string ret;
        // 反转一下
        reverse(v.begin(), v.end());
        for (int i = 0; i < n; i++) {
            switch (multi) {
            case 1000: {
                int digit = v[i];
                for (int k = 0; k < digit; k++) {
                    ret += "M";
                }
                break;
            }
            case 100: {
                if (v[i] == 4 || v[i] == 9) {
                    if (v[i] == 4) {
                        ret += "CD";
                    }
                    else {
                        ret += "CM";
                    }
                }
                else {
                    if (v[i] < 4) {
                        for (int k = 0; k < v[i]; k++) {
                            ret += "C";
                        }
                    }
                    else {
                        ret += "D";
                        for (int k = 0; k < v[i] - 5; k++) {
                            ret += "C";
                        }
                    }
                }
                break;
            }
            case 10: {
                if (v[i] == 4 || v[i] == 9) {
                    if (v[i] == 4) {
                        ret += "XL";
                    }
                    else {
                        ret += "XC";
                    }
                }
                else {
                    if (v[i] < 4) {
                        for (int k = 0; k < v[i]; k++) {
                            ret += "X";
                        }
                    }
                    else {
                        ret += "L";
                        for (int k = 0; k < v[i] - 5; k++) {
                            ret += "X";
                        }
                    }
                }
                break;
            }
            case 1: {
                if (v[i] == 4 || v[i] == 9) {
                    if (v[i] == 4) {
                        ret += "IV";
                    }
                    else {
                        ret += "IX";
                    }
                }
                else {
                    if (v[i] < 4) {
                        for (int k = 0; k < v[i]; k++) {
                            ret += "I";
                        }
                    }
                    else {
                        ret += "V";
                        for (int k = 0; k < v[i] - 5; k++) {
                            ret += "I";
                        }
                    }
                }
                break;
            }
            }
            multi /= 10;
        }
        return ret;
    }
}; 


// 思路：种子思想 RomanSeeds
class Solution {
public:
    vector<string>hundreds = { "","C","CC","CCC","CD","D","DC","DCC","DCCC","CM" };
    vector<string>tens = { "","X","XX","XXX","XL","L","LX","LXX","LXXX","XC" };
    vector<string>ones = { "","I","II","III","IV","V","VI","VII","VIII","IX" };
    string intToRoman(int num) {
        stack<int>s;
        while (num != 0) {
            int remainder = num % 10;
            num /= 10;
            s.push(remainder);
        }
        const int n = s.size();
        string ret;
        // s里的元素是反的，高位在栈顶
        for (int i = n; i > 0; i--) {
            auto top = s.top();
            s.pop();
            if (i == 4) {
                for (int k = 0; k < top; k++) {
                    ret += "M";
                }
            }
            else if (i == 3) {
                ret += hundreds[top];
            }
            else if (i == 2) {
                ret += tens[top];
            }
            else {
                ret += ones[top];
            }
        }
        return ret;
    }
};

// 撤去栈和循环，直接维护数字
class Solution {
public:
    vector<string>hundreds = { "","C","CC","CCC","CD","D","DC","DCC","DCCC","CM" };
    vector<string>tens = { "","X","XX","XXX","XL","L","LX","LXX","LXXX","XC" };
    vector<string>ones = { "","I","II","III","IV","V","VI","VII","VIII","IX" };
    string intToRoman(int num) {
        string ret;
        int thousand = num / 1000;
        for (int i = 0; i < thousand; i++) {
            ret += "M";
        }
        int hundred = (num / 100) % 10;
        ret += hundreds[hundred];
        int ten = (num / 10) % 10;
        ret += tens[ten];
        int one = num % 10;
        ret += ones[one];
        return ret;
    }
};
#endif // DEBUG

