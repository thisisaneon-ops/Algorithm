TreeNode* rebuildTree(vector<int>& post, vector<int>& in){
    return rebuild(post, 0, post.size() - 1, in, 0, in.size() - 1);
}
TreeNode* rebuild(vector<int>& post, int i ,int j, vector<int>& in, int m, int n){
    if(i > j || m > n){
        return nullptr;
    }
    TreeNode* node = new TreeNode(post[j]);
    int pos = i;
    for(; pos < n; pos++){
        if(in[pos] == post[j]){
            break;
        }
    }
    node->left = rebuild(post, i, pos - m + i - 1, in, m, pos - 1);
    node->right = rebuild(post, pos - m + i, j - 1, in, pos + 1, n);
    return node;
}

TreeNode* rebuildTree(vector<int>& in, vector<int>& post){
    unordered_map<int, int>dic;
    for(int i = 0; i < in.size(); i++){
        dic[in[i]] = i;
    }
    return rebuild(0, in.size() - 1, post, 0, post.size() - 1, dic);
}
TreeNode* rebuild(int m, int n, vector<int>& post, int i, int j, unordered_map<int, int>& dic){
    if(m > n || i > j){
        return nullptr;
    }
    TreeNode* node = new TreeNode(post[j]);
    int pos = dic[post[j]];
    int len = pos - m;
    node->left = rebuild(m, pos - 1, post, i, len + i - 1, dic);
    node->right = rebuild(pos + 1, n, post, len + i, j - 1, dic);
    return node;
}

/*
**Q：既然 BST 的中序是有序的，为什么重建普通二叉树还要给中序序列？**

**A：** 因为普通二叉树的“结构信息”和“数值大小”是解耦的。

- 在 **BST** 中：位置决定数值（左小右大），所以知道前序就能推导出位置。
- 在**普通树**中：位置是随意的。`inorder` 序列存在的意义不是提供“大小关系”，而是提供**“左右边界”**。
- 如果只有 `preorder` 且不是 BST，你无法知道一个节点到底是左孩子还是右孩子（除非像我们之前说的，引入空节点标记 `#`）。
*/