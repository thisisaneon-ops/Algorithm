#include<iostream>
using namespace std;

void getBC(string &t, vector<int>&bc){
    bc.resize(128);
    for(int i = 0; i < 128; i++){
        bc[i] = -1;
    }
    for(int i = 0; i < t.size(); i++){
        bc[t[i]] = i;
    }
    return;
}

int main(){
    string t = "abcabdcs";
    vector<int>bc;
    getBC(t, bc);
    return 0;
}