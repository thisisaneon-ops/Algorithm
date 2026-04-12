/*
比96稍难，虽然主体思路完全一致，但问题所属类型完全不同；

举个例子：当所需分配的节点总数是 i时，96题并不关心这i个节点的具体数据；例如{0,1} {2,3} {101,102}对i来说完全一样，但是95不行，要求是所有满足条件的BST树，子问题没有重叠（96子问题是重叠的）

注意的问题：

1. 要能想到，每一层需要返回的是一个TreeNode* 数组，而非单一的TreeNode* 元素，因为每一层都可以返回若干种不同构造的子树根节点
2. 注意空层，必须push_back(nullptr)才可能成功，否则容器为空两个for循环进不去所有新节点都不能构造！
3. 注意TreeNode* root = new TreeNode(val)的创建时机，不可以服用否则指针关系混乱！
*/

vector<TreeNode*> generateTrees(int n) {
    vector<TreeNode*>ret;
    return build(1, n);
}
vector<TreeNode*> build(int start, int end){
    vector<TreeNode*>cur;
    if(start > end){
        cur.push_back(nullptr);
        return cur;
    }
    for(int i = start; i <= end; i++){
        vector<TreeNode*>leftTree = build(start, i - 1);
        vector<TreeNode*>rightTree = build(i + 1, end);
        for(auto l : leftTree){
            for(auto r : rightTree){
                TreeNode* node = new TreeNode(i);
                node->left = l;
                node->right = r;
                cur.push_back(node);
            }
        }
    }
    return cur;
}