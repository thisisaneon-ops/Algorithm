/*
* 并查集，一种特殊的数据结构，常被使用在无向图连通性等，作为替代DFS BFS的算法
*/
#include<iostream>
#include<vector>
using namespace std;

class UnionFind{
private:
    vector<int>parent;
    int count;
public:
    UnionFind(const vector<int>& arr){
        const int n = arr.size();
        count = n;
        parent.resize(n, 0);
        for(int i = 0; i < n; i++){
            parent[i] = i;
        }
    }
    int find(int i){
        if(parent[i] != i){
            parent[i] = find(parent[i]);
        }
        return parent[i];
    }
    void Union(int x, int y){
        int rootX = find(x);
        int rootY = find(y);
        if(rootX != rootY){
            parent[rootX] = rootY;
            count--;
        }
    }
    int getCount(){
        return count;
    }
};