// ###### [103]二叉树的锯齿状程序遍历

// 给你二叉树的根节点 `root` ，返回其节点值的 **锯齿形层序遍历** 。（即先从左往右，再从右往左进行下一层遍历，以此类推，层与层之间交替进行）。

// 思想：只需要对索引为奇数的层反转就可以了！

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
    for(int i = 1; i < v.size(); i+=2){
        reverse(v[i].begin(), v[i].end());
    }
    return v;
}