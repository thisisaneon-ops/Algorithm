/*
最直观：
给你二叉树的根节点 `root` ，返回其节点值的 **层序遍历** 。 （即逐层地，从左到右访问所有节点）。

常见解法有两种：

1. 我们知道层序遍历在只要求 cout << 打印结果的时候比较简单，只需要queue存储并释放读取即可，但是这里要求我们返回一个二维数组，这就是的我们不得不对每个节点明确地标记所在地具体层数！

   这就让我们想到用pair < TreeNode*, int > 打包数据
*/

vector<vector<int>>levelOrder(TreeNode* root){
    using pair = pair<TreeNode*, int>;
    vector<vector<int>>v;
    if(root == nullptr){
        return v;
    }
    queue<pair>q;
   	q.emplace(root, 0);
    while(!q.empty()){
        auto u = q.front();
        q.pop();
        int level = u.second;
        TreeNode* cur = u.first;
        if(level == v.size()){
            v.push_back({});
        }
        v[level].push_back(cur->val);
        if(cur->left){
            q.emplace(cur->left, level + 1);
        }
        if(cur->right){
            q.emplace(cur->right, level + 1);
        }
    }
    return v;
}


// 能不能降低空间复杂度？？
// 2. ###### Batch Processing 批量处理

// 思想：每轮只处理当前层，通过队列大小控制处理元素，利用while内部嵌套for循环的方式保证节点按层处理即可；

// 优点：无level的额外内开销，更节省空间；时间基本相同

vector<vector<int>>levelOrder(TreeNode* root){
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
    return v;
}