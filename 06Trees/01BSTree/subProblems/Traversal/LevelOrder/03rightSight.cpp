/*
###### [199]二叉树的右视图

请输出二叉树一种可能的右视图

相对效率更低
*/
vector<int> rightSideView(TreeNode* root) {
    vector<vector<int>>v;
    if(root == nullptr){
        return {};
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
    vector<int>ret;
    for(int i = 0; i < v.size(); i++){
        ret.push_back(v[i][v[i].size() - 1]);
    }
    return ret;
}


// 我们看出，每层起始完全不需要维护一个完整数组，只需要一个变量捕捉，遇到层内的新元素直接替换即可！
// 优化：
vector<int> rightSideView(TreeNode* root) {
    vector<int>v;
    if(root == nullptr){
        return {};
    }
    queue<TreeNode* >q;
    q.push(root);
    while(!q.empty()){
        int cur_level_size = q.size();
        vector<int>cur_level;
        for(int i = 1; i <= cur_level_size; i++){
            TreeNode* front = q.front();
            q.pop();
            // 只有最后一个元素才推，否则直接孩子入栈+弹出
            if(i == cur_level_size){
                v.push_back(front->val);
            }
            if(front->left){
                q.push(front->left);
            }
            if(front->right){
                q.push(front->right);
            }
        }
    }
    return v;
}