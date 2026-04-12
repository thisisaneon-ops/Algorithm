// [505]找出每层最大的元素

vector<int> largestValues(TreeNode* root) {
    vector<int>v;
    if(root == nullptr){
        return v;
    }
    queue<TreeNode*>q;
    q.push(root);
    while(!q.empty()){
        int cur_size = q.size();
        int max = q.front()->val;
        for(int i = 1; i <= cur_size; i++){
            TreeNode* front = q.front();
            q.pop();
            if(front->val > max){
                max = front->val;
            }
            if(front->left){
                q.push(front->left);
            }
            if(front->right){
                q.push(front->right);
            }
        }
        v.push_back(max);
    }
    return v;
}

// 不难看出 199和505完全是同一个模式：

queue<Node*>Q;
Q.push(root);
while(!Q.empty()){
    int cur_size = Q.size();
    // 某某条件
    for(int i = 0; i < cur_size; i++){
        auto front = Q.front();
        // 对队首元素做某种操作
        Q.pop();
        // 比较并处理
    }
    // 对某某条件做回收
}
return xx;