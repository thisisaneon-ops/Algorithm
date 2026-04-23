// 描述一个集合所有子集的有两种方式：
// 1. 子集树
// 2. 组合树
// 有什么区别？？
// -- 子集树是一颗二叉树，每层只关心当前元素选取与否，去重不方便
// -- 组合树是一颗多叉树，需要for循环遍历，去重方便

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

// 1. 子集树
int arr[] = {1,2,3};
const int length = sizeof(arr) / sizeof(arr[0]);
vector<int>x;
void func(int i){
    if(i == length){
        if(x.empty()) { cout << "nullset" << endl; }
        else{
            for(auto& u : x) { cout << u << " "; }
            cout << endl;
        }
    }
    else{
        x.push_back(arr[i]);
        func(i + 1);
        x.pop_back();
        func(i + 1);
    }
}
int main(){
    func(0);
    return 0;
}

// 2. 组合树
vector<int>arr = {1,2,3};
const int length = sizeof(arr) / sizeof(arr[0]);
vector<int>x;
void func(int i){
    if(x.empty()){
        cout << "nullset" << endl;
    }
    else{
        for(auto& u : x){
            cout << u << " ";
        }
        cout << endl;
    }
    for(int k = i; k < length; k++){
        x.push_back(arr[k]);
        func(k+1);
        x.pop_back();
    }
}
int main(){
    func(0);
    return 0;
}

// 组合树去重
int nums[] = {...};
int length = ...;
vector<int>x;
void func(int i)
{
    if(x.empty())
    {
        cout << "nullset" << endl;
    }
    else 
    {
        for(auto& u : x)
        {
            cout << u << " ";
        }
        cout << endl;
    }
    for(int j = i; j < length; j++)  // 不回头
    {
        // 去重2
        if(j > i && nums[j] == nums[j - 1])  // 跳过连续的相同元素
        {
            continue;
        }
        x.push_back(nums[j]);
        func(j + 1);  // 再次不回头保证了同一个组合不会反复出现，例如[1,2,2] [2,2,1] [2,1,2]  //去重1
        x.pop_back();
    }
}