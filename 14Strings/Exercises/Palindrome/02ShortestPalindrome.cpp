// [214. 最短回文串](https://leetcode.cn/problems/shortest-palindrome/)
// 给定一个字符串 ***s***，你可以通过在字符串前面添加字符将其转换为回文串。找到并返回可以用这种方式转换的最短回文串。
// 例如：
// 输入：aacecaaa
// 输出：aaacecaaa

/*
思路：
找到前缀里最大的回文串，把剩余非回文部分反转追加到开头即可
将原串反转追加到原串后面，拼接成 s+'#'+rev 的形式，利用next数组找到最长回文前缀
*/

string ShortestPalindrome(string s){
    string rev = s;
    reverse(rev.begin(), rev.end());
    string d = s + "#" + rev;
    vector<int>next(d.size() + 1, 0);
    int j = 0;
    int k = -1;
    next[j] = k;
    while(j < d.size()){
        if(k == -1 || d[j] == d[k]){
            k++;
            j++;
            next[j] = k;
        }
        else k = next[k];
    }
    int len = next[d.size()];
    rev += d.substr(len, s.size() - len);
    return rev;
}