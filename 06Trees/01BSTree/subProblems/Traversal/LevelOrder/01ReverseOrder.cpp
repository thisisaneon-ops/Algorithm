// 【107】给你二叉树的根节点 `root` ，返回其节点值 **自底向上的层序遍历** 。 （即按从叶子节点所在层到根节点所在的层，逐层从左向右遍历）

// 牢记一件事，你永远不能也不太可能写出从二叉树子节点向上爬的函数，也没有必要，我们对于这种逆序输出的题目，只需要考虑将正序结果反转就可以了！

// 思想：只需要对层序遍历的结果做逆序处理即可！

vector<vector<int>>reverseLevelOrder(TreeNode* root){
    vector<vector<int>>v;
    if(root == nullptr){
        return v;
    }
    queue<TreeNode* >q;
   	q.push(root);
    while(!q.empty()){
		int cur_level_size = q.size();
        vector<int>cur_level;
        for(int i = 1; i <= cur_level_size; i++){
            TreeNode* front = q.front();
            q.pop();
            cur_level.push_back(front->val);
            if(front->left){
                q.push(front->left);
            }
            if(front->right){
                q.push(front->right);
            }
        }
        v.push_back(cur_level);
    }
    reverse(v.begin(), v.end());
    return v;
}