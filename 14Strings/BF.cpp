#include<iostream>
using namespace std;

int BF(string& s, string& t){
    int i = 0;
    int j = 0;
    while(i < s.size()){
        if(s[i] == t[j]){
            i++;
            j++;
            if(j == t.size()){
                return i - j;
            }
        }
        else{
            i = i - j + 1;
            j = 0;
        }
    }
    return -1;
}

int main(){
    string s = "abcabdabcd";
    string t = "abcd";
    cout << BF(s, t) << endl;
    return 0;
}