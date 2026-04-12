bool isBalance(TreeNode* node)
{
    if(node == nullptr)
    {
        return true;
    }
    if(!isBalance(node->left))
    {
        return false;
    }
    int left = height(node->left);
    int right = height(node->right);
    if(abs(left - right) > 1)
    {
        return false;
    }
    return isBalance(node->right);
}
int isBalance(TreeNode* node, bool& flag)
{
    if(node == nullptr)
    {
        return 0;
    }
    int left = isBalance(node->left, flag);
    int right = isBalance(node->right, flag);
    if(abs(left - right) > 1)
    {
        flag = false;
    }
    return max(left, right) + 1;
}