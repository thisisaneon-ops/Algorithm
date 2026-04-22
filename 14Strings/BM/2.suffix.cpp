#include<iostream>
using namespace std;

void getSuff(string &t, vector<int>& suff){
    int m = t.size();
    suff.resize(m);
    suff[m-1] = m;
    for(int i = m - 1; i >= 0; i--){
        int j = i;    // 指向当前比较的前缀的最后一位
        int k = m-1;  // 指向最后一位
        while(j >= 0 && t[j] == t[k]){
            j--; 
            k--;
        }
        suff[i] = i - j;
    }
}

int main(){
    string t = "abcdabc";
    vector<int>suff;
    getSuff(t, suff);
    for(int i = 0; i < t.size(); i++){
        cout << t[i] << " : " << suff[i] << endl;
    }
    return 0;
}