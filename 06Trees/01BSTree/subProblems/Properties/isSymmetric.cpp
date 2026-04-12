bool isSym(TreeNode* left, TreeNode* right)
{
    if(left == nullptr && right == nullptr)
    {
        return true;
    }   
    if(left == nullptr)
    {
        return false;
    }
    if(right == nullptr)
    {
        return false;
    }
    if(comp(left->val, right->val) || comp(right->val, left->val))
    {
        return false;
    }
    return isSym(left->right, right->left) && isSym(left->left, right->right);
}
// isSym  有剪枝的写法
bool isSym(TreeNode* left, TreeNode* right)
{
    if(left == nullptr && right == nullptr)
    {
        return true;
    }   
    if(left == nullptr)
    {
        return false;
    }
    if(right == nullptr)
    {
        return false;
    }
    if(!isSym(left->left, right->right))
    {
        return false;
    }
    if(comp(left->val, right->val) || comp(right->val, left->val))
    {
        return false;
    }
    return isSym(left->right, right->left);
}