// 小心空子树需要单独处理！不是合法路径！
class Solution {
public:
    int minDepth(TreeNode* root) {
        return depth(root);
    }
    int depth(TreeNode* node){
        if(node == nullptr){
            return 0;
        }
        int left = depth(node->left);
        int right = depth(node->right);
        if(left != 0 && right != 0){
            return min(left, right) + 1;
        }
        return left == 0 ? right + 1 : left + 1;
    }
};