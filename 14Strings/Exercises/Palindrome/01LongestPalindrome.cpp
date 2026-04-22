// [5. 最长回文子串](https://leetcode.cn/problems/longest-palindromic-substring/)

// 中心扩散; 从头至尾依次遍历, 奇偶都算，更新start和Len

string LongestPalindrome(string s){
    int len = 0;
    int start = 0;
    for(int i = 0; i < s.size(); i++){
        // 先考虑奇数情况
        int odd = 1;
        for(int dis = 1; i + dis < s.size() && i - dis >= 0; dis++){
            if(s[i + dis] == s[i - dis]){
                odd += 2;
            }
            else break;
        }
        if(odd > len){
            len = odd;
            start = i - (odd - 1) / 2;
        }
        int even = 0;
        for(int dis = 0; i + 1 + dis < s.size() && i - dis >= 0; dis++){
            if(s[i + 1 + dis] == s[i - dis]){
                even += 2;
            }
            else break;
        }
        if(even > len){
            len = even;
            start = i - (even - 1) / 2;
        }
    }
    return s.substr(start, len);
}


// 马拉车

// 马拉车思想是对中心扩散法的优化，引入了r数组记录每位的最长回文子串半径r

// 还没写