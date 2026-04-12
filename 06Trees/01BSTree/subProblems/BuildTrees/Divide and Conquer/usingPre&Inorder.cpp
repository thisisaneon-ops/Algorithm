TreeNode* rebuildTree(vector<int>& pre, vector<int>& in){
    return rebuild(pre, 0, pre.size() - 1, in, 0, in.size() - 1);
}
TreeNode* rebuild(vector<int>& pre, int i, int j, vector<int>& in, int m, int n){
    if(i > j || m > n){
        return nullptr;
    }
    TreeNode* node = new TreeNode(pre[i]);
    int pos = m;
    for(; pos <= n; pos++){
        if(in[pos] == pre[i]){
            break;
        }
    }
    TreeNode* left = rebuild(pre, i + 1, pos - m + i, in, m, pos - 1);
    TreeNode* right = rebuild(pre, pos - m + i + 1, j, in, pos + 1, n);
    node->left = left;
    node->right = right;
    return node;
}

/*
不难发现时间复杂度高，我们想办法降时间复杂度：

1. O(NLogN)  --有局限性；对应的是二分搜索思想，但是这道题没有明确写出是一颗BST树！所以只有在图示情况下这种思路正确！

2. O(N)  --哈希表存储

   我们对每一个数据在inOrder中的位置都做一个记录，这样在每次找pos的时候就无需线性遍历！
*/

TreeNode* rebuildTree(vector<int>& pre, vector<int>& in){
    unordered_map<int, int>dic;
    for(int i = 0; i < in.size(); i++){
        dic[in[i]] = i;
    }
    return rebuild(pre, 0, pre.size()-1, 0, in.size()-1, dic);
}
TreeNode* rebuild(vector<int>& pre, int i, int j, int m, int n, unordered_map<int, int>& dic)  /*in数组完全可以不传，有dic即可*/{
    if(i > j || m > n){
        return nullptr;
    }
    TreeNode* node = new TreeNode(pre[i]);
    int pos = dic[pre[i]];
    TreeNode* left = rebuild(pre, i + 1, pos - m + i, in, m, pos - 1);
    TreeNode* right = rebuild(pre, pos - m + i + 1, j, in, pos + 1, n);
    node->left = left;
    node->right = right;
    return node;
}