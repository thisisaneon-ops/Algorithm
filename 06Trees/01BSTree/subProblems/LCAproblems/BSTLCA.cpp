/*
###### [235]二叉搜索树的最近公共祖先

给定一个二叉搜索树, 找到该树中两个指定节点的最近公共祖先。

[最近公共祖先的定义为：“对于有根树 T 的两个结点 p、q，最近公共祖先表示为一个结点 x，满足 x 是 p、q 的祖先且 x 的深度尽可能大（**一个节点也可以是它自己的祖先**）。”

例如，给定如下二叉搜索树:  root = [6,2,8,0,4,7,9,null,null,3,5]
*/

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    int upper = max(q->val,p->val);
    int lower = min(q->val,p->val);
    return LCA(root, lower, upper);
}
TreeNode* LCA(TreeNode* node, int lower, int upper){
    if(node == nullptr){
        return nullptr;
    }
    int val = node->val;
    if(val < lower){
        return LCA(node->right, lower, upper);
    }
    else if(val > upper){
        return LCA(node->left, lower, upper);
    }
    else{
        return node;
    }
}