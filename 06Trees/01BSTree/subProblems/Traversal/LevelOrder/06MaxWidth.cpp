// 给你一棵二叉树的根节点 `root` ，返回树的 **最大宽度** 。

// 树的 **最大宽度** 是所有层中最大的 **宽度** 。

// 每一层的 **宽度** 被定义为该层最左和最右的非空节点（即，两个端点）之间的长度。将这个二叉树视作与满二叉树结构相同，两端点间会出现一些延伸到这一层的 `null` 节点，这些 `null` 节点也计入长度

// **注意点：**

// 1. 要结合完全二叉树（二叉堆）的性质，即父节点和左右孩子有严格的数学关系 i -- 2 * i + 1 -- 2 * i + 2
// 2. 要考虑pair的引入原因，因为仅TreeNode* node一个数据无法表征他在当前层的存储位置，也就无法计算宽度，因此必须使用pair<TreeNode*, long long(int)>
// 3. 要考虑整数溢出问题，一开始写int的时候错误，因为int在不断*2的过程中，一旦遇到一边倒的树必然很快就因为层数多带来溢出问题，因此我们要将数组的int idx的绝对位置换成long long 的层内相对位置！

int widthOfBinaryTree(TreeNode* root) {
    using pair = pair<TreeNode*, long long>;
    long long maxwidth = 0;
    queue<pair>q;
    q.emplace(root, 0);
    while(!q.empty()){
        int cur_size = q.size();
        long long firstidx = q.front().second;
        long long width = 1;
        bool flag = true;
        for(int k = 0; k < cur_size; k++){
            auto u = q.front();
            q.pop();
            width = u.second - firstidx + 1;
            long long idx = width - 1;
            TreeNode* node = u.first;
            // u.second如果不处理可能太大导致溢出，所以我们只需要对u.second做一下统一的数据处理即可！
            if(node->left){
                q.emplace(node->left, 2 * idx + 1);
            }
            if(node->right){
                q.emplace(node->right, 2 * idx + 2);
            }
        }
        maxwidth = max(maxwidth, width);
    }
    return maxwidth;
}