#include<iostream>
using namespace std;

int* getNext(string &t){
    int j = 0;
    int k = -1;
    int* next = new int[t.size()];
    next[j] = k;
    while(j < t.size() - 1){
        if(k == -1 || t[j] == t[k]){
            j++;
            k++;
            next[j] = k;
        }
        else{
            k = next[k];
        }
    }
    return next;
}

int KMP(string & s, string & t){
    int i = 0;
    int j = 0;
    int* next = getNext(t);
    while(i < s.size()){
        if(j == -1 || s[i] == t[j]){
            i++;
            j++;
            if(j == t.size()){
                return i - j;
            }
        }
        else{
            j = next[j];
        }
    }
    return -1;
}

int main(){
    string s = "abcabdabcd";
    string t = "abcd";
    cout << KMP(s, t) << endl;
    return 0;
}